#ifndef __STM32F303_DEVICE_HEADER__

#define __STM32F303_DEVICE_HEADER__

#include <stdio.h>

#define NULL 	((void *)0)
#define __IO	volatile
#define __weak  __attribute__((weak))
#define TRUE	1
#define FALSE	0
#define EN		TRUE
#define DIS		FALSE

/********************************************************************************/
/*						Cortex-M4 CORE											*/
/********************************************************************************/
#define NUM_PRIORITY_BITS 4

//EXTIx's IRQ Position for the NVIC
#define EXTI0_IRQ_NUM				6
#define EXTI1_IRQ_NUM				7
#define EXTI2_IRQ_NUM				8
#define EXTI3_IRQ_NUM				9
#define EXTI4_IRQ_NUM				10
#define EXTI9_5_IRQ_NUM				23
#define EXTI15_10_IRQ_NUM			40
//SPIx's IRQ Position for the NVIC
#define SPI1_IRQ_NUM				35
#define SPI2_IRQ_NUM				36
#define SPI3_IRQ_NUM				51
#define SPI4_IRQ_NUM				84
//I2Cx's IRQ Position for the NVIC
#define I2C1_IRQ_NUM				31
#define I2C2_IRQ_NUM				33
#define I2C3_IRQ_NUM				72

//NVIC Control Register
#define NVIC_ISER0			*((volatile uint32_t *)0xE000E100U)
#define NVIC_ISER1			*((volatile uint32_t *)0xE000E104U)
#define NVIC_ISER2			*((volatile uint32_t *)0xE000E108U)
#define NVIC_ICER0			*((volatile uint32_t *)0xE000E180U)
#define NVIC_ICER1			*((volatile uint32_t *)0xE000E184U)
#define NVIC_ICER2			*((volatile uint32_t *)0xE000E188U)
#define NVIC_IPR			 ((volatile uint32_t *)0xE000E400U)
#define NVIC_STIR			*((volatile uint32_t *)0xE000EF00U)
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

//Enable Peripheral clock
#define RCC_EN_CLK_GPIOA()			(RCC->AHBENR |= (1 << 17))
#define RCC_EN_CLK_GPIOB()			(RCC->AHBENR |= (1 << 18))
#define RCC_EN_CLK_GPIOC()			(RCC->AHBENR |= (1 << 19))
#define RCC_EN_CLK_GPIOD()			(RCC->AHBENR |= (1 << 20))
#define RCC_EN_CLK_GPIOE()			(RCC->AHBENR |= (1 << 21))
#define RCC_EN_CLK_GPIOF()			(RCC->AHBENR |= (1 << 22))
#define RCC_EN_CLK_GPIOG()			(RCC->AHBENR |= (1 << 23))
#define RCC_EN_CLK_GPIOH()			(RCC->AHBENR |= (1 << 16))
#define RCC_EN_CLK_ADC12()			(RCC->AHBENR |= (1 << 28))
#define RCC_EN_CLK_ADC34()			(RCC->AHBENR |= (1 << 29))
#define RCC_EN_CLK_SPI1()			(RCC->APB2ENR |= (1 << 12))
#define RCC_EN_CLK_SPI2()			(RCC->APB1ENR |= (1 << 14))
#define RCC_EN_CLK_SPI3()			(RCC->APB1ENR |= (1 << 15))
#define RCC_EN_CLK_SPI4()			(RCC->APB2ENR |= (1 << 15))
#define RCC_EN_CLK_I2C1()			(RCC->APB1ENR |= (1 << 21))
#define RCC_EN_CLK_I2C2()			(RCC->APB1ENR |= (1 << 22))
#define RCC_EN_CLK_I2C3()			(RCC->APB1ENR |= (1 << 30))


