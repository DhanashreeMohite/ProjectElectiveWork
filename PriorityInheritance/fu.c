#include "fu.h"

int main()
{
        int key, shmid;
	struct Shm *m;
        key = ftok(".", 'b');
	shmid = shmget(key, 1024, IPC_CREAT|0666);
	m= shmat(shmid, 0, 0);
	exit(0);
}

