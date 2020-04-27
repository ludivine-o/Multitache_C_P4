/*
 * thread.h
 *
 *  Created on: Apr 24, 2020
 *      Author: ludivineo
 */

#ifndef INC_THREAD_H_
#define INC_THREAD_H_

void thread_red_led (void * arg);
void thread_blue_led (void*arg);
void thread_green_led (void*arg);
void thread_logger(void*arg);

#endif /* INC_THREAD_H_ */
