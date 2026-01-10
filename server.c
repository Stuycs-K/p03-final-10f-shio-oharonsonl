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
  send(client_socket, id, sizeof(char), 0); // send the client's id

  int sema = semget(KEY, 1, 0);
  while (semctl(sema, 0, GETVAL) == 1)
    ; // wait until 8 clients

  send(client_socket, "1", sizeof(char), 0); // tell clients game has started
  // game logic

  exit(0); // Must exit the fork
}

// remove shared memory on quit
static void sighandler(int signo) {
  if (signo == SIGINT) {
    int shmid = shmget(KEY, sizeof(int), 0);
    int sema = semget(KEY, 1, 0);

    shmctl(shmid, IPC_RMID, 0);
    semctl(sema, IPC_RMID, 0);
    exit(1);
  }
}

int main() {
  signal(SIGINT, sighandler);
  int server_socket = server_setup();

  int mem_id = shmget(KEY, sizeof(char), IPC_CREAT | 0664);
  int sema = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0664);

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

  // remove later I think
  shmctl(mem_id, IPC_RMID, 0); // remove the segment
  semctl(sema, IPC_RMID, 0);
}
