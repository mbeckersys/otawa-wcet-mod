int minver(int row, int col, double eps);
int mmul(int row_a, int col_a, int row_b, int col_b);
static double a[3][3] = {3.0, -6.0, 7.0, 9.0, 0.0, -5.0, 5.0, -8.0, 6.0};
double b[3][3], c[3][3], aa[3][3], a_i[3][3], e[3][3], det;

double fabs(double n)
{
	double f;
# 59 "originaux/minver2.c"
	if(n >= 0)
# 59 "originaux/minver2.c"
		f = n;
	else
# 60 "originaux/minver2.c"
# 60 "originaux/minver2.c"
		f = -n;
# 61 "originaux/minver2.c"
	return f;
}

void main()
{
	int i, j;
	double eps;
# 69 "originaux/minver2.c"
	eps = 1.0e-6;
# 71 "originaux/minver2.c"
	for(i = 0; i < 3; i++)
# 72 "originaux/minver2.c"
		for(j = 0; j < 3; j++)
# 73 "originaux/minver2.c"
			(aa[i])[j] = (a[i])[j];
# 75 "originaux/minver2.c"
	minver(3, 3, eps);
# 76 "originaux/minver2.c"
	for(i = 0; i < 3; i++)
# 77 "originaux/minver2.c"
		for(j = 0; j < 3; j++)
# 78 "originaux/minver2.c"
			(a_i[i])[j] = (a[i])[j];
# 80 "originaux/minver2.c"
	mmul(3, 3, 3, 3);
}

