#include<stdio.h>
#include <stdlib.h>
#include "fifo.h"
#include <pthread.h>
#include <semaphore.h>


/*****************fonction envoi/reception dans liste + semaphore*************************/
void SendMessage(List_Id liste, char* message, int message_length){
	int int_message = (int)*message;
	if (liste == LIST_READ){
		push_element(&liste_read, int_message);
		sem_post(&liste_read.semaphore_list);
	}
	else if(liste == LIST_DISPLAY){
		push_element(&liste_display, int_message);
		sem_post(&liste_display.semaphore_list);
	}
}

int ReceiveMessage(List_Id liste, char* message, int message_length){
	int pop_status = 0;
	if (liste == LIST_READ){
		sem_wait(&liste_read.semaphore_list);
		pop_status = pop_element(&liste_read, message);
	}
	else if(liste == LIST_DISPLAY){
		sem_wait(&liste_display.semaphore_list);
		pop_status = pop_element(&liste_display, message);
	}
	return pop_status;
}




/**************************fonction d'init de la liste*******************************/
void init_list(struct List* liste){
	liste->head = 0;
	liste->tail = 0;
	liste->init = 1;
	liste->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	sem_init(&liste->semaphore_list,0,0);
}


/**************************fonction push*******************************/
int push_element(struct List *liste, int value) {

	////sem_wait(&liste->semaphore_list);
	if (liste->init == 1) {
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
			printf("(push_element() : ajout de l'élément %d)\n", value);
		}
		//sem_post(&liste->semaphore_list);
		return 1;
	}
	else {
		return 0;
	}
}






/**************************fonction pop V2*******************************/
int pop_element(struct List* liste, char * value) {

	//sem_wait(&liste->semaphore_list);
	pthread_mutex_lock (&liste->mutex);
	struct Element* tmp;
	if (liste->head == 0) {
		pthread_mutex_unlock (&liste->mutex);
		return 0; 							// Retourne 0 = fail
	}
	tmp = liste->head->next_p;
	*value = liste->head->value;
	free(liste->head);
	liste->head = tmp;						// Le pointeur pointe sur le dernier élément.
	pthread_mutex_unlock (&liste->mutex);
	printf("(pop_element() : suppression de l'élément)\n");
	return 1;								// retour 1 = success

}




