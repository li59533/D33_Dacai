/**
 **************************************************************************************************
 * @file        app_dvalue.h
 * @author
 * @app_dvalue
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _APP_DVALUE_H_
#define _APP_DVALUE_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    app_dvalue_Modules 
 * @{  
 */

/**
 * @defgroup      app_dvalue_Exported_Macros 
 * @{  
 */


/**
 * @}
 */

/**
 * @defgroup      app_dvalue_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_dvalue_Exported_Types 
 * @{  
 */
typedef enum
{
	Test_PGA_1 = 0,
	Test_PGA_10 ,
	Test_PGA_100 , 
}APP_Dvalue_Test_PGA_e;

/**
 * @}
 */

/**
 * @defgroup      app_dvalue_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_dvalue_Exported_Functions 
 * @{  
 */

void APP_Dvalue_Init(void);
void APP_Dvalue_TestPGA(uint8_t  Test_PGA);



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
