/**
 **************************************************************************************************
 * @file        bsp_ad5683_port.c
 * @author
 * @bsp_ad5683_port
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
#include "bsp_ad5683_port.h"
#include "bsp_spi.h"
#include "bsp_tim.h"

/**
 * @addtogroup    bsp_ad5683_port_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_ad5683_port_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_ad5683_port_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad5683_port_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_ad5683_port_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad5683_port_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad5683_port_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad5683_port_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad5683_port_Functions 
 * @brief         
 * @{  
 */
 



void BSP_AD5683_Pin_Init(void)
{
	// -----GPIO Init ------
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	/**SPI1 GPIO Configuration
	PB3     ------> SPI1_SCK
	PB4     ------> SPI1_MISO
	PB5     ------> SPI1_MOSI
	
	PA12  	------> Rest
	PB6		------> LDAC
	PB7		------> SYNC
	*/
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);	
	
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);		
	// ------------------------
	AD5683_REST_DOWN;
	HAL_Delay(1);
	AD5683_REST_UP;
	AD5683_LDAC_UP;
	AD5683_SYNC_UP;
	// -----SPI Init -------
	BSP_SPI_Init(BSP_SPI_1);
	
	
}

void BSP_AD5683_Tim_Init(void)
{
	
}

void BSP_AD5683_Start(void)
{
	
}

void BSP_AD5683_Stop(void)
{
	
}


void BSP_AD5683_WriteAndRead(uint8_t *tbuf , uint8_t * rbuf ,uint8_t len)
{
	BSP_SPI_WriteAndRead_Bytes_IT(BSP_SPI_1, tbuf ,  rbuf , len);
}

void BSP_AD5683_Write(uint8_t *buf , uint8_t len)
{
	//static uint8_t r_buf[3];
	BSP_SPI_Write( BSP_SPI_1 , buf ,len);
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

