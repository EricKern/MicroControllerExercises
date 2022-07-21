#ifndef LIB_ATSAME70_H
#define LIB_ATSAME70_H


#include "sam.h"
#include "dbgu.h"

//spio pio;
#define ATSAME70_BASE_PIOA    PIOA 
#define ATSAME70_BASE_PIOB    PIOB 
#define ATSAME70_BASE_PIOC    PIOC 
#define ATSAME70_BASE_PIOD    PIOD 
#define ATSAME70_BASE_PIOE    PIOE  
#define ATSAME70_BASE_DBGU    USART1 



static inline void ATSAME70_PIO_CfgOutput(
Pio *pPio, // \arg pointer to a PIO controller
unsigned long pioEnable) // \arg PIO to be enabled
{
	pPio->PIO_PER = pioEnable; // Set in PIO mode
	pPio->PIO_OER = pioEnable; // Configure in Output
}


static inline void ATSAME70_PIO_CfgInput(
Pio *pPio, // \arg pointer to a PIO controller
unsigned long pioEnable) // \arg PIO to be enabled
{
	pPio->PIO_PER = pioEnable; // Set in PIO mode
	pPio->PIO_ODR = pioEnable; // Configure in Input
}


static inline void ATSAME70_PIO_EnOutput(
Pio *pPio, // \arg pointer to a PIO controller
unsigned long pioEnable) // \arg PIO to be enabled
{
	pPio->PIO_PER = pioEnable; // Set in PIO mode
}

static inline void ATSAME70_PIO_DisOutput(
Pio *pPio, // \arg pointer to a PIO controller
unsigned long pioDisable) // \arg PIO to be enabled
{
	pPio->PIO_PDR = pioDisable; // Set in PIO mode
}


static inline void ATSAME70_PIO_SetOutput(
Pio *pPio, // \arg pointer to a PIO controller
unsigned long flag) // \arg output to be set
{
	pPio->PIO_SODR = flag;
}


static inline void ATSAME70_PIO_ClearOutput(
Pio *pPio, // arg pointer to a PIO controller
unsigned long flag) // arg output to be cleared
{
	pPio->PIO_CODR = flag;
}

static inline unsigned int ATSAME70_PIO_GetInput( // \return PIO input
Pio *pPio) // \arg pointer to a PIO controller
{
	return pPio->PIO_PDSR;
}

static inline void ATSAME70_PIO_Pulldown_Enable(
Pio *pPio, // arg pointer to a PIO controller
unsigned long flag) // arg output to be cleared
{
	pPio->PIO_PPDER = flag;
}

static inline void ATSAME70_PIO_Pulldown_Disable(
Pio *pPio, // arg pointer to a PIO controller
unsigned long flag) // arg output to be cleared
{
	pPio->PIO_PPDDR = flag;
}

static inline void ATSAME70_PIO_Pullup_Enable(
Pio *pPio, // arg pointer to a PIO controller
unsigned long flag) // arg output to be cleared
{
	pPio->PIO_PUER = flag;
}

static inline void ATSAME70_PIO_Pullup_Disable(
Pio *pPio, // arg pointer to a PIO controller
unsigned long flag) // arg output to be cleared
{
	pPio->PIO_PUDR = flag;
}

static inline void ATSAME70_PIO_Slow_Clock_Divider(
Pio *pPio, // arg pointer to a PIO controller
unsigned long flag) // arg output to be cleared
{
	pPio->PIO_SCDR = flag;
}

static inline void ATSAME70_PIO_Slow_Clock_Enable(
Pio *pPio, // arg pointer to a PIO controller
unsigned long flag) // arg output to be cleared
{
	pPio->PIO_IFSCER = flag;
}

static inline void ATSAME70_PIO_Input_Filter_Enable(
Pio *pPio, // arg pointer to a PIO controller
unsigned long flag) // arg output to be cleared
{
	pPio->PIO_IFER = flag;
}

static inline void ATSAME70_PIO_Edge_Select(
Pio *pPio, // arg pointer to a PIO controller
unsigned long flag) // arg output to be cleared
{
	pPio->PIO_ESR = flag;
}

static inline void ATSAME70_PIO_Level_Select(
Pio *pPio, // arg pointer to a PIO controller
unsigned long flag) // arg output to be cleared
{
	pPio->PIO_LSR = flag;
}

static inline void ATSAME70_PIO_Falling_Edge_Low_level_Select(
Pio *pPio, // arg pointer to a PIO controller
unsigned long flag) // arg output to be cleared
{
	pPio->PIO_FELLSR = flag;
}

static inline void ATSAME70_PIO_Raising_Edge_High_level_Select(
Pio *pPio, // arg pointer to a PIO controller
unsigned long flag) // arg output to be cleared
{
	pPio->PIO_REHLSR = flag;
}

static inline void ATSAME70_PIO_Interrupt_Enable(
Pio *pPio, // arg pointer to a PIO controller
unsigned long flag) // arg output to be cleared
{
	pPio->PIO_IER = flag;
}

static inline void ATSAME70_PIO_Interrupt_Disable(
Pio *pPio, // arg pointer to a PIO controller
unsigned long flag) // arg output to be cleared
{
	pPio->PIO_IDR = flag;
}

static inline void ATSAME70_PIO_Interrupt_Additional_Modes_Enable(
Pio *pPio, // arg pointer to a PIO controller
unsigned long flag) // arg output to be cleared
{
	pPio->PIO_AIMER = flag;
}

