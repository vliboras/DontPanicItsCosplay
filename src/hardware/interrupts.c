/**
 * @file interrupts.c
 *
 * @brief interrupts file
 *
 * @ingroup a group name
 */

/**********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/
#include <stdint.h>

#include "lpc2292.h"

/**********************************************************************************************************************
 * PUBLIC FUNCTION PROTOTYPES
 **********************************************************************************************************************/


/**
 * @brief IRQ Handler is the interrupt handler for IRQs
 * 
 * @details It retrieves the address of the corresponding interrupt handler from the VIC
 * vector address register and calls it.
 * After handling the interrupt, it clears the VIC vector address register to acknowledge
 * that the interrupt has been processed.
 *  
 */
void IRQ_Handler(void) __attribute__((interrupt("IRQ")));

/**********************************************************************************************************************
 * PUBLIC FUNCTIONS
 **********************************************************************************************************************/

void IRQ_Handler(void)
{
    void (*handler)(void);

    handler = (void (*)(void))VICVectAddr;
    handler();
    VICVectAddr = 0;
}

/**********************************************************************************************************************
 * END OF FILE
 **********************************************************************************************************************/
