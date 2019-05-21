/************************************************************************
*            (c) Copyright Freescale Semiconductor, 2011 -2014          *
*                        All Rights Reserved                            *
*************************************************************************

*************************************************************************
*                                                                       *
*   Freescale reserves the right to make changes without further notice *
*   to any product herein to improve reliability, function or design.   *
*   Freescale does not assume any liability arising out of the          *
*   application or use of any product, circuit, or software described   *
*   herein; neither does it convey any license under its patent rights  *
*   nor the rights of others.                                           *
*                                                                       *
*   Freescale products are not designed, intended, or authorized for    *
*   use as components in systems intended for surgical implant into     *
*   the body, or other applications intended to support life, or for    *
*   any other application in which the failure of the Freescale product *
*   could create a situation where personal injury or death may occur.  *
*                                                                       *
*   Should Buyer purchase or use Freescale products for any such        *
*   unintended or unauthorized application, Buyer shall indemnify and   *
*   hold Freescale and its officers, employees, subsidiaries,           *
*   affiliates, and distributors harmless against all claims costs,     *
*   damages, and expenses, and reasonable attorney fees arising out     *
*   of, directly or indirectly, any claim of personal injury or death   *
*   associated with such unintended or unauthorized use, even if such   *
*   claim alleges that Freescale was negligent regarding the design     *
*   or manufacture of the part.                                         *
*                                                                       *
*   Freescale and the Freescale logo* are registered trademarks of      *
*   Freescale Semicondutor, Inc.                                        *
*                                                                       *
*************************************************************************

*************************************************************************
*                                                                       *
*               Standard Software Driver for C55                        *
*                                                                       *
* FILE NAME     :  ssd_c55.h                                            *
* DATE          :  December 19, 2011                                    *
* AUTHOR        :  FPT Team                                             *
* E-mail        :  r56611@freescale.com                                 *
*                                                                       *
*************************************************************************/

/******************************* CHANGES *********************************
  0.1.0   12.19.2011         FPT Team      Initial Version
  0.1.2   01.17.2012         FPT Team      Removed C55_ERROR_RANGE and
                                           SSD_CONFIG.uTestArraySize
  0.1.3   02.06.2012         FPT Team      Changed prototype of
                                           FlashCheckStatus
  0.1.4      02.24.2012         Chen He       Moved pReqCompletionFn to CONTEXT_DATA
                                           to be compiler independent
  0.1.5   03.23.2011         FPT Team      Update values of macros for suspend
                                           operation, resume operation and
                                           user's test mode and returnCode
                                           returned within FlashCheckStatus()
  0.1.6      09.13.2013         FPT Team       Add C55_ERROR_ENABLE error code
  0.1.7   07.08.2014         FPT Team      Add C55_ERROR_SET_LOCK error code
  0.1.8   08.0802014         FPT Team      Add FlashAbort function
  1.0.0   09.30.2014         FPT Team      Finalize to RTM v100 (no source
                                           code changed).
*************************************************************************/

#ifndef _SSD_C55_H_
#define _SSD_C55_H_

#include "ssd_types.h"

/*************************************************************************/
/*                       Compiler select macros                          */
/*************************************************************************/
#define CODE_WARRIOR        0x00U
#define DIAB_COMPILER       0x01U
#define GREEN_HILLS         0x02U

/*************************************************************************/
/*                  Offsets of C55 Control Registers                     */
/*************************************************************************/
#define C55_MCR             0x0000U       /* Module Configuration Register */
#define C55_MCRA            0x0004U       /* Alternate Module Configuration Register */
#define C55_MCRE            0x0008U       /* Extended Module Configuration Register */
#define C55_CTL             0x000CU         /* Module control register */
#define C55_LOCK0           0x0010U       /* Lock 0 Register */
#define C55_LOCK1           0x0014U       /* Lock 1 Register */
#define C55_LOCK2           0x0018U       /* Lock 2 Register */
#define C55_LOCK3           0x001CU       /* Lock 3 Register */
#define C55_LOCK0A          0x0028U       /* Alternate Lock 0 Register */
#define C55_LOCK1A          0x002CU       /* Alternate Lock 1 Register */
#define C55_SEL0            0x0038U       /* Select 0 Register */
#define C55_SEL1            0x003CU       /* Select 1 Register */
#define C55_SEL2            0x0040U       /* Select 2 Register */
#define C55_SEL3            0x0044U       /* Select 3 Register */
#define C55_ADR             0x0050U       /* Address Register */
#define C55_UT0             0x0054U       /* User Test 0 register */
#define C55_UM0             0x0058U       /* User MISR 0 Register */
#define C55_UM1             0x005CU       /* User MISR 1 Register */
#define C55_UM2             0x0060U       /* User MISR 2 Register */
#define C55_UM3             0x0064U       /* User MISR 3 Register */
#define C55_UM4             0x0068U       /* User MISR 4 Register */
#define C55_UM5             0x006CU       /* User MISR 5 Register */
#define C55_UM6             0x0070U       /* User MISR 6 Register */
#define C55_UM7             0x0074U       /* User MISR 7 Register */
#define C55_UM8             0x0078U       /* User MISR 8 Register */
#define C55_UM9             0x007CU       /* User MISR 9 Register */
#define C55_OPP0            0x0080U       /* Over-Program Protection 0 Register */
#define C55_OPP1            0x0084U       /* Over-Program Protection 1 Register */
#define C55_OPP2            0x0088U       /* Over-Program Protection 2 Register */
#define C55_OPP3            0x008CU       /* Over-Program Protection 3 Register */
#define C55_ELOCK0          0x00A0U       /* Erase Hardware Lock 0 Register */
#define C55_ELOCK1          0x00A4U       /* Erase Hardware Lock 1 Register */
#define C55_ELOCK2          0x00A8U       /* Erase Hardware Lock 2 Register */
#define C55_ELOCK3          0x00ACU       /* Erase Hardware Lock 3 Register */
#define C55_PLOCK0          0x00B0U       /* Program Hardware Lock 0 Register */
#define C55_PLOCK1          0x00B4U       /* Program Hardware Lock 1 Register */
#define C55_PLOCK2          0x00B8U       /* Program Hardware Lock 2 Register */
#define C55_PLOCK3          0x00BCU       /* Program Hardware Lock 3 Register */
#define C55_UD0             0x00D0U
#define C55_UD1             0x00D4U
#define C55_UD2             0x00D8U
#define C55_UD3             0x00DCU
#define C55_UD4             0x00E0U
#define C55_UD5             0x00E4U
#define C55_UA0             0x00E8U
#define C55_UA1             0x00ECU
#define C55_XMCR            0x00F0U         /* express module configuration register */
#define C55_XDATA           0x0100U


