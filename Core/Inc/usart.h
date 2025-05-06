/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */
#define USART_BUFFER_SIZE 256
    typedef struct USARTData
    {
        UART_HandleTypeDef* huart;
        uint8_t sendBuf[USART_BUFFER_SIZE];
        uint8_t recvBuf[USART_BUFFER_SIZE];
        uint16_t sendLen;
        uint16_t recvLen;
    } USARTData;
#define USE_USART1_NORMAL 1
    extern USARTData usart1Data;
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */
    void USART1_Printf(const char* format, ...);

#ifdef DEBUG
#define LOG_D(__restrict__,...) USART1_Printf(__restrict__,##__VA_ARGS__)
#else
#define LOG_D(__restrict__,...)
#endif
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

