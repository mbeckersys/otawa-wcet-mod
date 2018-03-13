
int foo(int j)
{
	int i, result = 0;
# 4 "originaux/foo.c"
	for(i = 0; i < 100; i++)
# 6 "originaux/foo.c"
	{
# 7 "originaux/foo.c"
		result += 2;
	}
# 9 "originaux/foo.c"
	return result;
}

int main(void )
{
	int i, j, n = 10, c = 2, p;
# 15 "originaux/foo.c"
	for(i = get_value(); i <= n; i = i + c)
# 17 "originaux/foo.c"
	{
# 18 "originaux/foo.c"
		p = i - c * 2;
# 19 "originaux/foo.c"
		result += 2;
# 20 "originaux/foo.c"
		if(p)
# 20 "originaux/foo.c"
			k = i + 2;
	}
# 22 "originaux/foo.c"
	j = i + k;
# 23 "originaux/foo.c"
	j = foo(p);
# 24 "originaux/foo.c"
	return 0;
}

