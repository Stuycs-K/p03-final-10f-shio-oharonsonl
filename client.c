#include "networking.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

void client_logic(int server_socket) {
  char id;
  recv(server_socket, &id, sizeof(char), 0);
  printf("Recieved: %c\n", id);

  char tmp;
  recv(server_socket, &tmp, sizeof(char), 0);
  printf("GAME STARTS NOW! You are player %c\n", id);


  // game logic
}

int main(int argc, char *argv[]) {
  char *IP = "127.0.0.1";
  if (argc > 1) {
    IP = argv[1];
  }

  int server_socket = client_tcp_handshake(IP);
  printf("CONNECTED TO SERVER\n");

  client_logic(server_socket);
}
