#pragma once

#include <WinSock2.h>

void Game_Login(SOCKET);

enum Login { SIGNUP_LOGIN, LOGIN_LOGIN, EXIT_LOGIN};