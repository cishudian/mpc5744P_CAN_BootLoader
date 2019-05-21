/*
 * FlexCAN_api.c
 *
 *  Created on: Apr 23, 2014
 *      Author: B46398
 */

#include "FlexCAN_api.h"

#include "project.h"

#include "load.h"

/**  used for FlexCAN TX/RX interrupt test **/
CAN_Msg_Strcut CAN_TxMsg;  /* for CAN TX  */
CAN_Msg_Strcut CAN_RxMsg;  /* for CAN RX  */
CAN_Msg_Strcut CAN_RxFeedbackMsg; /* used to feed back the received CAN frame */

uint8_t CAN0_BufferReceive_Flag = 0;  /* FlexCAN0 received CAN frame flag */
uint8_t CAN1_BufferReceive_Flag = 0;  /* FlexCAN1 received CAN frame flag */

/***********************************************************************
 * call this function for CAN0 data transmit
 * Buffer: select the MB to transmit the CAN message(MB0~MB63)
 * CAN_Meg: CAN message to send
 ***********************************************************************/
void CAN0_TransmitMsg (CAN_MessageBuffer Buffer, CAN_Msg_Strcut CAN_Msg) 
{
	  uint8_t	i;
  
	  /* Assumption:  Message buffer CODE is INACTIVE */
	  CAN_0.MB[Buffer].CS.B.IDE = CAN_Msg.Frame_Type;           /* Frame type setting */

	  if( CAN_Msg.Frame_Type == StandardFrame)
	  	  CAN_0.MB[Buffer].ID.B.ID_STD = CAN_Msg.Frame_ID;      /* Transmit ID       */
	  else
	  {	  
		  CAN_0.MB[Buffer].ID.R = CAN_Msg.Frame_ID;      		 /* Transmit ID       */
		  CAN_0.MB[Buffer].CS.B.SRR = 1;           /* Tx frame (not req'd for standard frame)*/
	  }
	    
	  CAN_0.MB[Buffer].CS.B.RTR = CAN_Msg.Frame_DataType;       /* Data frame, not remote Tx request frame */
	  CAN_0.MB[Buffer].CS.B.DLC = sizeof(CAN_Msg.Frame_Data); /* # bytes to transmit w/o null */
	  for (i=0; i<sizeof(CAN_Msg.Frame_Data); i++) {
		CAN_0.MB[Buffer].DATA.B[i] = CAN_Msg.Frame_Data[i];      /* Data to be transmitted */
	  }
	  

	  CAN_0.MB[Buffer].CS.B.CODE =0xC;         /* Activate msg. buf. to transmit data frame */
}

/***********************************************************************
 * call this function for CAN1 data transmit
 * Buffer: select the MB to transmit the CAN message(MB0~MB63)
 * CAN_Meg: CAN message to send
 ***********************************************************************/
void CAN1_TransmitMsg (CAN_MessageBuffer Buffer, CAN_Msg_Strcut CAN_Msg) 
{
	uint8_t	i;
	  
	/* Assumption:  Message buffer CODE is INACTIVE */

	  CAN_1.MB[Buffer].CS.B.IDE = CAN_Msg.Frame_Type;           /* Frame type setting */
	  
	  if( CAN_Msg.Frame_Type == StandardFrame)
		  CAN_1.MB[Buffer].ID.B.ID_STD = CAN_Msg.Frame_ID;      /* Transmit ID       */
	  else
	  {
		  CAN_1.MB[Buffer].ID.R = CAN_Msg.Frame_ID;      		 /* Transmit ID       */
		  CAN_1.MB[Buffer].CS.B.SRR = 1;           /* Tx frame (not req'd for standard frame)*/
	  }

	  
	  CAN_1.MB[Buffer].CS.B.RTR = CAN_Msg.Frame_DataType;       /* Data frame, not remote Tx request frame */
	  CAN_1.MB[Buffer].CS.B.DLC = sizeof(CAN_Msg.Frame_Data); /* # bytes to transmit w/o null */
	  for (i=0; i<sizeof(CAN_Msg.Frame_Data); i++) {
		CAN_1.MB[Buffer].DATA.B[i] = CAN_Msg.Frame_Data[i];      /* Data to be transmitted */
	  }

	  CAN_1.MB[Buffer].CS.B.CODE =0xC;         /* Activate msg. buf. to transmit data frame */
}


