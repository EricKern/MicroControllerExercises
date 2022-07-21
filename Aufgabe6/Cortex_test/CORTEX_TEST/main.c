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

/*******************************************************************/
#define SELECT_SPI_MP3_CTRL 1 //VS1053 ctrl (MP3-Decoder)
#define SELECT_SPI_MP3_DATA 6 //VS1053 data (MP3-Decoder)
#define SELECT_SPI_WLAN 7 //WLAN
#define SELECT_SPI_MP3_MMC 11 //MMC/SD-card
#define SELECT_SPI_FLASH_RAM 12 //Flash ROM
#define SELECT_SPI_SI4362 13 //SI4362 (ADS-Chip)
#define SELECT_SPI_SI4689 14 //SI4689/SI4684 (Radio Chip)

#define SPI_INTERFACE SPI0

// enable -> cs active: communicating with the VS1053
void spi_mp3_mmc_csenable(void) 
{
	ATSAME70_PIO_ClearOutput(EN_SPI_PORT, EN_SPI);
}

// disable -> cs inactive: communicating with the VS1053
void spi_mp3_mmc_csdisable(void) 
{
	ATSAME70_PIO_SetOutput(EN_SPI_PORT, EN_SPI);
}

void spi_init(void) 
{
	PMC_EnablePeripheral(ID_SPI0); // ID_SPI0
	SPI_INTERFACE->SPI_CR = SPI_CR_SWRST; //spi reset
	
	spi_mp3_mmc_csenable();
	
	SPI_INTERFACE->SPI_IDR = 0xff; //first test with all interrupts disabled
	SPI_INTERFACE->SPI_MR = SPI_MR_MSTR
		| SPI_MR_PS
		| SPI_MR_PCSDEC
		| (SELECT_SPI_MP3_MMC << 16)
		| SPI_MR_MODFDIS; //spi mode configuration
	
	SPI_INTERFACE->SPI_CR = SPI_CR_SPIEN //spi enable
		| SPI_CR_FIFODIS;
}

#define SELECT_SPI_CSR_MP3_CTRL 0
#define SPI_MP3_CTRL_MCK_DIV50 50 // 150Mhz / 50 = 3MHz

#define SELECT_SPI_CSR_MP3_DATA 1
#define SPI_MP3_DATA_MCK_DIV25 25 // 150Mhz / 25 = 6MHz

#define SELECT_SPI_CSR_MMC 2
#define SPI_MMC_MCK_DIV151 151 // 150MHz / 151 = ~ 0,993 MHz


#define SELECT_SPI_CSR_FLASH_RAM 3 // Braucht man das?

#define SPI_CLOCK_POLARITY_ZERO 0
#define SPI_RAISING_EDGE 1
#define SPI_CS_AFTER_TRANSFER_ACTIVE 1
#define SPI_MCK_DIV9 9 //150 MHz / 9 = ~ 16,67 MHz
#define SPI_SHIFT_CLK_FLASH_RAM SPI_MCK_DIV9
#define SPI_DELAY_BEFORE_CLK_FLASH_RAM 1
#define SPI_DELAY_BETWEEN_TRANSFERS_FLASH_RAM 1

#define FLASH_RAM_CLK 20000000 // max 40000000 (=40MHz)
#define SPI_SHIFT_CLK_FLASH_RAM ((((uint32_t) BOARD_MCK)/(uint32_t)FLASH_RAM_CLK))
#if BOARD_MCK > (255 * FLASH_RAM_CLK)
#error FLASH spi shift clk too slow!
#endif

void spi_init_devices(void)
{
	// Kontrollinterface VS1053
	SPI_INTERFACE->SPI_CSR[SELECT_SPI_CSR_MP3_CTRL] =
	((SPI_CLOCK_POLARITY_ZERO << 0) & SPI_CSR_CPOL)
	| ((SPI_RAISING_EDGE << 1) & SPI_CSR_NCPHA)
	| ((SPI_CS_AFTER_TRANSFER_ACTIVE << 3) & SPI_CSR_CSAAT)
	| SPI_CSR_BITS_16_BIT
	| ((SPI_MP3_CTRL_MCK_DIV50 << 8 ))
	| SPI_CSR_DLYBS(SPI_DELAY_BEFORE_CLK_FLASH_RAM)
	| SPI_CSR_DLYBCT(SPI_DELAY_BETWEEN_TRANSFERS_FLASH_RAM);
	
	// Dateninterface VS1053
	SPI_INTERFACE->SPI_CSR[SELECT_SPI_CSR_MP3_DATA] =
	((SPI_CLOCK_POLARITY_ZERO << 0) & SPI_CSR_CPOL)
	| ((SPI_RAISING_EDGE << 1) & SPI_CSR_NCPHA)
	| ((SPI_CS_AFTER_TRANSFER_ACTIVE << 3) & SPI_CSR_CSAAT)
	| SPI_CSR_BITS_8_BIT
	| ((SPI_MP3_DATA_MCK_DIV25 << 8 ))
	| SPI_CSR_DLYBS(SPI_DELAY_BEFORE_CLK_FLASH_RAM)
	| SPI_CSR_DLYBCT(SPI_DELAY_BETWEEN_TRANSFERS_FLASH_RAM);
}

static inline void SPI_PutChar (unsigned short character, unsigned char cs_number )
{
	SPI_INTERFACE->SPI_TDR = (character & 0xffff) | ((cs_number & 0x0f) << 16);
}

