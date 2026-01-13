#ifndef SEMA_H
#define SEMA_H

#define STATES_KEY 234987271
#define BOARD_ONE 233949049
#define BOARD_TWO 22949049
#define BOARD_THREE 26949049
#define BOARD_FOUR 78949049

#define BOARD_ONE_SEM 67694200
#define BOARD_TWO_SEM 67694201
#define BOARD_THREE_SEM 67694202
#define BOARD_FOUR_SEM 67694203

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short *array;
  struct seminfo *__buf;
};

void decsem(int sema);
void incsem(int sema);

#endif
