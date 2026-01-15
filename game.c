#include "game.h"
#include <stdio.h>

// print struct game data  (for logging/debugging purposes)
void print_game_data(struct GameData *game) {
  printf("Player 1: %c\n", game->player1);
  printf("Player 2: %c\n", game->player2);
  printf("Board:\n");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%d ", game->board[i][j]);
    }
    printf("\n");
  }
  printf("Game State: %d\n", game->state);
}

void print_board(int board[3][3]){
  for (int i = 0; i < 3; i++) {
    printf("Row %d: ", i);
    for(int j = 0; j < 3; j++) {
      if (board[i][j] == 0)
        printf(" - ");
      else if (board[i][j] == 1)
        printf(" X ");
      else if(board[i][j] == 2)
        printf(" O ");
    }
    printf("\n");
  }
}

char *game_data_to_string(struct GameData *game) {
  static char buffer[100];
  snprintf(buffer, sizeof(buffer), "P1: %c, P2: %c, State: %d, Board: [%d,%d,%d;%d,%d,%d;%d,%d,%d]",
           game->player1, game->player2, game->state,
           game->board[0][0], game->board[0][1], game->board[0][2],
           game->board[1][0], game->board[1][1], game->board[1][2],
           game->board[2][0], game->board[2][1], game->board[2][2]);
  return buffer;
}

struct GameData string_to_game_data(const char *str) {
  struct GameData game;
  sscanf(str, "P1: %c, P2: %c, State: %d, Board: [%d,%d,%d;%d,%d,%d;%d,%d,%d]",
         &game.player1, &game.player2, (int *)&game.state,
         &game.board[0][0], &game.board[0][1], &game.board[0][2],
         &game.board[1][0], &game.board[1][1], &game.board[1][2],
         &game.board[2][0], &game.board[2][1], &game.board[2][2]);
  return game;
};

// '1' - player 1 wins
// '2' - player 2 wins or stalemate
// '-1' - game ongoing

int check_winner(int board[3][3]) {
  for (int i = 0; i < 3; i++) {
    if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2])
      return board[i][0];
    if (board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i])
      return board[0][i];
  }

  if (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    return board[0][0];
  if (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    return board[0][2];

  int empty_found = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == 0) {
        empty_found = 1;
        break;
      }
    }
    if (empty_found)
      break;
  }

  if (empty_found) {
    return -1; 
  }
  else
    return 2;
}