/*********GPIOx Peripheral***********/
//@GPIO_PinMode
#define GPIO_MODE_IN				0
#define GPIO_MODE_OUT				1
#define GPIO_MODE_AF				2
#define GPIO_MODE_AN				3
#define GPIO_MODE_INT_R				4
#define GPIO_MODE_INT_F				5
#define GPIO_MODE_INT_RF			6
//@GPIO_PinType
#define GPIO_OTYPE_PP				0
#define GPIO_OTYPE_OD				1
//@GPIO_PinSpeed
#define GPIO_SPEED_LOW				0
#define GPIO_SPEED_MED				1
#define GPIO_SPEED_HIGH				3
//@GPIO_PinPuPd
#define GPIO_NO_PUPD				0
#define GPIO_PULL_UP				1
#define GPIO_PULL_DOWN				2
//@GPIO_PinAltFnc
#define GPIO_ALT_FNC_0				0
#define GPIO_ALT_FNC_1				1
#define GPIO_ALT_FNC_2				2
#define GPIO_ALT_FNC_3				3
#define GPIO_ALT_FNC_4				4
#define GPIO_ALT_FNC_5				5
#define GPIO_ALT_FNC_6				6
#define GPIO_ALT_FNC_7				7
#define GPIO_ALT_FNC_8				8
#define GPIO_ALT_FNC_9				9
#define GPIO_ALT_FNC_10				10
#define GPIO_ALT_FNC_11				11
#define GPIO_ALT_FNC_12				12
#define GPIO_ALT_FNC_13				13
#define GPIO_ALT_FNC_14				14
#define GPIO_ALT_FNC_15				15

/*********USARTx/UARTx Peripheral***********/
#define USART_CR1_UE_Pos			0
#define USART_CR1_UESM_Pos			1
#define USART_CR1_RE_Pos			2
#define USART_CR1_TE_Pos			3
#define USART_CR1_IDLEIE_Pos		4
#define USART_CR1_RXNEIE_Pos		5
#define USART_CR1_TCIE_Pos			6
#define USART_CR1_TXEIE_Pos			7
#define USART_CR1_PEIE_Pos			8
#define USART_CR1_PS_Pos			9
#define USART_CR1_PCE_Pos			10
#define USART_CR1_WAKE_Pos			11
#define USART_CR1_M0_Pos			12
#define USART_CR1_MME_Pos			13
#define USART_CR1_CMIE_Pos			14
#define USART_CR1_OVER8_Pos			15
#define USART_CR1_DEDT_Pos			16
#define USART_CR1_DEAT_Pos			21
#define USART_CR1_RTOIE_Pos			26
#define USART_CR1_EOBIE_Pos			27
#define USART_CR1_M1_Pos			28

#define USART_CR1_UE_Msk			(0x01 << USART_CR1_UE_Pos)
#define USART_CR1_UESM_Msk			(0x01 << USART_CR1_UESM_Pos)
#define USART_CR1_RE_Msk			(0x01 << USART_CR1_RE_Pos)
#define USART_CR1_TE_Msk			(0x01 << USART_CR1_TE_Pos)
#define USART_CR1_IDLEIE_Msk		(0x01 << USART_CR1_IDLEIE_Pos)
#define USART_CR1_RXNEIE_Msk		(0x01 << USART_CR1_RXNEIE_Pos)
#define USART_CR1_TCIE_Msk			(0x01 << USART_CR1_TCIE_Pos)
#define USART_CR1_TXEIE_Msk			(0x01 << USART_CR1_TXEIE_Pos)
#define USART_CR1_PEIE_Msk			(0x01 << USART_CR1_PEIE_Pos)
#define USART_CR1_PS_Msk			(0x01 << USART_CR1_PS_Pos)
#define USART_CR1_PCE_Msk			(0x01 << USART_CR1_PCE_Pos)
#define USART_CR1_WAKE_Msk			(0x01 << USART_CR1_WAKE_Pos)
#define USART_CR1_M0_Msk			(0x01 << USART_CR1_M0_Pos)
#define USART_CR1_MME_Msk			(0x01 << USART_CR1_MME_Pos)
#define USART_CR1_CMIE_Msk			(0x01 << USART_CR1_CMIE_Pos)
#define USART_CR1_OVER8_Msk			(0x01 << USART_CR1_OVER8_Pos)
#define USART_CR1_DEDT_Msk			(0x1F << USART_CR1_DEDT_Pos)
#define USART_CR1_DEAT_Msk			(0x1F << USART_CR1_DEAT_Pos)
#define USART_CR1_RTOIE_Msk			(0x01 << USART_CR1_RTOIE_Pos)
#define USART_CR1_EOBIE_Msk			(0x01 << USART_CR1_EOBIE_Pos)
#define USART_CR1_M1_Msk			(0x01 << USART_CR1_M1_Pos)

