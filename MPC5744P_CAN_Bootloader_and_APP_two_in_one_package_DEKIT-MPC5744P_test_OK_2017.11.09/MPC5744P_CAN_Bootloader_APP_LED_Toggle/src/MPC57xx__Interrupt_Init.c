/**************************************************************************/
/* FILE NAME:                              COPYRIGHT (c) Freescale 2016   */
/* MPC57xx__Interrupt_Init.c                      All Rights Reserved     */
/*                                                                        */
/* DESCRIPTION:                                                           */
/* This is the interrupt controller configuration file.                   */
/*=========================================================================*/
/*                                                                        */
/*========================================================================*/
/* REV      AUTHOR        DATE        DESCRIPTION OF CHANGE               */
/* ---   -----------    ----------    ---------------------               */
/* 0.1    R. Moran       10/12/2008    Initial Version                    */
/* 1.1    K. Zemskov     24/02/2016    GHS support                        */
/**************************************************************************/
#include "derivative.h" /* include peripheral declarations */
#include "compiler_api.h"

#define GetCoreID() ((uint16_t) MFSPR(286))

#if defined(MPC574xP) || defined(MPC574xR) || defined(MPC5777M)
#define INTC             INTC_0
#endif

/* Hardware vector mode bit */
#define INTC_BCR_HVEN(coreId)   ( (uint32_t) (0x1UL << ((coreId) << 3UL)) )  /* coreId - hw coreId (value that is read from PIR) */

/*========================================================================*/
/*                      GLOBAL VARIABLES                                  */
/*========================================================================*/
extern const uint32_t IntcIsrVectorTable[];

/*========================================================================*/
/*                      EXTERNAL PROTOTYPES                               */
/*========================================================================*/
extern void VTABLE (void);

/*========================================================================*/
/*                          FUNCTIONS                                     */
/*========================================================================*/
/**************************************************************************/
/* FUNCTION     : SetIVPR                                                 */
/* PURPOSE      : Initialise Core IVPR                                    */
/**************************************************************************/
void SetIVPR (register unsigned int x)
{
    MTSPR(63, x);
}

