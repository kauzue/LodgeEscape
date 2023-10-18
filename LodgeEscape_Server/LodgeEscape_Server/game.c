#pragma warning(disable:4996)

#include <stdio.h>

#include "game.h"

enum Login { SIGN_UP_LOGIN, LOGIN_LOGIN, EXIT_LOGIN };
enum Main_Menu { START_GAME_MAIN_MENU, LOAD_GAME_MAIN_MENU, OPTION_MAIN_MENU, ENDING_MAIN_MENU, EXIT_MAIN_MENU };
enum Start_Game { CREATE_ROOM_START_GAME, FIND_ROOM_START_GAME, EXIT_START_GAME };
enum Option { LOGIN_DATA_OPTION, LOGOUT_OPTION, EXIT_OPTION };
enum Story { ITEM, MENU, CHAPTER, STAGE };
enum Menu { ITEM_MENU, SAVE_MENU, BACK_MENU, EXIT_MENU };
enum Item {
	FLASH = 10, FLASH_BATTERY = 11, FLASH_LIGHT = 12, WALLET_1 = 20, NOTE_1 = 50, WALLET_2 = 100010,
	NOTE_2 = 100040
};

void Sign_Up();
int Login();
int Game_Main_Menu();
void Start_Game();
int Option();
void Wait(int);
void InitStory();
int Story();
int Menu();
void Item();
void Save();

_declspec(thread) SOCKET sock;

int g_players_num;
int g_rooms_num = 0;
int g_saves_num[NUM_MAX_PLAYER_PER_SAVES];
int g_items_num[NUM_MAX_PLAYERS][NUM_MAX_PLAYER_PER_SAVES];
int g_clues_num[NUM_MAX_PLAYERS][NUM_MAX_PLAYER_PER_SAVES];

