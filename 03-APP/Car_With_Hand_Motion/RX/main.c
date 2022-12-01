/*
 * Gradution (slave) RX.c
 *
 * Created: 11/26/2022 11:50:35 PM
 * Author : marke
 */ 



#define F_CPU 16000000UL
#include "Types.h"

#include "LCD_interface.h"
#include "util/delay.h"
#include "LM35_interface.h"
#include "UART_interface.h"

//*********functions for driver l293d****************//
void forward(){
	DIO_vidWritePin(GPIOC,PIN3,HIGH);
	DIO_vidWritePin(GPIOC,PIN5,LOW);
	DIO_vidWritePin(GPIOC,PIN4,LOW);
	DIO_vidWritePin(GPIOC,PIN6,HIGH);
	
}
void backward(){
	DIO_vidWritePin(GPIOC,PIN3,LOW);
	DIO_vidWritePin(GPIOC,PIN5,HIGH);
	DIO_vidWritePin(GPIOC,PIN4,HIGH);
	DIO_vidWritePin(GPIOC,PIN6,LOW);
	
}
void left(){
	DC_vidStart(GPIOB, PIN5,95);
	DIO_vidWritePin(GPIOC,PIN3,HIGH);
	DIO_vidWritePin(GPIOC,PIN4,LOW);
	DIO_vidWritePin(GPIOC,PIN5,HIGH);
	DIO_vidWritePin(GPIOC,PIN6,LOW);
	
}
void right(){
	DC_vidStart(GPIOB, PIN5, 95);
	DIO_vidWritePin(GPIOC,PIN3,LOW);
	DIO_vidWritePin(GPIOC,PIN4,HIGH);
	DIO_vidWritePin(GPIOC,PIN5,LOW);
	DIO_vidWritePin(GPIOC,PIN6,HIGH);
	
	
}
void stop(){
	
	DIO_vidWritePin(GPIOC,PIN3,LOW);
	DIO_vidWritePin(GPIOC,PIN4,LOW);
	DIO_vidWritePin(GPIOC,PIN5,LOW);
	DIO_vidWritePin(GPIOC,PIN6,LOW);
	
}
 u8 x,y;
int main(void)
{
//****************driver l293d*************//
	DIO_vidSetPinMode(GPIOC,PIN3,OUTPUT);
	DIO_vidSetPinMode(GPIOC,PIN4,OUTPUT);
	DIO_vidSetPinMode(GPIOC,PIN5,OUTPUT);
	DIO_vidSetPinMode(GPIOC,PIN6,OUTPUT);
	DIO_vidSetPinMode(GPIOD,PIN4,INPUT);
	DIO_vidSetPinMode(GPIOD,PIN5,INPUT);
//**************uart**************************//
	USART_vidInit(9600);
//***************lcd****************************//
	DIO_vidSetPinMode(GPIOB,PIN2,OUTPUT);
	DIO_vidWritePin(GPIOB,PIN2,LOW);
	LCD_vidInit4bit(GPIOA,GPIOB,PIN1,GPIOB,PIN3,HIGH_NIBBLE);
//***************dc speed control***************************//
 	DC_vidInit(GPIOB, PIN5);

   
    while (1) 
    {
		 x= USART_u8RecieveByte();
		 _delay_ms(70);
//****************forward motion range**************//
		if ( (x>48)&& (x<148) && (x!='r') && (x!='l') && (x!='s') ){
			LCD_vidClearScreen4bit(GPIOA,GPIOB,PIN1,GPIOB,PIN3,HIGH_NIBBLE);
			LCD_voidDisplayString4bit(GPIOA,GPIOB,PIN1,GPIOB,PIN3,HIGH_NIBBLE,"forward");
			
			y=x-48;
			
			LCD_vidMoveCursor4bit(GPIOA,GPIOB,PIN1,GPIOB,PIN3,HIGH_NIBBLE,2,1);
			LCD_voidDisplayString4bit(GPIOA,GPIOB,PIN1,GPIOB,PIN3,HIGH_NIBBLE,"Speed :   ");
			LCD_vidDisplayNumber4bit(GPIOA,GPIOB,PIN1,GPIOB,PIN3,HIGH_NIBBLE,y);
			
//***************dc speed control********************//
		DC_vidStart(GPIOB, PIN5, y);
//*******************dc motion**********************//
			forward();
		}
		
//****************backward motion range**************//
		else if ((x>148) && (x<248) && (x!='r') && (x!='l') && (x!='s')){
			LCD_vidClearScreen4bit(GPIOA,GPIOB,PIN1,GPIOB,PIN3,HIGH_NIBBLE);
			LCD_voidDisplayString4bit(GPIOA,GPIOB,PIN1,GPIOB,PIN3,HIGH_NIBBLE,"backward");
			
			
			y=x-148;
			
		LCD_vidMoveCursor4bit(GPIOA,GPIOB,PIN1,GPIOB,PIN3,HIGH_NIBBLE,2,1);
		LCD_voidDisplayString4bit(GPIOA,GPIOB,PIN1,GPIOB,PIN3,HIGH_NIBBLE,"Speed :   ");
		LCD_vidDisplayNumber4bit(GPIOA,GPIOB,PIN1,GPIOB,PIN3,HIGH_NIBBLE,y);
		DC_vidStart(GPIOB, PIN5,y);
			backward();
			
		}
//****************right motion range**************//
		else if (x=='r'){
			LCD_vidClearScreen4bit(GPIOA,GPIOB,PIN1,GPIOB,PIN3,HIGH_NIBBLE);
			LCD_voidDisplayString4bit(GPIOA,GPIOB,PIN1,GPIOB,PIN3,HIGH_NIBBLE,"right");
			
			right();
			
			
		}
//****************left motion range**************//
		else if (x=='l'){
			LCD_vidClearScreen4bit(GPIOA,GPIOB,PIN1,GPIOB,PIN3,HIGH_NIBBLE);
			LCD_voidDisplayString4bit(GPIOA,GPIOB,PIN1,GPIOB,PIN3,HIGH_NIBBLE,"left");
	
			left();
			
		}
//****************stop motion range**************//
		
			else if (x=='s'){
				LCD_vidClearScreen4bit(GPIOA,GPIOB,PIN1,GPIOB,PIN3,HIGH_NIBBLE);
				LCD_voidDisplayString4bit(GPIOA,GPIOB,PIN1,GPIOB,PIN3,HIGH_NIBBLE,"stop");
	
				stop();
				
			}

	}
}