static inline int SPI_GetChar (void)
{
	return((SPI_INTERFACE->SPI_RDR) & 0xFFFF);
}

#define VS1053_READ 0x03
#define VS1053_WRITE 0x02
//#define SELECT_SPI_MP3_DATA 6 // spi slave address VS1053 data interface
//#define SELECT_SPI_MP3_CTRL 1 // spi slave address VS1053 control interface

void VS1053_read(unsigned char address, unsigned short count, unsigned short *pData){
	while(!(ATSAME70_PIO_GetInput(MP3_DREQ_PORT) & MP3_DREQ)); // VS1053 ready for communication?
	SPI_INTERFACE->SPI_TDR = (VS1053_READ << 8) + address | (SELECT_SPI_MP3_CTRL << 16);
	for (int i = 0; i < count; ++i){
		while(! (SPI_INTERFACE->SPI_SR & SPI_SR_TXEMPTY));
		SPI_GetChar();		// not sure if necessary
		SPI_PutChar(1, SELECT_SPI_MP3_CTRL);	// send dummy data to enable bus clock so VS1053 can send data back
		while(! (SPI_INTERFACE->SPI_SR & SPI_SR_TXEMPTY));
		pData[i] = SPI_GetChar();
		while(!(ATSAME70_PIO_GetInput(MP3_DREQ_PORT) & MP3_DREQ)); // VS1053 ready for communication?
	}
	
	spi_mp3_mmc_csdisable();
	delay20ns(4);
	spi_mp3_mmc_csenable();
	
}
void VS1053_write(unsigned char address, unsigned short count,unsigned short *pData){	
	SPI_INTERFACE->SPI_TDR = (VS1053_WRITE << 8) + address | (SELECT_SPI_MP3_CTRL << 16);
	for (int i = 0; i < count; ++i){
		while(! (SPI_INTERFACE->SPI_SR & SPI_SR_TXEMPTY));
		SPI_GetChar();
		SPI_PutChar(pData[i], SELECT_SPI_MP3_CTRL);	// send actual data
		while(! (SPI_INTERFACE->SPI_SR & SPI_SR_TXEMPTY));
		SPI_GetChar();
		while(!(ATSAME70_PIO_GetInput(MP3_DREQ_PORT) & MP3_DREQ));
	}
	
	spi_mp3_mmc_csdisable();
	delay20ns(4);
	spi_mp3_mmc_csenable();
}

void VS1053_write_data(unsigned char data){
	while(!(ATSAME70_PIO_GetInput(MP3_DREQ_PORT) & MP3_DREQ)); // VS1053 ready for communication?
	SPI_INTERFACE->SPI_TDR = data | (SELECT_SPI_MP3_DATA << 16);
	while(! (SPI_INTERFACE->SPI_SR & SPI_SR_TXEMPTY));
	
	spi_mp3_mmc_csdisable();
	delay20ns(4);
	spi_mp3_mmc_csenable();
}
/*******************************************************************/

#define VS1053_SOFT_RESET 0x0004
#define VS1002_NATIVE_SPI_MODE 0x0800
#define VS1053_SM_TESTS 0x0020
#define VS1053_DCLK_RAISING_EDGE 0x0000
#define VS1053_CLK_RANGE12_13MHZ 0x0000

#define MP3_XTALI 12288000 // XTAL (quarz) frequency
#define VS1053_SC_FREQ (MP3_XTALI - 8000000)/4000
#define SC_MULT_0 0x0000 // XTALI
#define SC_MULT_7 0xe000 // XTALI * 4.5
#define VS1053_SC_MULT SC_MULT_7
#define SC_ADD0 0x0000 // no modification allowed
#define SC_ADD2 0x1000 // 1.5 *
#define VS1053_SC_ADD SC_ADD2


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
	
	
	spi_init();
	spi_init_devices();
	
	unsigned short buffer = VS1053_SOFT_RESET;
	VS1053_write(0, 1, &buffer);		// init control register of VS1053
	
	dbgu_puts("1\n");
	
	buffer = (VS1002_NATIVE_SPI_MODE + VS1053_SM_TESTS
	+ VS1053_DCLK_RAISING_EDGE + VS1053_CLK_RANGE12_13MHZ);
	
	VS1053_write(0, 1, &buffer);		// init control register of VS1053
	
	buffer =(VS1053_SC_FREQ + VS1053_SC_ADD + VS1053_SC_MULT);
	
	VS1053_write(0x03, 1, &buffer);		// init clock register of VS1053
	
	for(int i = 0; i < 2; ++i){
		VS1053_write_data(0x53);
		VS1053_write_data(0xef);
		VS1053_write_data(0x6e);
		VS1053_write_data(0x7e);	// frequency in this byte
		
		VS1053_write_data(0);
		VS1053_write_data(0);
		VS1053_write_data(0);
		VS1053_write_data(0);
	}
	
	
	buffer = 0x0000;
	VS1053_write(0x0B, 0, &buffer);		// set volume
	
	
	
	
	while (1)
	{
		led0_on();
		delayms(300);
		led1_on();
		delayms(500);
		dbgu_puts("leds on!\n");
		led0_off();
		delayms(800);
		led1_off();
		delayms(1000);
		dbgu_puts("leds off!\n");
	}
}