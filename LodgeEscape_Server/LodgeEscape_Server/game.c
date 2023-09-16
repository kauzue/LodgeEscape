#pragma warning(disable:4996)

#include <stdio.h>

#include "game.h"

player_t s_players[NUM_MAX_PLAYERS];
ending_t s_endings[NUM_MAX_PLAYERS][NUM_MAX_PLAYER_PER_ENDINGS];

enum Login { SIGN_UP_LOGIN, LOGIN_LOGIN, EXIT_LOGIN };
enum Main_Menu { START_GAME_MAIN_MENU, LOAD_GAME_MAIN_MENU, OPTION_MAIN_MENU, ENDING_MAIN_MENU, EXIT_MAIN_MENU };
enum Start_Game { CREATE_ROOM_START_GAME, FIND_ROOM_START_GAME, EXIT_START_GAME };


void Sign_Up();
void Login();
void Game_Main_Menu();
void Start_Game();

SOCKET sock;
int g_players_num;

bool InitSystem()
{
	FILE* pb = fopen("player.bin", "rb");

	if (pb == NULL) {
		puts("플레이어 파일 오픈 실패");
		return false;
	}

	g_players_num = fread(s_players, sizeof(player_t), NUM_MAX_PLAYERS, pb);

	fclose(pb);
	return true;
}

void Game_Login(SOCKET socket)
{
	sock = socket;
	int msg_int;
	char msg_char[MAX_MSG_LEN] = "";

	while (true) {

		recv(sock, &msg_int, sizeof(msg_int), 0);

		switch (msg_int) {
		case SIGN_UP_LOGIN: {
			Sign_Up();
			break;
		}

		case LOGIN_LOGIN: {
			Login();
			break;
		}

		case EXIT_LOGIN: {
			return;
		}
		}
	}
}

void Sign_Up()
{
	FILE* pb = fopen("player.bin", "ab");
	if (pb == NULL) {
		puts("파일오픈 실패!");
		return;
	}

	player_t player;

	char msg_char[MAX_MSG_LEN] = "";
	int msg_int;

	while (true) {
		recv(sock, msg_char, MAX_MSG_LEN, 0);
		if (strcmp(msg_char, "0") == 0) {
			msg_int = -1;

			send(sock, &msg_int, sizeof(msg_int), 0);
			goto ERR_SIGNUP;
		}

		msg_int = 1;

		for (int i = 0; i < g_players_num; i++) {
			if (strcmp(msg_char, s_players[i].ID) == 0) {
				msg_int = 0;
				break;
			}
		}

		send(sock, &msg_int, sizeof(msg_int), 0);
		if (msg_int == 1) {
			strcpy(player.ID, msg_char);
			break;
		}
	}

	recv(sock, msg_char, MAX_MSG_LEN, 0);
	strcpy(player.password, msg_char);

	recv(sock, &msg_int, sizeof(msg_int), 0);
	player.player_num = msg_int;

	player.save_num = 0;
	player.ending_num = 0;

	memcpy(&s_players[g_players_num], &player, sizeof(player_t));
	++g_players_num;

	fwrite(&player, sizeof(player_t), 1, pb);
ERR_SIGNUP:
	fclose(pb);
}

void Login()
{
	char ID[MAX_MSG_LEN] = "";
	char PassWord[MAX_MSG_LEN] = "";
	int msg_int = -1;

	while (msg_int < 0) {
		recv(sock, ID, MAX_MSG_LEN, 0);
		recv(sock, PassWord, MAX_MSG_LEN, 0);
		if (strcmp(ID, "0") == 0) {
			msg_int = -2;
			send(sock, &msg_int, sizeof(msg_int), 0);
			return;
		}

		for (int i = 0; i < g_players_num; i++) {
			if (strcmp(s_players[i].ID, ID) == 0) {
				if (strcmp(s_players[i].password, PassWord) == 0) {
					msg_int = i;
					break;
				}
			}
		}

		send(sock, &msg_int, sizeof(msg_int), 0);
	}

	Game_Main_Menu();
}

void Game_Main_Menu()
{
	int msg_int;

	while (true) {
		recv(sock, &msg_int, sizeof(msg_int), 0);

		switch (msg_int) {
		case START_GAME_MAIN_MENU: {
			Start_Game();
			break;
		}

		case LOAD_GAME_MAIN_MENU: {
			break;
		}

		case OPTION_MAIN_MENU: {
			break;
		}

		case ENDING_MAIN_MENU: {
			recv(sock, &msg_int, sizeof(msg_int), 0);
			send(sock, &s_players[msg_int].ending_num, sizeof(s_players[msg_int].ending_num), 0);

			for (int i = 0; i < s_players[msg_int].ending_num; i++) {
				send(sock, s_endings[msg_int][i].number, sizeof(s_endings[msg_int][i].number), 0);
			}
			break;
		}

		case EXIT_MAIN_MENU: {
			return;
		}
		}
	}
}

void Start_Game()
{
	int msg_int;

	while (true) {
		recv(sock, &msg_int, sizeof(msg_int), 0);

		switch (msg_int) {
		case CREATE_ROOM_START_GAME: {
			break;
		}

		case FIND_ROOM_START_GAME: {
			break;
		}

		case EXIT_START_GAME: {
			return;
		}
		}
	}
}