#define USART_CR2_ADDM7_Pos			4
#define USART_CR2_LBDL_Pos			5
#define USART_CR2_LBDIE_Pos			6
#define USART_CR2_LBCL_Pos			8
#define USART_CR2_CPHA_Pos			9
#define USART_CR2_CPOL_Pos			10
#define USART_CR2_CLKEN_Pos			11
#define USART_CR2_STOP_Pos			12
#define USART_CR2_LINEN_Pos			14
#define USART_CR2_SWAP_Pos			15
#define USART_CR2_RXINV_Pos			16
#define USART_CR2_TXINV_Pos			17
#define USART_CR2_DATAINV_Pos		18
#define USART_CR2_MSBFIRST_Pos		19
#define USART_CR2_ABREN_Pos			20
#define USART_CR2_ABRMOD_Pos		21
#define USART_CR2_RTOEN_Pos			23
#define USART_CR2_ADD_Pos			24

#define USART_CR2_ADDM7_Msk			(0x01 << USART_CR2_ADDM7_Pos)
#define USART_CR2_LBDL_Msk			(0x01 << USART_CR2_LBDL_Pos)
#define USART_CR2_LBDIE_Msk			(0x01 << USART_CR2_LBDIE_Pos)
#define USART_CR2_LBCL_Msk			(0x01 << USART_CR2_LBCL_Pos)
#define USART_CR2_CPHA_Msk			(0x01 << USART_CR2_CPHA_Pos)
#define USART_CR2_CPOL_Msk			(0x01 << USART_CR2_CPOL_Pos)
#define USART_CR2_CLKEN_Msk			(0x01 << USART_CR2_CLKEN_Pos)
#define USART_CR2_STOP_Msk			(0x03 << USART_CR2_STOP_Pos)
#define USART_CR2_LINEN_Msk			(0x01 << USART_CR2_LINEN_Pos)
#define USART_CR2_SWAP_Msk			(0x01 << USART_CR2_SWAP_Pos)
#define USART_CR2_RXINV_Msk			(0x01 << USART_CR2_RXINV_Pos)
#define USART_CR2_TXINV_Msk			(0x01 << USART_CR2_TXINV_Pos)
#define USART_CR2_DATAINV_Msk		(0x01 << USART_CR2_DATAINV_Pos)
#define USART_CR2_MSBFIRST_Msk		(0x01 << USART_CR2_MSBFIRST_Pos)
#define USART_CR2_ABREN_Msk			(0x01 << USART_CR2_ABREN_Pos)
#define USART_CR2_ABRMOD_Msk		(0x03 << USART_CR2_ABRMOD_Pos)
#define USART_CR2_RTOEN_Msk			(0x01 << USART_CR2_RTOEN_Pos)
#define USART_CR2_ADD_Msk			(0x0F << USART_CR2_ADD_Pos)

#define USART_CR3_EIE_Pos			0
#define USART_CR3_IREN_Pos			1
#define USART_CR3_IRLP_Pos			2
#define USART_CR3_HDSEL_Pos			3
#define USART_CR3_NACK_Pos			4
#define USART_CR3_SCEN_Pos			5
#define USART_CR3_DMAR_Pos			6
#define USART_CR3_DMAT_Pos			7
#define USART_CR3_RTSE_Pos			8
#define USART_CR3_CTSE_Pos			9
#define USART_CR3_CTSIE_Pos			10
#define USART_CR3_ONEBIT_Pos		11
#define USART_CR3_OVRDIS_Pos		12
#define USART_CR3_DDRE_Pos			13
#define USART_CR3_DEM_Pos			14
#define USART_CR3_DEP_Pos			15
#define USART_CR3_SCARCNT_Pos		17
#define USART_CR3_WUS_Pos			20
#define USART_CR3_WUFIE_Pos			21

