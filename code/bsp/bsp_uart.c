/**
 **************************************************************************************************
 * @file        bsp_uart.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_conf.h"
#include "bsp_uart.h"
#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_led.h"
#include "dacai_port.h"
#include "mcuprotocol.h"

/**
 * @addtogroup    bsp_uart_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_uart_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_uart_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_uart_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Private_Variables 
 * @brief         
 * @{  
 */
 
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

DMA_HandleTypeDef hdma_usart1_tx ; 
DMA_HandleTypeDef hdma_usart3_tx ; 
 
//static uint8_t USART1_Tx_Buf[BSP_USART1_TXBUF_SIZE] = { 0 };
static uint8_t USART1_Rx_Buf[BSP_USART1_RXBUF_SIZE] = { 0 };

//static uint8_t USART3_Tx_Buf[BSP_USART3_TXBUF_SIZE] = { 0 };
static uint8_t USART3_Rx_Buf[BSP_USART3_RXBUF_SIZE] = { 0 };



/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Functions 
 * @brief         
 * @{  
 */

void BSP_USART_Init(uint8_t BSP_USARTx, uint8_t *userparams)
{

	USART_HandleTypeDef USART_Handle ; 
	switch(BSP_USARTx)
	{
		case BSP_USART1:
		{	
			/* Initialization and Configuration functions *********************************/
			huart1.Instance = USART1;
			huart1.Init.BaudRate = 115200;
			huart1.Init.WordLength = UART_WORDLENGTH_8B;
			huart1.Init.StopBits = UART_STOPBITS_1;
			huart1.Init.Parity = UART_PARITY_NONE;
			huart1.Init.Mode = UART_MODE_TX_RX;
			huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
			huart1.Init.OverSampling = UART_OVERSAMPLING_16;
			if (HAL_UART_Init(&huart1) != HAL_OK)
			{
				Error_Handler();
			}
			HAL_UART_Receive_IT(&huart1, USART1_Rx_Buf, 1);	
		}
		break;
		case BSP_USART3:
		{	
			/* Initialization and Configuration functions *********************************/
			huart3.Instance = USART3;
			huart3.Init.BaudRate = 19200;
			huart3.Init.WordLength = UART_WORDLENGTH_8B;
			huart3.Init.StopBits = UART_STOPBITS_1;
			huart3.Init.Parity = UART_PARITY_NONE;
			huart3.Init.Mode = UART_MODE_TX_RX;
			huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
			huart3.Init.OverSampling = UART_OVERSAMPLING_16;
			if (HAL_UART_Init(&huart3) != HAL_OK)
			{
				Error_Handler();
			}
			// UART Rx Init
			HAL_UART_Receive_IT(&huart3, USART3_Rx_Buf, 1);		
		}
		break;
		default:break;
	}
}

void BSP_USART_Close(uint8_t BSP_USARTx)
{
	
}

// ----------- Msp Func ------------
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(huart->Instance==USART1)
	{
		/* USER CODE BEGIN USART1_MspInit 0 */

		/* USER CODE END USART1_MspInit 0 */
		/* USART1 clock enable */
		__HAL_RCC_USART1_CLK_ENABLE();
		__HAL_RCC_DMA2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART1 GPIO Configuration
		PA9     ------> USART1_TX
		PA10     ------> USART1_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		// UART Rx Init
		HAL_UART_Receive_IT(huart, USART1_Rx_Buf, 1);
		
		/* USART1 DMA Init */
		/* USART1_TX Init */
		hdma_usart1_tx.Instance = DMA2_Stream7;
		hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;
		hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart1_tx.Init.Mode = DMA_NORMAL;
		hdma_usart1_tx.Init.Priority = DMA_PRIORITY_MEDIUM;
		hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(huart,hdmatx,hdma_usart1_tx);


		/* USART1 interrupt Init */
		HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		/* USER CODE BEGIN USART1_MspInit 1 */
		/* DMA2_Stream7_IRQn interrupt configuration */
		HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
		/* USER CODE END USART1_MspInit 1 */
	}
	else if(huart->Instance==USART3)
	{
		/* USER CODE BEGIN USART3_MspInit 0 */

		/* USER CODE END USART3_MspInit 0 */
		/* USART3 clock enable */
		__HAL_RCC_USART3_CLK_ENABLE();

		__HAL_RCC_GPIOD_CLK_ENABLE();
		__HAL_RCC_DMA1_CLK_ENABLE();
		/**USART3 GPIO Configuration
		PD8     ------> USART3_TX
		PD9     ------> USART3_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

		
		/* USART3 DMA Init */
		/* USART3_TX Init  */
		hdma_usart3_tx.Instance = DMA1_Stream3;
		hdma_usart3_tx.Init.Channel = DMA_CHANNEL_4;
		hdma_usart3_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_usart3_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart3_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart3_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart3_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart3_tx.Init.Mode = DMA_NORMAL;
		hdma_usart3_tx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_usart3_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

		if (HAL_DMA_Init(&hdma_usart3_tx) != HAL_OK)
		{
			Error_Handler();
		}
		
		__HAL_LINKDMA(huart,hdmatx,hdma_usart3_tx);
	
		/* USART3 interrupt Init */
		HAL_NVIC_SetPriority(USART3_IRQn, 6, 0);
		HAL_NVIC_EnableIRQ(USART3_IRQn);
		/* USER CODE BEGIN USART3_MspInit 1 */
		/* DMA interrupt init */
		/* DMA1_Stream3_IRQn interrupt configuration */
		HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);
		/* USER CODE END USART3_MspInit 1 */
	}
}


