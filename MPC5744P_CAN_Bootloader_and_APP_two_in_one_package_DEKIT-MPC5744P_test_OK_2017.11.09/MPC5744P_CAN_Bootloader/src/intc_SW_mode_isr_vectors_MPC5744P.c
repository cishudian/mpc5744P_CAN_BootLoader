/*****************************************************************************/
/* FILE NAME: intc_SW_mode_isr_vectors_MPC5744P.c COPYRIGHT(c) Freescale 2015*/
/*                                                      All Rights Reserved  */
/* DESCRIPTION: MPC5744P ISR vectors for INTC in software vector mode        */
/*              Based on MPC5744P ref manual rev 5.1 Table 7-20.             */
/* USAGE:  For desired vector #, replace "dummy" with ISR name and declare   */
/*         your isr name extern like the example below:                      */
/*                       extern void MyPeripheralISR(void);                  */
/*                                                                           */
/*****************************************************************************/	
/* REV      AUTHOR        DATE        DESCRIPTION OF CHANGE                  */
/* ---   -----------    ----------    ---------------------                  */
/* 1.0	  S Mihalik     03 Aug 2015   Initial version                        */
/*****************************************************************************/
#include "typedefs.h"
/*========================================================================*/
/*		PROTOTYPES					                                 	  */
/*========================================================================*/

#include "FlexCAN_api.h"

extern void PIT_Channel0_100ms_ISR(void);

void dummy 						  (void);

/*========================================================================*/
/*	GLOBAL VARIABLES						                              */
/*========================================================================*/

