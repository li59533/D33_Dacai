/**
 **************************************************************************************************
 * @file        conf_task.c
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
#include "conf_task.h"

/**
 * @addtogroup    XXX 
 * @{  
 */



/**
 * @addtogroup    conf_task_Modules 
 * @{  
 */

/**
 * @defgroup      conf_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      conf_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      conf_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      conf_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      conf_task_Private_Variables 
 * @brief         
 * @{  
 */
TimerHandle_t conf_task_tim;
TaskHandle_t  Conf_Task_Handle = NULL;

/**
 * @}
 */
 
/**
 * @defgroup      conf_task_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      conf_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

static void conf_task_tim_callback(TimerHandle_t xTimer);
/**
 * @}
 */

/**
 * @defgroup      conf_task_Functions 
 * @brief         
 * @{  
 */
//#define 		CONF_STK_SIZE 		256  							//任务堆栈大小	
//StackType_t 	Conf_TaskStack[CONF_STK_SIZE];			//任务堆栈
//StaticTask_t 	Conf_TaskTCB;												//任务控制块

uint32_t Conf_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Conf_Task,\
							"Conf Task",\
							128,
							NULL,
							2,
							&Conf_Task_Handle);
	
//	Conf_Task_Handle=xTaskCreateStatic((TaskFunction_t	)Conf_Task,		//任务函数
//										(const char* 	)"Conf Task",		//任务名称
//										(uint32_t 		)CONF_STK_SIZE,	//任务堆栈大小
//										(void* 		  	)NULL,				//传递给任务函数的参数
//										(UBaseType_t 	) 1, 	//任务优先级
//										(StackType_t*   )Conf_TaskStack,	//任务堆栈
//										(StaticTask_t*  )&Conf_TaskTCB);	//任务控制块              
//			
	
	return basetype;
}


void Conf_Task(void * pvParameter)
{
	uint32_t event_flag = 0;
	
	DEBUG("Conf Task Enter\r\n");
	UBaseType_t conftask_ramainheap = 0;

	while(1)
	{
		xTaskNotifyWait(0x00,ULONG_MAX,&event_flag , portMAX_DELAY);
		
		if((event_flag & CONF_TASK_TEST_EVENT) != 0x00)
		{
			DEBUG("Conf Task Looping\r\n");
			conftask_ramainheap = uxTaskGetStackHighWaterMark(NULL);
			DEBUG("Conf Task ramain heap:%d %%\r\n",conftask_ramainheap);
	
		}
		if((event_flag & CONF_TASK_TEST2_EVENT) != 0x00)
		{
			DEBUG("Conf Task CONF_TASK_TEST2_EVENT\r\n");
			
		}		
		if((event_flag & CONF_TASK_REV_EVENT) != 0x00)
		{
			DEBUG("Conf Task REV EVENT\r\n");
			
		}		
		if((event_flag & CONF_TASK_SEND_EVENT) != 0x00)
		{
			DEBUG("Conf Task SEND EVENT\r\n");
			
		}		
	}
	
}


void Conf_Task_Event_Start(uint32_t events, uint8_t event_from)
{
	switch(event_from)
	{
		case EVENT_FROM_TASK:
		{
			xTaskNotify(Conf_Task_Handle , events , eSetBits);
		}
		break;
		case EVENT_FROM_ISR:
		{
			xTaskNotifyFromISR(Conf_Task_Handle, events, eSetBits , NULL);
		}
		break;
		default:break;
	}
}

void Conf_Task_Tim_Init(void)
{
	conf_task_tim = xTimerCreate(	"ConfTimOUT",			/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
									pdMS_TO_TICKS(1000),
									pdTRUE,
									NULL,
									conf_task_tim_callback );
}

void Conf_Task_StartTim(uint16_t time_count)
{
	xTimerChangePeriod( conf_task_tim,  pdMS_TO_TICKS(time_count) , 0 );
	xTimerStart( conf_task_tim,0);
}
static void conf_task_tim_callback(TimerHandle_t xTimer)
{
	//Conf_Task_Event_Start(Conf_TASK_SEND_AT_EVENT, EVENT_FROM_TASK);
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

