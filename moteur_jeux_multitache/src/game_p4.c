/*
 * game_p4.c
 *
 *  Created on: Mar 30, 2020
 *      Author: ludivineo
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>





/*
#include "debug.h"
#include "game_P4.h"
#include "declarations.h"



int8_t g_matrix[COL_COUNT][LINE_COUNT];
int active_player = PLAYER_1;
int rounds = 0;
int g_token_top_selector = 1;



/************** affectation des struct de couleurs *******************

//static Color Black = { 0, 0, 0 }, Blue = { 0, 0, 255 }, Red = { 255, 0, 0 }, White = {
//		255, 255, 255 }, Purple = { 255, 0, 255 }, Yellow = { 255, 255, 0 };

Color matrix[7][7];
Color actual_matrix[7][7];



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


//afficher toutes les lignes de la matrice :
void matrix_lines_display(void) {
	for (int line = 0; line < LINE_COUNT; line++) {
		printf("Line %d  ", (line + 1));
		for (int col = 0; col < COL_COUNT; col++) {
			printf(" %d ", g_matrix[col][line]);
		}
		printf("\n");
	}
}




//afficher la ligne TOP :
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

//matrice à zero :
void init_matrix(void) {
	int row, col;
	for (row = 0; row < 7; row++) {
		for (col = 0; col < 7; col++) {
			matrix[row][col] = White;
			actual_matrix[row][col] = White;

		}
	}
}

//La colonne est-elle dispo ?
bool is_col_empty(int col) {
	if (col < 1) {
		error_printf("ASSERT_FAILED(col<1), col=%d\n", col);
		return false;
	}
	if (col > COL_COUNT) {
		error_printf("ASSERT_FAILED(col>%d), col=%d\n", COL_COUNT, col);
		return false;
	}
	if (g_matrix[col - 1][0] == 0) {
		return true;
	}
	return false;
}

/********************************** Fonction initialisation du jeu*****************************
void gp4_init(void) {
	debug_printf(1,
			"gp4_init() : Initialisation de la matrice, du top, du player \n");

	active_player = PLAYER_1;
	rounds = 0;
	g_token_top_selector = 3;
	init_matrix();
}

/************************************ Fonction Affichage de la matrice****************************
void gp4_show_board(void) {
	debug_printf(1, "Affichage de la matrice complete\n");
	top_line_display();
	matrix_lines_display();
	printf("\n");
}

/**************************************** Fonction changer de joueur**************************
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

/***************************************** Fonction déplacement**************************

//// à droite
//void gp4_move_right() {
//	debug_printf(1, "déplacement d'une case à droite\n");
//	//int destination = g_token_top_selector;
//	for (int destination = g_token_top_selector; destination <= COL_COUNT;
//			destination++) {
//		if (destination == COL_COUNT) {
//			destination = 0;
//		}
//		if (g_matrix[destination][0] != 0) {
//			continue;
//		} else {
//			g_token_top_selector = destination + 1;
//			return;
//		}
//	}
//}

// à droite V2
int gp4_move_right_test(void) {
	debug_printf(1, "déplacement d'une case à droite\n");
	int direction = +1;
	int destination = 0;
	while(1){
		//  décrémente le numéro de ma colone
		destination = g_token_top_selector + direction;
		//  if je suis en butée à gauche )
		if (destination > 7){
			// 	Je bascule mon jeton pour qu'il soit sur la 1er colonne de gauche (la min)
			destination = 1;
		}
		// si la colonne est jouable  :
		if (is_col_empty(destination) == true){
			//je valide la position
			g_token_top_selector = destination;
			return g_token_top_selector; 			//--> retourne un
		}
		// si j'ai fait un tour complet
//		if (destination == g_token_top_selector){
//			// je retourne que je peux pas jouer
//			return 0;
//		}
		direction ++;
	}
}

// à gauche V2
pos_token_t gp4_move_left_test(void) {
	debug_printf(1, "déplacement d'une case à gauche\n");
	int direction = -1;
	int destination;
	pos_token_t return_moved_token;
	return_moved_token.beg_position.c = g_token_top_selector-1;
	return_moved_token.beg_position.l = 0;
	return_moved_token.end_position.l = 0;
	while(1){
		//  décrémente le numéro de ma colone
		destination = g_token_top_selector + direction;
		//  if je suis en butée à gauche )
		if (destination < 1){
			// 	Je bascule mon jeton pour qu'il soit sur la 1er colonne de droite (la max
			destination = 7;
		}
		// si la colonne est jouable  :
		if (is_col_empty(destination) == true){
			//je valide la position
			g_token_top_selector = destination;
			return_moved_token.end_position.c = destination;
			return_moved_token.is_ok = true;
			return return_moved_token;
		}
		// si j'ai fait un tour complet
//		if (destination == g_token_top_selector){
//			// je retourne que je peux pas jouer
//			return 0;
//		}
		direction --;
	}
}


/************** Fonction validation de la position top + chute du jeton dans la colonne****************
pos_token_t gp4_play_token(void) {
	debug_printf(1, "gp4_play_token(): validation de la position (g_token) + placement du jeton\n");
	int column = g_token_top_selector - 1;
	int line = 5; 		//ou LINE_COUNT-1
	while (g_matrix[column][line] != 0) {
		line--;
	}
	g_matrix[(column)][line] = active_player;
	pos_token_t return_played_token;
	return_played_token.is_ok = true;
	return_played_token.beg_position.c = column;
	return_played_token.beg_position.l = 0;
	return_played_token.end_position.c = column;
	return_played_token.end_position.l = line;
	return return_played_token;

}

/*************Fonct matrice affiche nombre**********************
void matrix_to_nbr(int number, Color nbr_color, Color bckgrnd_color) {
	int row, col;
	for (row = 0; row < 7; row++) {
		for (col = 0; col < 7; col++) {
			if (number == 1) { /*Ensemble de conditions pour afficher le chiffre 1
				if ((col == 4) || (row == 3 && col == 1)
						|| (row == 2 && col == 2) || (row == 1 && col == 3)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}
			if (number == 2) { /*Ensemble de conditions pour afficher le chiffre 2*
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
			if (number == 3) { /*Ensemble de conditions pour afficher le chiffre 3*
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
			if (number == 4) { /*Ensemble de conditions pour afficher le chiffre 4*
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

			if (number == 5) { /*Ensemble de conditions pour afficher le chiffre 5*
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

			if (number == 6) { /*Ensemble de conditions pour afficher le chiffre 6*
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

			if (number == 7) { /*Ensemble de conditions pour afficher le chiffre 7
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
			if (number == 8) { /*Ensemble de conditions pour afficher le chiffre 8*
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

			if (number == 9) { /*Ensemble de conditions pour afficher le chiffre 9*
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

			if (number == 0) { /*Ensemble de conditions pour afficher le chiffre 0*
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






/************** Fonction de test*****************
void test_affichage(void) {
// initialise la matrice et l'affiche avec le top
	gp4_init();
	gp4_show_board();
}

void test_mouvement(void) {
// affiche le top + mvt dte + affiche + chgmt joueur + mvt gche + affiche + mvt gche + affiche + mvt gche + affiche
	gp4_init();
	gp4_show_board();
	gp4_move_left_test();
	gp4_show_board();
	gp4_move_left_test();
	gp4_show_board();
	gp4_move_left_test();
	gp4_show_board();

}

void test_validation_jeton(void) {
// initialise la matrice et l'affiche avec le top + succession de mvt
	gp4_init();
	gp4_show_board();
	gp4_move_right_test();
	gp4_play_token();
	gp4_show_board();
	gp4_next_player();
	gp4_move_left_test();
	gp4_move_left_test();
	gp4_play_token();
	gp4_show_board();
}
*/