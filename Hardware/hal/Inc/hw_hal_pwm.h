/*
 * hw_hal_pwm.h
 *
 *  Created on: Mar 17, 2025
 *      Author: GAOTIANHAO
 */

#ifndef HAL_INC_HW_HAL_PWM_H_
#define HAL_INC_HW_HAL_PWM_H_

#include "main.h"
#include "portmacro.h"


#ifdef __cpp_concepts
template <typename T>
concept PWMInterfaceConcept = requires(T t, float duty, float freq) {
  { t.setDutyCycle(duty) } -> std::same_as<void>;
  { t.getMaxFrequency() } -> std::convertible_to<float>;
  { t.setFrequency(freq) } -> std::same_as<void>;
};
#endif

#endif /* HAL_INC_HW_HAL_PWM_H_ */
