/*
 * CORTEX_TEST.c
 *
 * Created: 27.04.2020
 * Author : Timo Braungardt
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

#define LCD_DATA_ADDRESS		0x62000004 //adr A2 == CMD!
#define LCD_CMD_ADDRESS			0x62000000
#define LCD_SRAM_CHIP_SELECT	2
#define LCD_RD_SETUP			1	//setup time for CS, RD: N clock cycles
#define LCD_RD_PULSE			76	//active time for CS, RD: N clock cycles
#define LCD_RD_CYCLE			152 //cycle time for CS, RD: N clock cycles
#define LCD_WR_SETUP			1	//setup time for CS, WR: N clock cycles
#define LCD_WR_PULSE			8	//active time for CS, WR: N clock cycles
#define LCD_WR_CYCLE			15	//cycle time for CS, WR: N clock cycles

//ili9341 command table
#define ili9341_SOFTWARE_RESET 0x0001
#define ili9341_DISPLAY_ON 0x0029
#define ili9341_DISPLAY_OFF 0x0028
#define ili9341_DISPLAY_INVERSION_ON 0x0020
#define ili9341_DISPLAY_INVERSION_OFF 0x0021
#define ili9341_DISPLAY_COLUMN_ADDRESS_SET 0x002A
#define ili9341_DISPLAY_PAGE_ADDRESS_SET 0x002B
#define ili9341_DISPLAY_COLOR_SET 0x002d
#define ili9341_DISPLAY_MEMORY_WRITE 0x002C
#define ili9341_DISPLAY_MEMORY_CONTROL 0x0036
#define ili9341_DISPLAY_POWER_CONTROL1 0x00C0
#define ili9341_DISPLAY_POWER_CONTROL2 0x00C1
#define ili9341_DISPLAY_VCOM_CONTROL1 0x00C5
#define ili9341_DISPLAY_VCOM_CONTROL2 0x00C7
#define ili9341_DISPLAY_PIXEL_FORMAT_SET 0x003A
#define ili9341_DISPLAY_FRAME_CONTROL_NORMAL 0x00B1
#define ili9341_DISPLAY_FRAME_CONTROL_IDLE 0x00B2
#define ili9341_DISPLAY_FRAME_CONTROL_PARTIAL 0x00B3
#define ili9341_DISPLAY_DISPLAY_FUNCTION_CONTROL 0x00B6
#define ili9341_DISPLAY_GAMMA_SET 0x0026
#define ili9341_DISPLAY_POSITIVE_GAMMA_CORRECTION 0x00E0
#define ili9341_DISPLAY_NEGATIVE_GAMMA_CORRECTION 0x00E1
#define ili9341_DISPLAY_DIGITAL_GAMMA_CONTROL 0x00E2
#define ili9341_DISPLAY_SLEEP_OUT 0x0011
#define ili9341_DISPLAY_INTERFACE_CONTROL 0x00f6
#define ili9341_DISPLAY_BACKLIGHT_CONTROL1 0x00B8
#define ili9341_DISPLAY_BACKLIGHT_CONTROL2 0x00B9
#define ili9341_DISPLAY_BACKLIGHT_CONTROL3 0x00BA
#define ili9341_DISPLAY_BACKLIGHT_CONTROL4 0x00BB
#define ili9341_DISPLAY_BACKLIGHT_CONTROL5 0x00BC
#define ili9341_DISPLAY_BACKLIGHT_CONTROL7 0x00BE
#define ili9341_DISPLAY_BACKLIGHT_CONTROL8 0x00BF
#define ILI9341_DISPLAY_POWER_CONTROL_A 0x00CB
#define ILI9341_DISPLAY_POWER_CONTROL_B 0x00CF
#define ILI9341_DISPLAY_DRIVER_TIMING_CTL_A 0x00E8
#define ILI9341_DISPLAY_DRIVER_TIMING_CTL_B 0x00EA
#define ILI9341_DISPLAY_POWER_ON_SEQUENCE_CONTROL 0x00ED
#define ili9341_MY_1 0x80
#define ili9341_BGR 0x08
#define VP63 0xff
#define VP62 0xfc
#define VP61 0xbf
#define VP59 0xc0
#define VP57 0x80 //0x80;
#define VP50 0xa0
#define VP43 0xa6
#define VP36 0x50
#define VP27 0xd0
#define VP20 0x80
#define VP13 0xa0
#define VP6 0x98
#define VP4 0x30
#define VP2 0x20
#define VP1 0x0c
#define VP0 0x00

uint32_t sdram_heap_size  = 0;


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

void sdram_init(){
	printf("init SDRAM\n");
	// 2. aktivierung des Taktes
	PMC_EnablePeripheral(ID_SDRAMC);
	
	// 3. SRDAM Enable
	MATRIX->CCFG_SMCNFCS = CCFG_SMCNFCS_SDRAMEN;
	
	// 4. Konfigurierung des SDRAMs
	SDRAMC->SDRAMC_CR = SDRAMC_CR_NC_COL9 // 9 column bits
						| SDRAMC_CR_NR_ROW13 // 13 row bits (4K)
						| SDRAMC_CR_CAS_LATENCY3 // CAS Latency 3
						| SDRAMC_CR_NB_BANK4 // 4 banks
						| SDRAMC_CR_DBW // 16 bit
						| SDRAMC_CR_TWR(2)
						| SDRAMC_CR_TRC_TRFC(9) // 63ns min
						| SDRAMC_CR_TRP(3) // Command period (PRE to ACT)
						| SDRAMC_CR_TRCD(3) // Active Command to read/Write Command delay
						| SDRAMC_CR_TRAS(7) // Command period (ACT to PRE)
						| SDRAMC_CR_TXSR(10); // Exit self-refresh to active time
	
	// 5. Konfiguriere Memory Device Register
	//(SDRAMC_MDR): “SDRAM”
	SDRAMC->SDRAMC_MDR = 0;		// set device type to 0 (SDRAM) page 420 datasheet
			
	// 6. Delay
	delayus(200);
	
	// 7. SDRAM Initialisierung
	/* schon in same70q21.h definiert
	#define SDRAM_CS_ADDR						(0x70000000)
	#define SDRAMC_MR_MODE_ALLBANKS_PRECHARGE	(0x2 << 0)
	#define SDRAMC_MR_MODE_AUTO_REFRESH			(0x4 << 0)
	#define SDRAMC_MR_MODE_LOAD_MODEREG			(0x3 << 0)
	#define SDRAMC_MR_MODE_NORMAL				(0x0 << 0)
	*/
	
	volatile uint8_t *pSdram = (uint8_t *) SDRAM_CS_ADDR;
	
	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_ALLBANKS_PRECHARGE;
	*pSdram = 0;		//SDRAM ALLBANKS PRECHARGE OPERATION
	delayus(1);
	
	for(int i = 0; i<8; i++){
		SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_AUTO_REFRESH;
		*pSdram = 0;
		delayus(1);
	}
	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_LOAD_MODEREG;
	*pSdram = 0;
	delayus(1);
	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_NORMAL;
	*pSdram = 0;
	delayus(1);
	
	// 8. Konfiguriere Refresh Register
	SDRAMC->SDRAMC_TR =	781;			// set refresh to 7,81us - 64ms won't fit into the 12bit address (page 411 datasheet)
	
	// 9. Konfiguriere SDRAM Configuration Register
	SDRAMC->SDRAMC_CFR1 |= SDRAMC_CFR1_UNAL;		//Support Unaligned Access
}

