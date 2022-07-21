/**
 * \file
 *
 * \brief GCC startup file for ATSAME70Q21
 *
 * Copyright (c) 2017 Atmel Corporation, a wholly owned subsidiary of Microchip Technology Inc.
 *
 * \license_start
 *
 * \page License
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \license_stop
 *
 */

#define ENABLE_FPU   //-mfloat-abi=hard -mfpu=fpv5-d16

#include "same70q21.h"
#include "../board_cortex7.h"
#include "../LIB_ATSAME70.h"
#include "../dbgu.h"

/* Initialize segments */
extern uint32_t _sfixed;
extern uint32_t _efixed;
extern uint32_t _etext;
extern uint32_t _srelocate;
extern uint32_t _erelocate;
extern uint32_t _szero;
extern uint32_t _ezero;
extern uint32_t _sstack;
extern uint32_t _estack;

#define ADDR_CPACR 0xE000ED88									// Address for ARM CPACR
#define REG_CPACR (*((volatile uint32_t *)ADDR_CPACR))			// CPACR Register

typedef uint32_t irqflags_t;

//Enable FPU


inline static void fpu_enable(void)
{
	//irqflags_t flags;
	//flags = cpu_irq_save();
	REG_CPACR |=
	(0xFu << 20);
	__DSB();
	__ISB();
	//cpu_irq_restore(flags);
}





/** \cond DOXYGEN_SHOULD_SKIP_THIS */
int main(void);
/** \endcond */

void __libc_init_array(void);

//void HardFault_Handler(void);

/* Default empty handler */
void Dummy_Handler(void);

/* Cortex-M7 core handlers */
void NMI_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
//void HardFault_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void MemManage_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void BusFault_Handler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UsageFault_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SVC_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void DebugMon_Handler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PendSV_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SysTick_Handler      ( void ) __attribute__ ((weak, alias("Dummy_Handler")));

/* Peripherals handlers */
void SUPC_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RSTC_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RTC_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RTT_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void WDT_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PMC_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void EFC_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UART0_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UART1_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PIOA_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PIOB_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PIOC_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void USART0_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void USART1_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void USART2_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PIOD_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PIOE_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void HSMCI_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TWIHS0_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TWIHS1_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPI0_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SSC_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC0_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC1_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC2_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC3_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC4_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC5_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void AFEC0_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void DACC_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PWM0_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void ICM_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void ACC_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void USBHS_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void MCAN0_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void MCAN1_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void GMAC_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void AFEC1_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TWIHS2_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPI1_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void QSPI_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UART2_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UART3_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UART4_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC6_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC7_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC8_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC9_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC10_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC11_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void AES_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TRNG_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void XDMAC_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void ISI_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PWM1_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SDRAMC_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RSWDT_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));

