#pragma once

#define MAX_CHAPTER 1
#define MAX_STAGE 0

void InitStory(SOCKET, int, int, int);

typedef struct communication {
	SOCKET sock;
	int interact;
} communication_t;

communication_t communication;