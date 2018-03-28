#define _GNU_SOURCE
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sched.h> 
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
int gettime ()
{
  return time(NULL);
}
void Error(char *msg)
{
  perror(msg);
  exit(1);
}
//loop to provide delay of n seconds
void doSomething (int n, char *str)  
{
   int endTime;
   struct sched_param param;
   printf("start Time: %d\n", gettime());
   int now = gettime();
   int counter=0;
   printf("%s %d\n",str, gettime());
   sched_getparam(0, &param);
   printf("My Priority is : %d \n",param.sched_priority); 
   while ( ( gettime() - now) < n)
         { 
            counter++;
         }       
  sched_getparam(0, &param);
  printf("My Priority is : %d \n",param.sched_priority);
  endTime = gettime();
  printf("endTime: %d\n", endTime);
  printf("Process completed\n");
}



