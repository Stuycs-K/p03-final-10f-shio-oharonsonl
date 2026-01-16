#ifndef SEMA_H
#define SEMA_H

#define KEY 238969842

#ifndef __APPLE__
union semun {
   int val;
   struct semid_ds *buf;
   unsigned short *array;
   struct seminfo *__buf;
 };
#endif

void decsem(int sema);
void incsem(int sema);
void waitsem(int sema);

#endif
