#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>

union semun {
  int val;      // value for SETVAL 
  struct semid_ds *buf;  // buffer for IPC_STAT, IPC_SET
  unsigned short int *array;  // array for GETALL, SETALL   
 };
 
int main (void) {
 union semun arg;
 int key, semid;

 key=ftok(".", 'a');
 semid = semget (key, 1, IPC_CREAT | 0644);
 arg.val = 1; 
/* 1 for binary else > 1 for Counting Semaphore */
 semctl (semid, 0, SETVAL, arg);
}
