/*
 * functions.h
 *
 *  Created on: Sep 16, 2017
 *      Author: hgvalver
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "msp.h"
#include <driverlib.h>
#include <HAL_I2C.h>
#include <HAL_OPT3001.h>

void rgb_init(int power);
void rgb_on();
void rgb_off();
void rgb_toggle();

void startSeq();
int setPower(int value);
bool senseLight(float max_lux);
void shift(int* array, int size);

#endif /* FUNCTIONS_H_ */
