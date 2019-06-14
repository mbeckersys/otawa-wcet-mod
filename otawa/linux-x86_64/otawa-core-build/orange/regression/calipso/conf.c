
int main()
{
	int n = 10;
# 5 "originaux/conf.c"
	for(i = 0; i < n; i++)
# 5 "originaux/conf.c"
	{
# 6 "originaux/conf.c"
		for(j = i + 1; j <= n; j++)
# 6 "originaux/conf.c"
		{
# 7 "originaux/conf.c"
			w = i + 1 + j;
# 8 "originaux/conf.c"
			for(k = 0; k <= i; k++)
# 9 "originaux/conf.c"
				w = i + 1 + k;
# 10 "originaux/conf.c"
			a = w;
		}
	}
# 13 "originaux/conf.c"
	return 1;
}

