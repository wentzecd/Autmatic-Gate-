
#include <avr/io.h>
#include <stdint.h>
#include "libLCD/HD44780.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/interrupt.h>
#include "libKeypad/keypad_3by4.h"
//#include "IO_Macros.h"

#define MY_BUTTON1 PD7 
#define MY_BUTTON2 PD6 




/*Prototypes*/

void my_delay_ms(uint32_t delay);
short check_button_press_and_release(int button);
volatile uint8_t key;
volatile uint8_t keypad_flag;

ISR(TIMER1_OVF_vect)
{ 
	keypad_flag = 1;
}

int main(void)
{
	
	
	/*Outputs for Digital I/O Pins */
	DDRB |= _BV(DDB5);   //pin 13, indicator LED
	DDRB |= _BV(DDB1);   //pin 9, latch control
	
	
	/* Setup */
	sei();
	uint32_t i ;
	LCD_Setup();
	LCD_Clear();
	LCD_GotoXY(0,0);
	LCD_PrintString("Welcome!");
	my_delay_ms(3000);
	LCD_Clear();
	keypad_setup();
	uint8_t a = 0;
	uint8_t b = 0;
	

	
	//LCD_Clear();
	
	while(1)
	{
		
		
			LCD_GotoXY(0,0);
			LCD_PrintString("1. Open Gate");
			LCD_GotoXY(0,1);
			LCD_PrintString("2. Program");
		
		
		
		while(1)
		{
			
			key = key_pressed();
			
			if (check_button_press_and_release(MY_BUTTON2))	
			{
				LCD_Clear();
				LCD_GotoXY(0,0);
				LCD_PrintString("Opening Gate");
				PORTB |= _BV(PORTB5);
				PORTB |= _BV(PORTB1);
				my_delay_ms(5000);
				PORTB &= ~_BV(PORTB5);
				PORTB &= ~_BV(PORTB1);
				LCD_Clear();
				break;
			}
			
			
				if (key > 0)
				{
					uint8_t column;
					uint8_t row;
					
					
		
					/* decode column and row noting C0 = 1,..., C2 = 3, R0 = 1,..., R3 = 4 */
					column = key >> 4;
					row = key & 0x0F;
					
					if (column == 1 && row ==1)
					{
						LCD_Clear();
						LCD_GotoXY(0,0);
						LCD_PrintString("Opening Gate");
						PORTB |= _BV(PORTB5);
						PORTB |= _BV(PORTB1);
						my_delay_ms(5000);
						PORTB &= ~_BV(PORTB5);
						PORTB &= ~_BV(PORTB1);
						LCD_Clear();
						break;
					}
					
					if (column == 2 && row ==1)
					{
						a=1;
						LCD_Clear();
						LCD_GotoXY(0,0);
						LCD_PrintString("1.Unlock 2.Lock");
						LCD_GotoXY(0,1);
						LCD_PrintString("3. Normal Mode");
						my_delay_ms(5000);
						LCD_Clear();
						break;
					}
				
					
					else
					{
						/* print column on top and row on bottom */
						LCD_Clear();
						LCD_GotoXY(0,0);
						LCD_PrintInteger(column);
						LCD_GotoXY(0,1);
						LCD_PrintInteger(row);
						my_delay_ms(5000);
						key = 0x00;
						break; 
					}
				}
		
			 
		}
		
			
	
	}
	
}		




short check_button_press_and_release(int button)
{
	int ret_val = 0;


	if ((PIND & (1 << button)) != 0)
	{
		/* software debounce */
		_delay_ms(15);
		if ((PIND & (1 << button)) != 0)
		{
			/* wait for button to be released */
			while((PIND & (1 << button)) != 0)
				ret_val = 1;
		}
	}

	
	return ret_val;
}





//handles delays, only used in check_button_press_and_release function
void my_delay_ms(uint32_t delay) 
{
	uint32_t i;

	for (i=0; i<(delay/10); i++) 
	{
		_delay_ms(10);
	}
	if (delay % 10) {
		_delay_ms(delay % 10);
	}
}