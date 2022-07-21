/*
** dbgu.c
*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sam.h"
#include "device_startup/system_same70.h"
#include "LIB_ATSAME70.h"
#include "board_cortex7.h"
#include "dbgu.h"
#include "fifo.h"
#include "interrupts.h"
#include "xdmac.h"

#define MAX_RX_TIMEOUT          131071

#define ATSAME70_BASE_MATRIX    MATRIX

#define DBGU_RX_BUFFER_SIZE	64
char dbgu_rx_buffer[DBGU_RX_BUFFER_SIZE];
uint32_t dbgu_rx_buffer_fill = 0;
uint8_t uart_active = false;


void UART_SetBaudrate(Uart *pUart,
uint8_t OverSamp,
uint32_t baudrate,
uint32_t masterClock)
{
	unsigned int CD, FP, BaudError, ActualBaudRate;
	CD = 1;
	FP = 1;
	
	// Configure baudrate
	BaudError = 10;
	OverSamp = 0;
	pUart->UART_WPMR = 0x55534100;
	
	while (BaudError > 5)
	{
		CD = (masterClock / (baudrate * 8 * (2 - OverSamp)));
		FP = ((masterClock / (baudrate * (2 - OverSamp))) - CD * 8);
		ActualBaudRate = (masterClock / (CD * 8 + FP)) / (2 - OverSamp);
		BaudError = (100 - ((baudrate * 100 / ActualBaudRate)));
		if (BaudError > 5)
		{
			OverSamp++;
		}
	}

	pUart->UART_BRGR = (UART_BRGR_CD(CD));
	pUart->UART_BRGR = CD;
	// Configure OverSamp
	pUart->UART_MR |= (OverSamp << 19);
}

void UART_Configure(Uart *pUart,
					// uint32_t mode,
					 uint32_t baudrate,
					 uint32_t masterClock)
{
	PMC_EnablePeripheral(UART_ID);
	pUart->UART_MR = UART_MR_PAR_NO;  //8-Bit, no parity
	/* Reset and disable receiver & transmitter*/
	pUart->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX | UART_CR_RXDIS | UART_CR_TXDIS | UART_CR_RSTSTA;
	pUart->UART_IDR = 0xFFFFFFFF;
	UART_SetBaudrate(pUart, 0, baudrate, masterClock); // Configure baudrate
	/* Enable receiver and transmitter */
	pUart->UART_CR = UART_CR_RXEN | UART_CR_TXEN;
/*
	// Disable buffering for printf(). 
#if (defined (__GNUC__) && !defined (__SAMBA__))
	setvbuf(stdout, (char *)NULL, _IONBF, 0);
#endif
*/
}

inline unsigned int ATSAME70_UART_TxReady (
Uart *pUART ) // \arg pointer to a USART controller
{
	return (pUART->UART_SR & UART_IDR_TXRDY);
}

inline unsigned int ATSAME70_UART_RxReady (
Uart *pUART ) // \arg pointer to a USART controller
{
	return (pUART->UART_SR & UART_IDR_RXRDY);
}


#ifdef UART_FIFO_INTERRUPT
uint8_t  uart_fifo_tx_buffer[DBGU_UART_TX_FIFO_SIZE];
uint8_t  uart_fifo_rx_buffer[DBGU_UART_RX_FIFO_SIZE];

sfifo uart_tx_fifo;
sfifo uart_rx_fifo;

void enable_dbgu_uart_interrupt (void)
{
	NVIC_EnableIRQ(dbgu_uart_IRQn);
}

void disable_dbgu_uart_interrupt (void)
{
	NVIC_DisableIRQ(dbgu_uart_IRQn);
}

