/**
 **************************************************************************************************
 * @file        app_vibration_exciter.h
 * @author
 * @app_vibration_exciter
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _APP_VIBRATION_EXCITER_H_
#define _APP_VIBRATION_EXCITER_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    app_vibration_exciter_Modules 
 * @{  
 */

/**
 * @defgroup      app_vibration_exciter_Exported_Macros 
 * @{  
 */


/**
 * @}
 */

/**
 * @defgroup      app_vibration_exciter_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_vibration_exciter_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_vibration_exciter_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_vibration_exciter_Exported_Functions 
 * @{  
 */
void APP_Viration_Exciter_Init(void);
void APP_VirExc_Start(void);
void APP_VirExc_Stop(void);
void APP_VirExc_32Points_Loop(void);  // 312.5us (32point)

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
