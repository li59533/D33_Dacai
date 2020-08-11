/**
 **************************************************************************************************
 * @file        bsp_ad7682_port.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_ad7682_port.h"
#include "bsp_conf.h"
#include "bsp_spi.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    bsp_ad7682_port_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_ad7682_port_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_port_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_port_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_port_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_port_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_port_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_port_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_port_Functions 
 * @brief         
 * @{  
 */
void BSP_AD7682_Pin_Init(void)
{
	// -------SPI Init ----------
	BSP_SPI_Init(BSP_SPI_2);
}

void BSP_AD7682_Tim_Init(void)
{
	
}


void BSP_AD7682_StopSample(void)
{
	
}

void BSP_AD7682_StartSample(void)
{
	
}

void BSP_AD7682_StartCONV(void)
{
	
}

void BSP_AD7682_StopCONV(void)
{
	
}

void BSP_AD7682_Get(uint16_t cfg , uint16_t *value)
{
	BSP_SPI_WriteAndRead_Byte_IT( BSP_SPI_1, (uint8_t *)&cfg , (uint8_t *) value );
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

