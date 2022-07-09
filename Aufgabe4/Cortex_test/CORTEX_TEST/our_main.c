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

//MM
#include "lcd.h"

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

//---
void COLOUR_GLCD_write_address_data(uint8_t address, uint16_t data){			// compile error mit inline ???
	asm volatile ("DMB");
	*(volatile uint16_t*)LCD_CMD_ADDRESS = address; //write address
	asm volatile ("DMB");
	*(volatile uint16_t*)LCD_DATA_ADDRESS = data; //write data
}

void COLOUR_GLCD_Instruction_Write(uint16_t address) 
{
	asm volatile ("DMB");
	*(volatile uint16_t*)LCD_CMD_ADDRESS = address; //write address
	asm volatile ("DMB");
}

void COLOUR_GLCD_Data_Write (uint16_t data)
{
	asm volatile ("DMB");
	*(volatile uint16_t*)LCD_DATA_ADDRESS = data; //write data
	asm volatile ("DMB");
}

// must return *something* but what?
uint16_t COLOUR_GLCD_Data_Read() 
{
	asm volatile ("DMB");
	return (volatile uint16_t*)LCD_DATA_ADDRESS;
}

//void
void COLOUR_GLCD_setWholeDisplay() {COLOUR_GLCD_setXY(0, 0, 239, 319);}

void COLOUR_GLCD_setXY(unsigned short x1_axis, unsigned short y1_axis, unsigned short x2_axis, unsigned short y2_axis){
	printf("x: %i-%i y: %i-%i\n", x1_axis, x2_axis, y1_axis, y2_axis);
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_COLUMN_ADDRESS_SET);
	COLOUR_GLCD_Data_Write(x1_axis >> 8);
	COLOUR_GLCD_Data_Write(x1_axis & 0x00FF);
	COLOUR_GLCD_Data_Write(x2_axis >> 8);
	COLOUR_GLCD_Data_Write(x2_axis & 0x00FF);
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_PAGE_ADDRESS_SET);
	COLOUR_GLCD_Data_Write(y1_axis >> 8);
	COLOUR_GLCD_Data_Write(y1_axis & 0x00FF);
	COLOUR_GLCD_Data_Write(y2_axis >> 8);
	COLOUR_GLCD_Data_Write(y2_axis & 0x00FF);
}

