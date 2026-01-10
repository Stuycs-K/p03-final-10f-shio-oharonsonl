#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

void decsem(int sema) {
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;
  semop(sema, &sb, 1);
}

void incsem(int sema) {
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = 1;
  semop(sema, &sb, 1);
}
