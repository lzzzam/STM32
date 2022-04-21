#include "STM32F303RE.h"
#include "fakeit.hpp"

using namespace fakeit;

struct USART_interface 
{
   virtual void write_char(uint8_t data) = 0;
   virtual uint8_t read_char(void) = 0;
};

extern Mock<USART_interface> USART_mock;

void USART_write_char(uint8_t data);
void USART_read_char(uint8_t *data);