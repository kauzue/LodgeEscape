#include "function.h"

void loginmenu(SOCKET dosock, char msg)
{
    while (true) {
        int choice;

        send(dosock, "로그인 메뉴 \n \n", sizeof(msg), 0);
        send(dosock, "1.회원가입 \n", sizeof(msg), 0);
        send(dosock, "2.로그인 \n", sizeof(msg), 0);
        send(dosock, "선택: ", sizeof(msg), 0);
        recv(dosock, msg, sizeof(msg), 0);
        choice = msg - 48;

        system("cls");

        switch (choice) {
        case 1:
            SignUp(dosock);
            break;

        case 2:
            SignIn(dosock);
            break;

        default:
            send(dosock, "다시 입력해주세요.", sizeof(msg), 0);
            system("cls");
        }
    }
}