/************************************************************************
*            (c) Copyright Freescale Semiconductor, 2012-2014           *
*                         All Rights Reserved                           *
*************************************************************************
*************************************************************************
*                                                                       *
*                   Standard Software Driver for C55                    *
*                                                                       *
* FILE NAME     :  demo_common.h                                        *
* DATE          :  09.19.2014                                           *
*                                                                       *
* AUTHOR        :  FPT Team                                             *
* E-mail        :  r56611@freescale.com                                 *
*                                                                       *
************************************************************************/

/******************************* CHANGES ********************************
 1.0.0    12.29.2011      FPT Team       Initial Version for RTM version
 ***********************************************************************/
#ifndef __DEMO_COMMON__ 
#define __DEMO_COMMON__ 



#define DEMO_PASS       0x00000000
#define DEMO_FAIL       0xFFFFFFFF 

#define WRITE32(address, value)     (*(VUINT32*)(address) = (value))
#define READ32(address)             ((UINT32)(*(VUINT32*)(address)))
#define SET32(address, value)       (*(VUINT32*)(address) |= (value))
#define CLEAR32(address, value)     (*(VUINT32*)(address) &= ~(value))

#define READ64(address)             ((long long)(*(volatile long long*)(address)))
#define READ8(address)             ((UINT8)(*(VUINT8*)(address)))

extern const unsigned long FlashInit_C[];
extern const unsigned long FlashErase_C[];
extern const unsigned long FlashEraseAlternate_C[];
extern const unsigned long BlankCheck_C[];
extern const unsigned long FlashProgram_C[];
extern const unsigned long ProgramVerify_C[];
extern const unsigned long FlashCheckStatus_C[];
extern const unsigned long GetLock_C[];
extern const unsigned long SetLock_C[];
extern const unsigned long CheckSum_C[];
extern const unsigned long FlashSuspend_C[];
extern const unsigned long FlashResume_C[];
extern const unsigned long UserMarginReadCheck_C[];
extern const unsigned long FlashArrayIntegrityCheck_C[];
extern const unsigned long FlashArrayIntegrityResume_C[];
extern const unsigned long FlashArrayIntegritySuspend_C[];
extern const unsigned long OverPgmProtGetStatus_C[];
extern const unsigned long FlashAbort_C[];
extern const unsigned long FlashExpressProgram_C[];
#define pFlashInit                  ((PFLASHINIT)FlashInit_C)
#define pFlashErase                 ((PFLASHERASE)FlashErase_C)
#define pFlashEraseAlternate        ((PFLASHERASEALTERNATE)FlashEraseAlternate_C)
#define pBlankCheck                 ((PBLANKCHECK)BlankCheck_C)
#define pFlashProgram               ((PFLASHPROGRAM)FlashProgram_C)
#define pFlashCheckStatus           ((PFLASHCHECKSTATUS)FlashCheckStatus_C)
#define pProgramVerify              ((PPROGRAMVERIFY) ProgramVerify_C)
#define pGetLock                    ((PGETLOCK)GetLock_C)
#define pSetLock                    ((PSETLOCK)SetLock_C)
#define pCheckSum                   ((PCHECKSUM)CheckSum_C)
#define pFlashSuspend               ((PFLASHSUSPEND)FlashSuspend_C)
#define pFlashResume                ((PFLASHRESUME)FlashResume_C)
#define pUserMarginReadCheck        ((PUSERMARGINREADCHECK)UserMarginReadCheck_C)
#define pFlashArrayIntegrityCheck   ((PFLASHARRAYINTEGRITYCHECK)FlashArrayIntegrityCheck_C)
#define pFlashArrayIntegrityResume  ((PFLASHARRAYINTEGRITYRESUME)FlashArrayIntegrityResume_C)
#define pFlashArrayIntegritySuspend ((PFLASHARRAYINTEGRITYSUSPEND)FlashArrayIntegritySuspend_C)
#define pOverPgmProtGetStatus       ((POVERPGMPROTGETSTATUS)OverPgmProtGetStatus_C)
#define pFlashAbort                 ((PFLASHABORT)FlashAbort_C)
#define pFlashExpressProgram        ((PFLASHEXPRESSPROGRAM)FlashExpressProgram_C)

#endif /* End of (__DEMO_COMMON__) */