/********************************************************************************
 * call this function for CAN0 receive enable
 * Buffer: select the MB to transmit the CAN message (MB0~MB63)
 * FrameType: set the receive CAM message frame type(ExtendFrame or StandardFrame)
 * DataType: set the receive CAM message data type(RemoteFrame or DataFrame)
 * ID: the receive CAN message ID
 * ID_Mask: the receive CAN message ID mask
 ********************************************************************************/
void CAN0_ReceiveInit(CAN_MessageBuffer Buffer,CAN_FrameType FrameType, CAN_DataType DataType, uint32_t ID, uint32_t ID_Mask)
{
    /**********for receive **********/
    CAN_0.MB[Buffer].CS.B.IDE = FrameType;  /* MB buffer will look for a standard ID */
    CAN_0.MB[Buffer].CS.B.RTR = DataType;   /* receive remote frame or data frame*/
    
    if(FrameType == StandardFrame)
    {
       CAN_0.MB[Buffer].ID.B.ID_STD = ID; 	/* MB buffer will look for standard ID of ID */
       CAN_0.RXIMR[Buffer].R = ID_Mask<<18; /* set individual receive match ID mask */
    }
    else
    {
       CAN_0.MB[Buffer].ID.R = ID; 	    /* MB buffer will look for extend ID of ID */
       CAN_0.RXIMR[Buffer].R = ID_Mask;     /* set individual receive match ID mask */
    }
        
   CAN_0.MB[Buffer].CS.B.CODE = 4;     	/* MB buffer set to RX EMPTY */

}

/********************************************************************************
 * call this function for CAN1 receive enable
 * Buffer: select the MB to transmit the CAN message (MB0~MB63)
 * FrameType: set the receive CAM message frame type(ExtendFrame or StandardFrame)
 * DataType: set the receive CAM message data type(RemoteFrame or DataFrame)
 * ID: the receive CAN message ID
 * ID_Mask: the receive CAN message ID mask
 ********************************************************************************/
void CAN1_ReceiveInit(CAN_MessageBuffer Buffer, CAN_FrameType FrameType, CAN_DataType DataType, uint32_t ID, uint32_t ID_Mask)
{
    /**********for receive **********/
    CAN_1.MB[Buffer].CS.B.IDE = FrameType;     /* MB buffer will look for a FrameType(standard/extend) ID */
    CAN_1.MB[Buffer].CS.B.RTR = DataType;      /* receive remote frame or data frame*/
    
    if(FrameType == StandardFrame)
    {
        CAN_1.MB[Buffer].ID.B.ID_STD = ID; 	/* MB buffer will look for standard ID of ID */
        CAN_1.RXIMR[Buffer].R = ID_Mask<<18;    /* set individual receive match ID mask */
    }
    else
    {
        CAN_1.MB[Buffer].ID.R = ID; 	        /* MB buffer will look for extend ID of ID */
        CAN_1.RXIMR[Buffer].R = ID_Mask;        /* set individual receive match ID mask */
    }
            
        CAN_1.MB[Buffer].CS.B.CODE = 4;        /* MB buffer set to RX EMPTY */
}


/********************************************************************************
 * call this function read the received CAN message of CAN0
 * Buffer: select the MB to read the CAN message (MB0~MB63)
 * Return: the received CAN message in CAN message store struct
 * Note:
 *      this function should be called in CAN receive ISR to get the received CAN
 *      message and unlock the MB for next receive
 ********************************************************************************/
CAN_Msg_Strcut CAN0_ReceiveMsg( CAN_MessageBuffer Buffer)
{
	  uint8_t j;
	  uint32_t dummy;
	  
	  CAN_Msg_Strcut CAN_Msg;

	  CAN_Msg.Frame_CODE   = CAN_0.MB[Buffer].CS.B.CODE;    /* Read CODE, ID, LENGTH, DATA, TIMESTAMP */
	  dummy  = CAN_0.MB[Buffer].CS.B.IDE;
	  if(dummy == ExtendFrame)
	  {
		  CAN_Msg.Frame_Type = ExtendFrame;    
		  CAN_Msg.Frame_ID   = CAN_0.MB[Buffer].ID.R;
	  }
	  else
	  {
		  CAN_Msg.Frame_Type = StandardFrame;    
		  CAN_Msg.Frame_ID   = CAN_0.MB[Buffer].ID.B.ID_STD;
	  }
	  CAN_Msg.Frame_DataType = CAN_0.MB[Buffer].CS.B.RTR;
	  CAN_Msg.Frame_Length = CAN_0.MB[Buffer].CS.B.DLC;
	  for (j=0; j<CAN_Msg.Frame_Length; j++) 
	  { 
	    CAN_Msg.Frame_Data[j] = CAN_0.MB[Buffer].DATA.B[j];
	  }
	  CAN_Msg.Frame_TIMESTAMP = CAN_0.MB[Buffer].CS.B.TIMESTAMP;
	  dummy = CAN_0.TIMER.R;                /* Read TIMER to unlock message buffers */    
	  CAN_0.IFLAG1.R = (uint32_t)(1 <<Buffer);/* Clear CAN1 MB buffer flag */
	  
	  return CAN_Msg;
}

