/*!
 * Shift functions for ARMv7 Instruction Set
 *
 * \file shift.c
 * \author Thomas Jerabek
 * \date 02-2015
 *
 */

#include <stdio.h>

#if DBG == 12 /* use instrumentation to verify functionality */
#include "shift.h"
#include <stdio.h>
#else
#include <gliss/sys_call.h>
#include <arm/shift.h>
#endif

/* store current carry flag */
static volatile uint8_t CARRY_FLAG_SHIFT_ONLY = 0;
static volatile uint8_t ITSTATE_FOR_SYNTAX = 0;
static volatile uint8_t ITCOND_FOR_SYNTAX = 0;
static volatile uint8_t ITBLOCK_FOR_SYNTAX = 0;
static volatile uint8_t ITBLOCK_BASE_CONDITION_FOR_SYNTAX = 0;

uint8_t f_get_ITSTATE(void)
{
	return ITSTATE_FOR_SYNTAX;
}

uint8_t f_get_update_ITSTATE(void)
{
	uint8_t tmp = ITSTATE_FOR_SYNTAX;
	uint8_t tmp_condition = ITBLOCK_BASE_CONDITION_FOR_SYNTAX;

	// update condition depending on then/else (e.g., eq -> ne)
	//if ((ITBLOCK_FOR_SYNTAX & 0b11000000) == 0b10000000) 	// then -> no condition change!
	if ((ITBLOCK_FOR_SYNTAX & 0b11000000) == 0b01000000)	// else -> change base condition!
	{
		if (tmp_condition % 2 == 0)
		{
			tmp_condition++;
		}
		else
		{
			tmp_condition--;
		}
	}

	ITBLOCK_FOR_SYNTAX = ITBLOCK_FOR_SYNTAX << 2;

	if ((ITSTATE_FOR_SYNTAX & 0b00000111) == 0 )
	{
		ITSTATE_FOR_SYNTAX = 0;
	}
	else
	{
		ITSTATE_FOR_SYNTAX =  (tmp_condition << 4) | (0b00001111 & (ITSTATE_FOR_SYNTAX << 1));
	}

	return tmp;
}

/*
if t(then)... e(else)...
t = 10
e = 01
none = 00

*/
void f_calc_condition_ITSTATE(void)
{
	if ((ITSTATE_FOR_SYNTAX & 0b00001111) == 8)
	{
		ITBLOCK_FOR_SYNTAX = 0b00000000; // last condition, no changes else
	}
	else
	{
		if ((ITSTATE_FOR_SYNTAX & 0b00010000) == 0b00010000)	//firstcondition bit check
		{
			switch (ITSTATE_FOR_SYNTAX & 0b00001111)
			{
				case 0b1100: ITBLOCK_FOR_SYNTAX = 0b10000000; break;
				case 0b0100: ITBLOCK_FOR_SYNTAX = 0b01000000; break;
				case 0b1110: ITBLOCK_FOR_SYNTAX = 0b10100000; break;
				case 0b0110: ITBLOCK_FOR_SYNTAX = 0b01100000; break;
				case 0b1010: ITBLOCK_FOR_SYNTAX = 0b10010000; break;
				case 0b0010: ITBLOCK_FOR_SYNTAX = 0b01010000; break;
				case 0b1111: ITBLOCK_FOR_SYNTAX = 0b10101000; break;
				case 0b0111: ITBLOCK_FOR_SYNTAX = 0b01101000; break;
				case 0b1011: ITBLOCK_FOR_SYNTAX = 0b10011000; break;
				case 0b0011: ITBLOCK_FOR_SYNTAX = 0b01011000; break;
				case 0b1101: ITBLOCK_FOR_SYNTAX = 0b10100100; break;
				case 0b0101: ITBLOCK_FOR_SYNTAX = 0b01100100; break;
				case 0b1001: ITBLOCK_FOR_SYNTAX = 0b10010100; break;
				case 0b0001: ITBLOCK_FOR_SYNTAX = 0b01010100; break;
				default:  ITBLOCK_FOR_SYNTAX = 0b00000000;  break;
			}
		}
		else
		{
			switch (ITSTATE_FOR_SYNTAX & 0b00001111)
			{
				case 0b0100: ITBLOCK_FOR_SYNTAX = 0b10000000; break;
				case 0b1100: ITBLOCK_FOR_SYNTAX = 0b01000000; break;
				case 0b0010: ITBLOCK_FOR_SYNTAX = 0b10100000; break;
				case 0b1010: ITBLOCK_FOR_SYNTAX = 0b01100000; break;
				case 0b0110: ITBLOCK_FOR_SYNTAX = 0b10010000; break;
				case 0b1110: ITBLOCK_FOR_SYNTAX = 0b01010000; break;
				case 0b0001: ITBLOCK_FOR_SYNTAX = 0b10101000; break;
				case 0b1001: ITBLOCK_FOR_SYNTAX = 0b01101000; break;
				case 0b0101: ITBLOCK_FOR_SYNTAX = 0b10011000; break;
				case 0b1101: ITBLOCK_FOR_SYNTAX = 0b01011000; break;
				case 0b0011: ITBLOCK_FOR_SYNTAX = 0b10100100; break;
				case 0b1011: ITBLOCK_FOR_SYNTAX = 0b01100100; break;
				case 0b0111: ITBLOCK_FOR_SYNTAX = 0b10010100; break;
				case 0b1111: ITBLOCK_FOR_SYNTAX = 0b01010100; break;
				default: ITBLOCK_FOR_SYNTAX = 0b00000000; break;
			}
		}
	}
}


