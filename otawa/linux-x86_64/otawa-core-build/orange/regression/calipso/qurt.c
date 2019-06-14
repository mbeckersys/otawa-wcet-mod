double a[3], x1[2], x2[2];
int flag;
int qurt();

double fabs(double n)
{
	double f;
# 65 "originaux/qurt.c"
	if(n >= 0)
# 65 "originaux/qurt.c"
		f = n;
	else
# 66 "originaux/qurt.c"
# 66 "originaux/qurt.c"
		f = -n;
# 67 "originaux/qurt.c"
	return f;
}

double sqrt(val)
double val;
{
	double x = val / 10;
	double dx;
	double diff;
	double min_tol = 0.00001;
	int i, flag;
# 82 "originaux/qurt.c"
	flag = 0;
# 83 "originaux/qurt.c"
	if(val == 0)
# 83 "originaux/qurt.c"
		x = 0;
	else
# 84 "originaux/qurt.c"
# 84 "originaux/qurt.c"
	{
# 85 "originaux/qurt.c"
		for(i = 1; i < 20; i++)
# 86 "originaux/qurt.c"
		{
# 87 "originaux/qurt.c"
			if(!flag)
# 87 "originaux/qurt.c"
			{
# 88 "originaux/qurt.c"
				dx = ((val - x * x)) / ((2.0 * x));
# 89 "originaux/qurt.c"
				x = x + dx;
# 90 "originaux/qurt.c"
				diff = val - x * x;
# 91 "originaux/qurt.c"
				if(fabs(diff) <= min_tol)
# 91 "originaux/qurt.c"
					flag = 1;
			}
			else
# 93 "originaux/qurt.c"
# 94 "originaux/qurt.c"
				x = x;
		}
	}
# 97 "originaux/qurt.c"
	return x;
}

void main()
{
	int flag;
# 107 "originaux/qurt.c"
	a[0] = 1.0;
# 108 "originaux/qurt.c"
	a[1] = -3.0;
# 109 "originaux/qurt.c"
	a[2] = 2.0;
# 111 "originaux/qurt.c"
	qurt();
# 114 "originaux/qurt.c"
	a[0] = 1.0;
# 115 "originaux/qurt.c"
	a[1] = -2.0;
# 116 "originaux/qurt.c"
	a[2] = 1.0;
# 118 "originaux/qurt.c"
	qurt();
# 121 "originaux/qurt.c"
	a[0] = 1.0;
# 122 "originaux/qurt.c"
	a[1] = -4.0;
# 123 "originaux/qurt.c"
	a[2] = 8.0;
# 125 "originaux/qurt.c"
	qurt();
}

int qurt()
{
	char __tmp_0__ = 0;
	int __return__;
	double d, w1, w2;
# 132 "originaux/qurt.c"
	if(a[0] == 0.0)
	{
# 132 "originaux/qurt.c"
		__return__ = 999;
		__tmp_0__ = 1 != 0;
	}
	if(!__tmp_0__)
	{
# 133 "originaux/qurt.c"
		d = a[1] * a[1] - 4 * a[0] * a[2];
# 134 "originaux/qurt.c"
		w1 = 2.0 * a[0];
# 135 "originaux/qurt.c"
		w2 = sqrt(fabs(d));
	}
# 136 "originaux/qurt.c"
	if(!__tmp_0__)
	{
		if(d > 0.0)
# 137 "originaux/qurt.c"
		{
# 138 "originaux/qurt.c"
			flag = 1;
# 139 "originaux/qurt.c"
			x1[0] = ((-a[1] + w2)) / w1;
# 140 "originaux/qurt.c"
			x1[1] = 0.0;
# 141 "originaux/qurt.c"
			x2[0] = ((-a[1] - w2)) / w1;
# 142 "originaux/qurt.c"
			x2[1] = 0.0;
# 143 "originaux/qurt.c"
			__return__ = 0;
			__tmp_0__ = 1 != 0;
		}
		else
		{
# 145 "originaux/qurt.c"
# 145 "originaux/qurt.c"
			if(d == 0.0)
# 146 "originaux/qurt.c"
			{
# 147 "originaux/qurt.c"
				flag = 0;
# 148 "originaux/qurt.c"
				x1[0] = -(a[1] / w1);
# 149 "originaux/qurt.c"
				x1[1] = 0.0;
# 150 "originaux/qurt.c"
				x2[0] = x1[0];
# 151 "originaux/qurt.c"
				x2[1] = 0.0;
# 152 "originaux/qurt.c"
				__return__ = 0;
				__tmp_0__ = 1 != 0;
			}
			else
# 154 "originaux/qurt.c"
# 155 "originaux/qurt.c"
			{
# 156 "originaux/qurt.c"
				flag = -1;
# 157 "originaux/qurt.c"
				w2 /= w1;
# 158 "originaux/qurt.c"
				x1[0] = -(a[1] / w1);
# 159 "originaux/qurt.c"
				x1[1] = w2;
# 160 "originaux/qurt.c"
				x2[0] = x1[0];
# 161 "originaux/qurt.c"
				x2[1] = -w2;
# 162 "originaux/qurt.c"
				__return__ = 0;
				__tmp_0__ = 1 != 0;
			}
		}
	}
	__tmp_0__ = 0;
	return __return__;
}

