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

void SignIn(SOCKET dosock)
{
	char ID[100];
	char Password[100];
	int b_login = 0;

	do {
		send(dosock, "로그인 \n \n", sizeof(MAX_MSG_LEN), 0);
		send(dosock, "아이디: ", sizeof(MAX_MSG_LEN), 0);
		recv(dosock, ID, sizeof(ID), 0);

		send(dosock, "비밀번호: \n", sizeof(MAX_MSG_LEN), 0);
		recv(dosock, Password, sizeof(Password), 0);
		system("cls");
			
		for (r_num = 0; r_num < s_num_players; ++r_num) {
			if (strcmp(ID, s_players[r_num].ID) == 0 && strcmp(Password, s_players[r_num].password) == 0) {
				b_login = 1;
				break;
			}
		}

		if (!b_login) {
			send(dosock, "아이디 혹은 비밀번호가 일치하지 않습니다. \n", sizeof(MAX_MSG_LEN), 0);
			send(dosock, "다시 입력해주세요. \n", sizeof(MAX_MSG_LEN), 0);
			Sleep(1250);
			system("cls");
		}
	} while (!b_login);
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
		send(dosock, "회원가입 \n \n", sizeof(MAX_MSG_LEN), 0);
		send(dosock, "아이디: \n", sizeof(MAX_MSG_LEN), 0);
		recv(dosock, player.ID, sizeof(player.ID), 0);
		system("cls");

		same = 0;
		for (int i = 0; i < s_num_players; ++i) {
			if (strcmp(player.ID, s_players[i].ID) == 0) {
				send(dosock, "중복되는 아이디입니다. \n", sizeof(MAX_MSG_LEN), 0);
				send(dosock, "다시 입력해주세요. \n", sizeof(MAX_MSG_LEN), 0);
				Sleep(1250);
				system("cls");
				same = 1;
				break;
			}
		}
	} while (same);

	send(dosock, "비밀번호: \n", sizeof(MAX_MSG_LEN), 0);
	recv(dosock, player.password, sizeof(player.password), 0);
	system("cls");

	memcpy(&s_players[s_num_players], &player, sizeof(player_t));
	++s_num_players;

	fwrite(&player, sizeof(player_t), 1, pb);

	fclose(pb);
	system("cls");
}