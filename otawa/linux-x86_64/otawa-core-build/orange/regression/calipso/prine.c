
int prine(unsigned int n)
{
	char __tmp_0__ = 0;
	int __return__;
	unsigned int i;
# 8 "originaux/prine.c"
	if(n % 2 == 0)
	{
# 8 "originaux/prine.c"
		__return__ = n == 2;
		__tmp_0__ = 1 != 0;
	}
	if(!__tmp_0__)
# 10 "originaux/prine.c"
		for(i = 3; !__tmp_0__ && i * i <= n; __tmp_0__ || ((i += 2)))
# 11 "originaux/prine.c"
		{
# 12 "originaux/prine.c"
			if(i % n == 0)
			{
# 12 "originaux/prine.c"
				__return__ = 0;
				__tmp_0__ = 1 != 0;
			}
		}
# 14 "originaux/prine.c"
	if(!__tmp_0__)
		__return__ = n > 1;
	__tmp_0__ = 0;
	return __return__;
}

int main(void )
{
	unsigned int x = 513239;
	unsigned int y = 21649;
	int res1 = !prine(x);
	int res2 = res1 && prine(y);
# 25 "originaux/prine.c"
	return res2;
}

