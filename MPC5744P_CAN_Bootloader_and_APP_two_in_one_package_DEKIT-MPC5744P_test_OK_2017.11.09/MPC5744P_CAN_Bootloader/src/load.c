
#include "derivative.h"      /* derivative-specific definitions */

#include "load.h"
#include "compiler_api.h"
#include "FlexCAN_api.h"
#include "flexcan_init.h"

SRecord_t srcd;

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

uint32_t blkLockState;         		/* block lock status to be retrieved */
uint32_t pflash_pfcr0, pflash_pfcr1, pflash_pfcr2, pflash_pfcr3;

/* Source buffer for program and verify */
uint32_t  buffer[BUFFER_SIZE_BYTE / C55_WORD_SIZE];
MEM_REGION_INFO memRegionInfo;

uint32_t returnCode;         /* Return code from each SSD function. */
uint32_t  demoResult;

uint32_t dest;               /* destination address */
uint32_t size;               /* size applicable */
uint32_t source;             /* source address for program and verify */

uint32_t failedAddress;     /* save the failed address in flash */
uint32_t failedData;        /* save the failed data in flash */
uint32_t failedSource;      /* Save the failed source for verification */

uint32_t sum;               /* check sum result */

BOOL skipFlag;
uint32_t temp;

uint32_t lowBlockSelect;    /*flash low block select bitmap*/
uint32_t midBlockSelect;    /*flash middle block select bitmap*/
uint32_t highBlockSelect;   /*flash high block select bitmap*/

N256K_BLOCK_SEL n256KBlockSelect; /*flash 256KB block select bitmap*/

static uint8_t hex2value(uint8_t *p);

/*
 * copy the S-Record information from From to To
 */
void SRecord_Copy(SRecord_t *From, SRecord_t *To )
{
	uint32_t i;

	To->addr = From->addr;   /*copy address*/
	To->dtlen = From->dtlen; /*copy length*/

	for(i=0;i<To->dtlen;i++)
	{
		To->data[i] = From->data[i];/*copy data*/
	}

}
/*
 * merge two S-Record, Base = Base + Add
 * return the new S-Record via Base
 */
void SRecord_Merge(SRecord_t *Base, SRecord_t *Add )
{
	uint32_t i;

	Base->dtlen += Add->dtlen;  /*merge length*/

	for(i=0;i<Add->dtlen;i++)
	{
		Base->data[Base->dtlen + i] = Add->data[i];/*copy/add data*/
	}
}


