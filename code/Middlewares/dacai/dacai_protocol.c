/**
 **************************************************************************************************
 * @file        dacai_protocol.c
 * @author
 * @dacai_protocol
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
#include "dacai_protocol.h"
#include "dacai.h"
#include "clog.h"
#include "cmsis_armcc.h"

/**
 * @addtogroup    dacai_protocol_Modules 
 * @{  
 */

/**
 * @defgroup      dacai_protocol_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       dacai_protocol_Macros_Defines 
 * @brief         
 * @{  
 */
#define DACAI_HANDSHAKE			0X55
#define DACAI_RSET				0x07
#define DACAI_B1				0XB1
#define	DACAI_GETCURSCREEN		0X01
#define DACAI_READ_CONTROL		0X11

#define DACAI_CONTROL_TYPE_BUTTON	0x10
/**
 * @}
 */

/**
 * @defgroup      dacai_protocol_Constants_Defines 
 * @brief         
 * @{  
 */
const static uint8_t dacai_head[] = {0xEE};
const static uint8_t dacai_foot[] = {0xFF , 0xFC , 0xFF , 0xFF};

/**
 * @}
 */

/**
 * @defgroup       dacai_protocol_Private_Types
 * @brief         
 * @{  
 */
#pragma pack(1)
typedef struct
{
	uint16_t screen_id;
	uint16_t control_id;
	uint8_t control_type;
	uint8_t sub_type;
	uint8_t status;
}dacai_readcontrol_value_t;
#pragma pack()



#pragma pack(1) 
typedef struct
{
	uint8_t head;
	uint8_t cmd;
	uint8_t msg;
	uint16_t screen_id;
	uint16_t control_id;
	uint8_t control_type;
	uint8_t *payload;
	uint8_t foot[4];
}Dacai_Protocol_t;

typedef struct
{
    uint8_t current_screen_id;
    uint8_t current_equip_id;
    uint8_t finger_name_buf[10];
    uint8_t finger_id_buf[10];
    uint16_t record_count;
}CBvalue_t;



#pragma pack()
/**
 * @}
 */

/**
 * @defgroup      dacai_protocol_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_protocol_Public_Variables 
 * @brief         
 * @{  
 */
dacai_gui_info_t dacai_gui_info = 
{
	.handshake_flag = 0,
	.cur_s = 0,
};

/**
 * @}
 */

/**
 * @defgroup      dacai_protocol_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static uint16_t dacai_Tbuf_Add(uint8_t * space , uint8_t *addbuf , uint16_t len);
static void dacai_b1_analysis(uint8_t *cmd2 ,uint16_t len);
static void dacai_button_process(uint16_t screen_id , uint16_t control_id , uint8_t status);


static void (*Dacai_HandShake_Callback)(void); 
static void (*Dacai_Button_Callback)(uint16_t screen_id , uint16_t control_id ,uint8_t);
static void (*Dacai_Rest_Callback)(void); 

/**
 * @}
 */

/**
 * @defgroup      dacai_protocol_Functions 
 * @brief         
 * @{  
 */


void Dacai_Protocol_RevAnalgsis(uint8_t * cmd , uint16_t len)
{
	if(len == 0)
	{
		return ;
	}
	
	switch(*cmd)
	{
		case  DACAI_HANDSHAKE: 
			{
				DEBUG("Dacai HandShake OK\r\n");
				dacai_gui_info.handshake_flag = 1;
				
				if(Dacai_HandShake_Callback != NULL)
				{
					Dacai_HandShake_Callback();
				}
			}break;
		case  DACAI_RSET: 
			{
				DEBUG("Dacai Rset\r\n");

				if(Dacai_Rest_Callback != NULL)
				{
					Dacai_Rest_Callback();
				}
			}break;			
		case DACAI_B1:
			{
				//DEBUG("Dacai DACAI_B1 OK\r\n");
				dacai_b1_analysis(cmd + 1 , len -1);
			}break;
		default:break;
	}
	
}







static void dacai_b1_analysis(uint8_t *cmd2 ,uint16_t len)
{
	switch(*cmd2)
	{
		case DACAI_GETCURSCREEN:
			{
				dacai_gui_info.cur_s = *(cmd2 + 1) * 256 + *(cmd2 + 2);
				DEBUG("Cur Sreen:%d\r\n" , dacai_gui_info.cur_s);
			}break;
		case DACAI_READ_CONTROL:
			{
				dacai_readcontrol_value_t * dacai_readcontrol_value = (dacai_readcontrol_value_t *)(cmd2 + 1);
				
				switch(dacai_readcontrol_value->control_type)
				{
					case DACAI_CONTROL_TYPE_BUTTON:
					{
						
						dacai_button_process(dacai_readcontrol_value->screen_id , \
												dacai_readcontrol_value->control_id , \
												dacai_readcontrol_value->status);
						
					
					}break;
					default:break;
				}		
			}break;
		default:break;
	}
}

static void dacai_button_process(uint16_t screen_id , uint16_t control_id , uint8_t status)
{
	//DEBUG("screen_id:%d  control_id:%d  status:%d\r\n " , __REV16(screen_id) ,__REV16(control_id) , status );
	
	if(Dacai_Button_Callback != NULL)
	{
		Dacai_Button_Callback(__REV16(screen_id) , __REV16(control_id) ,status);
	}
}


// ---------- Callback func register -------