void COLOUR_GLCD_write_address_data(uint8_t address, uint16_t data){			// compile error mit inline ???
	asm volatile ("DMB");
	*(volatile uint16_t*)LCD_CMD_ADDRESS = address; //write address
	asm volatile ("DMB");
	*(volatile uint16_t*)LCD_DATA_ADDRESS = data; //write data
}

uint16_t COLOUR_GLCD_Data_Read(){
	asm volatile ("DMB");
	return *(volatile uint16_t*) LCD_DATA_ADDRESS;
}

void COLOUR_GLCD_Instruction_Write(uint16_t instruction){
	asm volatile ("DMB");
	*(volatile uint16_t*)LCD_CMD_ADDRESS = instruction; //write address
}

void COLOUR_GLCD_Data_Write(uint16_t data){
	asm volatile ("DMB");
	*(volatile uint16_t*)LCD_DATA_ADDRESS = data; //write data
}

void GLCD_Initialise(){
	PMC_EnablePeripheral(ID_SMC);		// aktiviere Takt für SPI Interface
	
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
														
	// initialisierung für den ILI9341
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

int16_t concatenateColour(unsigned char red, unsigned char green, unsigned char blue){
	int16_t colour = red;
	colour = colour << 5;
	colour += green;
	colour = colour << 6;
	colour += blue;
	return colour;
}


void GLCD_SetColouredPixel(unsigned short x, unsigned short y, unsigned char red, unsigned char green, unsigned char blue){
	// concatenate the chars
	int16_t colour = red;
	colour = colour << 5;
	colour += green;
	colour = colour << 6;
	colour += blue;
	// select the pixel to write to
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_COLUMN_ADDRESS_SET);
	COLOUR_GLCD_Data_Write(x >> 8);
	COLOUR_GLCD_Data_Write(x & 0x00FF);
	COLOUR_GLCD_Data_Write(x >> 8);
	COLOUR_GLCD_Data_Write(x & 0x00FF);
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_PAGE_ADDRESS_SET);
	COLOUR_GLCD_Data_Write(y >> 8);
	COLOUR_GLCD_Data_Write(y & 0x00FF);
	COLOUR_GLCD_Data_Write(y >> 8);
	COLOUR_GLCD_Data_Write(y & 0x00FF);
	// write the colour
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_MEMORY_WRITE);
	COLOUR_GLCD_Data_Write(colour);
}

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

