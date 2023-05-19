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

void SignIn()
{
	char ID[100];
	char Password[100];
	int b_login = 0;

	do {
		printf("�α��� \n \n");
		printf("���̵�: ");
		scanf("%s", ID);

		printf("��й�ȣ: ");
		scanf("%s", Password);
		system("cls");
			
		for (r_num = 0; r_num < s_num_players; ++r_num) {
			if (strcmp(ID, s_players[r_num].ID) == 0 && strcmp(Password, s_players[r_num].password) == 0) {
				b_login = 1;
				break;
			}
		}

		if (!b_login) {
			printf("���̵� �Ǵ� ��й�ȣ�� Ʋ�Ƚ��ϴ�. \n");
			printf("�ٽ� �Է����ּ���.");
			Sleep(1250);
			system("cls");
		}
	} while (!b_login);
}

void SignUp()
{
	FILE* pb = fopen("player.bin", "ab");

	if (pb == NULL) {
		puts("���Ͽ��� ����!");
		return;
	}

	int choice = 0;
	int same;

	player_t member;

	do {
		printf("ȸ������ \n \n");
		printf("���̵�: ");
		scanf("%s", member.ID);

		same = 0;
		for (int i = 0; i < s_num_players; ++i) {
			if (strcmp(member.ID, s_players[i].ID) == 0) {
				system("cls");
				printf("�ߺ��Ǵ� ���̵��Դϴ�. \n");
				printf("�ٽ� �Է����ּ���.");
				Sleep(1250);
				system("cls");
				same = 1;
				break;
			}
		}
	} while (same);

	printf("��й�ȣ: ");
	scanf("%s", member.password);
	system("cls");

	memcpy(&s_players[s_num_players], &member, sizeof(player_t));
	++s_num_players;

	fwrite(&member, sizeof(player_t), 1, pb);

	fclose(pb);
	system("cls");
}