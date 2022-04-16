#include "system.h"

#define USARTx_BUFFER_SIZE  25

USART_handle USART3_handle;
uint8_t txBuf[USARTx_BUFFER_SIZE];
uint8_t rxBuf[USARTx_BUFFER_SIZE];

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
    USART3_handle.pTxBuf = txBuf;
    USART3_handle.pRxBuf = rxBuf; 
    USART3_handle.TxLen = 0;
    USART3_handle.RxLen = 0;
    USART3_handle.USARTx_state = 0;

    // Initialize USART3
    __USART_init(&USART3_handle);
}