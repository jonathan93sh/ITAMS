/**********************************************************************
Boot Loader for ATMega32
Based at the Atmel AVR Application Note AVR109 "Self Programming"

NOTICE: NO BLOCK SUPPORT (not needed or supported when using AVRProg)

Compatible with AVRPROG (version 1.40)

Henning Hargaard 29.1.2015
***********************************************************************/
#include <avr/io.h>
#include <avr/boot.h>
#include <avr/pgmspace.h>
#include "uart.h"

#define	PAGESIZE 128
// Assume 1024 word boot loader
// Important: The Mega32 fuses must be set according to this !
#define	APP_END	0x3BFF

// Definitions for device recognition (ATMega32)
#define	PARTCODE         0x73
#define	SIGNATURE_BYTE_1 0x1E
#define	SIGNATURE_BYTE_2 0x95
#define	SIGNATURE_BYTE_3 0x02

BOOTLOADER_SECTION int main()
{
	char val;
	unsigned int address;
	unsigned int temp_int;
	
	// Disable all interrupts while boot loading
	__asm ("cli");
	// Clear SREG
	__asm ("eor r1,r1");
	__asm ("out 0x3f,r1");

	// Stack pointer = 0x085F (= RAMEND)
	__asm ("ldi r28,0x5F");
	__asm ("ldi r29,0x08");
	__asm ("out 0x3e,r29");
	__asm ("out 0x3d,r28" );

	// Initialize UART: 115200 bit/s, 8 data bits, no parity
	InitUART();

	while (1)
	{
		val = ReadChar();

		// Check auto increment status.
		if(val=='a')
		{
			SendChar('Y'); // Yes, we do auto increment.
		}

		// Set address.
		else if(val=='A') // Set address...
		{ // NOTE: Flash addresses are given in words, not bytes.
			address=((unsigned int)ReadChar()<<8) | ReadChar(); // Read address high and low byte.
			SendChar('\r'); // Send OK back.
		}

		// Chip erase.
		else if(val=='e')
		{
			for(address = 0; address < APP_END; address += PAGESIZE)
			{ // NOTE: Here we use address as a byte-address, not word-address, for convenience.
				boot_spm_busy_wait();
				boot_page_erase(address);
			}
			SendChar('\r'); // Send OK back.
		}

		// Read program memory.
		else if(val=='R')
		{
			// Send high byte, then low byte of flash word.
			boot_spm_busy_wait();
			boot_rww_enable();
			SendChar( pgm_read_byte_near((address << 1)+1 ) );
			SendChar( pgm_read_byte_near(address << 1) );
			address++; // Auto-advance to next Flash word.
		}

		// Write program memory, low byte.
		else if(val=='c')
		{ // NOTE: Always use this command before sending high byte.
			temp_int = ReadChar(); // Get low byte for later _FILL_TEMP_WORD.
			SendChar('\r'); // Send OK back.
		}
		
		// Write program memory, high byte.
		else if(val=='C')
		{
			temp_int |= ((unsigned int)ReadChar()<<8); // Get and insert high byte.
			boot_spm_busy_wait();
			boot_page_fill((address << 1), temp_int ); // Convert word-address to byte-address and fill.
			address++; // Auto-advance to next Flash word.
			SendChar('\r'); // Send OK back.
		}

		// Write page.
		else if(val== 'm')
		{
			if( address >= (APP_END>>1) ) // Protect boot loader area.
			{
				SendChar('?');
			}
			else
			{
				boot_spm_busy_wait();
				boot_page_write(address << 1); // Convert word-address to byte-address and write.
			}
			SendChar('\r'); // Send OK back.
		}

		// Enter and leave programming mode.
		else if( (val=='P') || (val=='L') )
		{
			SendChar('\r'); // Nothing special to do, just answer OK.
		}

		// Exit boot loader.
		else if(val=='E')
		{
			boot_spm_busy_wait();
			boot_rww_enable();
			SendChar('\r');
			// Generate watchdog RESET (starting the application)
			WDTCR = 0b00001000;
			while(1)
		{}
		}

		// Get programmer type.
		else if (val=='p')
		{
			SendChar('S'); // Answer 'SERIAL'.
		}

		// Return supported device codes.
		else if(val=='t')
		{
			SendChar( PARTCODE ); // Supports only this device, of course.
			SendChar( 0 ); // Send list terminator.
		}

		// Set LED, clear LED and set device type.
		else if((val=='x') || (val=='y') || (val=='T'))
		{
			ReadChar(); // Ignore the command and its parameter.
			SendChar('\r'); // Send OK back.
		}

		// Return programmer identifier.
		else if(val=='S')
		{
			SendChar('A'); // Return 'AVRBOOT'.
			SendChar('V'); // Software identifier (programmer signature) is always 7 characters.
			SendChar('R');
			SendChar('B');
			SendChar('O');
			SendChar('O');
			SendChar('T');
		}

		// Return software version.
		else if(val=='V')
		{
			SendChar('1');
			SendChar('5');
		}

		// Return signature bytes.
		else if(val=='s')
		{
			SendChar( SIGNATURE_BYTE_3 );
			SendChar( SIGNATURE_BYTE_2 );
			SendChar( SIGNATURE_BYTE_1 );
		}

		// The last command to accept is ESC (synchronization).
		else if(val!=0x1b) // If not ESC, then it is unrecognized...
		{
			SendChar('?');
		}
	}
}