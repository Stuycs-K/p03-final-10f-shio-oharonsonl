#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>

#ifndef NETWORKING_H
#define NETWORKING_H

int server_setup();
int client_tcp_handshake(char* server_address);
int server_tcp_handshake(int listen_socket);
void err(int i, char * msg);

#endif

#define BUFFER_SIZE 128
