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
	uint32_t sysclk = 8000000;
	//Compute prescaler
	if(pI2Sx_h->pI2Sx_conf.MCLK == I2S_MCLK_EN)
	{
		if(pI2Sx_h->pI2Sx_conf.DataSize > I2S_DS_16BIT)
		{
			i2sdiv = (uint8_t)(sysclk/(512*pI2Sx_h->pI2Sx_conf.Fs));
		}
		else
		{
			i2sdiv = (uint8_t)(sysclk/(512*pI2Sx_h->pI2Sx_conf.Fs));
		}
	}
	else
	{
		if(pI2Sx_h->pI2Sx_conf.DataSize > I2S_DS_16BIT)
		{
			i2sdiv = (uint8_t)(sysclk/(128*pI2Sx_h->pI2Sx_conf.Fs));
		}
		else
		{
			i2sdiv = (uint8_t)(sysclk/(64*pI2Sx_h->pI2Sx_conf.Fs));
		}
	}
	//Set prescaler value
	pI2Sx_h->pI2Sx->I2SPR |= (i2sdiv << SPI_I2SPR_I2SDIV);

}


void __I2S_reset(I2S_t *pI2Sx)
{
	if(pI2Sx == I2S2)
	{
		RCC->APB1RSTR |= (1 << 14);
		RCC->APB1RSTR &= ~(1 << 14);
	}
	else if(pI2Sx == I2S3)
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
