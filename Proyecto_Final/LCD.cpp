/*
 * LCD.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: emanuelhc / hgvalver
 */

#include "LCD.hpp"

LCD::LCD()
{
    SetBlockPosition(&m_sBlock, NULL, NULL, BLOCK_WIDTH, BLOCK_WIDTH);
    SetBlockPosition(&m_sPlayer, LD_TIRE, BLOCK, LD_TIRE+BLOCK_WIDTH, BLOCK+BLOCK_WIDTH);
    m_u8NextEnemy = 0;
}

uint8_t LCD::Setup()
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
    DrawMap();
    DrawPlayer();
    return(NO_ERR);
}

uint8_t LCD::OneBlockUp (Graphics_Rectangle *l_pRect)
{
    l_pRect->xMin += BLOCK;
    l_pRect->yMin += BLOCK;
    l_pRect->xMax += BLOCK;
    l_pRect->yMax += BLOCK;
    return(NO_ERR);
}

uint8_t LCD::TwoBlocksUp (Graphics_Rectangle *l_pRect)
{
    l_pRect->xMin += DOUBLE_BLOCK;
    l_pRect->yMin += DOUBLE_BLOCK;
    l_pRect->xMax += DOUBLE_BLOCK;
    l_pRect->yMax += DOUBLE_BLOCK;
    return(NO_ERR);
}

uint8_t LCD::SetBlockPosition (Graphics_Rectangle *l_pRect, int16_t l_i16XMin, int16_t l_i16YMin, int16_t l_i16XMax, int16_t l_i16YMax)
{
    l_pRect->xMin = l_i16XMin;
    l_pRect->yMin = l_i16YMin;
    l_pRect->xMax = l_i16XMax;
    l_pRect->yMax = l_i16YMax;
    return(NO_ERR);
}

uint8_t LCD::DrawMap()
{
    Graphics_setForegroundColor(&m_sContext, ClrBlack);
    DrawBorder();
    SetBlockPosition(&m_sBlock, BORDER, NULL, BORDER+BLOCK_WIDTH, BLOCK_WIDTH);
    DrawBorder();
    return(NO_ERR);
}

uint8_t LCD::DrawBorder()
{
    for (m_i8Counter=0; m_i8Counter<10; m_i8Counter++) {
        OneBlockUp(&m_sBlock);
        Graphics_fillRectangle(&m_sContext, &m_sBlock);
        OneBlockUp(&m_sBlock);
        Graphics_fillRectangle(&m_sContext, &m_sBlock);
        OneBlockUp(&m_sBlock);
    }
    return(NO_ERR);
}

uint8_t LCD::DrawPlayer()
{
    Graphics_fillRectangle(&m_sContext, &m_sPlayer);
    TwoBlocksUp(&m_sPlayer);
    Graphics_fillRectangle(&m_sContext, &m_sPlayer);
    SetBlockPosition(&m_sPlayer, LD_TIRE+DOUBLE_BLOCK, BLOCK, LD_TIRE+DOUBLE_BLOCK+BLOCK_WIDTH, BLOCK+BLOCK_WIDTH);
    Graphics_fillRectangle(&m_sContext, &m_sPlayer);
    TwoBlocksUp(&m_sPlayer);
    Graphics_fillRectangle(&m_sContext, &m_sPlayer);
    SetBlockPosition(&m_sPlayer, LD_TIRE+BLOCK, DOUBLE_BLOCK, LD_TIRE+BLOCK+BLOCK_WIDTH, DOUBLE_BLOCK+BLOCK_WIDTH);
    Graphics_fillRectangle(&m_sContext, &m_sPlayer);
    OneBlockUp(&m_sPlayer);
    Graphics_fillRectangle(&m_sContext, &m_sPlayer);
    OneBlockUp(&m_sPlayer);
    Graphics_fillRectangle(&m_sContext, &m_sPlayer);
    return(NO_ERR);
}

uint8_t LCD::DrawEnemy()
{
    // Select the enemy object to use
    switch (m_u8NextEnemy) {
    case 0:
        m_pEnemy = &m_sEnemy1;
        break;
    case 1:
        m_pEnemy = &m_sEnemy2;
        break;
    case 2:
    default:
        m_pEnemy = &m_sEnemy3;
    }
    // Calculate the next enemy object to use
    m_u8NextEnemy++;
    if (m_u8NextEnemy > 2)
        m_u8NextEnemy = 0;
    // Draw the enemy
    SetBlockPosition(m_pEnemy, LD_TIRE_L, MAX_POS, LD_TIRE_L+BLOCK_WIDTH, MAX_POS+BLOCK_WIDTH);
    Graphics_fillRectangle(&m_sContext, &m_sPlayer);
    SetBlockPosition(m_pEnemy, LD_TIRE_R, MAX_POS, LD_TIRE_R+BLOCK_WIDTH, MAX_POS+BLOCK_WIDTH);
    Graphics_fillRectangle(&m_sContext, &m_sPlayer);
    return(NO_ERR);
}
