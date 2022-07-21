#include "sam.h"
#include <stdint.h>
#include "LIB_ATSAME70.h"
#include "board_cortex7.h"
//#include "usb_msd/pmc.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

void ATSAME70_PIO_CfgPeriph(
Pio *pPio, // \arg pointer to a PIO controller
unsigned long periphEnable, // arg PERIPH A to enable -> PIO_ABCDSR1 PIO_ABCDSR2 = 00
unsigned long periph_address)
{
	pPio->PIO_PDR = periphEnable; //perihp enable + pio disable
	switch (periph_address)
	{
		case PERIPHERAL_A: pPio->PIO_ABCDSR[0] = pPio->PIO_ABCDSR[0] & (~periphEnable); pPio->PIO_ABCDSR[1] = pPio->PIO_ABCDSR[1] & (~periphEnable); break;
		case PERIPHERAL_B: pPio->PIO_ABCDSR[0] = pPio->PIO_ABCDSR[0] | ( periphEnable); pPio->PIO_ABCDSR[1] = pPio->PIO_ABCDSR[1] & (~periphEnable); break;
		case PERIPHERAL_C: pPio->PIO_ABCDSR[0] = pPio->PIO_ABCDSR[0] & (~periphEnable); pPio->PIO_ABCDSR[1] = pPio->PIO_ABCDSR[1] | ( periphEnable); break;
		case PERIPHERAL_D: pPio->PIO_ABCDSR[0] = pPio->PIO_ABCDSR[0] | ( periphEnable); pPio->PIO_ABCDSR[1] = pPio->PIO_ABCDSR[1] | ( periphEnable); break;
	}
	
}

void ATSAME70_PIO_Cfg(
Pio *pPio, // \arg pointer to a PIO controller
unsigned long pioEnable) // arg PERIPH A to enable -> PIO_ABCDSR1 PIO_ABCDSR2 = 00
{
	pPio->PIO_PER = pioEnable; //perihp enable + pio disable

}

