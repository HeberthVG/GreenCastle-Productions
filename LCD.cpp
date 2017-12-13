/*
 * LCD.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: emanuelhc / hgvalver
 */

#include "LCD.hpp"

LCD::LCD()
{
    SetBlockPosition(&m_sBlock, BORDER_L, INITIAL_CAR+BLOCK, BORDER_L+BLOCK_WIDTH, INITIAL_CAR+BLOCK-BLOCK_WIDTH);
    m_u8NextEnemy = NULL;
    m_i8Enemy1Pos = NULL;
    m_i8Enemy2Pos = NULL;
    m_i8Enemy3Pos = NULL;
    m_u32GameOver = NULL;
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
    /* Configures graphics context */
    Graphics_setBackgroundColor(&m_sContext, GRAPHICS_COLOR_WHITE);
    GrContextFontSet(&m_sContext, &g_sFontFixed6x8);
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    /* Draw Initial Graphics */
    DrawMap();
    DrawCar(&m_sPlayer, CENTER, INITIAL_CAR, ClrBlack);
    Graphics_setForegroundColor(&m_sContext, ClrRed);
    Graphics_drawStringCentered(&m_sContext, (int8_t *)SCORE, GRAPHICS_AUTO_STRING_LENGTH, SCORE_X, TEXT_Y, OPAQUE_TEXT);
    Graphics_drawStringCentered(&m_sContext, (int8_t *)SPEED, GRAPHICS_AUTO_STRING_LENGTH, SPEED_X, TEXT_Y, OPAQUE_TEXT);
    return(NO_ERR);
}

uint8_t LCD::OneBlockUp (Graphics_Rectangle *l_pRect)
{
    l_pRect->yMin -= BLOCK;
    l_pRect->yMax -= BLOCK;
    return(NO_ERR);
}

uint8_t LCD::TwoBlocksUp (Graphics_Rectangle *l_pRect)
{
    l_pRect->yMin -= DOUBLE_BLOCK;
    l_pRect->yMax -= DOUBLE_BLOCK;
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
    SetBlockPosition(&m_sBlock, BORDER_R, INITIAL_CAR+BLOCK, BORDER_R+BLOCK_WIDTH, INITIAL_CAR+BLOCK-BLOCK_WIDTH);
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
    if (!ENEMY_1_IS_ALIVE or !ENEMY_2_IS_ALIVE or !ENEMY_3_IS_ALIVE) {
        switch (m_u8NextEnemy) {
        case ENEMY_1:
            m_pEnemy = &m_sEnemy1;
            m_i8Enemy1Pos = BLOCK;
            m_u8LaneE1 = m_u8Lane;
            ENEMY_1_IS_ALIVE = true;
            m_u32Color = ENEMY1_CLR;
            break;
        case ENEMY_2:
            m_pEnemy = &m_sEnemy2;
            m_i8Enemy2Pos = BLOCK;
            m_u8LaneE2 = m_u8Lane;
            ENEMY_2_IS_ALIVE = true;
            m_u32Color = ENEMY2_CLR;
            break;
        case ENEMY_3:
        default:
            m_pEnemy = &m_sEnemy3;
            m_i8Enemy3Pos = BLOCK;
            m_u8LaneE3 = m_u8Lane;
            ENEMY_3_IS_ALIVE = true;
            m_u32Color = ENEMY3_CLR;
        }
        // Calculate the next enemy object to use
        m_u8NextEnemy++;
        if (m_u8NextEnemy > 2)
            m_u8NextEnemy = 0;
        DrawCar(m_pEnemy, m_u8Lane, DOUBLE_BLOCK, m_u32Color);
        return(NO_ERR);
    } else {
        return(ERR_ENEMY);
    }
}

