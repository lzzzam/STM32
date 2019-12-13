/*
 * ADC.h
 *
 *  Created on: Dec 10, 2019
 *      Author: luca
 */

#ifndef ADC_H_
#define ADC_H_

typedef enum{
	ADC_SINGLE_CONV,
	ADC_CONT_CONV
}ADC_CONV_MODE;

typedef enum{
	ADC_1_CONV,
	ADC_2_CONV,
	ADC_3_CONV,
	ADC_4_CONV,
	ADC_5_CONV,
	ADC_6_CONV,
	ADC_7_CONV,
	ADC_8_CONV,
	ADC_9_CONV,
	ADC_10_CONV,
	ADC_11_CONV,
	ADC_12_CONV,
	ADC_13_CONV,
	ADC_14_CONV,
	ADC_15_CONV,
	ADC_16_CONV
}ADC_REG_SEQ_LENGTH;

typedef enum{
	ADC1_IN1,
	ADC1_IN2,
	ADC1_IN3,
	ADC1_IN4,
	ADC1_IN5,
	ADC1_IN6,
	ADC1_IN7,
	ADC1_IN8,
	ADC1_IN9,
	ADC1_IN10,
	ADC1_IN11,
	ADC1_IN12,
	ADC1_IN13,
	ADC1_VREF_POS,
	ADC1_VOPAMP1,
	ADC1_V_TS,
	ADC1_VBAT_DIV_2,
	ADC1_VREF_INT
}ADC1_CHANNEL_NUM;

typedef enum{
	ADC12_CK_ADC12,
	ADC12_HCLK_DIV_1,
	ADC12_HCLK_DIV_2,
	ADC12_HCLK_DIV_4
}ADC12_CKMODE;

void __ADC1_Enable_VR();

void __ADC1_Disable_VR();

void __ADC1_Enable();

void __ADC1_Disable();

void __ADC1_Is_Ready();

void __ADC1_Conversion_Mode(ADC_CONV_MODE convmode);

void __ADC1_Set_Sequence_Length(ADC_REG_SEQ_LENGTH seqlength);

void __ADC1_Set_Sequence_1(ADC1_CHANNEL_NUM channel);

void __ADC1_StarConversion();

void __ADC1_Wait_End_Of_Conversion();

uint16_t __ADC1_Result_Of_Conversion();

void __ADC1_2_Set_ClockMode(ADC12_CKMODE ckmode);

void __ADC1_2_Enable_TempSensor();

void __ADC1_2_Enable_VRef_Internal();

#endif /* ADC_H_ */
