/**
 **************************************************************************************************
 * @file        app_cvalue.h
 * @author
 * @app_cvalue
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _APP_CVALUE_H_
#define _APP_CVALUE_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    app_cvalue_Modules 
 * @{  
 */

/**
 * @defgroup      app_cvalue_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_cvalue_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_cvalue_Exported_Types 
 * @{  
 */
typedef struct
{
	float C_value;
	uint8_t range;
	uint8_t schedule;
	uint8_t calc_flag;
}APP_Cvalue_t;
/**
 * @}
 */

/**
 * @defgroup      app_cvalue_Exported_Variables 
 * @{  
 */
extern APP_Cvalue_t APP_Cvalue;
/**
 * @}
 */

/**
 * @defgroup      app_cvalue_Exported_Functions 
 * @{  
 */
void APP_Cvalue_Init(void);
void APP_Cvalue_SW(void);
void APP_Cvalue_Cali(void);
void APP_Cvalue_Measure(void);
void APP_Cvalue_StartCharge(void);
void APP_Cvalue_StartDischarge(void);
void APP_Cvalue_Calc(void);
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
