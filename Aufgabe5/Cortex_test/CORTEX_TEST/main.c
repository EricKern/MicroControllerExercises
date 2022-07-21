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

#include "interrupts.h"

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

TcChannel* tc_channel_timer = timer_peripheral;

void timer_init(void) 
{
	dbgu_puts("Initializing timer");
	
	// Taktsignal aktivieren
	PMC_EnablePeripheral(timer_peripheral);
	
	
	// Takt für Programmierphase ausschalten
	interrupt_timer.TC_CCR = TC_CCR_CLKDIS_Msk;
	
	// TC Channel Mode Register konfigurieren
	interrupt_timer.TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK5 | TC_CMR_CPCTRG;
	interrupt_timer.TC_RC = 33; /* 1000Hz*/
	
	interrupt_timer.TC_IER = TC_IER_CPCS; // enable RC compare interrupt
	interrupt_timer.TC_CCR = TC_CCR_CLKEN_Msk; // enable clock
	// Zurücksetzen des Timers für definierte Startbedingung
	interrupt_timer.TC_CCR = TC_CCR_SWTRG; // reset counter & start clock
	
	// Interrupt control
	NVIC_SetPriority(timer_IRQn, timer_IRQ_priority);
	NVIC_DisableIRQ(timer_IRQn);
	NVIC_ClearPendingIRQ(timer_IRQn);
	
	NVIC_EnableIRQ(timer_IRQn);
	
	dbgu_puts("Done initializing timer");
}

void timerstop(void) 
{	
	tc_channel_timer->TC_CCR = TC_CCR_CLKDIS; // Value 2 : CLKDIS is [1] -> Disables the clock
}

int led_is_on = 1;
volatile uint32_t timer0_ticks = 0;
void timer_irq_handler(void) 
{
	uint32_t s = interrupt_timer.TC_SR; // read and clear status bits
	s = s;
	++timer0_ticks;
}

uint32_t timer_time_ms(void)
{
	return timer0_ticks;
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
	
	// Select 000 -> Taster 4
	/*
	ATSAME70_PIO_ClearOutput(BUTTON_MULTIPLEXER_SEL0_PORT,BUTTON_MULTIPLEXER_SEL0);
	ATSAME70_PIO_ClearOutput(BUTTON_MULTIPLEXER_SEL1_PORT,BUTTON_MULTIPLEXER_SEL1);
	ATSAME70_PIO_ClearOutput(BUTTON_MULTIPLEXER_SEL2_PORT,BUTTON_MULTIPLEXER_SEL2);
	*/
	
	timer_init();
	
	delayms(10);
	uint32_t t_stamp1 = timer_time_ms();
	printf("Timer should be 10 but is: %ld\n", t_stamp1);										
	
    while (1)
    {	
		if(timer_time_ms() >= 1000){
			timer0_ticks = 0;
			led_is_on = led_is_on ? 0 : 1;
			if (led_is_on)
				led0_off();
			else
				led0_on();
		}
    }
}
