#pragma warning(disable:4996)

#include <stdio.h>

#include "game.h"
#include "system.h"

enum Login { SIGN_UP_LOGIN, LOGIN_LOGIN, EXIT_LOGIN};
enum Main_Menu { START_GAME_MAIN_MENU, LOAD_GAME_MAIN_MENU, OPTION_MAIN_MENU, ENDING_MAIN_MENU, EXIT_MAIN_MENU };
enum Start_Game { CREATE_ROOM_START_GAME, FIND_ROOM_START_GAME, EXIT_START_GAME};

void Sign_Up();
void Login();
void Game_Main_Menu();
void Start_Game();

SOCKET sock;
int player_num;

void Game_Login(SOCKET socket)
{
	sock = socket;

	while (true) {
		system("cls");

		int x, y;
		int msg_int;
		int key = 0;

		x = 2;
		y = 0;

		MoveCursor(x - 2, y);
		printf("> Sign UP");

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
					Login();
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
	int msg_int;

	while (true) {
		system("cls");

		printf("id : ");
		scanf("%s", &ID);
		send(sock, &ID, sizeof(ID), 0);
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
	scanf("%s", &PassWord);
	send(sock, PassWord, sizeof(PassWord), 0);

	while (true) {
		system("cls");

		printf("player number : ");
		scanf("%d", &msg_int);
		if (msg_int > -1 || msg_int < 2) {
			send(sock, &msg_int, sizeof(msg_int), 0);
			break;
		}

		else {
			printf("0 혹은 1을 입력해 주세요. \n");
			system("pause");
		}
	}
}

void Login()
{

	char ID[MAX_MSG_LEN] = "";
	char PassWord[MAX_MSG_LEN] = "";
	int msg_int;

	while (true) {
		system("cls");

		printf("id : ");
		scanf("%s", ID);

		printf("password : ");
		scanf("%s", PassWord);

		send(sock, ID, MAX_MSG_LEN, 0);
		send(sock, PassWord, MAX_MSG_LEN, 0);

		recv(sock, &player_num, sizeof(msg_int), 0);
		if (player_num == -2) {
			return;
		}

		else if (player_num >= 0) {
			break;
		}

		system("cls");

		printf("아이디 혹은 비밀번호가 틀렸습니다.\n");
		printf("다시 입력해 주세요. \n");
		system("pause");
	}

	Game_Main_Menu();
}

void Game_Main_Menu()
{

	while (true) {
		system("cls");

		int x, y;
		int msg_int;
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
					printf("Load Game is developing \n");
					system("pause");
					break;
				}

				case OPTION_MAIN_MENU: {
					printf("Option is developing \n");
					system("pause");
					break;
				}

				case ENDING_MAIN_MENU: {
					int num_ending;

					send(sock, &player_num, sizeof(player_num), 0);
					recv(sock, &msg_int, sizeof(msg_int), 0);
					if (msg_int == 0) {
						printf("현재 발견한 엔딩이 없습니다. \n");
						system("pause");
					}

					for (int i = 0; i < msg_int; i++) {
						recv(sock, &num_ending, sizeof(num_ending), 0);
						printf("%d \n", num_ending);
					}
					break;
				}

				case EXIT_MAIN_MENU: {
					return;
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
				case CREATE_ROOM_START_GAME: {
					printf("Create Room is developing \n");
					system("pause");
					break;
				}

				case FIND_ROOM_START_GAME: {
					printf("Find Room is developing \n");
					system("pause");
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