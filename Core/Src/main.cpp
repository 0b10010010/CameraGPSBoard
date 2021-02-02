/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
//#include <RingBuffer.h>
#include "main.h"
extern "C" {
//#include "dma.h"
#include "gpio.h"
#include "usart.h"
#include "ublox_gps.h"
#include "CircularBuffer.h"
}
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
/* USER CODE BEGIN PV */
struct _commBuffer_t rxBuffer; // max buffer size is defined in CircularBuffer.h

uint8_t c = {0};

char buffer[101]; // size of the entire nav_pvt message (100 bytes)

unsigned short imgIndex = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void sendGPSData(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin); // uses pin A1 (PA1)
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void sendGPSData() // takes about 14050 cycles -> 14050/80MHz = 0.000175625 sec
{
	imgIndex++;
	// prepare the string with GPS data to send via USB
	snprintf(buffer, 101, "Image index:%i,Date:%i/%i/%i %i:%i:%i.%liLat:%li.%li,Lon:%li.%li\n\r", imgIndex, ubxMessage.pvt.year, ubxMessage.pvt.month, ubxMessage.pvt.day, ubxMessage.pvt.hour,ubxMessage.pvt.minute, ubxMessage.pvt.second, ubxMessage.pvt.nano, ubxMessage.pvt.lat/10000000, ubxMessage.pvt.lat%10000000, ubxMessage.pvt.lon/10000000, ubxMessage.pvt.lon%10000000);
	HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

int main(void)
{
  /* USER CODE BEGIN 1 */
// uncomment below to time cycles
//	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
//	DWT->CYCCNT = 0;
//	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

//	unsigned long t1 = DWT->CYCCNT;
/* Do something */
//	unsigned long t2 = DWT->CYCCNT;
//	unsigned long diff = t2 - t1;
//	snprintf(buffer, 101, "%li\n\r", diff);
//	HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  initBuffer(&rxBuffer, CIRCULAR_RX);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init(); // Camera Hotshoe interrupt pin
//  MX_DMA_Init();  // GPS receive DMA init.
  MX_USART1_UART_Init(); // GPS receive init. Read bytes in IT
  MX_USART2_UART_Init(); // ST-Link (USB) Init. Used for transferring last GPS data when Camera Hotshoe interrupts

  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);

  HAL_UART_Receive_IT(&huart1, &c, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	readGPS(&rxBuffer);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage 
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == GPIO_PIN_1)
  {
    sendGPSData();
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) // takes about 360 cycles -> 360/80Mhz = 0.0000045 sec
{
  if (huart->Instance == USART1)
  {
	  putChar(&rxBuffer, c);
	  HAL_UART_Receive_IT(&huart1, &c, 1);
  }
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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
