
int f(int n)
{
	int i, j, k;
	int s = 0;
# 10 "originaux/rapita2.c"
	for(i = 0; i < n; i++)
	{
# 11 "originaux/rapita2.c"
		if(i % 2 == 0)
# 12 "originaux/rapita2.c"
			for(j = 0; j < 5; j++)
# 13 "originaux/rapita2.c"
				s += 3;
		else
# 14 "originaux/rapita2.c"
# 15 "originaux/rapita2.c"
			for(k = 0; k < 3; k++)
# 16 "originaux/rapita2.c"
				s += 2;
	}
}

main()
{
	int i = f(10);
	int j = f(3);
}

