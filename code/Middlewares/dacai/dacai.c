/**
 **************************************************************************************************
 * @file        dacai.c
 * @author
 * @dacai
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
#include "dacai.h"
#include "dacai_port.h"
#include "clog.h"
#include "dacai_task.h"
/**
 * @addtogroup    dacai_Modules 
 * @{  
 */

/**
 * @defgroup      dacai_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       dacai_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_Constants_Defines 
 * @brief         
 * @{  
 */
#define DACAI_R_BUF_LEN			100
#define DACAI_T_QUEUE_LEN   	50
/**
 * @}
 */

/**
 * @defgroup       dacai_Private_Types
 * @brief         
 * @{  
 */
 
#pragma pack(1)
typedef struct
{
	uint8_t buf[DACAI_R_BUF_LEN];
	uint8_t in;
	uint8_t out ;
	uint8_t count;
	uint8_t size;
}dacai_revbuf_t;

typedef struct
{
	uint8_t buf[DACAI_T_QUEUE_LEN];
	uint8_t len;
}dacai_txbuf_t;
typedef struct
{
	dacai_txbuf_t tqueue[3];
	uint8_t in ;
	uint8_t out;
	uint8_t count;
	uint8_t size;
}dacai_txqueue_t;

#pragma pack()

/**
 * @}
 */

/**
 * @defgroup      dacai_Private_Variables 
 * @brief         
 * @{  
 */
dacai_revbuf_t dacai_revbuf = 
{
	.in = 0,
	.out = 0,
	.count = 0,
	.size = sizeof(dacai_revbuf.buf) / sizeof(dacai_revbuf.buf[0]),
};

dacai_txqueue_t dacai_txqueue = 
{
	.in = 0,
	.out = 0,
	.count = 0,
	.size = sizeof(dacai_txqueue.tqueue) / sizeof(dacai_txqueue.tqueue[0]),
};


static uint8_t dacai_sendspace[DACAI_T_QUEUE_LEN];
static uint8_t dacai_revspace[DACAI_R_BUF_LEN];
/**
 * @}
 */

/**
 * @defgroup      dacai_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void dacai_tryget_fullbuf(uint8_t buf);
static void dacai_rev_anaglysis(uint8_t *buf , uint8_t len);

/**
 * @}
 */

/**
 * @defgroup      dacai_Functions 
 * @brief         
 * @{  
 */
void Dacai_Init(void)
{
	Dacai_Port_Init();
}

void Dacai_RevPorcess(void)
{
	uint8_t buf_tmep;
	if(Dacai_Ring_out_Byte(&buf_tmep) >=0)
	{

		dacai_tryget_fullbuf(buf_tmep);
		//DEBUG("buf_tmep:0x%X\r\n" , buf_tmep);
		Dacai_Task_Event_Start(DACAI_TASK_REV_EVENT , EVENT_FROM_TASK);
	}
	else
	{
		DEBUG("Dacai_Ring is NULL\r\n");
	}
}

static void dacai_tryget_fullbuf(uint8_t buf)
{
	static uint8_t cur_ptr = 0 ;
	static uint8_t *foot_ptr = 0 ;
	
	dacai_revspace[cur_ptr] = buf ;
	cur_ptr ++;
	for(uint8_t i = 0; i < cur_ptr ; i ++)
	{
		if(dacai_revspace[i] == 0xee)
		{
			memcpy(dacai_revspace , &dacai_revspace[i] , cur_ptr -i);
			cur_ptr -= i;
			break;
		}
	}
	
	if(cur_ptr > 4)
	{
		foot_ptr = &dacai_revspace[cur_ptr - 4] ;
		//DEBUG("%X %X %X %X\r\n" ,foot_ptr[0] ,foot_ptr[1],foot_ptr[2],foot_ptr[3] );
		if(foot_ptr[0]== 0xff && foot_ptr[1]== 0xfc && foot_ptr[2]== 0xff && foot_ptr[3]== 0xff )
		{
			dacai_rev_anaglysis(dacai_revspace , cur_ptr - 1);
			cur_ptr = 0;
		}
		else
		{
			
		}
	}		
	
}
static void dacai_rev_anaglysis(uint8_t *buf , uint8_t len)
{
	uint8_t buf_temp[100];
	memcpy(buf_temp , buf , len);
	for(uint8_t i = 0 ; i < len; i ++)
	{
		DEBUG("0x%X  ", buf_temp[i]);
	}
}

void Dacai_Rev_Anaglysis(uint8_t *buf , uint16_t len)
{
	
}

// -------Send ----------------

void Dacai_Send_Process(void)
{
	uint16_t len = 0;
	if(Dacai_Queue_out_Bytes(dacai_sendspace , &len) >= 0)
	{
		Dacai_Port_Send(dacai_sendspace , len);
		Dacai_Task_Event_Start(DACAI_TASK_SEND_EVENT , EVENT_FROM_TASK);
	}
}

// ----------------------------


// ---------- Ring / Queue Func-----------------
void Dacai_Ring_in_Byte(uint8_t buf)
{
	dacai_revbuf.buf[dacai_revbuf.in ] = buf;
	dacai_revbuf.in ++ ; 
	dacai_revbuf.in %= dacai_revbuf.size;
	dacai_revbuf.count ++;
	
}

int8_t Dacai_Ring_out_Byte(uint8_t * buf)
{
	if(dacai_revbuf.count > 0)
	{
		*buf = dacai_revbuf.buf[dacai_revbuf.out];
		dacai_revbuf.out ++;
		dacai_revbuf.out %= dacai_revbuf.size;
		dacai_revbuf.count -- ;
	}
	else
	{
		return -1;
	}
	return dacai_revbuf.count;
}
// --
void Dacai_Queue_in_Bytes(uint8_t * buf , uint16_t len)
{
	if(len < DACAI_T_QUEUE_LEN)
	{
		memcpy(dacai_txqueue.tqueue[dacai_txqueue.in].buf , buf, len);
		dacai_txqueue.tqueue[dacai_txqueue.in].len = len;
		dacai_txqueue.in ++;
		dacai_txqueue.in %= dacai_txqueue.size;
		dacai_txqueue.count ++;
		
		Dacai_Task_Event_Start(DACAI_TASK_SEND_EVENT , EVENT_FROM_TASK);
	}
	else
	{
		DEBUG("Dacai Tx too long\r\n");
	}
}

int8_t Dacai_Queue_out_Bytes(uint8_t * buf, uint16_t * len)
{
	if(dacai_txqueue.count > 0 )
	{
		memcpy(buf ,dacai_txqueue.tqueue[dacai_txqueue.out].buf ,  dacai_txqueue.tqueue[dacai_txqueue.out].len);
		*len = dacai_txqueue.tqueue[dacai_txqueue.out].len;
		dacai_txqueue.out ++;
		dacai_txqueue.out %= dacai_txqueue.size;
		dacai_txqueue.count --;
	}
	else
	{
		return -1;
	}
	return dacai_txqueue.count;
}



// --------------------------------------

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

