/*
 * alg_pid.h
 *
 *  Created on: Mar 18, 2025
 *      Author: GAOTIANHAO
 */

#ifndef ALGORITHIM_INC_ALG_PID_H_
#define ALGORITHIM_INC_ALG_PID_H_

#include "portmacro.h"
class Algorithim_PID {
private:
	// PID参数
	float kp; // 比例系数
	float ki; // 积分系数
	float kd; // 微分系数

	// 状态变量
	float lastError; // 上一次的误差
	float last_lastError; // 上上次误差（用于增量式PID）
	float integral;  // 积分项
	float lastOutput; // 上一次的输出（用于增量式PID）
	float integral_limit;  // 积分限幅
	float output_limit;    // 输出限幅
	float delta_output_limit; // 输出变化速率限制

public:
	// 初始化方法
	void begin(float kp, float ki, float kd,float integral_limit=-1, float output_limit=-1, float delta_output_limit=-1){
		this->kp = kp;
		this->ki = ki;
		this->kd = kd;
		this->lastError = 0;
		this->integral = 0;
		this->last_lastError = 0;
		this->lastOutput = 0;
		this->integral_limit = integral_limit;
		this->output_limit = output_limit;
		this->delta_output_limit = delta_output_limit;
	}

	// 修改PID参数
	void set(float kp, float ki, float kd,float integral_limit=-1, float output_limit=-1,float delta_output_limit=-1) {
		this->kp = kp;
		this->ki = ki;
		this->kd = kd;
		this->integral_limit = integral_limit;
		this->output_limit = output_limit;
		this->delta_output_limit = delta_output_limit;
	}

	// 增量式PID计算输出
	float cal_absolute(float target_value, float measured_value) {
		float error = target_value - measured_value; // 计算误差
		float proportional = kp * error;
		integral += error;
		if (integral_limit > 0) {
			integral = LIMIT(integral, -integral_limit, integral_limit);
		}
		float integralTerm = ki * integral;
		float derivative = kd * (error - lastError);
		float output = proportional + integralTerm + derivative;

		if (output_limit > 0) {
			output = LIMIT(output, -output_limit, output_limit);
		}

		if(delta_output_limit > 0){//设为-1可以禁用
			// 对PID的变化速率进行限制
			float output_rate = output - lastOutput;
			if (output_rate > delta_output_limit)
				output = lastOutput + delta_output_limit;
			else if (output_rate < -delta_output_limit)
				output = lastOutput - delta_output_limit;
		}

		// 更新状态变量
		lastError = error;
		lastOutput = output;

		return output;
	}

	// 绝对式PID计算输出
	float cal_increase(float target_value, float measured_value) {
		float error = target_value - measured_value; // 计算误差
		float proportional = kp * (error-lastError);
		integral += error;
		// 限幅
		if (integral_limit > 0) {
			integral = LIMIT(integral, -integral_limit, integral_limit);
		}

		float integralTerm = ki * integral;
		float derivative = kd * (error - 2*lastError + last_lastError);
		float output = lastOutput + proportional + integralTerm + derivative;

		if (output_limit > 0) {
			output = LIMIT(output, -output_limit, output_limit);
		}

		if(delta_output_limit > 0){//设为-1可以禁用
			// 对PID的变化速率进行限制
			float output_rate = output - lastOutput;
			if (output_rate > delta_output_limit)
				output = lastOutput + delta_output_limit;
			else if (output_rate < -delta_output_limit)
				output = lastOutput - delta_output_limit;
		}

		// 更新状态变量
		last_lastError = lastError;
		lastError = error;
		lastOutput = output;

		return output;
	}
};



#endif /* ALGORITHIM_INC_ALG_PID_H_ */
