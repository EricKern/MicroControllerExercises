/*
 * CORTEX_TEST.c
 *
 * Created: 27.04.2020
 * Author : AWZ
 */


#include "sam.h"
#include "device_startup/system_same70.h"
#include "LIB_ATSAME70.h"
#include "board_cortex7.h"
#include "mpu.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "dbgu.h"
#include "sdram.h"
#include "sram.h"

uint32_t sdram_heap_size  = 0;

#define SDRAM_BASE 0x70000000

/*void penrose(void)
{
	char s[] = "\
	     ______________________\n\
	    /\\                     \\\n\
	   /  \\    _________________\\\n\
	   \\   \\   \\                /\n\
	    \\   \\   \\__________    /\n\
	     \\   \\   \\    /   /   /\n\
	      \\   \\   \\  /   /   /\n\
	       \\   \\   \\/   /   /\n\
	        \\   \\  /   /   /\n\
	         \\   \\/   /   /\n\
	          \\      /   /\n\
	           \\    /   /\n\
	            \\  /   /\n\
	             \\/___/\n";

	dbgu_puts(s);
}*/


void WDT_Disable(Wdt *pWDT)
{
	pWDT->WDT_MR = WDT_MR_WDDIS;
}

char dat[10];

char *my_itoa(int wert, int laenge) {
	int i;

	for(i  =0; i < laenge; i++) {
		dat[laenge-i-1] = (wert % 10) + 48;
		wert = wert / 10;
	}
	dat[laenge]='\0';
	return &dat[0];
}

void led0_on (void)
{
	ATSAME70_PIO_SetOutput(LED0_PORT,LED0);
}

/*void led1_on (void)
{
	ATSAME70_PIO_SetOutput(LED1_PORT,LED1);
}*/

void led0_off (void)
{
	ATSAME70_PIO_ClearOutput(LED0_PORT,LED0);
}

/*void led1_off (void)
{
	ATSAME70_PIO_ClearOutput(LED1_PORT,LED1);
}*/

uint32_t sdram_data_init (void) 
{
	// 1. Config of IO pins (done in board_cortex7_init.c)
	
	
	// 2. Activate the clock
	PMC_EnablePeripheral(ID_SDRAMC);
	
	// 3. SDRAM Enable:
	MATRIX->CCFG_SMCNFCS = CCFG_SMCNFCS_SDRAMEN;
	
	// 4. Configure SD RAM
	SDRAMC->SDRAMC_CFR1 = SDRAMC_CR_NC_COL9
						| SDRAMC_CR_NR_ROW13
						| SDRAMC_CR_CAS_LATENCY3
						| SDRAMC_CR_NB_BANK4
						| SDRAMC_CR_DBW
						| SDRAMC_CR_TWR(2)
						| SDRAMC_CR_TRC_TRFC(9)
						| SDRAMC_CR_TRP(3)
						| SDRAMC_CR_TRCD(3)
						| SDRAMC_CR_TRAS(7)
						| SDRAMC_CR_TXSR(10);
	
	// 5. Configure memory device register
	SDRAMC->SDRAMC_MDR = 0; // page 420
	
	
	// 6. wait 200us
	delayus(200);
	
	// 7. SDRAM Initialisierung
	volatile uint8_t *pSdram = (uint8_t *) SDRAM_CS_ADDR;
	
	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_NOP;
	*pSdram = 0;
	
	delayus(1);
	
	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_ALLBANKS_PRECHARGE;
	*pSdram = 0;
	
	delayus(1);
	
	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_AUTO_REFRESH;
	for (int i = 0; i < 8; i++) 
	{
		*pSdram = 0;	
	}
	
	delayus(1);
	
	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_LOAD_MODEREG;
	*pSdram = 0;

	delayus(1);
	
	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_NORMAL;
	*pSdram = 0;

	
	delayus(1);
	
	// 8. Konfiguriere refresh register
	SDRAMC->SDRAMC_TR = 781; // page 411
	
	// 9.
	SDRAMC->SDRAMC_CFR1 |= SDRAMC_CFR1_UNAL; // Support Unaligned Access
	
	return 0;
	
}

int main(void)
{
    /* Initialize the SAM system */
	SystemClkInit();
	SystemInit();
	soft_reset();				//reset VS1053, LCD, SI4684,  ...
	SCB_InvalidateDCache();		//after reset, you must invalidate each cache before enabling it.
	SCB_InvalidateICache();
	WDT_Disable(WDT);
	MPU_Configure();
	SCB_EnableICache();
	board_init();
	dbgu_uart_init();
	dbgu_clear();
	dbgu_puts("\n");
	dbgu_puts("Hello World! (" __DATE__ " " __TIME__ ")\n");
	//penrose();
	printf("MCK: %ld Hz\n",(int32_t) BOARD_MCK);
	calibrate_delayus();
	
	sdram_data_init();
	SCB_DisableDCache();
	
    while (1)
    {
		// LED PC19
		led0_on();
		
		delayms(200);
		
		led0_off();
		
		delayms(200);
		
		/**************************************************************/
		// Schreibe UNSIGNED INT32
		uint32_t test_var_int = 123;
		
		// Schreiben
		volatile uint16_t *sdram_base = (uint16_t*) SDRAM_BASE;
		
		*sdram_base = test_var_int;
		
		// Warten - damit Lesezugriff nicht wegen der Kapazität der Busleitungen noch funktioniert
		delayms(2000);
		
		// Lesen
		uint32_t read_back_int;
		
		read_back_int = *sdram_base;
		
		printf("[INT] We read back %d and it should be %d \n", read_back_int, test_var_int);
		if (read_back_int == test_var_int) 
		{
			led0_on();
			dbgu_puts("[INT] values same\n");
		}
		else
		{
			led0_off();
			dbgu_puts("[INT] values not same\n");
		}
		/**************************************************************/
		// Schreibe UNSIGNED LONG
		unsigned long test_var_long = 444;
		
		*sdram_base = test_var_long;
		
		// Warten - damit Lesezugriff nicht wegen der Kapazität der Busleitungen noch funktioniert
		delayms(2000);
		
		// Lesen
		unsigned long read_back_long;
		
		read_back_long = *sdram_base;
		
		printf("[LONG] We read back %d and it should be %d \n", read_back_long, test_var_long);
		if (read_back_long == test_var_long)
		{
			led0_on();
			dbgu_puts("[LONG] values same\n");
		}
		else
		{
			led0_off();
			dbgu_puts("[LONG] values not same\n");
		}
		/**************************************************************/
		
		
		delayms(1000);
		//dbgu_puts("value read back is:");
		//dbgu_puts(read_back);
		//dbgu_puts("\n");
		
    }
}
