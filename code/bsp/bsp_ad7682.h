/**
 **************************************************************************************************
 * @file        bsp_ad7682.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_AD7682_H_
#define _BSP_AD7682_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "bsp_ad7682_port.h"
/**
 * @addtogroup    bsp_ad7682_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_ad7682_Exported_Macros 
 * @{  
 */

#define BSP_AD7682_SAVE_SIZE     	1000	// 

#define BSP_AD7682_CHANNEL_0		0
#define BSP_AD7682_CHANNEL_1		1
#define BSP_AD7682_CHANNEL_2		2
#define BSP_AD7682_CHANNEL_3		3


/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_Exported_Types 
 * @{  
 */
typedef struct
{
	uint16_t curvalue;
	uint16_t buf[BSP_AD7682_SAVE_SIZE];
	uint16_t index;
	uint8_t buf_flag;
}BSP_AD7682_Value_t;
/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Exported_Variables 
 * @{  
 */
extern BSP_AD7682_Value_t BSP_AD7682_Value[4];
/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Exported_Functions 
 * @{  
 */


void BSP_AD7682_Init(void);
void BSP_AD7682_LoopTrig(void);   // usual in tim interrupt
void BSP_AD7682_SPI_GetValue(void);  // in SPI interrupt


// ------------- Test Code ------------

void BSP_AD7682_TestCode(void);
// ------------------------------------

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
