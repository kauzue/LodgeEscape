#include "function.h"

int loginmenu(SOCKET dosock)
{
    int choice = 1;
    int b_login = 0;
    char* msg[MAX_MSG_LEN];

    while (true) {
        send(dosock, "init", 5, 0);
        Sleep(50);
        send(dosock, "로그인 메뉴 \n", 14, 0);
        Sleep(10);
        send(dosock, "1.회원가입 \n", 13, 0);
        Sleep(10);
        send(dosock, "2.로그인 \n", 11, 0);
        Sleep(10);
        send(dosock, "선택: ", 7, 0);
        recv(dosock, msg, strlen(msg), 0);

        send(dosock, "cls", 4, 0);

        choice = atoi(msg);

        switch (choice) {
        case 1:
            SignUp(dosock);
            break;
        case 2:
            b_login = SignIn(dosock, b_login);
            choice = 0;
            return -1;

        default:
            send(dosock, "다시 입력해주세요.", 19, 0);
            Sleep(1250);
            send(dosock, "cls", 4, 0);
        }
    }
    return b_login;
}

void player1(SOCKET dosock, char* msg)
{

}