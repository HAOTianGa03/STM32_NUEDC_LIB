/*
 * stm32_test.h
 *
 *  Created on: Mar 23, 2025
 *      Author: GAOTIANHAO
 */

#ifndef INC_STM32_TEST_H_
#define INC_STM32_TEST_H_

#include "stm32_dc_buck.h"
#include "stm32_message.h"

extern Hardware_STM32_HRTIM_PWM g_hrtimerA_pwm_handler;
extern Hardware_STM32_ADC g_adc1_handler;
extern Hardware_STM32_Relay g_relay1_handler;
extern Hardware_STM32_Message g_message_handler;
extern Algorithim_DC_Buck<Hardware_STM32_HRTIM_PWM, Hardware_STM32_ADC ,Hardware_STM32_Relay>g_dc_buck_handler;
extern Algorithim_PID g_voltage_pid;
extern Algorithim_PID g_current_pid;

namespace stm32_test
{

  void adc_dma_test ()
  {
    g_adc1_handler.startSample();
    while(1)
      {
	static float voltage=0;
	static float current=0;
	voltage=g_adc1_handler.readVoltage();
	current=g_adc1_handler.readCurrent();
      }
  }

  void adc_it_test()
  {
    g_adc1_handler.startSample_IT();
    while(1)
      {
	static float voltage = 0;
	static float current = 0;
	voltage = g_adc1_handler.readVoltage_IT ();
	current = g_adc1_handler.readCurrent_IT ();
      }
  }


  void dc_dc_openLoop_test()
  {
    g_dc_buck_handler.setVin(5);
    g_dc_buck_handler.setVout(3.3);
    g_dc_buck_handler.enable();
    while (1)
      {
	g_dc_buck_handler.openVoltageLoopControl();
      }
  }

  void dc_dc_voltageClosedLoop_test()
  {
    g_dc_buck_handler.setVin(5);
    g_dc_buck_handler.setVout(3.3);
    g_voltage_pid.begin(0, 0, 0);
    g_dc_buck_handler.setCV_PID(&g_voltage_pid);
    g_dc_buck_handler.enable();
    while (1)
      {

	g_dc_buck_handler.closedVoltageLoopControl();
      }
  }

  void dc_dc_doubleMode_closedLoop_test()
  {
    g_dc_buck_handler.setVin(5);
    g_dc_buck_handler.setVout(3.3);
    g_voltage_pid.begin(0, 0, 0);
    g_current_pid.begin(0, 0, 0);
    g_dc_buck_handler.setCV_PID(&g_voltage_pid);
    g_dc_buck_handler.setCC_PID(&g_current_pid);
    g_dc_buck_handler.enable();
    while (1)
      {

	g_dc_buck_handler.closedVoltageLoopControl();
      }
  }

  void vofa_send_test()
  {
    printf("good\n");
    HAL_Delay(500);
  }

  void vofa_receive_callback_test(uint8_t *data, uint16_t len)
  {
    for (int i = 0; i < len; i++)
      {
	printf("%c\n", *(data + i));
      }
  }

  void vofa_receive_test()
  {
    g_message_handler.attachEvent(stm32_message::vofaReceiveCallback,PINGPONG_BUFFER);
    while(1)
      {
	g_message_handler.processHandler();
      }
  }
}

#endif /* INC_STM32_TEST_H_ */
