/*
 *######################################################################
 *                                RAppIDJDP
 *           Rapid Application Initialization and Documentation Tool
 *                         Freescale Semiconductor Inc.
 *
 *######################################################################
 *
 * Project Name           : baseconfigMPC5606S_for_CQCYM
 *
 * Project File           : baseconfigMPC5606S_for_CQCYM.rsp
 *
 * Revision Number        : 8.5
 *
 * Tool Version           : 1.0.0.3
 *
 * file                   : flexcan_init.c
 *
 * Target Compiler        : Codewarrior
 *
 * Target Part            : MPC5606S
 *
 * Part Errata Fixes      : none
 *
 * Project Last Save Date : 01-May-2014 11:42:45
 *
 * Created on Date        : 01-May-2014 11:45:39
 *
 * Brief Description      : This file contains FlexCAN register configuration in freeze mode
 *
 ******************************************************************************** 
 *
 * Detail Description     : File contains functions where each FlexCAN configuration for
 *                          maximum number of MBs, CAN speed, different operating modes,
 *                          Receive Mask and Interrupt Mask can be done in freeze mode.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "flexcan_init.h"

#include "FlexCAN_api.h"

/*    CAN_1_RximrArray Intialisation. 
     It is used to intialise CAN_1.RX Individual Mask0 to 
    CAN_1.RX Individual Mask63 register.                 */

const static uint32_t CAN_1_RximrArrayt[64] = {
0x00000000,0x00000000,0x00000000,0x00000000,  /*RX00,RX01,RX02,RX03,*/
0xFFFFFFF0,0x00000000,0xFFFFFFF0,0x00000000,  /*RX04,RX05,RX06,RX07,*/
0x00000000,0x00000000,0x00000000,0x00000000,  /*RX08,RX09,RX10,RX11,*/
0x00000000,0x00000000,0xFFFFFFFC,0xFFFFFFFB,  /*RX12,RX13,RX14,RX15,*/
0x00000000,0x00000000,0x00000000,0x00000000,  /*RX16,RX17,RX18,RX19,*/
0x00000000,0x00000000,0x00000000,0x00000000,  /*RX20,RX21,RX22,RX23,*/
0x00000000,0x00000000,0x00000000,0x00000000,  /*RX24,RX25,RX26,RX27,*/
0x00000000,0x00000000,0x00000000,0x00000000,  /*RX28,RX29,RX30,RX31,*/
0x00000000,0x00000000,0x00000000,0x00000000,  /*RX32,RX33,RX34,RX35,*/
0x00000000,0x00000000,0x00000000,0x00000000,  /*RX36,RX37,RX38,RX39,*/
0x00000000,0x00000000,0x00000000,0x00000000,  /*RX40,RX41,RX42,RX43,*/
0x00000000,0x00000000,0x00000000,0x00000000,  /*RX44,RX45,RX46,RX47,*/
0x00000000,0x00000000,0x00000000,0x00000000,  /*RX48,RX49,RX50,RX51,*/
0x00000000,0x00000000,0x00000000,0x00000000,  /*RX52,RX53,RX54,RX55,*/
0x00000000,0x00000000,0x00000000,0x00000000,  /*RX56,RX57,RX58,RX59,*/
0x00000000,0x00000000,0x00000000,0x00000000,  /*RX60,RX61,RX62,RX63,*/
};

/*********************  Initialization Function(s) ************************/

uint8_t flexcan_init_fnc(void)
{
   uint8_t init_status = 0;

   init_status += flexcan_0_init_fnc();
   init_status += 2*flexcan_1_init_fnc();

   return init_status;
}

/*
 * FlexCAN0 de-initialize function
 * reset its registers and shutdown the peripheral module
 */
uint8_t flexcan_0_deinit_fnc(void)
{
	/* Reset FlexCAN Module */
	CAN_0.MCR.B.SOFTRST = 1;
	while( CAN_0.MCR.B.SOFTRST ==1){}

	/* Set FRZ bit */
	CAN_0.MCR.B.FRZ       = 1;
	while( CAN_0.MCR.B.FRZACK == 0){}

	CAN_0.MCR.B.MDIS = 1;       /* Disable the module */

}

/*
 * FlexCAN1 de-initialize function
 * reset its registers and shutdown the peripheral module
 */
uint8_t flexcan_1_deinit_fnc(void)
{
	/* Reset FlexCAN Module */
	CAN_1.MCR.B.SOFTRST = 1;
	while( CAN_0.MCR.B.SOFTRST ==1){}

	/* Set FRZ bit */
	CAN_1.MCR.B.FRZ       = 1;
	while( CAN_1.MCR.B.FRZACK == 0){}

	CAN_1.MCR.B.MDIS = 1;       /* Disable the module */

}

/*********************  CAN_0 Initialization Function(s) ************************/

