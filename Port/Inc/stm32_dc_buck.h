/*
 * stm32_dc_buck.h
 *
 *  Created on: Mar 23, 2025
 *      Author: GAOTIANHAO
 */

#ifndef INC_STM32_DC_BUCK_H_
#define INC_STM32_DC_BUCK_H_

#include"alg_dc_buck.h"
#include "stm32_hrtim_pwm.h"
#include "stm32_adc.h"
#include "stm32_relay.h"


namespace stm32_dc_buck
{
  Algorithim_DC_Buck<Hardware_STM32_HRTIM_PWM, Hardware_STM32_ADC,
  Hardware_STM32_Relay>
  getDCBuck1(Hardware_STM32_HRTIM_PWM *pwm, Hardware_STM32_ADC *adc, Hardware_STM32_Relay *relay)
  {
    Algorithim_DC_Buck<Hardware_STM32_HRTIM_PWM, Hardware_STM32_ADC,
    Hardware_STM32_Relay>
    dc_buck;
    dc_buck.begin(pwm, 0, 0,
		  adc, relay, 0);
    return dc_buck;
  }
}
#endif /* INC_STM32_DC_BUCK_H_ */
