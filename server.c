#include "networking.h"

int PLAYER_NUM = 8;

void subserver_logic(int client_socket, char *id) {
  int states_id = shmget(STATES_KEY, sizeof(char) * PLAYER_NUM, 0);
  char *states = shmat(states_id, NULL, 0);

  if (states == (char *)-1) {
    perror("shmat");
    exit(1);
  }

  send(client_socket, id, sizeof(char), 0); // send the client's id

  int sema = semget(STATES_KEY, 1, 0);
  while (semctl(sema, 0, GETVAL) == 1)
    ; // wait until PLAYER_NUM clients

  send(client_socket, "1", sizeof(char), 0); // tell clients game has started
  // game logic

  char move[3];
  recv(client_socket, move, sizeof(move), 0);
  printf("Client %s played move: %s\n", id, move);

  if (strcmp(move, "ZZ") == 0) {
    printf("Client %s has won the game!\n", id);
    states[atoi(id) - 1] = 'W'; // mark winner in shared memory
  } else if (strcmp(move, "XX") == 0) {
    printf("Client %s has lost the game!\n", id);
    states[atoi(id) - 1] = 'L'; // mark loser in shared memory
  }

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

  send(client_socket, "1", sizeof(char), 0); // notify client all done

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

int main() {
  signal(SIGINT, sighandler);
  int server_socket = server_setup();

  int states = shmget(STATES_KEY, sizeof(char) * PLAYER_NUM, IPC_CREAT | 0664);
  int board_one = shmget(BOARD_ONE, sizeof(char) * PLAYER_NUM, IPC_CREAT | 0664);
  int board_two = shmget(BOARD_TWO, sizeof(char) * PLAYER_NUM, IPC_CREAT | 0664);
  int board_three = shmget(BOARD_THREE, sizeof(char) * PLAYER_NUM, IPC_CREAT | 0664);
  int board_four = shmget(BOARD_FOUR, sizeof(char) * PLAYER_NUM, IPC_CREAT | 0664);

  int sema = semget(STATES_KEY, 1, IPC_CREAT | IPC_EXCL | 0664);
  union semun us;
  us.val = 1;
  semctl(sema, 0, SETVAL, us);

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
