/*
 * display.c
 *
 *  Created on: Apr 15, 2020
 *      Author: ludivineo
 */

#include<pthread.h>
#include <unistd.h>

#include"fifo.h"
#include"app.h"
#include"__leds_control.h"
#include "__debug.h"

static Color matrix[LINE_COUNT + 1][COL_COUNT];
static Color actual_matrix[LINE_COUNT + 1][COL_COUNT];
static char init_matrix = 0;


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

void SetLedMatrix(void) {
	for (int row = 0; row < 7; row++) {
		int col = 0;
		while (col < 7) {
			if (init_matrix == 1 && actual_matrix[row][col].RValue == matrix[row][col].RValue //led est deja de la bonne couleur
			&& actual_matrix[row][col].GValue == matrix[row][col].GValue
					&& actual_matrix[row][col].BValue
							== matrix[row][col].BValue) {
			} else {
				setLedColor((row + 1), (col + 1), matrix[row][col].RValue,
						matrix[row][col].GValue, matrix[row][col].BValue);
				actual_matrix[row][col].RValue = matrix[row][col].RValue;
				actual_matrix[row][col].GValue = matrix[row][col].GValue;
				actual_matrix[row][col].BValue = matrix[row][col].BValue;
				debug_pr_fn(1, "SetLedMatrix() SLC = ok");
			}
			col++;
		}
	}
	init_matrix = 1;
}

void *display(void*arg) {
	debug_pr_fn(1,"display()entrée dans thread display\n");
	data_msg request;
	int receive_status;
	matrix[0][0] = Blue;
	SetLedMatrix();
	while (1) {
		receive_status = ReceiveMessage(LIST_DISPLAY, &request, sizeof(data_msg));

		if (receive_status == 1) {

			matrix[request.move_token.positions.beg_position.l][request.move_token.positions.beg_position.c].RValue = Black.RValue;
			matrix[request.move_token.positions.beg_position.l][request.move_token.positions.beg_position.c].GValue = Black.GValue;
			matrix[request.move_token.positions.beg_position.l][request.move_token.positions.beg_position.c].BValue = Black.BValue;
			matrix[request.move_token.positions.end_position.l][request.move_token.positions.end_position.c].RValue = request.move_token.color.RValue;
			matrix[request.move_token.positions.end_position.l][request.move_token.positions.end_position.c].GValue = request.move_token.color.GValue;
			matrix[request.move_token.positions.end_position.l][request.move_token.positions.end_position.c].BValue = request.move_token.color.BValue;
			SetLedMatrix();

			debug_pr_fn(1,"display()SetLedColor = OK\n");
			}
		usleep(500000);
	}
	pthread_exit(NULL);
}

