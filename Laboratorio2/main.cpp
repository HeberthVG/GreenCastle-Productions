#include "msp.h"
#include "main.hpp"
#include "Scheduler.hpp"
#include "Task.hpp"
#include "LED.hpp"
#include "LCD.hpp"
#include "Accelerometer.hpp"

// ##########################
// Global/Static declarations
// ##########################
uint8_t Task::m_u8NextTaskID = 0; // - Init task ID
volatile static uint64_t g_SystemTicks = 0; // - The system counter.
Scheduler g_MainScheduler; // - Instantiate a Scheduler

// #########################
//          MAIN
// #########################
int main(void)
{

    // - Instantiate two new Tasks
    /*LED BlueLED(BIT2);
    LED GreenLED(BIT1);
    LED RedLED(BIT0);*/
    LCD Display;
    Accelerometer Accel;
    // - Run the overall setup function for the system
    Setup();
    // - Attach the Tasks to the Scheduler;
    //g_MainScheduler.attach(&BlueLED,false,500);
    //g_MainScheduler.attach(&GreenLED,false,500);
    //g_MainScheduler.attach(&RedLED,false,500);
    //g_MainScheduler.attach(&GreenLED,true,NULL);
    //g_MainScheduler.attach(&RedLED,true,NULL);
    g_MainScheduler.attach(&Accel,false,10);
    g_MainScheduler.attach(&Display,true,NULL);
    // - Run the Setup for the scheduler and all tasks
    g_MainScheduler.setup();
    // - Main Loop
    while(1)
    {
    	__wfe(); // Wait for Event
        if(g_SystemTicks != g_MainScheduler.m_u64ticks)
        {
            //Trigger Green LED every 300ms
            /*if(g_SystemTicks%300==0){
                GreenLED.SendMessage(0,1);
            }
            //Trigger Red LED every 800ms
            if(g_SystemTicks%800==0){
                RedLED.SendMessage(0,2);
            }*/
            //- Only execute the tasks if one tick has passed.
            g_MainScheduler.m_u64ticks = g_SystemTicks;
            //l_u32PreviousTick = g_SystemTicks;
            g_MainScheduler.run();
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
	TIMER32_1->LOAD = TIMER32_COUNT; //~1ms ---> a 3Mhz
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
