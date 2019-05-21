
/************************************************************************
*            (c) Copyright Freescale Semiconductor, 2012-2014           *
*                         All Rights Reserved                           *
*************************************************************************
*************************************************************************
*                                                                       *
*                   Standard Software Driver for C55                    *
*                                                                       *
* FILE NAME     :  demo_utils.c                                         *
* DATE          :  09.19.2014                                           *
*                                                                       *
* AUTHOR        :  FPT Team                                             *
* E-mail        :  r56611@freescale.com                                 *
*                                                                       *
************************************************************************/

/******************************* CHANGES ********************************
 1.0.0    12.29.2011      FPT Team       Initial Version for RTM version
 ***********************************************************************/
#include "ssd_c55.h"
#include "ssd_c55_internal.h"


#include "block_mpc574xP.h"
#include "Flash_Driver_utils.h"

UINT32 g_usrCnt;

/***************************************************************************!

@name:  User_App

@brief: This function is to simulate the user's application code.

@param: N/A

@return: N/A

 ****************************************************************************/
void User_App(void)
{
    /* increase g_usrCnt */
    g_usrCnt ++;
    /* reset watchdog */
    WRITE32(SWT_REG + SWT_SR_OFFSET, 0x0000A602);

    WRITE32(SWT_REG + SWT_SR_OFFSET, 0x0000B480);
}

/***************************************************************************!

@name:  WaitOperationFinish

@brief: This function is to complete the whole operation.

@param: PSSD_CONFIG, UINT8, PCONTEXT_DATA

@return: UINT32

 ****************************************************************************/
UINT32 WaitOperationFinish(PSSD_CONFIG pSSDConfig,
                           UINT8 modeOp,
                           PCONTEXT_DATA pCtxData)
{
    UINT32 returnCode;
    UINT32 opResult;
    UINT32 demoResult;

    /* clear g_usrCnt */
    g_usrCnt = 0x0;

    while ((returnCode = pFlashCheckStatus(pSSDConfig, modeOp,
        &opResult, pCtxData)) == C55_INPROGRESS)
    {
        /* this driver is designed with asynchronous model, thus while the FlashCheckStatus function is still INPROGRESS,
        user can do any other task in user's application. If user does not do any task within this time interval, it is most
        likely synchronous model*/
        User_App();
    }
    if ((returnCode == C55_DONE) && (opResult == C55_OK))
    {
        demoResult = DEMO_PASS;
    }
    else
    {
        demoResult = DEMO_FAIL;
    }

    return (demoResult);
}
/***************************************************************************!

@name:  App_FlashErase

@brief: This function is used to demonstrate how to use FlashErase function
        in user's application.

@param: PSSD_CONFIG, UINT8, UINT32, UINT32, UINT32, N256K_BLOCK_SEL

@return: UINT32

 ****************************************************************************/
UINT32 App_FlashErase( PSSD_CONFIG pSSDConfig,
                        UINT8 eraseOption,
                        UINT32 lowBlockSelect,
                        UINT32 midBlockSelect,
                        UINT32 highBlockSelect,
                        N256K_BLOCK_SEL n256KBlockSelect)
{
    UINT32 returnCode;
    UINT32 demoResult;
    CONTEXT_DATA dummyCtxData;

    returnCode = pFlashErase(pSSDConfig,
                             eraseOption,
                             lowBlockSelect,
                             midBlockSelect,
                             highBlockSelect,
                             n256KBlockSelect);

    if(C55_OK == returnCode)
    {
        /* Wait until the operation finishes */
       demoResult = WaitOperationFinish(pSSDConfig, C55_MODE_OP_ERASE, &dummyCtxData);
    }
    else
    {
        demoResult = DEMO_FAIL;
    }
    return (demoResult);
}
/***************************************************************************!

@name:  App_FlashProgram

@brief: This function is used to demonstrate how to use FlashProgram function
        in user's application.

@param: PSSD_CONFIG, BOOL, UINT32, UINT32, UINT32, PCONTEXT_DATA

@return: UINT32

 ****************************************************************************/
