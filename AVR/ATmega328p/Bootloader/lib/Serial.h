#ifndef SERIAL_H
#define SERIAL_H

#ifdef BOOT_AUTO_RST
  extern uint8_t boot_timeout;
#endif

void usart_init();
void usart_putch(uint8_t send);
unsigned int usart_getch();
void usart_puts(uint8_t *buf, uint16_t len);


#endif
