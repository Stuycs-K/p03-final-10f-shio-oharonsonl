#include "networking.h"
#include <stdio.h>
#include <stdlib.h>

void client_logic(int server_socket) {
  // ...
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
