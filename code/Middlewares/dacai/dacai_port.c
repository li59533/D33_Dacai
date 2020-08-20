/**
 **************************************************************************************************
 * @file        dacai_port.c
 * @author
 * @dacai_port
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
#include "dacai_task.h"
#include "dacai_port.h"
#include "dacai.h"
#include "bsp_conf.h"
#include "bsp_uart.h"
#include "app_guifunc.h"
/**
 * @addtogroup    dacai_port_Modules 
 * @{  
 */

/**
 * @defgroup      dacai_port_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       dacai_port_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_port_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       dacai_port_Private_Types
 * @brief         
 * @{  
 */



/**
 * @}
 */

/**
 * @defgroup      dacai_port_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_port_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_port_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_port_Functions 
 * @brief         
 * @{  
 */
void Dacai_Port_Init(void)
{
	BSP_USART_Init( BSP_USART3 , 0);
	
	Dacai_Button_CallbackRegister(APP_GuiButton_Process);
	
	
}

void Dacai_Port_Send(uint8_t *buf , uint16_t len)
{
	BSP_USART_WriteBytes_DMA(BSP_USART3 , buf , len);
}


void Dacai_Port_Rev(uint8_t buf)
{
	Dacai_Ring_in_Byte(buf);
	Dacai_Task_Event_Start(DACAI_TASK_REV_EVENT, EVENT_FROM_ISR);
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

