//\===========================================================================================
//\ File: gba_directMemoryAccess.c
//\ Author: Morgan James
//\ Date Created: 28/11/2017
//\ Brief: Contains the function information for the class contained in gba_direcMemoryAccesss.h.
//\===========================================================================================

#include "gba_directMemoryAccesss.h"

void dma_cpy(void* dst, const void* src, u32 count, u32 mode)
{
	REG_DIRECT_MEMORY_ACCESS[3].cnt = 0;
	REG_DIRECT_MEMORY_ACCESS[3].src = src;
	REG_DIRECT_MEMORY_ACCESS[3].dst = dst;
	REG_DIRECT_MEMORY_ACCESS[3].cnt = count | mode;
}

void dma_fill(void* dst, volatile u32 src, u32 count, u32 mode)
{
	REG_DIRECT_MEMORY_ACCESS[3].cnt = 0;
	REG_DIRECT_MEMORY_ACCESS[3].src = (const void*)&src;
	REG_DIRECT_MEMORY_ACCESS[3].dst = dst;
	REG_DIRECT_MEMORY_ACCESS[3].cnt = count | mode | DIRECT_MEMORY_ACCESS_SRC_FIXED;
}

void dma_word_cpy(void* dst, const void* src, u32 size)
{
	dma_cpy(dst, src, size >> 2, DIRECT_MEMORY_ACCESS_CPY32);
}

void dma_word_fill(void* dst, volatile u32 src, u32 size)
{
	dma_fill(dst, src, size >> 2, DIRECT_MEMORY_ACCESS_FILL32);
}