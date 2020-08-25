
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
 
//#define 		TIME_STK_SIZE 		512  									//�����ջ��С	
//StackType_t 	Gui_TaskStack[TIME_STK_SIZE];								//�����ջ
//StaticTask_t 	Gui_TaskTCB;												//������ƿ�



uint32_t Gui_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Gui_Task,\
							"Gui_Task",\
							256,
							NULL,
							2,
							&Gui_Task_Handle);
	
//	Gui_Task_Handle=xTaskCreateStatic((TaskFunction_t	)Gui_Task,		//������
//										(const char* 	)"Gui Task",		//��������
//										(uint32_t 		)TIME_STK_SIZE,	//�����ջ��С
//										(void* 		  	)NULL,				//���ݸ��������Ĳ���
//										(UBaseType_t 	) 4, 	//�������ȼ�
//										(StackType_t*   )Gui_TaskStack,	//�����ջ
//										(StaticTask_t*  )&Gui_TaskTCB);	//������ƿ�              
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