void GLCD_Initialize(void) 
{
	PMC_EnablePeripheral(ID_SMC);		// aktiviere Takt f?r SPI Interface
	
	SMC->SMC_CS_NUMBER[LCD_SRAM_CHIP_SELECT].SMC_SETUP = SMC_SETUP_NWE_SETUP(LCD_WR_SETUP)
	| SMC_SETUP_NCS_WR_SETUP(LCD_WR_SETUP)
	| SMC_SETUP_NRD_SETUP(LCD_RD_SETUP)
	| SMC_SETUP_NCS_RD_SETUP(LCD_RD_SETUP);
	SMC->SMC_CS_NUMBER[LCD_SRAM_CHIP_SELECT].SMC_PULSE = SMC_PULSE_NWE_PULSE(LCD_WR_PULSE)
	| SMC_PULSE_NCS_WR_PULSE(LCD_WR_PULSE)
	| SMC_PULSE_NRD_PULSE(LCD_RD_PULSE)
	| SMC_PULSE_NCS_RD_PULSE(LCD_RD_PULSE);
	SMC->SMC_CS_NUMBER[LCD_SRAM_CHIP_SELECT].SMC_CYCLE = SMC_CYCLE_NWE_CYCLE(LCD_WR_CYCLE)
	| SMC_CYCLE_NRD_CYCLE(LCD_RD_CYCLE);
	SMC->SMC_CS_NUMBER[LCD_SRAM_CHIP_SELECT].SMC_MODE = (SMC_MODE_DBW_Msk & SMC_MODE_DBW_16_BIT)
	| (SMC_MODE_READ_MODE_Msk & SMC_MODE_READ_MODE )
	| (SMC_MODE_WRITE_MODE_Msk & SMC_MODE_WRITE_MODE);
	
	// initialisierung f?r den ILI9341
	COLOUR_GLCD_Instruction_Write(ILI9341_DISPLAY_POWER_CONTROL_B); //(0xcf);
	COLOUR_GLCD_Data_Write(0x00);
	COLOUR_GLCD_Data_Write(0xc1);
	COLOUR_GLCD_Data_Write(0x30);
	COLOUR_GLCD_Instruction_Write(ILI9341_DISPLAY_POWER_ON_SEQUENCE_CONTROL); //(0xed);
	COLOUR_GLCD_Data_Write(0x64);
	COLOUR_GLCD_Data_Write(0x03);
	COLOUR_GLCD_Data_Write(0x12);
	COLOUR_GLCD_Data_Write(0x81);
	COLOUR_GLCD_Instruction_Write(ILI9341_DISPLAY_POWER_CONTROL_A); //(0xcb);
	COLOUR_GLCD_Data_Write(0x39);
	COLOUR_GLCD_Data_Write(0x2c);
	COLOUR_GLCD_Data_Write(0x00);
	COLOUR_GLCD_Data_Write(0x34);
	COLOUR_GLCD_Data_Write(0x02);
	COLOUR_GLCD_Instruction_Write(ILI9341_DISPLAY_DRIVER_TIMING_CTL_B); //(0xea);//unbekannt!
	COLOUR_GLCD_Data_Write(0x00);
	COLOUR_GLCD_Data_Write(0x00);
	COLOUR_GLCD_Instruction_Write(ILI9341_DISPLAY_DRIVER_TIMING_CTL_A); //(0xe8);//unbekannt!
	COLOUR_GLCD_Data_Write(0x85);//(0x85);
	COLOUR_GLCD_Data_Write(0x10);//00
	COLOUR_GLCD_Data_Write(0x78);//78
	COLOUR_GLCD_Instruction_Write(0xF2); // 3Gamma Function Disable
	COLOUR_GLCD_Data_Write(0x00);
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_POWER_CONTROL1); //Power control
	COLOUR_GLCD_Data_Write(0x23); //VRH[5:0]
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_POWER_CONTROL2); //Power control
	COLOUR_GLCD_Data_Write(0x10); //SAP[2:0];BT[3:0]
	COLOUR_GLCD_Instruction_Write(0xC2); //unbekannt!
	COLOUR_GLCD_Data_Write(0x11);
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_VCOM_CONTROL1); //VCM control
	COLOUR_GLCD_Data_Write(0xc3); //(0x3d); //Contrast 3e
	COLOUR_GLCD_Data_Write(0x20); //(0x30); //28
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_VCOM_CONTROL2); //VCM control2
	COLOUR_GLCD_Data_Write(0xbb); //--
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_PIXEL_FORMAT_SET);
	COLOUR_GLCD_Data_Write(0x55);
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_MEMORY_CONTROL); // Memory Access Control
	COLOUR_GLCD_Data_Write(0x08);
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_FRAME_CONTROL_NORMAL);
	COLOUR_GLCD_Data_Write(0x00);
	COLOUR_GLCD_Data_Write(0x11);
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_DISPLAY_FUNCTION_CONTROL); // Display Function Control
	COLOUR_GLCD_Data_Write(0x08);
	COLOUR_GLCD_Data_Write(0x82);
	COLOUR_GLCD_Data_Write(0x27);
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_GAMMA_SET); //Gamma curve selected
	COLOUR_GLCD_Data_Write(0x01);
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_POSITIVE_GAMMA_CORRECTION); //Set Gamma
	COLOUR_GLCD_Data_Write(VP63 >> 4);
	COLOUR_GLCD_Data_Write(VP62 >> 2);
	COLOUR_GLCD_Data_Write(VP61 >> 2);
	COLOUR_GLCD_Data_Write(VP59 >> 4);
	COLOUR_GLCD_Data_Write(VP57 >> 3);
	COLOUR_GLCD_Data_Write(VP50 >> 4);
	COLOUR_GLCD_Data_Write(VP43 >> 1);
	COLOUR_GLCD_Data_Write (VP27 + (VP36 >> 4));
	COLOUR_GLCD_Data_Write(VP20 >> 1);
	COLOUR_GLCD_Data_Write(VP13 >> 4);
	COLOUR_GLCD_Data_Write(VP6 >> 3);
	COLOUR_GLCD_Data_Write(VP4 >> 4);
	COLOUR_GLCD_Data_Write(VP2 >> 2);
	COLOUR_GLCD_Data_Write(VP1 >> 2);
	COLOUR_GLCD_Data_Write(VP0 >> 4);
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_NEGATIVE_GAMMA_CORRECTION);
	COLOUR_GLCD_Data_Write(0x00);
	COLOUR_GLCD_Data_Write(0x00);
	COLOUR_GLCD_Data_Write(0x10);
	COLOUR_GLCD_Data_Write(0x03);
	COLOUR_GLCD_Data_Write(0x0f);
	COLOUR_GLCD_Data_Write(0x05);
	COLOUR_GLCD_Data_Write(0x2c);
	COLOUR_GLCD_Data_Write(0xa2);
	COLOUR_GLCD_Data_Write(0x3f);
	COLOUR_GLCD_Data_Write(0x05);
	COLOUR_GLCD_Data_Write(0x0e);
	COLOUR_GLCD_Data_Write(0x0c);
	COLOUR_GLCD_Data_Write(0x37);
	COLOUR_GLCD_Data_Write(0x3c);
	COLOUR_GLCD_Data_Write(0x0F);
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_SLEEP_OUT); //Exit Sleep
	delayms(120);
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_ON); //Display on
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_COLOR_SET);
	uint8_t i;
	for (i=0;i<32;i++) COLOUR_GLCD_Data_Write(i*2);//red
	for (i=0;i<64;i++) COLOUR_GLCD_Data_Write(i); //green
	for (i=0;i<32;i++) COLOUR_GLCD_Data_Write(i*2);//blue
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_COLUMN_ADDRESS_SET );
	COLOUR_GLCD_Data_Write(0);
	COLOUR_GLCD_Data_Write(0x00);
	COLOUR_GLCD_Data_Write(0);
	COLOUR_GLCD_Data_Write(0xff);
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_PAGE_ADDRESS_SET);
	COLOUR_GLCD_Data_Write(0);
	COLOUR_GLCD_Data_Write(0x00);
	COLOUR_GLCD_Data_Write(0);
	COLOUR_GLCD_Data_Write(0xff);
	COLOUR_GLCD_write_address_data(ili9341_DISPLAY_MEMORY_CONTROL,ili9341_MY_1 + ili9341_BGR);
	//BGR = blue-green-red
	
	
}

