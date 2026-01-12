#include "networking.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

void print_board(int board[3][3]){
  printf("Current game state: \n");
  for(int i = 0; i < 3; i++){
    printf("Row %d: ",i);
    for(int j = 0; j < 3; j++){
      if(board[i][j] == 0){//empty square
        printf("  ");
      }
      if(board[i][j] == 1){//x
        printf("X ");
      }
      else{//o or something's messed up
        printf("O ")l
      }
    }
    printf("\n");
  }
}

void client_logic(int server_socket) {
  char id;
  recv(server_socket, &id, sizeof(char), 0); // this is blocking

  printf("Recieved: %c\n", id);
  char dummy;
  recv(server_socket, &dummy, sizeof(char), 0);

  printf("GAME 1 STARTS NOW! You are player %c\n", id);

  //intialize game
  int board[3][3];
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      board[i][j] = 0;
    }
  }



  printf("Move using coordinates (top left is 0,0): \n");
  char move[3];
  fgets(move, sizeof(move), stdin);
  send(server_socket, move, sizeof(move), 0);

  printf("Waiting for other players to finish...\n");
  fflush(stdout);
  recv(server_socket, &dummy, sizeof(char), 0);
  printf("All players have finished the first round!\n");
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
