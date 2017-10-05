/*
 * functions.cpp
 *
 *  Created on: Sep 16, 2017
 *      Author: hgvalver
 */


#include "functions.h"

void rgb_init(int power)
{
    P2->DIR = (BIT2 | BIT1 | BIT0) & power;   //Inicializa LED RGB
    P2->OUT = 0;
}

void rgb_on()
{
    P2->OUT = BIT2 | BIT1 | BIT0;
}

void rgb_off()
{
    P2->OUT = 0;
}

void rgb_toggle()
{
    P2->OUT ^= BIT2 | BIT1 | BIT0;
}

/* Secuencia de inicio */
void startSeq() {
    for (int i=0; i<6; i++)
    {
        rgb_toggle();

        //Delay
        for(int j=4800000; j>0; j--);
    }
}

/* Definición de la potencia a manejar */
int setPower(int value)
{
    int power;
    switch (value)
    {
        case 10:
            power = 5;
            break;
        case 15:
            power = 6;
            break;
        default:
            power = 2;
    }
    return power;
}

/* Sensar la luz ambiente */
bool senseLight(float max_lux)
{
    bool light;
    float lux;
    lux = OPT3001_getLux();
    if (lux < max_lux)
        light = true;
    else
        light = false;
    return light;
}

/* Desplaza los elementos una posicion*/
void shift(int* array, int size)
{
    for (int* i=array; i<array+size-1; i++)
        *i = *(i+1);
}
