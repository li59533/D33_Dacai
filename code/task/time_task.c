
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
 
//#define 		TIME_STK_SIZE 		512  									//�����ջ��С	
//StackType_t 	Time_TaskStack[TIME_STK_SIZE];								//�����ջ
//StaticTask_t 	Time_TaskTCB;												//������ƿ�



uint32_t Time_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Time_Task,\
							"Time_Task",\
							256,
							NULL,
							1,
							&Time_Task_Handle);
	
//	Time_Task_Handle=xTaskCreateStatic((TaskFunction_t	)Time_Task,		//������
//										(const char* 	)"Time Task",		//��������
//										(uint32_t 		)TIME_STK_SIZE,	//�����ջ��С
//										(void* 		  	)NULL,				//���ݸ��������Ĳ���
//										(UBaseType_t 	) 4, 	//�������ȼ�
//										(StackType_t*   )Time_TaskStack,	//�����ջ
//										(StaticTask_t*  )&Time_TaskTCB);	//������ƿ�              
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




