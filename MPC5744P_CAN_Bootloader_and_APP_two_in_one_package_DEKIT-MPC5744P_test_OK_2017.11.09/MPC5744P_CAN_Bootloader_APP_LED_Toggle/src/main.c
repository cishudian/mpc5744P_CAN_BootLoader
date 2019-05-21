/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */

#include "MPC574xP_SystemInit.h"

extern void xcptn_xmpl(void);

int main(void)
{
	volatile int counter = 0;
	
	xcptn_xmpl ();              /* Configure and Enable Interrupts */

	Sys_Init();

	GPIO_Aux_Function_Config();

	Periphral_INTC_Init();

	PIT_Channel0_100ms_Init();

	/* Loop forever */
	for(;;) {	   
	   	counter++;
	}
}
