/*
 * RandomData.cpp
 *
 *  Created on: Oct 21, 2017
 *      Author: hgvalver
 */

#include "RandomData.hpp"

RandomData::RandomData()
{
    m_u32Data = OFFSET;
}

uint8_t RandomData::GenerateData()
{
    //m_u32Data = rand()%MAX_RANDOM_VALUE+OFFSET;
    m_u32Data += 100;
    if (m_u32Data >= MAX_RANDOM_VALUE+OFFSET)
        m_u32Data = OFFSET;
    return(NO_ERR);
}

uint8_t RandomData::setup()
{
    srand(time(NULL));
    return(NO_ERR);
}

uint8_t RandomData::run()
{
    RandomData::GenerateData();
    Task::SendMessage(TYPE_TRIGGER_AND_DATA,TO_LCD,(uint32_t)&m_u32Data);
    return(NO_ERR);
}
