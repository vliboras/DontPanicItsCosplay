/* linker_script.ld - Linker script for LPC2292 (ARM7TDMI) with 64KB RAM */

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 256K    /* Flash memory */
    RAM (rwx)   : ORIGIN = 0x40000000, LENGTH = 64K     /* 64KB RAM */
}

/* Entry Point */
ENTRY(Reset_Handler)

/* Define stack sizes */
_STACK_SIZE = 0x2000;       /* 8KB main stack */
_IRQ_STACK_SIZE = 0x800;    /* 2KB IRQ stack */
_FIQ_STACK_SIZE = 0x400;     /* 1KB FIQ stack */
_SVC_STACK_SIZE = 0x400;     /* 1KB SVC stack */
_ABT_STACK_SIZE = 0x400;     /* 1KB ABT stack */
_UND_STACK_SIZE = 0x400;     /* 1KB UND stack */

/* Section Definitions */
SECTIONS
{
    /* Interrupt Vector Table goes first into FLASH */
    .vectors :
    {
        . = ALIGN(4);
        KEEP(*(.vectors))
        . = ALIGN(4);
    } > FLASH

    /* Code section */
    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        *(.glue_7)         /* glue arm to thumb code */
        *(.glue_7t)        /* glue thumb to arm code */
        *(.eh_frame)
        
        KEEP(*(.init))
        KEEP(*(.fini))
        
        . = ALIGN(4);
        _etext = .;        /* end of text section */
    } > FLASH

    /* Read-only data */
    .rodata :
    {
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH

    /* ARM.exidx section for exception handling */
    .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    } > FLASH

    /* Initialized data sections - goes into RAM, load address in FLASH */
    _sidata = LOADADDR(.data);
    .data : AT ( _sidata )
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > RAM

    /* Uninitialized data section (BSS) */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        __bss_start__ = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = .;
    } > RAM

    /* Heap */
    .heap :
    {
        . = ALIGN(4);
        __end__ = .;
        PROVIDE(end = .);
        __HeapBase = .;
        . = ORIGIN(RAM) + LENGTH(RAM) - _STACK_SIZE - _IRQ_STACK_SIZE - _FIQ_STACK_SIZE 
                          - _SVC_STACK_SIZE - _ABT_STACK_SIZE - _UND_STACK_SIZE;
        __HeapLimit = .;
    } > RAM

    /* Stack sections */
    .stack :
    {
        . = ALIGN(4);
        _estack = .;
        
        /* Main stack */
        . = . + _STACK_SIZE;
        __stack_top__ = .;
        
        /* IRQ stack */
        __irq_stack_bottom__ = .;
        . = . + _IRQ_STACK_SIZE;
        __irq_stack_top__ = .;
        
        /* FIQ stack */
        __fiq_stack_bottom__ = .;
        . = . + _FIQ_STACK_SIZE;
        __fiq_stack_top__ = .;
        
        /* SVC stack */
        __svc_stack_bottom__ = .;
        . = . + _SVC_STACK_SIZE;
        __svc_stack_top__ = .;
        
        /* ABT stack */
        __abt_stack_bottom__ = .;
        . = . + _ABT_STACK_SIZE;
        __abt_stack_top__ = .;
        
        /* UND stack */
        __und_stack_bottom__ = .;
        . = . + _UND_STACK_SIZE;
        __und_stack_top__ = .;
    } > RAM

    /* Remove information from the standard libraries */
    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }

    /* Provide additional symbols if needed */
    PROVIDE(__stack = __stack_top__);
    PROVIDE(__irq_stack = __irq_stack_top__);
    PROVIDE(__fiq_stack = __fiq_stack_top__);
    PROVIDE(__svc_stack = __svc_stack_top__);
    PROVIDE(__abt_stack = __abt_stack_top__);
    PROVIDE(__und_stack = __und_stack_top__);
}