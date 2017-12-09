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
#define BORDER_L        34
#define BORDER_R        90
#define NO_ERR          0
#define LD_TIRE         58
#define LD_TIRE_L       42
#define LD_TIRE_R       74
#define MAX_POS         116
#define LEFT            11
#define CENTER          12
#define RIGHT           10
#define ENEMY_1         0
#define ENEMY_2         1
#define ENEMY_3         2

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
    protected:
    private:
        int8_t *m_pString;
        int8_t m_i8Counter;
        uint8_t m_u8NextEnemy;
        uint8_t m_u8Lane, m_u8LaneE1, m_u8LaneE2, m_u8LaneE3;
        int8_t m_i8Enemy1Pos, m_i8Enemy2Pos, m_i8Enemy3Pos, m_i8EnemyPos;
        bool ENEMY_1_IS_ALIVE, ENEMY_2_IS_ALIVE, ENEMY_3_IS_ALIVE;
};

#endif /* LCD_HPP_ */
