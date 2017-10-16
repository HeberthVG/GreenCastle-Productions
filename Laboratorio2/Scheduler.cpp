#include "Scheduler.hpp"

// - Scheduler constructor
Scheduler::Scheduler()
{
    m_u8OpenSlots = static_cast<uint8_t>(NUMBER_OF_SLOTS);
    m_u8NextSlot = 0;
    for(int index = 0; index < NUMBER_OF_SLOTS; index++)
    {
        m_aSchedule[index].pToAttach = (uintptr_t) 0; // Init to an invalid pointer
    }
    Scheduler::InitMessageBuffer();
    return;
}
// - Initialize message buffer with null data
uint8_t Scheduler::InitMessageBuffer(void)
{
    uint8_t l_u8ReturnCode = NO_ERR;
    for(int i=0; i<=MESAGGES_BUFFER_SPACE; i++)
    {
        m_u32MessageBuffer[i] = FREE;
    }
    m_u16BufferPosition = 0;
    return l_u8ReturnCode;
}
// - The attach function, inserts the task into the schedule slots.
uint8_t Scheduler::attach(Task * i_ToAttach, bool i_bTriggered, uint64_t i_u64TickInterval)
{
    uint8_t l_ErrorCode = NO_ERR;
    st_TaskInfo l_st_StructToAttach;

    l_st_StructToAttach.pToAttach = i_ToAttach;
    l_st_StructToAttach.u64ticks = this->m_u64ticks;
    l_st_StructToAttach.u64TickInterval = 0;
	l_st_StructToAttach.u64TickIntervalInitValue = i_u64TickInterval;
    l_st_StructToAttach.bTriggered = i_bTriggered;

    if((m_u8OpenSlots>0) && (m_u8NextSlot < NUMBER_OF_SLOTS))
    {
        m_aSchedule[m_u8NextSlot] =  l_st_StructToAttach;
        l_st_StructToAttach.u8ID = m_u8NextSlot;
        m_u8OpenSlots--;
        m_u8NextSlot++;
    }
    else
    {
        l_ErrorCode = RET_ERR;
    }
    return l_ErrorCode;
}
void Scheduler::CheckMessagesBuffer()
{
    m_u16Counter = 0;
    while((m_u32MessageBuffer[m_u16Counter]!=FREE) and (m_u16Counter<MESAGGES_BUFFER_SPACE))
    {
        switch(m_u32MessageBuffer[m_u16Counter]){
        case 0:
            m_aSchedule[m_u32MessageBuffer[m_u16Counter+1]].bSignal = true;
            break;
        case 1:
            m_aSchedule[m_u32MessageBuffer[m_u16Counter+1]].bSignal = true;
            m_aSchedule[m_u32MessageBuffer[m_u16Counter+1]].bMessage = true;
            m_aSchedule[m_u32MessageBuffer[m_u16Counter+1]].pToData = (uint32_t *) m_u32MessageBuffer[m_u16Counter+2];
            break;
        case 2:
            m_aSchedule[m_u32MessageBuffer[m_u16Counter+1]].bMessage = true;
            m_aSchedule[m_u32MessageBuffer[m_u16Counter+1]].pToData = (uint32_t *) m_u32MessageBuffer[m_u16Counter+2];
        }
        m_u32MessageBuffer[m_u16Counter] = FREE;
        m_u16Counter+=3;
    }
    g_pToType = &m_u32MessageBuffer[0];
    g_pToID   = &m_u32MessageBuffer[1];
    g_pToData = &m_u32MessageBuffer[2];
}
// - Execute the current schedule
uint8_t Scheduler::run(void)
{
    int l_iNextTaskSlot = 0U;
    Task * l_pNextTask = (uintptr_t) 0;
    uint8_t l_u8ReturnCode = NO_ERR;

    Scheduler::CheckMessagesBuffer();

    while(l_iNextTaskSlot < NUMBER_OF_SLOTS)
    {
    	l_pNextTask = static_cast<Task *> (m_aSchedule[l_iNextTaskSlot].pToAttach);
		if(l_pNextTask != ((uintptr_t) 0))
		{
		    if (m_aSchedule[l_iNextTaskSlot].bTriggered == true){
		        if(m_aSchedule[l_iNextTaskSlot].bSignal == true){
		            l_pNextTask->run();
		            m_aSchedule[l_iNextTaskSlot].bSignal = false;
		        }
		    }
		    else{
		        if(m_aSchedule[l_iNextTaskSlot].u64TickInterval == 0){
                    l_pNextTask->run();
		        }
		        m_aSchedule[l_iNextTaskSlot].u64TickInterval ++;

		        if(m_aSchedule[l_iNextTaskSlot].u64TickInterval > m_aSchedule[l_iNextTaskSlot].u64TickIntervalInitValue) {
		            m_aSchedule[l_iNextTaskSlot].u64TickInterval = 0;
		        }
		    }
		}
		l_iNextTaskSlot++;
    }
    CalculateNextSchedule(); // TODO

    return l_u8ReturnCode;
}
// - Execute the setup function for all tasks
uint8_t Scheduler::setup(void)
{
    int l_iNextTaskSlot = 0U;
    g_pToType = &m_u32MessageBuffer[0];
    g_pToID   = &m_u32MessageBuffer[1];
    g_pToData = &m_u32MessageBuffer[2];
    Task * l_pNextTask = (uintptr_t) 0;
    uint8_t l_u8ReturnCode = NO_ERR;

    while(l_iNextTaskSlot < NUMBER_OF_SLOTS)
    {
        l_pNextTask = static_cast<Task *> (m_aSchedule[l_iNextTaskSlot].pToAttach);
        if(l_pNextTask != ((uintptr_t) 0))
        {
            l_pNextTask->setup();
        }
        l_iNextTaskSlot++;
    }
    return l_u8ReturnCode;
}

uint8_t Scheduler::CalculateNextSchedule(void)
{
    return(NO_ERR);
}
uint8_t Scheduler::SortScheduleByPriority(Task * i_pSchedule)
{
    return(NO_ERR);
}
