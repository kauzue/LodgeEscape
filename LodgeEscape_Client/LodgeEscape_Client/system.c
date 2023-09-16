#include <Windows.h>

#include "system.h"

bool InitSystem()
{
    system("mode con cols=80 lines=25 | title LodgeEscape");
}

int ControlKey()
{
    int key = getch();

    if (key == 224) {
        key = getch();
    }

    if (key == 'w' || key == 'W' || key == 72) {
        return UP;
    }

    if (key == 's' || key == 'S' || key == 80) {
        return DOWN;
    }

    if (key == 'a' || key == 'A' || key == 75) {
        return LEFT;
    }

    if (key == 'd' || key == 'D' || key == 77) {
        return RIGHT;
    }

    if (key == 13 || key == 32) {
        return ENTER;
    }
}

void MoveCursor(int x, int y)
{
    HANDLE consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consolehandle, pos);
}