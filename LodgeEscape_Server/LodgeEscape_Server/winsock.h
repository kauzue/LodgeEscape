#pragma once

#include <WinSock2.h>

#define PORT_NUM 1252
#define BLOG_SIZE 5

void StartWinsock();
IN_ADDR GetDefaultMyIP();
SOCKET SetTCPServer(short, int);