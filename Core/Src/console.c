/**
  ******************************************************************************
  * File Name          : console.c
  * Description        : This file provides code for console output
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "console.h"

/* Private variables ---------------------------------------------------------*/
static SemaphoreHandle_t xStdioMutex;
static StaticSemaphore_t xStdioMutexBuffer;





/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/**
  * @brief  Initialize console.
  * @return None
  */
void vConsoleInit(void) {
    xStdioMutex = xSemaphoreCreateMutexStatic(&xStdioMutexBuffer);
}


/**
  * @brief  Prints message to console.
  * @param  fmt: Buffer contains text od data to be printed
  * @return None
  */
void vConsolePrint(const char *fmt, ...) {
    va_list vargs;

    va_start(vargs, fmt);
    
    xSemaphoreTake(xStdioMutex, portMAX_DELAY);

    vprintf(fmt, vargs);

    xSemaphoreGive(xStdioMutex);

    va_end(vargs);
}


/**
  * @brief  Prints log message to console.
  * @param  fmt: Formatted buffer contains text od data to be printed
  * @return None
  */
void vLoggingPrintf(const char *pcFormat, ...) {
  va_list arg;

  va_start( arg, pcFormat );
  vprintf( pcFormat, arg );
  va_end( arg );
}
