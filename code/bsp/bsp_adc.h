/**
 **************************************************************************************************
 * @file        bsp_adc.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_ADC_H_
#define _BSP_ADC_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_adc_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_adc_Exported_Macros 
 * @{  
 */
#define BSP_ADC_CHANNEL_COUNT 	2
#define BSP_ADC_CHANNEL_0		0
#define BSP_ADC_CHANNEL_1		1


// ------------User Channel define ---------------
#define BSP_ADC_SIG_CHANNEL		BSP_ADC_CHANNEL_0
#define BSP_ADC_CAL_CHANNEL		BSP_ADC_CHANNEL_1


// -----------------------------------------------

/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Exported_Types 
 * @{  
 */
typedef struct
{
	uint16_t average;
	float real_mv;
}bsp_adc_data_t;

/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Exported_Variables 
 * @{  
 */
extern bsp_adc_data_t BSP_ADC_Value[BSP_ADC_CHANNEL_COUNT];
/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Exported_Functions 
 * @{  
 */
void BSP_ADC_Init(void);
void BSP_ADC_DeInit(void);

void BSP_ADC_DisableIRQ(void);
void BSP_ADC_EnableIRQ(void);



// ----------TestCode -------------
void BSP_ADC_ShowValue(void);
// --------------------------------

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
