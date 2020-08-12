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
#include "bsp_tim.h"
#include "bsp_ad5683.h"
#include "arm_math.h"
#include "clog.h"


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
static float app_virexc_sinbuf[APP_VIREXC_SINPOINT_C];
static uint16_t app_virexc_gain = 1500;
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
	BSP_TIM_Init(BSP_TIM_13);

	float sin_buf_1[32];
	uint16_t sin_buf_2[32];
	
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




/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

