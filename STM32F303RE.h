#ifndef __STM32F303_DEVICE_HEADER__

#define __STM32F303_DEVICE_HEADER__

#define __IO	volatile

/********************************************************************************/
/*						Bit access 												*/
/********************************************************************************/
#define BIT0	(1 <<  0)
#define BIT1	(1 <<  1)
#define BIT2	(1 <<  2)
#define BIT3	(1 <<  3)
#define BIT4	(1 <<  4)
#define BIT5	(1 <<  5)
#define BIT6	(1 <<  6)
#define BIT7	(1 <<  7)
#define BIT8	(1 <<  8)
#define BIT9	(1 <<  9)
#define BIT10	(1 << 10)
#define BIT11	(1 << 11)
#define BIT12	(1 << 12)
#define BIT13	(1 << 13)
#define BIT14	(1 << 14)
#define BIT15	(1 << 15)
#define BIT16	(1 << 16)
#define BIT17	(1 << 17)
#define BIT18	(1 << 18)
#define BIT19	(1 << 19)
#define BIT20	(1 << 20)
#define BIT21	(1 << 21)
#define BIT22	(1 << 22)
#define BIT23	(1 << 23)
#define BIT24	(1 << 24)
#define BIT25	(1 << 25)
#define BIT26	(1 << 26)
#define BIT27	(1 << 27)
#define BIT28	(1 << 28)
#define BIT29	(1 << 29)
#define BIT30	(1 << 30)
#define BIT31	(1 << 31)


/*********RCC Peripheral***********/
#define RCC_CR_PLL_ON				 BIT24
#define RCC_CR_PLL_RDY				 BIT25

#define RCC_CFGR2_ADC12PRES_BIT0	 BIT4
#define RCC_CFGR2_ADC12PRES_BIT1	 BIT5
#define RCC_CFGR2_ADC12PRES_BIT2	 BIT6
#define RCC_CFGR2_ADC12PRES_BIT3	 BIT7
#define RCC_CFGR2_ADC12PRES_BIT4	 BIT8
#define RCC_CFGR2_ADC12PRES_CLK_EN	 BIT8
#define RCC_CFGR2_ADC12PRES_1		 RCC_CFGR2_ADC12PRES_CLK_EN
#define RCC_CFGR2_ADC12PRES_2		(RCC_CFGR2_ADC12PRES_CLK_EN | BIT4)
#define RCC_CFGR2_ADC12PRES_4		(RCC_CFGR2_ADC12PRES_CLK_EN | BIT5)
#define RCC_CFGR2_ADC12PRES_6		(RCC_CFGR2_ADC12PRES_CLK_EN | BIT5 | BIT4)
#define RCC_CFGR2_ADC12PRES_8		(RCC_CFGR2_ADC12PRES_CLK_EN | BIT6)
#define RCC_CFGR2_ADC12PRES_10		(RCC_CFGR2_ADC12PRES_CLK_EN | BIT6 | BIT4)
#define RCC_CFGR2_ADC12PRES_12		(RCC_CFGR2_ADC12PRES_CLK_EN | BIT6 | BIT5)
#define RCC_CFGR2_ADC12PRES_16		(RCC_CFGR2_ADC12PRES_CLK_EN | BIT6 | BIT5 | BIT4)
#define RCC_CFGR2_ADC12PRES_32		(RCC_CFGR2_ADC12PRES_CLK_EN | BIT7)
#define RCC_CFGR2_ADC12PRES_64		(RCC_CFGR2_ADC12PRES_CLK_EN | BIT7 | BIT4)
#define RCC_CFGR2_ADC12PRES_128		(RCC_CFGR2_ADC12PRES_CLK_EN | BIT7 | BIT5)
#define RCC_CFGR2_ADC12PRES_256		(RCC_CFGR2_ADC12PRES_CLK_EN | BIT7 | BIT5 | BIT4)

#define RCC_AHBENR_ADC12EN			 BIT28
#define RCC_AHBENR_ADC34EN			 BIT29

/*********ADC Peripheral***********/
#define ADC1_ISR_ADRDY				 BIT0
#define ADC1_ISR_EOSMP				 BIT1
#define ADC1_ISR_EOC				 BIT2
#define ADC1_ISR_EOS				 BIT3
#define ADC1_ISR_OVR				 BIT4
#define ADC1_ISR_AWD1				 BIT7
#define ADC1_ISR_AWD2				 BIT8
#define ADC1_ISR_AWD3				 BIT9

#define ADC1_CFGR_CONT				 BIT13

