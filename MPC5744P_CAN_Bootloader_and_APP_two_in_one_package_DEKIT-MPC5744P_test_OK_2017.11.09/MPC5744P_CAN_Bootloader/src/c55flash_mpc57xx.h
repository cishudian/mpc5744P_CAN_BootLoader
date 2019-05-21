/************************************************************************
*            (c) Copyright Freescale Semiconductor, 2012-2014           *
*                         All Rights Reserved                           *
*************************************************************************
*************************************************************************
*                                                                       *
*                   Standard Software Driver for C55                    *
*                                                                       *
* FILE NAME     :  c55flash_mpc57xx.h                                   *
* DATE          :  09.19.2014                                           *
*                                                                       *
* AUTHOR        :  FPT Team                                             *
* E-mail        :  r56611@freescale.com                                 *
*                                                                       *
************************************************************************/

/******************************* CHANGES ********************************
 1.0.0    12.29.2011      FPT Team       Initial Version for RTM version
 ***********************************************************************/
#ifndef _C55FLASH_MPC57XX_ 
#define _C55FLASH_MPC57XX_ 


/************************************************************************
*    flash dependent configuration
************************************************************************/
#define C55_REG_BASE                    0xFFFE0000
#define MAIN_ARRAY_BASE                 0x00800000
#define UTEST_ARRAY_BASE                0x00400000
#define UTEST_ARRAY_SIZE                0x00004000

#define C55_PROGRAMMABLE_SIZE           0x80

/* block number for each address space */
#define NUM_LOW_BLOCK                          4
#define NUM_MID_BLOCK                          2
#define NUM_HIGH_BLOCK                         6
#define NUM_256K_BLOCK_FIRST                   8
#define NUM_256K_BLOCK_SECOND                  0
#define NUM_BLOCK_ALL                   (NUM_LOW_BLOCK + NUM_MID_BLOCK + NUM_HIGH_BLOCK + NUM_256K_BLOCK_FIRST + NUM_256K_BLOCK_SECOND)

/* sofware watchdog definition */
#define SWT_REG                0xFC050000UL
#define SWT_CR_OFFSET        0x00000000UL
#define SWT_SR_OFFSET        0x00000010UL

/* Macro data cache avaiable in the main core */
#define DCACHE_AVAILABLE               1

/* Flash controller defination */
#define FLASH_FMC                   0xFC030000
/* Offsets of Platform Flash Configuration Register 1, 2, 3 */
#define FLASH_PFCR1           0             /* Offset address of PFCR1 */
#define FLASH_PFCR2           0             /* Offset address of PFCR2 */
#define FLASH_PFCR3           8             /* Offset address of PFCR3 */
#define FLASH_FMC_BFEN        0x00000001    /* Enable PBFEN bit */

#endif /* End of (_C55FLASH_MPC57XX_) */

