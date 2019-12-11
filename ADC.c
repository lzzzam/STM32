/*
 * ADC.c
 *
 *  Created on: Dec 10, 2019
 *      Author: luca
 */
#include <stdio.h>
#include <STM32F303RE.h>
#include <ADC.h>

void __ADC1_Enable_VR(){

	//Voltage Reg. Enable Sequence
	ADC1->CR &= ~ADC1_CR_ADVREGEN_00; //Intermediate State
	ADC1->CR |=  ADC1_CR_ADVREGEN_EN; //Enable State

}

void __ADC1_Disable_VR(){

	//Voltage Reg. Disable Sequence
	ADC1->CR &= ~ADC1_CR_ADVREGEN_00; //Intermediate State
	ADC1->CR |=  ADC1_CR_ADVREGEN_DIS; //Disable State

}

void __ADC1_Enable(){

	ADC1->CR |= ADC1_CR_ADEN;

}

void __ADC1_Disable(){

	ADC1->CR |= ADC1_CR_ADDIS;

}

void __ADC1_Is_Ready(){

	while( !(ADC1->ISR & ADC1_ISR_ADRDY) );

}

void __ADC1_Conversion_Mode(ADC_CONV_MODE convmode){

	switch(convmode) {

	case ADC_SINGLE_CONV:
		ADC1->CFGR &= ~ADC1_CFGR_CONT;
		break;

	case ADC_CONT_CONV:
		ADC1->CFGR |= ADC1_CFGR_CONT;
		break;

	}

}

void __ADC1_Set_Sequence_Length(ADC_REG_SEQ_LENGTH seqlength){

	//Reset length to 0000
	ADC1->SQR1 &= ~(ADC1_SQR1_L_BIT3 |
			ADC1_SQR1_L_BIT2 |
			ADC1_SQR1_L_BIT1 |
			ADC1_SQR1_L_BIT0);

	//Set sequence length
	switch(seqlength){

	case ADC_1_CONV:
		//length to 0000
		break;

	case ADC_2_CONV:
		ADC1->SQR1 |= ADC1_SQR1_L_2_CONV;
		break;

	case ADC_3_CONV:
		ADC1->SQR1 |= ADC1_SQR1_L_3_CONV;
		break;

	case ADC_4_CONV:
		ADC1->SQR1 |= ADC1_SQR1_L_4_CONV;
		break;

	case ADC_5_CONV:
		ADC1->SQR1 |= ADC1_SQR1_L_5_CONV;
		break;

	case ADC_6_CONV:
		ADC1->SQR1 |= ADC1_SQR1_L_6_CONV;
		break;

	case ADC_7_CONV:
		ADC1->SQR1 |= ADC1_SQR1_L_7_CONV;
		break;

	case ADC_8_CONV:
		ADC1->SQR1 |= ADC1_SQR1_L_8_CONV;
		break;

	case ADC_9_CONV:
		ADC1->SQR1 |= ADC1_SQR1_L_9_CONV;
		break;

	case ADC_10_CONV:
		ADC1->SQR1 |= ADC1_SQR1_L_10_CONV;
		break;

	case ADC_11_CONV:
		ADC1->SQR1 |= ADC1_SQR1_L_11_CONV;
		break;

	case ADC_12_CONV:
		ADC1->SQR1 |= ADC1_SQR1_L_12_CONV;
		break;

	case ADC_13_CONV:
		ADC1->SQR1 |= ADC1_SQR1_L_13_CONV;
		break;

	case ADC_14_CONV:
		ADC1->SQR1 |= ADC1_SQR1_L_14_CONV;
		break;

	case ADC_15_CONV:
		ADC1->SQR1 |= ADC1_SQR1_L_15_CONV;
		break;
	case ADC_16_CONV:
		ADC1->SQR1 |= ADC1_SQR1_L_16_CONV;
		break;

	}
}

void __ADC1_Set_Sequence_1(ADC1_CHANNEL_NUM channel){

	//Reset channel to 00000
	ADC1->SQR1 &= ~(ADC1_SQR1_SQ1_BIT4 |
				    ADC1_SQR1_SQ1_BIT3 |
				    ADC1_SQR1_SQ1_BIT2 |
				    ADC1_SQR1_SQ1_BIT1 |
				    ADC1_SQR1_SQ1_BIT0);

	switch(channel) {
	case ADC1_IN1:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_IN1;
		break;

	case ADC1_IN2:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_IN2;
		break;

	case ADC1_IN3:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_IN3;
		break;

	case ADC1_IN4:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_IN4;
		break;

	case ADC1_IN5:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_IN5;
		break;

	case ADC1_IN6:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_IN6;
		break;

	case ADC1_IN7:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_IN7;
		break;

	case ADC1_IN8:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_IN8;
		break;

	case ADC1_IN9:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_IN9;
		break;

	case ADC1_IN10:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_IN10;
		break;

	case ADC1_IN11:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_IN11;
		break;

	case ADC1_IN12:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_IN12;
		break;

	case ADC1_IN13:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_IN13;
		break;

	case ADC1_VREF_POS:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_VREF_POS;
		break;

	case ADC1_VOPAMP1:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_VOPAMP1;
		break;

	case ADC1_V_TS:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_V_TS;
		break;

	case ADC1_VBAT_DIV_2:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_VBAT;
		break;

	case ADC1_VREF_INT:
		ADC1->SQR1 |= ADC1_SQR1_SQ1_VREF_INT;
		break;
	}

}

void __ADC1_StarConversion(){

	ADC1->CR |= ADC1_CR_ADSTART;

}

void __ADC1_Wait_End_Of_Conversion(){

	while( !(ADC1->ISR & ADC1_ISR_EOC) );

}

uint16_t __ADC1_Result_Of_Conversion(){

	return  (uint16_t)ADC1->DR;

}

void __ADC1_2_Set_ClockMode(ADC12_CKMODE ckmode){

	//Reset ClockMode to 00 --> ADC12_CLK from PLL
	ADC1_2->CCR &= ~(ADC1_2_CCR_CKMODE_BIT1 | ADC1_2_CCR_CKMODE_BIT0);


	switch (ckmode) {

	case ADC12_CK_ADC12:
		//ClockMode 00 --> ADC12_CLK from PLL
		break;

	case ADC12_HCLK_DIV_1:
		ADC1_2->CCR |= ADC1_2_CCR_CKMODE_BIT0;
		break;

	case ADC12_HCLK_DIV_2:
		ADC1_2->CCR |= ADC1_2_CCR_CKMODE_BIT1;
		break;

	case ADC12_HCLK_DIV_4:
		ADC1_2->CCR |= (ADC1_2_CCR_CKMODE_BIT1 | ADC1_2_CCR_CKMODE_BIT0);
		break;

	default:
		break;

	}

}

void __ADC1_2_Enable_TempSensor(){

	ADC1_2->CCR |= ADC1_2_CCR_TSEN;

}

void __ADC1_2_Enable_VRef_Internal(){

	ADC1_2->CCR |= ADC1_2_CCR_VREFEN;

}