void  dbgu_uart_irq_handler(void) //uart_irq_handler
{
	//ATSAME70_PIO_ClearOutput(PIO06_PORT,PIO06);
	char c;
//	uint32_t flags = BASE_UART->UART_SR;
	if (BASE_DBGU_UART->UART_SR & UART_SR_TXRDY)						//tx interrupt?
	{
		if ((fifo_Out(&uart_tx_fifo,(uint8_t*) &c)) == FIFO_SUCCESS) //check char in fifo buffer
		{
			BASE_DBGU_UART->UART_THR = c;						//read char from fifo and write to transmit register
			while (BASE_DBGU_UART->UART_SR & UART_SR_TXRDY) {;}
		//	delay20ns(5);
		}
		else												//if no char in fifo buffer
		{
			BASE_DBGU_UART->UART_IDR = UART_IDR_TXRDY;			//disable tx interrupt
			NVIC_ClearPendingIRQ(dbgu_uart_IRQn);
		}
	}
	
	if (BASE_DBGU_UART->UART_SR & UART_SR_RXRDY)
	{
		
		fifo_In(&uart_rx_fifo, BASE_DBGU_UART->UART_RHR);
		while (BASE_DBGU_UART->UART_SR & UART_SR_RXRDY) {;}
		//delay20ns(3);
	}

	//ATSAME70_PIO_SetOutput(PIO06_PORT,PIO06);
}

#endif

#ifdef UART_TX_DMA
uint8_t dma_uart_tx_channel;
uint8_t dma_uart_tx_data_buffer1[(DMA_TX_DATA_BUFFER_SIZE + DCACHE_LINE_SIZE)*2];  //+ DCACHE_LINE_SIZE for cache alignment
uint8_t* dma_uart_tx_data_buffer;   ////pointer for dma_uart_tx_data_buffer1[] aligned to cache line size
uint32_t dma_uart_tx_data_buffer_init;
uint16_t dma_uart_tx_data_buffer_index = 0;
uint16_t dma_uart_tx_data_buffer_timeout = 0;
uint16_t offset_dma_uart_tx_data_buffer_index = 0;
#endif



void dbgu_uart_init(void)
{
	ATSAME70_BASE_MATRIX->CCFG_SYSIO = ATSAME70_BASE_MATRIX->CCFG_SYSIO | CCFG_SYSIO_SYSIO4;  // Open PIO for DBGU 
	UART_Configure(BASE_DBGU_UART, ATSAME70_DBGU_BAUD, BOARD_MCK);
	dbgu_rx_buffer_fill = 0;   // clear rx buffer 
	uart_active = true;
	
#ifdef UART_TX_DMA
	PMC_EnablePeripheral(ID_XDMAC);
	dma_uart_tx_channel = get_free_dma_channel();
	XDMAC->XDMAC_CHID[dma_uart_tx_channel].XDMAC_CC = XDAM_CONFIGURATION_TX_DBGU_UART;
	XDMAC->XDMAC_CHID[dma_uart_tx_channel].XDMAC_CDA  = (uint32_t) &(BASE_DBGU_UART->UART_THR);  //destination address
	dma_uart_tx_data_buffer_index = 0;
	offset_dma_uart_tx_data_buffer_index = 0;
	
	//dma_uart_tx_data_buffer_init = (uint32_t) dma_uart_tx_data_buffer1;
	//dma_uart_tx_data_buffer_init += DCACHE_LINE_SIZE - dma_uart_tx_data_buffer_init % DCACHE_LINE_SIZE;  //calculate pointer align
	//dma_uart_tx_data_buffer = (uint8_t*) dma_uart_tx_data_buffer_init;   //align pointer to cache line size
	dma_uart_tx_data_buffer = (uint8_t*) align_pointer_dcache_line_size((uint8_t*)dma_uart_tx_data_buffer1);
	//printf("\ndma uart tx buffer align: %lx   %lx\n",dma_uart_tx_data_buffer_init, dma_uart_tx_data_buffer_test);
	
	//printf("uart transmit DMA channel: %d XDMAC: %lx\n",dma_uart_tx_channel,XDMAC->XDMAC_CHID[dma_uart_tx_channel].XDMAC_CC);
	
#endif

	
#ifdef UART_FIFO_INTERRUPT
	//uart_fifo_init(BASE_UART);
	fifo_init(&uart_tx_fifo,(uint8_t*) &uart_fifo_tx_buffer, DBGU_UART_TX_FIFO_SIZE);
	fifo_init(&uart_rx_fifo,(uint8_t*) &uart_fifo_rx_buffer, DBGU_UART_RX_FIFO_SIZE);
	NVIC_SetPriority(dbgu_uart_IRQn , dbgu_uart_IRQ_priority);
	NVIC_DisableIRQ(dbgu_uart_IRQn);
	NVIC_ClearPendingIRQ(dbgu_uart_IRQn);
	BASE_DBGU_UART->UART_IDR = 0xffffffff;     //disable all uart interrupts
	BASE_DBGU_UART->UART_IER = UART_IDR_TXRDY + UART_IDR_RXRDY;  //enable tx + rx interrupt
//	BASE_DBGU_UART->UART_IER = UART_IDR_RXRDY;  //only rx interrupt
	NVIC_EnableIRQ(dbgu_uart_IRQn);
#endif
		
	BASE_DBGU_UART->UART_CR = UART_CR_RXEN | UART_CR_TXEN;   // Enable Transmitter & receiver
	uart_active = false;
	dbgu_clear();
	dbgu_puts("\n");
	
	
}

