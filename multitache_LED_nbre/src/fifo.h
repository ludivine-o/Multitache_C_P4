/*
 * fifo.h
 *
 *  Created on: Apr 7, 2020
 *      Author: ludivineo
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <semaphore.h>

extern struct List liste_display;
extern struct List liste_read;

typedef enum {
LIST_READ, LIST_DISPLAY }
List_Id;


/****************Structures d'elements de la liste********************/
struct Element {
	int value;
	struct Element *next_p;
};

/****************Structure de la liste********************/
struct List{
	struct Element *head;
	struct Element *tail;
	pthread_mutex_t mutex;
	sem_t semaphore_list;
	int init;

};

/*****************fonction envoi/reception dans liste + semaphore*************************/
int ReceiveMessage(List_Id liste, char* message, int message_length);
void SendMessage(List_Id liste, char* message, int message_length);

/***********fonction initialisation de la liste***************/
void init_list(struct List* liste);

/****************fonction push********************/
int push_element(struct List* liste, int value);

/***************fonction pop************************/
int pop_element(struct List* liste, char * value);


#endif /* FIFO_H_ */


