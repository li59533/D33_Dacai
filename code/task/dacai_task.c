/**
 **************************************************************************************************
 * @file        dacai_task.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "limits.h"
#include "clog.h"
#include "FreeRTOS.h"

#include "timers.h"
#include "dacai_task.h"
#include "rtos_tools.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "dacai.h"


/**
 * @addtogroup    dacai_task_Modules 
 * @{  
 */

/**
 * @defgroup      dacai_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      dacai_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      dacai_task_Private_Variables 
 * @brief         
 * @{  
 */
TimerHandle_t dacai_task_tim;
TaskHandle_t  Dacai_Task_Handle = NULL;

/**
 * @}
 */
 
/**
 * @defgroup      dacai_task_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

static void dacai_task_tim_callback(TimerHandle_t xTimer);

/**
 * @}
 */

/**
 * @defgroup      dacai_task_Functions 
 * @brief         
 * @{  
 */
//#define 		DACAI_STK_SIZE 		256  							//任务堆栈大小	
//StackType_t 	Dacai_TaskStack[DACAI_STK_SIZE];			//任务堆栈
//StaticTask_t 	Dacai_TaskTCB;												//任务控制块

uint32_t Dacai_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Dacai_Task,\
							"Dacai Task",\
							128,
							NULL,
							3,
							&Dacai_Task_Handle);
	
//	Dacai_Task_Handle=xTaskCreateStatic((TaskFunction_t	)Dacai_Task,		//任务函数
//										(const char* 	)"Dacai Task",		//任务名称
//										(uint32_t 		)DACAI_STK_SIZE,	//任务堆栈大小
//										(void* 		  	)NULL,				//传递给任务函数的参数
//										(UBaseType_t 	) 1, 	//任务优先级
//										(StackType_t*   )Dacai_TaskStack,	//任务堆栈
//										(StaticTask_t*  )&Dacai_TaskTCB);	//任务控制块              
//			
	
	return basetype;
}


void Dacai_Task(void * pvParameter)
{
	uint32_t event_flag = 0;
	
	DEBUG("Dacai Task Enter\r\n");
	UBaseType_t dacaitask_ramainheap = 0;
	
	
	Dacai_Init();
	RTOS_Delay_ms(1000);
	Dacai_SetPowerSaving(1 ,0x0f, 0xff, 30);
	Dacai_SetBuzzer(50);
	while(1)
	{
		xTaskNotifyWait(0x00,ULONG_MAX,&event_flag , portMAX_DELAY);
		
		if((event_flag & DACAI_TASK_TEST_EVENT) != 0x00)
		{
			DEBUG("Dacai Task Looping\r\n");
			dacaitask_ramainheap = uxTaskGetStackHighWaterMark(NULL);
			DEBUG("Dacai Task ramain heap:%d %%\r\n",dacaitask_ramainheap);
	
		}
		if((event_flag & DACAI_TASK_TEST2_EVENT) != 0x00)
		{
			DEBUG("Dacai Task DACAI_TASK_TEST2_EVENT\r\n");
			
		}		
		if((event_flag & DACAI_TASK_REV_EVENT) != 0x00)
		{
			Dacai_RevPorcess();
		}			
		if((event_flag & DACAI_TASK_SEND_EVENT) != 0x00)
		{
			Dacai_Send_Process();
			RTOS_Delay_ms(100);
			//DEBUG("Dacai Task Send EVENT\r\n");
		}			
	}
}


void Dacai_Task_Event_Start(uint32_t events, uint8_t event_from)
{
	switch(event_from)
	{
		case EVENT_FROM_TASK:
		{
			xTaskNotify(Dacai_Task_Handle , events , eSetBits);
		}
		break;
		case EVENT_FROM_ISR:
		{
			xTaskNotifyFromISR(Dacai_Task_Handle, events, eSetBits , NULL);
		}
		break;
		default:break;
	}
}

void Dacai_Task_Tim_Init(void)
{
	dacai_task_tim = xTimerCreate(	"DacaiTimOUT",			/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
									pdMS_TO_TICKS(1000),
									pdFALSE,
									NULL,
									dacai_task_tim_callback );
}

void Dacai_Task_StartTim(uint16_t time_count)
{
	xTimerChangePeriod( dacai_task_tim,  pdMS_TO_TICKS(time_count) , 0 );
	xTimerStart( dacai_task_tim,0);
}
static void dacai_task_tim_callback(TimerHandle_t xTimer)
{
	//Dacai_Task_Event_Start(Dacai_TASK_SEND_AT_EVENT, EVENT_FROM_TASK);
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

