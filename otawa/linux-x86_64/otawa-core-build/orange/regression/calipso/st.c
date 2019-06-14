
typedef unsigned char __u_char;

typedef unsigned short int __u_short;

typedef unsigned int __u_int;

typedef unsigned long int __u_long;

typedef signed char __int8_t;

typedef unsigned char __uint8_t;

typedef signed short int __int16_t;

typedef unsigned short int __uint16_t;

typedef signed int __int32_t;

typedef unsigned int __uint32_t;

__extension__ typedef signed long long int __int64_t;

__extension__ typedef unsigned long long int __uint64_t;

__extension__ typedef long long int __quad_t;

__extension__ typedef unsigned long long int __u_quad_t;

__extension__ typedef __u_quad_t __dev_t;

__extension__ typedef unsigned int __uid_t;

__extension__ typedef unsigned int __gid_t;

__extension__ typedef unsigned long int __ino_t;

__extension__ typedef __u_quad_t __ino64_t;

__extension__ typedef unsigned int __mode_t;

__extension__ typedef unsigned int __nlink_t;

__extension__ typedef long int __off_t;

__extension__ typedef __quad_t __off64_t;

__extension__ typedef int __pid_t;

__extension__ typedef struct  {
	int __val[2];
} __fsid_t;

__extension__ typedef long int __clock_t;

__extension__ typedef unsigned long int __rlim_t;

__extension__ typedef __u_quad_t __rlim64_t;

__extension__ typedef unsigned int __id_t;

__extension__ typedef long int __time_t;

__extension__ typedef unsigned int __useconds_t;

__extension__ typedef long int __suseconds_t;

__extension__ typedef int __daddr_t;

__extension__ typedef long int __swblk_t;

__extension__ typedef int __key_t;

__extension__ typedef int __clockid_t;

__extension__ typedef void *__timer_t;

__extension__ typedef long int __blksize_t;

__extension__ typedef long int __blkcnt_t;

__extension__ typedef __quad_t __blkcnt64_t;

__extension__ typedef unsigned long int __fsblkcnt_t;

__extension__ typedef __u_quad_t __fsblkcnt64_t;

__extension__ typedef unsigned long int __fsfilcnt_t;

__extension__ typedef __u_quad_t __fsfilcnt64_t;

__extension__ typedef int __ssize_t;

typedef __off64_t __loff_t;

typedef __quad_t *__qaddr_t;

typedef char *__caddr_t;

__extension__ typedef int __intptr_t;

__extension__ typedef unsigned int __socklen_t;

typedef __u_char u_char;

typedef __u_short u_short;

typedef __u_int u_int;

typedef __u_long u_long;

typedef __quad_t quad_t;

typedef __u_quad_t u_quad_t;

typedef __fsid_t fsid_t;

typedef __loff_t loff_t;

typedef __ino_t ino_t;

typedef __dev_t dev_t;

typedef __gid_t gid_t;

typedef __mode_t mode_t;

typedef __nlink_t nlink_t;

typedef __uid_t uid_t;

typedef __off_t off_t;

typedef __pid_t pid_t;

typedef __id_t id_t;

typedef __ssize_t ssize_t;

typedef __daddr_t daddr_t;

typedef __caddr_t caddr_t;

typedef __key_t key_t;

typedef __time_t time_t;

typedef __clockid_t clockid_t;

typedef __timer_t timer_t;

typedef unsigned int size_t;

typedef unsigned long int ulong;

typedef unsigned short int ushort;

typedef unsigned int uint;

typedef int int8_t __attribute__ ((__mode__(__QI__))) ;

typedef int int16_t __attribute__ ((__mode__(__HI__))) ;

typedef int int32_t __attribute__ ((__mode__(__SI__))) ;

typedef int int64_t __attribute__ ((__mode__(__DI__))) ;

typedef unsigned int u_int8_t __attribute__ ((__mode__(__QI__))) ;

typedef unsigned int u_int16_t __attribute__ ((__mode__(__HI__))) ;

typedef unsigned int u_int32_t __attribute__ ((__mode__(__SI__))) ;

typedef unsigned int u_int64_t __attribute__ ((__mode__(__DI__))) ;

typedef int register_t __attribute__ ((__mode__(__word__))) ;

typedef int __sig_atomic_t;

typedef struct  {
	unsigned long int __val[1024 / ((8 * sizeof(unsigned long int)))];
} __sigset_t;

typedef __sigset_t sigset_t;

struct timespec {
	__time_t tv_sec;
	long int tv_nsec;
} ;

