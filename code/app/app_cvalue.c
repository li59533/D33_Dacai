/**
 **************************************************************************************************
 * @file        app_cvalue.c
 * @author
 * @app_cvalue
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
#include "app_cvalue.h"
#include "app_sw.h"
#include "app_dvalue.h"
#include "bsp_ad7682.h"
#include "bsp_tim.h"
#include "clog.h"
/**
 * @addtogroup    app_cvalue_Modules 
 * @{  
 */

/**
 * @defgroup      app_cvalue_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       app_cvalue_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_cvalue_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       app_cvalue_Private_Types
 * @brief         
 * @{  
 */
typedef enum
{
	APP_CVALUE_Start = 1,
	APP_CVALUE_Cali_Discharge , 
	APP_CVALUE_Cali_Charge , 
	APP_CVALUE_Cali_Calc , 
	APP_CVALUE_Measure_Range ,
	APP_CVALUE_Measure_Discharge ,
	APP_CVALUE_Measure_Charge ,
	APP_CVALUE_Measure_Calc , 
	
}app_cvalue_state_machine_e;

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
 * @defgroup      app_cvalue_Private_Variables 
 * @brief         
 * @{  
 */
static uint16_t app_cvalue_checkv_time = 0;
/**
 * @}
 */

/**
 * @defgroup      app_cvalue_Public_Variables 
 * @brief         
 * @{  
 */
APP_Cvalue_t APP_Cvalue = 
{
	.C_value = 0 ,
	.range = 0,
	.schedule = 0,
	.calc_flag = 0,
	.cali_k = 1.0f,
};
/**
 * @}
 */

/**
 * @defgroup      app_cvalue_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void app_cvalue_changeRange(uint8_t range);
static void app_cvalue_powerdown(void);
/**
 * @}
 */

/**
 * @defgroup      app_cvalue_Functions 
 * @brief         
 * @{  
 */

void APP_Cvalue_Init(void)
{
	BSP_TIM_Init(BSP_TIM_10);
	BSP_TIM_Stop(BSP_TIM_10);
	APP_Cvalue_StartDischarge();
	//app_cvalue_changeRange(APP_CVALUE_UF);
}

static void app_cvalue_changeRange(uint8_t range)
{
	switch(range)
	{
		case APP_CVALUE_UF:
			{
				APP_SW_H(APP_SW_PF);
				APP_SW_H(APP_SW_NF);
				APP_SW_L(APP_SW_UF);
			}break;
		case APP_CVALUE_NF:
			{
				APP_SW_H(APP_SW_UF);
				APP_SW_H(APP_SW_PF);
				APP_SW_L(APP_SW_NF);				
			}break;
		case APP_CVALUE_PF:
			{
				APP_SW_H(APP_SW_UF);
				APP_SW_H(APP_SW_NF);
				APP_SW_L(APP_SW_PF);				
			}break;
		default:break;
	}
}

static void app_cvalue_powerdown(void)
{
	APP_SW_H(APP_SW_UF);
	APP_SW_H(APP_SW_PF);
	APP_SW_H(APP_SW_NF);	
}

void APP_Cvalue_SW(void)
{
	APP_SW_H(APP_SW_C_OR_D);
}

void APP_Cvalue_Cali(void)
{
	APP_SW_L(APP_SW_MEASURE_OR_CALI);
}

void APP_Cvalue_Measure(void)
{
	APP_SW_H(APP_SW_MEASURE_OR_CALI);
}

void APP_Cvalue_StartCharge(void)
{
	APP_SW_L(APP_SW_DIS_OR_CHARGE);
}

void APP_Cvalue_StartDischarge(void)
{
	app_cvalue_powerdown();
	APP_SW_H(APP_SW_DIS_OR_CHARGE);
}

void APP_Cvalue_Loop(void)
{
	if(APP_Cvalue.calc_flag == 1 && APP_Dvalue.calc_flag == 0 )
	{
		APP_Cvalue_Calc();
	}
}

void APP_Cvalue_Calc(void)
{
	static uint8_t status  = 0;
	
	switch(status)
	{
		case APP_CVALUE_Start:
			{
				if(APP_Cvalue.calc_flag == 1 && APP_Dvalue.calc_flag == 0 )
				{
					APP_Cvalue.schedule = 1;
					APP_Cvalue_Cali();
					
					status = APP_CVALUE_Cali_Discharge;
					APP_Cvalue_StartDischarge();
				}
				else
				{
					
				}
			}break;
		case APP_CVALUE_Cali_Discharge:
			{
				

				static uint8_t time_out = 0;
				time_out ++;
				if(time_out > 3)
				{
					time_out = 0 ;
					status = APP_CVALUE_Cali_Charge;
				}
				
			}break;				
		case APP_CVALUE_Cali_Charge:
			{
				Clog_Float("C:" ,BSP_AD7682_Get_CurValue(BSP_AD7682_C_OUT_CHANNEL));
				APP_Cvalue_StartCharge();
				app_cvalue_changeRange(APP_CVALUE_UF);
				BSP_TIM_Start(BSP_TIM_10);
				status = APP_CVALUE_Cali_Calc;
			}break;				
		case APP_CVALUE_Cali_Calc:
			{
				if(BSP_AD7682_Get_CurValue(BSP_AD7682_C_OUT_CHANNEL) > 1800.0f)
				{
					float measure_time = 0;
					measure_time = app_cvalue_checkv_time * 0.25f;
					Clog_Float("measure_time:" ,measure_time);
					app_cvalue_checkv_time = 0;
					BSP_TIM_Stop(BSP_TIM_10);
					
					
					
					status = APP_CVALUE_Start;

				}
			}break;
		case APP_CVALUE_Measure_Range:
			{
				
			}break;				
		case APP_CVALUE_Measure_Discharge:
			{
				
			}break;				
		case APP_CVALUE_Measure_Charge:
			{
				
			}break;
		case APP_CVALUE_Measure_Calc:
			{
				
			}break;				
		default:
			{
				status = APP_CVALUE_Start;
			}break;
	}
}



void APP_Cvalue_CheckV(void)
{
	float c_out = 0;
	c_out = BSP_AD7682_Get_CurValue(BSP_AD7682_C_OUT_CHANNEL);
	if(c_out > 2.0f && c_out < 1580.0f)
	{
		app_cvalue_checkv_time ++;
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

