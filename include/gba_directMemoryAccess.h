//\===========================================================================================
//\ File: gba_directMemoryAccess.h
//\ Author: Morgan James
//\ Date Created: 27/11/2017
//\ Brief: 
//\===========================================================================================

#ifndef __GBA_DIRECT_MEMORY_ACCESS_H__
#define __GBA_DIRECT_MEMORY_ACCESS_H__

#define DIRECT_MEMORY_ACCESS_ENABLE 0x80000000//Flag for turning on DMA.

#define DIRECT_MEMORY_ACCESS_16 0x00000000//Flag for the size 16b.
#define DIRECT_MEMORY_ACCESS_32 0x04000000//Flag for the size 32b

volatile unsigned int* directMemoryAccessSource = (volatile unsigned int*)0x40000D4;//Pointer to the DMA source location.

volatile unsigned int* directMemoryAccessDestination = (volatile unsigned int*)0x40000D8;//Pointer to the DMA destination location.

volatile unsigned int* directMemoryAccessCount = (volatile unsigned int*)0x40000DC;//Pointer to the DMa count/control.

inline void memoryCopy16DirectMemoryAccess(unsigned short* a_usDestination, unsigned short* a_usSource, int a_iAmount)//Copy data using DMA.
{
	*directMemoryAccessSource = (unsigned int)a_usSource;
	*directMemoryAccessDestination = (unsigned int)a_usDestination;
	*directMemoryAccessCount = a_iAmount | DIRECT_MEMORY_ACCESS_16 | DIRECT_MEMORY_ACCESS_ENABLE;
}

#endif//__GBA_DIRECT_MEMORY_ACCESS_H__
