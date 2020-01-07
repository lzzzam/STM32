/*
 * I2S.h
 *
 *  Created on: 6 gen 2020
 *      Author: luca
 */

#ifndef INC_I2S_H_
#define INC_I2S_H_

#include <STM32F303RE.h>

/********************************************************************************/
/*						Peripheral access method								*/
/********************************************************************************/
#define I2S2	SPI2
#define I2S3	SPI3
typedef SPI_t 	I2S_t;

/****************************************************************************
 *  							SPI Registers Bit
 ****************************************************************************/
//I2S Configuration Register
#define SPI_I2SCFGR_CHLEN	0
#define SPI_I2SCFGR_DATLEN	1
#define SPI_I2SCFGR_CKPOL	3
#define SPI_I2SCFGR_I2SSTD	4
#define SPI_I2SCFGR_PCMSYNC	7
#define SPI_I2SCFGR_I2SCFG	8
#define SPI_I2SCFGR_I2SE	10
#define SPI_I2SCFGR_I2SMOD	11
//I2S Prescaler Register
#define SPI_I2SPR_I2SDIV	0
#define SPI_I2SPR_ODD		8
#define SPI_I2SPR_MCKOE		9
/********************************************************************************
 *  					I2S Configuration Parameters
 ********************************************************************************/
//@Mode
#define I2S_MODE_SLAVE_TX	0
#define I2S_MODE_SLAVE_RX	1
#define I2S_MODE_MASTER_TX	2
#define I2S_MODE_MASTER_RX	3
//@SampFreq
#define I2S_FS_192KHZ		192000
#define I2S_FS_96KHZ		96000
#define I2S_FS_48KHZ		48000
#define I2S_FS_44KHZ		44000
//@DataSize
#define I2S_DS_16BIT		0
#define I2S_DS_24BIT		1
#define I2S_DS_32BIT		2
//@ChLen
#define I2S_CHLEN_16BIT		0
#define I2S_CHLEN_32BIT		1
//@Odd
#define I2S_ODD_LOW			0
#define I2S_ODD_HIGH		1
//@Cpol
#define I2S_CPOL_LOW		0
#define I2S_CPOL_HIGH		1
//@Std
#define I2S_STD_PHILIP		0
#define I2S_STD_MSB			1
#define I2S_STD_LSB			2
#define I2S_STD_PCM			3
//@Mclk
#define I2S_MCLK_DIS		0
#define I2S_MCLK_EN			1

/****************************************************************************
 * 			I2Sx Tx and Rx State for Interrupt based communication
 ****************************************************************************/
//@TX_State
#define I2S_TX_FREE		0		/*I2S is not transmitting data				*/
#define I2S_TX_BUSY		1		/*I2S is busy in transmitting  data			*/
//@RX_State
#define I2S_RX_FREE		0		/*I2S is not receiving data					*/
#define I2S_RX_BUSY		1		/*I2S is busy in receiving data				*/

//SPIx TX and RX complete event (@I2S_EVENT)
#define I2S_EVENT_TX_COMPLETE	0 /*Interrupt-based TX operation is complete*/
#define I2S_EVENT_RX_COMPLETE	1 /*Interrupt-based RX operation is complete*/

/****************************************************************************
 *  	 			I2Sx Configuration and Handle structure
 ****************************************************************************/
typedef struct{
	uint8_t Mode;		//@Mode
	uint32_t Fs;		//@SampFreq
	uint8_t DataSize;	//@DataSize
	uint8_t ChLen;		//@ChLen
	uint8_t Odd;		//@Odd
	uint8_t Cpol;		//@Cpol
	uint8_t Std;		//@Std
	uint8_t MCLK;		//@Mclk
}I2S_Config;

typedef struct{
	I2S_t *pI2Sx;
	I2S_Config pI2Sx_conf;
	uint16_t *pTxBuf_L;
	uint16_t *pTxBuf_R;
	uint16_t *pRxBuf_L;
	uint16_t *pRxBuf_R;
	uint32_t TxLen;
	uint32_t RxLen;
	uint8_t TxState;	//@TX_State
	uint8_t RxState;	//@RX_State
}I2S_Handle;

/****************************************************************************
 * @fn				- __I2S_EnPCLK
 *
 * @brief 			- Enable I2Sx Peripheral Clock
 * @param[*pSPIx] 	- I2Sx base address
 *
 * @note			- Call before __I2S_init
 ****************************************************************************/
void __I2S_EnPCLK(I2S_t *pI2Sx);	/*I2Sx with x = 2,3						*/


