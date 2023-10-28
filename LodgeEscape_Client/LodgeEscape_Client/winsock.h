#pragma once
#pragma comment(lib,"ws2_32")
#pragma warning(disable:4996)

#include <WinSock2.h>

#define PORT_NUM 1252
#define SERVER_IP "39.113.173.193"

SOCKET StartWinsock();