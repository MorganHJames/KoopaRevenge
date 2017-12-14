//\===========================================================================================
//\ File: gba_directMemoryAccess.c
//\ Author: Morgan James
//\ Date Created: 28/11/2017
//\ Brief: Contains the function information for the prototypes contained in gba_direcMemoryAccesss.h.
//\===========================================================================================

#include "gba_directMemoryAccesss.h"

void DirectMemoryAccessCopy(void* a_pDestination, const void* a_c_pSource, u32 a_u32Count, u32 a_u32Mode)
{
	REG_DIRECT_MEMORY_ACCESS[3].u32Count = 0;
	REG_DIRECT_MEMORY_ACCESS[3].pSource = a_c_pSource;
	REG_DIRECT_MEMORY_ACCESS[3].pDestination = a_pDestination;
	REG_DIRECT_MEMORY_ACCESS[3].u32Count = a_u32Count | a_u32Mode;
}

void DirectMemoryAccessFill(void* a_pDestination, vu32 a_vu32Source, u32 a_u32Count, u32 a_u32Mode)
{
	REG_DIRECT_MEMORY_ACCESS[3].u32Count = 0;
	REG_DIRECT_MEMORY_ACCESS[3].pSource = (const void*)&a_vu32Source;
	REG_DIRECT_MEMORY_ACCESS[3].pDestination = a_pDestination;
	REG_DIRECT_MEMORY_ACCESS[3].u32Count = a_u32Count | a_u32Mode | DIRECT_MEMORY_ACCESS_SRC_FIXED;
}

void DirectMemoryAccessWordCopy(void* a_pDestination, const void* a_c_pSource, u32 a_u32Size)
{
	DirectMemoryAccessCopy(a_pDestination, a_c_pSource, a_u32Size >> 2, DIRECT_MEMORY_ACCESS_CPY32);
}

void DirectMemoryAccessWordFill(void* a_pDestination, vu32 a_vu32Source, u32 a_u32Size)
{
	DirectMemoryAccessFill(a_pDestination, a_vu32Source, a_u32Size >> 2, DIRECT_MEMORY_ACCESS_FILL32);
}