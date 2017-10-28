/*
 * main.hpp
 *
 *  Created on: Aug 31, 2016
 *      Author: emanuelhc / hgvalver
 */

#ifndef MAIN_HPP_
#define MAIN_HPP_
#define TIMER32_COUNT 0x0000BB80  // ~1ms with 48MHz clock
#define TIME_UP_ERROR 1
// The main Setup function for the application
void Setup(void);
uint32_t l_u32PreviousTick = 0;

#endif /* MAIN_HPP_ */