UINT32 App_FlashProgram(PSSD_CONFIG pSSDConfig,
                      UINT8 pgmOption,
                      UINT32 dest,
                      UINT32 size,
                      UINT32 source,
                      PCONTEXT_DATA pCtxData )
{
    UINT32 returnCode;
    UINT32 demoResult;

    returnCode = pFlashProgram(pSSDConfig,pgmOption, dest, size, source, pCtxData);

    if(C55_OK == returnCode)
    {
        /* Wait until the operation finishes */
       demoResult = WaitOperationFinish(pSSDConfig, C55_MODE_OP_PROGRAM, pCtxData);
    }
    else
    {
        demoResult = DEMO_FAIL;
    }

    return (demoResult);
}
/***************************************************************************!

@name:  App_BlankCheck

@brief: This function is used to demonstrate how to use BlankCheck function
        in user's application.

@param: PSSD_CONFIG, UINT32, UINT32, UINT32*, UINT32*, PCONTEXT_DATA

@return: UINT32

 ****************************************************************************/
UINT32 App_BlankCheck( PSSD_CONFIG pSSDConfig,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 *pFailedAddress,
                    UINT32 *pFailedData,
                    PCONTEXT_DATA pCtxData )
{
    UINT32 returnCode;
    UINT32 demoResult;

    returnCode = pBlankCheck(pSSDConfig, dest, size, pFailedAddress, pFailedData, pCtxData);
    if(C55_OK == returnCode)
    {
        /* Wait until the operation finishes */
        demoResult = WaitOperationFinish(pSSDConfig, C55_MODE_OP_BLANK_CHECK, pCtxData);
    }
    else
    {
        demoResult = DEMO_FAIL;
    }
    return (demoResult);
}
/***************************************************************************!

@name:  App_CheckSum

@brief: This function is used to demonstrate how to use CheckSum function
        in user's application.

@param: PSSD_CONFIG, UINT32, UINT32, UINT32*, PCONTEXT_DATA

@return: UINT32

 ****************************************************************************/
UINT32 App_CheckSum( PSSD_CONFIG pSSDConfig,
                  UINT32 dest,
                  UINT32 size,
                  UINT32 *pSum,
                  PCONTEXT_DATA pCtxData )
{
    UINT32 returnCode;
    UINT32 demoResult;
    UINT32 temp;

    returnCode = pCheckSum(pSSDConfig, dest, size, pSum, pCtxData);
    if(C55_OK == returnCode)
    {
        /* Wait until the operation finishes */
       demoResult = WaitOperationFinish(pSSDConfig, C55_MODE_OP_CHECK_SUM, pCtxData);
       if (demoResult == DEMO_PASS)
       {
            /* verify to see check sum is correct */
            temp = 0x0;
            while (size > 0)
            {
                temp += *(VUINT32 *)dest;
                dest += 0x4;
                size -= 0x4;
            }
            if (temp != *pSum)
            {
                demoResult = DEMO_FAIL;
            }
       }
    }
    else
    {
        demoResult = DEMO_FAIL;
    }

    return (demoResult);

}
/***************************************************************************!

@name:  App_ProgramVerify

@brief: This function is used to demonstrate how to use ProgramVerify function
        in user's application.

@param: PSSD_CONFIG, UINT32, UINT32, UINT32, UINT32*, UINT32*, UINT32*, PCONTEXT_DATA

@return: UINT32

 ****************************************************************************/
UINT32 App_ProgramVerify( PSSD_CONFIG pSSDConfig,
                       UINT32 dest,
                       UINT32 size,
                       UINT32 source,
                       UINT32 *pFailedAddress,
                       UINT32 *pFailedData,
                       UINT32 *pFailedSource,
                       PCONTEXT_DATA pCtxData )
{
    UINT32 returnCode;
    UINT32 demoResult;

    returnCode = pProgramVerify(pSSDConfig, dest, size, source, pFailedAddress, pFailedData, pFailedSource, pCtxData);
    if(C55_OK == returnCode)
    {
        /* Wait until the operation finishes */
        demoResult = WaitOperationFinish(pSSDConfig, C55_MODE_OP_PROGRAM_VERIFY, pCtxData);
    }
    else
    {
        demoResult = DEMO_FAIL;
    }

    return (demoResult);

}

