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
double x1, x2, x3, x4, x, y, z, t, t1, t2;
double e1[4];
int i, j, k, l, n1, n2, n3, n4, n6, n7, n8, n9, n10, n11;

main()
{
# 26 "originaux/whet.c"
	t = 0.499975;
# 27 "originaux/whet.c"
	t1 = 0.50025;
# 28 "originaux/whet.c"
	t2 = 2.0;
# 32 "originaux/whet.c"
	n1 = 0 * 10;
# 33 "originaux/whet.c"
	n2 = 12 * 10;
# 34 "originaux/whet.c"
	n3 = 14 * 10;
# 35 "originaux/whet.c"
	n4 = 345 * 10;
# 36 "originaux/whet.c"
	n6 = 210 * 10;
# 37 "originaux/whet.c"
	n7 = 32 * 10;
# 38 "originaux/whet.c"
	n8 = 899 * 10;
# 39 "originaux/whet.c"
	n9 = 616 * 10;
# 40 "originaux/whet.c"
	n10 = 0 * 10;
# 41 "originaux/whet.c"
	n11 = 93 * 10;
# 45 "originaux/whet.c"
	x1 = 1.0;
# 46 "originaux/whet.c"
	x2 = ((x3 = ((x4 = -1.0))));
# 48 "originaux/whet.c"
	for(i = 1; i <= n1; i += 1)
# 48 "originaux/whet.c"
	{
# 49 "originaux/whet.c"
		x1 = ((x1 + x2 + x3 - x4)) * t;
# 50 "originaux/whet.c"
		x2 = ((x1 + x2 - x3 - x4)) * t;
# 51 "originaux/whet.c"
		x3 = ((x1 - x2 + x3 + x4)) * t;
# 52 "originaux/whet.c"
		x4 = ((-x1 + x2 + x3 + x4)) * t;
	}
# 61 "originaux/whet.c"
	e1[0] = 1.0;
# 62 "originaux/whet.c"
	e1[1] = ((e1[2] = ((e1[3] = -1.0))));
# 64 "originaux/whet.c"
	for(i = 1; i <= n2; i += 1)
# 64 "originaux/whet.c"
	{
# 65 "originaux/whet.c"
		e1[0] = ((e1[0] + e1[1] + e1[2] - e1[3])) * t;
# 66 "originaux/whet.c"
		e1[1] = ((e1[0] + e1[1] - e1[2] + e1[3])) * t;
# 67 "originaux/whet.c"
		e1[2] = ((e1[0] - e1[1] + e1[2] + e1[3])) * t;
# 68 "originaux/whet.c"
		e1[3] = ((-e1[0] + e1[1] + e1[2] + e1[3])) * t;
	}
# 76 "originaux/whet.c"
	for(i = 1; i <= n3; i += 1)
# 77 "originaux/whet.c"
		pa(e1);
# 84 "originaux/whet.c"
	j = 1;
# 85 "originaux/whet.c"
	for(i = 1; i <= n4; i += 1)
# 85 "originaux/whet.c"
	{
# 86 "originaux/whet.c"
		if(j == 1)
# 87 "originaux/whet.c"
			j = 2;
		else
# 88 "originaux/whet.c"
# 89 "originaux/whet.c"
			j = 3;
# 91 "originaux/whet.c"
		if(j > 2)
# 92 "originaux/whet.c"
			j = 0;
		else
# 93 "originaux/whet.c"
# 94 "originaux/whet.c"
			j = 1;
# 96 "originaux/whet.c"
		if(j < 1)
# 97 "originaux/whet.c"
			j = 1;
		else
# 98 "originaux/whet.c"
# 99 "originaux/whet.c"
			j = 0;
	}
# 109 "originaux/whet.c"
	j = 1;
# 110 "originaux/whet.c"
	k = 2;
# 111 "originaux/whet.c"
	l = 3;
# 113 "originaux/whet.c"
	for(i = 1; i <= n6; i += 1)
# 113 "originaux/whet.c"
	{
# 114 "originaux/whet.c"
		j = j * ((k - j)) * ((l - k));
# 115 "originaux/whet.c"
		k = l * k - ((l - j)) * k;
# 116 "originaux/whet.c"
		l = ((l - k)) * ((k + j));
# 118 "originaux/whet.c"
		e1[l - 2] = j + k + l;
# 119 "originaux/whet.c"
		e1[k - 2] = j * k * l;
	}
# 127 "originaux/whet.c"
	x = ((y = 0.5));
# 129 "originaux/whet.c"
	for(i = 1; i <= n7; i += 1)
# 129 "originaux/whet.c"
	{
# 130 "originaux/whet.c"
		x = t * atan(t2 * sin(x) * cos(x) / ((cos(x + y) + cos(x - y) -
			1.0)));
# 131 "originaux/whet.c"
		y = t * atan(t2 * sin(y) * cos(y) / ((cos(x + y) + cos(x - y) -
			1.0)));
	}
# 139 "originaux/whet.c"
	x = ((y = ((z = 1.0))));
# 141 "originaux/whet.c"
	for(i = 1; i <= n8; i += 1)
# 142 "originaux/whet.c"
		p3(x, y, &z);
# 149 "originaux/whet.c"
	j = 1;
# 150 "originaux/whet.c"
	k = 2;
# 151 "originaux/whet.c"
	l = 3;
# 153 "originaux/whet.c"
	e1[0] = 1.0;
# 154 "originaux/whet.c"
	e1[1] = 2.0;
# 155 "originaux/whet.c"
	e1[2] = 3.0;
# 157 "originaux/whet.c"
	for(i = 1; i <= n9; i += 1)
# 158 "originaux/whet.c"
		p0();
# 165 "originaux/whet.c"
	j = 2;
# 166 "originaux/whet.c"
	k = 3;
# 168 "originaux/whet.c"
	for(i = 1; i <= n10; i += 1)
# 168 "originaux/whet.c"
	{
# 169 "originaux/whet.c"
		j = j + k;
# 170 "originaux/whet.c"
		k = j + k;
# 171 "originaux/whet.c"
		j = k - j;
# 172 "originaux/whet.c"
		k = k - j - j;
	}
# 180 "originaux/whet.c"
	x = 0.75;
# 181 "originaux/whet.c"
	for(i = 1; i <= n11; i += 1)
# 182 "originaux/whet.c"
		x = sqrt(exp(log(x) / t1));
}

