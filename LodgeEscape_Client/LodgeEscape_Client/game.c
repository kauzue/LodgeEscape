#pragma warning(disable:4996)

#include <stdio.h>

#include "game.h"
#include "story.h"
#include "system.h"

enum Login { SIGN_UP_LOGIN, LOGIN_LOGIN, EXIT_LOGIN};
enum Main_Menu { START_GAME_MAIN_MENU, LOAD_GAME_MAIN_MENU, OPTION_MAIN_MENU, ENDING_MAIN_MENU, EXIT_MAIN_MENU };
enum Start_Game { CREATE_ROOM_START_GAME, FIND_ROOM_START_GAME, EXIT_START_GAME};
enum Option { LOGIN_DATA_OPTION, LOGOUT_OPTION, EXIT_OPTION};

void Sign_Up();
int Login();
int Game_Main_Menu();
void Start_Game();
int Create_Room();
void Find_Room();
void Load_Game();
int Option();
void Login_Data();
void Ending();

SOCKET sock;
int g_player_num;
int g_save_num;
int g_item_num;
int g_clue_num;
int g_room_num;

void Game_Login(SOCKET socket)
{
	sock = socket;

	while (true) {
		system("cls");

		int x, y;
		int key = 0;

		x = 2;
		y = 0;

		MoveCursor(x - 2, y);
		printf("> Sign Up");

		MoveCursor(x, y + 2);
		printf("Login");

		MoveCursor(x, y + 4);
		printf("Exit");

		while (key != 4) {
			key = ControlKey();

			switch (key) {
			case UP: {
				if (y > 0) {
					MoveCursor(x - 2, y);
					printf(" ");
					MoveCursor(x - 2, y -= 2);
					printf(">");
				}
				break;
			}

			case DOWN: {
				if (y < 4) {
					MoveCursor(x - 2, y);
					printf(" ");

					MoveCursor(x - 2, y += 2);
					printf(">");
				}
				break;
			}

			case ENTER: {
				y = y / 2;
				system("cls");
				send(sock, &y, sizeof(y), 0);

				switch (y) {
				case SIGN_UP_LOGIN: {
					Sign_Up();
					break;
				}

				case LOGIN_LOGIN: {
					int exit = Login();
					if (exit == 1) {
						exit = Game_Main_Menu();
						if (exit == -1) {
							return;
						}
					}
					break;
				}

				case EXIT_LOGIN: {
					return;
				}
				}
			}
			}
		}

	}
}

void Sign_Up()
{
	char ID[MAX_MSG_LEN] = "";
	char PassWord[MAX_MSG_LEN] = "";
	int msg_int = 0;

	while (true) {
		system("cls");

		printf("id : ");
		scanf_s("%s", ID, MAX_MSG_LEN);
		send(sock, ID, MAX_MSG_LEN, 0);
		recv(sock, &msg_int, sizeof(msg_int), 0);
		if (msg_int == -1) {
			return;
		}

		else if (msg_int == 1) {
			break;
		}

		system("cls");

		printf("이미 있는 아이디입니다. \n");
		printf("다시 입력해 주세요. \n");
		system("pause");

	}

	printf("password : ");
	scanf_s("%s", PassWord, MAX_MSG_LEN);
	send(sock, PassWord, sizeof(PassWord), 0);

	while (true) {
		system("cls");

		printf("player number : ");
		scanf_s("%d", &msg_int);
		if (msg_int > -1 && msg_int < 2) {
			send(sock, &msg_int, sizeof(msg_int), 0);
			break;
		}

		else {
			printf("0 혹은 1을 입력해 주세요. \n");
			system("pause");
		}
	}
}

int Login()
{
	char ID[MAX_MSG_LEN] = "";
	char PassWord[MAX_MSG_LEN] = "";

	while (true) {
		system("cls");

		printf("id : ");
		scanf_s("%s", ID, MAX_MSG_LEN);

		printf("password : ");
		scanf_s("%s", PassWord, MAX_MSG_LEN);

		send(sock, ID, MAX_MSG_LEN, 0);
		send(sock, PassWord, MAX_MSG_LEN, 0);

		recv(sock, &g_player_num, sizeof(g_player_num), 0);
		if (g_player_num == -2) {
			return 0;
		}
		recv(sock, &g_save_num, sizeof(g_save_num), 0);

		if (g_player_num >= 0) {
			break;
		}

		system("cls");

		printf("아이디 혹은 비밀번호가 틀렸습니다.\n");
		printf("다시 입력해 주세요. \n");
		system("pause");
	}

	return 1;
}

