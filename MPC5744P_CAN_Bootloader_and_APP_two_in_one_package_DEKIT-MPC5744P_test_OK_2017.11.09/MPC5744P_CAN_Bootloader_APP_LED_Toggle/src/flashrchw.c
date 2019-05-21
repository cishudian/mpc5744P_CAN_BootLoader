#if defined(START_FROM_FLASH)
#include "typedefs.h"

#define MPC57xx_ID    0x005A0000  /* RCHW boot ID for MPC57xx devices     */
#define VLE_ENABLE    0x01000000  /* VLE is enabled                       */

#define CPU2_ENABLED  0x00000001
#define CPU0_ENABLED  0x00000002
#define CPUC_ENABLED  0x00000004
#define CPU1_ENABLED  0x00000008

#if defined(MPC574xP) || defined(MPC5777C) || defined(MPC577xK)
extern void _start(void);
#define ENTRY_POINT  _start
#define RCHW_VAL (VLE_ENABLE | MPC57xx_ID)
#else
#if defined(TURN_ON_CPU0) && defined(TURN_ON_CPU1) && defined(TURN_ON_CPU2)
#define TARGET_CORES (CPU0_ENABLED | CPU1_ENABLED | CPU2_ENABLED)
#elif defined(TURN_ON_CPU0) && defined(TURN_ON_CPU1)
#define TARGET_CORES (CPU0_ENABLED | CPU1_ENABLED)
#elif defined(TURN_ON_CPU0) && defined(TURN_ON_CPU2)
#define TARGET_CORES (CPU0_ENABLED | CPU2_ENABLED)
#elif defined(TURN_ON_CPU1) && defined(TURN_ON_CPU2)
#define TARGET_CORES (CPU1_ENABLED | CPU2_ENABLED)
#elif defined(TURN_ON_CPU0)
#define TARGET_CORES (CPU0_ENABLED)
#elif defined(TURN_ON_CPU1)
#define TARGET_CORES (CPU1_ENABLED)
#elif defined(TURN_ON_CPU2)
#define TARGET_CORES (CPU2_ENABLED)
#else 
#error "Neither core is selected"
#endif /* defined(CPU0) && defined(CPU1) && defined(CPU2) */
#define RCHW_VAL (MPC57xx_ID | TARGET_CORES)
#endif

const uint32_t __attribute__ ((section(".rchw"))) RCHW1 = RCHW_VAL;
#if defined(MPC574xP) || defined(MPC5777C) || defined(MPC577xK)
const uint32_t __attribute__ ((section(".cpu0_reset_vector"))) RCHW2 = (uint32_t)ENTRY_POINT;
#else
#if defined(TURN_ON_CPU0)
const uint32_t __attribute__ ((section(".cpu0_reset_vector"))) RCHW2_0 = (uint32_t)0x1000000;
#endif
#if defined(TURN_ON_CPU1)
const uint32_t __attribute__ ((section(".cpu1_reset_vector"))) RCHW2_1 = (uint32_t)$(FLASH_START_2);
#endif
#if defined(TURN_ON_CPU2)
const uint32_t __attribute__ ((section(".cpu2_reset_vector"))) RCHW2_2 = (uint32_t)$(FLASH_START_3);
#endif
#endif
#endif /* defined(START_FROM_FLASH) */






