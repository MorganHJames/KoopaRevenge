//\===========================================================================================
//\ File: gba_types.h
//\ Author: Morgan James
//\ Date Created: 13/11/2017
//\ Brief: This is a small header file used to define types that are used for GBA development
//\ these types are named according to their signedness and their bit length
//\ u8 represents an unsigned integer that is 8 bits in size, this would be an unsigned char on 0x86 systems. 
//\ These are defined like this for simplicity and to keep code in appropriate spaces
//\===========================================================================================

#ifndef __GBA_TYPES_H__
#define __GBA_TYPES_H__

#include <stdint.h>
#include <stdbool.h>

//---------------------------------------------------------------------------------
// Data	types
//---------------------------------------------------------------------------------

typedef	uint8_t			u8;//Unsigned 8 bit value.	
typedef	uint16_t		u16;//Unsigned 16 bit value.
typedef	uint32_t		u32;//Unsigned 32 bit value.	
								 
typedef	int8_t			s8;//Signed 8 bit value.	
typedef	int16_t			s16;//Signed 16 bit value.	
typedef	int32_t			s32;//Signed 32 bit value.	
								 
typedef	volatile u8		vu8;//Volatile Unsigned 8 bit value.	
typedef	volatile u16	vu16;//Volatile Unsigned 16 bit value.	
typedef	volatile u32	vu32;//Volatile Unsigned 32 bit value.	
								 
typedef	volatile s8		vs8;//Volatile Signed 8 bit value.	
typedef	volatile s16	vs16;//Volatile Signed 8 bit value.	
typedef	volatile s32	vs32;//Volatile Signed 8 bit value.	

typedef u16             COLOR;//A define for a color which is a unsigned 16 bit value.

#endif //__GBA_TYPES_H__
