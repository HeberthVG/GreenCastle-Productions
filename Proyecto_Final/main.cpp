/*
 * main.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: emanuelhc / hgvalver
 */

#include "main.hpp"

// ##########################
// Global/Static declarations
// ##########################
volatile static uint64_t g_SystemTicks = 0; // - The system counter.

// #########################
//          MAIN
// #########################
int main(void)
{
    // - Run the overall setup function for the system
    Setup();

    // Create an object for LCD and run setup function
    LCD l_Display;
    l_Display.Setup();

    l_Display.CreateEnemy(12);
    l_Display.CreateEnemy(11);

    while (1) {
        if (g_SystemTicks == 100) {
            g_SystemTicks = 0;
            l_Display.MoveEnemy();
        }
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
	__enable_irq();

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
