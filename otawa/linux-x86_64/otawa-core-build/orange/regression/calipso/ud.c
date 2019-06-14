long int a[50][50], b[50], x[50];
int ludcmp(int nmax, int n);

void main()
{
	int i, j, nmax = 50, n = 5, chkerr;
	long int w;
# 73 "originaux/ud.c"
	for(i = 0; i <= n; i++)
# 75 "originaux/ud.c"
	{
# 77 "originaux/ud.c"
		w = 0.0;
# 79 "originaux/ud.c"
		for(j = 0; j <= n; j++)
# 81 "originaux/ud.c"
		{
# 83 "originaux/ud.c"
			(a[i])[j] = i + 1 + ((j + 1));
# 85 "originaux/ud.c"
			if(i == j)
# 87 "originaux/ud.c"
				(a[i])[j] *= 2.0;
# 89 "originaux/ud.c"
			w += (a[i])[j];
		}
# 93 "originaux/ud.c"
		b[i] = w;
	}
# 101 "originaux/ud.c"
	chkerr = ludcmp(nmax, n);
}

int ludcmp(int nmax, int n)
{
	int i, j, k;
	long int w, y[100];
# 119 "originaux/ud.c"
	for(i = 0; i < n; i++)
# 121 "originaux/ud.c"
	{
# 125 "originaux/ud.c"
		for(j = i + 1; j <= n; j++)
# 127 "originaux/ud.c"
		{
# 129 "originaux/ud.c"
			w = (a[j])[i];
# 131 "originaux/ud.c"
			if(i != 0)
# 137 "originaux/ud.c"
				for(k = 0; k < i; k++)
# 139 "originaux/ud.c"
					w -= (a[j])[k] * (a[k])[i];
# 141 "originaux/ud.c"
			(a[j])[i] = w / (a[i])[i];
		}
# 145 "originaux/ud.c"
		for(j = i + 1; j <= n; j++)
# 147 "originaux/ud.c"
		{
# 149 "originaux/ud.c"
			w = (a[i + 1])[j];
# 151 "originaux/ud.c"
			for(k = 0; k <= i; k++)
# 153 "originaux/ud.c"
				w -= (a[i + 1])[k] * (a[k])[j];
# 155 "originaux/ud.c"
			(a[i + 1])[j] = w;
		}
	}
# 161 "originaux/ud.c"
	y[0] = b[0];
# 163 "originaux/ud.c"
	for(i = 1; i <= n; i++)
# 165 "originaux/ud.c"
	{
# 167 "originaux/ud.c"
		w = b[i];
# 169 "originaux/ud.c"
		for(j = 0; j < i; j++)
# 171 "originaux/ud.c"
			w -= (a[i])[j] * y[j];
# 173 "originaux/ud.c"
		y[i] = w;
	}
# 177 "originaux/ud.c"
	x[n] = y[n] / (a[n])[n];
# 179 "originaux/ud.c"
	for(i = n - 1; i >= 0; i--)
# 181 "originaux/ud.c"
	{
# 183 "originaux/ud.c"
		w = y[i];
# 185 "originaux/ud.c"
		for(j = i + 1; j <= n; j++)
# 187 "originaux/ud.c"
			w -= (a[i])[j] * x[j];
# 189 "originaux/ud.c"
		x[i] = w / (a[i])[i];
	}
# 193 "originaux/ud.c"
	return 0;
}

