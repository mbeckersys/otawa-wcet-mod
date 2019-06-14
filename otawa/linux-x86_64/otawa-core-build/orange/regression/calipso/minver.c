int minver(int row, int col, double eps);
int mmul(int row_a, int col_a, int row_b, int col_b);
static double a[3][3] = {3.0, -6.0, 7.0, 9.0, 0.0, -5.0, 5.0, -8.0, 6.0};
double b[3][3], c[3][3], aa[3][3], a_i[3][3], e[3][3], det;

double fabs(double n)
{
	double f;
# 59 "originaux/minver.c"
	if(n >= 0)
# 59 "originaux/minver.c"
		f = n;
	else
# 60 "originaux/minver.c"
# 60 "originaux/minver.c"
		f = -n;
# 61 "originaux/minver.c"
	return f;
}

void main()
{
	int i, j;
	double eps;
# 69 "originaux/minver.c"
	eps = 1.0e-6;
# 71 "originaux/minver.c"
	for(i = 0; i < 3; i++)
# 72 "originaux/minver.c"
		for(j = 0; j < 3; j++)
# 73 "originaux/minver.c"
			(aa[i])[j] = (a[i])[j];
# 75 "originaux/minver.c"
	minver(3, 3, eps);
# 76 "originaux/minver.c"
	for(i = 0; i < 3; i++)
# 77 "originaux/minver.c"
		for(j = 0; j < 3; j++)
# 78 "originaux/minver.c"
			(a_i[i])[j] = (a[i])[j];
# 80 "originaux/minver.c"
	mmul(3, 3, 3, 3);
}

int mmul(int row_a, int col_a, int row_b, int col_b)
{
	char __tmp_0__ = 0;
	int __return__;
	int i, j, k, row_c, col_c;
	double w;
# 89 "originaux/minver.c"
	row_c = row_a;
# 90 "originaux/minver.c"
	col_c = col_b;
# 92 "originaux/minver.c"
	if(row_c < 1 || row_b < 1 || col_c < 1 || col_a != row_b)
	{
# 92 "originaux/minver.c"
		__return__ = 999;
		__tmp_0__ = 1 != 0;
	}
	if(!__tmp_0__)
# 93 "originaux/minver.c"
		for(i = 0; i < row_c; i++)
# 94 "originaux/minver.c"
		{
# 95 "originaux/minver.c"
			for(j = 0; j < col_c; j++)
# 96 "originaux/minver.c"
			{
# 97 "originaux/minver.c"
				w = 0.0;
# 98 "originaux/minver.c"
				for(k = 0; k < row_b; k++)
# 99 "originaux/minver.c"
					w += (a[i])[k] * (b[k])[j];
# 100 "originaux/minver.c"
				(c[i])[j] = w;
			}
		}
# 103 "originaux/minver.c"
	if(!__tmp_0__)
		__return__ = 0;
	__tmp_0__ = 0;
	return __return__;
}

