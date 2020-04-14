/*
 * leds_nbre.c
 *
 *  Created on: Apr 9, 2020
 *      Author: ludivineo
 */

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#include "leds_control.h"
#include "leds_nbre.h"
#include "fifo.h"

#define INC 1
#define DEC -1

/************** declaration des struct de couleurs *******************/
Color Black = { 0, 0, 0 }, Blue = { 0, 0, 255 }, Green = { 0, 255, 0 }, Red = {
		255, 0, 0 }, White = { 255, 255, 255 }, Purple = { 255, 0, 255 },
		Yellow = { 255, 255, 0 };
Color matrix[7][7];
Color actual_matrix[7][7];

/************** declaration des variables *******************/
extern struct List liste_display;
extern struct List liste_read;

char recept_tab[5];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Création du mutex */

/************************************************************************************************************
*fonction qui lit le signal envoyé par les boutons, traduit le msg ( increment ou décrement du chiffre)		*
*et transmets les consignes à "application" (incremeter pour fleche haut, décrement pour fleche bas) 		*
 ************************************************************************************************************/
void *read_button(void*arg) {
	printf("read_button() : entrée dans le thread read :  ");
	int request = 0;
	while (1) {
		if (readbutton(recept_tab, 5) == LCRC_OK) {
			printf("(%d %d %d %d); ",recept_tab[0], recept_tab[1], recept_tab[2], recept_tab[3]);
			//if (recept_tab[0] == 112) {
			//if (recept_tab[1] == 49 || recept_tab[1] == 50) {
			if (recept_tab[2] == 117 && recept_tab[3] == 100) { //vers le haut
				printf("read_button():condition \"haut\"\n");
				request = INC;
			}
			if (recept_tab[2] == 100 && recept_tab[3] == 100) {	// vers le bas
				printf("read_button():condition \"bas\" \n");
				request = DEC;
			}
			SendMessage(LIST_READ, (char *)&request, 1);
			//push_element(&liste_read, DEC);
			//sem_post(&liste_read.semaphore_list);
			//}
			//}
		}
	}
	pthread_exit(NULL);
}

/************************************************************************************************************
 *fonction qui recupere la consigne et l'applique : increment ou decrement du chiffre, et envoi à display	*
 ************************************************************************************************************/
void * application(void*arg) {
	printf("application():entrée dans le thread app \n");
	int number = 5;
	int receive_status = 0;
	char message = '0';
	while (1) {
		receive_status = ReceiveMessage(LIST_READ, &message, 1);
		//sem_wait(&liste_read.semaphore_list);
		if (receive_status == 1) {
			printf("application():succes pop (valeur : %d)\n",
					message);
			if (message == INC) {
				number++;
				if (number > 9) {
					number = 0;
				}
			} else if (message == DEC) {
				number--;
				if (number < 0) {
					number = 9;
				}
			}
			SendMessage(LIST_DISPLAY, (char*)&number, 1);
			//push_element(&liste_display, number);
			//sem_post(&liste_display.semaphore_list);
		}
	}
	pthread_exit(NULL);
}

/************************************************
 *fonction qui recupere le chiffre et l'affiche	*
 ***********************************************/
void *display(void*arg) {
	printf("display():entrée dans le thread display \n");
	char request_number;
	int receive_status;
	matrix_to_nbr(5, Red, Black);
	SetLedMatrix();
	while (1) {
	receive_status = ReceiveMessage(LIST_DISPLAY, &request_number, 1);
				//sem_wait(&liste_read.semaphore_list);
		//if (receive_status == 1) {
			printf("display(): request number : %d\n", request_number);
			matrix_to_nbr(request_number, Red, Black);
			SetLedMatrix();
			sleep(2);
		//}
	}
	pthread_exit(NULL);
}



/*########################################################################################################################*/



