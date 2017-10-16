#include "Task.hpp"

Task::Task()
{
    m_u8TaskID = m_u8NextTaskID;
    m_u8NextTaskID++;
    m_bIsFinished = false;
}

uint8_t Task::SendMessage(uint32_t i_u32Type, uint32_t i_u32ID)
{
    *g_pToType = i_u32Type;
    *g_pToID   = i_u32ID;
    g_pToType+=NEXT_POINTER;
    g_pToID+=NEXT_POINTER;
    return NO_ERR;
}

uint8_t Task::SendMessage(uint32_t i_u32Type, uint32_t i_u32ID, uint32_t i_u32PointerToData)
{
    *g_pToType = i_u32Type;
    *g_pToID   = i_u32ID;
    *g_pToData = i_u32PointerToData;
    return NO_ERR;
}
