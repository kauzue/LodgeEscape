#include "function.h"

static player_t s_players[NUM_MAX_PLAYERS];
static int s_num_players;
int r_num;

IN_ADDR GetDefaultMyIP()
{
    char localhostname[MAX_PATH];
    IN_ADDR addr = { 0, };
    if (gethostname(localhostname, MAX_PATH) == SOCKET_ERROR)
    {
        return addr;
    }
    HOSTENT* ptr = gethostbyname(localhostname);
    while (ptr && ptr->h_name)
    {
        if (ptr->h_addrtype == PF_INET)
        {
            memcpy(&addr, ptr->h_addr_list[0], ptr->h_length);
            break;
        }
        ptr++;
    }
    return addr;
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

int SignIn(SOCKET dosock, int b_login)
{
	char ID[100];
	char Password[100];

	do {
		send(dosock, "로그인 \n", 9, 0);
        Sleep(10);
		send(dosock, "아이디: ", 9, 0);
		recv(dosock, ID, strlen(ID), 0);

		send(dosock, "비밀번호:", 10, 0);
		recv(dosock, Password, strlen(Password), 0);
		system("cls");
			
		for (r_num = 0; r_num < s_num_players; ++r_num) {
			if (strcmp(ID, s_players[r_num].ID) == 0 && strcmp(Password, s_players[r_num].password) == 0) {
				b_login = 1;
				break;
			}
		}

		if (!b_login) {
			send(dosock, "아이디 혹은 비밀번호가 일치하지 않습니다.", 42, 0);
        Sleep(10);
			send(dosock, "다시 입력해주세요.", 19, 0);
			Sleep(1250);
			system("cls");
		}
	} while (!b_login);
	
	return r_num;
}

void SignUp(SOCKET dosock)
{
	FILE* pb = fopen("player.bin", "ab");

	if (pb == NULL) {
		puts("파일오픈 실패!");
		return;
	}

	int choice = 0;
	int same;

	player_t player;

	do {
		send(dosock, "회원가입 \n", 11, 0);
		send(dosock, "아이디: ", 9, 0);
		recv(dosock, player.ID, strlen(player.ID), 0);
		system("cls");

		same = 0;
		for (int i = 0; i < s_num_players; ++i) {
			if (strcmp(player.ID, s_players[i].ID) == 0) {
				send(dosock, "중복되는 아이디입니다.", 23, 0);
				send(dosock, "다시 입력해주세요.", 19, 0);
				Sleep(1250);
				system("cls");
				same = 1;
				break;
			}
		}
	} while (same);

	send(dosock, "비밀번호: ", 11, 0);
	recv(dosock, player.password, strlen(player.password), 0);
	system("cls");
	do {
		send(dosock, "플레이어 번호: ", 16, 0);
		recv(dosock, player.p_num, sizeof(player.p_num), 0);
		system("cls");

		same = 0;
		if (player.p_num != 1 || player.p_num != 2) {
			send(dosock, "1 혹은 2가 아닌 다른 값을 입력하셨습니다.", 42, 0);
			send(dosock, "다시 입력해주세요.", 19, 0);
			getchar();
			system("cls");
			same = 1;
		}
	} while (same);

	memcpy(&s_players[s_num_players], &player, sizeof(player_t));
	++s_num_players;

	fwrite(&player, sizeof(player_t), 1, pb);

	fclose(pb);
	system("cls");
}