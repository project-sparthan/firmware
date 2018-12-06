/**
  ******************************************************************************
  * File Name          : USART.h
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */
#include "cmsis_os.h"

#define espUART               huart1
#define RX_BUFFER_LENGTH	    64
#define UART_DATA_AVAILABLE   (int32_t) 1
#define UART_RX_DATA_TYPES	  (uint8_t) 4

#define START_OF_FRAME	      (uint8_t) 0xA5

#define OFFSET_SOF	          (uint8_t) 0
#define OFFSET_DATA_LENGTH	  (uint8_t) 1
#define OFFSET_FRAME_SEQ	    (uint8_t) 3
#define OFFSET_CRC8	          (uint8_t) 4
#define OFFSET_DATA_TYPE	    (uint8_t) 5
#define OFFSET_DATA_PAC	      (uint8_t) 7

#define SIZE_FRAMEHEAD	      (uint8_t) 5
#define SIZE_FRAMEID	        (uint8_t) 2
#define SIZE_FRAMETAIL	      (uint8_t) 2

#define FRAMEID_CMD_CAL	      (uint16_t)  0x0001
#define FRAMEID_CMD_PWR	      (uint16_t)  0x0002
#define FRAMEID_CMD_POS	      (uint16_t)  0x0003
#define FRAMEID_CMD_VEL	      (uint16_t)  0x0004

#define FRAMEID_FB_CAL	      (uint16_t)  0x1001
#define FRAMEID_FB_PWR	      (uint16_t)  0x1002
#define FRAMEID_FB_POS	      (uint16_t)  0x1003
#define FRAMEID_FB_VEL	      (uint16_t)  0x1004

extern uint8_t uartRxBuffer[64];
extern uint8_t frameID;
extern osThreadId uartRxThreadHandle;

typedef struct cmdCal_t{
  float         currentThresh;
  uint8_t       fullCal;
}__attribute__((packed)) cmdCal_t;

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */

extern cmdCal_t calCmd;
extern float motorPosCmd[5];
extern float motorVelCmd[5];
extern int32_t motorPwrCmd[5];

/* USER CODE END Private defines */

extern void _Error_Handler(char *, int);

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */

/* Enable interupt when UART line is idle after RXNE event to detect end of data frame.
Use with custom UART interupt handler to restart DMA after each data frame.
Useful when incoming data frames have variable byte length. */
#define UART_DMA_STOP_AT_IDLE(huart)    SET_BIT((huart).Instance->ICR, USART_ICR_IDLECF);\
                                        SET_BIT((huart).Instance->CR1, USART_CR1_IDLEIE); 

#define UART_START_RX(huart)    HAL_UART_AbortCpltCallback(huart)

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void serialPrint(UART_HandleTypeDef *huart, char _out[]);
void uartRxThreadFunction(void const * argument);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