const uint32_t __attribute__ ((section (".intc_vector_table"))) IntcIsrVectorTable[] = {
    
(uint32_t) &dummy, /* Vector #   0 Software settable flag 0 INTC (Software) */
(uint32_t) &dummy, /* Vector #   1 Software settable flag 1 INTC (Software) */
(uint32_t) &dummy, /* Vector #   2 Software settable flag 2 INTC (Software) */
(uint32_t) &dummy, /* Vector #   3 Software settable flag 3 INTC (Software) */
(uint32_t) &dummy, /* Vector #   4 Software settable flag 4 INTC (Software) */
(uint32_t) &dummy, /* Vector #   5 Software settable flag 5 INTC (Software) */
(uint32_t) &dummy, /* Vector #   6 Software settable flag 6 INTC (Software) */
(uint32_t) &dummy, /* Vector #   7 Software settable flag 7 INTC (Software) */
(uint32_t) &dummy, /* Vector #   8 Software settable flag 8 INTC (Software) */
(uint32_t) &dummy, /* Vector #   9 Software settable flag 9 INTC (Software) */
(uint32_t) &dummy, /* Vector #  10 Software settable flag 10 INTC (Software) */
(uint32_t) &dummy, /* Vector #  11 Software settable flag 11 INTC (Software) */
(uint32_t) &dummy, /* Vector #  12 Software settable flag 12 INTC (Software) */
(uint32_t) &dummy, /* Vector #  13 Software settable flag 13 INTC (Software) */
(uint32_t) &dummy, /* Vector #  14 Software settable flag 14 INTC (Software) */
(uint32_t) &dummy, /* Vector #  15 Software settable flag 15 INTC (Software) */
(uint32_t) &dummy, /* Vector #  16 Reserved */
(uint32_t) &dummy, /* Vector #  17 Reserved */
(uint32_t) &dummy, /* Vector #  18 Reserved */
(uint32_t) &dummy, /* Vector #  19 Reserved */
(uint32_t) &dummy, /* Vector #  20 Reserved */
(uint32_t) &dummy, /* Vector #  21 Reserved */
(uint32_t) &dummy, /* Vector #  22 Reserved */
(uint32_t) &dummy, /* Vector #  23 Reserved */
(uint32_t) &dummy, /* Vector #  24 Reserved */
(uint32_t) &dummy, /* Vector #  25 Reserved */
(uint32_t) &dummy, /* Vector #  26 Reserved */
(uint32_t) &dummy, /* Vector #  27 Reserved */
(uint32_t) &dummy, /* Vector #  28 Reserved */
(uint32_t) &dummy, /* Vector #  29 Reserved */
(uint32_t) &dummy, /* Vector #  30 Reserved */
(uint32_t) &dummy, /* Vector #  31 Reserved */
(uint32_t) &dummy, /* Vector #  32 Platform software watchdog timeout Software watchdog timer */
(uint32_t) &dummy, /* Vector #  33 Reserved for Platform watchdog timer1 */
(uint32_t) &dummy, /* Vector #  34 Reserved for Platform watchdog timer2 */
(uint32_t) &dummy, /* Vector #  35 Reserved for Platform watchdog timer3 */
(uint32_t) &dummy, /* Vector #  36 Platform periodic timer 0_0 (STM) STM */
(uint32_t) &dummy, /* Vector #  37 Platform periodic timer 0_1 (STM) STM */
(uint32_t) &dummy, /* Vector #  38 Platform periodic timer 0_2 (STM) STM */
(uint32_t) &dummy, /* Vector #  39 Platform periodic timer 0_3 (STM) STM */
(uint32_t) &dummy, /* Vector #  40 Reserved for Platform periodic timer 1_0 (STM) */
(uint32_t) &dummy, /* Vector #  41 Reserved for Platform periodic timer 1_1 (STM) */
(uint32_t) &dummy, /* Vector #  42 Reserved for Platform periodic timer 1_2 (STM) */
(uint32_t) &dummy, /* Vector #  43 Reserved for Platform periodic timer 1_3 (STM) */
(uint32_t) &dummy, /* Vector #  44 Reserved for Platform periodic timer 2_0 (STM) */
(uint32_t) &dummy, /* Vector #  45 Reserved for Platform periodic timer 2_1 (STM) */
(uint32_t) &dummy, /* Vector #  46 Reserved for Platform periodic timer 2_2 (STM) */
(uint32_t) &dummy, /* Vector #  47 Reserved for Platform periodic timer 2_3 (STM) */
(uint32_t) &dummy, /* Vector #  48 Reserved for Platform periodic timer 3_0 (STM) */
(uint32_t) &dummy, /* Vector #  49 Reserved for Platform periodic timer 3_1 (STM) */
(uint32_t) &dummy, /* Vector #  50 Reserved for Platform periodic timer 3_2 (STM) */
(uint32_t) &dummy, /* Vector #  51 Reserved for Platform periodic timer 3_3(STM) */
(uint32_t) &dummy, /* Vector #  52 eDMA Combined Error eDMA */
(uint32_t) &dummy, /* Vector #  53 eDMA Channel 0 eDMA */
(uint32_t) &dummy, /* Vector #  54 eDMA Channel 1 eDMA */
(uint32_t) &dummy, /* Vector #  55 eDMA Channel 2 eDMA */
(uint32_t) &dummy, /* Vector #  56 eDMA Channel 3 eDMA */
(uint32_t) &dummy, /* Vector #  57 eDMA Channel 4 eDMA */
(uint32_t) &dummy, /* Vector #  58 eDMA Channel 5 eDMA */
(uint32_t) &dummy, /* Vector #  59 eDMA Channel 6 eDMA */
(uint32_t) &dummy, /* Vector #  60 eDMA Channel 7 eDMA */
(uint32_t) &dummy, /* Vector #  61 eDMA Channel 8 eDMA */
(uint32_t) &dummy, /* Vector #  62 eDMA Channel 9 eDMA */
(uint32_t) &dummy, /* Vector #  63 eDMA Channel 10 eDMA */
(uint32_t) &dummy, /* Vector #  64 eDMA Channel 11 eDMA */
(uint32_t) &dummy, /* Vector #  65 eDMA Channel 12 eDMA */
(uint32_t) &dummy, /* Vector #  66 eDMA Channel 13 eDMA */
(uint32_t) &dummy, /* Vector #  67 eDMA Channel 14 eDMA */
(uint32_t) &dummy, /* Vector #  68 eDMA Channel 15 eDMA */
(uint32_t) &dummy, /* Vector #  69 eDMA Channel 16 eDMA */
(uint32_t) &dummy, /* Vector #  70 eDMA Channel 17 eDMA */
(uint32_t) &dummy, /* Vector #  71 eDMA Channel 18 eDMA */
(uint32_t) &dummy, /* Vector #  72 eDMA Channel 19 eDMA */
(uint32_t) &dummy, /* Vector #  73 eDMA Channel 20 eDMA */
(uint32_t) &dummy, /* Vector #  74 eDMA Channel 21 eDMA */
(uint32_t) &dummy, /* Vector #  75 eDMA Channel 22 eDMA */
(uint32_t) &dummy, /* Vector #  76 eDMA Channel 23 eDMA */
(uint32_t) &dummy, /* Vector #  77 eDMA Channel 24 eDMA */
(uint32_t) &dummy, /* Vector #  78 eDMA Channel 25 eDMA */
(uint32_t) &dummy, /* Vector #  79 eDMA Channel 26 eDMA */
(uint32_t) &dummy, /* Vector #  80 eDMA Channel 27 eDMA */
(uint32_t) &dummy, /* Vector #  81 eDMA Channel 28 eDMA */
(uint32_t) &dummy, /* Vector #  82 eDMA Channel 29 eDMA */
(uint32_t) &dummy, /* Vector #  83 eDMA Channel 30 eDMA */
(uint32_t) &dummy, /* Vector #  84 eDMA Channel 31 eDMA */
(uint32_t) &dummy, /* Vector #  85 Reserved for eDMA Channel 32 */
(uint32_t) &dummy, /* Vector #  86 Reserved for eDMA Channel 33 */
(uint32_t) &dummy, /* Vector #  87 Reserved for eDMA Channel 34 */
(uint32_t) &dummy, /* Vector #  88 Reserved for eDMA Channel 35 */
(uint32_t) &dummy, /* Vector #  89 Reserved for eDMA Channel 36 */
(uint32_t) &dummy, /* Vector #  90 Reserved for eDMA Channel 37 */
(uint32_t) &dummy, /* Vector #  91 Reserved for eDMA Channel 38 */
(uint32_t) &dummy, /* Vector #  92 Reserved for eDMA Channel 39 */
(uint32_t) &dummy, /* Vector #  93 Reserved for eDMA Channel 40 */
(uint32_t) &dummy, /* Vector #  94 Reserved for eDMA Channel 41 */
(uint32_t) &dummy, /* Vector #  95 Reserved for eDMA Channel 42 */
(uint32_t) &dummy, /* Vector #  96 Reserved for eDMA Channel 43 */
(uint32_t) &dummy, /* Vector #  97 Reserved for eDMA Channel 44 */
(uint32_t) &dummy, /* Vector #  98 Reserved for eDMA Channel 45 */
(uint32_t) &dummy, /* Vector #  99 Reserved for eDMA Channel 46 */
	
(uint32_t) &dummy, /* Vector # 100 Reserved for eDMA Channel 47 */
(uint32_t) &dummy, /* Vector # 101 Reserved for eDMA Channel 48 */
(uint32_t) &dummy, /* Vector # 102 Reserved for eDMA Channel 49 */
(uint32_t) &dummy, /* Vector # 103 Reserved for eDMA Channel 50 */
(uint32_t) &dummy, /* Vector # 104 Reserved for eDMA Channel 51 */
(uint32_t) &dummy, /* Vector # 105 Reserved for eDMA Channel 52 */
(uint32_t) &dummy, /* Vector # 106 Reserved for eDMA Channel 53 */
(uint32_t) &dummy, /* Vector # 107 Reserved for eDMA Channel 54 */
(uint32_t) &dummy, /* Vector # 108 Reserved for eDMA Channel 55 */
(uint32_t) &dummy, /* Vector # 109 Reserved for eDMA Channel 56 */
(uint32_t) &dummy, /* Vector # 110 Reserved for eDMA Channel 57 */
(uint32_t) &dummy, /* Vector # 111 Reserved for eDMA Channel 58 */
(uint32_t) &dummy, /* Vector # 112 Reserved for eDMA Channel 59 */
(uint32_t) &dummy, /* Vector # 113 Reserved for eDMA Channel 60 */
(uint32_t) &dummy, /* Vector # 114 Reserved for eDMA Channel 61 */
(uint32_t) &dummy, /* Vector # 115 Reserved for eDMA Channel 62 */
(uint32_t) &dummy, /* Vector # 116 Reserved for eDMA Channel 63 */
(uint32_t) &dummy, /* Vector # 117 Reserved for eDMA Channel 64 */
(uint32_t) &dummy, /* Vector # 118 Reserved for eDMA Channel 65 */
(uint32_t) &dummy, /* Vector # 119 Reserved for eDMA Channel 66 */
(uint32_t) &dummy, /* Vector # 120 Reserved for eDMA Channel 67 */
(uint32_t) &dummy, /* Vector # 121 Reserved for eDMA Channel 68 */
(uint32_t) &dummy, /* Vector # 122 Reserved for eDMA Channel 69 */
(uint32_t) &dummy, /* Vector # 123 Reserved for eDMA Channel 70 */
(uint32_t) &dummy, /* Vector # 124 Reserved for eDMA Channel 71 */
(uint32_t) &dummy, /* Vector # 125 Reserved for eDMA Channel 72 */
(uint32_t) &dummy, /* Vector # 126 Reserved for eDMA Channel 73 */
(uint32_t) &dummy, /* Vector # 127 Reserved for eDMA Channel 74 */
(uint32_t) &dummy, /* Vector # 128 Reserved for eDMA Channel 75 */
(uint32_t) &dummy, /* Vector # 129 Reserved for eDMA Channel 76 */
(uint32_t) &dummy, /* Vector # 130 Reserved for eDMA Channel 77 */
(uint32_t) &dummy, /* Vector # 131 Reserved for eDMA Channel 78 */
(uint32_t) &dummy, /* Vector # 132 Reserved for eDMA Channel 79 */
(uint32_t) &dummy, /* Vector # 133 Reserved for eDMA Channel 80 */
(uint32_t) &dummy, /* Vector # 134 Reserved for eDMA Channel 81 */
(uint32_t) &dummy, /* Vector # 135 Reserved for eDMA Channel 82 */
(uint32_t) &dummy, /* Vector # 136 Reserved for eDMA Channel 83 */
(uint32_t) &dummy, /* Vector # 137 Reserved for eDMA Channel 84 */
(uint32_t) &dummy, /* Vector # 138 Reserved for eDMA Channel 85 */
(uint32_t) &dummy, /* Vector # 139 Reserved for eDMA Channel 86 */
(uint32_t) &dummy, /* Vector # 140 Reserved for eDMA Channel 87 */
(uint32_t) &dummy, /* Vector # 141 Reserved for eDMA Channel 88 */
(uint32_t) &dummy, /* Vector # 142 Reserved for eDMA Channel 89 */
(uint32_t) &dummy, /* Vector # 143 Reserved for eDMA Channel 90 */
(uint32_t) &dummy, /* Vector # 144 Reserved for eDMA Channel 91 */
(uint32_t) &dummy, /* Vector # 145 Reserved for eDMA Channel 92 */
(uint32_t) &dummy, /* Vector # 146 Reserved for eDMA Channel 93 */
(uint32_t) &dummy, /* Vector # 147 Reserved for eDMA Channel 94 */
(uint32_t) &dummy, /* Vector # 148 Reserved for eDMA Channel 95 */
(uint32_t) &dummy, /* Vector # 149 Reserved for eDMA Channel 96 */
(uint32_t) &dummy, /* Vector # 150 Reserved for eDMA Channel 97 */
(uint32_t) &dummy, /* Vector # 151 Reserved for eDMA Channel 98 */
(uint32_t) &dummy, /* Vector # 152 Reserved for eDMA Channel 99 */
(uint32_t) &dummy, /* Vector # 153 Reserved for eDMA Channel 100 */
(uint32_t) &dummy, /* Vector # 154 Reserved for eDMA Channel 101 */
(uint32_t) &dummy, /* Vector # 155 Reserved for eDMA Channel 102 */
(uint32_t) &dummy, /* Vector # 156 Reserved for eDMA Channel 103 */
(uint32_t) &dummy, /* Vector # 157 Reserved for eDMA Channel 104 */
(uint32_t) &dummy, /* Vector # 158 Reserved for eDMA Channel 105 */
(uint32_t) &dummy, /* Vector # 159 Reserved for eDMA Channel 106 */
(uint32_t) &dummy, /* Vector # 160 Reserved for eDMA Channel 107 */
(uint32_t) &dummy, /* Vector # 161 Reserved for eDMA Channel 108 */
(uint32_t) &dummy, /* Vector # 162 Reserved for eDMA Channel 109 */
(uint32_t) &dummy, /* Vector # 163 Reserved for eDMA Channel 110 */
(uint32_t) &dummy, /* Vector # 164 Reserved for eDMA Channel 111 */
(uint32_t) &dummy, /* Vector # 165 Reserved for eDMA Channel 112 */
(uint32_t) &dummy, /* Vector # 166 Reserved for eDMA Channel 113 */
(uint32_t) &dummy, /* Vector # 167 Reserved for eDMA Channel 114 */
(uint32_t) &dummy, /* Vector # 168 Reserved for eDMA Channel 115 */
(uint32_t) &dummy, /* Vector # 169 Reserved for eDMA Channel 116 */
(uint32_t) &dummy, /* Vector # 170 Reserved for eDMA Channel 117 */
(uint32_t) &dummy, /* Vector # 171 Reserved for eDMA Channel 118 */
(uint32_t) &dummy, /* Vector # 172 Reserved for eDMA Channel 119 */
(uint32_t) &dummy, /* Vector # 173 Reserved for eDMA Channel 120 */
(uint32_t) &dummy, /* Vector # 174 Reserved for eDMA Channel 121 */
(uint32_t) &dummy, /* Vector # 175 Reserved for eDMA Channel 122 */
(uint32_t) &dummy, /* Vector # 176 Reserved for eDMA Channel 123 */
(uint32_t) &dummy, /* Vector # 177 Reserved for eDMA Channel 124 */
(uint32_t) &dummy, /* Vector # 178 Reserved for eDMA Channel 125 */
(uint32_t) &dummy, /* Vector # 179 Reserved for eDMA Channel 126 */
(uint32_t) &dummy, /* Vector # 180 Reserved for eDMA Channel 127 */
(uint32_t) &dummy, /* Vector # 181 Reserved for MEMU (Platform error reporting) MEMU */
(uint32_t) &dummy, /* Vector # 182 Reserved for MEMU (Platform error reporting) MEMU */
(uint32_t) &dummy, /* Vector # 183 Reserved for MEMU (Platform error reporting) MEMU */
(uint32_t) &dummy, /* Vector # 184 Reserved for MEMU (Platform error reporting) MEMU */
(uint32_t) &dummy, /* Vector # 185 Flash controller Prog/Erase/Suspend IRQ_0 Platform flash controller */
(uint32_t) &dummy, /* Vector # 186 Reserved for flash controller IRQs Platform flash controller */
(uint32_t) &dummy, /* Vector # 187 Reserved for flash controller IRQs Platform flash controller */
(uint32_t) &dummy, /* Vector # 188 Reserved for flash controller IRQs Platform flash controller */
(uint32_t) &dummy, /* Vector # 189 Reserved for AMU_0 */
(uint32_t) &dummy, /* Vector # 190 Reserved for AMU_1 */
(uint32_t) &dummy, /* Vector # 191 Reserved for AMU_2 */
(uint32_t) &dummy, /* Vector # 192 Reserved for AMU_3 */
(uint32_t) &dummy, /* Vector # 193 Reserved for AMU_4 */
(uint32_t) &dummy, /* Vector # 194 Reserved for AMU_5 */
(uint32_t) &dummy, /* Vector # 195 Reserved for future AMU expansion */
(uint32_t) &dummy, /* Vector # 196 Reserved for future AMU expansion */
(uint32_t) &dummy, /* Vector # 197 Reserved for future AMU expansion */
(uint32_t) &dummy, /* Vector # 198 Reserved for future AMU expansion */
(uint32_t) &dummy, /* Vector # 199 Reserved for Semaphore IOP */

(uint32_t) &dummy, /* Vector # 200 Reserved for Semaphore CPU0 */
(uint32_t) &dummy, /* Vector # 201 Reserved for Semaphore CPU1 */
(uint32_t) &dummy, /* Vector # 202 Reserved for Semaphore CPU_SC */
(uint32_t) &dummy, /* Vector # 203 Reserved for future on-platform modules */
(uint32_t) &dummy, /* Vector # 204 Reserved for future on-platform modules */
(uint32_t) &dummy, /* Vector # 205 Reserved for future on-platform modules */
(uint32_t) &dummy, /* Vector # 206 Reserved for future on-platform modules */
(uint32_t) &dummy, /* Vector # 207 Reserved for future on-platform modules */
(uint32_t) &dummy, /* Vector # 208 Reserved for future on-platform modules */
(uint32_t) &dummy, /* Vector # 209 Reserved for future on-platform modules */
(uint32_t) &dummy, /* Vector # 210 Reserved for future on-platform modules */
(uint32_t) &dummy, /* Vector # 211 Reserved for future on-platform modules */
(uint32_t) &dummy, /* Vector # 212 Reserved for future on-platform modules */
(uint32_t) &dummy, /* Vector # 213 Reserved for future on-platform modules */
(uint32_t) &dummy, /* Vector # 214 Reserved for future on-platform modules */
(uint32_t) &dummy, /* Vector # 215 Reserved for future on-platform modules */
(uint32_t) &dummy, /* Vector # 216 Timer IRQ Ethernet 0 ENET_0 */
(uint32_t) &dummy, /* Vector # 217 TX IRQ Ethernet 0 ENET_0 */
(uint32_t) &dummy, /* Vector # 218 RX IRQ Ethernet 0 ENET_0 */
(uint32_t) &dummy, /* Vector # 219 Error/Generic IRQ1 Ethernet 0 ENET_0 */
(uint32_t) &dummy, /* Vector # 220 Reserved for Ethernet_0_2 */
(uint32_t) &dummy, /* Vector # 221 Reserved for Ethernet_1_0 */
(uint32_t) &dummy, /* Vector # 222 Reserved for Ethernet_1_1 */
(uint32_t) &dummy, /* Vector # 223 Reserved for Ethernet_1_2 */
(uint32_t) &dummy, /* Vector # 224 Reserved for Real Time Counter (RTC) */
(uint32_t) &dummy, /* Vector # 225 Reserved for Autonomous Periodic Interrupt (API) */
(uint32_t) &PIT_Channel0_100ms_ISR, /* Vector # 226 Periodic Interrupt Timer (PIT_0) channel 0 PIT_0 */
(uint32_t) &dummy, /* Vector # 227 Periodic Interrupt Timer (PIT_0) channel 1 PIT_0 */
(uint32_t) &dummy, /* Vector # 228 Periodic Interrupt Timer (PIT_0) channel 2 PIT_0 */
(uint32_t) &dummy, /* Vector # 229 Periodic Interrupt Timer (PIT_0) channel 3 PIT_0 */
(uint32_t) &dummy, /* Vector # 230 Reserved for PITx PIT */
(uint32_t) &dummy, /* Vector # 231 Reserved for PITx PIT */
(uint32_t) &dummy, /* Vector # 232 Reserved for PITx PIT */
(uint32_t) &dummy, /* Vector # 233 Reserved for PITx PIT */
(uint32_t) &dummy, /* Vector # 234 Reserved for PITx PIT */
(uint32_t) &dummy, /* Vector # 235 Reserved for PITx PIT */
(uint32_t) &dummy, /* Vector # 236 Reserved for PITx PIT */
(uint32_t) &dummy, /* Vector # 237 Reserved for PITx PIT */
(uint32_t) &dummy, /* Vector # 238 Reserved for PITx PIT */
(uint32_t) &dummy, /* Vector # 239 Reserved for PIT_RTI PIT */
(uint32_t) &dummy, /* Vector # 240 Reserved */
(uint32_t) &dummy, /* Vector # 241 Reserved */
(uint32_t) &dummy, /* Vector # 242 XOSC counter expired External oscillator */
(uint32_t) &dummy, /* Vector # 243 SIUL2 External Interrupt_0 SIUL2 */
(uint32_t) &dummy, /* Vector # 244 SIUL2 External Interrupt_1 SIUL2 */
(uint32_t) &dummy, /* Vector # 245 SIUL2 External Interrupt_2 SIUL2 */
(uint32_t) &dummy, /* Vector # 246 SIUL2 External Interrupt_3 SIUL2 */
(uint32_t) &dummy, /* Vector # 247 Reserved for SIUL2 External Interrupt_4 SIUL2 */
(uint32_t) &dummy, /* Vector # 248 Reserved for SIUL2 External Interrupt_5 SIUL2 */
(uint32_t) &dummy, /* Vector # 249 Reserved for SIUL2 External Interrupt_6 SIUL2 */
(uint32_t) &dummy, /* Vector # 250 Reserved for SIUL2 External Interrupt_7 SIUL2 */
(uint32_t) &dummy, /* Vector # 251 Safe Mode Interrupt MC_ME */
(uint32_t) &dummy, /* Vector # 252 Mode Transition Interrupt MC_ME */
(uint32_t) &dummy, /* Vector # 253 Invalid Mode Interrupt MC_ME */
(uint32_t) &dummy, /* Vector # 254 Invalid Mode Config MC_ME */
(uint32_t) &dummy, /* Vector # 255 Functional and destructive reset alternate event interrupt MC_RGM */
(uint32_t) &dummy, /* Vector # 256 Reserved */
(uint32_t) &dummy, /* Vector # 257 Reserved */
(uint32_t) &dummy, /* Vector # 258 Reserved */
(uint32_t) &dummy, /* Vector # 259 DSPI_SR[TFUF] | DSPI_SR[RFOF] DSPI0 */
(uint32_t) &dummy, /* Vector # 260 DSPI_SR[EOQF] DSPI0 */
(uint32_t) &dummy, /* Vector # 261 DSPI_SR[TFFF] DSPI0 */
(uint32_t) &dummy, /* Vector # 262 DSPI_SR[TCF] DSPI0 */
(uint32_t) &dummy, /* Vector # 263 DSPI_SR[RFDF] DSPI0 */
(uint32_t) &dummy, /* Vector # 264 Reserved for DSPI0_5 DSPI0 */
(uint32_t) &dummy, /* Vector # 265 Reserved for DSPI0_6 DSPI0 */
(uint32_t) &dummy, /* Vector # 266 Reserved for DSPI0_7 DSPI0 */
(uint32_t) &dummy, /* Vector # 267 Reserved for DSPI0_8 DSPI0 */
(uint32_t) &dummy, /* Vector # 268 DSPI_SR[TFUF] | DSPI_SR[RFOF] DSPI1 */
(uint32_t) &dummy, /* Vector # 269 DSPI_SR[EOQF] DSPI1 */
(uint32_t) &dummy, /* Vector # 270 DSPI_SR[TFFF] DSPI1 */
(uint32_t) &dummy, /* Vector # 271 DSPI_SR[TCF] DSPI1 */
(uint32_t) &dummy, /* Vector # 272 DSPI_SR[RFDF] DSPI1 */
(uint32_t) &dummy, /* Vector # 273 Reserved for DSPI1_5 DSPI1 */
(uint32_t) &dummy, /* Vector # 274 Reserved for DSPI1_6 DSPI1 */
(uint32_t) &dummy, /* Vector # 275 Reserved for DSPI1_7 DSPI1 */
(uint32_t) &dummy, /* Vector # 276 Reserved for DSPI1_8 DSPI1 */
(uint32_t) &dummy, /* Vector # 277 DSPI_SR[TFUF] | DSPI_SR[RFOF] DSPI2 */
(uint32_t) &dummy, /* Vector # 278 DSPI_SR[EOQF] DSPI2 */
(uint32_t) &dummy, /* Vector # 279 DSPI_SR[TFFF] DSPI2 */
(uint32_t) &dummy, /* Vector # 280 DSPI_SR[TCF] DSPI2 */
(uint32_t) &dummy, /* Vector # 281 DSPI_SR[RFDF] DSPI2 */
(uint32_t) &dummy, /* Vector # 282 Reserved for DSPI2_5 DSPI2 */
(uint32_t) &dummy, /* Vector # 283 Reserved for DSPI2_6 DSPI2 */
(uint32_t) &dummy, /* Vector # 284 Reserved for DSPI2_7 DSPI2 */
(uint32_t) &dummy, /* Vector # 285 Reserved for DSPI2_8 DSPI2 */
(uint32_t) &dummy, /* Vector # 286 DSPI_SR[TFUF] | DSPI_SR[RFOF] DSPI3 */
(uint32_t) &dummy, /* Vector # 287 DSPI_SR[EOQF] DSPI3 */
(uint32_t) &dummy, /* Vector # 288 DSPI_SR[TFFF] DSPI3 */
(uint32_t) &dummy, /* Vector # 289 DSPI_SR[TCF] DSPI3 */
(uint32_t) &dummy, /* Vector # 290 DSPI_SR[RFDF] DSPI3 */
(uint32_t) &dummy, /* Vector # 291 Reserved for DSPI3_5 DSPI3 */
(uint32_t) &dummy, /* Vector # 292 Reserved for DSPI3_6 DSPI3 */
(uint32_t) &dummy, /* Vector # 293 Reserved for DSPI3_7 DSPI3 */
(uint32_t) &dummy, /* Vector # 294 Reserved for DSPI3_8 DSPI3 */
(uint32_t) &dummy, /* Vector # 295 Reserved for DSPI4_0 DSPI4 */
(uint32_t) &dummy, /* Vector # 296 Reserved for DSPI4_1 DSPI4 */
(uint32_t) &dummy, /* Vector # 297 Reserved for DSPI4_2 DSPI4 */
(uint32_t) &dummy, /* Vector # 298 Reserved for DSPI4_3 DSPI4 */
(uint32_t) &dummy, /* Vector # 299 Reserved for DSPI4_4 DSPI4 */

(uint32_t) &dummy, /* Vector # 300 Reserved for DSPI4_5 DSPI4 */
(uint32_t) &dummy, /* Vector # 301 Reserved for DSPI4_6 DSPI4 */
(uint32_t) &dummy, /* Vector # 302 Reserved for DSPI4_7 DSPI4 */
(uint32_t) &dummy, /* Vector # 303 Reserved for DSPI4_8 DSPI4 */
(uint32_t) &dummy, /* Vector # 304 Reserved for DSPI5_0 DSPI5 */
(uint32_t) &dummy, /* Vector # 305 Reserved for DSPI5_1 DSPI5 */
(uint32_t) &dummy, /* Vector # 306 Reserved for DSPI5_2 DSPI5 */
(uint32_t) &dummy, /* Vector # 307 Reserved for DSPI5_3 DSPI5 */
(uint32_t) &dummy, /* Vector # 308 Reserved for DSPI5_4 DSPI5 */
(uint32_t) &dummy, /* Vector # 309 Reserved for DSPI5_5 DSPI5 */
(uint32_t) &dummy, /* Vector # 310 Reserved for DSPI5_6 DSPI5 */
(uint32_t) &dummy, /* Vector # 311 Reserved for DSPI5_7 DSPI5 */
(uint32_t) &dummy, /* Vector # 312 Reserved for DSPI5_4 DSPI5 */
(uint32_t) &dummy, /* Vector # 313 Reserved for DSPI6_0 DSPI6 */
(uint32_t) &dummy, /* Vector # 314 Reserved for DSPI6_1 DSPI6 */
(uint32_t) &dummy, /* Vector # 315 Reserved for DSPI6_2 DSPI6 */
(uint32_t) &dummy, /* Vector # 316 Reserved for DSPI6_3 DSPI6 */
(uint32_t) &dummy, /* Vector # 317 Reserved for DSPI6_4 DSPI6 */
(uint32_t) &dummy, /* Vector # 318 Reserved for DSPI6_5 DSPI6 */
(uint32_t) &dummy, /* Vector # 319 Reserved for DSPI6_6 DSPI6 */
(uint32_t) &dummy, /* Vector # 320 Reserved for DSPI6_7 DSPI6 */
(uint32_t) &dummy, /* Vector # 321 Reserved for DSPI6_8 DSPI6 */
(uint32_t) &dummy, /* Vector # 322 Reserved for DSPI7_0 DSPI7 */
(uint32_t) &dummy, /* Vector # 323 Reserved for DSPI7_1 DSPI7 */
(uint32_t) &dummy, /* Vector # 324 Reserved for DSPI7_2 DSPI7 */
(uint32_t) &dummy, /* Vector # 325 Reserved for DSPI7_3 DSPI7 */
(uint32_t) &dummy, /* Vector # 326 Reserved for DSPI7_4 DSPI7 */
(uint32_t) &dummy, /* Vector # 327 Reserved for DSPI7_5 DSPI7 */
(uint32_t) &dummy, /* Vector # 328 Reserved for DSPI7_6 DSPI7 */
(uint32_t) &dummy, /* Vector # 329 Reserved for DSPI7_7 DSPI7 */
(uint32_t) &dummy, /* Vector # 330 Reserved for DSPI7_8 DSPI7 */
(uint32_t) &dummy, /* Vector # 331 Reserved for DSPI8_0 DSPI8 */
(uint32_t) &dummy, /* Vector # 332 Reserved for DSPI8_1 DSPI8 */
(uint32_t) &dummy, /* Vector # 333 Reserved for DSPI8_2 DSPI8 */
(uint32_t) &dummy, /* Vector # 334 Reserved for DSPI8_3 DSPI8 */
(uint32_t) &dummy, /* Vector # 335 Reserved for DSPI8_4 DSPI8 */
(uint32_t) &dummy, /* Vector # 336 Reserved for DSPI8_5 DSPI8 */
(uint32_t) &dummy, /* Vector # 337 Reserved for DSPI8_6 DSPI8 */
(uint32_t) &dummy, /* Vector # 338 Reserved for DSPI8_7 DSPI8 */
(uint32_t) &dummy, /* Vector # 339 Reserved for DSPI8_8 DSPI8 */
(uint32_t) &dummy, /* Vector # 340 Reserved for DSPI9_0 DSPI9 */
(uint32_t) &dummy, /* Vector # 341 Reserved for DSPI9_1 DSPI9 */
(uint32_t) &dummy, /* Vector # 342 Reserved for DSPI9_2 DSPI9 */
(uint32_t) &dummy, /* Vector # 343 Reserved for DSPI9_3 DSPI9 */
(uint32_t) &dummy, /* Vector # 344 Reserved for DSPI9_4 DSPI9 */
(uint32_t) &dummy, /* Vector # 345 Reserved for DSPI9_5 DSPI9 */
(uint32_t) &dummy, /* Vector # 346 Reserved for DSPI9_6 DSPI9 */
(uint32_t) &dummy, /* Vector # 347 Reserved for DSPI9_7 DSPI9 */
(uint32_t) &dummy, /* Vector # 348 Reserved for DSPI9_8 DSPI9 */
(uint32_t) &dummy, /* Vector # 349 Reserved for DSPI10_0 DSPI10 */
(uint32_t) &dummy, /* Vector # 350 Reserved for DSPI10_1 DSPI10 */
(uint32_t) &dummy, /* Vector # 351 Reserved for DSPI10_2 DSPI10 */
(uint32_t) &dummy, /* Vector # 352 Reserved for DSPI10_3 DSPI10 */
(uint32_t) &dummy, /* Vector # 353 Reserved for DSPI10_4 DSPI10 */
(uint32_t) &dummy, /* Vector # 354 Reserved for DSPI10_5 DSPI10 */
(uint32_t) &dummy, /* Vector # 355 Reserved for DSPI10_6 DSPI10 */
(uint32_t) &dummy, /* Vector # 356 Reserved for DSPI10_7 DSPI10 */
(uint32_t) &dummy, /* Vector # 357 Reserved for DSPI10_8 DSPI10 */
(uint32_t) &dummy, /* Vector # 358 Reserved for DSPI11_0 DSPI11 */
(uint32_t) &dummy, /* Vector # 359 Reserved for DSPI11_1 DSPI11 */
(uint32_t) &dummy, /* Vector # 360 Reserved for DSPI11_2 DSPI11 */
(uint32_t) &dummy, /* Vector # 361 Reserved for DSPI11_3 DSPI11 */
(uint32_t) &dummy, /* Vector # 362 Reserved for DSPI11_4 DSPI11 */
(uint32_t) &dummy, /* Vector # 363 Reserved for DSPI11_5 DSPI11 */
(uint32_t) &dummy, /* Vector # 364 Reserved for DSPI11_6 DSPI11 */
(uint32_t) &dummy, /* Vector # 365 Reserved for DSPI11_7 DSPI11 */
(uint32_t) &dummy, /* Vector # 366 Reserved for DSPI11_8 DSPI11 */
(uint32_t) &dummy, /* Vector # 367 Reserved for DSPI12_0 DSPI12 */
(uint32_t) &dummy, /* Vector # 368 Reserved for DSPI12_1 DSPI12 */
(uint32_t) &dummy, /* Vector # 369 Reserved for DSPI12_2 DSPI12 */
(uint32_t) &dummy, /* Vector # 370 Reserved for DSPI12_3 DSPI12 */
(uint32_t) &dummy, /* Vector # 371 Reserved for DSPI12_4 DSPI12 */
(uint32_t) &dummy, /* Vector # 372 Reserved for DSPI12_5 DSPI12 */
(uint32_t) &dummy, /* Vector # 373 Reserved for DSPI12_6 DSPI12 */
(uint32_t) &dummy, /* Vector # 374 Reserved for DSPI12_7 DSPI12 */
(uint32_t) &dummy, /* Vector # 375 Reserved for DSPI12_8 DSPI12 */
(uint32_t) &dummy, /* Vector # 376 LINFlex_RXI LINFlex_0 */
(uint32_t) &dummy, /* Vector # 377 LINFlex_TXI LINFlex_0 */
(uint32_t) &dummy, /* Vector # 378 LINFlex_ERR LINFlex_0 */
(uint32_t) &dummy, /* Vector # 379 Reserved for LINFlex/eSCI0_3 LINFlex_0 */
(uint32_t) &dummy, /* Vector # 380 LINFlex_RXI LINFlex_1 */
(uint32_t) &dummy, /* Vector # 381 LINFlex_TXI LINFlex_1 */
(uint32_t) &dummy, /* Vector # 382 LINFlex_ERR LINFlex_1 */
(uint32_t) &dummy, /* Vector # 383 Reserved for LINFlex/eSCI1_3 LINFlex_1 */
(uint32_t) &dummy, /* Vector # 384 Reserved for LINFlex/eSCI2_0 LINFlex_2 */
(uint32_t) &dummy, /* Vector # 385 Reserved for LINFlex/eSCI2_1 LINFlex_2 */
(uint32_t) &dummy, /* Vector # 386 Reserved for LINFlex/eSCI2_2 LINFlex_2 */
(uint32_t) &dummy, /* Vector # 387 Reserved for LINFlex/eSCI2_3 LINFlex_2 */
(uint32_t) &dummy, /* Vector # 388 Reserved for LINFlex/eSCI3_0 LINFlex_3 */
(uint32_t) &dummy, /* Vector # 389 Reserved for LINFlex/eSCI3_1 LINFlex_3 */
(uint32_t) &dummy, /* Vector # 390 Reserved for LINFlex/eSCI3_2 LINFlex_3 */
(uint32_t) &dummy, /* Vector # 391 Reserved for LINFlex/eSCI3_3 LINFlex_3 */
(uint32_t) &dummy, /* Vector # 392 Reserved for LINFlex/eSCI4_0 LINFlex_4 */
(uint32_t) &dummy, /* Vector # 393 Reserved for LINFlex/eSCI4_1 LINFlex_4 */
(uint32_t) &dummy, /* Vector # 394 Reserved for LINFlex/eSCI4_2 LINFlex_4 */
(uint32_t) &dummy, /* Vector # 395 Reserved for LINFlex/eSCI4_3 LINFlex_4 */
(uint32_t) &dummy, /* Vector # 396 Reserved for LINFlex/eSCI5_0 LINFlex_5 */
(uint32_t) &dummy, /* Vector # 397 Reserved for LINFlex/eSCI5_1 LINFlex_5 */
(uint32_t) &dummy, /* Vector # 398 Reserved for LINFlex/eSCI5_2 LINFlex_5 */
(uint32_t) &dummy, /* Vector # 399 Reserved for LINFlex/eSCI5_3 LINFlex_5 */

(uint32_t) &dummy, /* Vector # 400 Reserved for LINFlex/eSCI6_0 LINFlex_6 */
(uint32_t) &dummy, /* Vector # 401 Reserved for LINFlex/eSCI6_1 LINFlex_6 */
(uint32_t) &dummy, /* Vector # 402 Reserved for LINFlex/eSCI6_2 LINFlex_6 */
(uint32_t) &dummy, /* Vector # 403 Reserved for LINFlex/eSCI6_3 LINFlex_6 */
(uint32_t) &dummy, /* Vector # 404 Reserved for LINFlex/eSCI7_0 LINFlex_7 */
(uint32_t) &dummy, /* Vector # 405 Reserved for LINFlex/eSCI7_1 LINFlex_7 */
(uint32_t) &dummy, /* Vector # 406 Reserved for LINFlex/eSCI7_2 LINFlex_7 */
(uint32_t) &dummy, /* Vector # 407 Reserved for LINFlex/eSCI7_3 LINFlex_7 */
(uint32_t) &dummy, /* Vector # 408 Reserved for LINFlex/eSCI8_0 LINFlex_8 */
(uint32_t) &dummy, /* Vector # 409 Reserved for LINFlex/eSCI8_1 LINFlex_8 */
(uint32_t) &dummy, /* Vector # 410 Reserved for LINFlex/eSCI8_2 LINFlex_8 */
(uint32_t) &dummy, /* Vector # 411 Reserved for LINFlex/eSCI8_3 LINFlex_8 */
(uint32_t) &dummy, /* Vector # 412 Reserved for LINFlex/eSCI9_0 LINFlex_9 */
(uint32_t) &dummy, /* Vector # 413 Reserved for LINFlex/eSCI9_1 LINFlex_9 */
(uint32_t) &dummy, /* Vector # 414 Reserved for LINFlex/eSCI9_2 LINFlex_9 */
(uint32_t) &dummy, /* Vector # 415 Reserved for LINFlex/eSCI9_3 LINFlex_9 */
(uint32_t) &dummy, /* Vector # 416 Reserved for LINFlex/eSCI10_0 LINFlex_10 */
(uint32_t) &dummy, /* Vector # 417 Reserved for LINFlex/eSCI10_1 LINFlex_10 */
(uint32_t) &dummy, /* Vector # 418 Reserved for LINFlex/eSCI10_2 LINFlex_10 */
(uint32_t) &dummy, /* Vector # 419 Reserved for LINFlex/eSCI10_3 LINFlex_10 */
(uint32_t) &dummy, /* Vector # 420 Reserved for LINFlex/eSCI11_0 LINFlex_11 */
(uint32_t) &dummy, /* Vector # 421 Reserved for LINFlex/eSCI11_1 LINFlex_11 */
(uint32_t) &dummy, /* Vector # 422 Reserved for LINFlex/eSCI11_2 LINFlex_11 */
(uint32_t) &dummy, /* Vector # 423 Reserved for LINFlex/eSCI11_3 LINFlex_11 */
(uint32_t) &dummy, /* Vector # 424 Reserved for LINFlex/eSCI12_0 LINFlex_12 */
(uint32_t) &dummy, /* Vector # 425 Reserved for LINFlex/eSCI12_1 LINFlex_12 */
(uint32_t) &dummy, /* Vector # 426 Reserved for LINFlex/eSCI12_2 LINFlex_12 */
(uint32_t) &dummy, /* Vector # 427 Reserved for LINFlex/eSCI12_3 LINFlex_12 */
(uint32_t) &dummy, /* Vector # 428 Reserved for LINFlex/eSCI13_0 LINFlex_13 */
(uint32_t) &dummy, /* Vector # 429 Reserved for LINFlex/eSCI13_1 LINFlex_13 */
(uint32_t) &dummy, /* Vector # 430 Reserved for LINFlex/eSCI13_2 LINFlex_13 */
(uint32_t) &dummy, /* Vector # 431 Reserved for LINFlex/eSCI13_3 LINFlex_13 */
(uint32_t) &dummy, /* Vector # 432 Reserved for LINFlex/eSCI14_0 LINFlex_14 */
(uint32_t) &dummy, /* Vector # 433 Reserved for LINFlex/eSCI14_1 LINFlex_14 */
(uint32_t) &dummy, /* Vector # 434 Reserved for LINFlex/eSCI14_2 LINFlex_14 */
(uint32_t) &dummy, /* Vector # 435 Reserved for LINFlex/eSCI14_3 LINFlex_14 */
(uint32_t) &dummy, /* Vector # 436 Reserved for LINFlex/eSCI15_0 LINFlex_15 */
(uint32_t) &dummy, /* Vector # 437 Reserved for LINFlex/eSCI15_1 LINFlex_15 */
(uint32_t) &dummy, /* Vector # 438 Reserved for LINFlex/eSCI15_2 LINFlex_15 */
(uint32_t) &dummy, /* Vector # 439 Reserved for LINFlex/eSCI15_3 LINFlex_15 */
(uint32_t) &dummy, /* Vector # 440 Reserved for IIC_0_0 */
(uint32_t) &dummy, /* Vector # 441 Reserved for IIC_0_1 */
(uint32_t) &dummy, /* Vector # 442 Reserved for IIC_1_0 */
(uint32_t) &dummy, /* Vector # 443 Reserved for IIC_1_1 */
(uint32_t) &dummy, /* Vector # 444 Reserved for IIC_2_0 */
(uint32_t) &dummy, /* Vector # 445 Reserved for IIC_2_1 */
(uint32_t) &dummy, /* Vector # 446 Reserved for IIC_3_0 */
(uint32_t) &dummy, /* Vector # 447 Reserved for IIC_3_1 */
(uint32_t) &dummy, /* Vector # 448 Reserved for future use */
(uint32_t) &dummy, /* Vector # 449 Reserved for future use */
(uint32_t) &dummy, /* Vector # 450 Reserved for future use */
(uint32_t) &dummy, /* Vector # 451 Reserved for future use */
(uint32_t) &dummy, /* Vector # 452 Reserved for future use */
(uint32_t) &dummy, /* Vector # 453 LRNEIF | DRNEIF FlexRay_0 */
(uint32_t) &dummy, /* Vector # 454 LRCEIF | DRCEIF FlexRay_0 */
(uint32_t) &dummy, /* Vector # 455 FNEAIF FlexRay_0 */
(uint32_t) &dummy, /* Vector # 456 FNEBIF FlexRay_0 */
(uint32_t) &dummy, /* Vector # 457 WUPIF FlexRay_0 */
(uint32_t) &dummy, /* Vector # 458 PRIF FlexRay_0 */
(uint32_t) &dummy, /* Vector # 459 CHIF FlexRay_0 */
(uint32_t) &dummy, /* Vector # 460 TBIF FlexRay_0 */
(uint32_t) &dummy, /* Vector # 461 RBIF FlexRay_0 */
(uint32_t) &dummy, /* Vector # 462 MIF FlexRay_0 */
(uint32_t) &dummy, /* Vector # 463 Reserved for FlexRay_0_10 FlexRay_0 */
(uint32_t) &dummy, /* Vector # 464 Reserved for FlexRay_0_11 FlexRay_0 */
(uint32_t) &dummy, /* Vector # 465 Reserved for FlexRay_1_0 FlexRay_1 */
(uint32_t) &dummy, /* Vector # 466 Reserved for FlexRay_1_1 FlexRay_1 */
(uint32_t) &dummy, /* Vector # 467 Reserved for FlexRay_1_2 FlexRay_1 */
(uint32_t) &dummy, /* Vector # 468 Reserved for FlexRay_1_3 FlexRay_1 */
(uint32_t) &dummy, /* Vector # 469 Reserved for FlexRay_1_4 FlexRay_1 */
(uint32_t) &dummy, /* Vector # 470 Reserved for FlexRay_1_5 FlexRay_1 */
(uint32_t) &dummy, /* Vector # 471 Reserved for FlexRay_1_6 FlexRay_1 */
(uint32_t) &dummy, /* Vector # 472 Reserved for FlexRay_1_7 FlexRay_1 */
(uint32_t) &dummy, /* Vector # 473 Reserved for FlexRay_1_8 FlexRay_1 */
(uint32_t) &dummy, /* Vector # 474 Reserved for FlexRay_1_9 FlexRay_1 */
(uint32_t) &dummy, /* Vector # 475 Reserved for FlexRay_1_10 FlexRay_1 */
(uint32_t) &dummy, /* Vector # 476 Reserved for FlexRay_1_11 FlexRay_1 */
(uint32_t) &dummy, /* Vector # 477 Power Monitor Unit PMU */
(uint32_t) &dummy, /* Vector # 478 Power management Unit (temp sensor) PMU */
(uint32_t) &dummy, /* Vector # 479 Reserved for Clock Monitor Unit CMU */
(uint32_t) &dummy, /* Vector # 480 Reserved for PLL_0 PLL_0 */
(uint32_t) &dummy, /* Vector # 481 Reserved for PLL_0 PLL_0 */
(uint32_t) &dummy, /* Vector # 482 Reserved for PLL_1 PLL_1 */
(uint32_t) &dummy, /* Vector # 483 Reserved for PLL_1 PLL_1 */
(uint32_t) &dummy, /* Vector # 484 Reserved for ipi_int_ext_pd1_done */
(uint32_t) &dummy, /* Vector # 485 Reserved for ipi_int_ext_pd2_done */
(uint32_t) &dummy, /* Vector # 486 Reserved for ipi_int_pll1_clk_sw */
(uint32_t) &dummy, /* Vector # 487 Reserved for ipi_int_pll2_clk_sw */
(uint32_t) &dummy, /* Vector # 488 Alarm Interrupt (ALRM) FCCU */
(uint32_t) &dummy, /* Vector # 489 Configuration Time-out (CFG_TO) FCCU */
(uint32_t) &dummy, /* Vector # 490 Reserved for FCCU FCCU */
(uint32_t) &dummy, /* Vector # 491 Reserved for FCCU FCCU */
(uint32_t) &dummy, /* Vector # 492 Reserved for FCCU_4 FCCU */
(uint32_t) &dummy, /* Vector # 493 Reserved for FCCU_5 FCCU */
(uint32_t) &dummy, /* Vector # 494 Reserved for FCCU_6 FCCU */
(uint32_t) &dummy, /* Vector # 495 Reserved for FCCU_7 FCCU */
(uint32_t) &dummy, /* Vector # 496 ADC_EOC ADC_0 */
(uint32_t) &dummy, /* Vector # 497 ADC_ER ADC_0 */
(uint32_t) &dummy, /* Vector # 498 ADC_WD ADC_0 */
(uint32_t) &dummy, /* Vector # 499 Reserved for ADC ADC_0 */
	
(uint32_t) &dummy, /* Vector # 500 ADC_EOC ADC_1 */
(uint32_t) &dummy, /* Vector # 501 ADC_ER ADC_1 */
(uint32_t) &dummy, /* Vector # 502 ADC_WD ADC_1 */
(uint32_t) &dummy, /* Vector # 503 Reserved for ADC ADC_1 */
(uint32_t) &dummy, /* Vector # 504 ADC_EOC ADC_2 */
(uint32_t) &dummy, /* Vector # 505 ADC_ER ADC_2 */
(uint32_t) &dummy, /* Vector # 506 ADC_WD ADC_2 */
(uint32_t) &dummy, /* Vector # 507 Reserved for ADC ADC_2 */
(uint32_t) &dummy, /* Vector # 508 ADC_EOC ADC_3 */
(uint32_t) &dummy, /* Vector # 509 ADC_ER ADC_3 */
(uint32_t) &dummy, /* Vector # 510 ADC_WD ADC_3 */
(uint32_t) &dummy, /* Vector # 511 Reserved for ADC ADC_3 */
(uint32_t) &dummy, /* Vector # 512 Reserved for ADC ADC_4 */
(uint32_t) &dummy, /* Vector # 513 Reserved for ADC ADC_4 */
(uint32_t) &dummy, /* Vector # 514 Reserved for ADC ADC_4 */
(uint32_t) &dummy, /* Vector # 515 Reserved for ADC ADC_4 */
(uint32_t) &dummy, /* Vector # 516 Reserved for ADC ADC_5 */
(uint32_t) &dummy, /* Vector # 517 Reserved for ADC ADC_5 */
(uint32_t) &dummy, /* Vector # 518 Reserved for ADC ADC_5 */
(uint32_t) &dummy, /* Vector # 519 Reserved for ADC ADC_5 */
(uint32_t) &FlexCAN0_ESR_ISR, /* Vector # 520 FLEXCAN_ESR[ERR_INT] FlexCAN_0 */
(uint32_t) &FlexCAN0_ESR_BTR_ISR, /* Vector # 521 FLEXCAN_ESR_BOFF | FLEXCAN_Transmit_Warning | FLEXCAN_Receive_Warning FlexCAN_0 */
(uint32_t) &FlexCAN0_BUF03_ISR, /* Vector # 522 FLEXCAN_BUF_00_03 FlexCAN_0 */
(uint32_t) &FlexCAN0_BUF47_ISR, /* Vector # 523 FLEXCAN_BUF_04_07 FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 524 FLEXCAN_BUF_08_11 FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 525 FLEXCAN_BUF_12_15 FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 526 FLEXCAN_BUF_16_31 FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 527 FLEXCAN_BUF_32_39 FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 528 FLEXCAN_BUF_40_47 FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 529 FLEXCAN_BUF_48_55 FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 530 FLEXCAN_BUF_56_63 FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 531 Reserved FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 532 Reserved FlexCAN_0 */
(uint32_t) &FlexCAN1_ESR_ISR, /* Vector # 533 FLEXCAN_ESR[ERR_INT] FlexCAN_1 */
(uint32_t) &FlexCAN1_ESR_BTR_ISR, /* Vector # 534 FLEXCAN_ESR_BOFF | FLEXCAN_Transmit_Warning | FLEXCAN_Receive_Warning FlexCAN_1 */
(uint32_t) &FlexCAN1_BUF03_ISR, /* Vector # 535 FLEXCAN_BUF_00_03 FlexCAN_1 */
(uint32_t) &FlexCAN1_BUF47_ISR, /* Vector # 536 FLEXCAN_BUF_04_07 FlexCAN_1 */
(uint32_t) &FlexCAN1_BUF811_ISR, /* Vector # 537 FLEXCAN_BUF_08_11 FlexCAN_1 */
(uint32_t) &FlexCAN1_BUF1215_ISR, /* Vector # 538 FLEXCAN_BUF_12_15 FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 539 FLEXCAN_BUF_16_31 FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 540 FLEXCAN_BUF_32_39 FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 541 FLEXCAN_BUF_40_47 FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 542 FLEXCAN_BUF_48_55 FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 543 FLEXCAN_BUF_56_63 FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 544 Reserved FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 545 Reserved FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 546 FLEXCAN_ESR[ERR_INT] FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 547 FLEXCAN_ESR_BOFF | FLEXCAN_Transmit_Warning | FLEXCAN_Receive_Warning FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 548 FLEXCAN_BUF_00_03 FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 549 FLEXCAN_BUF_04_07 FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 550 FLEXCAN_BUF_08_11 FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 551 FLEXCAN_BUF_12_15 FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 552 FLEXCAN_BUF_16_31 FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 553 FLEXCAN_BUF_32_39 FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 554 FLEXCAN_BUF_40_47 FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 555 FLEXCAN_BUF_48_55 FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 556 FLEXCAN_BUF_56_63 FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 557 Reserved FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 558 Reserved FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 559 Reserved FlexCAN_3 */
(uint32_t) &dummy, /* Vector # 560 Reserved FlexCAN_3 */
(uint32_t) &dummy, /* Vector # 561 Reserved FlexCAN_3 */
(uint32_t) &dummy, /* Vector # 562 Reserved FlexCAN_3 */
(uint32_t) &dummy, /* Vector # 563 Reserved FlexCAN_3 */
(uint32_t) &dummy, /* Vector # 564 Reserved FlexCAN_3 */
(uint32_t) &dummy, /* Vector # 565 Reserved FlexCAN_3 */
(uint32_t) &dummy, /* Vector # 566 Reserved FlexCAN_3 */
(uint32_t) &dummy, /* Vector # 567 Reserved FlexCAN_3 */
(uint32_t) &dummy, /* Vector # 568 Reserved FlexCAN_3 */
(uint32_t) &dummy, /* Vector # 569 Reserved FlexCAN_3 */
(uint32_t) &dummy, /* Vector # 570 Valid Fast Message Received on Channel 0 SENT_0 */
(uint32_t) &dummy, /* Vector # 571 Valid Slow Message Received on Channel 0 SENT_0 */
(uint32_t) &dummy, /* Vector # 572 Receive Error Interrupt Channel 0 SENT_0 */
(uint32_t) &dummy, /* Vector # 573 Valid Fast Message Received on Channel 1 SENT_0 */
(uint32_t) &dummy, /* Vector # 574 Valid Slow Message Received on Channel 1 SENT_0 */
(uint32_t) &dummy, /* Vector # 575 Receive Error Interrupt Channel 1 SENT_0 */
(uint32_t) &dummy, /* Vector # 576 Reserved SENT_0 */
(uint32_t) &dummy, /* Vector # 577 Reserved SENT_0 */
(uint32_t) &dummy, /* Vector # 578 Reserved SENT_0 */
(uint32_t) &dummy, /* Vector # 579 Reserved SENT_0 */
(uint32_t) &dummy, /* Vector # 580 Reserved SENT_0 */
(uint32_t) &dummy, /* Vector # 581 Reserved SENT_0 */
(uint32_t) &dummy, /* Vector # 582 Valid Fast Message Received on Channel 0 SENT_1 */
(uint32_t) &dummy, /* Vector # 583 Valid Slow Message Received on Channel 0 SENT_1 */
(uint32_t) &dummy, /* Vector # 584 Receive Error Interrupt Channel 0 SENT_1 */
(uint32_t) &dummy, /* Vector # 585 Valid Fast Message Received on Channel 1 SENT_1 */
(uint32_t) &dummy, /* Vector # 586 Valid Slow Message Received on Channel 1 SENT_1 */
(uint32_t) &dummy, /* Vector # 587 Receive Error Interrupt Channel 1 SENT_1 */
(uint32_t) &dummy, /* Vector # 588 Reserved SENT_1 */
(uint32_t) &dummy, /* Vector # 589 Reserved SENT_1 */
(uint32_t) &dummy, /* Vector # 590 Reserved SENT_1 */
(uint32_t) &dummy, /* Vector # 591 Reserved SENT_1 */
(uint32_t) &dummy, /* Vector # 592 Reserved SENT_1 */
(uint32_t) &dummy, /* Vector # 593 Reserved SENT_1 */
(uint32_t) &dummy, /* Vector # 594 Read interrupt channel 1 SIPI */
(uint32_t) &dummy, /* Vector # 595 Read interrupt channel 2 SIPI */
(uint32_t) &dummy, /* Vector # 596 Read interrupt channel 3 SIPI */
(uint32_t) &dummy, /* Vector # 597 Read interrupt channel 4 SIPI */
(uint32_t) &dummy, /* Vector # 598 Reserved SIPI */
(uint32_t) &dummy, /* Vector # 599 Reserved SIPI */

(uint32_t) &dummy, /* Vector # 600 Reserved SIPI */
(uint32_t) &dummy, /* Vector # 601 Reserved SIPI */
(uint32_t) &dummy, /* Vector # 602 Error 1 SIPI */
(uint32_t) &dummy, /* Vector # 603 Error 2 SIPI */
(uint32_t) &dummy, /* Vector # 604 Trigger command SIPI */
(uint32_t) &dummy, /* Vector # 605 Tx interrupt LFAST0 */
(uint32_t) &dummy, /* Vector # 606 Tx exception LFAST0 */
(uint32_t) &dummy, /* Vector # 607 Rx interrupt LFAST0 */
(uint32_t) &dummy, /* Vector # 608 Rx exception LFAST0 */
(uint32_t) &dummy, /* Vector # 609 Rx ICLC LFAST0 */
(uint32_t) &dummy, /* Vector # 610 Reserved LFAST0 */
(uint32_t) &dummy, /* Vector # 611 TC0IR eTimer_0 */
(uint32_t) &dummy, /* Vector # 612 TC1IR eTimer_0 */
(uint32_t) &dummy, /* Vector # 613 TC2IR eTimer_0 */
(uint32_t) &dummy, /* Vector # 614 TC3IR eTimer_0 */
(uint32_t) &dummy, /* Vector # 615 TC4IR eTimer_0 */
(uint32_t) &dummy, /* Vector # 616 TC5IR eTimer_0 */
(uint32_t) &dummy, /* Vector # 617 Not used Reserved eTimer_0 */
(uint32_t) &dummy, /* Vector # 618 Not used Reserved eTimer_0 */
(uint32_t) &dummy, /* Vector # 619 WTIF eTimer_0 */
(uint32_t) &dummy, /* Vector # 620 Not used Reserved eTimer_0 */
(uint32_t) &dummy, /* Vector # 621 RCF eTimer_0 */
(uint32_t) &dummy, /* Vector # 622 TC0IR eTimer_1 */
(uint32_t) &dummy, /* Vector # 623 TC1IR eTimer_1 */
(uint32_t) &dummy, /* Vector # 624 TC2IR eTimer_1 */
(uint32_t) &dummy, /* Vector # 625 TC3IR eTimer_1 */
(uint32_t) &dummy, /* Vector # 626 TC4IR eTimer_1 */
(uint32_t) &dummy, /* Vector # 627 TC5IR eTimer_1 */
(uint32_t) &dummy, /* Vector # 628 Not used Reserved eTimer_1 */
(uint32_t) &dummy, /* Vector # 629 Not used Reserved eTimer_1 */
(uint32_t) &dummy, /* Vector # 630 Not used Reserved eTimer_1 */
(uint32_t) &dummy, /* Vector # 631 Not used Reserved eTimer_1 */
(uint32_t) &dummy, /* Vector # 632 RCF eTimer_1 */
(uint32_t) &dummy, /* Vector # 633 TC0IR eTimer_2 */
(uint32_t) &dummy, /* Vector # 634 TC1IR eTimer_2 */
(uint32_t) &dummy, /* Vector # 635 TC2IR eTimer_2 */
(uint32_t) &dummy, /* Vector # 636 TC3IR eTimer_2 */
(uint32_t) &dummy, /* Vector # 637 TC4IR eTimer_2 */
(uint32_t) &dummy, /* Vector # 638 TC5IR eTimer_2 */
(uint32_t) &dummy, /* Vector # 639 Not used Reserved eTimer_2 */
(uint32_t) &dummy, /* Vector # 640 Not used Reserved eTimer_2 */
(uint32_t) &dummy, /* Vector # 641 Not used Reserved eTimer_2 */
(uint32_t) &dummy, /* Vector # 642 Not used Reserved eTimer_2 */
(uint32_t) &dummy, /* Vector # 643 RCF eTimer_2 */
(uint32_t) &dummy, /* Vector # 644 Not used eTimer_3 */
(uint32_t) &dummy, /* Vector # 645 Not used eTimer_3 */
(uint32_t) &dummy, /* Vector # 646 Not used eTimer_3 */
(uint32_t) &dummy, /* Vector # 647 Not used eTimer_3 */
(uint32_t) &dummy, /* Vector # 648 Not used eTimer_3 */
(uint32_t) &dummy, /* Vector # 649 Not used eTimer_3 */
(uint32_t) &dummy, /* Vector # 650 Not used Reserved eTimer_3 */
(uint32_t) &dummy, /* Vector # 651 Not used Reserved eTimer_3 */
(uint32_t) &dummy, /* Vector # 652 Not used Reserved eTimer_3 */
(uint32_t) &dummy, /* Vector # 653 Not used Reserved eTimer_3 */
(uint32_t) &dummy, /* Vector # 654 Not used eTimer_3 */
(uint32_t) &dummy, /* Vector # 655 RF0 FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 656 COF0 FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 657 CAF0 FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 658 RF1 FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 659 COF1 FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 660 CAF1 FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 661 RF2 FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 662 COF2 FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 663 CAF2 FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 664 RF3 FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 665 COF3 FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 666 CAF3 FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 667 FFLAG FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 668 REF FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 669 Reserved FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 670 RF0 FlexPWM_1 */
(uint32_t) &dummy, /* Vector # 671 COF0 FlexPWM_1 */
(uint32_t) &dummy, /* Vector # 672 CAF0 FlexPWM_1 */
(uint32_t) &dummy, /* Vector # 673 RF1 FlexPWM_1 */
(uint32_t) &dummy, /* Vector # 674 COF1 FlexPWM_1 */
(uint32_t) &dummy, /* Vector # 675 CAF1 FlexPWM_1 */
(uint32_t) &dummy, /* Vector # 676 RF2 FlexPWM_1 */
(uint32_t) &dummy, /* Vector # 677 COF2 FlexPWM_1 */
(uint32_t) &dummy, /* Vector # 678 CAF2 FlexPWM_1 */
(uint32_t) &dummy, /* Vector # 679 RF3 FlexPWM_1 */
(uint32_t) &dummy, /* Vector # 680 COF3 FlexPWM_1 */
(uint32_t) &dummy, /* Vector # 681 CAF3 FlexPWM_1 */
(uint32_t) &dummy, /* Vector # 682 FFLAG FlexPWM_1 */
(uint32_t) &dummy, /* Vector # 683 REF FlexPWM_1 */
(uint32_t) &dummy, /* Vector # 684 Reserved FlexPWM_1 */
(uint32_t) &dummy, /* Vector # 685 Reserved FlexPWM_2 */
(uint32_t) &dummy, /* Vector # 686 Reserved FlexPWM_2 */
(uint32_t) &dummy, /* Vector # 687 Reserved FlexPWM_2 */
(uint32_t) &dummy, /* Vector # 688 Reserved FlexPWM_2 */
(uint32_t) &dummy, /* Vector # 689 Reserved FlexPWM_2 */
(uint32_t) &dummy, /* Vector # 690 Reserved FlexPWM_2 */
(uint32_t) &dummy, /* Vector # 691 Reserved FlexPWM_2 */
(uint32_t) &dummy, /* Vector # 692 Reserved FlexPWM_2 */
(uint32_t) &dummy, /* Vector # 693 Reserved FlexPWM_2 */
(uint32_t) &dummy, /* Vector # 694 Reserved FlexPWM_2 */
(uint32_t) &dummy, /* Vector # 695 Reserved FlexPWM_2 */
(uint32_t) &dummy, /* Vector # 696 Reserved FlexPWM_2 */
(uint32_t) &dummy, /* Vector # 697 Reserved FlexPWM_2 */
(uint32_t) &dummy, /* Vector # 698 Reserved FlexPWM_2 */
(uint32_t) &dummy, /* Vector # 699 Reserved FlexPWM_2 */

(uint32_t) &dummy, /* Vector # 700 MRS_I CTU_0 */
(uint32_t) &dummy, /* Vector # 701 T0_I CTU_0 */
(uint32_t) &dummy, /* Vector # 702 T1_I CTU_0 */
(uint32_t) &dummy, /* Vector # 703 T2_I CTU_0 */
(uint32_t) &dummy, /* Vector # 704 T3_I CTU_0 */
(uint32_t) &dummy, /* Vector # 705 T4_I CTU_0 */
(uint32_t) &dummy, /* Vector # 706 T5_I CTU_0 */
(uint32_t) &dummy, /* Vector # 707 T6_I CTU_0 */
(uint32_t) &dummy, /* Vector # 708 T7_I CTU_0 */
(uint32_t) &dummy, /* Vector # 709 FIFO0_I CTU_0 */
(uint32_t) &dummy, /* Vector # 710 FIFO1_I CTU_0 */
(uint32_t) &dummy, /* Vector # 711 FIFO2_I CTU_0 */
(uint32_t) &dummy, /* Vector # 712 FIFO3_I CTU_0 */
(uint32_t) &dummy, /* Vector # 713 ADC_I CTU_0 */
(uint32_t) &dummy, /* Vector # 714 ERR_I CTU_0 */
(uint32_t) &dummy, /* Vector # 715 Reserved CTU_0 */
(uint32_t) &dummy, /* Vector # 716 MRS_I CTU_1 */
(uint32_t) &dummy, /* Vector # 717 T0_I CTU_1 */
(uint32_t) &dummy, /* Vector # 718 T1_I CTU_1 */
(uint32_t) &dummy, /* Vector # 719 T2_I CTU_1 */
(uint32_t) &dummy, /* Vector # 720 T3_I CTU_1 */
(uint32_t) &dummy, /* Vector # 721 T4_I CTU_1 */
(uint32_t) &dummy, /* Vector # 722 T5_I CTU_1 */
(uint32_t) &dummy, /* Vector # 723 T6_I CTU_1 */
(uint32_t) &dummy, /* Vector # 724 T7_I CTU_1 */
(uint32_t) &dummy, /* Vector # 725 FIFO0_I CTU_1 */
(uint32_t) &dummy, /* Vector # 726 FIFO1_I CTU_1 */
(uint32_t) &dummy, /* Vector # 727 FIFO2_I CTU_1 */
(uint32_t) &dummy, /* Vector # 728 FIFO3_I CTU_1 */
(uint32_t) &dummy, /* Vector # 729 ADC_I CTU_1 */
(uint32_t) &dummy, /* Vector # 730 ERR_I CTU_1 */
(uint32_t) &dummy, /* Vector # 731 Reserved CTU_1 */
(uint32_t) &dummy, /* Vector # 732 sgen_error SGEN */
(uint32_t) &dummy, /* Vector # 733 Reserved SGEN */

};


void dummy (void) {   /* Dummy ISR vector to trap undefined ISRs */
    while (1) {};  /* Wait forever or for watchdog timeout */
}

