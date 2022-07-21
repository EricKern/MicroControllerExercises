#ifndef _Board_cortex7_H_
#define _Board_cortex7_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "sam.h"

//#define SAME70Q21
#define CONF_BOARD_USB_PORT
#define CONFIG_SLEEPMGR_ENABLE
#define GPS_TX_ACITVE 
/*
#define ARM_CM_DEMCR			(*(uint32_t *) 0xE000EDFC)
#define ARM_CM_DWT_CTRL			(*(uint32_t *) 0xE0001000)
#define ARM_CM_DWT_CYCCNT		(*(uint32_t *) 0xE0001004)
*/

/** board main clock xtal statup time */
#define BOARD_OSC_STARTUP_US            15625

#define BOARD_NAME "MP3 SAM E70"
#define BOARD_USB_BMATTRIBUTES USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP

//spio pio;
#define ATSAME70_BASE_PIOA    PIOA
#define ATSAME70_BASE_PIOB    PIOB
#define ATSAME70_BASE_PIOC    PIOC
#define ATSAME70_BASE_PIOD    PIOD
#define ATSAME70_BASE_DBGU    USART1
#define PERIPHERAL_A          0
#define PERIPHERAL_B          1
#define PERIPHERAL_C          2
#define PERIPHERAL_D          3

//SDRAM Interface
#define SDRAM_ADR0_PORT      ATSAME70_BASE_PIOC
#define SDRAM_ADR0			 PIO_PC20       //pin 120 
#define SDRAM_ADR0_PERIPHERAL PERIPHERAL_A

#define SDRAM_ADR1_PORT      ATSAME70_BASE_PIOC
#define SDRAM_ADR1			 PIO_PC21       //pin 122 
#define SDRAM_ADR1_PERIPHERAL PERIPHERAL_A

#define SDRAM_ADR2_PORT      ATSAME70_BASE_PIOC
#define SDRAM_ADR2			 PIO_PC22       //pin 124 
#define SDRAM_ADR2_PERIPHERAL PERIPHERAL_A

#define SDRAM_ADR3_PORT      ATSAME70_BASE_PIOC
#define SDRAM_ADR3			 PIO_PC23       //pin 127 
#define SDRAM_ADR3_PERIPHERAL PERIPHERAL_A

#define SDRAM_ADR4_PORT      ATSAME70_BASE_PIOC
#define SDRAM_ADR4			 PIO_PC24       //pin 130 
#define SDRAM_ADR4_PERIPHERAL PERIPHERAL_A

#define SDRAM_ADR5_PORT      ATSAME70_BASE_PIOC
#define SDRAM_ADR5			 PIO_PC25       //pin 133 
#define SDRAM_ADR5_PERIPHERAL PERIPHERAL_A

#define SDRAM_ADR6_PORT      ATSAME70_BASE_PIOC
#define SDRAM_ADR6			 PIO_PC26       //pin 13 
#define SDRAM_ADR6_PERIPHERAL PERIPHERAL_A

#define SDRAM_ADR7_PORT      ATSAME70_BASE_PIOC
#define SDRAM_ADR7			 PIO_PC27       //pin 12 periphal A
#define SDRAM_ADR7_PERIPHERAL PERIPHERAL_A

#define SDRAM_ADR8_PORT      ATSAME70_BASE_PIOC
#define SDRAM_ADR8			 PIO_PC28       //pin 76 periphal A
#define SDRAM_ADR8_PERIPHERAL PERIPHERAL_A

#define SDRAM_ADR9_PORT      ATSAME70_BASE_PIOC
#define SDRAM_ADR9			 PIO_PC29       //pin 16 periphal A
#define SDRAM_ADR9_PERIPHERAL PERIPHERAL_A

#define SDRAM_ADR10_PORT     ATSAME70_BASE_PIOD
#define SDRAM_ADR10			 PIO_PD13       //pin 88 periphal C
#define SDRAM_ADR10_PERIPHERAL PERIPHERAL_C

#define SDRAM_ADR11_PORT     ATSAME70_BASE_PIOC
#define SDRAM_ADR11			 PIO_PC31       //pin 14 periphal A
#define SDRAM_ADR11_PERIPHERAL PERIPHERAL_A

