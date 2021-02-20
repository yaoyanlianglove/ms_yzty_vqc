/**
  ******************************************************************************
  * File Name          : switch.h
  * Description        : This file contains all functions about switch.
  ******************************************************************************
  * @attention
  
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _switch_H
#define _switch_H
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "motor.h"
#define  REMOTE_SIGNAL_GEAR1       HAL_GPIO_ReadPin(DIN1_GPIO_Port, DIN1_Pin)
#define  REMOTE_SIGNAL_GEAR2       HAL_GPIO_ReadPin(DIN2_GPIO_Port, DIN2_Pin)
#define  REMOTE_SIGNAL_GEAR3       HAL_GPIO_ReadPin(DIN3_GPIO_Port, DIN3_Pin)
#define  REMOTE_SIGNAL_GEAR4       HAL_GPIO_ReadPin(DIN4_GPIO_Port, DIN4_Pin)
#define  REMOTE_SIGNAL_GEAR5       HAL_GPIO_ReadPin(DIN5_GPIO_Port, DIN5_Pin)
#define  REMOTE_SIGNAL_GEAR6       HAL_GPIO_ReadPin(DIN6_GPIO_Port, DIN6_Pin)
#define  REMOTE_SIGNAL_GEAR7       HAL_GPIO_ReadPin(DIN7_GPIO_Port, DIN7_Pin)
#define  REMOTE_SIGNAL_GEAR8       HAL_GPIO_ReadPin(DIN8_GPIO_Port, DIN8_Pin)
#define  REMOTE_SIGNAL_GEARA       HAL_GPIO_ReadPin(DIN9_GPIO_Port, DIN9_Pin)
#define  REMOTE_SIGNAL_GEARB       HAL_GPIO_ReadPin(DIN10_GPIO_Port, DIN10_Pin)

#define  REMOTE_SIGNAL_QIE_MOTOR   HAL_GPIO_ReadPin(QIE_MOTOR_GPIO_Port, QIE_MOTOR_Pin)
#define  QIE_MOTOR_CTL_X           HAL_GPIO_WritePin(QIE_MOTOR_CTL_GPIO_Port, QIE_MOTOR_CTL_Pin, GPIO_PIN_SET)
#define  QIE_MOTOR_CTL_Q           HAL_GPIO_WritePin(QIE_MOTOR_CTL_GPIO_Port, QIE_MOTOR_CTL_Pin, GPIO_PIN_RESET)
#define  REMOTE_SIGNAL_SUB_DITH_TIME 10        //遥信去抖时间 
#define  IGBT_TIME_OUT   60   //ms,IGBT超时时间
#define  DCT_TIME_OUT    140  //ms，电磁铁超时时间


#define  DIANCHITIE_LOW      HAL_GPIO_WritePin(DOUT3_GPIO_Port, DOUT3_Pin, GPIO_PIN_RESET)
#define  DIANCHITIE_HIGH     HAL_GPIO_WritePin(DOUT3_GPIO_Port, DOUT3_Pin, GPIO_PIN_SET)
#define  IGBT_DIR_LOW        HAL_GPIO_WritePin(DOUT1_GPIO_Port, DOUT1_Pin, GPIO_PIN_RESET)
#define  IGBT_DIR_HIGH       HAL_GPIO_WritePin(DOUT1_GPIO_Port, DOUT1_Pin, GPIO_PIN_SET)
#define  IGBT_MOTION_LOW     HAL_GPIO_WritePin(DOUT2_GPIO_Port, DOUT2_Pin, GPIO_PIN_RESET)
#define  IGBT_MOTION_HIGH    HAL_GPIO_WritePin(DOUT2_GPIO_Port, DOUT2_Pin, GPIO_PIN_SET)

#define  REMOTE_SIGNAL_GEAR0        HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3)
#define  REMOTE_SIGNAL_DIANCHITIE   HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_12)


#define  REMOTE_SIGNAL_CAP1     HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_7)
#define  REMOTE_SIGNAL_CAP2     HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_6)

#define  CAP1_IGBT_DIR_TOU      HAL_GPIO_WritePin(DOUT7_GPIO_Port, DOUT7_Pin, GPIO_PIN_SET)
#define  CAP1_IGBT_DIR_QIE      HAL_GPIO_WritePin(DOUT7_GPIO_Port, DOUT7_Pin, GPIO_PIN_RESET)    

#define  CAP2_IGBT_DIR_TOU      HAL_GPIO_WritePin(DOUT5_GPIO_Port, DOUT5_Pin, GPIO_PIN_SET)
#define  CAP2_IGBT_DIR_QIE      HAL_GPIO_WritePin(DOUT5_GPIO_Port, DOUT5_Pin, GPIO_PIN_RESET)

#define  CAP1_IGBT_MOTION_LOW   HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_RESET)
#define  CAP1_IGBT_MOTION_HIGH  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_SET)

#define  CAP2_IGBT_MOTION_LOW   HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, GPIO_PIN_RESET)
#define  CAP2_IGBT_MOTION_HIGH  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, GPIO_PIN_SET)

#define CAP1TOU        1
#define CAP2TOU        2
#define CAP1TOUCAP2TOU 3

#define CAP1QIE        4
#define CAP2QIE        5
#define CAP1QIECAP2QIE 6

#define CAP1QIECAP2TOU 7
#define CAP1TOUCAP2QIE 8

#define  CAP_IGBT_TIME_OUT   60  //ms,IGBT超时时间






/**
  * @brief  Gear status structures definition
  */
