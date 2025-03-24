/*
 * hw_port_relay.h
 *
 *  Created on: Mar 18, 2025
 *      Author: GAOTIANHAO
 */

#ifndef PORT_INC_HW_PORT_RELAY_H_
#define PORT_INC_HW_PORT_RELAY_H_

#include "hw_hal_relay.h"

class Hardware_STM32_Relay
{
public:
  void begin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin ,uint8_t active_level) {
    if (GPIOx == nullptr) {
	return;
    }
    GPIOx_ = GPIOx;
    GPIO_Pin_ = GPIO_Pin;
    active_level_=active_level;
  }
  void on() {
    if (GPIOx_ == nullptr) {
	return;
    }
    GPIO_PinState state=((active_level_)==0)?GPIO_PIN_RESET:GPIO_PIN_SET;
    HAL_GPIO_WritePin(GPIOx_, GPIO_Pin_, state);
    state_=true;
  }
  void off() {
    if (GPIOx_ == nullptr) {
	return;
    }
    GPIO_PinState state=((active_level_)==0)?GPIO_PIN_SET:GPIO_PIN_RESET;
    HAL_GPIO_WritePin(GPIOx_, GPIO_Pin_, state);
    state_=false;
  }
  bool getState() {
    if (GPIOx_ == nullptr) {
	return false;
    }
    return state_;
  }
private:
  GPIO_TypeDef *GPIOx_;
  uint16_t GPIO_Pin_;
  uint8_t active_level_;
  bool state_;
};


#endif /* PORT_INC_HW_PORT_RELAY_H_ */
