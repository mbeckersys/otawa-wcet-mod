/*
 * GLISS V2 -- used registers header template
 * Copyright (c) 2010, IRIT - UPS <casse@irit.fr>
 *
 * This file is part of GLISS V2.
 *
 * GLISS V2 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * GLISS V2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GLISS V2; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifndef ARM_USED_REGS
#define ARM_USED_REGS

#include "api.h"

/* register definition */
#define ARM_REG_COUNT	193
#define ARM_REG_BBIT		0
#define ARM_REG_PBIT		1
#define ARM_REG_LR_SAVED(i)	((i) + 4)
#define ARM_REG_LBIT		20
#define ARM_REG_WBIT		21
#define ARM_REG_SP_SAVED(i)	((i) + 23)
#define ARM_REG_PSRXMODE		39
#define ARM_REG_D(i)	((i) + 42)
#define ARM_REG_MSBIT		59
#define ARM_REG_HBIT		65
#define ARM_REG_APSR		67
#define ARM_REG_SPSR		85
#define ARM_REG_NPC		87
#define ARM_REG_RBIT		96
#define ARM_REG_PSRFMODE		99
#define ARM_REG_S(i)	((i) + 100)
#define ARM_REG_GPR(i)	((i) + 133)
#define ARM_REG_PSRSMODE		150
#define ARM_REG_SPSR_SAVED(i)	((i) + 151)
#define ARM_REG_IBIT		173
#define ARM_REG_B15SET		175
#define ARM_REG_R_SAVED(i)	((i) + 177)
#define ARM_REG_UBIT		182
#define ARM_REG_PSRCMODE		183
#define ARM_REG_SBIT		186
#define ARM_REG_ITSTATE		188
#define ARM_REG_FPSCR		191


/* storage definition */
#define ARM_REG_READ_MAX		18
#define ARM_REG_WRITE_MAX		19
typedef int arm_used_regs_read_t[ARM_REG_READ_MAX + 1];
typedef int arm_used_regs_write_t[ARM_REG_WRITE_MAX + 1];

/* function declaration */
void arm_used_regs(arm_inst_t *inst, arm_used_regs_read_t regs, arm_used_regs_write_t wrs);

#endif /* ARM_USED_REGS */
