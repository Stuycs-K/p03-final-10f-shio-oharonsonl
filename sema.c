#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

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

// while wait until semaphore is avaliable (0)
void waitsem(int sema) {
  while (semctl(sema, 0, GETVAL) <= 0)
    usleep(1e6);
}
