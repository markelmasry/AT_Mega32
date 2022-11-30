

#include "Types.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"

#include "LM35_interface.h"
#include "LM35_config.h"
#include "LM35_private.h"

void LM35_vidInit(_enuADCChannels enuADCChannel)
{
	ADC_vidInit(enuADCChannel);
}

u16 LM35_u8Read(void)
{
	u16 u16Read;
	/* Return Digital value*/
	u16Read = ADC_u16Read();
	
	return u16Read;
}