/* Exception Table */
__attribute__ ((section(".vectors")))
const DeviceVectors exception_table = {

        /* Configure Initial Stack Pointer, using linker-generated symbols */
        .pvStack = (void*) (&_estack),

        .pfnReset_Handler              = (void*) Reset_Handler,
        .pfnNMI_Handler                = (void*) NMI_Handler,
        .pfnHardFault_Handler          = (void*) HardFault_Handler,
        .pfnMemManage_Handler          = (void*) MemManage_Handler,
        .pfnBusFault_Handler           = (void*) BusFault_Handler,
        .pfnUsageFault_Handler         = (void*) UsageFault_Handler,
        .pfnReserved1_Handler          = (void*) (0UL), /* Reserved */
        .pfnReserved2_Handler          = (void*) (0UL), /* Reserved */
        .pfnReserved3_Handler          = (void*) (0UL), /* Reserved */
        .pfnReserved4_Handler          = (void*) (0UL), /* Reserved */
        .pfnSVC_Handler                = (void*) SVC_Handler,
        .pfnDebugMon_Handler           = (void*) DebugMon_Handler,
        .pfnReserved5_Handler          = (void*) (0UL), /* Reserved */
        .pfnPendSV_Handler             = (void*) PendSV_Handler,
        .pfnSysTick_Handler            = (void*) SysTick_Handler,

        /* Configurable interrupts */
        .pfnSUPC_Handler               = (void*) SUPC_Handler,   /* 0  Supply Controller */
        .pfnRSTC_Handler               = (void*) RSTC_Handler,   /* 1  Reset Controller */
        .pfnRTC_Handler                = (void*) RTC_Handler,    /* 2  Real-time Clock */
        .pfnRTT_Handler                = (void*) RTT_Handler,    /* 3  Real-time Timer */
        .pfnWDT_Handler                = (void*) WDT_Handler,    /* 4  Watchdog Timer */
        .pfnPMC_Handler                = (void*) PMC_Handler,    /* 5  Power Management Controller */
        .pfnEFC_Handler                = (void*) EFC_Handler,    /* 6  Embedded Flash Controller */
        .pfnUART0_Handler              = (void*) UART0_Handler,  /* 7  Universal Asynchronous Receiver Transmitter */
        .pfnUART1_Handler              = (void*) UART1_Handler,  /* 8  Universal Asynchronous Receiver Transmitter */
        .pvReserved9                   = (void*) (0UL),          /* 9  Reserved */
        .pfnPIOA_Handler               = (void*) PIOA_Handler,   /* 10 Parallel Input/Output Controller */
        .pfnPIOB_Handler               = (void*) PIOB_Handler,   /* 11 Parallel Input/Output Controller */
        .pfnPIOC_Handler               = (void*) PIOC_Handler,   /* 12 Parallel Input/Output Controller */
        .pfnUSART0_Handler             = (void*) USART0_Handler, /* 13 Universal Synchronous Asynchronous Receiver Transmitter */
        .pfnUSART1_Handler             = (void*) USART1_Handler, /* 14 Universal Synchronous Asynchronous Receiver Transmitter */
        .pfnUSART2_Handler             = (void*) USART2_Handler, /* 15 Universal Synchronous Asynchronous Receiver Transmitter */
        .pfnPIOD_Handler               = (void*) PIOD_Handler,   /* 16 Parallel Input/Output Controller */
        .pfnPIOE_Handler               = (void*) PIOE_Handler,   /* 17 Parallel Input/Output Controller */
        .pfnHSMCI_Handler              = (void*) HSMCI_Handler,  /* 18 High Speed MultiMedia Card Interface */
        .pfnTWIHS0_Handler             = (void*) TWIHS0_Handler, /* 19 Two-wire Interface High Speed */
        .pfnTWIHS1_Handler             = (void*) TWIHS1_Handler, /* 20 Two-wire Interface High Speed */
        .pfnSPI0_Handler               = (void*) SPI0_Handler,   /* 21 Serial Peripheral Interface */
        .pfnSSC_Handler                = (void*) SSC_Handler,    /* 22 Synchronous Serial Controller */
        .pfnTC0_Handler                = (void*) TC0_Handler,    /* 23 Timer Counter */
        .pfnTC1_Handler                = (void*) TC1_Handler,    /* 24 Timer Counter */
        .pfnTC2_Handler                = (void*) TC2_Handler,    /* 25 Timer Counter */
        .pfnTC3_Handler                = (void*) TC3_Handler,    /* 26 Timer Counter */
        .pfnTC4_Handler                = (void*) TC4_Handler,    /* 27 Timer Counter */
        .pfnTC5_Handler                = (void*) TC5_Handler,    /* 28 Timer Counter */
        .pfnAFEC0_Handler              = (void*) AFEC0_Handler,  /* 29 Analog Front-End Controller */
        .pfnDACC_Handler               = (void*) DACC_Handler,   /* 30 Digital-to-Analog Converter Controller */
        .pfnPWM0_Handler               = (void*) PWM0_Handler,   /* 31 Pulse Width Modulation Controller */
        .pfnICM_Handler                = (void*) ICM_Handler,    /* 32 Integrity Check Monitor */
        .pfnACC_Handler                = (void*) ACC_Handler,    /* 33 Analog Comparator Controller */
        .pfnUSBHS_Handler              = (void*) USBHS_Handler,  /* 34 USB High-Speed Interface */
        .pfnMCAN0_Handler              = (void*) MCAN0_Handler,  /* 35 Controller Area Network */
        .pvReserved36                  = (void*) (0UL),          /* 36 Reserved */
        .pfnMCAN1_Handler              = (void*) MCAN1_Handler,  /* 37 Controller Area Network */
        .pvReserved38                  = (void*) (0UL),          /* 38 Reserved */
        .pfnGMAC_Handler               = (void*) GMAC_Handler,   /* 39 Gigabit Ethernet MAC */
        .pfnAFEC1_Handler              = (void*) AFEC1_Handler,  /* 40 Analog Front-End Controller */
        .pfnTWIHS2_Handler             = (void*) TWIHS2_Handler, /* 41 Two-wire Interface High Speed */
        .pfnSPI1_Handler               = (void*) SPI1_Handler,   /* 42 Serial Peripheral Interface */
        .pfnQSPI_Handler               = (void*) QSPI_Handler,   /* 43 Quad Serial Peripheral Interface */
        .pfnUART2_Handler              = (void*) UART2_Handler,  /* 44 Universal Asynchronous Receiver Transmitter */
        .pfnUART3_Handler              = (void*) UART3_Handler,  /* 45 Universal Asynchronous Receiver Transmitter */
        .pfnUART4_Handler              = (void*) UART4_Handler,  /* 46 Universal Asynchronous Receiver Transmitter */
        .pfnTC6_Handler                = (void*) TC6_Handler,    /* 47 Timer Counter */
        .pfnTC7_Handler                = (void*) TC7_Handler,    /* 48 Timer Counter */
        .pfnTC8_Handler                = (void*) TC8_Handler,    /* 49 Timer Counter */
        .pfnTC9_Handler                = (void*) TC9_Handler,    /* 50 Timer Counter */
        .pfnTC10_Handler               = (void*) TC10_Handler,   /* 51 Timer Counter */
        .pfnTC11_Handler               = (void*) TC11_Handler,   /* 52 Timer Counter */
        .pvReserved53                  = (void*) (0UL),          /* 53 Reserved */
        .pvReserved54                  = (void*) (0UL),          /* 54 Reserved */
        .pvReserved55                  = (void*) (0UL),          /* 55 Reserved */
        .pfnAES_Handler                = (void*) AES_Handler,    /* 56 Advanced Encryption Standard */
        .pfnTRNG_Handler               = (void*) TRNG_Handler,   /* 57 True Random Number Generator */
        .pfnXDMAC_Handler              = (void*) XDMAC_Handler,  /* 58 Extensible DMA Controller */
        .pfnISI_Handler                = (void*) ISI_Handler,    /* 59 Image Sensor Interface */
        .pfnPWM1_Handler               = (void*) PWM1_Handler,   /* 60 Pulse Width Modulation Controller */
        .pvReserved61                  = (void*) (0UL),          /* 61 Reserved */
        .pfnSDRAMC_Handler             = (void*) SDRAMC_Handler, /* 62 SDRAM Controller */
        .pfnRSWDT_Handler              = (void*) RSWDT_Handler   /* 63 Reinforced Safety Watchdog Timer */
};

