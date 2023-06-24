#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

#define NUM_MAX_PLAYERS (100)
#define NUM_MAX_SAVES_PER_PLAYER (20)
#define MAX_MSG_LEN 256

#pragma comment(lib,"ws2_32")
#pragma warning(disable:4996)

typedef struct player {
	char ID[MAX_MSG_LEN];
	char password[MAX_MSG_LEN];
	int p_num;
} player_t;

typedef struct save {
	int stage;
	int chapter;
} save_t;

typedef struct ending {
	int number;
	char name[20];
} ending_t;

typedef struct clue {
	char name[20];
	char information[500];
} clue_t;

IN_ADDR GetDefaultMyIP();

void AcceptLoop(SOCKET sock);//Accept Loop
void EventLoop(SOCKET sock);
void DoIt(void* param); //송수신 스레드 진입점
void AcceptProc(int index);
void ReadProc(int index);
void CloseProc(int index);
int loginmenu(SOCKET dosock);
void OpenMainMenu(SOCKET dosock);
void player1(SOCKET dosock);
void SignIn(SOCKET dosock);
void SignUp(SOCKET dosock);