/*********************************************************************************
**** function: convert the original S-record line strings to SRecord_t construct
****           format for further process  
**** input   *line: the original S-record line strings
**** output *srcd_t: the converted result in  SRecord_t construct format
*********************************************************************************/
uint8_t SRcdCvt(uint8_t * line, SRecord_t *srcd_t)
{   
    uint8_t  stype,adrlen,slength,sdata,sdtlen,oddflag=0;
    uint8_t  checksum = 0;
    uint16_t  i;
    uint8_t  *sbuffer;
  
    if(*line!='S')      /*S19 line must start with char 'S'*/
    {
        srcd_t->dtlen=0;/*if not, the length set to zero and error report*/      
		    return SERR;
    }
		
    line++;             /*move to next char*/
    stype = *line - '0';/*indentify the S19 line type*/	

	if(stype == 0)
	{   /*S0 indicate the S19 file start and information, not useful for bootloader*/
		srcd_t->dtlen=0;
		return SFileStart;
	}
	else if(stype>6)
		{   /*S7/8/9 indicates the S19 file end*/
			srcd_t->dtlen=0;
			return SFileEnd;
		}
		else 
		{
			 adrlen = stype+1;            /*adrlen(address length) is the number of bytes of addr. 16bit@2B, 24bit@3B, 32bit@4B*/

			 line++;

			 slength=hex2value(line);   /*get the bytes number of addr. data & checksum  */

			 sdtlen=slength-adrlen-1;   /*get data length in bytes, remove one CRC uint8_t at line end */

			if(sdtlen&0x01)
			{                          /*if odd number of bytes      */
				oddflag=1;             /*the last uint8_t will be trancated and processed later*/
			}

			srcd_t->dtlen = (uint16_t)(sdtlen>>1);  /*data lenghth in uint16_t*/

			checksum += slength;  /*checksum includes all data bytes + address uint8_t + length uint8_t, this is the length uint8_t*/

			line += 2;      	 /*increase 2byte text/per char */
      
			for(srcd_t->addr=0,i=0; i<adrlen; i++,line=line+2) /*get the S-record line address*/
			{
			    sdata = hex2value(line);                  /*the uint8_t from 2 chars*/
				srcd_t->addr = (srcd_t->addr<<8) + sdata; /*re-construct the address*/
				checksum+=sdata;							/*checksum includes all data bytes + address uint8_t + length uint8_t, here is the address bytes*/
			}                                             /*calculate the S-record line CRC checksum*/
        
			sbuffer = (uint8_t *)&(srcd_t->data[0]);  		/*assign the buffer pointer to the S-Record data array*/

			for(i=0; i<srcd_t->dtlen*2; i++)
			{
			  	 sdata = hex2value(line);                /*the uint8_t from 2 chars*/
				 line +=  2;
				 *((uint8_t*)(sbuffer+i)) = sdata;       /*store the parsed data to srcd_t construct*/
				 checksum += sdata;                      /*checksum includes all data bytes + address uint8_t + length uint8_t, here is the data bytes*/
		    }

		}
		
		/* line point to last uint8_t (which has not been processed) now, the SRecord checksum is immediately after the last uint8_t  */
		if(oddflag)
		{
			sdata = hex2value(line);
			srcd_t->data[srcd_t->dtlen++]=(((uint16_t)sdata)<<8)|0x00FF;  //fill 0xFF to align uint16_t(two uint8_t )e.g. 0x8a -> 0x8aff
			checksum+=sdata;		/*checksum includes all data bytes + address uint8_t + length uint8_t, here is the last odd data uint8_t*/
			line+=2;
		}

		if ( checksum + hex2value(line) == 0xFF ) /*check CRC checksum*/
		    return SPASS;
		else
		    return SERR;
}

/******************************************************************************************
**** function:
****          1) convert the logical/local address to global address (optional)
****          2) align the start address to 4W(=8 Bytes) and staff data 0xFFFF accordingly
**** input *srcd_t: the convert result in  SRecord_t construct format
**** output : none
*******************************************************************************************/
void SrcdAlign4W(SRecord_t *srcd_t)
{  
    uint16_t i;
    uint8_t stafno;

 /*
  * the below logic address to physical address convert is just needed for S08/s12(X) serial MCU
  * the detailed logic address and corresponding physical(global) address should be referred to the chip datasheet/reference manual
  */
#ifdef S08_S12_S12X
    uint8_t *p;
    volatile dword physical_address;
    
    p = (uint8_t *)&srcd_t->addr;
    p++;
    if(*p != 0)  /*the paged logical address*/
    {            
      physical_address = (srcd_t->addr & 0xFF0000)>>16;
      physical_address = (physical_address - 0x08) * 0x4000 + 0x020000;
      physical_address = physical_address + ((srcd_t->addr & 0xFFFF) - 0x8000);
      
      srcd_t->addr = physical_address;
    } 
    else  /*the local address, eg.0x4000~0x7FFF-->0x3400~0x37FFF, 0xC000~0xFFFF-->0x3C000~0x3FFFF*/
    {
      srcd_t->addr = srcd_t->addr + 0x30000;
    }
#endif
    stafno = (srcd_t->addr&0x7)>>1;   /* number of uint16_t need to be pre-staffed  */
    srcd_t->addr &= 0xFFFFFFF8;           /* align data base address at 4W   */
    
    if(stafno) 
    {
        for(i=srcd_t->dtlen; i>0; i--) 
            srcd_t->data[i+stafno-1] = srcd_t->data[i-1];  // move forward data in number of stafno
        
        srcd_t->dtlen += stafno;    // update dtlen
        
        while(stafno--)    
            srcd_t->data[stafno] = 0xFFFF;           // pre-staff 0xFFFF
    }

    while((srcd_t->dtlen&0x000003)!=0)   // need to append post-staffing uint16_t
        srcd_t->data[srcd_t->dtlen++] = 0xFFFF;
}



