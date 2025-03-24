/*
 * hw_hal_adc.h
 *
 *  Created on: Mar 17, 2025
 *      Author: GAOTIANHAO
 */

#ifndef HAL_INC_HW_HAL_ADC_H_
#define HAL_INC_HW_HAL_ADC_H_

#include "main.h"
#include "portmacro.h"


#ifdef __cpp_concepts
template <typename T>
concept ADCInterfaceConcept = requires(T t) {
  { t.readVoltage() } -> std::convertible_to<float>;
  { t.readCurrent() } -> std::convertible_to<float>;
};
#endif


#endif /* HAL_INC_HW_HAL_ADC_H_ */
