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
#include "app_sw.h"
#include "bsp_ad7682.h"
#include "app_vibration_exciter.h"
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
	.Init.Period = 3661,//1831=120000000/65536的采样率;;
	.Init.Prescaler = 0,
	.Init.RepetitionCounter = 0,	
}; 
TIM_HandleTypeDef  htim3 =
{
	.Instance = TIM3,
	.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE,
	.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1,
	.Init.CounterMode = TIM_COUNTERMODE_UP,
	.Init.Period = 499, //500us一次
	.Init.Prescaler = 119,
	.Init.RepetitionCounter = 0,	
};


TIM_HandleTypeDef  htim11 =
{
	.Instance = TIM11,
	.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE,
	.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1,
	.Init.CounterMode = TIM_COUNTERMODE_UP,
	.Init.Period = 21000, //(4000point 250us)
	.Init.Prescaler = 1,
};


TIM_HandleTypeDef  htim13 =
{
	.Instance = TIM13,
	.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE,
	.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1,
	.Init.CounterMode = TIM_COUNTERMODE_UP,
	//.Init.Period = 26250, //312.5us一次(32point)
	.Init.Period = 2625, //31.25us一次(320point)
	.Init.Prescaler = 0,
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



void BSP_TIM_Init(uint8_t Timx)
{
	
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};	
	switch(Timx)
	{
		case BSP_TIM_3:
			{
				if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
				{
					Error_Handler();
				}		
				sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
				if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
				{
					Error_Handler();
				}		

				DEBUG("TIM3 Init\r\n");
			}
			break;
		case BSP_TIM_8:
			{
				if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
				{
					Error_Handler();
				}	
				sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
				if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
				{
					Error_Handler();
				}	
				sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
				sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
				if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
				{
					Error_Handler();
				}		
				DEBUG("TIM8 Init\r\n");
			}
			break;
		case BSP_TIM_11:
			{
				if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
				{
					Error_Handler();
				}			
				sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
				if (HAL_TIM_ConfigClockSource(&htim11, &sClockSourceConfig) != HAL_OK)
				{
					Error_Handler();
				}		
				DEBUG("TIM11 Init\r\n");
				
			}break;			
		case BSP_TIM_13:
			{
				if (HAL_TIM_Base_Init(&htim13) != HAL_OK)
				{
					Error_Handler();
				}			
				sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
				if (HAL_TIM_ConfigClockSource(&htim13, &sClockSourceConfig) != HAL_OK)
				{
					Error_Handler();
				}		
				DEBUG("TIM13 Init\r\n");
				
			}break;
		default:break;
	}

}	

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
	if(htim_base->Instance==TIM8)
	{
		__HAL_RCC_TIM8_CLK_ENABLE();
		__HAL_TIM_CLEAR_IT(&htim8, TIM_IT_UPDATE)  ;
		HAL_NVIC_SetPriority(TIM8_UP_TIM13_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);

	}
	else if(htim_base->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();
		__HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE)  ;
		HAL_NVIC_SetPriority(TIM3_IRQn, 6, 0);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);

	}
	else if(htim_base->Instance==TIM11)
	{
		__HAL_RCC_TIM11_CLK_ENABLE();
		__HAL_TIM_CLEAR_IT(&htim11, TIM_IT_UPDATE)  ;
		HAL_NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
	}		
	else if(htim_base->Instance==TIM13)
	{
		__HAL_RCC_TIM13_CLK_ENABLE();
		__HAL_TIM_CLEAR_IT(&htim13, TIM_IT_UPDATE)  ;
		HAL_NVIC_SetPriority(TIM8_UP_TIM13_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);
	}	

	
}

// ---------- Start and Stop -----------------
void BSP_TIM_Start(uint8_t Timx)
{
	switch(Timx)
	{
		case BSP_TIM_3:HAL_TIM_Base_Start_IT(&htim3);break;
		case BSP_TIM_8:HAL_TIM_Base_Start_IT(&htim8);break;
		case BSP_TIM_11:HAL_TIM_Base_Start_IT(&htim11);break;
		case BSP_TIM_13:HAL_TIM_Base_Start_IT(&htim13);break;
		default:break;
	}
}

void BSP_TIM_Stop(uint8_t Timx)
{
	switch(Timx)
	{
		case BSP_TIM_3:HAL_TIM_Base_Stop_IT(&htim3);break;
		case BSP_TIM_8:HAL_TIM_Base_Stop_IT(&htim8);break;
		case BSP_TIM_11:HAL_TIM_Base_Stop_IT(&htim11);break;
		case BSP_TIM_13:HAL_TIM_Base_Stop_IT(&htim13);break;
		default:break;
	}
}

// -------------------------------------------

// ---------------- TIM_IRQHandler --------------------

void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
	if(TIM11->SR & TIM_IT_UPDATE)
	{
		//APP_SW_Toggle(APP_SW_PD4);
		BSP_AD7682_LoopTrig();
		
		TIM11->SR &= (uint16_t)~TIM_IT_UPDATE;
	}

}

void TIM8_UP_TIM13_IRQHandler(void)
{
	if(TIM8->SR & TIM_IT_UPDATE)
	{
		TIM8->SR &= (uint16_t)~TIM_IT_UPDATE;
	}
	else if(TIM13->SR & TIM_IT_UPDATE)
	{
		//APP_SW_Toggle(APP_SW_PD4);
		APP_VirExc_32Points_Loop();
		//DEBUG("TIM13->SR & TIM_IT_UPDATE\r\n");
		TIM13->SR &= (uint16_t)~TIM_IT_UPDATE;
	}
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

// --------------------------------------------------------


/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

