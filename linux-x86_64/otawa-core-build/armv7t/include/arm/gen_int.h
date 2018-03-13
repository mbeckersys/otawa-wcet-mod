/* Generated by gep ($(date)) copyright (c) 2008 IRIT - UPS */

#ifndef ARM_ARM_INCLUDE_GEN_INT_H
#define ARM_ARM_INCLUDE_GEN_INT_H


#if defined(__cplusplus)
extern  "C"
{
#endif


#define ARM_GEN_INT_STATE
#define ARM_GEN_INT_INIT(s)
#define ARM_GEN_INT_DESTROY(s)


/* struct used to store masks and as buffer for instruction codes or any binary value which cannot fit into an uintN_t */
/* chunks are arranged in the same order as in memory, msb first, lsb last */
struct mask_t {
	uint32_t *mask;
	int bit_length;
};



#if defined(__cplusplus)
}
#endif

#endif /* ARM_ARM_INCLUDE_GEN_INT_H */