void dbgu_disable(void)
{
	while ((BASE_DBGU_UART->UART_SR & UART_SR_TXEMPTY) == 0);
	BASE_DBGU_UART->UART_CR = UART_CR_RXDIS | UART_CR_TXDIS;
}

#ifdef UART_TX_DMA

void UART_PutChar(Uart *pUart, uint8_t c)
{
	//ATSAME70_PIO_ClearOutput(PIO06_PORT,PIO06);
	uart_active = true;
	if(c == '\n') UART_PutChar(pUart,'\r');
	if ((XDMAC->XDMAC_GS & (1 << dma_uart_tx_channel)) != 0)  //DMA active
	{
		if (dma_uart_tx_data_buffer_index < (DMA_TX_DATA_BUFFER_SIZE-1))  //check space in transmit buffer: DMA buffer full?
		{
			dma_uart_tx_data_buffer[dma_uart_tx_data_buffer_index+offset_dma_uart_tx_data_buffer_index] = c; //write to DMA buffer
			dma_uart_tx_data_buffer_index++;
		}
		else  //if dma buffer full!
		{
			dma_uart_tx_data_buffer[dma_uart_tx_data_buffer_index+offset_dma_uart_tx_data_buffer_index] = c;  //write in transmit buffer
			dma_uart_tx_data_buffer_index++;		
			SCB_CleanDCache_by_Addr ((uint32_t*) &dma_uart_tx_data_buffer[offset_dma_uart_tx_data_buffer_index], (DMA_TX_DATA_BUFFER_SIZE) * sizeof(*dma_uart_tx_data_buffer) );  //data cache coherence!				
			while ((XDMAC->XDMAC_GS & (1 << dma_uart_tx_channel)) != 0)  {;}						//wait until DMA finished
			XDMAC->XDMAC_CHID[dma_uart_tx_channel].XDMAC_CSA  = (uint32_t) &dma_uart_tx_data_buffer[offset_dma_uart_tx_data_buffer_index];   //DMA source pointer -> transmit buffer
			XDMAC->XDMAC_CHID[dma_uart_tx_channel].XDMAC_CUBC = dma_uart_tx_data_buffer_index;		//data size in transmit buffer
			XDMAC->XDMAC_GE =  (1 << dma_uart_tx_channel);											//start DMA
			dma_uart_tx_data_buffer_index = 0;
			if (offset_dma_uart_tx_data_buffer_index == 0) offset_dma_uart_tx_data_buffer_index = DMA_TX_DATA_BUFFER_SIZE;       //change to second transmit buffer
			else offset_dma_uart_tx_data_buffer_index = 0;
		}
	}
	else  //DMA inactive
	{
		dma_uart_tx_data_buffer[dma_uart_tx_data_buffer_index+offset_dma_uart_tx_data_buffer_index] = c;  //write in transmit buffer
		dma_uart_tx_data_buffer_index++;	
		SCB_CleanDCache_by_Addr ((uint32_t*) &dma_uart_tx_data_buffer[offset_dma_uart_tx_data_buffer_index], (DMA_TX_DATA_BUFFER_SIZE) * sizeof(*dma_uart_tx_data_buffer)); //data cache coherence!	
		XDMAC->XDMAC_CHID[dma_uart_tx_channel].XDMAC_CSA  = (uint32_t) &dma_uart_tx_data_buffer[offset_dma_uart_tx_data_buffer_index];  //DMA source pointer
		XDMAC->XDMAC_CHID[dma_uart_tx_channel].XDMAC_CUBC  = dma_uart_tx_data_buffer_index;     //transmit buffer size	
		XDMAC->XDMAC_GE =  (1 << dma_uart_tx_channel);											//start DMA
		dma_uart_tx_data_buffer_index = 0;
		if (offset_dma_uart_tx_data_buffer_index == 0) offset_dma_uart_tx_data_buffer_index = DMA_TX_DATA_BUFFER_SIZE;       //change to second transmit buffer
		else offset_dma_uart_tx_data_buffer_index = 0;
	}
	//ATSAME70_PIO_SetOutput(PIO06_PORT,PIO06);
	uart_active = false;
}

