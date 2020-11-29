#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/boot.h>
#include <util/delay.h>
#include "WaspBoot.h"
#include "Serial.h"
#include "Timer.h"


//128 bytes = ATmega328p page size
#define FLASH_PAGE_SIZE	128

void (*app_start)(void) = 0x0000;

void exit_Bootloader();

int main ( void )
{
	//PORTB0 as output (Arduino -> D8)
	DDRB |= 0x01;
	usart_init();
	TC1_init();

	//blink status LED to signal Entering in Wasp_Bootloader
	uint8_t i = 0;
	for(i=0; i<3; i++)
	{
		PORTB |= 1;
		_delay_ms(50);
		PORTB &= ~1;
		_delay_ms(50);
	}

	//turn on LED to signal Bootloader is waiting
	//for receiving data
	PORTB |= 1;

#ifndef BOOT_AUTO_RST
	//signal to Host that Bootloader is ready
	usart_putch('B');
#endif


	uint16_t start_address = 0;
	uint32_t byte_count = 0;

	while(1)
	{
		uint8_t c = usart_getch();

		if(c == 'S')//Size: number of bytes
		{
			byte_count |= ((uint32_t)usart_getch() << 8);
			byte_count |=  (uint32_t)usart_getch();
		}
		else if(c == 'A')//Start Flash address
		{
			start_address |= ((uint32_t)usart_getch() << 8);
			start_address |=  (uint32_t)usart_getch();
		}
		else if(c == 'P')//Program Flash
		{
			uint32_t i;
			uint8_t sreg;

			// Disable interrupts.
			sreg = SREG;
			cli();

			//erase start page
			uint16_t start_page = start_address & 0xFF80;
			boot_page_erase(start_page);
			boot_spm_busy_wait();

			//initialize address counter
			uint16_t address = start_address;
			//initialize page counter
			uint16_t page = start_page;

			//cycle for entire chunk
			for(i=0; i< byte_count; i = i + 2)
			{
				//if a new page is reached
				if((uint16_t)(address & 0x007F) == 0)//last 7 bits are equal to 0
				{
					page = address & 0xFF80; 	//update Flash page
					boot_page_erase (page); 	//erase page
					boot_spm_busy_wait (); 	 	//wait until the memory is erased
				}

				//fast toogle led when receiveing datas
				if((TCNT1) > 100)
				{
					PORTB ^= 1;		//toogle status led
					TCNT1  = 0;		//reset TC1 value
				}

				//receive new Flash word
				uint8_t lsb = usart_getch(); usart_putch(lsb);
				uint8_t msb = usart_getch(); usart_putch(msb);
				uint16_t word = ((uint16_t)msb << 8) | (uint16_t)lsb;

				//populate page buffer
				boot_page_fill (address, word);

				//if page boundary is reached
				if((address & 0x007F) == 0x007E) //last 7 bits equal to FLASH_SIZE - 2 = 126
				{
					boot_page_write (page); // Store buffer in flash page.
					boot_spm_busy_wait();   // Wait until the memory is written.
				}

				//Proceed to next Flash word address
				address += 2;
			}

			// Reenable RWW-section again. We need this if we want to jump back
			// to the application after bootloading.
			boot_rww_enable ();
			// Re-enable interrupts (if they were ever enabled).
			SREG = sreg;

		}
		else if (c == 'R')
		{
			uint8_t i;
			for(i = 0; i < byte_count; i++)
			{
				uint8_t data = pgm_read_byte_near(start_address + i);
				usart_putch(data);
			}
		}
		else if(c == 'Q')//Quit and go to Application
		{
			exit_Bootloader();
		}
#ifdef BOOT_AUTO_RST
		else if(boot_timeout)//Bootloader time expired
		{
			exit_Bootloader();
		}
#endif
	}
}

void exit_Bootloader()
{
	//turn off status led
	PORTB &= ~1;

	//stop Timer/Counter
	TC1_disable();

	//jump to App
	app_start();
}
