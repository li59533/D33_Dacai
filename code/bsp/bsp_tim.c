/**
 **************************************************************************************************
 * @file        bsp_tim.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_conf.h"
#include "bsp_tim.h"

#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    bsp_tim_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_tim_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_tim_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_tim_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Private_Variables 
 * @brief         
 * @{  
 */
TIM_HandleTypeDef  htim8 =
{
	.Instance = TIM8,
	.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE,
	.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1,
	.Init.CounterMode = TIM_COUNTERMODE_UP,
	.Init.Period = 3661,//1831=120000000/65536�Ĳ�����;;
	.Init.Prescaler = 0,
	.Init.RepetitionCounter = 0,	
}; 
TIM_HandleTypeDef  htim3 =
{
	.Instance = TIM3,
	.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE,
	.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1,
	.Init.CounterMode = TIM_COUNTERMODE_UP,
	.Init.Period = 499, //500usһ��
	.Init.Prescaler = 119,
	.Init.RepetitionCounter = 0,	
};



/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Functions 
 * @brief         
 * @{  
 */

void BSP_TIM_Init(void)
{
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	
	if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
	{
		Error_Handler();
	}	

	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}	
	
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}	
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}	
	
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}	
	
	
	BSP_TIM3_Start();
	DEBUG("TIM8 TIM3 Init\r\n");
	
}	

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
	if(htim_base->Instance==TIM8)
	{
		__HAL_RCC_TIM8_CLK_ENABLE();
		__HAL_TIM_CLEAR_IT(&htim8, TIM_IT_UPDATE)  ;
		HAL_NVIC_SetPriority(TIM8_UP_TIM13_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);

	}else if(htim_base->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();
		__HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE)  ;
		HAL_NVIC_SetPriority(TIM3_IRQn, 6, 0);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);

	}
}

void BSP_TIM8_Start(void)
{
	HAL_TIM_Base_Start_IT(&htim8);
}
void BSP_TIM8_Stop(void)
{
	HAL_TIM_Base_Stop_IT(&htim8);
}

void BSP_TIM3_Start(void)
{
	HAL_TIM_Base_Start_IT(&htim3);
}
void BSP_TIM3_Stop(void)
{
	HAL_TIM_Base_Stop_IT(&htim3);
}

void BSP_TIM8_IRQHandler(void)
{
	
	if (TIM8->SR & TIM_IT_UPDATE) 
	{
		TIM8->SR &= (uint16_t)~TIM_IT_UPDATE;
		
		//BSP_AD7682_StartGetValue_InConf();
		//DEBUG("TIM8 IRQ\r\n");
	}	

	
	
	//HAL_TIM_IRQHandler(&htim8);
	//HAL_TIM_Base_Stop_IT(&htim2);

}
void BSP_TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim3);
	//BSP_AD7682_CheckFilterStatus();
	//HAL_TIM_Base_Stop_IT(&htim3);
	//DEBUG("TIM3 IRQ\r\n");
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
