#pragma comment(lib,"ws2_32")
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdbool.h>
#include <process.h>

#include "winsock.h"
#include "game.h"

void StartWinsock()
{
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    SOCKET sock = SetTCPServer(PORT_NUM, BLOG_SIZE);

    if (sock == -1) {
        perror("대기 소켓 오류");
        WSACleanup();
        return 0;
    }

    SOCKET serversock;
    SOCKADDR_IN cliaddr = { 0 };

    int len = sizeof(cliaddr);

    while (true) {
        serversock = accept(sock, (SOCKADDR*)&cliaddr, &len);
        if (serversock == -1) {
            perror("Accept 실패");
        }
        else {
            printf("%s:%d의 연결 요청 수락\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
            _beginthread(Game_Login, 0, serversock);
        }
    }

    closesocket(sock);
}

IN_ADDR GetDefaultMyIP()
{
    char localhostname[MAX_PATH];
    IN_ADDR addr = { 0, };
    if (gethostname(localhostname, MAX_PATH) == SOCKET_ERROR)
    {
        return addr;
    }
    HOSTENT* ptr = gethostbyname(localhostname);
    while (ptr && ptr->h_name)
    {
        if (ptr->h_addrtype == PF_INET)
        {
            memcpy(&addr, ptr->h_addr_list[0], ptr->h_length);
            break;
        }
        ptr++;
    }
    return addr;
}

SOCKET SetTCPServer(short pnum, int blog)
{
    SOCKET sock;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        return -1;
    }

    SOCKADDR_IN servaddr = { 0 };
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr = GetDefaultMyIP();
    servaddr.sin_port = htons(pnum);

    int re = 0;
    re = bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (re == -1) {
        return -1;
    }
    re = listen(sock, blog);
    if (re == -1) {
        return -1;
    }
    return sock;
}