/*
 * main.hpp
 *
 *  Created on: Dec 5, 2017
 *      Author: emanuelhc / hgvalver
 */

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include "msp.h"
#include "LCD.hpp"

#define TIMER32_COUNT 0x0000BB80  // ~1ms with 48MHz clock
#define TIME_UP_ERROR 1

// The main Setup function for the application
void Setup(void);


#endif /* MAIN_HPP_ */