struct timeval {
	__time_t tv_sec;
	__suseconds_t tv_usec;
} ;

typedef __suseconds_t suseconds_t;

typedef long int __fd_mask;

typedef struct  {
	__fd_mask __fds_bits[1024 / ((8 * sizeof(__fd_mask)))];
} fd_set;

typedef __fd_mask fd_mask;

extern int select(int __nfds, fd_set * __restrict __readfds, fd_set * __restrict
	__writefds, fd_set * __restrict __exceptfds, struct timeval * __restrict
	__timeout);
extern int pselect(int __nfds, fd_set * __restrict __readfds, fd_set
	* __restrict __writefds, fd_set * __restrict __exceptfds,
	struct timespec  const * __restrict __timeout, __sigset_t
	 const * __restrict __sigmask);
extern unsigned int gnu_dev_major(unsigned long long int
	__dev) __attribute__ ((__nothrow__)) ;
extern unsigned int gnu_dev_minor(unsigned long long int
	__dev) __attribute__ ((__nothrow__)) ;
extern unsigned long long int gnu_dev_makedev(unsigned int __major, unsigned int
	__minor) __attribute__ ((__nothrow__)) ;

typedef __blkcnt_t blkcnt_t;

typedef __fsblkcnt_t fsblkcnt_t;

typedef __fsfilcnt_t fsfilcnt_t;

typedef unsigned long int pthread_t;

typedef union  {
	char __size[36];
	long int __align;
} pthread_attr_t;

typedef struct __pthread_internal_slist {
	struct __pthread_internal_slist *__next;
} __pthread_slist_t;

typedef union  {
	struct __pthread_mutex_s {
		int __lock;
		unsigned int __count;
		int __owner;
		int __kind;
		unsigned int __nusers;
		union  {
			int __spins;
			__pthread_slist_t __list;
		} ;
	} __data;
	char __size[24];
	long int __align;
} pthread_mutex_t;

typedef union  {
	char __size[4];
	int __align;
} pthread_mutexattr_t;

typedef union  {
	struct  {
		int __lock;
		unsigned int __futex;
		unsigned long long int __total_seq;
		unsigned long long int __wakeup_seq;
		unsigned long long int __woken_seq;
		void *__mutex;
		unsigned int __nwaiters;
		unsigned int __broadcast_seq;
	} __data;
	char __size[48];
	long long int __align;
} pthread_cond_t;

typedef union  {
	char __size[4];
	int __align;
} pthread_condattr_t;

typedef unsigned int pthread_key_t;

typedef int pthread_once_t;

typedef union  {
	struct  {
		int __lock;
		unsigned int __nr_readers;
		unsigned int __readers_wakeup;
		unsigned int __writer_wakeup;
		unsigned int __nr_readers_queued;
		unsigned int __nr_writers_queued;
		unsigned char __flags;
		unsigned char __shared;
		unsigned char __pad1;
		unsigned char __pad2;
		int __writer;
	} __data;
	char __size[32];
	long int __align;
} pthread_rwlock_t;

typedef union  {
	char __size[8];
	long int __align;
} pthread_rwlockattr_t;

typedef int  volatile pthread_spinlock_t;

typedef union  {
	char __size[20];
	long int __align;
} pthread_barrier_t;

typedef union  {
	char __size[4];
	int __align;
} pthread_barrierattr_t;

typedef __clock_t clock_t;

struct tms {
	clock_t tms_utime;
	clock_t tms_stime;
	clock_t tms_cutime;
	clock_t tms_cstime;
} ;