pa(e)
double e[4];
{
	char lab = 0;
	register int j;

	j = 0;
	do
	{

		//lab = 0;
# 196 "originaux/whet.c"
		e[0] = ((e[0] + e[1] + e[2] - e[3])) * t;
# 197 "originaux/whet.c"
		e[1] = ((e[0] + e[1] - e[2] + e[3])) * t;
# 198 "originaux/whet.c"
		e[2] = ((e[0] - e[1] + e[2] + e[3])) * t;
# 199 "originaux/whet.c"
		e[3] = ((-e[0] + e[1] + e[2] + e[3])) / t2;
# 200 "originaux/whet.c"
		j += 1;
# 201 "originaux/whet.c"
		if(j < 6)
# 202 "originaux/whet.c"
			lab = 1 != 0;
	}
	while(lab);
}

p3(x, y, z)
double x, y, *z;
{
# 209 "originaux/whet.c"
	x = t * ((x + y));
# 210 "originaux/whet.c"
	y = t * ((x + y));
# 211 "originaux/whet.c"
	*z = ((x + y)) / t2;
}

p0()
{
# 217 "originaux/whet.c"
	e1[j] = e1[k];
# 218 "originaux/whet.c"
	e1[k] = e1[l];
# 219 "originaux/whet.c"
	e1[l] = e1[j];
}