#define SDRAM_ADR12_PORT     ATSAME70_BASE_PIOA
#define SDRAM_ADR12			 PIO_PA18       //pin 24 periphal C
#define SDRAM_ADR12_PERIPHERAL PERIPHERAL_C

#define SDRAM_BA0_PORT       ATSAME70_BASE_PIOA
#define SDRAM_BA0			 PIO_PA20       //pin 22  periphal C
#define SDRAM_BA0_PERIPHERAL PERIPHERAL_C

#define SDRAM_BA1_PORT       ATSAME70_BASE_PIOA
#define SDRAM_BA1			 PIO_PA0        //pin 102  periphal C
#define SDRAM_BA1_PERIPHERAL PERIPHERAL_C

#define SDRAM_DATA0_PORT     ATSAME70_BASE_PIOC
#define SDRAM_DATA0			 PIO_PC0       //pin 11 periphal A
#define SDRAM_DATA0_PERIPHERAL PERIPHERAL_A

#define SDRAM_DATA1_PORT     ATSAME70_BASE_PIOC
#define SDRAM_DATA1			 PIO_PC1       //pin 38 periphal A
#define SDRAM_DATA1_PERIPHERAL PERIPHERAL_A

#define SDRAM_DATA2_PORT     ATSAME70_BASE_PIOC
#define SDRAM_DATA2			 PIO_PC2       //pin 39 periphal A
#define SDRAM_DATA2_PERIPHERAL PERIPHERAL_A

#define SDRAM_DATA3_PORT     ATSAME70_BASE_PIOC
#define SDRAM_DATA3			 PIO_PC3       //pin 40 periphal A
#define SDRAM_DATA3_PERIPHERAL PERIPHERAL_A

#define SDRAM_DATA4_PORT     ATSAME70_BASE_PIOC
#define SDRAM_DATA4			 PIO_PC4       //pin 41 periphal A
#define SDRAM_DATA4_PERIPHERAL PERIPHERAL_A

#define SDRAM_DATA5_PORT     ATSAME70_BASE_PIOC
#define SDRAM_DATA5			 PIO_PC5       //pin 58 periphal A
#define SDRAM_DATA5_PERIPHERAL PERIPHERAL_A

#define SDRAM_DATA6_PORT     ATSAME70_BASE_PIOC
#define SDRAM_DATA6			 PIO_PC6       //pin 54 periphal A
#define SDRAM_DATA6_PERIPHERAL PERIPHERAL_A

#define SDRAM_DATA7_PORT     ATSAME70_BASE_PIOC
#define SDRAM_DATA7			 PIO_PC7       //pin 48 periphal A
#define SDRAM_DATA7_PERIPHERAL PERIPHERAL_A

#define SDRAM_DATA8_PORT     ATSAME70_BASE_PIOE
#define SDRAM_DATA8			 PIO_PE0       //pin 4 periphal A
#define SDRAM_DATA8_PERIPHERAL PERIPHERAL_A

#define SDRAM_DATA9_PORT     ATSAME70_BASE_PIOE
#define SDRAM_DATA9			 PIO_PE1       //pin 6 periphal A
#define SDRAM_DATA9_PERIPHERAL PERIPHERAL_A

#define SDRAM_DATA10_PORT    ATSAME70_BASE_PIOE
#define SDRAM_DATA10		 PIO_PE2       //pin 7 periphal A
#define SDRAM_DATA10_PERIPHERAL PERIPHERAL_A

#define SDRAM_DATA11_PORT    ATSAME70_BASE_PIOE
#define SDRAM_DATA11		 PIO_PE3       //pin 10 periphal A
#define SDRAM_DATA11_PERIPHERAL PERIPHERAL_A

#define SDRAM_DATA12_PORT    ATSAME70_BASE_PIOE
#define SDRAM_DATA12		 PIO_PE4       //pin 27 periphal A
#define SDRAM_DATA12_PERIPHERAL PERIPHERAL_A

#define SDRAM_DATA13_PORT    ATSAME70_BASE_PIOE
#define SDRAM_DATA13		 PIO_PE5       //pin 28 periphal A
#define SDRAM_DATA13_PERIPHERAL PERIPHERAL_A

