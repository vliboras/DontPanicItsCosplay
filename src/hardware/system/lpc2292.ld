/* Entry Point */
ENTRY(Reset_Handler)

_estack = ORIGIN(RAM) + LENGTH(RAM);

_reserved_ram_size = 10K;

_heap_size = 4K;

_fiq_stack_size = 1K;
_irq_stack_size = 1K;
_abt_stack_size = 512;
_und_stack_size = 512;
_spv_stack_size = 1K;
_usr_stack_size = LENGTH(RAM) - (_reserved_ram_size + _fiq_stack_size + _irq_stack_size + _abt_stack_size + _und_stack_size + _spv_stack_size + _heap_size);


MEMORY
{
    RAM (xrw)      : ORIGIN = 0x40000000, LENGTH = 64K
    FLASH (rx)      : ORIGIN = 0x00000000, LENGTH = 512K
}

SECTIONS
{
  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH

  /* The program code and other data goes into FLASH */
  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)    /* for debug */

    . = ALIGN(4);
    _etext = .;
  } >FLASH

  /* Constant data goes into FLASH */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } >FLASH

  /* For debug */
  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH

  /* used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data : 
  {
    . = ALIGN(8);
    _sdata = .;
    *(.data)
    *(.data*)

    . = ALIGN(8);
    _edata = .;
  } >RAM AT> FLASH

  
  /* Uninitialized data section */
  
  .bss :
  {
    . = ALIGN(8);
    _sbss = .;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(8);
    _ebss = .;
  } >RAM

  .heap (NOLOAD) : ALIGN(8)
  {
    . = ALIGN(8);
    _heap_start = .;
    . += _heap_size;
    _heap_end = .;
    . = ALIGN(8);
  } > RAM


  .stack_fiq (NOLOAD) : ALIGN(8)
  {
    . = ALIGN(8);
    _fiq_stack_start = .;
    . += _fiq_stack_size;
    _fiq_stack_end = .;
    . = ALIGN(8);
  } > RAM

  .stack_irq (NOLOAD) : ALIGN(8)
  {
    . = ALIGN(8);
    _irq_stack_start = .;
    . += _irq_stack_size;
    _irq_stack_end = .;
    . = ALIGN(8);
  } > RAM

  .stack_abt (NOLOAD) : ALIGN(8)
  {
    . = ALIGN(8);
    _abt_stack_start = .;
    . += _abt_stack_size;
    _abt_stack_end = .;
    . = ALIGN(8);
  } > RAM

  .stack_und (NOLOAD) : ALIGN(8)
  {
    . = ALIGN(8);
    _und_stack_start = .;
    . += _und_stack_size;
    _und_stack_end = .;
    . = ALIGN(8);
  } > RAM

  .stack_spv (NOLOAD) : ALIGN(8)
  {
    . = ALIGN(8);
    _spv_stack_start = .;
    . += _spv_stack_size;
    _spv_stack_end = .;
    . = ALIGN(8);
  } > RAM

  .stack_user (NOLOAD) : ALIGN(8)
  {
    . = ALIGN(8);
    _usr_stack_start = .;
    . += _usr_stack_size;
    _usr_stack_end = .;
    . = ALIGN(8);
  } > RAM

  ASSERT(_usr_stack_end <= _estack, "Error: RAM overflow: heap + stacks exceed RAM")

  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }
  /* Additional information for debug */
  .ARM.attributes 0 : { *(.ARM.attributes) }
}


