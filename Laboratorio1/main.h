/*
 * main.h
 *
 *  Created on: Sep 16, 2017
 *      Author: hgvalver
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "functions.h"
#include <array>

int power;  //Potencia de la lampara
bool light = false, sound = false, state = false; //Indican si se presenta la condición de encendido de luz y sonido
int time, maxTime; //Tiempo de encendido de la lámpara y tiempo máximo de encendido en segundos
float lux;  //Cantidad de lúmenes en el ambiente
float maxLux;   //Límite de luz
uint16_t ADC14Result; //Variables para lectura del microfono
int16_t adc14Signed;
int mean5s, mean1s; //Sonido los ultimos 5s y 1s
std::array<int,50> samples = {0};
unsigned samp, asd = 0, i;
int pba;
bool newSample = false;
bool previousButton = false, buttonRequest = false;
int j;

#endif /* MAIN_H_ */