#define SDRAM_DATA14_PORT    ATSAME70_BASE_PIOA
#define SDRAM_DATA14		 PIO_PA15      //pin 49 periphal A
#define SDRAM_DATA14_PERIPHERAL PERIPHERAL_A

#define SDRAM_DATA15_PORT    ATSAME70_BASE_PIOA
#define SDRAM_DATA15		 PIO_PA16      //pin 45 periphal A
#define SDRAM_DATA15_PERIPHERAL PERIPHERAL_A


#define SDRAM_CKE_PORT       ATSAME70_BASE_PIOD
#define SDRAM_CKE		     PIO_PD14      //pin 84 periphal C
#define SDRAM_CKE_PERIPHERAL PERIPHERAL_C

#define SDRAM_CLK_PORT       ATSAME70_BASE_PIOD
#define SDRAM_CLK		     PIO_PD23      //pin 57 periphal C
#define SDRAM_CLK_PERIPHERAL PERIPHERAL_C

#define SDRAM_CAS_PORT       ATSAME70_BASE_PIOD
#define SDRAM_CAS		     PIO_PD17      //pin 74 periphal C
#define SDRAM_CAS_PERIPHERAL PERIPHERAL_C

#define SDRAM_RAS_PORT       ATSAME70_BASE_PIOD
#define SDRAM_RAS		     PIO_PD16      //pin 78 periphal C
#define SDRAM_RAS_PERIPHERAL PERIPHERAL_C

#define SDRAM_WE_PORT        ATSAME70_BASE_PIOD
#define SDRAM_WE		     PIO_PD29      //pin 108 periphal C
#define SDRAM_WE_PERIPHERAL  PERIPHERAL_C

#define SDRAM_DQML_PORT      ATSAME70_BASE_PIOC
#define SDRAM_DQML		     PIO_PC18      //pin 111 periphal A
#define SDRAM_DQML_PERIPHERAL  PERIPHERAL_A

#define SDRAM_DQMH_PORT      ATSAME70_BASE_PIOD
#define SDRAM_DQMH		     PIO_PD15      //pin 106 periphal C
#define SDRAM_DQMH_PERIPHERAL  PERIPHERAL_C

//Ethernet SRAM Interface
#define ETH_CS_PORT      	 ATSAME70_BASE_PIOC
#define ETH_CS		     	 PIO_PC14      //pin 97 periphal A
#define ETH_CS_PERIPHERAL    PERIPHERAL_A

#define ETH_IOR_PORT      	 ATSAME70_BASE_PIOC
#define ETH_IOR		     	 PIO_PC11       //pin 82 periphal A
#define ETH_IOR_PERIPHERAL   PERIPHERAL_A

#define ETH_IOW_PORT      	 ATSAME70_BASE_PIOC
#define ETH_IOW		     	 PIO_PC8      //pin 94 periphal A
#define ETH_IOW_PERIPHERAL   PERIPHERAL_A

//Ethernet I/O Pins
#define ETH_INT_PORT      	 ATSAME70_BASE_PIOC
#define ETH_INT		     	 PIO_PC15      //pin 18   input
#define ETH_PWRST_PORT       ATSAME70_BASE_PIOD
#define ETH_PWRST		     PIO_PD31      //pin 2    output  obsolete!

//LCD SRAM Interface
#define LCD_CS_PORT      	 ATSAME70_BASE_PIOA
#define LCD_CS		     	 PIO_PA22      //pin 37 periphal C
#define LCD_CS_PERIPHERAL    PERIPHERAL_C

//LCD Touch Interface I/O Pins
#define LCD_D_CLK_PORT       ATSAME70_BASE_PIOD
#define LCD_D_CLK		     PIO_PD5       //pin 125  output
#define LCD_D_CS_PORT        ATSAME70_BASE_PIOD
#define LCD_D_CS		     PIO_PD6       //pin 121  output
#define LCD_D_IN_PORT        ATSAME70_BASE_PIOD
#define LCD_D_IN		     PIO_PD1       //pin 132  output
#define LCD_D_OUT_PORT       ATSAME70_BASE_PIOD
#define LCD_D_OUT		     PIO_PD4       //pin 126  input
#define LCD_D_BUSY_PORT      ATSAME70_BASE_PIOD
#define LCD_D_BUSY		     PIO_PD8       //pin 113  input
#define LCD_DIRQ_PORT        ATSAME70_BASE_PIOA
#define LCD_DIRQ		     PIO_PA2       //pin 93  input