#define ADC1_SQR1_L_BIT0			 BIT0
#define ADC1_SQR1_L_BIT1			 BIT1
#define ADC1_SQR1_L_BIT2			 BIT2
#define ADC1_SQR1_L_BIT3			 BIT3
#define ADC1_SQR1_L_2_CONV			 BIT0
#define ADC1_SQR1_L_3_CONV			 BIT1
#define ADC1_SQR1_L_4_CONV			(BIT1 | BIT0)
#define ADC1_SQR1_L_5_CONV			 BIT2
#define ADC1_SQR1_L_6_CONV			(BIT2 | BIT0)
#define ADC1_SQR1_L_7_CONV			(BIT2 | BIT1)
#define ADC1_SQR1_L_8_CONV			(BIT2 | BIT1 | BIT0)
#define ADC1_SQR1_L_9_CONV			 BIT3
#define ADC1_SQR1_L_10_CONV			(BIT3 | BIT0)
#define ADC1_SQR1_L_11_CONV			(BIT3 | BIT1)
#define ADC1_SQR1_L_12_CONV			(BIT3 | BIT1 | BIT0)
#define ADC1_SQR1_L_13_CONV			(BIT3 | BIT2)
#define ADC1_SQR1_L_14_CONV			(BIT3 | BIT2 | BIT0)
#define ADC1_SQR1_L_15_CONV			(BIT3 | BIT2 | BIT1)
#define ADC1_SQR1_L_16_CONV			(BIT3 | BIT2 | BIT1 | BIT0)
#define ADC1_SQR1_SQ1_BIT0			 BIT6
#define ADC1_SQR1_SQ1_BIT1			 BIT7
#define ADC1_SQR1_SQ1_BIT2			 BIT8
#define ADC1_SQR1_SQ1_BIT3			 BIT9
#define ADC1_SQR1_SQ1_BIT4			 BIT10
#define ADC1_SQR1_SQ1_IN1			 BIT6
#define ADC1_SQR1_SQ1_IN2			 BIT7
#define ADC1_SQR1_SQ1_IN3			(BIT7 | BIT6)
#define ADC1_SQR1_SQ1_IN4			 BIT8
#define ADC1_SQR1_SQ1_IN5			(BIT8 | BIT6)
#define ADC1_SQR1_SQ1_IN6			(BIT8 | BIT7)
#define ADC1_SQR1_SQ1_IN7			(BIT8 | BIT7 | BIT6)
#define ADC1_SQR1_SQ1_IN8			 BIT9
#define ADC1_SQR1_SQ1_IN9			(BIT9 | BIT6)
#define ADC1_SQR1_SQ1_IN10			(BIT9 | BIT7)
#define ADC1_SQR1_SQ1_IN11			(BIT9 | BIT7 | BIT6)
#define ADC1_SQR1_SQ1_IN12			(BIT9 | BIT8)
#define ADC1_SQR1_SQ1_IN13			(BIT9 | BIT8 | BIT6)
#define ADC1_SQR1_SQ1_VREF_POS		(BIT9 | BIT8 | BIT7)
#define ADC1_SQR1_SQ1_VOPAMP1		(BIT9 | BIT8 | BIT7 | BIT6)
#define ADC1_SQR1_SQ1_V_TS		 	 BIT10
#define ADC1_SQR1_SQ1_VBAT			(BIT10 | BIT6)
#define ADC1_SQR1_SQ1_VREF_INT		(BIT10 | BIT7)


#define ADC1_CR_ADEN				 BIT0
#define ADC1_CR_ADDIS				 BIT1
#define ADC1_CR_ADSTART				 BIT2
#define ADC1_CR_ADVREGEN_00			(BIT29 | BIT28)
#define ADC1_CR_ADVREGEN_EN			 BIT28
#define ADC1_CR_ADVREGEN_DIS		 BIT29

#define ADC1_2_CCR_CKMODE_BIT0		 BIT16
#define ADC1_2_CCR_CKMODE_BIT1		 BIT17
#define ADC1_2_CCR_TSEN				 BIT23
#define ADC1_2_CCR_VREFEN			 BIT22

/********************************************************************************/
/*						Peripheral addresses									*/
/********************************************************************************/
//Peripheral base addresses
#define RCC_BASE_ADDR			0x40021000UL
#define ADC12_BASE_ADDR			0x50000000UL
#define ADC34_BASE_ADDR			0x50000400UL

