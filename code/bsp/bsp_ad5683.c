/**
 **************************************************************************************************
 * @file        bsp_ad5683.c
 * @author
 * @bsp_ad5683
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
#include "bsp_conf.h"
#include "bsp_ad5683.h"
#include "bsp_ad5683_port.h"
/**
 * @addtogroup    bsp_ad5683_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_ad5683_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_ad5683_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad5683_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_ad5683_Private_Types
 * @brief         
 * @{  
 */
typedef union
{
	uint8_t buf[3];
	struct  {
		unsigned cmd:4;
		unsigned value:16;
		unsigned kong:4;
	}field;
}bsp_ad5683_sendbuf_u; 

typedef union
{
	uint16_t buf;
	struct  {
		unsigned rest:1; 	// 1-> rest,
		unsigned pd:2;	 	// 0-> Normal Mode , 
		unsigned ref:1;		// 0->Enable Internal REF , 1-> DISABLE
		unsigned gain:1;  	// 0->0~Vref   1->0~2*Vref
		unsigned dcen:1;  	// 0->independent 1->DCEN
		unsigned kong:10;
	}field;
}bsp_ad5683_conReg_u; 
/**
 * @}
 */

/**
 * @defgroup      bsp_ad5683_Private_Variables 
 * @brief         
 * @{  
 */

bsp_ad5683_conReg_u bsp_ad5683_conReg =
{
	.field.rest = 0,
	.field.pd = 0 , 
	.field.ref = 0 , 
	.field.gain = 0 ,
	.field.dcen = 0 ,
};

bsp_ad5683_sendbuf_u bsp_ad5683_sendbuf;
/**
 * @}
 */

/**
 * @defgroup      bsp_ad5683_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad5683_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void bsp_ad5683_writecmd(uint8_t cmd , uint16_t value);
/**
 * @}
 */

/**
 * @defgroup      bsp_ad5683_Functions 
 * @brief         
 * @{  
 */

void BSP_AD5683_Init(void)
{
	BSP_AD5683_Pin_Init();
	BSP_AD5683_Tim_Init();
	bsp_ad5683_writecmd(AD5683_CMD_None , 0);
	bsp_ad5683_writecmd(AD5683_CMD_W_ConReg , (uint16_t )bsp_ad5683_conReg.buf);
}

static void bsp_ad5683_writecmd(uint8_t cmd , uint16_t value)
{
	/*
	uint8_t cmdbuf[3];
	uint8_t temp[2];
	memcpy(temp , (uint8_t * )&value , 2);
	
	cmdbuf[0] = (cmd << 4 | temp[0] >> 4);
	cmdbuf[1] = (temp[0]<<4 | temp[1] >> 4);
	cmdbuf[2] = (temp[1] << 4 );
	
	BSP_AD5683_Write(cmdbuf , 3);
	*/ 
	
	bsp_ad5683_sendbuf.field.cmd = cmd;
	bsp_ad5683_sendbuf.field.value = value;
	bsp_ad5683_sendbuf.field.kong = 0;
	
	AD5683_SYNC_DOWN;
	BSP_AD5683_Write(bsp_ad5683_sendbuf.buf , 3);
	AD5683_SYNC_UP;
	AD5683_LDAC_DOWN;
	AD5683_LDAC_UP;
}


// -------------Test Code -------------------
void BSP_AD5683_Test(void)
{
	bsp_ad5683_writecmd(AD5683_CMD_W_InDACReg , 0x00ff);
}
// ------------------------------------------


/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

