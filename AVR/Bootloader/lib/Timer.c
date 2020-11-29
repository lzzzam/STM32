#include <avr/io.h>
#include <avr/interrupt.h>

void TC1_init()
{
  //Timer/Counter in Normal Mode of Operation
  TCCR1A = 0;
  TCCR1B = 0;
  //Reset Timer Counter
  TCNT1  = 0;

  //Set 1024 Prescaler (start timer)
  TCCR1B |= (1 << CS12) | (1 << CS10);
}

void TC1_disable()
{
  //reset TC1 value
  TCNT1 = 0;
  //Stop Timer/Counter
  TCCR1B = 0;
}
