/*
** timer.h
*/

#ifndef _FIFO_H_
#define _FIFO_H_

#define FIFO_FAIL     0
#define FIFO_SUCCESS  1

typedef struct {
	uint8_t *data;
	uint32_t read; // zeigt auf das Feld mit dem ältesten Inhalt
	uint32_t write; // zeigt immer auf leeres Feld
	uint32_t size;
} sfifo;


void fifo_init(sfifo *fifo, uint8_t *buf, uint32_t fifo_size);
uint8_t fifo_In(sfifo *fifo, uint8_t byte);
uint8_t fifo_Out(sfifo *fifo,uint8_t *pByte);
uint8_t fifo_status(sfifo *fifo);




#endif