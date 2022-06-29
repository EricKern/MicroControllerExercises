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

#define ETHERNET_SRAM_CHIP_SELECT 0
#define ET_CSWR_SETUP 1 //setup time for CS, WR: N clock cycles
#define ET_WR_SETUP 1 //setup time for CS, WR: N clock cycles
#define ET_CSWR_PULSE 4 //active time for CS, WR: N clock cycles
#define ET_WR_PULSE 4 //active time for CS, WR: N clock cycles
#define ET_WR_CYCLE 15 //cycle time for CS, WR: N clock cycles
#define ET_CSRD_SETUP 1 //setup time for CS, RD: N clock cycles
#define ET_RD_SETUP 1 //setup time for CS, RD: N clock cycles
#define ET_RD_PULSE 5 //active time for CS, RD: N clock cycles
#define ET_CSRD_PULSE 5 //active time for CS, RD: N clock cycles
#define ET_RD_CYCLE 19 //cycle time for CS, RD: N clock cycles

#define ETHERNET_DATA_ADDRESS 0x60000004 //adr A2 == CMD!
#define ETHERNET_CMD_ADDRESS 0x60000000

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

void dm9000_init();

uint16_t dm9000_read_reg(uint16_t reg_number);

void dm9000_write_reg(uint16_t reg_number, uint16_t data);

int dm9000_reset();

void GetMACaddress (unsigned char *dev_addr);

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
	
	dm9000_init();
	
	dbgu_uart_init();
	dbgu_clear();
	dbgu_puts("\n");
	dbgu_puts("Hello World! (" __DATE__ " " __TIME__ ")\n");
	penrose();
	printf("MCK: %ld Hz\n",(int32_t) BOARD_MCK);
	calibrate_delayus();
	
	
	uint16_t eth_reg_val = 1;
    while (1)
    {
		led0_on();
		led1_on();
		dbgu_puts("Start register write\n");
		dm9000_write_reg(0x10, 42);
		delayms(2000);
		
		led0_off();
		led1_off();
		dbgu_puts("Start register read\n");
		eth_reg_val = dm9000_read_reg(0x10);
		if(eth_reg_val == 42)
			dbgu_puts("Correct Read\n");
		else
			dbgu_puts("False Read\n");
		delayms(1000);
		dm9000_reset();
		delayms(1000);
		eth_reg_val = dm9000_read_reg(0x29);
		printf("Reg 0x29 has %d \n", eth_reg_val);
		if(eth_reg_val == 10)
			dbgu_puts("Reset worked\n");
		else
			dbgu_puts("Reset didn't work\n");
		
    }
}


void dm9000_init(){
	PMC_EnablePeripheral(ID_SMC);
	MPU_Configure();
	SMC->SMC_CS_NUMBER[ETHERNET_SRAM_CHIP_SELECT].SMC_SETUP = SMC_SETUP_NWE_SETUP(ET_WR_SETUP)
	| SMC_SETUP_NCS_WR_SETUP(ET_CSWR_SETUP)
	| SMC_SETUP_NRD_SETUP(ET_RD_SETUP)
	| SMC_SETUP_NCS_RD_SETUP(ET_CSRD_SETUP);
	SMC->SMC_CS_NUMBER[ETHERNET_SRAM_CHIP_SELECT].SMC_PULSE = SMC_PULSE_NWE_PULSE(ET_WR_PULSE)
	| SMC_PULSE_NCS_WR_PULSE(ET_CSWR_PULSE)
	| SMC_PULSE_NRD_PULSE(ET_RD_PULSE)
	| SMC_PULSE_NCS_RD_PULSE(ET_CSRD_PULSE);
	SMC->SMC_CS_NUMBER[ETHERNET_SRAM_CHIP_SELECT].SMC_CYCLE = SMC_CYCLE_NWE_CYCLE(ET_WR_CYCLE)
	| SMC_CYCLE_NRD_CYCLE(ET_RD_CYCLE);
	SMC->SMC_CS_NUMBER[ETHERNET_SRAM_CHIP_SELECT].SMC_MODE = (SMC_MODE_DBW_Msk & SMC_MODE_DBW_16_BIT);
	SMC->SMC_OCMS = 0;
}

uint16_t dm9000_read_reg(uint16_t reg_number)
{
	asm volatile ("DMB");
	*(volatile uint16_t*)ETHERNET_CMD_ADDRESS = reg_number;
	asm volatile ("DMB");
	return *(volatile uint16_t*)ETHERNET_DATA_ADDRESS;
}void dm9000_write_reg(uint16_t reg_number, uint16_t data)
{
	asm volatile ("DMB");
	*(volatile uint16_t*)ETHERNET_CMD_ADDRESS = reg_number;
	asm volatile ("DMB");
	*(volatile uint16_t*)ETHERNET_DATA_ADDRESS = data;
}

int dm9000_reset(){
	dm9000_write_reg(0x00, 1); //Network Control Register
}

void GetMACaddress (unsigned char *dev_addr){
	
}