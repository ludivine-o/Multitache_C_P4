
/****************************************************************
 * Création de threads avec Mutex pour protection des données	*
 *****************************************************************/

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






pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Création du mutex */


int tab[5];

void *thread_1(void *arg) // rempli le tab
{
	pthread_mutex_lock(&mutex);
	int contenu = 10;
	for(int i = 0; i<5; i++){
		tab[i] = contenu;
		printf("remplissage de la case %d avec %d\n", i, contenu);
		contenu += 10;
		sleep(1);
	}
	pthread_mutex_unlock(&mutex);
	(void) arg;
	pthread_exit(NULL);
}

void *thread_2(void *arg) // rempli le tab
{
	pthread_mutex_lock(&mutex);
	for(int i = 0; i<5; i++){
		printf("lecture de la case %d : %d\n",i, tab[i]);
	}
	(void) arg;
	pthread_mutex_lock(&mutex);
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t thread1, thread2;

	printf("Avant la création du thread.\n");

	pthread_create(&thread1, NULL, thread_1, NULL);
	pthread_create(&thread2, NULL, thread_2, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	//sleep(10);
	printf("Après la création du thread.\n");
}


