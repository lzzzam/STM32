#include "STM32F303RE.h"
#include "system.h"

#define __RESET_HANDLER__ __attribute__ ((section(".reset_handler")))
#define __DEFAULT_HANDLER__ __attribute__ ((weak, alias ("Default_Handler"), section(".irq_handlers")))
#define __VECTOR_TABLE__ __attribute__ ((section(".isr_vector"),used))
#define __STACK__ __attribute__((section(".stack"))) 

// Boundaries of .text, .data and .bss sections as declared in linker script
extern uint32_t __etext;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

// Boundaris of Stack section declared in linker script
extern uint32_t __StackTop;
extern uint32_t __StackLimit;

#define __STACK_SIZE 0xc00
uint32_t Main_Stack[__STACK_SIZE] __attribute__ ((section(".stack"), used));

// Entry point to Application
extern int main(void);

// Define default handler as a weak function
void __WEAK_FUNCTION__ Default_Handler(void);

// Intrinsic function to set Main Stack Pointer
void __setMSP(uint32_t address);

/* 
 * Forward declaration of the specific IRQ handlers. These are aliased
 * to the Default_Handler, which is a 'forever' loop. 
 */

// Main entry point
void __RESET_HANDLER__ Reset_Handler(void);
// ------------------ ARM ISR ------------------
void __DEFAULT_HANDLER__ NMI_Handler(void);
void __DEFAULT_HANDLER__ HardFault_Handler(void);
void __DEFAULT_HANDLER__ MemManage_Handler(void);
void __DEFAULT_HANDLER__ BusFault_Handler(void);
void __DEFAULT_HANDLER__ UsageFault_Handler(void);
void __DEFAULT_HANDLER__ SVC_Handler(void);
void __DEFAULT_HANDLER__ DebugMon_Handler(void);
void __DEFAULT_HANDLER__ PendSV_Handler(void);
void __DEFAULT_HANDLER__ SysTick_Handler(void);
// ------------------ STM ISR ------------------
void __DEFAULT_HANDLER__ WWDG_IRQHandler(void);
void __DEFAULT_HANDLER__ PVD_IRQHandler(void);
void __DEFAULT_HANDLER__ TAMPER_STAMP_IRQHandler(void);
void __DEFAULT_HANDLER__ RTC_WKUP_IRQHandler(void);
void __DEFAULT_HANDLER__ FLASH_IRQHandler(void);
void __DEFAULT_HANDLER__ RCC_IRQHandler(void);
void __DEFAULT_HANDLER__ EXTI0_IRQHandler(void);
void __DEFAULT_HANDLER__ EXTI1_IRQHandler(void);
void __DEFAULT_HANDLER__ EXTI2_TS_IRQHandler(void);
void __DEFAULT_HANDLER__ EXTI3_IRQHandler(void);
void __DEFAULT_HANDLER__ EXTI4_IRQHandler(void);
void __DEFAULT_HANDLER__ DMA1_Channel1_IRQHandler(void);
void __DEFAULT_HANDLER__ DMA1_Channel2_IRQHandler(void);
void __DEFAULT_HANDLER__ DMA1_Channel3_IRQHandler(void);
void __DEFAULT_HANDLER__ DMA1_Channel4_IRQHandler(void);
void __DEFAULT_HANDLER__ DMA1_Channel5_IRQHandler(void);
void __DEFAULT_HANDLER__ DMA1_Channel6_IRQHandler(void);
void __DEFAULT_HANDLER__ DMA1_Channel7_IRQHandler(void);
void __DEFAULT_HANDLER__ ADC1_2_IRQHandler(void);
void __DEFAULT_HANDLER__ USB_HP_CAN1_TX_IRQHandler(void);
void __DEFAULT_HANDLER__ USB_LP_CAN1_RX0_IRQHandler(void);
void __DEFAULT_HANDLER__ CAN1_RX1_IRQHandler(void);
void __DEFAULT_HANDLER__ CAN1_SCE_IRQHandler(void);
void __DEFAULT_HANDLER__ EXTI9_5_IRQHandler(void);
void __DEFAULT_HANDLER__ TIM1_BRK_TIM15_IRQHandler(void);
void __DEFAULT_HANDLER__ TIM1_UP_TIM16_IRQHandler(void);
void __DEFAULT_HANDLER__ TIM1_TRG_COM_TIM17_IRQHandler(void);
void __DEFAULT_HANDLER__ TIM1_CC_IRQHandler(void);
void __DEFAULT_HANDLER__ TIM2_IRQHandler(void);
void __DEFAULT_HANDLER__ TIM3_IRQHandler(void);
void __DEFAULT_HANDLER__ TIM4_IRQHandler(void);
void __DEFAULT_HANDLER__ I2C1_EV_IRQHandler(void);
void __DEFAULT_HANDLER__ I2C1_ER_IRQHandler(void);
void __DEFAULT_HANDLER__ I2C2_EV_IRQHandler(void);
void __DEFAULT_HANDLER__ I2C2_ER_IRQHandler(void);
void __DEFAULT_HANDLER__ SPI1_IRQHandler(void);
void __DEFAULT_HANDLER__ SPI2_IRQHandler(void);
void __DEFAULT_HANDLER__ USART1_IRQHandler(void);
void __DEFAULT_HANDLER__ USART2_IRQHandler(void);
void __DEFAULT_HANDLER__ USART3_IRQHandler(void);
void __DEFAULT_HANDLER__ EXTI15_10_IRQHandler(void);
void __DEFAULT_HANDLER__ RTC_Alarm_IRQHandler(void);
void __DEFAULT_HANDLER__ USBWakeUp_IRQHandler(void);
void __DEFAULT_HANDLER__ TIM8_BRK_IRQHandler(void);
void __DEFAULT_HANDLER__ TIM8_UP_IRQHandler(void);
void __DEFAULT_HANDLER__ TIM8_TRG_COM_IRQHandler(void);
void __DEFAULT_HANDLER__ TIM8_CC_IRQHandler(void);
void __DEFAULT_HANDLER__ ADC3_IRQHandler(void);
void __DEFAULT_HANDLER__ SPI3_IRQHandler(void);
void __DEFAULT_HANDLER__ UART4_IRQHandler(void);
void __DEFAULT_HANDLER__ UART5_IRQHandler(void);
void __DEFAULT_HANDLER__ TIM6_DAC_IRQHandler(void);
void __DEFAULT_HANDLER__ TIM7_IRQHandler(void);
void __DEFAULT_HANDLER__ DMA2_Channel1_IRQHandler(void);
void __DEFAULT_HANDLER__ DMA2_Channel2_IRQHandler(void);
void __DEFAULT_HANDLER__ DMA2_Channel3_IRQHandler(void);
void __DEFAULT_HANDLER__ DMA2_Channel4_IRQHandler(void);
void __DEFAULT_HANDLER__ DMA2_Channel5_IRQHandler(void);
void __DEFAULT_HANDLER__ ADC4_IRQHandler(void);
void __DEFAULT_HANDLER__ COMP1_2_3_IRQHandler(void);
void __DEFAULT_HANDLER__ COMP4_5_6_IRQHandler(void);
void __DEFAULT_HANDLER__ COMP7_IRQHandler(void);
void __DEFAULT_HANDLER__ USB_HP_IRQHandler(void);
void __DEFAULT_HANDLER__ USB_LP_IRQHandler(void);
void __DEFAULT_HANDLER__ USBWakeUp_RMP_IRQHandler(void);
void __DEFAULT_HANDLER__ FPU_IRQHandler(void);

