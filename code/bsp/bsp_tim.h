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

void BSP_TIM_Init(void);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base);
void BSP_TIM8_IRQHandler(void);
void BSP_TIM3_IRQHandler(void);
void BSP_TIM8_Start(void);
void BSP_TIM8_Stop(void);
void BSP_TIM3_Start(void);
void BSP_TIM3_Stop(void);
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
