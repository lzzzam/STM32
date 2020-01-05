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

	//Initialize I2Cx state as free
	pI2Cx_h->I2Cx_state = I2C_FREE;
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

uint8_t __I2C_get_CR1flag(I2C_handle *pI2Cx_h, uint8_t flag)
{
	if(pI2Cx_h->pI2Cx->CR1 & (1 << flag))
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

uint16_t __I2C_MasterSend(I2C_handle *pI2Cx_h, uint8_t *pTxBuf, uint32_t Len, uint8_t SAddr, uint8_t StartRpt)
{
	uint16_t nTxBytes = 0;

	while(Len > 0)
	{
		uint32_t CR2_tmp = 0;

		//Set Slave Address
		CR2_tmp |= (SAddr << 1);
		CR2_tmp &= ~(1 << I2C_CR2_RD_WRN); //Set Write operation

		//Send with RELOAD mode
		if(Len > 255)
		{
			//Update Length
			Len = Len - 255;

			//Set 255 as Number of Bytes to be transferred
			CR2_tmp |= (0xFF << I2C_CR2_NBYTES);

			//Clear TCR bit
			pI2Cx_h->pI2Cx->ISR &= ~(1 << I2C_ISR_TCR);

			//Set RELOAD bit
			CR2_tmp |= (1 << I2C_CR2_RELOAD);

			//Set CR2 register
			pI2Cx_h->pI2Cx->CR2 = CR2_tmp;

			//Start communication
			pI2Cx_h->pI2Cx->CR2 |= (1 << I2C_CR2_START);

			//Wait until Start phase is completed
			while( __I2C_get_CR2flag(pI2Cx_h, I2C_CR2_START) );

			//While TCR flag is reset
			while( ! __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_TCR) )
			{
				//Wait as long as TXDR is empty and NACK is not received
				while( ! __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_TXIS) &&
					   ! __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_NACKF));

				//Check  if NACK is received
				if( __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_NACKF) ){
					//return number of byte transferred
					return nTxBytes;
				}

				//Write new data into TX Data register
				*((uint8_t *)&pI2Cx_h->pI2Cx->TXDR) = *((uint8_t *)pTxBuf);
				pTxBuf++;
				nTxBytes++;
			}

		}
		//Send without RELOAD mode
		else
		{
			//Set Number of Bytes to be transferred
			CR2_tmp |= ((uint8_t)(Len & 0xFF) << I2C_CR2_NBYTES);

			//Master release I2C bus if SR is disabled
			if(StartRpt == I2C_DISABLE_SR)
				//Set Auto-End mode
				CR2_tmp |= (1 << I2C_CR2_AUTOEND); //Auto STOP after last byte is transmitted

			//Set CR2 register
			pI2Cx_h->pI2Cx->CR2 = CR2_tmp;

			//Start communication
			pI2Cx_h->pI2Cx->CR2 |= (1 << I2C_CR2_START);

			//Wait until Start phase is completed
			while( __I2C_get_CR2flag(pI2Cx_h, I2C_CR2_START) );

			while(Len > 0)
			{
				//Wait as long as TXDR is empty and NACK is not received
				while( ! __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_TXIS) &&
					   ! __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_NACKF));

				//Check  if NACK is received
				if( __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_NACKF) ){
					//return number of byte transferred
					return nTxBytes;
				}

				//Write new data into TX Data register
				*((uint8_t *)&pI2Cx_h->pI2Cx->TXDR) = *((uint8_t *)pTxBuf);
				pTxBuf++;
				Len--;
				nTxBytes++;
			}
		}
	}

	return nTxBytes;
}



