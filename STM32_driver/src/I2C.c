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

	//Set Own Slave Address1
	uint8_t Saddr = (pI2Cx_h->pI2Cx_conf.Addr & 0x7F); //mask 7 Bit
	pI2Cx_h->pI2Cx->OAR1 |= (Saddr << 1);

	//Enable Own Address1
	pI2Cx_h->pI2Cx->OAR1 |= (1 << 15);
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
	//Wait if I2Cx is BUSY
	while( __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_BUSY) );

	//Clear PE bit in CR1 register
	pI2Cx_h->pI2Cx->CR1 &= ~(1 << 0);
}


uint8_t __I2C_get_ISRflag(I2C_handle *pI2Cx_h, uint8_t flag)
{
	if(pI2Cx_h->pI2Cx->ISR & (1 << flag))
	{
		return TRUE;
	}

	return FALSE;

}

uint8_t __I2C_get_CR2flag(I2C_handle *pI2Cx_h, uint8_t flag)
{
	if(pI2Cx_h->pI2Cx->CR2 & (1 << flag))
	{
		return TRUE;
	}

	return FALSE;
}

uint16_t __I2C_MasterSend(I2C_handle *pI2Cx_h, uint8_t SAddr)
{

	uint8_t *pTxBuf = pI2Cx_h->pTxBuf;
	uint16_t Len    = pI2Cx_h->TxLen;
	uint16_t nTxBytes = 0;

	while(Len > 0)
	{
		uint32_t CR2_tmp = 0;

		//Set Slave Address
		CR2_tmp |= (SAddr << 1);
		CR2_tmp &= ~(1 << 10); //Set Write operation


		//Send with RELOAD mode
		if(Len > 255)
		{
			//Update Length
			Len = Len - 255;

			//Set 255 as Number of Bytes to be transferred
			CR2_tmp |= (0xFF << 16);

			//Clear TCR bit
			pI2Cx_h->pI2Cx->ISR &= ~(1 << 7);

			//Set RELOAD bit
			CR2_tmp |= (1 << 24);

			//Set CR2 register
			pI2Cx_h->pI2Cx->CR2 = CR2_tmp;

			//Start communication
			pI2Cx_h->pI2Cx->CR2 |= (1 << 13);

			//Wait until Start phase is completed
			while( __I2C_get_CR2flag(pI2Cx_h, I2C_CR2_START) );

			//While TCR flag is reset
			while( ! __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_TCR) )
			{
				//Check  if NACK is received
				if( __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_NACKF) ){
					//return number of byte transferred
					return nTxBytes;
				}
				//transmit new byte
				else
				{
					//Wait until TXDR is empty (check TXIS flag)
					while(  ! __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_TXIS) );

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
			CR2_tmp |= ((uint8_t)(Len & 0xFF) << 16);

			//Set Auto-End mode
			CR2_tmp |= (1 << 25);

			//Set CR2 register
			pI2Cx_h->pI2Cx->CR2 = CR2_tmp;

			//Start communication
			pI2Cx_h->pI2Cx->CR2 |= (1 << 13);

			//Wait until Start phase is completed
			while( __I2C_get_CR2flag(pI2Cx_h, I2C_CR2_START) );

			while(Len > 0){

				//Check  if NACK is received
				if( __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_NACKF) ){
					//return number of byte transferred
					return nTxBytes;
				}
				else
				{
					//Wait until TXDR is empty (check TXIS flag)
					while( ! __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_TXIS) );

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



uint16_t __I2C_MasterReceive(I2C_handle *pI2Cx_h, uint8_t SAddr)
{
	uint8_t *pRxBuf = pI2Cx_h->pRxBuf;
	uint16_t Len = pI2Cx_h->RxLen;
	uint16_t nRxBytes = 0;

	while(Len > 0)
	{
		uint32_t CR2_tmp = 0;

		//Set Slave Address
		CR2_tmp |= (SAddr << 1);
		CR2_tmp |= (1 << 10); //Set Read operation


		//Read with RELOAD mode
		if(Len > 255)
		{
			//Update Length
			Len = Len - 255;

			//Set 255 as Number of Bytes to be transferred
			CR2_tmp |= (0xFF << 16);

			//Clear TCR bit
			pI2Cx_h->pI2Cx->ISR &= ~(1 << 7);

			//Set RELOAD bit
			CR2_tmp |= (1 << 24);

			//Set CR2 register
			pI2Cx_h->pI2Cx->CR2 = CR2_tmp;

			//Start communication
			pI2Cx_h->pI2Cx->CR2 |= (1 << 13);

			//Wait until Start phase is completed
			while( __I2C_get_CR2flag(pI2Cx_h, I2C_CR2_START) );

			//While TCR flag is set
			while( ! __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_TCR) )
			{
				//Wait until RXDR is not empty (check RXNE flag)
				while( ! __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_RXNE) );

				//Read new data from RX Data register
				*((uint8_t *)pRxBuf) = *((uint8_t *)&pI2Cx_h->pI2Cx->RXDR);
				pRxBuf++;
				nRxBytes++;
			}
		}
		//Read with AUTO-END mode
		else
		{
			//Set Number of Bytes to be received
			CR2_tmp |= ((Len & 0xFF) << 16);

			//Set Auto-End mode
			CR2_tmp |= (1 << 25);

			//Set CR2 register
			pI2Cx_h->pI2Cx->CR2 = CR2_tmp;

			//Start communication
			pI2Cx_h->pI2Cx->CR2 |= (1 << 13);

			//Wait until Start phase is completed
			while( __I2C_get_CR2flag(pI2Cx_h, I2C_CR2_START) );

			while(Len > 0){

				//Wait until RXDR is not empty (check RXNE flag)
				while( ! __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_RXNE) );

				//Read new data from RX Data register
				*((uint8_t *)pRxBuf) = *((uint8_t *)&pI2Cx_h->pI2Cx->RXDR);
				pRxBuf++;
				Len--;
				nRxBytes++;
			}
		}
	}


	return nRxBytes;
}

