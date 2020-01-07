/*
 * I2S.c
 *
 *  Created on: 6 gen 2020
 *      Author: luca
 */
#include <I2S.h>


void __I2S_EnPCLK(I2S_t *pI2Sx)
{
	if(pI2Sx == I2S2)
	{
		RCC_EN_CLK_SPI2();
	}
	else if(pI2Sx == I2S3)
	{
		RCC_EN_CLK_SPI3();
	}
}


void __I2S_init(I2S_Handle *pI2Sx_h)
{
	//Enable peripheral clock
	__I2S_EnPCLK(pI2Sx_h->pI2Sx);

	//Reset Configuration registers
	pI2Sx_h->pI2Sx->I2SCFGR = 0;
	pI2Sx_h->pI2Sx->I2SPR = 0x0002;

	//Set I2S mode for SPI peripheral
	pI2Sx_h->pI2Sx->I2SCFGR |= (1 << SPI_I2SCFGR_I2SMOD);

	//Set Configuration Mode
	pI2Sx_h->pI2Sx->I2SCFGR |= (pI2Sx_h->pI2Sx_conf.Mode << SPI_I2SCFGR_I2SCFG);

	//Set Data Length
	pI2Sx_h->pI2Sx->I2SCFGR |= (pI2Sx_h->pI2Sx_conf.DataSize << SPI_I2SCFGR_DATLEN);

	//Set Channel Length
	pI2Sx_h->pI2Sx->I2SCFGR |= (pI2Sx_h->pI2Sx_conf.ChLen << SPI_I2SCFGR_CHLEN);

	//Set Clock Polarity
	pI2Sx_h->pI2Sx->I2SCFGR |= (pI2Sx_h->pI2Sx_conf.Cpol << SPI_I2SCFGR_CKPOL);

	//I2S Standard
	pI2Sx_h->pI2Sx->I2SCFGR |= (pI2Sx_h->pI2Sx_conf.Std << SPI_I2SCFGR_I2SSTD);

	//Set MCLK Output
	pI2Sx_h->pI2Sx->I2SPR |= (pI2Sx_h->pI2Sx_conf.MCLK << SPI_I2SPR_MCKOE);

	//Set Sample Frequency
	uint8_t i2sdiv;
	uint32_t sysclk = __RCC_getSYSCLK();
	//Compute prescaler
	if(pI2Sx_h->pI2Sx_conf.MCLK == I2S_MCLK_EN)//MCKOE is set
	{
		i2sdiv = (uint8_t)((sysclk/(256*pI2Sx_h->pI2Sx_conf.Fs)) - pI2Sx_h->pI2Sx_conf.Odd);
	}
	else//MCKOE is cleared
	{
		if(pI2Sx_h->pI2Sx_conf.DataSize > I2S_DS_16BIT)//channel frame is 32-bit
		{
			i2sdiv = (uint8_t)((sysclk/(64*pI2Sx_h->pI2Sx_conf.Fs)) - pI2Sx_h->pI2Sx_conf.Odd);
		}
		else
		{
			if(pI2Sx_h->pI2Sx_conf.ChLen == I2S_CHLEN_16BIT)//channel frame is 16-bit
			{
				i2sdiv = (uint8_t)((sysclk/(32*pI2Sx_h->pI2Sx_conf.Fs)) - pI2Sx_h->pI2Sx_conf.Odd);
			}
			else//channel frame is 32-bit
			{
				i2sdiv = (uint8_t)((sysclk/(64*pI2Sx_h->pI2Sx_conf.Fs)) - pI2Sx_h->pI2Sx_conf.Odd);
			}
		}
	}

	//Set prescaler value
	pI2Sx_h->pI2Sx->I2SPR |= (i2sdiv << SPI_I2SPR_I2SDIV);

}


void __I2S_reset(I2S_t *pI2Sx)
{
	if(pI2Sx == I2S2)//Reset SPI2
	{
		RCC->APB1RSTR |= (1 << 14);
		RCC->APB1RSTR &= ~(1 << 14);
	}
	else if(pI2Sx == I2S3)//Reset SPI3
	{
		RCC->APB1RSTR |= (1 << 15);
		RCC->APB1RSTR &= ~(1 << 15);
	}
}


void __I2S_enable(I2S_Handle *pI2Sx_h)
{
	pI2Sx_h->pI2Sx->I2SCFGR |= (1 << SPI_I2SCFGR_I2SE);
}


void __I2S_disable(I2S_Handle *pI2Sx_h)
{
	pI2Sx_h->pI2Sx->CR1 &= ~(1 << SPI_I2SCFGR_I2SE);
}

void __I2S_sendData(I2S_Handle *pI2Sx_h, uint16_t *pTxBuf_L, uint16_t *pTxBuf_R, uint32_t Len)
{
	//while(Len > 0){

		//wait until TX buffer is empty
		while(!__SPI_get_SRflag((SPI_Handle *) pI2Sx_h, SPI_SR_TXE));

		//Write into TXFIFO buffer
		*((uint16_t *)&pI2Sx_h->pI2Sx->DR) = *((uint16_t *)pTxBuf_L);

		//wait until TX buffer is empty
		while(!__SPI_get_SRflag((SPI_Handle *) pI2Sx_h, SPI_SR_TXE));

		*((uint16_t *)&pI2Sx_h->pI2Sx->DR) = *((uint16_t *)pTxBuf_R);

//		if(__SPI_get_SRflag((SPI_Handle *) pI2Sx_h, SPI_SR_CHSIDE) == FALSE)//transmit Left Channel
//		{
//			//Write into TXFIFO buffer
//			*((uint16_t *)&pI2Sx_h->pI2Sx->DR) = *((uint16_t *)pTxBuf_L);
//			(uint16_t *)pTxBuf_L++;
//			Len--;
//		}
//		else//transmit Right Channel
//		{
//			//Write into TXFIFO buffer
//			*((uint16_t *)&pI2Sx_h->pI2Sx->DR) = *((uint16_t *)pTxBuf_R);
//			(uint16_t *)pTxBuf_R++;
//			Len--;
//		}
//	}
}

void __I2S_receiveData(I2S_Handle *pI2Sx_h, uint16_t *pRxBuf_L, uint16_t *pRxBuf_R, uint32_t Len)
{
	while(Len > 0){

		//wait until RX buffer is NOT empty
		while(!__SPI_get_SRflag((SPI_Handle *) pI2Sx_h, SPI_SR_RXNE));

		if(__SPI_get_SRflag((SPI_Handle *) pI2Sx_h, SPI_SR_CHSIDE) == FALSE)//receive Left Channel
		{
			//Read RXFIFO buffer
			*((uint16_t *)pRxBuf_L) = *((uint16_t *)&pI2Sx_h->pI2Sx->DR);
			(uint16_t *)pRxBuf_L++;
			Len--;
		}
		else//receive Right Channel
		{
			//Read RXFIFO buffer
			*((uint16_t *)pRxBuf_R) = *((uint16_t *)&pI2Sx_h->pI2Sx->DR);
			(uint16_t *)pRxBuf_R++;
			Len--;
		}
	}
}

void __I2S_IRQconfig(I2S_Handle *pI2Sx_h, uint8_t EnOrDis, uint8_t Priority)
{
	uint8_t IRQ = SPI_IRQ_NUM(pI2Sx_h->pI2Sx);
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

void __I2S_IRQhandle(I2S_Handle *pI2Sx_h)
{

}

__weak void __I2S_AppEventCallback(I2S_Handle *pI2Sx_h, uint8_t AppEv)
{
	//define in Application code
}