#define USART_CR3_EIE_Msk			(0x01 << USART_CR3_EIE_Pos)
#define USART_CR3_IREN_Msk			(0x01 << USART_CR3_IREN_Pos)
#define USART_CR3_IRLP_Msk			(0x01 << USART_CR3_IRLP_Pos)
#define USART_CR3_HDSEL_Msk			(0x01 << USART_CR3_HDSEL_Pos)
#define USART_CR3_NACK_Msk			(0x01 << USART_CR3_NACK_Pos)
#define USART_CR3_SCEN_Msk			(0x01 << USART_CR3_SCEN_Pos)
#define USART_CR3_DMAR_Msk			(0x01 << USART_CR3_DMAR_Pos)
#define USART_CR3_DMAT_Msk			(0x01 << USART_CR3_DMAT_Pos)
#define USART_CR3_RTSE_Msk			(0x01 << USART_CR3_RTSE_Pos)
#define USART_CR3_CTSE_Msk			(0x01 << USART_CR3_CTSE_Pos)
#define USART_CR3_CTSIE_Msk			(0x01 << USART_CR3_CTSIE_Pos)
#define USART_CR3_ONEBIT_Msk		(0x01 << USART_CR3_ONEBIT_Pos)
#define USART_CR3_OVRDIS_Msk		(0x01 << USART_CR3_OVRDIS_Pos)
#define USART_CR3_DDRE_Msk			(0x01 << USART_CR3_DDRE_Pos)
#define USART_CR3_DEM_Msk			(0x01 << USART_CR3_DEM_Pos)
#define USART_CR3_DEP_Msk			(0x01 << USART_CR3_DEP_Pos)
#define USART_CR3_SCARCNT_Msk		(0x07 << USART_CR3_SCARCNT_Pos)
#define USART_CR3_WUS_Msk			(0x03 << USART_CR3_WUS_Pos)
#define USART_CR3_WUFIE_Msk			(0x01 << USART_CR3_WUFIE_Pos)

#define USART_BRR_BRR_Pos			0
#define USART_BRR_BRR_Msk			(0xFFFF << USART_BRR_BRR_Pos)

#define USART_GTPR_PSC_Pos			0
#define USART_GTPR_GT_Pos			8

#define USART_GTPR_PSC_Msk			(0xFF << USART_GTPR_PSC_Pos)
#define USART_GTPR_GT_Msk			(0xFF << USART_GTPR_GT_Pos)

#define USART_RTOR_RTO_Pos			0
#define USART_RTOR_BLEN_Pos			24

#define USART_RTOR_RTO_Msk			(0x00FFFFFF << USART_RTOR_RTO_Pos)
#define USART_RTOR_BLEN_Msk			(0xFF << USART_RTOR_BLEN_Pos)

#define USART_RQR_ABRRQ_Pos			0
#define USART_RQR_SBKRQ_Pos			1
#define USART_RQR_MMRQ_Pos			2
#define USART_RQR_RXFRQ_Pos			3
#define USART_RQR_TXFRQ_Pos			4

#define USART_RQR_ABRRQ_Msk			(0x01 << USART_RQR_ABRRQ_Pos)
#define USART_RQR_SBKRQ_Msk			(0x01 << USART_RQR_SBKRQ_Pos)
#define USART_RQR_MMRQ_Msk			(0x01 << USART_RQR_MMRQ_Pos)
#define USART_RQR_RXFRQ_Msk			(0x01 << USART_RQR_RXFRQ_Pos)
#define USART_RQR_TXFRQ_Msk			(0x01 << USART_RQR_TXFRQ_Pos)

