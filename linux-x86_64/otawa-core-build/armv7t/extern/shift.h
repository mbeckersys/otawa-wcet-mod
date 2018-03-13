/*!
 * Shift functions for ARMv7 Instruction Set
 *
 * \file shift.h
 * \author Thomas Jerabek
 * \date 02-2015
 *
 */

#ifndef GLISS_SHIFT_H
#define GLISS_SHIFT_H

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define GLISS_SHIFT_STATE
#define GLISS_SHIFT_INIT(s)
#define GLISS_SHIFT_DESTROY(s)
#define LSL	0
#define LSR	1
#define ASR	2
#define ROR	3
#define RRX	4

uint8_t f_get_ITSTATE(void);
uint8_t f_set_ITSTATE(uint8_t value);
uint8_t f_get_update_ITSTATE(void);
void f_calc_condition_ITSTATE(void);

uint8_t f_get_C(void);

uint32_t f_LSL_C(uint32_t value, int amount, uint8_t *carry_out);
uint32_t f_LSR_C(uint32_t value, int amount, uint8_t *carry_out);
uint32_t f_ASR_C(int32_t value, int amount, uint8_t *carry_out);
uint32_t f_ROR_C(uint32_t value, int amount, uint8_t *carry_out);
uint32_t f_RRX_C(uint32_t value, uint8_t carry_in, uint8_t *carry_out);

uint32_t f_LSL(uint32_t value, int amount);
uint32_t f_LSR(uint32_t value, int amount);
uint32_t f_ASR(int32_t value, int amount);
uint32_t f_ROR(uint32_t value, int amount);
uint32_t f_RRX(uint32_t value, uint8_t carry_in);


uint32_t Decode_and_Shift(uint8_t type, uint8_t imm5, uint32_t input_value, uint8_t CFLAG);



#if defined(__cplusplus)
}
#endif


#endif /* GLISS_SHIFT_H */
