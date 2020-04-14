/*
 * fifo.h
 *
 *  Created on: Apr 7, 2020
 *      Author: ludivineo
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <semaphore.h>

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

/***********fonction initialisation de la liste***************/
void init_list(struct List* liste);

/****************fonction push********************/
void push_element(struct List* liste, int value);

/***************fonction pop************************/
int pop_element(struct List* liste);


#endif /* FIFO_H_ */


