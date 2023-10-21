#pragma warning(disable:4996)

#include "game.h"
#include "winsock.h"
#include <stdio.h>

int main(void)
{

	/*
	char save_filename[16];

	FILE* pb = fopen("player.bin", "wb");
	for (int i = 0; i < NUM_MAX_PLAYER_PER_SAVES; i++) {
		sprintf(save_filename, "save%02d.bin", i + 1);

		FILE* sb = fopen(save_filename, "wb");

		fclose(sb);
	}

	fclose(pb);

	return 0;
	*/

	bool err_init;
	err_init = InitSystem();
	if (err_init == false) {
		goto ERR_MAIN;
	}
	StartWinsock();

ERR_MAIN:
	return 0;
}