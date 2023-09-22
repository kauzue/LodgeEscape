#include <WinSock2.h>

#include "story.h"
#include "system.h"

SOCKET sock;
int g_player_num;
int g_save_num;
int g_room_num;

enum Chapter { CHAPTER1, CHAPTER2, CHAPTER3, CHAPTER4 };
enum Stage { STAGE1, STAGE2, STAGE3, STAGE4 };
enum _011 { EXPLORE_011, INVESTIGATE_011, MENU_011, EXIT_011};
enum _111 { EXPLORE_111, INVESTIGATE_111, MENU_111, EXIT_111 };

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
	int x, y;
	int key = 0;

	x = 2;
	y = 2;

	printf("ģ���� �Բ� ������ ��԰� ������ ���ڸ��� �츮�� ������ �ῡ �����. \n");
	printf("�ῡ�� ����� ������ �ѷ����� ������ �ƴ� �ٸ� ���ó�� ������. \n");


	MoveCursor(x - 2, y);
	printf("> ���� �ѷ�����");

	MoveCursor(x, y + 2);
	printf("�� ����");

	MoveCursor(x, y + 4);
	printf("�޴�");

	MoveCursor(x, y + 6);
	printf("Exit");

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
			//send(sock, &y, sizeof(y), 0);

			switch (y) {
			case EXPLORE_011: {
				break;
			}

			case INVESTIGATE_011: {
				break;
			}

			case MENU_011: {
				break;
			}

			case EXIT_011: {
				break;
			}
			}

		}
		}

	}
}

void Player1_Chapter1()
{
	printf("�÷��̾� 1");
	system("pause");
}

void EXIT_GAME()
{

}