#include "system.h"
#include "winsock.h"

int main(void)
{
	InitSystem();

	StartWinsock();

	return 0;
}