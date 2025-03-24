/*
 * t.h
 *
 *  Created on: Mar 15, 2025
 *      Author: GAOTIANHAO
 */

#ifndef ALGORITHIM_INC_ALG_DC_BUCK_H_
#define ALGORITHIM_INC_ALG_DC_BUCK_H_

#include "main.h"
#include "portmacro.h"
#include <utility>
#include "hw_hal_pwm.h"
#include "hw_hal_adc.h"
#include "hw_hal_relay.h"
#include "alg_pid.h"

//Note
/*输入电压可用户设置，也可以通过ADC读取，输入电压主要用于过压保护和切换
 * Algorithim_DC_Buck类中的vout和current是设定的目标值，类中不存有adc读到的实际值
 * adc需要提供接口给du_buck类读取实际值
 */

// BuckConverter 类声明
#ifdef __cpp_concepts
template < PWMInterfaceConcept PWM, ADCInterfaceConcept ADC , RelayInterfaceConcept RELAY>
#else
template <class PWM, class ADC, class RELAY>
#endif
class Algorithim_DC_Buck {
public:
  Algorithim_DC_Buck(){}
  void begin(PWM *pwm,float vout,float current,ADC *adc_out = nullptr ,RELAY *relay = nullptr, float vin=0 , ADC *adc_in = nullptr)
  {
    pwm_ = pwm;
    adc_out_ = adc_out;
    adc_in_ = adc_in;
    relay_= relay;
    vin_ = vin;
    vout_ = vout;
    current_ = current;
  }

  void setCV_PID(Algorithim_PID *pid)
  {
    cv_pid_ = pid;
  }

  void setCC_PID(Algorithim_PID *pid)
  {
    cc_pid_ = pid;
  }

  void setVin(float vin)
  {
    vin_ = vin;
  }

  void setVout(float vout)
  {
    vout_ = vout;
  }

  bool readVin()
  {
    if(!adc_in_){return false;}
    vin_ = adc_in_->readVoltage();
    return true;
  }

  void setCurrent(float current)
  {
    current_ = current;
  }

  void openVoltageLoopControl() {
    if(vin_ == 0 || vout_>vin_||!isEnable_) {return ;}
  }

  void closedVoltageLoopControl() {
    float output;
    if(!adc_out_||!isEnable_){return ;}
    output = LIMIT((cv_pid_->cal_increase(vout_, adc_out_->readVoltage())),0,1);
    pwm_->setDutyCycle(output);
  }

  void closedCurrentLoopControl() {
    float output;
    if(!adc_out_||!isEnable_){return ;}
    output = LIMIT(cc_pid_->cal_increase(current_, adc_out_->readCurrent()),0,1);
    pwm_->setDutyCycle(output);
  }


  void enable() {
    isEnable_=true;
    relay_->on();
  }

  void disable() {
    isEnable_=false;
    relay_->off();
  }

  bool isEnable()
  {
    return isEnable_;
  }
  PWM *pwm_;
  ADC *adc_out_;
  ADC *adc_in_;
  RELAY *relay_;
  Algorithim_PID *cc_pid_;
  Algorithim_PID *cv_pid_;
  bool isEnable_=false;
  float vin_;
  float vout_;
  float current_;
};


#endif /* ALGORITHIM_INC_ALG_DC_BUCK_H_ */