#define USART_ISR_PE_Pos			0
#define USART_ISR_FE_Pos			1
#define USART_ISR_NF_Pos			2
#define USART_ISR_ORE_Pos			3
#define USART_ISR_IDLE_Pos			4
#define USART_ISR_RXNE_Pos			5
#define USART_ISR_TC_Pos			6
#define USART_ISR_TXE_Pos			7
#define USART_ISR_LBDF_Pos			8
#define USART_ISR_CTSIF_Pos			9
#define USART_ISR_CTS_Pos			10
#define USART_ISR_RTOF_Pos			11
#define USART_ISR_EOBF_Pos			12
#define USART_ISR_ABRE_Pos			14
#define USART_ISR_ABRF_Pos			15
#define USART_ISR_BUSY_Pos			16
#define USART_ISR_CMF_Pos			17
#define USART_ISR_SBKF_Pos			18
#define USART_ISR_RWU_Pos			19
#define USART_ISR_WUF_Pos			20
#define USART_ISR_TEAK_Pos			21
#define USART_ISR_REAK_Pos			22

#define USART_ISR_PE_Msk			(0x01 << USART_ISR_PE_Pos)
#define USART_ISR_FE_Msk			(0x01 << USART_ISR_FE_Pos)
#define USART_ISR_NF_Msk			(0x01 << USART_ISR_NF_Pos)
#define USART_ISR_ORE_Msk			(0x01 << USART_ISR_ORE_Pos)
#define USART_ISR_IDLE_Msk			(0x01 << USART_ISR_IDLE_Pos)
#define USART_ISR_RXNE_Msk			(0x01 << USART_ISR_RXNE_Pos)
#define USART_ISR_TC_Msk			(0x01 << USART_ISR_TC_Pos)
#define USART_ISR_TXE_Msk			(0x01 << USART_ISR_TXE_Pos)
#define USART_ISR_LBDF_Msk			(0x01 << USART_ISR_LBDF_Pos)
#define USART_ISR_CTSIF_Msk			(0x01 << USART_ISR_CTSIF_Pos)
#define USART_ISR_CTS_Msk			(0x01 << USART_ISR_CTS_Pos)
#define USART_ISR_RTOF_Msk			(0x01 << USART_ISR_RTOF_Pos)
#define USART_ISR_EOBF_Msk			(0x01 << USART_ISR_EOBF_Pos)
#define USART_ISR_ABRE_Msk			(0x01 << USART_ISR_ABRE_Pos)
#define USART_ISR_ABRF_Msk			(0x01 << USART_ISR_ABRF_Pos)
#define USART_ISR_BUSY_Msk			(0x01 << USART_ISR_BUSY_Pos)
#define USART_ISR_CMF_Msk			(0x01 << USART_ISR_CMF_Pos)
#define USART_ISR_SBKF_Msk			(0x01 << USART_ISR_SBKF_Pos)
#define USART_ISR_RWU_Msk			(0x01 << USART_ISR_RWU_Pos)
#define USART_ISR_WUF_Msk			(0x01 << USART_ISR_WUF_Pos)
#define USART_ISR_TEAK_Msk			(0x01 << USART_ISR_TEAK_Pos)
#define USART_ISR_REAK_Msk			(0x01 << USART_ISR_REAK_Pos)

#define USART_ICR_PECF_Pos			0
#define USART_ICR_FECF_Pos			1
#define USART_ICR_NCF_Pos			2
#define USART_ICR_ORECF_Pos			3
#define USART_ICR_IDLECF_Pos		4
#define USART_ICR_TCCF_Pos			6
#define USART_ICR_LBDFCF_Pos		8
#define USART_ICR_CTSCF_Pos			9
#define USART_ICR_RTOCF_Pos			11
#define USART_ICR_EOBCF_Pos			12
#define USART_ICR_CMFCF_Pos			17
#define USART_ICR_WUFCF_Pos			20

