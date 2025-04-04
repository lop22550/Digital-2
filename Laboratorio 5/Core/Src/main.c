/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint16_t estado = 0;        // Variable para guardar estado del juego.
uint16_t contador_J1 = 0;   //
uint16_t contador_J2 = 0;
uint16_t Ganador_J1 = 0;       //Guarda un número para indicar el ganador.
uint16_t Ganador_J2 = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  //HAL_GPIO_WritePin(J1_L1_GPIO_Port, J1_L1_Pin, SET);
  while (1)
  {

	  refreshPort();
	  Ganador_indicador();
	  _7seg_output();



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, J2_L2_Pin|J2_L3_Pin|J2_L4_Pin|_7seg_g_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, J1_L2_Pin|J1_L3_Pin|J1_L4_Pin|_7seg_c_Pin
                          |_7seg_d_Pin|_7seg_e_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, J2_L1_Pin|_7seg_f_Pin|J1_L1_Pin|_7seg_a_Pin
                          |_7seg_b_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : J2_L2_Pin J2_L3_Pin J2_L4_Pin _7seg_g_Pin */
  GPIO_InitStruct.Pin = J2_L2_Pin|J2_L3_Pin|J2_L4_Pin|_7seg_g_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : J1_L2_Pin J1_L3_Pin J1_L4_Pin _7seg_c_Pin
                           _7seg_d_Pin _7seg_e_Pin */
  GPIO_InitStruct.Pin = J1_L2_Pin|J1_L3_Pin|J1_L4_Pin|_7seg_c_Pin
                          |_7seg_d_Pin|_7seg_e_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : J2_L1_Pin _7seg_f_Pin J1_L1_Pin _7seg_a_Pin
                           _7seg_b_Pin */
  GPIO_InitStruct.Pin = J2_L1_Pin|_7seg_f_Pin|J1_L1_Pin|_7seg_a_Pin
                          |_7seg_b_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Start_Pin J1_Pin */
  GPIO_InitStruct.Pin = Start_Pin|J1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : J2_Pin */
  GPIO_InitStruct.Pin = J2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(J2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	if(GPIO_Pin == Start_Pin){
				estado++;
				if (estado > 1 ){estado = 0; Ganador_J1 = 0; Ganador_J2 = 0;}
			}
	if(GPIO_Pin == J1_Pin){
		if (estado == 1){
		contador_J1++;
		if (contador_J1 >4){contador_J1 = 0; contador_J2 = 0; estado = 0;}
		}
	}

	if(GPIO_Pin == J2_Pin){
		if (estado == 1){
			contador_J2++;
			if (contador_J2 >4){contador_J1 = 0; contador_J2 = 0; estado = 0;}
		}
	}


}

void refreshPort(void){
	//if (contador == contador_J1){

	switch (contador_J1){
	case 1:
		HAL_GPIO_WritePin(J1_L1_GPIO_Port, J1_L1_Pin, SET);
		HAL_GPIO_WritePin(J1_L2_GPIO_Port, J1_L2_Pin, RESET);
		HAL_GPIO_WritePin(J1_L3_GPIO_Port, J1_L3_Pin, RESET);
		HAL_GPIO_WritePin(J1_L4_GPIO_Port, J1_L4_Pin, RESET);
		break;
	case 2:
		HAL_GPIO_WritePin(J1_L1_GPIO_Port, J1_L1_Pin, SET);
		HAL_GPIO_WritePin(J1_L2_GPIO_Port, J1_L2_Pin, SET);
    	HAL_GPIO_WritePin(J1_L3_GPIO_Port, J1_L3_Pin, RESET);
    	HAL_GPIO_WritePin(J1_L4_GPIO_Port, J1_L4_Pin, RESET);
    	break;
	case 3:
		HAL_GPIO_WritePin(J1_L1_GPIO_Port, J1_L1_Pin, SET);
		HAL_GPIO_WritePin(J1_L2_GPIO_Port, J1_L2_Pin, SET);
		HAL_GPIO_WritePin(J1_L3_GPIO_Port, J1_L3_Pin, SET);
		HAL_GPIO_WritePin(J1_L4_GPIO_Port, J1_L4_Pin, RESET);
		break;
	case 4:
		HAL_GPIO_WritePin(J1_L1_GPIO_Port, J1_L1_Pin, SET);
		HAL_GPIO_WritePin(J1_L2_GPIO_Port, J1_L2_Pin, SET);
		HAL_GPIO_WritePin(J1_L3_GPIO_Port, J1_L3_Pin, SET);
		HAL_GPIO_WritePin(J1_L4_GPIO_Port, J1_L4_Pin, SET);
		break;
	default:
		HAL_GPIO_WritePin(J1_L1_GPIO_Port, J1_L1_Pin, RESET);
		HAL_GPIO_WritePin(J1_L2_GPIO_Port, J1_L2_Pin, RESET);
		HAL_GPIO_WritePin(J1_L3_GPIO_Port, J1_L3_Pin, RESET);
		HAL_GPIO_WritePin(J1_L4_GPIO_Port, J1_L4_Pin, RESET);

	}


	switch (contador_J2){
		case 1:
			HAL_GPIO_WritePin(J2_L1_GPIO_Port, J2_L1_Pin, SET);
			HAL_GPIO_WritePin(J2_L2_GPIO_Port, J2_L2_Pin, RESET);
			HAL_GPIO_WritePin(J2_L3_GPIO_Port, J2_L3_Pin, RESET);
			HAL_GPIO_WritePin(J2_L4_GPIO_Port, J2_L4_Pin, RESET);
			break;
		case 2:
			HAL_GPIO_WritePin(J2_L1_GPIO_Port, J2_L1_Pin, SET);
			HAL_GPIO_WritePin(J2_L2_GPIO_Port, J2_L2_Pin, SET);
	    	HAL_GPIO_WritePin(J2_L3_GPIO_Port, J2_L3_Pin, RESET);
	    	HAL_GPIO_WritePin(J2_L4_GPIO_Port, J2_L4_Pin, RESET);
	    	break;
		case 3:
			HAL_GPIO_WritePin(J2_L1_GPIO_Port, J2_L1_Pin, SET);
			HAL_GPIO_WritePin(J2_L2_GPIO_Port, J2_L2_Pin, SET);
			HAL_GPIO_WritePin(J2_L3_GPIO_Port, J2_L3_Pin, SET);
			HAL_GPIO_WritePin(J2_L4_GPIO_Port, J2_L4_Pin, RESET);
			break;
		case 4:
			HAL_GPIO_WritePin(J2_L1_GPIO_Port, J2_L1_Pin, SET);
			HAL_GPIO_WritePin(J2_L2_GPIO_Port, J2_L2_Pin, SET);
			HAL_GPIO_WritePin(J2_L3_GPIO_Port, J2_L3_Pin, SET);
			HAL_GPIO_WritePin(J2_L4_GPIO_Port, J2_L4_Pin, SET);
			break;
		default:
			HAL_GPIO_WritePin(J2_L1_GPIO_Port, J2_L1_Pin, RESET);
			HAL_GPIO_WritePin(J2_L2_GPIO_Port, J2_L2_Pin, RESET);
			HAL_GPIO_WritePin(J2_L3_GPIO_Port, J2_L3_Pin, RESET);
			HAL_GPIO_WritePin(J2_L4_GPIO_Port, J2_L4_Pin, RESET);

		}



}

void _7seg_output(void){
	if(Ganador_J1 == 1){
	switch (Ganador_J1){
		case 1:
			HAL_GPIO_WritePin(_7seg_a_GPIO_Port, _7seg_a_Pin, RESET);
			HAL_GPIO_WritePin(_7seg_b_GPIO_Port, _7seg_b_Pin, SET);
			HAL_GPIO_WritePin(_7seg_c_GPIO_Port, _7seg_c_Pin, SET);
			HAL_GPIO_WritePin(_7seg_d_GPIO_Port, _7seg_d_Pin, RESET);
			HAL_GPIO_WritePin(_7seg_e_GPIO_Port, _7seg_e_Pin, RESET);
			HAL_GPIO_WritePin(_7seg_f_GPIO_Port, _7seg_f_Pin, RESET);
			HAL_GPIO_WritePin(_7seg_g_GPIO_Port, _7seg_g_Pin, RESET);
		/*case 2:
			HAL_GPIO_WritePin(_7seg_a_GPIO_Port, _7seg_a_Pin, SET);
			HAL_GPIO_WritePin(_7seg_b_GPIO_Port, _7seg_b_Pin, SET);
			HAL_GPIO_WritePin(_7seg_c_GPIO_Port, _7seg_c_Pin, RESET);
			HAL_GPIO_WritePin(_7seg_d_GPIO_Port, _7seg_d_Pin, SET);
			HAL_GPIO_WritePin(_7seg_e_GPIO_Port, _7seg_e_Pin, SET);
			HAL_GPIO_WritePin(_7seg_f_GPIO_Port, _7seg_f_Pin, RESET);
			HAL_GPIO_WritePin(_7seg_g_GPIO_Port, _7seg_g_Pin, SET);*/
		default:
			HAL_GPIO_WritePin(_7seg_a_GPIO_Port, _7seg_a_Pin, RESET);
			HAL_GPIO_WritePin(_7seg_b_GPIO_Port, _7seg_b_Pin, RESET);
			HAL_GPIO_WritePin(_7seg_c_GPIO_Port, _7seg_c_Pin, RESET);
			HAL_GPIO_WritePin(_7seg_d_GPIO_Port, _7seg_d_Pin, RESET);
			HAL_GPIO_WritePin(_7seg_e_GPIO_Port, _7seg_e_Pin, RESET);
			HAL_GPIO_WritePin(_7seg_f_GPIO_Port, _7seg_f_Pin, RESET);
			HAL_GPIO_WritePin(_7seg_g_GPIO_Port, _7seg_g_Pin, RESET);
	} //Fin del switch case
	}//Fin del if

	if(Ganador_J2 == 2){
		switch (Ganador_J2){
			/*case 1:
				HAL_GPIO_WritePin(_7seg_a_GPIO_Port, _7seg_a_Pin, RESET);
				HAL_GPIO_WritePin(_7seg_b_GPIO_Port, _7seg_b_Pin, SET);
				HAL_GPIO_WritePin(_7seg_c_GPIO_Port, _7seg_c_Pin, SET);
				HAL_GPIO_WritePin(_7seg_d_GPIO_Port, _7seg_d_Pin, RESET);
				HAL_GPIO_WritePin(_7seg_e_GPIO_Port, _7seg_e_Pin, RESET);
				HAL_GPIO_WritePin(_7seg_f_GPIO_Port, _7seg_f_Pin, RESET);
				HAL_GPIO_WritePin(_7seg_g_GPIO_Port, _7seg_g_Pin, RESET);*/
			case 2:
				HAL_GPIO_WritePin(_7seg_a_GPIO_Port, _7seg_a_Pin, SET);
				HAL_GPIO_WritePin(_7seg_b_GPIO_Port, _7seg_b_Pin, SET);
				HAL_GPIO_WritePin(_7seg_c_GPIO_Port, _7seg_c_Pin, RESET);
				HAL_GPIO_WritePin(_7seg_d_GPIO_Port, _7seg_d_Pin, SET);
				HAL_GPIO_WritePin(_7seg_e_GPIO_Port, _7seg_e_Pin, SET);
				HAL_GPIO_WritePin(_7seg_f_GPIO_Port, _7seg_f_Pin, RESET);
				HAL_GPIO_WritePin(_7seg_g_GPIO_Port, _7seg_g_Pin, SET);
			default:
				HAL_GPIO_WritePin(_7seg_a_GPIO_Port, _7seg_a_Pin, RESET);
				HAL_GPIO_WritePin(_7seg_b_GPIO_Port, _7seg_b_Pin, RESET);
				HAL_GPIO_WritePin(_7seg_c_GPIO_Port, _7seg_c_Pin, RESET);
				HAL_GPIO_WritePin(_7seg_d_GPIO_Port, _7seg_d_Pin, RESET);
				HAL_GPIO_WritePin(_7seg_e_GPIO_Port, _7seg_e_Pin, RESET);
				HAL_GPIO_WritePin(_7seg_f_GPIO_Port, _7seg_f_Pin, RESET);
				HAL_GPIO_WritePin(_7seg_g_GPIO_Port, _7seg_g_Pin, RESET);
		}//Fin del switch case
		}//Fin del if


}

void Ganador_indicador (void){
	if (contador_J1 == 4){
		Ganador_J1 = 1;
	} else {Ganador_J1 = 0;}

	if (contador_J2 == 4){
		Ganador_J2 = 2;
	} else {Ganador_J2 = 0;}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
