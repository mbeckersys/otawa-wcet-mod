/*
 *	$Id: old_elf.h,v 1.10 2009/07/21 13:17:58 barre Exp $
 *	old_elf module interface
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
#ifndef ARM_OLD_ELF_H
#define ARM_OLD_ELF_H

#include "grt.h"
#include "mem.h"
#include "api.h"

#if defined(__cplusplus)
    extern  "C" {
#endif

#define ARM_LOADER_STATE
#define ARM_LOADER_INIT(s)
#define ARM_LOADER_DESTROY(s)

/* arm_loader_t type */
typedef struct arm_loader_t arm_loader_t;


/* loader management */
arm_loader_t *arm_loader_open(const char *path);
void arm_loader_close(arm_loader_t *loader);
void arm_loader_load(arm_loader_t *loader, arm_platform_t *pf);
arm_address_t arm_loader_start(arm_loader_t *loader);


/* system initialization (used internally during platform and state initialization) */
arm_address_t arm_brk_init(arm_loader_t *loader);

/* section access */
typedef struct arm_loader_sect_t {
	const char *name;
	arm_address_t addr;
	int size;
	enum {
		ARM_LOADER_SECT_UNKNOWN = 0,
		ARM_LOADER_SECT_TEXT,
		ARM_LOADER_SECT_DATA,
		ARM_LOADER_SECT_BSS
	} type;
} arm_loader_sect_t;
int arm_loader_count_sects(arm_loader_t *loader);
void arm_loader_sect(arm_loader_t *loader, int sect, arm_loader_sect_t *data);

/* symbol access */
typedef struct {
	const char *name;
	arm_address_t value;
	int size;
	int sect;
	enum {
		ARM_LOADER_SYM_NO_TYPE,
		ARM_LOADER_SYM_DATA,
		ARM_LOADER_SYM_CODE
	} type;
	enum {
		ARM_LOADER_NO_BINDING,
		ARM_LOADER_LOCAL,
		ARM_LOADER_GLOBAL,
		ARM_LOADER_WEAK
	} bind;
} arm_loader_sym_t;
int arm_loader_count_syms(arm_loader_t *loader);
void arm_loader_sym(arm_loader_t *loader, int sym, arm_loader_sym_t *data);



#if defined(__cplusplus)
}
#endif

#endif	/* ARM_OLD_ELF_H */
