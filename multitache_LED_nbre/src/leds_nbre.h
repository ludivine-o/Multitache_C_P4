/*
 * leds_nbre.h
 *
 *  Created on: Apr 9, 2020
 *      Author: ludivineo
 */

#ifndef LEDS_NBRE_H_
#define LEDS_NBRE_H_



typedef struct {
	int RValue;
	int GValue;
	int BValue;
} Color;



/*************Fonction threads**********************/
void *read_button(void*arg); 													// lit le contenu du retour de read button
void *application(void*arg);													// execute la demande transmise par read_button
void *display(void*arg);														// affiche la demande transmise par l'app



/*************Fonction gestion matrix et led**********************/
void init_matrix(void);
void matrix_to_nbr(int number, Color nbr_color, Color bckgrnd_color);
void SetLedMatrix(void);






#endif /* LEDS_NBRE_H_ */
