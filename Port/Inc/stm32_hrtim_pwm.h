/*
 * stm32_hrtim_pwm.h
 *
 *  Created on: Mar 20, 2025
 *      Author: GAOTIANHAO
 */

#ifndef INC_STM32_HRTIM_PWM_H_
#define INC_STM32_HRTIM_PWM_H_

#include "hw_port_hrtim_pwm.h"

namespace stm32_hrtim_pwm
{
  Hardware_STM32_HRTIM_PWM getTimerAOutput()
  {
    Hardware_STM32_HRTIM_PWM hrtim_pwm;
    hrtim_pwm.begin(&hhrtim1, HRTIM_TIMER_A, HRTIM_COMPARE_EVENT_2);
    return hrtim_pwm;
  }
}



#endif /* INC_STM32_HRTIM_PWM_H_ */