void uart_clear_tx_buffer(Uart *pUart)    //-> timer_irq_handler
{
	if ((dma_uart_tx_data_buffer_index > 0) & (uart_active == false))             //tx data in buffer? + UART_PutChar inactive? 
	{
		SCB_CleanDCache_by_Addr ((uint32_t*) &dma_uart_tx_data_buffer[offset_dma_uart_tx_data_buffer_index], (DMA_TX_DATA_BUFFER_SIZE) * sizeof(*dma_uart_tx_data_buffer) );   //data cache coherence!
		while ((XDMAC->XDMAC_GS & (1 << dma_uart_tx_channel)) != 0)  {;}												//wait until DMA finished
		XDMAC->XDMAC_CHID[dma_uart_tx_channel].XDMAC_CSA  = (uint32_t) &dma_uart_tx_data_buffer[offset_dma_uart_tx_data_buffer_index];   //DMA source pointer
		XDMAC->XDMAC_CHID[dma_uart_tx_channel].XDMAC_CUBC  = dma_uart_tx_data_buffer_index;								//transmit buffer size
		XDMAC->XDMAC_GE =  (1 << dma_uart_tx_channel);																	//start DMA
		dma_uart_tx_data_buffer_index = 0;
		if (offset_dma_uart_tx_data_buffer_index == 0) offset_dma_uart_tx_data_buffer_index = DMA_TX_DATA_BUFFER_SIZE;  //change to second transmit buffer
		else offset_dma_uart_tx_data_buffer_index = 0;
	}
}  

uint8_t UART_GetChar(Uart *pUart)
{
	while ((pUart->UART_SR & UART_SR_RXRDY) == 0);
	return pUart->UART_RHR;
}

int dbgu_getc(char *c)
{
	if(!ATSAME70_UART_RxReady((Uart*)BASE_DBGU_UART)) {
		return 0;
	}

	*c = UART_GetChar((Uart*)BASE_DBGU_UART);
	return 1;
}

uint8_t UART_Get_RXRDY(Uart *pUart)
{
	return (uint8_t) (pUart->UART_SR & UART_SR_RXRDY);
}
#endif


//brief  Sends one packet of data through the specified USART peripheral. This
//function operates synchronously, so it only returns when the data has been actually sent.
//param pUsart  Pointer to an USART peripheral.
//param c  Character to send
#ifdef UART_FIFO_INTERRUPT

void UART_PutChar(Uart *pUart, uint8_t c)				//uart tx interrupts on!!!
{
	uint8_t fifo_data;
	uint32_t dbgutimeout = 0;
	if(c == '\n') UART_PutChar(pUart,'\r');
	//uint8_t fifo_status =  FIFO_FAIL;
	uart_active = true;
	if (((pUart->UART_SR) & UART_SR_TXRDY) != 0)         //check transmitter status
	{
		pUart->UART_THR = c;							 //if transmitter ready, write char to transmit register
	}	
	else
	{
		(pUart->UART_IER) = UART_IER_TXRDY;				//enable TXrdy interrupt
		while (fifo_In(&uart_tx_fifo,c) == FIFO_FAIL)	//if fifo full, wait until interrupt reads fifo
		{  
			dbgutimeout ++;
			delayus(1);													  //problem: delay calibrated?
			if (dbgutimeout > UART_TIMEOUT_US)                            //no interrupts? trap?
			{
				while (((pUart->UART_SR) & UART_SR_TXRDY) == 0) {;}       //check transmit register
				while ((fifo_Out(&uart_tx_fifo,(uint8_t*) &fifo_data)) == FIFO_SUCCESS) //read fifo buffer
				BASE_DBGU_UART->UART_THR = fifo_data;								    //+ send data
				fifo_In(&uart_tx_fifo,c);                                               //write fifo buffer
				break;											 	
			}
		}
	}
	uart_active = false;
}

