/*
 * I2C.h
 *
 *  Created on: 26 dic 2019
 *      Author: luca
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include <STM32F303RE.h>


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

void __I2C_EnPCLK(I2C_t *pI2Cx);
void __I2C_init(I2C_handle *pI2Cx_h);
void __I2C_reset(I2C_handle *pI2Cx_h);
void __I2C_enable(I2C_handle *pI2Cx_h);
void __I2C_disable(I2C_handle *pI2Cx_h);
uint16_t __I2C_MasterSend(I2C_handle *pI2Cx_h, uint8_t SAddr);
uint16_t __I2C_MasterReceive(I2C_handle *pI2Cx_h, uint8_t SAddr);
void __I2C_SlaveOperation(I2C_handle *pI2Cx_h);
void __I2C_SlaveTransmitter(I2C_handle *pI2Cx_h);
void __I2C_SlaveReceiver(I2C_handle *pI2Cx_h);

void __I2C_IRQconfig(I2C_handle *pI2Cx_h, 	/*I2Cx handle address			*/
		 	 	 	 uint8_t     EnOrDis,	/*EN or DIS						*/
					 uint8_t     Priority);	/*0-15 where 0 is Highest  		*/
void __I2C_IRQhandle();




#endif /* INC_I2C_H_ */
