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

// -------------- User Define ----------------
#define APP_SW_C_OR_D				APP_SW_PD4  // 1:measure C , 0:measure D
#define APP_SW_MEASURE_OR_CALI		APP_SW_PD2  // 1:measure   , 0:cali
#define APP_SW_DIS_OR_CHARGE		APP_SW_PD3  // 1:discharge , 0:charge

#define APP_SW_UF					APP_SW_PC10 // 1:OFF , 0:ON
#define APP_SW_NF					APP_SW_PC11 // 1:OFF , 0:ON
#define APP_SW_PF					APP_SW_PC12 // 1:OFF , 0:ON

// -------------------------------------------

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
