/**
 * @file system_lpc2292.c
 *
 * @brief System initialization for LPC2292
 *
 * @ingroup System
 */

/**********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/

#include "lpc2292.h"
#include <stdint.h>

/**********************************************************************************************************************
 * EXTERNAL/GLOBAL/OTHER DATA
 **********************************************************************************************************************/

/** @brief System core clock frequency in Hz */
uint32_t system_core_clock = 4000000;

/**********************************************************************************************************************
 * PUBLIC FUNCTIONS
 **********************************************************************************************************************/

/**
 * @brief Gets the current system clock frequency.
 *
 * This function returns the current system clock frequency in Hz.
 *
 * @return Current system clock frequency in Hz
 */
uint32_t system_clock_get(void)
{
    return system_core_clock;
}

/**
 * @brief Initializes the system clock and other hardware components.
 *
 * This function is called during system startup to configure the system clock
 * and any other necessary hardware initialization.
 *
 * @return None
 */
void system_init(void)
{
    return;
}

/**********************************************************************************************************************
 * END OF FILE
 **********************************************************************************************************************/