#define USART_ICR_PECF_Msk			(0x01 << USART_ICR_PECF_Pos)
#define USART_ICR_FECF_Msk			(0x01 << USART_ICR_FECF_Pos)
#define USART_ICR_NCF_Msk			(0x01 << USART_ICR_NCF_Pos)
#define USART_ICR_ORECF_Msk			(0x01 << USART_ICR_ORECF_Pos)
#define USART_ICR_IDLECF_Msk		(0x01 << USART_ICR_IDLECF_Pos)
#define USART_ICR_TCCF_Msk			(0x01 << USART_ICR_TCCF_Pos)
#define USART_ICR_LBDFCF_Msk		(0x01 << USART_ICR_LBDFCF_Pos)
#define USART_ICR_CTSCF_Msk			(0x01 << USART_ICR_CTSCF_Pos)
#define USART_ICR_RTOCF_Msk			(0x01 << USART_ICR_RTOCF_Pos)
#define USART_ICR_EOBCF_Msk			(0x01 << USART_ICR_EOBCF_Pos)
#define USART_ICR_CMFCF_Msk			(0x01 << USART_ICR_CMFCF_Pos)
#define USART_ICR_WUFCF_Msk			(0x01 << USART_ICR_WUFCF_Pos)

#define USART_RDR_RDR_Pos			0
#define USART_RDR_RDR_Msk			(0x01 << USART_RDR_RDR_Pos)

#define USART_TDR_RDR_Pos			0
#define USART_TDR_RDR_Msk			(0x01 << USART_RDR_RDR_Pos)


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
#define FLITF_BASE_ADDR			0x40022000U
#define RCC_BASE_ADDR			0x40021000U
#define GPIOx_BASE_ADDR			0x48000000U
#define ADC12_BASE_ADDR			0x50000000U
#define ADC34_BASE_ADDR			0x50000400U
#define EXTI_BASE_ADDR			0x40010400U
#define SYSCFG_BASE_ADDR		0x40010000U
#define SPI1_BASE_ADDR			0x40013000U
#define SPI2_I2S2_BASE_ADDR		0x40003800U
#define SPI3_I2S3_BASE_ADDR		0x40003C00U
#define SPI4_BASE_ADDR			0x40013C00U
#define I2C1_BASE_ADDR			0x40005400U
#define I2C2_BASE_ADDR			0x40005800U
#define I2C3_BASE_ADDR			0x40007800U
#define USART1_BASE_ADDR		0x40013800U
#define USART2_BASE_ADDR		0x40004400U
#define USART3_BASE_ADDR		0x40004800U
#define UART4_BASE_ADDR			0x40004C00U
#define UART5_BASE_ADDR			0x40005000U

//Peripheral address offset
#define FLITF_OFFSET			0X00000000U
#define RCC_OFFSET				0x00000000U
#define GPIOA_OFFSET			0x00000000U
#define GPIOB_OFFSET			0x00000400U
#define GPIOC_OFFSET			0x00000800U
#define GPIOD_OFFSET			0x00000C00U
#define GPIOE_OFFSET			0x00001000U
#define GPIOF_OFFSET			0x00001400U
#define GPIOG_OFFSET			0x00001800U
#define GPIOH_OFFSET			0x00001C00U
#define ADC_MASTER_OFFSET		0x00000000U
#define ADC_SLAVE_OFFSET		0x00000100U
#define ADC_COMM_OFFSET			0x00000300U
#define EXTI_OFFSET				0x00000000U
#define SYSCFG_OFFSET			0x00000000U
#define SPI1_OFFSET				0x00000000U
#define SPI2_I2S2_OFFSET		0x00000000U
#define SPI3_I2S3_OFFSET		0x00000000U
#define SPI4_OFFSET				0x00000000U
#define I2C1_OFFSET				0x00000000U
#define I2C2_OFFSET				0x00000000U
#define I2C3_OFFSET				0x00000000U