/*************************************************************************/
/*              C55 Module Control Registers Field Definitions           */
/*************************************************************************/
/* Bit map for Module Configuration Register */
#define C55_MCR_RVE         0x80000000U   /* Read Voltage Error */
#define C55_MCR_RRE         0x40000000U   /* Read Reference Error */
#define C55_MCR_AEE         0x20000000U   /* Address Encode Error */
#define C55_MCR_EEE         0x10000000U   /* ECC after ECC Error */
#define C55_MCR_EER         0x00008000U   /* ECC Event Error */
#define C55_MCR_RWE         0x00004000U   /* Read While Write Event Error */
#define C55_MCR_SBC         0x00002000U   /* Single Bit Correction Error */
#define C55_MCR_PEAS        0x00000800U   /* Program/Erase Access Space */
#define C55_MCR_DONE        0x00000400U   /* State Machine Status */
#define C55_MCR_PEG         0x00000200U   /* Program/Erase Good */
#define C55_MCR_PECIE       0x00000100U   /* Program/Erase Complete Interrupt Enable */
#define C55_MCR_FERS        0x00000080U   /* Factory Erase */
#define C55_MCR_PGM         0x00000010U   /* Program */
#define C55_MCR_PSUS        0x00000008U   /* Program Suspend */
#define C55_MCR_ERS         0x00000004U   /* Erase */
#define C55_MCR_ESUS        0x00000002U   /* Erase Suspend */
#define C55_MCR_EHV         0x00000001U   /* Enable High Voltage */
#define C55_MCR_PES         0x00010000U   /* Program and Erase Sequence Erro */
#define C55_MCR_PEP         0x00020000U   /* Program and Erase Protection Error */
#define C55_MCR_FEV         0x00100000U   /* Factory Erase Voltage Available */
#define C55_MCR_FPGM        0x00000040U   /* Fast program */
/* Bit map for module control register */
#define C55_CTL_L0          0x00000001U   /* Level Zero Reservation */
#define C55_CTL_L1          0x00000002U   /* Level One Reservation */
#define C55_CTL_L0MI        0x000F0000U   /* Level Zero Master ID */
#define C55_CTL_L1MI        0x00F00000U   /* Level One Master ID */
/* Bit map for express module configuration register */
#define C55_XMCR_XMEM       0x40000000U        /* XMEM bit - express memory region */
#define C55_XMCR_XH         0x20000000U        /* XH bit - express high region */
#define C55_XMCR_XM         0x00000000U        /* XM bit - express mid region */
#define C55_XMCR_XL         0x08000000U        /* XL bit - express low region */
#define C55_XMCR_X64K       0x02000000U        /* XL bit - express low region */
#define C55_XMCR_X32K       0x01000000U        /* XL bit - express low region */
#define C55_XMCR_X16K       0x00800000U        /* XL bit - express low region */
#define C55_XMCR_XADDR      0x007FFF80U        /* XADDR bit - express address */
#define C55_XMCR_XDONE      0x00000040U        /* XDONE bit - express state machine status */
#define C55_XMCR_XPEG       0x00000020U        /* XPEG bit - express program good */
#define C55_XMCR_XPGM       0x00000010U        /* XPGM bit - express program */
#define C55_XMCR_XDOK       0x00000004U        /* XDOK bit - express data OK */
#define C55_XMCR_XEHV       0x00000001U        /* XEHV bit - express enable high voltage */
#define XMCR_INTERNAL_ADDR_MASK    0x7BFFFF80U

