/*
 * LCD.cpp
 *
 *  Created on: Oct 21, 2017
 *      Author: emanuelhc / hgvalver
 */

#include "LCD.hpp"

LCD::LCD()
{
    m_sSky.xMin = PIXEL_MIN;
    m_sSky.xMax = PIXEL_MAX;
    m_sSky.yMax = PIXEL_MAX;
    m_sEarth.xMin = PIXEL_MIN;
    m_sEarth.yMin = PIXEL_MIN;
    m_sEarth.xMax = PIXEL_MAX;
}

uint8_t LCD::run()
{
    RefreshScreen();
    return(NO_ERR);
}

uint8_t LCD::setup()
{
    MAP_CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    /* Initializes graphics context */
    Graphics_initContext(&m_sContext, &g_sCrystalfontz128x128);
    //LCD::DrawTitle();
    return(NO_ERR);
}

uint8_t LCD::DrawTitle()
{
    if (m_u32Pixel < 127) {
    Graphics_setForegroundColor(&m_sContext, ClrBlue);
    Graphics_fillRectangle(&m_sContext, &m_sSky);
    }
    if (m_u32Pixel > 0) {
    Graphics_setForegroundColor(&m_sContext, ClrGreen);
    Graphics_fillRectangle(&m_sContext, &m_sEarth);
    }
    if (m_u32Pixel > PIXEL_MIN and m_u32Pixel < PIXEL_MAX) {
    Graphics_setForegroundColor(&m_sContext, ClrWhite);
    Graphics_drawLine(&m_sContext, PIXEL_MIN, m_u32WhiteLine, PIXEL_MAX, m_u32WhiteLine);
    }
    return(NO_ERR);
}

uint8_t LCD::Delay()
{
    volatile int i;
    for (i=0;i < 1700000 ; i ++);
    return(NO_ERR);

}

uint8_t LCD::RefreshScreen()
{
    m_u32Position = *g_pToData;
    m_u32Pixel  = abs(m_u32Position-MIN_VALUE)*PIXEL_MAX/(MAX_VALUE-MIN_VALUE);

    if (abs(m_sEarth.yMax - m_u32Pixel) > NOISE) {
        m_sSky.yMin = m_u32Pixel+WHITE_LINE;
        m_sEarth.yMax = m_u32Pixel;
        m_u32WhiteLine = m_u32Pixel+NEXT_PIXEL;

        LCD::DrawTitle();
    }
    return(NO_ERR);
}
