/*
 * thread.c
 *
 *  Created on: Apr 24, 2020
 *      Author: ludivineo
 */

#include "local_leds.h"
#include "cmsis_os2.h"
#include "local_button.h"
#include "send_to_serial.h"

extern osSemaphoreId_t sem_thread_led;
extern osMessageQueueId_t sendToLog;

void thread_red_led(void * arg) {
	while (1) {
		LedRedOn();
		osDelay(400);
		LedRedOff();
		osDelay(400);

	}
}

void thread_blue_led(void*arg) {
	while (1) {
		WaitForLocalButtonReleased();
		for (int i = 0; i < 5; i++) {
			LedBlueOn();
			osDelay(100);
			LedBlueOff();
			osDelay(100);
		}
		osSemaphoreRelease(sem_thread_led);
	}
}

void thread_green_led(void*arg) {
	while (1) {
		char msg [12] = "Hello World";
		osSemaphoreAcquire(sem_thread_led, osWaitForever);
		for (int i = 0; i < 5; i++) {
			LedGreenOn();
			osDelay(100);
			LedGreenOff();
			osDelay(100);
		}
		osMessageQueuePut(sendToLog, &msg, 0, osWaitForever);
	}
}

void thread_logger(void*arg) {
	char msg [12];
	while(1){
		osMessageQueueGet(sendToLog, &msg, NULL, osWaitForever);
		sendToSerial(msg,sizeof(msg));
	}
}