//Peripheral address
#define FLITF_ADDR				(FLITF_BASE_ADDR + FLITF_OFFSET)
#define RCC_ADDR				(RCC_BASE_ADDR + RCC_OFFSET)
#define GPIOA_ADDR				(GPIOx_BASE_ADDR + GPIOA_OFFSET)
#define GPIOB_ADDR				(GPIOx_BASE_ADDR + GPIOB_OFFSET)
#define GPIOC_ADDR				(GPIOx_BASE_ADDR + GPIOC_OFFSET)
#define GPIOD_ADDR				(GPIOx_BASE_ADDR + GPIOD_OFFSET)
#define GPIOE_ADDR				(GPIOx_BASE_ADDR + GPIOE_OFFSET)
#define GPIOF_ADDR				(GPIOx_BASE_ADDR + GPIOF_OFFSET)
#define GPIOG_ADDR				(GPIOx_BASE_ADDR + GPIOG_OFFSET)
#define GPIOH_ADDR				(GPIOx_BASE_ADDR + GPIOH_OFFSET)
#define ADC1_ADDR				(ADC12_BASE_ADDR + ADC_MASTER_OFFSET)
#define ADC2_ADDR				(ADC12_BASE_ADDR + ADC_SLAVE_OFFSET)
#define ADC3_ADDR				(ADC34_BASE_ADDR + ADC_MASTER_OFFSET)
#define ADC4_ADDR				(ADC34_BASE_ADDR + ADC_SLAVE_OFFSET)
#define ADC12_COMM_ADDR			(ADC12_BASE_ADDR + ADC_COMM_OFFSET)
#define ADC34_COMM_ADDR			(ADC34_BASE_ADDR + ADC_COMM_OFFSET)
#define EXTI_ADDR				(EXTI_BASE_ADDR + EXTI_OFFSET)
#define SYSCFG_ADDR				(SYSCFG_BASE_ADDR + SYSCFG_OFFSET)
#define SPI1_ADDR				(SPI1_BASE_ADDR + SPI1_OFFSET)
#define SPI2_I2S2_ADDR			(SPI2_I2S2_BASE_ADDR + SPI2_I2S2_OFFSET)
#define SPI3_I2S3_ADDR			(SPI3_I2S3_BASE_ADDR + SPI3_I2S3_OFFSET)
#define SPI4_ADDR				(SPI4_BASE_ADDR + SPI4_OFFSET)
#define I2C1_ADDR				(I2C1_BASE_ADDR + I2C1_OFFSET)
#define I2C2_ADDR				(I2C2_BASE_ADDR + I2C2_OFFSET)
#define I2C3_ADDR				(I2C3_BASE_ADDR + I2C3_OFFSET)
#define USART1_ADDR				(USART1_BASE_ADDR)
#define USART2_ADDR				(USART2_BASE_ADDR)
#define USART3_ADDR				(USART3_BASE_ADDR)
#define UART4_ADDR				(UART4_BASE_ADDR)
#define UART5_ADDR				(UART5_BASE_ADDR)

/********************************************************************************/
/*						Peripheral access method								*/
/********************************************************************************/
#define FLITF	((FLITF_t *)FLITF_ADDR)
#define RCC		((RCC_t *)RCC_ADDR)
#define GPIOA	((GPIO_t *)GPIOA_ADDR)
#define GPIOB	((GPIO_t *)GPIOB_ADDR)
#define GPIOC	((GPIO_t *)GPIOC_ADDR)
#define GPIOD	((GPIO_t *)GPIOD_ADDR)
#define GPIOE	((GPIO_t *)GPIOE_ADDR)
#define GPIOF	((GPIO_t *)GPIOF_ADDR)
#define GPIOG	((GPIO_t *)GPIOG_ADDR)
#define GPIOH	((GPIO_t *)GPIOH_ADDR)
#define ADC1	((ADC_t *)ADC1_ADDR)
#define ADC2	((ADC_t *)ADC2_ADDR)
#define ADC3	((ADC_t *)ADC3_ADDR)
#define ADC4	((ADC_t *)ADC4_ADDR)
#define ADC1_2	((ADC_common_t *)ADC12_COMM_ADDR)
#define ADC3_4	((ADC_common_t *)ADC34_COMM_ADDR)
#define EXTI	((EXTI_t *)EXTI_ADDR)
#define SYSCFG  ((SYSCFG_t *)SYSCFG_ADDR)
#define SPI1	((SPI_t *)SPI1_ADDR)
#define SPI2	((SPI_t *)SPI2_I2S2_ADDR)
#define SPI3	((SPI_t *)SPI3_I2S3_ADDR)
#define SPI4	((SPI_t *)SPI4_ADDR)
#define I2C1	((I2C_t *)I2C1_ADDR)
#define I2C2	((I2C_t *)I2C2_ADDR)
#define I2C3	((I2C_t *)I2C3_ADDR)
#define USART1	((USART_t *)USART1_ADDR)
#define USART2	((USART_t *)USART2_ADDR)
#define USART3	((USART_t *)USART3_ADDR)
#define UART4	((USART_t *)UART4_ADDR)
#define UART5	((USART_t *)UART5_ADDR)

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

