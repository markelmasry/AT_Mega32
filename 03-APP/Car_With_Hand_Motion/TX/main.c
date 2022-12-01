/*
 * Graduation project (RC Car) MASTER.c
 *
 * Created: 11/26/2022 11:53:09 PM
 * Author : Michael-Malak
 */ 


/*********** Microcontroler Speed *************/
 
#define  F_CPU 16000000UL

#include <util/delay.h>

#include "Types.h"
#include "FLX_interface.h"
#include "ADC_interface.h"
#include "UART_interface.h"

/*********** ADC Read Variables *************/
u16 x,y,z;


int main(void)
{
/*********** UART Speed Define *************/  
    
    USART_vidInit(9600);
	

    
while(1){
		
/*********** Assign Flex Values to variables *************/  
		
	    FLX_vidInit(ADC0_CHANNEL);
	    x=FLX_u16Read();
		
		_delay_ms(50);
		
		FLX_vidInit(ADC1_CHANNEL);
		y=FLX_u16Read();
		
		_delay_ms(50);
		
		FLX_vidInit(ADC4_CHANNEL);
		z=FLX_u16Read();
		
		_delay_ms(50);
		
/*********** For Sending Right direction *************/  

		if(y>800 )
		{
			USART_vidSendByte('r');
		}
		
/*********** For Sending Forward/Backward direction *************/ 	
	
		else if (y>450 && y<800)
		{
			
/*********** For Sending Forward direction by sending value between 48-148 *************/ 		
			if (x>500 && x<700)
			{
				z=z*100;
				z=z/1024;
				z=z;
				
				
				USART_vidSendByte('0'+z);
			}
			
/*********** For Sending Forward direction by sending value between 148-248 *************/ 			
			else if ( x<500)
			{
				z=z*100;
				z=z/1024;
				z=z+100;
				
				USART_vidSendByte('0'+z);
			}
			else if ( x>700)
			{
				USART_vidSendByte('s');
			}
		}
		
/*********** For Sending Left direction *************/

		else if (y<450)
		{
			USART_vidSendByte('l');
		}
		
		
		

		_delay_ms(50);
		
    }
}

