/**
 **************************************************************************************************
 * @file        bsp_ad7682.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_ad7682.h"
#include "bsp_conf.h"
#include "bsp_ad7682_port.h"
#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    bsp_ad7682_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_ad7682_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Macros_Defines 
 * @brief         
 * @{  
 */
#define BSP_AD7682_SAMPLE_CFG 		0x3A41 	// 0x3A71 : external 2.5V  ,0x3A41: internal 2.5V


/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_Constants_Defines 
 * @brief         
 * @{  
 */


/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Private_Types
 * @brief         
 * @{  
 */


typedef struct
{
	uint8_t req_index;
	uint8_t resp_index;
}bsp_ad7682_reqrespindex_t;

/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_Private_Variables 
 * @brief         
 * @{  
 */

BSP_AD7682_Value_t BSP_AD7682_Value[4] = 
{
	{
		.curvalue = 0,
		.index = 0,
		.buf_flag = 0,
	},
	{
		.curvalue = 0,
		.index = 0,
		.buf_flag = 0,
	},	
	{
		.curvalue = 0,
		.index = 0,
		.buf_flag = 0,
	},
	{
		.curvalue = 0,
		.index = 0,
		.buf_flag = 0,
	},	
};

static uint8_t bsp_ad7682_ch_seq[4] = { 0 , 1 , 2 , 3 };

bsp_ad7682_reqrespindex_t curindex = 
{
	.req_index = 0,
	.resp_index = 0,
};

static uint16_t bsp_ad7682_curvalue = 0;

/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Functions 
 * @brief         
 * @{  
 */

void BSP_AD7682_Init(void)
{
	BSP_AD7682_Pin_Init();
	DEBUG("BSP_AD7682 is Init\r\n");
}
  
void BSP_AD7682_StartGetValue_InConf(void)
{
	/*
	uint8_t next_ad_ch = 0;
	uint16_t ad7682_cfg = 0 ; 
	next_ad_ch = bsp_ad7682_ch_queue[bsp_ad7682_cur_ad_ch];

	ad7682_cfg = (uint16_t)BSP_AD7682_SAMPLE_CFG | ( next_ad_ch << 7 );
	ad7682_cfg=ad7682_cfg << 2;
	BSP_AD7682_StartCONV();
	BSP_AD7682_Get( ad7682_cfg , &bsp_ad7682_rec[bsp_ad7682_cur_ad_ch]);
	*/
}

void BSP_AD7682_LoopTrig(void)   // usual in tim interrupt
{
	uint8_t req_channel = 0;
	uint8_t resp_channel = 0;
	uint16_t ad7682_cfg = 0 ; 
	
	req_channel = bsp_ad7682_ch_seq[curindex.req_index];
	ad7682_cfg = (uint16_t)BSP_AD7682_SAMPLE_CFG | ( req_channel << 7 );
	ad7682_cfg = ad7682_cfg << 2;
	
	BSP_AD7682_Get( ad7682_cfg , &bsp_ad7682_curvalue);

}

void BSP_AD7682_SPI_GetValue(void)  // in SPI interrupt
{
	static uint8_t start_getflag = 0;
	
	
	
	if(curindex.req_index > curindex.resp_index)
	{
		if((curindex.req_index - curindex.resp_index) == 2)
		{
			start_getflag = 1;
		}
		else
		{
			start_getflag = 0;
		}
	}
	else
	{
		if((curindex.req_index + 4 - curindex.resp_index) == 2)
		{
			start_getflag = 1;
		}
		else
		{
			start_getflag = 0;
		}
	}
	
	if(start_getflag == 1)
	{
		BSP_AD7682_Value[curindex.resp_index].curvalue = bsp_ad7682_curvalue;
		BSP_AD7682_Value[curindex.resp_index].buf[BSP_AD7682_Value[curindex.resp_index].index ++] = bsp_ad7682_curvalue;
		if(BSP_AD7682_Value[curindex.resp_index].index == BSP_AD7682_SAVE_SIZE)
		{
			BSP_AD7682_Value[curindex.resp_index].index = 0;
			BSP_AD7682_Value[curindex.resp_index].buf_flag = 1;
		}
		
		curindex.resp_index ++;
		curindex.resp_index %= 4;
		
	}
	
	curindex.req_index ++;
	curindex.req_index %= 4;

}



// -------------- Test Code -------------------

void BSP_AD7682_TestCode(void)
{
	
}


// --------------------------------------------
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

