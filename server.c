#include "game.h"
#include "networking.h"
#include "sema.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <unistd.h>

void subserver_logic(int client_socket, char *id) {
  send(client_socket, &id[0], sizeof(char), 0);

  int sema = semget(KEY, 1, 0);
  while (semctl(sema, 0, GETVAL) == 1) {
    sleep(1);
  };

  int game_ids[4] = {shmget(KEY, sizeof(struct GameData), 0664),
                     shmget(KEY + 1, sizeof(struct GameData), 0664),
                     shmget(KEY + 2, sizeof(struct GameData), 0664),
                     shmget(KEY + 3, sizeof(struct GameData), 0664)};

  int game_semas[4] = {
      semget(KEY + 10, 1, 0664),
      semget(KEY + 11, 1, 0664),
      semget(KEY + 12, 1, 0664),
      semget(KEY + 13, 1, 0664),
  };

  struct GameData *games[4] = {
      shmat(game_ids[0], NULL, 0), shmat(game_ids[1], NULL, 0),
      shmat(game_ids[2], NULL, 0), shmat(game_ids[3], NULL, 0)};

  int game_index = 0;
  for (int i = 0; i < 4; i++) {
    waitsem(game_semas[i]);
    decsem(game_semas[i]);

    if (games[i]->player1 == id[0] || games[i]->player2 == id[0]) {
      game_index = i;
      incsem(game_semas[i]);
      break;
    }

    incsem(game_semas[i]);
  }

  waitsem(game_semas[game_index]);
  decsem(game_semas[game_index]);

  char *state = game_data_to_string(games[game_index]);
  send(client_socket, state, sizeof(state), 0);

  incsem(game_semas[game_index]);

  while (1) {
    sleep(1);
  }

  exit(0);
}

// remove shared memory on quit
static void sighandler(int signo) {
  if (signo == SIGINT) {
    int sema = semget(KEY, 1, 0);
    semctl(sema, IPC_RMID, 0);

    int game_ids[4] = {
        shmget(KEY, sizeof(struct GameData), 0664),
        shmget(KEY + 1, sizeof(struct GameData), 0664),
        shmget(KEY + 2, sizeof(struct GameData), 0664),
        shmget(KEY + 3, sizeof(struct GameData), 0664),
    };

    int game_semas[4] = {
        semget(KEY + 10, 1, 0664),
        semget(KEY + 11, 1, 0664),
        semget(KEY + 12, 1, 0664),
        semget(KEY + 13, 1, 0664),
    };

    for (int i = 0; i < 4; i++) {
      semctl(game_semas[i], IPC_RMID, 0);
      shmctl(game_ids[i], IPC_RMID, 0);
    }

    exit(1);
  }
}

int main() {
  signal(SIGINT, sighandler);
  int server_socket = server_setup();

  int game_ids[4] = {
      shmget(KEY, sizeof(struct GameData), IPC_CREAT | IPC_EXCL | 0664),
      shmget(KEY + 1, sizeof(struct GameData), IPC_CREAT | IPC_EXCL | 0664),
      shmget(KEY + 2, sizeof(struct GameData), IPC_CREAT | IPC_EXCL | 0664),
      shmget(KEY + 3, sizeof(struct GameData), IPC_CREAT | IPC_EXCL | 0664)};

  struct GameData *games[4] = {
      shmat(game_ids[0], NULL, 0), shmat(game_ids[1], NULL, 0),
      shmat(game_ids[2], NULL, 0), shmat(game_ids[3], NULL, 0)};

  int game_semas[4] = {
      semget(KEY + 10, 1, IPC_CREAT | IPC_EXCL | 0664),
      semget(KEY + 11, 1, IPC_CREAT | IPC_EXCL | 0664),
      semget(KEY + 12, 1, IPC_CREAT | IPC_EXCL | 0664),
      semget(KEY + 13, 1, IPC_CREAT | IPC_EXCL | 0664),
  };

  for (int i = 0; i < 4; i++) {
    union semun us;
    us.val = 1;
    semctl(game_semas[i], 0, SETVAL, us);
  }

  // GAME ONE
  waitsem(game_semas[0]);
  decsem(game_semas[0]);

  games[0]->player1 = '1';
  games[0]->state = PLAYER_ONE_MOVE;
  games[0]->player2 = '2';

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      games[0]->board[i][j] = 0;

  incsem(game_semas[0]);

  // GAME 2
  waitsem(game_semas[1]);
  decsem(game_semas[1]);

  games[1]->player1 = '3';
  games[1]->state = PLAYER_ONE_MOVE;
  games[1]->player2 = '4';

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      games[1]->board[i][j] = 0;

  incsem(game_semas[1]);

  // GAME 3
  waitsem(game_semas[2]);
  decsem(game_semas[2]);

  games[2]->player1 = '5';
  games[2]->state = PLAYER_ONE_MOVE;
  games[2]->player2 = '6';

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      games[2]->board[i][j] = 0;

  incsem(game_semas[2]);

  // GAME 4
  waitsem(game_semas[3]);
  decsem(game_semas[3]);

  games[3]->player1 = '7';
  games[3]->state = PLAYER_ONE_MOVE;
  games[3]->player2 = '8';

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      games[3]->board[i][j] = 0;

  incsem(game_semas[3]);

  int sema =
      semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0664); // semaphore for game start
  union semun us;
  us.val = 1;
  semctl(sema, 0, SETVAL, us);

  int clients = 0;
  while (clients < 8) {
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

  semctl(sema, IPC_RMID, 0);
}
