#include "networking.h"
#define MAX_PLAYERS 8
#define SHMKEY 67694200
#define SEMKEY 67674201

void subserver_logic(int client_socket) {
  // ...

  //wait to get the ready signal from client, figure that out soon

  //once ready, set up semaphore + shm and write into it, then close and put semaphore down


  exit(0); // Must exit the fork
}

int main() {
  int server_socket = server_setup();

  //set up semaphore
  int semid = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0664);
  union semun u;
  u.val = 1;
  int r = semctl(semid,0,SETVAL,u);

  //set up shm
  int *data;
  int shmid;
  shmid = shmget(SHMKEY, MAX_PLAYERS*sizeof(int) + 1, IPC_CREAT | 0664);
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
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_flg = SEM_UNDO;
    sb.sem_op = -1;
    semop(semid, &sb, 1);
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
      //temporarily release semaphore
      sb.sem_op = 1;
      err(semop(semid, &sb, 1), "problem releasing semaphore");
    }
  }

  //once all players are ready parent closes + deletes shared memory and semaphore
  shmdt(data);
  shmctl(shmid, IPC_RMID, 0);
  semctl(semid,IPC_RMID,0);
}
