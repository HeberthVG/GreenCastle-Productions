/*
 * main.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: emanuelhc / hgvalver
 */

#include "main.hpp"

// #########################
//          MAIN
// #########################
int main(void)
{
    // - Run the overall setup function for the system
    Setup();

    // Create an object for LCD
    LCD l_Display;
    // Create an object for random data
    RandomData l_Data;

    // Run setup functions
    l_Display.Setup();
    l_Data.Setup();

    // Enable interruptions
    __enable_irq();

    // Main Loop
    while (g_bGameOver == false) {
        // Update the score
        if (g_SystemTicks>=REFRESH*g_u8Level) {
            g_bNewEnemy = l_Data.NewEnemy(g_u8Level);
            g_u32Score++;
            g_SystemTicks = 0;
        }
        // Refresh the value of score and speed
        if (g_SystemTicks%REFRESH==0)
            l_Display.RefreshData(g_u32Score, g_u8Speed);
        // Selects the lane of new enemy and creates it
        if (g_bNewEnemy) {
            l_Display.CreateEnemy(l_Data.Lane());
            g_bNewEnemy = false;
        }
        // Move the enemies
        if (g_SystemTicks%g_u8Level==0)
            l_Display.MoveEnemy();
        g_bGameOver = l_Display.IsGameOver();
    }
}

void GetSpeed(void)
{
    if(g_bLevelChanged == true) {
        switch (g_u8Level) {
        case LVL1:
            g_u8Speed = 1;
            break;
        case LVL2:
            g_u8Speed = 2;
            break;
        case LVL3:
            g_u8Speed = 3;
            break;
        case LVL4:
            g_u8Speed = 4;
            break;
        case LVL5:
            g_u8Speed = 5;
            break;
        default:
            g_u8Speed = 1;
        }
        g_bLevelChanged = false;
    }
}
// **********************************
// Setup function for the application
// @input - none
// @output - none
// **********************************
void Setup(void)
{
	// ****************************
	//         DEVICE CONFIG
	// ****************************
	// - Disable WDT
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

	// ****************************
	//       TIMER CONFIG
	// ****************************
	// - Configure Timer32_1  with MCLK (3Mhz), Division by 1, Enable the interrupt, Periodic Mode
	// - Enable the interrupt in the NVIC
	// - Start the timer in UP mode.
	// - Re-enable interrupts
	TIMER32_1->LOAD = TIMER32_COUNT; //~1ms ---> a 48Mhz
	TIMER32_1->CONTROL = TIMER32_CONTROL_SIZE | TIMER32_CONTROL_PRESCALE_0 | TIMER32_CONTROL_MODE | TIMER32_CONTROL_IE | TIMER32_CONTROL_ENABLE;
	NVIC_SetPriority(T32_INT1_IRQn,1);
	NVIC_EnableIRQ(T32_INT1_IRQn);

	/* Variables config */
	g_u32Score = 0;
	g_u8Level = LVL3;
	g_bLevelChanged = true;
	g_bGameOver = false;
	g_bNewEnemy = false;
	GetSpeed();
	return;
}

extern "C"
{
    // - Handle the Timer32 Interrupt
	void T32_INT1_IRQHandler(void)
	{
		TIMER32_1->INTCLR = 0U;
		g_SystemTicks++;
		return;
	}
}
