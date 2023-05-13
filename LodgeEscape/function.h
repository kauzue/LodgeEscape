#pragma once

typedef struct player {
	char ID[100];
	char password[100];
} player_t;

typedef struct save {
	int checkpoint;
} save_t;

typedef struct ending {
	int number;
	char name[20];
} ending_t;

typedef struct clue {
	char name[20];
	char information[500];
} clue_t;