/*
 * RandomData.cpp
 *
 *  Created on: Oct 21, 2017
 *      Author: hgvalver
 */

#include "RandomData.hpp"

bool RandomData::NewEnemy(uint8_t l_u8Level)
{
    m_u32RandomValue = rand()%NEW_ENEMY;
    switch (l_u8Level) {
    case LVL1:
        m_u8Probabilities = PROB_LV1;
        break;
    case LVL2:
        m_u8Probabilities = PROB_LV2;
        break;
    case LVL3:
        m_u8Probabilities = PROB_LV3;
        break;
    case LVL4:
        m_u8Probabilities = PROB_LV4;
        break;
    case LVL5:
    default:
        m_u8Probabilities = PROB_LV5;
    }
    m_u8Probabilities = PROB_LV1;
    if (m_u32RandomValue%m_u8Probabilities==0)
        return(true);
    else
        return(false);
}

uint8_t RandomData::Lane()
{
    m_u32RandomValue = rand()%DIRECTION;
    return(m_u32RandomValue);
}

uint8_t RandomData::Setup()
{
    srand(time(NULL));
    return(NO_ERR);
}
