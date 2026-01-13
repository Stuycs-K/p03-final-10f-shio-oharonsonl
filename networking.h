#include "sema.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

#define PLAYER_NUM 8

#ifndef NETWORKING_H
#define NETWORKING_H

int server_setup();
int client_tcp_handshake(char* server_address);
int server_tcp_handshake(int listen_socket);

#endif
