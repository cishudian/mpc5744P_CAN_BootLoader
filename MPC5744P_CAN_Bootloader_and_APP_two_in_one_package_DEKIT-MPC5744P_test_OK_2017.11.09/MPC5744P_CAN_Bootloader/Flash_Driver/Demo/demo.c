/************************************************************************
*            (c) Copyright Freescale Semiconductor, 2012-2014           *
*                         All Rights Reserved                           *
*************************************************************************
*************************************************************************
*                                                                       *
*                   Standard Software Driver for C55                    *
*                                                                       *
* FILE NAME     :  demo.c                                               *
* DATE          :  09.19.2014                                           *
*                                                                       *
* AUTHOR        :  FPT Team                                             *
* E-mail        :  r56611@freescale.com                                 *
*                                                                       *
************************************************************************/

/******************************* CHANGES ********************************
 1.0.0    12.29.2011      FPT Team       Initial Version for RTM version
 ***********************************************************************/



#include    "demo.h"

#include "derivative.h" /* include peripheral declarations */

extern void xcptn_xmpl(void);

void ErrorTrap(UINT32 returnCode);

SSD_CONFIG ssdConfig = {
    C55_REG_BASE,         /* C55 control register base */
    MAIN_ARRAY_BASE,      /* base of main array */
    { 0, 0, 0 },          /* blocks info of low address space */
    { 0, 0, 0 },          /* blocks info of mid address space */
    { 0, 0, 0 },          /* blocks info of high address space */
    0,                    /* number of blocks in 256K address space */
    UTEST_ARRAY_BASE,     /* base of UTEST array */
    TRUE,                 /* interface flag indicate main or alternate interface */
    C55_PROGRAMMABLE_SIZE,/* programmable size */
    FALSE                 /* debug mode selection */
};

CONTEXT_DATA dummyCtxData;
CONTEXT_DATA pgmCtxData;
CONTEXT_DATA bcCtxData;
CONTEXT_DATA pvCtxData;
CONTEXT_DATA csCtxData;
CONTEXT_DATA exPgmCtxData;

/* Source buffer for program and verify */
UINT32  buffer[BUFFER_SIZE_BYTE / C55_WORD_SIZE];
MEM_REGION_INFO memRegionInfo;

#if DCACHE_AVAILABLE
    extern void dcache_disable(void);
    extern void dcache_enable(void);
#endif