/********************************************************************************
 * call this function read the received CAN message of CAN1
 * Buffer: select the MB to read the CAN message (MB0~MB63)
 * Return: the received CAN message in CAN message store struct
 * Note:
 *      this function should be called in CAN receive ISR to get the received CAN
 *      message and unlock the MB for next receive
 ********************************************************************************/
CAN_Msg_Strcut CAN1_ReceiveMsg( CAN_MessageBuffer Buffer)
{
	  uint8_t j;
	  uint32_t dummy;
	  
	  CAN_Msg_Strcut CAN_Msg;

	  CAN_Msg.Frame_CODE   = CAN_1.MB[Buffer].CS.B.CODE;    /* Read CODE, ID, LENGTH, DATA, TIMESTAMP */
	  dummy  = CAN_1.MB[Buffer].CS.B.IDE;
	  if(dummy == ExtendFrame)
	  {
	  	CAN_Msg.Frame_Type = ExtendFrame;    
	  	CAN_Msg.Frame_ID   = CAN_1.MB[Buffer].ID.R;
	  }
	  else
	  {
	  	CAN_Msg.Frame_Type = StandardFrame;    
	  	CAN_Msg.Frame_ID   = CAN_1.MB[Buffer].ID.B.ID_STD;
	  }
	  CAN_Msg.Frame_DataType = CAN_1.MB[Buffer].CS.B.RTR;
	  CAN_Msg.Frame_Length = CAN_1.MB[Buffer].CS.B.DLC;
	  for (j=0; j<CAN_Msg.Frame_Length; j++) 
	  { 
	    CAN_Msg.Frame_Data[j] = CAN_1.MB[Buffer].DATA.B[j];
	  }
	  CAN_Msg.Frame_TIMESTAMP = CAN_1.MB[Buffer].CS.B.TIMESTAMP;
	  dummy = CAN_1.TIMER.R;                /* Read TIMER to unlock message buffers */    
	  CAN_1.IFLAG1.R = (uint32_t)(1 <<Buffer);/* Clear CAN1 MB buffer flag */
	  
	  return CAN_Msg;
}


/**************************************************************************************
 * call this function for CAN0 bus off handle
 * Return: None
 * Note:
 *      this function should be called in CAN bus off ISR to handle/recover the CAN bus 
**************************************************************************************/
void CAN0_BusOff_Handle(void)
{
	unsigned long temp;
	temp = CAN_0.CTRL1.B.BOFFREC;
	CAN_0.ESR1.B.BOFFINT = 1;	/** clear the bus off interrupt flag **/
	if (temp == 0)   			/* while the CAN bus off automatically recovery is enabled */
		temp = 0;               /* if automatically recover, no interrupt is needed infact,can just set a flag */
	else                        /* while the CAN bus off automatically recovery is disabled */
	{
		CAN_0.MCR.B.SOFTRST = 1;
		temp = CAN_0.MCR.B.SOFTRST;     /* soft reset the CAN module */
		while(temp)
		{
			temp = CAN_0.MCR.B.SOFTRST;	 /* waite until the soft reset is finished */
		}
		
		CAN_0.MCR.R = 0x5980000F;        /* reinitialize the MCR register */
	}
	
}

