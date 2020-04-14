
/**********************************************
* 	multi-thread en liaison serie			*
* 			112 49 100 100					*
* 				J	D	A					*
* 											*
* 			J1 : 49							*
*			J2 : 50							*
*			gauche : 100					*
*			droite : 108					*
*			haut : 114						*
*			bas : 117						*
*			appui : 100						*
*			relache : 117					*
**********************************************/





#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include "leds_control.h"
#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1

//	ARGUMENTS DU pthread_create
//	pthread_t * thread,  				//thread
//	pthread_attr_t * attr, 				//NULL
//	void * (* start_routine) (void *), 	// fonction à executer
//	void * arg);						//Parametre de la fonction

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Création du mutex */


char recept_tab [5];
int active_player, direction, number;



void *thread_send(void *arg){
	//pthread_mutex_lock (&mutex);

	while(1){
		//
		setLedColor(3, 2, 255, 0, 0);
		sleep(1);
	}
	pthread_exit(NULL);
	//pthread_mutex_unlock (&mutex);
}

void *thread_read(void *arg){
	while(1){
		if (readbutton(recept_tab, 5) == LCRC_OK){
			printf("%d %d %d %d\n", recept_tab[0], recept_tab[1], recept_tab[2], recept_tab[3]);
		}
		//pthread_mutex_lock (&mutex);
		if (recept_tab[1] == 49){
			active_player = 1;
		}
		else if (recept_tab[1] == 50){
			active_player = 2;
		}
		if (recept_tab[2] == 117 && recept_tab[3] == 100 ){
					direction = 1;
		}
		else if (recept_tab[2] == 100 && recept_tab[3] == 100 ){
							direction = 3;
		}
	}
	//pthread_mutex_unlock (&mutex);
	pthread_exit(NULL);
}

void *thread_application(void *arg){
	pthread_mutex_lock (&mutex);
	//si fleche haut
		// si joueur 2
			//--> LED bleu
		//si joueur 1
			// --> LED rouge
	pthread_mutex_unlock (&mutex);
	pthread_exit(NULL);
}

int main(void){
	pthread_t thread1;
	pthread_t thread2;
	openLink();
	pthread_create(&thread1, NULL, thread_send, NULL);
	pthread_create(&thread2, NULL, thread_read, NULL);
	pthread_join (thread1, NULL);
	pthread_join (thread2, NULL);
	closeLink();
	return 0;
}
