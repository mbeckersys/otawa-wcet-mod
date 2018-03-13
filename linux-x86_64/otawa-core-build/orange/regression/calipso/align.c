
typedef signed char int8_t;

typedef short int int16_t;

typedef int int32_t;

__extension__ typedef long long int int64_t;

typedef unsigned char uint8_t;

typedef unsigned short int uint16_t;

typedef unsigned int uint32_t;

__extension__ typedef unsigned long long int uint64_t;

typedef signed char int_least8_t;

typedef short int int_least16_t;

typedef int int_least32_t;

__extension__ typedef long long int int_least64_t;

typedef unsigned char uint_least8_t;

typedef unsigned short int uint_least16_t;

typedef unsigned int uint_least32_t;

__extension__ typedef unsigned long long int uint_least64_t;

typedef signed char int_fast8_t;

typedef int int_fast16_t;

typedef int int_fast32_t;

__extension__ typedef long long int int_fast64_t;

typedef unsigned char uint_fast8_t;

typedef unsigned int uint_fast16_t;

typedef unsigned int uint_fast32_t;

__extension__ typedef unsigned long long int uint_fast64_t;

typedef int intptr_t;

typedef unsigned int uintptr_t;

__extension__ typedef long long int intmax_t;

__extension__ typedef unsigned long long int uintmax_t;

uint32_t align(uint32_t i)
{
# 5 "originaux/align.c"
	if(i != 0)
# 5 "originaux/align.c"
	{
# 6 "originaux/align.c"
		while(i & 0x01000000)
# 7 "originaux/align.c"
			i <<= 1;
	}
# 9 "originaux/align.c"
	return i;
}

void main()
{
# 15 "originaux/align.c"
	return align(511);
}

