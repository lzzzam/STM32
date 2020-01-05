/*
 * I2C.h
 *
 *  Created on: 26 dic 2019
 *      Author: luca
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include <STM32F303RE.h>

/****************************************************************************
 *  							I2C Registers Bit
 ****************************************************************************/
//Control Register 1
#define I2C_CR1_TXIE		1		/*TX interrupt enable					*/
#define I2C_CR1_RXIE		2       /*RX interrupt enable					*/
#define I2C_CR1_ADDRIE		3       /*Address match interrupt enable		*/
#define I2C_CR1_NACKIE		4       /*Not ACK received interrupt enable		*/
#define I2C_CR1_STOPIE		5       /*STOP detection interrupt enable		*/
#define I2C_CR1_TCIE		6       /*Transfer Complete interrupt enable	*/
//Control Register 2
#define I2C_CR2_RD_WRN		10      /*Transfer direction (Master Mode)		*/
#define I2C_CR2_ADD10		11      /*10-bit Addressing mode (Master Mode)	*/
#define I2C_CR2_START		13      /*START generation						*/
#define I2C_CR2_STOP		14      /*STOP generation (Master Mode)			*/
#define I2C_CR2_NACK		15      /*NACK generation (Slave Mode)			*/
#define I2C_CR2_NBYTES		16      /*Number of bytes (Master Mode)			*/
#define I2C_CR2_RELOAD		24      /*NBYTES Reload mode					*/
#define I2C_CR2_AUTOEND		25      /*Automatic End mode (Master Mode)		*/
//Own Address Register 1
#define I2C_OAR1_OA1_0		0       /*Own Address 1 bit 0					*/
#define I2C_OAR1_OA1_7_1	1       /*Own Address 1 bit 7 to 1				*/
#define I2C_OAR1_OA1_9_8	8       /*Own Address 1 bit 9 to 8				*/
#define I2C_OAR1_OA1MODE	10      /*Own Address 1 10-bit mode				*/
#define I2C_OAR1_OA1EN		15      /*Own Address 1 enable					*/
//Interrupt and Status Register
#define I2C_ISR_TXE			0       /*Transmit data register empty			*/
#define I2C_ISR_TXIS		1       /*Transmit interrupt status				*/
#define I2C_ISR_RXNE		2       /*Receive data register not empty		*/
#define I2C_ISR_ADDR		3       /*Address matched (Slave mode)			*/
#define I2C_ISR_NACKF		4       /*Not ACK received flag					*/
#define I2C_ISR_STOPF		5       /*STOP detection flag					*/
#define I2C_ISR_TC			6       /*Transfer complete flag (Master Mode)	*/
#define I2C_ISR_TCR			7       /*Transfer complete reload				*/
#define I2C_ISR_BUSY		15      /*Bus is busy							*/
#define I2C_ISR_DIR			16      /*Transfer direction (Slave Mode)		*/
//Interrupt Clear Register
#define I2C_ICR_ADDRCF		3       /*Address matched flag clear			*/
#define I2C_ICR_NACKCF		4       /*Not ACK flag clear					*/
#define I2C_ICR_STOPCF		5       /*STOP detection flag clear				*/
/****************************************************************************
 * 				I2Cx State\Callback\Configuration defines
 ****************************************************************************/
//I2Cx state for Interrupt-based operation (@I2CxState)
#define I2C_FREE			0	/*Peripheral is free						*/
#define I2C_BUSY_IN_TX		1	/*Peripheral is busy in Master transmission	*/
#define I2C_BUSY_IN_RX		2	/*Peripheral is busy in Master reception	*/
#define I2C_SLAVE_MODE		3	/*Peripheral is working in Slave mode		*/
//Start Repeat disable\enable	(@StartRepeat)
#define I2C_DISABLE_SR		0	/*STOP after Master transfer				*/
#define I2C_ENABLE_SR		1	/*Repeat START after Master transfer		*/
//Application Callback Event	(@AppEvent)
#define I2C_EVENT_NACKF		0	/*NACK received in byte transmission		*/
#define I2C_EVENT_STOPF		1	/*STOP condition is detected				*/
#define I2C_EVENT_TC		2	/*Transfer Complete (Master Mode)			*/
#define I2C_EVENT_DATA_REQ	3	/*Slave is requested to send byte			*/
#define I2C_EVENT_DATA_RCV	4	/*Slave has received a new byte				*/
//Slave Transfer direction
#define I2C_SLAVE_RECEIVE	0	/*Slave Receiver mode						*/
#define I2C_SLAVE_TRANSMIT	1	/*Slave Transmitter mode					*/
/****************************************************************************
 *  	 			I2Cx Configuration and Handle structure
 ****************************************************************************/
