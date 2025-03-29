/*
 * stm32_callback.cpp
 *
 *  Created on: Mar 22, 2025
 *      Author: GAOTIANHAO
 */


#include"hw_port_adc.h"
#include"hw_port_message.h"
#include "tim.h"
#include "SEGGER_SYSVIEW_Conf.h"
#include "SEGGER_SYSVIEW.h"

extern Hardware_STM32_Message g_message_handler;
extern Hardware_STM32_ADC g_adc1_handler;
extern Hardware_STM32_Message g_message_handler;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  g_adc1_handler.dmaCallbackHandler(hadc);
}

void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  g_adc1_handler.iTCallbackHandler(hadc);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  g_message_handler.callbackHandler(huart, Size);
}

void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim)
{
  if(htim == &htim1)
    {
      SEGGER_SYSVIEW_RecordEnterISR();
      g_message_handler.processHandler();
      SEGGER_SYSVIEW_RecordExitISR();
    }

}
