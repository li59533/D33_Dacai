/**
 **************************************************************************************************
 * @file        dacai.h
 * @author
 * @dacai
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _DACAI_H_
#define _DACAI_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    dacai_Modules 
 * @{  
 */
#include "dacai_protocol.h"
/**
 * @defgroup      dacai_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_Exported_Functions 
 * @{  
 */
void Dacai_Init(void);
void Dacai_RevPorcess(void);
void Dacai_Send_Process(void);

// ---------- Ring / Queue Func-----------------
void Dacai_Ring_in_Byte(uint8_t buf);
int8_t Dacai_Ring_out_Byte(uint8_t * buf);
void Dacai_Queue_in_Bytes(uint8_t * buf , uint16_t len);
int8_t Dacai_Queue_out_Bytes(uint8_t * buf, uint16_t * len);


// ---------- Test Code ------------------------
void Dacai_TestCode(void);
// ---------------------------------------------
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
