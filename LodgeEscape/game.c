#include "function.h"

player_t s_players[NUM_MAX_PLAYERS];

char msg[MAX_MSG_LEN] = "";
int s_num_players;
int r_num;

int loginmenu(SOCKET dosock)
{
    int choice = 3;

    while (choice) {
        send(dosock, "init", 5, 0);
        Sleep(50);

		strcpy(msg, "로그인 메뉴 \n");
        send(dosock, msg, MAX_MSG_LEN, 0);
        Sleep(50);

		strcpy(msg, "1.회원가입 \n");
        send(dosock, msg, MAX_MSG_LEN, 0);
        Sleep(50);

		strcpy(msg, "2.로그인 \n");
        send(dosock, msg, MAX_MSG_LEN, 0);
        Sleep(50);

		strcpy(msg, "선택: ");
        send(dosock, msg, MAX_MSG_LEN, 0);
		recv(dosock, msg, MAX_MSG_LEN, 0);

        send(dosock, "cls", 4, 0);

		choice = atoi(msg);

        switch (choice) {
        case 1:
            SignUp(dosock);
            break;
        case 2:
            SignIn(dosock);
            choice = 0;
			break;

        default:
			strcpy(msg, "다시 입력해주세요.");
            send(dosock, msg, MAX_MSG_LEN, 0);
            Sleep(1250);

            send(dosock, "cls", 4, 0);

			choice = 3;
        }
    }
	OpenMainMenu(dosock);
}

void OpenMainMenu(SOCKET dosock)
{
	strcpy(msg, "menu");
	send(dosock, msg, MAX_MSG_LEN, 0);
	recv(dosock, msg, MAX_MSG_LEN, 0);

	if (strcmp(msg, "start game") == 0) {
		if (r_num == 1) {
			player1(dosock);
		}
	}

	else if (strcmp(msg, "continue") == 0) {
		send(dosock, "success", 8, 0);
	}

	else if (strcmp(msg, "login data") == 0) {
		char ch = s_players[r_num].p_num + '0';

		strcpy(msg, "아이디 : ");
		strcat(msg, s_players[r_num].ID);
		strcat(msg, "\n");
		send(dosock, msg, MAX_MSG_LEN, 0);

		strcpy(msg, "비밀번호 : ");
		strcat(msg, s_players[r_num].password);
		strcat(msg, "\n");
		send(dosock, msg, MAX_MSG_LEN, 0);

		if (s_players[r_num].p_num == 1) {
			strcpy(msg, "플레이어 번호 : 1 \n");
		}

		else {
			strcpy(msg, "플레이어 번호 : 2 \n");
		}
		send(dosock, msg, MAX_MSG_LEN, 0);

		strcpy(msg, "pause");
		send(dosock, msg, MAX_MSG_LEN, 0);
		
		strcpy(msg, "menu");
		send(dosock, msg, MAX_MSG_LEN, 0);
	}

	else if (strcmp(msg, "logout") == 0) {
		loginmenu(dosock);
	}

	else if (strcmp(msg, "chapter") == 0) {
		send(dosock, "success", 8, 0);

	}

	else if (strcmp(msg, "ending") == 0) {
		send(dosock, "success", 8, 0);

	}
}

void player1(SOCKET dosock)
{
	strcpy(msg, "player1");
	send(dosock, msg, MAX_MSG_LEN, 0);
}

void Init()
{
	FILE* pb = fopen("player.bin", "rb");

	if (pb == NULL) {
		puts("파일오픈 실패!");
		return;
	}

	s_num_players = fread(s_players, sizeof(player_t), NUM_MAX_PLAYERS, pb);
}