UINT32 main1(void)
{
    register UINT32 returnCode;           /* Return code from each SSD function. */
    register UINT32 demoResult;

    register UINT32 dest;                 /* destination address */
    UINT32 size;                 /* size applicable */
    UINT32 source;               /* source address for program and verify */

    UINT32 failedAddress;          /* save the failed address in flash */
    UINT32 failedData;             /* save the failed data in flash */
    UINT32 failedSource;           /* Save the failed source for verification */

    UINT32 blkLockState;         /* block lock status to be retrieved */

    UINT32 sum;                  /* check sum result */
    UINT32 i;                    /* Index */
    UINT32 j;
    BOOL skipFlag;
    UINT32 temp;

    UINT32 lowBlockSelect;
    UINT32 midBlockSelect;
    UINT32 highBlockSelect;
    UINT32 pflash_pfcr0, pflash_pfcr1, pflash_pfcr2, pflash_pfcr3;
    N256K_BLOCK_SEL n256KBlockSelect;


    xcptn_xmpl ();              /* Configure and Enable Interrupts */

    /**************************************************************************/
    /* Initialize source buffer                                               */
    /**************************************************************************/
    for (i = 0; i < (BUFFER_SIZE_BYTE / C55_WORD_SIZE); i++)
    {
        buffer[i] = i;
    }

    /* set up function pointers in context data */
    pgmCtxData.pReqCompletionFn = pFlashProgram;
    bcCtxData.pReqCompletionFn = pBlankCheck;
    pvCtxData.pReqCompletionFn = pProgramVerify;
    csCtxData.pReqCompletionFn = pCheckSum;
    exPgmCtxData.pReqCompletionFn = pFlashExpressProgram;
    /* If user wants to run this demo for alternate interface, please assign */
    /* ssdConfig.mainInterfaceFlag = FALSE and ssdConfig.programmablesize = 32 here */
    /* then all below codes can be applied for alternate interface */

    /* Initialize for express program */
    InitMemRegionInfo(&memRegionInfo);

    /**************************************************************************/
    /* Initialize Flash                                                       */
    /**************************************************************************/
    ssdConfig.c55RegBase = C55_REG_BASE;
    ssdConfig.mainArrayBase = MAIN_ARRAY_BASE;
    ssdConfig.uTestArrayBase = UTEST_ARRAY_BASE;
    ssdConfig.mainInterfaceFlag = TRUE;
    ssdConfig.programmableSize = C55_PROGRAMMABLE_SIZE;
    ssdConfig.BDMEnable = FALSE;

//#if DCACHE_AVAILABLE
//    dcache_disable();
//#endif
    /* Invalidate flash controller cache */
#ifndef MPC5777C
    DisableFlashControllerCache(FLASH_PFCR1, FLASH_FMC_BFEN, &pflash_pfcr1);
    DisableFlashControllerCache(FLASH_PFCR2, FLASH_FMC_BFEN, &pflash_pfcr2);
#endif

    /* Flash Init */
    returnCode = pFlashInit(&ssdConfig);

    if (C55_OK != returnCode)
    {
        ErrorTrap(returnCode);
    }

    /**************************************************************************/
    /* Lock to Protect UTest Address Space                                    */
    /**************************************************************************/
    returnCode = pGetLock(&ssdConfig, C55_BLOCK_UTEST, &blkLockState);
    if (C55_OK != returnCode)
    {
        ErrorTrap(returnCode);
    }

    if (!(blkLockState & 0x00000001))
    {
        returnCode = pSetLock(&ssdConfig, C55_BLOCK_UTEST, 0x1);
        if (C55_OK != returnCode)
        {
            ErrorTrap(returnCode);
        }
    }

    /**************************************************************************/
    /* Unlock all blocks in low address space                                 */
    /**************************************************************************/
    returnCode = pSetLock(&ssdConfig, C55_BLOCK_LOW, UNLOCK_LOW_BLOCKS);
    if (C55_OK != returnCode)
    {
        ErrorTrap(returnCode);
    }

    /**************************************************************************/
    /* Unlock all blocks in mid address space                                 */
    /**************************************************************************/
    returnCode = pSetLock(&ssdConfig, C55_BLOCK_MID, UNLOCK_MID_BLOCKS);
    if (C55_OK != returnCode)
    {
        ErrorTrap(returnCode);
    }

    /**************************************************************************/
    /* Unlock all blocks in high address space                                */
    /**************************************************************************/
    returnCode = pSetLock(&ssdConfig, C55_BLOCK_HIGH, UNLOCK_HIGH_BLOCKS);
    if (C55_OK != returnCode)
    {
        ErrorTrap(returnCode);
    }
    /**************************************************************************/
    /* Unlock all blocks in 256K blocks                                       */
    /**************************************************************************/
    returnCode = pSetLock(&ssdConfig, C55_BLOCK_256K_FIRST, UNLOCK_FIRST256_BLOCKS);
    if (C55_OK != returnCode)
    {
        ErrorTrap(returnCode);
    }

    returnCode = pSetLock(&ssdConfig, C55_BLOCK_256K_SECOND, UNLOCK_SECOND256_BLOCKS);
    if (C55_OK != returnCode)
    {
        ErrorTrap(returnCode);
    }
    /**************************************************************************
    Call FlashErase, BlankCheck, FlashProgram, ProgramVerify, CheckSum
    for each individual block.
    **************************************************************************/
    /* Enable software watchdog to demonstrate that user can reset watchdog
    in demo code if it is enabled */
    EnableSoftwareWatchdog();
    for (i = 0; i < NUM_BLOCK_ALL; i++)
    {
        skipFlag = FALSE;
        for (j = 0; j < SKIP_IDX_NUM; j++)
        {
            temp = SKIP_BLOCK_IDX[j];
            if (i == temp)
            {
                skipFlag = TRUE;
                break;
            }
        }
        if (skipFlag == FALSE)
        {
            lowBlockSelect = 0x0;
            midBlockSelect = 0;
            highBlockSelect = 0;
            n256KBlockSelect.first256KBlockSelect = 0;
            n256KBlockSelect.second256KBlockSelect = 0;

            if (i < NUM_LOW_BLOCK)
            {
                lowBlockSelect = (1 << i);
            }
            else if (i < (NUM_LOW_BLOCK + NUM_MID_BLOCK))
            {
                temp = i - NUM_LOW_BLOCK;
                midBlockSelect = (1 << temp);
            }
            else if (i < (NUM_LOW_BLOCK + NUM_MID_BLOCK + NUM_HIGH_BLOCK))
            {
                temp = i - (NUM_LOW_BLOCK + NUM_MID_BLOCK);
                highBlockSelect = (1 << temp);
            }
            else if (i < (NUM_LOW_BLOCK + NUM_MID_BLOCK + NUM_HIGH_BLOCK + NUM_256K_BLOCK_FIRST))
            {

                temp = i - (NUM_LOW_BLOCK + NUM_MID_BLOCK + NUM_HIGH_BLOCK);
                n256KBlockSelect.first256KBlockSelect = (1 << temp);
            }
            else
            {
                temp = i - (NUM_LOW_BLOCK + NUM_MID_BLOCK + NUM_HIGH_BLOCK + NUM_256K_BLOCK_FIRST);
                n256KBlockSelect.second256KBlockSelect = (1 << temp);
            }
            /* erase block individually */
            demoResult = App_FlashErase(&ssdConfig,
                                     C55_ERASE_MAIN,
                                     lowBlockSelect,
                                     midBlockSelect,
                                     highBlockSelect,
                                     n256KBlockSelect);
            if (demoResult == DEMO_FAIL)
            {
                ErrorTrap(demoResult);
            }
            dest = BLOCK_START_ADDRS[i];
            size = BLOCK_END_ADDRS[i] + 1 - BLOCK_START_ADDRS[i];
            /* blank check */
            demoResult = App_BlankCheck(&ssdConfig,
                                        dest,
                                        size,
                                        &failedAddress,
                                        &failedData,
                                        &bcCtxData);
            if (demoResult == DEMO_FAIL)
            {
                ErrorTrap(demoResult);
            }
            /* program to beginning of block */
            dest = BLOCK_START_ADDRS[i];
            size = BUFFER_SIZE_BYTE;
            source = (UINT32)buffer;
            demoResult = App_FlashProgram(&ssdConfig,
                                        FALSE,
                                        dest,
                                        size,
                                        source,
                                        &pgmCtxData);
            if (demoResult == DEMO_FAIL)
            {
                ErrorTrap(demoResult);
            }
            /* Program verify */
            demoResult = App_ProgramVerify(&ssdConfig,
                                        dest,
                                        size,
                                        source,
                                        &failedAddress,
                                        &failedData,
                                        &failedSource,
                                        &pvCtxData);
            if (demoResult == DEMO_FAIL)
            {
                ErrorTrap(demoResult);
            }
            /* Program to end of block */
            dest = BLOCK_END_ADDRS[i] + 1 - BUFFER_SIZE_BYTE;
            size = BUFFER_SIZE_BYTE;
            source = (UINT32)buffer;
            demoResult = App_FlashProgram(&ssdConfig,
                                        FALSE,
                                        dest,
                                        size,
                                        source,
                                        &pgmCtxData);
            if (demoResult == DEMO_FAIL)
            {
                ErrorTrap(demoResult);
            }
            /* Program verify */
            demoResult = App_ProgramVerify(&ssdConfig,
                                        dest,
                                        size,
                                        source,
                                        &failedAddress,
                                        &failedData,
                                        &failedSource,
                                        &pvCtxData);
            if (demoResult == DEMO_FAIL)
            {
                ErrorTrap(demoResult);
            }
            /* Check sum */
            demoResult = App_CheckSum(&ssdConfig,
                                        dest,
                                        size,
                                        &sum,
                                        &csCtxData);
            if (demoResult == DEMO_FAIL)
            {
                ErrorTrap(demoResult);
            }

            /* Demo for C55FP flash module */
            if (ssdConfig.programmableSize & C55FP_INDICATOR)
            {
                /* Fast programming */
                dest = BLOCK_START_ADDRS[i] + BUFFER_SIZE_BYTE;
                size = BUFFER_SIZE_BYTE;
                source = (UINT32)BLOCK_START_ADDRS[i];
                demoResult = App_FlashProgram(&ssdConfig,
                                            PGM_OPT_FAST_MASK,
                                            dest,
                                            size,
                                            source,
                                            &pgmCtxData);
                if (demoResult == DEMO_FAIL)
                {
                    ErrorTrap(demoResult);
                }
                /* Program verify */
                demoResult = App_ProgramVerify(&ssdConfig,
                                            dest,
                                            size,
                                            source,
                                            &failedAddress,
                                            &failedData,
                                            &failedSource,
                                            &pvCtxData);
                if (demoResult == DEMO_FAIL)
                {
                    ErrorTrap(demoResult);
                }

                if (i < (NUM_LOW_BLOCK + NUM_MID_BLOCK + NUM_HIGH_BLOCK))
                {
                    /* Express progaram */


                    dest += BUFFER_SIZE_BYTE;
                    size = BUFFER_SIZE_BYTE;
                    source = (UINT32)BLOCK_START_ADDRS[i];
                    demoResult = App_FlashExpressProgram(&ssdConfig,
                                                        memRegionInfo,
                                                        dest,
                                                        size,
                                                        source,
                                                        &exPgmCtxData);
                    if (demoResult == DEMO_FAIL)
                    {
                        ErrorTrap(demoResult);
                    }
                    /* Program verify */
                    demoResult = App_ProgramVerify(&ssdConfig,
                                                dest,
                                                size,
                                                source,
                                                &failedAddress,
                                                &failedData,
                                                &failedSource,
                                                &pvCtxData);
                    if (demoResult == DEMO_FAIL)
                    {
                        ErrorTrap(demoResult);
                    }
                }

            }// end of if (ssdConfig.programmableSize & C55FP_INDICATOR)
        }// end of if (skipFlag == FALSE)
    }// end of for (i = 0; i < NUM_BLOCK_ALL; i++)
    /**************************************************************************
    Call FlashErase to erase all blocks at the same time.
    **************************************************************************/
    lowBlockSelect = ALL_LOW_BLOCK_SEL;
    midBlockSelect = ALL_MID_BLOCK_SEL;
    highBlockSelect = ALL_HIGH_BLOCK_SEL;
    n256KBlockSelect.first256KBlockSelect = ALL_FIRST256_BLOCK_SEL;
    n256KBlockSelect.second256KBlockSelect = ALL_SECOND256_BLOCK_SEL;
    demoResult = App_FlashErase(&ssdConfig,
                             C55_ERASE_MAIN,
                             lowBlockSelect,
                             midBlockSelect,
                             highBlockSelect,
                             n256KBlockSelect);
    if (demoResult == DEMO_FAIL)
    {
        ErrorTrap(demoResult);
    }
    dest = BLOCK_START_ADDRS[i];
    size = BLOCK_END_ADDRS[i] + 1 - BLOCK_START_ADDRS[i];
    /* blank check to demonstrate that erase is successful*/
    for (i = 0; i < NUM_BLOCK_ALL; i++)
    {
        skipFlag = FALSE;
        for (j = 0; j < SKIP_IDX_NUM; j++)
        {
            if (i == SKIP_BLOCK_IDX[j])
            {
                skipFlag = TRUE;
                break;
            }
        }
        if (skipFlag == FALSE)
        {
            dest = BLOCK_START_ADDRS[i];
            size = BLOCK_END_ADDRS[i] + 1 - BLOCK_START_ADDRS[i];
            demoResult = App_BlankCheck(&ssdConfig,
                                        dest,
                                        size,
                                        &failedAddress,
                                        &failedData,
                                        &bcCtxData);
            if (demoResult == DEMO_FAIL)
            {
                ErrorTrap(demoResult);
            }
        }
    }

    /**************************************************************************/
    /* Stimulate RWW error                                                    */
    /**************************************************************************/
    skipFlag = TurnOnMCR_RWE(&ssdConfig);

    /**************************************************************************/
    /* Stimulate ECC error                                                    */
    /**************************************************************************/
    skipFlag = TurnOnMCR_EER(&ssdConfig);

    /* Disable software watchdog at the end of Demo */
    DisableSoftwareWatchdog();

    /* Restore flash controller cache */
#ifndef MPC5777C
    RestoreFlashControllerCache(FLASH_PFCR1 ,pflash_pfcr1);
    RestoreFlashControllerCache(FLASH_PFCR2 ,pflash_pfcr2);
#endif


    /* Enable Data cache if present */
//#if DCACHE_AVAILABLE
//    dcache_enable();
//#endif

    /* DEMO FINISHED */
    while(1)
    {
        /* do nothing */
    }
}

