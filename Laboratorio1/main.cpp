/*****************************************************************************
*
* Copyright (C) 2013 - 2016 Texas Instruments Incorporated - http://www.ti.com/
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* * Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the
*   distribution.
*
* * Neither the name of Texas Instruments Incorporated nor the names of
*   its contributors may be used to endorse or promote products derived
*   from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*
* MSP432 empty main.c template
*
* for GNU compiler
*
******************************************************************************/

#include "msp.h"
#include "main.h"
#include <stdlib.h>

int main(void)
{
	
    WDTCTL = WDTPW | WDTHOLD;        /* Stop watchdog timer */

    //Definicion de variables
    power = setPower(15); //15W
    maxTime = 50; //5s
    maxLux = 50.0;

    //Inicializacion del hardware

    //Inicializa los LEDs
    rgb_init(power);

    //Inicializa Timer32
    //TIMER32_1->LOAD = 0x0000BB80; //~1ms ---> a 48Mhz
    TIMER32_1->LOAD = 0x00493E00; //~100ms ---> a 48Mhz
    TIMER32_1->CONTROL = TIMER32_CONTROL_SIZE | TIMER32_CONTROL_PRESCALE_0 | TIMER32_CONTROL_MODE | TIMER32_CONTROL_IE | TIMER32_CONTROL_ENABLE;
    NVIC_SetPriority(T32_INT1_IRQn,1);

    //Inicializa ADC con el microfono
    P4->SEL0 = BIT3;
    P4->SEL1 = BIT3;
    P4->DIR &= ~BIT3;
    ADC14->CTL0 = ADC14_CTL0_PDIV_0 | ADC14_CTL0_SHS_0 | ADC14_CTL0_DIV_7 |
          ADC14_CTL0_SSEL__MCLK | ADC14_CTL0_SHT0_1 | ADC14_CTL0_ON
          | ADC14_CTL0_SHP;
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_10 | ADC14_MCTLN_VRSEL_0;
    ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_ENC;
    ADC14->IER0 = ADC14_IER0_IE0;
    NVIC_SetPriority(ADC14_IRQn,1);

    // Inicializa protocolo i2c
    Init_I2C_GPIO();
    I2C_init();


    //Secuencia de Inicio
    startSeq();

    //Estado Inicial
    light = senseLight(maxLux);
    lux = OPT3001_getLux();

    if (light)
    {
        rgb_on();
        time = 0;
        state = true;
    }
    else {
        rgb_off();
        state = false;
    }

    //button
    P3->DIR |= BIT5;
    P3->OUT |= BIT5;

    //Se habilitan las interrupciones
    NVIC_EnableIRQ(T32_INT1_IRQn);
    NVIC_EnableIRQ(ADC14_IRQn);
    //NVIC_EnableIRQ(PORT1_IRQn);

    while(1)
    {
        if (!BITBAND_PERI(P3->IN, 5)){//!(P3IN & GPIO_PIN1)) {
        //buttonRequest = !BITBAND_PERI(P3->IN, 5);
        //if ((previousButton == buttonRequest) and (buttonRequest == true)) {
            //previousButton = buttonRequest;
            if (state) {
                light = false;
                sound = false;
                state = false;
                rgb_off();
            }
            else {
                light = true;
                sound = true;
                state = true;
                rgb_on();
                time = 0;
            }
            //Delay
            for(j=1200000; j>0; j--);
        }
        //else {
            //previousButton = buttonRequest;
        //}

        if(newSample){

            if (time >= maxTime) {
                rgb_off();
                state = false;
            }

            light = senseLight(maxLux);
            lux = OPT3001_getLux();

            mean5s = 0;
            mean1s = 0;
            for (samp = 0; samp < samples.size(); samp++) {
                mean5s += samples[samp];
                pba = samples[samp];
                if (samp >= samples.size()*4/5)
                    mean1s += samples[samp];
            }
            mean5s = mean5s/(samples.size()*4/5);
            mean1s = mean1s/(samples.size()/5);

            if (mean1s > 1.1*mean5s)
                sound = true;
            else
                sound = false;

            if (sound and light)
            {
                rgb_on();
                time = 0;
                state = true;
            }
            newSample = false;
        }
    }
	
    return 0;
}

extern "C"
{
    void T32_INT1_IRQHandler(void)
    {
        __disable_irq();
        TIMER32_1->INTCLR = 0U;
        time++;
        ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_SC;
        __enable_irq();
        return;
    }

    void ADC14_IRQHandler(void)
    {
        __disable_irq();
        ADC14Result = ADC14->MEM[0];
        adc14Signed = abs(ADC14Result - 8192);
        for (i=0; i<samples.size()-1; i++)
           samples[i] = samples[i+1];
        samples[samples.size()-1] = adc14Signed;
        newSample = true;
        ADC14->CLRIFGR0 = ADC14_CLRIFGR0_CLRIFG0;
        __enable_irq();
        return;
    }

    /*void PORT1(void)
    {
        P1->IFG &= ~BIT3;
        if (light and sound) {
            light = false;
            sound = false;
            rgb_off();
        }
        else {
            light = true;
            sound = true;
            rgb_on();
            time = 0;
        }
    }*/
    /*void PORT1_IRQHandler(void)
    {
    volatile uint32_t i;
    if(P1IFG & BIT1){
    if (light and sound) {
                light = false;
                sound = false;
                rgb_off();
            }
            else {
                light = true;
                sound = true;
                rgb_on();
                time = 0;
            }
    }
    // write your code to handle buttons here
    // Delay for switch debounce
    for(i = 0; i < 10000; i++)
    P1IFG &= ~BIT1; // Clear the interrupt Flag
    }*/
}
