/*
 * RandomData.hpp
 *
 *  Created on: Oct 21, 2017
 *      Author: hgvalver
 */

#ifndef RANDOMDATA_HPP_
#define RANDOMDATA_HPP_

#define DIRECTION       3
#define NEW_ENEMY       100
#define LVL1            100
#define LVL2            60
#define LVL3            30
#define LVL4            20
#define LVL5            5
#define PROB_LV1        10
#define PROB_LV2        5
#define PROB_LV3        4
#define PROB_LV4        3
#define PROB_LV5        2
#define NO_ERR          0

#include "msp.h"
#include <stdlib.h>
#include <time.h>

class RandomData
{
    public:
        RandomData(void) {};
        bool NewEnemy(uint8_t l_u8Level);
        uint8_t Lane(void);
        uint8_t Setup(void);
    protected:
    private:
        uint32_t m_u32RandomValue;
        uint8_t m_u8Probabilities;
};


#endif /* RANDOMDATA_HPP_ */
