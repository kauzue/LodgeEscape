#include <stdio.h>
#include <WinSock2.h>
#include <process.h>

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
enum _001 { EXPLORE_001, INVESTIGATE_001, NEXTSTAGE_001, MENU_001 };
enum _002 {
	EXPLORE_ROOM_1_002, EXPLORE_ROOM_2_002, EXPLORE_ROOM_3_002, EXPLORE_ROOM_4_002,
	BACKSTAGE_002, MENU_002
};
enum _003 { EXPLORE_003, NEXTCHAPTER_003, BACKSTAGE_003, MENU_003 };
enum _101 { EXPLORE_101, INVESTIGATE_101, NEXTSTAGE_101, MENU_101 };
enum _102 {
	EXPLORE_ROOM_1_102, EXPLORE_ROOM_2_102, EXPLORE_ROOM_3_102, EXPLORE_BOOKSHELF_102, EXPLORE_KITCHEN_102,
	BACKSTAGE_102, MENU_102
};
enum _103 { EXPLORE_103, NEXTCHAPTER_103, BACKSTAGE_103, MENU_103 };
enum Menu { ITEM, SAVE, BACK, EXIT };
enum Item {
	FLASH = 10, FLASH_BATTERY = 11, FLASH_LIGHT = 12, WALLET_1 = 20, NOTE_1 = 50, WALLET_2 = 100010,
	NOTE_2 = 100040, KNIFE = 100050, DRY_DISHCLOTH = 100060, WET_DISHCLOTH = 100061
};
enum Book {
	BOOK0, BOOK1, BOOK2, BOOK3, BOOK4, BOOK5, BOOK6, BOOK7, BOOK8, BOOK9,
	BOOK10, BOOK11, BOOK12, BOOK13, BOOK14, BOOK15, BOOK16, BOOK17, BOOK18, BOOK19,
	BOOK20, BOOK21, BOOK22, BOOK23, BOOK24, BOOK25, BOOK26, BOOK27, BOOK28, BOOK29,
	BOOK30, BOOK31, BOOK32, BOOK33, BOOK34, BOOK35, BOOK36, BOOK37, BOOK38, BOOK39,
};

