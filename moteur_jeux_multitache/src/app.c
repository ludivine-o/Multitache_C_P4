/*
 * app.c
 *
 *  Created on: Apr 15, 2020
 *      Author: ludivineo
 */

#include<stdio.h>
#include<pthread.h>

#include "fifo.h"
#include"app.h"
#include "__debug.h"

static int8_t g_token_top_selector = 1;
static int8_t active_player = NO_PLAYER;
static int8_t g_matrix[COL_COUNT][LINE_COUNT];

Color Black = { 0, 0, 0 }, Blue = { 0, 0, 255 }, Red = { 255, 0, 0 }, White = {
		255, 255, 255 }, Purple = { 255, 0, 255 }, Yellow = { 255, 255, 0 },
		Green = { 0, 255, 0 };

void top_line_display(void) {
	printf("TOP =   ");
	for (int i_top = 1; i_top <= COL_COUNT; i_top++) {
		if (i_top != g_token_top_selector) {
			printf(" 0 ");
		} else {
			printf(" %d ", active_player);
		}
	}
	printf("\n\n");
}
void matrix_lines_display(void) {
	for (int line = 0; line < LINE_COUNT; line++) {
		printf("Line %d  ", (line + 1));
		for (int col = 0; col < COL_COUNT; col++) {
			printf(" %d ", g_matrix[col][line]);
		}
		printf("\n");
	}
}

void gp4_show_board(void) {
	debug_printf(1, "Affichage de la matrice complete\n");
	top_line_display();
	matrix_lines_display();
	printf("\n");
}

bool is_col_empty(int col) {
	if (col < 1) {
		return false;
	}
	if (col > COL_COUNT) {
		return false;
	}
	if (g_matrix[col - 1][0] == 0) {
		return true;
	}
	return false;
}

void gp4_init(void) {
	int row, col;
	data_msg instructions_to_send;
	active_player = PLAYER_1;
	g_token_top_selector = START_POSITION;
	for (row = 0; row < 7; row++) {
		for (col = 0; col < 7; col++) {
			g_matrix[row][col] = NO_PLAYER;
		}
	}
	instructions_to_send.move_token.positions.end_position.c = START_POSITION;
	instructions_to_send.move_token.positions.end_position.l = 0;
	instructions_to_send.move_token.color = color_P1;

}

pos_token_t gp4_move_right_test(void) {
	int direction = +1;
	int destination;
	pos_token_t return_moved_token;
	return_moved_token.beg_position.c = g_token_top_selector - 1;
	return_moved_token.beg_position.l = 0;
	return_moved_token.end_position.l = 0;
	destination = g_token_top_selector + direction;
	while (1) {
		if (destination > COL_COUNT) {
			destination = 1;
		}
		if (is_col_empty(destination) == true) {
			g_token_top_selector = destination;
			return_moved_token.end_position.c = g_token_top_selector - 1;
			return_moved_token.is_ok = true;
			return return_moved_token;
		}
		destination++;
	}
}

pos_token_t gp4_move_left_test(void) {
	int direction = -1;
	int destination;
	pos_token_t return_moved_token;
	return_moved_token.beg_position.c = g_token_top_selector - 1;
	return_moved_token.beg_position.l = 0;
	return_moved_token.end_position.l = 0;
	destination = g_token_top_selector + direction;
	while (1) {
		if (destination < 1) {
			destination = 7;
		}
		if (is_col_empty(destination) == true) {
			g_token_top_selector = destination;
			return_moved_token.end_position.c = destination - 1;
			return_moved_token.is_ok = true;
			return return_moved_token;
		}
		destination--;
	}
}

pos_token_t gp4_play_token(void) {
	int column = g_token_top_selector - 1;
	int line = 5;	//ou LINE_COUNT-1
	while (g_matrix[column][line] != 0) {
		line--;
	}
	g_matrix[(column)][line] = active_player;
	pos_token_t return_played_token;
	return_played_token.is_ok = true;
	return_played_token.beg_position.c = column;
	return_played_token.beg_position.l = 0;
	return_played_token.end_position.c = column;
	return_played_token.end_position.l = line + 1;
	return return_played_token;
}

