#define STATES_KEY 234987271
#define BOARD_ONE 233949049
#define BOARD_TWO 22949049
#define BOARD_THREE 26949049
#define BOARD_FOUR 78949049

#define BOARD_ONE_SEM 67694200
#define BOARD_TWO_SEM 67694201
#define BOARD_THREE_SEM 67694202
#define BOARD_FOUR_SEM 67694203

#define MOVE_ONE 67694204
#define MOVE_TWO 67694205
#define MOVE_THREE 67694206
#define MOVE_FOUR 67694207

#ifndef __APPLE__
  union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
  };
#endif

#ifndef SEMA_H
#define SEMA_H
void decsem(int sema);
void incsem(int sema);

#endif