extern clock_t times(struct tms *__buffer) __attribute__ ((__nothrow__)) ;
extern double acos(double __x) __attribute__ ((__nothrow__)) ;
extern double __acos(double __x) __attribute__ ((__nothrow__)) ;
extern double asin(double __x) __attribute__ ((__nothrow__)) ;
extern double __asin(double __x) __attribute__ ((__nothrow__)) ;
extern double atan(double __x) __attribute__ ((__nothrow__)) ;
extern double __atan(double __x) __attribute__ ((__nothrow__)) ;
extern double atan2(double __y, double __x) __attribute__ ((__nothrow__)) ;
extern double __atan2(double __y, double __x) __attribute__ ((__nothrow__)) ;
extern double cos(double __x) __attribute__ ((__nothrow__)) ;
extern double __cos(double __x) __attribute__ ((__nothrow__)) ;
extern double sin(double __x) __attribute__ ((__nothrow__)) ;
extern double __sin(double __x) __attribute__ ((__nothrow__)) ;
extern double tan(double __x) __attribute__ ((__nothrow__)) ;
extern double __tan(double __x) __attribute__ ((__nothrow__)) ;
extern double cosh(double __x) __attribute__ ((__nothrow__)) ;
extern double __cosh(double __x) __attribute__ ((__nothrow__)) ;
extern double sinh(double __x) __attribute__ ((__nothrow__)) ;
extern double __sinh(double __x) __attribute__ ((__nothrow__)) ;
extern double tanh(double __x) __attribute__ ((__nothrow__)) ;
extern double __tanh(double __x) __attribute__ ((__nothrow__)) ;
extern double acosh(double __x) __attribute__ ((__nothrow__)) ;
extern double __acosh(double __x) __attribute__ ((__nothrow__)) ;
extern double asinh(double __x) __attribute__ ((__nothrow__)) ;
extern double __asinh(double __x) __attribute__ ((__nothrow__)) ;
extern double atanh(double __x) __attribute__ ((__nothrow__)) ;
extern double __atanh(double __x) __attribute__ ((__nothrow__)) ;
extern double exp(double __x) __attribute__ ((__nothrow__)) ;
extern double __exp(double __x) __attribute__ ((__nothrow__)) ;
extern double frexp(double __x, int *__exponent) __attribute__ ((__nothrow__)) ;
extern double __frexp(double __x, int
	*__exponent) __attribute__ ((__nothrow__)) ;
extern double ldexp(double __x, int __exponent) __attribute__ ((__nothrow__)) ;
extern double __ldexp(double __x, int
	__exponent) __attribute__ ((__nothrow__)) ;
extern double log(double __x) __attribute__ ((__nothrow__)) ;
extern double __log(double __x) __attribute__ ((__nothrow__)) ;
extern double log10(double __x) __attribute__ ((__nothrow__)) ;
extern double __log10(double __x) __attribute__ ((__nothrow__)) ;
extern double modf(double __x, double *__iptr) __attribute__ ((__nothrow__)) ;
extern double __modf(double __x, double *__iptr) __attribute__ ((__nothrow__)) ;
extern double expm1(double __x) __attribute__ ((__nothrow__)) ;
extern double __expm1(double __x) __attribute__ ((__nothrow__)) ;
extern double log1p(double __x) __attribute__ ((__nothrow__)) ;
extern double __log1p(double __x) __attribute__ ((__nothrow__)) ;
extern double logb(double __x) __attribute__ ((__nothrow__)) ;
extern double __logb(double __x) __attribute__ ((__nothrow__)) ;
extern double pow(double __x, double __y) __attribute__ ((__nothrow__)) ;
extern double __pow(double __x, double __y) __attribute__ ((__nothrow__)) ;
extern double sqrt(double __x) __attribute__ ((__nothrow__)) ;
extern double __sqrt(double __x) __attribute__ ((__nothrow__)) ;
extern double hypot(double __x, double __y) __attribute__ ((__nothrow__)) ;
extern double __hypot(double __x, double __y) __attribute__ ((__nothrow__)) ;
extern double cbrt(double __x) __attribute__ ((__nothrow__)) ;
extern double __cbrt(double __x) __attribute__ ((__nothrow__)) ;
extern double ceil(double __x) __attribute__ ((__const__, __nothrow__)) ;
extern double __ceil(double __x) __attribute__ ((__const__, __nothrow__)) ;
extern double fabs(double __x) __attribute__ ((__const__, __nothrow__)) ;
extern double __fabs(double __x) __attribute__ ((__const__, __nothrow__)) ;
extern double floor(double __x) __attribute__ ((__const__, __nothrow__)) ;
extern double __floor(double __x) __attribute__ ((__const__, __nothrow__)) ;
extern double fmod(double __x, double __y) __attribute__ ((__nothrow__)) ;
extern double __fmod(double __x, double __y) __attribute__ ((__nothrow__)) ;
extern int __isinf(double __value) __attribute__ ((__const__, __nothrow__)) ;
extern int __finite(double __value) __attribute__ ((__const__, __nothrow__)) ;
extern int isinf(double __value) __attribute__ ((__const__, __nothrow__)) ;
extern int finite(double __value) __attribute__ ((__const__, __nothrow__)) ;
extern double drem(double __x, double __y) __attribute__ ((__nothrow__)) ;
extern double __drem(double __x, double __y) __attribute__ ((__nothrow__)) ;
extern double significand(double __x) __attribute__ ((__nothrow__)) ;
extern double __significand(double __x) __attribute__ ((__nothrow__)) ;
extern double copysign(double __x, double __y) __attribute__ ((__const__,
	__nothrow__)) ;
