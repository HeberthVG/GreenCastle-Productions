/*
 * LCD.cpp
 *
 *  Created on: Oct 21, 2017
 *      Author: hgvalver
 */

#include "LCD.hpp"

LCD::LCD()
{
    m_sBlue.xMin = 0;
    m_sBlue.yMin = 65;
    m_sBlue.xMax = 127;
    m_sBlue.yMax = 127;
    m_sBrown.xMin = 0;
    m_sBrown.yMin = 0;
    m_sBrown.xMax = 127;
    m_sBrown.yMax = 62;
    m_sWhite.xMin = 0;
    m_sWhite.yMin = 63;
    m_sWhite.xMax = 127;
    m_sWhite.yMax = 64;
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
    LCD::DrawTitle();
    return(NO_ERR);
}

uint8_t LCD::DrawTitle()
{
    Graphics_setForegroundColor(&m_sContext, ClrBlue);
    Graphics_fillRectangle(&m_sContext, &m_sBlue);
    Graphics_setForegroundColor(&m_sContext, ClrBrown);
    Graphics_fillRectangle(&m_sContext, &m_sBrown);
    Graphics_setForegroundColor(&m_sContext, ClrWhite);
    Graphics_fillRectangle(&m_sContext, &m_sWhite);
    //Delay();
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
    m_u32Pixel  = (m_u32Position-MIN_VALUE)*MAX_NUMBER_PIXEL/(MAX_VALUE-MIN_VALUE);
    m_sBlue.yMin = m_u32Pixel+WHITE_LINE;
    m_sBrown.yMax = m_u32Pixel;
    m_sWhite.yMin = m_u32Pixel+NEXT_PIXEL;
    m_sWhite.yMax = m_u32Pixel+WHITE_LINE-NEXT_PIXEL;
    LCD::DrawTitle();
    return(NO_ERR);
}
