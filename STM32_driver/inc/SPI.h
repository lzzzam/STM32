/*
 * SPI.h
 *
 *  Created on: 17 dic 2019
 *      Author: luca
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include <STM32F303RE.h>

/****************************************************************************
 *  							SPI Registers Bit
 ****************************************************************************/
#define SPI_CR1_CPHA		0    /*Clock Phase 								*/
#define SPI_CR1_CPOL		1    /*Clock Polarity							*/
#define SPI_CR1_MSTR		2    /*Master\Slave 							*/
#define SPI_CR1_BR			3    /*Baud Rate								*/
#define SPI_CR1_SPE			6    /*SPI peripheral enable					*/
#define SPI_CR1_LSBFIRST	7    /*LSB\MSB first 							*/
#define SPI_CR1_SSI			8    /*SS internal								*/
#define SPI_CR1_SSM			9    /*SS software management					*/
#define SPI_CR1_RXONLY		10   /*RX\TX only								*/
#define SPI_CR1_CRCL		11   /*not used in this driver					*/
#define SPI_CR1_CRCNEXT		12   /*not used in this driver					*/
#define SPI_CR1_CRCEN		13   /*not used in this driver					*/
#define SPI_CR1_BIDIOE		14   /*Bidirectional output enable				*/
#define SPI_CR1_BIDIMODE	15   /*Bidirectional mode						*/

#define SPI_CR2_RXDMAEN		0    /*not used in this driver					*/
#define SPI_CR2_TXDMAEN		1    /*not used in this driver					*/
#define SPI_CR2_SSOE		2    /*SS output enable							*/
#define SPI_CR2_NSSP		3    /*SS pulse enable							*/
#define SPI_CR2_FRF			4    /*Frame format								*/
#define SPI_CR2_ERRIE		5    /*Communication Error Interrupt enable		*/
#define SPI_CR2_RXNEIE		6    /*RXFIFO not empty Interrupt enable		*/
#define SPI_CR2_TXEIE		7    /*TXFIFO empty Interrupt enable			*/
#define SPI_CR2_DS			8    /*Data Size								*/
#define SPI_CR2_FRXTH		12   /*RXFIFO Threshold							*/
#define SPI_CR2_LDMA_RX		13   /*not used in this driver					*/
#define SPI_CR2_LDMA_TX		14   /*not used in this driver					*/

//@SPI_Status_Register_Flag
#define SPI_SR_RXNE			0    /*RXFIFO not empty flag					*/
#define SPI_SR_TXE			1    /*TXFIFO empty flag						*/
#define SPI_SR_CHSIDE		2    /*not used in this driver					*/
#define SPI_SR_UDR			3    /*not used in this driver					*/
#define SPI_SR_CRCERR		4    /*not used in this driver					*/
#define SPI_SR_MODF			5    /*Mode fault flag							*/
#define SPI_SR_OVR			6    /*Overrun flag								*/
#define SPI_SR_BSY			7    /*Busy flag								*/
#define SPI_SR_FRE			8    /*Frame error flag							*/
#define SPI_SR_FRLVL		9    /*RXFIFO level 							*/
#define SPI_SR_FTLVL		11   /*TXFIFO level								*/

/****************************************************************************
 *  					SPI Configuration Parameters
 ****************************************************************************/
//@Mode
#define SPI_MODE_MASTER	1		/*Set SPI with MASTER mode					*/
#define SPI_MODE_SLAVE	0       /*Set SPI with SLAVE mode					*/
//@BusConfig
#define SPI_BUS_FULLDUPLEX	0   /*Set FullDuplex Communication				*/
#define SPI_BUS_HALFDUPLEX	1   /*Set HalfDuplex Communication				*/
#define SPI_BUS_SIMPLEX_RX	2   /*Set Simplex RX only Communication			*/
#define SPI_BUS_SIMPLEX_TX	3   /*Set Simplex TX only Communication			*/
//@SSMgm
#define SPI_SS_SW	1           /*Set Software Slave Selection management	*/
#define SPI_SS_HW	0           /*Set Hardware Slave Selection management	*/
//@BaudRate
#define SPI_BR_PCLK_DIV2	0   /*Set Peripheral clock at AHB clock / 2		*/
#define SPI_BR_PCLK_DIV4	1   /*Set Peripheral clock at AHB clock / 4		*/
#define SPI_BR_PCLK_DIV8	2   /*Set Peripheral clock at AHB clock / 8		*/
#define SPI_BR_PCLK_DIV16	3   /*Set Peripheral clock at AHB clock / 16	*/
#define SPI_BR_PCLK_DIV32	4   /*Set Peripheral clock at AHB clock / 32	*/
#define SPI_BR_PCLK_DIV64	5   /*Set Peripheral clock at AHB clock / 64	*/
#define SPI_BR_PCLK_DIV128	6   /*Set Peripheral clock at AHB clock / 128	*/
#define SPI_BR_PCLK_DIV256	7   /*Set Peripheral clock at AHB clock / 256	*/
//@CPol
#define SPI_CPOL_HIGH	1       /*Set Clock Idle state to HIGH 				*/
#define SPI_CPOL_LOW	0       /*Set Clock Idle state to LOW 				*/
//@CPha
#define SPI_CPHA_LOW	0       /*Set Clock active edge to first transition */
#define SPI_CPHA_HIGH	1       /*Set Clock active edge to second transition*/
//@DataSize
#define SPI_DS_4BIT		3       /*Set Data Size to 4 bit					*/
#define SPI_DS_5BIT		4       /*Set Data Size to 5 bit					*/
#define SPI_DS_6BIT		5       /*Set Data Size to 6 bit					*/
#define SPI_DS_7BIT		6       /*Set Data Size to 7 bit					*/
#define SPI_DS_8BIT		7       /*Set Data Size to 8 bit					*/
#define SPI_DS_9BIT		8       /*Set Data Size to 9 bit					*/
#define SPI_DS_10BIT	9       /*Set Data Size to 10 bit					*/
#define SPI_DS_11BIT	10      /*Set Data Size to 11 bit					*/
#define SPI_DS_12BIT	11      /*Set Data Size to 12 bit					*/
#define SPI_DS_13BIT	12      /*Set Data Size to 13 bit					*/
#define SPI_DS_14BIT	13      /*Set Data Size to 14 bit					*/
#define SPI_DS_15BIT	14      /*Set Data Size to 15 bit					*/
#define SPI_DS_16BIT	15      /*Set Data Size to 16 bit					*/

