/*
 * hw_port_pwm.h
 *
 *  Created on: Mar 18, 2025
 *      Author: GAOTIANHAO
 */

#ifndef PORT_INC_HW_PORT_PWM_H_
#define PORT_INC_HW_PORT_PWM_H_

#include "hw_hal_pwm.h"

class Hardware_STM32_PWM
{
public:
  void begin(TIM_HandleTypeDef *htim) {
    if (htim == nullptr) {
	return;
    }
    htim_ = htim;
    HAL_TIM_PWM_Start(htim_, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(htim_, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(htim_, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(htim_, TIM_CHANNEL_4);
  }

  void setDutyCycle(float duty, uint32_t channel) {
    if (htim_ == nullptr) {
	return;
    }
    switch (channel) {
      case TIM_CHANNEL_1:
	__HAL_TIM_SET_COMPARE(htim_, TIM_CHANNEL_1, duty);
	break;
      case TIM_CHANNEL_2:
	__HAL_TIM_SET_COMPARE(htim_, TIM_CHANNEL_2, duty);
	break;
      case TIM_CHANNEL_3:
	__HAL_TIM_SET_COMPARE(htim_, TIM_CHANNEL_3, duty);
	break;
      case TIM_CHANNEL_4:
	__HAL_TIM_SET_COMPARE(htim_, TIM_CHANNEL_4, duty);
	break;
      default:
	break;
    }
  }

  float getMaxFrequency() {
    if (htim_ == nullptr) {
	return 0;
    }
    return HAL_RCC_GetPCLK1Freq();
  }

  void setFrequency(float freq) {
    if (htim_ == nullptr) {
	return;
    }
    __HAL_TIM_SET_AUTORELOAD(htim_, HAL_RCC_GetPCLK1Freq() / freq);
  }
private:
  TIM_HandleTypeDef *htim_;
};
#endif /* PORT_INC_HW_PORT_PWM_H_ */
