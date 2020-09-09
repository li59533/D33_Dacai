/**
 **************************************************************************************************
 * @file        app_conf.c
 * @author
 * @app_conf
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
#include "app_conf.h"
#include "mcuprotocol.h"
#include "bsp_uart.h"
#include "conf_task.h"
#include "rtos_tools.h"
/**
 * @addtogroup    app_conf_Modules 
 * @{  
 */

/**
 * @defgroup      app_conf_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       app_conf_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       app_conf_Private_Types
 * @brief         
 * @{  
 */
#pragma pack(1)
typedef struct
{
	uint8_t buf[500];
	uint16_t len;
}APP_Conf_R_buf_t;

typedef struct
{
	APP_Conf_R_buf_t Queue[2];
	uint8_t in ;
	uint8_t out;
	uint8_t count;
	uint8_t size;
}APP_Conf_R_Queue_t ; 

typedef struct
{
	uint8_t buf[500];
	uint16_t len;
}APP_Conf_T_buf_t;

typedef struct
{
	APP_Conf_R_buf_t Queue[2];
	uint8_t in ;
	uint8_t out;
	uint8_t count;
	uint8_t size;
}APP_Conf_T_Queue_t ; 


#pragma pack()
/**
 * @}
 */

/**
 * @defgroup      app_conf_Private_Variables 
 * @brief         
 * @{  
 */
APP_Conf_R_Queue_t APP_Conf_R_Queue = 
{
	.in = 0,
	.out = 0 , 
	.count = 0 ,
	.size = sizeof(APP_Conf_R_Queue.Queue) / sizeof(APP_Conf_R_Queue.Queue[0]),
};
APP_Conf_T_Queue_t APP_Conf_T_Queue = 
{
	.in = 0,
	.out = 0 , 
	.count = 0 ,
	.size = sizeof(APP_Conf_T_Queue.Queue) / sizeof(APP_Conf_T_Queue.Queue[0]),	
};
/**
 * @}
 */

/**
 * @defgroup      app_conf_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void app_conf_in_R_queue(uint8_t * buf , uint16_t len);
static int8_t app_conf_out_R_queue(uint8_t * buf , uint16_t *len);
/**
 * @}
 */

/**
 * @defgroup      app_conf_Functions 
 * @brief         
 * @{  
 */
 
 
void APP_Conf_ProtocolInit(void)
{
	MCUprotocol_FlowSetCallback( MCUPROTOCOL_FLOWCHANNEL_CONF , app_conf_in_R_queue );
	
	//MCU_P2P_FrameTypeDataSet_Callback(void (*callback)(uint8_t * buf ,uint16_t len));
}

static void app_conf_in_R_queue(uint8_t * buf , uint16_t len)
{
	memcpy(APP_Conf_R_Queue.Queue[APP_Conf_R_Queue.in].buf , buf , len);
	APP_Conf_R_Queue.Queue[APP_Conf_R_Queue.in].len = len;
	
	APP_Conf_R_Queue.in ++;     
	APP_Conf_R_Queue.in %= APP_Conf_R_Queue.size;
	APP_Conf_R_Queue.count ++;
	
	Conf_Task_Event_Start(CONF_TASK_REV_EVENT, EVENT_FROM_ISR);
}

static int8_t app_conf_out_R_queue(uint8_t * buf , uint16_t *len)
{
	if(APP_Conf_R_Queue.count > 0)
	{
		memcpy(buf ,APP_Conf_R_Queue.Queue[APP_Conf_R_Queue.out].buf ,  APP_Conf_R_Queue.Queue[APP_Conf_R_Queue.out].len);
		* len = APP_Conf_R_Queue.Queue[APP_Conf_R_Queue.out].len;
		
		APP_Conf_R_Queue.out ++;
		APP_Conf_R_Queue.out %= APP_Conf_R_Queue.size;
		APP_Conf_R_Queue.count --;		
	}

	
	return APP_Conf_R_Queue.count;
}


void APP_Conf_RevProcess(void)
{
	uint8_t * rbuf = 0;
	rbuf = 
	if(app_conf_out_R_queue)
}




void APP_Conf_Send(uint8_t *buf , uint16_t len)
{
	BSP_USART_WriteBytes_DMA(BSP_USART1 , buf , len);
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