uint8_t f_set_ITSTATE(uint8_t value)
{
    ITSTATE_FOR_SYNTAX = value;
	ITBLOCK_BASE_CONDITION_FOR_SYNTAX = value >> 4; // condition
	f_calc_condition_ITSTATE();
	return value;
}

uint8_t f_get_C(void)
{
    return CARRY_FLAG_SHIFT_ONLY;
}

/* Logical Shift Left */
uint32_t f_LSL_C(uint32_t value, int shift, uint8_t *carry_out)
{
    uint32_t tmp = 0;

    *carry_out = 0;

    if(shift > 0)
    {
        tmp = value << shift;
        if(((value >> (32-shift)) & 0x00000001) == 1)
        {
            *carry_out = 1;
        }
    }
    else
    {
        printf("Error: f_LSL_C;value:%d,shift:%d\n",value,shift);
    }

    return tmp;
}

/* Logical Shift Left with 0 shift */
uint32_t f_LSL(uint32_t value, int shift) {
    uint32_t tmp = 0;
    uint8_t carry;
    if(shift == 0)
        tmp = value;
    else
        tmp = f_LSL_C(value, shift, &carry);
 
    return tmp;
}

/* Logical Shift Right */
uint32_t f_LSR_C(uint32_t value, int shift, uint8_t *carry_out)
{
    uint32_t tmp = 0;

    *carry_out = 0;

    if(shift > 0)
    {
        tmp = value >> shift;
        if(((value >> (shift-1)) & 0x00000001) == 1)
        {
            *carry_out = 1;
        }
    }
    else
    {
        printf("Error: f_LSR_C;value:%d,shift:%d\n",value,shift);
    }

    return tmp;
}

/* Logical Shift Right with 0 shift */
uint32_t f_LSR(uint32_t value, int shift)
{
    uint32_t tmp = 0;
    uint8_t carry;
    if(shift == 0)
    {
        tmp = value;
    }
    else
    {
        tmp = f_LSR_C(value,shift,&carry);
    }

    return tmp;
}


