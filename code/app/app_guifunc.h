/**
 **************************************************************************************************
 * @file        app_guifunc.h
 * @author
 * @app_guifunc
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _APP_GUIFUNC_H_
#define _APP_GUIFUNC_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
#include "clog.h"
/**
 * @addtogroup    app_guifunc_Modules 
 * @{  
 */

/**
 * @defgroup      app_guifunc_Exported_Macros 
 * @{  
 */


/**
 * @}
 */

/**
 * @defgroup      app_guifunc_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_guifunc_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_guifunc_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_guifunc_Exported_Functions 
 * @{  
 */
void APP_Gui_Init(void);
void APP_Gui_SetParam(void);
void APP_Gui_Button_CB(uint16_t screen_id , uint16_t control_id  , uint8_t status);
void APP_Gui_HandShake_CB(void);
void APP_Gui_Rest_CB(void);


void APP_Gui_Loop(void);   // loop in 20ms
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
