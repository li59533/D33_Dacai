
/**
 **************************************************************************************************
 * @file        time_task.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "time_task.h"
#include "clog.h"
#include "crc.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "app_dvalue.h"
#include "app_cvalue.h"
/**
 * @addtogroup    time_task_Modules 
 * @{  
 */

/**
 * @defgroup      time_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      time_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      time_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      time_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      time_task_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      time_task_Public_Variables 
 * @brief         
 * @{  
 */
TaskHandle_t  Time_Task_Handle = NULL;
/**
 * @}
 */

/**
 * @defgroup      time_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      time_task_Functions 
 * @brief         
 * @{  
 */
 
//#define 		TIME_STK_SIZE 		512  									//任务堆栈大小	
//StackType_t 	Time_TaskStack[TIME_STK_SIZE];								//任务堆栈
//StaticTask_t 	Time_TaskTCB;												//任务控制块



uint32_t Time_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Time_Task,\
							"Time_Task",\
							256,
							NULL,
							1,
							&Time_Task_Handle);
	
//	Time_Task_Handle=xTaskCreateStatic((TaskFunction_t	)Time_Task,		//任务函数
//										(const char* 	)"Time Task",		//任务名称
//										(uint32_t 		)TIME_STK_SIZE,	//任务堆栈大小
//										(void* 		  	)NULL,				//传递给任务函数的参数
//										(UBaseType_t 	) 4, 	//任务优先级
//										(StackType_t*   )Time_TaskStack,	//任务堆栈
//										(StaticTask_t*  )&Time_TaskTCB);	//任务控制块              
//		
	
	
	return basetype;
}

void Time_Task(void * pvParameter)
{
	DEBUG("Time Task Enter\r\n");
	while(1)
	{
		APP_Dvalue_Loop();
		//APP_Cvalue_Calc();
		RTOS_Delay_ms(20);
	}
}
							

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */




