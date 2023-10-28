#include <stdio.h>
#include <WinSock2.h>

#include "story.h"
#include "system.h"

SOCKET sock;
int g_player_num;
int g_save_num;
int g_item_num;
int g_room_num;
int end = 0;

enum Chapter { CHAPTER0, CHAPTER1, CHAPTER2, CHAPTER3, CHAPTER4 };
enum Stage { STAGE1, STAGE2, STAGE3, STAGE4 };
enum _001 { EXPLORE_001, INVESTIGATE_001, MENU_001 };
enum _002 { EXPLORE_ROOM_1_002, EXPLORE_ROOM_2_002, EXPLORE_ROOM_3_002, EXPLORE_ROOM_4_002, MENU_002 };
enum _101 { EXPLORE_101, INVESTIGATE_101, MENU_101 };
enum Menu { ITEM, SAVE, BACK, EXIT };
enum Item {
	FLASH = 10, FLASH_BATTERY = 11, FLASH_LIGHT = 12, WALLET_1 = 20, NOTE_1 = 50, WALLET_2 = 100010,
	NOTE_2 = 100040
};

void Player0();
void Player1();
int Menu_Game();
void Item();
void Exit_Game();
int Player0_Chapter0(int);
int Player0_Chapter1(int);
int Player1_Chapter0(int);
int Player1_Chapter1(int);

