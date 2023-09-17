#include <WinSock2.h>

#include "game.h"
#include "story.h"

item_t s_items[NUM_MAX_PLAYERS][NUM_MAX_PLAYER_PER_SAVES][NUM_MAX_SAVE_PER_ITEMS];
clue_t s_clues[NUM_MAX_PLAYERS][NUM_MAX_PLAYER_PER_SAVES][NUM_MAX_SAVE_PER_CLUES];

void Story();

SOCKET sock;

void InitStory(SOCKET socket)
{
	int player_num;
	int save_num;

	sock = socket;

	recv(sock, &player_num, sizeof(player_num), 0);
	send(sock, s_players[player_num].player_num, sizeof(s_players[player_num].player_num), 0);
	recv(sock, &save_num, sizeof(save_num), 0);
	send(sock, &s_saves[player_num][save_num].chapter, sizeof(s_saves[player_num][save_num].chapter), 0);
	send(sock, &s_saves[player_num][save_num].stage, sizeof(s_saves[player_num][save_num].stage), 0);

	Story();
}

void Story()
{

}