/****************************************************************************
 * @fn				- __I2S_init
 *
 * @brief 			- Initialize I2Sx Peripheral
 * @param[*pI2Sx_h] - I2Sx handle address
 *
 ****************************************************************************/
void __I2S_init(I2S_Handle *pI2Sx_h);	/*I2Sx handle address				*/


/****************************************************************************
 * @fn						- __I2S_reset
 *
 * @brief 					- Reset I2Sx register to default values after
 * 							  PowerOn reset
 * @param[*pI2Sx] 			- I2Sx base address
 *
 ****************************************************************************/
void __I2S_reset(I2S_t *pI2Sx);		/*I2Sx with x = 2,3						*/

/****************************************************************************
 * @fn						- __I2S_enable
 *
 * @brief 					- Enable I2Sx communication
 * @param[*pI2Sx_h] 		- I2Sx handle address
 *
 * @note					- Call before sending or receiving data
 ****************************************************************************/
void __I2S_enable(I2S_Handle *pI2Sx_h);	/*I2Sx handle address				*/


/****************************************************************************
 * @fn						- __I2S_disable
 *
 * @brief 					- Disable SPIx communication
 * @param[*pI2Sx_h] 		- I2Sx handle address
 *
 * @note					- Call after communication is complete
 ****************************************************************************/
void __I2S_disable(I2S_Handle *pI2Sx_h);/*I2Sx handle address				*/


/****************************************************************************
 * @fn						- __I2S_sendData
 *
 * @param[*pI2Sx_h] 		- I2Sx handle address
 * @param[data] 			- Data to be transmitted
 *
 * @note					-
 ****************************************************************************/
void __I2S_sendData(I2S_Handle *pI2Sx_h, uint16_t *pTxBuf_L, uint16_t *pTxBuf_R, uint32_t Len);


/****************************************************************************
 * @fn						- __I2S_sendData
 *
 * @param[*pI2Sx_h] 		- I2Sx handle address
 * @param[*data] 			- Pointer to store received value
 *
 * @note					-
 ****************************************************************************/
void __I2S_receiveData(I2S_Handle *pI2Sx_h, uint16_t *pRxBuf_L, uint16_t *pRxBuf_R, uint32_t Len);

/****************************************************************************
 * @fn						- __I2S_IRQconfig
 *
 * @brief 					- Configure the IRQ in the NVIC peripheral
 * 							  inside Cortex-M4 core
 * @param[*pI2Sx_h]			- I2Sx handle address to be enabled for Interrupt
 * 							  generation
 * @param[EnOrDis]			- Enable or Disable IRQ handling by the NVIC
 * @param[Priority]			- Interrupt priority
 *
 * @note					-
 ****************************************************************************/
void __I2S_IRQconfig(I2S_Handle *pI2Sx_h,	/*SPIx handle address			*/
					 uint8_t     EnOrDis,	/*EN or DIS						*/
					 uint8_t     Priority);	/*0-15 where 0 is Highest  		*/


/****************************************************************************
 * @fn						- __I2S_IRQhandle
 *
 * @brief 					- Handles the various source of I2Sx interrupt
 * 							  (BSY, TXE, RXNE, OVR, MODF, FRE flags) and
 * 							  execute proper operations
 * @param[*pI2Sx_h]			- I2Sx handle address that has generated the
 * 							  interrupt
 *
 * @note					- Must be called inside the I2Sx ISR function
 *
 ****************************************************************************/
void __I2S_IRQhandle(I2S_Handle *pI2Sx_h);	/*I2Sx handle address			*/


/****************************************************************************
 * @fn						- __I2S_AppEventCallback
 *
 * @brief 					- Each time interrupt-based TX and RX operations
 * 							  are completed a corresponding event is arised
 * 							  and this function is called from the TX and RX
 * 							  internal handle function.
 *
 * @param[*pI2Sx_h]			- I2Sx handle address that has generated the
 * 							  interrupt
 * @param[AppEv]			- @I2S_EVENT
 *
 * @note					- This function must be defined from the
 * 							  Application. Default is empty and don't
 * 							  execute any operation. This must be used
 * 							  to do proper operation after each TX and RX
 * 							  operation is complete.
 ****************************************************************************/
void __I2S_AppEventCallback(I2S_Handle *pI2Sx_h,	/*I2Sx handle address	*/
							uint8_t     AppEv);		/*@I2S_EVENT			*/


#endif /* INC_I2S_H_ */
