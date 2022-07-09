
#ifndef DMAC_H
#define DMAC_H

#include <stdint.h>
#include "sam.h"

#define NUMBER_OF_DMA_CHANNELS 24

/** Number of DMA channels */
#define XDMAC_CONTROLLER_NUM            1
/** Number of DMA channels */
#define XDMAC_CHANNEL_NUM               24
/** Max DMA single transfer size */
#define XDMAC_MAX_BT_SIZE               0xFFFF
/**     @}*/

/*----------------------------------------------------------------------------
 *         Macro
 *----------------------------------------------------------------------------*/
#define XDMA_GET_DATASIZE(size) ((size==0)? XDMAC_CC_DWIDTH_BYTE : \
								((size==1)? XDMAC_CC_DWIDTH_HALFWORD : \
								(XDMAC_CC_DWIDTH_WORD  )))
#define XDMA_GET_CC_SAM(s)      ((s==0)? XDMAC_CC_SAM_FIXED_AM : \
								((s==1)? XDMAC_CC_SAM_INCREMENTED_AM : \
								((s==2)? XDMAC_CC_SAM_UBS_AM : \
									XDMAC_CC_SAM_UBS_DS_AM )))
#define XDMA_GET_CC_DAM(d)      ((d==0)? XDMAC_CC_DAM_FIXED_AM : \
								((d==1)? XDMAC_CC_DAM_INCREMENTED_AM : \
								((d==2)? XDMAC_CC_DAM_UBS_AM : \
									XDMAC_CC_DAM_UBS_DS_AM )))
#define XDMA_GET_CC_MEMSET(m)   ((m==0)? XDMAC_CC_MEMSET_NORMAL_MODE : \
									XDMAC_CC_MEMSET_HW_MODE)

#define NUMBER_OF_DMA_CHANNELS 24

void init_all_dma_channels_default(void);
uint8_t get_free_dma_channel(void);
void set_free_dma_channel (uint8_t channel_number);

#endif //#ifndef DMAC_H

