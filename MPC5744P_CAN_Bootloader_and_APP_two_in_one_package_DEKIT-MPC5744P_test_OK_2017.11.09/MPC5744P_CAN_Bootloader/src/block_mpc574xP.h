/************************************************************************
*            (c) Copyright Freescale Semiconductor, 2012-2014           *
*                         All Rights Reserved                           *
*************************************************************************
*************************************************************************
*                                                                       *
*                   Standard Software Driver for C55                    *
*                                                                       *
* FILE NAME     :  block_mpc57xx.h                                      *
* DATE          :  09.19.2014                                           *
*                                                                       *
* AUTHOR        :  FPT Team                                             *
* E-mail        :  r56611@freescale.com                                 *
*                                                                       *
************************************************************************/

/******************************* CHANGES ********************************
 1.0.0    12.29.2011      FPT Team       Initial Version for RTM version
 ***********************************************************************/
#ifndef __BLOCK_MPC57XX__ 
#define __BLOCK_MPC57XX__ 

#include "Flash_Driver_common.h"
#include "ssd_c55.h"

#include "c55flash_mpc57xx.h"


/* Lock State */
#define UNLOCK_LOW_BLOCKS               0x0000000C  /*low block 2 & 3 for bootloader should be locked and protected */
#define UNLOCK_MID_BLOCKS               0x00000000
#define UNLOCK_HIGH_BLOCKS              0x00000000  /*high block 6*64KB=384KB, address from 0xFA_0000 to 0xFF_FFFF*/
#ifdef RAM_TARGET
#define UNLOCK_FIRST256_BLOCKS          0x00
#endif
#ifdef FLASH_TARGET
#define UNLOCK_FIRST256_BLOCKS          0x00   /* 8*256K = 2MB for use application*/
#endif
#define UNLOCK_SECOND256_BLOCKS         0x00000000
/* bit mask for block select for each address space */
/* need to un-select the blocks which are not accessed in demo*/
#define ALL_LOW_BLOCK_SEL              (~UNLOCK_LOW_BLOCKS)
#define ALL_MID_BLOCK_SEL              (~UNLOCK_MID_BLOCKS)
#define ALL_HIGH_BLOCK_SEL             (~UNLOCK_HIGH_BLOCKS)
#define ALL_FIRST256_BLOCK_SEL         (~UNLOCK_FIRST256_BLOCKS)
#define ALL_SECOND256_BLOCK_SEL        (~UNLOCK_SECOND256_BLOCKS)
/* index of block that should not be accessed in demo code*/
#ifdef RAM_TARGET
#define SKIP_IDX_NUM                    0x1
#endif

#ifdef FLASH_TARGET
//#define SKIP_IDX_NUM                  0x5    /*for Flash SSD demo project*/

#define SKIP_IDX_NUM                    0x2    /*for bootloader project*/
#endif

/* macros to simulate RWE and ERR */
#define EER_ADDR                    0x00F9C000
#define RWE_ADDR                    0x00F98000
#define RWE_LOW_SEL                 0x4
#define RWE_MID_SEL                 0x0
#define RWE_HIGH_SEL                0x0
#define RWE_FIRST256_SEL            0x0
#define RWE_SECOND256_SEL           0x0


extern const UINT32 BLOCK_START_ADDRS[NUM_BLOCK_ALL];
extern const UINT32 BLOCK_END_ADDRS[NUM_BLOCK_ALL];
extern const UINT32 SKIP_BLOCK_IDX[SKIP_IDX_NUM];
extern void InitMemRegionInfo(PMEM_REGION_INFO pMemRegionInfo);

#endif /* End of (__BLOCK_MPC57XX__) */
