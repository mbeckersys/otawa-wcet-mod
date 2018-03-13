#ifndef ARM_LINUX_ENV_H
#define ARM_LINUX_ENV_H

#include "api.h"
#include "loader.h"

#if defined(__cplusplus)
    extern  "C" {
#endif


/* module name: env */

#define ARM_ENV_STATE
#define ARM_ENV_INIT(s)
#define ARM_ENV_DESTROY(s)


/* system initialization (used internally during platform and state initialization) */
void arm_stack_fill_env(arm_loader_t *loader, arm_platform_t *platform,  arm_env_t *env);
void arm_registers_fill_env(arm_env_t *env, arm_state_t *state);
void arm_set_brk(arm_platform_t *pf, arm_address_t address);

#if defined(__cplusplus)
}
#endif

#endif /* ARM_LINUX_ENV_H */
