/* Generated by gep (118/02/19 18:37:34) copyright (c) 2008 IRIT - UPS */
#ifndef GLISS_ARM_INCLUDE_ARM_API_H
#define GLISS_ARM_INCLUDE_ARM_API_H

#include <stdint.h>
#include <stdio.h>

#if defined(__WIN32) || defined(__WIN64)
#	ifdef __cplusplus
#		define __BEGIN_DECLS	extern "C" {
#		define __END_DECLS		}
#	else
#		define __BEGIN_DECLS
#		define __END_DECLS
#	endif
#else
#	include <sys/cdefs.h>
#endif


#include "id.h"
#include "mem.h"
#include "decode.h"

#define ARM_PROC_NAME "ARM"
#define ARM_PC_NAME  GPR[15]

/* return an instruction identifier as a string instead of the arm_ident_t which is not very user friendly */
char *arm_get_string_ident(arm_ident_t id);

/* opaque types */
typedef struct arm_platform_t arm_platform_t;
typedef struct arm_fetch_t arm_fetch_t;
typedef struct arm_decoder_t arm_decoder_t;
struct arm_loader_t;
typedef struct mask_t mask_t;

/* arm_state_t type */
typedef struct arm_state_t {
	arm_platform_t *platform;
	uint8_t BBIT;
	uint8_t PBIT;
	uint32_t LR_saved[16];
	uint8_t LBIT;
	uint8_t WBIT;
	uint32_t SP_saved[16];
	uint8_t PSRXMODE;
	double D[16];
	uint8_t MSBIT;
	uint8_t HBIT;
	uint32_t APSR;
	uint32_t SPSR;
	uint32_t NPC;
	uint8_t RBIT;
	uint8_t PSRFMODE;
	float S[32];
	uint32_t GPR[16];
	uint8_t PSRSMODE;
	uint32_t SPSR_saved[16];
	uint8_t IBIT;
	uint8_t B15SET;
	uint32_t R_saved[5];
	uint8_t UBIT;
	uint8_t PSRCMODE;
	uint8_t SBIT;
	uint8_t ITSTATE;
	uint32_t FPSCR;

	arm_memory_t *M;

} arm_state_t;

/* arm_sim_t type */
typedef struct arm_sim_t {
	arm_state_t *state;
	arm_decoder_t *decoder;
	/* on libc stripped programs it is difficult to find the exit point, so we specify it */
	arm_address_t addr_exit;
	/* anything else? */
	int ended;
} arm_sim_t;


/* arm_value_t type */
typedef union arm_value_t {
	int8_t int8;
	uint8_t uint8;
	int16_t int16;
	uint16_t uint16;
	int32_t int32;
	uint32_t uint32;

} arm_value_t;


/* arm_ii_t type */
typedef struct arm_ii_t {
	arm_value_t val;
} arm_ii_t;

/* arm_inst_t type */
typedef struct arm_inst_t {
	arm_ident_t   ident;
	arm_address_t addr;
	arm_ii_t instrinput[10];

} arm_inst_t;

/* auxiliary vector */
typedef struct arm_auxv_t {
	int	a_type;
	union {
		long a_val;
		void *a_ptr;
		void (*a_fcn)();
	} a_un;
} arm_auxv_t;

/* environment description */
typedef struct arm_env_t
{
	int argc;

	char **argv;
	arm_address_t argv_addr;

	char **envp;
	arm_address_t envp_addr;

	arm_auxv_t *auxv;
	arm_address_t auxv_addr;

	arm_address_t stack_pointer;
	arm_address_t brk_addr;
} arm_env_t;

/* platform management */
#define ARM_MAIN_MEMORY		0
arm_platform_t *arm_new_platform(void);
arm_memory_t *arm_get_memory(arm_platform_t *platform, int index);
struct arm_env_t;
struct arm_env_t *arm_get_sys_env(arm_platform_t *platform);
void arm_lock_platform(arm_platform_t *platform);
void arm_unlock_platform(arm_platform_t *platform);
int arm_load_platform(arm_platform_t *platform, const char *path);
void arm_load(arm_platform_t *platform, struct arm_loader_t *loader);

/* fetching */
arm_fetch_t *arm_new_fetch(arm_platform_t *pf, arm_state_t *state);
void arm_delete_fetch(arm_fetch_t *fetch);

typedef union {
	uint32_t u32;
	mask_t *mask;
} code_t;
arm_ident_t arm_fetch(arm_fetch_t *fetch, arm_address_t address, code_t *code);

/* decoding */
typedef struct arm_mode_t {
	const char *name;
	arm_inst_t *(*decode)(arm_decoder_t *decoder, arm_address_t address);
} arm_mode_t;
extern arm_mode_t arm_modes[];

arm_decoder_t *arm_new_decoder(arm_platform_t *pf);
void arm_delete_decoder(arm_decoder_t *decoder);
arm_inst_t *arm_decode(arm_decoder_t *decoder, arm_address_t address);
void arm_free_inst(arm_inst_t *inst);
/* only used if several ISS defined to fully initialize decoder structure,
 * does nothing if one inst set only is defined */
void arm_set_cond_state(arm_decoder_t *decoder, arm_state_t *state);
/* decoding functions for one specific instr set */
/* decoding function for instr set 0, named ARM */
arm_inst_t *arm_decode_ARM(arm_decoder_t *decoder, arm_address_t address);
/* decoding function for instr set 1, named THUMB */
arm_inst_t *arm_decode_THUMB(arm_decoder_t *decoder, arm_address_t address);
unsigned long arm_get_inst_size(arm_inst_t* inst);
unsigned long arm_get_inst_size_from_id(arm_ident_t id);


/* code execution */
void arm_execute(arm_state_t *state, arm_inst_t *inst);

/* state management function */
arm_state_t *arm_new_state(arm_platform_t *platform);
void arm_delete_state(arm_state_t *state);
arm_state_t *arm_copy_state(arm_state_t *state);
arm_state_t *arm_fork_state(arm_state_t *state);
void arm_dump_state(arm_state_t *state, FILE *out);
arm_platform_t *arm_platform(arm_state_t *state);

/* simulation functions */
arm_sim_t *arm_new_sim(arm_state_t *state, arm_address_t start_addr, arm_address_t exit_addr);
arm_inst_t *arm_next_inst(arm_sim_t *sim);
uint64_t arm_run_and_count_inst(arm_sim_t *sim);
void arm_run_sim(arm_sim_t *sim);
void arm_step(arm_sim_t *sim);
void arm_delete_sim(arm_sim_t *sim);
arm_address_t  arm_next_addr(arm_sim_t *sim);
void arm_set_next_address(arm_sim_t *sim, arm_address_t address);
#define arm_set_entry_address(sim, addr) arm_set_next_address(sim, addr)
void arm_set_exit_address(arm_sim_t *sim, arm_address_t address);
#define arm_set_sim_ended(sim) (sim)->ended = 1
#define arm_is_sim_ended(sim) ((sim)->ended)

/* disassemble function */
void arm_disasm(char *buffer, arm_inst_t *inst);
typedef char *(*arm_label_solver_t)(arm_address_t address);
extern arm_label_solver_t arm_solve_label;
char *arm_solve_label_null(arm_address_t address);

/* variable length functions */
uint32_t value_on_mask(mask_t *inst, mask_t *mask);

#endif /* GLISS_ARM_INCLUDE_ARM_API_H */
