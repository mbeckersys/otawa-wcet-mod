void vec_mpy1(short int y[], short int  const x[], short int scaler);
long int mac(short int  const *a, short int  const *b, long int sqr, long int
	*sum);
void fir(short int  const array1[], short int  const coeff[], long int
	output[]);
void fir_no_red_ld(short int  const x[], short int  const h[], long int y[]);
long int latsynth(short int b[], short int  const k[], long int n, long int f);
void iir1(short int  const *coefs, short int  const *input, long int *optr,
	long int *state);
long int codebook(long int mask, long int bitchanged, long int numbasis,
	long int codeword, long int g, short int  const *d, short int ddim,
	short int theta);
void jpegdct(short int *d, short int *r);

void vec_mpy1(short int y[], short int  const x[], short int scaler)
{
	long int i;
# 35 "originaux/edn.c"
	for(i = 0; i < 150; i++)
# 36 "originaux/edn.c"
		y[i] += scaler * x[i] >> 15;
}

long int mac(short int  const *a, short int  const *b, long int sqr, long int
	*sum)
{
	long int i;
	long int dotp = *sum;
# 49 "originaux/edn.c"
	for(i = 0; i < 150; i++)
# 49 "originaux/edn.c"
	{
# 50 "originaux/edn.c"
		dotp += b[i] * a[i];
# 51 "originaux/edn.c"
		sqr += b[i] * b[i];
	}
# 54 "originaux/edn.c"
	*sum = dotp;
# 55 "originaux/edn.c"
	return sqr;
}

void fir(short int  const array1[], short int  const coeff[], long int output[])
{
	long int i, j, sum;
# 67 "originaux/edn.c"
	for(i = 0; i < 100 - 50; i++)
# 67 "originaux/edn.c"
	{
# 68 "originaux/edn.c"
		sum = 0;
# 69 "originaux/edn.c"
		for(j = 0; j < 50; j++)
# 69 "originaux/edn.c"
		{
# 70 "originaux/edn.c"
			sum += array1[i + j] * coeff[j];
		}
# 72 "originaux/edn.c"
		output[i] = sum >> 15;
	}
}

void fir_no_red_ld(short int  const x[], short int  const h[], long int y[])
{
	long int i, j;
	long int sum0, sum1;
	short int x0, x1, h0, h1;
# 89 "originaux/edn.c"
	for(j = 0; j < 100; j += 2)
# 89 "originaux/edn.c"
	{
# 90 "originaux/edn.c"
		sum0 = 0;
# 91 "originaux/edn.c"
		sum1 = 0;
# 92 "originaux/edn.c"
		x0 = x[j];
# 93 "originaux/edn.c"
		for(i = 0; i < 32; i += 2)
# 93 "originaux/edn.c"
		{
# 94 "originaux/edn.c"
			x1 = x[j + i + 1];
# 95 "originaux/edn.c"
			h0 = h[i];
# 96 "originaux/edn.c"
			sum0 += x0 * h0;
# 97 "originaux/edn.c"
			sum1 += x1 * h0;
# 98 "originaux/edn.c"
			x0 = x[j + i + 2];
# 99 "originaux/edn.c"
			h1 = h[i + 1];
# 100 "originaux/edn.c"
			sum0 += x1 * h1;
# 101 "originaux/edn.c"
			sum1 += x0 * h1;
		}
# 103 "originaux/edn.c"
		y[j] = sum0 >> 15;
# 104 "originaux/edn.c"
		y[j + 1] = sum1 >> 15;
	}
}

long int latsynth(short int b[], short int  const k[], long int n, long int f)
{
	long int i;
# 116 "originaux/edn.c"
	f -= b[n - 1] * k[n - 1];
# 117 "originaux/edn.c"
	for(i = n - 2; i >= 0; i--)
# 117 "originaux/edn.c"
	{
# 118 "originaux/edn.c"
		f -= b[i] * k[i];
# 119 "originaux/edn.c"
		b[i + 1] = b[i] + ((k[i] * ((f >> 16)) >> 16));
	}
# 121 "originaux/edn.c"
	b[0] = f >> 16;
# 122 "originaux/edn.c"
	return f;
}

void iir1(short int  const *coefs, short int  const *input, long int *optr,
	long int *state)
{
	long int x;
	long int t;
	long int n;
# 135 "originaux/edn.c"
	x = input[0];
# 136 "originaux/edn.c"
	for(n = 0; n < 50; n++)
# 136 "originaux/edn.c"
	{
# 137 "originaux/edn.c"
		t = x + ((coefs[2] * state[0] + coefs[3] * state[1] >> 15));
# 138 "originaux/edn.c"
		x = t + ((coefs[0] * state[0] + coefs[1] * state[1] >> 15));
# 139 "originaux/edn.c"
		state[1] = state[0];
# 140 "originaux/edn.c"
		state[0] = t;
# 141 "originaux/edn.c"
		coefs += 4;
# 142 "originaux/edn.c"
		state += 2;
	}
# 144 "originaux/edn.c"
	*optr++ = x;
}