/****************************************************************************
 * 			SPIx Tx and Rx State for Interrupt based communication
 ****************************************************************************/
//@TX_State
#define SPI_TX_FREE		0		/*SPI is not transmitting data				*/
#define SPI_TX_BUSY		1		/*SPI is busy in transmitting  data			*/
//@RX_State
#define SPI_RX_FREE		0		/*SPI is not receiving data					*/
#define SPI_RX_BUSY		1		/*SPI is busy in receiving data				*/

//SPIx TX and RX complete event (@SPI_EVENT)
#define SPI_EVENT_TX_COMPLETE	0 /*Interrupt-based TX operation is complete*/
#define SPI_EVENT_RX_COMPLETE	1 /*Interrupt-based RX operation is complete*/

/****************************************************************************
 *  	 			SPIx Configuration and Handle structure
 ****************************************************************************/
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
	SPI_t *pSPIx;			//SPIx base address
	SPI_Config pSPIx_conf;	//SPIx Configuration
	uint8_t *TxBuffer;		//Data buffer to be transmitted		(used for Interrupt-based send)
	uint16_t TxLen;			//Number of data to be transmitted	(used for Interrupt-based send)
	uint8_t  TxState;		//@TX_State							(used for Interrupt-based send)
	uint8_t *RxBuffer;		//Data buffer for received data		(used for Interrupt-based receive)
	uint16_t RxLen;			//Number of data to be received		(used for Interrupt-based receive)
	uint8_t  RxState;		//@RX_State							(used for Interrupt-based receive)
}SPI_Handle;


/****************************************************************************
 * @fn			- SPI_IRQ_NUM
 *
 * @brief 		- Convert SPIx address to respective IRQ number
 * @param[x] 	- SPIx base address to be converted
 *
 * @note		- x range is SPI1, SPI2, SPI3 or SPI4
 ****************************************************************************/
#define SPI_IRQ_NUM(x)	((x== SPI1) ? SPI1_IRQ_NUM : \
						 (x== SPI2) ? SPI2_IRQ_NUM : \
						 (x== SPI3) ? SPI3_IRQ_NUM : \
						 (x== SPI4) ? SPI4_IRQ_NUM : SPI1_IRQ_NUM)



/****************************************************************************
 * @fn				- __SPI_EnPCLK
 *
 * @brief 			- Enable SPIx Peripheral Clock
 * @param[*pSPIx] 	- SPIx base address
 *
 * @note			- Call before __SPI_init
 ****************************************************************************/
void __SPI_EnPCLK(SPI_t *pSPIx);



/****************************************************************************
 * @fn				- __SPI_init
 *
 * @brief 			- Initialize SPIx Peripheral
 * @param[*pSPIx_h] - SPIx handle address
 *
 ****************************************************************************/
void __SPI_init(SPI_Handle *pSPIx_h);


/****************************************************************************
 * @fn						- __SPI_reset
 *
 * @brief 					- Reset SPIx register to default values after
 * 							  PowerOn reset
 * @param[*pSPIx] 			- SPIx base address
 *
 ****************************************************************************/
void __SPI_reset(SPI_t *pSPIx);


/****************************************************************************
 * @fn						- __SPI_enable
 *
 * @brief 					- Enable SPIx communication
 * @param[*pSPIx_h] 		- SPIx handle address
 *
 * @note					- Call before sending or receiving data
 ****************************************************************************/
void __SPI_enable(SPI_Handle *pSPIx_h);


/****************************************************************************
 * @fn						- __SPI_disable
 *
 * @brief 					- Disable SPIx communication
 * @param[*pSPIx_h] 		- SPIx handle address
 *
 * @note					- Call after communication is complete
 ****************************************************************************/