uint8_t flexcan_0_init_fnc(void)
{

    uint16_t i, x;
    uint8_t status;
    uint16_t j;

    CAN_0.MCR.B.MDIS = 1;       /* Disable module before selecting clock source*/
    CAN_0.CTRL1.B.CLKSRC=0;     /* Clock Source = oscillator clock (40 MHz) */

    /*enabling the CAN module */
    CAN_0.MCR.B.MDIS    = 0;

    /* Reset FlexCAN Module */
    CAN_0.MCR.B.SOFTRST = 1;
    while( CAN_0.MCR.B.SOFTRST ==1){}

    /* Set FRZ bit */
    CAN_0.MCR.B.FRZ       = 1;
    while( CAN_0.MCR.B.FRZACK == 0){}

    /* Set CAN clock source 1: bus , 0: oscillator */
    CAN_0.CTRL1.B.CLKSRC   = 0;


/* ----------------------------------------------------------- */
/*                   CAN_0.MCR Control Register                          */
/* ----------------------------------------------------------- */
    CAN_0.MCR.R = 0x5983000F;

    /*Enable the FlexCAN module: 0*/
    /* FRZ bit :1*/
    /* FIFO Enable :0*/
    /* Halt : 1*/
    /* FlexCAN not ready: 1*/
    /* Soft Reset : 0*/
    /* Freeze Mode Acknowledge : 1*/
    /* Supervisor Mode : 1*/
    /* Warning Interrupt Enable : 0*/
    /* Low Power Mode Acknowledge : 0*/
    /* Doze Mode Enable : 0*/
    /* Self Reception Disable : 1*/
    /* Backwards Compatibility Configuration : 0*/
    /* Local Priority Enable : 0*/
    /* Abort Enable : 0*/
    /* ID Acceptance Mode : 0*/
    /* Maximum Number of Message Buffers : 15*/

/* ----------------------------------------------------------- */
/*    CAN_0.CR Control Register                                */
/* ----------------------------------------------------------- */
    CAN_0.CTRL1.R  = 0x0414C036;
    /* Bus -Off Interrupt Mask: Enabled         */
    /* CAN bit Sampling Mode: 1 Sample           */
    /* CAN Error Interrupt Mask: Enabled        */
    /* CLOCK Source: Oscillator                   */
    /* Listen Only Mode: Disabled                */
    /* Loop Back Mode: Disabled                  */
    /* Bus off Recovery: Enabled                */
    /* Lowest Buffer Transfer First: Enabled    */
    /* Phase Segment1: 3                         */
    /* Phase Segment2: 5                         */
    /* Prescalar Division Factor: 5(40MHz/5==8MHz--> 8/16= 500kbps)  */
    /* Propagation Segment: 7                    */
    /* Resynchronization Jump Width: 1           */
    /* Timer Synch Mode: Enabled                */



    /* Set the FlexCAN Maximum Buffer Number */
    CAN_0.MCR.B.MAXMB  = 16;


    /* clear memory from message buffer 8 to 15 */
    for(x=8; x < 16; x++)
    {
        CAN_0.MB[x].CS.R = 0;
        CAN_0.MB[x].ID.R = 0;
        for(i=0; i < 2; i++) 
        {
            CAN_0.MB[x].DATA.W[i] = 0;
        }
    }

/* ----------------------------------------------------------- */
/*    CAN_0.IMASK2 Interrupt Masks High Register                 */
/* ----------------------------------------------------------- */
    CAN_0.IMASK2.R  = 0x00000000;

/* ----------------------------------------------------------- */
/*    CAN_0.IMASK1 Interrupt Masks Low Register                  */
/* ----------------------------------------------------------- */

    CAN_0.IFLAG1.R  = 0x000000F0;/*clean the flags first*/
    CAN_0.IMASK1.R  = 0x000000F0;
    
    CAN0_ReceiveInit(MB4, StandardFrame, DataFrame, 0x123,0xFF0);
    CAN0_ReceiveInit(MB6, StandardFrame, DataFrame, 0x64,0xFFF);/*receive only standard ID 0x64 for bootloader download CAN frame ID*/

    /* Negate the HALT and the FREEZE bit to let the FlexCAN synchronize. */
    /* Exit and Disable freeze mode */
    CAN_0.MCR.B.HALT  =  0;
    CAN_0.MCR.B.FRZ   =  0;
    

    /* await synchronization (delay) */
    for(j=1; j < 255; j++){}

    if(CAN_0.MCR.B.NOTRDY == 1)
    {
       status = 1;
    }
    else
    {
       status = 0;
    }


    return status;

}
/*********************  CAN_1 Initialization Function(s) ************************/