extern double __copysign(double __x, double __y) __attribute__ ((__const__,
	__nothrow__)) ;
extern int __isnan(double __value) __attribute__ ((__const__, __nothrow__)) ;
extern int isnan(double __value) __attribute__ ((__const__, __nothrow__)) ;
extern double j0(double ) __attribute__ ((__nothrow__)) ;
extern double __j0(double ) __attribute__ ((__nothrow__)) ;
extern double j1(double ) __attribute__ ((__nothrow__)) ;
extern double __j1(double ) __attribute__ ((__nothrow__)) ;
extern double jn(int , double ) __attribute__ ((__nothrow__)) ;
extern double __jn(int , double ) __attribute__ ((__nothrow__)) ;
extern double y0(double ) __attribute__ ((__nothrow__)) ;
extern double __y0(double ) __attribute__ ((__nothrow__)) ;
extern double y1(double ) __attribute__ ((__nothrow__)) ;
extern double __y1(double ) __attribute__ ((__nothrow__)) ;
extern double yn(int , double ) __attribute__ ((__nothrow__)) ;
extern double __yn(int , double ) __attribute__ ((__nothrow__)) ;
extern double erf(double ) __attribute__ ((__nothrow__)) ;
extern double __erf(double ) __attribute__ ((__nothrow__)) ;
extern double erfc(double ) __attribute__ ((__nothrow__)) ;
extern double __erfc(double ) __attribute__ ((__nothrow__)) ;
extern double lgamma(double ) __attribute__ ((__nothrow__)) ;
extern double __lgamma(double ) __attribute__ ((__nothrow__)) ;
extern double gamma(double ) __attribute__ ((__nothrow__)) ;
extern double __gamma(double ) __attribute__ ((__nothrow__)) ;
extern double lgamma_r(double , int *__signgamp) __attribute__ ((__nothrow__)) ;
extern double __lgamma_r(double , int
	*__signgamp) __attribute__ ((__nothrow__)) ;
extern double rint(double __x) __attribute__ ((__nothrow__)) ;
extern double __rint(double __x) __attribute__ ((__nothrow__)) ;
extern double nextafter(double __x, double __y) __attribute__ ((__const__,
	__nothrow__)) ;
extern double __nextafter(double __x, double __y) __attribute__ ((__const__,
	__nothrow__)) ;
extern double remainder(double __x, double __y) __attribute__ ((__nothrow__)) ;
extern double __remainder(double __x, double
	__y) __attribute__ ((__nothrow__)) ;
extern double scalbn(double __x, int __n) __attribute__ ((__nothrow__)) ;
extern double __scalbn(double __x, int __n) __attribute__ ((__nothrow__)) ;
extern int ilogb(double __x) __attribute__ ((__nothrow__)) ;
extern int __ilogb(double __x) __attribute__ ((__nothrow__)) ;
extern double scalb(double __x, double __n) __attribute__ ((__nothrow__)) ;
extern double __scalb(double __x, double __n) __attribute__ ((__nothrow__)) ;
extern float acosf(float __x) __attribute__ ((__nothrow__)) ;
extern float __acosf(float __x) __attribute__ ((__nothrow__)) ;
extern float asinf(float __x) __attribute__ ((__nothrow__)) ;
extern float __asinf(float __x) __attribute__ ((__nothrow__)) ;
extern float atanf(float __x) __attribute__ ((__nothrow__)) ;
extern float __atanf(float __x) __attribute__ ((__nothrow__)) ;
extern float atan2f(float __y, float __x) __attribute__ ((__nothrow__)) ;
extern float __atan2f(float __y, float __x) __attribute__ ((__nothrow__)) ;
extern float cosf(float __x) __attribute__ ((__nothrow__)) ;
extern float __cosf(float __x) __attribute__ ((__nothrow__)) ;
extern float sinf(float __x) __attribute__ ((__nothrow__)) ;
extern float __sinf(float __x) __attribute__ ((__nothrow__)) ;
extern float tanf(float __x) __attribute__ ((__nothrow__)) ;
extern float __tanf(float __x) __attribute__ ((__nothrow__)) ;
extern float coshf(float __x) __attribute__ ((__nothrow__)) ;
extern float __coshf(float __x) __attribute__ ((__nothrow__)) ;
extern float sinhf(float __x) __attribute__ ((__nothrow__)) ;
extern float __sinhf(float __x) __attribute__ ((__nothrow__)) ;
extern float tanhf(float __x) __attribute__ ((__nothrow__)) ;
extern float __tanhf(float __x) __attribute__ ((__nothrow__)) ;
extern float acoshf(float __x) __attribute__ ((__nothrow__)) ;
extern float __acoshf(float __x) __attribute__ ((__nothrow__)) ;
extern float asinhf(float __x) __attribute__ ((__nothrow__)) ;
extern float __asinhf(float __x) __attribute__ ((__nothrow__)) ;
extern float atanhf(float __x) __attribute__ ((__nothrow__)) ;
extern float __atanhf(float __x) __attribute__ ((__nothrow__)) ;
extern float expf(float __x) __attribute__ ((__nothrow__)) ;
extern float __expf(float __x) __attribute__ ((__nothrow__)) ;
extern float frexpf(float __x, int *__exponent) __attribute__ ((__nothrow__)) ;
extern float __frexpf(float __x, int
	*__exponent) __attribute__ ((__nothrow__)) ;
