/**
 **************************************************************************************************
 * @file        bsp_flash.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_FLASH_H_
#define _BSP_FLASH_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_flash_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_flash_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Exported_Functions 
 * @{  
 */
 
int8_t BSP_Flash_WriteBytes(uint32_t addr_start , uint8_t * buf , uint16_t len);
uint16_t BSP_Flash_ReadBytes(uint32_t addr,uint8_t *buf,uint16_t len);

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
