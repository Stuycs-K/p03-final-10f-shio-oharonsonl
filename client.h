#ifndef client_h
#define client_h
void print_board(int board[3][3]);
void client_logic(int server_socket);
void game(int GOING_FIRST, int server_socket);
#endif
