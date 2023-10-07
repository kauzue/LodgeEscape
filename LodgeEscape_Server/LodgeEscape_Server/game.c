#pragma warning(disable:4996)

#include <stdio.h>

#include "game.h"

enum Login { SIGN_UP_LOGIN, LOGIN_LOGIN, EXIT_LOGIN };
enum Main_Menu { START_GAME_MAIN_MENU, LOAD_GAME_MAIN_MENU, OPTION_MAIN_MENU, ENDING_MAIN_MENU, EXIT_MAIN_MENU };
enum Start_Game { CREATE_ROOM_START_GAME, FIND_ROOM_START_GAME, EXIT_START_GAME };
enum Option { LOGIN_DATA_OPTION, LOGOUT_OPTION, EXIT_OPTION };
enum Story { EXPLORE, INVESTIGATE, MENU };
enum Menu { ITEM_MENU, SAVE_MENU, BACK_MENU, EXIT_MENU };

void Sign_Up();
int Login();
int Game_Main_Menu();
void Start_Game();
int Option();
void Wait(int);
void InitStory();
int Story();
int Menu();

_declspec(thread) SOCKET sock;

int g_players_num;
int g_rooms_num = 0;
int g_saves_num[NUM_MAX_PLAYER_PER_SAVES];
int g_items_num[NUM_MAX_PLAYERS][NUM_MAX_PLAYER_PER_SAVES];

bool InitSystem()
{
	char save_filename[16];
	sprintf(save_filename, "save%2d.bin", 0);

	FILE* pb = fopen("player.bin", "rb");
	FILE* sb_1 = fopen("save01.bin", "rb");
	FILE* sb_2 = fopen("save02.bin", "rb");
	FILE* sb_3 = fopen("save03.bin", "rb");
	FILE* sb_4 = fopen("save04.bin", "rb");
	FILE* sb_5 = fopen("save05.bin", "rb");
	FILE* sb_6 = fopen("save06.bin", "rb");
	FILE* sb_7 = fopen("save07.bin", "rb");
	FILE* sb_8 = fopen("save08.bin", "rb");
	FILE* sb_9 = fopen("save09.bin", "rb");
	FILE* sb_10 = fopen("save10.bin", "rb");
	FILE* sb_11 = fopen("save11.bin", "rb");
	FILE* sb_12 = fopen("save12.bin", "rb");
	FILE* sb_13 = fopen("save13.bin", "rb");
	FILE* sb_14 = fopen("save14.bin", "rb");
	FILE* sb_15 = fopen("save15.bin", "rb");
	FILE* sb_16 = fopen("save16.bin", "rb");
	FILE* sb_17 = fopen("save17.bin", "rb");
	FILE* sb_18 = fopen("save18.bin", "rb");
	FILE* sb_19 = fopen("save19.bin", "rb");
	FILE* sb_20 = fopen("save20.bin", "rb");

	if (pb == NULL) {
		puts("플레이어 파일 오픈 실패");
		return false;
	}

	if (sb_1 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_1;
	}

	if (sb_2 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_2;
	}

	if (sb_3 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_3;
	}

	if (sb_4 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_4;
	}

	if (sb_5 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_5;
	}

	if (sb_6 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_6;
	}

	if (sb_7 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_7;
	}

	if (sb_8 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_8;
	}

	if (sb_9 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_9;
	}

	if (sb_10 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_10;
	}

	if (sb_11 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_11;
	}

	if (sb_12 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_12;
	}

	if (sb_13 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_13;
	}

	if (sb_14 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_14;
	}

	if (sb_15 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_15;
	}

	if (sb_16 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_16;
	}

	if (sb_17 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_17;
	}

	if (sb_18 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_18;
	}

	if (sb_19 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_19;
	}

	if (sb_20 == NULL) {
		puts("세이브 파일 오픈 실패");
		goto ERR_FILE_20;
	}

	g_players_num = fread(s_players, sizeof(player_t), NUM_MAX_PLAYERS, pb);
	g_saves_num[0] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_1);
	g_saves_num[1] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_2);
	g_saves_num[2] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_3);
	g_saves_num[3] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_4);
	g_saves_num[4] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_5);
	g_saves_num[5] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_6);
	g_saves_num[6] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_7);
	g_saves_num[7] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_8);
	g_saves_num[8] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_9);
	g_saves_num[9] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_10);
	g_saves_num[10] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_11);
	g_saves_num[11] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_12);
	g_saves_num[12] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_13);
	g_saves_num[13] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_14);
	g_saves_num[14] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_15);
	g_saves_num[15] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_16);
	g_saves_num[16] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_17);
	g_saves_num[17] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_18);
	g_saves_num[18] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_19);
	g_saves_num[19] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb_20);

	fclose(pb);
	fclose(sb_1);
	fclose(sb_2);
	fclose(sb_3);
	fclose(sb_4);
	fclose(sb_5);
	fclose(sb_6);
	fclose(sb_7);
	fclose(sb_8);
	fclose(sb_9);
	fclose(sb_10);
	fclose(sb_11);
	fclose(sb_12);
	fclose(sb_13);
	fclose(sb_14);
	fclose(sb_15);
	fclose(sb_16);
	fclose(sb_17);
	fclose(sb_18);
	fclose(sb_19);
	fclose(sb_20);
	return true;

