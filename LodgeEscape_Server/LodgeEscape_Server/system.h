#pragma once

#include <WinSock2.h>
#include <stdbool.h>

#define NUM_MAX_PLAYERS 100
#define NUM_MAX_ROOMS 10
#define NUM_MAX_ITEMS_PER_PLAYER 10
#define NUM_MAX_CLUES_PER_PLAYER 10
#define NUM_MAX_SAVES_PER_PLAYER 20
#define NUM_MAX_ENDINGS_PER_PLAYER 5
#define MAX_MSG_LEN 256


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
	char name[MAX_MSG_LEN];
} ending_t;

typedef struct item {
	char name[MAX_MSG_LEN];
	char information[MAX_MSG_LEN];
} item_t;

typedef struct clue {
	char name[MAX_MSG_LEN];
	char information[MAX_MSG_LEN];
} clue_t;

bool InitSystem();