/*
 * LCD.hpp
 *
 *  Created on: Dec 5, 2017
 *      Author: emanuelhc / hgvalver
 */

#ifndef LCD_HPP_
#define LCD_HPP_

#define SPEED           "Speed"
#define SPEED_X         110
#define SCORE           "Score"
#define SCORE_X         17
#define TEXT_Y          58
#define VALUE_Y         68
#define BLOCK_WIDTH     3
#define SPACE           2
#define NULL            0
#define INITIAL_CAR     120
#define BLOCK           4
#define DOUBLE_BLOCK    8
#define BORDER_L        34
#define BORDER_R        90
#define NO_ERR          0
#define ERR_ENEMY       1
#define LD_TIRE         58
#define LD_TIRE_L       42
#define LD_TIRE_R       74
#define MAX_POS         4
#define LEFT            1
#define CENTER          2
#define RIGHT           0
#define ENEMY_1         0
#define ENEMY_2         1
#define ENEMY_3         2
#define COLISION        97
#define LIMIT_Y         127
#define ENEMY1_CLR      ClrHoneydew
#define ENEMY2_CLR      ClrMediumSeaGreen
#define ENEMY3_CLR      ClrPaleTurquoise

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
        uint8_t CreateEnemy(uint8_t l_u8Lane);
        uint8_t MoveEnemy(void);
        uint8_t MovePlayer(void);
        uint8_t OneBlockUp(Graphics_Rectangle *l_pRect);
        uint8_t TwoBlocksUp(Graphics_Rectangle *l_pRect);
        uint8_t SetBlockPosition(Graphics_Rectangle *l_pRect, int16_t l_i16XMin, int16_t l_i16YMin, int16_t l_i16XMax, int16_t l_i16YMax);
        uint8_t Setup(void);
        uint8_t DrawCar(Graphics_Rectangle *l_pRect, uint8_t l_u8Lane, uint8_t l_u8PosY, int32_t l_iColor);
        uint8_t EraseCar(Graphics_Rectangle *l_pRect, uint8_t l_u8OldPosition, uint8_t l_u8PosY);
        uint8_t CheckLimitY (Graphics_Rectangle *l_pRect);
        uint8_t RefreshData (uint32_t m_u32Score, uint8_t m_u8Speed);
        uint8_t CarCrashed (Graphics_Rectangle *l_pRect);
        int32_t IsRectangleOverlap(Graphics_Rectangle *rect1, Graphics_Rectangle *rect2);
        bool IsGameOver (void);
    protected:
    private:
        int8_t *m_pString;
        int8_t m_i8Counter;
        uint8_t m_u8NextEnemy, m_u8Lane, m_u8LaneE1, m_u8LaneE2, m_u8LaneE3;
        int8_t m_i8Enemy1Pos, m_i8Enemy2Pos, m_i8Enemy3Pos, m_i8EnemyPos;
        char c_Data[32];
        bool ENEMY_1_IS_ALIVE, ENEMY_2_IS_ALIVE, ENEMY_3_IS_ALIVE;
        uint32_t m_u32GameOver, m_u32Color;
        bool m_bGameOver;
};

#endif /* LCD_HPP_ */
