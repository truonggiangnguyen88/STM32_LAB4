/*
 * scheduler.h
 *
 *  Created on: Nov 4, 2024
 *      Author: ASUS
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>
typedef struct{
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t	RunMe;
	uint32_t TaskID;
} sTask;

#define SCH_MAX_TASKS 5
#define NO_TASK_ID	  0
extern sTask SCH_tasks_G[SCH_MAX_TASKS];
extern uint8_t current_index_task;
extern uint8_t key_index;

void SCH_Init(void);
void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
void SCH_Delete_Task(int task_index);
void SCH_Insert_Task(sTask newTask);

#endif /* INC_SCHEDULER_H_ */