/* User Test 0 Register */
#define C55_UT0_UTE         0x80000000U
#define C55_UT0_SBCE        0x40000000U
#define C55_UT0_AEIE        0x00004000U
#define C55_UT0_EDIE        0x00002000U
#define C55_UT0_EIE         0x00001000U
#define C55_UT0_NAIBP       0x00000200U
#define C55_UT0_AIBPE       0x00000100U
#define C55_UT0_AISUS       0x00000040U
#define C55_UT0_MRE         0x00000020U
#define C55_UT0_MRV         0x00000010U
#define C55_UT0_AIS         0x00000004U
#define C55_UT0_AIE         0x00000002U
#define C55_UT0_AID         0x00000001U

/*************************************************************************/
/*                   Return Codes for SSD functions                      */
/*************************************************************************/

#define C55_OK                      0x00000000U
#define C55_ERROR_ALIGNMENT         0x00000001U   /* Alignment error */
#define C55_ERROR_ENABLE            0x00000002U   /* it's impossible to enable an operation */
#define C55_ERROR_BUSY              0x00000004U   /* New program/erase cannot be preformed while previous high voltage operation in progress */
#define C55_ERROR_PGOOD             0x00000008U   /* The program operation is unsuccessful */
#define C55_ERROR_EGOOD             0x00000010U   /* The erase operation is unsuccessful */
#define C55_ERROR_NOT_BLANK         0x00000020U   /* There is non-blank location in the checked flash memory */
#define C55_ERROR_VERIFY            0x00000040U   /* There is a mismatch between the source data and content in the checked flash memory */
#define C55_ERROR_BLOCK_INDICATOR   0x00000080U   /* Invalid block indicator */
#define C55_ERROR_ALTERNATE         0x00000100U   /* The operation is unsupported via alternate interface */
#define C55_ERROR_FACTORY_OP        0x00000200U   /* Factory erase/program cannot be performed */
#define C55_ERROR_MISMATCH          0x00000400U   /* The MISR generated by the AIC hardware doesnot match the MISR passed by the user */
#define C55_ERROR_NO_BLOCK          0x00000800U   /* No blocks have been enabled for Array Integrity check */
#define C55_ERROR_ADDR_SEQ          0x00001000U   /* Invalid address sequence */
#define C55_ERROR_MARGIN_LEVEL      0x00002000U   /* Invalid margin level */
#define C55_ERROR_ERASE_OPTION      0x00004000U   /* Invalid erase option */
#define C55_ERROR_MODE_OP           0x00008000U   /* Invalid mode op */
#define C55_ERROR_SET_LOCK          0x00040000U   /* Invalid set lock value */
#define C55_ERROR_RESUME            0x00080000U   /* This master can't resume the P/E operation */
#define C55_ERROR_SUSPEND           0x00100000U   /* This master can't suspend the P/E operation */

#define C55_ERROR_ABORT_RESERVATION 0x00200000U
#define C55_ERROR_ECC_NO_DWORD_SEL  0x00400000U     /* there is no double word selected for ECC checking */
#define C55_ERROR_ECC_NOTCHECK      0x00800000U   /* don't check ECC logic for this case */
#define C55_ERROR_ECC_LOGIC         0x01000000U
#define C55_ERROR_ADDR_NOT_INVERTED 0x02000000U
#define C55_ERROR_ADDR_ENCODE       0x04000000U


#define C55_ERROR_PEP              0x08000000U
#define C55_ERROR_PES              0x10000000U

#define C55_DONE                    0x00010000U   /* Done status */
#define C55_INPROGRESS              0x00020000U   /* InProgress status */

/*************************************************************************/
/*            Predefined values for flags, options variables             */
/*************************************************************************/

/* Checking mode used in FlashCheckStatus */
#define C55_MODE_OP_PROGRAM         0x00U
#define C55_MODE_OP_ERASE           0x01U
#define C55_MODE_OP_PROGRAM_VERIFY  0x02U
#define C55_MODE_OP_BLANK_CHECK     0x03U
#define C55_MODE_OP_CHECK_SUM       0x04U
#define C55_MODE_OP_USER_TEST_CHECK 0x05U
#define C55_MODE_OP_EXPRESS_PROGRAM 0x06U

/* Indicators for getting/setting block lock state */
#define C55_BLOCK_LOW               0x00U   /* Block lock protection of low address space */
#define C55_BLOCK_MID               0x01U   /* Block lock protection of mid address space */
#define C55_BLOCK_HIGH              0x02U   /* Block lock protection of high address space */
#define C55_BLOCK_256K_FIRST        0x03U   /* Block lock protection of first 32 blocks in 256K address space */
#define C55_BLOCK_256K_SECOND       0x04U   /* Block lock protection of next 16 blocks in 256K address space */
#define C55_BLOCK_UTEST             0x05U   /* Block lock protection of UTest address space */

/* Indicators for getting program hardware lock state */
#define C55_BLOCK_LOW_PGM           0x40U   /* Block lock protection of low address space */
#define C55_BLOCK_MID_PGM           0x41U   /* Block lock protection of mid address space */
#define C55_BLOCK_HIGH_PGM          0x42U   /* Block lock protection of high address space */
#define C55_BLOCK_256K_FIRST_PGM    0x43U   /* Block lock protection of first 32 blocks in 256K address space */
#define C55_BLOCK_256K_SECOND_PGM   0x44U   /* Block lock protection of next 16 blocks in 256K address space */
#define C55_BLOCK_UTEST_PGM         0x45U   /* Block lock protection of UTest address space */