long int codebook(long int mask, long int bitchanged, long int numbasis,
	long int codeword, long int g, short int  const *d, short int ddim,
	short int theta)
{
	long int j;
	long int tmpMask;
# 161 "originaux/edn.c"
	tmpMask = mask << 1;
# 162 "originaux/edn.c"
	for(j = bitchanged + 1; j <= numbasis; j++)
# 162 "originaux/edn.c"
		;
# 178 "originaux/edn.c"
	return g;
}

void jpegdct(short int *d, short int *r)
{
	long int t[12];
	short int i, j, k, m, n, p;
# 190 "originaux/edn.c"
	for(k = 1, m = 0, n = 13, p = 8; k <= 8; k += 7, m += 3, n += 3, p -= 7,
		d -= 64)
# 190 "originaux/edn.c"
	{
# 191 "originaux/edn.c"
		for(i = 0; i < 8; i++, d += p)
# 191 "originaux/edn.c"
		{
# 192 "originaux/edn.c"
			for(j = 0; j < 4; j++)
# 192 "originaux/edn.c"
			{
# 193 "originaux/edn.c"
				t[j] = d[k * j] + d[k * ((7 - j))];
# 194 "originaux/edn.c"
				t[7 - j] = d[k * j] - d[k * ((7 - j))];
			}
# 196 "originaux/edn.c"
			t[8] = t[0] + t[3];
# 197 "originaux/edn.c"
			t[9] = t[0] - t[3];
# 198 "originaux/edn.c"
			t[10] = t[1] + t[2];
# 199 "originaux/edn.c"
			t[11] = t[1] - t[2];
# 200 "originaux/edn.c"
			d[0] = t[8] + t[10] >> m;
# 201 "originaux/edn.c"
			d[4 * k] = t[8] - t[10] >> m;
# 202 "originaux/edn.c"
			t[8] = (short int)((t[11] + t[9])) * r[10];
# 203 "originaux/edn.c"
			d[2 * k] = t[8] + (short int)((t[9] * r[9] >> n));
# 204 "originaux/edn.c"
			d[6 * k] = t[8] + (short int)((t[11] * r[11] >> n));
# 205 "originaux/edn.c"
			t[0] = (short int)((t[4] + t[7])) * r[2];
# 206 "originaux/edn.c"
			t[1] = (short int)((t[5] + t[6])) * r[0];
# 207 "originaux/edn.c"
			t[2] = t[4] + t[6];
# 208 "originaux/edn.c"
			t[3] = t[5] + t[7];
# 209 "originaux/edn.c"
			t[8] = (short int)((t[2] + t[3])) * r[8];
# 210 "originaux/edn.c"
			t[2] = (short int)t[2] * r[1] + t[8];
# 211 "originaux/edn.c"
			t[3] = (short int)t[3] * r[3] + t[8];
# 212 "originaux/edn.c"
			d[7 * k] = (short int)((t[4] * r[4] + t[0] + t[2])) >>
				n;
# 213 "originaux/edn.c"
			d[5 * k] = (short int)((t[5] * r[6] + t[1] + t[3])) >>
				n;
# 214 "originaux/edn.c"
			d[3 * k] = (short int)((t[6] * r[5] + t[1] + t[2])) >>
				n;
# 215 "originaux/edn.c"
			d[1 * k] = (short int)((t[7] * r[7] + t[0] + t[3])) >>
				n;
		}
	}
}

int main(void )
{
	short int a[200] = {0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400, 0x0000, 0x07ff, 0x0c00, 0x0800, 0x0200, 0xf800,
		0xf300, 0x0400};
	short int b[200] = {0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000, 0x0c60, 0x0c40, 0x0c20, 0x0c00, 0xf600, 0xf400,
		0xf200, 0xf000};
	short int c = 0x3;
	long int output[200];
	long int d = 0xAAAA;
	int e[1] = {0xEEEE};
# 275 "originaux/edn.c"
	vec_mpy1(a, b, c);
# 276 "originaux/edn.c"
	c = mac(a, b, (long int)c, (long int*)output);
# 277 "originaux/edn.c"
	fir(a, b, output);
# 278 "originaux/edn.c"
	fir_no_red_ld(a, b, output);
# 279 "originaux/edn.c"
	d = latsynth(a, b, 100, d);
# 280 "originaux/edn.c"
	iir1(a, b, &output[100], output);
# 281 "originaux/edn.c"
	e[0] = codebook(d, 1, 17, e[0], d, a, c, 1);
# 282 "originaux/edn.c"
	jpegdct(a, b);
# 283 "originaux/edn.c"
	return 0;
}

