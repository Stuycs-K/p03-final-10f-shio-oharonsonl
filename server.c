#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "networking.h"

void subserver_logic() {
  // ...
}

int main() {
  int server_socket = server_setup();

  while (1) {
    int client_socket = server_tcp_handshake(server_socket);
    printf("A CLIENT HAS BEEN CONNECTED");

    int subserver = fork();

    if (subserver == -1) {
      perror("fork");
      exit(1);
    }

    else if (subserver == 0)
      subserver_logic(client_socket);
  }
}
