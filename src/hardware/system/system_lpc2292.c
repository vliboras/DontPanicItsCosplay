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
static uint32_t system_core_clock = 4000000;

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
 * @brief Sets the system clock frequency.
 *
 * This function sets the system clock frequency to the specified value.
 * It does not perform any hardware configuration; it simply updates the
 * global variable representing the system clock frequency.
 *
 * @param frequency The desired system clock frequency in Hz
 */
void system_clock_set(uint32_t frequency)
{
    system_core_clock = frequency;
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
