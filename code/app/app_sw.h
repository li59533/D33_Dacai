/**
 **************************************************************************************************
 * @file        app_sw.h
 * @author
 * @app_sw
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _APP_SW_H_
#define _APP_SW_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    app_sw_Modules 
 * @{  
 */

/**
 * @defgroup      app_sw_Exported_Macros 
 * @{  
 */

#define APP_SW_COUNT       			8

#define APP_SW_PD0					0
#define APP_SW_PD1					1
#define APP_SW_PD2					2
#define APP_SW_PD3					3
#define APP_SW_PD4					4
#define APP_SW_PC10					5
#define APP_SW_PC11					6
#define APP_SW_PC12					7
/**
 * @}
 */

/**
 * @defgroup      app_sw_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_sw_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_sw_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_sw_Exported_Functions 
 * @{  
 */
void APP_SW_Init(void);
void APP_SW_H(uint8_t bsp_swx);
void APP_SW_L(uint8_t bsp_swx);
void APP_SW_Toggle(uint8_t bsp_swx);
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