/*************************************************************************************
**** function: convert the 2 chars of S-record line to 1 Byte hex value*  
**** input *p: pointor to S-record line string
**** output : 1 Byte hex value
**************************************************************************************/
uint8_t hex2value(uint8_t *p)
{
	uint8_t k,i;

    k=*p;
    p++;
    i=*p;
    p++;

    if(k>='0' && k<='9')
        k=k-'0';
    else
        k=k-'A'+10;
    
    if(i>='0' && i<='9')
        i=i-'0';
    else
        i=i-'A'+10;
    
    return k*16+i;
}

/************************************************************************
** CAN received data process, feed back busy and flag new data received
** input: none
** output: none
***********************************************************************/
void RcvDtProc(void)
{

    CAN_TxMsg.Frame_ID = UpLoadID;
    CAN_TxMsg.Frame_DataType = DataFrame;
    CAN_TxMsg.Frame_Type = StandardFrame;
    CAN_TxMsg.Frame_Length = 1;
    CAN_TxMsg.Frame_Data[0] = UP_BUSY;

    /* feedback UP_BUSY immediately after a valid frame received */
    CAN0_TransmitMsg(MB0,CAN_TxMsg);

    CAN0_BufferReceive_Flag = 1;	  /*set the receive flag*/
}

/***************************************************************
** bootloader status acknowledge to PC terminal
** input: the status to feed back
** output: none
****************************************************************/
void StatusAck(uint8_t sta)
{
	CAN_TxMsg.Frame_ID = UpLoadID;
	CAN_TxMsg.Frame_DataType = DataFrame;
	CAN_TxMsg.Frame_Type = StandardFrame;
	CAN_TxMsg.Frame_Length = 1;
	CAN_TxMsg.Frame_Data[0] = sta;

   /* feedback UP_BUSY immediately after a valid frame received  */
	CAN0_TransmitMsg(MB0,CAN_TxMsg);

}



/*******************************************************************
** function: clean the bootloader used RAM  for NVM driver
** input: none
** output: none
********************************************************************/
void CleanRAM(void)
{
    uint32_t cnt;
    uint32_t *pRam;

    /*
     * clean system SRAM
     */
    cnt = __SRAM_SIZE/4;
    pRam = (uint32_t*)__SRAM_BASE_ADDR;

    while(cnt--)
        *pRam++ = 0;

    /*
	 * clean system Local DMEM
	 */
	cnt = __LOCAL_DMEM_SIZE/4;
	pRam = (uint32_t*)__LOCAL_DMEM_BASE_ADDR;

	while(cnt--)
		*pRam++ = 0;
}

/*******************************************************************
** function: do the preparation for bootloader jump to user app
** input: none
** output: none
********************************************************************/
void Prepare_Before_Jump(void)
{
	flexcan_0_deinit_fnc();   /*shutdown the MSCAN module*/
	PPCASM (" wrteei 0 "); 		  /*disable the CPU interrupt*/
    CleanRAM();       /*clean the bootloader used RAM  for NVM driver*/

}

/*************************************************************************************
**** function: program the S-record into RAM
**** input *srcd_t: the converted word aligned result in  SRecord_t construct format
**** output : none
**************************************************************************************/
void SrcdProg_RAM(SRecord_t *srcd_t)
{
    uint8_t i;

    for(i=0; i<srcd_t->dtlen;)
    {
       *(uint32_t *)(srcd_t->addr+i*2) =  *(uint32_t *)&srcd_t->data[i]; /*4 Bytes per write*/
       i += 2;
    }
}