extern float ldexpf(float __x, int __exponent) __attribute__ ((__nothrow__)) ;
extern float __ldexpf(float __x, int __exponent) __attribute__ ((__nothrow__)) ;
extern float logf(float __x) __attribute__ ((__nothrow__)) ;
extern float __logf(float __x) __attribute__ ((__nothrow__)) ;
extern float log10f(float __x) __attribute__ ((__nothrow__)) ;
extern float __log10f(float __x) __attribute__ ((__nothrow__)) ;
extern float modff(float __x, float *__iptr) __attribute__ ((__nothrow__)) ;
extern float __modff(float __x, float *__iptr) __attribute__ ((__nothrow__)) ;
extern float expm1f(float __x) __attribute__ ((__nothrow__)) ;
extern float __expm1f(float __x) __attribute__ ((__nothrow__)) ;
extern float log1pf(float __x) __attribute__ ((__nothrow__)) ;
extern float __log1pf(float __x) __attribute__ ((__nothrow__)) ;
extern float logbf(float __x) __attribute__ ((__nothrow__)) ;
extern float __logbf(float __x) __attribute__ ((__nothrow__)) ;
extern float powf(float __x, float __y) __attribute__ ((__nothrow__)) ;
extern float __powf(float __x, float __y) __attribute__ ((__nothrow__)) ;
extern float sqrtf(float __x) __attribute__ ((__nothrow__)) ;
extern float __sqrtf(float __x) __attribute__ ((__nothrow__)) ;
extern float hypotf(float __x, float __y) __attribute__ ((__nothrow__)) ;
extern float __hypotf(float __x, float __y) __attribute__ ((__nothrow__)) ;
extern float cbrtf(float __x) __attribute__ ((__nothrow__)) ;
extern float __cbrtf(float __x) __attribute__ ((__nothrow__)) ;
extern float ceilf(float __x) __attribute__ ((__const__, __nothrow__)) ;
extern float __ceilf(float __x) __attribute__ ((__const__, __nothrow__)) ;
extern float fabsf(float __x) __attribute__ ((__const__, __nothrow__)) ;
extern float __fabsf(float __x) __attribute__ ((__const__, __nothrow__)) ;
extern float floorf(float __x) __attribute__ ((__const__, __nothrow__)) ;
extern float __floorf(float __x) __attribute__ ((__const__, __nothrow__)) ;
extern float fmodf(float __x, float __y) __attribute__ ((__nothrow__)) ;
extern float __fmodf(float __x, float __y) __attribute__ ((__nothrow__)) ;
extern int __isinff(float __value) __attribute__ ((__const__, __nothrow__)) ;
extern int __finitef(float __value) __attribute__ ((__const__, __nothrow__)) ;
extern int isinff(float __value) __attribute__ ((__const__, __nothrow__)) ;
extern int finitef(float __value) __attribute__ ((__const__, __nothrow__)) ;
extern float dremf(float __x, float __y) __attribute__ ((__nothrow__)) ;
extern float __dremf(float __x, float __y) __attribute__ ((__nothrow__)) ;
extern float significandf(float __x) __attribute__ ((__nothrow__)) ;
extern float __significandf(float __x) __attribute__ ((__nothrow__)) ;
extern float copysignf(float __x, float __y) __attribute__ ((__const__,
	__nothrow__)) ;
extern float __copysignf(float __x, float __y) __attribute__ ((__const__,
	__nothrow__)) ;
