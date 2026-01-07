#include "networking.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>

void subserver_logic(int client_socket, char* id) {
  send(client_socket, id, sizeof(id), 0); // send the client's id

  exit(0); // Must exit the fork
}

int main() {
  int server_socket = server_setup();
  int clients = 0;

  while (clients < 8) {
    int client_socket = server_tcp_handshake(server_socket);
    printf("A CLIENT HAS BEEN CONNECTED\n");
    clients++;
    int subserver = fork();

    if (subserver == -1) {
      perror("fork");
      exit(1);
    }

    else if (subserver == 0) {
      char buf[4];
      sprintf(buf, "%d", clients);
      subserver_logic(client_socket, buf);
    }
  }
}
