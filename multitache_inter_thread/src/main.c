#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "fifo.h"
#include <semaphore.h>

/******************Thread d'envoi (push)****************************/
void *thread_push(void *arg){
	struct List * p_liste = arg;
	while(1){
		for(int i=0; i<10; i++) {
			push_element(p_liste, i);
			sleep(1);
		}
	}
	pthread_exit(NULL);
}

/******************Thread de lecture/supression (pop)****************************/
void *thread_pop(void *arg){
	int Value;
	struct List* p_liste = arg;
	while(1){
		for(int i=0; i<10; i++) {
			/*
			int pop_return = pop_element(p_liste,&Value);
			if (pop_return != -1){
				printf("contenu de l'élément : %d; suppression de l'élément\n", pop_return);
			}*/


			}
}
	}
	pthread_exit(NULL);
}


int main(void){
// declaration des threads
	pthread_t thread1;
	pthread_t thread2;

//declaration et init de la liste
	struct List liste;
	init_list(&liste);



// ouverture du lien, lancement des 2 threads, fermeture du lien
	pthread_create(&thread1, NULL, thread_push, &liste);
	pthread_create(&thread2, NULL, thread_pop, &liste);
	pthread_join (thread1, NULL);
	pthread_join (thread2, NULL);

	return 0;
}
