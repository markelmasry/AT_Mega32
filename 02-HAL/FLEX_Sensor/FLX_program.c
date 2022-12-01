

#include "Types.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"

#include "FLX_interface.h"
#include "FLX_config.h"
#include "FLX_private.h"

void FLX_vidInit(_enuADCChannels enuADCChannel)
{
	ADC_vidInit(enuADCChannel);
}

u16 FLX_u16Read(void)
{
		u16 u16Read;
	/* Return Digital value*/
	u16Read = ADC_u16Read();
	
	return u16Read;
}