/*
** sdram.h
*/

#ifndef _SDRAM_H_
#define _SDRAM_H_


#define BOARD_SDRAM_SIZE  (2*1024*1024)

#define SDRAM_SIZE  0x02000000
#define SDRAM_BASE  0x70000000


#define SDRAM_TWR	2   //2*10ns
#define SDRAM_TRC	7	//7*10ns
#define SDRAM_TRP	5	//5*10ns
#define SDRAM_TRCD	2	//2*10ns
#define SDRAM_TRAS	5	//5*10ns
#define SDRAM_TXSR	8	//8*10ns

#define SDRAM_TR	7 * MCK/1000000  // Refresh time [us] * MCK [MHz]

/*
** prototypes
*/


#endif

