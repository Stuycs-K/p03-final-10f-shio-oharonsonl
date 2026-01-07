#include <unistd.h>

#ifndef NETWORKING_H
#define NETWORKING_H

int server_setup();
int client_tcp_handshake(char* server_address);
int server_tcp_handshake(int listen_socket);

#endif

#define BUFFER_SIZE 128
