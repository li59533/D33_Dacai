/**
 **************************************************************************************************
 * @file        virexc_task.c
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
#include "virexc_task.h"
#include "rtos_tools.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "app_vibration_exciter.h"
#include "bsp_led.h"
#include "app_dvalue.h"
#include "app_cvalue.h"
/**
 * @addtogroup    virexc_task_Modules 
 * @{  
 */

/**
 * @defgroup      virexc_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      virexc_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      virexc_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      virexc_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      virexc_task_Private_Variables 
 * @brief         
 * @{  
 */
TimerHandle_t virexc_task_tim;
TaskHandle_t  VirExc_Task_Handle = NULL;

/**
 * @}
 */
 
/**
 * @defgroup      virexc_task_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      virexc_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

static void virexc_task_tim_callback(TimerHandle_t xTimer);
/**
 * @}
 */

/**
 * @defgroup      virexc_task_Functions 
 * @brief         
 * @{  
 */
//#define 		VIREXC_STK_SIZE 		256  							//任务堆栈大小	
//StackType_t 	VirExc_TaskStack[VIREXC_STK_SIZE];			//任务堆栈
//StaticTask_t 	VirExc_TaskTCB;												//任务控制块

uint32_t VirExc_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(VirExc_Task,\
							"VirExc Task",\
							2048,
							NULL,
							6,
							&VirExc_Task_Handle);
	
//	VirExc_Task_Handle=xTaskCreateStatic((TaskFunction_t	)VirExc_Task,		//任务函数
//										(const char* 	)"VirExc Task",		//任务名称
//										(uint32_t 		)VIREXC_STK_SIZE,	//任务堆栈大小
//										(void* 		  	)NULL,				//传递给任务函数的参数
//										(UBaseType_t 	) 1, 	//任务优先级
//										(StackType_t*   )VirExc_TaskStack,	//任务堆栈
//										(StaticTask_t*  )&VirExc_TaskTCB);	//任务控制块              
//			
	

	return basetype;
}


void VirExc_Task(void * pvParameter)
{
	uint32_t event_flag = 0;
	
	DEBUG("VirExc Task Enter\r\n");
	UBaseType_t virexctask_ramainheap = 0;

	
	// ------ Init -------
	
	APP_Dvalue_Init();
	APP_Cvalue_Init();
	
	APP_Viration_Exciter_Init();
	VirExc_Task_Tim_Init();
	
	// -------------------
	// ------ Test Code --
	//VirExc_Task_Event_Start(VIREXC_TASK_START_EVENT, EVENT_FROM_TASK);
	APP_VirExc_Start();
	APP_VirExc_PID_Start();
	// -------------------
	
	while(1)
	{
		xTaskNotifyWait(0x00,ULONG_MAX,&event_flag , portMAX_DELAY);
		
		if((event_flag & VIREXC_TASK_TEST_EVENT) != 0x00)
		{
			DEBUG("VirExc Task Looping\r\n");
			virexctask_ramainheap = uxTaskGetStackHighWaterMark(NULL);
			DEBUG("VirExc Task ramain heap:%d %%\r\n",virexctask_ramainheap);
	
		}
		if((event_flag & VIREXC_TASK_START_EVENT) != 0x00)
		{
			DEBUG("VirExc Task VIREXC_TASK_START_EVENT\r\n");
			APP_VirExc_Start();

			BSP_LED_BlinkStandard(BSP_LED_EXCITATION, 0, Blink_LowSpeed);
		}		
		if((event_flag & VIREXC_TASK_PID1250_EVENT) != 0x00)
		{
			DEBUG("VirExc Task PID1250\r\n");
			VirExc_Task_StartTim(100);
		}	
	
		
	}
	
}


void VirExc_Task_Event_Start(uint32_t events, uint8_t event_from)
{
	switch(event_from)
	{
		case EVENT_FROM_TASK:
		{
			xTaskNotify(VirExc_Task_Handle , events , eSetBits);
		}
		break;
		case EVENT_FROM_ISR:
		{
			xTaskNotifyFromISR(VirExc_Task_Handle, events, eSetBits , NULL);
		}
		break;
		default:break;
	}
}

void VirExc_Task_Tim_Init(void)
{
	virexc_task_tim = xTimerCreate(	"VirExcTimOUT",			/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
									pdMS_TO_TICKS(1000),
									pdTRUE,
									NULL,
									virexc_task_tim_callback );
}

void VirExc_Task_StartTim(uint16_t time_count)
{
	xTimerChangePeriod( virexc_task_tim,  pdMS_TO_TICKS(time_count) , 0 );
	xTimerStart( virexc_task_tim,0);
}
static void virexc_task_tim_callback(TimerHandle_t xTimer)
{
	APP_VirExc_PID_Loop();
	//VirExc_Task_Event_Start(VirExc_TASK_SEND_AT_EVENT, EVENT_FROM_TASK);
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

