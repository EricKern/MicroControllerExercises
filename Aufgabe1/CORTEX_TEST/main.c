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
//#include "sram.h"

uint32_t sdram_heap_size  = 0;

void penrose(void)
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
}


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

void led1_on (void)
{
	ATSAME70_PIO_SetOutput(LED1_PORT,LED1);
}

void led0_off (void)
{
	ATSAME70_PIO_ClearOutput(LED0_PORT,LED0);
}

void led1_off (void)
{
	ATSAME70_PIO_ClearOutput(LED1_PORT,LED1);
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
	penrose();
	printf("MCK: %ld Hz\n",(int32_t) BOARD_MCK);
	calibrate_delayus();
	
	//MM
	// Configure pins as output
	ATSAME70_PIO_CfgOutput(EN_SPI_PORT, EN_SPI);
	
	ATSAME70_PIO_CfgOutput(SPI_CS0_PORT, SPI_CS0);
	ATSAME70_PIO_CfgOutput(SPI_CS1_PORT, SPI_CS1);
	ATSAME70_PIO_CfgOutput(SPI_CS3_PORT, SPI_CS3);
	
	// Set enable of decoder to 1 (disable)
	ATSAME70_PIO_SetOutput(EN_SPI_PORT, EN_SPI);
	
    while (1)
    {
		// LED PC19
		led0_on();
		
		delayms(200);
		
		led0_off();
		
		// LED PC10
		led1_on();
		
		delayms(200);
		
		
		led1_off();
		
		delayms(200);
		
		// LED PB5
		ATSAME70_PIO_SetOutput(LED2_PORT,LED2);
		
		delayms(200);
		
		ATSAME70_PIO_ClearOutput(LED2_PORT,LED2);
		
		// MM
		// Set enable of decoder to 0
		ATSAME70_PIO_ClearOutput(EN_SPI_PORT, EN_SPI);
		
		// LED0
		ATSAME70_PIO_SetOutput(SPI_CS0_PORT, SPI_CS0);		// A PB2  1
		
		ATSAME70_PIO_ClearOutput(SPI_CS1_PORT, SPI_CS1);	// B PA31 0
		
		ATSAME70_PIO_ClearOutput(SPI_CS3_PORT, SPI_CS3);	// C PD27 0
		
		delayms(200);
		
		// LED 2
		ATSAME70_PIO_ClearOutput(SPI_CS0_PORT, SPI_CS0);	// A PB2  0
		
		ATSAME70_PIO_SetOutput(SPI_CS1_PORT, SPI_CS1);		// B PA31 1
		
		ATSAME70_PIO_ClearOutput(SPI_CS3_PORT, SPI_CS3);	// C PD27 0
		
		delayms(200);
		
		// LED 3 (diese LED leuchtet bei mir nicht - vermutlich defektes Bauteil oder falsch herum eingebaut)
		ATSAME70_PIO_SetOutput(SPI_CS0_PORT, SPI_CS0);		// A PB2  1
		
		ATSAME70_PIO_SetOutput(SPI_CS1_PORT, SPI_CS1);		// B PA31 1
		
		ATSAME70_PIO_ClearOutput(SPI_CS3_PORT, SPI_CS3);	// C PD27 0
		
		delayms(200);
		
		// LED 4
		ATSAME70_PIO_ClearOutput(SPI_CS0_PORT, SPI_CS0);	// A PB2  0
		
		ATSAME70_PIO_ClearOutput(SPI_CS1_PORT, SPI_CS1);	// B PA31 0
		
		ATSAME70_PIO_SetOutput(SPI_CS3_PORT, SPI_CS3);		// C PD27 1
		
		delayms(200);
		
		// LED 5
		ATSAME70_PIO_SetOutput(SPI_CS0_PORT, SPI_CS0);		// A PB2  1
		
		ATSAME70_PIO_ClearOutput(SPI_CS1_PORT, SPI_CS1);	// B PA31 0
		
		ATSAME70_PIO_SetOutput(SPI_CS3_PORT, SPI_CS3);		// C PD27 1
		
		delayms(200);
		
		// LED 6
		ATSAME70_PIO_ClearOutput(SPI_CS0_PORT, SPI_CS0);	// A PB2  0
		
		ATSAME70_PIO_SetOutput(SPI_CS1_PORT, SPI_CS1);		// B PA31 1
		
		ATSAME70_PIO_SetOutput(SPI_CS3_PORT, SPI_CS3);		// C PD27 1
		
		delayms(200);
		
		// LED 7
		ATSAME70_PIO_SetOutput(SPI_CS0_PORT, SPI_CS0);		// A PB2  1
		
		ATSAME70_PIO_SetOutput(SPI_CS1_PORT, SPI_CS1);		// B PA31 1
		
		ATSAME70_PIO_SetOutput(SPI_CS3_PORT, SPI_CS3);		// C PD27 1
		
		delayms(200);
		
		//
		
		ATSAME70_PIO_ClearOutput(SPI_CS0_PORT, SPI_CS0);	// A PB2  0
		
		ATSAME70_PIO_ClearOutput(SPI_CS1_PORT, SPI_CS1);	// B PA31 0
		
		ATSAME70_PIO_ClearOutput(SPI_CS3_PORT, SPI_CS3);	// C PD27 0
		
		// Set enable of decoder to 1 (disable)
		ATSAME70_PIO_SetOutput(EN_SPI_PORT, EN_SPI);
		
			
    }
}
