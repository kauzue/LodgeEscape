#pragma once

#include <WinSock2.h>
#include <stdbool.h>

#define NUM_MAX_PLAYERS 100
#define MAX_MSG_LEN 256
#define NUM_MAX_PLAYER_PER_ENDINGS 10


typedef struct player {
	char ID[MAX_MSG_LEN];
	char password[MAX_MSG_LEN];
	int player_num;
	int save_num;
	int ending_num;
} player_t;

typedef struct room {
	char r_name[MAX_MSG_LEN];
	int r_password;
	SOCKET sock;
} room_t;

typedef struct save {
	int stage;
	int chapter;
	int item_num;
	int clue_num;
} save_t;

typedef struct ending {
	int number;
} ending_t;

typedef struct item {
	int number;
} item_t;

typedef struct clue {
	int number;
} clue_t;

bool InitSystem();

void Game_Login(SOCKET);