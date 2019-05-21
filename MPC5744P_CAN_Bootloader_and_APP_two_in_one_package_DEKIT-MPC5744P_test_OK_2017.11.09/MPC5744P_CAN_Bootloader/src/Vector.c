/**************************************************************************/
/*                                                                        */
/* DESCRIPTION:                                                           */
/* This is a generic base template for all core exceptions, excluding     */
/* IVOR4 exceptions which have seperate handler                           */
/*                                                                        */
/* This file starts in memory at the beginning of the                     */
/*".core_exceptions_table" section.                                       */
/**************************************************************************/
#include "compiler_api.h"

#include "derivative.h" /* include peripheral declarations */

#define PPCASMF(x) PPCASM (" " tostring(x) " ")
#define PPCASMF2(x,x1) PPCASM (" " tostring(x) "," tostring(x1) " ")

PPCASMF( .globl VTABLE);
PPCASMF( .globl IVOR0_Vector );
PPCASMF( .globl IVOR1_Handler );
PPCASMF( .globl IVOR2_Handler );
PPCASMF( .globl IVOR3_Vector );
PPCASMF( .globl IVOR4_Vector );
PPCASMF( .globl IVOR5_Vector );
PPCASMF( .globl IVOR6_Vector );
PPCASMF( .globl IVOR7_Vector );
PPCASMF( .globl IVOR8_Vector );
PPCASMF( .globl IVOR9_Vector );
PPCASMF( .globl IVOR10_Vector );
PPCASMF( .globl IVOR11_Vector );
PPCASMF( .globl IVOR12_Vector );
PPCASMF( .globl IVOR13_Vector );
PPCASMF( .globl IVOR14_Vector );
PPCASMF( .globl IVOR15_Vector );

PPCASMF( .globl INTC_INTCInterruptHandler);

PPCASMF( .extern     IVOR4_Handler);
PPCASMF2( .section    .core_exceptions_table, "axv" );

VEC_ALIGN;
PPCASMF( VTABLE: );
PPCASMF( IVOR0_Vector: );
PPCASMF( e_b   IVOR0_Vector );

VEC_ALIGN;
PPCASMF( IVOR1_Vector: );
PPCASMF( e_b   IVOR1_Handler );

VEC_ALIGN;
PPCASMF( IVOR2_Vector: );
PPCASMF( e_b   IVOR2_Handler );

VEC_ALIGN;
PPCASMF( IVOR3_Vector: );
PPCASMF( e_b   IVOR3_Vector );

VEC_ALIGN;
PPCASMF( IVOR4_Vector: );
PPCASMF( e_b   IVOR4_Handler );
//PPCASMF( e_b   INTC_INTCInterruptHandler );

VEC_ALIGN;
PPCASMF( IVOR5_Vector: );
PPCASMF( e_b   IVOR5_Vector );

VEC_ALIGN;
PPCASMF( IVOR6_Vector: );
PPCASMF( e_b   IVOR6_Vector );

VEC_ALIGN;
PPCASMF( IVOR7_Vector: );
PPCASMF( e_b   IVOR7_Vector );

VEC_ALIGN;
PPCASMF( IVOR8_Vector: );
PPCASMF( se_illegal );  /* for semihosting support  */
PPCASMF( se_rfi );

VEC_ALIGN;
PPCASMF( IVOR9_Vector: );
PPCASMF( e_b   IVOR9_Vector );

VEC_ALIGN;
PPCASMF( IVOR10_Vector: );
PPCASMF( e_b   IVOR10_Vector );

VEC_ALIGN;
PPCASMF( IVOR11_Vector: );
PPCASMF( e_b   IVOR11_Vector );

VEC_ALIGN;
PPCASMF( IVOR12_Vector: );
PPCASMF( e_b   IVOR12_Vector );

VEC_ALIGN;
PPCASMF( IVOR13_Vector: );
PPCASMF( e_b   IVOR13_Vector );

VEC_ALIGN;
PPCASMF( IVOR14_Vector: );
PPCASMF( e_b   IVOR14_Vector );

VEC_ALIGN;
PPCASMF( IVOR15_Vector: );
PPCASMF( e_b   IVOR15_Vector );

/** All interrupt handlers should be of this type */
typedef void(*INTCInterruptFn)(void);

VEC_ALIGN;
void INTC_INTCInterruptHandler(void)
{
    INTCInterruptFn *handlerFn = (INTCInterruptFn*)(*(unsigned int*)&INTC_0.IACKR0.R);

    (**handlerFn)();

    INTC_0.EOIR0.R = 0;
}
