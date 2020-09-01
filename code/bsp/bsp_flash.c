/**
 **************************************************************************************************
 * @file        bsp_flash.c
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

#include "clog.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_flash.h"
/**
 * @addtogroup    bsp_flash_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_flash_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_flash_Macros_Defines 
 * @brief         
 * @{  
 */
#define FLASH_PAGE_SIZE 0x20000
#define FLASH_BANK_SIZE 0xfffff
/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_flash_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Functions 
 * @brief         
 * @{  
 */
 
/*
00> PFlash:Example Start 
00> 
00> PFlash:Information 
00> Total:Program_Flash_Size: 1024KB, Hex:(0xfffff) 
00> Program:Flash_Sector_Size: 128KB, Hex:(0x20000) 

*/ 


int8_t BSP_Flash_WriteBytes(uint32_t addr_start , uint8_t * buf , uint16_t len)
{

	FLASH_EraseInitTypeDef pEraseInit ; 
	uint32_t SectorError ; 
	
	uint32_t addr_s = 0;
	addr_s = addr_start - FLASH_BASE;
	
	HAL_FLASH_Unlock();
	
	
	if((addr_s % 0x20000) == 0)
	{
		pEraseInit.Sector = addr_s / 0x20000 + 4;
		
		pEraseInit.Banks = FLASH_BANK_1;
		pEraseInit.NbSectors = 1;
		pEraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
		pEraseInit.VoltageRange  = FLASH_VOLTAGE_RANGE_3;	
		
		HAL_FLASHEx_Erase( &pEraseInit, &SectorError);
	}
	else
	{
		
	}
	
	for(uint16_t i = 0 ; i < len ; i ++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, addr_start ,(uint64_t )buf[i] );
		addr_start ++;
	}

	HAL_FLASH_Lock();
	

	return 0;
}

uint16_t BSP_Flash_ReadBytes(uint32_t addr,uint8_t *buf,uint16_t len)
{
	uint8_t * read_ptr = (uint8_t *)addr;
	for(uint16_t i = 0; i < len; i ++)
	{
		*(buf + i) = *(read_ptr + i);
	}
	return len;
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