void __SPI_disable(SPI_Handle *pSPIx_h);

/****************************************************************************
 * @fn						- __SPI_get_SRflag
 *
 * @brief 					- Return Status Register flag value
 * 							  from SPIx_SR
 * @param[*pSPIx_h] 		- SPIx handle address
 * @param[flag] 			- @SPI_Status_Register_Flag
 *
 * @note					- Used to read BSY, TXE, RXNE, OVR, MODF, FRE
 * 							  flags
 ****************************************************************************/
uint8_t __SPI_get_SRflag(SPI_Handle *pSPIx_h, uint8_t flag);

/****************************************************************************
 * @fn						- __SPI_sendData
 *
 * @brief 					- Blocking transmission function
 * @param[*pSPIx_h] 		- SPIx handle address
 * @param[*pTxBuf] 			- Pointer to data buffer
 * @param[Len] 				- Number of bytes to be transmitted
 *
 * @note					- Wait until all bytes are transmitted
 ****************************************************************************/
void __SPI_sendData(SPI_Handle *pSPIx_h, uint8_t *pTxBuf, int16_t Len);


/****************************************************************************
 * @fn						- __SPI_receiveData
 *
 * @brief 					- Blocking receiving function
 * @param[*pSPIx_h] 		- SPIx handle address
 * @param[*pTxBuf] 			- Pointer to data buffer
 * @param[Len] 				- Number of bytes to be received
 *
 * @note					- Wait until all bytes are received
 ****************************************************************************/
void __SPI_receiveData(SPI_Handle *pSPIx_h, uint8_t *pRxBuf, uint16_t Len);

/****************************************************************************
 * @fn						- __SPI_sendData_IT
 *
 * @brief 					- Non-Blocking transmission function
 * @param[*pSPIx_h] 		- SPIx handle address
 * @param[*pTxBuf] 			- Pointer to data buffer
 * @param[Len] 				- Number of bytes to be transmitted
 *
 * @note					- Interrupt-based transmission
 *							  Each time the TXFIFO is empty the TXE flag
 *							  is set and a SPIx global interrupt is executed.
 *							  Then a new data is transmitted
 ****************************************************************************/
uint8_t __SPI_sendData_IT(SPI_Handle *pSPIx_h, uint8_t *pTxBuf, int16_t Len);

/****************************************************************************
 * @fn						- __SPI_receiveData_IT
 *
 * @brief 					- Non-Blocking receiving function
 * @param[*pSPIx_h] 		- SPIx handle address
 * @param[*pTxBuf] 			- Pointer to data buffer
 * @param[Len] 				- Number of bytes to be received
 *
 * @note					- Interrupt-based receiving
 *							  Each time the RXFIFO is not empty the RXNE flag
 *							  is set and a SPIx global interrupt is executed.
 *							  Then a new data is received
 ****************************************************************************/
uint8_t __SPI_receiveData_IT(SPI_Handle *pSPIx_h, uint8_t *pRxBuf, uint16_t Len);

/****************************************************************************
 * @fn						- __SPI_IRQconfig
 *
 * @brief 					- Configure the IRQ in the NVIC peripheral
 * 							  inside Cortex-M4 core
 * @param[*pSPIx_h]			- SPIx handle address to be enabled for Interrupt
 * 							  generation
 * @param[EnOrDis]			- Enable or Disable IRQ handling by the NVIC
 * @param[Priority]			- Interrupt priority
 *
 * @note					- Must be used before calling
 * 							  __SPI_sendData_IT and __SPI_receiveData_IT
 ****************************************************************************/
void __SPI_IRQconfig(SPI_Handle *pSPIx_h, uint8_t EnOrDis, uint8_t Priority);


/****************************************************************************
 * @fn						- __SPI_IRQhandle
 *
 * @brief 					- Handles the various source of SPIx interrupt
 * 							  (BSY, TXE, RXNE, OVR, MODF, FRE flags) and
 * 							  execute proper operations
 * @param[*pSPIx_h]			- SPIx handle address that has generated the
 * 							  interrupt
 *
 * @note					- Must be called inside the SPIx ISR function
 * 							  (SPI1_IRQHandler)
 ****************************************************************************/
void __SPI_IRQhandle(SPI_Handle *pSPIx_h);


/****************************************************************************
 * @fn						- __SPI_AppEventCallback
 *
 * @brief 					- Each time interrupt-based TX and RX operations
 * 							  are completed a corresponding event is arised
 * 							  and this function is called from the TX and RX
 * 							  internal handle function.
 *
 * @param[*pSPIx_h]			- SPIx handle address that has generated the
 * 							  interrupt
 * @param[AppEv]			- @SPI_EVENT
 *
 * @note					- This function must be defined from the
 * 							  Application. Default is empty and don't
 * 							  execute any operation. This must be used
 * 							  to do proper operation after each TX and RX
 * 							  operation is complete.
 ****************************************************************************/
void __SPI_AppEventCallback(SPI_Handle *pSPIx_h, uint8_t AppEv);


#endif /* INC_SPI_H_ */
