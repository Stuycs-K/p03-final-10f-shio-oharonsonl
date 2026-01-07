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

  while(1){
    printf("Ready to start playing? y/n/exit\n");
    char * buffer = malloc(BUFFER_SIZE);
    fgets(buffer, BUFFER_SIZE, stdin);
    if(!strcmp(buffer, "y")){
      break;

    }
    if(!strcmp(buffer,"exit")){
      exit(0);
    }
    sleep(1);
  }

  client_logic(server_socket);
}
