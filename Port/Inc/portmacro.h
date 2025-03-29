/*
 * portmacro.h
 *
 *  Created on: Mar 17, 2025
 *      Author: GAOTIANHAO
 */

#ifndef INC_PORTMACRO_H_
#define INC_PORTMACRO_H_


//这个文件夹用来放置一些常用的宏定义，以及外部库依赖
/*当前的外部库列表
 concepts
 coroutine
 */
#if __has_include(<version>)
#include <version>
#ifdef __cpp_lib_concepts
#include <concepts>
#endif
#ifdef __cpp_lib_coroutine
#include <coroutine>
#endif
#endif


#define LIMIT(value, minVal, maxVal) (((value) < (minVal)) ? (minVal) : (((value) > (maxVal)) ? (maxVal) : (value)))


#endif /* INC_PORTMACRO_H_ */
