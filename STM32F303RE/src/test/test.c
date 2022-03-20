#include <STM32F303RE.h>

uint8_t i;
uint8_t flag = 5;


int main(void)
{
	for(i=0; i<100; i++)
    {
        flag++;
    }

	while(1);
}