/*************************************************************************************
**** function: program the S-record into P-Flash
**** input *srcd_t: the converted and 4W aligned result in  SRecord_t construct format
**** output : none
**************************************************************************************/
void SrcdProg_PFlash(SRecord_t *srcd_t)
{
	register uint32_t Result;

	Result = App_FlashProgram(&ssdConfig,
								FALSE,
								srcd_t->addr,
								(srcd_t->dtlen*2),
								(uint32_t)&srcd_t->data[0],
								&pgmCtxData);
	if (Result == DEMO_FAIL)
	{
		ErrorTrap(Result);
	}
	/* Program verify */
	Result = App_ProgramVerify(&ssdConfig,
								srcd_t->addr,
								(srcd_t->dtlen*2),
								(uint32_t)&srcd_t->data[0],
								&failedAddress,
								&failedData,
								&failedSource,
								&pvCtxData);
	if (Result == DEMO_FAIL)
	{
		ErrorTrap(Result);
	}

}

/*************************************************************************************************
 * this function call the Flash driver to:
 *  1.initialize the Flash module
 *  2. lock the UTest Flash space and bootloader reside space
 *  2.unlock the user application code Flash space
 ************************************************************************************************/
void Flash_Init(void)
{
		register uint32_t returnCode;           /* Return code from each SSD function. */

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
}


/***************************************************************
** erase the flash block for user application
** input: none
** output: none
****************************************************************/
void erase_flash_except_bootloader(void)
{
	register uint32_t Result;
	uint32_t i;                    		/* Index */
	uint32_t j;
	BOOL skipFlag;
	uint32_t temp;

	uint32_t lowBlockSelect;
	uint32_t midBlockSelect;
	uint32_t highBlockSelect;

	N256K_BLOCK_SEL n256KBlockSelect;

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
			Result = App_FlashErase(&ssdConfig,
									 C55_ERASE_MAIN,
									 lowBlockSelect,
									 midBlockSelect,
									 highBlockSelect,
									 n256KBlockSelect);
			if (Result == DEMO_FAIL)
			{
				ErrorTrap(Result);
			}
			dest = BLOCK_START_ADDRS[i];
			size = BLOCK_END_ADDRS[i] + 1 - BLOCK_START_ADDRS[i];
			/* blank check */
			Result = App_BlankCheck(&ssdConfig,
										dest,
										size,
										&failedAddress,
										&failedData,
										&bcCtxData);
			if (Result == DEMO_FAIL)
			{
				ErrorTrap(Result);
			}
		}// end of if (skipFlag == FALSE)
	}// end of for (i = 0; i < NUM_BLOCK_ALL; i++)
}

/***************************************************************************************
 * delay some microsecond with software loop
 ***************************************************************************************/
void Cpu_DelayMS(uint32_t ms)
{
	uint32_t Cpu_Freq;
	while(ms--)
	{
		for(Cpu_Freq = 0x1000;Cpu_Freq>0;)
			Cpu_Freq--;
	}
}

/****************************** CODE FOR CAN COMMUNICATION *************************************/
/* Values in ASCII table should be avoided 0~9, a~f, A~F, s, S                                 */
/* 0~9: 0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39                                      */
/* a~f: 0x61,0x62,0x63,0x64,0x65,0x66                                                          */
/* A~F: 0x41,0x42,0x43,0x44,0x45,0x46                                                          */
/* s:   0x73                                                                                   */
/* S:   0x53                                                                                   */
/***********************************************************************************************/
/*
#define  LOAD_LINK         0xFF  
#define  LOAD_DATA         0xFE
#define  LOAD_LINE_END     0xFD
#define  LOAD_FILE_END     0xFC

#define  UP_READY          0xC3
#define  UP_BUSY           0xC2
#define  UP_PRGEND         0xC1
#define  UP_ERR            0x00
*/



        
      
    
    
    
    
    