extern int __isnanf(float __value) __attribute__ ((__const__, __nothrow__)) ;
extern int isnanf(float __value) __attribute__ ((__const__, __nothrow__)) ;
extern float j0f(float ) __attribute__ ((__nothrow__)) ;
extern float __j0f(float ) __attribute__ ((__nothrow__)) ;
extern float j1f(float ) __attribute__ ((__nothrow__)) ;
extern float __j1f(float ) __attribute__ ((__nothrow__)) ;
extern float jnf(int , float ) __attribute__ ((__nothrow__)) ;
extern float __jnf(int , float ) __attribute__ ((__nothrow__)) ;
extern float y0f(float ) __attribute__ ((__nothrow__)) ;
extern float __y0f(float ) __attribute__ ((__nothrow__)) ;
extern float y1f(float ) __attribute__ ((__nothrow__)) ;
extern float __y1f(float ) __attribute__ ((__nothrow__)) ;
extern float ynf(int , float ) __attribute__ ((__nothrow__)) ;
extern float __ynf(int , float ) __attribute__ ((__nothrow__)) ;
extern float erff(float ) __attribute__ ((__nothrow__)) ;
extern float __erff(float ) __attribute__ ((__nothrow__)) ;
extern float erfcf(float ) __attribute__ ((__nothrow__)) ;
extern float __erfcf(float ) __attribute__ ((__nothrow__)) ;
extern float lgammaf(float ) __attribute__ ((__nothrow__)) ;
extern float __lgammaf(float ) __attribute__ ((__nothrow__)) ;
extern float gammaf(float ) __attribute__ ((__nothrow__)) ;
extern float __gammaf(float ) __attribute__ ((__nothrow__)) ;
extern float lgammaf_r(float , int *__signgamp) __attribute__ ((__nothrow__)) ;
extern float __lgammaf_r(float , int
	*__signgamp) __attribute__ ((__nothrow__)) ;
extern float rintf(float __x) __attribute__ ((__nothrow__)) ;
extern float __rintf(float __x) __attribute__ ((__nothrow__)) ;
extern float nextafterf(float __x, float __y) __attribute__ ((__const__,
	__nothrow__)) ;
extern float __nextafterf(float __x, float __y) __attribute__ ((__const__,
	__nothrow__)) ;
extern float remainderf(float __x, float __y) __attribute__ ((__nothrow__)) ;
extern float __remainderf(float __x, float __y) __attribute__ ((__nothrow__)) ;
extern float scalbnf(float __x, int __n) __attribute__ ((__nothrow__)) ;
extern float __scalbnf(float __x, int __n) __attribute__ ((__nothrow__)) ;
extern int ilogbf(float __x) __attribute__ ((__nothrow__)) ;
extern int __ilogbf(float __x) __attribute__ ((__nothrow__)) ;
extern float scalbf(float __x, float __n) __attribute__ ((__nothrow__)) ;
extern float __scalbf(float __x, float __n) __attribute__ ((__nothrow__)) ;
extern long double acosl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __acosl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double asinl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __asinl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double atanl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __atanl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double atan2l(long double __y, long double
	__x) __attribute__ ((__nothrow__)) ;
extern long double __atan2l(long double __y, long double
	__x) __attribute__ ((__nothrow__)) ;
extern long double cosl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __cosl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double sinl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __sinl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double tanl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __tanl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double coshl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __coshl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double sinhl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __sinhl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double tanhl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __tanhl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double acoshl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __acoshl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double asinhl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __asinhl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double atanhl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __atanhl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double expl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __expl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double frexpl(long double __x, int
	*__exponent) __attribute__ ((__nothrow__)) ;
extern long double __frexpl(long double __x, int
	*__exponent) __attribute__ ((__nothrow__)) ;
extern long double ldexpl(long double __x, int
	__exponent) __attribute__ ((__nothrow__)) ;
extern long double __ldexpl(long double __x, int
	__exponent) __attribute__ ((__nothrow__)) ;
