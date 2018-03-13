#ifndef ARM_SYS_CALL_H
#define ARM_SYS_CALL_H

#if defined(__cplusplus)
extern "C" {
#endif

#define ARM_SYS_CALL_STATE
#define ARM_SYS_CALL_INIT(s)
#define ARM_SYS_CALL_DESTROY(s)

void swi_impl(int code);

#if defined(__cplusplus)
}
#endif


#endif /* ARM_SYS_CALL_H */