/* Indicators for getting erase hardware lock state */
#define C55_BLOCK_LOW_ERS           0x80U   /* Block lock protection of low address space */
#define C55_BLOCK_MID_ERS           0x81U   /* Block lock protection of mid address space */
#define C55_BLOCK_HIGH_ERS          0x82U   /* Block lock protection of high address space */
#define C55_BLOCK_256K_FIRST_ERS    0x83U   /* Block lock protection of first 32 blocks in 256K address space */
#define C55_BLOCK_256K_SECOND_ERS   0x84U   /* Block lock protection of next 16 blocks in 256K address space */
#define C55_BLOCK_UTEST_ERS         0x85U   /* Block lock protection of UTest address space */

/* Declarations for flash suspend operation */
#define C55_SUS_NOTHING             0x10U   /* No program/erase operation */
#define C55_PGM_WRITE               0x11U   /* A program sequence in interlock write stage. */
#define C55_ERS_WRITE               0x12U   /* An erase sequence in interlock write stage. */
#define C55_ERS_SUS_PGM_WRITE       0x13U   /* An erase-suspend program sequence in interlock write stage. */
#define C55_PGM_SUS                 0x14U   /* The program operation is in suspend state */
#define C55_ERS_SUS                 0x15U   /* The erase operation is in suspend state */
#define C55_ERS_SUS_PGM_SUS         0x16U   /* The erase-suspended program operation is in suspend state */
#define C55_USER_TEST_SUS           0x17U   /* The UTest check operation is in suspend state */

/* Declarations for flash resume operation */
#define C55_RES_NOTHING             0x20U   /* No suspended program/erase operation */
#define C55_RES_PGM                 0x21U   /* The program operation is resumed */
#define C55_RES_ERS                 0x22U   /* The erase operation is resumed */
#define C55_RES_ERS_PGM             0x23U   /* The erase-suspended program operation is resumed */
#define C55_RES_USER_TEST           0x24U   /* The UTest check operation is resumed */

#define C55_USER_TEST_BREAK_SBC     0x30U   /* The UTest check operation is broken by Single bit correction */
#define C55_USER_TEST_BREAK_DBD     0x31U   /* The UTest check operation is broken by Double bit detection */

/* Declarations of margin levels */
#define C55_MARGIN_LEVEL_PROGRAM    0x00U
#define C55_MARGIN_LEVEL_ERASE      0x01U

/* Declarations of address sequences */
#define C55_ADDR_SEQ_PROPRIETARY    0x00U
#define C55_ADDR_SEQ_LINEAR         0x01U

/* Declarations of break options */
#define C55_BREAK_NONE              0x00U   /* No break at all */
#define C55_BREAK_ON_DBD            0x01U   /* Break on Double bit detection */
#define C55_BREAK_ON_DBD_SBC        0x02U   /* Break on bot Double bit detection and Single bit correction */

/* definition for program option */
#define PGM_OPT_FACTORY_MASK        0x01U
#define PGM_OPT_L0RESRV_MASK        0x20U
#define PGM_OPT_L1RESRV_MASK        0x40U
#define PGM_OPT_LxRESRV_MASK        0x60U
#define PGM_OPT_FAST_MASK           0x80U

/* Declarations of erase options */
#define ERS_OPT_FACTORY_MASK        0x01U
#define ERS_OPT_UTEST_MASK          0x02U
#define ERS_OPT_L0RESRV_MASK        0x20U
#define ERS_OPT_L1RESRV_MASK        0x40U
#define ERS_OPT_LxRESRV_MASK        0x60U
/* below macros are not used in FlashErase anymore. However, still keep them here because user may already use it*/
#define C55_ERASE_MAIN              0x00U   /* Perform normal erase on main array */
#define C55_ERASE_MAIN_FERS         0x01U   /* Perform factory erase on main array */
#define C55_ERASE_UTEST             0x02U   /* Perform erase on UTest array */
#define C55_ERASE_UTEST_FERS        0x03U   /* Perform factory erase on UTest array */

/* Declarations of abort options */
#define C55_ABORT_RESERVATION       0x01U

#define C55_PGM_HARDWARE_LOCK       0x40U
#define C55_ERS_HARDWARE_LOCK       0x80U

/* definition for Flash ECC check */
#define C55_ECC_ERR_BIT_SET_ZERO    0x0U
#define C55_ECC_ERR_BIT_SET_ONE     0x1U
#define C55_ECC_ERR_BIT_SET_TWO     0x2U

/*************************************************************************/
/*                   Other Macros for SSD functions                      */
/*************************************************************************/

#define C55_WORD_SIZE               4U      /* size of a word in byte */
#define C55_DWORD_SIZE              8U      /* size of a double word in byte */
#define C55_PAGE_SIZE               32U     /* size of a page in byte */
#define C55_QPAGE_SIZE              128U    /* size of a quad-page in byte */
#define C55_FAST_PGM_ALIGN          0x1000U /* Fast program boundary*/

