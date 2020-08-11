/**
 **************************************************************************************************
 * @file        bsp_ad5683.h
 * @author
 * @bsp_ad5683
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_AD5683_H_
#define _BSP_AD5683_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_ad5683_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_ad5683_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad5683_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad5683_Exported_Types 
 * @{  
 */
typedef enum
{
	AD5683_CMD_None 		= 0x00,
	AD5683_CMD_W_InReg 		= 0x01,
	AD5683_CMD_UP_DACReg 	= 0x02,
	AD5683_CMD_W_InDACReg 	= 0x03,
	AD5683_CMD_W_ConReg		= 0x04,
	AD5683_CMD_R_InReg 		= 0x05,
}BSP_AD5683_Cmd_e;


/**
 * @}
 */

/**
 * @defgroup      bsp_ad5683_Exported_Variables 
 * @{  
 */

/**
 * @}
 */ 

/**
 * @defgroup      bsp_ad5683_Exported_Functions 
 * @{  
 */
void BSP_AD5683_Init(void);
void BSP_AD5683_SetOut(uint16_t value);

// -----------Test Code ----------
void BSP_AD5683_Test(void);
// -------------------------------


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
