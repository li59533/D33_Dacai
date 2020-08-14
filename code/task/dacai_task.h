/**
 **************************************************************************************************
 * @file        dacai_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _DACAI_TASK_H_
#define _DACAI_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
#include "rtos_tools.h"

/**
 * @addtogroup    dacai_task_Modules 
 * @{  
 */

/**
 * @defgroup      dacai_task_Exported_Macros 
 * @{  
 */
#define DACAI_TASK_TEST_EVENT 			(0X01 << 0)
#define DACAI_TASK_TEST2_EVENT			(0X01 << 1)
#define DACAI_TASK_REV_EVENT			(0X01 << 2)
#define DACAI_TASK_SEND_EVENT			(0X01 << 3)
/**
 * @}
 */

/**
 * @defgroup      dacai_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      dacai_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_task_Exported_Variables 
 * @{  
 */
extern TaskHandle_t  Dacai_Task_Handle ;
/**
 * @}
 */

/**
 * @defgroup      dacai_task_Exported_Functions 
 * @{  
 */
uint32_t Dacai_Task_Init(void); 
void Dacai_Task(void * pvParameter);
void Dacai_Task_Event_Start(uint32_t events, uint8_t event_from);
void Dacai_Task_Tim_Init(void);
void Dacai_Task_StartTim(uint16_t time_count);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
#endif