/***************************************************************************!

@name:  ErrorTrap

@brief: This function is used to trap the error code in demo

@param: UINT32

@return: N/A

 ****************************************************************************/
void ErrorTrap(UINT32 returnCode)
{
    VUINT32 failedReason;

    failedReason = returnCode;

    while(1)
    {
        ;
    }
}
/***************************************************************************!

@name:  SyncProgram

@brief: This function is used to program data to flash synchronously in order to
        create ECC error in flash.

@param: PSSD_CONFIG, UINT32, UINT32, UINT32

@return: UINT32

 ****************************************************************************/
UINT32 SyncProgram (PSSD_CONFIG pSSDConfig, UINT32 dest, UINT32 size, UINT32 source)
{
    UINT32          ret;
    UINT32          opResult;
    UINT32 returnCode;

    ret = pFlashProgram(pSSDConfig, FALSE, dest, size, source, &pgmCtxData);
    if (ret == C55_OK)
    {
        /* Wait until the operation finishes */
         while ((returnCode = pFlashCheckStatus(pSSDConfig, C55_MODE_OP_PROGRAM,
        &opResult, &pgmCtxData)) == C55_INPROGRESS);
    }
    return ret;
}

/***************************************************************************!

@name:  TurnOnMCR_RWE

@brief: This function is used to turn on RWE bit to simulate Read while write error.

@param: PSSD_CONFIG

@return: BOOL

 ****************************************************************************/
BOOL TurnOnMCR_RWE(PSSD_CONFIG pSSDConfig)
{
    BOOL result;
    UINT32 opResult;
    UINT32 data;
    UINT32 returnCode;
    N256K_BLOCK_SEL n256KBlockSelect;

    n256KBlockSelect.first256KBlockSelect = RWE_FIRST256_SEL;
    n256KBlockSelect.second256KBlockSelect = RWE_SECOND256_SEL;


    pFlashErase(pSSDConfig, C55_ERASE_MAIN, RWE_LOW_SEL, RWE_MID_SEL, RWE_HIGH_SEL, n256KBlockSelect);

    /* Read the flash while the program is in progress */
    data = READ32(RWE_ADDR);

    /* Check if the RWE bit is set */
    result = C55_REG_BIT_TEST(pSSDConfig->c55RegBase + C55_MCR, C55_MCR_RWE) != 0 ? TRUE : FALSE;

    /* Wait until the operation finishes */
     while ((returnCode = pFlashCheckStatus(pSSDConfig, C55_MODE_OP_ERASE,
        &opResult, &dummyCtxData)) == C55_INPROGRESS);

    return result;
}

/***************************************************************************!

@name:  TurnOnMCR_EER

@brief: This function is used to turn on EER bit to simulate ECC error.

@param: PSSD_CONFIG

@return: BOOL

 ****************************************************************************/
BOOL TurnOnMCR_EER(PSSD_CONFIG pSSDConfig)
{
    UINT32 buf1[2] = { 0x12345678, 0xAFDBCA42 };
    UINT32 buf2[2] = { 0xABCDEF12, 0xECDFBAD3 };
    UINT32 data;

    UINT32 size = C55_DWORD_SIZE;
    UINT32 source = (UINT32) buf1;

    buf1[0] = 0x12345678;
    buf1[1] = 0xAFDBCA42;

    buf2[0] = 0xABCDEF12;
    buf2[1] = 0xECDFBAD3;

    SyncProgram(pSSDConfig, EER_ADDR, size, source);

    source = (UINT32) buf2;
    SyncProgram(pSSDConfig, EER_ADDR, size, source);

    /* read to trigger EER error */
    data = READ32(EER_ADDR);
    /* Workaround delay for Cobra55 */
    for(size = 0; size < 2; size++);

    /* Check if the EER bit is set */
    return C55_REG_BIT_TEST(pSSDConfig->c55RegBase + C55_MCR, C55_MCR_EER) != 0 ? TRUE : FALSE;
}
/***************************************************************************!

@name:  EER_exception_handler

@brief: This function is the exception handler for RWE and ECC error.

@param: UINT32, UINT16

@return: UINT32

 ****************************************************************************/
