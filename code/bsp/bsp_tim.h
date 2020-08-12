/**
 **************************************************************************************************
 * @file        bsp_tim.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_TIM_H_
#define _BSP_TIM_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
#include "bsp_conf.h"
/**
 * @addtogroup    bsp_tim_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_tim_Exported_Macros 
 * @{  
 */
#define BSP_TIM_3    0
#define BSP_TIM_8    1
#define BSP_TIM_11   2
#define BSP_TIM_13   3


/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Exported_Functions 
 * @{  
 */

void BSP_TIM_Init(uint8_t Timx);
void BSP_TIM_Start(uint8_t Timx);
void BSP_TIM_Stop(uint8_t Timx);



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