uint8_t UART_GetChar(Uart *pUart)
{
	uint8_t c;
	while ((fifo_Out(&uart_rx_fifo,(uint8_t*) &c)) != FIFO_SUCCESS) {;}
	return c;
}

int dbgu_getc(char *c)
{
	if ((fifo_Out(&uart_rx_fifo,(uint8_t*) c)) == FIFO_SUCCESS) {return 1;}
	else return 0;
}

uint8_t UART_Get_RXRDY(Uart *pUart)
{
	if (fifo_status(&uart_rx_fifo) == FIFO_SUCCESS) return 1;
	else return 0;
}


void uart_clear_tx_buffer(Uart *pUart)   //only if dbgu interrupt not possible: Hard fault handler ...
{
	uint8_t c;
	if ((uart_tx_fifo.size == DBGU_UART_TX_FIFO_SIZE ) & (uart_active == false)) //check fifo valid + uart inactive???
	{
		while ((fifo_Out(&uart_tx_fifo,(uint8_t*) &c)) == FIFO_SUCCESS) //check fifo buffer
		{
			while ((pUart->UART_SR & UART_SR_TXEMPTY) == 0) {;}
			pUart->UART_THR = c;						//read char from fifo and write to transmit register
		}
	}
}
#endif

#ifdef UART_NO_DMA_NO_INTERRUPT
void UART_PutChar(Uart *pUart, uint8_t c)		//uart tx interrupts off!!!
{
	if(c == '\n') UART_PutChar(BASE_DBGU_UART,'\r');
	while ((pUart->UART_SR & UART_SR_TXEMPTY) == 0);   // Wait for the transmitter to be ready
	pUart->UART_THR = c;  // Send character
}


void uart_clear_tx_buffer(Uart *pUart)    //-> timer_irq_handler
{
	while ((pUart->UART_SR & UART_SR_TXEMPTY) == 0);
}
#endif

#ifdef UART_NO_DMA_NO_INTERRUPT
uint8_t UART_Get_RXRDY(Uart *pUart)
{
	return (uint8_t) (pUart->UART_SR & UART_SR_RXRDY);
}

int dbgu_getc(char *c)
{
	if(!ATSAME70_UART_RxReady((Uart*)BASE_DBGU_UART)) {
		return 0;
	}

	*c = UART_GetChar((Uart*)BASE_DBGU_UART);
	return 1;
}

uint8_t UART_GetChar(Uart *pUart)
{
	while ((pUart->UART_SR & UART_SR_RXRDY) == 0);
	return pUart->UART_RHR;
}

#endif




void dbgu_puts(const char *s)
{
	while(*s) {
		UART_PutChar(BASE_DBGU_UART, *s++);
	}
}

void dbgu_tick(void)
{
	for(;;) {
		char c;
		if(!dbgu_getc(&c)) return;
		if(c == 10) continue;
		
		if(c == 8) {
			if(dbgu_rx_buffer_fill > 0) {
				dbgu_rx_buffer_fill--;
				UART_PutChar(BASE_DBGU_UART,8);
				UART_PutChar(BASE_DBGU_UART,' ');
				UART_PutChar(BASE_DBGU_UART,8);
			}
		}
		else if(c == 13) {
			UART_PutChar(BASE_DBGU_UART,10);
			UART_PutChar(BASE_DBGU_UART,13);
			dbgu_rx_buffer[dbgu_rx_buffer_fill] = 0;
			dbgu_command(dbgu_rx_buffer);
			dbgu_rx_buffer_fill = 0;
		}
		else {
			if(dbgu_rx_buffer_fill < (DBGU_RX_BUFFER_SIZE-1)) {
				dbgu_rx_buffer[dbgu_rx_buffer_fill++] = c;
				UART_PutChar(BASE_DBGU_UART,c);
			}
		}
	}
}

void dbgu_clear(void)
{
	UART_PutChar(BASE_DBGU_UART,27);		//dbgu_putc(27);
	UART_PutChar(BASE_DBGU_UART,'[');		//dbgu_putc('[');
	UART_PutChar(BASE_DBGU_UART,'2');		//dbgu_putc('2');
	UART_PutChar(BASE_DBGU_UART,'J');		//dbgu_putc('J');
}


