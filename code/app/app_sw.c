/**
 **************************************************************************************************
 * @file        app_sw.c
 * @author
 * @app_sw
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
 
#include "app_sw.h"
#include "bsp_gpio.h"
#include "clog.h"
/**
 * @addtogroup    app_sw_Modules 
 * @{  
 */

/**
 * @defgroup      app_sw_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       app_sw_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_sw_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       app_sw_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_sw_Private_Variables 
 * @brief         
 * @{  
 */

 
 
static BSP_GPIO_Instance_t app_sw_instance[APP_SW_COUNT] =
{
	{
	.GPIOx = GPIOD,
	.GPIO_Init.Pin = GPIO_PIN_0,
	.GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP,
	.GPIO_Init.Pull = GPIO_PULLDOWN,
	.GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
	// .GPIO_Init.Alternate = ,
	.Begin_status = GPIO_PIN_RESET,
    },
	{
	.GPIOx = GPIOD,
	.GPIO_Init.Pin = GPIO_PIN_1,
	.GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP,
	.GPIO_Init.Pull = GPIO_PULLDOWN,
	.GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
	// .GPIO_Init.Alternate = ,
	.Begin_status = GPIO_PIN_RESET,
    },	
	{
	.GPIOx = GPIOD,
	.GPIO_Init.Pin = GPIO_PIN_2,
	.GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP,
	.GPIO_Init.Pull = GPIO_PULLDOWN,
	.GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
	// .GPIO_Init.Alternate = ,
	.Begin_status = GPIO_PIN_RESET,
    },	
	{
	.GPIOx = GPIOD,
	.GPIO_Init.Pin = GPIO_PIN_3,
	.GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP,
	.GPIO_Init.Pull = GPIO_PULLDOWN,
	.GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
	// .GPIO_Init.Alternate = ,
	.Begin_status = GPIO_PIN_RESET,
    },	
	{
	.GPIOx = GPIOD,
	.GPIO_Init.Pin = GPIO_PIN_4,
	.GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP,
	.GPIO_Init.Pull = GPIO_PULLDOWN,
	.GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
	// .GPIO_Init.Alternate = ,
	.Begin_status = GPIO_PIN_RESET,
    },	
	{
	.GPIOx = GPIOC,
	.GPIO_Init.Pin = GPIO_PIN_10,
	.GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP,
	.GPIO_Init.Pull = GPIO_PULLDOWN,
	.GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
	// .GPIO_Init.Alternate = ,
	.Begin_status = GPIO_PIN_RESET,
    },	
	{
	.GPIOx = GPIOC,
	.GPIO_Init.Pin = GPIO_PIN_11,
	.GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP,
	.GPIO_Init.Pull = GPIO_PULLDOWN,
	.GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
	// .GPIO_Init.Alternate = ,
	.Begin_status = GPIO_PIN_RESET,
    },		
	{
	.GPIOx = GPIOC,
	.GPIO_Init.Pin = GPIO_PIN_12,
	.GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP,
	.GPIO_Init.Pull = GPIO_PULLDOWN,
	.GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
	// .GPIO_Init.Alternate = ,
	.Begin_status = GPIO_PIN_RESET,
    },		
};
/**
 * @}
 */

/**
 * @defgroup      app_sw_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_sw_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_sw_Functions 
 * @brief         
 * @{  
 */

void APP_SW_Init(void)
{
	// ---------CLK---------------
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	// ---------------------------
	uint8_t i = 0 ;
    for( i = 0 ; i < APP_SW_COUNT ; i ++ )
    {
        HAL_GPIO_Init(app_sw_instance[i].GPIOx , &app_sw_instance[i].GPIO_Init);
    }
    for( i = 0 ; i < APP_SW_COUNT ; i ++ )
    {
        HAL_GPIO_WritePin(app_sw_instance[i].GPIOx , app_sw_instance[i].GPIO_Init.Pin , app_sw_instance[i].Begin_status);            
    }	
}

void APP_SW_H(uint8_t bsp_swx)
{
    HAL_GPIO_WritePin(app_sw_instance[bsp_swx].GPIOx , app_sw_instance[bsp_swx].GPIO_Init.Pin , GPIO_PIN_SET); 
}

void APP_SW_L(uint8_t bsp_swx)
{
    HAL_GPIO_WritePin(app_sw_instance[bsp_swx].GPIOx , app_sw_instance[bsp_swx].GPIO_Init.Pin , GPIO_PIN_RESET); 
}


void APP_SW_Toggle(uint8_t bsp_swx)
{
    HAL_GPIO_TogglePin(app_sw_instance[bsp_swx].GPIOx , app_sw_instance[bsp_swx].GPIO_Init.Pin);
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

