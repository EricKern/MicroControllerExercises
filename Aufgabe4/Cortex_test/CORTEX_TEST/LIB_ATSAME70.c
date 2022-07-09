
#include "sam.h"
#include "dbgu.h"
#include "board_cortex7.h"

__inline void ATSAME70_PIO_CfgOutput(
Pio *pPio, // \arg pointer to a PIO controller
unsigned long pioEnable) // \arg PIO to be enabled
{
	pPio->PIO_PER = pioEnable; // Set in PIO mode
	pPio->PIO_OER = pioEnable; // Configure in Output
}

__inline void ATSAME70_PIO_CfgInput(
Pio *pPio, // \arg pointer to a PIO controller
unsigned long pioEnable) // \arg PIO to be enabled
{
	pPio->PIO_PER = pioEnable; // Set in PIO mode
	pPio->PIO_ODR = pioEnable; // Configure in Input
}


__inline void ATSAME70_PIO_EnOutput(
Pio *pPio, // \arg pointer to a PIO controller
unsigned long pioEnable) // \arg PIO to be enabled
{
	pPio->PIO_PER = pioEnable; // Set in PIO mode
}

__inline void ATSAME70_PIO_DisOutput(
Pio *pPio, // \arg pointer to a PIO controller
unsigned long pioDisable) // \arg PIO to be enabled
{
	pPio->PIO_PDR = pioDisable; // Set in PIO mode
}


//*----------------------------------------------------------------------------
//* \fn AT91F_PIO_SetOutput
//* \brief Set to 1 output PIO
//*----------------------------------------------------------------------------
__inline void ATSAME70_PIO_SetOutput(
Pio *pPio, // \arg pointer to a PIO controller
unsigned long flag) // \arg output to be set
{
	pPio->PIO_SODR = flag;
}

//*----------------------------------------------------------------------------
//* \fn AT91F_PIO_ClearOutput
//* \brief Set to 0 output PIO
//*----------------------------------------------------------------------------
__inline void ATSAME70_PIO_ClearOutput(
Pio *pPio, // arg pointer to a PIO controller
unsigned long flag) // arg output to be cleared
{
	pPio->PIO_CODR = flag;
}


// \ATSAME70_PIO_CfgPeriph: brief Enable pins to be drived by peripheral
//periphAEnable periphBEnable periphCEnable periphDEnable -> PIO_ABCDSR1 PIO_ABCDSR2
//     0              0             0             0       ->       0          0
//     1              X             X             X       ->       0          0
//     0              1             X             X       ->       1          0
//     0              0             1             X       ->       0          1
//     0              0             0             1       ->       1          1

__inline void ATSAME70_PIO_CfgPeriph(
Pio *pPio, // \arg pointer to a PIO controller
unsigned long periphAEnable, // arg PERIPH A to enable -> PIO_ABCDSR1 PIO_ABCDSR2 = 00
unsigned long periphBEnable, // arg PERIPH B to enable -> PIO_ABCDSR1 PIO_ABCDSR2 = 10
unsigned long periphCEnable, // arg PERIPH C to enable -> PIO_ABCDSR1 PIO_ABCDSR2 = 01
unsigned long periphDEnable) // arg PERIPH D to enable -> PIO_ABCDSR1 PIO_ABCDSR2 = 11

{
	pPio->PIO_PDR = periphAEnable | periphBEnable | periphCEnable | periphDEnable;
	pPio->PIO_ABCDSR[0] = ((~periphAEnable) & periphBEnable)
	| ((~periphAEnable) & (~periphBEnable) & (~periphCEnable) & periphDEnable);
	pPio->PIO_ABCDSR[1] = ((~periphAEnable) & (~periphBEnable) & periphCEnable)
	| ((~periphAEnable) & (~periphBEnable) & (~periphCEnable) & periphDEnable);

	pPio->PIO_PDR = (periphAEnable | periphBEnable | periphCEnable| periphDEnable); // Set in Periph mode
}

