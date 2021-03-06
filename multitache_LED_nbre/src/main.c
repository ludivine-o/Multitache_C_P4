/*
*****************************************************************************

  File        : main.cpp


  //TODO : /!\ Les chiffres passent de 2 en 2 !!!!


*****************************************************************************
*/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#include "leds_control.h"
#include "leds_nbre.h"
#include "fifo.h"

struct List liste_display;
struct List liste_read;

int main(void){

	//declaration et init de la liste de lecture
	init_list(&liste_read);
	printf("init list() : initialisation de la file d'attente de lecture \n");

	//declaration et init de la liste d'envoi
	init_list(&liste_display);
	printf("init list() : initialisation de la file d'attente d'écriture \n");

	//init des deux matrix
	init_matrix();
	printf("init list() : initialisation des matrices \n");

	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;

	openLink();
	pthread_create(&thread1, NULL, read_button, NULL);
	pthread_create(&thread2, NULL, application, NULL);
	pthread_create(&thread3, NULL, display, NULL);
	pthread_join (thread1, NULL);
	pthread_join (thread2, NULL);
	closeLink();
	return 0;

}
