/**
 **************************************************************************************************
 * @file        time_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _TIME_TASK_H_
#define _TIME_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
 
#include "rtos_tools.h"

/**
 * @addtogroup    time_task_Modules 
 * @{  
 */

/**
 * @defgroup      time_task_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      time_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      time_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      time_task_Exported_Variables 
 * @{  
 */
extern TaskHandle_t  Time_Task_Handle ;
/**
 * @}
 */

/**
 * @defgroup      time_task_Exported_Functions 
 * @{  
 */

void Time_Task(void * pvParameter);	
uint32_t Time_Task_Init(void);
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


