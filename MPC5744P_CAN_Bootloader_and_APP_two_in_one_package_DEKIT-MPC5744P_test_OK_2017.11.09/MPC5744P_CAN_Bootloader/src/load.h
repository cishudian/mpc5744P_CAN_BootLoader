
#ifndef LOAD_H_
#define LOAD_H_

#include  "ssd_c55.h"
#include  "ssd_c55_internal.h"

#include  "Flash_Driver_utils.h"
#include  "block_mpc574xP.h"

#define  SPASS       0
#define  SERR        1
#define  SFileStart  2
#define  SFileEnd    3


#define DownLoadID  0x64
#define UpLoadID    0xC8

#define NO_ERR 0x00
#define ERR_BUFFER_FULL 0x80


typedef struct {
	  uint32_t  ID;
	  uint8_t FrameType;
	  uint8_t FrameFormat;
	  uint8_t  DtLen;
	  uint8_t  data[8];
} CanMsg_t;

/******************* info code from host -> ECU ************************************************/
#define  DOWN_LINK             0xFF
#define  DOWN_LINE_END         0xFE


#define  DOWN_FILE_END         0xFD



/******************* acknowledging from ECU -> HOST in first CAN uint8_t **************************/
#define  UP_READY              0xC3
#define  UP_BUSY               0xC2
#define  UP_PRGEND             0xC1
#define  UP_ERR                0x00

/******************* ECU bootloader status *****************************************************/
#define  _STA_NOT_LINKED       0x00
#define  _STA_LINKED           0x01
#define  _STA_PRGEND           0x02

/*
 * structure used to store S-record information
 * address, length and data
 */
typedef struct {
	uint32_t addr;
	uint32_t  dtlen;
	uint16_t  data[20];
} SRecord_t;

extern  SRecord_t srcd,LastLine_srcd;

extern void SRecord_Copy(SRecord_t *From, SRecord_t *To );
extern void SRecord_Merge(SRecord_t *Base, SRecord_t *Add );
extern uint8_t SRcdCvt(uint8_t * line, SRecord_t *srcd);
extern void SrcdAlign4W(SRecord_t *srcd);
extern void SrcdProg_RAM(SRecord_t *srcd_t);
extern void SrcdProg_PFlash(SRecord_t *srcd);


extern void StatusAck(uint8_t sta) ;
extern void RcvDtProc(void);
extern void Prepare_Before_Jump(void);
extern void app_entry(void);

extern void Cpu_DelayMS(uint32_t ms);

extern void ErrorTrap(UINT32 returnCode); /*error trap function for Flash driver*/
extern void Flash_Init(void);
extern void erase_flash_except_bootloader(void);
/*
 * all this symbols difined in project linker command file
 */
//extern uint32_t __SRAM_BASE_ADDR,__SRAM_SIZE,__LOCAL_DMEM_BASE_ADDR,__LOCAL_DMEM_SIZE;

#define __SRAM_BASE_ADDR		0x40000000
#define __SRAM_SIZE				0x00060000
#define __LOCAL_DMEM_BASE_ADDR  0x50800000
#define __LOCAL_DMEM_SIZE		0x00010000

#define RAM_RANGE_CHECK(addr)     ((addr>(__SRAM_BASE_ADDR-1))&&(addr<(__SRAM_BASE_ADDR + __SRAM_SIZE)) ? 1 :0)

#endif /*end of LOAD_H_*/
