#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>   //futex
#include <linux/futex.h>        //futex
#include <syscall.h>
#include <sys/mman.h>
#include <unistd.h> 
#include <sched.h>
#include <sys/shm.h>
#define _GNU_SOURCE

struct Shm{
 int futex_add;
};

void Error(char *msg)
{
  perror(msg);
  exit(1);
}

int gettime ()
{
  return time(NULL);
}

void doSomething (int n, char *str)
{
   struct sched_param param;
   int now = gettime();
   int counter=0;
   printf("%s %d \n",str, gettime());
   sched_getparam(0, &param);
   printf("Priority : %d \n",param.sched_priority);  
        while ( ( gettime() - now) < n)
         { 
            counter++;
         }        
  sched_getparam(0, &param);
  printf("Priority : %d \n",param.sched_priority);
  printf("Work completed at : %d \n",gettime());
}
int FutexLock(int *addr1, int val1)
{       
        return syscall(SYS_futex,addr1,FUTEX_LOCK_PI,val1, NULL, NULL, 0);
}
int FutexUnlock(int *addr, int n)
{
        return syscall(SYS_futex,addr,FUTEX_UNLOCK_PI,n, NULL, NULL, 0);
}
	

