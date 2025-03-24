/*
 * hw_hal_relay.h
 *
 *  Created on: Mar 17, 2025
 *      Author: GAOTIANHAO
 */

#ifndef HAL_INC_HW_HAL_RELAY_H_
#define HAL_INC_HW_HAL_RELAY_H_

#include "main.h"
#include "portmacro.h"


#ifdef __cpp_concepts
template <typename T>
concept RelayInterfaceConcept = requires(T t, bool state) {
  { t.on() } -> std::same_as<void>;
  { t.off() } -> std::same_as<void>;
  { t.getState() } -> std::convertible_to<bool>;
};
#endif


#endif /* HAL_INC_HW_HAL_RELAY_H_ */
