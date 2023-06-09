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
	char ID[MAX_MSG_LEN];
	char* msg[MAX_MSG_LEN];
	char password[MAX_MSG_LEN];

	do {
		send(dosock, "로그인 \n", 9, 0);
		Sleep(10);
		send(dosock, "아이디: ", 9, 0);
		recv(dosock, msg, MAX_MSG_LEN, 0);

    strcpy(ID, msg);
    printf("%s", ID);

		send(dosock, "비밀번호: ", 10, 0);
		recv(dosock, msg, MAX_MSG_LEN, 0);
		send(dosock, "cls", 4, 0);

    strcpy(password, msg);

		for (r_num = 0; r_num < s_num_players; ++r_num) {
			if (strcmp(ID, s_players[r_num].ID) == 0 && strcmp(password, s_players[r_num].password) == 0) {
				b_login = 1;
				break;
			}
		}

		if (!b_login) {
			send(dosock, "아이디 혹은 비밀번호가 일치하지 않습니다. \n", 44, 0);
			Sleep(10);
			send(dosock, "다시 입력해주세요.", 19, 0);
			Sleep(1250);
			send(dosock, "cls", 4, 0);
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
	char* msg[MAX_MSG_LEN];

	player_t player;

	do {
		send(dosock, "회원가입 \n", 11, 0);
		Sleep(10);
		send(dosock, "아이디: ", 9, 0);
		recv(dosock, msg, MAX_MSG_LEN, 0);

		same = 0;
		for (int i = 0; i < s_num_players; ++i) {
			if (strcmp(msg, s_players[i].ID) == 0) {
				send(dosock, "cls", 4, 0);
				Sleep(10);
				send(dosock, "중복되는 아이디입니다. \n", 23, 0);
				Sleep(10);
				send(dosock, "다시 입력해주세요.", 19, 0);
				Sleep(1250);
				send(dosock, "cls", 4, 0);
				same = 1;
				break;
			}
		}
	} while (same);

  strcpy(player.ID, msg);

	send(dosock, "비밀번호: ", 11, 0);
	recv(dosock, msg, MAX_MSG_LEN, 0);

  strcpy(player.password, msg);

	do {
		send(dosock, "플레이어 번호: ", 16, 0);
		recv(dosock, msg, MAX_MSG_LEN, 0);
		player.p_num = atoi(msg);

		same = 0;
		if (player.p_num != 1 && player.p_num != 2) {
			send(dosock, "cls", 4, 0);
			Sleep(10);
			send(dosock, "1 혹은 2가 아닌 다른 값을 입력하셨습니다.", 42, 0);
			Sleep(10);
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