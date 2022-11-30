#include "Types.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "TMR2_interface.h"

#include "DC_interface.h"
#include "DC_config.h"
#include "DC_private.h"

void DC_vidInit(_enuGPIOX enuPIN2Port, _enuPINX enuPinNum)
{
    TMR2_voidInit();
    DIO_vidSetPinMode(enuPIN2Port, enuPinNum, OUTPUT);
}

void DC_vidStart(_enuGPIOX enuPIN2Port, _enuPINX enuPinNum,u8 u8dutycycle)
{
    DIO_vidWritePin(enuPIN2Port, enuPinNum, LOW);
    TMR2_GenerateFastPWM(u8dutycycle);
    TMR2_voidStart(TMR2_CLK_1024);
}

void DC_vidStop(void)
{
    TMR2_voidStopTMR2();
}