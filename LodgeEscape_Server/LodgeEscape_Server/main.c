#include "game.h"
#include "story.h"
#include "winsock.h"

int main(void)
{
	bool err_init;
	Init();
	err_init = InitSystem();
	if (err_init == false) {
		goto ERR_MAIN;
	}
	StartWinsock();

ERR_MAIN:
	DeleteInit();
	return 0;
}