int _MAX(sin_0);
int _MAX(sin_1);
int _MAX(sin_2);
int _MAX(fft_c_0);
int _MAX(fft_c_0_0);
int _MAX(fft_c_0_0_0);

typedef struct  {
	float real, imag;
} COMPLEX;

void fft_c(int n);
void init_w(int n);
int n = 1024;
COMPLEX x[1024], w[1024];

float fabs(float n)
{
	float f;
# 71 "originaux/fft1k.c"
	if(n >= 0)
# 71 "originaux/fft1k.c"
		f = n;
	else
# 72 "originaux/fft1k.c"
# 72 "originaux/fft1k.c"
		f = -n;
# 73 "originaux/fft1k.c"
	return f;
}

float sin(rad)
float rad;
{
	float app;
	float diff;
	int inc = 1;
# 83 "originaux/fft1k.c"
	_BEGIN(sin_0);
# 84 "originaux/fft1k.c"
	_BEGIN(sin_1);
# 85 "originaux/fft1k.c"
	_BEGIN(sin_2);
# 87 "originaux/fft1k.c"
	while(rad > 2 * 3.14159265358979323846)
# 87 "originaux/fft1k.c"
	{
# 88 "originaux/fft1k.c"
		_COUNT(sin_0);
# 89 "originaux/fft1k.c"
		rad -= 2 * 3.14159265358979323846;
	}
# 91 "originaux/fft1k.c"
	while(rad < -(2 * 3.14159265358979323846))
# 91 "originaux/fft1k.c"
	{
# 92 "originaux/fft1k.c"
		_COUNT(sin_1);
# 93 "originaux/fft1k.c"
		rad += 2 * 3.14159265358979323846;
	}
# 95 "originaux/fft1k.c"
	app = ((diff = rad));
# 97 "originaux/fft1k.c"
	diff = diff * -((rad * rad)) / ((2.0 * inc * ((2.0 * inc + 1.0))));
# 98 "originaux/fft1k.c"
	app = app + diff;
# 99 "originaux/fft1k.c"
	inc++;
# 100 "originaux/fft1k.c"
	while(fabs(diff) >= 0.00001)
# 100 "originaux/fft1k.c"
	{
# 101 "originaux/fft1k.c"
		_COUNT(sin_2);
# 103 "originaux/fft1k.c"
		diff = diff * -((rad * rad)) / ((2.0 * inc * ((2.0 * inc +
			1.0))));
# 105 "originaux/fft1k.c"
		inc++;
	}
# 108 "originaux/fft1k.c"
	_END(sin_0);
# 109 "originaux/fft1k.c"
	_END(sin_1);
# 110 "originaux/fft1k.c"
	_END(sin_2);
# 111 "originaux/fft1k.c"
	return app;
}

float cos(rad)
float rad;
{
	float sin();
# 119 "originaux/fft1k.c"
	return sin(3.14159265358979323846 / 2.0 - rad);
}

void main()
{
	int i;
# 128 "originaux/fft1k.c"
	init_w(n);
# 130 "originaux/fft1k.c"
	(x[0]).real = 1.0;
# 131 "originaux/fft1k.c"
	fft_c(n);
# 132 "originaux/fft1k.c"
	_PRINT(sin_0);
# 133 "originaux/fft1k.c"
	_PRINT(sin_1);
# 134 "originaux/fft1k.c"
	_PRINT(sin_2);
# 135 "originaux/fft1k.c"
	_PRINT(fft_c_0);
# 136 "originaux/fft1k.c"
	_PRINT(fft_c_0_0);
# 137 "originaux/fft1k.c"
	_PRINT(fft_c_0_0_0);
}

void fft_c(int n)
{
	int N = log2(n);
	int ci;
# 156 "originaux/fft1k.c"
	for(k = 0; k < N; k++)
# 157 "originaux/fft1k.c"
	{
# 160 "originaux/fft1k.c"
		for(j = 0; j < n * pow(2, -k); j++)
# 163 "originaux/fft1k.c"
			for(i = 0; i < n - j; i = i + n * pow(2, -k + 1))
# 164 "originaux/fft1k.c"
				ci = ((n - j)) / ((n * pow(2, -k + 1)));
	}
}

void init_w(int n)
{
	int i;
	float a = 2.0 * 3.14159265358979323846 / n;
# 171 "originaux/fft1k.c"
	for(i = 0; i < n; i++)
# 171 "originaux/fft1k.c"
	{
# 172 "originaux/fft1k.c"
		(w[i]).real = cos(i * a);
# 173 "originaux/fft1k.c"
		(w[i]).imag = sin(i * a);
	}
}