uint16_t __I2C_MasterReceive(I2C_handle *pI2Cx_h, uint8_t *pRxBuf, uint32_t Len, uint8_t SAddr, uint8_t StartRpt)
{
	uint16_t nRxBytes = 0;

	while(Len > 0)
	{
		uint32_t CR2_tmp = 0;

		//Set Slave Address
		CR2_tmp |= (SAddr << 1);
		CR2_tmp |= (1 << I2C_CR2_RD_WRN); //Set Read operation

		//Read with RELOAD mode
		if(Len > 255)
		{
			//Update Length
			Len = Len - 255;

			//Set 255 as Number of Bytes to be transferred
			CR2_tmp |= (0xFF << I2C_CR2_NBYTES);

			//Clear TCR bit
			pI2Cx_h->pI2Cx->ISR &= ~(1 << I2C_ISR_TCR);

			//Set RELOAD bit
			CR2_tmp |= (1 << I2C_CR2_RELOAD);

			//Set CR2 register
			pI2Cx_h->pI2Cx->CR2 = CR2_tmp;

			//Start communication
			pI2Cx_h->pI2Cx->CR2 |= (1 << I2C_CR2_START);

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
		//Read without RELOAD mode
		else
		{
			//Set Number of Bytes to be received
			CR2_tmp |= ((Len & 0xFF) << I2C_CR2_NBYTES);

			//Master release I2C bus if SR is disabled
			if(StartRpt == I2C_DISABLE_SR)
				//Set Auto-End mode
				CR2_tmp |= (1 << I2C_CR2_AUTOEND); //Auto STOP after last byte is received

			//Set CR2 register
			pI2Cx_h->pI2Cx->CR2 = CR2_tmp;

			//Start communication
			pI2Cx_h->pI2Cx->CR2 |= (1 << I2C_CR2_START);

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

void __I2C_MasterSend_IT(I2C_handle *pI2Cx_h, uint8_t *pTxBuf, uint32_t Len, uint8_t SAddr, uint8_t StartRpt)
{
	if(pI2Cx_h->I2Cx_state == I2C_FREE)
	{
		//Copy TX data into I2Cx handle
		pI2Cx_h->pTxBuf = pTxBuf;
		pI2Cx_h->TxLen  = Len;
		pI2Cx_h->StartRpt = StartRpt;

		//Set Slave Address
		pI2Cx_h->pI2Cx->CR2 |= (SAddr << 1);
		pI2Cx_h->pI2Cx->CR2 &= ~(1 << I2C_CR2_RD_WRN); //Set Write operation

		//Send with RELOAD mode
		if(pI2Cx_h->TxLen > 255)
		{
			//Set 255 as Number of Bytes to be transferred
			pI2Cx_h->pI2Cx->CR2 |= (0xFF << I2C_CR2_NBYTES);

			//Clear TCR bit
			pI2Cx_h->pI2Cx->ISR &= ~(1 << I2C_ISR_TCR);

			//Set RELOAD bit
			pI2Cx_h->pI2Cx->CR2 |= (1 << I2C_CR2_RELOAD);

		}
		//Send without RELOAD mode
		else
		{
			//Clear RELOAD bit
			pI2Cx_h->pI2Cx->CR2 &= ~(1 << I2C_CR2_RELOAD);

			//Clear TCR bit
			pI2Cx_h->pI2Cx->ISR &= ~(1 << I2C_ISR_TCR);

			//Set Number of Bytes to be transferred
			pI2Cx_h->pI2Cx->CR2 &= ~(0xFF << I2C_CR2_NBYTES); //clear NBYTES
			pI2Cx_h->pI2Cx->CR2 |= ((uint8_t)(pI2Cx_h->TxLen & 0xFF) << I2C_CR2_NBYTES);
		}

		//Update peripheral state
		pI2Cx_h->I2Cx_state = I2C_BUSY_IN_TX;

		//Start communication
		pI2Cx_h->pI2Cx->CR2 |= (1 << I2C_CR2_START);

		//Enable Interrupt generation
		pI2Cx_h->pI2Cx->CR1 |= ((1 << I2C_CR1_TXIE) |
								(1 << I2C_CR1_TCIE) |
								(1 << I2C_CR1_NACKIE)|
								(1 << I2C_CR1_STOPIE));
	}
}

void __I2C_MasterReceive_IT(I2C_handle *pI2Cx_h, uint8_t *pRxBuf, uint32_t Len, uint8_t SAddr, uint8_t StartRpt)
{
	if(pI2Cx_h->I2Cx_state == I2C_FREE)
	{
		//Copy RX data into I2Cx handle
		pI2Cx_h->pRxBuf = pRxBuf;
		pI2Cx_h->RxLen  = Len;
		pI2Cx_h->StartRpt = StartRpt;

		//Set Slave Address
		pI2Cx_h->pI2Cx->CR2 |= (SAddr << 1);
		pI2Cx_h->pI2Cx->CR2 |= (1 << I2C_CR2_RD_WRN); //Set Read operation

		//Receive with RELOAD mode
		if(pI2Cx_h->RxLen > 255)
		{
			//Set 255 as Number of Bytes to be received
			pI2Cx_h->pI2Cx->CR2 |= (0xFF << I2C_CR2_NBYTES);

			//Clear TCR bit
			pI2Cx_h->pI2Cx->ISR &= ~(1 << I2C_ISR_TCR);

			//Set RELOAD bit
			pI2Cx_h->pI2Cx->CR2 |= (1 << I2C_CR2_RELOAD);

		}
		//Receive without RELOAD mode
		else
		{
			//Clear RELOAD bit
			pI2Cx_h->pI2Cx->CR2 &= ~(1 << I2C_CR2_RELOAD);

			//Clear TCR bit
			pI2Cx_h->pI2Cx->ISR &= ~(1 << I2C_ISR_TCR);

			//Set Number of Bytes to be received
			pI2Cx_h->pI2Cx->CR2 &= ~(0xFF << I2C_CR2_NBYTES); //clear NBYTES
			pI2Cx_h->pI2Cx->CR2 |= ((uint8_t)(pI2Cx_h->RxLen & 0xFF) << I2C_CR2_NBYTES);
		}

		//Update peripheral state
		pI2Cx_h->I2Cx_state = I2C_BUSY_IN_RX;

		//Start communication
		pI2Cx_h->pI2Cx->CR2 |= (1 << I2C_CR2_START);

		//Enable Interrupt generation
		pI2Cx_h->pI2Cx->CR1 |= ((1 << I2C_CR1_RXIE) |
								(1 << I2C_CR1_TCIE) |
								(1 << I2C_CR1_NACKIE)|
								(1 << I2C_CR1_STOPIE));
	}
}

void __I2C_enableSlaveOp(I2C_handle *pI2Cx_h)
{
	//Enable ADDR interrupt
	pI2Cx_h->pI2Cx->CR1 |= (1 << I2C_CR1_ADDRIE);

	//Enable Own Address1
	pI2Cx_h->pI2Cx->OAR1 |= (1 << I2C_OAR1_OA1EN);
}

void __I2C_disableSlaveOp(I2C_handle *pI2Cx_h)
{
	//Disable ADDR interrupt
	pI2Cx_h->pI2Cx->CR1 &= ~(1 << I2C_CR1_ADDRIE);

	//Disable Own Address1
	pI2Cx_h->pI2Cx->OAR1 &= ~(1 << I2C_OAR1_OA1EN);
}

void __I2C_SlaveSend(I2C_handle *pI2Cx_h, uint8_t data)
{
	//Write new byte into TX Data register
	*((uint8_t *)&pI2Cx_h->pI2Cx->TXDR) = (uint8_t)data;
}

void __I2C_SlaveReceive(I2C_handle *pI2Cx_h, uint8_t *data)
{
	//Read new byte from RX Data register
	*((uint8_t *)data) = *((uint8_t *)&pI2Cx_h->pI2Cx->RXDR);
}

static void __I2C_handleTXIS_IT(I2C_handle *pI2Cx_h)
{
	if(pI2Cx_h->I2Cx_state == I2C_SLAVE_MODE)
	{
		//inform application that a new byte is requested as slave
		//and let the application handle the new requested byte
		__I2C_AppEventCallback(pI2Cx_h, I2C_EVENT_DATA_REQ);
	}
	else if(pI2Cx_h->TxLen > 0)//Master mode
	{
		//Fill TXDR with new byte
		*((uint8_t *)&pI2Cx_h->pI2Cx->TXDR) = *((uint8_t *)pI2Cx_h->pTxBuf);
		pI2Cx_h->pTxBuf++;
		pI2Cx_h->TxLen--;
	}
}

static void __I2C_handleRXNE_IT(I2C_handle *pI2Cx_h)
{
	if(pI2Cx_h->I2Cx_state == I2C_SLAVE_MODE)
	{
		//inform application that a new byte is received as slave
		//and let the application handle the new byte
		__I2C_AppEventCallback(pI2Cx_h, I2C_EVENT_DATA_RCV);
	}
	else if(pI2Cx_h->RxLen > 0)//Master mode
	{
		//Read new byte from RXDR
		*((uint8_t *)pI2Cx_h->pRxBuf) = *((uint8_t *)&pI2Cx_h->pI2Cx->RXDR);
		pI2Cx_h->pRxBuf++;
		pI2Cx_h->RxLen--;
	}
}

static void __I2C_handleADDR_IT(I2C_handle *pI2Cx_h)
{
	//Set Slave Mode
	pI2Cx_h->I2Cx_state = I2C_SLAVE_MODE;

	//Enable NACK and STOPF interrupt
	pI2Cx_h->pI2Cx->CR1 |= ((1 << I2C_CR1_NACKIE)|
							(1 << I2C_CR1_STOPIE));

	//check transfer direction
	if( __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_DIR) == I2C_SLAVE_TRANSMIT )
	{
		//Flush TXDR
		pI2Cx_h->pI2Cx->ISR |= ( 1 << I2C_ISR_TXE );

		//Enable TXIS Interrupt generation
		pI2Cx_h->pI2Cx->CR1 |= (1 << I2C_CR1_TXIE);
	}
	else if(__I2C_get_ISRflag(pI2Cx_h, I2C_ISR_DIR) == I2C_SLAVE_RECEIVE )
	{
		//Enable RXNE Interrupt generation
		pI2Cx_h->pI2Cx->CR1 |= (1 << I2C_CR1_RXIE);
	}

	//Clear ADDR Flag (send Address ACK to Master)
	pI2Cx_h->pI2Cx->ICR |= (1 << I2C_ICR_ADDRCF);
	pI2Cx_h->pI2Cx->ICR &= ~(1 << I2C_ICR_ADDRCF);
}

static void __I2C_handleTC_IT(I2C_handle *pI2Cx_h)
{
	//Disable Interrupt generation
	if(pI2Cx_h->I2Cx_state == I2C_BUSY_IN_TX)
	{
		//Clear TXIS interrupt enable
		pI2Cx_h->pI2Cx->CR1 &= ~(1 << I2C_CR1_TXIE);
	}
	else if(pI2Cx_h->I2Cx_state == I2C_BUSY_IN_RX)
	{
		//read last byte if present
		__I2C_handleRXNE_IT(pI2Cx_h);
		//Clear RXNE interrupt enable
		pI2Cx_h->pI2Cx->CR1 &= ~(1 << I2C_CR1_RXIE);
	}

	//Clear TC interrupt enable
	pI2Cx_h->pI2Cx->CR1 &= ~(1 << I2C_CR1_TCIE);

	//Send stop request if Start Repeat is disabled
	if(pI2Cx_h->StartRpt == I2C_DISABLE_SR)
		pI2Cx_h->pI2Cx->CR2 |= (1 << I2C_CR2_STOP);

	//Free the I2Cx state
	pI2Cx_h->I2Cx_state = I2C_FREE;

	//Inform Application Transaction is completed
	__I2C_AppEventCallback(pI2Cx_h, I2C_EVENT_TC);
}

static void __I2C_handleTCR_IT(I2C_handle *pI2Cx_h)
{
	if(pI2Cx_h->I2Cx_state == I2C_BUSY_IN_TX)
	{
		//Send with RELOAD mode
		if(pI2Cx_h->TxLen > 255)
		{
			//Set 255 as Number of Bytes to be transferred
			pI2Cx_h->pI2Cx->CR2 |= (0xFF << I2C_CR2_NBYTES);

			//Clear TCR bit
			pI2Cx_h->pI2Cx->ISR &= ~(1 << I2C_ISR_TCR);

			//Set RELOAD bit
			pI2Cx_h->pI2Cx->CR2 |= (1 << I2C_CR2_RELOAD);
		}
		//Send without RELOAD mode
		else
		{
			//Clear RELOAD bit
			pI2Cx_h->pI2Cx->CR2 &= ~(1 << I2C_CR2_RELOAD);

			//Set Number of Bytes to be transferred
			pI2Cx_h->pI2Cx->CR2 &= ~(0xFF << I2C_CR2_NBYTES); //clear NBYTES
			pI2Cx_h->pI2Cx->CR2 |= ((uint8_t)(pI2Cx_h->TxLen & 0xFF) << I2C_CR2_NBYTES);
		}
	}
	else if(pI2Cx_h->I2Cx_state == I2C_BUSY_IN_RX)
	{
		//Receive with RELOAD mode
		if(pI2Cx_h->RxLen > 255)
		{
			//Set 255 as Number of Bytes to be transferred
			pI2Cx_h->pI2Cx->CR2 |= (0xFF << I2C_CR2_NBYTES);

			//Clear TCR bit
			pI2Cx_h->pI2Cx->ISR &= ~(1 << I2C_ISR_TCR);

			//Set RELOAD bit
			pI2Cx_h->pI2Cx->CR2 |= (1 << I2C_CR2_RELOAD);

		}
		//Receive without RELOAD mode
		else
		{
			//Clear RELOAD bit
			pI2Cx_h->pI2Cx->CR2 &= ~(1 << I2C_CR2_RELOAD);

			//Set Number of Bytes to be received
			pI2Cx_h->pI2Cx->CR2 &= ~(0xFF << I2C_CR2_NBYTES); //clear NBYTES
			pI2Cx_h->pI2Cx->CR2 |= ((uint8_t)(pI2Cx_h->RxLen & 0xFF) << I2C_CR2_NBYTES);
		}
	}

	//Restart communication
	pI2Cx_h->pI2Cx->CR2 |= (1 << I2C_CR2_START);

}

static void __I2C_handleSTOPF_IT(I2C_handle *pI2Cx_h)
{
	//Clear STOPF
	pI2Cx_h->pI2Cx->ICR |= (1 << I2C_ICR_STOPCF);
	pI2Cx_h->pI2Cx->ICR &= ~(1 << I2C_ICR_STOPCF);

	//Disable Interrupt generation
	pI2Cx_h->pI2Cx->CR1 &= ~((1 << I2C_CR1_TXIE) |
							 (1 << I2C_CR1_RXIE) |
							 (1 << I2C_CR1_TCIE) |
							(1 << I2C_CR1_NACKIE)|
							(1 << I2C_CR1_STOPIE));

	//Free the I2Cx state
	pI2Cx_h->I2Cx_state = I2C_FREE;

	//Inform Application transaction is closed
	__I2C_AppEventCallback(pI2Cx_h, I2C_EVENT_STOPF);
}

static void __I2C_handleNACKF_IT(I2C_handle *pI2Cx_h)
{
	//Clear NACKF
	pI2Cx_h->pI2Cx->ICR |= (1 << I2C_ICR_NACKCF);
	pI2Cx_h->pI2Cx->ICR &= ~(1 << I2C_ICR_NACKCF);

	//Inform Application NACK is received
	__I2C_AppEventCallback(pI2Cx_h, I2C_EVENT_NACKF);
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

void __I2C_EV_IRQhandle(I2C_handle *pI2Cx_h)
{
	uint8_t temp1;
	uint8_t temp2;

	temp1 = __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_ADDR);
	temp2 = __I2C_get_CR1flag(pI2Cx_h, I2C_CR1_ADDRIE);

	//Handle ADDR interrupt
	if(temp1 && temp2)
	{
		__I2C_handleADDR_IT(pI2Cx_h);
	}

	temp1 = __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_TXIS);
	temp2 = __I2C_get_CR1flag(pI2Cx_h, I2C_CR1_TXIE);

	//Handle TXIS interrupt
	if(temp1 && temp2)
	{
		__I2C_handleTXIS_IT(pI2Cx_h);
	}

	temp1 = __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_RXNE);
	temp2 = __I2C_get_CR1flag(pI2Cx_h, I2C_CR1_RXIE);

	//Handle RXNE interrupt
	if(temp1 && temp2)
	{
		__I2C_handleRXNE_IT(pI2Cx_h);
	}

	temp1 = __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_TC);
	temp2 = __I2C_get_CR1flag(pI2Cx_h, I2C_CR1_TCIE);

	//Handle TC interrupt
	if(temp1 && temp2)
	{
		__I2C_handleTC_IT(pI2Cx_h);
	}

	temp1 = __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_TCR);
	temp2 = __I2C_get_CR1flag(pI2Cx_h, I2C_CR1_TCIE);

	//Handle TCR interrupt
	if(temp1 && temp2)
	{
		__I2C_handleTCR_IT(pI2Cx_h);
	}

	temp1 = __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_NACKF);
	temp2 = __I2C_get_CR1flag(pI2Cx_h, I2C_CR1_NACKIE);

	//Handle NACKF interrupt
	if(temp1 && temp2)
	{
		__I2C_handleNACKF_IT(pI2Cx_h);
	}

	temp1 = __I2C_get_ISRflag(pI2Cx_h, I2C_ISR_STOPF);
	temp2 = __I2C_get_CR1flag(pI2Cx_h, I2C_CR1_STOPIE);

	//Handle STOPF interrupt
	if(temp1 && temp2)
	{
		__I2C_handleSTOPF_IT(pI2Cx_h);
	}

}


__weak void __I2C_AppEventCallback(I2C_handle *pI2Cx_h, uint8_t AppEv)
{
	//define in Application code
}
