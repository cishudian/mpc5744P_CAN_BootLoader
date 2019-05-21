/************************************************************************
*            (c) Copyright Freescale Semiconductor, 2012-2014           *
*                         All Rights Reserved                           *
*************************************************************************
*************************************************************************
*                                                                       *
*                   Standard Software Driver for C55                    *
*                                                                       *
* FILE NAME     :  demo_utils .h                                        *
* DATE          :  09.19.2014                                           *
*                                                                       *
* AUTHOR        :  FPT Team                                             *
* E-mail        :  r56611@freescale.com                                 *
*                                                                       *
************************************************************************/

/******************************* CHANGES ********************************
 1.0.0    12.29.2011      FPT Team       Initial Version for RTM version
 ***********************************************************************/
#ifndef __DEMO_UTILS__
#define __DEMO_UTILS__

/* buffer size */
#define BUFFER_SIZE_BYTE                0x1000

/************************************************************************
*    Extern variables
************************************************************************/

extern SSD_CONFIG ssdConfig;
extern CONTEXT_DATA dummyCtxData;
extern CONTEXT_DATA pgmCtxData;
extern CONTEXT_DATA bcCtxData;
extern CONTEXT_DATA pvCtxData;
extern CONTEXT_DATA csCtxData;
extern CONTEXT_DATA exPgmCtxData;

extern UINT32  buffer[BUFFER_SIZE_BYTE / C55_WORD_SIZE];

/************************************************************************
*    Extern functions used in demo code
************************************************************************/

extern UINT32 App_FlashErase( PSSD_CONFIG pSSDConfig,
                        UINT8 eraseOption,
                        UINT32 lowBlockSelect,
                        UINT32 midBlockSelect,
                        UINT32 highBlockSelect,
                        N256K_BLOCK_SEL n256KBlockSelect);

extern UINT32 App_FlashProgram(PSSD_CONFIG pSSDConfig,
                      BOOL factoryPgmFlag,
                      UINT32 dest,
                      UINT32 size,
                      UINT32 source,
                      PCONTEXT_DATA pCtxData );

extern UINT32 App_BlankCheck( PSSD_CONFIG pSSDConfig,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 *pFailedAddress,
                    UINT32 *pFailedData,
                    PCONTEXT_DATA pCtxData );

extern UINT32 App_CheckSum( PSSD_CONFIG pSSDConfig,
                  UINT32 dest,
                  UINT32 size,
                  UINT32 *pSum,
                  PCONTEXT_DATA pCtxData );

extern UINT32 App_ProgramVerify( PSSD_CONFIG pSSDConfig,
                       UINT32 dest,
                       UINT32 size,
                       UINT32 source,
                       UINT32 *pFailedAddress,
                       UINT32 *pFailedData,
                       UINT32 *pFailedSource,
                       PCONTEXT_DATA pCtxData );

extern UINT32 WaitOperationFinish(PSSD_CONFIG pSSDConfig,
                           UINT8 modeOp,
                           PCONTEXT_DATA pCtxData);
extern void User_App(void);

extern BOOL TurnOnMCR_EER(PSSD_CONFIG pSSDConfig);
extern BOOL TurnOnMCR_RWE(PSSD_CONFIG pSSDConfig);
extern UINT32 EER_exception_handler(UINT32 return_address, UINT16 instruction);
extern UINT32 SyncProgram (PSSD_CONFIG pSSDConfig, UINT32 dest, UINT32 size, UINT32 source);
extern void EnableSoftwareWatchdog (void);
extern void DisableSoftwareWatchdog (void);
extern void DisableFlashControllerCache(UINT32 flashConfigReg,
                                        UINT32 disableVal,
                                        UINT32 *origin_pflash_pfcr);
extern void RestoreFlashControllerCache(UINT32 flashConfigReg,
                                        UINT32 pflash_pfcr);

#endif /* of DEMO_UTILS */
