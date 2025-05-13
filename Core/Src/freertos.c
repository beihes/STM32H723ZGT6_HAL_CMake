/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dts.h"
#include "spiLCD.h"
#include "octospi.h"
#include "rtc.h"
#include "usart.h"
#include "w25qxx.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
RTC_DateTypeDef rtcDate;
RTC_TimeTypeDef rtcTime;
uint32_t ledTaskCounter = 0; // Counter for the LED task
int32_t temperature = 0;
/* USER CODE END Variables */
/* Definitions for ledTask */
osThreadId_t ledTaskHandle;
const osThreadAttr_t ledTask_attributes = {
  .name = "ledTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal1,
};
/* Definitions for lcdTask */
osThreadId_t lcdTaskHandle;
const osThreadAttr_t lcdTask_attributes = {
  .name = "lcdTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartLED_Task(void *argument);
void StartLCD_Task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
    HAL_DTS_Start(&hdts);                                  // HAL的DTS初始化
    rtcDate = Get_Build_Date();
    rtcTime = Get_Build_TIME();
    Set_RTC_Start_Time(rtcDate, rtcTime);
    if (OSPI1_W25Qxx_Init() == OSPI_W25Qxx_OK) {
        if (OSPI1_W25Qxx_Test() != OSPI_W25Qxx_OK) {
            USART1_Printf("w25qxx测试不通过\r\n");
        }
    }
    SPI_LCD_Init();
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
        /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
        /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
        /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
        /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of ledTask */
  ledTaskHandle = osThreadNew(StartLED_Task, NULL, &ledTask_attributes);

  /* creation of lcdTask */
  lcdTaskHandle = osThreadNew(StartLCD_Task, NULL, &lcdTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
        /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
        /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartLED_Task */
/**
  * @brief  Function implementing the ledTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartLED_Task */
void StartLED_Task(void *argument)
{
  /* USER CODE BEGIN StartLED_Task */
        /* Infinite loop */
    for (;;) {
        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_RESET);
        osDelay(500);
        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);
        osDelay(500);
        LOG_D("LED NUM:%08X\r\n", ledTaskCounter++);
        HAL_RTC_GetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN);
        HAL_RTC_GetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN);
        HAL_DTS_GetTemperature(&hdts, &temperature);
    }
  /* USER CODE END StartLED_Task */
}

/* USER CODE BEGIN Header_StartLCD_Task */
/**
* @brief Function implementing the lcdTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLCD_Task */
void StartLCD_Task(void *argument)
{
  /* USER CODE BEGIN StartLCD_Task */
      /* Infinite loop */
    LCD_SetAsciiFont(&ASCII_Font12);
    for (;;) {
        SPILCD_Printf(10, 10, "%4d|%02d|%02d %d %02d:%02d:%02d %03d", rtcDate.Year + 2000, rtcDate.Month, rtcDate.Date, rtcDate.WeekDay, rtcTime.Hours, rtcTime.Minutes, rtcTime.Seconds, HAL_GetTick() % 1000);
        SPILCD_Printf(10, 30, "temp:%09ld", temperature);
        osDelay(1);
    }
  /* USER CODE END StartLCD_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