ERR_FILE_20:
	fclose(sb_19);
ERR_FILE_19:
	fclose(sb_18);
ERR_FILE_18:
	fclose(sb_17);
ERR_FILE_17:
	fclose(sb_16);
ERR_FILE_16:
	fclose(sb_15);
ERR_FILE_15:
	fclose(sb_14);
ERR_FILE_14:
	fclose(sb_13);
ERR_FILE_13:
	fclose(sb_12);
ERR_FILE_12:
	fclose(sb_11);
ERR_FILE_11:
	fclose(sb_10);
ERR_FILE_10:
	fclose(sb_9);
ERR_FILE_9:
	fclose(sb_8);
ERR_FILE_8:
	fclose(sb_7);
ERR_FILE_7:
	fclose(sb_6);
ERR_FILE_6:
	fclose(sb_5);
ERR_FILE_5:
	fclose(sb_4);
ERR_FILE_4:
	fclose(sb_3);
ERR_FILE_3:
	fclose(sb_2);
ERR_FILE_2:
	fclose(sb_1);
ERR_FILE_1:
	fclose(pb);
	return false;
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
			int exit = Login();
			if (exit == -1) {
				return;
			}
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
		puts("플레이어 파일 오픈 실패!");
		return;
	}

	FILE* sb = fopen("save.bin", "ab");
	if(sb == NULL) {
		puts("세이브 파일 오픈 실패!");
		goto ERR_SAVE_FILE;
	}

	player_t player;
	save_t save;

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
	save.player_num = g_players_num;
	save.chapter = 0;
	save.stage = 0;

	memcpy(&s_players[g_players_num], &player, sizeof(player_t));
	memcpy(&s_saves[g_players_num], &save, sizeof(save_t));
	++g_players_num;

	fwrite(&player, sizeof(player_t), 1, pb);
	
ERR_SIGNUP:
	fclose(sb);
ERR_SAVE_FILE:
	fclose(pb);
}

int Login()
{
	char ID[MAX_MSG_LEN] = "";
	char PassWord[MAX_MSG_LEN] = "";
	int msg_int = -1;
	int save = 0;

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
		send(sock, &save, sizeof(save), 0);
	}

	int exit = Game_Main_Menu();
	if (exit == -1) {
		return -1;
	}
	return 0;
}

int Game_Main_Menu()
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
			recv(sock, &msg_int, sizeof(msg_int), 0);
			send(sock, &s_players[msg_int].save_num, sizeof(s_players[msg_int].save_num), 0);

			for (int i = 0; i < s_players[msg_int].save_num; i++) {
				send(sock, &s_saves[msg_int][i].stage, sizeof(s_saves[msg_int][i].stage), 0);
				send(sock, &s_saves[msg_int][i].chapter, sizeof(s_saves[msg_int][i].chapter), 0);
			}

			break;
		}

		case OPTION_MAIN_MENU: {
			int log = Option();
			if (log == -1) {
				return 0;
			}
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
			return -1;
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
			room_t room;


			recv(sock, room.r_name, MAX_MSG_LEN, 0);
			if (strcmp(room.r_name, "0") == 0) {
				return;
			}
			recv(sock, &room.r_password, sizeof(room.r_password), 0);
			recv(sock, &room.player1, sizeof(room.player1), 0);
			if (room.player1 == -1) {
				goto EXIT_CREATE_ROOM;
			}
			recv(sock, &room.sock_client1, sizeof(SOCKET), 0);
			send(sock, &g_rooms_num, sizeof(g_rooms_num), 0);

			room.player2 = -1;
			room.sock_server1 = sock;
			room.sock_server2 = sock;
			room.sock_client2 = room.sock_client1;
			room.exit_num = 0;
			memcpy(&s_rooms[g_rooms_num], &room, sizeof(room_t));
			++g_rooms_num;

			Wait(g_rooms_num - 1);

			return;

EXIT_CREATE_ROOM:
			break;
		}

		case FIND_ROOM_START_GAME: {
			int room_num, password;
			
			while(true) {
				send(sock, &g_rooms_num, sizeof(g_rooms_num), 0);
				if (g_rooms_num == 0) {
					goto EXIT_FIND_ROOM;
				}

				for (int i = 0; i < g_rooms_num; i++) {
					send(sock, s_rooms[i].r_name, MAX_MSG_LEN, 0);
				}

				recv(sock, &room_num, sizeof(room_num), 0);
				if (room_num == -1) {
					goto EXIT_FIND_ROOM;
				}
				recv(sock, &s_rooms[room_num].player2, sizeof(s_rooms[room_num].player2), 0);

				recv(sock, &password, sizeof(password), 0);
				if (s_rooms[room_num].r_password == password) {
					if (s_players[s_rooms[room_num].player1].player_num == s_players[s_rooms[room_num].player2].player_num) {
						room_num = -1;
					}
					send(sock, &room_num, sizeof(room_num), 0);
					if (room_num == -1) {
						return;
					}

					recv(sock, &s_rooms[room_num].sock_client2, sizeof(SOCKET), 0);
					send(sock, &s_rooms[room_num].sock_client2, sizeof(SOCKET), 0);
					s_rooms[room_num].sock_server2 = sock;
					g_rooms_num--;
					break;
				}
			}
			
			InitStory(sock);
			return;

EXIT_FIND_ROOM:
			break;
		}

		case EXIT_START_GAME: {
			return;
		}
		}
	}
}

