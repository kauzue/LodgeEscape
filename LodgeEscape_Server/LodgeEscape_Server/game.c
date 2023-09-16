#pragma warning(disable:4996)

#include <stdio.h>

#include "game.h"
#include "system.h"

player_t s_players[NUM_MAX_PLAYERS];

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

void Game_Login(SOCKET sock)
{
	int msg_int;
	char msg_char[MAX_MSG_LEN] = "";

	while (true) {

		recv(sock, &msg_int, sizeof(msg_int), 0);

		switch (msg_int) {
		case SIGNUP_LOGIN: {
			FILE* pb = fopen("player.bin", "ab");
			if (pb == NULL) {
				puts("파일오픈 실패!");
				return;
			}

			player_t player;

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
			break;
		}

		case LOGIN_LOGIN: {
			char ID[MAX_MSG_LEN] = "";
			char PassWord[MAX_MSG_LEN] = "";

			recv(sock, ID, MAX_MSG_LEN, 0);
			recv(sock, PassWord, MAX_MSG_LEN, 0);
			if (strcmp(ID, "0") == 0) {
				msg_int = -1;
				send(sock, &msg_int, sizeof(msg_int), 0);
				goto ERR_LOGIN;
			}

			msg_int = 0;

			for (int i = 0; i < g_players_num; i++) {
				if (strcmp(s_players[i].ID, ID) == 0) {
					if (strcmp(s_players[i].password, PassWord) == 0) {
						msg_int = 1;
						break;
					}
				}
			}

			send(sock, &msg_int, sizeof(msg_int), 0);

ERR_LOGIN:
			break;
		}

		case EXIT_LOGIN: {
			return;
		}
		}
	}
}