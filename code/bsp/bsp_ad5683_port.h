/**
 **************************************************************************************************
 * @file        bsp_ad5683_port.h
 * @author
 * @bsp_ad5683_port
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_AD5683_PORT_H_
#define _BSP_AD5683_PORT_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_ad5683_port_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_ad5683_port_Exported_Macros 
 * @{  
 */

#define AD5683_SYNC_UP  	HAL_GPIO_WritePin( GPIOB, GPIO_PIN_7 , GPIO_PIN_SET)
#define AD5683_SYNC_DOWN  	HAL_GPIO_WritePin( GPIOB, GPIO_PIN_7 , GPIO_PIN_RESET)

#define AD5683_REST_UP  	HAL_GPIO_WritePin( GPIOA, GPIO_PIN_12 , GPIO_PIN_SET)
#define AD5683_REST_DOWN  	HAL_GPIO_WritePin( GPIOA, GPIO_PIN_12 , GPIO_PIN_RESET)

#define AD5683_LDAC_UP  	HAL_GPIO_WritePin( GPIOB, GPIO_PIN_6 , GPIO_PIN_SET)
#define AD5683_LDAC_DOWN  	HAL_GPIO_WritePin( GPIOB, GPIO_PIN_6 , GPIO_PIN_RESET)

/**
 * @}
 */

/**
 * @defgroup      bsp_ad5683_port_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad5683_port_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad5683_port_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad5683_port_Exported_Functions 
 * @{  
 */
void BSP_AD5683_Pin_Init(void);
void BSP_AD5683_Tim_Init(void);
void BSP_AD5683_Start(void);
void BSP_AD5683_Stop(void);
void BSP_AD5683_WriteAndRead(uint8_t *tbuf , uint8_t * rbuf ,uint8_t len);
void BSP_AD5683_Write(uint8_t *buf , uint8_t len);
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
