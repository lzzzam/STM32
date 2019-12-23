/*
 * SPI.h
 *
 *  Created on: 17 dic 2019
 *      Author: luca
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include <STM32F303RE.h>

/********************************
 *  SPI Registers Bit
 ********************************/
#define SPI_CR1_CPHA		0
#define SPI_CR1_CPOL		1
#define SPI_CR1_MSTR		2
#define SPI_CR1_BR			3
#define SPI_CR1_SPE			6
#define SPI_CR1_LSBFIRST	7
#define SPI_CR1_SSI			8
#define SPI_CR1_SSM			9
#define SPI_CR1_RXONLY		10
#define SPI_CR1_CRCL		11
#define SPI_CR1_CRCNEXT		12
#define SPI_CR1_CRCEN		13
#define SPI_CR1_BIDIOE		14
#define SPI_CR1_BIDIMODE	15

#define SPI_CR2_RXDMAEN		0
#define SPI_CR2_TXDMAEN		1
#define SPI_CR2_SSOE		2
#define SPI_CR2_NSSP		3
#define SPI_CR2_FRF			4
#define SPI_CR2_ERRIE		5
#define SPI_CR2_RXNEIE		6
#define SPI_CR2_TXEIE		7
#define SPI_CR2_DS			8
#define SPI_CR2_FRXTH		12
#define SPI_CR2_LDMA_RX		13
#define SPI_CR2_LDMA_TX		14

//@SPI_Status_Register_Flag
#define SPI_SR_RXNE			0
#define SPI_SR_TXE			1
#define SPI_SR_CHSIDE		2
#define SPI_SR_UDR			3
#define SPI_SR_CRCERR		4
#define SPI_SR_MODF			5
#define SPI_SR_OVR			6
#define SPI_SR_BSY			7
#define SPI_SR_FRE			8
#define SPI_SR_FRLVL		9
#define SPI_SR_FTLVL		11

/********************************
 *  SPI Configuration Parameters
 ********************************/
//@Mode
#define SPI_MODE_MASTER	1
#define SPI_MODE_SLAVE	0
//@BusConfig
#define SPI_BUS_FULLDUPLEX	0
#define SPI_BUS_HALFDUPLEX	1
#define SPI_BUS_SIMPLEX_RX	2
#define SPI_BUS_SIMPLEX_TX	3
//@SSMgm
#define SPI_SS_SW	1
#define SPI_SS_HW	0
//@BaudRate
#define SPI_BR_PCLK_DIV2	0
#define SPI_BR_PCLK_DIV4	1
#define SPI_BR_PCLK_DIV8	2
#define SPI_BR_PCLK_DIV16	3
#define SPI_BR_PCLK_DIV32	4
#define SPI_BR_PCLK_DIV64	5
#define SPI_BR_PCLK_DIV128	6
#define SPI_BR_PCLK_DIV256	7
//@CPol
#define SPI_CPOL_HIGH	1
#define SPI_CPOL_LOW	0
//@CPha
#define SPI_CPHA_FIRST	0
#define SPI_CPHA_SECOND	1
//@DataSize
#define SPI_DS_4BIT		3
#define SPI_DS_5BIT		4
#define SPI_DS_6BIT		5
#define SPI_DS_7BIT		6
#define SPI_DS_8BIT		7
#define SPI_DS_9BIT		8
#define SPI_DS_10BIT	9
#define SPI_DS_11BIT	10
#define SPI_DS_12BIT	11
#define SPI_DS_13BIT	12
#define SPI_DS_14BIT	13
#define SPI_DS_15BIT	14
#define SPI_DS_16BIT	15

#define SPI_IRQ_NUM(x)	((x== SPI1) ? SPI1_IRQ_NUM : \
						 (x== SPI2) ? SPI2_IRQ_NUM : \
						 (x== SPI3) ? SPI3_IRQ_NUM : \
						 (x== SPI4) ? SPI4_IRQ_NUM : SPI1_IRQ_NUM)

//SPIx Tx and Rx State for Interrupt based communication
#define SPI_TX_FREE		0
#define SPI_TX_BUSY		1
#define SPI_RX_FREE		0
#define SPI_RX_BUSY		1
//SPIx TX and RX complete event
#define SPI_EVENT_TX_COMPLETE	0
#define SPI_EVENT_RX_COMPLETE	1

typedef struct{
	uint8_t Mode;		//@Mode
	uint8_t BusConfig;	//@BusConfig
	uint8_t SSMgm;		//@SSMgm
	uint8_t BaudRate;	//@BaudRate
	uint8_t CPol;		//@CPol
	uint8_t CPha;		//@CPha
	uint8_t DataSize;	//@DataSize
}SPI_Config;

typedef struct{
	SPI_t *pSPIx;
	SPI_Config pSPIx_conf;
	uint8_t *TxBuffer;
	uint16_t TxLen;
	uint8_t  TxState;
	uint8_t *RxBuffer;
	uint16_t RxLen;
	uint8_t  RxState;
}SPI_Handle;


void __SPI_EnPCLK(SPI_t *pSPIx);
void __SPI_init(SPI_Handle *pSPIx_h);
void __SPI_reset(SPI_t *pSPIx);
void __SPI_enable(SPI_Handle *pSPIx_h);
void __SPI_disable(SPI_Handle *pSPIx_h);
uint8_t __SPI_get_SRflag(SPI_Handle *pSPIx_h, uint8_t flag);	//flag @SPI_Status_Register_Flag
void __SPI_sendData(SPI_Handle *pSPIx_h, uint8_t *pTxBuf, int16_t Len);
void __SPI_receiveData(SPI_Handle *pSPIx_h, uint8_t *pRxBuf, uint16_t Len);
uint8_t __SPI_sendData_IT(SPI_Handle *pSPIx_h, uint8_t *pTxBuf, int16_t Len);
uint8_t __SPI_receiveData_IT(SPI_Handle *pSPIx_h, uint8_t *pRxBuf, uint16_t Len);
void __SPI_IRQconfig(SPI_Handle *pSPIx_h, uint8_t EnOrDis, uint8_t Priority);
void __SPI_IRQhandle(void);
__weak void __SPI_AppEventCallback(SPI_Handle *pSPIx_h, uint8_t AppEv);


#endif /* INC_SPI_H_ */
