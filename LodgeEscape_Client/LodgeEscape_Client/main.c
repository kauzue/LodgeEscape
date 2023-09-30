#include "system.h"
#include "winsock.h"

int main(void)
{
	bool a = InitGame();
	if (a == false) {
		return 0;
	}

	InitSystem();

	StartWinsock();

	return 0;
}