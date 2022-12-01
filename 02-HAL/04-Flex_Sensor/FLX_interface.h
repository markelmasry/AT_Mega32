#ifndef _HAL_FLX_INTERFACE_H
#define _HAL_FLX_INTERFACE_H

#include "ADC_interface.h"

void FLX_vidInit(_enuADCChannels enuADCChannel);

u16 FLX_u16Read(void);

#endif