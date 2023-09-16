#include <stdio.h>
#include <process.h>

#include "winsock.h"
#include "game.h"

SOCKET StartWinsock()
{
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);

    SOCKET sock;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        return -1;
    }

    SOCKADDR_IN servaddr = { 0 };
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    servaddr.sin_port = htons(PORT_NUM);

    int re = 0;
    re = connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (re == -1) {
        puts("서버가 닫혀있거나 서버 주소 혹은 서버 포트가 서버와 일치하지 않습니다.");
        return -1;
    }

    Game_Login(sock);
}