#define C55_USER_TEST_ENABLE_PASSWORD      0xF9F99999U
#define C55_FACTORY_ERASE_DIARY_LOCATION   0x0020U

#define C55_FLASH_MODULE_MASK       0xF0000000U
#define C55FP_INDICATOR             0x80000000U
#define C55_LOCK_MASK               0xC0U

#define NULL_POINTER                ((void *)0xFFFFFFFFU)

/* read and write macros */
#define WRITE8(address, value)      (*(VUINT8*)(address) = (value))
#define READ8(address)              ((UINT8)(*(VUINT8*)(address)))
#define SET8(address, value)        (*(VUINT8*)(address) |= (value))
#define CLEAR8(address, value)      (*(VUINT8*)(address) &= ~(value))

#define WRITE16(address, value)     (*(VUINT16*)(address) = (value))
#define READ16(address)             ((UINT16)(*(VUINT16*)(address)))
#define SET16(address, value)       (*(VUINT16*)(address) |= (value))
#define CLEAR16(address, value)     (*(VUINT16*)(address) &= ~(value))

#define WRITE32(address, value)     (*(VUINT32*)(address) = (value))
#define READ32(address)             ((UINT32)(*(VUINT32*)(address)))
#define SET32(address, value)       (*(VUINT32*)(address) |= (value))
#define CLEAR32(address, value)     (*(VUINT32*)(address) &= ~(value))

/* Macros for Accessing the Registers */
#define C55_REG_BIT_SET(address, mask)        (*(VUINT32*)(address) |= (mask))
#define C55_REG_BIT_CLEAR(address, mask)      (*(VUINT32*)(address) &= ~(mask))
#define C55_REG_BIT_TEST(address, mask)       (*(VUINT32*)(address) & (mask))
#define C55_REG_WRITE(address, value)         (*(VUINT32*)(address) = (value))
#define C55_REG_READ(address)                 ((UINT32)(*(VUINT32*)(address)))
#define C55_GET_BIT(value, position)          (UINT8)(((value) >> (position)) & 0x01U)

/* Set/Clear C55-MCR bits without affecting MCR-EER, MCR-RWE, and MCR-SBC */
#define C55_MCR_BIT_SET(MCRAddress, mask)      \
    C55_REG_WRITE(MCRAddress, ((mask | C55_REG_READ(MCRAddress)) & (~(C55_MCR_EER | C55_MCR_RWE | C55_MCR_SBC))))

#define C55_MCR_BIT_CLEAR(MCRAddress, mask)    \
    C55_REG_WRITE(MCRAddress, (((~mask) & C55_REG_READ(MCRAddress)) & (~(C55_MCR_EER | C55_MCR_RWE | C55_MCR_SBC))))

#define C55_MCR_EER_CLEAR(MCRAddress)    \
    C55_REG_WRITE(MCRAddress, (C55_REG_READ(MCRAddress) | C55_MCR_EER))

#define C55_MCR_RWE_CLEAR(MCRAddress)    \
    C55_REG_WRITE(MCRAddress, (C55_REG_READ(MCRAddress) | C55_MCR_RWE))

#define C55_MCR_SBC_CLEAR(MCRAddress)    \
    C55_REG_WRITE(MCRAddress, (C55_REG_READ(MCRAddress) | C55_MCR_SBC))

#define C55_MCR_EER_RWE_SBC_RVE_RRE_AEE_EEE_CLEAR(MCRAddress)    \
    C55_REG_WRITE(MCRAddress, (C55_REG_READ(MCRAddress) | C55_MCR_EER | C55_MCR_RWE | C55_MCR_SBC | \
                    C55_MCR_RVE | C55_MCR_RRE | C55_MCR_AEE | C55_MCR_EEE))
#define C55_MCR_PES_PEP_CLEAR(MCRAddress)    \
    C55_REG_WRITE(MCRAddress, (C55_REG_READ(MCRAddress) | C55_MCR_PES | C55_MCR_PEP))

#define C55_MAIN_ARRAY_SIZE(pSSDConfig)    \
    ((((pSSDConfig->lowBlockInfo.n16KBlockNum + pSSDConfig->midBlockInfo.n16KBlockNum + \
    pSSDConfig->highBlockInfo.n16KBlockNum) << 4U /*16*/) + \
    ((pSSDConfig->lowBlockInfo.n32KBlockNum + pSSDConfig->midBlockInfo.n32KBlockNum + \
    pSSDConfig->highBlockInfo.n32KBlockNum) << 5U /*32*/) + \
    ((pSSDConfig->lowBlockInfo.n64KBlockNum + pSSDConfig->midBlockInfo.n64KBlockNum + \
    pSSDConfig->highBlockInfo.n64KBlockNum) << 6U /*64*/) + \
    (pSSDConfig->n256KBlockNum << 8U)) << 10U /*1024*/)

#define C55_LOW_BLOCK_NUM(pSSDConfig)     \
    (pSSDConfig->lowBlockInfo.n16KBlockNum + pSSDConfig->lowBlockInfo.n32KBlockNum +  \
    pSSDConfig->lowBlockInfo.n64KBlockNum)

#define C55_MID_BLOCK_NUM(pSSDConfig)     \
    (pSSDConfig->midBlockInfo.n16KBlockNum + pSSDConfig->midBlockInfo.n32KBlockNum +  \
    pSSDConfig->midBlockInfo.n64KBlockNum)

