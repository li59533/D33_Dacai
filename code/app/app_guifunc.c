/**
 **************************************************************************************************
 * @file        app_guifunc.c
 * @author
 * @app_guifunc
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "app_guifunc.h"
#include "app_vibration_exciter.h"
/**
 * @addtogroup    app_guifunc_Modules 
 * @{  
 */

/**
 * @defgroup      app_guifunc_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       app_guifunc_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_guifunc_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       app_guifunc_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_guifunc_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_guifunc_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_guifunc_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_guifunc_Functions 
 * @brief         
 * @{  
 */
// --------- GUI Screen Define ---------- 
#define GUI_TEST_SCREEN		0


// --------------------------------------
// --------- Button Define --------------
#define GUI_TEST1_BUTTON	16
#define GUI_TEST2_BUTTON 	17


// --------------------------------------


void APP_GuiButton_Process(uint16_t screen_id , uint16_t control_id  , uint8_t status)
{
	switch(screen_id)
	{
		case GUI_TEST_SCREEN:
			{
				switch(control_id)
				{
					case GUI_TEST1_BUTTON:
						{
							APP_VirExc_PID_1250();
							DEBUG("GUI_TEST1_BUTTON\r\n");
							
						}break;
					case GUI_TEST2_BUTTON:
						{
							APP_VirExc_PID_50();
							DEBUG("GUI_TEST2_BUTTON\r\n");
						}break;
					default:break;
				}
			}break;
		default:break;
	}
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

