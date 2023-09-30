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
    char bool_temporary[MAX_MSG_LEN] = "";

    FILE* it_1 = fopen("item1.txt", "r");
    FILE* it_2 = fopen("item2.txt", "r");
    FILE* ct_1 = fopen("clue1.txt", "r");
    FILE* ct_2 = fopen("clue2.txt", "r");

    if (it_1 == NULL) {
        puts("아이템 파일 오픈 실패");
        system("pause");
        return false;
    }

    if (it_2 == NULL) {
        puts("아이템2 파일 오픈 실패");
        system("pause");
        goto ERR_FILE_IT_2;
    }

    if (ct_1 == NULL) {
        puts("단서1 파일 오픈 실패");
        system("pause");
        goto ERR_FILE_CT_1;
    }

    if (ct_1 == NULL) {
        puts("단서2 파일 오픈 실패");
        system("pause");
        goto ERR_FILE_CT_2;
    }

    for (int i = 0; i < MAX_ITEMS_NUM; i++) {
        strcpy(bool_temporary, "");
        fscanf_s(it_1, "%f %[^\t] %[^\t] %s", &s_items_1[i].number, s_items_1[i].name, MAX_MSG_LEN, s_items_1[i].explaination, MAX_MSG_LEN, bool_temporary, MAX_MSG_LEN);
        if (strcmp(bool_temporary, "true") == 0) {
            s_items_1[i].use = bool_temporary;
        }
        printf("%f %s %s %d \n", s_items_1[i].number, s_items_1[i].name, s_items_1[i].explaination, s_items_1[i].use);
    }

    for (int i = 0; i < MAX_ITEMS_NUM; i++) {
        strcpy(bool_temporary, "");
        fscanf_s(it_2, "%f %[^\t] %[^\t] %s", &s_items_2[i].number, s_items_2[i].name, MAX_MSG_LEN, s_items_2[i].explaination, MAX_MSG_LEN, bool_temporary, MAX_MSG_LEN);
        if (strcmp(bool_temporary, "true") == 0) {
            s_items_2[i].use = (bool)bool_temporary;
        }
    }

    for (int i = 0; i < MAX_CLUES_NUM; i++) {
        strcpy(bool_temporary, "");
        fscanf_s(ct_1, "%f %[^\t] %[^\t] %s", &s_clues_1[i].number, s_clues_1[i].name, MAX_MSG_LEN, s_clues_1[i].explaination, MAX_MSG_LEN, bool_temporary, MAX_MSG_LEN);
        if (strcmp(bool_temporary, "true") == 0) {
            s_clues_1[i].use = (bool)bool_temporary;
        }
    }


    for (int i = 0; i < MAX_CLUES_NUM; i++) {
        strcpy(bool_temporary, "");
        fscanf_s(ct_2, "%f %[^\t] %[^\t] %s", &s_clues_2[i].number, s_clues_2[i].name, MAX_MSG_LEN, s_clues_2[i].explaination, MAX_MSG_LEN, bool_temporary, MAX_MSG_LEN);
        if (strcmp(bool_temporary, "true") == 0) {
            s_clues_2[i].use = (bool)bool_temporary;
        }
    }
    
    fclose(it_1);
    fclose(ct_1);
    fclose(it_2);
    fclose(ct_2);
    return false;

ERR_FILE_CT_2:
    fclose(ct_1);

ERR_FILE_CT_1:
    fclose(it_2);

ERR_FILE_IT_2:
    fclose(it_1);
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