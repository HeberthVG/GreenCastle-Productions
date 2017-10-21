/*
 * LCD.hpp
 *
 *  Created on: Oct 21, 2017
 *      Author: hgvalver
 */

#ifndef LCD_HPP_
#define LCD_HPP_

#define MIN_VALUE        4922
#define MAX_VALUE        11462
#define MAX_NUMBER_PIXEL 125
#define WHITE_LINE       3
#define NEXT_PIXEL       3

#include "msp.h"
#include "Task.hpp"
#include <driverlib.h>
#include <grlib.h>
#include "Crystalfontz128x128_ST7735.h"
#include <stdio.h>

class LCD : public Task
{
    public:
        LCD(void);
        Graphics_Context m_sContext;
        Graphics_Rectangle m_sBlue, m_sBrown, m_sWhite;
        uint8_t DrawTitle(void);
        uint8_t RefreshScreen(void);
        uint8_t Delay(void);
        virtual uint8_t run(void);
        virtual uint8_t setup(void);
    protected:
    private:
        uint32_t m_u32Position, m_u32Pixel;
};

#endif /* LCD_HPP_ */