#define C55_HIGH_BLOCK_NUM(pSSDConfig)     \
    (pSSDConfig->highBlockInfo.n16KBlockNum + pSSDConfig->highBlockInfo.n32KBlockNum +  \
    pSSDConfig->highBlockInfo.n64KBlockNum)

/*************************************************************************/
/*                   SSD Configuration Structure                         */
/*************************************************************************/

/* Block information for an address space */
typedef struct _c55_block_info
{
    UINT32 n16KBlockNum;         /* Number of 16K blocks */
    UINT32 n32KBlockNum;         /* Number of 32K blocks */
    UINT32 n64KBlockNum;         /* Number of 64K blocks */
} BLOCK_INFO, *PBLOCK_INFO;

/* SSD Configuration Structure */
typedef struct _c55_ssd_config
{
    UINT32 c55RegBase;           /* C55 control register base */
    UINT32 mainArrayBase;        /* base of main array */
    BLOCK_INFO lowBlockInfo;     /* blocks info of low address space */
    BLOCK_INFO midBlockInfo;     /* blocks info of mid address space */
    BLOCK_INFO highBlockInfo;    /* blocks info of high address space */
    UINT32 n256KBlockNum;        /* number of blocks in 256K address space */
    UINT32 uTestArrayBase;       /* base of UTEST array */
    BOOL mainInterfaceFlag;      /* interface flag indicate main or alternate interface */
    UINT32 programmableSize;     /* programmable size */
    BOOL BDMEnable;              /* debug mode selection */
} SSD_CONFIG, *PSSD_CONFIG;

/* MISR structure */
typedef struct _c55_misr
{
    UINT32 W0;
    UINT32 W1;
    UINT32 W2;
    UINT32 W3;
    UINT32 W4;
    UINT32 W5;
    UINT32 W6;
    UINT32 W7;
    UINT32 W8;
    UINT32 W9;
} MISR, *PMISR;

/* Structure data for the context values */
typedef struct _c55_context_data
{
    UINT32 dest;
    UINT32 size;
    UINT32 source;
    UINT32 *pFailedAddress;
    UINT32 *pFailedData;
    UINT32 *pFailedSource;
    UINT32 *pSum;
    PMISR pMisr;
    void* pReqCompletionFn;
    UINT32 operationOpt;
} CONTEXT_DATA, *PCONTEXT_DATA;

/* Block select structure for 256K address space */
typedef struct _c55_n256k_block_sel
{
    UINT32 first256KBlockSelect;
    UINT32 second256KBlockSelect;
} N256K_BLOCK_SEL, *PN256K_BLOCK_SEL;

/* Start address of memory regions */
typedef struct _c55_mem_region
{
    UINT32 n16KLowEvenPartBase;
    UINT32 n16KLowOddPartBase;
    UINT32 n32KLowEvenPartBase;
    UINT32 n32KLowOddPartBase;
    UINT32 n64KLowEvenPartBase;
    UINT32 n64KLowOddPartBase;
    UINT32 n16KMidEvenPartBase;
    UINT32 n16KMidOddPartBase;
    UINT32 n32KMidEvenPartBase;
    UINT32 n32KMidOddPartBase;
    UINT32 n64KMidEvenPartBase;
    UINT32 n64KMidOddPartBase;
    UINT32 n16KHighEvenPartBase;
    UINT32 n16KHighOddPartBase;
    UINT32 n32KHighEvenPartBase;
    UINT32 n32KHighOddPartBase;
    UINT32 n64KHighEvenPartBase;
    UINT32 n64KHighOddPartBase;
    UINT32 n256KBase;
} MEM_REGION_INFO, *PMEM_REGION_INFO;

/* Struct of ADR register */
typedef union
{
    UINT32 R;
    struct
    {
        UINT32 SAD         :1U;                /* bit 31 is Utest NVM address*/
        UINT32 aMEM        :1U;                /* bit 30 is memory space */
        UINT32 aH          :1U;                /* bit 29 is High address space */
        UINT32 aM          :1U;                /* bit 28 is Mid address space */
        UINT32 aL          :1U;                /* bit 27 is Low address space */
        UINT32 a256K       :1U;                /* bit 26 is 256K address space */
        UINT32 a64K        :1U;                /* bit 25 is 64K address space */
        UINT32 a32K        :1U;                /* bit 24 is 32K address space */
        UINT32 a16K        :1U;                /* bit 23 is 16K address space */
        UINT32 ADDR        :20U;               /* bit 3 -> 22 are internal address */
        UINT32 reserved    :3U;                /* bit 0, 1, 2 are reserved */
    } B;
}INTERNAL_FLASH_ADDR;

/*************************************************************************/
/*                      Prototypes of wrapper SSD Functions              */
/*************************************************************************/

extern UINT32 FlashInit ( PSSD_CONFIG pSSDConfig );

extern UINT32 FlashErase ( PSSD_CONFIG pSSDConfig,
                    UINT8 eraseOption,
                    UINT32 lowBlockSelect,
                    UINT32 midBlockSelect,
                    UINT32 highBlockSelect,
                    N256K_BLOCK_SEL n256KBlockSelect
                    );

