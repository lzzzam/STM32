/*
 * GPIO.c
 *
 *  Created on: 15 dic 2019
 *      Author: luca
 */
#include <GPIO.h>

void __GPIO_init(GPIO_t *pGPIOx,
				 uint8_t PinNumber,
				 uint8_t PinMode,
				 uint8_t PinType,
				 uint8_t PinSpeed,
				 uint8_t PinPuPdControl,
				 uint8_t PinAlternateFnc)
{

	if(PinMode == GPIO_MODE_IN ||
	   PinMode == GPIO_MODE_OUT ||
	   PinMode == GPIO_MODE_AF ||
	   PinMode == GPIO_MODE_AN)
	{
		//Set Mode
		pGPIOx->MODER |= (PinMode << (PinNumber * 2));

		//Set Type
		pGPIOx->OTYPER |= (PinMode << PinNumber);

		//Set Speed
		pGPIOx->OSPEEDR |= (PinSpeed << (PinNumber * 2));

		//Set PullUp\PullDown
		pGPIOx->PUPDR |= (PinPuPdControl << (PinNumber *2));

		//Set Alternate Function
		if(PinNumber <= 7)
		{
			//Set AFLR
			pGPIOx->AFRL |= (PinAlternateFnc << (PinNumber * 4));
		}
		else
		{
			//Set AFHR
			pGPIOx->AFRH |= (PinAlternateFnc << (PinNumber * 4));
		}
	}
	else if(PinMode == GPIO_MODE_INT_R ||
			PinMode == GPIO_MODE_INT_F ||
			PinMode == GPIO_MODE_INT_RF)
	{
		//Set Mode as input
		pGPIOx->MODER |= (GPIO_MODE_IN << (PinNumber *2));

		//Set PullUp\PullDown
		pGPIOx->PUPDR |= (PinPuPdControl << (PinNumber *2));

		//Set Rising\Falling Edge
		if(PinMode == GPIO_MODE_INT_R)//Rising Edge
		{
			//Set RTSR
			EXTI->RTSR1 |= (1 << PinNumber);
			EXTI->FTSR1 &= ~(1 << PinNumber);
		}
		else if(PinMode == GPIO_MODE_INT_F)//Falling Edge
		{
			//Set FTSR
			EXTI->FTSR1 |= (1 << PinNumber);
			EXTI->RTSR1 &= ~(1 << PinNumber);
		}
		else if(PinMode == GPIO_MODE_INT_RF)//Rising + Falling Edge
		{
			//Set RTSR and FTSR
			EXTI->FTSR1 |= (1 << PinNumber);
			EXTI->RTSR1 |= (1 << PinNumber);
		}

		//Set EXTIx Input Multiplexer
		uint8_t Reg_num = PinNumber / 4;
		uint8_t Reg_offset  = PinNumber % 4;
		uint8_t PortCode = GPIO_EXTI_MUX_SEL(pGPIOx);
		SYSCFG->EXTICR[Reg_num] &= ~(0xF << (Reg_offset*4)); 	 //Reset Value
		SYSCFG->EXTICR[Reg_num] |= (PortCode << (Reg_offset*4)); //Set Port code

		//Enable Interrupt in EXTI
		EXTI->IMR1 |= (1 << PinNumber);

	}


}

void __GPIO_reset(GPIO_t *pGPIOx)
{
	if(pGPIOx == GPIOA){
		//Reset GPIOA Port
		RCC->AHBRSTR |= (1 << 17);
		RCC->AHBRSTR &= ~(1 << 17);
	}
	else if(pGPIOx == GPIOB)
	{
		//Reset GPIOB Port
		RCC->AHBRSTR |= (1 << 18);
		RCC->AHBRSTR &= ~(1 << 18);
	}
	else if(pGPIOx == GPIOC)
	{
		//Reset GPIOC Port
		RCC->AHBRSTR |= (1 << 19);
		RCC->AHBRSTR &= ~(1 << 19);
	}
	else if(pGPIOx == GPIOD)
	{
		//Reset GPIOD Port
		RCC->AHBRSTR |= (1 << 20);
		RCC->AHBRSTR &= ~(1 << 20);

	}
	else if(pGPIOx == GPIOE)
	{
		//Reset GPIOE Port
		RCC->AHBRSTR |= (1 << 21);
		RCC->AHBRSTR &= ~(1 << 21);
	}
	else if(pGPIOx == GPIOF)
	{
		//Reset GPIOF Port
		RCC->AHBRSTR |= (1 << 22);
		RCC->AHBRSTR &= ~(1 << 22);
	}
	else if(pGPIOx == GPIOG)
	{
		//Reset GPIOG Port
		RCC->AHBRSTR |= (1 << 23);
		RCC->AHBRSTR &= ~(1 << 23);

	}
	else if(pGPIOx == GPIOH)
	{
		//Reset GPIOG Port
		RCC->AHBRSTR |= (1 << 16);
		RCC->AHBRSTR &= ~(1 << 16);
	}

}

uint8_t __GPIO_readPin(GPIO_t *pGPIOx,
					   uint8_t PinNumber)
{
	//Shift Input Data Reg and Mask LSB
	uint8_t value = ((pGPIOx->IDR >> PinNumber) & 0x1);
	return value;
}

uint16_t __GPIO_readPort(GPIO_t *pGPIOx)
{
	return (uint16_t)pGPIOx->IDR;
}

void __GPIO_writePin(GPIO_t *pGPIOx,
		   	   	   	 uint8_t PinNumber,
					 uint8_t Value)
{
	if(Value == TRUE)
	{
		//Set Bit
		pGPIOx->ODR |= (1 << PinNumber);
	}
	else if(Value == FALSE)
	{
		//Clear Bit
		pGPIOx->ODR &= ~(1 << PinNumber);
	}

}

void __GPIO_writePort(GPIO_t *pGPIOx,
					  uint16_t Value)
{
	//Write entire Register
	pGPIOx->ODR = (uint32_t)Value;
}

void __GPIO_tooglePin(GPIO_t *pGPIOx,
	 	 	  	  	  uint8_t PinNumber)
{
	//XOR with PinNumber bit
	pGPIOx->ODR ^= (1 << PinNumber);
}

void __GPIO_IRQconfig(uint8_t PinNumber,
					  uint8_t EnOrDis,
					  uint8_t Priority)
{
	uint8_t irq = GPIO_EXTI_IRQ_NUM(PinNumber);
	uint8_t Reg_num = irq / 32;
	uint8_t Reg_offset = irq % 32;

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

	//Set priority
	uint8_t iprx = irq / 4;
	uint8_t shift_amount = ((irq % 4)*8) + NUM_PRIORITY_BITS;
	*(NVIC_IPR + iprx) |= (Priority << shift_amount);


}

void __GPIO_IRQhandling(uint8_t PinNumber)
{

}