winner_t gp4_check_status(void) {
	winner_t game_status;
	game_status.status = 0;
	int compteur = 0;
	int col, line;
	for (line = 0; line < 7; line++) {
		for (col = 0; col < 4; col++) {
			if (g_matrix[line][col] == g_matrix[line][col + 1]) {
				if (g_matrix[line][col] == g_matrix[line][col + 2]) {
					if (g_matrix[line][col] == g_matrix[line][col + 3]) {
						if (g_matrix[line][col] != 0) {
							game_status.status = stop_winner;
							game_status.win_type = vert;
							if (g_matrix[line][col] == 1) {
								game_status.win_player = PLAYER_1;
								return game_status;
							} else {
								game_status.win_player = PLAYER_2;
								return game_status;
							}
						}
					}
				}
			}
		}
	}
	for (col = 0; col < 7; col++) {
		for (line = 0; line < 3; line++) {
			if (g_matrix[line][col] == g_matrix[line + 1][col]) {
				if (g_matrix[line][col] == g_matrix[line + 2][col]) {
					if (g_matrix[line][col] == g_matrix[line + 3][col]) {
						if (g_matrix[line][col] != 0) {
							game_status.status = stop_winner;
							game_status.win_type = horiz;
							if (g_matrix[line][col] == 1) {
								game_status.win_player = PLAYER_1;
								return game_status;
							} else {
								game_status.win_player = PLAYER_2;
								return game_status;
							}
						}
					}
				}
			}
		}
	}
	for (line = 0; line < 3; line++) {
		for (col = 0; col < 4; col++) {
			if (g_matrix[line][col] == g_matrix[line + 1][col + 1]) {
				if (g_matrix[line][col] == g_matrix[line + 2][col + 2]) {
					if (g_matrix[line][col] == g_matrix[line + 3][col + 3]) {
						if (g_matrix[line][col] != 0) {
							game_status.status = stop_winner;
							game_status.win_type = right_diag;
							if (g_matrix[line][col] == 1) {
								game_status.win_player = PLAYER_1;
								return game_status;
							} else {
								game_status.win_player = PLAYER_2;
								return game_status;
							}
						}
					}
				}
			}
		}
	}
	for (col = 3; col < 7; col++) {
		for (line = 0; line < 3; line++) {
			if (g_matrix[line][col] == g_matrix[line - 1][col - 1]) {
				if (g_matrix[line][col] == g_matrix[line - 2][col - 2]) {
					if (g_matrix[line][col] == g_matrix[line - 3][col - 3]) {
						if (g_matrix[line][col] != 0) {
							game_status.status = stop_winner;
							game_status.win_type = left_diag;
							if (g_matrix[line][col] == 1) {
								game_status.win_player = PLAYER_1;
								return game_status;
							} else {
								game_status.win_player = PLAYER_2;
								return game_status;
							}

						}
					}
				}
			}
		}
	}
	for (col = 0; col < 7; col++) {
		if (!is_col_empty(col)) {
			compteur++;
		}
	}
	if (compteur == 6) {
		game_status.status = stop_equal;
	}
	return game_status;
}

void gp4_next_player(void) {
	debug_printf(1, "changement de joueur\n");
	if (active_player == 1) {
		active_player = 2;
	} else {
		active_player = 1;
	}
	//TODO :placer le token sur une colonne dispo
	g_token_top_selector = 1;
}

void * application(void*arg) {
	debug_pr_fn(1, "app()entrée dans thread app\n");
	int receive_status = 0;
	data_msg received_instructions;
	data_msg instructions_to_send;
	pos_token_t played_token;
	winner_t game_status;

	while (1) {

		debug_pr_fn(1, "app()entrée dans while thread app\n");
		receive_status = ReceiveMessage(LIST_READ, &received_instructions, sizeof(data_msg));
		debug_pr_fn(1, "app()receive msg status : %d\n", receive_status);
		if (receive_status == 1) {
			if (active_player==NO_PLAYER){
				gp4_init();
				SendMessage(LIST_DISPLAY, &instructions_to_send,sizeof(data_msg));
			}
			else{

			if (received_instructions.value[0] == input_KEY) { //type de commande : saisie clavier
					game_status = gp4_check_status();
					if (game_status.status = live) { // si le jeu n'est NI NULL, NI GAGNE
						if (received_instructions.value[1] == PLAYER_1) { //definir le joueur 1
							active_player = PLAYER_1;
							instructions_to_send.move_token.color = color_P1;
						}
						if (received_instructions.value[1] == PLAYER_2) { //definir le joueur 2
							active_player = PLAYER_2;
							instructions_to_send.move_token.color = color_P2;
						}
						if (received_instructions.value[2] == LEFT) { //direction gauche
							played_token = gp4_move_left_test();
						}
						if (received_instructions.value[2] == RIGHT) { //direction droite
							played_token = gp4_move_right_test();
						}
						if (received_instructions.value[2] == DOWN) { //direction droite
							played_token = gp4_play_token();
						}
						//FIN : Instruction à envoyer
						gp4_show_board();
						instructions_to_send.move_token.positions.beg_position.c =	played_token.beg_position.c;
						instructions_to_send.move_token.positions.beg_position.l =	played_token.beg_position.l;
						instructions_to_send.move_token.positions.end_position.c =  played_token.end_position.c;
						instructions_to_send.move_token.positions.end_position.l =	played_token.end_position.l;
						SendMessage(LIST_DISPLAY, &instructions_to_send,sizeof(data_msg));
						debug_pr_fn(1, "app()send queue = ok\n");
					}
				}
			}
		}
		pthread_exit(NULL);
	}