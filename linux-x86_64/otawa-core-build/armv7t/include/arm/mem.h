/*
 *	$Id: io_mem.h,v 1.4 2009/01/21 07:30:54 casse Exp $
 *	io_mem module interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2008, IRIT UPS.
 * 
 *	GLISS is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	GLISS is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with OTAWA; if not, write to the Free Software 
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifndef ARM_IO_MEM_H
#define ARM_IO_MEM_H

#include <stdint.h>
#include <stddef.h>
#include "config.h"

#if defined(__cplusplus)
    extern  "C" {
#endif

#define ARM_MEM_STATE
#define ARM_MEM_INIT(s)
#define ARM_MEM_DESTROY(s)

#define ARM_MEM_IO

typedef uint32_t arm_address_t;
typedef uint32_t arm_size_t;
typedef struct arm_memory_t arm_memory_t;
 
/* creation function */
arm_memory_t *arm_mem_new(void);
void arm_mem_delete(arm_memory_t *memory);
arm_memory_t *arm_mem_copy(arm_memory_t *memory);
 
/* read functions */
uint8_t arm_mem_read8(arm_memory_t *, arm_address_t);
uint16_t arm_mem_read16(arm_memory_t *, arm_address_t);
uint32_t arm_mem_read32(arm_memory_t *, arm_address_t);
uint64_t arm_mem_read64(arm_memory_t *, arm_address_t);
float arm_mem_readf(arm_memory_t *, arm_address_t);
double arm_mem_readd(arm_memory_t *, arm_address_t);
long double arm_mem_readld(arm_memory_t *, arm_address_t);
void arm_mem_read(arm_memory_t *memory, arm_address_t, void *buf, size_t size);
 
 
/* write functions */
void arm_mem_write8(arm_memory_t *, arm_address_t, uint8_t);
void arm_mem_write16(arm_memory_t *, arm_address_t, uint16_t);
void arm_mem_write32(arm_memory_t *, arm_address_t, uint32_t);
void arm_mem_write64(arm_memory_t *, arm_address_t, uint64_t);
void arm_mem_writef(arm_memory_t *, arm_address_t, float);
void arm_mem_writed(arm_memory_t *, arm_address_t, double);
void arm_mem_writeld(arm_memory_t *, arm_address_t, long double);
void arm_mem_write(arm_memory_t *memory, arm_address_t, void *buf, size_t size);


/* callback related functions */
/* in the prototype of a typical callback function, arguments are the address of the memory transfer,
 * the size of the transfer in bytes, the address (as a void* to be cast) of the data (typically a register)
 * to be read or written from or to memory and the access type (read or write memory) */
/* !!WARNING!! the memory is divided into pages and callback functions are defined for an entire page, not only for a few addresses */

/* type access values */
#define ARM_MEM_READ	0
#define ARM_MEM_WRITE	1
/* callback function prototype */
typedef void (*arm_callback_fun_t)(arm_address_t addr, int size, void *data, int type_access, void *cdata);
void arm_set_range_callback(arm_memory_t *mem, arm_address_t start, arm_address_t end, arm_callback_fun_t f, void* data);
void arm_unset_range_callback(arm_memory_t *mem, arm_address_t start, arm_address_t end);

/* spy function prototypes */
#ifdef ARM_MEM_SPY
typedef enum { arm_access_read, arm_access_write } arm_access_t;
typedef void (*arm_mem_spy_t)(arm_memory_t *mem, arm_address_t addr, arm_size_t size, arm_access_t access, void *data);
void arm_mem_set_spy(arm_memory_t *mem, arm_mem_spy_t fun, void *data);
#endif

#if defined(__cplusplus)
}
#endif

#endif	/* ARM_IO_MEM_H */
