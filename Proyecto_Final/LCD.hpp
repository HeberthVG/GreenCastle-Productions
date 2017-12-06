/*
 * LCD.hpp
 *
 *  Created on: Dec 5, 2017
 *      Author: emanuelhc / hgvalver
 */

#ifndef LCD_HPP_
#define LCD_HPP_

#define SPEED           "Speed: "
#define SCORE           "Score: "
#define BLOCK_WIDTH     3
#define SPACE           2
#define NULL            0
#define BLOCK           4
#define DOUBLE_BLOCK    8
#define BORDER          60
#define NO_ERR          0
#define LD_TIRE         28
#define LD_TIRE_L       12
#define LD_TIRE_R       42
#define MAX_POS         116

#include "msp.h"
#include <driverlib.h>
#include <grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.hpp"
#include <stdio.h>
#include <stdlib.h>


class LCD
{
    public:
        LCD();
        Graphics_Context m_sContext;
        Graphics_Rectangle m_sBlock, m_sEnemy1, m_sEnemy2, m_sEnemy3, m_sPlayer;
        Graphics_Rectangle *m_pEnemy;
        uint8_t DrawMap(void);
        uint8_t DrawBorder(void);
        uint8_t DrawEnemy(void);
        uint8_t DrawPlayer(void);
        uint8_t MoveEnemy(void);
        uint8_t MovePlayer(void);
        uint8_t OneBlockUp (Graphics_Rectangle *l_pRect);
        uint8_t TwoBlocksUp (Graphics_Rectangle *l_pRect);
        uint8_t SetBlockPosition (Graphics_Rectangle *l_pRect, int16_t l_i16XMin, int16_t l_i16YMin, int16_t l_i16XMax, int16_t l_i16YMax);
        uint8_t Setup(void);
    protected:
    private:
        int8_t *m_pString;
        int8_t m_i8Counter;
        uint8_t m_u8NextEnemy;
};

#endif /* LCD_HPP_ */
