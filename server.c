#include "networking.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void subserver_logic(int client_socket) {
  // ...

  exit(0); // Must exit the fork
}

int main() {
  int server_socket = server_setup();

  while (1) {
    int client_socket = server_tcp_handshake(server_socket);
    printf("A CLIENT HAS BEEN CONNECTED\n");

    int subserver = fork();

    if (subserver == -1) {
      perror("fork");
      exit(1);
    }

    else if (subserver == 0)
      subserver_logic(client_socket);
  }
}
