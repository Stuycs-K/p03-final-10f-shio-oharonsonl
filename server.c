#include "networking.h"
#include "server.h"

#define EMPTY 0
#define X 1
#define O 2

void subserver_logic(int client_socket, char *id) {
  int states_id = shmget(STATES_KEY, sizeof(char) * PLAYER_NUM, 0);
  char *states = shmat(states_id, NULL, 0);

  int board_one = shmget(BOARD_ONE, sizeof(int) * 9, IPC_CREAT | 0664);
  int board_two = shmget(BOARD_TWO, sizeof(int) * 9, IPC_CREAT | 0664);
  int board_three = shmget(BOARD_THREE, sizeof(int) * 9, IPC_CREAT | 0664);
  int board_four = shmget(BOARD_FOUR, sizeof(int) * 9, IPC_CREAT | 0664);

  int move_one = shmget(MOVE_ONE, sizeof(char) * 2, IPC_CREAT | 0664);
  int move_two = shmget(MOVE_TWO, sizeof(char) * 2, IPC_CREAT | 0664);
  int move_three = shmget(MOVE_THREE, sizeof(char) * 2, IPC_CREAT | 0664);
  int move_four = shmget(MOVE_FOUR, sizeof(char) * 2, IPC_CREAT | 0664);

  if (states == (char *)-1) {
    perror("shmat");
    exit(1);
  }

  send(client_socket, id, sizeof(char), 0); // send the client's id

  int sema = semget(STATES_KEY, 1, 0);
  while (semctl(sema, 0, GETVAL) == 1)
    ; // wait until PLAYER_NUM clients

  send(client_socket, "1", sizeof(char), 0); // tell clients game has started

  //three games
  char * opp_move;
  for(int i = 0; i < 3; i++){
    int** board;
    int board_sem;
    if(i != 0){//update later, for now only one game works
      break;
      char opp_id = determine_opps(states, id);
    }
    else{

      if(*id == '1'||*id=='2'){
        board = shmat(board_one,0,0);
        board_sem = semget(BOARD_ONE_SEM, 1, 0);
        opp_move = shmat(move_one,0,0);
      }
      if(*id == '3'||*id=='4'){
        board = shmat(board_two,0,0);
        board_sem = semget(BOARD_TWO_SEM, 1, 0);
        opp_move = shmat(move_two,0,0);
      }
      if(*id == '5'||*id=='6'){
        board = shmat(board_three,0,0);
        board_sem = semget(BOARD_THREE_SEM, 1, 0);
        opp_move = shmat(move_three,0,0);
      }
      if(*id == '7'||*id=='8'){
        board = shmat(board_four,0,0);
        board_sem = semget(BOARD_FOUR_SEM, 1, 0);
        opp_move = shmat(move_four,0,0);
      }

      if(atoi(id) % 2 == 0){//first move
        incsem(board_sem);
        for(int i = 0; i < 3; i++){
          for(int j = 0; j < 3; j++){
            board[i][j] = 0;
          }
        }
      }
    }
    //game

    char my_move[3];

    //first move
    if(atoi(id) % 2 == 0){
      recv(client_socket, my_move, 3,0);
      int x_cor = atoi(&my_move[0]);
      int y_cor = atoi(&my_move[2]);

      board[y_cor][x_cor] = 1;

      opp_move[0] = my_move[0];
      opp_move[1] = my_move[2];

      decsem(board_sem);
    }
    while(1){
      incsem(board_sem);

      //check for a winner
      int lines[8][3] = {//all winning lines
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // cols
        {0, 4, 8}, {2, 4, 6}             // diags
      };

      for (int i = 0; i < 8; i++) {
        int a = lines[i][0], b = lines[i][1], c = lines[i][2];

        int ar = a / 3, ac = a % 3;
        int br = b / 3, bc = b % 3;
        int cr = c / 3, cc = c % 3;

        int v1 = board[ar][ac];
        if (v1 == EMPTY) continue; // can't win with empties

        int v2 = board[br][bc];
        int v3 = board[cr][cc];

        if (v1 == v2 && v2 == v3){
          if(v1 == 1){
            if(atoi(id) % 2 ==0){
              opp_move[0] = 4;
              opp_move[1] = 4;
              states[atoi(id)-1]='W';
            }
            else{
              opp_move[0] = 3;
              opp_move[1] = 3;
              states[atoi(id)-1] = 'L';
              printf("Client lost, exiting\n");
              exit(0);
            }
          }
          else{
            if(atoi(id) % 2 ==0){
              opp_move[0] = 3;
              opp_move[1] = 3;
              states[atoi(id)-1] = 'L';
              printf("Client lost, exiting\n");
              exit(0);
            }
            else{
              opp_move[0] = 4;
              opp_move[1] = 4;
              states[atoi(id)-1] = 'W';
            }
          }
        }
      }

      send(client_socket, opp_move, 2, 0);
      recv(client_socket, my_move, 3, 0);

      int x_cor = atoi(&my_move[0]);
      int y_cor = atoi(&my_move[2]);

      if(atoi(id)%2==0)board[y_cor][x_cor] = 2;
      else{
        board[y_cor][x_cor] = 1;
      }

      opp_move[0] = my_move[0];
      opp_move[1] = my_move[2];

      decsem(board_sem);
    }
    shmdt(board);
    shmdt(opp_move);
  }
  // game logic

  printf("Current game states:\n");
  for (int i = 0; i < PLAYER_NUM; i++) {
    printf("Player %d: %c\n", i + 1, states[i]);
  }

  // loop until all players have finished
  int finished = 0;
  while (!finished) {
    finished = 1;
    for (int i = 0; i < PLAYER_NUM; i++) {
      if (states[i] != 'W' && states[i] != 'L') {
        finished = 0;
        break;
      }
    }
    sleep(1);
  }
  printf("All players have finished the game.\n");



  shmdt(states);
  exit(0); // Must exit the fork
}

