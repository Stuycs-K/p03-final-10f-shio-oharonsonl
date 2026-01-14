#include "networking.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

void client_logic(int server_socket) {
  char id;
  recv(server_socket, &id, sizeof(char), 0);
  printf("Recieved: %c\n", id);

  char str_state[256];
  recv(server_socket, str_state, sizeof(str_state), 0);
  struct GameData game = string_to_game_data(str_state);
  print_board(game.board);

  printf("GAME STARTS NOW! You are player #%c\n", id);

  while (game.state != WIN && game.state != LOSE && game.state != STALEMATE) {
    if ((game.state == PLAYER_ONE_MOVE && game.player1 == id) ||
        (game.state == PLAYER_TWO_MOVE && game.player2 == id)) {
      int row, col;
      printf("Your move! Enter row and column (0, 1, or 2) separated by space: ");
      scanf("%d %d", &row, &col);

      // send move to server
      char move[4];
      snprintf(move, sizeof(move), "%d%d", row, col);
      send(server_socket, move, sizeof(move), 0);
    } else {
      printf("Waiting for opponent's move...\n");
    }

    // receive updated game state from server -- this loops infintely idk why
    char str_state[256];
    recv(server_socket, str_state, sizeof(str_state), 0);
    game = string_to_game_data(str_state);
    print_board(game.board);
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
