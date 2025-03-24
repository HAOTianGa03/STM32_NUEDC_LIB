/*
 * stm32_callback.cpp
 *
 *  Created on: Mar 22, 2025
 *      Author: GAOTIANHAO
 */


#include"hw_port_adc.h"
#include"hw_port_message.h"


extern Hardware_STM32_Message g_message_handler;
extern Hardware_STM32_ADC g_adc1_handler;

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