uint8_t LCD::MoveEnemy()
{
    if (ENEMY_1_IS_ALIVE) {
        EraseCar(&m_sEnemy1, m_u8LaneE1, m_i8Enemy1Pos);
        m_i8Enemy1Pos++;
        if (m_i8Enemy1Pos < LIMIT_Y) {
            DrawCar(&m_sEnemy1, m_u8LaneE1, m_i8Enemy1Pos, ENEMY1_CLR);
            CarCrashed(&m_sEnemy1);
        } else {
            ENEMY_1_IS_ALIVE = false;
        }
    }
    if (ENEMY_2_IS_ALIVE) {
        EraseCar(&m_sEnemy2, m_u8LaneE2, m_i8Enemy2Pos);
        m_i8Enemy2Pos++;
        if (m_i8Enemy2Pos < LIMIT_Y) {
            DrawCar(&m_sEnemy2, m_u8LaneE2, m_i8Enemy2Pos, ENEMY2_CLR);
            CarCrashed(&m_sEnemy2);
        } else {
            ENEMY_2_IS_ALIVE = false;
        }
    }
    if (ENEMY_3_IS_ALIVE) {
        EraseCar(&m_sEnemy3, m_u8LaneE3, m_i8Enemy3Pos);
        m_i8Enemy3Pos++;
        if (m_i8Enemy3Pos < LIMIT_Y) {
            DrawCar(&m_sEnemy3, m_u8LaneE3, m_i8Enemy3Pos, ENEMY3_CLR);
            CarCrashed(&m_sEnemy3);
        } else {
            ENEMY_3_IS_ALIVE = false;
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
    Graphics_setForegroundColor(&m_sContext, l_i32Color);
    SetBlockPosition(l_pRect, m_u8Lane, l_u8PosY, m_u8Lane+BLOCK_WIDTH, l_u8PosY-BLOCK_WIDTH);
    CheckLimitY(l_pRect);
    Graphics_fillRectangle(&m_sContext, l_pRect);
    Graphics_setForegroundColor(&m_sContext, l_i32Color);
    TwoBlocksUp(l_pRect);
    CheckLimitY(l_pRect);
    Graphics_fillRectangle(&m_sContext, l_pRect);
    Graphics_setForegroundColor(&m_sContext, l_i32Color);
    SetBlockPosition(l_pRect, m_u8Lane+DOUBLE_BLOCK, l_u8PosY, m_u8Lane+DOUBLE_BLOCK+BLOCK_WIDTH, l_u8PosY-BLOCK_WIDTH);
    CheckLimitY(l_pRect);
    Graphics_fillRectangle(&m_sContext, l_pRect);
    Graphics_setForegroundColor(&m_sContext, l_i32Color);
    TwoBlocksUp(l_pRect);
    CheckLimitY(l_pRect);
    Graphics_fillRectangle(&m_sContext, l_pRect);
    Graphics_setForegroundColor(&m_sContext, l_i32Color);
    SetBlockPosition(l_pRect, m_u8Lane+BLOCK, l_u8PosY-BLOCK, m_u8Lane+BLOCK+BLOCK_WIDTH, l_u8PosY-BLOCK-BLOCK_WIDTH);
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
    if ((l_pRect->yMin > INITIAL_CAR) or (l_pRect->yMin < DOUBLE_BLOCK))
        Graphics_setForegroundColor(&m_sContext, ClrWhite);
    return(NO_ERR);
}

uint8_t LCD::RefreshData (uint32_t l_u32Score, uint8_t l_u8Speed)
{
    Graphics_setForegroundColor(&m_sContext, ClrGray);
    sprintf(c_Data, "%5d", l_u32Score);
    Graphics_drawStringCentered(&m_sContext, (int8_t *) c_Data, GRAPHICS_AUTO_STRING_LENGTH, SCORE_X, VALUE_Y, OPAQUE_TEXT);
    sprintf(c_Data, "%5d", l_u8Speed);
    Graphics_drawStringCentered(&m_sContext, (int8_t *) c_Data, GRAPHICS_AUTO_STRING_LENGTH, SPEED_X, VALUE_Y, OPAQUE_TEXT);
    return(NO_ERR);
}

uint8_t LCD::CarCrashed (Graphics_Rectangle *l_pRect)
{
    if (m_u32GameOver == NULL)
        m_u32GameOver = IsRectangleOverlap(l_pRect, &m_sPlayer);
    return(NO_ERR);
}

bool LCD::IsGameOver ()
{
    if (m_u32GameOver == NULL)
        m_bGameOver = false;
    else {
        m_bGameOver = true;
    }
    return(m_bGameOver);
}

int32_t LCD::IsRectangleOverlap(Graphics_Rectangle *rect1, Graphics_Rectangle *rect2)
{
    if ((((rect1->xMin <= rect2->xMin) and (rect2->xMin <= rect1->xMax)) or
         ((rect1->xMin <= rect2->xMax) and (rect2->xMax <= rect1->xMax))) and
        rect1->yMin==COLISION) {
        return(1);
    } else {
        return(0);
    }
}