//LCD Intensity Control Interface TC Output: TIOB
#define LCD_INTENSITY_PORT   ATSAME70_BASE_PIOA
#define LCD_INTENSITY		 PIO_PA1       //pin 199  output periphal B
#define LCD_INTENSITY_PERIPHERAL   PERIPHERAL_B

//Rotation Encoder Interface I/O Pins
//#define ENCODER_REQUEST_PORT ATSAME70_BASE_PIOD
//#define ENCODER_REQUEST		 PIO_PD10       //pin 101  input
//#define ENCODER_DATA_PORT    ATSAME70_BASE_PIOA
//#define ENCODER_DATA		 PIO_PA29       //pin 129  input
#define ENCODER_RESET_PORT   ATSAME70_BASE_PIOD
#define ENCODER_RESET		 PIO_PD2        //pin 131  output

//Analog Multiplexer ENCODER + BUTTON Interface
#define BUTTON_MULTIPLEXER_SEL0_PORT		ATSAME70_BASE_PIOA
#define BUTTON_MULTIPLEXER_SEL0				PIO_PA29       //pin 129  output
#define BUTTON_MULTIPLEXER_SEL1_PORT		ATSAME70_BASE_PIOD
#define BUTTON_MULTIPLEXER_SEL1				PIO_PD10       //pin 101  output
#define BUTTON_MULTIPLEXER_SEL2_PORT		ATSAME70_BASE_PIOC
#define BUTTON_MULTIPLEXER_SEL2				PIO_PC17       //pin 103  output
#define BUTTON_MULTIPLEXER_TASTER_PORT		ATSAME70_BASE_PIOB
#define BUTTON_MULTIPLEXER_TASTER			PIO_PB0       //pin 21  input

#define BUTTON_MULTIPLEXER_TASTER_PORT_INTERRUPT			PIOB_IRQn
#define BUTTON_MULTIPLEXER_TASTER_PORT_INTERRUPT_PRIORITY   10
#define button_irq_handler									PIOC_Handler

//TWI (I2C) Interface
#define TWD_PORT   			 ATSAME70_BASE_PIOA
#define TWD		  			 PIO_PA3       //pin 91  input/output  periphal A
#define TWD_PERIPHERAL       PERIPHERAL_A

#define TWCK_PORT   		 ATSAME70_BASE_PIOA
#define TWCK	  			 PIO_PA4       //pin 77  input/output  periphal A
#define TWCK_PERIPHERAL       PERIPHERAL_A

//SPI Interface
#define SPI_CS0_PORT   	     ATSAME70_BASE_PIOB
#define SPI_CS0		  		 PIO_PB2        //pin 26  output  periphal D
#define SPI_CS0_PERIPHERAL   PERIPHERAL_D

#define SPI_CS1_PORT   	     ATSAME70_BASE_PIOA
#define SPI_CS1		  		 PIO_PA31       //pin 118  output  periphal A
#define SPI_CS1_PERIPHERAL   PERIPHERAL_A

#define SPI_CS3_PORT   	     ATSAME70_BASE_PIOD
#define SPI_CS3		  		 PIO_PD27       //pin 47  output  periphal B
#define SPI_CS3_PERIPHERAL   PERIPHERAL_B

#define SPCK_PORT   	     ATSAME70_BASE_PIOD
#define SPCK		  		 PIO_PD22       //pin 60  output  periphal B
#define SPCK_PERIPHERAL      PERIPHERAL_B

#define MISO_PORT   	     ATSAME70_BASE_PIOD
#define MISO		  		 PIO_PD20       //pin 65  input  periphal B
#define MISO_PERIPHERAL      PERIPHERAL_B

#define MOSI_PORT   	     ATSAME70_BASE_PIOD
#define MOSI		  		 PIO_PD21       //pin 63  output  periphal B
#define MOSI_PERIPHERAL      PERIPHERAL_B

