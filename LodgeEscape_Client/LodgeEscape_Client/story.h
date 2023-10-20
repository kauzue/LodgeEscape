#pragma once

#define MAX_CHAPTER 0
#define MAX_STAGE 0

void InitStory(SOCKET, int, int, int);

typedef struct communication {
	SOCKET sock;
} communication_t;

communication_t communication;