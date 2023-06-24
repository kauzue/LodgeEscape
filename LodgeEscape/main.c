#include "function.h"

#define PORT_NUM 1252
#define BLOG_SIZE 5

SOCKET SetTCPServer(short pnum, int blog);//��� ���� ����
SOCKET sock_base[FD_SETSIZE];
HANDLE hev_base[FD_SETSIZE];
int cnt;

int main(void)
{
    Init();

    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);//���� �ʱ�ȭ	
    SOCKET sock = SetTCPServer(PORT_NUM, BLOG_SIZE);//��� ���� ����

    if (sock == -1) {
        perror("��� ���� ����");
        WSACleanup();
        return 0;
    }

    AcceptLoop(sock);//Accept Loop
    WSACleanup();//���� ����ȭ
    return 0;
}

SOCKET SetTCPServer(short pnum, int blog)
{
    SOCKET sock;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//���� ����
    if (sock == -1) {
        return -1;
    }

    SOCKADDR_IN servaddr = { 0 };//���� �ּ�
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr = GetDefaultMyIP();
    servaddr.sin_port = htons(pnum);

    int re = 0;
    //���� �ּҿ� ��Ʈ��ũ �������̽� ����
    re = bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (re == -1) {
        return -1;
    }
    re = listen(sock, blog);//�� �α� ť ����
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
        dosock = accept(sock, (SOCKADDR*)&cliaddr, &len);//���� ����
        if (dosock == -1)
        {
            perror("Accept ����");
            break;
        }
        printf("%s:%d�� ���� ��û ����\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
        _beginthread(DoIt, 0, (void*)dosock);
    }
    closesocket(sock);//���� �ݱ�
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

    int len = sizeof(cliaddr);
    int choice;
    char ID[MAX_MSG_LEN] = "";

    player_t s_players[NUM_MAX_PLAYERS];

    getpeername(dosock, (SOCKADDR*)&cliaddr, &len);//��� ���� �ּ� �˾Ƴ���
    char msg[MAX_MSG_LEN] = "";
    if (loginmenu(dosock)) {
        OpenMainMenu();

    }

    while (recv(dosock, msg, strlen(msg), 0) > 0) {//����
        printf("%s:%d �κ��� recv:%s\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), msg);
    }

    printf("%s�� ��� ����\n", ID);
    closesocket(dosock);//���� �ݱ�
}

void AcceptProc(int index)
{
    SOCKADDR_IN cliaddr = { 0 };
    int len = sizeof(cliaddr);

    SOCKET dosock = accept(sock_base[0], (SOCKADDR*)&cliaddr, &len);

    if (cnt == FD_SETSIZE / 20) {
        printf("ä�� ���� �� ���� %s:%d �������� ���Ͽ����ϴ�. \n", inet_ntoa(cliaddr.sin_addr),
            ntohs(cliaddr.sin_port));
        closesocket(dosock);
        return;
    }
    AddNetworkEvent(dosock, FD_READ | FD_CLOSE);
    printf("ä�� �濡 %s:%d �����Ͽ����ϴ�. \n", inet_ntoa(cliaddr.sin_addr),
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
    printf("[%s:%d]���� �����̽��ϴ�. \n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

    closesocket(sock_base[index]);
    WSACloseEvent(hev_base[index]);
    cnt--;
    sock_base[index] = sock_base[cnt];
    hev_base[index] = hev_base[cnt];

    char smsg[MAX_MSG_LEN];
    sprintf(smsg, "[%s:%d]���� �����̽��ϴ�. \n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
    for (int i = 1; i < cnt; i++) {
        send(sock_base[i], smsg, MAX_MSG_LEN, 0);
    }
}