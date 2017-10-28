/*
 * LCD.hpp
 *
 *  Created on: Oct 21, 2017
 *      Author: emanuelhc / hgvalver
 */

#ifndef LCD_HPP_
#define LCD_HPP_

#define MIN_VALUE        4822
#define MAX_VALUE        11541
#define WHITE_LINE       2
#define NEXT_PIXEL       1
#define PIXEL_MIN        0
#define PIXEL_MAX        127
#define NOISE            2

#include "msp.h"
#include "Task.hpp"
#include <driverlib.h>
#include <grlib.h>
#include "Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include <stdlib.h>

class LCD : public Task
{
    public:
        LCD();
        Graphics_Context m_sContext;
        Graphics_Rectangle m_sSky, m_sEarth;
        uint8_t DrawTitle(void);
        uint8_t RefreshScreen(void);
        uint8_t Delay(void);
        virtual uint8_t run(void);
        virtual uint8_t setup(void);
    protected:
    private:
        uint32_t m_u32Position, m_u32Pixel;
        uint32_t m_u32WhiteLine;
};

#endif /* LCD_HPP_ */