void COLOUR_GLCD_setWholeDisplay() {COLOUR_GLCD_setXY(0, 0, 239, 319);}


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
	calibrate_delayus();
	SCB_DisableDCache();		// disable data cache - Benötigt?
	sdram_init();
	GLCD_Initialise();
	
	
	
	dbgu_puts ("looking for display type\n");
	#define DISPLAY_SSD1289_ID 0x8989
	#define DISPLAY_ILI9341_ID 0x009341
	COLOUR_GLCD_Instruction_Write(0);
	if (COLOUR_GLCD_Data_Read() == DISPLAY_SSD1289_ID)
	dbgu_puts ("LCD Display SSD1289 found!\n");
	uint32_t display_id = 0;
	COLOUR_GLCD_Instruction_Write(0xd3);
	display_id = COLOUR_GLCD_Data_Read() & 0x00ff;
	display_id = COLOUR_GLCD_Data_Read() & 0x00ff;
	display_id = (display_id <<8) | (COLOUR_GLCD_Data_Read() & 0x00ff);
	display_id = (display_id <<8) | (COLOUR_GLCD_Data_Read() & 0x00ff);
	if (display_id == DISPLAY_ILI9341_ID)
	dbgu_puts ("LCD Display ILI9341 found!\n");
	
	
	COLOUR_GLCD_setWholeDisplay();
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_MEMORY_WRITE);
	for (int i = 0; i < 320*240; i++)
	{
		COLOUR_GLCD_Data_Write(0xffff);
	}
	
	COLOUR_GLCD_setXY(100,200,109,209);
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_MEMORY_WRITE);
	for (int i = 0; i < 100; i++)
	{
		COLOUR_GLCD_Data_Write(concatenateColour(0xff, 0, 0));
	}
	
	COLOUR_GLCD_setXY(100,210,109,219);
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_MEMORY_WRITE);
	for (int i = 0; i < 100; i++)
	{
		COLOUR_GLCD_Data_Write(concatenateColour(0, 0xff, 0));
	}
	
	COLOUR_GLCD_setXY(100,220,109,229);
	COLOUR_GLCD_Instruction_Write(ili9341_DISPLAY_MEMORY_WRITE);
	for (int i = 0; i < 100; i++)
	{
		COLOUR_GLCD_Data_Write(concatenateColour(0, 0, 0xff));
	}
	
	GLCD_SetColouredPixel(100, 100, 0x00, 0x2f, 0x00);
	GLCD_SetColouredPixel(101, 100, 0x2f, 0x00, 0x00);
	GLCD_SetColouredPixel(102, 100, 0x00, 0x00, 0x2f);

	
    while (1)
    {
		delayms(1000);
		
		#define DISPLAY_SSD1289_ID 0x8989
		#define DISPLAY_ILI9341_ID 0x009341
		COLOUR_GLCD_Instruction_Write(0);
		if (COLOUR_GLCD_Data_Read() == DISPLAY_SSD1289_ID)
		dbgu_puts ("LCD Display SSD1289 found!\n");
		uint32_t display_id = 0;
		COLOUR_GLCD_Instruction_Write(0xd3);
		display_id = COLOUR_GLCD_Data_Read() & 0x00ff;
		display_id = COLOUR_GLCD_Data_Read() & 0x00ff;
		display_id = (display_id <<8) | (COLOUR_GLCD_Data_Read() & 0x00ff);
		display_id = (display_id <<8) | (COLOUR_GLCD_Data_Read() & 0x00ff);
		if (display_id == DISPLAY_ILI9341_ID)
		dbgu_puts ("LCD Display ILI9341 found!\n");
    }
}
