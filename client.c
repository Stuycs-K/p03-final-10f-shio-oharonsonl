#include "networking.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

void client_logic(int server_socket) {
  char id;
  recv(server_socket, &id, sizeof(char), 0); // this is blocking

  printf("Recieved: %c\n", id);
  recv(server_socket, NULL, sizeof(char), 0);

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

  //  while(1){
  //    printf("Ready to start playing? y/n/exit\n");
  //    char * buffer = malloc(BUFFER_SIZE);
  //    fgets(buffer, BUFFER_SIZE, stdin);
  //    if(!strcmp(buffer, "y")){
  //      err(send(server_socket,"1",strlen(to_server),0), "issue sending ready
  //      message to server"); break;
  //    }
  //    if(!strcmp(buffer,"exit")){
  //      exit(0);
  //    }
  //    sleep(1);
  //  }
  //
  //  printf("You have readied!\n");
  //  while(1){
  //    //will fill in with code waiting to get the ready signal from the server
  //  }

  client_logic(server_socket);
}
