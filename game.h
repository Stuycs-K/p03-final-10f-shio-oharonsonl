#include <string.h>

#ifndef GAME_H
#define GAME_H

enum GAME_STATE { PLAYER_ONE_MOVE, PLAYER_TWO_MOVE, P1_WIN, P2_WIN };

struct GameData {
  char player1;
  char player2;
  int board[3][3];
  enum GAME_STATE state;
};

void print_game_data(struct GameData *game);
void print_board(int board[3][3]);
char *game_data_to_string(struct GameData *game);
struct GameData string_to_game_data(const char *str);
int check_winner(int board[3][3]);

#endif