typedef struct{
	uint32_t Speed;			/*SCLK frequency in Hz, up to 400kHz			*/
	uint8_t Addr;			/*Own address when Slave, 7 bit only (0-127)	*/
}I2C_Config;

typedef struct{
	I2C_t *pI2Cx;			/*Base address of I2Cx peripheral 				*/
	I2C_Config pI2Cx_conf;	/*I2Cx configuration 							*/
	uint8_t *pTxBuf;		/*Pointer to TX buffer							*/
	uint8_t *pRxBuf;		/*Pointer to RX buffer							*/
	uint16_t TxLen;			/*Number of byte to be received in Master TX	*/
	uint16_t RxLen;			/*Number of byte to be received in Master RX	*/
	uint8_t  I2Cx_state;	/*@I2CxState									*/
	uint8_t  StartRpt;		/*@StartRepeat									*/
}I2C_handle;

/****************************************************************************
 * @fn			- SPI_IRQ_NUM
 *
 * @brief 		- Convert I2Cx address to respective IRQ number
 * @param[x] 	- I2Cx base address to be converted
 *
 * @note		- x range is I2C1, I2C2, I2C3
 ****************************************************************************/
#define I2C_IRQ_NUM(x)	((x== I2C1) ? I2C1_IRQ_NUM : \
						 (x== I2C2) ? I2C2_IRQ_NUM : \
						 (x== I2C3) ? I2C3_IRQ_NUM : I2C3_IRQ_NUM)

/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
void __I2C_EnPCLK(I2C_t *pI2Cx);

/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
void __I2C_init(I2C_handle *pI2Cx_h);

/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
void __I2C_reset(I2C_handle *pI2Cx_h);

/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
void __I2C_enable(I2C_handle *pI2Cx_h);

/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
void __I2C_disable(I2C_handle *pI2Cx_h);

/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
uint8_t __I2C_get_ISRflag(I2C_handle *pI2Cx_h,
						  uint8_t 	  flag);

/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
uint8_t __I2C_get_CR2flag(I2C_handle *pI2Cx_h,
						  uint8_t 	  flag);

/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
uint16_t __I2C_MasterSend(I2C_handle *pI2Cx_h,
						  uint8_t	 *pTxBuf,
						  uint32_t 	  Len,
						  uint8_t	  SAddr,
						  uint8_t 	  StartRpt);

/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
uint16_t __I2C_MasterReceive(I2C_handle *pI2Cx_h,
							 uint8_t 	*pRxBuf,
							 uint32_t 	 Len,
							 uint8_t 	 SAddr,
							 uint8_t 	 StartRpt);


/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
void __I2C_MasterSend_IT(I2C_handle *pI2Cx_h,
						  	 uint8_t	*pTxBuf,
							 uint32_t 	 Len,
							 uint8_t	 SAddr,
							 uint8_t 	 StartRpt);


/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
void __I2C_MasterReceive_IT(I2C_handle *pI2Cx_h,
						  	uint8_t	   *pRxBuf,
							uint32_t 	Len,
							uint8_t	    SAddr,
							uint8_t 	StartRpt);


/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
void __I2C_enableSlaveOp(I2C_handle *pI2Cx_h);


/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
void __I2C_disableSlaveOp(I2C_handle *pI2Cx_h);


/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
void __I2C_SlaveSend(I2C_handle *pI2Cx_h,
					 uint8_t 	 data);


/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
void __I2C_SlaveReceive(I2C_handle *pI2Cx_h,
						uint8_t    *data);

/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
void __I2C_IRQconfig(I2C_handle *pI2Cx_h, 	/*I2Cx handle address			*/
		 	 	 	 uint8_t     EnOrDis,	/*EN or DIS						*/
					 uint8_t     Priority);	/*0-15 where 0 is Highest  		*/


/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
void __I2C_EV_IRQhandle(I2C_handle *pI2Cx_h);


/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
void __I2C_AppEventCallback(I2C_handle *pI2Cx_h,
							uint8_t     AppEv);		/*@AppEvent				*/

#endif /* INC_I2C_H_ */
