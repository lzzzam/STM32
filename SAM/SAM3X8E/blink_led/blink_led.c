#include <sam3x8e.h>
#include <ioport/ioport.h>

#define MY_LED    IOPORT_CREATE_PIN(PIOB, 27)

#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_PLLACK

// ===== System Clock (MCK) Prescaler Options   (Fmck = Fsys / (SYSCLK_PRES))
//#define CONFIG_SYSCLK_PRES          SYSCLK_PRES_1
#define CONFIG_SYSCLK_PRES          SYSCLK_PRES_2
//#define CONFIG_SYSCLK_PRES          SYSCLK_PRES_4
//#define CONFIG_SYSCLK_PRES          SYSCLK_PRES_8
//#define CONFIG_SYSCLK_PRES          SYSCLK_PRES_16
//#define CONFIG_SYSCLK_PRES          SYSCLK_PRES_32
//#define CONFIG_SYSCLK_PRES          SYSCLK_PRES_64
//#define CONFIG_SYSCLK_PRES          SYSCLK_PRES_3

// ===== PLL0 (A) Options   (Fpll = (Fclk * PLL_mul) / PLL_div)
// Use mul and div effective values here.
#define CONFIG_PLL0_SOURCE          PLL_SRC_MAINCK_XTAL
#define CONFIG_PLL0_MUL             14
#define CONFIG_PLL0_DIV             1


int main(void)
{
  sysclk_init();

  ioport_init();

  ioport_set_pin_mode(MY_LED, IOPORT_MODE_PULLUP);
  ioport_set_pin_dir(MY_LED, IOPORT_DIR_OUTPUT);

  ioport_set_pin_level(MY_LED, (bool) 0);

  while(1)
  {
    ioport_set_pin_level(MY_LED, (bool) 0);
    for(uint32_t i=0; i<0xFFFFF; i++)
    {

    }

    ioport_set_pin_level(MY_LED, (bool) 1);
    for(uint32_t i=0; i<0xFFFFF; i++)
    {

    }

  }

  return 0;
}
