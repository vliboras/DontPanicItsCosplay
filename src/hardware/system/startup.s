/* TODO: ADD STACK SWITCHING  */
.syntax unified
.arch arm7tdmi
.arm

/* Interrupt Vector Table */
.section .vectors, "ax"
.word Reset_Handler
.word Undef_Handler
.word SWI_Handler
.word Prefetch_Abort_Handler
.word Data_Abort_Handler
.word 0                  /* Reserved vector */
.word IRQ_Handler
.word FIQ_Handler


/* Code Section */
.section .text
.arm

/* System Reset Handler */
.global Reset_Handler
.type  Reset_Handler, %function
Reset_Handler:
    /* Initialize stack pointer */
    LDR SP, =_estack
    
    /* Copy initialized data from FLASH to RAM */
    LDR R0, =_sdata
    LDR R1, =_edata
    LDR R2, =_sidata
    BL CopyData

    /* Clear zero-initialized data section */
    LDR R0, =_sbss
    LDR R1, =_ebss
    BL ZeroBSS

    /* Hardware initialization */
    BL SystemInit

    /* Transfer control to main application */
    LDR R0, =main
    BX R0
    /* Return security */
    B .
.size Reset_Handler, . - Reset_Handler

/* Data Section Copy Routine */
CopyData:
    CMP R0, R1
    BEQ CopyEnd
    LDR R3, [R2], #4
    STR R3, [R0], #4
    B CopyData

CopyEnd:
    BX LR

/* BSS Section Zero Initialization */
ZeroBSS:
    MOV R2, #0
ZeroLoop:
    CMP R0, R1
    BEQ ZeroEnd
    STR R2, [R0], #4
    B ZeroLoop
ZeroEnd:
    BX LR


/* Temporary SystemInit stub */
.weak SystemInit
SystemInit:
    BX LR

.weak HardFault_Handler
HardFault_Handler:
    B .

.weak Undef_Handler
Undef_Handler:
    B .

.weak SWI_Handler
SWI_Handler:
    B .

.weak Prefetch_Abort_Handler
Prefetch_Abort_Handler:
    B .

.weak Data_Abort_Handler
Data_Abort_Handler:
    B .

.weak IRQ_Handler
IRQ_Handler:
    B .

.weak FIQ_Handler
FIQ_Handler:
    B .

/* Default IRQ Handler */
.weak Default_IRQ_Handler
Default_IRQ_Handler:
    B .