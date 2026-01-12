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
        printf("O ");
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

  char opp_move[2];
  char my_move[3];

  //PLACEHOLDER FOR CHECKING IF THE CLIENT HAS THE FIRST MOVE OR NOT
  while(GOING_FIRST){
    printf("Because you are going first, you are X's\n");
    print_board(board);
    printf("Move using coordinates (top left is 0,0): \n");
    fgets(my_move, sizeof(my_move), stdin);

    int x_cor = atoi(my_move[0]);
    int y_cor = atoi(my_move[2]);

    if(x_cor > 2 || x_cor < 0 || y_cor > 2 || y_cor < 2){
      printf("Invalid input! Try again\n");
    }
    else{
      board[y_cor][x_cor] = 1;
      send(server_socket,my_move,sizeof(my_move),0);
      break;
    }
  }
  else{
    printf("Because you are not going first, you have O's (but get the auto-win in a stalemate!)\n");
  }


  while(1){
    recv(server_socket,opp_move,2,0);

  }

  print_board(board);

  printf("Move using coordinates (top left is 0,0): \n");
  fgets(move, sizeof(move), stdin);
  send(server_socket, move, sizeof(move), 0);

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
