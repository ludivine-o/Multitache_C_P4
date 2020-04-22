/*
 * fifo.h
 *
 *  Created on: Apr 7, 2020
 *      Author: ludivineo
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <semaphore.h>
#include "app.h"


typedef enum {
LIST_READ, LIST_DISPLAY }
List_Id;

typedef union data_msg {
	move_token_t move_token;
	char value[10];
}data_msg;

#define MSGSIZE sizeof(data_msg)

struct Element {
	data_msg data;
	struct Element *next_p;
};

struct List{
	struct Element *head;
	struct Element *tail;
	pthread_mutex_t mutex;
	sem_t semaphore_list;
	int init;
};

void init_list(struct List* liste);
struct List liste_display;
struct List liste_read;

void SendMessage(List_Id liste, data_msg * message, int message_length);
int ReceiveMessage(List_Id liste, data_msg * message, int message_length);


#endif /* FIFO_H_ */


