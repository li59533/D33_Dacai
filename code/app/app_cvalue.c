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
	APP_CVALUE_Measure_Wait ,
	APP_CVALUE_Measure_Calc , 
	
}app_cvalue_state_machine_e;






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
	.range = APP_CVALUE_UF,
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
				APP_Cvalue.range = APP_CVALUE_UF;
			}break;
		case APP_CVALUE_NF:
			{
				APP_SW_H(APP_SW_UF);
				APP_SW_H(APP_SW_PF);
				APP_SW_L(APP_SW_NF);
				APP_Cvalue.range = APP_CVALUE_NF;			
			}break;
		case APP_CVALUE_PF:
			{
				APP_SW_H(APP_SW_UF);
				APP_SW_H(APP_SW_NF);
				APP_SW_L(APP_SW_PF);	
				APP_Cvalue.range = APP_CVALUE_PF;				
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
	static uint8_t range = APP_CVALUE_UF;
	static uint8_t status  = 0;
	float measure_time = 0;
	
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
					APP_Cvalue.schedule = 10;
					time_out = 0 ;
					status = APP_CVALUE_Cali_Charge;
				}
				
			}break;				
		case APP_CVALUE_Cali_Charge:
			{
				//Clog_Float("C:" ,BSP_AD7682_Get_CurValue(BSP_AD7682_C_OUT_CHANNEL));
				APP_Cvalue_StartCharge();
				app_cvalue_changeRange(APP_CVALUE_UF);
				BSP_TIM_Start(BSP_TIM_10);
				status = APP_CVALUE_Cali_Calc;
				APP_Cvalue.schedule = 15;
			}break;				
		case APP_CVALUE_Cali_Calc:
			{
				if(BSP_AD7682_Get_CurValue(BSP_AD7682_C_OUT_CHANNEL) > 1800.0f)
				{
					measure_time = app_cvalue_checkv_time * 0.25f;
					Clog_Float("C_Cali_time:" ,measure_time);
					APP_Cvalue.cali_k = measure_time / 220.0f;
					app_cvalue_checkv_time = 0;
					BSP_TIM_Stop(BSP_TIM_10);

					status = APP_CVALUE_Measure_Discharge;
					APP_Cvalue_StartDischarge();
					APP_Cvalue_Measure();
					APP_Cvalue.schedule = 20;
				}
			}break;
		case APP_CVALUE_Measure_Range:
			{
				
			}break;				
		case APP_CVALUE_Measure_Discharge:
			{
				static uint8_t time_out = 0;
				time_out ++;
				if(time_out > 3)
				{
					time_out = 0 ;
					status = APP_CVALUE_Measure_Charge;
					APP_Cvalue.schedule = 50;
				}
								
			}break;				
		case APP_CVALUE_Measure_Charge:
			{
				//Clog_Float("C:" ,BSP_AD7682_Get_CurValue(BSP_AD7682_C_OUT_CHANNEL));
				app_cvalue_checkv_time = 0;
				APP_Cvalue_StartCharge();
				app_cvalue_changeRange(range);
				BSP_TIM_Start(BSP_TIM_10);
				status = APP_CVALUE_Measure_Wait;
				APP_Cvalue.schedule = 70;
			}break;
		case APP_CVALUE_Measure_Wait:
			{
	
				static uint8_t time_out_1 = 0;

				time_out_1 ++;
				measure_time = app_cvalue_checkv_time * 0.25f;	
				
				if(time_out_1 > 55 || BSP_AD7682_Get_CurValue(BSP_AD7682_C_OUT_CHANNEL) > 2200.0f)
				{
					Clog_Float("measure_time:" , measure_time);
					time_out_1 = 0;
					BSP_TIM_Stop(BSP_TIM_10);
					APP_Cvalue.schedule = 90;
					
					switch(range)
					{
						case APP_CVALUE_UF:
							{
								DEBUG("APP_CVALUE_UF\r\n");
								if(measure_time < 10)
								{
									range = APP_CVALUE_NF;
								
									APP_Cvalue.status = APP_CVALUE_WAIT_CALC;
									status = APP_CVALUE_Measure_Discharge;
									APP_Cvalue_StartDischarge();
									APP_Cvalue_Measure();
								}
								else if(measure_time > 800)
								{
									APP_Cvalue.status = APP_CVALUE_OVER;
									status = APP_CVALUE_Measure_Discharge;
									APP_Cvalue_StartDischarge();
									APP_Cvalue_Measure();									
								}
								else
								{
									APP_Cvalue.status = APP_CVALUE_NORMALE;
									status = APP_CVALUE_Measure_Calc;
									APP_Cvalue_StartDischarge();
									APP_Cvalue_Measure();										
								}
							}break;
						case APP_CVALUE_NF:
							{
								DEBUG("APP_CVALUE_NF\r\n");
								if(measure_time < 1)
								{
									range = APP_CVALUE_PF;
								
									APP_Cvalue.status = APP_CVALUE_WAIT_CALC;
									status = APP_CVALUE_Measure_Discharge;
									APP_Cvalue_StartDischarge();
									APP_Cvalue_Measure();
								}								
								else if(measure_time > 1000)
								{
									range = APP_CVALUE_UF;
									
									APP_Cvalue.status = APP_CVALUE_WAIT_CALC;
									status = APP_CVALUE_Measure_Discharge;
									APP_Cvalue_StartDischarge();
									APP_Cvalue_Measure();									
								}
								else
								{
									APP_Cvalue.status = APP_CVALUE_NORMALE;
									status = APP_CVALUE_Measure_Calc;
									APP_Cvalue_StartDischarge();
									APP_Cvalue_Measure();										
								}								
							}break;
						case APP_CVALUE_PF:
							{
								DEBUG("APP_CVALUE_PF\r\n");
								if(measure_time < 1)
								{
									APP_Cvalue.status = APP_CVALUE_OVER;
									status = APP_CVALUE_Measure_Discharge;
									APP_Cvalue_StartDischarge();
									APP_Cvalue_Measure();
								}								
								else if(measure_time > 1000)
								{
									range = APP_CVALUE_NF;
									
									APP_Cvalue.status = APP_CVALUE_WAIT_CALC;
									status = APP_CVALUE_Measure_Discharge;
									APP_Cvalue_StartDischarge();
									APP_Cvalue_Measure();									
								}
								else
								{
									APP_Cvalue.status = APP_CVALUE_NORMALE;
									status = APP_CVALUE_Measure_Calc;
									APP_Cvalue_StartDischarge();
									APP_Cvalue_Measure();										
								}									
								
							}break;
						default:break;
					}
				}
				
				
			}break;
		case APP_CVALUE_Measure_Calc:
			{

				measure_time = app_cvalue_checkv_time * 0.25f;		
				
				if(APP_Cvalue.range == APP_CVALUE_UF)
				{
					APP_Cvalue.C_value = measure_time * 0.1f / APP_Cvalue.cali_k;
				}
				else if(APP_Cvalue.range == APP_CVALUE_NF)
				{
					APP_Cvalue.C_value = measure_time / APP_Cvalue.cali_k; 
				}
				else if(APP_Cvalue.range == APP_CVALUE_PF)
				{
					APP_Cvalue.C_value = measure_time / APP_Cvalue.cali_k;
				}
				Clog_Float("C_value:" ,APP_Cvalue.C_value);
				
				APP_Cvalue.schedule = 100;
				status = APP_CVALUE_Measure_Discharge;
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
		//DEBUG("c_t:%d\r\n" , app_cvalue_checkv_time);
		//Clog_Float("C_value:" ,c_out);
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