int Game_Main_Menu()
{
	while (true) {
		system("cls");

		int x, y;
		int msg_int = 0;
		int key = 0;

		x = 2;
		y = 0;

		MoveCursor(x - 2, y);
		printf("> Start Game");

		MoveCursor(x, y + 2);
		printf("Load Game");

		MoveCursor(x, y + 4);
		printf("Option");

		MoveCursor(x, y + 6);
		printf("Ending");

		MoveCursor(x, y + 8);
		printf("Exit");

		while (key != 4) {
			key = ControlKey();

			switch (key) {
			case UP: {
				if (y > 0) {
					MoveCursor(x - 2, y);
					printf(" ");
					MoveCursor(x - 2, y -= 2);
					printf(">");
				}
				break;
			}

			case DOWN: {
				if (y < 8) {
					MoveCursor(x - 2, y);
					printf(" ");

					MoveCursor(x - 2, y += 2);
					printf(">");
				}
				break;
			}

			case ENTER: {
				y = y / 2;
				system("cls");
				send(sock, &y, sizeof(y), 0);

				switch (y) {
				case START_GAME_MAIN_MENU: {
					Start_Game();
					break;
				}

				case LOAD_GAME_MAIN_MENU: {
					Load_Game();
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
					Ending();
					break;
				}

				case EXIT_MAIN_MENU: {
					return -1;
				}
				}
			}

			}
		}
	}
}

void Start_Game()
{
	while (true) {
		system("cls");

		int x, y;
		int key = 0;

		x = 2, y = 0;

		MoveCursor(x - 2, y);
		printf("> Create Room");

		MoveCursor(x, y + 2);
		printf("Find Room");

		MoveCursor(x, y + 4);
		printf("Exit");

		while (key != 4) {
			key = ControlKey();

			switch (key) {
			case UP: {
				if (y > 0) {
					MoveCursor(x - 2, y);
					printf(" ");
					MoveCursor(x - 2, y -= 2);
					printf(">");
				}
				break;
			}

			case DOWN: {
				if (y < 4) {
					MoveCursor(x - 2, y);
					printf(" ");

					MoveCursor(x - 2, y += 2);
					printf(">");
				}
				break;
			}

			case ENTER: {
				y = y / 2;
				system("cls");
				send(sock, &y, sizeof(y), 0);

				switch (y) {
				case CREATE_ROOM_START_GAME: {
					int exit;

					exit = Create_Room();
					if (exit == -1) {
						return;
					}
					break;
				}

				case FIND_ROOM_START_GAME: {
					Find_Room();
					break;
				}

				case EXIT_START_GAME: {
					return;
				}
				}
			}
			}
		}
	}
}

int Create_Room()
{
	char room_name[MAX_MSG_LEN] = "";
	char password[MAX_MSG_LEN];

	//fflush(stdin);
	//getc(stdin);

	printf("room name : ");
	scanf_s("%s", room_name, MAX_MSG_LEN);
	printf("password : ");
	scanf_s("%s", password, MAX_MSG_LEN);

	send(sock, room_name, MAX_MSG_LEN, 0);
	if (strcmp(room_name, "0") == 0) {
		getc(stdin);
		return -1;
	}
	send(sock, password, MAX_MSG_LEN, 0);
	send(sock, &g_player_num, sizeof(g_player_num), 0);
	send(sock, &sock, sizeof(SOCKET), 0);
	recv(sock, &g_room_num, sizeof(g_room_num), 0);
	send(sock, &g_save_num, sizeof(g_save_num), 0);

	system("cls");
	printf("다른 플레이어를 기다리는 중");

	while (true) {
		if (recv(sock, &communication.sock, sizeof(SOCKET), 0) >= 0) {
			communication.interact = 0;
			break;
		}
	}

	InitStory(sock, g_player_num, g_save_num, g_room_num);

	return 0;
}

void Find_Room()
{
	char room_name[MAX_MSG_LEN] = "";
	char password[MAX_MSG_LEN];
	int msg_int;
	int choice_room = 0;

	while (true) {
		system("cls");
		recv(sock, &msg_int, sizeof(msg_int), 0);
		if (msg_int == 0) {
			printf("현재 개설된 방이 없습니다. \n");
			system("pause");
			return;
		}

		for (int i = 0; i < msg_int; i++) {
			recv(sock, room_name, MAX_MSG_LEN, 0);
			printf("%d. %s \n \n", i, room_name);
		}

		//getc(stdin);

		printf("choice : ");
		scanf_s("%d", &choice_room);
		if (choice_room == -1) {
			send(sock, &choice_room, sizeof(choice_room), 0);
			return;
		}

		else if (choice_room >= 0 && choice_room < msg_int) {
			send(sock, &choice_room, sizeof(choice_room), 0);
			send(sock, &g_player_num, sizeof(g_player_num), 0);
			send(sock, &g_player_num, sizeof(g_player_num), 0);

			printf("password : ");
			scanf_s("%s", password, MAX_MSG_LEN);
			send(sock, password, MAX_MSG_LEN, 0);
			recv(sock, &msg_int, sizeof(msg_int), 0);
			if (msg_int == -1) {
				system("cls");
				printf("이미 같은 번호의 플레어어가 입장해 있습니다. \n");
				system("pause");
				getc(stdin);

				return;
			}

			else if (msg_int >= 0) {
				send(sock, &sock, sizeof(SOCKET), 0);
				recv(sock, &communication.sock, sizeof(SOCKET), 0);
				communication.interact = 0;
				send(sock, &g_save_num, sizeof(g_save_num), 0);
				recv(sock, &msg_int, sizeof(msg_int), 0);
				if (msg_int == 0) {
					printf("선택하신 챕터가 다릅니다. 이 방의 챕터와 다릅니다. 다시 시도해 주세요. \n");
					system("pause");
					return;
				}

				break;
			}
		}
		else {
			choice_room = -2;
			send(sock, &choice_room, sizeof(choice_room), 0);
			printf("개설된 방 중 하나를 선택해 주세요. \n");
			system("pause");
		}
	}

	InitStory(sock, g_player_num, g_save_num, choice_room);

	return;
}