/* Arithmetic Shift Right */
uint32_t f_ASR_C(int32_t value, int shift, uint8_t *carry_out)
{
    uint32_t tmp = value;

    *carry_out = 0;

    if(shift > 0)
    {
        if(value > 0)
        {
            tmp = value >> shift;
        }
        else if (value < 0)
        {
             /*
                e.g.: value = 1011 1001, shift = 4
                0000 1011 right shift;
                0000 1111 shifted mask
                1111 0000 invert mask
                1111 1011 make OR
            */
            tmp = value >> shift | ~(~0U >> shift);
        }
        /* else value is zero */

        if(((value >> (shift-1)) & 0x00000001) == 1)
        {
            *carry_out = 1;
        }
    }
    else
    {
       printf("Error: f_ASR_C;value:%d,shift:%d\n",value,shift);
    }

    return tmp;
}

/*  Arithmetic Shift Right with 0 shift */
uint32_t f_ASR(int32_t value, int shift)
{
    uint32_t tmp = 0;
    uint8_t carry;
    if(shift == 0)
    {
        tmp = value;
    }
    else
    {
        tmp = f_ASR_C(value,shift,&carry);
    }

    return tmp;
}


/* Rotate Right */
uint32_t f_ROR_C(uint32_t value, int shift, uint8_t *carry_out)
{
    uint32_t tmp = 0;

    *carry_out = 0;

    if(shift > 0)
    {
        tmp = (value >> shift) | (value <<(32-shift));
        /* last shifted bit */
        if((tmp & 0x80000000) == 0x80000000)
        {
            *carry_out = 1;
        }
    }
    else
    {
       printf("Error: f_ROR_C;value:%d,shift:%d\n",value,shift);
    }

    return tmp;
}

/* Rotate Right with 0 shift */
uint32_t f_ROR(uint32_t value, int shift)
{
    uint32_t tmp = 0;
    uint8_t carry;
    if(shift == 0)
    {
        tmp = value;
    }
    else
    {
        tmp = f_ROR_C(value,shift,&carry);
    }

    return tmp;
}


/* Rotate Right with Extend */
uint32_t f_RRX_C(uint32_t value, uint8_t carry_in, uint8_t *carry_out) {
    *carry_out = value & 0x00000001; /* lsb */

    return ((value >> 1) | (carry_in<<31));
}

/* Rotate Right with Extend with 0 shift */
uint32_t f_RRX(uint32_t value, uint8_t carry_in) {
    uint8_t carry;
    return f_RRX_C(value, carry_in, &carry);
}


/*
combines
    DecodeImmShift(bits(2) type, bits(5) imm5)
    Shift(bits(N) value, SRType type, integer amount, bit carry_in)
    imm5 = shift_n
*/
uint32_t Decode_and_Shift(uint8_t type, uint8_t imm5, uint32_t input_value, uint8_t CFLAG)
{
    uint8_t shift_n;
    uint32_t value;
    uint8_t carry_out = 0;

    switch(type)
	{
		case 0:
            if(imm5 == 0)
            {
                value = input_value;
            }
            else
            {
                shift_n = imm5;
                value = f_LSL_C(input_value,shift_n,&carry_out);
			}
			break;

		case 1:
			if(imm5 == 0)
			{
				shift_n = 32;
			}
			else
			{
				shift_n = imm5;
			}
			value = f_LSR_C(input_value,shift_n,&carry_out);
			break;

		case 2:
			if(imm5 == 0)
			{
				shift_n = 32;
			}
			else
			{
				shift_n = imm5;
			}
			value = f_ASR_C(input_value,shift_n,&carry_out);
			break;

		case 3:
            if(imm5 == 0)
			{
				value = f_RRX_C(input_value,CFLAG,&carry_out);
			}
			else
			{
				shift_n = imm5;
				value = f_ROR_C(input_value,shift_n,&carry_out);
			}
			break;
        case 4:
            shift_n = imm5;
            value = f_ROR_C(input_value,shift_n,&carry_out);
			break;
	}

    CARRY_FLAG_SHIFT_ONLY = carry_out;

    return value;
}