/**
 * \brief This is the code that gets called on processor reset.
 * To initialize the device, and call the main() routine.
 */

__STATIC_INLINE void TCM_Enable(void)
{
	__DSB();
	__ISB();
	//SCB->ITCMCR = (SCB_ITCMCR_EN_Msk | SCB_ITCMCR_RMW_Msk | SCB_ITCMCR_RETEN_Msk);
	SCB->DTCMCR = (SCB_DTCMCR_EN_Msk | SCB_DTCMCR_RMW_Msk | SCB_DTCMCR_RETEN_Msk);
	__DSB();
	__ISB();
}
void Reset_Handler(void)
{
        uint32_t *pSrc, *pDest;

		//EFC->EEFC_FCR = (EEFC_FCR_FKEY_PASSWD | EEFC_FCR_FCMD_CGPB | EEFC_FCR_FARG(7));
		//EFC->EEFC_FCR = (EEFC_FCR_FKEY_PASSWD | EEFC_FCR_FCMD_SGPB | EEFC_FCR_FARG(7));
		//EFC->EEFC_FCR = (EEFC_FCR_FKEY_PASSWD | EEFC_FCR_FCMD_SGPB | EEFC_FCR_FARG(8));
		//EFC->EEFC_FCR = (EEFC_FCR_FKEY_PASSWD | EEFC_FCR_FCMD_CGPB | EEFC_FCR_FARG(8));
		//TCM_Enable();
        /* Initialize the relocate segment */
        pSrc = &_etext;
        pDest = &_srelocate;

        if (pSrc != pDest) {
                for (; pDest < &_erelocate;) {
                        *pDest++ = *pSrc++;
                }
        }

        /* Clear the zero segment */
        for (pDest = &_szero; pDest < &_ezero;) {
                *pDest++ = 0;
        }

        /* Set the vector table base address */
        pSrc = (uint32_t *) & _sfixed;
        SCB->VTOR = ((uint32_t) pSrc & SCB_VTOR_TBLOFF_Msk);

#ifdef  ENABLE_FPU
		fpu_enable();
#endif
        /* Initialize the C library */
        __libc_init_array();

        /* Branch to main function */
        main();

        /* Infinite loop */
        while (1);
}

