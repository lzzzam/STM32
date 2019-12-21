/*
 * SPI.c
 *
 *  Created on: 17 dic 2019
 *      Author: luca
 */
#include <SPI.h>

void __SPI_EnPCLK(SPI_t *pSPIx){

	if(pSPIx == SPI1)
	{
		RCC_EN_CLK_SPI1();
	}
	else if(pSPIx == SPI2)
	{
		RCC_EN_CLK_SPI2();
	}
	else if(pSPIx == SPI3)
	{
		RCC_EN_CLK_SPI3();
	}
	else if(pSPIx == SPI4)
	{
		RCC_EN_CLK_SPI4();
	}

}

void __SPI_init(SPI_Handle *pSPIx_h){

	uint32_t reg_CR1 = 0;

	//Set Master\Slave mode
	reg_CR1 |= (pSPIx_h->pSPIx_conf.Mode << SPI_CR1_MSTR);

	//Set Bus Configuration
	if(pSPIx_h->pSPIx_conf.BusConfig == SPI_BUS_FULLDUPLEX)
	{
		reg_CR1 &= ~(1 << SPI_CR1_BIDIMODE);
		reg_CR1 &= ~(1 << SPI_CR1_RXONLY);
	}
	else if(pSPIx_h->pSPIx_conf.BusConfig == SPI_BUS_HALFDUPLEX)
	{
		reg_CR1 |= (1 << SPI_CR1_BIDIMODE);
	}
	else if(pSPIx_h->pSPIx_conf.BusConfig == SPI_BUS_SIMPLEX_RX)
	{
		reg_CR1 &= ~(1 << SPI_CR1_BIDIMODE);
		reg_CR1 |= (1 << SPI_CR1_RXONLY);
	}
	else if(pSPIx_h->pSPIx_conf.BusConfig == SPI_BUS_SIMPLEX_TX)
	{
		reg_CR1 &= ~(1 << SPI_CR1_BIDIMODE);
		reg_CR1 &= ~(1 << SPI_CR1_RXONLY);
	}

	//Set SS Management
	reg_CR1 |= (pSPIx_h->pSPIx_conf.SSMgm << SPI_CR1_SSM);

	//Enable SS Output if Mode Master and SSMgm is set to HW
	if((pSPIx_h->pSPIx_conf.Mode == SPI_MODE_MASTER) &&  (! pSPIx_h->pSPIx_conf.SSMgm))
		pSPIx_h->pSPIx->CR2 |= (1 << SPI_CR2_SSOE);

	//Set BaudRate
	reg_CR1 |= (pSPIx_h->pSPIx_conf.BaudRate << SPI_CR1_BR);

	//Set CPOL
	reg_CR1 |= (pSPIx_h->pSPIx_conf.CPol << SPI_CR1_CPOL);

	//Set CPHA
	reg_CR1 |= (pSPIx_h->pSPIx_conf.CPha << SPI_CR1_CPHA);

	//Write to CR1
	pSPIx_h->pSPIx->CR1 = reg_CR1;

	//Set Data Size
	pSPIx_h->pSPIx->CR2 |= (pSPIx_h->pSPIx_conf.DataSize << SPI_CR2_DS);
	//Set RXFIFO Threshold
	if(pSPIx_h->pSPIx_conf.DataSize <= SPI_DS_8BIT)
		pSPIx_h->pSPIx->CR2 |= (1 << SPI_CR2_FRXTH); //RXNE Flag is set when RXFIFO level >= of 1/4 (8Bit)
}


void __SPI_reset(SPI_t *pSPIx){

	if(pSPIx == SPI1)
	{
		RCC->APB2RSTR |= (1 << 12);
		RCC->APB2RSTR &= ~(1 << 12);
	}
	else if(pSPIx == SPI2)
	{
		RCC->APB1RSTR |= (1 << 14);
		RCC->APB1RSTR &= ~(1 << 14);
	}
	else if(pSPIx == SPI3)
	{
		RCC->APB1RSTR |= (1 << 15);
		RCC->APB1RSTR &= ~(1 << 15);
	}
	else if(pSPIx == SPI4)
	{
		RCC->APB2RSTR |= (1 << 15);
		RCC->APB2RSTR &= ~(1 << 15);
	}

}


void __SPI_enable(SPI_Handle *pSPIx_h){

	pSPIx_h->pSPIx->CR1 |= (1 << SPI_CR1_SPE);
}


void __SPI_disable(SPI_Handle *pSPIx_h){

	pSPIx_h->pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
}


uint8_t __SPI_get_SRflag(SPI_Handle *pSPIx_h, uint8_t flag){

	if(pSPIx_h->pSPIx->SR & (1 << flag))
	{
		return TRUE;
	}
	return FALSE;
}


void __SPI_sendData(SPI_Handle *pSPIx_h, uint8_t *pTxBuf, int16_t Len){

	while(Len > 0){

		//wait until TX buffer is empty
		while(!__SPI_get_SRflag(pSPIx_h, SPI_SR_TXE));

		//Write into TXFIFO buffer
		if(pSPIx_h->pSPIx_conf.DataSize > SPI_DS_8BIT)
		{
			*((uint16_t *)&pSPIx_h->pSPIx->DR) = *((uint16_t *)pTxBuf);
			(uint16_t *)pTxBuf++;
			Len--;
			Len--;
		}
		else
		{
			*((uint8_t *)&pSPIx_h->pSPIx->DR) = *((uint8_t *)pTxBuf);
			(uint8_t *)pTxBuf++;
			Len--;
		}

	}

}


void __SPI_receiveData(SPI_Handle *pSPIx_h, uint8_t *pRxBuf, uint16_t Len){

	while(Len > 0){

		//wait until RX buffer is NOT empty
		while(!__SPI_get_SRflag(pSPIx_h, SPI_SR_RXNE));

		//Read RXFIFO buffer
		if(pSPIx_h->pSPIx_conf.DataSize > SPI_DS_8BIT)
		{
			*((uint16_t *)pRxBuf) = pSPIx_h->pSPIx->DR;
			(uint16_t *)pRxBuf++;
			Len--;
			Len--;
		}
		else
		{
			*((uint8_t *)pRxBuf) = pSPIx_h->pSPIx->DR;
			(uint8_t *)pRxBuf++;
			Len--;
		}

	}

}





void __SPI_IRQconfig(uint8_t IRQ, uint8_t EnOrDis, uint8_t Priority){

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
