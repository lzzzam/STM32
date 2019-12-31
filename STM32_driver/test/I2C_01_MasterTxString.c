/**
  ******************************************************************************
  * @file    main.c
  * @author  Auto-generated by STM32CubeIDE
  * @version V1.0
  * @brief   Default main function.
  ******************************************************************************
*/
#include <STM32F303RE.h>
#include <GPIO.h>
#include <I2C.h>

/*
 * SCL  --> PB8	(D15)
 * SDA  --> PB9 (D14)
 * SCL debug  --> PB6
 * SDA debug  --> PB7
 * IMPORTANT: arduino Mega PULLUP resistor is already present on SDA and SCL
 * IMPORTANT: arduino Wire Lib. use a 32 byte rx\tx buffer, if more byte are
 * transmitted\received in the same I2C communication it will be discarded
 */


void delay();
void PushButton(void);

int main(void)
{
	uint8_t SAddr = 0x68;
	uint8_t String[] = "Ciao sono STM32F303RE!!";
	uint8_t ssize = sizeof(String);

	I2C_handle I2C1_handle;

	I2C1_handle.pI2Cx = I2C1;
	I2C1_handle.pI2Cx_conf.Speed = 100000; //100kHz
	I2C1_handle.pI2Cx_conf.Addr  = 0x0;
	I2C1_handle.pTxBuf = NULL;
	I2C1_handle.pRxBuf = NULL;
	I2C1_handle.TxLen  = 0;
	I2C1_handle.RxLen  = 0;

	//Initialize SPI1
	__I2C_EnPCLK(I2C1);
	__I2C_init(&I2C1_handle);

	//Enable GPIOx peripheral clock
	__GPIO_EnPCLK(GPIOB);
	__GPIO_EnPCLK(GPIOC);

	//Configure User Button as Input
	__GPIO_init(GPIOC, 13, GPIO_MODE_IN, GPIO_OTYPE_PP, GPIO_SPEED_LOW, GPIO_NO_PUPD, GPIO_ALT_FNC_0);

	//Configure SCL
	__GPIO_init(GPIOB, 8, GPIO_MODE_AF, GPIO_OTYPE_OD, GPIO_SPEED_HIGH, GPIO_NO_PUPD, GPIO_ALT_FNC_4);

	//Configure SDA
	__GPIO_init(GPIOB, 9, GPIO_MODE_AF, GPIO_OTYPE_OD, GPIO_SPEED_HIGH, GPIO_NO_PUPD, GPIO_ALT_FNC_4);

	//Configure SCL for Logic Analyzer
	__GPIO_init(GPIOB, 6, GPIO_MODE_AF, GPIO_OTYPE_OD, GPIO_SPEED_HIGH, GPIO_NO_PUPD, GPIO_ALT_FNC_4);

	//Configure SDA for Logic Analyzer
	__GPIO_init(GPIOB, 7, GPIO_MODE_AF, GPIO_OTYPE_OD, GPIO_SPEED_HIGH, GPIO_NO_PUPD, GPIO_ALT_FNC_4);



	while(1){

		uint8_t txed = 0;

		PushButton();

		//Enable I2C1
		__I2C_enable(&I2C1_handle);

		//Send String
		txed = __I2C_MasterSend(&I2C1_handle, String, ssize, SAddr, I2C_DISABLE_SR);//Transmit and close communication

		//Disable I2C1
		__I2C_disable(&I2C1_handle);

		//to avoid unused variable warning
		(void)txed;
	}

}


void PushButton(void){

	//Wait until button is pressed
	while(__GPIO_readPin(GPIOC, 13) == TRUE);
	delay();

}

void delay(){
	uint32_t i;
	for(i=0; i<100000; i++);
}
