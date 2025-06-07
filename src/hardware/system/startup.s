.syntax unified
.arm

/* Interrupt Vector Table */
.section .isr_vector, "ax", %progbits
.word Reset_Handler
.word Undef_Handler
.word SPV_Handler
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

    /* todo: check it */

    /* Set SP for Undefined mode (0x1B) */
    MRS R0, CPSR
    BIC R0, R0, #0x1F
    ORR R0, R0, #0x1B
    MSR CPSR_c, R0
    LDR SP, =_und_stack_end

    /* Set SP for FIQ mode (0x11) */
    MRS R0, CPSR
    BIC R0, R0, #0x1F
    ORR R0, R0, #0x11
    MSR CPSR_c, R0
    LDR SP, =_fiq_stack_end

    /* Set SP for IRQ mode (0x12) */
    MRS R0, CPSR
    BIC R0, R0, #0x1F
    ORR R0, R0, #0x12
    MSR CPSR_c, R0
    LDR SP, =_irq_stack_end

    /* Set SP for Abort mode (0x17) */
    MRS R0, CPSR
    BIC R0, R0, #0x1F
    ORR R0, R0, #0x17
    MSR CPSR_c, R0
    LDR SP, =_abt_stack_end

    /* Set SP for User/System mode (0x1F) */
    MRS R0, CPSR
    BIC R0, R0, #0x1F
    ORR R0, R0, #0x1F
    MSR CPSR_c, R0
    LDR SP, =_usr_stack_end

    /* Work in Supervisor mode as deafult */
    /* Set SP for Supervisor mode (0x13) */
    MRS R0, CPSR
    BIC R0, R0, #0x1F
    ORR R0, R0, #0x13
    MSR CPSR_c, R0
    LDR SP, =_spv_stack_end
    
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
    BL system_init

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


/* Temporary system_init stub */
.weak system_init
system_init:
    BX LR

.weak Undef_Handler
Undef_Handler:
    B .

.weak SPV_Handler
SPV_Handler:
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

/* Peripheral Handlers */
.weak TIMER0_IRQHandler
.set TIMER0_IRQHandler, Default_IRQ_Handler

.weak UART0_IRQHandler
.set UART0_IRQHandler, Default_IRQ_Handler

/* TODO: Add other */