/*
 * scheduler.c
 *
 *  Created on: Nov 4, 2024
 *      Author: ASUS
 */

#include "scheduler.h"
#include "global.h"
sTask SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;
uint8_t key_index = 0;

void SCH_Init(void){
	current_index_task = 0;
	for(int i = 0; i < SCH_MAX_TASKS; i++){
		SCH_Delete_Task(i);
	}
	  //SCH_Add_Task(getKeyInput, 10, 5);
	  SCH_Add_Task(fsm_automatic, 0, 25);
	 // SCH_Add_Task(scan_7SEG, 0, 25);
	  SCH_Add_Task(fsm_setting, 7, 25);
}

void SCH_Delete_Task(int task_index){
	SCH_tasks_G[task_index].Delay = 0;
	SCH_tasks_G[task_index].Period = 0;
	SCH_tasks_G[task_index].RunMe = 0;
	SCH_tasks_G[task_index].TaskID = 0;
	SCH_tasks_G[task_index].pTask = 0x0000;
}

void SCH_Insert_Task(sTask newTask){
	key_index = 0;
	for(int i = 0; i < current_index_task; i++){
		if((newTask.Delay >= SCH_tasks_G[i].Delay) && SCH_tasks_G[i].Period != 0){
			newTask.Delay -= SCH_tasks_G[i].Delay;
			key_index = i + 1;
		}
		else break;
	}
	for(int j = current_index_task; j > key_index; j--){
		if(SCH_tasks_G[j].Period != 0){
			SCH_tasks_G[j].Delay -= newTask.Delay;
			SCH_tasks_G[j] = SCH_tasks_G[j - 1];
		}
	}
	SCH_tasks_G[key_index] = newTask;
}

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	if(current_index_task < SCH_MAX_TASKS){
		sTask newTask;
		newTask.pTask = pFunction;
		newTask.Delay = DELAY;
		newTask.Period = PERIOD;
		newTask.RunMe = 0;
		newTask.TaskID = current_index_task;
		if(current_index_task == 0){
			SCH_tasks_G[0] = newTask;
		}
		else{
			SCH_Insert_Task(newTask);
		}
		current_index_task++;
	}
}

void SCH_Update(){
	if(SCH_tasks_G[0].pTask){
		if(SCH_tasks_G[0].Delay > 0){
			SCH_tasks_G[0].Delay--;
		}
		else{
			SCH_tasks_G[0].RunMe += 1;
			if(SCH_tasks_G[0].Period){
				SCH_tasks_G[0].Delay = SCH_tasks_G[0].Period;
			}
		}
	}
}

void SCH_Dispatch_Tasks(){
	if(SCH_tasks_G[0].RunMe > 0){
		SCH_tasks_G[0].RunMe--;
		(*SCH_tasks_G[0].pTask)();

		sTask completedTask = SCH_tasks_G[0];

		for(int i = 0; i < current_index_task - 1; i++){
			SCH_tasks_G[i] = SCH_tasks_G[i+1];
		}

		SCH_Delete_Task(current_index_task - 1);
		// Nếu task có chu kỳ, thêm lại vào mảng với `Delay` đã đặt lại
		if (completedTask.Period > 0) {
			completedTask.Delay = completedTask.Period;
			SCH_Insert_Task(completedTask);
			current_index_task++;
		}
	}
}




//
//
//void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
//	if(current_index_task < SCH_MAX_TASKS){
//		SCH_tasks_G[current_index_task].pTask = pFunction;
//		SCH_tasks_G[current_index_task].Delay = DELAY;
//		SCH_tasks_G[current_index_task].Period = PERIOD;
//		SCH_tasks_G[current_index_task].RunMe = 0;
//		SCH_tasks_G[current_index_task].TaskID = current_index_task;
//		current_index_task++;
//	}
//}
//
//void SCH_Update(){
//	for(int i = 0; i < current_index_task; i++){
//		if(SCH_tasks_G[i].pTask){
//			if(SCH_tasks_G[i].Delay > 0){
//				SCH_tasks_G[i].Delay--;
//			}
//			else{
//				SCH_tasks_G[i].RunMe += 1;
//				if(SCH_tasks_G[i].Period){
//					SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
//				}
//			}
//		}
//	}
//}
//
//void SCH_Dispatch_Tasks(){
//	for(int i = 0; i < current_index_task; i++){
//		if(SCH_tasks_G[i].RunMe > 0){
//			SCH_tasks_G[i].RunMe--;
//			(*SCH_tasks_G[i].pTask)();
//		}
//	}
//}
