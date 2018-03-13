long int expint(int n, long int x);

void main(void )
{
# 11 "originaux/expint.c"
	expint(50, 1);
}

long int foo(long int x)
{
# 22 "originaux/expint.c"
	return x * x + 8 * x << 4 - x;
}

long int expint(int n, long int x)
{
	char __tmp_0__ = 0;
	long int __return__;
	int i, ii, nm1;
	long int a, b, c, d, del, fact, h, psi, ans;
# 44 "originaux/expint.c"
	nm1 = n - 1;
# 48 "originaux/expint.c"
	if(x > 1)
# 50 "originaux/expint.c"
	{
# 52 "originaux/expint.c"
		b = x + n;
# 54 "originaux/expint.c"
		c = 2e6;
# 56 "originaux/expint.c"
		d = 3e7;
# 58 "originaux/expint.c"
		h = d;
# 62 "originaux/expint.c"
		for(i = 1; !__tmp_0__ && i <= 100; __tmp_0__ || i++)
# 64 "originaux/expint.c"
		{
# 66 "originaux/expint.c"
			a = -(i * ((nm1 + i)));
# 68 "originaux/expint.c"
			b += 2;
# 70 "originaux/expint.c"
			d = 10 * ((a * d + b));
# 72 "originaux/expint.c"
			c = b + a / c;
# 74 "originaux/expint.c"
			del = c * d;
# 76 "originaux/expint.c"
			h *= del;
# 78 "originaux/expint.c"
			if(del < 10000)
# 80 "originaux/expint.c"
			{
# 82 "originaux/expint.c"
				ans = h * -x;
# 84 "originaux/expint.c"
				__return__ = ans;
				__tmp_0__ = 1 != 0;
			}
		}
	}
	else
# 92 "originaux/expint.c"
# 94 "originaux/expint.c"
	{
# 96 "originaux/expint.c"
		ans = nm1 != 0 ? 2 : 1000;
# 98 "originaux/expint.c"
		fact = 1;
# 100 "originaux/expint.c"
		for(i = 1; i <= 100; i++)
# 102 "originaux/expint.c"
		{
# 104 "originaux/expint.c"
			fact *= -(x / i);
# 106 "originaux/expint.c"
			if(i != nm1)
# 108 "originaux/expint.c"
				del = -(fact / ((i - nm1)));
			else
# 110 "originaux/expint.c"
# 112 "originaux/expint.c"
			{
# 114 "originaux/expint.c"
				psi = 0x00FF;
# 116 "originaux/expint.c"
				for(ii = 1; ii <= nm1; ii++)
# 118 "originaux/expint.c"
					psi += ii + nm1;
# 120 "originaux/expint.c"
				del = psi + fact * foo(x);
			}
# 124 "originaux/expint.c"
			ans += del;
		}
	}
# 134 "originaux/expint.c"
	if(!__tmp_0__)
		__return__ = ans;
	__tmp_0__ = 0;
	return __return__;
}