int mmul(int row_a, int col_a, int row_b, int col_b)
{
	char __tmp_0__ = 0;
	int __return__;
	int i, j, k, row_c, col_c;
	double w;
# 89 "originaux/minver2.c"
	row_c = row_a;
# 90 "originaux/minver2.c"
	col_c = col_b;
# 92 "originaux/minver2.c"
	if(row_c < 1 || row_b < 1 || col_c < 1 || col_a != row_b)
	{
# 92 "originaux/minver2.c"
		__return__ = 999;
		__tmp_0__ = 1 != 0;
	}
	if(!__tmp_0__)
# 93 "originaux/minver2.c"
		for(i = 0; i < row_c; i++)
# 94 "originaux/minver2.c"
		{
# 95 "originaux/minver2.c"
			for(j = 0; j < col_c; j++)
# 96 "originaux/minver2.c"
			{
# 97 "originaux/minver2.c"
				w = 0.0;
# 98 "originaux/minver2.c"
				for(k = 0; k < row_b; k++)
# 99 "originaux/minver2.c"
					w += (a[i])[k] * (b[k])[j];
# 100 "originaux/minver2.c"
				(c[i])[j] = w;
			}
		}
# 103 "originaux/minver2.c"
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
# 114 "originaux/minver2.c"
	if(row < 2 || row > 500 || eps <= 0.0)
	{
# 114 "originaux/minver2.c"
		__return__ = 999;
		__tmp_0__ = 1 != 0;
	}
	if(!__tmp_0__)
	{
# 115 "originaux/minver2.c"
		w1 = 1.0;
# 116 "originaux/minver2.c"
		for(i2 = 0; i2 < row; i2++)
# 116 "originaux/minver2.c"
			work[i2] = i2;
# 117 "originaux/minver2.c"
		for(k = 0; !__tmp_0__ && k < row; __tmp_0__ || k++)
# 118 "originaux/minver2.c"
		{
# 119 "originaux/minver2.c"
			wmax = 0.0;
# 120 "originaux/minver2.c"
			for(i = k; i < row; i++)
# 121 "originaux/minver2.c"
			{
# 122 "originaux/minver2.c"
				w = fabs((a[i])[k]);
# 123 "originaux/minver2.c"
				if(w > wmax)
# 123 "originaux/minver2.c"
				{
# 123 "originaux/minver2.c"
					wmax = w;
# 123 "originaux/minver2.c"
					r = i;
				}
			}
# 125 "originaux/minver2.c"
			pivot = (a[r])[k];
# 126 "originaux/minver2.c"
			api = fabs(pivot);
# 127 "originaux/minver2.c"
			if(api <= eps)
# 127 "originaux/minver2.c"
			{
# 127 "originaux/minver2.c"
				det = w1;
# 127 "originaux/minver2.c"
				__return__ = 1;
				__tmp_0__ = 1 != 0;
			}
			if(!__tmp_0__)
			{
# 128 "originaux/minver2.c"
				w1 *= pivot;
# 129 "originaux/minver2.c"
				u = k * col;
# 130 "originaux/minver2.c"
				v = r * col;
# 131 "originaux/minver2.c"
				if(r != k)
# 132 "originaux/minver2.c"
				{
# 133 "originaux/minver2.c"
					w1 = -w;
# 134 "originaux/minver2.c"
					iw = work[k];
# 135 "originaux/minver2.c"
					work[k] = work[r];
# 136 "originaux/minver2.c"
					work[r] = iw;
# 137 "originaux/minver2.c"
					for(j = 0; j < row; j++)
# 138 "originaux/minver2.c"
					{
# 139 "originaux/minver2.c"
						s = u + j;
# 140 "originaux/minver2.c"
						t = v + j;
# 141 "originaux/minver2.c"
						w = (a[k])[j];
# 142 "originaux/minver2.c"
						(a[k])[j] = (a[r])[j];
# 143 "originaux/minver2.c"
						(a[r])[j] = w;
					}
				}
# 146 "originaux/minver2.c"
				for(i3 = 0; i3 < row; i3++)
# 146 "originaux/minver2.c"
					(a[k])[i3] /= pivot;
# 147 "originaux/minver2.c"
				for(i4 = 0; i4 < row; i4++)
# 148 "originaux/minver2.c"
				{
# 149 "originaux/minver2.c"
					if(i4 != k)
# 150 "originaux/minver2.c"
					{
# 151 "originaux/minver2.c"
						v = i4 * col;
# 152 "originaux/minver2.c"
						s = v + k;
# 153 "originaux/minver2.c"
						w = (a[i4])[k];
# 154 "originaux/minver2.c"
						if(w != 0.0)
# 155 "originaux/minver2.c"
						{
# 156 "originaux/minver2.c"
							for(j2 = 0; j2 < row;
								j2++)
							{
# 157 "originaux/minver2.c"
	if(j2 != k)
# 157 "originaux/minver2.c"
		(a[i4])[j2] -= w * (a[k])[j2];
							}
# 158 "originaux/minver2.c"
							(a[i4])[k] = -(w /
								pivot);
						}
					}
				}
# 162 "originaux/minver2.c"
				(a[k])[k] = 1.0 / pivot;
			}
		}
		if(!__tmp_0__)
		{
# 166 "originaux/minver2.c"
			for(i5 = 0; i5 < row; i5++)
# 167 "originaux/minver2.c"
			{
# 168 "originaux/minver2.c"
				while(!__tmp_1__ && 1)
# 169 "originaux/minver2.c"
				{
# 170 "originaux/minver2.c"
					k = work[i5];
# 171 "originaux/minver2.c"
					if(k == i5)
# 171 "originaux/minver2.c"
						__tmp_1__ = 1 != 0;
					if(!__tmp_1__)
					{
# 172 "originaux/minver2.c"
						iw = work[k];
# 173 "originaux/minver2.c"
						work[k] = work[i5];
# 174 "originaux/minver2.c"
						work[i5] = iw;
# 175 "originaux/minver2.c"
						for(j = 0; j < row; j++)
# 176 "originaux/minver2.c"
						{
# 177 "originaux/minver2.c"
							u = j * col;
# 178 "originaux/minver2.c"
							s = u + i5;
# 179 "originaux/minver2.c"
							t = u + k;
# 180 "originaux/minver2.c"
							w = (a[k])[i5];
# 181 "originaux/minver2.c"
							(a[k])[i5] = (a[k])[k];
# 182 "originaux/minver2.c"
							(a[k])[k] = w;
						}
					}
				}
				__tmp_1__ = 0;
			}
# 186 "originaux/minver2.c"
			det = w1;
		}
	}
# 187 "originaux/minver2.c"
	if(!__tmp_0__)
		__return__ = 0;
	__tmp_0__ = 0;
	return __return__;
}

