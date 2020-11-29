#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include "Serial.h"

void (*boot_start)(void) = (void *)0x7000;

int main(void)
{
  usart_init();

  while(1)
  {
    uint8_t c = usart_getch();

    if(c == 'R')
    {
      boot_start();
    }
  }
}
