#pragma warning(disable:4996)

#include <math.h>
#include <Windows.h>

#include "system.h"

bool InitSystem()
{
    system("mode con cols=80 lines=25 | title LodgeEscape");
}

bool InitGame()
{
    int int_temporary;
    char bool_temporary[MAX_MSG_LEN] = "";

    FILE* it = fopen("item.csv", "r");
    FILE* ct = fopen("clue.csv", "r");

    if (it == NULL) {
        puts("아이템 파일 오픈 실패");
        system("pause");
        return false;
    }

    if (ct == NULL) {
        puts("단서1 파일 오픈 실패");
        system("pause");
        goto ERR_FILE_CT;
    }

    for (int i = 0; i < MAX_ITEMS_NUM; i++) {
        int_temporary = 0;
        strcpy(bool_temporary, "");
        fscanf_s(it, "%d,", &int_temporary);
        if (int_temporary == 0) {
            break;
        }
        s_items[int_temporary].number = int_temporary;
        fscanf_s(it, "%[^,],%[^,],%s", s_items[int_temporary].name, MAX_MSG_LEN, s_items[int_temporary].explaination, MAX_MSG_LEN, bool_temporary, MAX_MSG_LEN);
        if (strcmp(bool_temporary, "TRUE") == 0) {
            s_items[int_temporary].use = bool_temporary;
        }
    }

    for (int i = 0; i < MAX_CLUES_NUM; i++) {
        int_temporary = 0;
        strcpy(bool_temporary, "");
        fscanf_s(ct, "%d,", &int_temporary);
        if (int_temporary == 0) {
            break;
        }
        fscanf_s(ct, "%[^,],%[^,],%s", &s_clues[int_temporary].name, MAX_MSG_LEN, s_clues[int_temporary].explaination, MAX_MSG_LEN, bool_temporary, MAX_MSG_LEN);
        if (strcmp(bool_temporary, "TRUE") == 0) {
            s_clues[int_temporary].use = (bool)bool_temporary;
        }
    }
    
    fclose(it);
    fclose(ct);
    return true;

ERR_FILE_CT:
    fclose(it);
    return false;
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