#if defined(MPC5777C)
void InitIVORS (void)
{
#if defined (__ghs__) || defined (__DCC__)    /* GreenHills or Diab*/
    PPCASM("e_lis       r0, VTABLE@ha");
    PPCASM("e_add16i    r0, r0, VTABLE@l");
    PPCASM("e_rlwinm    r0, r0, 0, 16, 27");
    PPCASM("mtspr       IVOR0, r0");  /* IVOR0 400 Critical input                                           */
    PPCASM("e_add16i    r3, r0, 0x010");
    PPCASM("mtspr       IVOR1, r3");  /* IVOR1 401 Machine check                                            */
    PPCASM("e_add16i    r3, r0, 0x020");
    PPCASM("mtspr       IVOR2, r3");  /* IVOR2 402 Data storage                                             */
    PPCASM("e_add16i    r3, r0, 0x030");
    PPCASM("mtspr       IVOR3, r3");  /* IVOR3 403 Instruction storage                                      */
    PPCASM("e_add16i    r3, r0, 0x040");
    PPCASM("mtspr       IVOR4, r3");  /* IVOR4 404 External input                                           */
    PPCASM("e_add16i    r3, r0, 0x050");
    PPCASM("mtspr       IVOR5, r3");  /* IVOR5 405 Alignment                                                */
    PPCASM("e_add16i    r3, r0, 0x060");
    PPCASM("mtspr       IVOR6, r3");  /* IVOR7 406 Program                                                  */
    PPCASM("e_add16i    r3, r0, 0x070");
    PPCASM("mtspr       IVOR7, r3");  /* IVOR7 407 Floating-point unavailable                               */
    PPCASM("e_add16i    r3, r0, 0x080");
    PPCASM("mtspr       IVOR8, r3");  /* IVOR8 408 System call                                              */
    PPCASM("e_add16i    r3, r0, 0x090");
    PPCASM("mtspr       IVOR9, r3");  /* IVOR9 409 Auxiliary processor unavailable. Not used by the e200z6. */
    PPCASM("e_add16i    r3, r0, 0x0A0");
    PPCASM("mtspr       IVOR10, r3"); /* IVOR10 410 Decrementer                                             */
    PPCASM("e_add16i    r3, r0, 0x0B0");
    PPCASM("mtspr       IVOR11, r3"); /* IVOR11 411 Fixed-interval timer interrupt                          */
    PPCASM("e_add16i    r3, r0, 0x0C0");
    PPCASM("mtspr       IVOR12, r3"); /* IVOR12 412 Watchdog timer interrupt                                */
    PPCASM("e_add16i    r3, r0, 0x0D0");
    PPCASM("mtspr       IVOR13, r3"); /* IVOR13 413 Data TLB error                                          */
    PPCASM("e_add16i    r3, r0, 0x0E0");
    PPCASM("mtspr       IVOR14, r3"); /* IVOR14 414 Instruction TLB error                                   */
    PPCASM("e_add16i    r3, r0, 0x0F0");
    PPCASM("mtspr       IVOR15, r3"); /* IVOR15 415 Debug                                                   */

                           /* IVOR16-IVOR31 - Reserved for future architectural use              */

    PPCASM("e_add16i    r3, r0, 0x100");
    PPCASM("mtspr       IVOR32, r3"); /* IVOR32 528 SPE APU unavailable                                     */
    PPCASM("e_add16i    r3, r0, 0x110");
    PPCASM("mtspr       IVOR33, r3"); /* IVOR33 529 SPE floating-point data exception                       */
    PPCASM("e_add16i    r3, r0, 0x120");
    PPCASM("mtspr       IVOR34, r3"); /* IVOR34 530 SPE floating-point round exception                      */
#else
    unsigned int reg0, reg1;
    PPCASM("e_lis %0, VTABLE@ha \n\t" : "=r" (reg0));
    PPCASM("e_add16i %0, %0, VTABLE@l \n\t" : "=r" (reg0));
    PPCASM("e_rlwinm %0, %0, 0, 16, 27 \n\t" : "=r" (reg0));
    MTSPR(400, reg0);
    PPCASM("e_add16i %0, %1, 0x010 \n\t" : "=r" (reg1) : "r" (reg0));
    MTSPR(401, reg1);
    PPCASM("e_add16i %0, %1, 0x020 \n\t" : "=r" (reg1) : "r" (reg0));
    MTSPR(402, reg1);
    PPCASM("e_add16i %0, %1, 0x030 \n\t" : "=r" (reg1) : "r" (reg0));
    MTSPR(403, reg1);
    PPCASM("e_add16i %0, %1, 0x040 \n\t" : "=r" (reg1) : "r" (reg0));
    MTSPR(404, reg1);
    PPCASM("e_add16i %0, %1, 0x050 \n\t" : "=r" (reg1) : "r" (reg0));
    MTSPR(405, reg1);
    PPCASM("e_add16i %0, %1, 0x060 \n\t" : "=r" (reg1) : "r" (reg0));
    MTSPR(406, reg1);
    PPCASM("e_add16i %0, %1, 0x070 \n\t" : "=r" (reg1) : "r" (reg0));
    MTSPR(407, reg1);
    PPCASM("e_add16i %0, %1, 0x080 \n\t" : "=r" (reg1) : "r" (reg0));
    MTSPR(408, reg1);
    PPCASM("e_add16i %0, %1, 0x090 \n\t" : "=r" (reg1) : "r" (reg0));
    MTSPR(409, reg1);
    PPCASM("e_add16i %0, %1, 0x0A0 \n\t" : "=r" (reg1) : "r" (reg0));
    MTSPR(410, reg1);
    PPCASM("e_add16i %0, %1, 0x0B0 \n\t" : "=r" (reg1) : "r" (reg0));
    MTSPR(411, reg1);
    PPCASM("e_add16i %0, %1, 0x0C0 \n\t" : "=r" (reg1) : "r" (reg0));
    MTSPR(412, reg1);
    PPCASM("e_add16i %0, %1, 0x0D0 \n\t" : "=r" (reg1) : "r" (reg0));
    MTSPR(413, reg1);
    PPCASM("e_add16i %0, %1, 0x0E0 \n\t" : "=r" (reg1) : "r" (reg0));
    MTSPR(414, reg1);
    PPCASM("e_add16i %0, %1, 0x0F0 \n\t" : "=r" (reg1) : "r" (reg0));
    MTSPR(415, reg1);
#endif
}
#endif

