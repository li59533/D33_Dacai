/**
 **************************************************************************************************
 * @file        version.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _VERSION_H_
#define _VERSION_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
#include "bsp_conf.h"
/**
 * @addtogroup    version_Modules 
 * @{  
 */

/**
 * @defgroup      version_Exported_Macros 
 * @{  
 */


/**
 * @}
 */

/**
 * @defgroup      version_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Exported_Types 
 * @{  
 */
typedef struct 
{
    GPIO_TypeDef * GPIOx;
    GPIO_InitTypeDef GPIO_Init;
    GPIO_PinState Begin_status;
    /* data */
}BSP_GPIO_Instance_t;
/**
 * @}
 */

/**
 * @defgroup      version_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Exported_Functions 
 * @{  
 */

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
