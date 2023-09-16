#pragma warning(disable:4996)

#include <stdio.h>

#include "game.h"
#include "system.h"

enum Login { SIGNUP_LOGIN, LOGIN_LOGIN, EXIT_LOGIN};

void Game_Login(SOCKET sock)
{
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

				char ID[MAX_MSG_LEN] = "";
				char PassWord[MAX_MSG_LEN] = "";

				switch (y) {
				case SIGNUP_LOGIN: {
					while (true) {
						system("cls");
						printf("id : ");
						scanf("%s", &ID);
						send(sock, &ID, sizeof(ID), 0);
						recv(sock, &msg_int, sizeof(msg_int), 0);
						if (msg_int == -1) {
							goto ERR_SIGNUP;
						}

						else if (msg_int == 1) {
							break;
						}

						printf("이미 있는 아이디입니다. \n");
						printf("다시 입력해 주세요. \n");
						system("pause");

					}

					printf("password : ");
					scanf("%s", &PassWord);
					send(sock, PassWord, sizeof(PassWord), 0);

					while (true) {
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
ERR_SIGNUP:
						break;
					}
					break;
				}

				case LOGIN_LOGIN: {
					while (true) {
						printf("id : ");
						scanf("%s", ID);

						printf("password : ");
						scanf("%s", PassWord);

						send(sock, ID, MAX_MSG_LEN, 0);
						send(sock, PassWord, MAX_MSG_LEN, 0);

						recv(sock, &msg_int, sizeof(msg_int), 0);
						if (msg_int == -1) {
							goto ERR_LOGIN;
						}

						else if (msg_int == 1) {
							break;
						}

						printf("아이디 혹은 비밀번호가 틀렸습니다.\n");
						printf("다시 입력해 주세요. \n");
						system("pause");
					}
					printf("성공");

ERR_LOGIN:
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