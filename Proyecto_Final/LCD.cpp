/*
 * LCD.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: emanuelhc / hgvalver
 */

#include "LCD.hpp"

LCD::LCD()
{
    SetBlockPosition(&m_sBlock, BORDER_L, NULL, BORDER_L+BLOCK_WIDTH, BLOCK_WIDTH);
    SetBlockPosition(&m_sPlayer, LD_TIRE, BLOCK, LD_TIRE+BLOCK_WIDTH, BLOCK+BLOCK_WIDTH);
    m_u8NextEnemy = 0;
    m_i8Enemy1Pos = NULL;
    m_i8Enemy2Pos = NULL;
    m_i8Enemy3Pos = NULL;
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
    //Graphics_clearDisplay(&m_sContext);
    DrawMap();
    DrawCar(&m_sPlayer, CENTER, BLOCK, ClrBlack);
    return(NO_ERR);
}

uint8_t LCD::OneBlockUp (Graphics_Rectangle *l_pRect)
{
    l_pRect->yMin += BLOCK;
    l_pRect->yMax += BLOCK;
    return(NO_ERR);
}

uint8_t LCD::TwoBlocksUp (Graphics_Rectangle *l_pRect)
{
    l_pRect->yMin += DOUBLE_BLOCK;
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
    SetBlockPosition(&m_sBlock, BORDER_R, NULL, BORDER_R+BLOCK_WIDTH, BLOCK_WIDTH);
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

uint8_t LCD::CreateEnemy(uint8_t l_u8Lane)
{
    m_u8Lane = l_u8Lane;
    // Select the enemy object to use
    switch (m_u8NextEnemy) {
    case ENEMY_1:
        m_pEnemy = &m_sEnemy1;
        m_i8Enemy1Pos = MAX_POS;
        m_u8LaneE1 = m_u8Lane;
        ENEMY_1_IS_ALIVE = true;
        break;
    case ENEMY_2:
        m_pEnemy = &m_sEnemy2;
        m_i8Enemy2Pos = MAX_POS;
        m_u8LaneE2 = m_u8Lane;
        ENEMY_2_IS_ALIVE = true;
        break;
    case ENEMY_3:
        m_pEnemy = &m_sEnemy3;
        m_i8Enemy3Pos = MAX_POS;
        m_u8LaneE3 = m_u8Lane;
        ENEMY_3_IS_ALIVE = true;
        break;
    }
    // Calculate the next enemy object to use
    m_u8NextEnemy++;
    if (m_u8NextEnemy > 2)
        m_u8NextEnemy = 0;
    DrawCar(m_pEnemy, m_u8Lane, MAX_POS, ClrCyan);
    return(NO_ERR);
}

uint8_t LCD::MoveEnemy()
{
    if (ENEMY_1_IS_ALIVE) {
        EraseCar(&m_sEnemy1, m_u8LaneE1, m_i8Enemy1Pos);
        m_i8Enemy1Pos--;
        if (m_i8Enemy1Pos > -13) {
            DrawCar(&m_sEnemy1, m_u8LaneE1, m_i8Enemy1Pos, ClrYellow);
        } else {
            ENEMY_1_IS_ALIVE = false;
        }
    }
    if (ENEMY_2_IS_ALIVE) {
        EraseCar(&m_sEnemy2, m_u8LaneE2, m_i8Enemy2Pos);
        m_i8Enemy2Pos--;
        if (m_i8Enemy2Pos > -13) {
            DrawCar(&m_sEnemy2, m_u8LaneE2, m_i8Enemy2Pos, ClrGreen);
        } else {
            ENEMY_2_IS_ALIVE = false;
        }
    }
    return(NO_ERR);
}

uint8_t LCD::DrawCar(Graphics_Rectangle *l_pRect, uint8_t l_u8Lane, uint8_t l_u8PosY, int32_t l_i32Color)
{
    switch (l_u8Lane) {
    case LEFT:
        m_u8Lane = LD_TIRE_L;
        break;
    case CENTER:
        m_u8Lane = LD_TIRE;
        break;
    case RIGHT:
    default:
        m_u8Lane = LD_TIRE_R;
    }
    SetBlockPosition(l_pRect, m_u8Lane, l_u8PosY, m_u8Lane+BLOCK_WIDTH, l_u8PosY+BLOCK_WIDTH);
    CheckLimitY(l_pRect);
    Graphics_fillRectangle(&m_sContext, l_pRect);
    Graphics_setForegroundColor(&m_sContext, l_i32Color);
    TwoBlocksUp(l_pRect);
    CheckLimitY(l_pRect);
    Graphics_fillRectangle(&m_sContext, l_pRect);
    Graphics_setForegroundColor(&m_sContext, l_i32Color);
    SetBlockPosition(l_pRect, m_u8Lane+DOUBLE_BLOCK, l_u8PosY, m_u8Lane+DOUBLE_BLOCK+BLOCK_WIDTH, l_u8PosY+BLOCK_WIDTH);
    CheckLimitY(l_pRect);
    Graphics_fillRectangle(&m_sContext, l_pRect);
    Graphics_setForegroundColor(&m_sContext, l_i32Color);
    TwoBlocksUp(l_pRect);
    CheckLimitY(l_pRect);
    Graphics_fillRectangle(&m_sContext, l_pRect);
    Graphics_setForegroundColor(&m_sContext, l_i32Color);
    SetBlockPosition(l_pRect, m_u8Lane+BLOCK, l_u8PosY+BLOCK, m_u8Lane+BLOCK+BLOCK_WIDTH, l_u8PosY+BLOCK+BLOCK_WIDTH);
    CheckLimitY(l_pRect);
    Graphics_fillRectangle(&m_sContext, l_pRect);
    Graphics_setForegroundColor(&m_sContext, l_i32Color);
    OneBlockUp(l_pRect);
    CheckLimitY(l_pRect);
    Graphics_fillRectangle(&m_sContext, l_pRect);
    Graphics_setForegroundColor(&m_sContext, l_i32Color);
    OneBlockUp(l_pRect);
    CheckLimitY(l_pRect);
    Graphics_fillRectangle(&m_sContext, l_pRect);
    return(NO_ERR);
}

uint8_t LCD::EraseCar(Graphics_Rectangle *l_pRect, uint8_t l_u8OldPosition, uint8_t l_u8PosY)
{
    LCD::DrawCar(l_pRect, l_u8OldPosition, l_u8PosY, ClrWhite);
    return (NO_ERR);
}

uint8_t LCD::CheckLimitY (Graphics_Rectangle *l_pRect)
{
    if ((l_pRect->yMin < BLOCK) or (l_pRect->yMin > MAX_POS))
        Graphics_setForegroundColor(&m_sContext, ClrWhite);
    return(NO_ERR);
}
