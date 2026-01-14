#ifndef GAME_H
#define GAME_H

enum GAME_STATE { PLAYER_ONE_MOVE, PLAYER_TWO_MOVE, WIN, LOSE, STALEMATE };

struct GameData {
  char player1;
  char player2;
  int board[3][3];
  enum GAME_STATE state;
};

#endif
