/**
 **************************************************************************************************
 * @file        bsp_spi.h
 * @author
 * @bsp_spi
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_SPI_H_
#define _BSP_SPI_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_spi_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_spi_Exported_Macros 
 * @{  
 */
#define BSP_SPI_1 		0
#define BSP_SPI_2		1

/**
 * @}
 */

/**
 * @defgroup      bsp_spi_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_spi_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_spi_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_spi_Exported_Functions 
 * @{  
 */
void BSP_SPI_Init(uint8_t bsp_spix);
void BSP_SPI_Write_IT(uint8_t bsp_spix , uint8_t *buf, uint16_t len);
void BSP_SPI_Write(uint8_t bsp_spix , uint8_t *buf, uint16_t len);
void BSP_SPI_Read_IT(uint8_t bsp_spix,uint8_t *buf , uint16_t len);
void BSP_SPI_WriteAndRead_Byte_IT(uint8_t bsp_spix,uint8_t *tbuf , uint8_t * rbuf);
void BSP_SPI_WriteAndRead_Bytes_IT(uint8_t bsp_spix,uint8_t *tbuf , uint8_t * rbuf ,uint8_t len);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
#endif
