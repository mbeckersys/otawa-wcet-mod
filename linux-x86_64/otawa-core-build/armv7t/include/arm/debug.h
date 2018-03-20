/* Generated by gep (118/02/19 18:37:34) copyright (c) 2011 IRIT - UPS */
#ifndef GLISS_ARM_ARM_DEBUG_H
#define GLISS_ARM_ARM_DEBUG_H

#include "api.h"

__BEGIN_DECLS

/* register type */
typedef enum {
	RTYPE_NONE = 0,
	RTYPE_BITS,
	RTYPE_ADDR,
	RTYPE_INT,
	RTYPE_FLOAT
} register_type_t;

/* register field description */
typedef struct {
	const char *name;
	int hbit, lbit;
} register_field_t;

/* register bank description */ 
typedef struct register_bank_t {
	int id;
	const char *name;
	const char *format;
	int size;
	register_type_t type;
	int tsize;
	union {
		register_field_t fields;
	} data;
} register_bank_t;

/* register value */
typedef union {
	int32_t iv;
	int64_t lv;
	float fv;
	double dv;
} register_value_t;

/* IRQ functions */
typedef struct arm_exception_t {
	const char *name;
	void (*fun)(arm_state_t *state);
	int is_irq;
} arm_exception_t;
	

/* functions */
register_bank_t *arm_get_registers(void);
register_value_t arm_get_register(arm_state_t *state, int id, int index);
void arm_set_register(arm_state_t *state, int id, int index, register_value_t value);
arm_exception_t *arm_exceptions(void);

/* macros avoiding customisation in debugger */
#define debug_get_registers()				arm_get_registers()
#define debug_get_register(s, id, idx)		arm_get_register(s, id, idx)
#define debug_set_register(s, id, idx, v)	arm_set_register(s, id, idx, v)
#define debug_exceptions					arm_exceptions()

__END_DECLS

#endif	// GLISS_ARM_ARM_DEBUG_H
