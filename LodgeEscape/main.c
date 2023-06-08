#include "function.h"

#define PORT_NUM 1252
#define BLOG_SIZE 5

SOCKET SetTCPServer(short pnum, int blog);//대기 소켓 설정
SOCKET sock_base[FD_SETSIZE];
HANDLE hev_base[FD_SETSIZE];
int cnt;

int main(void)
{
    Init();

	WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);//윈속 초기화	
    SOCKET sock = SetTCPServer(PORT_NUM, BLOG_SIZE);//대기 소켓 설정

    if (sock == -1) {
        perror("대기 소켓 오류");
        WSACleanup();
        return 0;
    }

    AcceptLoop(sock);//Accept Loop
    WSACleanup();//윈속 해제화
    return 0;
}

SOCKET SetTCPServer(short pnum, int blog)
{
    SOCKET sock;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//소켓 생성
    if (sock == -1) {
        return -1;
    }

    SOCKADDR_IN servaddr = { 0 };//소켓 주소
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr = GetDefaultMyIP();
    servaddr.sin_port = htons(pnum);

    int re = 0;
    //소켓 주소와 네트워크 인터페이스 결합
    re = bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (re == -1) {
        return -1;
    }
    re = listen(sock, blog);//백 로그 큐 설정
    if (re == -1) {
        return -1;
    }
    return sock;
}

void AcceptLoop(SOCKET sock)
{
    SOCKET dosock;
    SOCKADDR_IN cliaddr = { 0 };
    int len = sizeof(cliaddr);
    while (true)
    {
        dosock = accept(sock, (SOCKADDR*)&cliaddr, &len);//연결 수락
        if (dosock == -1)
        {
            perror("Accept 실패");
            break;
        }
        printf("%s:%d의 연결 요청 수락\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
        _beginthread(DoIt, 0, (void*)dosock);
    }
    closesocket(sock);//소켓 닫기
}

HANDLE AddNetworkEvent(SOCKET sock, long net_event)
{
    HANDLE hev = WSACreateEvent();
    sock_base[cnt] = sock;
    hev_base[cnt] = hev;
    cnt++;

    WSAEventSelect(sock, hev, net_event);
    return hev;
}

void EventLoop(SOCKET sock)
{
    AddNetworkEvent(sock, FD_ACCEPT);
    while (true) {
        int index = WSAWaitForMultipleEvents(cnt, hev_base, false, INFINITE, false);

        WSANETWORKEVENTS net_events;
        WSAEnumNetworkEvents(sock_base[index], hev_base[index], &net_events);

        switch (net_events.lNetworkEvents) {
        case FD_ACCEPT:
            AcceptProc(index);
            break;

        case FD_READ:
            ReadProc(index);
            break;

        case FD_CLOSE:
            CloseProc(index);
            break;
        }
    }
    closesocket(sock);
}

void DoIt(void* param)
{
    SOCKET dosock = (SOCKET)param;
    SOCKADDR_IN cliaddr = { 0 };
    player_t player[NUM_MAX_PLAYERS];
    int len = sizeof(cliaddr);
    int choice;
    getpeername(dosock, (SOCKADDR*)&cliaddr, &len);//상대 소켓 주소 알아내기
    char msg[MAX_MSG_LEN];
    send(dosock,"Init", 5, 0);
    int r_num = loginmenu(dosock, msg);
    send(dosock, "친구와 함께 여관에 놀러왔고 여관에 들어서자마자 우리는 졸려 잠이 들었다.잠에서 깨어나서 주위를 둘러보니", 104, 0);//송신

    while (recv(dosock, msg, strlen(msg), 0) > 0) {//수신
        printf("%s:%d 로부터 recv:%s\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), msg);
        if (player[r_num].p_num == 1) {
            player1(dosock, msg[MAX_MSG_LEN]);
        }
    }

    printf("%s:%d와 통신 종료\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
    closesocket(dosock);//소켓 닫기
}

void AcceptProc(int index)
{
    SOCKADDR_IN cliaddr = { 0 };
    int len = sizeof(cliaddr);

    SOCKET dosock = accept(sock_base[0], (SOCKADDR*)&cliaddr, &len);

    if (cnt == FD_SETSIZE / 20) {
        printf("채팅 방이 꽉 차서 %s:%d 입장하지 못하였습니다. \n", inet_ntoa(cliaddr.sin_addr),
            ntohs(cliaddr.sin_port));
        closesocket(dosock);
        return;
    }
    AddNetworkEvent(dosock, FD_READ | FD_CLOSE);
    printf("채팅 방에 %s:%d 입장하였습니다. \n", inet_ntoa(cliaddr.sin_addr),
        ntohs(cliaddr.sin_port));
}

void ReadProc(int index)
{
    char msg[MAX_MSG_LEN];
    recv(sock_base[index], msg, MAX_MSG_LEN, 0);

    SOCKADDR_IN cliaddr = { 0 };
    int len = sizeof(cliaddr);

    getpeername(sock_base[index], (SOCKADDR*)&cliaddr, &len);

    char smsg[MAX_MSG_LEN];
    sprintf(smsg, "[%s:%d]:%s", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), msg);
    for (int i = 1; i < cnt; i++) {
        send(sock_base[i], smsg, MAX_MSG_LEN, 0);
    }
}

void CloseProc(int index)
{
    SOCKADDR_IN cliaddr = { 0 };
    int len = sizeof(cliaddr);

    getpeername(sock_base[index], (SOCKADDR*)&cliaddr, &len);
    printf("[%s:%d]님이 나가셨습니다. \n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

    closesocket(sock_base[index]);
    WSACloseEvent(hev_base[index]);
    cnt--;
    sock_base[index] = sock_base[cnt];
    hev_base[index] = hev_base[cnt];

    char smsg[MAX_MSG_LEN];
    sprintf(smsg, "[%s:%d]님이 나가셨습니다. \n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
    for (int i = 1; i < cnt; i++) {
        send(sock_base[i], smsg, MAX_MSG_LEN, 0);
    }
}
