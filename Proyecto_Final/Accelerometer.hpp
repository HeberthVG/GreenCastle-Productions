/*
 * Accelerometer.hpp
 *
 *  Created on: Oct 28, 2017
 *      Author: emanuelhc / hgvalver
 */

#ifndef Accelerometer_HPP_
#define Accelerometer_HPP_

#include "msp.h"
#include <driverlib.h>

class Accelerometer
{
    public:
        Accelerometer(){};
        virtual uint32_t run(void);
        virtual uint8_t setup(void);
    protected:
    private:
        uint32_t m_u32Data;
        uint32_t m_u32Data1;
        uint32_t m_u32Data2;
};


#endif /* Accelerometer_HPP_ */
