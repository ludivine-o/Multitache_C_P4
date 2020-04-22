/*
 * leds_nbre.c
 *
 *  Created on: Apr 9, 2020
 *      Author: ludivineo
 */


#include<stdio.h>
#include<pthread.h>
#include<unistd.h>













/*
#include "leds_control.h"
#include "fifo.h"
#include "game_P4.h"
#include "threads.h"

************** declaration des variables *******************




extern struct List liste_display;
extern struct List liste_read;

char recept_tab[5];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; * Création du mutex *

************************************************************************************************************
 *fonction qui lit le signal envoyé par les boutons, traduit le msg ( increment ou décrement du chiffre)		*
 *et transmets les consignes à "application" (incremeter pour fleche haut, décrement pour fleche bas) 		*
 ************************************************************************************************************
void *read_button(void*arg) {
	printf("read_button() : entrée dans le thread read :  ");
	char request[10];
	while (1) {
		if (readbutton(recept_tab, 5) == LCRC_OK) {
			printf("(%d %d %d %d); ", recept_tab[0], recept_tab[1],
					recept_tab[2], recept_tab[3]);

			//TODO : 15 Ajouter un octet à value pour définir le type de commande (value[01 = 1 ->type clavier
			if (recept_tab[0] == 112) {
				if (recept_tab[1] == 49) {
					request[1] = PLAYER_1;
				}
				if (recept_tab[1] == 50) {
					request[1] = PLAYER_2;
				}
				if (recept_tab[2] == 117 && recept_tab[3] == 100) { //vers le haut
					printf("read_button():condition \"haut\"\n");
					request[2] = UP;
				}
				if (recept_tab[2] == 114 && recept_tab[3] == 100) {	// vers le droite
					printf("read_button():condition \"droite\" \n");
					request[2] = RIGHT;
				}
				if (recept_tab[2] == 100 && recept_tab[3] == 100) { //vers le bas
					printf("read_button():condition \"bas\"\n");
					request[2] = DOWN;
				}
				if (recept_tab[2] == 108 && recept_tab[3] == 100) { //vers le gauche
					printf("read_button():condition \"gauche\"\n");
					request[2] = LEFT;
				}
			}
			SendMessage(LIST_READ, request, 3);
		}
	}
	pthread_exit(NULL);
}

/************************************************************************************************************
 *fonction qui recupere la consigne et l'applique : increment ou decrement du chiffre, et envoi à display	*
 ************************************************************************************************************
void * application(void*arg) {
	printf("application():entrée dans le thread app \n");
	//int number = 5;
	int receive_status = 0;
	char message [10];
	gp4_init();
	while (1) {
		receive_status = ReceiveMessage(LIST_READ, &message, 10);
		if (receive_status == 1) {
			printf("application():succes pop\n");
			if (message.value[1] == PLAYER_1){
			//TODO : modifier toutes les fonctions de gp4 pour qu'elles aient un retour de type strut pos_token_t
			//TODO : composer msg à envoyer à l'affichage en fonction du retour du coeur de jeu
			//SendMessage(LIST_DISPLAY, (char*) &number, 1);

			}


		}
	}
	pthread_exit(NULL);
}

/************************************************
 *fonction qui recupere le chiffre et l'affiche	*
 ***********************************************
void *display(void*arg) {
	printf("display():entrée dans le thread display \n");
	struct Element request;
	int receive_status;

	matrix_to_nbr(5, Red, Black);

	SetLedMatrix();
	while (1) {
		receive_status = ReceiveMessage(LIST_DISPLAY, &request, 1);

		// traite le msg recu de l'app

		if (receive_status == 1) {
			printf("display(): request \n");
//			matrix_to_nbr(request_number, Red, Black);
//			SetLedMatrix();
			sleep(2);
		}
	}
	pthread_exit(NULL);
}



void SetLedMatrix(void) {
	for (int row = 0; row < 7; row++) {
		int col = 0;
		while (col < 7) {
			if (actual_matrix[row][col].RValue == matrix[row][col].RValue //led est deja de la bonnecouleu************************fonction d'init de la liste*******************************
void init_list(struct List* liste){
	liste->head = 0;
	liste->tail = 0;
	liste->init = 1;
	liste->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	sem_init(&liste->semaphore_list,0,0);
}r
			&& actual_matrix[row][col].GValue == matrix[row][col].GValue
					&& actual_matrix[row][col].BValue
							== matrix[row][col].BValue) {
			} else {
				setLedColor((row + 1), (col + 1), matrix[row][col].RValue,
						matrix[row][col].GValue, matrix[row][col].BValue);
				actual_matrix[row][col] = matrix[row][col];
			}
			col++;
		}
	}
}
*/
