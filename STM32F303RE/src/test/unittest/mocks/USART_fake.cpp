#include "USART_fake.hpp"

Mock<USART_interface> USART_mock;
USART_interface  &USART_fake = USART_mock.get();

void USART_write_char(uint8_t data)
{
    USART_fake.write_char(data);
}

void USART_read_char(uint8_t *data)
{
    *data = USART_fake.read_char();
    return;
}