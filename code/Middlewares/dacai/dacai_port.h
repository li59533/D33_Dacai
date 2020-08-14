/**
 **************************************************************************************************
 * @file        dacai_port.h
 * @author
 * @dacai_port
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _DACAI_PORT_H_
#define _DACAI_PORT_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    dacai_port_Modules 
 * @{  
 */

/**
 * @defgroup      dacai_port_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_port_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_port_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_port_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_port_Exported_Functions 
 * @{  
 */
void Dacai_Port_Init(void);
void Dacai_Port_Send(uint8_t *buf , uint16_t len);
void Dacai_Port_Rev(uint8_t buf);

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
