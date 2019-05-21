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
 * file                   : flexcan_init.h
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
 * Brief Description      : This file contains functions declaration of FlexCAN code file
 *
 *
 *######################################################################
*/

#ifndef  _FLEXCAN_INIT_H
#define  _FLEXCAN_INIT_H
/********************  Dependent Include files here **********************/

#include "derivative.h" /* include peripheral declarations */


/*********************  Receive FIFO Macro here ****************************/
#define FLEXCAN_0_RXFIFO     (*(volatile struct FLEXCAN_RXFIFO_t *)   &CAN_0.BUF[0])

/**********************  Function Prototype here *************************/

uint8_t flexcan_init_fnc(void);

uint8_t flexcan_0_deinit_fnc(void);
uint8_t flexcan_1_deinit_fnc(void);

uint8_t flexcan_0_init_fnc(void);
uint8_t flexcan_1_init_fnc(void);


#endif  /*_FLEXCAN_INIT_H*/

/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

