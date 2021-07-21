/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Standard includes ---------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <pthread.h>

/* FreeRTOS kernel includes --------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "list.h"
#include "timers.h"
#include "semphr.h"
#include "queue.h"

/* Local includes ------------------------------------------------------------*/
#include "freertos.h"
#include "console.h"
#include "services.h"





/*----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
