/*
 * I2C.c
 *
 *  Created on: 26 dic 2019
 *      Author: luca
 */

#include <USART.h>

#define RCC_APB2ENR_USART1EN_Pos    14
#define RCC_APB1ENR_USART2EN_Pos    17
#define RCC_APB1ENR_USART3EN_Pos    18
#define RCC_APB1ENR_UART4EN_Pos     19
#define RCC_APB1ENR_UART5EN_Pos     20

void __USART_EnPCLK(USART_t *pUSARTx)
{
    // 1. Enable peripheral clock
    switch ((uint32_t)pUSARTx)
    {
        case (uint32_t)USART1:
            // Enable APB1 USART2 peripheral clock
            RCC->APB2ENR |= (1 << RCC_APB2ENR_USART1EN_Pos);
            break;

        case (uint32_t)USART2:
            // Enable APB1 USART2 peripheral clock
            RCC->APB1ENR |= (1 << RCC_APB1ENR_USART2EN_Pos);
            break;
        
        case (uint32_t)USART3:
            // Enable APB1 USART3 peripheral clock
            RCC->APB1ENR |= (1 << RCC_APB1ENR_USART3EN_Pos);
            break;

        case (uint32_t)UART4:
            // Enable APB1 UART4 peripheral clock
            RCC->APB1ENR |= (1 << RCC_APB1ENR_UART4EN_Pos);
            break;

        case (uint32_t)UART5:
            // Enable APB1 UART5 peripheral clock
            RCC->APB1ENR |= (1 << RCC_APB1ENR_UART5EN_Pos);
            break;
    }   
}

void __USART_init(USART_handle *pUSARTx_h)
{
    /* Configure USARTx peripheral  */

    // 1. Disable USARTx peripheral
    pUSARTx_h->pUSARTx->CR1 = pUSARTx_h->pUSARTx->CR1 & ~((uint32_t)USART_CR1_UE_Msk);

    // 2. Configure Stop bit
    switch (pUSARTx_h->pUSARTx_config.StopBit)
    {
        case USART_0_5_STOP_BITS:
            // STOP[1:0] = b01
            pUSARTx_h->pUSARTx->CR2 = (pUSARTx_h->pUSARTx->CR2 & ~((uint32_t)USART_CR2_STOP_Msk)) | (0x1 << USART_CR2_STOP_Pos);
            break;

        case USART_1_STOP_BITS:
            // STOP[1:0] = b00
            pUSARTx_h->pUSARTx->CR2 = (pUSARTx_h->pUSARTx->CR2 & ~((uint32_t)USART_CR2_STOP_Msk));
            break;

        case USART_1_5_STOP_BITS:
            // STOP[1:0] = b11
            pUSARTx_h->pUSARTx->CR2 = (pUSARTx_h->pUSARTx->CR2 & ~((uint32_t)USART_CR2_STOP_Msk)) | (0x3 << USART_CR2_STOP_Pos);
            break;

        case USART_2_STOP_BITS:
            // STOP[1:0] = b10
            pUSARTx_h->pUSARTx->CR2 = (pUSARTx_h->pUSARTx->CR2 & ~((uint32_t)USART_CR2_STOP_Msk)) | (0x2 << USART_CR2_STOP_Pos);
            break;
    }
    
    // 3. Configure Parity bit
    switch (pUSARTx_h->pUSARTx_config.ParityBit)
    {
        case USART_NO_PARITY:
            // Disable Parity Control
            pUSARTx_h->pUSARTx->CR1 = (pUSARTx_h->pUSARTx->CR1 & ~((uint32_t)USART_CR1_PCE_Msk));
            break;

        case USART_EVEN_PARITY:
            // Enable Parity Control and Even parity
            pUSARTx_h->pUSARTx->CR1 = (pUSARTx_h->pUSARTx->CR1  & ~((uint32_t)USART_CR1_PS_Msk | USART_CR1_PCE_Msk));
            break;

        case USART_ODD_PARITY:
            // Enable Parity Control and Odd parity
            pUSARTx_h->pUSARTx->CR1 = (pUSARTx_h->pUSARTx->CR1  & ~((uint32_t)USART_CR1_PS_Msk | (uint32_t)USART_CR1_PCE_Msk)) | USART_CR1_PS_Msk;
            break;
    }
    
    // 4. Configure Word length
    switch (pUSARTx_h->pUSARTx_config.WordLen)
    {
        case USART_WORD_7_BITS:
            // M[1:0] = b10
            pUSARTx_h->pUSARTx->CR1 = (pUSARTx_h->pUSARTx->CR1 & ~((uint32_t)USART_CR1_M1_Msk | (uint32_t)USART_CR1_M0_Msk)) | USART_CR1_M1_Msk;
            break;

        case USART_WORD_8_BITS:
            // M[1:0] = b00
            pUSARTx_h->pUSARTx->CR1 = (pUSARTx_h->pUSARTx->CR1 & ~((uint32_t)USART_CR1_M1_Msk | (uint32_t)USART_CR1_M0_Msk));
            break;

        case USART_WORD_9_BITS:
            // M[1:0] = b01
            pUSARTx_h->pUSARTx->CR1 = (pUSARTx_h->pUSARTx->CR1 & ~((uint32_t)USART_CR1_M1_Msk | (uint32_t)USART_CR1_M0_Msk)) | USART_CR1_M0_Msk;
            break;
    }
    
    // 5. Configure Baudrate
    uint32_t sysclk = __RCC_getSYSCLK();
    uint32_t baudrate = pUSARTx_h->pUSARTx_config.Speed;
    uint16_t usart_div = (uint16_t)(sysclk/baudrate);

    pUSARTx_h->pUSARTx->BRR = usart_div << USART_BRR_BRR_Pos;

    /* Enable USARTx peripheral and communication */

    // Enable peripheral
    pUSARTx_h->pUSARTx->CR1 = pUSARTx_h->pUSARTx->CR1 | USART_CR1_UE_Msk;

    // Enable TX and RX
    pUSARTx_h->pUSARTx->CR1 = pUSARTx_h->pUSARTx->CR1 | USART_CR1_TE_Msk | USART_CR1_RE_Msk;
}

void __USART_write_char(USART_handle *pUSARTx_h, uint8_t data)
{
    while (!(pUSARTx_h->pUSARTx->ISR & USART_ISR_TXE_Msk))
        ; // Wait till new byte can be transmitted
    
    // Send new data
    pUSARTx_h->pUSARTx->TDR = data;
}

void __USART_read_char(USART_handle *pUSARTx_h, uint8_t *data)
{
    while (!(pUSARTx_h->pUSARTx->ISR & USART_ISR_RXNE_Msk))
        ; // Wait till new byte is received

    // Read received data
    *data = (uint8_t)pUSARTx_h->pUSARTx->RDR;
}