/**
 **************************************************************************************************
 * @file        gui_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _GUI_TASK_H_
#define _GUI_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
 
#include "rtos_tools.h"

/**
 * @addtogroup    gui_task_Modules 
 * @{  
 */

/**
 * @defgroup      gui_task_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gui_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      gui_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gui_task_Exported_Variables 
 * @{  
 */
extern TaskHandle_t  Gui_Task_Handle ;
/**
 * @}
 */

/**
 * @defgroup      gui_task_Exported_Functions 
 * @{  
 */

void Gui_Task(void * pvParameter);	
uint32_t Gui_Task_Init(void);
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


