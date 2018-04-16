#include "common.h"

int main()
{
        int key, semid;
        char ch;
        cpu_set_t mask;         //cpu_set_t data structure represents a set of CPUs.
        CPU_ZERO( &mask );      //Clears set, so that it contains no CPUs. 
        CPU_SET( 2, &mask );    //add cpu to set		
        struct sched_param par;
        if(sched_setaffinity( 0, sizeof(mask), &mask ) == -1 )
	        Error("sched_setaffinity\n");
	par.sched_priority = 38;
        if( sched_setscheduler( 0, SCHED_FIFO, &par ) == -1 )
                Error("sched_setscheduler\n");
        printf("High process arrived at : %d\n", gettime());
        printf("Press any button to enter into critical section\n");
        ch = getchar();
        printf("High process waiting for lock\n"); 
        if ((key=ftok(".",'a')) == -1)
                Error("ftok");
        struct sembuf buf = {0, -1, 0|SEM_UNDO};   
        if((semid = semget(key, 1, 0)) == -1)
                Error("semget");
        if(semop(semid, &buf, 1) == -1)
                Error("semop");
        doSomething(5,"High Priority Process started working at : ");
	buf.sem_op = 1;
        if(semop(semid, &buf, 1) == -1)
                Error("semop");
        exit(0);
}


