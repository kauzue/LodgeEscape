#include "game.h"
#include "winsock.h"

int main(void)
{
	bool err_init;
	err_init = InitSystem();
	if (err_init == false) {
		goto ERR_MAIN;
	}
	StartWinsock();

ERR_MAIN:
	return 0;
}