// IRQ Handler type used to declare vector table
typedef void (* const pHandler)(void);

// ISR vector table
__VECTOR_TABLE__ pHandler __vector_table[] = 
{
    (pHandler) &__StackTop,                     // Top of Stack
    Reset_Handler,                              // The reset handler
    NMI_Handler,                                // The NMI handler
    HardFault_Handler,                          // The hard fault handler
    MemManage_Handler,                          // The MPU fault handler
    BusFault_Handler,                           // The bus fault handler
    UsageFault_Handler,                         // The usage fault handler
    0,                                          // Reserved
    0,                                          // Reserved
    0,                                          // Reserved
    0,                                          // Reserved
    SVC_Handler,                                // SVCall handler
    DebugMon_Handler,                           // Debug monitor handler
    0,                                          // Reserved
    PendSV_Handler,                             // The PendSV handler
    SysTick_Handler,                            // The SysTick handler

    // ----------------------------------------------------------------------
    // Chip Level - STM32F303RE
    WWDG_IRQHandler, //
    PVD_IRQHandler, //
    TAMPER_STAMP_IRQHandler, //
    RTC_WKUP_IRQHandler, //
    FLASH_IRQHandler, //
    RCC_IRQHandler, //
    EXTI0_IRQHandler, //
    EXTI1_IRQHandler, //
    EXTI2_TS_IRQHandler, //
    EXTI3_IRQHandler, //
    EXTI4_IRQHandler, //
    DMA1_Channel1_IRQHandler, //
    DMA1_Channel2_IRQHandler, //
    DMA1_Channel3_IRQHandler, //
    DMA1_Channel4_IRQHandler, //
    DMA1_Channel5_IRQHandler, //
    DMA1_Channel6_IRQHandler, //
    DMA1_Channel7_IRQHandler, //
    ADC1_2_IRQHandler, //
    USB_HP_CAN1_TX_IRQHandler, //
    USB_LP_CAN1_RX0_IRQHandler, //
    CAN1_RX1_IRQHandler, //
    CAN1_SCE_IRQHandler, //
    EXTI9_5_IRQHandler, //
    TIM1_BRK_TIM15_IRQHandler, //
    TIM1_UP_TIM16_IRQHandler, //
    TIM1_TRG_COM_TIM17_IRQHandler, //
    TIM1_CC_IRQHandler, //
    TIM2_IRQHandler, //
    TIM3_IRQHandler, //
    TIM4_IRQHandler, //
    I2C1_EV_IRQHandler, //
    I2C1_ER_IRQHandler, //
    I2C2_EV_IRQHandler, //
    I2C2_ER_IRQHandler, //
    SPI1_IRQHandler, //
    SPI2_IRQHandler, //
    USART1_IRQHandler, //
    USART2_IRQHandler, //
    USART3_IRQHandler, //
    EXTI15_10_IRQHandler, //
    RTC_Alarm_IRQHandler, //
    USBWakeUp_IRQHandler, //
    TIM8_BRK_IRQHandler, //
    TIM8_UP_IRQHandler, //
    TIM8_TRG_COM_IRQHandler, //
    TIM8_CC_IRQHandler, //
    ADC3_IRQHandler, //
    0, //
    0, //
    0, //
    SPI3_IRQHandler, //
    UART4_IRQHandler, //
    UART5_IRQHandler, //
    TIM6_DAC_IRQHandler, //
    TIM7_IRQHandler, //
    DMA2_Channel1_IRQHandler, //
    DMA2_Channel2_IRQHandler, //
    DMA2_Channel3_IRQHandler, //
    DMA2_Channel4_IRQHandler, //
    DMA2_Channel5_IRQHandler, //
    ADC4_IRQHandler, //
    0, //
    0, //
    COMP1_2_3_IRQHandler, //
    COMP4_5_6_IRQHandler, //
    COMP7_IRQHandler, //
    0, //
    0, //
    0, //
    0, //
    0, //
    0, //
    0, //
    USB_HP_IRQHandler, //
    USB_LP_IRQHandler, //
    USBWakeUp_RMP_IRQHandler, //
    0, //
    0, //
    0, //
    0, //
    FPU_IRQHandler //
};


// Main entry point after reset
void Reset_Handler(void)
{
    // Copy .data section from FLASH to RAM
    uint8_t *src = (uint8_t *)&__etext;
    for (uint8_t *dst=(uint8_t *)&__data_start__; dst<(uint8_t *)&__data_end__; dst++)
    {
        *dst = *src;
        src++;
    }

    // Initialize .bss section with zero
    for (uint8_t *dst=(uint8_t *)&__bss_start__; dst<(uint8_t *)&__bss_end__; dst++)
    {
        *dst = 0;
    }

    // Initialize peripheral
    systemInit();

    // Reset MSP
    asm ("mov r0, %0\n\t"
        "msr msp, r0"
        :
        : "r" (&__StackTop));

    // Jump to main
    main();

    while(1)
        ; // Wait forever

}

// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
void __attribute__ ((section(".irq_handlers"))) Default_Handler(void)
{
  while (1)
    ; // Infinite Loop
}

void __attribute__ ((naked)) __setMSP(uint32_t address)
{
    asm ("msr msp, r0");
}