//GPIOx
typedef struct {
	__IO uint32_t 	MODER;
	__IO uint32_t	OTYPER;
	__IO uint32_t	OSPEEDR;
	__IO uint32_t	PUPDR;
	__IO uint32_t	IDR;
	__IO uint32_t	ODR;
	__IO uint32_t	BSRR;
	__IO uint32_t	LCKR;
	__IO uint32_t	AFR[2];
	__IO uint32_t	BRR;
}GPIO_t;

//EXTI
typedef struct{
	__IO uint32_t 	IMR1;
	__IO uint32_t	EMR1;
	__IO uint32_t	RTSR1;
	__IO uint32_t	FTSR1;
	__IO uint32_t	SWIER1;
	__IO uint32_t	PR1;
	__IO uint32_t	IMR2;
	__IO uint32_t	EMR2;
	__IO uint32_t	RTSR2;
	__IO uint32_t	FTSR2;
	__IO uint32_t	SWIER2;
	__IO uint32_t	PR2;
}EXTI_t;

//System Configuration Controller
typedef struct{
	__IO uint32_t 	CFGR1;
	__IO uint32_t	RCR;
	__IO uint32_t	EXTICR[4];
	__IO uint32_t	CFGR2;
	__IO uint32_t	CFGR3;
	__IO uint32_t	CFGR4;
}SYSCFG_t;

typedef struct{
	__IO uint32_t 	CR1;
	__IO uint32_t	CR2;
	__IO uint32_t	SR;
	__IO uint32_t	DR;
	__IO uint32_t	CRCPR;
	__IO uint32_t	RXCRCR;
	__IO uint32_t	TXCRCR;
	__IO uint32_t	I2SCFGR;
	__IO uint32_t	I2SPR;
}SPI_t;

typedef struct{
	__IO uint32_t 	CR1;
	__IO uint32_t	CR2;
	__IO uint32_t	OAR1;
	__IO uint32_t	OAR2;
	__IO uint32_t	TIMINGR;
	__IO uint32_t	TIMEOUTR;
	__IO uint32_t	ISR;
	__IO uint32_t	ICR;
	__IO uint32_t	PECR;
	__IO uint32_t	RXDR;
	__IO uint32_t	TXDR;
}I2C_t;

typedef struct{
	__IO uint32_t 	ACR;
	__IO uint32_t	KEYR;
	__IO uint32_t	OPTKEYR;
	__IO uint32_t	SR;
	__IO uint32_t	CR;
	__IO uint32_t	AR;
	__IO uint32_t	OBR;
	__IO uint32_t	WRPR;
}FLITF_t;


typedef struct{
	__IO uint32_t CR1;
	__IO uint32_t CR2;
	__IO uint32_t CR3;
	__IO uint32_t BRR;
	__IO uint32_t GTPR;
	__IO uint32_t RTOR;
	__IO uint32_t RQR;
	__IO uint32_t ISR;
	__IO uint32_t ICR;
	__IO uint32_t RDR;
	__IO uint32_t TDR;
}USART_t;


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

/********************************************************************************/
/*								include driver headers							*/
/********************************************************************************/
#include <RCC.h>
#include <GPIO.h>
#include <SPI.h>
#include <I2S.h>
#include <I2C.h>
#include <USART.h>

#endif
