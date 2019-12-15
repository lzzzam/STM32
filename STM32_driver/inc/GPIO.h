/*
 * GPIO.h
 *
 *  Created on: 15 dic 2019
 *      Author: luca
 */

#ifndef GPIO_H_
#define GPIO_H_
#include <STM32F303RE.h>

#define GPIO_EXTI_MUX_SEL(x)	 ((x==GPIOA) ? 0 : \
								  (x==GPIOB) ? 1 : \
								  (x==GPIOC) ? 2 : \
								  (x==GPIOD) ? 3 : \
								  (x==GPIOE) ? 4 : \
								  (x==GPIOF) ? 5 : \
								  (x==GPIOG) ? 6 : \
								  (x==GPIOH) ? 7 : 7)

#define GPIO_EXTI_IRQ_NUM(x)	((x==0)  ? EXTI0_IRQ_NUM :\
								 (x==1)  ? EXTI1_IRQ_NUM :\
								 (x==2)  ? EXTI2_IRQ_NUM :\
								 (x==3)  ? EXTI3_IRQ_NUM :\
								 (x==4)  ? EXTI4_IRQ_NUM :\
								 (x<=9)  ? EXTI9_5_IRQ_NUM :\
								 (x<=15) ? EXTI15_10_IRQ_NUM : EXTI15_10_IRQ_NUM)


void __GPIO_init(GPIO_t *pGPIOx,			/*GPIOx with x = A,B,C...H	*/
				 uint8_t PinNumber,			/*0-15						*/
				 uint8_t PinMode,			/*@GPIO_PinMode				*/
				 uint8_t PinType,			/*@GPIO_PinType				*/
				 uint8_t PinSpeed,			/*@GPIO_PinSpeed			*/
				 uint8_t PinPuPdControl,	/*@GPIO_PinPuPd				*/
				 uint8_t PinAlternateFnc);	/*@GPIO_PinAltFnc			*/

void __GPIO_reset(GPIO_t *pGPIOx);			/*GPIOx with x = A,B,C...H	*/

uint8_t __GPIO_readPin(GPIO_t *pGPIOx,		/*GPIOx with x = A,B,C...H	*/
		 	 	 	   uint8_t PinNumber);	/*0-15						*/

uint16_t __GPIO_readPort(GPIO_t *pGPIOx);	/*GPIOx with x = A,B,C...H	*/

void __GPIO_writePin(GPIO_t *pGPIOx,		/*GPIOx with x = A,B,C...H	*/
		 	 	 	 uint8_t PinNumber,		/*0-15						*/
					 uint8_t Value);		/*TRUE or FALSE				*/

void __GPIO_writePort(GPIO_t *pGPIOx,		/*GPIOx with x = A,B,C...H	*/
					  uint16_t Value);		/*0-65535					*/


void __GPIO_tooglePin(GPIO_t *pGPIOx,		/*GPIOx with x = A,B,C...H	*/
 	 	 	 	 	  uint8_t PinNumber);	/*0-15						*/

void __GPIO_IRQconfig(uint8_t PinNumber,	/*0-15						*/
					  uint8_t EnOrDis,		/*EN or DIS					*/
					  uint8_t Priority);	/*0-15 where 0 is Highest   */

void __GPIO_IRQhandling(uint8_t PinNumber);


#endif /* GPIO_H_ */
