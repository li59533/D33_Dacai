/**
 **************************************************************************************************
 * @file        dacai_protocol.c
 * @author
 * @dacai_protocol
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
#include "dacai_protocol.h"
/**
 * @addtogroup    dacai_protocol_Modules 
 * @{  
 */

/**
 * @defgroup      dacai_protocol_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       dacai_protocol_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_protocol_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       dacai_protocol_Private_Types
 * @brief         
 * @{  
 */
#pragma pack(1) 
typedef struct
{
	uint8_t head;
	uint8_t cmd;
	uint8_t msg;
	uint16_t screen_id;
	uint16_t control_id;
	uint8_t control_type;
	uint8_t *payload;
	uint8_t cmd_tail[4];
}Dacai_Protocol_t;
#pragma pack()
/**
 * @}
 */

/**
 * @defgroup      dacai_protocol_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_protocol_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_protocol_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_protocol_Functions 
 * @brief         
 * @{  
 */


/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

