#ifndef _GBA_DMA_H_
#define _GBA_DMA_H_

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
#define REG_DMA ((volatile DMA_REC*)0x040000B0)

// Define our DMA control register variables
#define DMA_DST_INC		(0x00 << 21)
#define DMA_DST_DEC		(0x01 << 21)
#define DMA_DST_FIXED	(0x02 << 21)
#define DMA_DST_RELOAD	(0x03 << 21)

#define DMA_SRC_INC		(0x00 << 23)
#define DMA_SRC_DEC		(0x01 << 23)
#define DMA_SRC_FIXED	(0x02 << 23)

#define DMA_REPEAT		(0x01 << 25)

#define DMA_16			(0x00 << 26)
#define DMA_32			(0x01 << 26)

#define DMA_AT_NOW		(0x00 << 28)
#define DMA_AT_VBLANK	(0x01 << 28)
#define DMA_AT_HBLANK	(0x02 << 28)
#define DMA_AT_REFRESH	(0x03 << 28)

#define DMA_IRQ			(0x01 << 30)

#define DMA_ENABLE		(0x01 << 31)

#define DMA_NOW			(DMA_ENABLE | DMA_AT_NOW)
#define DMA_16NOW		(DMA_NOW | DMA_16)
#define DMA_32NOW		(DMA_NOW | DMA_32)

// DMA copy flags
#define DMA_CPY16		DMA_16NOW
#define DMA_CPY32		DMA_32NOW

// DMA fill flags
#define DMA_FILL16		(DMA_NOW | DMA_SRC_FIXED | DMA_16)
#define DMA_FILL32		(DMA_NOW | DMA_SRC_FIXED | DMA_32)

// DMA transfer, copy and fill routines
#define DMA_TRANSFER(_dst, _src, _count, _ch, _mode)\
do{													\
	REG_DMA[_ch].cnt = 0;							\
	REG_DMA[_ch].src = (const void*)(_src);			\
	REG_DMA[_ch].dst = (void*)(_dst);				\
	REG_DMA[_ch].cnt = _count | _mode;				\
}while(0)

static inline void dma_cpy(void* dst, const void* src, u32 count, u32 mode)
{
	REG_DMA[3].cnt = 0;
	REG_DMA[3].src = src;
	REG_DMA[3].dst = dst;
	REG_DMA[3].cnt = count | mode;
}

static inline void dma_fill(void* dst, volatile u32 src, u32 count, u32 mode)
{
	REG_DMA[3].cnt = 0;
	REG_DMA[3].src = (const void*)&src;
	REG_DMA[3].dst = dst;
	REG_DMA[3].cnt = count | mode | DMA_SRC_FIXED;
}

static inline void dma_word_cpy(void* dst, const void* src, u32 size)
{
	dma_cpy(dst, src, size >> 2, DMA_CPY32);
}

static inline void dma_word_fill(void* dst, volatile u32 src, u32 size)
{
	dma_fill(dst, src, size >> 2, DMA_FILL32);
}

#define DMA_HDMA	(DMA_ENABLE | DMA_REPEAT | DMA_AT_HBLANK | DMA_DST_FIXED)

#endif // _GBA_DMA_H_