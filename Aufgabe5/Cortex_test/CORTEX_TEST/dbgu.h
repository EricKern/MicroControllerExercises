/*
** dbgu.h
*/

#ifndef _DBGU_H_
#define _DBGU_H_

#include "sam.h"
#include "device_startup/system_same70.h"
#include "fifo.h"

//#define UART_TX_DMA  //use DMA 
#define UART_NO_DMA_NO_INTERRUPT
//#define UART_FIFO_INTERRUPT //use FIFO + Interrupt for UART

#ifdef  UART_TX_DMA
#ifdef  UART_NO_DMA_NO_INTERRUPT
#error  collision UART TX DMA / UART NO DMA NO INTERRUPT
#endif
#ifdef  UART_FIFO_INTERRUPT
#error  collision UART TX DMA / UART FIFO INTERRUPT
#endif
#endif

#ifdef  UART_NO_DMA_NO_INTERRUPT
#ifdef  UART_TX_DMA
#error  collision UART TX DMA / UART NO DMA NO INTERRUPT
#endif
#ifdef  UART_FIFO_INTERRUPT
#error  collision UART NO DMA NO INTERRUPT / UART FIFO INTERRUPT
#endif
#endif

#ifdef  UART_FIFO_INTERRUPT  
#ifdef  UART_TX_DMA
#error  collision UART TX DMA / UART_FIFO_INTERRUPT
#endif
#ifdef  UART_NO_DMA_NO_INTERRUPT
#error  collision UART NO DMA NO INTERRUPT / UART FIFO INTERRUPT
#endif
#endif

#define DBGU_UART_TX_FIFO_SIZE		32
#define DBGU_UART_RX_FIFO_SIZE		256
#define DMA_TX_DATA_BUFFER_SIZE		256     //modulo 32
#define DCACHE_LINE_SIZE   32

#define XDAM_CONFIGURATION_TX_DBGU_UART (XDMAC_CC_TYPE_PER_TRAN + \
										XDMAC_CC_MBSIZE_SINGLE + \
										XDMAC_CC_DSYNC_MEM2PER + \
										XDMAC_CC_CSIZE_CHK_1 + \
										XDMAC_CC_DWIDTH_BYTE + \
										XDMAC_CC_SIF_AHB_IF0 + \
										XDMAC_CC_DIF_AHB_IF1 + \
										XDMAC_CC_SAM_INCREMENTED_AM + \
										XDMAC_CC_DAM_FIXED_AM + \
										XDMAC_CC_PERID(UART_DMAC_ID_TX)) 
/*
#define DBGU_INTERRUPT_PRIORITY  100
#define dbgu_uart_irq_handler	UART0_Handler
#define dbgu_uart_IRQn			UART0_IRQn
#define dbgu_uart_IRQ_priority	DBGU_INTERRUPT_PRIORITY
*/


// Register base for USART
#define BASE_DBGU_UART          UART0
#define UART_ID					ID_UART0
#define ATSAME70_DBGU_BAUD		115200
#define UART_DMAC_ID_TX			UART0_DMAC_ID_TX
#define UART_TIMEOUT_US         30000000/ATSAME70_DBGU_BAUD + 1  //30Bit ~ < 3 char

/// Standard operating mode (asynchronous, 8bit, no parity, 1 stop bit)
#define DBGU_STANDARD           AT91C_US_PAR_NONE

// Standard Asynchronous Mode : 8 bits , 1 stop , no parity
#define ATSAME70_US_ASYNC_MODE ( US_MR_USART_MODE_NORMAL_Val + \
US_MR_NBSTOP_1_BIT  + \
US_MR_PAR_NO + \
US_MR_CHRL_8_BIT + \
US_MR_USCLKS_MCK )


unsigned int ATSAME70_UART_TxReady (Uart *pUart );
int  ATSAME70_UART_GetChar (const Uart *pUart);
void UART_Configure(Uart *pUart, uint32_t baudrate, uint32_t masterClock);
//void dbgu_init(void); 
void dbgu_uart_init(void);
void UART_PutChar(Uart *pUart, uint8_t c);
uint8_t UART_GetChar(Uart *pUart);
uint32_t UART_GetStatus(Uart *pUart);
uint8_t UART_Get_RXRDY(Uart *pUart);
//void dbgu_putc(char c);
void dbgu_puts(const char *s);

int dbgu_getc(char *c);
unsigned int ATSAME70_UART_RxReady (Uart *pUART );
void dbgu_tick(void);
void dbgu_command(const char *cmd);

//uint32_t USART_IsRxReady(Usart *pUsart);
//uint8_t USART_IsDataAvailable(Usart *pUsart);
void UART_SetBaudrate(Uart *pUart, uint8_t OverSamp, uint32_t baudrate, uint32_t masterClock);
void USART_SetTransmitterEnabled(Usart *pUsart, uint8_t enabled);
void USART_DisableRx(Usart *pUsart);
void USART_DisableTx(Usart *pUsart);
void USART_EnableRx(Usart *pUsart);
void USART_EnableTx(Usart *pUsart);
void USART_ResetRx(Usart *pUsart);
void USART_ResetTx(Usart *pUsart);
void USART_SetReceiverEnabled(Usart *pUsart, uint8_t enabled);
//void USART_SetRTSEnabled(Usart *pUsart, uint8_t enabled);
void USART_SetRTSEnabled(Usart *pUsart, uint8_t enabled);
void USART_Write(Usart *pUsart, uint16_t data, volatile uint32_t timeOut);
uint16_t USART_Read(Usart *pUsart, volatile uint32_t timeOut);
uint8_t USART_IsDataAvailable(Usart *pUsart);
uint32_t USART_IsRxReady(Usart *pUsart);
//void UART_wait_until_txfifo_clear(void);
void dbgu_clear(void);
void uart_clear_tx_buffer(Uart *pUart);   //void clear_uart_txfifo_buffer(void);
void dbgu_disable(void);

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

extern void DBGU_Configure(
    unsigned int mode,
    unsigned int baudrate,
    unsigned int mck);

extern unsigned char DBGU_GetChar(void);

extern void DBGU_PutChar(unsigned char c);

extern unsigned int DBGU_IsRxReady(void);

#endif

