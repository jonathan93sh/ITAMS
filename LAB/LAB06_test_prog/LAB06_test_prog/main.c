/*
 * LAB06_test_prog.c
 *
 * Created: 06-02-2017 14:19:08
 * Author : jonathan
 */ 
#define  F_CPU 3686400  
#include <avr/io.h>
#include <avr/delay.h>


int main(void)
{
    /* Replace with your application code */
	
	DDRA = 0x00; //inputs
	DDRC = 0xFF; //outputs
	
	PORTC = 0b1111;
	
    while (1) 
    {
		if((~PINA) & 0b1 == 1) // jump to boot
		{
			for(uint8_t i = 0; i < 10; i++)
			{
				PORTC = 0x00;
				_delay_ms(50);
				PORTC = 0xFF;
				_delay_ms(50);
			}
			
			__asm("jmp 0x3C00");
			
		}
		
		
		
		
		
    }
}