//SPI Interface I/O Pins
#define EN_SPI_PORT   	     ATSAME70_BASE_PIOC
#define EN_SPI		  		 PIO_PC9       //pin 86  output

//JTAG Interface
#define TCK_PORT   	         ATSAME70_BASE_PIOB
#define TCK		  		     PIO_PB7        //pin 89  input  periphal alternate
#define TMS_PORT   	         ATSAME70_BASE_PIOB
#define TMS		  		     PIO_PB6        //pin 79  input  periphal alternate
#define TDO_PORT   	         ATSAME70_BASE_PIOB
#define TDO		  		     PIO_PB5        //pin 109  output  periphal alternate
#define TDI_PORT   	         ATSAME70_BASE_PIOB
#define TDI		  		     PIO_PB4        //pin 105  input  periphal alternate

//DEBUG RS232 (print) Interface
#define DBGU_RX_PORT   	     ATSAME70_BASE_PIOA
#define DBGU_RX		  		 PIO_PA9        //pin 75  input  periphal A
#define DBGU_RX_PERIPHERAL   PERIPHERAL_A
#define DBGU_TX_PORT   	     ATSAME70_BASE_PIOA
#define DBGU_TX		  		 PIO_PA10       //pin 66  output  periphal A
#define DBGU_TX_PERIPHERAL   PERIPHERAL_A

//Interrupt Inputs I/O Pins
#define SENSOR_INT_PORT   	 ATSAME70_BASE_PIOD
#define SENSOR_INT		     PIO_PD9       //pin 110  input low active
#define RADIO_INT_PORT   	 ATSAME70_BASE_PIOA
#define RADIO_INT		     PIO_PA12      //pin 68   input low active

//Inputs/Outputs Connector I/O Pins
#define PIO00_PORT   	     ATSAME70_BASE_PIOA
#define PIO00		         PIO_PA13      //pin 42  Input/Output
#define PIO01_PORT   	     ATSAME70_BASE_PIOA
#define PIO01		         PIO_PA14      //pin 51  Input/Output
#define PIO02_PORT   	     ATSAME70_BASE_PIOA
#define PIO02		         PIO_PA23      //pin 46  Input/Output
#define PIO03_PORT   	     ATSAME70_BASE_PIOA
#define PIO03		         PIO_PA24      //pin 56  Input/Output
#define PIO04_PORT   	     ATSAME70_BASE_PIOD
#define PIO04		         PIO_PD24      //pin 55  Input/Output
#define PIO05_PORT   	     ATSAME70_BASE_PIOA
#define PIO05		         PIO_PA26      //pin 62  Input/Output
#define PIO06_PORT   	     ATSAME70_BASE_PIOA
#define PIO06		         PIO_PA11      //pin 64  Input/Output
#define PIO07_PORT   	     ATSAME70_BASE_PIOD
#define PIO07		         PIO_PD19      //pin 67  Input/Output

#define ADC_INPUT0_CHANNEL			0
#define ADC_INP4_CHANNEL			1
#define ADC_INP5_CHANNEL			2
#define ADC_INP2_CHANNEL			6
#define ADC_INP3_CHANNEL			8
#define ADC_TEMP_SENSOR_CHANNEL		11
#define ADC_INPUT1_CHANNEL			12
#define INPUT_5V_CHANNEL			13
#define INPUT_1_2V_CHANNEL			15
#define INPUT_3_3V_CHANNEL			17

#define ADC_INPUT0				0
#define ADC_INP4			    1
#define ADC_INP5				2
#define ADC_INP2				3
#define ADC_INP3				4
#define ADC_TEMP_SENSOR			5
#define ADC_INPUT1				6
#define INPUT_5V			    7 
#define INPUT_1_2V			    8
#define INPUT_3_3V				9


