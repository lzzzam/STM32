/*
 * I2C.h
 *
 *  Created on: 26 dic 2019
 *      Author: luca
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include <STM32F303RE.h>

#define I2C_SDADEL	0
#define I2C_SCLDEL

typedef struct{
	uint32_t Speed;	//SCLK freq in Hz (max 100kHz)
	uint8_t Addr;	//Own address when Slave
}I2C_Config;

typedef struct{
	I2C_t *pI2Cx;
	I2C_Config pI2Cx_conf;
}I2C_handle;

void __I2C_EnPCLK(I2C_t *pI2Cx);
void __I2C_init(I2C_handle *pI2Cx_h);
void __I2C_reset(I2C_handle *pI2Cx_h);
void __I2C_enable(I2C_handle *pI2Cx_h);
void __I2C_disable(I2C_handle *pI2Cx_h);
uint16_t __I2C_MasterSend(I2C_handle *pI2Cx_h, uint8_t *pTxBuf, uint16_t Len, uint8_t SAddr);
void __I2C_MasterReceive(I2C_handle *pI2Cx_h, uint8_t *pRxBuf, uint8_t Len, uint8_t SAddr);
void __I2C_SlaveSend(I2C_handle *pI2Cx_h, uint8_t *pTxBuf, uint8_t Len);
void __I2C_SlaveReceive(I2C_handle *pI2Cx_h, uint8_t *pRxBuf, uint8_t Len);
void __I2C_IRQconfig();
void __I2C_IRQhandle();




#endif /* INC_I2C_H_ */
