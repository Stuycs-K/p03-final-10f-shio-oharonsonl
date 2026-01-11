#ifndef SEMA_H
#define SEMA_H

#define KEY 234987271

// union semun {
//   int val;
//   struct semid_ds *buf;
//   unsigned short *array;
//   struct seminfo *__buf;
// };

void decsem(int sema);
void incsem(int sema);

#endif
