#include "function.h"

int loginmenu(SOCKET dosock, char* msg)
{
    int choice = 1;
    int b_login = 0;


    while (true) {
        send(dosock, "�α��� �޴� \n \n", 16, 0);
        send(dosock, "1.ȸ������ \n", 13, 0);
        send(dosock, "2.�α��� \n", 11, 0);
        send(dosock, "����: ", 7, 0);
        while (recv(dosock, &msg, strlen(msg), 0) != 0);

        system("cls");

        switch (choice) {
        case 1:
            SignUp(dosock);
            break;
        case 2:
            b_login = SignIn(dosock, b_login);
            choice = 0;
            return -1;

        default:
            send(dosock, "�ٽ� �Է����ּ���.", 19, 0);
            system("cls");
        }
    }
    return b_login;
}

void player1(SOCKET dosock, char* msg)
{

}