/**
 * \brief Default interrupt handler for unused IRQs.
 */
void Dummy_Handler(void)
{
	ATSAME70_PIO_CfgOutput(LED0_PORT,LED0);
	PMC_EnablePeripheral(ID_PIOA);
	ATSAME70_PIO_CfgPeriph(DBGU_RX_PORT,DBGU_RX,DBGU_RX_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(DBGU_TX_PORT,DBGU_TX,DBGU_TX_PERIPHERAL);
	MATRIX->CCFG_SYSIO = MATRIX->CCFG_SYSIO | CCFG_SYSIO_SYSIO4;
	
	if (PMC->PMC_MCKR == SYS_BOARD_MCKR) UART_Configure(BASE_DBGU_UART,ATSAME70_DBGU_BAUD,BOARD_MCK);
	else UART_Configure(BASE_DBGU_UART,ATSAME70_DBGU_BAUD,12000000);
	/* Enable receiver and transmitter */
	dbgu_clear();
	dbgu_puts("Dummy Handler Handler\n");
	while (1) {
		ATSAME70_PIO_CfgOutput(LED0_PORT,LED0);
		ATSAME70_PIO_ClearOutput(LED0_PORT, LED0);
		delayms(10);
		ATSAME70_PIO_SetOutput(LED0_PORT, LED0);
		delayms(10);
	}

}

#define ADDR_UFSR 0xE000ED88									// Address for usage fault status register
#define UFSR_NOCP 0x8											//no coprocessor usage fault


#define SCB_CFSR_USGFAULTSR_UNDEFINSTR_MASK   0x1   << 16
#define SCB_CFSR_USGFAULTSR_INVSTATE_MASK     0x1	<< 17
#define SCB_CFSR_USGFAULTSR_INVPC_MASK		  0x1	<< 18
#define SCB_CFSR_USGFAULTSR_NOCP_MASK		  0x1	<< 19
#define SCB_CFSR_USGFAULTSR_UNALIGNED_MASK	  0x1	<< 24
#define SCB_CFSR_USGFAULTSR_DIVBYZERO_MASK    0x1	<< 25


/* [15:10]	-	Reserved.
	  [9]	DIVBYZERO     Divide by zero UsageFault: The processor has executed an SDIV or UDIV instruction with a divisor of 0.
      [8]	UNALIGNED     The processor has made an unaligned memory access.
	 [7:4]	-	Reserved.
     [3]	NOCP            No coprocessor UsageFault: The processor has attempted to access a coprocessor. The processor does not support coprocessor instructions.
     [2]	INVPC           Invalid PC load UsageFault, caused by an invalid PC load by EXC_RETURN: The processor has attempted an illegal load of EXC_RETURN to the PC, as a result of an invalid context, or an invalid EXC_RETURN value.
                            When this bit is set to 1, the PC value stacked for the exception return points to the instruction that tried to perform the illegal load of the PC.
	  [1]	INVSTATE        Invalid state UsageFault:The processor has attempted to execute an instruction that makes illegal use of the EPSR. When this bit is set to 1, the PC value stacked for the exception return points to the instruction that attempted the illegal use of the EPSR.
	  [0]	UNDEFINSTR       Undefined instruction UsageFault: The processor has attempted to execute an undefined instruction. An undefined instruction is an instruction that the processor cannot decode.

*/

#define SCB_CFSR_BUSFAULTSR_IBUSERR_MASK		0x1 << 8
#define SCB_CFSR_BUSFAULTSR_PRECISERR_MASK		0x1 << 9
#define SCB_CFSR_BUSFAULTSR_IMPRECISERR_MASK	0x1 << 10
#define SCB_CFSR_BUSFAULTSR_UNSTKERR_MASK		0x1 << 11
#define SCB_CFSR_BUSFAULTSR_STKERR_MASK			0x1 << 12
#define SCB_CFSR_BUSFAULTSR_LSPERR_MASK			0x1 << 13
#define SCB_CFSR_BUSFAULTSR_BFARVALID_MASK		0x1 << 15

/*
[7]	BFARVALID  BusFault Address Register (BFAR) valid flag: BFAR holds a valid fault address.
[6]	-	Reserved.
[5]	LSPERR[a] A bus fault occurred during floating-point lazy state preservation.
[4]	STKERR BusFault on stacking for exception entry: Stacking for an exception entry has caused one or more BusFaults.
[3]	UNSTKERR BusFault on unstacking for a return from exception: Unstack for an exception return has caused one or more BusFaults.
[2]	IMPRECISERR Imprecise data bus error: A data bus error has occurred, but the return address in the stack frame is not related to the instruction that caused the error.
    This is an asynchronous fault. Therefore, if it is detected when the priority of the current process is higher than the BusFault priority, the BusFault becomes pending and becomes active only when the processor returns from all higher priority processes. If a precise fault occurs before the processor enters the handler for the imprecise BusFault, the handler detects both IMPRECISERR set to 1 and one of the precise fault status bits set to 1.
[1]	PRECISERR Precise data bus error: A data bus error has occurred, and the PC value stacked for the exception return points to the instruction that caused the fault.
[0]	IBUSERR Instruction bus error:Instruction bus error. The processor detects the instruction bus error on prefetching an instruction, but it sets the IBUSERR flag to 1 only if it attempts to issue the faulting instruction.

*/

#define SCB_CFSR_MEMFAULTSR_IACCVIOL_MASK		0x1 << 0
#define SCB_CFSR_MEMFAULTSR_DACCVIOL_MASK		0x1 << 1
#define SCB_CFSR_MEMFAULTSR_MUNSTKERR_MASK		0x1 << 3
#define SCB_CFSR_MEMFAULTSR_MSTKERR_MASK		0x1 << 4
#define SCB_CFSR_MEMFAULTSR_MLSPERR_MASK		0x1 << 5
#define SCB_CFSR_MEMFAULTSR_MMARVALID_MASK		0x1 << 7


/*
[7]	MMARVALID MemManage Fault Address Register (MMFAR) valid flag: MMAR holds a valid fault address. If a MemManage fault occurs and is escalated to a HardFault because of priority, the HardFault handler must set this bit to 0. This prevents problems on return to a stacked active MemManage fault handler whose MMAR value has been overwritten.
[6]	-	Reserved.
[5]	MLSPERR[a] A MemManage fault occurred during floating-point lazy state preservation.
[4]	MSTKERR MemManage fault on stacking for exception entry: Stacking for an exception entry has caused one or more access violations. When this bit is 1, the SP is still adjusted but the values in the context area on the stack might be incorrect. The processor has not written a fault address to the MMAR.
[3]	MUNSTKERR MemManage fault on unstacking for a return from exception: This fault is chained to the handler. This means that when this bit is 1, the original return stack is still present. The processor has not adjusted the SP from the failing return, and has not performed a new save. The processor has not written a fault address to the MMAR.
[2]	-	Reserved.
[1]	DACCVIOL Data access violation flag: The processor attempted a load or store at a location that does not permit the operation.
[0]	IACCVIOL Instruction access violation flag: This fault occurs on any access to an XN region, even when the MPU is disabled or not present. When this bit is 1, the PC value stacked for the exception return points to the faulting instruction. The processor has not written a fault address to the MMAR.
*/

void HardFault_Handler1(void)
{
	uart_clear_tx_buffer((Uart*)BASE_DBGU_UART);
	while(1);
}

void HardFault_Handler(void)
{
/*
	uint32_t hardfault_args[8];
	 volatile unsigned long stacked_r0 ;
	 volatile unsigned long stacked_r1 ;
	 volatile unsigned long stacked_r2 ;
	 volatile unsigned long stacked_r3 ;
	 volatile unsigned long stacked_r12 ;
	 volatile unsigned long stacked_lr ;
	 volatile unsigned long stacked_pc ;
	 volatile unsigned long stacked_psr ;
	 volatile unsigned long _CFSR ;
	 volatile unsigned long _HFSR ;
	 volatile unsigned long _DFSR ;
	 volatile unsigned long _AFSR ;
	 volatile unsigned long _BFAR ;
	 volatile unsigned long _MMAR ;

	 stacked_r0 = ((unsigned long)hardfault_args[0]) ;
	 stacked_r1 = ((unsigned long)hardfault_args[1]) ;
	 stacked_r2 = ((unsigned long)hardfault_args[2]) ;
	 stacked_r3 = ((unsigned long)hardfault_args[3]) ;
	 stacked_r12 = ((unsigned long)hardfault_args[4]) ;
	 stacked_lr = ((unsigned long)hardfault_args[5]) ;
	 stacked_pc = ((unsigned long)hardfault_args[6]) ;
	 stacked_psr = ((unsigned long)hardfault_args[7]) ;

	 // Configurable Fault Status Register
	 // Consists of MMSR, BFSR and UFSR
	 _CFSR = (*((volatile unsigned long *)(0xE000ED28))) ;
	 
	 // Hard Fault Status Register
	 _HFSR = (*((volatile unsigned long *)(0xE000ED2C))) ;

	 // Debug Fault Status Register
	 _DFSR = (*((volatile unsigned long *)(0xE000ED30))) ;

	 // Auxiliary Fault Status Register
	 _AFSR = (*((volatile unsigned long *)(0xE000ED3C))) ;

	 // Read the Fault Address Registers. These may not contain valid values.
	 // Check BFARVALID/MMARVALID to see if they are valid values
	 // MemManage Fault Address Register
	 _MMAR = (*((volatile unsigned long *)(0xE000ED34))) ;
	 // Bus Fault Address Register
	 _BFAR = (*((volatile unsigned long *)(0xE000ED38))) ;

	*/
	
	//sprintf(msg, "SCB->HFSR = 0x%08x\n", SCB->HFSR);
	//uint32_t hfsr_status = SCB->HFSR;
	
	//clear_uart_txfifo_buffer();	
	//BASE_DBGU_UART->UART_CR = UART_CR_RXDIS | UART_CR_TXDIS;
	dbgu_disable();
	ATSAME70_PIO_CfgOutput(LED0_PORT,LED0);
	PMC_EnablePeripheral(ID_PIOA);	
	ATSAME70_PIO_CfgPeriph(DBGU_RX_PORT,DBGU_RX,DBGU_RX_PERIPHERAL);
	ATSAME70_PIO_CfgPeriph(DBGU_TX_PORT,DBGU_TX,DBGU_TX_PERIPHERAL);
			MATRIX->CCFG_SYSIO = MATRIX->CCFG_SYSIO | CCFG_SYSIO_SYSIO4;
	
	if (PMC->PMC_MCKR == SYS_BOARD_MCKR)  UART_Configure(BASE_DBGU_UART,ATSAME70_DBGU_BAUD,BOARD_MCK);
	else UART_Configure(BASE_DBGU_UART,ATSAME70_DBGU_BAUD,12000000);
			/* Enable receiver and transmitter */
	//uart_clear_tx_buffer((Uart*)BASE_DBGU_UART);	

	//dbgu_clear();
	  static char msg[80];
	  dbgu_puts("\nIn Hard Fault Handler\n"); 
	  sprintf(msg, "SCB->HFSR = 0x%08lx\n", SCB->HFSR);
	  dbgu_puts(msg);
	  if ((SCB->HFSR & (1 << 30)) != 0) {
		  dbgu_puts("Forced Hard Fault\n");
	  if((SCB->CFSR & SCB_CFSR_USGFAULTSR_Msk)) 
		 {
			 dbgu_puts("Usage Fault: ");
			 if(SCB->CFSR & SCB_CFSR_USGFAULTSR_UNDEFINSTR_MASK)	dbgu_puts("Undefined Instruction \n");
			 if(SCB->CFSR & SCB_CFSR_USGFAULTSR_INVSTATE_MASK)		dbgu_puts("Invalid State \n");
			 if(SCB->CFSR & SCB_CFSR_USGFAULTSR_NOCP_MASK)			dbgu_puts("Invalid PC Load \n");
			 if(SCB->CFSR & SCB_CFSR_USGFAULTSR_NOCP_MASK)			dbgu_puts("No coprocessor \n");
			 if(SCB->CFSR & SCB_CFSR_USGFAULTSR_UNALIGNED_MASK)		dbgu_puts("Unaligned Memory Access \n");
			 if(SCB->CFSR & SCB_CFSR_USGFAULTSR_DIVBYZERO_MASK)		dbgu_puts("Divide by Zero \n");	
		 }
		 if((SCB->CFSR & SCB_CFSR_BUSFAULTSR_Msk)) 
		 {
			 dbgu_puts("Bus Fault: ");
			  if(SCB->CFSR & SCB_CFSR_BUSFAULTSR_IBUSERR_MASK)		dbgu_puts("Instruction Bus Error \n");
			  if(SCB->CFSR & SCB_CFSR_BUSFAULTSR_PRECISERR_MASK)	dbgu_puts("Data Bus Error \n");
			  if(SCB->CFSR & SCB_CFSR_BUSFAULTSR_IMPRECISERR_MASK)	dbgu_puts("Priority Error \n");
			  if(SCB->CFSR & SCB_CFSR_BUSFAULTSR_UNSTKERR_MASK)		dbgu_puts("on Unstacking \n");
			  if(SCB->CFSR & SCB_CFSR_BUSFAULTSR_STKERR_MASK)		dbgu_puts("on Stacking \n");
			  if(SCB->CFSR & SCB_CFSR_BUSFAULTSR_LSPERR_MASK)		dbgu_puts("occurred during Floating-point \n");
			  if(SCB->CFSR & SCB_CFSR_BUSFAULTSR_BFARVALID_MASK)	dbgu_puts("Address Register valid \n");
		 }
		 if((SCB->CFSR & SCB_CFSR_MEMFAULTSR_Msk)) 
		 {
			 dbgu_puts("Memory Manage Fault: ");
			 if(SCB->CFSR & SCB_CFSR_MEMFAULTSR_IACCVIOL_MASK)		dbgu_puts("Instruction Access Violation \n");
			 if(SCB->CFSR & SCB_CFSR_MEMFAULTSR_DACCVIOL_MASK)		dbgu_puts("Data Access Violation \n");
			 if(SCB->CFSR & SCB_CFSR_MEMFAULTSR_MUNSTKERR_MASK)		dbgu_puts("MemManage Fault on Unstacking \n");
			 if(SCB->CFSR & SCB_CFSR_MEMFAULTSR_MSTKERR_MASK)		dbgu_puts("MemManage Fault on Stacking  \n");
			 if(SCB->CFSR & SCB_CFSR_MEMFAULTSR_MLSPERR_MASK)		dbgu_puts("MemManage Fault occurred during Floating-point \n");
			 if(SCB->CFSR & SCB_CFSR_MEMFAULTSR_MMARVALID_MASK)		dbgu_puts("Fault Address Register (MMFAR) valid  \n");
		}
		
	  }
	  uart_clear_tx_buffer((Uart*)BASE_DBGU_UART);

	while (1) {
		ATSAME70_PIO_CfgOutput(LED0_PORT,LED0);	//blink, blink, blink, ...
		ATSAME70_PIO_ClearOutput(LED0_PORT, LED0);
		delayms(100);
		ATSAME70_PIO_SetOutput(LED0_PORT, LED0);
		delayms(100);
	}
}
