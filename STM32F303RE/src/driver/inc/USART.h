/*
 * USART.h
 *
 *  Created on: 25 dic 2022
 *      Author: luca
 */

#ifndef INC_USART_H_
#define INC_USART_H_

#include <STM32F303RE.h>

typedef enum{
    USART_NO_PARITY,
    USART_EVEN_PARITY,
    USART_ODD_PARITY
} USART_Parity;

typedef enum{
    USART_0_5_STOP_BITS,
    USART_1_STOP_BITS,
    USART_1_5_STOP_BITS,
    USART_2_STOP_BITS,
} USART_Stop;

typedef enum{
    USART_WORD_7_BITS,
    USART_WORD_8_BITS,
    USART_WORD_9_BITS
} USART_WordLen;

typedef struct{
    uint32_t        Speed;
    USART_Parity    ParityBit;
    USART_Stop      StopBit;
    USART_WordLen   WordLen;
} USART_Config;

typedef struct{
	USART_t     *pUSARTx;		   /*Base address of USARTx peripheral 			*/
	USART_Config pUSARTx_config;   /*USARTx configuration 						*/
} USART_handle;

void __USART_EnPCLK(USART_t *pUSARTx);
void __USART_init(USART_handle *pUSARTx_h);
void __USART_write_char(USART_handle *pUSARTx_h, uint8_t data);
void __USART_read_char(USART_handle *pUSARTx_h, uint8_t *data);

#endif/* INC_USART_H_ */