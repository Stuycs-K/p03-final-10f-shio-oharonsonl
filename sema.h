#ifndef SEMA_H
#define SEMA_H

#define KEY 238969842

#ifndef __APPLE__
<<<<<<< HEAD
 union semun {
=======
union semun {
>>>>>>> 29a9224b29e9da5756f419253bcf8acf0fbd8a19
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