void GLCD_SetColouredPixel(unsigned short x, unsigned short y, unsigned char red, unsigned char green, unsigned char blue) 
{
	
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
	
	GLCD_Initialize();
	
    while (1)
    {
		printf("HI from printf\n");
		
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
		

		
		COLOUR_GLCD_Instruction_Write(0);
		
		//dbgu_puts("hi");
		printf("HI from printf --- %d \n", COLOUR_GLCD_Data_Read());
		
		if (COLOUR_GLCD_Data_Read() == DISPLAY_SSD1289_ID)
		dbgu_puts ("LCD Display SSD1289 found!\n");
		uint32_t display_id = 0;
		COLOUR_GLCD_Instruction_Write(0xd3);
		delayus(100);
		display_id = COLOUR_GLCD_Data_Read() & 0x00ff;
		display_id = COLOUR_GLCD_Data_Read() & 0x00ff;
		display_id = (display_id <<8) | (COLOUR_GLCD_Data_Read() & 0x00ff);
		display_id = (display_id <<8) | (COLOUR_GLCD_Data_Read() & 0x00ff);
		
		printf("HI from printf --- %04x \n", display_id);
		
		if (display_id == DISPLAY_ILI9341_ID)
		dbgu_puts ("LCD Display ILI9341 found!\n");

		COLOUR_GLCD_setWholeDisplay();
    }
}