void InitStory(SOCKET socket, int player_num, int save_num, int room_num)
{
	int exit;
	int player_number;
	int msg_int;

	sock = socket;
	g_player_num = player_num;
	g_save_num = save_num;
	g_room_num = room_num;

	send(sock, &g_player_num, sizeof(g_player_num), 0);
	recv(sock, &player_number, sizeof(player_number), 0);
	send(sock, &g_save_num, sizeof(g_save_num), 0);

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
	int exit = 0;
	int chapter_number;
	int stage_number;

	while (true) {
		recv(sock, &chapter_number, sizeof(chapter_number), 0);
		recv(sock, &stage_number, sizeof(stage_number), 0);
		if (chapter_number > MAX_CHAPTER || end > 0) {
			end = 4;
			send(sock, &end, sizeof(end), 0);
			Exit_Game();
			return;
		}

		switch (chapter_number) {
		case CHAPTER0: {
			exit = Player0_Chapter0(stage_number);
			break;
		}
		case CHAPTER1: {
			exit = Player0_Chapter1(stage_number);
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

		default: {
			return;
		}
		}
		if (exit == -1) {
			return;
		}

	}
}

void Player1()
{
	int exit = 0;
	int chapter_number;
	int stage_number;

	while (true) {
		recv(sock, &chapter_number, sizeof(chapter_number), 0);
		recv(sock, &stage_number, sizeof(stage_number), 0);
		if (chapter_number > MAX_CHAPTER || end > 0) {
			end = 4;
			send(sock, &end, sizeof(end), 0);
			Exit_Game();
			return;
		}

		switch (chapter_number) {
		case CHAPTER0: {
			exit = Player1_Chapter0(stage_number);
			break;
		}

		case CHAPTER1: {
			exit = Player1_Chapter1(stage_number);
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

		default: {
			return;
		}
		}
		if (exit == -1) {
			return;
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
							printf("%d. %d챕터 %d스테이지 \n아이템 : %d개 \n단서 : %d개 \n \n", i + 1, chapter, stage, item, clue);
						}

						printf("페이지 (1 ~ 5) : ");
						scanf_s("%d", &msg_int);
						i = 4 * (msg_int - 1);
						if (msg_int == 1) {
							i = 2;
						}
						else if (msg_int < 1 || msg_int > 5) {
							msg_int = 0;
							send(sock, &msg_int, sizeof(msg_int), 0);
							break;
						}
						send(sock, &msg_int, sizeof(msg_int), 0);
					}

					printf("선택 : ");
					scanf_s("%d", &msg_int);
					if (msg_int >= 3 && msg_int <= 20) {
						msg_int--;
						send(sock, &msg_int, sizeof(msg_int), 0);
					}

					else {
						system("cls");
						printf("이 저장장치는 선택할 수 없습니다.");

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
	int item, item_num, max_item, max_page;
	int i = 0;

	send(sock, &g_player_num, sizeof(g_player_num), 0);
	recv(sock, &max_item, sizeof(max_item), 0);
	if (max_item == 0) {
		printf("현재 가진 아이템이 없습니다. \n");
		system("pause");
		return;
	}

	max_page = max_item / 4 + 1;
	if (max_item % 4 == 0) {
		max_page -= 1;
	}

	while (true) {
		system("cls");
		recv(sock, &item_num, sizeof(item_num), 0);
		for (i; i < item_num; i++) {
			recv(sock, &item, sizeof(item), 0);
			printf("%d. %s \n", item, s_items[item].name);
			printf("%s \n", s_items[item].explaination);
			if (s_items[item].use == true) {
				printf("사용 가능 \n \n");
			}

			else {
				printf("\n");
			}
		}

		printf("페이지 (1 ~ %d) : ", max_page);
		scanf_s("%d", &msg_int);
		i = 4 * (msg_int - 1);
		if (msg_int < 1 || msg_int > max_page) {
			msg_int = -1;
			send(sock, &msg_int, sizeof(msg_int), 0);
			break;
		}
		send(sock, &i, sizeof(i), 0);
	}

	printf("선택 : ");
	scanf_s("%d", &msg_int);
	send(sock, &msg_int, sizeof(msg_int), 0);
	recv(sock, &msg_int, sizeof(msg_int), 0);
	system("cls");

	switch (msg_int) {
	case FLASH: {
		printf("아직 사용할 수 없습니다. \n");
		system("pause");
		break;
	}

	case FLASH_BATTERY: {
		printf("이 아이템을 지니고 있지 않습니다. \n");
		system("pause");
		break;
	}

	case FLASH_LIGHT: {
		printf("이 아이템을 지니고 있지 않습니다. \n");
		system("pause");
		break;
	}

	case WALLET_1: {
		printf("돈과 신분증을 얻었다. \n");
		system("pause");
		break;
	}

	case NOTE_1: {
		printf("아직 사용할 수 없습니다. \n");
		system("pause");
		break;
	}

	case WALLET_2: {
		printf("돈과 신분증을 얻었다. \n");
		system("pause");
		break;
	}

	case NOTE_2: {
		printf("아직 사용할 수 없습니다. \n");
		system("pause");
		break;
	}

	default: {
		printf("이 아이템은 사용할 수 없거나 지니고 있지 않습니다. \n");
		system("pause");
		break;
	}
	}
}

void Exit_Game()
{
	system("cls");
	int msg_int;
	printf("다른 플레이어 기다리는 중");

	send(sock, &g_room_num, sizeof(g_room_num), 0);
	recv(sock, &msg_int, sizeof(msg_int), 0);
	getc(stdin);
	return;
}

int Player0_Chapter0(int stage)
{
	int x, y;
	int key;
	int msg_int;
	int exit = 0;

	switch (stage) {
	case STAGE1: {
		int explore = 0;
		int investigate = 0;

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
					y = y / 2 - 2;
					system("cls");

					switch (y) {
					case EXPLORE_001: {
						printf("불이 약간 들어오는 전구가 보이고 아무런 소리도 들리지 않는다. \n");
						printf("문 4개가 보인다. \n");
						system("pause");
						explore++;
						break;
					}

					case INVESTIGATE_001: {
						msg_int = 0;
						send(sock, &msg_int, sizeof(msg_int), 0);
						send(sock, &g_player_num, sizeof(g_player_num), 0);
						send(sock, &msg_int, sizeof(msg_int), 0);
						recv(sock, &msg_int, sizeof(msg_int), 0);
						printf("손전등, 지갑, 수첩이 있다. \n \n");
						printf("손전등, 지갑, 수첩 획득 \n");
						system("pause");
						investigate++;
						if (msg_int != 1) {
							msg_int = 3;
							send(sock, &msg_int, sizeof(msg_int), 0);
							msg_int = 10;
							send(sock, &msg_int, sizeof(msg_int), 0);
							msg_int = 20;
							send(sock, &msg_int, sizeof(msg_int), 0);
							msg_int = 50;
							send(sock, &msg_int, sizeof(msg_int), 0);
						}
						break;
					}

					case MENU_001: {
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
		break;
	}

	case STAGE2: {
		int t = 0;
		int tem = 0;
		while (t == 0 || tem == 0) {
			key = 0;
			x = 2;
			y = 2;

			system("cls");

			printf("이 방에는 불이 약간 들어오는 전구와 문 4개가 보인다. \n");

			MoveCursor(x - 2, y);
			printf("> 방 1 조사");

			MoveCursor(x, y + 2);
			printf("방 2 조사");

			MoveCursor(x, y + 4);
			printf("방 3 조사");

			MoveCursor(x, y + 6);
			printf("방 4 조사");

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
					y = y / 2 - 2;
					system("cls");

					switch (y) {
					case EXPLORE_ROOM_1_002: {
						msg_int = 5;
						send(sock, &msg_int, sizeof(msg_int), 0);
						msg_int = 0;
						send(sock, &msg_int, sizeof(msg_int), 0);
						send(sock, &msg_int, sizeof(msg_int), 0);
						send(sock, &g_player_num, sizeof(g_player_num), 0);
						printf("화장실이다. 물은 나오지 않는 것 같다. \n");
						system("pause");
					}

					case EXPLORE_ROOM_2_002: {
						printf("문이 잠겨있습니다. \n");
						system("pause");
					}

					case EXPLORE_ROOM_3_002: {
						printf("문이 잠겨있습니다. \n");
						system("pause");
					}

					case EXPLORE_ROOM_4_002: {
						printf("문이 잠겨있습니다. \n");
						system("pause");
					}

					case MENU_002: {

					}
					}
				}
				}
			}
		}
		break;
	}

	case STAGE3: {
		break;
	}

	case STAGE4: {
		break;
	}

	}

	if (stage == MAX_STAGE) {
		msg_int = 2;
	}

	else {
		msg_int = 3;
	}

	send(sock, &msg_int, sizeof(msg_int), 0);
	send(sock, &g_player_num, sizeof(g_player_num), 0);

	return 0;
}

int Player0_Chapter1(int stage)
{
	return;
}

int Player1_Chapter0(int stage)
{
	int x, y;
	int key;
	int msg_int;
	int exit = 0;

	switch (stage) {
	case STAGE1: {
		int explore = 0;
		int investigate = 0;

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
					y = y / 2 - 2;
					system("cls");

					switch (y) {
					case EXPLORE_101: {
						printf("촛불만이 여관을 비추고 있다. \n");
						printf("밖에는 어둡고 비가 오고 있으며 창문과 출입구는 모두 잠겨있어 나가기는 어려울 것 같다. \n");
						printf("안에는 책장 하나와 간이 주방과 다른 방으로 연결된 문들이 3개가 보인다. \n");
						system("pause");
						explore++;
						break;
					}

					case INVESTIGATE_101: {
						msg_int = 0;
						send(sock, &msg_int, sizeof(msg_int), 0);
						send(sock, &g_player_num, sizeof(g_player_num), 0);
						send(sock, &msg_int, sizeof(msg_int), 0);
						recv(sock, &msg_int, sizeof(msg_int), 0);
						printf("지갑과 수첩이 있다. \n \n");
						printf("지갑, 수첩 획득 \n");
						investigate++;
						if (msg_int != 1) {
							msg_int = 2;
							send(sock, &msg_int, sizeof(msg_int), 0);
							msg_int = 100010;
							send(sock, &msg_int, sizeof(msg_int), 0);
							msg_int = 100040;
							send(sock, &msg_int, sizeof(msg_int), 0);
						}
						system("pause");
						break;
					}

					case MENU_101: {
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
		break;
	}

	case STAGE2: {
		break;
	}

	case STAGE3: {
		break;
	}

	case STAGE4: {
		break;
	}

	}

	if (stage == MAX_STAGE) {
		msg_int = 2;
	}

	else {
		msg_int = 3;
	}


	send(sock, &msg_int, sizeof(msg_int), 0);
	send(sock, &g_player_num, sizeof(g_player_num), 0);

	return 0;
}

int Player1_Chapter1(int stage)
{

}