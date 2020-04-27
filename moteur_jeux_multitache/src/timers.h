/*
 * timers.h
 *
 *  Created on: Apr 22, 2020
 *      Author: ludivineo
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include <stdint.h>
#define TIMER_MAX 4


typedef enum {
	ROUND_TIMER,
	IDLE_TIMER,
}TimerId;


typedef enum {
	STOP = 2,
	START = 3,
}Status;

typedef enum {
	Thrd_APP,
	Thrd_DISPLAY,
}Owner;

typedef struct {
	Status status;
	int8_t countdown;
	Owner owner;
}Timer;


void start_timer (int8_t timer_id, int8_t intcountdown, Owner owner);
void stop_timer (int8_t timer_id);
void *timers(void*arg);






#endif /* TIMERS_H_ */
