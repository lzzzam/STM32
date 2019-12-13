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
