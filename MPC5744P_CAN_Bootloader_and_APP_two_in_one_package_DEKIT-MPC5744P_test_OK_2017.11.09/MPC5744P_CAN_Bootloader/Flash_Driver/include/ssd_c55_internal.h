/************************************************************************
*            (c) Copyright Freescale Semiconductor, 2011                *
*                        All Rights Reserved                            *
*************************************************************************

*************************************************************************
*                                                                       *
*   Freescale reserves the right to make changes without further notice *
*   to any product herein to improve reliability, function or design.   *
*   Freescale does not assume any liability arising out of the          *
*   application or use of any product, circuit, or software described   *
*   herein; neither does it convey any license under its patent rights  *
*   nor the rights of others.                                           *
*                                                                       *
*   Freescale products are not designed, intended, or authorized for    *
*   use as components in systems intended for surgical implant into     *
*   the body, or other applications intended to support life, or for    *
*   any other application in which the failure of the Freescale product *
*   could create a situation where personal injury or death may occur.  *
*                                                                       *
*   Should Buyer purchase or use Freescale products for any such        *
*   unintended or unauthorized application, Buyer shall indemnify and   *
*   hold Freescale and its officers, employees, subsidiaries,           *
*   affiliates, and distributors harmless against all claims costs,     *
*   damages, and expenses, and reasonable attorney fees arising out     *
*   of, directly or indirectly, any claim of personal injury or death   *
*   associated with such unintended or unauthorized use, even if such   *
*   claim alleges that Freescale was negligent regarding the design     *
*   or manufacture of the part.                                         *
*                                                                       *
*   Freescale and the Freescale logo* are registered trademarks of      *
*   Freescale Semicondutor, Inc.                                        *
*                                                                       *
*************************************************************************

*************************************************************************
*                                                                       *
*               Standard Software Driver for C55                        *
*                                                                       *
* FILE NAME     :  ssd_c55_internal.h                                   *
* DATE          :  December 20, 2011                                    *
* AUTHOR        :  FPT Team                                             *
* E-mail        :  r56611@freescale.com                                 *
*                                                                       *
*************************************************************************/

/******************************* CHANGES *********************************
  0.1.0       12.20.2011         FPT Team       Initial Version
  0.1.1          02.24.2012         Chen He        Updated number of words to be proceessed
  0.1.2       04.09.2012         FPT Team       Update value for FLASH_USER_TEST_WAIT
  1.0.0       09.30.2014         FPT Team      Finalize to RTM v100 (no source
                                                code changed).
*************************************************************************/

#ifndef _SSD_C55_INTERNAL_H_
#define _SSD_C55_INTERNAL_H_

/* Cycles counter used in FlashResume */
/* about 500ns at 400MHz system clock */
#define FLASH_RESUME_WAIT                15

/* Cycles counter used in FlashArrayIntegritySuspend/Resume */
#define FLASH_USER_TEST_WAIT             450

/* Number of words that will be processed in a blank check cycle */
#define NUM_WORDS_BLANK_CHECK_CYCLE      90

/* Number of words that will be processed in a program verify cycle */
#define NUM_WORDS_PROGRAM_VERIFY_CYCLE   80

/* Number of words that will be processed in a check sum cycle */
#define NUM_WORDS_CHECK_SUM_CYCLE        120

#endif  /* _SSD_C55_INTERNAL_H_ */
