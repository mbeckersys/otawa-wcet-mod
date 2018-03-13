double ar[8];
double ai[8] = {0.};
int fft1(int n, int flag);

static double fabs(double n)
{
	double f;
# 62 "originaux/fft1.c"
	if(n >= 0)
# 62 "originaux/fft1.c"
		f = n;
	else
# 63 "originaux/fft1.c"
# 63 "originaux/fft1.c"
		f = -n;
# 64 "originaux/fft1.c"
	return f;
}

static double log(double n)
{
# 69 "originaux/fft1.c"
	return 4.5;
}

static double sin(double rad)
{
	double app;
	double diff;
	int inc = 1;
# 81 "originaux/fft1.c"
	while(rad > 2 * 3.14159)
# 82 "originaux/fft1.c"
		rad -= 2 * 3.14159;
# 83 "originaux/fft1.c"
	while(rad < -(2 * 3.14159))
# 84 "originaux/fft1.c"
		rad += 2 * 3.14159;
# 85 "originaux/fft1.c"
	app = ((diff = rad));
# 87 "originaux/fft1.c"
	diff = diff * -((rad * rad)) / ((2.0 * inc * ((2.0 * inc + 1.0))));
# 88 "originaux/fft1.c"
	app = app + diff;
# 89 "originaux/fft1.c"
	inc++;
# 90 "originaux/fft1.c"
	while(fabs(diff) >= 0.00001)
# 90 "originaux/fft1.c"
	{
# 92 "originaux/fft1.c"
		diff = diff * -((rad * rad)) / ((2.0 * inc * ((2.0 * inc +
			1.0))));
# 94 "originaux/fft1.c"
		inc++;
	}
# 97 "originaux/fft1.c"
	return app;
}

static double cos(double rad)
{
	int res;
# 105 "originaux/fft1.c"
	res = sin(3.14159 / 2.0 - rad);
# 106 "originaux/fft1.c"
	return res;
}

void main()
{
	int i, n = 8, flag, chkerr;
# 118 "originaux/fft1.c"
	for(i = 0; i < n; i++)
# 119 "originaux/fft1.c"
		ar[i] = cos(2 * 3.14159 * i / n);
# 122 "originaux/fft1.c"
	flag = 0;
# 123 "originaux/fft1.c"
	chkerr = fft1(n, flag);
# 126 "originaux/fft1.c"
	flag = 1;
# 127 "originaux/fft1.c"
	chkerr = fft1(n, flag);
}

int fft1(int n, int flag)
{
	char __tmp_0__ = 0;
	int __return__;
	int i, j, k, it, xp, xp2, j1, j2, iter;
	double sign, w, wr, wi, dr1, dr2, di1, di2, tr, ti, arg;
	int lg8, lg2;
# 139 "originaux/fft1.c"
	if(n < 2)
	{
# 139 "originaux/fft1.c"
		__return__ = 999;
		__tmp_0__ = 1 != 0;
	}
	if(!__tmp_0__)
	{
# 140 "originaux/fft1.c"
		lg8 = log((double)n);
# 141 "originaux/fft1.c"
		lg2 = log(2.0);
# 142 "originaux/fft1.c"
		iter = lg8 / lg2;
# 143 "originaux/fft1.c"
		j = 1;
# 147 "originaux/fft1.c"
		for(i = 0; i < iter; i++)
# 148 "originaux/fft1.c"
			j *= 2;
# 149 "originaux/fft1.c"
		if(fabs(n - j) > 1.0e-6)
		{
# 150 "originaux/fft1.c"
			__return__ = 1;
			__tmp_0__ = 1 != 0;
		}
		if(!__tmp_0__)
		{
# 153 "originaux/fft1.c"
			sign = flag == 1 ? 1.0 : -1.0;
# 154 "originaux/fft1.c"
			xp2 = n;
# 155 "originaux/fft1.c"
			for(it = 0; it < iter; it++)
# 156 "originaux/fft1.c"
			{
# 157 "originaux/fft1.c"
				xp = xp2;
# 158 "originaux/fft1.c"
				xp2 /= 2;
# 159 "originaux/fft1.c"
				w = 3.14159 / xp2;
# 163 "originaux/fft1.c"
				for(k = 0; k < xp2; k++)
# 164 "originaux/fft1.c"
				{
# 165 "originaux/fft1.c"
					arg = k * w;
# 166 "originaux/fft1.c"
					wr = cos(arg);
# 167 "originaux/fft1.c"
					wi = sign * sin(arg);
# 168 "originaux/fft1.c"
					i = k - xp;
# 169 "originaux/fft1.c"
					for(j = xp; j <= n; j += xp)
# 170 "originaux/fft1.c"
					{
# 171 "originaux/fft1.c"
						j1 = j + i;
# 172 "originaux/fft1.c"
						j2 = j1 + xp2;
# 173 "originaux/fft1.c"
						dr1 = ar[j1];
# 174 "originaux/fft1.c"
						dr2 = ar[j2];
# 175 "originaux/fft1.c"
						di1 = ai[j1];
# 176 "originaux/fft1.c"
						di2 = ai[j2];
# 177 "originaux/fft1.c"
						tr = dr1 - dr2;
# 178 "originaux/fft1.c"
						ti = di1 - di2;
# 179 "originaux/fft1.c"
						ar[j1] = dr1 + dr2;
# 180 "originaux/fft1.c"
						ai[j1] = di1 + di2;
# 181 "originaux/fft1.c"
						ar[j2] = tr * wr - ti * wi;
# 182 "originaux/fft1.c"
						ai[j2] = ti * wr + tr * wi;
					}
				}
			}
# 189 "originaux/fft1.c"
			j1 = n / 2;
# 190 "originaux/fft1.c"
			j2 = n - 1;
# 191 "originaux/fft1.c"
			j = 1;
# 195 "originaux/fft1.c"
			for(i = 1; i <= j2; i++)
# 196 "originaux/fft1.c"
			{
# 197 "originaux/fft1.c"
				if(i < j)
# 198 "originaux/fft1.c"
				{
# 199 "originaux/fft1.c"
					tr = ar[j - 1];
# 200 "originaux/fft1.c"
					ti = ai[j - 1];
# 201 "originaux/fft1.c"
					ar[j - 1] = ar[i - 1];
# 202 "originaux/fft1.c"
					ai[j - 1] = ai[i - 1];
# 203 "originaux/fft1.c"
					ar[i - 1] = tr;
# 204 "originaux/fft1.c"
					ai[i - 1] = ti;
				}
# 206 "originaux/fft1.c"
				k = j1;
# 207 "originaux/fft1.c"
				while(k < j)
# 208 "originaux/fft1.c"
				{
# 209 "originaux/fft1.c"
					j -= k;
# 210 "originaux/fft1.c"
					k /= 2;
				}
# 212 "originaux/fft1.c"
				j += k;
			}
# 214 "originaux/fft1.c"
			if(flag == 0)
			{
# 214 "originaux/fft1.c"
				__return__ = 0;
				__tmp_0__ = 1 != 0;
			}
			if(!__tmp_0__)
			{
# 215 "originaux/fft1.c"
				w = n;
# 216 "originaux/fft1.c"
				for(i = 0; i < n; i++)
# 217 "originaux/fft1.c"
				{
# 218 "originaux/fft1.c"
					ar[i] /= w;
# 219 "originaux/fft1.c"
					ai[i] /= w;
				}
			}
		}
	}
# 221 "originaux/fft1.c"
	if(!__tmp_0__)
		__return__ = 0;
	__tmp_0__ = 0;
	return __return__;
}