int minver(int row, int col, double eps)
{
	char __tmp_1__ = 0, __tmp_0__ = 0;
	int __return__;
	int work[500], i, j, k, r, iw, s, t, u, v, i2, i3, i4, i5, j2;
	double w, wmax, pivot, api, w1;
# 114 "originaux/minver.c"
	if(row < 2 || row > 500 || eps <= 0.0)
	{
# 114 "originaux/minver.c"
		__return__ = 999;
		__tmp_0__ = 1 != 0;
	}
	if(!__tmp_0__)
	{
# 115 "originaux/minver.c"
		w1 = 1.0;
# 116 "originaux/minver.c"
		for(i2 = 0; i2 < row; i2++)
# 116 "originaux/minver.c"
			work[i2] = i2;
# 117 "originaux/minver.c"
		for(k = 0; !__tmp_0__ && k < row; __tmp_0__ || k++)
# 118 "originaux/minver.c"
		{
# 119 "originaux/minver.c"
			wmax = 0.0;
# 120 "originaux/minver.c"
			for(i = k; i < row; i++)
# 121 "originaux/minver.c"
			{
# 122 "originaux/minver.c"
				w = fabs((a[i])[k]);
# 123 "originaux/minver.c"
				if(w > wmax)
# 123 "originaux/minver.c"
				{
# 123 "originaux/minver.c"
					wmax = w;
# 123 "originaux/minver.c"
					r = i;
				}
			}
# 125 "originaux/minver.c"
			pivot = (a[r])[k];
# 126 "originaux/minver.c"
			api = fabs(pivot);
# 127 "originaux/minver.c"
			if(api <= eps)
# 127 "originaux/minver.c"
			{
# 127 "originaux/minver.c"
				det = w1;
# 127 "originaux/minver.c"
				__return__ = 1;
				__tmp_0__ = 1 != 0;
			}
			if(!__tmp_0__)
			{
# 128 "originaux/minver.c"
				w1 *= pivot;
# 129 "originaux/minver.c"
				u = k * col;
# 130 "originaux/minver.c"
				v = r * col;
# 131 "originaux/minver.c"
				if(r != k)
# 132 "originaux/minver.c"
				{
# 133 "originaux/minver.c"
					w1 = -w;
# 134 "originaux/minver.c"
					iw = work[k];
# 135 "originaux/minver.c"
					work[k] = work[r];
# 136 "originaux/minver.c"
					work[r] = iw;
# 137 "originaux/minver.c"
					for(j = 0; j < row; j++)
# 138 "originaux/minver.c"
					{
# 139 "originaux/minver.c"
						s = u + j;
# 140 "originaux/minver.c"
						t = v + j;
# 141 "originaux/minver.c"
						w = (a[k])[j];
# 142 "originaux/minver.c"
						(a[k])[j] = (a[r])[j];
# 143 "originaux/minver.c"
						(a[r])[j] = w;
					}
				}
# 146 "originaux/minver.c"
				for(i3 = 0; i3 < row; i3++)
# 146 "originaux/minver.c"
					(a[k])[i3] /= pivot;
# 147 "originaux/minver.c"
				for(i4 = 0; i4 < row; i4++)
# 148 "originaux/minver.c"
				{
# 149 "originaux/minver.c"
					if(i4 != k)
# 150 "originaux/minver.c"
					{
# 151 "originaux/minver.c"
						v = i4 * col;
# 152 "originaux/minver.c"
						s = v + k;
# 153 "originaux/minver.c"
						w = (a[i4])[k];
# 154 "originaux/minver.c"
						if(w != 0.0)
# 155 "originaux/minver.c"
						{
# 156 "originaux/minver.c"
							for(j2 = 0; j2 < row;
								j2++)
							{
# 157 "originaux/minver.c"
	if(j2 != k)
# 157 "originaux/minver.c"
		(a[i4])[j2] -= w * (a[k])[j2];
							}
# 158 "originaux/minver.c"
							(a[i4])[k] = -(w /
								pivot);
						}
					}
				}
# 162 "originaux/minver.c"
				(a[k])[k] = 1.0 / pivot;
			}
		}
		if(!__tmp_0__)
		{
# 166 "originaux/minver.c"
			for(i5 = 0; i5 < row; i5++)
# 167 "originaux/minver.c"
			{
# 168 "originaux/minver.c"
				while(!__tmp_1__ && 1)
# 169 "originaux/minver.c"
				{
# 170 "originaux/minver.c"
					k = work[i5];
# 171 "originaux/minver.c"
					if(k == i5)
# 171 "originaux/minver.c"
						__tmp_1__ = 1 != 0;
					if(!__tmp_1__)
					{
# 172 "originaux/minver.c"
						iw = work[k];
# 173 "originaux/minver.c"
						work[k] = work[i5];
# 174 "originaux/minver.c"
						work[i5] = iw;
# 175 "originaux/minver.c"
						for(j = 0; j < row; j++)
# 176 "originaux/minver.c"
						{
# 177 "originaux/minver.c"
							u = j * col;
# 178 "originaux/minver.c"
							s = u + i5;
# 179 "originaux/minver.c"
							t = u + k;
# 180 "originaux/minver.c"
							w = (a[k])[i5];
# 181 "originaux/minver.c"
							(a[k])[i5] = (a[k])[k];
# 182 "originaux/minver.c"
							(a[k])[k] = w;
						}
					}
				}
				__tmp_1__ = 0;
			}
# 186 "originaux/minver.c"
			det = w1;
		}
	}
# 187 "originaux/minver.c"
	if(!__tmp_0__)
		__return__ = 0;
	__tmp_0__ = 0;
	return __return__;
}

