/**
  ******************************************************************************
  * File Name          : auto.h
  * Description        : This file provides code for how to auto control.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __auto_H
#define __auto_H
#ifdef __cplusplus
 extern "C" {
#endif
     
#include "config_para.h"   
#include "telemetry.h" 
#include "remote_signal.h"

void Auto_Control_Clear_Motion(void);
void Auto_Control_Time_Counter(SwitchTypeDef* sw, uint32_t tyDelay, uint32_t capTouDelay, uint32_t capQieDelay);
void Auto_Control_Capa_Clear_Motion(void);   
  
uint8_t Auto_Control(ACSampleTypeDef *sample, ConfigParaTypeDef *cfg, SwitchTypeDef* sw);
#ifdef __cplusplus
}
#endif
#endif 
/************************ZXDQ *****END OF FILE****/

