/************************************************************************
*            (c) Copyright Freescale Semiconductor, 2012-2014           *
*                         All Rights Reserved                           *
*************************************************************************
*************************************************************************
*                                                                       *
*                   Standard Software Driver for C55                    *
*                                                                       *
* FILE NAME     :  block_mpc57xx.c                                     *
* DATE          :  09.19.2014                                           *
*                                                                       *
* AUTHOR        :  FPT Team                                             *
* E-mail        :  r56611@freescale.com                                 *
*                                                                       *
************************************************************************/

/******************************* CHANGES ********************************
 1.0.0    12.29.2011      FPT Team       Initial Version for RTM version
 ***********************************************************************/

#include "ssd_types.h"

#include "block_mpc574xP.h"

/* Block start addresses */
const UINT32 BLOCK_START_ADDRS[NUM_BLOCK_ALL] =
{
    /* LOW */
    0x00800000, 0x00804000, 0x00F98000, 0x00F9C000, 
    /* MID */
    0x00808000, 0x00810000, 
    /* HIGH */
    0x00FA0000, 0x00FB0000, 0x00FC0000, 0x00FD0000, 0x00FE0000, 0x00FF0000, 
    /* 256K */
    0x01000000, 0x01040000, 0x01080000, 0x010C0000,
    0x01100000, 0x01140000, 0x01180000, 0x011C0000
};

/* Block end addresses */
const UINT32 BLOCK_END_ADDRS[NUM_BLOCK_ALL] =
{
    /* LOW */
    0x00803FFF, 0x00807FFF, 0x00F9BFFF, 0x00F9FFFF, 
    /* MID */
    0x0080FFFF, 0x00817FFF, 
    /* HIGH */
    0x00FAFFFF, 0x00FBFFFF, 0x00FCFFFF, 0x00FDFFFF, 0x00FEFFFF, 0x00FFFFFF,
    /* 256K */
    0x0103FFFF, 0x0107FFFF, 0x010BFFFF, 0x010FFFFF,    
    0x0113FFFF, 0x0117FFFF, 0x011BFFFF, 0x011FFFFF,
};

/* index of block which must not be accessed in demo*/
/* shall not access to BAF block and the blocks in the same partition with block storing code*/
#ifdef RAM_TARGET
const UINT32 SKIP_BLOCK_IDX[SKIP_IDX_NUM] =
{
    0x1 /* BAF block */
};
#endif

#ifdef FLASH_TARGET
const UINT32 SKIP_BLOCK_IDX[SKIP_IDX_NUM] =
{

	/*for Flash SSD demo project*/
//    0x1, /* BAF block */
//    0xC, /* block in the same partition to store code. This should be updated in pair with linker file in flash*/
//    0xD, /* block in the same partition to store code. This should be updated in pair with linker file in flash*/
//    0xE, /* block in the same partition to store code. This should be updated in pair with linker file in flash*/
//    0xF /* block in the same partition to store code. This should be updated in pair with linker file in flash*/

	/*for bootloader project, the flash block to ship depends on the project linker command file*/
	0x2, /* bootloader block, Flash low 2 block: address 0x00F98000 to 0x00F9BFFF*/
	0x3, /* bootloader block, Flash low 3 block address 0x00F9C000 to 0x00F9FFFF */
};
#endif

/* Initialize Memory region information */
void InitMemRegionInfo(PMEM_REGION_INFO pMemRegionInfo)
{

}
