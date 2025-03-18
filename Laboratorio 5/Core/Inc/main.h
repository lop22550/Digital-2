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
#define J2_L2_Pin GPIO_PIN_1
#define J2_L2_GPIO_Port GPIOC
#define J2_L3_Pin GPIO_PIN_2
#define J2_L3_GPIO_Port GPIOC
#define J2_L4_Pin GPIO_PIN_3
#define J2_L4_GPIO_Port GPIOC
#define J1_L2_Pin GPIO_PIN_0
#define J1_L2_GPIO_Port GPIOA
#define J1_L3_Pin GPIO_PIN_1
#define J1_L3_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define J1_L4_Pin GPIO_PIN_4
#define J1_L4_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define _7seg_c_Pin GPIO_PIN_5
#define _7seg_c_GPIO_Port GPIOC
#define J2_L1_Pin GPIO_PIN_0
#define J2_L1_GPIO_Port GPIOB
#define Start_Pin GPIO_PIN_1
#define Start_GPIO_Port GPIOB
#define Start_EXTI_IRQn EXTI1_IRQn
#define _7seg_g_Pin GPIO_PIN_2
#define _7seg_g_GPIO_Port GPIOB
#define _7seg_f_Pin GPIO_PIN_12
#define _7seg_f_GPIO_Port GPIOB
#define J1_Pin GPIO_PIN_14
#define J1_GPIO_Port GPIOB
#define J1_EXTI_IRQn EXTI15_10_IRQn
#define _7seg_b_Pin GPIO_PIN_6
#define _7seg_b_GPIO_Port GPIOC
#define _7seg_a_Pin GPIO_PIN_8
#define _7seg_a_GPIO_Port GPIOC
#define _7seg_e_Pin GPIO_PIN_11
#define _7seg_e_GPIO_Port GPIOA
#define _7seg_d_Pin GPIO_PIN_12
#define _7seg_d_GPIO_Port GPIOA
#define J2_Pin GPIO_PIN_15
#define J2_GPIO_Port GPIOA
#define J2_EXTI_IRQn EXTI15_10_IRQn
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define J1_L1_Pin GPIO_PIN_7
#define J1_L1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
