/*
 * Accelerometer.cpp
 *
 *  Created on: Oct 28, 2017
 *      Author: emanuelhc / hgvalver
 */

#include "Accelerometer.hpp"

uint8_t Accelerometer::setup()
{
    /* Configures Pin 4.0, 4.2, and 6.1 as ADC input */
        MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN2, GPIO_TERTIARY_MODULE_FUNCTION);
        MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN1, GPIO_TERTIARY_MODULE_FUNCTION);

        /* Initializing ADC (ADCOSC/64/8) */
        MAP_ADC14_enableModule();
        MAP_ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_64, ADC_DIVIDER_8,
                0);

        /* Configuring ADC Memory (ADC_MEM0 - ADC_MEM2 (A11, A13, A14)  with no repeat)
             * with internal 2.5v reference */
        MAP_ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM2, true);
        MAP_ADC14_configureConversionMemory(ADC_MEM0,
                ADC_VREFPOS_AVCC_VREFNEG_VSS,
                ADC_INPUT_A14, ADC_NONDIFFERENTIAL_INPUTS);

        MAP_ADC14_configureConversionMemory(ADC_MEM1,
                ADC_VREFPOS_AVCC_VREFNEG_VSS,
                ADC_INPUT_A13, ADC_NONDIFFERENTIAL_INPUTS);

        MAP_ADC14_configureConversionMemory(ADC_MEM2,
                ADC_VREFPOS_AVCC_VREFNEG_VSS,
                ADC_INPUT_A11, ADC_NONDIFFERENTIAL_INPUTS);

        /* Enabling the interrupt when a conversion on channel 2 (end of sequence)
         *  is complete and enabling conversions */
        MAP_ADC14_enableInterrupt(ADC_INT2);

        /* Enabling Interrupts */
       // MAP_Interrupt_enableInterrupt(INT_ADC14);
        //MAP_Interrupt_enableMaster();

        /* Setting up the sample timer to automatically step through the sequence
         * convert.
         */
        MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

        /* Triggering the start of the sample */
        MAP_ADC14_enableConversion();
        MAP_ADC14_toggleConversionTrigger();



    //return(NO_ERR);
}

uint32_t Accelerometer::run()
{
    m_u32Data = ADC14_getResult(ADC_MEM0);
    m_u32Data1 = ADC14_getResult(ADC_MEM1);
    m_u32Data2 = ADC14_getResult(ADC_MEM2);

    if(m_u32Data <4000 ){

        return 4;
    }
    if(m_u32Data <8000 and m_u32Data >4000  ){
        return 3;
    }
    if(m_u32Data <9000 and m_u32Data >8000  ){
        return 5;
    }
    if(m_u32Data <10000 and m_u32Data >7000  ){
        return 1;
    }
    if(m_u32Data <15000 and m_u32Data >10000  ){
       return 2;
     }
    //printfm_u32Data;
    //return m_u32Data0;
    //Task::SendMessage(TYPE_TRIGGER_AND_DATA,TO_LCD,(uint32_t)&m_u32Data);
    //return(NO_ERR);
}
