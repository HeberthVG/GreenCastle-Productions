/*
 * Scheduler.hpp
 *
 *  Created on: Aug 31, 2016
 *      Author: eortiz
 */

#ifndef TASKS_SCHEDULER_HPP_
#define TASKS_SCHEDULER_HPP_
#include "msp.h"
#include "Task.hpp"

#define NUMBER_OF_SLOTS       255
#define NULL                  0
#define MESAGGES_BUFFER_SPACE 1536
#define FREE                  0xFFFFFFFF
#define INITIAL_VALUE         2
// - This structure defines the Task Information
struct st_TaskInfo {
	Task * pToAttach; // - Pointer to the Task
	bool bTriggered;
	uint8_t u8ID;
	uint64_t u64TickInterval; // - How often the task is executed
	uint64_t u64ticks; // - Current tick count
	uint64_t u64TickIntervalInitValue; // - Value to reset
	bool bSignal; // - Trigger the task
	bool bMessage; // - Flag to indicate if there is a message
	uint32_t * pToData; // - Pointer to data received
    uint32_t * pToBuffer; //- Pointer to free space in message buffer
};

class Scheduler
{
public:
    Scheduler();
    uint64_t m_u64ticks;
    uint32_t m_u32MessageBuffer [MESAGGES_BUFFER_SPACE];
    uint16_t m_u16BufferPosition; //- Pointer to free space in message buffer
    uint8_t attach(Task * i_ToAttach, bool i_bTriggered=false, uint64_t i_u64TickInterval = 0);
    uint8_t run(void);
    uint8_t setup(void);
    void CheckMessagesBuffer(void);
    uint8_t InitMessageBuffer(void);
private:
    uint16_t m_u16Counter;
    uint8_t m_u8OpenSlots; // - Available slots
    uint8_t m_u8NextSlot;  // - Next available slot
    st_TaskInfo m_aSchedule[NUMBER_OF_SLOTS]; // - Current schedule to be executed
    st_TaskInfo m_aNextSchedule[NUMBER_OF_SLOTS]; // - Next schedule to be executed (not implemented)
    uint8_t CalculateNextSchedule(void); // - Calculate next schedule tasks (not implemented)
    uint8_t SortScheduleByPriority(Task * i_pSchedule); // - Sorts a schedule based on priority (not implemented)
};



#endif /* TASKS_SCHEDULER_HPP_ */
