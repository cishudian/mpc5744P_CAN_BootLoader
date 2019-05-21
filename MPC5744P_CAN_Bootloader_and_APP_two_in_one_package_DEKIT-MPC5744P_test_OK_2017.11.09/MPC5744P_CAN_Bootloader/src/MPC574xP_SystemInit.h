/*
 * MPC574xP_SystemInit.h
 *
 *  Created on: 2017Äê11ÔÂ3ÈÕ
 *      Author: pc
 */

#ifndef MPC574XP_SYSTEMINIT_H_
#define MPC574XP_SYSTEMINIT_H_

#define 	DRUN_MODE 	0x3

#include "project.h"

extern void Sys_Init(void);
extern void GPIO_Aux_Function_Config(void);
extern void Periphral_INTC_Init(void);
extern void PIT_Channel0_100ms_Init(void);
extern void PIT_Channel0_100ms_ISR(void);

#endif /* MPC574XP_SYSTEMINIT_H_ */