bool InitSystem()
{
	char save_filename[16];

	FILE* pb = fopen("player.bin", "rb");
	if (pb == NULL) {
		puts("플레이어 파일 오픈 실패");
		return false;
	}

	g_players_num = fread(s_players, sizeof(player_t), NUM_MAX_PLAYERS, pb);

	fclose(pb);

	for (int i = 0; i < NUM_MAX_PLAYER_PER_SAVES; i++) {
		sprintf(save_filename, "save%02d.bin", i + 1);

		FILE* sb = fopen(save_filename, "rb");
		if (sb == NULL) {
			puts("세이브 파일 오픈 실패");
			return false;
		}

		g_saves_num[i] = fread(s_saves, sizeof(save_t), NUM_MAX_PLAYERS, sb);

		fclose(sb);
	}

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
	player_t player;
	save_t save;

	char save_filename[16];
	char msg_char[MAX_MSG_LEN] = "";
	int msg_int;

	FILE* pb = fopen("player.bin", "ab");
	if (pb == NULL) {
		puts("플레이어 파일 오픈 실패!");
		return;
	}

	for (int i = 0; i < NUM_MAX_PLAYER_PER_SAVES; i++) {
		sprintf(save_filename, "save%02d.bin", i + 1);
		FILE* sb = fopen(save_filename, "ab");
		if (sb == NULL) {
			puts("세이브 파일 오픈 실패!");
			return;
		}

		save.item_num = 0;
		save.clue_num = 0;
		save.chapter = 0;
		save.stage = 0;

		memcpy(&s_saves[g_players_num][i], &save, sizeof(save_t));
		g_items_num[g_players_num][i] = 0;
		g_clues_num[g_players_num][i] = 0;
		g_saves_num[i]++;

		fwrite(&save, sizeof(save_t), 1, sb);

		fclose(sb);
	}

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

int Login()
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
		if (msg_int == -1) {
			send(sock, &msg_int, sizeof(msg_int), 0);
			continue;
		}
		msg_int = 0;

		send(sock, &msg_int, sizeof(msg_int), 0);
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
			int player_num;
			int i = 0;
			int save_num = 1;

			recv(sock, &player_num, sizeof(player_num), 0);

			while (true) {
				save_num = NUM_MAX_PLAYER_PER_SAVES / 5 * save_num;
				send(sock, &save_num, sizeof(save_num), 0);

				for (i; i < save_num; i++) {
					send(sock, &s_saves[player_num][i].chapter, sizeof(int), 0);
					send(sock, &s_saves[player_num][i].stage, sizeof(int), 0);
					send(sock, &s_saves[player_num][i].item_num, sizeof(int), 0);
					send(sock, &s_saves[player_num][i].clue_num, sizeof(int), 0);
				}

				recv(sock, &save_num, sizeof(save_num), 0);
				i = 4 * (save_num - 1);
				if (save_num == 0) {
					break;
				}
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
			recv(sock, room.r_password, MAX_MSG_LEN, 0);
			recv(sock, &room.player1, sizeof(room.player1), 0);
			if (room.player1 == -1) {
				goto EXIT_CREATE_ROOM;
			}
			recv(sock, &room.sock_client1, sizeof(SOCKET), 0);
			send(sock, &g_rooms_num, sizeof(g_rooms_num), 0);

			recv(sock, &msg_int, sizeof(msg_int), 0);
			room.player1_chapter = s_saves[room.player1][msg_int].chapter;
			room.player2_chapter = s_saves[room.player1][msg_int].chapter;
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
			int room_num;
			char password[MAX_MSG_LEN];
			
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
				else if (room_num == -2) {
					continue;
				}
				recv(sock, &s_rooms[room_num].player2, sizeof(s_rooms[room_num].player2), 0);

				recv(sock, password, MAX_MSG_LEN, 0);
				if (strcmp(s_rooms[room_num].r_password, password) == 0) {
					if (s_players[s_rooms[room_num].player1].player_num == s_players[s_rooms[room_num].player2].player_num) {
						room_num = -1;
					}
					send(sock, &room_num, sizeof(room_num), 0);
					if (room_num == -1) {
						return;
					}

					recv(sock, &s_rooms[room_num].sock_client2, sizeof(SOCKET), 0);
					send(sock, &s_rooms[room_num].sock_client2, sizeof(SOCKET), 0);
					recv(sock, &msg_int, sizeof(msg_int), 0);
					s_rooms[room_num].player2_chapter = s_saves[s_rooms[room_num].player2][msg_int].chapter;
					s_rooms[room_num].sock_server2 = sock;
					g_rooms_num--;
					break;
				}
			}
			
			Wait(room_num);
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
	int msg_int = 0;

	if (s_rooms[room_num].player1_chapter != s_rooms[room_num].player2_chapter) {
		send(s_rooms[room_num].sock_server2, &msg_int, sizeof(msg_int), 0);
		return;
	}

	else if(s_rooms[room_num].sock_server1 != s_rooms[room_num].sock_server2) {
		msg_int = 1;
		send(s_rooms[room_num].sock_server2, &msg_int, sizeof(msg_int), 0);
		InitStory();
		return;
	}

	while (true) {
		if (s_rooms[room_num].sock_server2 != s_rooms[room_num].sock_server1) {
			break;
		}
	}

	send(s_rooms[room_num].sock_server1, &s_rooms[room_num].sock_client2, sizeof(SOCKET), 0);
	InitStory();
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
	int msg_int, player_num;

	while (true) {
		recv(sock, &msg_int, sizeof(msg_int), 0);

		switch (msg_int) {
		case ITEM: {
			recv(sock, &player_num, sizeof(player_num), 0);
			recv(sock, &msg_int, sizeof(msg_int), 0);
			for (int i = 0; i < msg_int; i++) {
				recv(sock, &s_items[1][s_saves[player_num][1].item_num].number, sizeof(int), 0);
				s_saves[player_num][1].item_num++;
			}
			break;
		}

		case MENU: {
			msg_int = Menu();
			if (msg_int == -1) {
				return -1;
			}
			break;
		}

		case CHAPTER: {
			recv(sock, &player_num, sizeof(player_num), 0);
			s_saves[player_num][1].stage++;
		}

		case STAGE: {
			recv(sock, &player_num, sizeof(player_num), 0);
			s_saves[player_num][1].stage++;
		}
		}
	}

}

