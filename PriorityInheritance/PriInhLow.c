#define _GNU_SOURCE
#include <sched.h>
#include "fu.h"

int main()
{
    	int key, shmid;
	struct Shm *m;
        char ch;        
	key = ftok(".", 'b');
	shmid = shmget(key, 1024, 0);
	m= shmat(shmid, 0, 0);	
	printf("My pid: %d \n", getpid());       
        struct sched_param param;       //scheduling parameter        
        cpu_set_t mask;         //cpu_set_t data structure represents a set of CPUs.
        CPU_ZERO( &mask );      //Clears set, so that it contains no CPUs. 
        CPU_SET( 1, &mask );    //add cpu to set        
        if(sched_setaffinity( getpid(), sizeof(mask), &mask ) == -1 )
                Error("sched_setaffinity\n");                
        param.sched_priority = 20;
        if( sched_setscheduler( getpid(), SCHED_FIFO, &param ) == -1 )
                Error("sched_setscheduler\n");        
        printf("Press any button to enter into critical section \n");
        ch = getchar();        
        FutexLock(&m->futex_add, 0);
        printf("Aquired lock... \n");
        printf("futex_add : %d \n",m->futex_add);        
        doSomething(15,"Low Priority Process started working at : ");        
        printf("Low Priority Process releasing lock...");
        FutexUnlock(&m->futex_add, 0);
        printf("futex_add : %d \n",m->futex_add);
        exit(0);
}
		
