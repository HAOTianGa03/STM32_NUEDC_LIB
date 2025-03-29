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
#include "adc.h"
#include "dma.h"
#include "hrtim.h"
#include "usart.h"
#include "gpio.h"
#include "tim.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32_hrtim_pwm.h"
#include "stm32_adc.h"
#include "stm32_dc_buck.h"
#include "stm32_relay.h"
#include "stm32_test.h"
#include "stm32_message.h"
#include "SEGGER_SYSVIEW.h"
#include "SEGGER_SYSVIEW_Conf.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
Hardware_STM32_HRTIM_PWM g_hrtimerA_pwm_handler;
Hardware_STM32_ADC g_adc1_handler;
Hardware_STM32_Relay g_relay1_handler;
Hardware_STM32_Message g_message_handler;
Algorithim_DC_Buck<Hardware_STM32_HRTIM_PWM, Hardware_STM32_ADC,Hardware_STM32_Relay>g_dc_buck_handler;
Algorithim_PID g_voltage_pid;
Algorithim_PID g_current_pid;


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
volatile unsigned int _TestFunc0Cnt;
volatile unsigned int _TestFunc1Cnt;


/*********************************************************************
 *
 *       Local functions
 *
 **********************************************************************
 */

/*********************************************************************
 *
 *       _TestFunc1()
 *
 *  Function description
 *    Simple dummy function.
 */
static void _TestFunc1(void) {
  SEGGER_SYSVIEW_RecordVoid(34);
  _TestFunc1Cnt = 100;
  do {
      _TestFunc1Cnt--;
  } while (_TestFunc1Cnt);
  SEGGER_SYSVIEW_RecordEndCall(34);
}

/*********************************************************************
 *
 *       _TestFunc0()
 *
 *  Function description
 *    Simple dummy calling _TestFunc1()
 */
static void _TestFunc0(void) {
  SEGGER_SYSVIEW_RecordVoid(33);
  _TestFunc0Cnt = 100;
  while(50 < --_TestFunc0Cnt);
  _TestFunc1();
  while(--_TestFunc0Cnt);
  SEGGER_SYSVIEW_RecordEndCall(33);
}
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_HRTIM1_Init();
  MX_USART1_UART_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_TIM1_Init();

  /* USER CODE BEGIN 2 */
  SEGGER_SYSVIEW_Conf();            /* Configure and initialize SystemView  */
  SEGGER_SYSVIEW_Start();           /* Starts SystemView recording*/
  SEGGER_SYSVIEW_OnIdle();          /* Tells SystemView that System is currently in "Idle"*/
  //定时事件处理
  //  HAL_TIM_Base_Start_IT(&htim1);
  //串口抽象层初始化
  g_message_handler=stm32_message::getUART1();
  g_message_handler.startReceive();

  //高级定时器抽象层初始化
  g_hrtimerA_pwm_handler=stm32_hrtim_pwm::getTimerAOutput();
  g_hrtimerA_pwm_handler.setOutput();
  g_hrtimerA_pwm_handler.setDutyCycle(0.3);

  //ADC抽象层初始化
  g_adc1_handler=stm32_adc::getADC1();
  g_adc1_handler.startSample();
  __HAL_DMA_DISABLE_IT(&hdma_adc1, DMA_IT_HT);
  //  //继电器抽象层初始化
  g_relay1_handler=stm32_relay::getRelay1();

  //算法抽象层初始化
  //  g_dc_buck_handler=stm32_dc_buck::getDCBuck1(&g_hrtimerA_pwm_handler,&g_adc1_handler,&g_relay1_handler);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
    {
      /* USER CODE END WHILE */
      //      _TestFunc0();
      //      stm32_test::dc_dc_doubleMode_closedLoop_test();
      stm32_test::dc_dc_doubleMode_closedLoop_test();
      stm32_test::vofa_send_test();

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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 75;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    {
      Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

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