void SignIn(SOCKET dosock)
{
	char ID[MAX_MSG_LEN];
	char password[MAX_MSG_LEN];
	int b_login = 1;

	while (b_login) {
		send(dosock, "로그인 \n", 9, 0);
		Sleep(100);

		send(dosock, "아이디 ", 11, 0);
		Sleep(50);

		strcpy(msg, "선택: ");
		send(dosock, msg, MAX_MSG_LEN, 0);
		recv(dosock, msg, MAX_MSG_LEN, 0);

		int err = WSAGetLastError();

		strcpy(ID, msg);
		printf("%s", ID);

		strcpy(msg, "비밀번호 ");
		send(dosock, msg, MAX_MSG_LEN, 0);
		Sleep(50);

		strcpy(msg, "선택: ");
		send(dosock, msg, MAX_MSG_LEN, 0);
		recv(dosock, msg, MAX_MSG_LEN, 0);
		send(dosock, "cls", 4, 0);

		strcpy(password, msg);

		for (r_num = 0; r_num < s_num_players; ++r_num) {
			if (strcmp(ID, s_players[r_num].ID) == 0 && strcmp(password, s_players[r_num].password) == 0) {
				b_login = 0;
				break;
			}
		}

		if (b_login) {
			send(dosock, "아이디 혹은 비밀번호가 일치하지 않습니다. \n", 44, 0);
			Sleep(50);
			send(dosock, "다시 입력해주세요.", 19, 0);
			Sleep(1250);
			send(dosock, "cls", 4, 0);
			b_login++;
		}
	};
}

void SignUp(SOCKET dosock)
{
	FILE* pb = fopen("player.bin", "ab");

	if (pb == NULL) {
		puts("파일오픈 실패!");
		return;
	}

	int choice = 0;
	int same = 0;
	char msg[MAX_MSG_LEN] = "";

	player_t player;

	do {
		send(dosock, "회원가입 \n", 11, 0);
		Sleep(100);
		strcpy(msg, "아이디 ");
		send(dosock, msg, MAX_MSG_LEN, 0);
		Sleep(50);
		strcpy(msg, "선택: ");
		send(dosock, msg, MAX_MSG_LEN, 0);
		recv(dosock, msg, MAX_MSG_LEN, 0);

		printf("%s", msg);

		for (int i = 0; i < s_num_players; ++i) {
			if (strcmp(msg, s_players[i].ID) == 0) {
				send(dosock, "cls", 4, 0);
				Sleep(50);
				send(dosock, "중복되는 아이디입니다. \n", 23, 0);
				Sleep(50);
				send(dosock, "다시 입력해주세요.", 19, 0);
				Sleep(1250);
				send(dosock, "cls", 4, 0);
				same++;
				break;
			}

			else {
				same = 0;
			}
		}
	} while (same);

	strcpy(player.ID, msg);

	send(dosock, "비밀번호 ", 9, 0);
	Sleep(50);

	strcpy(msg, "선택: ");
	send(dosock, msg, MAX_MSG_LEN, 0);
	recv(dosock, msg, MAX_MSG_LEN, 0);

	strcpy(player.password, msg);

	do {
		send(dosock, "플레이어 번호 ", 14, 0);
		Sleep(50);

		strcpy(msg, "선택: ");
		send(dosock, msg, MAX_MSG_LEN, 0);
		recv(dosock, msg, MAX_MSG_LEN, 0);
		player.p_num = atoi(msg);

		same = 0;
		if (player.p_num != 1 && player.p_num != 2) {
			send(dosock, "cls", 4, 0);
			Sleep(50);
			send(dosock, "1 혹은 2가 아닌 다른 값을 입력하셨습니다.", 42, 0);
			Sleep(50);
			send(dosock, "다시 입력해주세요.", 19, 0);
			Sleep(1250);
			send(dosock, "cls", 4, 0);
			same = 1;
		}
	} while (same);

	memcpy(&s_players[s_num_players], &player, sizeof(player_t));
	++s_num_players;

	fwrite(&player, sizeof(player_t), 1, pb);

	fclose(pb);
	send(dosock, "cls", 4, 0);
}