extern UINT32 FlashEraseAlternate ( PSSD_CONFIG pSSDConfig,
                    UINT32 interlockAddress
                    );

extern UINT32 BlankCheck ( PSSD_CONFIG pSSDConfig,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 *pFailedAddress,
                    UINT32 *pFailedData,
                    PCONTEXT_DATA pCtxData
                    );

extern UINT32 FlashProgram ( PSSD_CONFIG pSSDConfig,
                    BOOL factoryPgmFlag,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 source,
                    PCONTEXT_DATA pCtxData
                    );

extern UINT32 ProgramVerify ( PSSD_CONFIG pSSDConfig,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 source,
                    UINT32 *pFailedAddress,
                    UINT32 *pFailedData,
                    UINT32 *pFailedSource,
                    PCONTEXT_DATA pCtxData
                    );

extern UINT32 FlashCheckStatus ( PSSD_CONFIG pSSDConfig,
                    UINT8 modeOp,
                    UINT32 *opResult,
                    PCONTEXT_DATA pCtxData
                    );

extern UINT32 GetLock ( PSSD_CONFIG pSSDConfig,
                    UINT8 blkLockIndicator,
                    UINT32 *blkLockState
                    );

extern UINT32 SetLock ( PSSD_CONFIG pSSDConfig,
                    UINT8 blkLockIndicator,
                    UINT32 blkLockState
                    );

extern UINT32 OverPgmProtGetStatus ( PSSD_CONFIG pSSDConfig,
                    UINT8 blkProtIndicator,
                    UINT32 *blkProtState
                    );

extern UINT32 CheckSum ( PSSD_CONFIG pSSDConfig,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 *pSum,
                    PCONTEXT_DATA pCtxData
                    );

extern UINT32 FlashSuspend ( PSSD_CONFIG pSSDConfig,
                    UINT8 *suspendState
                    );

extern UINT32 FlashResume ( PSSD_CONFIG pSSDConfig,
                    UINT8 *resumeState
                    );

extern UINT32 FlashAbort (PSSD_CONFIG pSSDConfig, UINT8 abortOption);

extern UINT32 FlashArrayIntegrityCheck ( PSSD_CONFIG pSSDConfig,
                    UINT32 lowEnabledBlocks,
                    UINT32 midEnabledBlocks,
                    UINT32 highEnabledBlocks,
                    N256K_BLOCK_SEL n256KEnabledBlocks,
                    UINT8 breakOption,
                    UINT8 addrSeq,
                    PMISR pMisrValue,
                    PCONTEXT_DATA pCtxData
                    );

extern UINT32 FlashArrayIntegritySuspend ( PSSD_CONFIG pSSDConfig,
                    UINT8 *suspendState
                    );

extern UINT32 FlashArrayIntegrityResume ( PSSD_CONFIG pSSDConfig,
                    UINT8 *resumeState
                    );

extern UINT32 UserMarginReadCheck ( PSSD_CONFIG pSSDConfig,
                    UINT32 lowEnabledBlocks,
                    UINT32 midEnabledBlocks,
                    UINT32 highEnabledBlocks,
                    N256K_BLOCK_SEL n256KEnabledBlocks,
                    UINT8 breakOption,
                    UINT8 marginLevel,
                    PMISR pMisrValue,
                    PCONTEXT_DATA pCtxData
                    );
extern UINT32 FlashECCLogicCheck ( PSSD_CONFIG pSSDConfig,
                            PMEM_REGION_INFO pMemRegionInfo,
                            UINT32* dataVal,
                            UINT32* errBits,
                            UINT8 eccValue,
                            UINT8 errECCBits,
                            UINT8 dWordSel);
extern UINT32 FlashEDCAfterECCLogicCheck ( PSSD_CONFIG pSSDConfig,
                                    PMEM_REGION_INFO pMemRegionInfo,
                                    UINT32*    dataValue,
                                    UINT32*    errBits,
                                    UINT8    eccValue,
                                    UINT8    errECCBits,
                                    UINT8 dWordSel);
extern UINT32 FlashExpressProgram ( PSSD_CONFIG pSSDConfig,
                    PMEM_REGION_INFO pMemRegionInfo,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 source,
                    PCONTEXT_DATA pCtxData);
extern INTERNAL_FLASH_ADDR SystemToInternalAddress( PSSD_CONFIG pSSDConfig,
                                PMEM_REGION_INFO pMemRegionInfo,
                                UINT32 sysAddress);
extern UINT32 FlashAddressEncodeLogicCheck ( PSSD_CONFIG pSSDConfig,
        PMEM_REGION_INFO pMemRegionInfo,
        UINT32*   invertBits   );
/*************************************************************************/
/*                      SSD Function Pointer Types                       */
/*************************************************************************/

typedef UINT32 (*PFLASHINIT) ( PSSD_CONFIG pSSDConfig );

typedef UINT32 (*PFLASHERASE) ( PSSD_CONFIG pSSDConfig,
                    UINT8 eraseOption,
                    UINT32 lowBlockSelect,
                    UINT32 midBlockSelect,
                    UINT32 highBlockSelect,
                    N256K_BLOCK_SEL n256KBlockSelect
                    );

