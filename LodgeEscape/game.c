#include "function.h"

void loginmenu(SOCKET dosock, char msg)
{
    while (true) {
        int choice;

        send(dosock, "�α��� �޴� \n \n", sizeof(msg), 0);
        send(dosock, "1.ȸ������ \n", sizeof(msg), 0);
        send(dosock, "2.�α��� \n", sizeof(msg), 0);
        send(dosock, "����: ", sizeof(msg), 0);
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
            send(dosock, "�ٽ� �Է����ּ���.", sizeof(msg), 0);
            system("cls");
        }
    }
}