static inline unsigned int ATSAME70_PIO_Get_Interrupt_Mask( // \return PIO input
Pio *pPio) // \arg pointer to a PIO controller
{
	return pPio->PIO_IMR;
}

static inline unsigned int ATSAME70_PIO_Get_Interrupt_Status( // \return PIO input
Pio *pPio) // \arg pointer to a PIO controller
{
	return pPio->PIO_ISR;
}

static inline void ATSAME70_MATRIX_CCFG_SYSIO(
Matrix *pMatrix, // arg pointer to a Matrix controller
unsigned long flag) // register value
{
	pMatrix->CCFG_SYSIO = flag;
}

//typedef uint32_t ioport_mode_t;
//typedef uint32_t ioport_pin_t;
//typedef uint32_t ioport_port_t;
//typedef uint32_t ioport_port_mask_t;

//uint32_t pio_get_pin_group_mask(uint32_t ul_pin);
//Pio *pio_get_pin_group(uint32_t ul_pin);
//uint32_t pio_get_pin_group_id(uint32_t ul_pin);
//void pio_enable_pin_interrupt(uint32_t ul_pin);

//#define IOPORT_CREATE_PIN(port, pin) ((IOPORT_ ## port) * 32 + (pin))
//#define IOPORT_BASE_ADDRESS (uintptr_t)PIOA
//#define IOPORT_PIO_OFFSET   ((uintptr_t)PIOB - (uintptr_t)PIOA)

enum ioport_sense {
	IOPORT_SENSE_BOTHEDGES, /*!< IOPORT sense both rising and falling edges */
	IOPORT_SENSE_FALLING,   /*!< IOPORT sense falling edges */
	IOPORT_SENSE_RISING,    /*!< IOPORT sense rising edges */
	IOPORT_SENSE_LEVEL_LOW, /*!< IOPORT sense low level  */
	IOPORT_SENSE_LEVEL_HIGH,/*!< IOPORT sense High level  */
};

static inline void ioport_set_pin_sense_mode(Pio *pPio,uint32_t pin, enum ioport_sense pin_sense)
{
	
	/*   AIMMR    ELSR    FRLHSR    pin sense
	 *       0       X         X    IOPORT_SENSE_BOTHEDGES (Default)
	 *       1       0         0    IOPORT_SENSE_FALLING
	 *       1       0         1    IOPORT_SENSE_RISING
	 *       1       1         0    IOPORT_SENSE_LEVEL_LOW
	 *       1       1         1    IOPORT_SENSE_LEVEL_HIGH
	 */
	switch(pin_sense) {
	case IOPORT_SENSE_LEVEL_LOW:
		pPio->PIO_LSR = 0x1 << (pin & 0x1f);   //level select register
		pPio->PIO_FELLSR = 0x1 << (pin & 0x1f);  //falling level/low level select register
		break;
	case IOPORT_SENSE_LEVEL_HIGH:
		pPio->PIO_LSR = 0x1 << (pin & 0x1f);
		pPio->PIO_REHLSR = 0x1 << (pin & 0x1f);
		break;
	case IOPORT_SENSE_FALLING:
		pPio->PIO_ESR = 0x1 << (pin & 0x1f);
		pPio->PIO_FELLSR = 0x1 << (pin & 0x1f);
		break;
	case IOPORT_SENSE_RISING:
		pPio->PIO_ESR = 0x1 << (pin & 0x1f);
		pPio->PIO_REHLSR = 0x1 << (pin & 0x1f);
		break;
	default:
		pPio->PIO_AIMDR = 0x1 << (pin & 0x1f);
		return;
	}
	pPio->PIO_AIMER = 0x1 << (pin & 0x1f);
	
}

/**  Enable additional interrupt modes. */
#define PIO_IT_AIME                 (1 << 4)

/**  Interrupt High Level/Rising Edge detection is active. */
#define PIO_IT_RE_OR_HL             (1 << 5)
/**  Interrupt Edge detection is active. */
#define PIO_IT_EDGE                 (1 << 6)

static inline void pio_configure_interrupt(Pio *p_pio, const uint32_t ul_mask, const uint32_t ul_attr)
{
	/* Configure additional interrupt mode registers. */
	if (ul_attr & PIO_IT_AIME) {
		/* Enable additional interrupt mode. */
		p_pio->PIO_AIMER = ul_mask;

		/* If bit field of the selected pin is 1, set as
		   Rising Edge/High level detection event. */
		if (ul_attr & PIO_IT_RE_OR_HL) {
			/* Rising Edge or High Level */
			p_pio->PIO_REHLSR = ul_mask;
		} else {
			/* Falling Edge or Low Level */
			p_pio->PIO_FELLSR = ul_mask;
		}

		/* If bit field of the selected pin is 1, set as
		   edge detection source. */
		if (ul_attr & PIO_IT_EDGE) {
			/* Edge select */
			p_pio->PIO_ESR = ul_mask;
		} else {
			/* Level select */
			p_pio->PIO_LSR = ul_mask;
		}
	} else {
		/* Disable additional interrupt mode. */
		p_pio->PIO_AIMDR = ul_mask;
	}
}

/*
void pio_enable_pin_interrupt(Pio *pPio, uint32_t ul_pin)
{
	pPio->PIO_IER = 0x1 << (ul_pin & 0x1f);
}

void pio_disable_pin_interrupt(Pio *pPio, uint32_t ul_pin)
{
	pPio->PIO_IDR = 0x1 << (ul_pin & 0x1f);
}
*/
#endif