void Player0();
void Player1();
int Menu_Game();
void Item();
void InterPhone();
void Recv();
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

	case KNIFE: {
		printf("이 아이템은 사용할 수 없습니다.");
		system("pause");
		break;
	}

	case DRY_DISHCLOTH: {
		printf("이 아이템은 사용할 수 없습니다.");
		system("pause");
		break;
	}

	case WET_DISHCLOTH: {
		printf("이 아이템은 사용할 수 없습니다.");
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

void InterPhone()
{
	int msg_int;
	int back = 0;
	char msg_char[MAX_MSG_LEN] = "";

	msg_int = 10;
	send(sock, &msg_int, sizeof(msg_int), 0);
	send(sock, &g_room_num, sizeof(g_room_num), 0);
	recv(sock, &msg_int, sizeof(msg_int), 0);
	send(sock, &g_player_num, sizeof(g_player_num), 0);

	system("cls");

	_beginthread(Recv, 0, NULL);

	while (true) {
		printf("전송 할 메시지 : ");
		scanf_s("%s", msg_char, MAX_MSG_LEN);
		send(sock, msg_char, MAX_MSG_LEN, 0);
		if (strcmp(msg_char, "back") == 0) {
			break;
		}
	}
}

void Recv()
{
	char msg_char[MAX_MSG_LEN] = "";

	while (true) {
		recv(communication.sock, &msg_char, MAX_MSG_LEN, 0);

		printf("\n받은 메시지 : %s \n전송 할 메시지 : ", msg_char);
		if (strcmp(msg_char, "back") == 0) {
			break;
		}
	}

	exit(0);
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
		while (true) {
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
			printf("다음 스테이지");

			MoveCursor(x, y + 6);
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
					if (y < 10) {
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

					case NEXTSTAGE_001: {
						int msg_int = 3;
						send(sock, &msg_int, sizeof(msg_int), 0);
						send(sock, &g_player_num, sizeof(g_player_num), 0);

						return 0;
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
		while (true) {
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

			MoveCursor(x, y + 8);
			printf("이전 스테이지");

			MoveCursor(x, y + 10);
			printf("메뉴");

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
					if (y < 12) {
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

					switch (y) {
					case EXPLORE_ROOM_1_002: {
						msg_int = 5;
						send(sock, &msg_int, sizeof(msg_int), 0);
						msg_int = 0;
						send(sock, &msg_int, sizeof(msg_int), 0);
						send(sock, &msg_int, sizeof(msg_int), 0);
						send(sock, &g_room_num, sizeof(g_room_num), 0);
						recv(sock, &msg_int, sizeof(msg_int), 0);
						if (msg_int >= 1) {
							msg_int = 7;
							send(sock, &msg_int, sizeof(msg_int), 0);
							send(sock, &g_player_num, sizeof(g_player_num), 0);
							msg_int = 60;
							send(sock, &msg_int, sizeof(msg_int), 0);
							recv(sock, &msg_int, sizeof(msg_int), 0);
							if (msg_int != 1) {
								printf("방 열쇠를 얻었다. \n");

								msg_int = 0;
								send(sock, &msg_int, sizeof(msg_int), 0);
								send(sock, &g_player_num, sizeof(g_player_num), 0);
								msg_int = 1;
								send(sock, &msg_int, sizeof(msg_int), 0);
								recv(sock, &msg_int, sizeof(msg_int), 0);
								printf("방 열쇠 획득 \n");
								system("pause");
								system("cls");
								if (msg_int != 1) {
									msg_int = 1;
									send(sock, &msg_int, sizeof(msg_int), 0);
									msg_int = 60;
									send(sock, &msg_int, sizeof(msg_int), 0);
								}
							}
						}
						printf("화장실이다. 물은 나오지 않는 것 같다. \n");
						system("pause");
						break;
					}

					case EXPLORE_ROOM_2_002: {
						printf("문이 잠겨있습니다. \n");
						system("pause");
						break;
					}

					case EXPLORE_ROOM_3_002: {
						msg_int = 7;
						send(sock, &msg_int, sizeof(msg_int), 0);
						send(sock, &g_player_num, sizeof(g_player_num), 0);
						msg_int = 60;
						send(sock, &msg_int, sizeof(msg_int), 0);
						recv(sock, &msg_int, sizeof(msg_int), 0);
						if (msg_int == 1) {
							printf("현재 가진 열쇠로 문을 열 수 있을 것 같다. \n \n");
							printf("문을 열고 들어가시겠습니까? (1/0) \n");
							scanf_s("%d", &msg_int);
							if (msg_int == 1) {
								int msg_int = 3;
								send(sock, &msg_int, sizeof(msg_int), 0);
								send(sock, &g_player_num, sizeof(g_player_num), 0);

								return 0;
							}
						}

						else {
							printf("문이 잠겨있습니다. \n \n");
							system("pause");
						}

						break;
					}

					case EXPLORE_ROOM_4_002: {
						printf("문이 잠겨있습니다. \n");
						system("pause");
						break;
					}

					case BACKSTAGE_002: {
						int msg_int = 6;
						send(sock, &msg_int, sizeof(msg_int), 0);
						send(sock, &g_player_num, sizeof(g_player_num), 0);

						return 0;
					}

					case MENU_002: {
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

	case STAGE3: {
		while (true) {
			key = 0;
			x = 2;
			y = 2;

			system("cls");

			printf("3번째 방에 들어왔다. \n");

			MoveCursor(x - 2, y);
			printf("> 방 조사");

			MoveCursor(x, y + 2);
			printf("다음 챕터");

			MoveCursor(x, y + 4);
			printf("이전 스테이지");

			MoveCursor(x, y + 6);
			printf("메뉴");

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

					switch (y) {
					case EXPLORE_003: {
						printf("방에는 서랍장과 전화기가 보인다. \n \n");
						printf("전화기에 불이 들어와 있는 것 같다. \n");
						printf("전화기를 사용하시겠습니까? (1/0) \n");
						scanf_s("%d", &msg_int);
						if (msg_int == 1) {
							InterPhone();
						}
						break;
					}

					case NEXTCHAPTER_003: {

						break;
					}

					case BACKSTAGE_003: {

						break;
					}

					case MENU_003: {

						break;
					}
					}

				}

				}

			}

		}

		break;
	}
	}
}

int Player0_Chapter1(int stage)
{
	return 0;
}

int Player1_Chapter0(int stage)
{
	int x, y;
	int key;
	int msg_int;
	int exit = 0;

	switch (stage) {
	case STAGE1: {
		while (true) {
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
			printf("다음 스테이지");

			MoveCursor(x, y + 6);
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
					if (y < 10) {
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

					case NEXTSTAGE_101: {
						int msg_int = 3;
						send(sock, &msg_int, sizeof(msg_int), 0);
						send(sock, &g_player_num, sizeof(g_player_num), 0);

						return 0;
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
		int choice;
		while (true) {
			key = 0;
			x = 2;
			y = 2;

			system("cls");

			printf("이곳에는 가운데에 있는 촛불로 빛이 밝혀지고 있고 책장과 주방과 방 3개가 보인다. \n");

			MoveCursor(x - 2, y);
			printf("> 방 1 조사");

			MoveCursor(x, y + 2);
			printf("방 2 조사");

			MoveCursor(x, y + 4);
			printf("방 3 조사");

			MoveCursor(x, y + 6);
			printf("책장 조사");

			MoveCursor(x, y + 8);
			printf("주방 조사");

			MoveCursor(x, y + 10);
			printf("이전 스테이지");

			MoveCursor(x, y + 12);
			printf("메뉴");

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
					if (y < 14) {
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

					switch (y) {
					case EXPLORE_ROOM_1_102: {
						printf("화장실이다. \n \n");
						msg_int = 7;
						send(sock, &msg_int, sizeof(msg_int), 0);
						send(sock, &g_player_num, sizeof(g_player_num), 0);
						msg_int = 100060;
						send(sock, &msg_int, sizeof(msg_int), 0);
						recv(sock, &msg_int, sizeof(msg_int), 0);
						if (msg_int == 1) {
							printf("마른 행주에 물을 묻혔다. \n");
							system("pause");
							msg_int = 8;
							send(sock, &msg_int, sizeof(msg_int), 0);
							send(sock, &g_player_num, sizeof(g_player_num), 0);
							msg_int = 100060;
							send(sock, &msg_int, sizeof(msg_int), 0);
						}

						system("cls");
						printf("화장실이다. \n \n");

						printf("세면대의 물을 내릴 수 있을 것 같다. \n \n");

						printf("세면대의 물을 내리시겠습니까? (1/0) \n");
						scanf_s("%d", &choice);
						if (choice == 1) {
							msg_int = 5;
							send(sock, &msg_int, sizeof(msg_int), 0);
							msg_int = 0;
							send(sock, &msg_int, sizeof(msg_int), 0);
							send(sock, &choice, sizeof(choice), 0);
							send(sock, &g_room_num, sizeof(g_room_num), 0);

							system("cls");
							printf("물을 내렸다. \n");
							system("pause");
						}

						break;
					}

					case EXPLORE_ROOM_2_102: {
						printf("문이 잠겨있습니다. \n");
						system("pause");
						break;
					}

					case EXPLORE_ROOM_3_102: {
						printf("문이 열려있다. \n \n");

						printf("들어가시겠습니까? (1/0) \n");
						scanf_s("%d", &choice);
						if (choice == 1) {
							int msg_int = 3;
							send(sock, &msg_int, sizeof(msg_int), 0);
							send(sock, &g_player_num, sizeof(g_player_num), 0);

							return 0;
						}
						break;
					}

					case EXPLORE_BOOKSHELF_102: {
						printf("책장이다. \n \n");
						printf("책을 읽을 수 있을 것 같다. \n");
						printf("책을 읽으시겠습니까? (1/0) \n");
						scanf_s("%d", &choice);
						if (choice == 1) {
							msg_int = 5;
							send(sock, &msg_int, sizeof(msg_int), 0);
							msg_int = 1;
							send(sock, &msg_int, sizeof(msg_int), 0);
							msg_int = 0;
							send(sock, &msg_int, sizeof(msg_int), 0);
							send(sock, &g_room_num, sizeof(g_room_num), 0);
							recv(sock, &msg_int, sizeof(msg_int), 0);

							system("cls");

							switch (msg_int) {
							case BOOK0: {
								printf("(책 이름) \n \n");
								printf("(책 내용) \n");
								system("pause");
								break;
							}

							case BOOK1: {
								system("pause");
								break;
							}

							case BOOK2: {
								system("pause");
								break;
							}

							case BOOK3: {
								system("pause");
								break;
							}

							case BOOK4: {
								system("pause");
								break;
							}

							case BOOK5: {
								system("pause");
								break;
							}

							case BOOK6: {
								system("pause");
								break;
							}

							case BOOK7: {
								system("pause");
								break;
							}

							case BOOK8: {
								system("pause");
								break;
							}

							case BOOK9: {
								system("pause");
								break;
							}

							case BOOK10: {
								system("pause");
								break;
							}

							case BOOK11: {
								system("pause");
								break;
							}

							case BOOK12: {
								system("pause");
								break;
							}

							case BOOK13: {
								system("pause");
								break;
							}

							case BOOK14: {
								system("pause");
								break;
							}

							case BOOK15: {
								system("pause");
								break;
							}

							case BOOK16: {
								system("pause");
								break;
							}

							case BOOK17: {
								system("pause");
								break;
							}

							case BOOK18: {
								system("pause");
								break;
							}

							case BOOK19: {
								system("pause");
								break;
							}

							case BOOK20: {
								system("pause");
								break;
							}

							case BOOK21: {
								system("pause");
								break;
							}

							case BOOK22: {
								system("pause");
								break;
							}

							case BOOK23: {
								system("pause");
								break;
							}

							case BOOK24: {
								system("pause");
								break;
							}

							case BOOK25: {
								system("pause");
								break;
							}

							case BOOK26: {
								system("pause");
								break;
							}

							case BOOK27: {
								system("pause");
								break;
							}

							case BOOK28: {
								system("pause");
								break;
							}

							case BOOK29: {
								system("pause");
								break;
							}

							case BOOK30: {
								system("pause");
								break;
							}

							case BOOK31: {
								system("pause");
								break;
							}

							case BOOK32: {
								system("pause");
								break;
							}

							case BOOK33: {
								system("pause");
								break;
							}

							case BOOK34: {
								system("pause");
								break;
							}

							case BOOK35: {
								system("pause");
								break;
							}

							case BOOK36: {
								system("pause");
								break;
							}

							case BOOK37: {
								system("pause");
								break;
							}

							case BOOK38: {
								system("pause");
								break;
							}

							case BOOK39: {
								system("pause");
								break;
							}

							default: {
								printf("모든 책을 읽은 것 같다. \n");
								system("puase");
								break;
							}

							}

							if (msg_int >= 20) {
								system("cls");
								printf("철문이 보인다. \n");
								printf("하지만 열 수 있는 방법은 보이지 않는다. \n");
								system("pause");
							}

							msg_int = 5;
							send(sock, &msg_int, sizeof(msg_int), 0);
							msg_int = 1;
							send(sock, &msg_int, sizeof(msg_int), 0);
							send(sock, &msg_int, sizeof(msg_int), 0);
							send(sock, &g_room_num, sizeof(g_room_num), 0);


						}
						break;
					}

					case EXPLORE_KITCHEN_102: {
						printf("주방에는 칼과 행주가 있고 불은 나오지 않는 것 같다. \n \n");

						msg_int = 0;
						send(sock, &msg_int, sizeof(msg_int), 0);
						send(sock, &g_player_num, sizeof(g_player_num), 0);
						msg_int = 1;
						send(sock, &msg_int, sizeof(msg_int), 0);
						recv(sock, &msg_int, sizeof(msg_int), 0);
						printf("칼, 마른행주 획득 \n");
						system("pause");
						if (msg_int != 1) {
							msg_int = 2;
							send(sock, &msg_int, sizeof(msg_int), 0);
							msg_int = 100050;
							send(sock, &msg_int, sizeof(msg_int), 0);
							msg_int = 100060;
							send(sock, &msg_int, sizeof(msg_int), 0);
						}
						break;
					}

					case BACKSTAGE_102: {
						int msg_int = 6;
						send(sock, &msg_int, sizeof(msg_int), 0);
						send(sock, &g_player_num, sizeof(g_player_num), 0);

						return 0;
					}

					case MENU_102: {
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

	case STAGE3: {
		while (true) {
			key = 0;
			x = 2;
			y = 2;

			system("cls");

			printf("3번째 방에 들어왔다. \n");

			MoveCursor(x - 2, y);
			printf("> 방 조사");

			MoveCursor(x, y + 2);
			printf("다음 챕터");

			MoveCursor(x, y + 4);
			printf("이전 스테이지");

			MoveCursor(x, y + 6);
			printf("메뉴");

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

					switch (y) {
					case EXPLORE_003: {
						printf("방에는 전화기가 보인다. \n \n");
						printf("전화기에 불이 들어와 있는 것 같다. \n");
						printf("전화기를 사용하시겠습니까? (1/0) \n");
						scanf_s("%d", &msg_int);
						if (msg_int == 1) {
							InterPhone();
						}
						break;
					}

					case NEXTCHAPTER_003: {

						break;
					}

					case BACKSTAGE_003: {

						break;
					}

					case MENU_003: {

						break;
					}
					}

				}

				}

			}

		}
		break;
	}
	}
}

int Player1_Chapter1(int stage)
{
	return 0;
}