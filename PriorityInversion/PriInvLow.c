#include "common.h"

int main()
{
        char ch;
        int key, semid;
        cpu_set_t mask;         //cpu_set_t data structure represents a set of CPUs.
        CPU_ZERO( &mask );      //Clears set, so that it contains no CPUs. 
        CPU_SET( 1, &mask );    //add cpu to set		
        struct sched_param param;
        if(sched_setaffinity( 0, sizeof(mask), &mask ) == -1 )
	        Error("sched_setaffinity\n");      
        param.sched_priority = 20;
        if(sched_setscheduler( 0, SCHED_FIFO, &param ) == -1 )
                Error("sched_setscheduler\n");          
        printf("Low process arrived at : %d\n", gettime());
        printf("Press any button to enter into critical section \n");
        ch = getchar();
        if ((key=ftok(".",'a')) == -1)
                Error("ftok");
        struct sembuf buf = {0, -1, 0|SEM_UNDO};   
        if((semid = semget(key, 1, 0)) == -1)
                Error("semget");
        if(semop(semid, &buf, 1) == -1)
                Error("semop");
        doSomething(20,"Low Priority Process started working at : ");  
	buf.sem_op = 1;
        if(semop(semid, &buf, 1) == -1)
                Error("semop");        
        exit(0);
}


