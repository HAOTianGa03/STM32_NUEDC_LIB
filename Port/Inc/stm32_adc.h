/*
 * stm32_adc.h
 *
 *  Created on: Mar 22, 2025
 *      Author: GAOTIANHAO
 */

#ifndef INC_STM32_ADC_H_
#define INC_STM32_ADC_H_

#include "hw_port_adc.h"
#include "adc.h"

namespace stm32_adc
{
  Hardware_STM32_ADC getADC1()
  {
    Hardware_STM32_ADC adc;
    adc.begin(&hadc1, STM32_ADC_SINGLE_ENDED);
    return adc;
  }
}


#endif /* INC_STM32_ADC_H_ */
