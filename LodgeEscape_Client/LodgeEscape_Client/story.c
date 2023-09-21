#include <WinSock2.h>

#include "story.h"

SOCKET sock;
int g_player_num;
int g_save_num;
int g_room_num;

enum Chapter { CHAPTER1, CHAPTER2, CHAPTER3, CHAPTER4 };
enum Stage { STAGE1, STAGE2, STAGE3, STAGE4 };

void Player0();
void Player1();
void Player0_Chapter1();
void Player1_Chapter1();

void InitStory(SOCKET socket, int player_num, int save_num, int room_num)
{
	int player_number;
	int msg_int;

	sock = socket;
	g_player_num = player_num;
	g_save_num = save_num;
	g_room_num = room_num;

	recv(sock, &msg_int, sizeof(msg_int), 0);
	send(sock, &g_player_num, sizeof(g_player_num), 0);
	recv(sock, &player_number, sizeof(player_number), 0);

	system("cls");

	if (player_number == 0) {
		Player0();
	}

	else {
		Player1();
	}
}

void Player0()
{
	int chapter_number;
	int stage_number;

	send(sock, &g_save_num, sizeof(g_save_num), 0);
	recv(sock, &chapter_number, sizeof(chapter_number), 0);
	recv(sock, &stage_number, sizeof(stage_number), 0);

	switch (chapter_number) {
	case CHAPTER1: {
		Player0_Chapter1();
		break;
	}

	case CHAPTER2: {
		break;
	}

	case CHAPTER3: {
		break;
	}

	case CHAPTER4: {
		break;
	}
	}
}

void Player1()
{
	int chapter_number;
	int stage_number;

	send(sock, &g_save_num, sizeof(g_save_num), 0);
	recv(sock, &chapter_number, sizeof(chapter_number), 0);
	recv(sock, &stage_number, sizeof(stage_number), 0);

	switch (chapter_number) {
	case CHAPTER1: {
		Player1_Chapter1();
		break;
	}

	case CHAPTER2: {
		break;
	}

	case CHAPTER3: {
		break;
	}

	case CHAPTER4: {
		break;
	}
	}
}

void Player0_Chapter1()
{
	printf("플레이어 0");
	system("pause");
}

void Player1_Chapter1()
{
	printf("플레이어 1");
	system("pause");
}