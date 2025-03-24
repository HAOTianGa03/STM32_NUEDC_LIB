/*
 * stm32_relay.h
 *
 *  Created on: Mar 23, 2025
 *      Author: GAOTIANHAO
 */

#ifndef INC_STM32_RELAY_H_
#define INC_STM32_RELAY_H_

#include"hw_port_relay.h"

namespace stm32_relay
{
  Hardware_STM32_Relay getRelay1()
  {
    Hardware_STM32_Relay relay;
    relay.begin(RELAY1_GPIO_Port,RELAY1_Pin,1);
    return relay;
  }
}

#endif /* INC_STM32_RELAY_H_ */