uint8_t flexcan_1_init_fnc(void)
{

    uint16_t i, x;
    uint8_t status;
    uint16_t j;

    /*enabling the CAN module */
    CAN_1.MCR.B.MDIS    = 0;

    /* Reset FlexCAN Module */
    CAN_1.MCR.B.SOFTRST = 1;
    while( CAN_1.MCR.B.SOFTRST ==1){}

    /* Set FRZ bit */
    CAN_1.MCR.B.FRZ       = 1;
    while( CAN_1.MCR.B.FRZACK == 0){}

    /* Set CAN clock source 1: bus , 0: oscillator */
    CAN_1.CTRL1.B.CLKSRC   = 0;


    /* ----------------------------------------------------------- */
    /*                   CAN_1.MCR Control Register                          */
    /* ----------------------------------------------------------- */
        CAN_1.MCR.R = 0x5983000F;

        /*Enable the FlexCAN module: 0*/
        /* FRZ bit :1*/
        /* FIFO Enable :0*/
        /* Halt : 1*/
        /* FlexCAN not ready: 1*/
        /* Soft Reset : 0*/
        /* Freeze Mode Acknowledge : 1*/
        /* Supervisor Mode : 1*/
        /* Warning Interrupt Enable : 0*/
        /* Low Power Mode Acknowledge : 0*/
        /* Doze Mode Enable : 0*/
        /* Self Reception Disable : 1*/
        /* Backwards Compatibility Configuration : 0*/
        /* Local Priority Enable : 0*/
        /* Abort Enable : 0*/
        /* ID Acceptance Mode : 0*/
        /* Maximum Number of Message Buffers : 15*/

    /* ----------------------------------------------------------- */
    /*    CAN_1.CR Control Register                                */
    /* ----------------------------------------------------------- */
        CAN_1.CTRL1.R  = 0x0414C016;
        /* Bus -Off Interrupt Mask: Enabled         */
        /* CAN bit Sampling Mode: 1 Sample           */
        /* CAN Error Interrupt Mask: Enabled        */
        /* CLOCK Source: Oscillator                   */
        /* Listen Only Mode: Disabled                */
        /* Loop Back Mode: Disabled                  */
        /* Bus off Recovery: Enabled                */
        /* Lowest Buffer Transfer First: Enabled    */
        /* Phase Segment1: 3                         */
        /* Phase Segment2: 5                         */
        /* Prescalar Division Factor: 5(40MHz/5==8MHz-->500kbps)               */
        /* Propagation Segment: 7                    */
        /* Resynchronization Jump Width: 1           */
        /* Timer Synch Mode: Disabled                */



        /* Set the FlexCAN Maximum Buffer Number */
        CAN_1.MCR.B.MAXMB  = 16;


        /* clear memory from message buffer 0 to 15 */
        for(x=0; x < 16; x++)
        {
            CAN_1.MB[x].CS.R = 0;
            CAN_1.MB[x].ID.R = 0;
            for(i=0; i < 2; i++) 
            {
                CAN_1.MB[x].DATA.W[i] = 0;
            }
        }


    /* ----------------------------------------------------------- */
    /*    CAN_1.RX Mask Individual Mask                             */
    /* ----------------------------------------------------------- */
        for(x=0 ; x<64 ; x++)
        {
            CAN_1.RXIMR[x].R = CAN_1_RximrArrayt[x];
        }

    /* ----------------------------------------------------------- */
    /*    CAN_1.IMASK2 Interrupt Masks High Register                 */
    /* ----------------------------------------------------------- */
        CAN_1.IMASK2.R  = 0x00000000;

    /* ----------------------------------------------------------- */
    /*    CAN_1.IMASK1 Interrupt Masks Low Register                  */
    /* ----------------------------------------------------------- */

        CAN_1.IFLAG1.R = 0x0000FFFF;/*clean the flags first*/
        CAN_1.IMASK1.R = 0x0000FFFF;
    
    
    CAN1_ReceiveInit(MB4,StandardFrame, DataFrame, 0x333, 0xFF0);  /*receive 0x330~0x33F, total 16 ID CAN Frame */
    CAN1_ReceiveInit(MB6, ExtendFrame, RemoteFrame, 0x111,0xFFFFFFF0);  /*receive 0x110~0x11F, total 16 ID CAN Frame */
    

    CAN1_ReceiveInit(MB14, StandardFrame, DataFrame, 0x222,0xFFC); /*receive 0x220~0x223, total 4 ID CAN Frame */
    CAN1_ReceiveInit(MB15, ExtendFrame, RemoteFrame, 0x1111666,0xFFFFFFFB); /*receive 0x111662 and 0x111666, total 2 ID CAN Frame */
    

    /* Negate the HALT and the FREEZE bit to let the FlexCAN synchronize. */
    /* Exit and Disable freeze mode */
    CAN_1.MCR.B.HALT  =  0;
    CAN_1.MCR.B.FRZ   =  0;
    

    /* await synchronization (delay) */
    for(j=1; j < 255; j++){}

    if(CAN_1.MCR.B.NOTRDY == 1)
    {
       status = 1;
    }
    else
    {
       status = 0;
    }


    return status;

}

 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

