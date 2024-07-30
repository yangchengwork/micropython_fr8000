/*
 * Memory Spaces Definitions.
 *
 * Need modifying for a specific board. 
 *   FLASH.ORIGIN: starting address of flash
 *   FLASH.LENGTH: length of flash
 *   RAM.ORIGIN: starting address of RAM bank 0
 *   RAM.LENGTH: length of RAM bank 0
 *
 * The values below can be addressed in further linker scripts
 * using functions like 'ORIGIN(RAM)' or 'LENGTH(RAM)'.
 */

MEMORY
{
  FLASH (rx)    : ORIGIN = 0x08002000, LENGTH = 1016K
  PRAM (xrw)    : ORIGIN = 0x1FFE0000, LENGTH = 128K
  SRAM (rw)     : ORIGIN = 0x20000000, LENGTH = 256K
}

/* 
 * The entry point is informative, for debuggers and simulators,
 * since the Cortex-M vector points to it anyway.
 */
ENTRY(Reset_Handler)

_Min_Heap_Size = 0x1000 ;	/* required amount of heap  */

/* Sections Definitions */

SECTIONS
{
    /* The startup code into "FLASH" Rom type memory */
    .isr_vector :
    {
        . = ALIGN(8);
        KEEP(*(.isr_vector))        /* Startup code */
        . = ALIGN(8);
    } >FLASH

    /*
     * The program code is stored in the .text section, 
     * which goes to FLASH.
     */
    .text :
    {
    	. = ALIGN(8);
        *(.text .text.*)            /* all remaining code */
        
        *(.glue_7)         /* glue arm to thumb code */
	    *(.glue_7t)        /* glue thumb to arm code */
	    *(.eh_frame)
	
	    KEEP (*(.init))
	    KEEP (*(.fini))

		. = ALIGN(8);
       	_etext = .;
    } >FLASH

    /* Constant data into "ROM" Rom type memory */
    .rodata :
    {
        . = ALIGN(8);
        *(.rodata)         /* .rodata sections (constants, strings, etc.) */
        *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
        . = ALIGN(8);
    } >FLASH
    
    .ARM.extab   : { 
		. = ALIGN(8);
		*(.ARM.extab* .gnu.linkonce.armextab.*)
		. = ALIGN(8);
	} >FLASH

	.ARM : {
		. = ALIGN(8);
		__exidx_start = .;
		*(.ARM.exidx*)
		__exidx_end = .;
		. = ALIGN(8);
	} >FLASH

	.preinit_array     :
	{
		. = ALIGN(8);
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array*))
		PROVIDE_HIDDEN (__preinit_array_end = .);
		. = ALIGN(8);
	} >FLASH

	.init_array :
	{
		. = ALIGN(8);
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array*))
		PROVIDE_HIDDEN (__init_array_end = .);
		. = ALIGN(8);
	} >FLASH

	.fini_array :
	{
		. = ALIGN(8);
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT(.fini_array.*)))
		KEEP (*(.fini_array*))
		PROVIDE_HIDDEN (__fini_array_end = .);
		. = ALIGN(8);
	} >FLASH

    /*
     * The initialised data section.
     *
     * The program executes knowing that the data is in the RAM
     * but the loader puts the initial values in the FLASH (inidata).
     * It is one task of the startup to copy the initial values from 
     * FLASH to RAM.
     */
    /* Used by the startup to initialize data */
    _siram_code = LOADADDR(.ram_code);
    .ram_code :
    {
        . = ALIGN(8);
        _sram_code = .;         /* create a global symbol at ram_code start */
        *(.ram_code.*)          /* RAM code */
        *(ram_code*)            /* RAM code */

        . = ALIGN(8);
        _eram_code = .;         /* define a global symbol at ram_code end */
    } >PRAM  AT>FLASH

    .share_mem (NOLOAD) :
    {
        . = ALIGN(8);
        *(share_mem)
        . = ALIGN(8);
    } >SRAM

    /* Used by the startup to initialize data */
    _sidata = LOADADDR(.data);
    .data :
    {
        . = ALIGN(8);
        _sdata = .;        /* create a global symbol at data start */
        *(.data)           /* .data sections */
        *(.data*)          /* .data* sections */

        . = ALIGN(8);
        _edata = .;        /* define a global symbol at data end */

    } >SRAM AT>FLASH
    
    /*
     * The uninitialised data sections. NOLOAD is used to avoid
     * the "section `.bss' type changed to PROGBITS" warning
     */

    /* The primary uninitialised data section. */
    .bss (NOLOAD) :
    {
        /* This is used by the startup in order to initialize the .bss section */
        _sbss = .;         /* define a global symbol at bss start */
        __bss_start__ = _sbss;
        *(.bss)
        *(.bss*)
        *(COMMON)

        . = ALIGN(8);
        _ebss = .;         /* define a global symbol at bss end */
        __bss_end__ = _ebss;
    } >SRAM
    
    /* User_heap section, used to check that there is enough "SRAM" Ram type memory left */
    ._user_heap :
    {
        . = ALIGN(8);
        PROVIDE ( _heap_start = . );
        . = . + _Min_Heap_Size;
        PROVIDE ( _heap_end = . );
        . = ALIGN(8);
    } >SRAM
}
