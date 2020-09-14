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
#include "system_param.h"
#include "dacai.h"
#include "app_guifunc.h"
#include "bsp_led.h"
#include "mcuprotocol.h"
#include "app_conf.h"

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
	APP_DVALUE_CALC_Wait	= 1,
	APP_DVALUE_CALC_Check_SIG ,
	APP_DVALUE_CALC_Get_Average  ,
	APP_DVALUE_CALC_Complete , 
}app_dvalue_calc_state_machine_e;

typedef enum
{
	APP_DVALUE_CALI_Wait	= 1,
	APP_DVALUE_CALI_Check_SIG ,
	APP_DVALUE_CALI_Get_Average  ,
	APP_DVALUE_CALI_Complete , 
}app_dvalue_cali_state_machine_e;


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
				BSP_Led_Blink(BSP_LED_RANGE , 2 , 10 , 100);
			}break;
		case Test_PGA_10:	
			{
				APP_SW_H(APP_SW_PD1);
				APP_SW_L(APP_SW_PD0);
				APP_Dvalue.mul = 10;
				BSP_Led_Blink(BSP_LED_RANGE , 2 , 50 , 100);
			}break;
		case Test_PGA_100:	
			{
				APP_SW_L(APP_SW_PD1);
				APP_SW_H(APP_SW_PD0);
				APP_Dvalue.mul = 100;
				BSP_Led_Blink(BSP_LED_RANGE , 2 , 90 , 100);
			}break;
		default:break;
	}
}

void APP_Dvalue_Calc(void)
{
	static uint8_t status = 0 ;
	
	switch(status)
	{
		case APP_DVALUE_CALC_Wait:
			{

				if(APP_Dvalue.calc_flag == 1 && APP_Cvalue.calc_flag == 0)
				{
					//APP_Dvalue.D_value = 0;
					//APP_Dvalue.calc_flag = 0;
					APP_Dvalue.schedule = 1;
					status = APP_DVALUE_CALC_Check_SIG;
					//APP_Dvalue_TestPGA(Test_PGA_1);

				}
				else
				{
					
				}
			}break;
		case APP_DVALUE_CALC_Check_SIG:
			{
				static uint16_t time_count = 0 ;
				time_count ++ ;
				APP_Dvalue.schedule = (uint8_t )((50.0 / 10.0) * time_count);
				
				if(time_count > 10)
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
					else if(BSP_ADC_Value[BSP_ADC_SIG_CHANNEL].real_mv > 2800.0f)
					{
						APP_Dvalue_TestPGA(Test_PGA_1);
					}
					else
					{
						APP_Dvalue.schedule = 80;
						status = APP_DVALUE_CALC_Get_Average;
					}					
					
				}
			}break;
		case APP_DVALUE_CALC_Get_Average:
			{
				DEBUG("APP_DVALUE_Get_Average\r\n");
				static float sig_buf[4];
				static uint8_t sig_count = 0;
				
				sig_buf[sig_count] = BSP_ADC_Value[BSP_ADC_SIG_CHANNEL].real_mv;
				
				sig_count ++;

				if(sig_count == 4)
				{
					sig_count = 0;
					float sum = 0;
					for(uint8_t i = 0; i < 4 ; i ++)
					{
						sum += sig_buf[i];
					}
					float temp = 0;
					
					temp = (float)(sum / 4.0f) / APP_Dvalue.mul * 4.0f;
					//APP_Dvalue.D_value = temp * 0.7018f - 1.701f;
					APP_Dvalue.D_value = temp ;
					APP_Dvalue.schedule = 100;
					status = APP_DVALUE_CALC_Complete;
				}
			}break;
		case APP_DVALUE_CALC_Complete:
			{
				static uint8_t wait_time = 0;
				wait_time ++;
				if(wait_time > 10)
				{
					BSP_Led_Blink(BSP_LED_D , 2 , 50 , 100);
					wait_time = 0;
					status = APP_DVALUE_CALC_Wait;
				}
				
				
			}break;
		default:
			{
				DEBUG("APP_DVALUE_default\r\n");
				status = APP_DVALUE_CALC_Wait;
			}break;
	}
}

