#include "networking.h"
#define MAX_PLAYERS 8
#define SHMKEY 67694200
#define SEMKEY 67674201

void subserver_logic(int client_socket) {
  // ...

  exit(0); // Must exit the fork
}

int main() {
  int server_socket = server_setup();

  int *data;
  int shmid;
  shmid = shmget(SHMKEY, MAX_PLAYERS*sizeof(int) + 1, IPC_CREAT | 0644);
  data = shmat(shmid, 0, 0);
  //0 out array to be 100% sure that players will be ready
  for(int i = 0; i < MAX_PLAYERS + 1; i++){
    data[i] = 0;
  }

  while (1) {
    int client_socket = server_tcp_handshake(server_socket);
    printf("A CLIENT HAS  CONNECTED\n");

    int subserver = fork();

    if (subserver == -1) {
      perror("fork");
      exit(1);
    }

    else if (subserver == 0)
      subserver_logic(client_socket);
  }

  while(1){
    int readies = 0;
    for(int i = 0; i < MAX_PLAYERS; i++){
      if(data[i] == 1)readies++;
    }
    if(readies==MAX_PLAYERS){
      data[MAX_PLAYERS] = 1;
      break;
    }
    else{
      printf("Not all players are ready\n");
      wait(1);
    }
  }

  //once all players are ready parent closes + deletes shared memory
  shmdt(data);
  shmctl(shmid, IPC_RMID, 0);
}
