/**
 * @brief This test implement a Serial communication reflector.
 * 
 * Each new byte received on the Serial communication is sent back 
 * to the host. USART3 is used as peripheral, with RX and TX pins
 * mapped respectively to PB8 and PB9.
 * 
 * The initialization of the system is done using the systemInit().
 * This function is defined as "weak", can be redefined in user code
 * and is automatically called during startup, see @ref Reset_Handler.
 * 
 * The serial port is initialized with:
 * - Baudrate = 9600
 * - Word length = 8
 * - Stop bits = 1
 * - Parity bit = no parity
 * 
 * To execute this test follow these instructions:
 *  1) Hook up a USB->SERIAL converter 
 *  2) Open a terminal and run the following command (Mac OSX):
 *     screen /dev/tty.YOUR_USB_TO_UART_DEVICE 9600
 *  3) Type any character and receive it back
 */

#include "STM32F303RE.h"
#include "../system/system.h"

USART_handle USART3_handle;

int main(void)
{
    while (1)
    { 
        uint8_t data;
        __USART_read_char(&USART3_handle, &data);
        __USART_write_char(&USART3_handle, data);
    }
}

// This function is called into Reset Handler
void systemInit()
{
    // Enable GPIO Port B - Peripheral clock
    __GPIO_EnPCLK(GPIOB);

    // Enable USART3 - Peripheral clock
    __USART_EnPCLK(USART3);

    // Configure PB8 as USART3 - RX
	__GPIO_init(GPIOB, 8, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_LOW, GPIO_NO_PUPD, GPIO_ALT_FNC_7);

    // Configure PB9 as USART3 - TX
	__GPIO_init(GPIOB, 9, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_LOW, GPIO_NO_PUPD, GPIO_ALT_FNC_7);

    // Initialize USART3 handle
    USART3_handle.pUSARTx = USART3;
    USART3_handle.pUSARTx_config.Speed = 9600;
    USART3_handle.pUSARTx_config.WordLen = USART_WORD_8_BITS;
    USART3_handle.pUSARTx_config.StopBit = USART_1_STOP_BITS;
    USART3_handle.pUSARTx_config.ParityBit = USART_NO_PARITY;

    // Initialize USART3
    __USART_init(&USART3_handle);
}