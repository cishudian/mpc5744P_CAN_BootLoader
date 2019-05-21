/*
 * FlexCAN_api.h
 *
 *  Created on: Apr 23, 2014
 *      Author: B46398
 */

#ifndef FLEXCAN_API_H_
#define FLEXCAN_API_H_

#include "derivative.h" /* include peripheral declarations */

/** used for CAN message frame type configuration **/
typedef enum {
ExtendFrame = 1,
StandardFrame = 0
}CAN_FrameType;

/** used for CAN message data type configuration **/
typedef enum {
RemoteFrame = 1,
DataFrame = 0
}CAN_DataType;

/** struct used for CAN message store **/
typedef struct {
	CAN_FrameType Frame_Type;          /* CAN frame type */
	uint32_t Frame_CODE;               /* CAN frame message buffer code */
	uint32_t Frame_ID;                 /* CAN frame message ID */
	CAN_DataType Frame_DataType;       /* is it a remote frame data */
	uint32_t Frame_Length;             /* CAN frame message number of data bytes */
	uint8_t  Frame_Data[8];            /* CAN frame message data string*/
	uint32_t Frame_TIMESTAMP;          /* CAN frame message time */ 		
}CAN_Msg_Strcut;

/** for FlexCAN Message Buffer select**/
typedef enum{
	MB0 = 0,
	MB1 = 1,
	MB2 = 2,
	MB3 = 3,
	MB4 = 4,
	MB5 = 5,
	MB6 = 6,
	MB7 = 7,
	MB8 = 8,
	MB9 = 9,
	MB10 = 10,
	MB11 = 11,
	MB12 = 12,
	MB13 = 13,
	MB14 = 14,
	MB15 = 15,
	MB16 = 16,
	MB17 = 17,
	MB18 = 18,
	MB19 = 19,
	MB20 = 20,
	MB21 = 21,
	MB22 = 22,
	MB23 = 23,
	MB24 = 24,
	MB25 = 25,
	MB26 = 26,
	MB27 = 27,
	MB28 = 28,
	MB29 = 29,
	MB30 = 30,
	MB31 = 31,
	MB32 = 32,
	MB33 = 33,
	MB34 = 34,
	MB35 = 35,
	MB36 = 36,
	MB37 = 37,
	MB38 = 38,
	MB39 = 39,
	MB40 = 40,
	MB41 = 41,
	MB42 = 42,
	MB43 = 43,
	MB44 = 44,
	MB45 = 45,
	MB46 = 46,
	MB47 = 47,
	MB48 = 48,
	MB49 = 49,
	MB50 = 50,
	MB51 = 51,
	MB52 = 52,
	MB53 = 53,
	MB54 = 54,
	MB55 = 55,
	MB56 = 56,
	MB57 = 57,
	MB58 = 58,
	MB59 = 59,
	MB60 = 60,
	MB61 = 61,
	MB62 = 62,
	MB63 = 63
}CAN_MessageBuffer;

/** the FlexCAN MB interrupt flag bit mask **/
#define MB0_INT_FLAF   (uint32_t)(1<<0)
#define MB1_INT_FLAF   (uint32_t)(1<<1)
#define MB2_INT_FLAF   (uint32_t)(1<<2)
#define MB3_INT_FLAF   (uint32_t)(1<<3)
#define MB4_INT_FLAF   (uint32_t)(1<<4)
#define MB5_INT_FLAF   (uint32_t)(1<<5)
#define MB6_INT_FLAF   (uint32_t)(1<<6)
#define MB7_INT_FLAF   (uint32_t)(1<<7)
#define MB8_INT_FLAF   (uint32_t)(1<<8)
#define MB9_INT_FLAF   (uint32_t)(1<<9)
#define MB10_INT_FLAF  (uint32_t)(1<<10)
#define MB11_INT_FLAF  (uint32_t)(1<<11)
#define MB12_INT_FLAF  (uint32_t)(1<<12)
#define MB13_INT_FLAF  (uint32_t)(1<<13)
#define MB14_INT_FLAF  (uint32_t)(1<<14)
#define MB15_INT_FLAF  (uint32_t)(1<<15)
#define MB16_INT_FLAF  (uint32_t)(1<<16)
#define MB17_INT_FLAF  (uint32_t)(1<<17)
#define MB18_INT_FLAF  (uint32_t)(1<<18)
#define MB19_INT_FLAF  (uint32_t)(1<<19)
#define MB20_INT_FLAF  (uint32_t)(1<<20)
#define MB21_INT_FLAF  (uint32_t)(1<<21)
#define MB22_INT_FLAF  (uint32_t)(1<<22)
#define MB23_INT_FLAF  (uint32_t)(1<<23)
#define MB24_INT_FLAF  (uint32_t)(1<<24)
#define MB25_INT_FLAF  (uint32_t)(1<<25)
#define MB26_INT_FLAF  (uint32_t)(1<<26)
#define MB27_INT_FLAF  (uint32_t)(1<<27)
#define MB28_INT_FLAF  (uint32_t)(1<<28)
#define MB29_INT_FLAF  (uint32_t)(1<<29)
#define MB30_INT_FLAF  (uint32_t)(1<<30)
#define MB31_INT_FLAF  (uint32_t)(1<<31)


