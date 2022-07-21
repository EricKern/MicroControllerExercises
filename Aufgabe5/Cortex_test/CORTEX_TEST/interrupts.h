/*
** interrupts.h
*/

#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

//TC0 PWM LCD
//TC1 Timer sec
//TC2 VS1053 Timer
//TC3 IR Sensor (HTPA) Timer

#define DBGU_INTERRUPT_PRIORITY				50
#define GPS_INTERRUPT_PRIORITY				20
#define TIMER_INTERRUPT_PRIORITY			16
#define VS1053_TIMER_INTERRUPT_PRIORITY		10
#define HTPA_TIMER_INTERRUPT_PRIORITY       22


#define TC0_CHANNEL		ID_TC0_CHANNEL0  //TC0:  ID_TC0_CHANNEL0
#define TC1_CHANNEL		ID_TC0_CHANNEL1  //TC1:  ID_TC0_CHANNEL1
#define TC2_CHANNEL		ID_TC0_CHANNEL2  //TC2:  ID_TC0_CHANNEL2
#define TC3_CHANNEL		ID_TC1_CHANNEL0  //TC3:  ID_TC1_CHANNEL0
#define TC4_CHANNEL		ID_TC1_CHANNEL1  //TC4:  ID_TC1_CHANNEL1
#define TC5_CHANNEL		ID_TC1_CHANNEL2  //TC5:  ID_TC1_CHANNEL2
#define TC6_CHANNEL		ID_TC2_CHANNEL0  //TC6:  ID_TC2_CHANNEL0
#define TC7_CHANNEL		ID_TC2_CHANNEL1  //TC7:  ID_TC2_CHANNEL1
#define TC8_CHANNEL		ID_TC2_CHANNEL2  //TC8:  ID_TC2_CHANNEL2
#define TC9_CHANNEL		ID_TC3_CHANNEL0  //TC9:  ID_TC2_CHANNEL0
#define TC10_CHANNEL	ID_TC3_CHANNEL1  //TC10:  ID_TC2_CHANNEL1
#define TC11_CHANNEL	ID_TC3_CHANNEL2  //TC11:  ID_TC2_CHANNEL2

#define timer_irq_handler			TC3_Handler
#define timer_IRQn					TC3_IRQn
#define timer_IRQ_priority			TIMER_INTERRUPT_PRIORITY
#define timer_peripheral			TC3_CHANNEL    //ID_TC1_CHANNEL0   //TC3!
//#define timer						TC1
#define interrupt_timer				TC1->TC_CHANNEL[0]


#define vs1053timer_irq_handler		TC4_Handler
#define vs1053timer_IRQn			TC4_IRQn
#define vs1053timer_IRQ_priority	VS1053_TIMER_INTERRUPT_PRIORITY
#define vs1053timer_peripheral		TC4_CHANNEL      //ID_TC2_CHANNEL0   //TC4!
//#define vs1053timer                 TC2
#define vs1053_timer				TC1->TC_CHANNEL[1]

#define HTPAtimer_irq_handler		TC5_Handler
#define HTPAtimer_IRQn				TC5_IRQn
#define HTPAtimer_IRQ_priority		HTPA_TIMER_INTERRUPT_PRIORITY
#define HTPAtimer_peripheral		TC5_CHANNEL
#define HTPAtimer					TC1->TC_CHANNEL[2]

#define gps_uart_irq_handler		UART3_Handler
#define gps_uart_IRQn				UART3_IRQn
#define gps_uart_IRQ_priority		GPS_INTERRUPT_PRIORITY


#define dbgu_uart_irq_handler		UART0_Handler
#define dbgu_uart_IRQn				UART0_IRQn
#define dbgu_uart_IRQ_priority		DBGU_INTERRUPT_PRIORITY


#endif
