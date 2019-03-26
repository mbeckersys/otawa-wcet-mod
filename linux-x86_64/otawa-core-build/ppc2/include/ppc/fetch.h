/* Generated by gep (119/02/26 23:30:57) copyright (c) 2008 IRIT - UPS */

#ifndef GLISS_PPC_INCLUDE_PPC_FETCH_H
#define GLISS_PPC_INCLUDE_PPC_FETCH_H


#if defined(__cplusplus)
extern  "C"
{
#endif

#include "api.h"
#include "config.h"

#define PPC_FETCH_STATE
#define PPC_FETCH_INIT(s)
#define PPC_FETCH_DESTROY(s)

/* fetch structure */
struct ppc_fetch_t
{
	/* the memory which we are supposed to fetch from, useful on Harvard architectures where we deal with several memories */
	ppc_memory_t *mem;
/* state used to determine correct fetch */
	ppc_state_t *state;};

#if defined(__cplusplus)
}
#endif

#endif /* GLISS_PPC_INCLUDE_PPC_FETCH_H */
