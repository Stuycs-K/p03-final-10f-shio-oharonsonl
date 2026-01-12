#ifndef SEMA_H
#define SEMA_H

#define STATES_KEY 234987271
#define BOARD_ONE 233949049
#define BOARD_TWO 22949049
#define BOARD_THREE 26949049
#define BOARD_FOUR 78949049

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short *array;
  struct seminfo *__buf;
};

void decsem(int sema);
void incsem(int sema);

#endif
