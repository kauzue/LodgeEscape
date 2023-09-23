#include <stdio.h>
#include <WinSock2.h>

#include "story.h"
#include "system.h"

SOCKET sock;
int g_player_num;
int g_save_num;
int g_room_num;

enum Chapter { CHAPTER1, CHAPTER2, CHAPTER3, CHAPTER4 };
enum Stage { STAGE1, STAGE2, STAGE3, STAGE4 };
enum _011 { EXPLORE_011, INVESTIGATE_011, MENU_011 };
enum _111 { EXPLORE_111, INVESTIGATE_111, MENU_111 };
enum Menu { ITEM, SAVE, BACK, EXIT };

int Player0();
int Player1();
int Player0_Chapter1();
int Player1_Chapter1();
int Menu_Game();
void Exit_Game();

void InitStory(SOCKET socket, int player_num, int save_num, int room_num)
{
	int exit;
	int player_number;
	int msg_int;

	sock = socket;
	g_player_num = player_num;
	g_save_num = save_num;
	g_room_num = room_num;

	while (true) {

		send(sock, &g_player_num, sizeof(g_player_num), 0);
		recv(sock, &player_number, sizeof(player_number), 0);

		system("cls");

		if (player_number == 0) {
			exit = Player0();
		}

		else {
			exit = Player1();
		}
		if (exit == -1) {
			break;
		}
	}
}

int Player0()
{
	int exit = 0;
	int chapter_number;
	int stage_number;

	send(sock, &g_save_num, sizeof(g_save_num), 0);
	recv(sock, &chapter_number, sizeof(chapter_number), 0);
	recv(sock, &stage_number, sizeof(stage_number), 0);

	switch (chapter_number) {
	case CHAPTER1: {
		exit = Player0_Chapter1();
		break;
	}

	case CHAPTER2: {
		printf("성공");
		break;
	}

	case CHAPTER3: {
		break;
	}

	case CHAPTER4: {
		break;
	}
	}

	if (exit == -1) {
		return -1;
	}
	return 0;
}

int Player1()
{
	int exit = 0;
	int chapter_number;
	int stage_number;

	send(sock, &g_save_num, sizeof(g_save_num), 0);
	recv(sock, &chapter_number, sizeof(chapter_number), 0);
	recv(sock, &stage_number, sizeof(stage_number), 0);

	switch (chapter_number) {
	case CHAPTER1: {
		exit = Player1_Chapter1();
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

	if (exit == -1) {
		return -1;
	}
	return 0;
}

int Player0_Chapter1()
{
	int x, y;
	int key;
	int explore = 0;
	int investigate = 0;
	int exit = 0;

	while (explore == 0 || investigate == 0) {
		key = 0;
		x = 2;
		y = 4;

		system("cls");

		printf("친구와 함께 여관에 놀러왔고 여관에 들어서자마자 우리는 졸려서 잠에 들었다. \n");
		printf("잠에서 깨어나서 주위를 둘러보니 여관이 아닌 다른 장소처럼 보였다. \n \n \n");


		MoveCursor(x - 2, y);
		printf("> 주위 둘러보기");

		MoveCursor(x, y + 2);
		printf("몸 수색");

		MoveCursor(x, y + 4);
		printf("메뉴");

		while (key != 4) {
			key = ControlKey();

			switch (key) {
			case UP: {
				if (y > 4) {
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
				y = y / 2 - 1;
				system("cls");
				send(sock, &y, sizeof(y), 0);
				send(sock, &g_player_num, sizeof(g_player_num), 0);

				switch (y) {
				case EXPLORE_011: {
					printf("불이 약간 들어오는 전구와 전화기가 보이고 아무런 소리도 들리지 않는다. \n");
					printf("문 3개가 보인다. \n");
					system("pause");
					explore++;
					break;
				}

				case INVESTIGATE_011: {
					printf("손전등, 지갑, 수첩이 있다. \n \n");
					printf("손전등, 지갑, 수첩 획득 \n");
					system("pause");
					investigate++;
					break;
				}

				case MENU_011: {
					exit = Menu_Game();
					if (exit == -1) {
						return -1;
					}
					break;
				}
				}

			}
			}

		}
	}

	printf("성공 \n");
	Exit_Game();
	return -1;
}

int Player1_Chapter1()
{
	int x, y;
	int key;
	int explore = 0;
	int investigate = 0;
	int exit = 0;

	while (explore == 0 || investigate == 0) {
		key = 0;
		x = 2;
		y = 4;

		system("cls");

		printf("친구와 함께 여관에 놀러왔고 여관에 들어서자마자 우리는 졸려서 잠에 들었다. \n");
		printf("잠에서 깨어나서 주위를 둘러보니 친구가 사라져 있었다. \n \n \n");

		MoveCursor(x - 2, y);
		printf("> 주위 둘러보기");

		MoveCursor(x, y + 2);
		printf("몸 수색");

		MoveCursor(x, y + 4);
		printf("메뉴");

		while (key != 4) {
			key = ControlKey();

			switch (key) {
			case UP: {
				if (y > 4) {
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
				y = y / 2 - 1;
				system("cls");
				send(sock, &y, sizeof(y), 0);
				send(sock, &g_player_num, sizeof(g_player_num), 0);

				switch (y) {
				case EXPLORE_011: {
					printf("촛불만이 여관을 비추고 있다. \n");
					printf("밖에는 어둡고 비가 오고 있으며 창문과 출입구는 모두 잠겨있어 나가기는 어려울 것 같다. \n");
					printf("안에는 전화기와 다른 방으로 연결된 문들이 5개가 보인다. \n");
					system("pause");
					explore++;
					break;
				}

				case INVESTIGATE_011: {
					printf("지갑 외에 다른 단서는 아무것도 없다. \n \n");
					printf("지갑 획득 \n");
					system("pause");
					investigate++;
					break;
				}

				case MENU_011: {
					exit = Menu_Game();
					if (exit == -1) {
						return -1;
					}
					break;
				}
				}

			}
			}

		}
	}

	Exit_Game();
	return -1;
}

int Menu_Game()
{
	int x, y;
	int key;

	while (true) {
		key = 0;
		x = 2;
		y = 0;

		system("cls");

		MoveCursor(x - 2, y);
		printf("> 아이템");

		MoveCursor(x, y + 2);
		printf("세이브");

		MoveCursor(x, y + 4);
		printf("이전");

		MoveCursor(x, y + 6);
		printf("종료");

		while (key != 4) {
			key = ControlKey();

			switch (key) {
			case UP: {
				if (y > 2) {
					MoveCursor(x - 2, y);
					printf(" ");
					MoveCursor(x - 2, y -= 2);
					printf(">");
				}
				break;
			}

			case DOWN: {
				if (y < 6) {
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
				case ITEM: {
					printf("Item is developing \n");
					system("pause");
					break;
				}

				case SAVE: {
					printf("Save is developing \n");
					system("pause");
					break;
				}

				case BACK: {
					return 0;
				}

				case EXIT: {
					Exit_Game();
					return -1;
				}
				}
			}
			}
		}
	}
}

void Exit_Game()
{
	int msg_int;
	printf("다른 플레이어 기다리는 중");

	send(sock, &g_room_num, sizeof(g_room_num), 0);
	recv(sock, &msg_int, sizeof(msg_int), 0);
	getc(stdin);
	return;
}