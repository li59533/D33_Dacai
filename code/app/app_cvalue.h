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
	uint8_t status;
	uint32_t range;
	uint8_t schedule;
	uint8_t calc_flag;
	float cali_k;
	
}APP_Cvalue_t;

typedef enum
{
	APP_CVALUE_OVER = 1 ,
	APP_CVALUE_WAIT_CALC ,
	APP_CVALUE_NORMALE,
}app_cvalue_status_e;

typedef enum
{
	APP_CVALUE_UF = 1,
	APP_CVALUE_NF ,
	APP_CVALUE_PF , 
}app_cvalue_range_e;



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
void APP_Cvalue_Loop(void);
void APP_Cvalue_Calc(void);
void APP_Cvalue_CheckV(void);
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
