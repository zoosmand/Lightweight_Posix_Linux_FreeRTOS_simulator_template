/**
  ******************************************************************************
  * @file           : services.h
  * @brief          : Header for services.c file.
  *                   This file contains the common defines of the services.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __SERVICES_H
#define __SERVICES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Local includes ------------------------------------------------------------*/
#include "main.h"

/* Priorities at which the tasks are created. */
#define RECEIVER_PRIO	                  (tskIDLE_PRIORITY + 2)
#define	TASK_SENDER_PRIO		            (tskIDLE_PRIORITY + 1)

/* Stack sizes which tasks obtaine */
#define RECEIVER_STACK_SIZE             configMINIMAL_STACK_SIZE
#define TASK_SENDER_STACK_SIZE          configMINIMAL_STACK_SIZE

/* The rate at which data is sent to the queue.  The times are converted from
milliseconds to ticks using the pdMS_TO_TICKS() macro. */
#define TASK_SENDER_FREQ			          pdMS_TO_TICKS(200UL)
#define TIMER_SENDER_FREQ               pdMS_TO_TICKS(2000UL)

/* The number of items the queue can hold at once. */
#define QUEUE_LENGTH					          2

/* The values sent to the queue receive task from the queue send task and the
queue send software timer respectively. */
#define TASK_SENDER_VAL			            100UL
#define TIMER_SENDER_VAL			          200UL


/* Exported functions prototypes ---------------------------------------------*/
void srvConsoleMessenger(void);


/*----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif /* __SERVICES_H */