void Load_Game()
{
	int msg_int;
	int item;
	int clue;
	int stage;
	int chapter;
	int i = 0;

	send(sock, &g_player_num, sizeof(g_player_num), 0);

	while (true) {
		system("cls");

		recv(sock, &msg_int, sizeof(msg_int), 0);
		for (i; i < msg_int; i++) {
			recv(sock, &chapter, sizeof(chapter), 0);
			recv(sock, &stage, sizeof(stage), 0);
			recv(sock, &item, sizeof(item), 0);
			recv(sock, &clue, sizeof(clue), 0);
			printf("%d. %d챕터 %d스테이지 \n아이템 : %d개 \n단서 : %d개 \n \n", i + 1, chapter, stage, item, clue);
		}

		printf("페이지 (1 ~ 5) : ");
		scanf_s("%d", &msg_int);
		i = 4 * (msg_int - 1);
		if (msg_int < 1 || msg_int > 5) {
			msg_int = 0;
			send(sock, &msg_int, sizeof(msg_int), 0);
			break;
		}
		send(sock, &msg_int, sizeof(msg_int), 0);
	}

	printf("선택 : ");
	scanf_s("%d", &msg_int);
	if (msg_int >= 1 && msg_int <= 20) {
		msg_int--;
		g_save_num = msg_int;
	}

	return;
}

int Option()
{
	system("cls");

	int x, y;
	int key = 0;

	x = 2, y = 0;

	MoveCursor(x - 2, y);
	printf("> Login Data");

	MoveCursor(x, y + 2);
	printf("Logout");

	MoveCursor(x, y + 4);
	printf("Exit");

	while (key != 4) {
		key = ControlKey();

		switch (key) {
		case UP: {
			if (y > 0) {
				MoveCursor(x - 2, y);
				printf(" ");
				MoveCursor(x - 2, y -= 2);
				printf(">");
			}
			break;
		}

		case DOWN: {
			if (y < 4) {
				MoveCursor(x - 2, y);
				printf(" ");

				MoveCursor(x - 2, y += 2);
				printf(">");
			}
			break;
		}

		case ENTER: {
			y = y / 2;
			system("cls");
			send(sock, &y, sizeof(y), 0);

			switch (y) {
			case LOGIN_DATA_OPTION: {
				Login_Data();
				return 0;

			}

			case LOGOUT_OPTION: {
				return -1;
				break;
			}

			case EXIT_OPTION: {
				return 0;
			}
			}
		}
		}

	}

	return 0;
}

void Login_Data()
{
	char msg_char[MAX_MSG_LEN] = "";
	int msg_int;

	send(sock, &g_player_num, sizeof(g_player_num), 0);
	recv(sock, msg_char, MAX_MSG_LEN, 0);
	printf("플레이어 아이디 : %s \n", msg_char);
	recv(sock, msg_char, MAX_MSG_LEN, 0);
	printf("플레이어 비밀번호 : %s \n", msg_char);
	recv(sock, &msg_int, sizeof(msg_int), 0);
	printf("플레이어 번호 : %d \n", msg_int);
	printf("현재 세이브 번호 : %d \n", g_save_num + 1);
	recv(sock, &msg_int, sizeof(msg_int), 0);
	printf("플레이어 엔딩 개수 : %d \n", msg_int);

	system("pause");

	return;
}

void Ending()
{
	int msg_int;
	int num_ending;

	send(sock, &g_player_num, sizeof(g_player_num), 0);
	recv(sock, &msg_int, sizeof(msg_int), 0);
	if (msg_int == 0) {
		printf("현재 발견한 엔딩이 없습니다. \n");
		system("pause");
	}

	for (int i = 0; i < msg_int; i++) {
		recv(sock, &num_ending, sizeof(num_ending), 0);
		printf("%d \n", num_ending);
	}
	
	return;
}