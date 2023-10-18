#include <stdio.h>
#include <WinSock2.h>

#include "story.h"
#include "system.h"

SOCKET sock;
int g_player_num;
int g_save_num;
int g_item_num;
int g_room_num;

enum Chapter { CHAPTER0, CHAPTER1, CHAPTER2, CHAPTER3, CHAPTER4 };
enum Stage { STAGE1, STAGE2, STAGE3, STAGE4 };
enum _011 { EXPLORE_011, INVESTIGATE_011, MENU_011 };
enum _111 { EXPLORE_111, INVESTIGATE_111, MENU_111 };
enum Menu { ITEM, SAVE, BACK, EXIT };
enum Item {
	FLASH = 10, FLASH_BATTERY = 11, FLASH_LIGHT = 12, WALLET_1 = 20, NOTE_1 = 50, WALLET_2 = 100010,
	NOTE_2 = 100040
};

int Player0();
int Player1();
int Player0_Chapter0();
int Player1_Chapter0();
int Menu_Game();
void Item();
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
	case CHAPTER0: {
		exit = Player0_Chapter0();
		break;
	}
	case CHAPTER1: {
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

int Player1()
{
	int exit = 0;
	int chapter_number;
	int stage_number;

	send(sock, &g_save_num, sizeof(g_save_num), 0);
	recv(sock, &chapter_number, sizeof(chapter_number), 0);
	recv(sock, &stage_number, sizeof(stage_number), 0);

	switch (chapter_number) {
	case CHAPTER0: {
		exit = Player1_Chapter0();
		break;
	}

	case CHAPTER1: {
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

int Player0_Chapter0()
{
	int x, y;
	int key;
	int msg_int;
	int explore = 0;
	int investigate = 0;
	int exit = 0;

	while (explore == 0 || investigate == 0) {
		key = 0;
		x = 2;
		y = 4;

		system("cls");

		printf("ģ���� �Բ� ������ ��԰� ������ ���ڸ��� �츮�� ������ �ῡ �����. \n");
		printf("�ῡ�� ����� ������ �ѷ����� ������ �ƴ� �ٸ� ���ó�� ������. \n \n \n");


		MoveCursor(x - 2, y);
		printf("> ���� �ѷ�����");

		MoveCursor(x, y + 2);
		printf("�� ����");

		MoveCursor(x, y + 4);
		printf("�޴�");

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
				y = y / 2 - 2;
				system("cls");

				switch (y) {
				case EXPLORE_011: {
					printf("���� �ణ ������ ������ ��ȭ�Ⱑ ���̰� �ƹ��� �Ҹ��� �鸮�� �ʴ´�. \n");
					printf("�� 3���� ���δ�. \n");
					system("pause");
					explore++;
					break;
				}

				case INVESTIGATE_011: {
					msg_int = 0;
					send(sock, &msg_int, sizeof(msg_int), 0);
					send(sock, &g_player_num, sizeof(g_player_num), 0);
					printf("������, ����, ��ø�� �ִ�. \n \n");
					printf("������, ����, ��ø ȹ�� \n");
					system("pause");
					investigate++;
					if (investigate == 1) {
						msg_int = 3;
						send(sock, &msg_int, sizeof(msg_int), 0);
						msg_int = 10;
						send(sock, &msg_int, sizeof(msg_int), 0);
						msg_int = 20;
						send(sock, &msg_int, sizeof(msg_int), 0);
						msg_int = 50;
						send(sock, &msg_int, sizeof(msg_int), 0);
					}

					else {
						msg_int = 0;
						send(sock, &msg_int, sizeof(msg_int), 0);
					}
					break;
				}

				case MENU_011: {
					msg_int = 1;
					send(sock, &msg_int, sizeof(msg_int), 0);
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
}

int Player1_Chapter0()
{
	int x, y;
	int key;
	int msg_int;
	int explore = 0;
	int investigate = 0;
	int exit = 0;

	while (explore == 0 || investigate == 0) {
		key = 0;
		x = 2;
		y = 4;

		system("cls");

		printf("ģ���� �Բ� ������ ��԰� ������ ���ڸ��� �츮�� ������ �ῡ �����. \n");
		printf("�ῡ�� ����� ������ �ѷ����� ģ���� ����� �־���. \n \n \n");

		MoveCursor(x - 2, y);
		printf("> ���� �ѷ�����");

		MoveCursor(x, y + 2);
		printf("�� ����");

		MoveCursor(x, y + 4);
		printf("�޴�");

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
				y = y / 2 - 2;
				system("cls");

				switch (y) {
				case EXPLORE_011: {
					printf("�кҸ��� ������ ���߰� �ִ�. \n");
					printf("�ۿ��� ��Ӱ� �� ���� ������ â���� ���Ա��� ��� ����־� ������� ����� �� ����. \n");
					printf("�ȿ��� ��ȭ��� �ٸ� ������ ����� ������ 5���� ���δ�. \n");
					system("pause");
					explore++;
					break;
				}

				case INVESTIGATE_011: {
					msg_int = 0;
					send(sock, &msg_int, sizeof(msg_int), 0);
					send(sock, &g_player_num, sizeof(g_player_num), 0);
					printf("������ ��ø�� �ִ�. \n \n");
					printf("����, ��ø ȹ�� \n");
					investigate++;
					if (investigate == 1) {
						msg_int = 2;
						send(sock, &msg_int, sizeof(msg_int), 0);
						msg_int = 100010;
						send(sock, &msg_int, sizeof(msg_int), 0);
						msg_int = 100040;
						send(sock, &msg_int, sizeof(msg_int), 0);
					}

					else {
						msg_int = 0;
						send(sock, &msg_int, sizeof(msg_int), 0);
					}
					system("pause");
					break;
				}

				case MENU_011: {
					msg_int = 1;
					send(sock, &msg_int, sizeof(msg_int), 0);
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
}

int Menu_Game()
{
	int x, y;
	int key;
	int msg_int;

	while (true) {
		key = 0;
		x = 2;
		y = 0;

		system("cls");

		MoveCursor(x - 2, y);
		printf("> ������");

		MoveCursor(x, y + 2);
		printf("���̺�");

		MoveCursor(x, y + 4);
		printf("����");

		MoveCursor(x, y + 6);
		printf("����");

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
					Item();
					break;
				}

				case SAVE: {
					int chapter, stage, item, clue;
					int i = 2;

					send(sock, &g_player_num, sizeof(g_player_num), 0);

					while (true) {
						system("cls");

						recv(sock, &msg_int, sizeof(msg_int), 0);
						for (i; i < msg_int; i++) {
							recv(sock, &chapter, sizeof(chapter), 0);
							recv(sock, &stage, sizeof(stage), 0);
							recv(sock, &item, sizeof(item), 0);
							recv(sock, &clue, sizeof(clue), 0);
							printf("%d. %dé�� %d�������� \n������ : %d�� \n�ܼ� : %d�� \n \n", i + 1, chapter, stage, item, clue);
						}

						printf("������ (1 ~ 5) : ");
						scanf_s("%d", &msg_int);
						i = 4 * (msg_int - 1);
						if (msg_int < 1 || msg_int > 5) {
							msg_int = 0;
							send(sock, &msg_int, sizeof(msg_int), 0);
							break;
						}
						send(sock, &msg_int, sizeof(msg_int), 0);
					}

					printf("���� : ");
					scanf_s("%d", &msg_int);
					if (msg_int >= 3 && msg_int <= 20) {
						msg_int--;
						send(sock, &msg_int, sizeof(msg_int), 0);
					}

					else {
						msg_int = 0;
						send(sock, &msg_int, sizeof(msg_int), 0);
						break;
					}

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

void Item()
{
	int msg_int;
	int item, item_num;

	send(sock, &g_player_num, sizeof(g_player_num), 0);
	recv(sock, &item_num, sizeof(item_num), 0);
	if (item_num == 0) {
		printf("���� ���� �������� �����ϴ�. \n");
		system("pause");
		return;
	}

	for (int i = 0; i < item_num; i++) {
		recv(sock, &item, sizeof(item), 0);
		printf("%d. %s \n", item, s_items[item].name);
		printf("%s \n", s_items[item].explaination);
		if (s_items[item].use == true) {
			printf("��� ���� \n \n");
		}

		else {
			printf("\n");
		}
	}

	printf("���� : ");
	scanf_s("%d", &msg_int);
	send(sock, &msg_int, sizeof(msg_int), 0);
	system("cls");

	switch (msg_int) {
	case FLASH: {
		printf("���� ����� �� �����ϴ�. \n");
		system("pause");
		break;
	}

	case FLASH_BATTERY: {
		printf("�� �������� ���ϰ� ���� �ʽ��ϴ�. \n");
		system("pause");
		break;
	}

	case FLASH_LIGHT: {
		printf("�� �������� ���ϰ� ���� �ʽ��ϴ�. \n");
		system("pause");
		break;
	}

	case WALLET_1: {
		printf("���� �ź����� �����. \n");
		system("pause");
		break;
	}

	case NOTE_1: {
		printf("���� ����� �� �����ϴ�. \n");
		system("pause");
		break;
	}

	case WALLET_2: {
		printf("���� �ź����� �����. \n");
		system("pause");
		break;
	}

	case NOTE_2: {
		printf("���� ����� �� �����ϴ�. \n");
		system("pause");
		break;
	}

	default: {
		printf("�� �������� ����� �� ���ų� ���ϰ� ���� �ʽ��ϴ�. \n");
		system("pause");
		break;
	}
	}
}

void Exit_Game()
{
	int msg_int;
	printf("�ٸ� �÷��̾� ��ٸ��� ��");

	send(sock, &g_room_num, sizeof(g_room_num), 0);
	recv(sock, &msg_int, sizeof(msg_int), 0);
	getc(stdin);
	return;
}