/**
 **************************************************************************************************
 * @file        virexc_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _VIREXC_TASK_H_
#define _VIREXC_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

#include "rtos_tools.h"

/**
 * @addtogroup    virexc_task_Modules 
 * @{  
 */

/**
 * @defgroup      virexc_task_Exported_Macros 
 * @{  
 */
#define VIREXC_TASK_TEST_EVENT 				(0X01 << 0)
#define VIREXC_TASK_TEST2_EVENT				(0X01 << 1)
#define VIREXC_TASK_PID1250_EVENT			(0X01 << 2)
#define VIREXC_TASK_START_EVENT				(0X01 << 3)

/**
 * @}
 */

/**
 * @defgroup      virexc_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      virexc_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      virexc_task_Exported_Variables 
 * @{  
 */
extern TaskHandle_t  VirExc_Task_Handle ;
/**
 * @}
 */

/**
 * @defgroup      virexc_task_Exported_Functions 
 * @{  
 */
uint32_t VirExc_Task_Init(void); 
void VirExc_Task(void * pvParameter);
void VirExc_Task_Event_Start(uint32_t events, uint8_t event_from);
void VirExc_Task_Tim_Init(void);
void VirExc_Task_StartTim(uint16_t time_count);

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


