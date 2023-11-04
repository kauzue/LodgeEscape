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
#define NUM_MAX_STORY 20

typedef struct ending {
	int number;
} ending_t;

typedef struct item {
	int number;
} item_t;

typedef struct clue {
	int number;
} clue_t;

typedef struct story {
	int num_item;
	int num_clue;
} story_t;

typedef struct player {
	char ID[MAX_MSG_LEN];
	char password[MAX_MSG_LEN];
	int player_num;
	int save_num;
	int ending_num;
	ending_t endings[NUM_MAX_PLAYER_PER_ENDINGS];
} player_t;

typedef struct room {
	char r_name[MAX_MSG_LEN];
	char r_password[MAX_MSG_LEN];
	int player1;
	int player1_chapter;
	int player2;
	int player2_chapter;
	int exit_num;
	int water_num;
	int book_num;
	SOCKET sock_server1;
	SOCKET sock_server2;
	SOCKET sock_client1;
	SOCKET sock_client2;
} room_t;

typedef struct save {
	int item_num;
	int clue_num;
	item_t items[NUM_MAX_SAVE_PER_ITEMS];
	clue_t clues[NUM_MAX_SAVE_PER_CLUES];
	story_t storys[NUM_MAX_STORY];
	int stage;
	int chapter;
} save_t;

player_t s_players[NUM_MAX_PLAYERS];
room_t s_rooms[NUM_MAX_ROOMS];
save_t s_saves[NUM_MAX_PLAYERS][NUM_MAX_PLAYER_PER_SAVES];

bool InitSystem();
void Game_Login(SOCKET);