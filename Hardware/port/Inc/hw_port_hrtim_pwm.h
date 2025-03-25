/*
 * hw_port_hrtim_pwm.h
 *
 *  Created on: Mar 19, 2025
 *      Author: GAOTIANHAO
 */

#ifndef PORT_INC_HW_PORT_HRTIM_PWM_H_
#define PORT_INC_HW_PORT_HRTIM_PWM_H_

#include "hw_hal_pwm.h"
#include "hrtim.h"


enum hw_port_hrtim_pwm_channel_t {
  HRTIM_TIMER_MASTER=HRTIM_TIMERID_MASTER,
  HRTIM_TIMER_A=HRTIM_TIMERID_TIMER_A,
  HRTIM_TIMER_B=HRTIM_TIMERID_TIMER_B,
  HRTIM_TIMER_C=HRTIM_TIMERID_TIMER_C,
  HRTIM_TIMER_D=HRTIM_TIMERID_TIMER_D,
  HRTIM_TIMER_E=HRTIM_TIMERID_TIMER_E,
  HRTIM_TIMER_F=HRTIM_TIMERID_TIMER_F
};

enum hw_port_hrtim_pwm_compare_unit_t {
  HRTIM_COMPARE_EVENT_1=HRTIM_COMPAREUNIT_1,
  HRTIM_COMPARE_EVENT_2=HRTIM_COMPAREUNIT_2,
  HRTIM_COMPARE_EVENT_3=HRTIM_COMPAREUNIT_3,
  HRTIM_COMPARE_EVENT_4=HRTIM_COMPAREUNIT_4
};

enum hw_tim_id_t {
  HRTIM_TIMER_A_ID=0,
  HRTIM_TIMER_B_ID,
  HRTIM_TIMER_C_ID,
  HRTIM_TIMER_D_ID,
  HRTIM_TIMER_E_ID,
  HRTIM_TIMER_F_ID
};

////sysclk到tim不要分频！！！注意
class Hardware_STM32_HRTIM_PWM
{
public:
  void begin(HRTIM_HandleTypeDef *hhrtim,hw_port_hrtim_pwm_channel_t hrtim_timer_id,hw_port_hrtim_pwm_compare_unit_t compare_unit) {
    if (hhrtim == nullptr) {
	return;
    }
    hhrtim_ = hhrtim;
    channel_=hrtim_timer_id;
    compare_unit_=compare_unit;
    sysclk_frequency_=HAL_RCC_GetSysClockFreq();
    //启动互补输出
    switch (channel_) {
      case HRTIM_TIMER_MASTER:
	break;
      case HRTIM_TIMER_A:
	HAL_HRTIM_WaveformOutputStart(hhrtim_, HRTIM_OUTPUT_TA1|HRTIM_OUTPUT_TA2);
	id_=HRTIM_TIMER_A_ID;
	break;
      case HRTIM_TIMER_B:
	HAL_HRTIM_WaveformOutputStart(hhrtim_,
				      HRTIM_OUTPUT_TB1 | HRTIM_OUTPUT_TB2);
	id_=HRTIM_TIMER_B_ID;
	break;
      case HRTIM_TIMER_C:
	HAL_HRTIM_WaveformOutputStart(hhrtim_,
				      HRTIM_OUTPUT_TC1 | HRTIM_OUTPUT_TC2);
	id_=HRTIM_TIMER_C_ID;
	break;
      case HRTIM_TIMER_D:
	HAL_HRTIM_WaveformOutputStart(hhrtim_,
				      HRTIM_OUTPUT_TD1 | HRTIM_OUTPUT_TD2);
	id_=HRTIM_TIMER_D_ID;
	break;
      case HRTIM_TIMER_E:
	HAL_HRTIM_WaveformOutputStart(hhrtim_,
				      HRTIM_OUTPUT_TE1 | HRTIM_OUTPUT_TE2);
	id_=HRTIM_TIMER_E_ID;
	break;
      case HRTIM_TIMER_F:
	HAL_HRTIM_WaveformOutputStart(hhrtim_,
				      HRTIM_OUTPUT_TF1 | HRTIM_OUTPUT_TF2);
	id_=HRTIM_TIMER_F_ID;
	break;
    }
    period_=__HAL_HRTIM_GETPERIOD(hhrtim_, id_);
  }

  void setOutput()
  {
    HAL_HRTIM_WaveformCounterStart(hhrtim_, channel_);  // Start the counter of the Timer
  }

  void setFrequency(float freq) {
    if(freq == 0){return ;}
    period_ = static_cast<uint32_t>(sysclk_frequency_ / freq);
    __HAL_HRTIM_SETPERIOD(hhrtim_, id_, period_);
    __HAL_HRTIM_SETCOMPARE(hhrtim_, id_, compare_unit_,period_* duty_);
  }

  float getMaxFrequency()
  {
    return sysclk_frequency_ / period_ * 1.0f;
  }

  void setDutyCycle(float duty) {
    duty_=duty;
    uint32_t newCompareValue = period_* duty_;
    __HAL_HRTIM_SETCOMPARE(hhrtim_, id_, compare_unit_,newCompareValue );//timer参数可能要改一下
  }

private:
  HRTIM_HandleTypeDef *hhrtim_;
  uint32_t period_;
  float duty_;
  hw_port_hrtim_pwm_channel_t channel_;//用于hal库提供api的使用
  hw_tim_id_t id_;//用于保留字api的使用
  hw_port_hrtim_pwm_compare_unit_t compare_unit_;
  uint32_t sysclk_frequency_;//sysclk到tim不要分频！！！注意
};






#endif /* PORT_INC_HW_PORT_HRTIM_PWM_H_ */
