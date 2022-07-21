
#include "common/compiler.h"
#include "fifo.h"


void fifo_init(sfifo *fifo, uint8_t * buf, uint32_t fifo_size){
	fifo->read = 0;
	fifo->write = 0;
	fifo->size = fifo_size;
	fifo->data = buf;
}

	//
	// Stellt 1 Byte in den Ringbuffer
	//
	// Returns:
	//     BUFFER_FAIL       der Ringbuffer ist voll. Es kann kein weiteres Byte gespeichert werden
	//     BUFFER_SUCCESS    das Byte wurde gespeichert
	//
	
inline uint8_t fifo_In(sfifo *fifo, uint8_t byte)
	{
		
		if ( ( fifo->write + 1 == fifo->read ) ||
		( fifo->read == 0 && fifo->write + 1 == fifo->size) )
		return FIFO_FAIL; // fifo voll

		fifo->data[fifo->write] = byte;

		fifo->write++;
		if (fifo->write >= fifo->size)
		fifo->write = 0;

		return FIFO_SUCCESS;
	}

	//
	// Holt 1 Byte aus dem Ringbuffer, sofern mindestens eines abholbereit ist
	//
	// Returns:
	//     BUFFER_FAIL       der Ringbuffer ist leer. Es kann kein Byte geliefert werden.
	//     BUFFER_SUCCESS    1 Byte wurde geliefert
	//
inline	uint8_t fifo_Out(sfifo *fifo, uint8_t *pByte)
	{
		if (fifo->read == fifo->write)
		return FIFO_FAIL;

		*pByte = fifo->data[fifo->read];

		fifo->read++;
		if (fifo->read >= fifo->size)
		fifo->read = 0;

		return FIFO_SUCCESS;
	}
	
inline	uint8_t fifo_status(sfifo *fifo)
{
	if (fifo->read == fifo->write)
	return FIFO_FAIL;
	else
	return FIFO_SUCCESS;
}