/*
 * RCC.h
 *
 *  Created on: Dec 10, 2019
 *      Author: luca
 */

#ifndef RCC_H_
#define RCC_H_

//@SYSCLK_FREQ
#define SYSCLK_16MHZ	0
#define SYSCLK_24MHZ	1
#define SYSCLK_32MHZ	2
#define SYSCLK_40MHZ	3
#define SYSCLK_48MHZ	4
#define SYSCLK_56MHZ	5
#define SYSCLK_64MHZ	6
#define SYSCLK_72MHZ	7

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

void __RCC_PLL_Enable(void);

void __RCC_PLL_Disable(void);

void __RCC_PLL_Is_Ready(void);

void __RCC_Enable_ADC12(void);

uint32_t __RCC_getSYSCLK(void);

void __RCC_setSYSCLK(uint8_t sysclk);	//@SYSCLK_FREQ

#endif /* RCC_H_ */
