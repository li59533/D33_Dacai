
/**
 **************************************************************************************************
 * @file        gui_task.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "gui_task.h"
#include "clog.h"
#include "crc.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "app_guifunc.h"
/**
 * @addtogroup    gui_task_Modules 
 * @{  
 */

/**
 * @defgroup      gui_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gui_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      gui_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gui_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      gui_task_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      gui_task_Public_Variables 
 * @brief         
 * @{  
 */
TaskHandle_t  Gui_Task_Handle = NULL;
/**
 * @}
 */

/**
 * @defgroup      gui_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gui_task_Functions 
 * @brief         
 * @{  
 */
 
//#define 		TIME_STK_SIZE 		512  									//任务堆栈大小	
//StackType_t 	Gui_TaskStack[TIME_STK_SIZE];								//任务堆栈
//StaticTask_t 	Gui_TaskTCB;												//任务控制块



uint32_t Gui_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Gui_Task,\
							"Gui_Task",\
							256,
							NULL,
							2,
							&Gui_Task_Handle);
	
//	Gui_Task_Handle=xTaskCreateStatic((TaskFunction_t	)Gui_Task,		//任务函数
//										(const char* 	)"Gui Task",		//任务名称
//										(uint32_t 		)TIME_STK_SIZE,	//任务堆栈大小
//										(void* 		  	)NULL,				//传递给任务函数的参数
//										(UBaseType_t 	) 4, 	//任务优先级
//										(StackType_t*   )Gui_TaskStack,	//任务堆栈
//										(StaticTask_t*  )&Gui_TaskTCB);	//任务控制块              
//		
	
	
	return basetype;
}



void Gui_Task(void * pvParameter)
{
	
	APP_Gui_Init();
	RTOS_Delay_ms(1000);
	APP_Gui_SetParam();
	
	DEBUG("Gui Task Enter\r\n");
	while(1)
	{
		APP_Gui_Loop();
		RTOS_Delay_ms(500);
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




