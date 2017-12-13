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
#include "RandomData.hpp"

#define TIMER32_COUNT   0x0000BB80  // ~1ms with 48MHz clock
#define TIME_UP_ERROR   1
#define REFRESH         10
#define NEW_DATA        1000

// The main Setup function for the application
void Setup(void);

// Variables
int move_enemy = 0;
uint32_t g_u32Score;
uint8_t g_u8Speed, g_u8Level;
bool g_bLevelChanged, g_bGameOver, g_bNewEnemy;

// ##########################
// Global/Static declarations
// ##########################
volatile static uint64_t g_SystemTicks = 0; // - The system counter.


#endif /* MAIN_HPP_ */
