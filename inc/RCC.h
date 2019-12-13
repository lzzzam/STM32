/*
 * RCC.h
 *
 *  Created on: Dec 10, 2019
 *      Author: luca
 */

#ifndef RCC_H_
#define RCC_H_

typedef enum{
	ADC12_CLK_DIS,
	ADC12_PRESCALER_1,
	ADC12_PRESCALER_2,
	ADC12_PRESCALER_4,
	ADC12_PRESCALER_6,
	ADC12_PRESCALER_8,
	ADC12_PRESCALER_10,
	ADC12_PRESCALER_12,
	ADC12_PRESCALER_16,
	ADC12_PRESCALER_32,
	ADC12_PRESCALER_64,
	ADC12_PRESCALER_128,
	ADC12_PRESCALER_256
}ADC12_CLK_Prescaler;

void __RCC_SetPrescaler_ADC12_CLK(ADC12_CLK_Prescaler val);

void __RCC_PLL_Enable();

void __RCC_PLL_Disable();

void __RCC_PLL_Is_Ready();

void __RCC_Enable_ADC12();

#endif /* RCC_H_ */