/**************************************************************************************
 * call this function for CAN1 bus off handle
 * Return: None
 * Note:
 *      this function should be called in CAN bus off ISR to handle/recover the CAN bus 
**************************************************************************************/
void CAN1_BusOff_Handle(void)
{
	unsigned long temp;
	temp = CAN_1.CTRL1.B.BOFFREC;
	CAN_1.ESR1.B.BOFFINT = 1;	/** clear the bus off interrupt flag **/
	if (temp == 0)   			/* while the CAN bus off automatically recovery is enabled */
		temp = 0;               /* if automatically recover, no interrupt is needed infact,can just set a flag */
	else                        /* while the CAN bus off automatically recovery is disabled */
	{
		CAN_1.MCR.B.SOFTRST = 1;
		temp = CAN_1.MCR.B.SOFTRST;     /* soft reset the CAN module */
		while(temp)
		{
			temp = CAN_1.MCR.B.SOFTRST;	 /* waite until the soft reset is finished */
		}
		
		CAN_1.MCR.R = 0x5980000F;        /* reinitialize the MCR register */
	}
	
}

/************************* INTERRUPT HANDLERS ************************/

void FlexCAN0_ESR_ISR (void)
{
    CAN_0.ESR1.B.ERRINT = 1;

}


void FlexCAN0_ESR_BTR_ISR (void)
{
    CAN_0.ESR1.B.TWRNINT = 1;
    CAN_0.ESR1.B.RWRNINT = 1;

    CAN0_BusOff_Handle();  /** call the bus off handle **/
}


void FlexCAN0_BUF03_ISR (void)
{
    CAN_0.IFLAG1.R =0x0000000F;


}


void FlexCAN0_BUF47_ISR (void)
{

	if(CAN_0.IFLAG1.R & MB4_INT_FLAF)
	{
		CAN_RxMsg = CAN0_ReceiveMsg(MB4);/*copy the received CAN data into RAM*/
		CAN_0.IFLAG1.R = MB4_INT_FLAF;      /* clear the interrupt flags */
	}
	else if(CAN_0.IFLAG1.R & MB6_INT_FLAF)
	{
		CAN_RxMsg = CAN0_ReceiveMsg(MB6);/*copy the received CAN data into RAM*/
		CAN_0.IFLAG1.R = MB6_INT_FLAF;      /* clear the interrupt flags */
	}
	else
	{
		CAN_0.IFLAG1.R =0x000000F0;          /* clear the interrupt flags */
	}

	INTC_0.CPR0.B.PRI = 0;/*set Current Priority to the lowest(0) to enable all peripheral interrupt */

	RcvDtProc();/*respond the PC terminal */
}


void FlexCAN1_ESR_ISR (void)
{
    CAN_1.ESR1.B.ERRINT = 1;

}


void FlexCAN1_ESR_BTR_ISR (void)
{
    CAN_1.ESR1.B.TWRNINT = 1;
    CAN_1.ESR1.B.RWRNINT = 1;

    CAN1_BusOff_Handle();  /** call the bus off handle **/

}


void FlexCAN1_BUF03_ISR (void)
{
    CAN_1.IFLAG1.R =0x0000000F;

}


void FlexCAN1_BUF47_ISR (void)
{
	 if(CAN_1.IFLAG1.R & MB4_INT_FLAF)
	 {
		 CAN_RxMsg = CAN1_ReceiveMsg(MB4);/*copy the received CAN data into RAM*/
		 CAN_1.IFLAG1.R = MB4_INT_FLAF;      /* clear the interrupt flags */
		 CAN1_BufferReceive_Flag = 1;     /*set the receive flag*/
	 }
	 else if(CAN_1.IFLAG1.R & MB6_INT_FLAF)
	 {
		CAN_RxMsg = CAN1_ReceiveMsg(MB6);/*copy the received CAN data into RAM*/
		CAN_1.IFLAG1.R = MB6_INT_FLAF;      /* clear the interrupt flags */
		CAN1_BufferReceive_Flag = 1;	  /*set the receive flag*/
	 }
	 else
	 {
		 CAN_1.IFLAG1.R =0x000000F0;   /* clear the interrupt flags */
	 }

}


void FlexCAN1_BUF811_ISR (void)
{
    CAN_1.IFLAG1.R =0x00000F00;

}


