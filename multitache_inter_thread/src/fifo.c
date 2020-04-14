#include<stdio.h>
#include <stdlib.h>
#include "fifo.h"
#include <pthread.h>
#include <semaphore.h>







/**************************fonction d'init de la liste*******************************/
void init_list(struct List* liste){

	liste->head = 0;
	liste->tail = 0;
	liste->init = 1;
	liste->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	sem_init(&liste->semaphore_list,0,1);
}


/**************************fonction push*******************************/
int push_element(struct List *liste, int value) {

	//sem_wait(&liste->semaphore_list);
	if (&liste->init == 1) {
		struct Element* new_element = malloc(sizeof(struct Element)); 			//new_element contient l'adresse memoire des 8 octets crée
		if (new_element) {            											 // si le malloc contient bien une adresse
			pthread_mutex_lock(&liste->mutex);
			new_element->value = value;                   							//valeur du struct
			new_element->next_p = 0;              										// adresse du prochain element
			if (liste->head == 0) {                								      // si la liste est vide
				liste->tail = new_element; 										//on attache le nouvel element a la queue de liste
				liste->head = new_element;         									  // on attache la tete aussi
			} else {                    													//si la liste contient deja des elements
				liste->tail->next_p = new_element;
				liste->tail = new_element;
			}
			pthread_mutex_unlock(&liste->mutex);
			printf("ajout de l'élément %d, à l'adresse ....\n", value);
		}
		sem_post(&liste->semaphore_list);
		return 1;
	}
	else {
		return 0;
	}
}


/**************************fonction push*******************************/
int pop_element(struct List* liste, int *value) {
	int result_value; 			// va contenir la valeur du dernier element de la liste
	sem_wait(&liste->semaphore_list);
	pthread_mutex_lock (&liste->mutex);
	struct Element* tmp;
	if (liste->head == 0) {
		pthread_mutex_unlock (&liste->mutex);
		return -1; 	// Retourne -1 si la pile est vide
	}
	tmp = liste->head->next_p;
	result_value = liste->head->value;
	free(liste->head);
	liste->head = tmp;			// Le pointeur pointe sur le dernier élément.
	pthread_mutex_unlock (&liste->mutex);
	return result_value;		// Retourne la valeur soutirée de la pile.

}
