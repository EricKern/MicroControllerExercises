
#include "stdio.h"
#include <stdint.h>
#include <assert.h>
#include "xdmac.h"
#include "LIB_ATSAME70.h"
#include "board_cortex7.h"

//uint32_t dma_channel_active = 0;



//get free dma channel + set free dma channel interrupt mask

uint8_t get_free_dma_channel(void)
{
	uint8_t channel_number;
	PMC_EnablePeripheral(ID_XDMAC);
	//__disable_irq();
	for (channel_number = 0; channel_number < NUMBER_OF_DMA_CHANNELS; channel_number++)
	{
		if (((1<< channel_number) & XDMAC->XDMAC_GIM) == 0)
		{
			XDMAC->XDMAC_GIE = (1<< channel_number);
			XDMAC->XDMAC_CHID[channel_number].XDMAC_CNDC = 0;
			XDMAC->XDMAC_CHID[channel_number].XDMAC_CBC = 0;
			XDMAC->XDMAC_CHID[channel_number].XDMAC_CDS_MSP = 0;
			XDMAC->XDMAC_CHID[channel_number].XDMAC_CSUS = 0;
			XDMAC->XDMAC_CHID[channel_number].XDMAC_CDUS = 0;
			XDMAC->XDMAC_CHID[channel_number].XDMAC_CBC = XDMAC_CBC_BLEN(0);	
			XDMAC->XDMAC_CHID[channel_number].XDMAC_CIE = XDMAC_CIE_BIE;//ENABLES END OF BLOCK INTERRUPT
				
			return channel_number;
		}
	}
	//__enable_irq();
	printf("no dma channel available\n"); 
	return -1;
}

void set_free_dma_channel (uint8_t channel_number)
{
	XDMAC->XDMAC_GID = (1<< channel_number);	
}

//uint32_t dma_address_offset_between_channels;

/*
void init_all_dma_channels_default(void)
{
	uint32_t i;

	for (i=0;i<NUMBER_OF_DMA_CHANNELS;i++)
	{
//		dma_address_offset = dma_address_offset_between_channels * i;
		XDMAC->XDMAC_CHID[i].XDMAC_CNDC = 0;
		XDMAC->XDMAC_CHID[i].XDMAC_CBC = 0;
		XDMAC->XDMAC_CHID[i].XDMAC_CDS_MSP = 0;
		XDMAC->XDMAC_CHID[i].XDMAC_CSUS = 0;
		XDMAC->XDMAC_CHID[i].XDMAC_CDUS = 0;
	}
}
*/

void dma_channel_test(void)
{
	uint8_t i = 0;
	PMC_EnablePeripheral(ID_XDMAC);
	for (i=0; i<NUMBER_OF_DMA_CHANNELS; i++)
	{
		printf("free DMA channel %d\n", get_free_dma_channel());
	}
	delayms(5000);
}
