#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1

//	ARGUMENTS DU pthread_create
//	pthread_t * thread,  				//thread
//	pthread_attr_t * attr, 				//NULL
//	void * (* start_routine) (void *), 	// fonction à executer
//	void * arg);						//Parametre de la fonction


/**************************************************
 * 													*
 * creer 2 threads qui s'executent en meme temps	*
 * 													*
 ************************************************** */



void *thread_1(void *arg)
{
	while(1){
		printf("Hello World.\n");
		sleep(1);
	}
	(void) arg;
	pthread_exit(NULL);
}
void *thread_2(void *arg)
{
	while(1){
		printf("World is mine.\n");
		sleep(2);
	}
	(void) arg;
	pthread_exit(NULL);
}
int main(void)
{
    pthread_t thread1, thread2;

    printf("Avant la création du thread.\n");

    if(pthread_create(&thread1, NULL, thread_1, NULL) == -1) {
	perror("pthread_create");
	return EXIT_FAILURE;
    }
    if(pthread_create(&thread2, NULL, thread_2, NULL) == -1 ){
		perror("pthread_create");
		return EXIT_FAILURE;
    }
    sleep(100);
    printf("Après la création du thread.\n");
    return EXIT_SUCCESS;
}