#define MB32_INT_FLAF   (uint32_t)(1<<0)
#define MB33_INT_FLAF   (uint32_t)(1<<1)
#define MB34_INT_FLAF   (uint32_t)(1<<2)
#define MB35_INT_FLAF   (uint32_t)(1<<3)
#define MB36_INT_FLAF   (uint32_t)(1<<4)
#define MB37_INT_FLAF   (uint32_t)(1<<5)
#define MB38_INT_FLAF   (uint32_t)(1<<6)
#define MB39_INT_FLAF   (uint32_t)(1<<7)
#define MB40_INT_FLAF   (uint32_t)(1<<8)
#define MB41_INT_FLAF   (uint32_t)(1<<9)
#define MB42_INT_FLAF   (uint32_t)(1<<10)
#define MB43_INT_FLAF   (uint32_t)(1<<11)
#define MB44_INT_FLAF   (uint32_t)(1<<12)
#define MB45_INT_FLAF   (uint32_t)(1<<13)
#define MB46_INT_FLAF   (uint32_t)(1<<14)
#define MB47_INT_FLAF   (uint32_t)(1<<15)
#define MB48_INT_FLAF   (uint32_t)(1<<16)
#define MB49_INT_FLAF   (uint32_t)(1<<17)
#define MB50_INT_FLAF   (uint32_t)(1<<18)
#define MB51_INT_FLAF   (uint32_t)(1<<19)
#define MB52_INT_FLAF   (uint32_t)(1<<20)
#define MB53_INT_FLAF   (uint32_t)(1<<21)
#define MB54_INT_FLAF   (uint32_t)(1<<22)
#define MB55_INT_FLAF   (uint32_t)(1<<23)
#define MB56_INT_FLAF   (uint32_t)(1<<24)
#define MB57_INT_FLAF   (uint32_t)(1<<25)
#define MB58_INT_FLAF   (uint32_t)(1<<26)
#define MB59_INT_FLAF   (uint32_t)(1<<27)
#define MB60_INT_FLAF   (uint32_t)(1<<28)
#define MB61_INT_FLAF   (uint32_t)(1<<29)
#define MB62_INT_FLAF   (uint32_t)(1<<30)
#define MB63_INT_FLAF   (uint32_t)(1<<31)

/*---------------------------------------------------------------------------*/
/* External variables                                                        */
/*---------------------------------------------------------------------------*/
extern CAN_Msg_Strcut CAN_TxMsg;         /* for CAN TX test */
extern CAN_Msg_Strcut CAN_RxMsg;         /* for CAN RX test */
extern CAN_Msg_Strcut CAN_RxFeedbackMsg; /* used to feed back the received CAN frame */
extern uint8_t CAN0_BufferReceive_Flag;  /* FlexCAN0 received CAN frame flag */
extern uint8_t CAN1_BufferReceive_Flag;  /* FlexCAN1 received CAN frame flag */

extern void CAN0_TransmitMsg (CAN_MessageBuffer Buffer, CAN_Msg_Strcut CAN_Msg);
extern void CAN1_TransmitMsg (CAN_MessageBuffer Buffer, CAN_Msg_Strcut CAN_Msg);

extern void CAN0_ReceiveInit(CAN_MessageBuffer Buffer, CAN_FrameType FrameType,  CAN_DataType DataType, uint32_t ID, uint32_t ID_Mask);
extern void CAN1_ReceiveInit(CAN_MessageBuffer Buffer, CAN_FrameType FrameType,  CAN_DataType DataType, uint32_t ID, uint32_t ID_Mask);

extern CAN_Msg_Strcut CAN0_ReceiveMsg( CAN_MessageBuffer Buffer);
extern CAN_Msg_Strcut CAN1_ReceiveMsg( CAN_MessageBuffer Buffer);

void FlexCAN_api_test(void);

void CAN0_BusOff_Handle(void);
void CAN1_BusOff_Handle(void);

void FlexCAN0_ESR_ISR(void);
void FlexCAN0_ESR_BTR_ISR(void);
void FlexCAN0_BUF03_ISR(void);
void FlexCAN0_BUF47_ISR(void);
void FlexCAN1_ESR_ISR(void);
void FlexCAN1_ESR_BTR_ISR(void);
void FlexCAN1_BUF03_ISR(void);
void FlexCAN1_BUF47_ISR(void);
void FlexCAN1_BUF811_ISR(void);
void FlexCAN1_BUF1215_ISR(void);

#endif /* FLEXCAN_API_H_ */
