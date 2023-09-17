#pragma once

#include <WinSock2.h>
#include <stdbool.h>

#define NUM_MAX_PLAYERS 100
#define NUM_MAX_ROOMS 100
#define MAX_MSG_LEN 256
#define NUM_MAX_PLAYER_PER_SAVES 20
#define NUM_MAX_PLAYER_PER_ENDINGS 10
#define NUM_MAX_SAVE_PER_ITEMS 10
#define NUM_MAX_SAVE_PER_CLUES 10

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
	int player1;
	int player2;
	SOCKET sock1;
	SOCKET sock2;
} room_t;

typedef struct save {
	int stage;
	int chapter;
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

player_t s_players[NUM_MAX_PLAYERS];
room_t s_rooms[NUM_MAX_ROOMS];
save_t s_saves[NUM_MAX_PLAYERS][NUM_MAX_PLAYER_PER_SAVES];
ending_t s_endings[NUM_MAX_PLAYERS][NUM_MAX_PLAYER_PER_ENDINGS];

bool InitSystem();

void Game_Login(SOCKET);