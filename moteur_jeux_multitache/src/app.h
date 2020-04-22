/*
 * app.h
 *
 *  Created on: Apr 15, 2020
 *      Author: ludivineo
 */

#ifndef APP_H_
#define APP_H_

#include <stdbool.h>
#include <stdint.h>

#define COL_COUNT 7		//il y a 7 colonnes (de 1 à 7)
#define LINE_COUNT 6	//il y a 6 lignes (de 1 à 6)
#define START_POSITION 4

#define color_P1 Yellow
#define color_P2 Green


void * application(void*arg);


typedef struct {
	unsigned char RValue;
	unsigned char GValue;
	unsigned char BValue;
} Color;

extern Color Black, Red, Green, Blue, White, Purple, Yellow;

typedef enum {
	input_KEY,
	output_LED,
}cmd_t;


typedef enum {
	UP, RIGHT, DOWN, LEFT,
} dir_t;

typedef enum {
	NO_PLAYER, PLAYER_1, PLAYER_2,
} player_t;

typedef enum {
	live, //!< Need to continue game
	stop_winner, //!< game is finish and winner
	stop_equal //<! game is finish and equal
} status_t;

typedef enum {
	horiz, vert, right_diag, left_diag,
} victory_t;

typedef struct {
	int8_t l;
	int8_t c;
} point_t;

typedef struct {
	status_t status; //!< status of winner
	victory_t win_type; //<!
	player_t win_player; //<! the winner player
	point_t win_position[4]; //!< position of 4 winner token
} winner_t;

typedef struct {
	bool is_ok;
	point_t beg_position;
	point_t end_position;
} pos_token_t;

typedef struct {
	pos_token_t positions;
	Color color;
}move_token_t;


#endif /* APP_H_ */
