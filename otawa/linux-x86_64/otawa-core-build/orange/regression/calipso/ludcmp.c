double a[50][50], b[50], x[50];
int ludcmp(int nmax, int n, double eps);

static double fabs(double n)
{
	double f;
# 70 "originaux/ludcmp.c"
	if(n >= 0)
# 70 "originaux/ludcmp.c"
		f = n;
	else
# 71 "originaux/ludcmp.c"
# 71 "originaux/ludcmp.c"
		f = -n;
# 72 "originaux/ludcmp.c"
	return f;
}

void main()
{
	int i, j, nmax = 50, n = 5, chkerr;
	double eps, w;
# 81 "originaux/ludcmp.c"
	eps = 1.0e-6;
# 83 "originaux/ludcmp.c"
	for(i = 0; i <= n; i++)
# 84 "originaux/ludcmp.c"
	{
# 85 "originaux/ludcmp.c"
		w = 0.0;
# 86 "originaux/ludcmp.c"
		for(j = 0; j <= n; j++)
# 87 "originaux/ludcmp.c"
		{
# 88 "originaux/ludcmp.c"
			(a[i])[j] = i + 1 + ((j + 1));
# 89 "originaux/ludcmp.c"
			if(i == j)
# 89 "originaux/ludcmp.c"
				(a[i])[j] *= 10.0;
# 90 "originaux/ludcmp.c"
			w += (a[i])[j];
		}
# 92 "originaux/ludcmp.c"
		b[i] = w;
	}
# 95 "originaux/ludcmp.c"
	chkerr = ludcmp(nmax, n, eps);
}

int ludcmp(int nmax, int n, double eps)
{
	char __tmp_0__ = 0;
	int __return__;
	int i, j, k;
	double w, y[100];
# 105 "originaux/ludcmp.c"
	if(n > 99 || eps <= 0.0)
	{
# 105 "originaux/ludcmp.c"
		__return__ = 999;
		__tmp_0__ = 1 != 0;
	}
	if(!__tmp_0__)
	{
# 106 "originaux/ludcmp.c"
		for(i = 0; !__tmp_0__ && i < n; __tmp_0__ || i++)
# 107 "originaux/ludcmp.c"
		{
# 108 "originaux/ludcmp.c"
			if(fabs((a[i])[i]) <= eps)
			{
# 108 "originaux/ludcmp.c"
				__return__ = 1;
				__tmp_0__ = 1 != 0;
			}
			if(!__tmp_0__)
			{
# 109 "originaux/ludcmp.c"
				for(j = i + 1; j <= n; j++)
# 110 "originaux/ludcmp.c"
				{
# 111 "originaux/ludcmp.c"
					w = (a[j])[i];
# 112 "originaux/ludcmp.c"
					if(i != 0)
# 113 "originaux/ludcmp.c"
						for(k = 0; k < i; k++)
# 114 "originaux/ludcmp.c"
							w -= (a[j])[k] *
								(a[k])[i];
# 115 "originaux/ludcmp.c"
					(a[j])[i] = w / (a[i])[i];
				}
# 117 "originaux/ludcmp.c"
				for(j = i + 1; j <= n; j++)
# 118 "originaux/ludcmp.c"
				{
# 119 "originaux/ludcmp.c"
					w = (a[i + 1])[j];
# 120 "originaux/ludcmp.c"
					for(k = 0; k <= i; k++)
# 121 "originaux/ludcmp.c"
						w -= (a[i + 1])[k] * (a[k])[j];
# 122 "originaux/ludcmp.c"
					(a[i + 1])[j] = w;
				}
			}
		}
		if(!__tmp_0__)
		{
# 125 "originaux/ludcmp.c"
			y[0] = b[0];
# 126 "originaux/ludcmp.c"
			for(i = 1; i <= n; i++)
# 127 "originaux/ludcmp.c"
			{
# 128 "originaux/ludcmp.c"
				w = b[i];
# 129 "originaux/ludcmp.c"
				for(j = 0; j < i; j++)
# 130 "originaux/ludcmp.c"
					w -= (a[i])[j] * y[j];
# 131 "originaux/ludcmp.c"
				y[i] = w;
			}
# 133 "originaux/ludcmp.c"
			x[n] = y[n] / (a[n])[n];
# 134 "originaux/ludcmp.c"
			for(i = n - 1; i >= 0; i--)
# 135 "originaux/ludcmp.c"
			{
# 136 "originaux/ludcmp.c"
				w = y[i];
# 137 "originaux/ludcmp.c"
				for(j = i + 1; j <= n; j++)
# 138 "originaux/ludcmp.c"
					w -= (a[i])[j] * x[j];
# 139 "originaux/ludcmp.c"
				x[i] = w / (a[i])[i];
			}
		}
	}
# 141 "originaux/ludcmp.c"
	if(!__tmp_0__)
		__return__ = 0;
	__tmp_0__ = 0;
	return __return__;
}

