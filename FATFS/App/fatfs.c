/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
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
#include "fatfs.h"

uint8_t retUSER;    /* Return value for USER */
char USERPath[4];   /* USER logical drive path */
FATFS USERFatFS;    /* File system object for USER logical drive */
FIL USERFile;       /* File object for USER */

/* USER CODE BEGIN Variables */
BYTE work[_MAX_SS];
UINT fnum;
BYTE WriteBuffer[] = "hello world  你好!!";
/* USER CODE END Variables */

void MX_FATFS_Init(void)
{
  /*## FatFS: Link the USER driver ###########################*/
  retUSER = FATFS_LinkDriver(&USER_Driver, USERPath);

  /* USER CODE BEGIN Init */
    /* additional user code for init */
    /* USER CODE BEGIN Init */
    // retUSER = f_mount(&USERFatFS, "", 1);


    // if (retUSER == FR_NO_FILESYSTEM) {
    //     USART1_Printf("FLASH is not formatted\r\n");

    //     retUSER = f_mkfs("", FM_ANY, 0, work, sizeof work);

    //     if (retUSER == FR_OK) {
    //         USART1_Printf("The FLASH formats the file system successfully\r\n");

    //         retUSER = f_mount(NULL, "", 1);

    //         retUSER = f_mount(&USERFatFS, "", 1);
    //     }
    //     else {
    //         USART1_Printf("Formatting failure\r\n");
    //         while (1);
    //     }
    // }
    // else if (retUSER != FR_OK) {
    //     USART1_Printf("The external Flash failed to mount the file system. Procedure (%d)\r\n", retUSER);
    //     USART1_Printf("Possible cause: The SPI Flash initialization fails\r\n");
    //     while (1);
    // }
    // else {
    //     USART1_Printf("The file system is mounted successfully, and you can perform read/write tests\r\n");
    // }
    // /*----------------------- 文件系统测试：写测试 -----------------------------*/
    //     /* 打开文件，如果文件不存在则创建它 */
    // USART1_Printf("\r\n****** 即将进行文件写入测试... ******\r\n");
    // retUSER = f_open(&USERFile, "0:FatUSERFatFS读写测试文件.txt", FA_CREATE_ALWAYS | FA_WRITE);
    // if (retUSER == FR_OK) {
    //     USART1_Printf("》打开/创建FatUSERFatFS读写测试文件.txt文件成功，向文件写入数据。\r\n");
    //     /* 将指定存储区内容写入到文件内 */
    //     retUSER = f_write(&USERFile, WriteBuffer, sizeof(WriteBuffer), &fnum);
    //     if (retUSER == FR_OK) {
    //         USART1_Printf("》文件写入成功，写入字节数据：%d\n", fnum);
    //         USART1_Printf("》向文件写入的数据为：\r\n%s\r\n", WriteBuffer);
    //     }
    //     else {
    //         USART1_Printf("！！文件写入失败：(%d)\n", retUSER);
    //     }
    //     /* 不再读写，关闭文件 */
    //     f_close(&USERFile);
    // }
    // else {
    //     printf("！！打开/创建文件失败。\r\n");
    // }

    // USART1_Printf("****** 即将进行文件读取测试... ******\r\n");
    // retUSER = f_open(&USERFile, "FatUSERFatFS读写测试文件.txt", FA_OPEN_EXISTING | FA_READ);
    // if (retUSER == FR_OK) {
    //     USART1_Printf("》打开文件成功。\r\n");
    //     retUSER = f_read(&USERFile, work, sizeof(work), &fnum);
    //     if (retUSER == FR_OK) {
    //         USART1_Printf("》文件读取成功,读到字节数据：%d\r\n", fnum);
    //         USART1_Printf("》读取得的文件数据为：\r\n%s \r\n", work);
    //     }
    //     else {
    //         USART1_Printf("！！文件读取失败：(%d)\n", retUSER);
    //     }
    // }
    // else {
    //     USART1_Printf("！！打开文件失败。\r\n");
    // }
    // /* 不再读写，关闭文件 */
    // f_close(&USERFile);
  /* USER CODE END Init */
}

/**
  * @brief  Gets Time from RTC
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
  /* USER CODE BEGIN get_fattime */
    return 0;
  /* USER CODE END get_fattime */
}

/* USER CODE BEGIN Application */

/* USER CODE END Application */
