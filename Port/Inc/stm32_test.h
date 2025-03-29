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
#include "SEGGER_SYSVIEW.h"
#include "SEGGER_SYSVIEW_Conf.h"

extern Hardware_STM32_HRTIM_PWM g_hrtimerA_pwm_handler;
extern Hardware_STM32_ADC g_adc1_handler;
extern Hardware_STM32_Relay g_relay1_handler;
extern Hardware_STM32_Message g_message_handler;
extern Algorithim_DC_Buck<Hardware_STM32_HRTIM_PWM, Hardware_STM32_ADC ,Hardware_STM32_Relay>g_dc_buck_handler;
extern Algorithim_PID g_voltage_pid;
extern Algorithim_PID g_current_pid;

namespace stm32_test
{
  enum power_control_mode_t
  {
    VOLTAGE_CLOSE_LOOP,
    CURRENT_CLOSE_LOOP
  };

  enum vofa_isResetPID_bool_t
  {
    NO_RESET_PID,
    RESET_PID
  };

  enum vofa_isOutput_bool_t
  {
    OUTPUT_STOP,
    OUTPUT_START
  };

  struct target_vofa_set_value_t
  {
    float target_voltage;
    float target_current;
  };


  target_vofa_set_value_t g_target_vofa_set;
  vofa_isResetPID_bool_t g_bool_isResetPID = NO_RESET_PID;
  vofa_isOutput_bool_t g_bool_isOutput = OUTPUT_STOP;
  power_control_mode_t g_power_control_mode = VOLTAGE_CLOSE_LOOP;
  Algorithim_PID g_voltage_pid_vofa_set;
  Algorithim_PID g_current_pid_vofa_set;

  void vofaReceiveCallback(uint8_t *data,uint16_t len)
  {
    float temp;
    char s[20];
    memcpy(s,data,len);
    s[len]='\0';
    if (sscanf(s, "VP=%f", &temp) >0)
      {
	g_voltage_pid_vofa_set.kp=temp;
	printf("VP: %f\n", temp);
      }
    else if (sscanf(s, "VI=%f", &temp) >0)
      {
	g_voltage_pid_vofa_set.ki=temp;
	printf("VI: %f\n", temp);
      }
    else if (sscanf(s, "VD=%f", &temp) >0)
      {
	g_voltage_pid_vofa_set.kd=temp;
	printf("VD: %f\n", temp);
      }
    else if (sscanf(s, "CP=%f", &temp) >0)
      {
	g_current_pid_vofa_set.kp=temp;
	printf("CP: %f\n", temp);
      }
    else if (sscanf(s, "CI=%f", &temp) >0)
      {
	g_current_pid_vofa_set.ki=temp;
	printf("CI: %f\n", temp);
      }
    else if (sscanf(s, "CD=%f", &temp) >0)
      {
	g_current_pid_vofa_set.kd=temp;
	printf("CD: %f\n", temp);
      }
    else if (sscanf(s, "V=%f", &temp)>0)
      {
	g_target_vofa_set.target_voltage = temp;
	printf("V: %f\n", temp);
      }
    else if (sscanf(s, "C=%f", &temp)>0)
      {
	g_target_vofa_set.target_current = temp;
	printf("C: %f\n", temp);
      }
    else if (sscanf(s, "VL=%f", &temp)>0)
      {
	g_voltage_pid_vofa_set.integral_limit=temp;
	printf("VL: %f\n", temp);
      }
    else if (sscanf(s, "CL=%f", &temp) >0)
      {
	g_current_pid_vofa_set.integral_limit=temp;
	printf("CL: %f\n", temp);
      }
    else if (sscanf(s, "MODE=%f", &temp) >0)
      {
	if (temp == 0)
	  {
	    printf("VOLTAGE MODE\n");
	    g_power_control_mode = VOLTAGE_CLOSE_LOOP;
	  }
	else if (temp == 1)
	  {
	    printf("CURRENT MODE\n");
	    g_power_control_mode = CURRENT_CLOSE_LOOP;
	  }
      }
    else if (sscanf(s, "EN=%f", &temp) >0)
      {

	if (temp == 0)
	  {
	    g_bool_isOutput = OUTPUT_STOP;
	    printf("OUTPUT STOP\n");
	  }
	else if (temp == 1)
	  {
	    g_bool_isOutput = OUTPUT_START;
	    printf("OUTPUT START\n");
	  }
      }
    else if (strcmp (s, "RESET") == 0)
      {
	printf("RESET\n");
	HAL_NVIC_SystemReset();
      }
    else if (strcmp (s, "CLEAR") == 0)
      {
	g_voltage_pid_vofa_set.kp = 0;
	g_voltage_pid_vofa_set.ki = 0;
	g_voltage_pid_vofa_set.kd = 0;
	g_voltage_pid_vofa_set.integral_limit = 0;
	g_current_pid_vofa_set.kp = 0;
	g_current_pid_vofa_set.ki = 0;
	g_current_pid_vofa_set.kd = 0;
	g_bool_isResetPID = RESET_PID;
	printf("RESET PID\n");
      }
  }