typedef enum
{
    GEAR_OK                      = 0x00U,
    GEAR_ERROR                   = 0x01U
} GearStatusTypeDef;

/**
  * @brief  Gear status structures definition
  */
typedef enum
{
    CAP_OK                       = 0x00U,
    CAP1_ERROR                   = 0x01U,
    CAP2_ERROR                   = 0x02U,
    CAP1_AND_CAP2_ERROR          = 0x03U,
    CAP_CONTROL_ERROR            = 0x04U,
} CapStatusTypeDef; 
/**
  * @brief  Switch status structures definition
  */
typedef enum
{
    SWITCH_OK                    = 0x00U,
    SWITCH_GEAR_ERROR            = 0x01U,
    SWITCH_ERROR                 = 0x02U,
    SWITCH_TURN_FAIL             = 0x03U,
} SwitchStatusTypeDef; 

/**
  * @brief  Switch motion definition
  */
typedef enum
{
    RC_NONE                      = 0x00U,
    RC_UP_VOL                    = 0x01U,
    RC_DOWN_VOL                  = 0x02U,
    RC_CONTROL_CAP               = 0x03U,
} SwitchMotionTypeDef;
/**
  * @brief  Gear signal status structures definition
  */
typedef struct 
{             
    uint8_t  gear1;                    //档位：1
    uint8_t  gear2;                    //档位：2
    uint8_t  gear3;                    //档位：3
    uint8_t  gear4;                    //档位：4
    uint8_t  gear5;                    //档位：5  
    uint8_t  gear6;                    //档位：6
    uint8_t  gear7;                    //档位：7
    uint8_t  gear8;                    //档位：8
    uint8_t  gear9;                    //档位：9
    uint8_t  gear10;                   //档位：10
    uint8_t  gear11;                   //档位：11
    uint8_t  gear12;                   //档位：12
    uint8_t  gear13;                   //档位：13
    uint8_t  gear14;                   //档位：14
    uint8_t  gear15;                   //档位：15
    uint8_t  gear16;                   //档位：16
    uint8_t  gear17;                   //档位：17     
}GearSignalTypeDef;  
/**
  * @brief  Cap signal status structures definition
  */
typedef struct 
{             
    uint8_t  cap1;                    //电容器1状态 0 未投 1 已投 
    uint8_t  cap2;                    //电容器2状态 0 未投 1 已投     
}CapSignalTypeDef;
/**
  * @brief  Switch structures definition
  */
typedef struct 
{
    uint8_t  currentGear;         //当前档位
    uint8_t  memoryGear;          //记忆档位
    uint8_t  expectGear;          //预期档位
    uint8_t  beforeMotionGear;    //动作前档位
    uint8_t  totalGear;           //总档位
    uint8_t  beforeMotionCapStat; //动作前电容器状态 
    uint8_t  currentCapStat;      //当前电容器状态
    uint8_t  destCapStat;         //要达到的电容器状态
    uint8_t  autoMotion;          //0 没动作， 1 升压 2 降压  3 投切电容
    uint8_t  remoteMotion;        //0 没动作， 1 升压 2 降压  3 投切电容 
    uint8_t  lcdMotion;           //0 没动作， 1 升压 2 降压  3 投切电容
    uint8_t  handMotion;          //0 没动作， 1 升压 2 降压  3 投切电容
    uint8_t  motion;              //0 没动作， 1 升压 2 降压  3 投切电容
    uint8_t  lastMotion;          //上一次动作
    uint8_t  gearFault;           //开关状态 0 正常，1 故障
    uint8_t  resetFlag;           //重启标志
    uint8_t  cap1MotionFlag;      //电容器1动作记录标志
    uint8_t  cap2MotionFlag;      //电容器2动作记录标志
}SwitchTypeDef;


void     Gear_Signal_Time_Counter(GearSignalTypeDef *gearSignal);
GearStatusTypeDef    Read_Gear(SwitchTypeDef* sw, GearSignalTypeDef* gearSignal);
GearStatusTypeDef    Gear_Check(SwitchTypeDef *sw, GearSignalTypeDef *gearSignal);
SwitchStatusTypeDef  Switch_Calibration(SwitchTypeDef* sw, MotorTypeDef* motor);
SwitchStatusTypeDef  Switch_Init(SwitchTypeDef* sw, uint8_t toatlGear);
SwitchStatusTypeDef  Switch_Control(SwitchTypeDef* sw);
SwitchStatusTypeDef  Go_To_Middle(uint8_t dir, MotorTypeDef* motor, SwitchTypeDef* sw, uint8_t motorType);

void     Cap_Signal_Time_Counter(CapSignalTypeDef *capSignal);
CapStatusTypeDef    Cap_Check(SwitchTypeDef *sw, CapSignalTypeDef *capSignal);
CapStatusTypeDef    Cap_Control(SwitchTypeDef *sw);
#ifdef __cplusplus
}
#endif

#endif

/************************ZXDQ *****END OF FILE****/
  