void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{

	if(huart->Instance==USART1)
	{
		/* USER CODE BEGIN USART1_MspDeInit 0 */

		/* USER CODE END USART1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART1_CLK_DISABLE();

		/**USART1 GPIO Configuration
		PA9     ------> USART1_TX
		PA10     ------> USART1_RX
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

		/* USART1 DMA DeInit */
		HAL_DMA_DeInit(huart->hdmatx);

		/* USART1 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART1_IRQn);
		/* USER CODE BEGIN USART1_MspDeInit 1 */

		/* USER CODE END USART1_MspDeInit 1 */
	}
	else if(huart->Instance==USART3)
	{
		/* USER CODE BEGIN USART3_MspDeInit 0 */

		/* USER CODE END USART3_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART3_CLK_DISABLE();

		/**USART3 GPIO Configuration
		PD8     ------> USART3_TX
		PD9     ------> USART3_RX
		*/
		HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8|GPIO_PIN_9);

		/* USART3 DMA DeInit */
		HAL_DMA_DeInit(huart->hdmatx);

		/* USART3 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART3_IRQn);
		/* USER CODE BEGIN USART3_MspDeInit 1 */

		/* USER CODE END USART3_MspDeInit 1 */
	}
}

// --------------------------------
// ---------- 485 en --------------
/*
static void bsp_usart_485en_R(uint8_t BSP_USARTx)
{
	switch(BSP_USARTx)
	{
		case BSP_USART1: break;
		case BSP_USART6: break;
		default:break;
	}
}

static void bsp_usart_485en_T(uint8_t BSP_USARTx)
{
	switch(BSP_USARTx)
	{
		case BSP_USART1: break;
		case BSP_USART6: break;
		default:break;
	}
}
*/
// --------------------------------

void BSP_USART_WriteBytes_DMA(uint8_t BSP_USARTx,uint8_t* pbuf,uint16_t len)
{
	switch(BSP_USARTx)
	{
		case BSP_USART1:
			{
				HAL_UART_Transmit_DMA(&huart1, pbuf, len);				
			}
			break;
		case BSP_USART3:
			{
				HAL_UART_Transmit_DMA(&huart3, pbuf, len);	
			}
			break;
		default:
			{
				DEBUG("Usart %d is err\r\n",BSP_USARTx);
			}
			break;
	}

	
}

uint16_t BSP_USART_ReadBytes_DMA(uint8_t BSP_USARTx)
{
	return 0;
}


// ----------this send way is very danger !!!!----------
void BSP_USART_WriteBytes(uint8_t BSP_USARTx,uint8_t* pBuf,uint16_t length)
{

}
	
uint16_t BSP_USART_ReadBytes(uint8_t BSP_USARTx,uint8_t* pBuf,uint16_t length)
{
	return 0;
}
// -------------------------------------------------

// -------------- IRQ ------------------------------
void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart1);
	HAL_UART_Receive_IT(&huart1, USART1_Rx_Buf, 1);
}

void USART3_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart3);
	HAL_UART_Receive_IT(&huart3, USART3_Rx_Buf, 1);
}

void DMA2_Stream7_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_usart1_tx);
}

void DMA1_Stream3_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_usart3_tx);
	//DEBUG("DMA1_Stream3_IRQHandler\r\n" );
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART1)
	{
		DEBUG("UART1_RxCplt:%x\r\n" , USART1_Rx_Buf[0]);
		MCUprotocol_FlowAnalysis( MCUPROTOCOL_FLOWCHANNEL_CONF , USART1_Rx_Buf , 1);
		
	}
	else if(huart->Instance==USART3)
	{
		Dacai_Port_Rev(USART3_Rx_Buf[0]);

		//DEBUG("UART3_RxCplt:%x\r\n" , USART3_Rx_Buf[0]);
	}
}



void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	//DEBUG("HAL_UART_TxCpltCallback");
}

// -------------------------------------------------



// --------------- Test Code -----------------------
uint8_t testbuf[] = {0x01 , 0x02, 0x03, 0x05,0x04,0xff,0xcd};
void BSP_Uart_TestCode(void)
{
	BSP_USART_WriteBytes_DMA(BSP_USART3,testbuf,sizeof(testbuf));
}

// -------------------------------------------------
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

