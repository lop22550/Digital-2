/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RGB4_R_Pin GPIO_PIN_13
#define RGB4_R_GPIO_Port GPIOC
#define fotores1_Pin GPIO_PIN_0
#define fotores1_GPIO_Port GPIOC
#define RGB1_G_Pin GPIO_PIN_1
#define RGB1_G_GPIO_Port GPIOC
#define RGB2_G_Pin GPIO_PIN_2
#define RGB2_G_GPIO_Port GPIOC
#define fotores2_Pin GPIO_PIN_3
#define fotores2_GPIO_Port GPIOC
#define fotores3_Pin GPIO_PIN_0
#define fotores3_GPIO_Port GPIOA
#define fotores4_Pin GPIO_PIN_1
#define fotores4_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define RGB3_G_Pin GPIO_PIN_4
#define RGB3_G_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define E_Pin GPIO_PIN_6
#define E_GPIO_Port GPIOA
#define F_Pin GPIO_PIN_5
#define F_GPIO_Port GPIOC
#define G_Pin GPIO_PIN_6
#define G_GPIO_Port GPIOC
#define B_Pin GPIO_PIN_8
#define B_GPIO_Port GPIOC
#define A_Pin GPIO_PIN_9
#define A_GPIO_Port GPIOC
#define C_Pin GPIO_PIN_11
#define C_GPIO_Port GPIOA
#define D_Pin GPIO_PIN_12
#define D_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define RGB1_R_Pin GPIO_PIN_10
#define RGB1_R_GPIO_Port GPIOC
#define RGB2_R_Pin GPIO_PIN_11
#define RGB2_R_GPIO_Port GPIOC
#define RGB3_R_Pin GPIO_PIN_12
#define RGB3_R_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define RGB4_G_Pin GPIO_PIN_7
#define RGB4_G_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
