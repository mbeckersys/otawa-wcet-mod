
int f(int n)
{
	int i, j, k;
	int s = 0;
# 10 "originaux/rapita.c"
	for(i = 0; i < n; i++)
	{
# 11 "originaux/rapita.c"
		if(i < 6)
# 12 "originaux/rapita.c"
			for(j = 0; j < 5; j++)
# 13 "originaux/rapita.c"
				s += 3;
		else
# 14 "originaux/rapita.c"
# 15 "originaux/rapita.c"
			for(k = 0; k < 3; k++)
# 16 "originaux/rapita.c"
				s += 2;
	}
}

main()
{
	int i = f(10);
	int j = f(3);
}

