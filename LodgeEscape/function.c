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

void SignIn()
{
	char ID[100];
	char Password[100];
	int b_login = 0;

	do {
		printf("로그인 \n \n");
		printf("아이디: ");
		scanf("%s", ID);

		printf("비밀번호: ");
		scanf("%s", Password);
		system("cls");
			
		for (r_num = 0; r_num < s_num_players; ++r_num) {
			if (strcmp(ID, s_players[r_num].ID) == 0 && strcmp(Password, s_players[r_num].password) == 0) {
				b_login = 1;
				break;
			}
		}

		if (!b_login) {
			printf("아이디 또는 비밀번호가 틀렸습니다. \n");
			printf("다시 입력해주세요.");
			Sleep(1250);
			system("cls");
		}
	} while (!b_login);
}

void SignUp()
{
	FILE* pb = fopen("player.bin", "ab");

	if (pb == NULL) {
		puts("파일오픈 실패!");
		return;
	}

	int choice = 0;
	int same;

	player_t member;

	do {
		printf("회원가입 \n \n");
		printf("아이디: ");
		scanf("%s", member.ID);

		same = 0;
		for (int i = 0; i < s_num_players; ++i) {
			if (strcmp(member.ID, s_players[i].ID) == 0) {
				system("cls");
				printf("중복되는 아이디입니다. \n");
				printf("다시 입력해주세요.");
				Sleep(1250);
				system("cls");
				same = 1;
				break;
			}
		}
	} while (same);

	printf("비밀번호: ");
	scanf("%s", member.password);
	system("cls");

	memcpy(&s_players[s_num_players], &member, sizeof(player_t));
	++s_num_players;

	fwrite(&member, sizeof(player_t), 1, pb);

	fclose(pb);
	system("cls");
}