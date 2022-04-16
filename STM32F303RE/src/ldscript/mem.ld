/* 
 * Linker script to configure memory regions. 
 * Modified from template of ARM GCC compiler 
 */

MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
  RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 64K
}

/* Define the Stack Size in Words*/
__stack_size = 0xC00;


ENTRY(Reset_Handler)

/* Set stack top to end of RAM, and stack limit move down by
 * size of stack section */
__stack_section_start = ORIGIN(RAM) + LENGTH(RAM) - __stack_size*4;

SECTIONS
{
	/* Interrupt vectors */
	.isr_vector : ALIGN(4)
    {
        __vectors_start = ABSOLUTE(.) ;
		KEEP(*(.isr_vector))

    } >FLASH
	
	/* IRQ handlers */
	.irq_handlers : ALIGN(4)
    {
        __handlers_start = ABSOLUTE(.) ;
		*(.reset_handler)
		*(.irq_handlers)

    } >FLASH

	/* Instruction and RO data sections */
	.text :
	{
		*(.text*)
		*(.rodata*)
	} > FLASH

	/* To copy multiple ROM to RAM sections
	 * uncomment .copy.table section */
	/*
	.copy.table :
	{
		. = ALIGN(4);
		__copy_table_start__ = .;
		LONG (__etext)
		LONG (__data_start__)
		LONG (__data_end__ - __data_start__)
		LONG (__etext2)
		LONG (__data2_start__)
		LONG (__data2_end__ - __data2_start__)
		__copy_table_end__ = .;
	} > FLASH
	*/

	/* To clear multiple BSS sections,
	 * uncomment .zero.table section */
	/*
	.zero.table :
	{
		. = ALIGN(4);
		__zero_table_start__ = .;
		LONG (__bss_start__)
		LONG (__bss_end__ - __bss_start__)
		LONG (__bss2_start__)
		LONG (__bss2_end__ - __bss2_start__)
		__zero_table_end__ = .;
	} > FLASH
	*/

	/* Location counter can end up 2byte aligned with narrow Thumb code but
	   __etext is assumed by startup code to be the LMA of a section in RAM
	   which must be 4byte aligned */
	__etext = ALIGN (4);

	/* Initialized global variables */
	.data : AT (__etext)
	{

		__data_start__ = .;
		*(.data*)

		. = ALIGN(4);

		/* All data end */
		__data_end__ = .;

	} > RAM

	/* Unitialized global variables */
	.bss :
	{
		. = ALIGN(4);
		__bss_start__ = .;
		*(.bss*)
		. = ALIGN(4);
		__bss_end__ = .;
	} > RAM

	/* Stack */
	.stack __stack_section_start :
	{
		*(.stack)
	} > RAM

	/* Set stack top to end of RAM, and stack limit move down by
	 * size of stack section */
	__StackTop = ORIGIN(RAM) + LENGTH(RAM);
	__StackLimit = __StackTop - SIZEOF(.stack);
	PROVIDE(__stack = __StackTop);
}
