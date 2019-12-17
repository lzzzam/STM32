/*
 * GPIO.h
 *
 *  Created on: 15 dic 2019
 *      Author: luca
 */

#ifndef GPIO_H_
#define GPIO_H_
#include <STM32F303RE.h>

/**********************************************************************
 * @fn			- GPIO_EXTI_MUX_SEL
 *
 * @brief 		- Convert GPIO port to EXTI Multiplexer selector
 * @param[x] 	- GPIO port to be converted
 *
 * @note		- x range is [GPIOA,GPIOB...,GPIOH]
 **********************************************************************/
#define GPIO_EXTI_MUX_SEL(x)	 ((x==GPIOA) ? 0 : \
								  (x==GPIOB) ? 1 : \
								  (x==GPIOC) ? 2 : \
								  (x==GPIOD) ? 3 : \
								  (x==GPIOE) ? 4 : \
								  (x==GPIOF) ? 5 : \
								  (x==GPIOG) ? 6 : \
								  (x==GPIOH) ? 7 : 7)


/**********************************************************************
 * @fn			- GPIO_EXTI_IRQ_NUM
 *
 * @brief 		- Convert EXTI line to respective IRQ number
 * @param[x] 	- EXTI line to be converted
 *
 * @note		- x range is 0-15
 **********************************************************************/
#define GPIO_EXTI_IRQ_NUM(x)	((x==0)  ? EXTI0_IRQ_NUM :\
								 (x==1)  ? EXTI1_IRQ_NUM :\
								 (x==2)  ? EXTI2_IRQ_NUM :\
								 (x==3)  ? EXTI3_IRQ_NUM :\
								 (x==4)  ? EXTI4_IRQ_NUM :\
								 (x<=9)  ? EXTI9_5_IRQ_NUM :\
								 (x<=15) ? EXTI15_10_IRQ_NUM : EXTI15_10_IRQ_NUM)



/************************************************************************
 * @fn			- __GPIO_EnPCLK
 *
 * @brief 		- Enable GPIOx Peripheral Clock
 * @param[x] 	- GPIOx port base address
 *
 * @note		- Call before __GPIO_init
 ************************************************************************/
void __GPIO_EnPCLK(GPIO_t *pGPIOx);


/************************************************************************
 * @fn						- __GPIO_init
 *
 * @brief 					- Initialize GPIOx pin
 * @param[pGPIOx] 			- GPIOx port base address
 * @param[PinNumber] 		- Port Pin to be initialized
 * @param[PinMode] 			- Define mode of the Pin
 * @param[PinType] 			- Define output port type of the pin
 * @param[PinSpeed] 		- Define output port speed
 * @param[PinPuPdControl] 	- Define PU\PD characteristic
 * @param[PinAlternateFnc]	- Define Pin alternate function
 *
 * @note					- Must be called before using the Pin
 ************************************************************************/
void __GPIO_init(GPIO_t *pGPIOx,			/*GPIOx with x = A,B,C...H	*/
				 uint8_t PinNumber,			/*0-15						*/
				 uint8_t PinMode,			/*@GPIO_PinMode				*/
				 uint8_t PinType,			/*@GPIO_PinType				*/
				 uint8_t PinSpeed,			/*@GPIO_PinSpeed			*/
				 uint8_t PinPuPdControl,	/*@GPIO_PinPuPd				*/
				 uint8_t PinAlternateFnc);	/*@GPIO_PinAltFnc			*/



/************************************************************************
 * @fn						- __GPIO_reset
 *
 * @brief 					- Reset GPIOx port to default values after
 * 							  PowerOn reset
 * @param[pGPIOx] 			- GPIOx port base address
 *
 * @note					-
 ************************************************************************/
void __GPIO_reset(GPIO_t *pGPIOx);			/*GPIOx with x = A,B,C...H	*/



/************************************************************************
 * @fn						- __GPIO_readPin
 *
 * @brief 					- Read input pin
 * @param[pGPIOx] 			- GPIOx port base address
 * @param[PinNumber]		- Port Pin
 *
 * @return					- Return TRUE or FALSE
 * @note					- The pin must be initialized as input
 ************************************************************************/
uint8_t __GPIO_readPin(GPIO_t *pGPIOx,		/*GPIOx with x = A,B,C...H	*/
		 	 	 	   uint8_t PinNumber);	/*0-15						*/



/************************************************************************
 * @fn						- __GPIO_readPort
 *
 * @brief 					- Read entire Port
 * @param[pGPIOx] 			- GPIOx port base address
 *
 * @return					- Return GPIOx current value
 * @note					-
 ************************************************************************/
uint16_t __GPIO_readPort(GPIO_t *pGPIOx);	/*GPIOx with x = A,B,C...H	*/



/************************************************************************
 * @fn						- __GPIO_writePin
 *
 * @brief 					- Write to output pin
 * @param[pGPIOx] 			- GPIOx port base address
 * @param[PinNumber]		- Port Pin
 * @param[Value]			- Value to be written
 *
 * @note					- The pin must be initialized as output
 ************************************************************************/
void __GPIO_writePin(GPIO_t *pGPIOx,		/*GPIOx with x = A,B,C...H	*/
		 	 	 	 uint8_t PinNumber,		/*0-15						*/
					 uint8_t Value);		/*TRUE or FALSE				*/



/************************************************************************
 * @fn						- __GPIO_writePort
 *
 * @brief 					- Write to output Port
 * @param[pGPIOx] 			- GPIOx port base address
 * @param[Value]			- Value to be written
 *
 * @note					- Write to the entire port
 ************************************************************************/
void __GPIO_writePort(GPIO_t *pGPIOx,		/*GPIOx with x = A,B,C...H	*/
					  uint16_t Value);		/*0-65535					*/




/************************************************************************
 * @fn						- __GPIO_tooglePin
 *
 * @brief 					- Toogle output pin
 * @param[pGPIOx] 			- GPIOx port base address
 * @param[PinNumber]		- Port Pin to be inverted
 *
 * @note					- The pin must be initialized as output
 ************************************************************************/
void __GPIO_tooglePin(GPIO_t *pGPIOx,		/*GPIOx with x = A,B,C...H	*/
 	 	 	 	 	  uint8_t PinNumber);	/*0-15						*/



/************************************************************************
 * @fn						- __GPIO_IRQconfig
 *
 * @brief 					- Configure the IRQ in the NVIC peripheral
 * 							  inside Cortex-M4 core
 * @param[PinNumber]		- Port Pin to be enabled for Interrupt
 * 							  generation
 * @param[EnOrDis]			- Enable or Disable IRQ handling by the NVIC
 * @param[Priority]			- Interrupt priority
 *
 * @note					- The pin must be initialized in Interrupt Mode
 ************************************************************************/
void __GPIO_IRQconfig(uint8_t PinNumber,	/*0-15						*/
					  uint8_t EnOrDis,		/*EN or DIS					*/
					  uint8_t Priority);	/*0-15 where 0 is Highest   */



/************************************************************************
 * @fn						- __GPIO_IRQhandling
 *
 * @brief 					- Clear the pending Interrupt request inside
 * 							  the EXTI and NVIC
 * @param[PinNumber]		- Port Pin that has generated the interrupt
 *
 * @note					- Must be called inside the EXTIx handler
 ************************************************************************/
void __GPIO_IRQhandling(uint8_t PinNumber); /*0-15						*/


#endif /* GPIO_H_ */