#define ADC_VREF                2500   // [mV]
#define INPUT_ADC0_SCALE        1024   //2^12 12-Bit ADC
#define INPUT_ADC1_SCALE        1024   //2^12 12-Bit ADC
#define INPUT_2_SCALE           4096   //2^12 12-Bit ADC
#define INPUT_3_SCALE           4096   //2^12 12-Bit ADC
#define INPUT_4_SCALE           4096   //2^12 12-Bit ADC
#define INPUT_5_SCALE           4096   //2^12 12-Bit ADC
#define INPUT_1_2V_SCALE        4096   //2^12 12-Bit ADC
#define INPUT_3_3V_SCALE        2048   //2^12 12-Bit ADC + divider 1:2
#define INPUT_5V_SCALE          1300   //2^12 12-Bit ADC + divider 1:3.2   Ri = 3.3k
#define TEMP_SCALE				9543   //2^12 12-Bit ADC 
#define TEMP_OFFSET				242    //284    //2^12 12-Bit ADC 
//UTEMP(25C) = 0.72V; 2,33mV/C -> UTEMP(0C) = 0.72V - 2,33mV * 25 = 662mV
//-> UTEMP = 662mV + T*2,33mV/C -> T = UTEMP/2,33 - 662/2,33 = UTEMP/2,33 - 284
// T = ADC_VALUE/(2^12 * 2,33)  * ADC_VREF - 284 = ADC_VALUE/9543 * ADC_VREF - 284 = ADC_VALUE/TEMP_SCALE * ADC_VREF - TEMP_OFFSET


//ADC Interface
#define AD0                    1<<0
#define AD1                    1<<1
#define AD2                    1<<2
#define AD3                    1<<3
#define AD4                    1<<4
#define AD5                    1<<5
#define AD6                    1<<6
#define AD7                    1<<7
#define AD8                    1<<8
#define AD9                    1<<9
#define AD10                   1<<10
#define AD11                   1<<11

#define ANALOG_INPUT0_CHANNEL  AD0
#define ANALOG_INPUT0_AFEC     AFEC0
#define ANALOG_INPUT1_CHANNEL  AD0
#define ANALOG_INPUT1_AFEC     AFEC1
#define ADC_INPUT2			   AD6
#define ADC_INPUT2_AFEC        AFEC0
#define ADC_INPUT3			   AD8
#define ADC_INPUT3_AFEC        AFEC0
#define ADC_INPUT4			   AD1
#define ADC_INPUT4_AFEC        AFEC0
#define ADC_INPUT5			   AD2
#define ADC_INPUT5_AFEC        AFEC0
#define ADC_INPUT_1_2V		   AD3
#define ADC_INPUT_1_2V_AFEC	   AFEC1


#define ADC_INPUT_3_3V		   AD5
#define ADC_INPUT_3_3V_AFEC	   AFEC1


#define ADC_INPUT_5V		   AD1    //(INPUT_5V>12)? (1<<(INPUT_5V-12)) : (1<<INPUT_5V) //AD1
#define ADC_INPUT_5V_AFEC	   AFEC1  //(INPUT_5V>12)?  AFEC1 : AFEC0


#define ADC_INPUT_TASTER	   AD10
#define ADC_INPUT_TASTER_AFEC  AFEC0

#define ANALOG_INPUT0_PORT   ATSAME70_BASE_PIOD
#define ANALOG_INPUT0		 PIO_PD30        //pin 34  input periphal alternate  AFE0  AD0
#define ANALOG_INPUT1_PORT   ATSAME70_BASE_PIOB
#define ANALOG_INPUT1		 PIO_PB1         //pin 20  input periphal alternate

#define ADCIN2_PORT   	     ATSAME70_BASE_PIOA
#define ADCIN2		  		 PIO_PA17        //pin 25  input periphal alternate
#define ADCIN3_PORT   	     ATSAME70_BASE_PIOA
#define ADCIN3		  		 PIO_PA19        //pin 23  input periphal alternate
#define ADCIN4_PORT   	     ATSAME70_BASE_PIOA
#define ADCIN4		  		 PIO_PA21        //pin 32  input periphal alternate
#define ADCIN5_PORT   	     ATSAME70_BASE_PIOB
#define ADCIN5		  		 PIO_PB3         //pin 31  input periphal alternate