/**************************************************************************/
/* FUNCTION     : InitINTC                                                */
/* PURPOSE      : This function intializes the INTC for software vector   */
/*                mode.                                                   */
/**************************************************************************/
void InitINTC(void) {   

	uint32_t __attribute__((unused)) temp;

#if !defined(MPC574xP)
    uint16_t coreId = GetCoreID ();
#endif

    /* Choose software (HVEN=0) or hardware (HVEN=1) vector mode */
#if defined(MPC574xP)
    INTC.BCR.R   = 0;     /* Software vector mode   */
#elif defined(MPC5777C)
    INTC.MCR.R  &= ~(INTC_BCR_HVEN( coreId ));     /* Software vector mode   */
#else
    INTC.BCR.R  &= ~(INTC_BCR_HVEN( coreId ));     /* Software vector mode   */
#endif
#if defined(MPC574xP)
    temp = INTC.IACKR0.R;
    /* Set INTC ISR vector table base addr. */
    INTC.IACKR0.R = (uint32_t) &IntcIsrVectorTable[0];
#elif defined(MPC574xR)
    temp = (coreId) ? INTC.IACKR[1].R : INTC.IACKR[0].R;
    /* Set INTC ISR vector table base addr. */
    if (coreId) INTC.IACKR[1].R = (uint32_t) &IntcIsrVectorTable[0];
    else INTC.IACKR[0].R = (uint32_t) &IntcIsrVectorTable[0];
#elif defined(MPC5777C)
    temp = INTC.IACKR_PRC[coreId].R;
    /* Set INTC ISR vector table base addr. */
    INTC.IACKR_PRC[coreId].R = (uint32_t) &IntcIsrVectorTable[0];
#elif defined(MPC574xC)
    temp = (coreId) ? INTC.IACKR1.R : INTC.IACKR0.R;
    /* Set INTC ISR vector table base addr. */
    if (coreId) INTC.IACKR1.R = (uint32_t) &IntcIsrVectorTable[0];
    else INTC.IACKR0.R = (uint32_t) &IntcIsrVectorTable[0];
#else
    temp = INTC.IACKR[coreId].R;
    /* Set INTC ISR vector table base addr. */
    INTC.IACKR[coreId].R = (uint32_t) &IntcIsrVectorTable[0];
#endif
}


/**************************************************************************/
/* FUNCTION     : enableIrq                                               */
/* PURPOSE      : This function sets INTC's current priority to 0.        */
/*                External interrupts to the core are enabled.            */
/**************************************************************************/
void enableIrq(void) {

#if !defined(MPC574xP)
    uint16_t coreId = GetCoreID ();
#endif

    /* Ensure INTC's current priority is 0 */
#if defined(MPC574xP)
    INTC.CPR0.R = 0U;
#elif  defined(MPC574xR)
    /* Ensure INTC's current priority is 0 */
    if (coreId) INTC_0.CPR[1].R = 0U;
    else INTC_0.CPR[0].R = 0U;
#elif defined(MPC5777C)
    INTC.CPR_PRC[coreId].R = 0U;
#elif  defined(MPC574xC)
    /* Ensure INTC's current priority is 0 */
    if (coreId) INTC.CPR1.R = 0U;
    else INTC.CPR0.R = 0U;
#else
    /* Ensure INTC's current priority is 0 */
    INTC.CPR[coreId].R = 0U;
#endif
    /* Enable external interrupts */
    PPCASM (" wrteei 1 ");
}


/**************************************************************************/
/* FUNCTION     : xcptn_xmpl                                              */
/* PURPOSE      : This function sets up the necessary functions to raise  */
/*                and handle a Interrupt in software vector mode          */
/**************************************************************************/
void xcptn_xmpl(void) {
    
    /* Initialise Core IVPR */
    SetIVPR ((unsigned int) &VTABLE);
#if defined(MPC5777C)
    InitIVORS();
#endif
    /* Initialize INTC for SW vector mode */
    InitINTC();               
    
    /* Enable interrupts */
    enableIrq();

}


