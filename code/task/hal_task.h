/**
 **************************************************************************************************
 * @file        hal_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _HAL_TASK_H_
#define _HAL_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "rtos_tools.h"
/**
 * @addtogroup    hal_task_Modules 
 * @{  
 */

/**
 * @defgroup      hal_task_Exported_Macros 
 * @{  
 */
#define HAL_TASK_TEST_EVENT 			(0X01 << 0)
#define HAL_TASK_TEST2_EVENT			(0X01 << 1)

#define HAL_TASK_SYS_PARAM_SAVE_EVENT	(0x01 << 2)
/**
 * @}
 */

/**
 * @defgroup      hal_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      hal_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Exported_Variables 
 * @{  
 */
extern TaskHandle_t  Hal_Task_Handle ;
/**
 * @}
 */

/**
 * @defgroup      hal_task_Exported_Functions 
 * @{  
 */
uint32_t Hal_Task_Init(void); 
void Hal_Task(void * pvParameter);
void Hal_Task_Event_Start(uint32_t events, uint8_t event_from);
void Hal_Task_Tim_Init(void);
void Hal_Task_StartTim(uint16_t time_count);

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


