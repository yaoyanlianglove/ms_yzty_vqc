/**
  ******************************************************************************
  * File Name          : modbus_interface.h
  * Description        : This file provides the function about interface of modbus.
  ******************************************************************************
  * @attention
  
  *
  ******************************************************************************
  */
#include "modbus_interface.h"
#include "auto.h"
extern ModbusTypeDef modbus;
extern int16_t telemetryReg[32];              //遥测输入寄存器
/*****************************************************************************
 Function    : Modbus_Interface_Init
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Modbus_Interface_Init(RemoteSignalTypeDef *remoteSignal, ConfigParaTypeDef *configPara,
                      ClockTypeDef *clock)
{
    uint8_t i;
    modbus.coilReg[0 ] = &remoteSignal->autoMode;
    modbus.coilReg[1 ] = &remoteSignal->remoteMode;

    
    modbus.discreteInputReg[0 ] = &remoteSignal->autoMode;
    modbus.discreteInputReg[1 ] = &remoteSignal->remoteMode;
    modbus.discreteInputReg[2 ] = &remoteSignal->gearSignal.gear1;
    modbus.discreteInputReg[3 ] = &remoteSignal->gearSignal.gear2;
    modbus.discreteInputReg[4 ] = &remoteSignal->gearSignal.gear3;
    modbus.discreteInputReg[5 ] = &remoteSignal->gearSignal.gear4;
    modbus.discreteInputReg[6 ] = &remoteSignal->gearSignal.gear5;
    modbus.discreteInputReg[7 ] = &remoteSignal->gearSignal.gear6;
    modbus.discreteInputReg[8 ] = &remoteSignal->gearSignal.gear7;
    modbus.discreteInputReg[9 ] = &remoteSignal->gearSignal.gear8;
    modbus.discreteInputReg[10] = &remoteSignal->gearSignal.gear9;
    modbus.discreteInputReg[11] = &remoteSignal->gearSignal.gear10;
    modbus.discreteInputReg[12] = &remoteSignal->gearSignal.gear11;
    modbus.discreteInputReg[13] = &remoteSignal->gearSignal.gear12;
    modbus.discreteInputReg[14] = &remoteSignal->gearSignal.gear13;
    modbus.discreteInputReg[15] = &remoteSignal->gearSignal.gear14;
    modbus.discreteInputReg[16] = &remoteSignal->gearSignal.gear15;
    modbus.discreteInputReg[17] = &remoteSignal->gearSignal.gear16;
    modbus.discreteInputReg[18] = &remoteSignal->gearSignal.gear17;
    modbus.discreteInputReg[19] = &remoteSignal->initFail;
    modbus.discreteInputReg[20] = &remoteSignal->lockSwitch;
    modbus.discreteInputReg[21] = &remoteSignal->oilPosAlarm;
    modbus.discreteInputReg[22] = &remoteSignal->oilTemAlarm;
    modbus.discreteInputReg[23] = &remoteSignal->overCurrentAlarm;
    modbus.discreteInputReg[24] = &remoteSignal->lowVoltageAlarm;
    modbus.discreteInputReg[25] = &remoteSignal->highVoltageAlarm;
    modbus.discreteInputReg[26] = &remoteSignal->gearFault;
    modbus.discreteInputReg[27] = &remoteSignal->switchFault;
    modbus.discreteInputReg[28] = &remoteSignal->cap1Fault;
    modbus.discreteInputReg[29] = &remoteSignal->cap2Fault;
    modbus.discreteInputReg[30] = &remoteSignal->controlCapFail;
    modbus.discreteInputReg[31] = &remoteSignal->turnGearFail;
    modbus.discreteInputReg[32] = &remoteSignal->capSignal.cap1;
    modbus.discreteInputReg[33] = &remoteSignal->capSignal.cap2;


    for(i = 0; i < MODBUS_INPUT_REG_LIMIT; i++)
        modbus.inputReg[i ] = &telemetryReg[i];


    modbus.holdingReg[0 ] = &configPara->thDownVoltage;
    modbus.holdingReg[1 ] = &configPara->thUpVoltage;
    modbus.holdingReg[2 ] = &configPara->tySpace;
    modbus.holdingReg[3 ] = &configPara->tyDelay;
    modbus.holdingReg[4 ] = &configPara->ctRatio;
    modbus.holdingReg[5 ] = &configPara->lockOverCurrent;
    modbus.holdingReg[6 ] = &configPara->lockVoltageUpLimit;
    modbus.holdingReg[7 ] = &configPara->lockVoltageLowLimit;
    modbus.holdingReg[8 ] = &configPara->lockHighVoltage;
    modbus.holdingReg[9 ] = &configPara->lockLowVoltage;
    modbus.holdingReg[10] = &configPara->thAlarmTemp;
    modbus.holdingReg[11] = &configPara->tranCapacity;
    modbus.holdingReg[12] = &configPara->code;
    modbus.holdingReg[13] = &configPara->pfUpLimit;
    modbus.holdingReg[14] = &configPara->pfDownLimit;
    modbus.holdingReg[15] = &configPara->thQNeed;
    modbus.holdingReg[16] = &configPara->tcDelay;
    modbus.holdingReg[17] = &configPara->qcDelay;
    modbus.holdingReg[18] = &configPara->deviceInfo.tapTotalNum;
    modbus.holdingReg[19] = &configPara->deviceInfo.tapWideHigh;
    modbus.holdingReg[20] = &configPara->deviceInfo.tapWideLow;
    modbus.holdingReg[21] = &configPara->deviceInfo.switchType;
    modbus.holdingReg[22] = &configPara->deviceInfo.hardVersion;
    modbus.holdingReg[23] = &configPara->deviceInfo.softVersion;
    modbus.holdingReg[24] = &clock->y;
    modbus.holdingReg[25] = &clock->m;
    modbus.holdingReg[26] = &clock->d;
    modbus.holdingReg[27] = &clock->h;
    modbus.holdingReg[28] = &clock->min;
    modbus.holdingReg[29] = &clock->s;

    Modbus_Start_Rec();
}
/*****************************************************************************
 Function    : Modbus_Interface_Remote_Control_Process
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
uint8_t Modbus_Interface_Remote_Control_Process(RemoteSignalTypeDef *remoteSignal, 
                                                ConfigParaTypeDef   *configPara,
                                                SwitchTypeDef       *sw,
                                                uint8_t regAddr, uint8_t *data, uint8_t regNum)
{
    if(regAddr == 0)
    {
        if(regNum != 2)
            return 2;
        if((data[0 ] ^ data[1 ]) == 1)
        {
            if(data[0 ] == 1)
            {
                if(remoteSignal->autoMode == 0)
                {
                    Auto_Control_Clear_Motion();         //手动切自动，自动参数清零
                    remoteSignal->autoMode   = data[0 ];
                    remoteSignal->remoteMode = data[1 ];
                }
            }
            else if(data[1 ] == 1)
            {
                if(remoteSignal->remoteMode == 0)
                {
                    Auto_Control_Clear_Motion();         //自动切手动，自动参数清零
                    remoteSignal->autoMode   = data[0 ];
                    remoteSignal->remoteMode = data[1 ];
                }
            }
        }
        else
            return 3;
    }
    else if(regAddr == 2)
    {
        if(regNum != 2)
            return 2;
        if(remoteSignal->remoteMode == 0)
            return 3;
        if(remoteSignal->lockSwitch == 1)
            return 4;
        if((data[0 ] ^ data[1 ]) == 1)
        {
            if(data[0 ] == 1)
            {
                if(sw->currentGear < configPara->deviceInfo.tapTotalNum && sw->currentGear > 0)                
                    sw->remoteMotion = 1;
                else
                    return 3;                    
            }
            else if(data[1 ] == 1)
            {
                if(sw->currentGear < configPara->deviceInfo.tapTotalNum + 1 && sw->currentGear > 1)        
                    sw->remoteMotion = 2;
                else
                    return 3;
            }
        }
        else
            return 3;
    }
    else if(regAddr == 4)
    {
        if(regNum != 2)
            return 2;
        if(remoteSignal->remoteMode == 0)
            return 3;
        else if(remoteSignal->lockSwitch == 1)
            return 4;
        sw->destCapStat = data[0] | (data[1] << 1);
        sw->remoteMotion      = 3;
    }
    else if(regAddr == 6)
    {
        if(regNum != 1)
            return 2;
        if(remoteSignal->remoteMode == 0)
            return 3;
        if(data[0] == 1)
            sw->resetFlag = 1;  //重启
        else
            return 3;
    }
    else 
        return 2;

    return 0;
}

/*****************************************************************************
 Function    : Modbus_Interface_Set_Config_Process
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
uint8_t Modbus_Interface_Set_Config_Process(RemoteSignalTypeDef *remoteSignal, 
                                            ConfigParaTypeDef   *configPara,
                                            ClockTypeDef        *clock,
                                            SaveFlagTypeDef     *saveFlag,
                                            uint8_t regAddr, uint16_t *data, uint8_t regNum)
{
    uint8_t i;
    uint8_t res = 0;
    for(i = regAddr; i < regAddr+regNum; i++)
    {
        switch(i)
        {
            case 0:
                if(data[i] < 10000 || data[i] > 12000)
                    res = 3;
            break;
            case 1:
                if(data[i] < 8000 || data[i] > 10000)
                    res = 3;
            break;
            case 2:
                if(data[i] < 5 || data[i] > 3600)
                    res = 3;
            break;
            case 3:
                if(data[i] < 5 || data[i] > 1200)
                    res = 3;
            break;
            case 4:
                if(data[i] == 300 || data[i] == 600 || data[i] == 1000)
                    ;
                else
                    res = 3;
            break;
            case 5:;
            break;
            case 6:;
            break;
            case 7:;
            break;
            case 8:
                if(data[i] < 12000 || data[i] > 30000)
                    res = 3;
            break;
            case 9:
                if(data[i] < 1000 || data[i] > 8000)
                    res = 3;
            break;
            case 10:;
            break;
            case 11:;
            break;
            case 12:;
            break;
            case 13:
                if(data[i] > 100)
                    res = 3;
            break;
            case 14:
                if(data[i] > 100)
                    res = 3;
            break;
            case 15:;
            break;
            case 16:
                if(data[i] < 5 || data[i] > 1200)
                    res = 3;
            break;
            case 17:
                if(data[i] < 5 || data[i] > 1200)
                    res = 3;
            break;

            case 18:
                res = 3;
            break;
            case 19:
                res = 3;
            break;
            case 20:
                res = 3;
            break;
            case 21:
                res = 3;
            break;
            case 22:
                res = 3;
            break;
            case 23:
                res = 3;
            break;
            case 24:
                if(data[i] < 19 || data[i] > 100)
                    res = 3;
            break;
            case 25:
                if(data[i] == 0 || data[i] > 12)
                    res = 3;
            break;
            case 26:
                if(data[i] == 0 || data[i] > 31)
                    res = 3;
            break;

            case 27:
                if(data[i] > 23)
                    res = 3;
            break;
            case 28:
                if(data[i] > 59)
                    res = 3;
            break;
            case 29:
                if(data[i] > 59)
                    res = 3;
            break;
            
            default:;
            break;
        }
    }
    if(res == 0)
    {
        for(i = regAddr; i < regAddr+regNum; i++)
        {
            switch(i)
            {
                case 0:
                    configPara->thDownVoltage = data[i];
                break;
                case 1:
                    configPara->thUpVoltage = data[i];
                break;
                case 2:
                    configPara->tySpace = data[i];
                break;
                case 3:
                    configPara->tyDelay = data[i];
                break;
                case 4:
                    configPara->ctRatio = data[i];
                break;
                case 5:
                    configPara->lockOverCurrent = data[i];
                break;
                case 6:
                    configPara->lockVoltageUpLimit = data[i];
                break;
                case 7:
                    configPara->lockVoltageLowLimit = data[i];
                break;
                case 8:
                    configPara->lockHighVoltage = data[i];
                break;
                case 9:
                    configPara->lockLowVoltage = data[i];
                break;
                case 10:
                    configPara->thAlarmTemp = data[i];
                break;
                case 11:
                    configPara->tranCapacity = data[i];
                break;
                case 12:
                    configPara->code = data[i];
                break;

                case 13:
                    configPara->pfUpLimit = data[i];
                break;
                case 14:
                    configPara->pfDownLimit = data[i];
                break;
                case 15:
                    configPara->thQNeed = data[i];
                break;
                case 16:
                    configPara->tcDelay = data[i];
                break;
                case 17:
                    configPara->qcDelay = data[i];
                break;
                case 18:
                    ;
                break;
                case 19:
                    ;
                break;
                case 20:
                    
                break;
                case 21:
                    ;
                break;
                case 22:
                    ;
                break;
                case 23:
                    
                break;
                case 24:
                    clock->y = data[i];
                break;
                case 25:
                    clock->m = data[i];
                break;
                case 26:
                    clock->d = data[i];
                break;
                case 27:
                    clock->h = data[i];
                break;
                case 28:
                    clock->min = data[i];
                break;
                case 29:
                    clock->s = data[i];
                break;
                default:;
                break;
            }
        }
        if(regAddr > 23)
            Clock_Set_Date_And_Time(clock);
        else
        {
            if(Save_Config_Para(configPara) != STORAGE_OK)
            {
                remoteSignal->storeErr = 1;
                return 4;  //设备故障
            }
        }
    }
    return res;
}
/************************ZXDQ *****END OF FILE****/
