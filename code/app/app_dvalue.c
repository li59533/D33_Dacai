/**
 **************************************************************************************************
 * @file        app_dvalue.c
 * @author
 * @app_dvalue
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
#include "app_dvalue.h"
#include "bsp_ad7682.h"
#include "app_sw.h"
/**
 * @addtogroup    app_dvalue_Modules 
 * @{  
 */

/**
 * @defgroup      app_dvalue_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       app_dvalue_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_dvalue_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       app_dvalue_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_dvalue_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_dvalue_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_dvalue_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_dvalue_Functions 
 * @brief         
 * @{  
 */
void APP_Dvalue_Init(void)
{
	BSP_AD7682_Init();
	APP_Dvalue_TestPGA(Test_PGA_1);
}

void APP_Dvalue_TestPGA(uint8_t  Test_PGA)
{
	switch(Test_PGA)
	{
		case Test_PGA_1 :
			{
				APP_SW_L(APP_SW_PD1);
				APP_SW_L(APP_SW_PD0);
			}break;
		case Test_PGA_10:	
			{
				APP_SW_H(APP_SW_PD1);
				APP_SW_L(APP_SW_PD0);
			}break;
		case Test_PGA_100:	
			{
				APP_SW_L(APP_SW_PD1);
				APP_SW_H(APP_SW_PD0);
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

