/*
 * stm32_message_handler.h
 *
 *  Created on: Mar 23, 2025
 *      Author: GAOTIANHAO
 */

#ifndef INC_STM32_MESSAGE_H_
#define INC_STM32_MESSAGE_H_

#include "hw_port_message.h"
#include "stdio.h"
#include "string.h"


namespace stm32_message
{
  Hardware_STM32_Message getUART1()
  {
    Hardware_STM32_Message message;
    message.begin(2, 20, &huart1);
    return message;
  }
}


#endif /* INC_STM32_MESSAGE_H_ */