UINT32 EER_exception_handler(UINT32 return_address, UINT16 instruction)
{
    C55_MCR_EER_RWE_SBC_RVE_RRE_AEE_EEE_CLEAR(ssdConfig.c55RegBase + C55_MCR);

#if(VLE_IS_ON)
    if ((instruction & 0x9000) == 0x1000)
    {
        // first 4 Bits have a value of 1,3,5,7
        return_address += 4;    // instruction was 32 bit
    }
    else
    {
        // first 4 Bits have a value of 0,2,4,6,8,9,A,B,C,D,E (and F, but F is reserved)
        return_address += 2;    // instruction was 16 bit
    }
#else
    return_address += 4;    // instruction was 32 bit
#endif

    return return_address;
}
/***************************************************************************!

@name:  EnableSoftwareWatchdog

@brief: This function is used to enable software watchdog.

@param: N/A

@return: N/A

 ****************************************************************************/
void EnableSoftwareWatchdog (void)
{

    if (!(READ32(SWT_REG + SWT_CR_OFFSET) & 0x1))
    {
        WRITE32(SWT_REG + SWT_SR_OFFSET, 0x0000C520);
        WRITE32(SWT_REG + SWT_SR_OFFSET, 0x0000D928);
        // enable SWT
        SET32(SWT_REG + SWT_CR_OFFSET, 0x1);
    }

}
/***************************************************************************!

@name:  DisableSoftwareWatchdog

@brief: This function is used to disable software watchdog.

@param: N/A

@return: N/A

 ****************************************************************************/
void DisableSoftwareWatchdog (void)
{
    WRITE32(SWT_REG + SWT_SR_OFFSET, 0x0000C520);
    WRITE32(SWT_REG + SWT_SR_OFFSET, 0x0000D928);
    // disable SWT
    CLEAR32(SWT_REG + SWT_CR_OFFSET, 0x1);
}

/***************************************************************************!

@name:  App_FlashExpressProgram

@brief: This function is used to demonstrate how to use FlashExpressProgram function
        in user's application.

@param: PSSD_CONFIG, BOOL, UINT32, UINT32, UINT32, PCONTEXT_DATA

@return: UINT32

 ****************************************************************************/
UINT32 App_FlashExpressProgram(PSSD_CONFIG pSSDConfig,
                            PMEM_REGION_INFO pMemRegionInfo,
                            UINT32 dest,
                            UINT32 size,
                            UINT32 source,
                            PCONTEXT_DATA pCtxData)
{
    UINT32 returnCode;
    UINT32 demoResult;

    returnCode = pFlashExpressProgram(pSSDConfig,pMemRegionInfo, dest, size, source, pCtxData);

    if(C55_OK == returnCode)
    {
        /* Wait until the operation finishes */
       demoResult = WaitOperationFinish(pSSDConfig, C55_MODE_OP_EXPRESS_PROGRAM, pCtxData);
    }
    else
    {
        demoResult = DEMO_FAIL;
    }

    return (demoResult);
}

/**************************************************************
*                          Disable Flash Cache                  *
***************************************************************/
void DisableFlashControllerCache(UINT32 flashConfigReg,
                                 UINT32 disableVal,
                                 UINT32 *origin_pflash_pfcr)
{
    /* Read the values of the register of flash configuration */
    *origin_pflash_pfcr = READ32(FLASH_FMC + flashConfigReg);

    /* Disable Caches */
    CLEAR32(FLASH_FMC + flashConfigReg, disableVal);
}

/*****************************************************************
*               Restore configuration register of FCM              *
******************************************************************/
void RestoreFlashControllerCache(UINT32 flashConfigReg,
                                 UINT32 pflash_pfcr)
{
    WRITE32(FLASH_FMC + flashConfigReg, pflash_pfcr);
}