/*************Fonct allumage ligne V2**********************/
void SetLedMatrix(void) {
	for (int row = 0; row < 7; row++) {
		int col = 0;
		while (col < 7) {
			if (actual_matrix[row][col].RValue == matrix[row][col].RValue //led est deja de la bonnecouleur
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

///*************Fonct allumage ligne V1**********************/
//void SetLedMatrix() {
//	for (int row = 0; row < 7; row++) {
//		int col = 0;
//		while (col < 7) {
//			setLedColor((row + 1), (col + 1), matrix[row][col].RValue,
//					matrix[row][col].GValue, matrix[row][col].BValue);
//			col++;
//		}
//	}
//}

/*************Fonct matrice eteinte**********************/
void init_matrix(void) {
	int row, col;
	for (row = 0; row < 7; row++) {
		for (col = 0; col < 7; col++) {
			matrix[row][col] = White;
			actual_matrix[row][col] = White;

		}
	}
}
/*************Fonct matrice affiche nombre**********************/
void matrix_to_nbr(int number, Color nbr_color, Color bckgrnd_color) {
	int row, col;
	for (row = 0; row < 7; row++) {
		for (col = 0; col < 7; col++) {
			if (number == 1) { /*Ensemble de conditions pour afficher le chiffre 1*/
				if ((col == 4) || (row == 3 && col == 1)
						|| (row == 2 && col == 2) || (row == 1 && col == 3)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}
			if (number == 2) { /*Ensemble de conditions pour afficher le chiffre 2*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 1 && col == 5) || (row == 2 && col == 5)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 1)
						|| (row == 5 && col == 1) || (row == 6 && col == 2)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}
			if (number == 3) { /*Ensemble de conditions pour afficher le chiffre 3*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 1 && col == 5) || (row == 2 && col == 5)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 5)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 5 && col == 1)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}
			if (number == 4) { /*Ensemble de conditions pour afficher le chiffre 4*/
				if ((row == 0 && col == 4) || (row == 1 && col == 3)
						|| (row == 1 && col == 4) || (row == 2 && col == 2)
						|| (row == 2 && col == 4) || (row == 3 && col == 1)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 3 && col == 5)
						|| (row == 4 && col == 4) || (row == 5 && col == 4)
						|| (row == 6 && col == 4)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}

			if (number == 5) { /*Ensemble de conditions pour afficher le chiffre 5*/
				if ((row == 0 && col == 1) || (row == 0 && col == 2)
						|| (row == 0 && col == 3) || (row == 0 && col == 4)
						|| (row == 0 && col == 5) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 3 && col == 1)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 5)
						|| (row == 5 && col == 5) || (row == 6 && col == 1)
						|| (row == 6 && col == 2) || (row == 6 && col == 3)
						|| (row == 6 && col == 4)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}

			if (number == 6) { /*Ensemble de conditions pour afficher le chiffre 6*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 3 && col == 1)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 1)
						|| (row == 4 && col == 5) || (row == 5 && col == 1)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 1 && col == 5)) {

					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}

			if (number == 7) { /*Ensemble de conditions pour afficher le chiffre 7*/
				if ((row == 0 && col == 1) || (row == 0 && col == 2)
						|| (row == 0 && col == 3) || (row == 0 && col == 4)
						|| (row == 0 && col == 5) || (row == 1 && col == 5)
						|| (row == 2 && col == 5) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 3 && col == 5)
						|| (row == 4 && col == 5) || (row == 5 && col == 5)
						|| (row == 6 && col == 5)) {

					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;

			}
			if (number == 8) { /*Ensemble de conditions pour afficher le chiffre 8*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 2 && col == 5)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 1)
						|| (row == 4 && col == 5) || (row == 5 && col == 1)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 1 && col == 5)) {

					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}

			if (number == 9) { /*Ensemble de conditions pour afficher le chiffre 9*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 2 && col == 5)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 3 && col == 5)
						|| (row == 4 && col == 5) || (row == 5 && col == 1)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 1 && col == 5)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;

			}

			if (number == 0) { /*Ensemble de conditions pour afficher le chiffre 0*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 2 && col == 5)
						|| (row == 3 && col == 5) || (row == 4 && col == 1)
						|| (row == 4 && col == 5) || (row == 5 && col == 1)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 1 && col == 5) || (row == 3 && col == 1)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}
		}
	}
}

