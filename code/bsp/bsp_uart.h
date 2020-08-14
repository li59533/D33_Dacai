/**
 **************************************************************************************************
 * @file        bsp_uart.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_UART_H_
#define _BSP_UART_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
#include "bsp_conf.h"
/**
 * @addtogroup    bsp_uart_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_uart_Exported_Macros 
 * @{  
 */
#define BSP_UART_COUNT			2
#define BSP_USART1				0

#define BSP_USART3				1

//#define BSP_USART6				2


#define BSP_USART1_TXBUF_SIZE 	256	
#define BSP_USART1_RXBUF_SIZE	256
#define BSP_USART2_TXBUF_SIZE	256
#define BSP_USART2_RXBUF_SIZE	256

#define BSP_USART3_TXBUF_SIZE	256
#define BSP_USART3_RXBUF_SIZE	256


#define BSP_USART1_TX_DMA_ACTIVE 	1
#define BSP_USART1_RX_DMA_ACTIVE	1

#if BSP_USART1_RX_DMA_ACTIVE == 1
	#define BSP_USART1_IDEL_ACTIVE  1
#else
	#define BSP_USART1_IDEL_ACTIVE  0
#endif


#define BSP_USART3_TX_DMA_ACTIVE 	1
#define BSP_USART3_RX_DMA_ACTIVE	1

#if BSP_USART3_RX_DMA_ACTIVE == 1
	#define BSP_USART3_IDEL_ACTIVE  1
#else
	#define BSP_USART3_IDEL_ACTIVE  0
#endif


/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Exported_Functions 
 * @{  
 */
 
void BSP_USART_Init(uint8_t BSP_USARTx, uint8_t *userparams);
void BSP_USART_WriteBytes_DMA(uint8_t BSP_USARTx,uint8_t* pBuf,uint16_t length);
void BSP_USART_WriteBytes(uint8_t BSP_USARTx,uint8_t* pBuf,uint16_t length);
	

 
// ------------Test-------------

void BSP_Uart_TestCode(void);
// -----------------------------

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
