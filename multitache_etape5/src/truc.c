#include "leds_control.h"
#include <unistd.h>

/***********Structures color**************/
typedef struct {
	int RValue;
	int GValue;
	int BValue;
} Color;

Color Black = { 0, 0, 0 }, Blue = { 0, 0, 255 }, Green = { 0, 255, 0 }, Red = {
		255, 0, 0 }, White = { 255, 255, 255 }, Purple = { 255, 0, 255 },
		Yellow = { 255, 255, 0 };

static Color matrix[7][7];

///*************Fonct allumage ligne**********************/
void SetLedMatrix() {
	for (int row = 0; row < 7; row++) {
		int col = 0;
		while (col < 7) {
			setLedColor((row + 1), (col + 1), matrix[row][col].RValue,
					matrix[row][col].GValue, matrix[row][col].BValue);
			col++;
		}
	}
}

/*************Fonct matrice eteinte**********************/
void init_matrix() {
	int row, col;
	for (row = 0; row < 7; row++) {
		for (col = 0; col < 7; col++) {
			matrix[row][col] = White;
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

/*************Fonct matrice affiche figure iteration 4**********************/
void matrix_to_figure4(Color color1, Color color2, Color color3, Color color4) {
	int row, col;
	for (row = 0; row < 7; row++) {
		for (col = 0; col < 7; col++) {
			if (row == 0 || row == 6) { /*1ere et derniere ligne*/
				matrix[row][col] = color1;
			} else if (row == 1 || row == 5) { /*2eme et penultieme ligne*/
				if (col == 0 || col == 6) {
					matrix[row][col] = color1;
				} else
					matrix[row][col] = color2;
			} else if (row == 2 || row == 4) { /*3eme et antepenultieme ligne*/
				if (col == 0 || col == 6) {
					matrix[row][col] = color1;
				} else if (col == 1 || col == 5) {
					matrix[row][col] = color2;
				} else
					matrix[row][col] = color3;
			} else { /* ligne du milieu*/
				if (col == 1 || col == 5) {
					matrix[row][col] = color2;
				} else if (col == 0 || col == 6) {
					matrix[row][col] = color1;
				} else if (col == 2 || col == 4) {
					matrix[row][col] = color3;
				} else
					matrix[row][col] = color4;
			}
		}
	}
}

/*************Fonct matrice affiche 4signes**********************
 ******1 = coeur, 2 = pique, 3 = carrreau, 4= trefle**************/
void matrix_to_4signs(Color bckgrnd, Color color1, Color color2, int number) {
	int row, col;
	for (row = 0; row < 7; row++) {
		for (col = 0; col < 7; col++) {
			if (number == 1) { /*Ensemble de conditions pour afficher coeur*/
				if (row == 0) {
					if (col == 1 || col == 5) {
						matrix[row][col] = color1;
					} else
						matrix[row][col] = bckgrnd;
				} else if (row == 1) {
					if (col == 3) {
						matrix[row][col] = bckgrnd;
					} else
						matrix[row][col] = color1;
				} else if (row == 2 || row == 3) {
					matrix[row][col] = color1;
				} else if (row == 4) {
					if (col == 0 || col == 6) {
						matrix[row][col] = bckgrnd;
					} else
						matrix[row][col] = color1;
				} else if (row == 5) {
					if (col == 2 || col == 3 || col == 4) {
						matrix[row][col] = color1;
					} else
						matrix[row][col] = bckgrnd;
				} else if (row == 6) {
					if (col == 3) {
						matrix[row][col] = color1;
					} else
						matrix[row][col] = bckgrnd;
				}

			}
			if (number == 2) { /*Ensemble de conditions pour afficher pique*/
				if (row == 0) {
					if (col == 3) {
						matrix[row][col] = color2;
					} else
						matrix[row][col] = bckgrnd;
				} else if (row == 1) {
					if (col == 2 || col == 3 || col == 4) {
						matrix[row][col] = color2;
					} else
						matrix[row][col] = bckgrnd;
				} else if (row == 2) {
					if (col >= 1 && col <= 5) {
						matrix[row][col] = color2;
					} else
						matrix[row][col] = bckgrnd;
				} else if (row == 3) {
					matrix[row][col] = color2;
				} else if (row == 4) {
					if (col % 2 == 0) {
						matrix[row][col] = bckgrnd;
					} else
						matrix[row][col] = color2;
				} else if (row == 5) {
					if (col == 3) {
						matrix[row][col] = color2;
					} else
						matrix[row][col] = bckgrnd;
				} else if (row == 6) {
					if (col == 2 || col == 3 || col == 4) {
						matrix[row][col] = color2;
					} else
						matrix[row][col] = bckgrnd;
				}
			}
			if (number == 3) { /*Ensemble de conditions pour afficher carreau*/
				if (row == 0 || row == 6) {
					if (col == 3) {
						matrix[row][col] = color1;
					} else
						matrix[row][col] = bckgrnd;
				} else if (row == 1 || row == 5) {
					if (col >= 2 && col <= 4) {
						matrix[row][col] = color1;
					} else
						matrix[row][col] = bckgrnd;
				} else if (row == 2 || row == 4) {
					if (col >= 1 && col <= 5) {
						matrix[row][col] = color1;
					}
				} else if (row == 3) {
					matrix[row][col] = color1;
				} else if (row == 5) {
					if (col == 2 || col == 3 || col == 4) {
						matrix[row][col] = color1;
					} else
						matrix[row][col] = bckgrnd;
				} else if (row == 6) {
					if (col == 3) {
						matrix[row][col] = color1;
					} else
						matrix[row][col] = bckgrnd;
				}
			}
			if (number == 4) { /*Ensemble de conditions pour afficher trefle*/
				if (row == 0 || row == 1) {
					if (col >= 2 && col <= 4) {
						matrix[row][col] = color2;
					} else
						matrix[row][col] = bckgrnd;
				} else if (row == 2 || row == 4) {
					if (col == 2 || col == 4) {
						matrix[row][col] = bckgrnd;
					} else
						matrix[row][col] = color2;
				} else if (row == 3) {
					matrix[row][col] = color2;
				} else if (row == 5) {
					if (col == 3) {
						matrix[row][col] = color2;
					} else
						matrix[row][col] = bckgrnd;
				} else if (row == 6) {
					if (col == 2 || col == 3 || col == 4) {
						matrix[row][col] = color2;
					} else
						matrix[row][col] = bckgrnd;
				}
			}

		}
	}

}

/*******************************************************************Main***************************************************************/
int main(int argc, char* argv[]) {
	init_matrix();


//	matrix_to_figure4(Blue, Green, Red, Yellow);
//
//	for (int number = 1; number <=4; number ++) {
//		matrix_to_4signs(White, Red, Black, number);
//		SetLedMatrix();
//		sleep(3);
//	}


// /******Pour afficher un compte à rebours *****/
//	for (int number = 9; number >= 0; number--) {
//		matrix_to_nbr(matrix, number, Red, Black);
//		SetLedLine(matrix, 7);
//		sleep(3);
//	}

// /******Pour afficher coeur, pique, carreau, treffle *****/
//	matrix_to_4signs(matrix, White, Red, Black, 1);
//	SetLedLine(matrix, 7);


}

