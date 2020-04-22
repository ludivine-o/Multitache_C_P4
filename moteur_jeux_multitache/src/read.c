/*
 * read.c
 *
 *  Created on: Apr 15, 2020
 *      Author: ludivineo
 */

#include<stdio.h>
#include<pthread.h>

#include "__debug.h"
#include "__leds_control.h"
#include "app.h"
#include "fifo.h"


void *read_button(void*arg) {
	debug_pr_fn(1,"read()entrée thread read\n");
	char recept_tab[5]={0};
	data_msg request;
	while (1) {
		if (readbutton(recept_tab, 5) == LCRC_OK) {
			debug_pr_fn(1,"read()input = (%d %d %d %d)\n", recept_tab[0], recept_tab[1],	recept_tab[2], recept_tab[3]);
			if (recept_tab[3] == 100) {
				request.type = MSG_PLAYER;

				if (recept_tab[1] == 49) {
					request.params.player.player = PLAYER_1;
				}
				if (recept_tab[1] == 50) {
					request.params.player.player = PLAYER_2;
				}
				if (recept_tab[2] == 117) { //vers le haut
					printf("read_button():condition \"haut\"\n");
					request.params.player.direction = UP;
				}
				if (recept_tab[2] == 114 ) {	// vers le droite
					printf("read_button():condition \"droite\" \n");
					request.params.player.direction = RIGHT;
				}
				if (recept_tab[2] == 100 ) { //vers le bas
					printf("read_button():condition \"bas\"\n");
					request.params.player.direction = DOWN;
				}
				if (recept_tab[2] == 108 ) { //vers le gauche
					printf("read_button():condition \"gauche\"\n");
					request.params.player.direction = LEFT;
				}
			debug_pr_fn(1,"read() send to queue = OK\n");
			SendMessage(LIST_READ, &request, sizeof(struct data_msg));
			}
		}
	}
	pthread_exit(NULL);
}