extern long double logl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __logl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double log10l(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __log10l(long double __x) __attribute__ ((__nothrow__)) ;
extern long double modfl(long double __x, long double
	*__iptr) __attribute__ ((__nothrow__)) ;
extern long double __modfl(long double __x, long double
	*__iptr) __attribute__ ((__nothrow__)) ;
extern long double expm1l(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __expm1l(long double __x) __attribute__ ((__nothrow__)) ;
extern long double log1pl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __log1pl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double logbl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __logbl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double powl(long double __x, long double
	__y) __attribute__ ((__nothrow__)) ;
extern long double __powl(long double __x, long double
	__y) __attribute__ ((__nothrow__)) ;
extern long double sqrtl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __sqrtl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double hypotl(long double __x, long double
	__y) __attribute__ ((__nothrow__)) ;
extern long double __hypotl(long double __x, long double
	__y) __attribute__ ((__nothrow__)) ;
extern long double cbrtl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __cbrtl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double ceill(long double __x) __attribute__ ((__const__,
	__nothrow__)) ;
extern long double __ceill(long double __x) __attribute__ ((__const__,
	__nothrow__)) ;
extern long double fabsl(long double __x) __attribute__ ((__const__,
	__nothrow__)) ;
extern long double __fabsl(long double __x) __attribute__ ((__const__,
	__nothrow__)) ;
extern long double floorl(long double __x) __attribute__ ((__const__,
	__nothrow__)) ;
extern long double __floorl(long double __x) __attribute__ ((__const__,
	__nothrow__)) ;
extern long double fmodl(long double __x, long double
	__y) __attribute__ ((__nothrow__)) ;
extern long double __fmodl(long double __x, long double
	__y) __attribute__ ((__nothrow__)) ;
extern int __isinfl(long double __value) __attribute__ ((__const__,
	__nothrow__)) ;
extern int __finitel(long double __value) __attribute__ ((__const__,
	__nothrow__)) ;
extern int isinfl(long double __value) __attribute__ ((__const__,
	__nothrow__)) ;
extern int finitel(long double __value) __attribute__ ((__const__,
	__nothrow__)) ;
extern long double dreml(long double __x, long double
	__y) __attribute__ ((__nothrow__)) ;
extern long double __dreml(long double __x, long double
	__y) __attribute__ ((__nothrow__)) ;
extern long double significandl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __significandl(long double
	__x) __attribute__ ((__nothrow__)) ;
extern long double copysignl(long double __x, long double
	__y) __attribute__ ((__const__, __nothrow__)) ;
extern long double __copysignl(long double __x, long double
	__y) __attribute__ ((__const__, __nothrow__)) ;
extern int __isnanl(long double __value) __attribute__ ((__const__,
	__nothrow__)) ;
extern int isnanl(long double __value) __attribute__ ((__const__,
	__nothrow__)) ;
extern long double j0l(long double ) __attribute__ ((__nothrow__)) ;
extern long double __j0l(long double ) __attribute__ ((__nothrow__)) ;
extern long double j1l(long double ) __attribute__ ((__nothrow__)) ;
extern long double __j1l(long double ) __attribute__ ((__nothrow__)) ;
extern long double jnl(int , long double ) __attribute__ ((__nothrow__)) ;
extern long double __jnl(int , long double ) __attribute__ ((__nothrow__)) ;
extern long double y0l(long double ) __attribute__ ((__nothrow__)) ;
extern long double __y0l(long double ) __attribute__ ((__nothrow__)) ;
extern long double y1l(long double ) __attribute__ ((__nothrow__)) ;
extern long double __y1l(long double ) __attribute__ ((__nothrow__)) ;
extern long double ynl(int , long double ) __attribute__ ((__nothrow__)) ;
extern long double __ynl(int , long double ) __attribute__ ((__nothrow__)) ;
extern long double erfl(long double ) __attribute__ ((__nothrow__)) ;
extern long double __erfl(long double ) __attribute__ ((__nothrow__)) ;
extern long double erfcl(long double ) __attribute__ ((__nothrow__)) ;
extern long double __erfcl(long double ) __attribute__ ((__nothrow__)) ;
extern long double lgammal(long double ) __attribute__ ((__nothrow__)) ;
extern long double __lgammal(long double ) __attribute__ ((__nothrow__)) ;
extern long double gammal(long double ) __attribute__ ((__nothrow__)) ;
extern long double __gammal(long double ) __attribute__ ((__nothrow__)) ;
extern long double lgammal_r(long double , int
	*__signgamp) __attribute__ ((__nothrow__)) ;
extern long double __lgammal_r(long double , int
	*__signgamp) __attribute__ ((__nothrow__)) ;
extern long double rintl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double __rintl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double nextafterl(long double __x, long double
	__y) __attribute__ ((__const__, __nothrow__)) ;
extern long double __nextafterl(long double __x, long double
	__y) __attribute__ ((__const__, __nothrow__)) ;
extern long double remainderl(long double __x, long double
	__y) __attribute__ ((__nothrow__)) ;
extern long double __remainderl(long double __x, long double
	__y) __attribute__ ((__nothrow__)) ;
extern long double scalbnl(long double __x, int
	__n) __attribute__ ((__nothrow__)) ;
extern long double __scalbnl(long double __x, int
	__n) __attribute__ ((__nothrow__)) ;
extern int ilogbl(long double __x) __attribute__ ((__nothrow__)) ;
extern int __ilogbl(long double __x) __attribute__ ((__nothrow__)) ;
extern long double scalbl(long double __x, long double
	__n) __attribute__ ((__nothrow__)) ;
extern long double __scalbl(long double __x, long double
	__n) __attribute__ ((__nothrow__)) ;
extern int signgam;

typedef enum  {
	_IEEE_ = -1,
	_SVID_,
	_XOPEN_,
	_POSIX_,
	_ISOC_
} _LIB_VERSION_TYPE;

extern _LIB_VERSION_TYPE _LIB_VERSION;

struct exception {
	int type;
	char *name;
	double arg1;
	double arg2;
	double retval;
} ;

extern int matherr(struct exception *__exc);
double sqrt(double );
int Seed;
double ArrayA[1000], ArrayB[1000];
double SumA, SumB;
double Coef;

void InitSeed()
{
# 29 "originaux/st.c"
	Seed = 0;
}

void Calc_Sum_Mean(double Array[], double *Sum, double *Mean)
{
	int i;
# 38 "originaux/st.c"
	*Sum = 0;
# 39 "originaux/st.c"
	for(i = 0; i < 1000; i++)
# 40 "originaux/st.c"
		*Sum += Array[i];
# 41 "originaux/st.c"
	*Mean = *Sum / 1000;
}

double Square(double x)
{
# 48 "originaux/st.c"
	return x * x;
}

void Calc_Var_Stddev(double Array[], double Mean, double *Var, double *Stddev)
{
	int i;
	double diffs;
# 58 "originaux/st.c"
	diffs = 0.0;
# 59 "originaux/st.c"
	for(i = 0; i < 1000; i++)
# 60 "originaux/st.c"
		diffs += Square(Array[i] - Mean);
# 61 "originaux/st.c"
	*Var = diffs / 1000;
# 62 "originaux/st.c"
	*Stddev = sqrt(*Var);
}

void Calc_LinCorrCoef(double ArrayA[], double ArrayB[], double MeanA, double
	MeanB)
{
	int i;
	double numerator, Aterm, Bterm;
# 72 "originaux/st.c"
	numerator = 0.0;
# 73 "originaux/st.c"
	Aterm = ((Bterm = 0.0));
# 74 "originaux/st.c"
	for(i = 0; i < 1000; i++)
# 74 "originaux/st.c"
	{
# 75 "originaux/st.c"
		numerator += ((ArrayA[i] - MeanA)) * ((ArrayB[i] - MeanB));
# 76 "originaux/st.c"
		Aterm += Square(ArrayA[i] - MeanA);
# 77 "originaux/st.c"
		Bterm += Square(ArrayB[i] - MeanB);
	}
# 81 "originaux/st.c"
	Coef = numerator / ((sqrt(Aterm) * sqrt(Bterm)));
}

void Initialize(double Array[])
{
	register int i;
# 94 "originaux/st.c"
	for(i = 0; i < 1000; i++)
# 95 "originaux/st.c"
		Array[i] = i + RandomInteger() / 8095.0;
}

void RandomInteger()
{
# 104 "originaux/st.c"
	Seed = ((Seed * 133 + 81)) % 8095;
# 105 "originaux/st.c"
	return Seed;
}

int ttime()
{
	struct tms buffer;
	int utime;
# 119 "originaux/st.c"
	utime = buffer.tms_utime / 60.0 * 1000.0;
# 120 "originaux/st.c"
	return utime;
}

void main()
{
	long int StartTime, StopTime;
	float TotalTime;
	double MeanA, MeanB, VarA, VarB, StddevA, StddevB;
# 131 "originaux/st.c"
	InitSeed();
# 134 "originaux/st.c"
	StartTime = ttime();
# 136 "originaux/st.c"
	Initialize(ArrayA);
# 137 "originaux/st.c"
	Calc_Sum_Mean(ArrayA, &SumA, &MeanA);
# 138 "originaux/st.c"
	Calc_Var_Stddev(ArrayA, MeanA, &VarA, &StddevA);
# 140 "originaux/st.c"
	Initialize(ArrayB);
# 141 "originaux/st.c"
	Calc_Sum_Mean(ArrayB, &SumB, &MeanB);
# 142 "originaux/st.c"
	Calc_Var_Stddev(ArrayB, MeanB, &VarB, &StddevB);
# 147 "originaux/st.c"
	Calc_LinCorrCoef(ArrayA, ArrayB, MeanA, MeanB);
# 149 "originaux/st.c"
	StopTime = ttime();
# 150 "originaux/st.c"
	TotalTime = ((StopTime - StartTime)) / 1000.0;
}

