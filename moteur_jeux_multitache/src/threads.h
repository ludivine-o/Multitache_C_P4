/*
 * leds_nbre.h
 *
 *  Created on: Apr 9, 2020
 *      Author: ludivineo
 */

#ifndef THREADS_H_
#define THREADS_H_



/*************Fonction threads**********************/
void *read_button(void*arg); 													// lit le contenu du retour de read button
void *application(void*arg);													// execute la demande transmise par read_button
void *display(void*arg);														// affiche la demande transmise par l'app





#endif /* THREADS_H_ */