  void timerA_pwm_test ()
  {
    g_hrtimerA_pwm_handler=stm32_hrtim_pwm::getTimerAOutput();
    g_hrtimerA_pwm_handler.setDutyCycle(0.3);
    g_hrtimerA_pwm_handler.setOutput();
  }

  void adc_dma_test ()
  {
    g_message_handler=stm32_message::getUART1();
    g_message_handler.startReceive();
    g_adc1_handler=stm32_adc::getADC1();
    g_adc1_handler.startSample();
    while(1)
      {
	static float voltage=0;
	static float current=0;
	voltage=g_adc1_handler.readVoltage();
	current=g_adc1_handler.readCurrent();
	printf("voltage:%f\n",voltage);
	printf("current:%f\n",current);
      }
  }

  void adc_it_test()
  {
    //adc注入组测试需要先开启PWM输出
    timerA_pwm_test();
    g_adc1_handler=stm32_adc::getADC1();
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
    g_dc_buck_handler=stm32_dc_buck::getDCBuck1(&g_hrtimerA_pwm_handler,&g_adc1_handler,&g_relay1_handler);
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
    g_dc_buck_handler=stm32_dc_buck::getDCBuck1(&g_hrtimerA_pwm_handler,&g_adc1_handler,&g_relay1_handler);
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
    g_dc_buck_handler=stm32_dc_buck::getDCBuck1(&g_hrtimerA_pwm_handler,&g_adc1_handler,&g_relay1_handler);
    g_dc_buck_handler.setVin(5);
    g_dc_buck_handler.setVout(3.3);
    g_voltage_pid.begin(1, 1, 1);
    g_current_pid.begin(2, 2, 2);
    g_dc_buck_handler.setCV_PID(&g_voltage_pid);
    g_dc_buck_handler.setCC_PID(&g_current_pid);
    g_adc1_handler.startSample();
//    __HAL_DMA_DISABLE_IT(&hdma_adc1, DMA_IT_HT);

    g_message_handler.attachEvent(vofaReceiveCallback,PINGPONG_BUFFER);

    while (1)
      {
	SEGGER_SYSVIEW_RecordVoid(33);
	if(g_bool_isOutput == OUTPUT_START)
	  {
	    g_dc_buck_handler.enable();
	  }
	else
	  {
	    g_dc_buck_handler.disable();
	  }
	printf("%d\n",g_dc_buck_handler.isEnable());
	SEGGER_SYSVIEW_RecordEndCall(33);
	HAL_Delay(500);
	switch(g_power_control_mode)
	{
	  case VOLTAGE_CLOSE_LOOP:
	    if (g_bool_isResetPID == RESET_PID)
	      {
		g_dc_buck_handler.cv_pid_->kp=g_voltage_pid_vofa_set.kp;
		g_dc_buck_handler.cv_pid_->ki=g_voltage_pid_vofa_set.ki;
		g_dc_buck_handler.cv_pid_->kd=g_voltage_pid_vofa_set.kd;
		g_dc_buck_handler.cv_pid_->integral_limit=g_voltage_pid_vofa_set.integral_limit;
	      }
	    g_dc_buck_handler.closedVoltageLoopControl ();

	    break;
	  case CURRENT_CLOSE_LOOP:
	    if (g_bool_isResetPID == RESET_PID)
	      {
		g_dc_buck_handler.cc_pid_->kp=g_current_pid_vofa_set.kp;
		g_dc_buck_handler.cc_pid_->ki=g_current_pid_vofa_set.ki;
		g_dc_buck_handler.cc_pid_->kd=g_current_pid_vofa_set.kd;
		g_dc_buck_handler.cc_pid_->integral_limit=g_current_pid_vofa_set.integral_limit;
	      }
	    g_dc_buck_handler.closedCurrentLoopControl ();
	    break;
	}
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
    g_message_handler.attachEvent(vofaReceiveCallback,PINGPONG_BUFFER);
    while(1)
      {
	g_message_handler.processHandler();
      }
  }
}

#endif /* INC_STM32_TEST_H_ */
