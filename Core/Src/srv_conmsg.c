/**
  ******************************************************************************
  * File Name          : services.c
  * Description        : This file provides code for the services
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "services.h"

/* Private variables ---------------------------------------------------------*/
static QueueHandle_t xQueue = NULL;
static TimerHandle_t xTimer = NULL;

/* Function prototypes -------------------------------------------------------*/
static void prvReceiveMessage(void *pvParameters);
static void prvSendMessage(void *pvParameters);
static void prvSendTimerMessage(TimerHandle_t xTimerHandle);





/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/**
  * @brief  Defines Console Messenger servies.
  * @return None
  */
void srvConsoleMessenger(void) {
  xQueue = xQueueCreate(QUEUE_LENGTH, sizeof(uint32_t));

  if(xQueue != NULL) {
    xTaskCreate(prvReceiveMessage, "ReceiveMessage", RECEIVER_STACK_SIZE, NULL, RECEIVER_PRIO, NULL);
    xTaskCreate(prvSendMessage, "SendMessage", TASK_SENDER_STACK_SIZE, NULL, TASK_SENDER_PRIO, NULL);

    xTimer = xTimerCreate("Timer", TIMER_SENDER_FREQ, pdTRUE, NULL, prvSendTimerMessage);

    if(xTimer != NULL) {
      xTimerStart( xTimer, 0 );
    }
  }
}


/**
  * @brief  Handles sending messages from a task.
  * @param  pvParameters: Link to FreeRTOS parameters
  * @return None
  */
static void prvSendMessage(void *pvParameters) {
  TickType_t xNextWakeTime;
  const uint32_t ulValueToSend = TASK_SENDER_VAL;

  (void) pvParameters;

  xNextWakeTime = xTaskGetTickCount();

  while (1) {
    vTaskDelayUntil(&xNextWakeTime, TASK_SENDER_FREQ);
    xQueueSend(xQueue, &ulValueToSend, 0U);
  }
}


/**
  * @brief  Handles sending messages from a times.
  * @param  pvParameters: Link to FreeRTOS parameters
  * @return None
  */
static void prvSendTimerMessage(TimerHandle_t xTimerHandle) {
  const uint32_t ulValueToSend = TIMER_SENDER_VAL;
  (void) xTimerHandle;

  xQueueSend(xQueue, &ulValueToSend, 0U);
}


/**
  * @brief  Handles receiving messages from a queue.
  * @param  pvParameters: Link to FreeRTOS parameters
  * @return None
  */
static void prvReceiveMessage(void *pvParameters) {
  uint32_t ulReceivedValue;

  (void) pvParameters;

  while (1) {
    xQueueReceive( xQueue, &ulReceivedValue, portMAX_DELAY );
    
    switch (ulReceivedValue) {
      case TASK_SENDER_VAL:
        vConsolePrint( "Message received from task\n" );
        break;

      case TIMER_SENDER_VAL:
        vConsolePrint( "Message received from software timer\n" );
        break;

      default:
        vConsolePrint( "Unexpected message\n" );
        break;
    }
  }
}