/**
 * \brief Enables or disables the transmitter of an USART peripheral.
 *
 *
 * \param pUsart  Pointer to an USART peripheral
 * \param enabled  If true, the transmitter is enabled; otherwise it is
 * disabled.
 */
void USART_SetTransmitterEnabled(Usart *pUsart, uint8_t enabled)
{
	if (enabled)
		pUsart->US_CR = US_CR_TXEN;
	else
		pUsart->US_CR = US_CR_TXDIS;
}

/**
 * \brief Disables the Receiver of an USART peripheral.
 *
 * \param pUsart  Pointer to an USART peripheral
 */
void USART_DisableRx(Usart *pUsart)
{

	pUsart->US_CR = US_CR_RXDIS;
}

/**
 * \brief Disables the transmitter of an USART peripheral.
 *
 * \param pUsart  Pointer to an USART peripheral
 */
void USART_DisableTx(Usart *pUsart)
{
	pUsart->US_CR =  US_CR_TXDIS;
}

/**
 * \brief Enables the Receiver of an USART peripheral.
 *
 * \param pUsart  Pointer to an USART peripheral
 */
void USART_EnableRx(Usart *pUsart)
{
	pUsart->US_CR = US_CR_RXEN;
}

/**
 * \brief Enables the transmitter of an USART peripheral
 *
 * \param pUsart  Pointer to an USART peripheral
 */
void USART_EnableTx(Usart *pUsart)
{
	pUsart->US_CR =  US_CR_TXEN;
}
/**
 * \brief Resets or disables the Receiver of an USART peripheral.
 *
 *
 * \param pUsart  Pointer to an USART peripheral
 */
void USART_ResetRx(Usart *pUsart)
{
	pUsart->US_CR = US_CR_RSTRX | US_CR_RXDIS;
}

/**
 * \brief resets and disables the transmitter of an USART peripheral.
 *
 *
 * \param pUsart  Pointer to an USART peripheral
 */
void USART_ResetTx(Usart *pUsart)
{
	pUsart->US_CR =  US_CR_RSTTX | US_CR_TXDIS;
}
/**
 * \brief Enables or disables the receiver of an USART peripheral
 *
 *
 * \param pUsart  Pointer to an USART peripheral
 * \param enabled  If true, the receiver is enabled; otherwise it is disabled.
 */
void USART_SetReceiverEnabled(Usart *pUsart, uint8_t enabled)
{
	if (enabled)
		pUsart->US_CR = US_CR_RXEN;
	else
		pUsart->US_CR = US_CR_RXDIS;
}

/**
 * \brief Enables or disables the Request To Send (RTS) of an USART peripheral
 *
 *
 * \param pUsart  Pointer to an USART peripheral
 * \param enabled  If true, the RTS is enabled (0); otherwise it is disabled.
 */
void USART_SetRTSEnabled(Usart *pUsart, uint8_t enabled)
{
	if (enabled)
		pUsart->US_CR = US_CR_RTSEN;
	else
		pUsart->US_CR = US_CR_RTSDIS;
}

/**
 * \brief Sends one packet of data through the specified USART peripheral. This
 * function operates synchronously, so it only returns when the data has been
 * actually sent.
 *
 *
 * \param pUsart  Pointer to an USART peripheral.
 * \param data  Data to send including 9nth bit and sync field if necessary (in
 *        the same format as the US_THR register in the datasheet).
 * \param timeOut  Time out value (0 = no timeout).
 */
void USART_Write(Usart *pUsart, uint16_t data, volatile uint32_t timeOut)
{
	if (timeOut == 0) {
		while ((pUsart->US_CSR & US_CSR_TXEMPTY) == 0);
	} else {
		while ((pUsart->US_CSR & US_CSR_TXEMPTY) == 0) {
			if (timeOut == 0) {
				//TRACE_ERROR("USART_Write: Timed out.\n\r");
				return;
			}

			timeOut--;
		}
	}

	pUsart->US_THR = data;
}

/**
 * \brief  Reads and return a packet of data on the specified USART peripheral.
 * This function operates asynchronously, so it waits until some data has been
 * received.
 *
 * \param pUsart  Pointer to an USART peripheral.
 * \param timeOut  Time out value (0 -> no timeout).
 */
