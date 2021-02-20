/**
  ******************************************************************************
  * File Name          : auto.c
  * Description        : This file provides code for how to auto control.
  ******************************************************************************
  * @attention
  * 
  *
  ******************************************************************************
  */
#include "auto.h"
#include <math.h>
#include <stdlib.h>


volatile  uint32_t autoUpVoltageConfigCount     = 0;
volatile  uint8_t  areaNum = 0;
volatile  uint8_t  lastAreaNum = 0;
volatile  uint32_t areaCount = 0;
volatile  uint8_t  areaFlagOK = 0;
volatile  uint8_t  autoControlMotion            = 0;  //0 无，1 升压，2 降压 3 投切电容

volatile  uint8_t  autoMotionDest               = 0;  //自动控制的瞬时目标值0 无，1 升压，2 降压 3 投切电容


/*****************************************************************************
 Function    : Auto_Area_Judge
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
uint8_t Auto_Area_Judge(float uAvg, uint16_t pf, ConfigParaTypeDef *cfg)
{
    if(uAvg >= cfg->thDownVoltage)
    {
        if(pf >= cfg->pfUpLimit)
            return 1;
        else if(pf > cfg->pfDownLimit && pf < cfg->pfUpLimit)
            return 2;
        else if(pf <= cfg->pfDownLimit)
            return 3;
    }
    else if(uAvg < cfg->thDownVoltage && uAvg > cfg->thUpVoltage)
    {
        if(pf >= cfg->pfUpLimit)
            return 8;
        else if(pf > cfg->pfDownLimit && pf < cfg->pfUpLimit)
            return 9;
        else if(pf <= cfg->pfDownLimit)
            return 4;
    }
    else if(uAvg <= cfg->thUpVoltage)
    {
        if(pf >= cfg->pfUpLimit)
            return 7;
        else if(pf > cfg->pfDownLimit && pf < cfg->pfUpLimit)
            return 6;
        else if(pf <= cfg->pfDownLimit)
            return 5;
    }
    return 0;
}
/*****************************************************************************
 Function    : Auto_Control
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
uint8_t Auto_Control(ACSampleTypeDef *sample, ConfigParaTypeDef *cfg, SwitchTypeDef* sw)
{
    float    uMin = 0.0;
    float    uMax = 0.0;
    float    ua   = 0.0;
    float    ub   = 0.0;
    float    uc   = 0.0;
    float    uAvg = 0.0;
    uint16_t pf   = 0.0;
    float    qt   = 0.0;    //总无功
    float    qMin = 0.0;
    float    qa   = 0.0;
    float    qb   = 0.0;
    float    qc   = 0.0;
    float    qth  = 0.0;    //单个电容器组容量
    ua  = sample->ua;
    ub  = sample->ub;
    uc  = sample->uc;
    qa  = fabs(sample->qa);
    qb  = fabs(sample->qb);
    qc  = fabs(sample->qc);
    qth = (float) cfg->thQNeed;
    uAvg = (ua + ub + uc)/3.0;
    uMin = ua;
    if(ub < uMin)
        uMin = ub;
    if(uc < uMin)
        uMin = uc;
    uMax = ua;
    if(ub > uMax)
        uMax = ub;
    if(uc > uMax)
        uMax = uc;
    
    qMin = qa;
    if(qb < qMin)
        qMin = qb;
    if(qc < qMin)
        qMin = qc;

    qt = (qa + qb + qc); //取正数

    pf = sample->pf * 100;
    areaNum = Auto_Area_Judge(uAvg, pf, cfg);
    
    switch(areaNum)
    {
        case 1:
            if(sw->currentCapStat > 0)
            {
                sw->destCapStat = sw->currentCapStat - 1;
                autoMotionDest = 3;
            }
            else if(uMin > cfg->lockVoltageLowLimit)
                autoMotionDest = 2;
            else 
                autoMotionDest = 0;
        break;
        case 2:
            if(uMin > cfg->lockVoltageLowLimit)
                autoMotionDest = 2;
            else 
                autoMotionDest = 0;
        break;
        case 3:
            if(uMin > cfg->lockVoltageLowLimit)
                autoMotionDest = 2;
            else
                autoMotionDest = 0;
        break;
        case 4:
            if(sw->currentCapStat < 3) 
            {
                if(sw->currentCapStat == 0)
                {
                    if(qt > 3*qth && qMin > 3*qth/3)
                    {
                        autoMotionDest = 3;
                        sw->destCapStat = 3;
                    }
                    else if(qt < 3*qth && qt > 2*qth && qMin > 2*qth/3)
                    {
                        autoMotionDest = 3;
                        sw->destCapStat = 2;
                    }
                    else if(qt < 2*qth && qt > 1*qth && qMin > 1*qth/3)
                    {
                        autoMotionDest = 3;
                        sw->destCapStat = 1;
                    }
                    else
                        autoMotionDest = 0;
                } 
                else if(sw->currentCapStat == 1)
                {
                    if(qt > 2*qth && qMin > 2*qth/3)
                    {
                        autoMotionDest = 3;
                        sw->destCapStat = 3;
                    }
                    else if(qt < 2*qth && qt > 1*qth && qMin > 1*qth/3)
                    {
                        autoMotionDest = 3;
                        sw->destCapStat = 2;
                    }
                    else
                        autoMotionDest = 0;
                }
                else if(sw->currentCapStat == 2)
                {
                    if(qt > 1*qth && qMin > 1*qth/3)
                    {
                        autoMotionDest = 3;
                        sw->destCapStat = 3;
                    }
                    else 
                        autoMotionDest = 0;
                }
            }  
            else
                autoMotionDest = 0;
        break;
        case 5:
            if(sw->currentCapStat < 3) 
            {
                if(sw->currentCapStat == 0)
                {
                    if(qt > 3*qth && qMin > 3*qth/3)
                    {
                        autoMotionDest = 3;
                        sw->destCapStat = 3;
                    }
                    else if(qt < 3*qth && qt > 2*qth && qMin > 2*qth/3)
                    {
                        autoMotionDest = 3;
                        sw->destCapStat = 2;
                    }
                    else if(qt < 2*qth && qt > 1*qth && qMin > 1*qth/3)
                    {
                        autoMotionDest = 3;
                        sw->destCapStat = 1;
                    }
                    else
                        autoMotionDest = 0;
                } 
                else if(sw->currentCapStat == 1)
                {
                    if(qt > 2*qth && qMin > 2*qth/3)
                    {
                        autoMotionDest = 3;
                        sw->destCapStat = 3;
                    }
                    else if(qt < 2*qth && qt > 1*qth && qMin > 1*qth/3)
                    {
                        autoMotionDest = 3;
                        sw->destCapStat = 2;
                    }
                    else
                        autoMotionDest = 0;
                }
                else if(sw->currentCapStat == 2)
                {
                    if(qt > 1*qth && qMin > 1*qth/3)
                    {
                        autoMotionDest = 3;
                        sw->destCapStat = 3;
                    }
                    else
                        autoMotionDest = 0;
                }
            }  
            else if(uMax < cfg->lockVoltageUpLimit)
                    autoMotionDest = 1;
            else
                autoMotionDest =  0;
        break;
        case 6:
            if(uMax < cfg->lockVoltageUpLimit)
                autoMotionDest = 1;
            else
                autoMotionDest = 0;
        break;
        case 7:
            if(sw->currentCapStat > 0)
            {
                sw->destCapStat = sw->currentCapStat - 1;
                autoMotionDest = 3;
            }
            else
                autoMotionDest = 0;
        break;
        case 8:
            if(sw->currentCapStat > 0)
            {
                sw->destCapStat = sw->currentCapStat - 1;
                autoMotionDest = 3;
            }
            else
                autoMotionDest = 0;
        break;
        case 9:
            autoMotionDest = 0;
        break;
        default:
            autoMotionDest = 0;
    }

    return autoControlMotion;
}

/*****************************************************************************
 Function    : Auto_Control_Delay
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Auto_Control_Clear_Motion(void)
{
    areaFlagOK        = 0;
    autoControlMotion = 0;
    areaCount         = 0;
    lastAreaNum       = 0;
}
/*****************************************************************************
 Function    : Auto_Control_Time_Counter
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Auto_Control_Time_Counter(SwitchTypeDef* sw, uint32_t tyDelay, uint32_t capTouDelay, uint32_t capQieDelay)
{
    if(areaNum == lastAreaNum && areaFlagOK == 0 && areaNum != 9 && areaNum != 0)
    {
        if(autoMotionDest == 1 || autoMotionDest == 2)
        {
            if(areaCount < tyDelay)
                areaCount++;
            else
            {
                areaCount = 0;
                areaFlagOK = 1;
            }
        }
        else if(autoMotionDest == 3)
        {
            if(sw->destCapStat > sw->currentCapStat)
            {
                if(areaCount < capTouDelay)
                    areaCount++;
                else
                {
                    areaCount = 0;
                    areaFlagOK = 1;
                }
            }
            else if(sw->destCapStat < sw->currentCapStat)
            {
                if(areaCount < capQieDelay)
                    areaCount++;
                else
                {
                    areaCount = 0;
                    areaFlagOK = 1;
                }
            }
        } 
    }
    else
    {
        areaCount = 0;
        lastAreaNum = areaNum;
    }
    if(areaFlagOK == 1)
        autoControlMotion = autoMotionDest;
}
/************************ZXDQ *****END OF FILE****/

