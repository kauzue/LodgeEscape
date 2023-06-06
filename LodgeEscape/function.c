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
		puts("���Ͽ��� ����!");
		return;
	}

	s_num_players = fread(s_players, sizeof(player_t), NUM_MAX_PLAYERS, pb);
}

int SignIn(SOCKET dosock, int b_login)
{
	char ID[100];
	char Password[100];

	do {
		send(dosock, "�α��� \n", 9, 0);
		Sleep(1);
		send(dosock, "���̵�: ", 9, 0);
		recv(dosock, ID, strlen(ID), 0);

		send(dosock, "��й�ȣ:", 10, 0);
		recv(dosock, Password, strlen(Password), 0);
		send(dosock, "cls", 4, 0);

		for (r_num = 0; r_num < s_num_players; ++r_num) {
			if (strcmp(ID, s_players[r_num].ID) == 0 && strcmp(Password, s_players[r_num].password) == 0) {
				b_login = 1;
				break;
			}
		}

		if (!b_login) {
			send(dosock, "���̵� Ȥ�� ��й�ȣ�� ��ġ���� �ʽ��ϴ�. \n", 42, 0);
			Sleep(1);
			send(dosock, "�ٽ� �Է����ּ���.", 19, 0);
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
		puts("���Ͽ��� ����!");
		return;
	}

	int choice = 0;
	int same;

	player_t player;

	do {
		send(dosock, "ȸ������ \n", 11, 0);
		Sleep(1);
		send(dosock, "���̵�: ", 9, 0);
		recv(dosock, player.ID, strlen(player.ID), 0);
		send(dosock, "cls", 4, 0);

		same = 0;
		for (int i = 0; i < s_num_players; ++i) {
			if (strcmp(player.ID, s_players[i].ID) == 0) {
				send(dosock, "�ߺ��Ǵ� ���̵��Դϴ�. \n", 23, 0);
				Sleep(1);
				send(dosock, "�ٽ� �Է����ּ���.", 19, 0);
				Sleep(1250);
				send(dosock, "cls", 4, 0);
				same = 1;
				break;
			}
		}
	} while (same);

	send(dosock, "��й�ȣ: ", 11, 0);
	recv(dosock, player.password, strlen(player.password), 0);
	send(dosock, "cls", 4, 0);

	do {
		send(dosock, "�÷��̾� ��ȣ: ", 16, 0);
		recv(dosock, player.p_num, sizeof(player.p_num), 0);
		send(dosock, "cls", 4, 0);

		same = 0;
		if (player.p_num != 1 && player.p_num != 2) {
			send(dosock, "1 Ȥ�� 2�� �ƴ� �ٸ� ���� �Է��ϼ̽��ϴ�.", 42, 0);
			Sleep(1);
			send(dosock, "�ٽ� �Է����ּ���.", 19, 0);
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