typedef UINT32 (*PFLASHERASEALTERNATE) ( PSSD_CONFIG pSSDConfig,
                    UINT32 interlockAddress
                    );

typedef UINT32 (*PBLANKCHECK) ( PSSD_CONFIG pSSDConfig,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 *pFailedAddress,
                    UINT32 *pFailedData,
                    PCONTEXT_DATA pCtxData
                    );

typedef UINT32 (*PFLASHPROGRAM) ( PSSD_CONFIG pSSDConfig,
                    BOOL factoryPgmFlag,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 source,
                    PCONTEXT_DATA pCtxData
                    );

typedef UINT32 (*PPROGRAMVERIFY) ( PSSD_CONFIG pSSDConfig,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 source,
                    UINT32 *pFailedAddress,
                    UINT32 *pFailedData,
                    UINT32 *pFailedSource,
                    PCONTEXT_DATA pCtxData
                    );

typedef UINT32 (*PFLASHCHECKSTATUS) ( PSSD_CONFIG pSSDConfig,
                    UINT8 modeOp,
                    UINT32 *opResult,
                    PCONTEXT_DATA pCtxData
                    );

typedef UINT32 (*PGETLOCK) ( PSSD_CONFIG pSSDConfig,
                    UINT8 blkLockIndicator,
                    UINT32 *blkLockState
                    );

typedef UINT32 (*PSETLOCK) ( PSSD_CONFIG pSSDConfig,
                    UINT8 blkLockIndicator,
                    UINT32 blkLockState
                    );

typedef UINT32 (*POVERPGMPROTGETSTATUS) ( PSSD_CONFIG pSSDConfig,
                    UINT8 blkProtIndicator,
                    UINT32* blkProtState
                    );

typedef UINT32 (*PCHECKSUM) ( PSSD_CONFIG pSSDConfig,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 *pSum,
                    PCONTEXT_DATA pCtxData
                    );

typedef UINT32 (*PFLASHSUSPEND) ( PSSD_CONFIG pSSDConfig,
                    UINT8 *suspendState
                    );

typedef UINT32 (*PFLASHRESUME) ( PSSD_CONFIG pSSDConfig,
                    UINT8 *resumeState
                    );

typedef UINT32 (*PFLASHABORT) ( PSSD_CONFIG pSSDConfig, UINT8 abortOption );

typedef UINT32 (*PFLASHARRAYINTEGRITYCHECK) ( PSSD_CONFIG pSSDConfig,
                    UINT32 lowEnabledBlocks,
                    UINT32 midEnabledBlocks,
                    UINT32 highEnabledBlocks,
                    N256K_BLOCK_SEL n256KEnabledBlocks,
                    UINT8 breakOption,
                    UINT8 addrSeq,
                    PMISR pMisrValue,
                    PCONTEXT_DATA pCtxData
                    );

typedef UINT32 (*PFLASHARRAYINTEGRITYSUSPEND) ( PSSD_CONFIG pSSDConfig,
                    UINT8 *suspendState
                    );

typedef UINT32 (*PFLASHARRAYINTEGRITYRESUME) ( PSSD_CONFIG pSSDConfig,
                    UINT8 *resumeState
                    );

typedef UINT32 (*PUSERMARGINREADCHECK) ( PSSD_CONFIG pSSDConfig,
                    UINT32 lowEnabledBlocks,
                    UINT32 midEnabledBlocks,
                    UINT32 highEnabledBlocks,
                    N256K_BLOCK_SEL n256KEnabledBlocks,
                    UINT8 breakOption,
                    UINT8 marginLevel,
                    PMISR pMisrValue,
                    PCONTEXT_DATA pCtxData
                    );
typedef UINT32 (*PFLASHECCLOGICCHECK) ( PSSD_CONFIG pSSDConfig,
                            PMEM_REGION_INFO pMemRegionInfo,
                            UINT32* dataVal,
                            UINT32* errBits,
                            UINT8 eccValue,
                            UINT8 errECCBits,
                            UINT8 dWordSel);
typedef UINT32 (*PFLASHEDCAFTERECCLOGICCHECK) ( PSSD_CONFIG pSSDConfig,
                                    PMEM_REGION_INFO pMemRegionInfo,
                                    UINT32*    dataValue,
                                    UINT32*    errBits,
                                    UINT8    eccValue,
                                    UINT8    errECCBits,
                                    UINT8 dWordSel);
typedef UINT32 (*PFLASHEXPRESSPROGRAM) ( PSSD_CONFIG pSSDConfig,
                    PMEM_REGION_INFO pMemRegionInfo,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 source,
                    PCONTEXT_DATA pCtxData);
typedef INTERNAL_FLASH_ADDR (*PSYSTEMTOINTERNALADDRESS)( PSSD_CONFIG pSSDConfig,
                                PMEM_REGION_INFO pMemRegionInfo,
                                UINT32 sysAddress);
typedef UINT32 (*PFLASHADDRESSENCODELOGICCHECK) ( PSSD_CONFIG pSSDConfig,
        PMEM_REGION_INFO pMemRegionInfo,
        UINT32*   invertBits   );
#endif /* _SSD_C55_H_ */
