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
int Option();

SOCKET sock;
int g_player_num;
int g_save_num;
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
		recv(sock, &g_save_num, sizeof(g_save_num), 0);
		if (g_player_num == -2) {
			return 0;
		}

		else if (g_player_num >= 0) {
			break;
		}

		system("cls");

		printf("아이디 혹은 비밀번호가 틀렸습니다.\n");
		printf("다시 입력해 주세요. \n");
		system("pause");
	}

	int exit = Game_Main_Menu();
	if (exit == -1) {
		return -1;
	}
	return 0;
}

int Game_Main_Menu()
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
					int stage;
					int chapter;
					int choice_save;

					send(sock, &g_player_num, sizeof(g_player_num), 0);
					recv(sock, &msg_int, sizeof(msg_int), 0);
					if (msg_int == 0) {
						printf("현재 저장한 게임 데이터가 없습니다. \n");
						system("pause");
						break;
					}
					while (true) {
						for (int i = 0; i < msg_int; i++) {
							recv(sock, &stage, sizeof(stage), 0);
							recv(sock, &chapter, sizeof(chapter), 0);
							printf("%d. %d스테이지 %d챕터 \n", i + 1, stage, chapter);
						}
						printf("선택 : ");
						scanf_s("%d", &choice_save);
						if (choice_save >= 0 || choice_save < msg_int) {
							g_save_num = choice_save;
							break;
						}

						system("cls");
						printf("다시 선택해 주세요. \n");
						system("puase");
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
					char room_name[MAX_MSG_LEN] = "";
					int password, msg_int;

					printf("room name : ");
					scanf_s("%s", room_name, MAX_MSG_LEN);
					printf("password : ");
					scanf_s("%d", &password);

					send(sock, room_name, MAX_MSG_LEN, 0);
					send(sock, &password, sizeof(password), 0);
					send(sock, &g_player_num, sizeof(g_player_num), 0);
					recv(sock, &g_room_num, sizeof(g_room_num), 0);

					system("cls");
					printf("다른 플레이어를 기다리는 중");

					recv(sock, &msg_int, sizeof(msg_int), 0);
					if (msg_int >= 0) {
						send(sock, &msg_int, sizeof(msg_int), 0);
						InitStory(sock, g_player_num, g_save_num, g_room_num);
					}

					break;
				}

				case FIND_ROOM_START_GAME: {
					char room_name[MAX_MSG_LEN] = "";
					int msg_int, choice_room, password;

					while (true) {
						recv(sock, &msg_int, sizeof(msg_int), 0);
						if (msg_int == 0) {
							printf("현재 개설된 방이 없습니다.");
							system("pause");
							goto EXIT_FIND_ROOM;
						}

						for (int i = 0; i < msg_int; i++) {
							recv(sock, room_name, MAX_MSG_LEN, 0);
							printf("%d. %s \n \n", i, room_name);
						}

						printf("choice : ");
						scanf_s("%d", &choice_room);
						if (choice_room == -1) {
							goto EXIT_FIND_ROOM;
						}

						else if (choice_room >= 0 && choice_room <= msg_int) {
							send(sock, &choice_room, sizeof(choice_room), 0);
							send(sock, &g_player_num, sizeof(g_player_num), 0);

							printf("password : ");
							scanf_s("%d", &password);
							send(sock, &password, sizeof(password), 0);
							recv(sock, &msg_int, sizeof(msg_int), 0);
							if (msg_int >= 0) {
								break;
							}
						}
					}

					InitStory(sock, g_player_num, g_save_num, g_room_num);

EXIT_FIND_ROOM:
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
			case LOGIN_DATA_OPTION: {
				char msg_char[MAX_MSG_LEN] = "";
				int msg_int;

				send(sock, &g_player_num, sizeof(g_player_num), 0);
				recv(sock, msg_char, MAX_MSG_LEN, 0);
				printf("플레이어 아이디 : %s \n", msg_char);
				recv(sock, msg_char, MAX_MSG_LEN, 0);
				printf("플레이어 비밀번호 : %s \n", msg_char);
				recv(sock, &msg_int, sizeof(msg_int), 0);
				printf("플레이어 번호 : %d \n", msg_int);
				recv(sock, &msg_int, sizeof(msg_int), 0);
				printf("플레이어 세이브 개수 : %d \n", msg_int);
				recv(sock, &msg_int, sizeof(msg_int), 0);
				printf("플레이어 엔딩 개수 : %d \n", msg_int);

				system("pause");
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

}