int Menu()
{
	int msg_int;

	while (true) {

		recv(sock, &msg_int, sizeof(msg_int), 0);

		switch (msg_int) {
		case ITEM_MENU: {
			Item();
			break;
		}

		case SAVE_MENU: {
			Save();
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

void Item()
{
	int msg_int;
	int player_num;

	recv(sock, &player_num, sizeof(player_num), 0);
	send(sock, &s_saves[player_num][1].item_num, sizeof(int), 0);
	if (s_saves[player_num][1].item_num == 0) {
		return;
	}

	for (int i = 0; i < s_saves[player_num][1].item_num; i++) {
		send(sock, &s_items[1][i].number, sizeof(s_items[1][i].number), 0);
	}

	recv(sock, &msg_int, sizeof(msg_int), 0);

	switch (msg_int) {
	case FLASH: {
		break;
	}

	case FLASH_BATTERY: {
		for (int i = 0; i < s_saves[player_num][1].item_num; i++) {
			if (s_items[1][i].number == msg_int) {
				s_items[1][i].number = 12;
				break;
			}
		}
		break;
	}

	case FLASH_LIGHT: {
		for (int i = 0; i < s_saves[player_num][1].item_num; i++) {
			if (s_items[1][i].number == msg_int) {
				s_items[1][i].number = 11;
				break;
			}
		}
		break;
	}

	case WALLET_1: {
		for (int i = 0; i < s_saves[player_num][1].item_num; i++) {
			if (s_items[1][i].number == msg_int) {
				s_items[1][i].number = 21;
				break;
			}
		}

		s_items[1][s_saves[player_num][1].item_num].number = 30;
		s_saves[player_num][1].item_num++;
		s_items[1][s_saves[player_num][1].item_num].number = 40;
		s_saves[player_num][1].item_num++;
		break;
	}

	case NOTE_1: {
		break;
	}

	case WALLET_2: {
		for (int i = 0; i < s_saves[player_num][1].item_num; i++) {
			if (s_items[1][i].number == msg_int) {
				s_items[1][i].number = 100011;
				break;
			}
		}

		s_items[1][s_saves[player_num][1].item_num].number = 100020;
		s_saves[player_num][1].item_num++;
		s_items[1][s_saves[player_num][1].item_num].number = 100030;
		s_saves[player_num][1].item_num++;
		break;
	}

	case NOTE_2: {
		break;
	}

	default: {
		break;
	}
	}

	return;
}

void Save()
{
	int player_num;
	int i = 2;
	int save_num = 1;

	recv(sock, &player_num, sizeof(player_num), 0);


	while (true) {
		save_num = NUM_MAX_PLAYER_PER_SAVES / 5 * save_num;
		send(sock, &save_num, sizeof(save_num), 0);

		for (i; i < save_num; i++) {
			send(sock, &s_saves[player_num][i].chapter, sizeof(int), 0);
			send(sock, &s_saves[player_num][i].stage, sizeof(int), 0);
			send(sock, &s_saves[player_num][i].item_num, sizeof(int), 0);
			send(sock, &s_saves[player_num][i].clue_num, sizeof(int), 0);
		}

		recv(sock, &save_num, sizeof(save_num), 0);
		if (save_num == 0) {
			break;
		}
	}

	recv(sock, &save_num, sizeof(save_num), 0);
	i = 4 * (save_num - 1);
	if (save_num == 0) {
		return;
	}

	s_saves[player_num][save_num].chapter = s_saves[player_num][1].chapter;
	s_saves[player_num][save_num].stage = s_saves[player_num][1].stage;
	s_saves[player_num][save_num].item_num = s_saves[player_num][1].item_num;
	s_saves[player_num][save_num].clue_num = s_saves[player_num][1].clue_num;

	return;
}