//\===========================================================================================
//\ File: gba_directMemoryAccess.h
//\ Author: Morgan James
//\ Date Created: 28/11/2017
//\ Brief: Functions and definitions to copy quickly.
//\===========================================================================================

#ifndef _GBA_DIRECT_MEMORY_ACCESS_H_
#define _GBA_DIRECT_MEMORY_ACCESS_H_

#include "gba_types.h"

// Define a register for DMA
typedef struct DMA_REC
{
	const void* src;
	void* dst;
	u32 cnt;
}DMA_REC;

// Get a pointer to the DMA memory location
// access this as an array to get addresses 0 - 3
#define REG_DIRECT_MEMORY_ACCESS ((volatile DMA_REC*)0x040000B0)

// Define our DMA control register variables
#define DIRECT_MEMORY_ACCESS_DST_INC		(0x00 << 21)
#define DIRECT_MEMORY_ACCESS_DST_DEC		(0x01 << 21)
#define DIRECT_MEMORY_ACCESS_DST_FIXED	(0x02 << 21)
#define DIRECT_MEMORY_ACCESS_DST_RELOAD	(0x03 << 21)

#define DIRECT_MEMORY_ACCESS_SRC_INC		(0x00 << 23)
#define DIRECT_MEMORY_ACCESS_SRC_DEC		(0x01 << 23)
#define DIRECT_MEMORY_ACCESS_SRC_FIXED	(0x02 << 23)

#define DIRECT_MEMORY_ACCESS_REPEAT		(0x01 << 25)

#define DIRECT_MEMORY_ACCESS_16			(0x00 << 26)
#define DIRECT_MEMORY_ACCESS_32			(0x01 << 26)

#define DIRECT_MEMORY_ACCESS_AT_NOW		(0x00 << 28)
#define DIRECT_MEMORY_ACCESS_AT_VBLANK	(0x01 << 28)
#define DIRECT_MEMORY_ACCESS_AT_HBLANK	(0x02 << 28)
#define DIRECT_MEMORY_ACCESS_AT_REFRESH	(0x03 << 28)

#define DIRECT_MEMORY_ACCESS_IRQ			(0x01 << 30)

#define DIRECT_MEMORY_ACCESS_ENABLE		(0x01 << 31)

#define DIRECT_MEMORY_ACCESS_NOW			(DIRECT_MEMORY_ACCESS_ENABLE | DIRECT_MEMORY_ACCESS_AT_NOW)
#define DIRECT_MEMORY_ACCESS_16NOW		(DIRECT_MEMORY_ACCESS_NOW | DIRECT_MEMORY_ACCESS_16)
#define DIRECT_MEMORY_ACCESS_32NOW		(DIRECT_MEMORY_ACCESS_NOW | DIRECT_MEMORY_ACCESS_32)

// DMA copy flags
#define DIRECT_MEMORY_ACCESS_CPY16		DIRECT_MEMORY_ACCESS_16NOW
#define DIRECT_MEMORY_ACCESS_CPY32		DIRECT_MEMORY_ACCESS_32NOW

// DMA fill flags
#define DIRECT_MEMORY_ACCESS_FILL16		(DIRECT_MEMORY_ACCESS_NOW | DIRECT_MEMORY_ACCESS_SRC_FIXED | DIRECT_MEMORY_ACCESS_16)
#define DIRECT_MEMORY_ACCESS_FILL32		(DIRECT_MEMORY_ACCESS_NOW | DIRECT_MEMORY_ACCESS_SRC_FIXED | DIRECT_MEMORY_ACCESS_32)

// DMA transfer, copy and fill routines
#define DIRECT_MEMORY_ACCESS_TRANSFER(_dst, _src, _count, _ch, _mode)\
do{													\
	REG_DIRECT_MEMORY_ACCESS[_ch].cnt = 0;							\
	REG_DIRECT_MEMORY_ACCESS[_ch].src = (const void*)(_src);			\
	REG_DIRECT_MEMORY_ACCESS[_ch].dst = (void*)(_dst);				\
	REG_DIRECT_MEMORY_ACCESS[_ch].cnt = _count | _mode;				\
}while(0)

extern void dma_cpy(void* dst, const void* src, u32 count, u32 mode);

extern void dma_fill(void* dst, volatile u32 src, u32 count, u32 mode);

extern void dma_word_cpy(void* dst, const void* src, u32 size);

extern void dma_word_fill(void* dst, volatile u32 src, u32 size);

#define DIRECT_MEMORY_ACCESS_HDMA	(DIRECT_MEMORY_ACCESS_ENABLE | DIRECT_MEMORY_ACCESS_REPEAT | DIRECT_MEMORY_ACCESS_AT_HBLANK | DIRECT_MEMORY_ACCESS_DST_FIXED)

#endif // _GBA_DIRECT_MEMORY_ACCESS_H_