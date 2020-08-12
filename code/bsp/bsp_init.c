/**
 **************************************************************************************************
 * @file        bsp_init.c
 * @author
 * @bsp_init
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_init.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_adc.h"

#include "app_sw.h"
#include "bsp_tim.h"
#include "bsp_ad7682.h"
/**
 * @addtogroup    bsp_init_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_init_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_init_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_init_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_init_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_init_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_init_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_init_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_init_Functions 
 * @brief         
 * @{  
 */
void BSP_Init(void)
{
	// ---------Test Code -----------
	APP_SW_Init();
	APP_SW_H(0);
	
	BSP_ADC_Init();
	
	// ------------------------------
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

