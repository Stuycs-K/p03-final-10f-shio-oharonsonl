#include "networking.h"
#include "client.h"

void print_board(int board[3][3]){
  printf("Current game state: \n");
  for(int i = 0; i < 3; i++){
    printf("Row %d: ",i);
    for(int j = 0; j < 3; j++){
      if(board[i][j] == 0){//empty square
        printf(" - ");
      }
      else if(board[i][j] == 1){//x
        printf(" X ");
      }
      else if(board[i][j] == 2){//o or something's messed up
        printf(" O ");
      }
    }
    printf("\n");
  }
}

void client_logic(int server_socket) {
  char my_id_print;
  recv(server_socket, &my_id_print, sizeof(char), 0); // this is blocking

  printf("Recieved: %c\n", my_id_print);

  printf("GAME 1 STARTS NOW! You are player %c\n", my_id_print);

  int my_id = my_id_print - '0';
  printf("my_id = %d\n",my_id);

  if(my_id % 2 == 0){
    game(0,server_socket);
  }
  else{
    game(1,server_socket);
  }

  char opp_id;
  recv(server_socket, &opp_id, sizeof(char), 0);
  printf("Congratulations, you are in the semifinals! You are playing player %c\n", opp_id);
  //player with lower id number goes first
  if(my_id < opp_id)game(1,server_socket);
  else{
    game(0,server_socket);
  }

  recv(server_socket,&opp_id,sizeof(char), 0);
  printf("Playing for the championship against player %c!\n",opp_id);
  //player with lower id number goes first
  if(my_id < opp_id)game(1,server_socket);
  else{
    game(0,server_socket);
  }


  printf("WE DID IT!!!!! YOU WIN!!!!!!\n");
  exit(0);
}

void game(int GOING_FIRST, int server_socket){
  //intialize board
  int board[3][3];
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      board[i][j] = 0;
    }
  }

  char opp_move[2];
  char my_move[4];

  while(GOING_FIRST==1){
    printf("Because you are going first, you are X's (the board is currently empty)\n");
    printf("Move using coordinates (top left is 0,0): \n");
    fgets(my_move, sizeof(my_move), stdin);

    int x_cor = my_move[0] - '0';
    int y_cor = my_move[2] - '0';

    fflush(stdin);
    printf("x_cor = %d, y_cor = %d, my_move[2] = %c\n", x_cor, y_cor, my_move[2]);

    if(x_cor > 2 || x_cor < 0 || y_cor > 2 || y_cor < 0){
      printf("Invalid input! Try again\n");
    }
    else{
      board[y_cor][x_cor] = 1;
      send(server_socket,my_move,sizeof(my_move),0);
      break;
    }
  }
  if(GOING_FIRST != 0)printf("Your move succeeeded\n");
  if(GOING_FIRST==0){
    printf("Because you are not going first, you have O's (but get the auto-win in a stalemate!)\n");
  }

  while(1){
    //use listen to block until there's actually a move from the server
    fd_set descriptors;
    FD_ZERO(&descriptors);
    FD_SET(server_socket, &descriptors);
    select(server_socket+1, &descriptors, NULL,NULL,NULL);

    recv(server_socket,opp_move,2,0);
    int x_cor = opp_move[0] - '0';
    int y_cor = opp_move[1] - '0';

    printf("\nI am a stupid potato head %c %c\n", opp_move[0], opp_move[1]);

    if(y_cor == 3 && x_cor == 3){//server sent loss code
      printf("It appears you have lost. Adios!\n");
      exit(0);
      //can later give the opportunity to stay and wait to hear winner, maybe even a third place game
    }

    else if(y_cor == 4 && x_cor == 4){//server sent win message
      printf("You win! Yay!\n");
    }

    if(GOING_FIRST==0)board[y_cor][x_cor] = 2;
    else{
      board[y_cor][x_cor] = 1;
    }

    int i = 0;

    //loop until valid input
    while(1){
      printf("i = %d\n", i);
      i++;
      print_board(board);
      printf("Move using coordinates (top left is 0,0): \n");
      fgets(my_move, sizeof(my_move), stdin);

      int x_cor = my_move[0] - '0';
      int y_cor = my_move[2] - '0';

      fflush(stdin);

      if(x_cor > 2 || x_cor < 0 || y_cor > 2 || y_cor < 0){
      printf("Invalid input! Try again\n");
      }
      else{
        board[y_cor][x_cor] = 1;
        send(server_socket,my_move,sizeof(my_move),0);
        break;
      }
    }
  }
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
