#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *whatever(void *param)
{
	int *my_haha=(int *)param;
	int *what = (int *) malloc(sizeof(int)*4);
	printf("%d\n", *my_haha);
	what[2]=7458;
	sleep(5);
	return ((void *)what);
}

int main()
{	
	pthread_t id;
	int haha;
	int *heehee;
	haha = 5;
	pthread_create(&id, 0, whatever, (void*)&haha);
#ifdef PTHREAD_JOIN	
	pthread_join(id, (void **)(&heehee));
	printf("Heehee[2] is %d\n", heehee[2]);
#else	
	//To allow other threads to continue execution, 
	//the main thread should terminate by calling 
	//pthread_exit() rather than exit()
	pthread_exit(0);
	//exit(1);
	//if call pthread_exit(); the main thread will stop executing and 
	//will remain in zombie(defunct) status until all other threads exit
	//cannot get return status of other threads 
	//and cannot do clean-up for other threads (unless use pthread_join()	
#endif
}
