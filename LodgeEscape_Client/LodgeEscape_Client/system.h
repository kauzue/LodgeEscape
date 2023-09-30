#pragma once

#include <stdio.h>
#include <stdbool.h>

#define MAX_MSG_LEN 256
#define MAX_ITEMS_NUM 10
#define MAX_CLUES_NUM 10

enum KEY { UP, DOWN, LEFT, RIGHT, ENTER };

typedef struct item_player_1 {
	float number;
	char name[MAX_MSG_LEN];
	char explaination[MAX_MSG_LEN];
	bool use;
} item_t_1;

typedef struct clue_player_1 {
	float number;
	char name[MAX_MSG_LEN];
	char explaination[MAX_MSG_LEN];
	bool use;
} clue_t_1;

typedef struct item_player_2 {
	float number;
	char name[MAX_MSG_LEN];
	char explaination[MAX_MSG_LEN];
	bool use;
} item_t_2;

typedef struct clue_player_2 {
	float number;
	char name[MAX_MSG_LEN];
	char explaination[MAX_MSG_LEN];
	bool use;
} clue_t_2;

item_t_1 s_items_1[MAX_ITEMS_NUM];
clue_t_1 s_clues_1[MAX_CLUES_NUM];
item_t_2 s_items_2[MAX_ITEMS_NUM];
clue_t_2 s_clues_2[MAX_CLUES_NUM];

bool InitSystem();
bool InitGame();
int ControlKey();
void MoveCursor(int, int);