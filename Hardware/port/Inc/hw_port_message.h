/*
 * hw_port_serial.h
 *
 *  Created on: Mar 23, 2025
 *      Author: GAOTIANHAO
 */

#ifndef PORT_INC_HW_PORT_MESSAGE_H_
#define PORT_INC_HW_PORT_MESSAGE_H_


#include "usart.h"

typedef enum {
  PINGPONG_BUFFER = 0,
  number_of_event,
} ProcessEvent;

typedef void (*MessageCallback)(uint8_t *data, uint16_t len);

class Hardware_STM32_Message
{
public:
  void begin(uint16_t buffer_num, size_t buffer_len, UART_HandleTypeDef *huart)
  {
    if (!huart) {
	return;
    }
    if (buffer_num == 0 || buffer_len == 0) {
	return;
    }
    _buffer_num = buffer_num;
    _buffer_len = buffer_len;
    _huart = huart;
    _buffer = new uint8_t*[buffer_num];
    for (int i = 0; i < buffer_num; i++) {
	_buffer[i] = new uint8_t[buffer_len];
    }
  }

  void startReceive()
  {
    _startDMA();
  }

  void callbackHandler(UART_HandleTypeDef *huart, uint16_t Size) {
    if (huart == _huart) {
	_data_len = Size;
	_new_data_available = true;
	_receiveBufferIndex = (_receiveBufferIndex + 1) % _buffer_num;
	_startDMA();
    }
  }

  void attachEvent(MessageCallback cb, ProcessEvent event) {
    _cb[event] = cb;
  }

  void stopEvent(MessageCallback cb, ProcessEvent event) {
    _cb[event] = NULL;
  }

  void processHandler() {
    if (_new_data_available) {
	_new_data_available = false;
	_processBufferIndex = (_processBufferIndex + 1) % _buffer_num;
	if (_cb[PINGPONG_BUFFER]) {
	    _cb[PINGPONG_BUFFER](_buffer[_processBufferIndex], _data_len);
	}
    }
  }

private:
  UART_HandleTypeDef *_huart;
  uint8_t **_buffer;
  uint8_t _buffer_num;
  uint8_t _buffer_len;
  int _data_len;
  bool _new_data_available = 0;
  uint8_t _receiveBufferIndex = 0;
  int8_t _processBufferIndex = -1;
  MessageCallback _cb[number_of_event];

  void _startDMA()
  {
    HAL_UARTEx_ReceiveToIdle_DMA(_huart, _buffer[_receiveBufferIndex], 2 * _buffer_len);
  }
};



#endif /* PORT_INC_HW_PORT_MESSAGE_H_ */
