/* Generated by GLISS V2.0 Copyright (c) 2009 IRIT - UPS (118/04/09 13:03:09) */
#ifndef ARM_PLATFORM_H
#define ARM_PLATFORM_H

#include <arm/api.h>
#include <arm/mem.h>
#include <arm/grt.h>
#include <arm/error.h>
#include <arm/gen_int.h>
#include <arm/loader.h>
#include <arm/code.h>
#include <arm/env.h>
#include <arm/sys_call.h>
#include <arm/shift.h>


/* arm_platform_t structure */
struct arm_platform_t
{
	int usage;

	/* entry point of the simulated program */
	arm_address_t entry;
	/* initial sp, argv, envp ... */
	arm_env_t *sys_env;

	union
	{
		arm_memory_t *array[0];
		struct
		{
			arm_memory_t *M;

		} named;
	} mems;
	ARM_MEM_STATE
	ARM_GRT_STATE
	ARM_ERROR_STATE
	ARM_GEN_INT_STATE
	ARM_LOADER_STATE
	ARM_CODE_STATE
	ARM_ENV_STATE
	ARM_SYS_CALL_STATE
	ARM_SHIFT_STATE

};

/* functions */

#endif	/* ARM_PLATFORM_H */