#define ADC1_2V_PORT   	     ATSAME70_BASE_PIOC
#define ADC1_2V		  		 PIO_PC12         //pin 17  input periphal alternate
#define ADC3_3V_PORT   	     ATSAME70_BASE_PIOC
#define ADC3_3V		  		 PIO_PC30         //pin 15  input periphal alternate
#define ADC5V_PORT   	     ATSAME70_BASE_PIOC
#define ADC5V		  		 PIO_PC13         //pin 19  input periphal alternate

//DAC Interface
#define DAC0                 1<<0
#define DAC1                 1<<1
#define DAC0_CORTEX_PORT   	 ATSAME70_BASE_PIOB
#define DAC0_CORTEX		     PIO_PB13        //pin 144  input periphal alternate
#define DAC1_CORTEX_PORT   	 ATSAME70_BASE_PIOD
#define DAC1_CORTEX		     PIO_PD0         //pin 1  input periphal alternate

//USB Interface Inputs I/O Pins: Board Power from USB-Connector (FTDI USB Connector)
#define USB_POWER_PORT   	 ATSAME70_BASE_PIOA
#define USB_POWER		     PIO_PA28        //pin 112  input
//USB Interface Inputs I/O Pins: Indicator for USB Connection
#define USB_ON_5V_PORT   	 ATSAME70_BASE_PIOD
#define USB_ON_5V		     PIO_PD7         //pin 119  input

#define USB_VBUS_FLAGS         (PIO_INPUT | PIO_PULLUP)
//#define USB_VBUS_PIN             PIO_PC9_IDX  /* As IO pin input */
#define USB_VBUS_PIN             PIO_PA28_IDX  /* As IO pin input */
//#define USB_VBUS_PIN_IRQn ( PIOC_IRQn)
#define USB_VBUS_PIN_IRQn ( PIOA_IRQn)
#define USB_VBUS_PIO_ID       ID_PIOA
//#define USB_VBUS_PIO_ID       ID_PIOC
//#define USB_VBUS_PIO_MASK  PIO_PC9
#define USB_VBUS_PIO_MASK  PIO_PA28

//IR Sensor Inputs I/O Pins
#define IR_DATA_PORT   	 	 ATSAME70_BASE_PIOA
#define IR_DATA		     	 PIO_PA30        //pin 116  input

//WLAN RS232  Interface
#define WLAN_TX_PORT   	 	 ATSAME70_BASE_PIOD
#define WLAN_TX		     	 PIO_PD18        //pin 69  input periphal C
#define WLAN_TX_PERIPHERAL   PERIPHERAL_C

#define WLAN_RX_PORT   	 	 ATSAME70_BASE_PIOD
#define WLAN_RX		     	 PIO_PD3        //pin 128  output periphal C
#define WLAN_RX_PERIPHERAL   PERIPHERAL_C

//WLAN I/O Pins
#define WLAN_WAKEPUP_PORT    ATSAME70_BASE_PIOD
#define WLAN_WAKEPUP		 PIO_PD11        //pin 98  output
#define WLAN_EN_PORT    	 ATSAME70_BASE_PIOD
#define WLAN_EN		 		 PIO_PD12        //pin 88  output

//GPS RS232  Interface
#define GPS_RX_PORT   	 	 ATSAME70_BASE_PIOD
#define GPS_RX		     	 PIO_PD28        //pin 71  input   URXD3
#define GPS_RX_PERIPHERAL    PERIPHERAL_A    //input periphal a
#define GPS_TX_PORT   	 	 ATSAME70_BASE_PIOD
#define GPS_TX		     	 PIO_PD31        //pin 71  input   URXD3
#define GPS_TX_PERIPHERAL    PERIPHERAL_B    //output periphal b

//MP3-Decoder (VS1053) I/O Pins
#define MP3_DREQ_PORT    	 ATSAME70_BASE_PIOC
#define MP3_DREQ		 	 PIO_PC16        //pin 100  input

//LED I/O Pins
#define LED0_PORT    	 	 ATSAME70_BASE_PIOC
#define LED0		 	 	 PIO_PC19        //pin 117  output
#define LED1_PORT    	 	 ATSAME70_BASE_PIOC
#define LED1		 	 	 PIO_PC10        //pin 90  output
#define LED2_PORT    	 	 ATSAME70_BASE_PIOB
#define LED2		 	 	 PIO_PB5         //pin 109  output TDO Output!!!

