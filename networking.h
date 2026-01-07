#ifndef NETWORKING_H
#define NETWORKING_H

int server_setup();
int client_tcp_handshake(char* server_address);
int server_tcp_handshake(int listen_socket);

#endif

#define SHMKEY 6769420
#define SEMKEY 6769421
