/**
 **************************************************************************************************
 * @file        app_vibration_exciter.c
 * @author
 * @app_vibration_exciter
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
#include "app_vibration_exciter.h"
#include "bsp_spi.h"
#include "bsp_adc.h"
#include "bsp_tim.h"
#include "bsp_ad5683.h"
#include "arm_math.h"
#include "clog.h"
#include "arm_math.h"
#include "virexc_task.h"
#include "app_dvalue.h"
#include "system_param.h"
#include "bsp_led.h"
/**
 * @addtogroup    app_vibration_exciter_Modules 
 * @{  
 */

/**
 * @defgroup      app_vibration_exciter_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       app_vibration_exciter_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_vibration_exciter_Constants_Defines 
 * @brief         
 * @{  
 */
#define APP_VIREXC_FREQ			100

#define APP_VIREXC_SINPOINT_C	320
/**
 * @}
 */

/**
 * @defgroup       app_vibration_exciter_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_vibration_exciter_Private_Variables 
 * @brief         
 * @{  
 */
 
/*
	.Kp = 4.0f,
	.Ki = 0.5f,
	.Kd = 0.2f,

*/ 
arm_pid_instance_f32 PID = 
{
	.Kp = 1.6f,
	.Ki = 0.0f,
	.Kd = 0.0f,
};
 
 
static float app_virexc_sinbuf[APP_VIREXC_SINPOINT_C];
static uint16_t app_virexc_gain = 1;
static float desired_value = 20.0f;
static uint8_t app_virexc_pid_flag = 0;
/**
 * @}
 */

/**
 * @defgroup      app_vibration_exciter_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_vibration_exciter_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_vibration_exciter_Functions 
 * @brief         
 * @{  
 */
 
 





void APP_Viration_Exciter_Init(void)
{
	BSP_AD5683_Init();
	arm_pid_init_f32(&PID , 1);
	BSP_TIM_Init(BSP_TIM_13);
	
	for(uint16_t i = 0 ; i < APP_VIREXC_SINPOINT_C; i ++)
	{
		app_virexc_sinbuf[i] = (arm_sin_f32(2*3.1415926f*i/APP_VIREXC_SINPOINT_C) + 1) / 2.0f;
	}
}

void APP_VirExc_Start(void)
{
	
	BSP_TIM_Start(BSP_TIM_13);
}

void APP_VirExc_Stop(void)
{

	BSP_TIM_Stop(BSP_TIM_13);
}

void APP_VirExc_32Points_Loop(void)  // 312.5us (32point)
{
	static uint16_t point_seq = 0;
	uint16_t value = 0;
	
	value = (uint16_t )(app_virexc_sinbuf[point_seq ++] * app_virexc_gain);
	BSP_AD5683_SetOut(value);

	point_seq %= APP_VIREXC_SINPOINT_C;
	
}

void APP_VirExc_UPgain(void)
{
	app_virexc_gain +=10;
}

void APP_VirExc_Downgain(void)
{
	if(app_virexc_gain > 10)
	{
		app_virexc_gain -= 10;
	}
}

void APP_VirExc_PID_Start(void)
{
	if(app_virexc_pid_flag == 0)
	{
		app_virexc_pid_flag = 1;
		VirExc_Task_Event_Start(VIREXC_TASK_PID1250_EVENT,EVENT_FROM_TASK);
		
	}
	else
	{
		
	}	
}

void APP_VirExc_PID_1250(void)
{
	desired_value = (float)(g_SystemParam_Config.D_cali_result / 4.0 * 10.0f);
	APP_VirExc_PID_Start();
	BSP_Led_Blink(BSP_LED_EXCITATION , 0 , 50 , 100);
}

void APP_VirExc_PID_50(void)
{
	desired_value = 0.0f;
	APP_VirExc_PID_Start();
	BSP_Led_Blink(BSP_LED_EXCITATION , 1 , 50 , 100);
}

void APP_VirExc_PID_Loop(void)
{
	float out = 0;
	float err_range = 0;
	float next_gain = 0;
	
	if(APP_Dvalue.cali_flag == 1)
	{
		if(APP_Dvalue.cali_mv > 0)
		{
			desired_value = APP_Dvalue.cali_mv * APP_Dvalue.mul ;
		}
		else
		{
			return ;
		}
		
		err_range = desired_value - BSP_ADC_Value[BSP_ADC_SIG_CHANNEL].real_mv;
	}
	else
	{
		
		
		
		err_range = desired_value - BSP_ADC_Value[BSP_ADC_CAL_CHANNEL].real_mv;
	}	
	
	//Clog_Float("err_range:" , err_range);
	
	out = arm_pid_f32(&PID , err_range);
	
	//Clog_Float("out:" , out);

	next_gain = (float) (app_virexc_gain + out);
	
	if(next_gain < 0)
	{
		app_virexc_gain = 0;
	}
	else if(next_gain > 65535)
	{
		app_virexc_gain = 1000;
	}
	else
	{
		app_virexc_gain = (uint16_t )next_gain;
	}
	//DEBUG("app_virexc_gain :%d\r\n" , app_virexc_gain);	
}


// ---------------- Test Code -----------

void APP_VirExc_TestCode(void)
{
	float out = 0;
	float err_range = 0;
	
	err_range = desired_value - BSP_ADC_Value[BSP_ADC_CAL_CHANNEL].real_mv;
	
	Clog_Float("err_range:" , err_range);
	
	out = arm_pid_f32(&PID , err_range);
	
	Clog_Float("out:" , out);

	app_virexc_gain = (uint16_t )(app_virexc_gain + out);
	DEBUG("app_virexc_gain :%d\r\n" , app_virexc_gain);
//	if(out > 1000)
//	{
//		desired_value = 100.0f;
//	}
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

