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
#include "bsp_adc.h"
#include "rtos_tools.h"
#include "virexc_task.h"
#include "app_cvalue.h"
#include "clog.h"
/**
 * @addtogroup    app_dvalue_Modules 
 * @{  
 */

/**
 * @defgroup      app_dvalue_IO_Define          s 
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

typedef enum
{
	APP_DVALUE_Wait	= 1,
	APP_DVALUE_Check_SIG ,
	APP_DVALUE_Get_Average  ,
	APP_DVALUE_Calc_Complete , 
}app_dvalue_state_machine_e;



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
APP_Dvalue_t APP_Dvalue = 
{
	.D_value = 0,
	.mul = Test_PGA_1,
	.schedule = 0,
	.calc_flag = 0,
};
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

void APP_Dvalue_SW(void)
{
	APP_SW_L(APP_SW_C_OR_D);	
}

void APP_Dvalue_TestPGA(uint8_t  Test_PGA)
{
	switch(Test_PGA)
	{
		case Test_PGA_1 :
			{
				APP_SW_L(APP_SW_PD1);
				APP_SW_L(APP_SW_PD0);
				APP_Dvalue.mul = 1;
			}break;
		case Test_PGA_10:	
			{
				APP_SW_H(APP_SW_PD1);
				APP_SW_L(APP_SW_PD0);
				APP_Dvalue.mul = 10;
			}break;
		case Test_PGA_100:	
			{
				APP_SW_L(APP_SW_PD1);
				APP_SW_H(APP_SW_PD0);
				APP_Dvalue.mul = 100;
			}break;
		default:break;
	}
}

void APP_Dvalue_Calc(void)
{
	static uint8_t status = 0 ;
	
	switch(status)
	{
		case APP_DVALUE_Wait:
			{

				if(APP_Dvalue.calc_flag == 1 && APP_Cvalue.calc_flag == 0)
				{
					//APP_Dvalue.D_value = 0;
					//APP_Dvalue.calc_flag = 0;
					APP_Dvalue.schedule = 1;
					status = APP_DVALUE_Check_SIG;
					APP_Dvalue_TestPGA(Test_PGA_1);

				}
				else
				{
					
				}
			}break;
		case APP_DVALUE_Check_SIG:
			{
				static uint16_t time_count = 0 ;
				time_count ++ ;
				APP_Dvalue.schedule = (uint8_t )((50.0 / 50.0) * time_count);
				
				if(time_count > 50)
				{
					time_count = 0;
					
					
					
					
					if(BSP_ADC_Value[BSP_ADC_SIG_CHANNEL].real_mv < 33.0f)
					{
						APP_Dvalue_TestPGA(Test_PGA_100);
					}
					else if(BSP_ADC_Value[BSP_ADC_SIG_CHANNEL].real_mv < 330.0f)
					{
						if(APP_Dvalue.mul == 1)
						{
							APP_Dvalue_TestPGA(Test_PGA_10);
						}
						else if(APP_Dvalue.mul == 10)
						{
							APP_Dvalue_TestPGA(Test_PGA_100);
						}
						else if(APP_Dvalue.mul == 100)
						{
							//status = APP_DVALUE_Get_Average;
						}
					}
					else
					{
						APP_Dvalue.schedule = 80;
						status = APP_DVALUE_Get_Average;
					}					
					
				}
			}break;
		case APP_DVALUE_Get_Average:
			{
				DEBUG("APP_DVALUE_Get_Average\r\n");
				static float sig_buf[8];
				static uint8_t sig_count = 0;
				
				sig_buf[sig_count] = BSP_ADC_Value[BSP_ADC_SIG_CHANNEL].real_mv;
				
				sig_count ++;

				if(sig_count == 8)
				{
					sig_count = 0;
					float sum = 0;
					for(uint8_t i = 0; i < 8 ; i ++)
					{
						sum += sig_buf[i];
					}
					float temp = 0;
					
					temp = (float)(sum / 8.0f) / APP_Dvalue.mul * 4.0f;
					APP_Dvalue.D_value = temp * 0.7018f - 1.701f;
					APP_Dvalue.schedule = 100;
					status = APP_DVALUE_Calc_Complete;
				}
			}break;
		case APP_DVALUE_Calc_Complete:
			{
				static uint8_t wait_time = 0;
				wait_time ++;
				if(wait_time > 100)
				{
					wait_time = 0;
					status = APP_DVALUE_Wait;
				}
				
				
			}break;
		default:
			{
				DEBUG("APP_DVALUE_default\r\n");
				status = APP_DVALUE_Wait;
			}break;
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

