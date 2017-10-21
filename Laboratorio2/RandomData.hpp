/*
 * RandomData.hpp
 *
 *  Created on: Oct 21, 2017
 *      Author: hgvalver
 */

#ifndef RANDOMDATA_HPP_
#define RANDOMDATA_HPP_

#define MAX_RANDOM_VALUE 6540
#define OFFSET    4922

#include "msp.h"
#include "Task.hpp"
#include <stdlib.h>
#include <time.h>

class RandomData : public Task
{
    public:
        RandomData(void);
        uint8_t GenerateData(void);
        virtual uint8_t run(void);
        virtual uint8_t setup(void);
    protected:
    private:
        uint32_t m_u32Data;
};


#endif /* RANDOMDATA_HPP_ */