void Dacai_Button_CallbackRegister(void (*callback)(uint16_t screen_id , uint16_t control_id ,uint8_t status))
{
	Dacai_Button_Callback = callback;
}
void Dacai_HandShake_CallbackRegister(void (*callback)(void))
{
	Dacai_HandShake_Callback = callback;
}

void Dacai_Rest_CallbackRegister(void (*callback)(void))
{
	Dacai_Rest_Callback = callback;
}


// ---------- Some Driver -------------------
//Dacai_Queue_in_Bytes(uint8_t *buf , uint16_t len);
static uint16_t dacai_Tbuf_Add(uint8_t * space , uint8_t *addbuf , uint16_t len)
{
	memcpy(space , addbuf , len);
	return len;
}

// ---- 
void Dacai_SetHandShake(void)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd = 0x04;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}

void Dacai_SetRest(void)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd[] = {0x07 ,0x35 ,0x5A ,0x53 ,0xA5};
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)cmd , sizeof(cmd));
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}
void Dacai_Disable_Updata(void)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd[] = {0xb3 ,0x00 };
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)cmd ,  sizeof(cmd));
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);	
}

void Dacai_Enable_Updata(void)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd[] = {0xb3 ,0x01 };
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)cmd ,  sizeof(cmd));
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);	
}

// ----
void Dacai_CleanScreen(void)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd = 0x01;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}
// ----
void Dacai_DisFull_Image(uint16_t image_id,uint8_t masken)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd = 0x31;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd , 1);

	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&image_id , 2);	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&masken , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}


// ----
void Dacai_SetPowerSaving(uint8_t enable, uint8_t bl_off_level, uint8_t bl_on_level, uint8_t bl_on_time)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd = 0x77;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd , 1);

	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&enable , 1);	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&bl_on_level , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&bl_off_level , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&bl_on_time , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}
// ----
void Dacai_SetBuzzer(uint8_t time)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd = 0x61;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&time , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}

// ----
void Dacai_GetScreen(void)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd = 0xB1;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd , 1);
	uint8_t cmd2 = 0x01;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd2 , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}
// ----
void Dacai_SetScreen(uint16_t screen_id)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd = 0xB1;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd , 1);
	uint8_t cmd2 = 0x00;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd2 , 1);
	uint16_t temp = __REV16(screen_id);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&temp , 2);	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}
// ----
void Dacai_SetControlVisiable(uint16_t screen_id , uint16_t control_id,uint8_t visible)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd = 0xB1;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd , 1);
	uint8_t cmd2 = 0x03;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd2 , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&screen_id , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&control_id , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&visible , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}
// ----
void Dacai_SetButtonValue(uint16_t screen_id,uint16_t control_id,uint8_t state)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd = 0xB1;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd , 1);
	uint8_t cmd2 = 0x10;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd2 , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&screen_id , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&control_id , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&state , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}
// ----
void Dacai_SetTextValue(uint16_t screen_id,uint16_t control_id,uint8_t *str , uint16_t len)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	uint16_t screen_id_temp = __REV16(screen_id);
	uint16_t control_id_temp = __REV16(control_id);
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd = 0xB1;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd , 1);
	uint8_t cmd2 = 0x10;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd2 , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&screen_id_temp , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&control_id_temp , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)str , len);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}

// ----
void Dacai_SetMeterValue(uint16_t screen_id,uint16_t control_id,uint32_t value)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd = 0xB1;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd , 1);
	uint8_t cmd2 = 0x10;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd2 , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&screen_id , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&control_id , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&value , 4);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}
// ----
void Dacai_SetSliderValue(uint16_t screen_id,uint16_t control_id,uint32_t value)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd = 0xB1;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd , 1);
	uint8_t cmd2 = 0x10;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd2 , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&screen_id , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&control_id , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&value , 4);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}
// ----
void Dacai_SetTimer(uint16_t screen_id,uint16_t control_id,uint32_t timeout)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd = 0xB1;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd , 1);
	uint8_t cmd2 = 0x40;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd2 , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&screen_id , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&control_id , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&timeout , 4);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}
// ----
void Dacai_StartTimer(uint16_t screen_id,uint16_t control_id)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd = 0xB1;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd , 1);
	uint8_t cmd2 = 0x41;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd2 , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&screen_id , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&control_id , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}
// ----
void Dacai_StopTimer(uint16_t screen_id,uint16_t control_id)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd = 0xB1;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd , 1);
	uint8_t cmd2 = 0x42;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd2 , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&screen_id , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&control_id , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}
// ----
void Dacai_PauseTimer(uint16_t screen_id,uint16_t control_id)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd = 0xB1;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd , 1);
	uint8_t cmd2 = 0x42;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd2 , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&screen_id , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&control_id , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}

// ----
void Dacai_SetProgressBar(uint16_t screen_id,uint16_t control_id,uint32_t value)
{
	uint8_t space_ptr = 0;
	uint8_t tempbuf[50];
	uint16_t screen_id_temp = __REV16(screen_id);
	uint16_t control_id_temp = __REV16(control_id);
	uint32_t value_temp = __REV(value);
	
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_head , 1);
	uint8_t cmd = 0xB1;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd , 1);
	uint8_t cmd2 = 0x10;
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&cmd2 , 1);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&screen_id_temp , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&control_id_temp , 2);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)&value_temp , 4);
	space_ptr += dacai_Tbuf_Add( tempbuf + space_ptr, (uint8_t *)dacai_foot , 4);
	Dacai_Queue_in_Bytes( tempbuf , space_ptr);
}
// ----




/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

