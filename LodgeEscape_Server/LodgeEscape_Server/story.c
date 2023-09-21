#include "game.h"

void Story();

SOCKET sock;
CRITICAL_SECTION criticalsection;

void Init()
{
	InitializeCriticalSectionAndSpinCount(&criticalsection, 1000);
}

void DeleteInit()
{
	DeleteCriticalSection(&criticalsection);
}

void InitStory(SOCKET socket)
{
	EnterCriticalSection(&criticalsection);
	sock = socket;
	int player_num;
	int save_num;
	int msg_int = 0;

	send(sock, &msg_int, sizeof(msg_int), 0);
	recv(sock, &player_num, sizeof(player_num), 0);
	send(sock, &s_players[player_num].player_num, sizeof(s_players[player_num].player_num), 0);
	recv(sock, &save_num, sizeof(save_num), 0);
	send(sock, &s_saves[player_num][save_num].chapter, sizeof(s_saves[player_num][save_num].chapter), 0);
	send(sock, &s_saves[player_num][save_num].stage, sizeof(s_saves[player_num][save_num].stage), 0);

	LeaveCriticalSection(&criticalsection);

	Story();
}

void Story()
{

}