#define _GNU_SOURCE
#include <sched.h>
#include "fu.h"

int main()
{
        char ch;
	printf("Medium Priority Process arrived at : %d \n",gettime());
	cpu_set_t mask;         //cpu_set_t data structure represents a set of CPUs.
        CPU_ZERO( &mask );      //Clears set, so that it contains no CPUs. 
        CPU_SET( 1, &mask );    //add cpu to set		
        struct sched_param parm;
        if(sched_setaffinity( 0, sizeof(mask), &mask ) == -1 )
	        Error("sched_setaffinity\n");
        parm.sched_priority = 28;
        if( sched_setscheduler( 0, SCHED_FIFO, &parm ) == -1 )
                Error("sched_setscheduler\n");
        printf("Press any button to enter into critical section \n");
        ch = getchar();
        doSomething(5,"Medium Priority Process started working at : ");	              
        exit(0);	
}
		

