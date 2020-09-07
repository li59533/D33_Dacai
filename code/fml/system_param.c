/**
 **************************************************************************************************
 * @file        system_param.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *              
 **************************************************************************************************
 */
#include "self_def.h"
#include "system_param.h"
#include "bsp_flash.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "crc.h"
#include "bsp_uniqueID.h"
/**
 * @addtogroup    system_param_Modules 
 * @{  
 */

/**
 * @defgroup      system_param_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Private_Variables 
 * @brief         
 * @{  
 */
const SystemParam_Config_t SystemParam_Config_Default = 
{
	//.SNcode ={ 0x12 , 0x34 ,0x56 , 0x78 , 0x90, 0xA0, 0xAB ,0x4F} ,
	.D_caliunit_value = 497 ,
	.D_cali_result = 1250 ,  
	.language_num = 0,
};
/**
 * @}
 */
    
/**
 * @defgroup      system_param_Public_Variables 
 * @brief         
 * @{  
 */
SystemParam_Config_t g_SystemParam_Config;
/**
 * @}
 */

/**
 * @defgroup      system_param_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Functions 
 * @brief         
 * @{  
 */
 
 
 
void SystemParam_Init(void)
{		
	BSP_Flash_ReadBytes(SYS_PARAM_SAVE_FLASH_FIRSTHEAD, (uint8_t *)&g_SystemParam_Config , sizeof(g_SystemParam_Config) );
	if(CRC16_Modbus((uint8_t *)&g_SystemParam_Config,sizeof(g_SystemParam_Config)) == 0) // Same Save
	{
		DEBUG("SysParam SNCode:");
		for(uint8_t i = 0 ; i < sizeof(g_SystemParam_Config.SNcode ) ; i++)
		{
			DEBUG("0x%x " , g_SystemParam_Config.SNcode[i]);
		}
		DEBUG("\r\n");	
		DEBUG("SYS Param Read OK\r\n");
	}
	else
	{
		BSP_Flash_ReadBytes(SYS_PARAM_SAVE_FLASH_SECONDHEAD, (uint8_t *)&g_SystemParam_Config , sizeof(g_SystemParam_Config) );
		if(CRC16_Modbus((uint8_t *)&g_SystemParam_Config,sizeof(g_SystemParam_Config)) == 0)
		{
			DEBUG("SysParam SNCode:");
			for(uint8_t i = 0 ; i < sizeof(g_SystemParam_Config.SNcode ) ; i++)
			{
				DEBUG("0x%x " , g_SystemParam_Config.SNcode[i]);
			}
			DEBUG("\r\n");	
			
			DEBUG("Sys D caliUnit:%d\r\n",g_SystemParam_Config.D_caliunit_value);
			DEBUG("Sys D cali result mv:%d\r\n",g_SystemParam_Config.D_cali_result);
			DEBUG("SYS Param Read OK\r\n");			
		}
		else
		{
			SystemParam_Reset();
		}		

	}

}

int16_t SystemParam_Read(uint8_t handle)
{
    switch (handle)
    {
        case SYSTEMPARAM_CONFIG:
        {
            if (1)
            {
                
            }
            break;
        }
    }
    return 0;
}

void SystemParam_Save(void)
{
	g_SystemParam_Config.crc = CRC16_Modbus((uint8_t*)&g_SystemParam_Config, sizeof(g_SystemParam_Config) - sizeof(g_SystemParam_Config.crc));
	BSP_Flash_WriteBytes(SYS_PARAM_SAVE_FLASH_FIRSTHEAD,(uint8_t *)&g_SystemParam_Config,sizeof(g_SystemParam_Config));
	BSP_Flash_WriteBytes(SYS_PARAM_SAVE_FLASH_SECONDHEAD,(uint8_t *)&g_SystemParam_Config,sizeof(g_SystemParam_Config));
	DEBUG("Sys save\r\n");
}

void SystemParam_Reset(void)
{
	g_SystemParam_Config = SystemParam_Config_Default;
	
	
	BSP_GetUniqueID();
	
	SystemParam_Save();
	DEBUG("SystemParam_Reset Load DefaultConf\r\n");

}

void SystemParam_Apply(uint8_t handle)
{
    switch (handle)
    {
        case SYSTEMPARAM_CONFIG:
        {
 
            break;
        }
    }
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

