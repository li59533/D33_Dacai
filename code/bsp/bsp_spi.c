/**
 **************************************************************************************************
 * @file        bsp_spi.c
 * @author
 * @bsp_spi
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
#include "bsp_spi.h"
#include "bsp_conf.h"
/**
 * @addtogroup    bsp_spi_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_spi_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_spi_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_spi_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_spi_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_spi_Private_Variables 
 * @brief         
 * @{  
 */
SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
/**
 * @}
 */

/**
 * @defgroup      bsp_spi_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_spi_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_spi_Functions 
 * @brief         
 * @{  
 */
 



void BSP_SPI_Init(uint8_t bsp_spix)
{
	if(bsp_spix == BSP_SPI_1)
	{
		hspi1.Instance = SPI1;
		hspi1.Init.Mode = SPI_MODE_MASTER;
		hspi1.Init.Direction = SPI_DIRECTION_2LINES;
		hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
		hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
		hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
		hspi1.Init.NSS = SPI_NSS_SOFT;
		hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
		hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
		hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
		hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
		hspi1.Init.CRCPolynomial = 7;
		if (HAL_SPI_Init(&hspi1) != HAL_OK)
		{
			Error_Handler();
		}		
	}
	else if(bsp_spix == BSP_SPI_2)
	{
		hspi2.Instance = SPI2;
		hspi2.Init.Mode = SPI_MODE_MASTER;
		hspi2.Init.Direction = SPI_DIRECTION_2LINES;
		hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
		hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
		hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
		hspi2.Init.NSS = SPI_NSS_HARD_OUTPUT;
		hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
		hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
		hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
		hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
		hspi2.Init.CRCPolynomial = 7;
		if (HAL_SPI_Init(&hspi2) != HAL_OK)
		{
			Error_Handler();
		}
	}
}


void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(spiHandle->Instance==SPI1)
	{
		/* USER CODE BEGIN SPI1_MspInit 0 */

		/* USER CODE END SPI1_MspInit 0 */
		/* SPI1 clock enable */
		__HAL_RCC_SPI1_CLK_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**SPI1 GPIO Configuration
		PB3     ------> SPI1_SCK
		PB4     ------> SPI1_MISO
		PB5     ------> SPI1_MOSI
		*/
		
		GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USER CODE BEGIN SPI1_MspInit 1 */
		HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(SPI1_IRQn);
		/* USER CODE END SPI1_MspInit 1 */
	}
	else if(spiHandle->Instance==SPI2)
	{
		/* USER CODE BEGIN SPI2_MspInit 0 */

		/* USER CODE END SPI2_MspInit 0 */
		/* SPI2 clock enable */
		__HAL_RCC_SPI2_CLK_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**SPI2 GPIO Configuration
		PB12     ------> SPI2_NSS
		PB13     ------> SPI2_SCK
		PB14     ------> SPI2_MISO
		PB15     ------> SPI2_MOSI
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USER CODE BEGIN SPI2_MspInit 1 */
		// --------NVIC configuration--------
		HAL_NVIC_SetPriority(SPI2_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(SPI2_IRQn);
		// ----------------------------------
		/* USER CODE END SPI2_MspInit 1 */
	}
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

	if(spiHandle->Instance==SPI1)
	{
		/* USER CODE BEGIN SPI1_MspDeInit 0 */

		/* USER CODE END SPI1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_SPI1_CLK_DISABLE();

		/**SPI1 GPIO Configuration
		PB3     ------> SPI1_SCK
		PB4     ------> SPI1_MISO
		PB5     ------> SPI1_MOSI
		*/
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);

		/* USER CODE BEGIN SPI1_MspDeInit 1 */

		/* USER CODE END SPI1_MspDeInit 1 */
	}
	else if(spiHandle->Instance==SPI2)
	{
		/* USER CODE BEGIN SPI2_MspDeInit 0 */

		/* USER CODE END SPI2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_SPI2_CLK_DISABLE();

		/**SPI2 GPIO Configuration
		PB12     ------> SPI2_NSS
		PB13     ------> SPI2_SCK
		PB14     ------> SPI2_MISO
		PB15     ------> SPI2_MOSI
		*/
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

		/* USER CODE BEGIN SPI2_MspDeInit 1 */

		/* USER CODE END SPI2_MspDeInit 1 */
	}
}



void BSP_SPI_Write_IT(uint8_t bsp_spix , uint8_t *buf, uint16_t len)
{
	switch(bsp_spix)
	{
		case BSP_SPI_1: HAL_SPI_Transmit_IT(&hspi1, buf , len) ; break;
		case BSP_SPI_2: HAL_SPI_Transmit_IT(&hspi2, buf , len) ; break;
		default:break;
	}
}

void BSP_SPI_Write(uint8_t bsp_spix , uint8_t *buf, uint16_t len)
{
	switch(bsp_spix)
	{
		case BSP_SPI_1: HAL_SPI_Transmit(&hspi1, buf , len , 1);break;
		case BSP_SPI_2: HAL_SPI_Transmit(&hspi2, buf , len , 1);break;
		default:break;
	}	
	
}

void BSP_SPI_Read_IT(uint8_t bsp_spix,uint8_t *buf , uint16_t len)
{
	switch(bsp_spix)
	{
		case BSP_SPI_1: HAL_SPI_Receive_IT(&hspi1, buf , len);break;
		case BSP_SPI_2: HAL_SPI_Receive_IT(&hspi2, buf , len);break;
		default:break;
	}	
	
}

void BSP_SPI_WriteAndRead_Byte_IT(uint8_t bsp_spix,uint8_t *tbuf , uint8_t * rbuf)
{
	switch(bsp_spix)
	{
		case BSP_SPI_1:HAL_SPI_TransmitReceive_IT( &hspi1 , tbuf , rbuf , 1); break;
		case BSP_SPI_2:HAL_SPI_TransmitReceive_IT( &hspi2 , tbuf , rbuf , 1); break;
		default:break;
	}	
	
}

void BSP_SPI_WriteAndRead_Bytes_IT(uint8_t bsp_spix,uint8_t *tbuf , uint8_t * rbuf ,uint8_t len)
{
	switch(bsp_spix)
	{
		case BSP_SPI_1:HAL_SPI_TransmitReceive_IT( &hspi1 , tbuf , rbuf , len); break;
		case BSP_SPI_2:HAL_SPI_TransmitReceive_IT( &hspi2 , tbuf , rbuf , len); break;
		default:break;
	}	
	
}


void SPI1_IRQHandler(void)
{
	HAL_SPI_IRQHandler(&hspi1); // clear some flag
	if(HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_READY)
	{
		
		//BSP_AD7682_GetValue();
	}		
	
	//DEBUG("SPI IRQ\r\n");
}


void BSP_SPI2_IRQHandler(void)
{
	HAL_SPI_IRQHandler(&hspi2); // clear some flag
	if(HAL_SPI_GetState(&hspi2) == HAL_SPI_STATE_READY)
	{
		
		//BSP_AD7682_GetValue();
	}		
	
	//DEBUG("SPI IRQ\r\n");
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