void __I2C_SlaveSend(I2C_handle *pI2Cx_h)
{
	//Wait until Slave is selected (Check ADDR flag)
	while( ! __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_ADDR) );

	//Flush TXDR
	pI2Cx_h->pI2Cx->ISR |= ( 1 << 0 );

	//Clear ADDR Flag
	pI2Cx_h->pI2Cx->ICR |= (1 << 3);
	pI2Cx_h->pI2Cx->ICR &= ~(1 << 3);

	uint8_t *pTxBuf = pI2Cx_h->pTxBuf;
	uint16_t Len = pI2Cx_h->TxLen;

	while(Len > 0)
	{
		//Wait until TXDR is empty (check TXIS flag)
		while( ! __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_TXIS) );

		//Write new data into TX Data register
		*((uint8_t *)&pI2Cx_h->pI2Cx->TXDR) = *((uint8_t *)pTxBuf);
		pTxBuf++;
		Len--;
	}

}

void __I2C_SlaveReceive(I2C_handle *pI2Cx_h)
{
	//Wait until Slave is selected (Check ADDR flag)
	while( ! __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_ADDR) );

	//Clear ADDR Flag
	pI2Cx_h->pI2Cx->ICR |= (1 << 3);
	pI2Cx_h->pI2Cx->ICR &= ~(1 << 3);

	uint8_t *pRxBuf = pI2Cx_h->pRxBuf;
	uint16_t Len = pI2Cx_h->RxLen;

	while(Len > 0)
	{
		//Wait until RXDR is not empty (check RXNE flag)
		while( ! __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_RXNE) );

		//Read new data from RX Data register
		*((uint8_t *)pRxBuf) = *((uint8_t *)&pI2Cx_h->pI2Cx->RXDR);
		pRxBuf++;
		Len--;
	}
}


void __I2C_IRQconfig(I2C_handle *pI2Cx_h, uint8_t EnOrDis, uint8_t Priority)
{
	uint8_t IRQ = I2C_IRQ_NUM(pI2Cx_h->pI2Cx);
	uint8_t Reg_num = IRQ / 32;
	uint8_t Reg_offset = IRQ % 32;

	if(EnOrDis == EN)
	{
		//Enable IRQ
		if(Reg_num == 0)
		{
			//Interrupt Set-Enable Reg 0
			NVIC_ISER0 |= (1 << Reg_offset);
		}else if(Reg_num == 1)
		{
			//Interrupt Set-Enable Reg 1
			NVIC_ISER1 |= (1 << Reg_offset);
		}else if(Reg_num == 2)
		{
			//Interrupt Set-Enable Reg 2
			NVIC_ISER2 |= (1 << Reg_offset);
		}
	}
	else if(EnOrDis == DIS)
	{
		//Disable IRQ
		if(Reg_num == 0)
		{
			//Interrupt Clear-Enable Reg 0
			NVIC_ICER0 |= (1 << Reg_offset);
		}else if(Reg_num == 1)
		{
			//Interrupt Clear-Enable Reg 1
			NVIC_ICER1 |= (1 << Reg_offset);
		}else if(Reg_num == 2)
		{
			//Interrupt Clear-Enable Reg 2
			NVIC_ICER2 |= (1 << Reg_offset);
		}
	}

	//Set IRQ priority
	uint8_t iprx = IRQ / 4;
	uint8_t shift_amount = ((IRQ % 4)*8) + (8 - NUM_PRIORITY_BITS);
	*(NVIC_IPR + iprx) |= (Priority << shift_amount);
}
