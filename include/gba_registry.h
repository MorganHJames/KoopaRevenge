//\===========================================================================================
//\ File: gba_registry.h
//\ Author: Morgan James
//\ Date Created: 13/11/2017
//\ Brief: This class defines the base register addresses for I/O VRAM etc.
//\===========================================================================================

#ifndef __GBA_REGISRTY_H__
#define __GBA_REGISRTY_H__

#define	EXTERNAL_WORK_RANDOM_ACCESS_MEMORY		0x02000000//Define the Base Address for External (on-board) Work RAM (WRAM).This is 256K in Size.
#define	EXTERNAL_WORK_RANDOM_ACCESS_MEMORY_END	0x02040000 // From This address up to 0x02FFFFFF is not utilized.

#define INTERNAL_WORK_RANDOM_ACCESS_MEMORY		0x03000000//Define the Base Address for Internal (on-chip) Work RAM (WRAM). This is 32K in Size.

#define REGISTRY_BASE							0x04000000//Define the Base Address for I/O or Hardware Registers.

#define VIDEO_RANDOM_ACCESS_MEMORY				0x06000000//Define the Base Address for Video RAM (VRAM).This is 96K in Size.

#define	SAVE_RANDOM_ACCESS_MEMORY				0x0E000000//Define the Base Address for Cart Save RAM (VRAM). This is 64K (Max) in Size.



#ifndef	NULL
#define	NULL									0//Define for null.
#endif

#endif//__GBA_REGISRTY_H__