void APP_Dvalue_Cali(void)
{
	static uint8_t status = 0; 
	
	switch(status)
	{
		
		case APP_DVALUE_CALI_Wait:
			{
				if(g_SystemParam_Config.D_caliunit_value == 0)
				{
					// µ¯´°
				}		
				else
				{
					APP_Dvalue.cali_mv = (float )(g_SystemParam_Config.D_caliunit_value / 4.0f);
					status = APP_DVALUE_CALI_Check_SIG;
				}

			}break;
		case APP_DVALUE_CALI_Check_SIG:
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
						status = APP_DVALUE_CALC_Get_Average;
					}					
				}				
			}break;
		case APP_DVALUE_CALI_Get_Average:
			{
				DEBUG("APP_DVALUE_Get_Average\r\n");
				//static float sig_buf[8];
				static uint8_t sig_count = 0;
				
				//sig_buf[sig_count] = BSP_ADC_Value[BSP_ADC_SIG_CHANNEL].real_mv;
				
				sig_count ++;

				if(sig_count == 8)
				{
//					sig_count = 0;
//					float sum = 0;
//					for(uint8_t i = 0; i < 8 ; i ++)
//					{
//						sum += sig_buf[i];
//					}
//					float temp = 0;
//					
//					temp = (float)(sum / 8.0f) / APP_Dvalue.mul * 4.0f;
					//APP_Dvalue.D_value = temp * 0.7018f - 1.701f;
					g_SystemParam_Config.D_cali_result = (uint16_t)(BSP_ADC_Value[BSP_ADC_CAL_CHANNEL].real_mv / 10.0f * 4.0f);
					
					g_SystemParam_Config.D_cali_time.year = app_gui_rtc.year;
					g_SystemParam_Config.D_cali_time.month = app_gui_rtc.month;
					g_SystemParam_Config.D_cali_time.day = app_gui_rtc.day;
					g_SystemParam_Config.D_cali_time.hour = app_gui_rtc.hour;
					g_SystemParam_Config.D_cali_time.min = app_gui_rtc.min;
					g_SystemParam_Config.D_cali_time.sec = app_gui_rtc.sec;
					
					SystemParam_Save();
					APP_Dvalue.schedule = 100;
					status = APP_DVALUE_CALI_Complete;
					
					Dacai_GetRTC();
				}
			}break;	
		case APP_DVALUE_CALI_Complete:
			{
				status = 0;
				APP_Dvalue.cali_flag = 0;
			}break;
		default:
			{
				DEBUG("APP_DVALUE Cali_default\r\n");
				status = APP_DVALUE_CALI_Wait;				
			}break;
		
	}
}

void APP_Dvalue_Loop(void)
{
	if(APP_Dvalue.cali_flag == 1)
	{
		APP_Dvalue_Cali();
	}
	else
	{
		APP_Dvalue_Calc();
	}
}


// -------------- Report Data -------------------
void APP_Dvalue_Report_data(void)
{
	uint8_t * buf_space ;
	uint8_t * payload_ptr ;
	MCUprotocolTLV_t MCUprotocolTLV;
	uint8_t len = 0;
	buf_space = pvPortMalloc(sizeof(uint8_t) * 100); //vPortFree()
	
	MCUprotocolp2p_t * MCUprotocolp2p = (MCUprotocolp2p_t * )buf_space;
	
	MCUprotocolp2p->Head = MCUPROTOCOL_AHR_SIGN;
	//MCUprotocolp2p->Length = ;
	MCUprotocolp2p->FCF.Ack = 0;
	MCUprotocolp2p->FCF.ConnType = MCUPROTOCOL_CONNTYPE_P2P;
	MCUprotocolp2p->FCF.FrameType = MCUPROTOCOL_FRAMETYPE_DATA;
	MCUprotocolp2p->FCF.Gateway = 0;
	MCUprotocolp2p->FCF.none_1 = 0;
	MCUprotocolp2p->FCF.none_2 = 0;
	MCUprotocolp2p->FCF.Pending = 0;
	MCUprotocolp2p->FCF.Sec = 0;
	MCUprotocolp2p->FCF.Trans = 0;
	MCUprotocolp2p->Seq = g_MCUprotocol_Seq ++;
	MCUprotocolp2p->Cmd = MCUCmd_SelfUPData;
	
	payload_ptr = &MCUprotocolp2p->Cmd + 1;
	
	MCUprotocolTLV.Tag = UPDATA_DVALUE_TAG;
	MCUprotocolTLV.Len = 4;
	memcpy(MCUprotocolTLV.Value.Array , (uint8_t *)&APP_Dvalue.D_value , 4);
	payload_ptr += MCUprotocol_AddTlv(payload_ptr ,&MCUprotocolTLV);
	len += 4;
	
	MCUprotocolp2p->Length = len + 9;
	
	
	MCUprotocolp2p->FCS = MCUprotocol_GetChecksum((uint8_t *)&MCUprotocolp2p->FCF , MCUprotocolp2p->Length - 5);
	
	MCUprotocolp2p->Foot = MCUPROTOCOL_AFR_SIGN;
	
	
	APP_Conf_Send_InQueue( &MCUprotocolp2p->Head , MCUprotocolp2p->Length);
	vPortFree(buf_space);
}


// ----------------------------------------------
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

