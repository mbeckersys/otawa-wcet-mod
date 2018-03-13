/* Generated by gep (118/02/13 18:43:07) copyright (c) 2011 IRIT - UPS */

#include <assert.h>
#include <arm/debug.h>
#include <arm/macros.h>
#include <arm/grt.h>

#define GLISS_IDX		idx
#define GLISS_I			r.iv
#define GLISS_L			r.lv
#define GLISS_F			r.fv
#define GLISS_D			r.dv
#define GLISS_GET_I(a)	r.iv = a
#define GLISS_GET_L(a)	r.lv = a
#define GLISS_GET_F(a)	r.fv = a
#define GLISS_GET_D(a)	r.dv = a

static register_bank_t arm_registers[] = {
	{
		23,
		"CPSR",
		"CPSR",
		1,
		RTYPE_INT,
		32
	},
	{
		24,
		"Registers",
		"R%d",
		16,
		RTYPE_INT,
		32
	},
	{
		-1
	}
};


/**
 * Get the description of registers of the architecture.
 * @return		Array of registers (last one has a negative identifier).
 */
register_bank_t *arm_get_registers(void) {
	return arm_registers;
}

/**
 * Get the value of a register.
 * @param state		Current state.
 * @param id		Register identifier (from register_bank_t).
 * @param idx		Index in the bank (ignored for non-mutiple register bank).
 * @return			Value of the register.
 */
register_value_t arm_get_register(arm_state_t *state, int id, int idx) {
	register_value_t r;
	switch(id) {
	case 23: {
				GLISS_GET_I(ARM_APSR);

		} break;
	case 24: {
				GLISS_GET_I(ARM_GPR[GLISS_IDX]);

		} break;

	default:
		assert(0);
	}
	return r;
}


/**
 * Set the value of a register in the given state.
 * @param state		Current state.
 * @param id		Register identifier (from register_bank_t).
 * @param idx		Index in the bank (ignored for non-mutiple register bank).
 * @param value		Value to put in register.
 */
void arm_set_register(arm_state_t *state, int id, int idx, register_value_t r) {
	switch(id) {
	case 23: {
				ARM_APSR = GLISS_I;

		} break;
	case 24: {
				if((GLISS_IDX == 15))
		ARM_NPC = GLISS_I;
	else
		ARM_GPR[GLISS_IDX] = GLISS_I;

		} break;

	default:
		assert(0);
	}
}


/* handle of exceptions */
void handle_FIQ(arm_state_t *state) {
		uint32_t exn_tmp;
	exn_tmp = ARM_APSR;
	ARM_APSR = arm_set_field32(ARM_APSR, 17, 4, 0);
	ARM_SPSR = exn_tmp;
	ARM_APSR = arm_set_field32(ARM_APSR, ((uint8_t)(1)), 7, 7);
	if((14 == 15))
		ARM_NPC = (ARM_GPR[15] + 4);
	else
		ARM_GPR[14] = (ARM_GPR[15] + 4);
	ARM_GPR[15] = 28;

}
void handle_IRQ(arm_state_t *state) {
		uint32_t exn_tmp;
	exn_tmp = ARM_APSR;
	ARM_APSR = arm_set_field32(ARM_APSR, 18, 4, 0);
	ARM_SPSR = exn_tmp;
	ARM_APSR = arm_set_field32(ARM_APSR, ((uint8_t)(1)), 7, 7);
	if((14 == 15))
		ARM_NPC = (ARM_GPR[15] + 4);
	else
		ARM_GPR[14] = (ARM_GPR[15] + 4);
	ARM_GPR[15] = 24;

}


/* list of exceptions */
static arm_exception_t exceptions[] = {
	{ "FIQ", handle_FIQ, 1 },
	{ "IRQ", handle_IRQ, 1 },
	{ 0, 0, 0 }
};


/**
 * Get the list of exceptions.
 * @return	List of exceptions ended by an item whose name is null.
 */
arm_exception_t *arm_exceptions(void) {
	return exceptions;
}