int Option()
{
	int msg_int;

	recv(sock, &msg_int, sizeof(msg_int), 0);

	switch (msg_int) {
	case LOGIN_DATA_OPTION: {
		recv(sock, &msg_int, sizeof(msg_int), 0);
		send(sock, s_players[msg_int].ID, MAX_MSG_LEN, 0);
		send(sock, s_players[msg_int].password, MAX_MSG_LEN, 0);
		send(sock, &s_players[msg_int].player_num, sizeof(s_players[msg_int].player_num), 0);
		send(sock, &s_players[msg_int].save_num, sizeof(s_players[msg_int].save_num), 0);
		send(sock, &s_players[msg_int].ending_num, sizeof(s_players[msg_int].ending_num), 0);
		return 0;
	}

	case LOGOUT_OPTION: {
		return -1;
	}

	case EXIT_OPTION: {
		return 0;
	}
	}
}

void Wait(int room_num)
{
	while (true) {
		if (s_rooms[room_num].sock_server2 != s_rooms[room_num].sock_server1) {
			break;
		}
	}

	send(s_rooms[room_num].sock_server1, &s_rooms[room_num].sock_client2, sizeof(SOCKET), 0);
	InitStory(s_rooms[room_num].sock_server1);
}

void InitStory()
{
	int room_num;
	int player_num;
	int save_num;
	int err;
	
	while (true) {
		recv(sock, &player_num, sizeof(player_num), 0);
		send(sock, &s_players[player_num].player_num, sizeof(s_players[player_num].player_num), 0);
		recv(sock, &save_num, sizeof(save_num), 0);
		send(sock, &s_saves[player_num][save_num].chapter, sizeof(s_saves[player_num][save_num].chapter), 0);
		send(sock, &s_saves[player_num][save_num].stage, sizeof(s_saves[player_num][save_num].stage), 0);

		err = Story();
		if (err == -1) {
			recv(sock, &room_num, sizeof(room_num), 0);
			s_rooms[room_num].exit_num += 1;

			while (true) {
				if (s_rooms[room_num].exit_num == 2) {
					send(sock, &room_num, sizeof(room_num), 0);
					break;
				}
			}

			return 0;
		}
	}
}

int Story()
{
	int msg_int;
	int room_num;
	int player_num;
	int explore = 0;
	int investigate = 0;
	int exit = 0;

	while (explore == 0 || investigate == 0) {
		recv(sock, &msg_int, sizeof(msg_int), 0);
		recv(sock, &player_num, sizeof(player_num), 0);

		switch (msg_int) {
		case EXPLORE: {
			explore++;
			break;
		}

		case INVESTIGATE: {
			investigate++;
			if (investigate == 1) {
				recv(sock, &msg_int, sizeof(msg_int), 0);
				for (int i = 0; i < msg_int; 0) {
					recv(sock, &msg_int, sizeof(msg_int), 0);

				}
			}
			break;
		}

		case MENU: {
			exit = Menu();
			if (exit == -1) {
				return -1;
			}
			break;
		}
		}
	}

	return -1;
}

int Menu()
{
	int msg_int;

	while (true) {

		recv(sock, &msg_int, sizeof(msg_int), 0);

		switch (msg_int) {
		case ITEM_MENU: {
			break;
		}

		case SAVE_MENU: {
			break;
		}

		case BACK_MENU: {
			return 0;
		}

		case EXIT_MENU: {
			return -1;
		}
		}
	}
}