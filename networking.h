#ifndef NETWORKING_H
#define NETWORKING_H

#include <sys/types.h>

int server_setup();
int client_tcp_handshake(char* server_address);
int server_tcp_handshake(int listen_socket);

#endif
