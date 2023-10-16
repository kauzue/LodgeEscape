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
	int player1_chapter;
	int player2;
	int player2_chapter;
	int exit_num;
	SOCKET sock_server1;
	SOCKET sock_server2;
	SOCKET sock_client1;
	SOCKET sock_client2;
} room_t;

typedef struct save {
	int player_num;
	int item_num;
	int clue_num;
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
item_t s_items[NUM_MAX_PLAYER_PER_SAVES][NUM_MAX_SAVE_PER_ITEMS];
ending_t s_endings[NUM_MAX_PLAYERS][NUM_MAX_PLAYER_PER_ENDINGS];

bool InitSystem();
void Game_Login(SOCKET);