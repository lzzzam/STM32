/*
 * I2C.c
 *
 *  Created on: 26 dic 2019
 *      Author: luca
 */

#include <I2C.h>

void __I2C_EnPCLK(I2C_t *pI2Cx){

	if(pI2Cx == I2C1)
	{
		RCC_EN_CLK_I2C1();
	}
	else if(pI2Cx == I2C2)
	{
		RCC_EN_CLK_I2C2();
	}
	else if(pI2Cx == I2C3)
	{
		RCC_EN_CLK_I2C3();
	}

}

void __I2C_init(I2C_handle *pI2Cx_h)
{
	//Enable I2Cx Peripheral Clock
	__I2C_EnPCLK(pI2Cx_h->pI2Cx);

	//Set I2C SCLK source
	/*High Speed Internal Oscillator (8MHz) as default in RCC->CFGR3*/

	//Set Prescaler to 16: Tpresc = 16*125ns = 2000ns
	pI2Cx_h->pI2Cx->TIMINGR |= (0xF << 28);

	//Set Data Hold Time: SDADEL <= 1690/Tpresc = 0 in Standard Mode
	//See Reference manual "Setup and Hold Timing" SDADEL equation
	pI2Cx_h->pI2Cx->TIMINGR &=  ~(0xF << 16); //Clear 4 bit

	//Set Data Setup Time: SCLDEL >= 550/Tpresc = 0 in Standard Mode
	//See Reference manual "Setup and Hold Timing" SCLDEL equation
	pI2Cx_h->pI2Cx->TIMINGR &=  ~(0xF << 20); //Clear 4 bit

	//Set SCLK High and Low periods,
	uint32_t Fpresc = 8000000/16; // HSI/prescaler
	uint8_t SCLH = (uint8_t)(Fpresc/(pI2Cx_h->pI2Cx_conf.Speed))/2 - 1;
	uint8_t SCLL = SCLH;
	pI2Cx_h->pI2Cx->TIMINGR |= ((SCLH << 8) | (SCLL));

	//Set Own Slave address
	uint8_t Saddr = (pI2Cx_h->pI2Cx_conf.Addr & 0x7F); //mask 7 Bit
	pI2Cx_h->pI2Cx->OAR1 |= (Saddr << 1);
}

void __I2C_reset(I2C_handle *pI2Cx_h)
{

	if(pI2Cx_h->pI2Cx == I2C1)
	{
		RCC->APB1RSTR |= (1 << 21);
		RCC->APB1RSTR &= ~(1 << 21);
	}
	else if(pI2Cx_h->pI2Cx == I2C2)
	{
		RCC->APB1RSTR |= (1 << 22);
		RCC->APB1RSTR &= ~(1 << 22);
	}
	else if(pI2Cx_h->pI2Cx == I2C3)
	{
		RCC->APB1RSTR |= (1 << 30);
		RCC->APB1RSTR &= ~(1 << 30);
	}

}

void __I2C_enable(I2C_handle *pI2Cx_h)
{
	//Set PE bit in CR1 register
	pI2Cx_h->pI2Cx->CR1 |= (1 << 0);
}

void __I2C_disable(I2C_handle *pI2Cx_h)
{
	//Clear PE bit in CR1 register
	pI2Cx_h->pI2Cx->CR1 &= ~(1 << 0);
}

uint16_t __I2C_MasterSend(I2C_handle *pI2Cx_h, uint8_t *pTxBuf, uint16_t Len, uint8_t SAddr)
{

	uint16_t nTxBytes = 0;

	while(Len > 0)
	{
		uint32_t CR2_tmp = 0;

		//Set Slave Address
		CR2_tmp |= SAddr;
		CR2_tmp &= ~(1 << 10); //Set Write operation


		//Send with RELOAD mode
		if(Len > 255)
		{
			//Update Length
			Len = Len - 255;

			//Set 255 as Number of Bytes to be transferred
			CR2_tmp |= (0xFF << 16);

			//Set RELOAD bit
			CR2_tmp |= (1 << 24);

			//Set CR2 register
			pI2Cx_h->pI2Cx->CR2 = CR2_tmp;

			//Start communication
			pI2Cx_h->pI2Cx->CR2 |= (1 << 13);

			//Wait until Start phase is completed
			while( pI2Cx_h->pI2Cx->CR2 & (1 << 13) );

			//While TCR flag is set
			while( !(pI2Cx_h->pI2Cx->ISR & (1 >> 7)) )
			{
				//Check  if NACK is received
				if(pI2Cx_h->pI2Cx->ISR & (1 << 4)){
					//return number of byte transferred
					return nTxBytes;
				}
				//transmit new byte
				else
				{
					//Wait until TXDR is empty (check TXIS flag)
					while( !(pI2Cx_h->pI2Cx->ISR & (1 << 1)) );

					//Write new data into TX Data register
					*((uint8_t *)&pI2Cx_h->pI2Cx->TXDR) = *((uint8_t *)pTxBuf);
					pTxBuf++;
					nTxBytes++;
				}
			}
		}
		//Send with AUTO-END mode
		else
		{
			//Set Number of Bytes to be transferred
			CR2_tmp |= ((Len & 0xFF) << 16);

			//Set Auto-End mode
			CR2_tmp |= (1 << 25);

			//Set CR2 register
			pI2Cx_h->pI2Cx->CR2 = CR2_tmp;

			//Start communication
			pI2Cx_h->pI2Cx->CR2 |= (1 << 13);

			//Wait until Start phase is completed
			while( pI2Cx_h->pI2Cx->CR2 & (1 << 13) );

			while(Len > 0){

				//Check  if NACK is received
				if(pI2Cx_h->pI2Cx->ISR & (1 << 4)){
					//return number of byte transferred
					return nTxBytes;
				}
				else
				{
					//Wait until TXDR is empty (check TXIS flag)
					while( !(pI2Cx_h->pI2Cx->ISR & (1 << 1)) );

					//Write new data into TX Data register
					*((uint8_t *)&pI2Cx_h->pI2Cx->TXDR) = *((uint8_t *)pTxBuf);
					pTxBuf++;
					Len--;
					nTxBytes++;
				}
			}
		}
	}


	return nTxBytes;
}