void FlexCAN1_BUF1215_ISR (void)
{
    if(CAN_1.IFLAG1.R & MB14_INT_FLAF)
   	 {
   		 CAN_RxMsg = CAN1_ReceiveMsg(MB14);/*copy the received CAN data into RAM*/
   		 CAN_1.IFLAG1.R = MB14_INT_FLAF;      /* clear the interrupt flags */
   		 CAN1_BufferReceive_Flag = 1;     /*set the receive flag*/
   	 }
   	 else if(CAN_1.IFLAG1.R & MB15_INT_FLAF)
   	 {
   		CAN_RxMsg = CAN1_ReceiveMsg(MB15);/*copy the received CAN data into RAM*/
   		CAN_1.IFLAG1.R = MB15_INT_FLAF;      /* clear the interrupt flags */
   		CAN1_BufferReceive_Flag = 1;	  /*set the receive flag*/
   	 }
   	 else
   	 {
   	    CAN_1.IFLAG1.R =0x0000F000;
   	 }

}

/** call to toggle an pre-define I/O to toggle a external LED or generate a square wave for test/debug **/
void ToggleLED1_IO(void)
{
  unsigned int j = 0;

  for(j = 0; j < 0x20000; j ++) {}  /* some delay  */
  SIUL2.GPDO[LED_B].B.PDO = 1;  /* output High */
  for(j = 0; j < 0x20000; j ++) {}  /* some delay  */
  SIUL2.GPDO[LED_B].B.PDO = 0;  /* output Low  */

}

/** for FlexCAN api test **/
void FlexCAN_api_test(void)
{
	uint8_t j = 0;
	static uint8_t myCNT = 0;

	/* fill the CAN frame data */

	  CAN_TxMsg.Frame_Type = StandardFrame;
	  CAN_TxMsg.Frame_DataType = DataFrame;
	  CAN_TxMsg.Frame_ID = 0x333;

	  for(j=0;j<8;j++)
	  {
	   	  CAN_TxMsg.Frame_Data[j] = (uint8_t)(myCNT + 1);
	  }

	  for(j=0;j<2;j++)
	  {
	    	ToggleLED1_IO();
			CAN0_TransmitMsg(MB0, CAN_TxMsg);/* Transmit one message from a FlexCAN 0 buffer */
	  }

	  if(CAN0_BufferReceive_Flag == 1)
	  {
	    	CAN0_BufferReceive_Flag = 0;  //clear the flag

//	    	INTC_0.CPR0.B.PRI = 0;/*set Current Priority to the lowest(0) to enable all peripheral interrupt */

	    	SIUL2.GPDO[LED_R].B.PDO = 0;  /* toggle the LED_R  */

	    	myCNT++;


			CAN_RxFeedbackMsg.Frame_Type = CAN_RxMsg.Frame_Type;
			CAN_RxFeedbackMsg.Frame_DataType = CAN_RxMsg.Frame_DataType;

			/*   get the CAN received message    */
			CAN_RxFeedbackMsg.Frame_ID = CAN_RxMsg.Frame_ID;
			for(j=0;j<8;j++)
			{
				CAN_RxFeedbackMsg.Frame_Data[j] = CAN_RxMsg.Frame_Data[j];
			}

			CAN0_TransmitMsg(MB1, CAN_RxFeedbackMsg);/* feedback the received message from a FlexCAN 1 buffer */

	  }


//	 if(CAN1_BufferReceive_Flag == 1)
//	 {
//	      	CAN1_BufferReceive_Flag = 0;  //clear the flag
//	      	for(j=0;j<2;j++)
//	      	{
//	      		Msic_DelayMS_PIT(20);//20ms
//	      		//Toggle_MCU_LED2();
//	      		//ToggleLED1_IO();
//	      		if(j==0)
//	      		{
//	      			CAN_RxFeedbackMsg.Frame_Type = CAN_RxMsg.Frame_Type;
//	      			CAN_RxFeedbackMsg.Frame_DataType = CAN_RxMsg.Frame_DataType;
//
//	      			/*   get the CAN received message    */
//	      			CAN_RxFeedbackMsg.Frame_ID = CAN_RxMsg.Frame_ID;
//	      			for(j=0;j<8;j++)
//	      			{
//	      				CAN_RxFeedbackMsg.Frame_Data[j] = CAN_RxMsg.Frame_Data[j];
//	      			}
//
//	      			j = 0;  /*  recover the temp*/
//	      		}
//	      		CAN1_TransmitMsg(MB1, CAN_RxFeedbackMsg);/* feedback the received message from a FlexCAN 1 buffer */
//	      	}
//	  }
}

/*
 *######################################################################
 *                           End of File
 *######################################################################
*/


