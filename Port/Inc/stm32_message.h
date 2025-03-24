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

  void vofaReceiveCallback(uint8_t *data,uint16_t len)
  {
    float temp;
    char s[20];
    memcpy(s,data,len);
    s[len]='\0';
    if (sscanf(s, "VP=%f", &temp) >0)
      {
	printf("VP: %f\n", temp);
      }
    else if (sscanf(s, "VI=%f", &temp) >0)
      {
	printf("VI: %f\n", temp);
      }
    else if (sscanf(s, "VD=%f", &temp) >0)
      {
	printf("VD: %f\n", temp);
      }
    else if (sscanf(s, "CP=%f", &temp) >0)
      {
	printf("CP: %f\n", temp);
      }
    else if (sscanf(s, "CI=%f", &temp) >0)
      {
	printf("CI: %f\n", temp);
      }
    else if (sscanf(s, "CD=%f", &temp) >0)
      {
	printf("CD: %f\n", temp);
      }
    else if (sscanf(s, "V=%f", &temp)>0)
      {
	printf("V: %f\n", temp);
      }
    else if (sscanf(s, "D=%f", &temp)>0)
      {
	printf("D: %f\n", temp);
      }
    else if (sscanf(s, "VL=%f", &temp)>0)
      {
	printf("VL: %f\n", temp);
      }
    else if (sscanf(s, "CL=%f", &temp) >0)
      {
	printf("CL: %f\n", temp);
      }
    else if (sscanf(s, "MODE=%f", &temp) >0)
        {
  	printf("CL: %f\n", temp);
        }
    else if (strcmp (s, "RESET") == 0)
      {
	printf("RESET\n");
	HAL_NVIC_SystemReset();
      }
    else if (strcmp (s, "CLEAR") == 0)
      {
	printf("CLEAR\n");
      }
  }
}


#endif /* INC_STM32_MESSAGE_H_ */
