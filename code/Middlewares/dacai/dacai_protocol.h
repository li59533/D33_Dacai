/**
 **************************************************************************************************
 * @file        dacai_protocol.h
 * @author
 * @dacai_protocol
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _DACAI_PROTOCOL_H_
#define _DACAI_PROTOCOL_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    dacai_protocol_Modules 
 * @{  
 */

/**
 * @defgroup      dacai_protocol_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_protocol_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dacai_protocol_Exported_Types 
 * @{  
 */
typedef struct
{
	uint16_t cur_s;
	uint8_t handshake_flag ; 
}dacai_gui_info_t;


/**
 * @}
 */

/**
 * @defgroup      dacai_protocol_Exported_Variables 
 * @{  
 */
extern dacai_gui_info_t dacai_gui_info;
/**
 * @}
 */

/**
 * @defgroup      dacai_protocol_Exported_Functions 
 * @{  
 */
void Dacai_Protocol_RevAnalgsis(uint8_t * cmd , uint16_t len);
// -------------Callback Register --------------------
void Dacai_Button_CallbackRegister(void (*callback)(uint16_t screen_id , uint16_t control_id ,uint8_t status));
void Dacai_HandShake_CallbackRegister(void (*callback)(void));
void Dacai_Rest_CallbackRegister(void (*callback)(void));
void Dacai_GetRTC_CallbackRegister(void (*callback)(uint8_t *buf ,uint16_t len));
// ---------------------------------------------------
void Dacai_SetHandShake(void);
void Dacai_SetRest(void);
void Dacai_Disable_Updata(void);
void Dacai_Enable_Updata(void);
void Dacai_CleanScreen(void);
void Dacai_DisFull_Image(uint16_t image_id,uint8_t masken);
void Dacai_SetPowerSaving(uint8_t enable, uint8_t bl_off_level, uint8_t bl_on_level, uint8_t bl_on_time);
void Dacai_SetBuzzer(uint8_t time);
void Dacai_GetScreen(void);
void Dacai_SetScreen(uint16_t screen_id);
void Dacai_SetControlVisiable(uint16_t screen_id , uint16_t control_id,uint8_t visible);
void Dacai_SetButtonValue(uint16_t screen_id,uint16_t control_id,uint8_t state);
void Dacai_SetTextValue(uint16_t screen_id,uint16_t control_id,uint8_t *str , uint16_t len);
void Dacai_SetMeterValue(uint16_t screen_id,uint16_t control_id,uint32_t value);
void Dacai_SetSliderValue(uint16_t screen_id,uint16_t control_id,uint32_t value);
void Dacai_SetTimer(uint16_t screen_id,uint16_t control_id,uint32_t timeout);
void Dacai_StartTimer(uint16_t screen_id,uint16_t control_id);
void Dacai_StopTimer(uint16_t screen_id,uint16_t control_id);
void Dacai_PauseTimer(uint16_t screen_id,uint16_t control_id);
void Dacai_SetProgressBar(uint16_t screen_id,uint16_t control_id,uint32_t value);
void Dacai_GetRTC(void);
void Dacai_Change_Language(uint8_t language_num);
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
