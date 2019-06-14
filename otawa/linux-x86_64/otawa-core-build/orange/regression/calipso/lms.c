static float gaussian(void );
float mu = 0.01;

int rand()
{
	static unsigned long int next = 1;
# 72 "originaux/lms.c"
	next = next * 1103515 + 12345;
# 73 "originaux/lms.c"
	return (unsigned int)((next / 65536)) % 32768;
}

static float log(float r)
{
# 78 "originaux/lms.c"
	return 4.5;
}

static float fabs(float n)
{
	float f;
# 85 "originaux/lms.c"
	if(n >= 0)
# 85 "originaux/lms.c"
		f = n;
	else
# 86 "originaux/lms.c"
# 86 "originaux/lms.c"
		f = -n;
# 87 "originaux/lms.c"
	return f;
}

static float sqrt(float val)
{
	float x = val / 10;
	float dx;
	double diff;
	double min_tol = 0.00001;
	int i, flag;
# 101 "originaux/lms.c"
	flag = 0;
# 102 "originaux/lms.c"
	if(val == 0)
# 102 "originaux/lms.c"
		x = 0;
	else
# 103 "originaux/lms.c"
# 103 "originaux/lms.c"
	{
# 104 "originaux/lms.c"
		for(i = 1; i < 20; i++)
# 105 "originaux/lms.c"
		{
# 106 "originaux/lms.c"
			if(!flag)
# 106 "originaux/lms.c"
			{
# 107 "originaux/lms.c"
				dx = ((val - x * x)) / ((2.0 * x));
# 108 "originaux/lms.c"
				x = x + dx;
# 109 "originaux/lms.c"
				diff = val - x * x;
# 110 "originaux/lms.c"
				if(fabs(diff) <= min_tol)
# 110 "originaux/lms.c"
					flag = 1;
			}
			else
# 112 "originaux/lms.c"
# 113 "originaux/lms.c"
				x = x;
		}
	}
# 116 "originaux/lms.c"
	return x;
}

static float sin(float rad)
{
	float app;
	float diff;
	int inc = 1;
# 130 "originaux/lms.c"
	while(rad > 2 * 3.14159265358979323846)
# 130 "originaux/lms.c"
	{
# 131 "originaux/lms.c"
		rad -= 2 * 3.14159265358979323846;
	}
# 137 "originaux/lms.c"
	while(rad < -(2 * 3.14159265358979323846))
# 137 "originaux/lms.c"
	{
# 138 "originaux/lms.c"
		rad += 2 * 3.14159265358979323846;
	}
# 144 "originaux/lms.c"
	app = ((diff = rad));
# 146 "originaux/lms.c"
	diff = diff * -((rad * rad)) / ((2.0 * inc * ((2.0 * inc + 1.0))));
# 147 "originaux/lms.c"
	app = app + diff;
# 148 "originaux/lms.c"
	inc++;
# 150 "originaux/lms.c"
	while(fabs(diff) >= 0.00001)
# 150 "originaux/lms.c"
	{
# 152 "originaux/lms.c"
		diff = diff * -((rad * rad)) / ((2.0 * inc * ((2.0 * inc +
			1.0))));
# 154 "originaux/lms.c"
		inc++;
	}
# 168 "originaux/lms.c"
	return app;
}

static float gaussian()
{
	static int ready = 0;
	static float gstore;
	static float rconst1 = (float)((2.0 / 32768));
	static float rconst2 = (float)((32768 / 2.0));
	float v1, v2, r, fac;
	float gaus;
# 181 "originaux/lms.c"
	if(ready == 0)
# 181 "originaux/lms.c"
	{
# 182 "originaux/lms.c"
		v1 = (float)rand() - rconst2;
# 183 "originaux/lms.c"
		v2 = (float)rand() - rconst2;
# 184 "originaux/lms.c"
		v1 *= rconst1;
# 185 "originaux/lms.c"
		v2 *= rconst1;
# 186 "originaux/lms.c"
		r = v1 * v1 + v2 * v2;
# 190 "originaux/lms.c"
		while(r > 1.0)
# 190 "originaux/lms.c"
		{
# 191 "originaux/lms.c"
			v1 = (float)rand() - rconst2;
# 192 "originaux/lms.c"
			v2 = (float)rand() - rconst2;
# 193 "originaux/lms.c"
			v1 *= rconst1;
# 194 "originaux/lms.c"
			v2 *= rconst1;
# 195 "originaux/lms.c"
			r = v1 * v1 + v2 * v2;
		}
# 206 "originaux/lms.c"
		fac = sqrt(-(2.0 * log(r) / r));
# 207 "originaux/lms.c"
		gstore = v1 * fac;
# 208 "originaux/lms.c"
		gaus = v2 * fac;
# 209 "originaux/lms.c"
		ready = 1;
	}
	else
# 212 "originaux/lms.c"
# 212 "originaux/lms.c"
	{
# 213 "originaux/lms.c"
		ready = 0;
# 214 "originaux/lms.c"
		gaus = gstore;
	}
# 217 "originaux/lms.c"
	return gaus;
}

int main()
{
	float lms(float , float , float *, int , float , float );
	static float d[201], b[21];
	float signal_amp, noise_amp, arg, x, y;
	int k;
	static float aa, bb;
# 230 "originaux/lms.c"
	signal_amp = sqrt(2.0);
# 231 "originaux/lms.c"
	noise_amp = 0.2 * sqrt(12.0);
# 232 "originaux/lms.c"
	arg = 2.0 * 3.14159265358979323846 / 20.0;
# 233 "originaux/lms.c"
	for(k = 0; k < 201; k++)
# 233 "originaux/lms.c"
	{
# 235 "originaux/lms.c"
		aa = signal_amp * sin(arg * k);
# 236 "originaux/lms.c"
		bb = noise_amp * gaussian();
# 237 "originaux/lms.c"
		d[k] = aa + bb;
	}
# 241 "originaux/lms.c"
	mu = 2.0 * mu / ((20 + 1));
# 243 "originaux/lms.c"
	x = 0.0;
# 244 "originaux/lms.c"
	for(k = 0; k < 201; k++)
# 244 "originaux/lms.c"
	{
# 245 "originaux/lms.c"
		lms(x, d[k], b, 20, mu, 0.01);
# 247 "originaux/lms.c"
		x = d[k];
	}
# 256 "originaux/lms.c"
	return 0;
}

float lms(float x, float d, float *b, int l, float mu, float alpha)
{
	int ll;
	float e, mu_e, lms_const, y;
	static float px[51];
	static float sigma = 2.0;
# 283 "originaux/lms.c"
	px[0] = x;
# 286 "originaux/lms.c"
	y = b[0] * px[0];
# 290 "originaux/lms.c"
	for(ll = 1; ll <= l; ll++)
# 291 "originaux/lms.c"
		y = y + b[ll] * px[ll];
# 294 "originaux/lms.c"
	e = d - y;
# 301 "originaux/lms.c"
	for(ll = 0; ll <= l; ll++)
# 302 "originaux/lms.c"
		b[ll] = b[ll] + mu_e * px[ll];
# 304 "originaux/lms.c"
	for(ll = l; ll >= 1; ll--)
# 305 "originaux/lms.c"
		px[ll] = px[ll - 1];
# 306 "originaux/lms.c"
	return y;
}