void board_init(void)
{
	//enable pio clk 
	PMC_EnablePeripheral(ID_PIOA);
	PMC_EnablePeripheral(ID_PIOB);
	PMC_EnablePeripheral(ID_PIOC);
	PMC_EnablePeripheral(ID_PIOD);
	PMC_EnablePeripheral(ID_PIOE);
	
	//SDRAM Address
	ATSAME70_PIO_CfgPeriph(SDRAM_ADR0_PORT,SDRAM_ADR0,SDRAM_ADR0_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_ADR1_PORT,SDRAM_ADR1,SDRAM_ADR1_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_ADR2_PORT,SDRAM_ADR2,SDRAM_ADR2_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_ADR3_PORT,SDRAM_ADR3,SDRAM_ADR3_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_ADR4_PORT,SDRAM_ADR4,SDRAM_ADR4_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_ADR5_PORT,SDRAM_ADR5,SDRAM_ADR5_PERIPHERAL);
    ATSAME70_PIO_CfgPeriph(SDRAM_ADR6_PORT,SDRAM_ADR6,SDRAM_ADR6_PERIPHERAL);
    ATSAME70_PIO_CfgPeriph(SDRAM_ADR7_PORT,SDRAM_ADR7,SDRAM_ADR7_PERIPHERAL);
    ATSAME70_PIO_CfgPeriph(SDRAM_ADR8_PORT,SDRAM_ADR8,SDRAM_ADR8_PERIPHERAL);
    ATSAME70_PIO_CfgPeriph(SDRAM_ADR9_PORT,SDRAM_ADR9,SDRAM_ADR9_PERIPHERAL);
    ATSAME70_PIO_CfgPeriph(SDRAM_ADR10_PORT,SDRAM_ADR10,SDRAM_ADR10_PERIPHERAL);
    ATSAME70_PIO_CfgPeriph(SDRAM_ADR11_PORT,SDRAM_ADR11,SDRAM_ADR11_PERIPHERAL);
    ATSAME70_PIO_CfgPeriph(SDRAM_ADR12_PORT,SDRAM_ADR12,SDRAM_ADR12_PERIPHERAL);
    ATSAME70_PIO_CfgPeriph(SDRAM_BA0_PORT,SDRAM_BA0,SDRAM_BA0_PERIPHERAL);
    ATSAME70_PIO_CfgPeriph(SDRAM_BA1_PORT,SDRAM_BA1,SDRAM_BA1_PERIPHERAL);
	
	//SDRAM Data
	ATSAME70_PIO_CfgPeriph(SDRAM_DATA0_PORT,SDRAM_DATA0,SDRAM_DATA0_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_DATA1_PORT,SDRAM_DATA1,SDRAM_DATA1_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_DATA2_PORT,SDRAM_DATA2,SDRAM_DATA2_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_DATA3_PORT,SDRAM_DATA3,SDRAM_DATA3_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_DATA4_PORT,SDRAM_DATA4,SDRAM_DATA4_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_DATA5_PORT,SDRAM_DATA5,SDRAM_DATA5_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_DATA6_PORT,SDRAM_DATA6,SDRAM_DATA6_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_DATA7_PORT,SDRAM_DATA7,SDRAM_DATA7_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_DATA8_PORT,SDRAM_DATA8,SDRAM_DATA8_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_DATA9_PORT,SDRAM_DATA9,SDRAM_DATA9_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_DATA10_PORT,SDRAM_DATA10,SDRAM_DATA10_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_DATA11_PORT,SDRAM_DATA11,SDRAM_DATA11_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_DATA12_PORT,SDRAM_DATA12,SDRAM_DATA12_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_DATA13_PORT,SDRAM_DATA13,SDRAM_DATA13_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_DATA14_PORT,SDRAM_DATA14,SDRAM_DATA14_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_DATA15_PORT,SDRAM_DATA15,SDRAM_DATA15_PERIPHERAL);
	
	//SDRAM Control
	ATSAME70_PIO_CfgPeriph(SDRAM_CKE_PORT,SDRAM_CKE,SDRAM_CKE_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_CLK_PORT,SDRAM_CLK,SDRAM_CLK_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_CAS_PORT,SDRAM_CAS,SDRAM_CAS_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_RAS_PORT,SDRAM_RAS,SDRAM_RAS_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SDRAM_WE_PORT,SDRAM_WE,SDRAM_WE_PERIPHERAL);
    ATSAME70_PIO_CfgPeriph(SDRAM_DQML_PORT,SDRAM_DQML,SDRAM_DQML_PERIPHERAL);
    ATSAME70_PIO_CfgPeriph(SDRAM_DQMH_PORT,SDRAM_DQMH,SDRAM_DQMH_PERIPHERAL);

	//Ethernet SRAM Interface DM9000
	ATSAME70_PIO_CfgPeriph(ETH_CS_PORT,ETH_CS,ETH_CS_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(ETH_IOR_PORT,ETH_IOR,ETH_IOR_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(ETH_IOW_PORT,ETH_IOW,ETH_IOW_PERIPHERAL);

	ATSAME70_PIO_CfgOutput(ETH_PWRST_PORT,ETH_PWRST);  //obsolete!
	ATSAME70_PIO_SetOutput(ETH_PWRST_PORT,ETH_PWRST);
	ATSAME70_PIO_CfgInput (ETH_INT_PORT,ETH_INT);      //ethernet interrupt
	ATSAME70_PIO_Pulldown_Disable(ETH_INT_PORT,ETH_INT); 
	ATSAME70_PIO_Pullup_Disable(ETH_INT_PORT,ETH_INT); 
	//LCD SRAM Interface
	ATSAME70_PIO_CfgPeriph(LCD_CS_PORT,LCD_CS,LCD_CS_PERIPHERAL);
	
	//LCD Touch Serial Interface I/O Pins
	ATSAME70_PIO_CfgOutput(LCD_D_CLK_PORT, LCD_D_CLK);
	ATSAME70_PIO_CfgOutput(LCD_D_CS_PORT, LCD_D_CS);
	ATSAME70_PIO_CfgOutput(LCD_D_IN_PORT, LCD_D_IN);
	ATSAME70_PIO_CfgInput (LCD_D_OUT_PORT, LCD_D_OUT);
	ATSAME70_PIO_Pulldown_Disable(LCD_D_OUT_PORT, LCD_D_OUT);
	ATSAME70_PIO_Pullup_Disable(LCD_D_OUT_PORT, LCD_D_OUT);
	ATSAME70_PIO_CfgInput (LCD_D_BUSY_PORT, LCD_D_BUSY);
	ATSAME70_PIO_Pulldown_Disable(LCD_D_BUSY_PORT, LCD_D_BUSY);
	ATSAME70_PIO_Pullup_Disable(LCD_D_BUSY_PORT, LCD_D_BUSY);
	ATSAME70_PIO_CfgInput (LCD_DIRQ_PORT, LCD_DIRQ);
	ATSAME70_PIO_Pulldown_Disable(LCD_DIRQ_PORT, LCD_DIRQ);
	ATSAME70_PIO_Pullup_Disable(LCD_DIRQ_PORT, LCD_DIRQ);
	//LCD Intensity Control Interface TC Output: TIOB
	ATSAME70_PIO_CfgPeriph(LCD_INTENSITY_PORT,LCD_INTENSITY,LCD_INTENSITY_PERIPHERAL);


	//Rotation + Button Encoder Interface I/O Pins
	
	ATSAME70_PIO_CfgOutput(BUTTON_MULTIPLEXER_SEL0_PORT,BUTTON_MULTIPLEXER_SEL0);
	ATSAME70_PIO_CfgOutput(BUTTON_MULTIPLEXER_SEL1_PORT,BUTTON_MULTIPLEXER_SEL1);
	ATSAME70_PIO_CfgOutput(BUTTON_MULTIPLEXER_SEL2_PORT,BUTTON_MULTIPLEXER_SEL2);
	ATSAME70_PIO_CfgInput (BUTTON_MULTIPLEXER_TASTER_PORT,BUTTON_MULTIPLEXER_TASTER);
	ATSAME70_PIO_Pullup_Enable(BUTTON_MULTIPLEXER_TASTER_PORT,BUTTON_MULTIPLEXER_TASTER);
	ATSAME70_PIO_Edge_Select(BUTTON_MULTIPLEXER_TASTER_PORT,BUTTON_MULTIPLEXER_TASTER);
	ATSAME70_PIO_Falling_Edge_Low_level_Select(BUTTON_MULTIPLEXER_TASTER_PORT,BUTTON_MULTIPLEXER_TASTER);
	
	ATSAME70_PIO_Input_Filter_Enable(BUTTON_MULTIPLEXER_TASTER_PORT,BUTTON_MULTIPLEXER_TASTER); //enable input filter
	ATSAME70_PIO_Slow_Clock_Divider(BUTTON_MULTIPLEXER_TASTER_PORT, 1);                         //32kHz slow clock divider
	ATSAME70_PIO_Slow_Clock_Enable(BUTTON_MULTIPLEXER_TASTER_PORT,BUTTON_MULTIPLEXER_TASTER);   //enable debouncing filter
	
	ATSAME70_PIO_CfgOutput(ENCODER_RESET_PORT,ENCODER_RESET);
	ATSAME70_PIO_SetOutput(ENCODER_RESET_PORT,ENCODER_RESET);   //reset Encoder FFs

	//TWI (I2C) Interface
	ATSAME70_PIO_CfgPeriph(TWD_PORT,TWD,TWD_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(TWCK_PORT,TWCK,TWCK_PERIPHERAL);

	//SPI Interface
	
	//ATSAME70_PIO_CfgOutput(ATSAME70_BASE_PIOB,PIO_PB2);
	AFEC0->AFEC_CHDR = ADC_INPUT5;  //for CS0; ADC_INPUT5 is alternate function
	
	
	ATSAME70_PIO_CfgPeriph(SPI_CS0_PORT,SPI_CS0,SPI_CS0_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SPI_CS1_PORT,SPI_CS1,SPI_CS1_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SPI_CS3_PORT,SPI_CS3,SPI_CS3_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(SPCK_PORT,SPCK,SPCK_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(MISO_PORT,MISO,MISO_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(MOSI_PORT,MOSI,MOSI_PERIPHERAL);
	
	
	//SPI Interface I/O Pins
	ATSAME70_PIO_CfgOutput(EN_SPI_PORT,EN_SPI);

	//JTAG Interface: no init!
	
	//DEBUG RS232 (print) Interface
	ATSAME70_PIO_CfgPeriph(DBGU_RX_PORT,DBGU_RX,DBGU_RX_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(DBGU_TX_PORT,DBGU_TX,DBGU_TX_PERIPHERAL);

	//Interrupt Inputs I/O Pins
	ATSAME70_PIO_CfgInput (SENSOR_INT_PORT,SENSOR_INT);
	ATSAME70_PIO_Pullup_Enable(SENSOR_INT_PORT,SENSOR_INT);
	ATSAME70_PIO_CfgInput (RADIO_INT_PORT,RADIO_INT);
	ATSAME70_PIO_Pullup_Enable(RADIO_INT_PORT,RADIO_INT);
	
	//Inputs/Outputs Connector I/O Pins: Input Configuration
	ATSAME70_PIO_CfgInput (PIO00_PORT,PIO00);
	ATSAME70_PIO_CfgInput (PIO01_PORT,PIO01);
	ATSAME70_PIO_CfgInput (PIO02_PORT,PIO02);
	ATSAME70_PIO_CfgInput (PIO03_PORT,PIO03);
	ATSAME70_PIO_CfgInput (PIO04_PORT,PIO04);
	ATSAME70_PIO_CfgInput (PIO05_PORT,PIO05);
	ATSAME70_PIO_CfgInput (PIO06_PORT,PIO06);
	ATSAME70_PIO_CfgInput (PIO07_PORT,PIO07);
	
	ATSAME70_PIO_CfgOutput(PIO06_PORT,PIO06);
	//USB Interface Inputs I/O Pins: Indicator for USB Connection
	ATSAME70_PIO_CfgInput ( USB_POWER_PORT,USB_POWER);
	
	//USB Interface Inputs I/O Pins: Board Power from USB-Connector (FTDI USB Connector)
	ATSAME70_PIO_CfgInput ( USB_ON_5V_PORT,USB_ON_5V);
	ATSAME70_PIO_Pulldown_Disable(USB_ON_5V_PORT,USB_ON_5V);
	ATSAME70_PIO_Pullup_Disable(USB_ON_5V_PORT,USB_ON_5V);
	//IR Sensor Inputs I/O Pins
	ATSAME70_PIO_CfgInput ( IR_DATA_PORT,IR_DATA	);

	//WLAN RS232  Interface
	ATSAME70_PIO_CfgPeriph( WLAN_TX_PORT, WLAN_TX,WLAN_TX_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph( WLAN_RX_PORT, WLAN_RX,WLAN_RX_PERIPHERAL);

	//WLAN I/O Pins
	ATSAME70_PIO_CfgOutput(WLAN_WAKEPUP_PORT,WLAN_WAKEPUP);
	ATSAME70_PIO_CfgOutput(WLAN_EN_PORT,WLAN_EN);
	//ATSAME70_PIO_ClearOutput(WLAN_EN_PORT,WLAN_EN);
	ATSAME70_PIO_SetOutput(WLAN_EN_PORT,WLAN_EN);
	//GPS RS232  Interface
	ATSAME70_PIO_CfgPeriph(GPS_RX_PORT,GPS_RX,GPS_RX_PERIPHERAL);
	#ifdef GPS_TX_ACITVE 
	ATSAME70_PIO_CfgPeriph(GPS_TX_PORT,GPS_TX,GPS_TX_PERIPHERAL);
	#endif
	//ATSAME70_PIO_CfgInput(GPS_RX_PORT,GPS_RX);

   //MP3-Decoder (VS1053) I/O Pins
   	ATSAME70_PIO_CfgInput (MP3_DREQ_PORT,MP3_DREQ);
	#define DEFMSTR_TYPE_LAST    1
	//LED I/O Pins
	MATRIX->CCFG_SYSIO = CCFG_SYSIO_SYSIO5;
	MATRIX->MATRIX_SCFG[0] = MATRIX_SCFG_SLOT_CYCLE(2) + MATRIX_SCFG_DEFMSTR_TYPE(DEFMSTR_TYPE_LAST) ;                      //internal SRAM IF0
	MATRIX->MATRIX_SCFG[1] = MATRIX_SCFG_SLOT_CYCLE(2) + MATRIX_SCFG_DEFMSTR_TYPE(DEFMSTR_TYPE_LAST) ;                      //internal SRAM IF1
	MATRIX->MATRIX_SCFG[2] = MATRIX_SCFG_SLOT_CYCLE(2) + MATRIX_SCFG_DEFMSTR_TYPE(DEFMSTR_TYPE_LAST) ;                      //internal ROM
	MATRIX->MATRIX_SCFG[3] = MATRIX_SCFG_SLOT_CYCLE(2) + MATRIX_SCFG_DEFMSTR_TYPE(DEFMSTR_TYPE_LAST) ;                      //internal FLASH
	MATRIX->MATRIX_SCFG[4] = MATRIX_SCFG_SLOT_CYCLE(2) + MATRIX_SCFG_DEFMSTR_TYPE(DEFMSTR_TYPE_LAST) ;                      //USB HS Dual Port RAM
	MATRIX->MATRIX_SCFG[5] = MATRIX_SCFG_SLOT_CYCLE(2) + MATRIX_SCFG_DEFMSTR_TYPE(DEFMSTR_TYPE_LAST) ;                      //EBI
	MATRIX->MATRIX_SCFG[6] = MATRIX_SCFG_SLOT_CYCLE(2) + MATRIX_SCFG_DEFMSTR_TYPE(DEFMSTR_TYPE_LAST) ;                      //QSPI
	MATRIX->MATRIX_SCFG[7] = MATRIX_SCFG_SLOT_CYCLE(2) + MATRIX_SCFG_DEFMSTR_TYPE(DEFMSTR_TYPE_LAST) ;                      //peripheral bridge
	MATRIX->MATRIX_SCFG[8] = MATRIX_SCFG_SLOT_CYCLE(2) + MATRIX_SCFG_DEFMSTR_TYPE(DEFMSTR_TYPE_LAST) ;                      //Cortex AHB Slave
	ATSAME70_PIO_CfgOutput(LED0_PORT,LED0);
	ATSAME70_PIO_CfgOutput(LED1_PORT,LED1);
	ATSAME70_PIO_CfgOutput(LED2_PORT,LED2); //TDO Output!!!  periphal alternate

	//Connector RS232 Interface
	ATSAME70_PIO_CfgPeriph(RXD1_PORT,RXD1,RXD1_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(TXD1_PORT,TXD1,TXD1_PERIPHERAL);

    //ADC Interface: Channel Enable Register 
    ANALOG_INPUT0_AFEC->AFEC_CHER = (ANALOG_INPUT0_AFEC->AFEC_CHER) | ANALOG_INPUT0_CHANNEL;
    ANALOG_INPUT1_AFEC->AFEC_CHER = (ANALOG_INPUT0_AFEC->AFEC_CHER) | ANALOG_INPUT1_CHANNEL;
    ADC_INPUT2_AFEC->AFEC_CHER = (ADC_INPUT2_AFEC->AFEC_CHER) |  ADC_INPUT2;
    ADC_INPUT3_AFEC->AFEC_CHER = (ADC_INPUT3_AFEC->AFEC_CHER) |  ADC_INPUT3;
    ADC_INPUT4_AFEC->AFEC_CHER = (ADC_INPUT4_AFEC->AFEC_CHER) |  ADC_INPUT4;
    ADC_INPUT5_AFEC->AFEC_CHER = (ADC_INPUT5_AFEC->AFEC_CHER) |  ADC_INPUT5;
    ADC_INPUT_1_2V_AFEC->AFEC_CHER = (ADC_INPUT_1_2V_AFEC->AFEC_CHER) | ADC_INPUT_1_2V;
    ADC_INPUT_3_3V_AFEC->AFEC_CHER = (ADC_INPUT_3_3V_AFEC->AFEC_CHER) | ADC_INPUT_3_3V;
    ADC_INPUT_5V_AFEC->AFEC_CHER = (ADC_INPUT_5V_AFEC->AFEC_CHER) | ADC_INPUT_5V;
    //ADC_INPUT_TASTER_AFEC->AFEC_CHER = (ADC_INPUT_TASTER_AFEC->AFEC_CHER) | ADC_INPUT_TASTER;
	
	//DAC Interface Channel Enable Register 
	// DACC->DACC_CHER = DAC0 | DAC1;		
}


void SCB_InvalidateDCache_by_Addr (uint32_t *addr, int32_t dsize)
{
	int32_t op_size = dsize;
	uint32_t op_addr = (uint32_t)addr;
	int32_t linesize = 32U;                /* in Cortex-M7 size of cache line is fixed to 8 words (32 bytes) */
//	if (((SCB->CCR) &  SCB_CCR_DC_Msk) == 0) return;  //if cache disabled return
	__DSB();
	while (op_size > 0) {
		SCB->DCCIMVAC = op_addr; //SCB->DCIMVAC = op_addr;
		op_addr += linesize;
		op_size -= linesize;
	}
	__DSB();
	__ISB();
}

void SCB_CleanDCache_by_Addr (uint32_t *addr, int32_t dsize)
{
    int32_t  op_size = dsize;
    uint32_t op_addr = (uint32_t) addr;
    uint32_t linesize = 32UL;               // in Cortex-M7 size of cache line is fixed to 8 words (32 bytes)
//	if (((SCB->CCR) &  SCB_CCR_DC_Msk) == 0) return;   //if cache disabled return
    __DSB();

    while (op_size > 0) {
      SCB->DCCMVAC = op_addr;
      op_addr +=          linesize;
      op_size -= (int32_t)linesize;
    }

    __DSB();
    __ISB();
}

void SCB_CleanInvalidateDCache_by_Addr (uint32_t *addr, int32_t dsize)
{
    int32_t  op_size = dsize;
    uint32_t op_addr = (uint32_t) addr;
    uint32_t linesize = 32UL;               // in Cortex-M7 size of cache line is fixed to 8 words (32 bytes)
//	if (((SCB->CCR) &  SCB_CCR_DC_Msk) == 0) return;  //if cache disabled return: clean data cache -> write back dirty cache entries (after reset, the entries of data cache are undefined!!!)
    __DSB();

    while (op_size > 0) {
      SCB->DCCIMVAC = op_addr;
      op_addr +=          linesize;
      op_size -= (int32_t)linesize;
    }

    __DSB();
    __ISB();
}

void disable_data_cache (void)
{
	if ((SCB->CCR) &  SCB_CCR_DC_Msk) 	SCB_DisableDCache();   //disable data cache only, if data cache is enabled! because SCB_DisableDCache cleans data cache 
}

void enable_data_cache (void)
{
	if (((SCB->CCR) &  SCB_CCR_DC_Msk) == 0) 	
	{
		SCB_InvalidateDCache();
		SCB_EnableDCache();
	}
	if ((SCB->CCR) &  SCB_CCR_DC_Msk) printf("Data Cache enabled\n");  
}

void disable_instruction_cache (void)
{
	if ((SCB->CCR) &  SCB_CCR_IC_Msk) 	SCB_DisableICache();
}

void enable_instruction_cache (void)
{
	if (((SCB->CCR) &  SCB_CCR_IC_Msk) == 0) 	SCB_EnableICache();
}



void soft_reset (void)
{
	__disable_irq();
	RSTC->RSTC_MR = RSTC_MR_KEY_PASSWD | RSTC_MR_ERSTL(5) ;
	delayms(10);
	RSTC->RSTC_CR = RSTC_CR_KEY_PASSWD | RSTC_CR_EXTRST;
	delayms(100);
	RSTC->RSTC_MR = RSTC_MR_KEY_PASSWD | RSTC_MR_ERSTL(5) | RSTC_MR_URSTEN;
	delayus(10);
	__enable_irq();
}

void delay20ns(unsigned long value)
{
	unsigned long i;
	
	i = 0;
	
	for (i=value; i>0;i--)
	{
		asm volatile ("NOP");
		asm volatile ("NOP");
		asm volatile ("NOP");
		asm volatile ("NOP");
		asm volatile ("NOP");
		asm volatile ("NOP");
		asm volatile ("NOP");
		asm volatile ("NOP");
		asm volatile ("NOP");
		//asm volatile ("NOP");
	}
}

uint32_t delayus_parameter = 40;

void delayus(unsigned long value)
{
	unsigned long i;
	if (value == 0) return;
	//i = 0;
	
	for (i=value; i>0;i--)
	{
		delay20ns(delayus_parameter);
	}
}

void delayms(unsigned long value)
{
	unsigned long i;
	i = 0;

	for (i=value; i>0;i--)
	{
		delayus(1000);
	}
}


void PMC_EnablePeripheral(uint32_t dwId)
{
	//assert(dwId < 63);

	if (dwId < 32) {
		if ((PMC->PMC_PCSR0 & ((uint32_t)1 << dwId)) == ((uint32_t)1 << dwId)) {
		/*	TRACE_DEBUG("PMC_EnablePeripheral: clock of peripheral" \
						 " %u is already enabled\n\r", (unsigned int)dwId);
		*/
		} else
			PMC->PMC_PCER0 = 1 << dwId;
	} else {
		dwId -= 32;

		if ((PMC->PMC_PCSR1 & ((uint32_t)1 << dwId)) == ((uint32_t)1 << dwId)) {
		/*	TRACE_DEBUG("PMC_EnablePeripheral: clock of peripheral" \
						 " %u is already enabled\n\r", (unsigned int)(dwId + 32));
		*/				 
		} else
			PMC->PMC_PCER1 = 1 << dwId;
	}
}

void PMC_DisablePeripheral(uint32_t dwId)
{
	assert(dwId < 63);

	if (dwId < 32) {
		if ((PMC->PMC_PCSR0 & ((uint32_t)1 << dwId)) != ((uint32_t)1 << dwId)) {
	/*		TRACE_DEBUG("PMC_DisablePeripheral: clock of peripheral" \
						" %u is not enabled\n\r", (unsigned int)dwId);
	*/	
		} else
			PMC->PMC_PCDR0 = 1 << dwId;
	} else {
		dwId -= 32;

		if ((PMC->PMC_PCSR1 & ((uint32_t)1 << dwId)) != ((uint32_t)1 << dwId)) {
/*			TRACE_DEBUG("PMC_DisablePeripheral: clock of peripheral"
						 " %u is not enabled\n\r", (unsigned int)(dwId + 32));
*/
		} else
			PMC->PMC_PCDR1 = 1 << dwId;
	}
}

uint32_t PMC_IsPeriphEnabled(uint32_t dwId)
{
	assert(dwId < ID_PERIPH_COUNT);

	if (dwId < 32)
		return (PMC->PMC_PCSR0 & (1 << dwId));
	else
		return (PMC->PMC_PCSR1 & (1 << (dwId - 32)));
}

#define PMC_FAST_STARTUP_Msk    (0x7FFFFu)

#define PIO_DELTA   ((uint32_t) PIOB - (uint32_t) PIOA)



struct s_interrupt_source {
	uint32_t id;
	uint32_t mask;
	uint32_t attr;

	/* Interrupt handler. */
	void (*handler) (const uint32_t, const uint32_t);
};
uint32_t get_power_source(void)
{
	static uint32_t last_power_source = POWER_SOURCE_UNKNOWN;

	if((ATSAME70_PIO_GetInput(USB_ON_5V_PORT) & USB_ON_5V) == 0) {
		last_power_source = POWER_SOURCE_EXT;
	}
	else {
		last_power_source = POWER_SOURCE_USB;
	}
	
	return last_power_source;
}


void reset(void) 
{
	RSTC->RSTC_CR = RSTC_CR_KEY_PASSWD | RSTC_CR_PROCRST | RSTC_CR_EXTRST;
}

#define CONFIG_USBCLK_DIV           1

 void SystemClkInit( void )
 {
	 /* Set FWS according to SYS_BOARD_MCKR configuration */
	 EFC->EEFC_FMR = EEFC_FMR_FWS(FLASH_WAIT_STATE) | EEFC_FMR_CLOE;
	 // EFC->EEFC_FCR = (EEFC_FCR_FKEY_PASSWD | EEFC_FCR_FCMD_SGPB | EEFC_FCR_FARG(7));
	 // EFC->EEFC_FCR = (EEFC_FCR_FKEY_PASSWD | EEFC_FCR_FCMD_SGPB | EEFC_FCR_FARG(8));
	 // TCM_ENABLE();
	

	 /* Initialize main oscillator */
	 if ( !(PMC->CKGR_MOR & CKGR_MOR_MOSCSEL) )  //main oscillator register: MOSCEL = 1?
	 {
		 PMC->CKGR_MOR = CKGR_MOR_KEY_PASSWD | SYS_BOARD_OSCOUNT | CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN;
		//Key + start-up time + RC-oszillator enable + crystal oszillator enable (12MHz)
		 while ( !(PMC->PMC_SR & PMC_SR_MOSCXTS) )  //crystal oszillator stabilized?
		 {  ;  }
	 }

	 // Switch to 3-20MHz Xtal oscillator: PMC Clock Generator Main Oscillator Register
	 PMC->CKGR_MOR = CKGR_MOR_KEY_PASSWD | SYS_BOARD_OSCOUNT | CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN | CKGR_MOR_MOSCSEL;
	//Key + start-up time + RC-oszillator enable + crystal oszillator enable (12MHz) + select crystal oszillator
	 while ( !(PMC->PMC_SR & PMC_SR_MOSCSELS) )  //crystal oszillator selection done?
	 {  ;  }
/*
	 PMC->PMC_MCKR = (PMC->PMC_MCKR & ~(uint32_t)PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_MAIN_CLK;
	//master clock register: select main clock
	 while ( !(PMC->PMC_SR & PMC_SR_MCKRDY) ) //master clock ready?
	 {  ;   }
*/
	 /* Initialize PLLA */
	 PMC->CKGR_PLLAR = SYS_BOARD_PLLAR;
	 while ( !(PMC->PMC_SR & PMC_SR_LOCKA) )  //PLL A is locked?
	 {  ;   }

	 // Switch to main clock 
	 PMC->PMC_MCKR = (SYS_BOARD_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_MAIN_CLK;  //select PLL A clock -> master clock
	 while ( !(PMC->PMC_SR & PMC_SR_MCKRDY) )  //master clock ready?
	 {   ;  }

	 //Switch to PLLA: Prescaler 1:2; Master clock prescaler 1:2; PLLA_CLK = 600MHz; Processor CLK: 600MHz/Prescaler = 300MHz; Master CLK = Processor CLK/Master clock prescaler = 150MHz
	 PMC->PMC_MCKR = SYS_BOARD_MCKR;   //SYS_BOARD_MCKR: (PMC_MCKR_PRES_CLK_2 | PMC_MCKR_CSS_PLLA_CLK | PMC_MCKR_MDIV(PMC_MCKR_MDIV_PCK_DIV2_Val))
	 while ( !(PMC->PMC_SR & PMC_SR_MCKRDY) )  //master clock ready?
	 {   ;  }


	//USB clock enable
	PMC->CKGR_UCKR = CKGR_UCKR_UPLLCOUNT(3) | CKGR_UCKR_UPLLEN;

	// Wait UTMI PLL Lock Status 
	while (!(PMC->PMC_SR & PMC_SR_LOCKU));
	
	PMC->PMC_USB = PMC_USB_USBS | PMC_USB_USBDIV(CONFIG_USBCLK_DIV - 1);  //select UPLL input + DIV = 1
	PMC->PMC_SCER = PMC_SCER_USBCLK;
 }
/*
void sysclk_disable_usb(void)
{
	pmc_disable_udpck();
}

void sysclk_enable_peripheral_clock(uint32_t ul_id)
{
	pmc_enable_periph_clk(ul_id);
}
*/
#define USB_LED_PORT         LED0_PORT
#define LED_USB              LED0		 	 	         //pin 117  output


void LED_On (uint8_t led)
{
	if (led == 0) ATSAME70_PIO_ClearOutput(LED0_PORT, LED0);
	if (led == 1) ATSAME70_PIO_ClearOutput(LED1_PORT, LED1);
	if (led == 2) ATSAME70_PIO_ClearOutput(LED2_PORT, LED2);
}

void LED_Off (uint8_t led)
{
	if (led == 0) ATSAME70_PIO_SetOutput(LED0_PORT, LED0);
	if (led == 1) ATSAME70_PIO_SetOutput(LED1_PORT, LED1);
	if (led == 2) ATSAME70_PIO_SetOutput(LED2_PORT, LED2);
}

#define DWT_LSR_Present_Msk			ITM_LSR_Present_Msk
#define DWT_LSR_Access_Msk			ITM_LSR_Access_Msk
#define DWT_LAR_KEY					0xC5ACCE55

void reset_cycle_cnt (void)
{
	if (DWT->CTRL !=0)
	{
		//printf("cycle counter available %lx\n",DWT->CTRL);
		CoreDebug->DEMCR   |= (1 <<24);
		DWT->CYCCNT = 0;
		DWT->CTRL = 0;
	}
}

inline void start_cycle_cnt(void)
{
	DWT->CTRL |= 0x00000001;
}

inline void stop_cycle_cnt(void)
{
	DWT->CTRL &= 0xfffffffe;
}

uint32_t get_cycle_cnt(void)
{
	return DWT->CYCCNT;
}



void dwt_access_enable (uint8_t ena)
{
	uint32_t lsr = DWT->LSR;
	CoreDebug->DEMCR = CoreDebug->DEMCR | CoreDebug_DEMCR_TRCENA_Msk;
	if ((lsr & DWT_LSR_Present_Msk) != 0)
	{
		if (ena)
		{
			if ((lsr & DWT_LSR_Access_Msk) != 0)
			{
				DWT->LAR = DWT_LAR_KEY;
			}		
		}
		else
		{	
			if ((lsr & DWT_LSR_Access_Msk) == 0)
			{
				DWT->LAR = 0;
			}
			
		}
	}
}

//calibrate delayus_parameter
void calibrate_delayus (void)
{
	//int32_t cnt_100us = 0;
	uint16_t i;
	dwt_access_enable(true);
	reset_cycle_cnt();
	start_cycle_cnt();	
	for (i=100; i>0;i--)
	{
		delay20ns(delayus_parameter);
	}
	stop_cycle_cnt();
	//cnt_100us = get_cycle_cnt();   
	//printf("cnt 100us: %ld",cnt_100us);
	if (get_cycle_cnt() < 1000)
		delayus_parameter = 42;
	else
	{
		delayus_parameter = (delayus_parameter * (CPU_CLK/100))/get_cycle_cnt();  //[10ms]
		delayus_parameter = delayus_parameter/100 + 1;   //100us correction
	}
	printf("delayus_parameter: %ld\n",delayus_parameter);
}


inline void* align_pointer_dcache_line_size(void* pointer_in)
{
	uint32_t pointer_buffer = (uint32_t) pointer_in;
	pointer_buffer = pointer_buffer + DCACHE_LINE_SIZE - pointer_buffer % DCACHE_LINE_SIZE;  //calculate pointer align
	return (void*)pointer_buffer;
}


void trig_logicanalyzer(void)
{
	ATSAME70_PIO_ClearOutput(PIO06_PORT,PIO06);
	delay20ns(2);
	ATSAME70_PIO_SetOutput(PIO06_PORT,PIO06);
	delay20ns(2);
	//ATSAME70_PIO_ClearOutput(PIO06_PORT,PIO06);
}