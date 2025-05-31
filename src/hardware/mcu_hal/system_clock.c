/**
 * @file bsp.c
 *
 * @brief bsp file
 *
 * @ingroup a group name
 */

/**********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/

#include "system_clock.h"
#include "lpc2292.h"

/**********************************************************************************************************************
 * DEFINES
 **********************************************************************************************************************/

/**
 * @name PLLCON Register Bit Fields
 * @{
 */
#define PLLCON_PLLE_BIT   (0UL) /**< PLL Enable bit position */
#define PLLCON_PLLE_WIDTH (1UL) /**< PLL Enable bit width */
#define PLLCON_PLLC_BIT   (1UL) /**< PLL Connect bit position */
#define PLLCON_PLLC_WIDTH (1UL) /**< PLL Connect bit width */
/** @} */

/**
 * @name PLLCFG Register Bit Fields
 * @{
 */
#define PLLCFG_MSEL_BIT   (0UL) /**< PLL Multiplier bit position */
#define PLLCFG_MSEL_WIDTH (5UL) /**< PLL Multiplier bit width */
#define PLLCFG_PSEL_BIT   (5UL) /**< PLL Divider bit position */
#define PLLCFG_PSEL_WIDTH (2UL) /**< PLL Divider bit width */
/** @} */

/**
 * @name PLLSTAT Register Bit Fields
 * @{
 */
#define PLLSTAT_MSEL_BIT    (0UL)  /**< MSEL field (read-back) bit position */
#define PLLSTAT_MSEL_WIDTH  (5UL)  /**< MSEL field width */
#define PLLSTAT_PSEL_BIT    (5UL)  /**< PSEL field (read-back) bit position */
#define PLLSTAT_PSEL_WIDTH  (2UL)  /**< PSEL field width */
#define PLLSTAT_PLLE_BIT    (8UL)  /**< PLL Enabled status bit */
#define PLLSTAT_PLLE_WIDTH  (1UL)  /**< Width of PLLE bit */
#define PLLSTAT_PLLC_BIT    (9UL)  /**< PLL Connected status bit */
#define PLLSTAT_PLLC_WIDTH  (1UL)  /**< Width of PLLC bit */
#define PLLSTAT_PLOCK_BIT   (10UL) /**< PLL Lock status bit */
#define PLLSTAT_PLOCK_WIDTH (1UL)  /**< Width of PLOCK bit */
/** @} */

/**
 * @name PLL Feed Sequences
 * @{
 */
#define PLLFEED_SEQUENCE_AA (0xAAUL) /**< First feed sequence value */
#define PLLFEED_SEQUENCE_55 (0x55UL) /**< Second feed sequence value */
/** @} */

/**
 * @name APBDIV (VPBDIV) Clock Divider Options
 * @{
 */
#define APBDIV        (VPBDIV) /**< Peripheral bus clock divider register */
#define APBDIV_SAME   (0x01UL) /**< PCLK = CCLK   */
#define APBDIV_HALF   (0x02UL) /**< PCLK = CCLK/2 */
#define APBDIV_FOURTH (0x00UL) /**< PCLK = CCLK/4 */
/** @} */

/**********************************************************************************************************************
 * PRIVATE TYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * PRIVATE FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * PRIVATE DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * EXTERNAL/GLOBAL/OTHER DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * EXTERNAL/WEAK/OTHER FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * PRIVATE FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * PUBLIC FUNCTIONS
 **********************************************************************************************************************/

uint8_t system_clock_init(void)
{
    /* Enable PLL (not connect) */
    PLLCON = ((1 & PLLCON_PLLE_WIDTH) << PLLCON_PLLE_BIT);

    /* Set CCLK 60 MHz */
    PLLCFG = ((4 & PLLCFG_MSEL_WIDTH) << PLLCFG_MSEL_BIT) | ((0 & PLLCFG_PSEL_WIDTH) << PLLCFG_PSEL_BIT);

    PLLFEED = PLLFEED_SEQUENCE_AA;
    PLLFEED = PLLFEED_SEQUENCE_55;

    /* Wait until PLL locks (PLOCK = 1) */
    while (!(PLLSTAT & ((1 & PLLSTAT_PLOCK_WIDTH) << PLLSTAT_PLOCK_BIT)))
    {
        /* Wait for PLOCK bit to be set */
    }

    /* Enable and connect the PLL as the system clock source */
    PLLCON = ((1 & PLLCON_PLLE_WIDTH) << PLLCON_PLLE_BIT) | ((1 & PLLCON_PLLC_WIDTH) << PLLCON_PLLC_BIT);

    PLLFEED = PLLFEED_SEQUENCE_AA;
    PLLFEED = PLLFEED_SEQUENCE_55;

    /* (PCLK = CCLK / 2 = 30 MHz) */
    APBDIV = APBDIV_HALF;

    return 0;
}

/**********************************************************************************************************************
 * END OF FILE
 **********************************************************************************************************************/
