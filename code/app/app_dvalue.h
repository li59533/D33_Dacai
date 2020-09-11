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

typedef struct
{
	float D_value;
	uint8_t mul;
	uint8_t schedule;
	uint8_t calc_flag;
	uint8_t cali_flag;
	float cali_mv;
}APP_Dvalue_t;



/**
 * @}
 */

/**
 * @defgroup      app_dvalue_Exported_Variables 
 * @{  
 */
extern APP_Dvalue_t APP_Dvalue ;
/**
 * @}
 */

/**
 * @defgroup      app_dvalue_Exported_Functions 
 * @{  
 */

void APP_Dvalue_Init(void);
void APP_Dvalue_SW(void);
void APP_Dvalue_TestPGA(uint8_t  Test_PGA);
void APP_Dvalue_Calc(void);
void APP_Dvalue_Cali(void);
void APP_Dvalue_Loop(void);
void APP_Dvalue_Report_data(void);
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
