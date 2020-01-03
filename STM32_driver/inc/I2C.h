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
#define I2C_CR1_TXIE		1
#define I2C_CR1_RXIE		2
#define I2C_CR1_ADDRIE		3
#define I2C_CR1_NACKIE		4
#define I2C_CR1_STOPIE		5
#define I2C_CR1_TCIE		6
//Control Register 2
#define I2C_CR2_RD_WRN		10
#define I2C_CR2_ADD10		11
#define I2C_CR2_START		13
#define I2C_CR2_STOP		14
#define I2C_CR2_NACK		15
#define I2C_CR2_NBYTES		16
#define I2C_CR2_RELOAD		24
#define I2C_CR2_AUTOEND		25
//Own Address Register 1
#define I2C_OAR1_OA1_0		0
#define I2C_OAR1_OA1_7_1	1
#define I2C_OAR1_OA1_9_8	8
#define I2C_OAR1_OA1MODE	10
#define I2C_OAR1_OA1EN		15
//Interrupt and Statur Register
#define I2C_ISR_TXE			0
#define I2C_ISR_TXIS		1
#define I2C_ISR_RXNE		2
#define I2C_ISR_ADDR		3
#define I2C_ISR_NACKF		4
#define I2C_ISR_STOPF		5
#define I2C_ISR_TC			6
#define I2C_ISR_TCR			7
#define I2C_ISR_BUSY		15
#define I2C_ISR_DIR			16
//Interrupt Clear Register
#define I2C_ICR_ADDRCF		3
#define I2C_ICR_NACKCF		4
#define I2C_ICR_STOPCF		5


/****************************************************************************
 * 				I2Cx State\Callback\Configuration defines
 ****************************************************************************/
//I2Cx state for Interrupt-based transaction
#define I2C_FREE			0
#define I2C_BUSY_IN_TX		1
#define I2C_BUSY_IN_RX		2
//Start Repeat disable\enable
#define I2C_DISABLE_SR		0
#define I2C_ENABLE_SR		1
//Application Callback Event
#define I2C_EVENT_NACKF		0
#define I2C_EVENT_STOPF		1
#define I2C_EVENT_TC		2

#define I2C_PC_SEND			0
#define I2C_PC_RECEIVE		1
/****************************************************************************
 *  	 			I2Cx Configuration and Handle structure
 ****************************************************************************/
typedef struct{
	uint32_t Speed;	//SCLK freq in Hz (max 100kHz)
	uint8_t Addr;	//Own address when Slave
}I2C_Config;

typedef struct{
	I2C_t *pI2Cx;
	I2C_Config pI2Cx_conf;
	uint8_t *pTxBuf;
	uint8_t *pRxBuf;
	uint16_t TxLen;
	uint16_t RxLen;
	uint8_t  I2Cx_state;
	uint8_t  StartRpt;
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
void __I2C_SlaveSend(I2C_handle *pI2Cx_h,
					 uint8_t 	*pTxBuf,
					 uint32_t 	 Len);

/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
void __I2C_SlaveReceive(I2C_handle *pI2Cx_h,
						uint8_t    *pRxBuf,
						uint32_t 	Len);


/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
void __I2C_SlaveSend_IT(I2C_handle *pI2Cx_h,
					 	uint8_t    *pTxBuf,
						uint32_t 	Len);


/****************************************************************************
 * @fn			-
 *
 * @brief 		-
 * @param[ ] 	-
 *
 * @note		-
 ****************************************************************************/
void __I2C_SlaveReceive_IT(I2C_handle *pI2Cx_h,
						   uint8_t    *pRxBuf,
						   uint32_t    Len);



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
							uint8_t     AppEv);

#endif /* INC_I2C_H_ */