#define USB_LED_PORT         LED0_PORT    	 	 
#define LED_USB              LED0		 	 	         //pin 117  output
//Connector RS232 Interface
#define RXD1_PORT   	     ATSAME70_BASE_PIOA
#define RXD1		  		 PIO_PA5        //pin 73  input periphal C
#define RXD1_PERIPHERAL      PERIPHERAL_A    //input periphal a

#define TXD1_PORT   	     ATSAME70_BASE_PIOA
#define TXD1		  		 PIO_PA6        //pin 114  input periphal C
#define TXD1_PERIPHERAL      PERIPHERAL_A    //input periphal a

//clock oszillator 18.432 MHz + 32. KHz
#define XIN_PORT   	     	 ATSAME70_BASE_PIOB
#define XIN 		  		 PIO_PB9        //pin 142  input periphal alternate
#define XOUT_PORT   	     ATSAME70_BASE_PIOB
#define XOUT 		  		 PIO_PB8        //pin 141  input periphal alternate
#define XIN32_PORT   	     ATSAME70_BASE_PIOA
#define XIN32 		  		 PIO_PA7        //pin 35  input periphal alternate
#define XOUT32_PORT   	     ATSAME70_BASE_PIOA
#define XOUT32 		  		 PIO_PA8        //pin 36  input periphal alternate

#define SELECT_KEY1					2
#define SELECT_KEY2					3
#define SELECT_KEY3					1
#define SELECT_KEY4					0
#define SELECT_KEY5					5
#define SELECT_KEY6					4
#define SELECT_ENCODER_UP_DOWN		6
#define SELECT_ENCODER_VALID		7

#define KEY0			0
#define KEY1			1
#define KEY2			2
#define KEY3			3
#define KEY4			4
#define KEY_ROT			5
#define KEY_ROT_UP		6
#define KEY_ROT_DOWN	7

#define NO_KEY			8

#define POWER_SOURCE_UNKNOWN	0
#define POWER_SOURCE_EXT		1
#define POWER_SOURCE_USB		2

#define HEAP_SIZE		(SDRAM_SIZE / 2)
size_t heap_usage(void); /* from syscalls.c */


void board_init(void);
uint32_t get_power_source(void);
void reset(void);
void delay20ns(unsigned long value);
void delayus(unsigned long value);
void delayms(unsigned long value);
void PMC_EnablePeripheral(uint32_t dwId);
void PMC_DisablePeripheral(uint32_t dwId);
uint32_t PMC_IsPeriphEnabled(uint32_t dwId);
void ATSAME70_PIO_CfgPeriph(Pio *pPio, unsigned long periphEnable, unsigned long periph_address);
void ATSAME70_PIO_Cfg(Pio *pPio, unsigned long pioEnable); 
void soft_reset (void);
void trig_logicanalyzer(void);
void SCB_InvalidateDCache_by_Addr (uint32_t *addr, int32_t dsize);
void SCB_CleanDCache_by_Addr (uint32_t *addr, int32_t dsize);
void SCB_CleanInvalidateDCache_by_Addr (uint32_t *addr, int32_t dsize);
void disable_data_cache (void);
void enable_data_cache (void);
void disable_instruction_cache (void);
void enable_instruction_cache (void);
void SystemClkInit( void );
void LED_On (uint8_t led);
void LED_Off (uint8_t led);
void sysclk_disable_usb(void);
void sysclk_enable_peripheral_clock(uint32_t ul_id);
extern void start_cycle_cnt(void);
extern void stop_cycle_cnt(void);
void dwt_access_enable (uint8_t ena);
void reset_cycle_cnt (void);
uint32_t get_cycle_cnt(void);
void calibrate_delayus (void);
void* align_pointer_dcache_line_size(void* pointer_in);

uint32_t pio_handler_set_pin(uint32_t ul_pin, uint32_t ul_flag, void (*p_handler) (uint32_t, uint32_t));
uint32_t pio_handler_set(Pio *p_pio, uint32_t ul_id, uint32_t ul_mask,uint32_t ul_attr, void (*p_handler) (uint32_t, uint32_t));


#endif
//Ethernet init i/o