//Peripheral address offset
#define RCC_OFFSET				0x00000000UL
#define ADC_MASTER_OFFSET		0x00000000UL
#define ADC_SLAVE_OFFSET		0x00000100UL
#define ADC_COMM_OFFSET			0x00000300UL

//Peripheral address
#define RCC_ADDR				(RCC_BASE_ADDR + RCC_OFFSET)
#define ADC1_ADDR				(ADC12_BASE_ADDR + ADC_MASTER_OFFSET)
#define ADC2_ADDR				(ADC12_BASE_ADDR + ADC_SLAVE_OFFSET)
#define ADC3_ADDR				(ADC34_BASE_ADDR + ADC_MASTER_OFFSET)
#define ADC4_ADDR				(ADC34_BASE_ADDR + ADC_SLAVE_OFFSET)
#define ADC12_COMM_ADDR			(ADC12_BASE_ADDR + ADC_COMM_OFFSET)
#define ADC34_COMM_ADDR			(ADC34_BASE_ADDR + ADC_COMM_OFFSET)


/********************************************************************************/
/*						Peripheral access method								*/
/********************************************************************************/
#define RCC		((RCC_t *)RCC_ADDR)
#define ADC1	((ADC_t *)ADC1_ADDR)
#define ADC2	((ADC_t *)ADC2_ADDR)
#define ADC3	((ADC_t *)ADC3_ADDR)
#define ADC4	((ADC_t *)ADC4_ADDR)
#define ADC1_2	((ADC_common_t *)ADC12_COMM_ADDR)
#define ADC3_4	((ADC_common_t *)ADC34_COMM_ADDR)

/********************************************************************************/
/*						Peripheral structure overlay							*/
/********************************************************************************/

//Reset and Clock Control
typedef struct {
	__IO uint32_t 	CR;
	__IO uint32_t	CFGR;
	__IO uint32_t	CIR;
	__IO uint32_t	APB2RSTR;
	__IO uint32_t	APB1RSTR;
	__IO uint32_t	AHBENR;
	__IO uint32_t	APB2ENR;
	__IO uint32_t	APB1ENR;
	__IO uint32_t	BDCR;
	__IO uint32_t	CSR;
	__IO uint32_t	AHBRSTR;
	__IO uint32_t	CFGR2;
	__IO uint32_t	CFGR3;
}RCC_t;

//ADC
typedef struct {
	__IO uint32_t 	ISR;
	__IO uint32_t	IER;
	__IO uint32_t	CR;
	__IO uint32_t	CFGR;
		 uint32_t	RESERVED_01;
	__IO uint32_t	SMPR1;
	__IO uint32_t	SMPR2;
		 uint32_t	RESERVED_02;
	__IO uint32_t	TR1;
	__IO uint32_t	TR2;
	__IO uint32_t	TR3;
		 uint32_t	RESERVED_03;
	__IO uint32_t	SQR1;
	__IO uint32_t	SQR2;
	__IO uint32_t	SQR3;
	__IO uint32_t	SQR4;
	__IO uint32_t	DR;
		 uint32_t	RESERVED_04;
		 uint32_t	RESERVED_05;
	__IO uint32_t	JSQR;
	 	 uint32_t	RESERVED_06;
	 	 uint32_t	RESERVED_07;
	 	 uint32_t	RESERVED_08;
	 	 uint32_t	RESERVED_09;
	__IO uint32_t	OFR1;
	__IO uint32_t	OFR2;
	__IO uint32_t	OFR3;
	__IO uint32_t	OFR4;
	 	 uint32_t	RESERVED_10;
	 	 uint32_t	RESERVED_11;
	 	 uint32_t	RESERVED_12;
	 	 uint32_t	RESERVED_13;
	__IO uint32_t	JDR1;
	__IO uint32_t	JDR2;
	__IO uint32_t	JDR3;
	__IO uint32_t	JDR4;
	 	 uint32_t	RESERVED_14;
	 	 uint32_t	RESERVED_15;
	 	 uint32_t	RESERVED_16;
	 	 uint32_t	RESERVED_17;
	__IO uint32_t	AWD2CR;
	__IO uint32_t	AWD3CR;
	 	 uint32_t	RESERVED_18;
	 	 uint32_t	RESERVED_19;
	__IO uint32_t	DIFSEL;
	__IO uint32_t	CALFACT;
}ADC_t;


//ADC common registers
typedef struct{
	__IO uint32_t	CSR;
		 uint32_t	RESERVED_01;
	__IO uint32_t	CCR;
	__IO uint32_t	CDR;
}ADC_common_t;

#endif
