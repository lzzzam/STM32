/*
 * RCC.c
 *
 *  Created on: Dec 10, 2019
 *      Author: luca
 */
#include <stdio.h>
#include <STM32F303RE.h>
#include <RCC.h>

void __RCC_SetPrescaler_ADC12_CLK(ADC12_CLK_Prescaler val){

	//Reset ADC12PRES to 00000
	RCC->CFGR2 &= ~(RCC_CFGR2_ADC12PRES_BIT4 |
					RCC_CFGR2_ADC12PRES_BIT3 |
					RCC_CFGR2_ADC12PRES_BIT2 |
					RCC_CFGR2_ADC12PRES_BIT1 |
					RCC_CFGR2_ADC12PRES_BIT0);

	//Set Prescaler value
	switch (val) {
		case ADC12_CLK_DIS:
			RCC->CFGR2 &= ~RCC_CFGR2_ADC12PRES_CLK_EN;
			break;

		case ADC12_PRESCALER_1:
			RCC->CFGR2 |= RCC_CFGR2_ADC12PRES_1;
			break;

		case ADC12_PRESCALER_2:
			RCC->CFGR2 |= RCC_CFGR2_ADC12PRES_2;
			break;

		case ADC12_PRESCALER_4:
			RCC->CFGR2 |= RCC_CFGR2_ADC12PRES_4;
			break;

		case ADC12_PRESCALER_6:
			RCC->CFGR2 |= RCC_CFGR2_ADC12PRES_6;
			break;

		case ADC12_PRESCALER_8:
			RCC->CFGR2 |= RCC_CFGR2_ADC12PRES_8;
			break;

		case ADC12_PRESCALER_10:
			RCC->CFGR2 |= RCC_CFGR2_ADC12PRES_10;
			break;

		case ADC12_PRESCALER_12:
			RCC->CFGR2 |= RCC_CFGR2_ADC12PRES_12;
			break;

		case ADC12_PRESCALER_16:
			RCC->CFGR2 |= RCC_CFGR2_ADC12PRES_16;
			break;

		case ADC12_PRESCALER_32:
			RCC->CFGR2 |= RCC_CFGR2_ADC12PRES_32;
			break;

		case ADC12_PRESCALER_64:
			RCC->CFGR2 |= RCC_CFGR2_ADC12PRES_64;
			break;

		case ADC12_PRESCALER_128:
			RCC->CFGR2 |= RCC_CFGR2_ADC12PRES_128;
			break;

		case ADC12_PRESCALER_256:
			RCC->CFGR2 |= RCC_CFGR2_ADC12PRES_256;
			break;

		default:
			//Disable ADC12_CLK
			RCC->CFGR2 &= ~RCC_CFGR2_ADC12PRES_CLK_EN;
			break;
	}
}


void __RCC_PLL_Enable(){

	RCC->CR |= RCC_CR_PLL_ON;

}

void __RCC_PLL_Disable(){

	RCC->CR &= ~RCC_CR_PLL_ON;

}


void __RCC_PLL_Is_Ready(){

	while( !(RCC->CR & RCC_CR_PLL_RDY) );

}

void __RCC_Enable_ADC12(){

	RCC->AHBENR	|= RCC_AHBENR_ADC12EN;

}

uint32_t __RCC_getSYSCLK()
{
	uint32_t hsi = 8000000;
	uint32_t hse = 0;
	uint32_t sysclk;

	//Read Switch Status
	uint8_t sws = ((RCC->CFGR >> 2) & 0x3);

	if(sws == 0)//HSI
	{
		//SYSCLK equal to High Speed Internal oscillator
		sysclk = hsi;
	}
	else if(sws == 1)//HSE
	{
		//SYSCLK equal to High Speed External oscillator
		sysclk = hse;
	}
	else if(sws == 2)//PLL
	{
		uint8_t pllsrc = ((RCC->CFGR >> 15) & 0x3);	//read register flags
		uint8_t prediv = (RCC->CFGR2 & 0xF) + 1; 	//read register flags & compute PREDIV factor
		uint8_t pllmul = ((RCC->CFGR >> 18) & 0xF); //read register
		uint32_t pllclk;

		//compute PLL multiplication factor
		//from register configuration
		if(pllmul < 0xF)
			pllmul += 2;
		else if(pllmul == 0xF)
			pllmul += 1;

		if(pllsrc == 0)//HSI/2 and PREDIV = 2
		{
			pllclk = ((hsi/2)/2)*pllmul;
		}
		else if(pllsrc == 1)//HSI/2
		{
			pllclk = (hsi/prediv)*pllmul;
		}
		else if(pllsrc == 2)//HSE
		{
			pllclk = ((hse/2)/prediv)*pllmul;
		}

		//SYSCLK equal to PLL
		sysclk = pllclk;
	}

	return sysclk;
}

void __RCC_setSYSCLK(uint8_t sysclk)
{
	//Configure FLASH prefetch buffer latency in FLASH Interface
	if(sysclk <= SYSCLK_24MHZ)
	{
		//Zero Wait state
		FLITF->ACR &= ~(0xF << 0);
	}
	else if(sysclk <= SYSCLK_48MHZ)
	{
		//One Wait state
		FLITF->ACR |= (1 << 0);
	}
	else if(sysclk <= SYSCLK_72MHZ)
	{
		//Two Wait state
		FLITF->ACR |= (2 << 0);
	}


	//Set PLL source as HSI
	RCC->CFGR |= (1 << 15);

	//Set PLL PREDIV to 0
	RCC->CFGR2 &= ~(0xF << 0);

	//Set PLLMUL
	RCC->CFGR |= (sysclk << 18);

	//Turn on PLL
	RCC->CR |= (1 << 24);

	//wait until PLL is steady
	while(!((RCC->CR >> 25) & 0x1));

	//Set PLL as SYSCLK source
	RCC->CFGR |= (0x2 << 0);
}
