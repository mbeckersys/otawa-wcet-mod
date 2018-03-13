#define TARGET_ENDIANNESS little
#define HOST_ENDIANNESS little

/* TODO: update reg names */

#define ARM_SYSCALL_CODE(i, s) ((s)->GPR[0])
#define ARM_SYSCALL_MEM(s) ((s)->M)

#define ARM_SYSPARM_REG32_RCNT 4
#define ARM_SYSPARM_REG32_REG(s, i) 	((s)->GPR[3 + (i)])
#define ARM_SYSPARM_REG32_SP(s) 		((s)->GPR[1])
#define ARM_SYSPARM_REG32_RETURN(s, v)	{ (s)->GPR[3] = (v); }
#define ARM_SYSPARM_REG32_SUCCEED(s)	{ (s)->CGPR[7] = (s)->CGPR[7] & 0xFE; }
#define ARM_SYSPARM_REG32_FAILED(s)		{ (s)->CGPR[7] = (s)->CGPR[7] | 0x01; }

/* generic macro */
#define ARM_GET_R(s, i)		((s)->GPR[i])

/* compatibility */
#define sc_impl(_1, _2, _3)		arm_syscall(inst, state)
#define print(t)				printf("%s\n", t)

/* THUMB-2 decoding */
#define ARM_ORDER_BYTES_CISC	word = (buff[1] << 24) | (buff[0] << 16) | (buff[3] << 8) | buff[2];
#define ARM_INIT_PC \
	{ state->GPR[15] = platform->entry; \
	if(state->GPR[15] & 0x1) { \
		state->GPR[15] &= 0xfffffffe; \
		state->APSR |= 1<<5; \
	} }
	
/* mode bit removal */
#define ARM_PROCESS_CODE_LABEL(a)		a = a & 0xfffffffe;

#define ARM7
