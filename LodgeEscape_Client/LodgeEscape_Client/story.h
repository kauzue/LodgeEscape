#pragma once

void InitStory(SOCKET, int, int, int);

typedef struct communication {
	SOCKET sock;
} communication_t;

communication_t communication;