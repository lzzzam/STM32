#include<avr/io.h>
#include<util/delay.h>
//#include "../Boot.h"

#define USART_BAUDRATE 9600
#define USART_TIMEOUT	BOOT_TIMEOUT
#define BAUD_PRESCALE (((16000000 / (USART_BAUDRATE * 16UL))) - 1)

#ifdef BOOT_AUTO_RST
  boot_timeout = 0;
#endif

void usart_init()
{



  UBRR0L = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value..
  // into the low byte of the UBRR register
  UBRR0H = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value..
  // into the high byte of the UBRR register

  // 2 stop bit, Use 8-bit character sizes
  UCSR0C |= (1<<USBS0) | (1 << UCSZ00) | (1 << UCSZ01);

  // Turn on the transmission and reception circuitry
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}

void usart_putch(uint8_t send)
{
  while ((UCSR0A & (1 << UDRE0)) == 0); // Do nothing until UDR is ready..
  // for more data to be written to it
  UDR0 = send; // Send the byte
}

unsigned int usart_getch()
{
  // Do nothing until data have been received and is ready to be read from UDR
  while ((UCSR0A & (1 << RXC0)) == 0)
  {
#ifdef BOOT_AUTO_RST
      //if timeout expired
      if(TCNT1 > USART_TIMEOUT)
      {
        boot_timeout = 1;
        return 0xFF;
      }
#endif
  }

  return(UDR0); // return the byte
}

void usart_puts(uint8_t *buf, uint16_t len)
{
  uint16_t i;
  for(i=0; i<len; i++)
  {
    usart_putch(*buf++);
  }
}
