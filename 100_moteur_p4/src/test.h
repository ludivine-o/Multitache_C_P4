/*
 * test.h
 *
 *  Created on: Apr 6, 2020
 *      Author: ludivineo
 */

#ifndef TEST_H_
#define TEST_H_

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
PLAYER_1,
PLAYER_2
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




#endif /* TEST_H_ */
