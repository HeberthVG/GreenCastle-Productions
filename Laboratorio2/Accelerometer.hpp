/*
 * Accelerometer.hpp
 *
 *  Created on: Oct 28, 2017
 *      Author: emanuelhc / hgvalver
 */

#ifndef Accelerometer_HPP_
#define Accelerometer_HPP_

#include "msp.h"
#include "Task.hpp"
#include <driverlib.h>

class Accelerometer : public Task
{
    public:
        Accelerometer(){};
        virtual uint8_t run(void);
        virtual uint8_t setup(void);
    protected:
    private:
        uint32_t m_u32Data;
};


#endif /* Accelerometer_HPP_ */
