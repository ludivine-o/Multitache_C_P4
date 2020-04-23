/*
*****************************************************************************

  File        : main.cpp

  The MIT License (MIT)
  Copyright (c) 2019 STMicroelectronics

******************************************************************************/
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#include "__debug.h"
#include"__leds_control.h"
#include"fifo.h"
#include"read.h"
#include"app.h"
#include"display.h"
#include"timers.h"


int main(void){

	init_list(&liste_read);//declaration et init de la liste de lecture
	init_list(&liste_display);	//declaration et init de la liste d'envoi


	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;

	openLink();
	pthread_create(&thread1, NULL, read_button, NULL);
	debug_pr_fn(1,"main()creation thread read\n");
	pthread_create(&thread2, NULL, application, NULL);
	debug_pr_fn(1,"main()creation thread app\n");
	pthread_create(&thread3, NULL, display, NULL);
	debug_pr_fn(1,"main()creation thread display\n");
	pthread_create(&thread4, NULL, timers, NULL);
	debug_pr_fn(1,"main()creation thread timers\n");
	pthread_join (thread1, NULL);
	pthread_join (thread2, NULL);
	pthread_join (thread3, NULL);
	pthread_join (thread4, NULL);
	closeLink();


	return 0;
}