uint16_t USART_Read(Usart *pUsart, volatile uint32_t timeOut)
{
	if (timeOut == 0) {
		while ((pUsart->US_CSR & US_CSR_RXRDY) == 0);
	} else {
		while ((pUsart->US_CSR & US_CSR_RXRDY) == 0) {
			if (timeOut == 0) {
				//TRACE_ERROR("USART_Read: Timed out.\n\r");
				return 0;
			}

			timeOut--;
		}
	}

	return pUsart->US_RHR;
}

/**
 * \brief  Returns 1 if some data has been received and can be read from an
 * USART; otherwise returns 0.
 *
 * \param pUsart  Pointer to an USART instance.
 */
uint8_t USART_IsDataAvailable(Usart *pUsart)
{
	if ((pUsart->US_CSR & US_CSR_RXRDY) != 0)
		return 1;
	else
		return 0;
}

/**
 * \brief   Return 1 if a character can be read in USART
 * \param pUsart  Pointer to an USART peripheral.
 */
uint32_t USART_IsRxReady(Usart *pUsart)
{
	return (pUsart->US_CSR & US_CSR_RXRDY);
}

/**
 * \brief   Get present status
 * \param pUsart  Pointer to an USART peripheral.
 */
uint32_t USART_GetStatus(Usart *pUsart)
{
	return pUsart->US_CSR;
}

/**
 * \brief   Enable interrupt
 * \param pUsart  Pointer to an USART peripheral.
 * \param mode  Interrupt mode.
 */
void USART_EnableIt(Usart *pUsart, uint32_t mode)
{
	pUsart->US_IER = mode;
}

/**
 * \brief   Disable interrupt
 * \param pUsart  Pointer to an USART peripheral.
 * \param mode  Interrupt mode.
 */
void USART_DisableIt(Usart *pUsart, uint32_t mode)
{
	pUsart->US_IDR = mode;
}

/**
 * \brief   Return interrupt mask
 * \param pUsart  Pointer to an USART peripheral.
 */
uint32_t USART_GetItMask(Usart *pUsart)
{
	return pUsart->US_IMR;
}

/**
 * \brief  Reads and returns a character from the USART.
 *
 * \note This function is synchronous (i.e. uses polling).
 * \param pUsart  Pointer to an USART peripheral.
 * \return Character received.
 */
uint8_t USART_GetChar(Usart *pUsart)
{
	while ((pUsart->US_CSR & US_CSR_RXRDY) == 0);

	return pUsart->US_RHR;
}

/**
 * \brief  Enable Rx Timeout for USART.
 *
 * \param pUsart  Pointer to an USART peripheral.
 * \param Timeout  Timeout value
 * \return None
 */
void USART_EnableRecvTimeOut(Usart *pUsart, uint32_t Timeout)
{
	if (Timeout <= MAX_RX_TIMEOUT)
		pUsart->US_RTOR = Timeout;
	else if (Timeout == 0) {
		//TRACE_DEBUG("Timeout is disabled\n\r");
	} else {
		//TRACE_INFO_WP("\n\r");
		//TRACE_FATAL("Timeout value is out of range\n\r");
	}
}

/**
 * \brief  Enable Tx Timeout for USART.
 *
 * \param pUsart  Pointer to an USART peripheral.
 * \param TimeGaurd  TimeGaurd value
 * \return None
 */
void USART_EnableTxTimeGaurd(Usart *pUsart, uint32_t TimeGaurd)
{
	if (((pUsart->US_MR & US_MR_USART_MODE_LON) && TimeGaurd <= 16777215) ||
		 ((pUsart->US_MR & US_MR_USART_MODE_LON) && TimeGaurd <= 255))
		pUsart->US_TTGR = TimeGaurd;
//	else
		//TRACE_ERROR(" TimeGaurd Value is too big for mode");
}
/**
 * \brief  Acknowledge Rx timeout and sets to Idle or periodic repetitive state.
 *
 * \param pUsart  Pointer to an USART peripheral.
 * \param Periodic  If timeout is periodic or should wait for new char
 * \return None
 */
void USART_AcknowledgeRxTimeOut(Usart *pUsart, uint8_t Periodic)
{
	if (Periodic) {
		pUsart->US_CR = US_CR_RETTO;     // Restart timeout timer
	} else {
		// Puts USARt in Idle mode and waits for a char after timeout
		pUsart->US_CR = US_CR_STTTO;
	}
}
