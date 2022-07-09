/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2015, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

/** \file */

/**
 * \addtogroup mmu MMU Initialization
 *
 * \section Usage
 *
 * Translation Look-aside Buffers (TLBs) are an implementation technique that
 * caches translations or translation table entries. TLBs avoid the requirement
 * for every memory access to perform a translation table lookup.
 * The ARM architecture does not specify the exact form of the TLB structures
 * for any design. In a similar way to the requirements for caches, the
 * architecture only defines certain principles for TLBs:
 *
 * The MMU supports memory accesses based on memory sections or pages:
 * Super-sections Consist of 16MB blocks of memory. Support for Super sections
 * is optional.
 * -# Sections Consist of 1MB blocks of memory.
 * -# Large pages Consist of 64KB blocks of memory.
 * -# Small pages Consist of 4KB blocks of memory.
 *
 * Access to a memory region is controlled by the access permission bits and
 * the domain field in the TLB entry.
 * Memory region attributes
 * Each TLB entry has an associated set of memory region attributes. These
 * control accesses to the caches,
 * how the write buffer is used, and if the memory region is Shareable and
 * therefore must be kept coherent.
 *
 * Related files:\n
 * \ref mmu.c\n
 * \ref mmu.h \n
 */

/*-------------------------------------------------------------------------- */
/*         Headers                                                           */
/*-------------------------------------------------------------------------- */
//#include <chip.h>
#include "stdint.h"
#include "sam.h"
#include "mpu.h"
/*----------------------------------------------------------------------------
 *        Exported functions

 *----------------------------------------------------------------------------*/
/**
 * \brief Enables the MPU module.
 *
 * \param dwMPUEnable  Enable/Disable the memory region.
 */
void MPU_Enable(uint32_t dwMPUEnable)
{
	MPU->CTRL = dwMPUEnable;
}

/**
 * \brief Set active memory region.
 *
 * \param dwRegionNum  The memory region to be active.
 */
void MPU_SetRegionNum(uint32_t dwRegionNum)
{
	MPU->RNR = dwRegionNum;
}

/**
 * \brief Disable the current active region.
 */
extern void MPU_DisableRegion(void)
{
	MPU->RASR &= 0xfffffffe;
}

/**
 * \brief Setup a memory region.
 *
 * \param dwRegionBaseAddr  Memory region base address.
 * \param dwRegionAttr  Memory region attributes.
 */
void MPU_SetRegion(uint32_t dwRegionBaseAddr, uint32_t dwRegionAttr)
{
	MPU->RBAR = dwRegionBaseAddr;
	MPU->RASR = dwRegionAttr;
}


/**
 * \brief Calculate region size for the RASR.
 */
uint32_t MPU_CalMPURegionSize(uint32_t dwActualSizeInBytes)
{
	uint32_t dwRegionSize = 32;
	uint32_t dwReturnValue = 4;

	while (dwReturnValue < 31) {
		if (dwActualSizeInBytes <= dwRegionSize)
			break;
		else
			dwReturnValue++;

		dwRegionSize <<= 1;
	}

	return (dwReturnValue << 1);
}


/**
 *  \brief Update MPU regions.
 *
 *  \return Unused (ANSI-C compatibility).
 */
void MPU_UpdateRegions(uint32_t dwRegionNum, uint32_t dwRegionBaseAddr,
						uint32_t dwRegionAttr)
{

	/* Disable interrupt */
	__disable_irq();

	/* Clean up data and instruction buffer */
	__DSB();
	__ISB();

	/* Set active region */
	MPU_SetRegionNum(dwRegionNum);

	/* Disable region */
	MPU_DisableRegion();

	/* Update region attribute */
	MPU_SetRegion(dwRegionBaseAddr, dwRegionAttr);

	/* Clean up data and instruction buffer to make the new region taking
	   effect at once */
	__DSB();
	__ISB();

	/* Enable the interrupt */
	__enable_irq();
}
#define REGION_SIZE_ENCODING_2M        0x14                              
#define REGION_SIZE_ENCODING_4M        0x15
#define REGION_SIZE_ENCODING_8M        0x16
#define REGION_SIZE_ENCODING_16M       0x17
#define REGION_SIZE_ENCODING_32M       0x18
#define REGION_SIZE_ENCODING_64M       0x19
#define REGION_SIZE_ENCODING_128M      0x1a
#define REGION_SIZE_ENCODING_256M      0x1b
#define MPU_REGION_SIZE                (REGION_SIZE_ENCODING_256M << 1)
#define MPU_ATTRIBUTE				MPU_AP_FULL_ACCESS | MPU_REGION_EXECUTE_NEVER 
#define MPU_REGION0					MPU_EXT_EBI_REGION
#define MPU_REGION0_BASE_ADDRESS	EXT_EBI_START_ADDRESS
#define MPU_REGION0_ATTRIBUTE       MPU_ENABLE | MPU_REGION_SIZE | MPU_ATTRIBUTE                             //MPU_RSAR register

void MPU_Configure (void)
{
	MPU_UpdateRegions(MPU_REGION0,MPU_REGION0_BASE_ADDRESS,MPU_REGION0_ATTRIBUTE);
	MPU_Enable(MPU_REGION0);
}