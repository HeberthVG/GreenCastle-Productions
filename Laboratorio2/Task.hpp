#ifndef TASK_HPP_
#define TASK_HPP_

#include "msp.h"

#define NO_ERR                     0
#define RET_ERR                    1
#define NEXT_POINTER               3
#define TYPE_TRIGGER_AND_DATA      1
#define TO_LCD                     4

uint32_t    *g_pToType, *g_pToID, *g_pToData;

class Task
{
	public:
		Task();
		uint8_t m_u8TaskID;
		virtual uint8_t     run(void){return(0);};
		virtual uint8_t     setup(void){return(0);};
        uint8_t             SendMessage(uint32_t i_u32Type, uint32_t i_u32ID);
		uint8_t             SendMessage(uint32_t i_u32Type, uint32_t i_u32ID, uint32_t i_u32PointerToData);
		bool                IsTaskFinished(void){return m_bIsFinished;};
		uint8_t             GetTaskPriority(void) {return m_u8Priority;};
		void                SetTaskPriority(uint8_t i_u8NewPriority){m_u8Priority = i_u8NewPriority;};
	private:
	   static uint8_t m_u8NextTaskID;
	   uint8_t m_u8Priority;
	protected:
	   bool m_bIsFinished;
};

#endif /* TASK_HPP_ */
