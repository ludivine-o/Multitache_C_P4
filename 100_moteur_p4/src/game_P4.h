/*
 * game_P4.h
 *
 *  Created on: Mar 31, 2020
 *      Author: ludivineo
 */


#ifndef GAME_P4_H_
#define GAME_P4_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

/* definition de la matrice, c'est un tableau de 6 lignes et de 7 cases chacunes
 * int8_t matrix 	[7cases]
 * 					[7cases]
 * 					[7cases]
 */
#define COL_COUNT 7		//il y a 7 colonnes (de 1 à 7)
#define LINE_COUNT 6	//il y a 6 lignes (de 1 à 6)

#define PLAYER_UNKNOW 0
#define PLAYER_1 1
#define PLAYER_2 2



typedef enum {
	live, //!< Need to continue game
	stop_winner, //!< game is finish and winner
	stop_equal //<! game is finish and equal
} status_t;

typedef enum {
	horiz ,
	vert,
	right_diag,
	left_diag,
} victory_t;

typedef enum {
	NO_PLAYER,
	//PLAYER_1,
	//PLAYER_2
} player_t;

typedef struct {
	int8_t l;
	int8_t c;
} point_t;

typedef struct {
	status_t status; //!< status of winner
	victory_t win_type; //<!
	player_t win_player; //<! the winner player
	point_t win_position[4]; //!< position of 4 winner tiken
} winner_t;


typedef struct {
	bool is_ok;
	point_t beg_position;
	point_t end_position;
} pos_token_t;




#endif /* GAME_P4_H_ */


