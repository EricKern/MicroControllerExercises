/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) %copyright_year%, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

#include "sam.h"

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/* @endcond */

/* %ATMEL_SYSTEM% */
/* Clock Settings (600MHz PLL VDDIO 3.3V and VDDCORE 1.2V) */
/* Clock Settings (300MHz HCLK, 150MHz MCK)=> PRESC = 2, MDIV = 2 */

#define CRYSTAL_FREQUENCY   12000000            //12 MHz

#if     CRYSTAL_FREQUENCY > 20000000
#error  crystal frequency too high!!!
#endif
#if     CRYSTAL_FREQUENCY < 3000000
#error  crystal frequency too low!!!
#endif


//PLL A input frequency: 4..32 MHz; output frequency: 160..500MHz

#define PLL_MULA			0x31		            //PPLA clock frequency = 0x31U+1 = 49+1 = 50 * PLLA input frequency
#define PLL_DIVA			1						//bypass

#if     (PLL_MULA == 0) | (PLL_DIVA == 0) 
#error  error! PLL A disabled!!!
#endif

#if     PLL_MULA > 62
#error  error! PLL MULA value vorbidden!!!
#endif
#if     PLL_DIVA > 255
#error  error! PLL DIVA value vorbidden!!!
#endif


#define SYS_BOARD_OSCOUNT   (CKGR_MOR_MOSCXTST(0x8U))
#define PLLAR_MULA           CKGR_PLLAR_MULA(PLL_MULA)
#define PLLAR_DIVA           CKGR_PLLAR_DIVA(PLL_DIVA)

#define SYS_BOARD_PLLAR     (CKGR_PLLAR_ONE | PLLAR_MULA | CKGR_PLLAR_PLLACOUNT(0x3fU) | PLLAR_DIVA)
#define BOARD_MCK			((PLL_MULA + 1) * CRYSTAL_FREQUENCY)/(PLLAR_DIVA * 4)
#define CPU_CLK				((PLL_MULA + 1) * CRYSTAL_FREQUENCY)/(PLLAR_DIVA * 2)

#if     BOARD_MCK > 150000000
#error  board clk too fast!!!
#endif

//worst case conditions VDDIO > 2.7V
#define FLASH_WAIT_STATE     (BOARD_MCK/21333333)
#if     (FLASH_WAIT_STATE == 0) & BOARD_MCK > 25000000
#error  FLASH wait_state too small!!!
#endif
#if     (FLASH_WAIT_STATE == 1) & BOARD_MCK > 51000000
#error  FLASH wait_state too small!!!
#endif
#if     (FLASH_WAIT_STATE == 2) & BOARD_MCK > 76000000
#error  FLASH wait_state too small!!!
#endif
#if     (FLASH_WAIT_STATE == 3) & BOARD_MCK > 102000000
#error  FLASH wait_state too small!!!
#endif
#if     (FLASH_WAIT_STATE == 4) & BOARD_MCK > 128000000
#error  FLASH wait_state too small!!!
#endif



//#define SYS_BOARD_MCKR      (PMC_MCKR_PRES_CLK_2 | PMC_MCKR_CSS_PLLA_CLK | (1<<8))
#define SYS_BOARD_MCKR      (PMC_MCKR_PRES_CLK_2 | PMC_MCKR_CSS_PLLA_CLK | PMC_MCKR_MDIV(PMC_MCKR_MDIV_PCK_DIV2_Val))

 