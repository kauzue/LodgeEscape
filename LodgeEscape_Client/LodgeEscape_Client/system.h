#pragma once

#include <stdbool.h>

#define MAX_MSG_LEN 256

enum KEY { UP, DOWN, LEFT, RIGHT, ENTER };

bool InitSystem();
int ControlKey();
void MoveCursor(int, int);