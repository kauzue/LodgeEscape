#pragma once

#include <stdio.h>
#include <stdbool.h>

#define MAX_MSG_LEN 256
#define MAX_ITEMS_NUM 200000
#define MAX_CLUES_NUM 200000

enum KEY { UP, DOWN, LEFT, RIGHT, ENTER };

typedef struct item_player_1 {
	int number;
	char name[MAX_MSG_LEN];
	char explaination[MAX_MSG_LEN];
	bool use;
} item_t;

typedef struct clue_player_1 {
	int number;
	char name[MAX_MSG_LEN];
	char explaination[MAX_MSG_LEN];
	bool use;
} clue_t;

item_t s_items[MAX_ITEMS_NUM];
clue_t s_clues[MAX_CLUES_NUM];

bool InitSystem();
bool InitGame();
int ControlKey();
void MoveCursor(int, int);