// remove shared memory on quit
static void sighandler(int signo) {
  if (signo == SIGINT) {
    int states = shmget(STATES_KEY, sizeof(int), 0);
    int board_one = shmget(STATES_KEY, sizeof(int), 0);
    int board_two = shmget(STATES_KEY, sizeof(int), 0);
    int board_three= shmget(STATES_KEY, sizeof(int), 0);
    int board_four= shmget(STATES_KEY, sizeof(int), 0);
    int sema = semget(STATES_KEY, 1, 0);

    shmctl(states, IPC_RMID, 0);
    shmctl(board_one, IPC_RMID, 0);
    shmctl(board_two, IPC_RMID, 0);
    shmctl(board_three, IPC_RMID, 0);
    shmctl(board_four, IPC_RMID, 0);
    semctl(sema, IPC_RMID, 0);
    exit(1);
  }
}

//will figure this out
char determine_opps(char * states, char * id){

}

int main() {
  signal(SIGINT, sighandler);
  int server_socket = server_setup();

  int states = shmget(STATES_KEY, sizeof(char) * PLAYER_NUM, IPC_CREAT | 0664);
  int board_one = shmget(BOARD_ONE, sizeof(int) * 9, IPC_CREAT | 0664);
  int board_two = shmget(BOARD_TWO, sizeof(int) * 9, IPC_CREAT | 0664);
  int board_three = shmget(BOARD_THREE, sizeof(int) * 9, IPC_CREAT | 0664);
  int board_four = shmget(BOARD_FOUR, sizeof(int) * 9, IPC_CREAT | 0664);

  int move_one = shmget(MOVE_ONE, sizeof(char) * 2, IPC_CREAT | 0664);
  int move_two = shmget(MOVE_TWO, sizeof(char) * 2, IPC_CREAT | 0664);
  int move_three = shmget(MOVE_THREE, sizeof(char) * 2, IPC_CREAT | 0664);
  int move_four = shmget(MOVE_FOUR, sizeof(char) * 2, IPC_CREAT | 0664);

  int sema = semget(STATES_KEY, 1, IPC_CREAT | IPC_EXCL | 0664);
  union semun us;
  us.val = 1;
  semctl(sema, 0, SETVAL, us);

  int board_sem[4];
  board_sem[0] = semget(BOARD_ONE_SEM, 1, 0);
  board_sem[1] = semget(BOARD_ONE_SEM, 1, 0);
  board_sem[2] = semget(BOARD_ONE_SEM, 1, 0);
  board_sem[3] = semget(BOARD_ONE_SEM, 1, 0);
  for(int i = 0; i < 4; i++){
    union semun us;
    us.val = 1;
    semctl(board_sem[i], 0, SETVAL, us);
  }


  int clients = 0;
  while (clients < PLAYER_NUM) {
    int client_socket = server_tcp_handshake(server_socket);
    printf("A CLIENT HAS BEEN CONNECTED\n");
    clients++;

    int subserver = fork();
    if (subserver == -1) {
      perror("fork");
      exit(1);
    }

    else if (subserver == 0) {
      char buf[4];
      sprintf(buf, "%d", clients);
      subserver_logic(client_socket, buf);
    }
  }

  decsem(sema);

  for (int i = 0; i < PLAYER_NUM; i++)
    wait(NULL); // wait for all child processes

  // remove later I think
  shmctl(states, IPC_RMID, 0); // remove the segment
  semctl(sema, IPC_RMID, 0);
}
