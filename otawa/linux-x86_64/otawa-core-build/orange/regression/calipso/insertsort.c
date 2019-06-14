unsigned int a[11];

int main()
{
	int i, j, temp;
# 15 "originaux/insertsort.c"
	a[0] = 0;
# 16 "originaux/insertsort.c"
	a[1] = 11;
# 16 "originaux/insertsort.c"
	a[2] = 10;
# 16 "originaux/insertsort.c"
	a[3] = 9;
# 16 "originaux/insertsort.c"
	a[4] = 8;
# 16 "originaux/insertsort.c"
	a[5] = 7;
# 16 "originaux/insertsort.c"
	a[6] = 6;
# 16 "originaux/insertsort.c"
	a[7] = 5;
# 17 "originaux/insertsort.c"
	a[8] = 4;
# 17 "originaux/insertsort.c"
	a[9] = 3;
# 17 "originaux/insertsort.c"
	a[10] = 2;
# 18 "originaux/insertsort.c"
	i = 2;
# 19 "originaux/insertsort.c"
	while(i <= 10)
# 19 "originaux/insertsort.c"
	{
# 23 "originaux/insertsort.c"
		j = i;
# 27 "originaux/insertsort.c"
		while(a[j] < a[j - 1])
# 28 "originaux/insertsort.c"
		{
# 32 "originaux/insertsort.c"
			temp = a[j];
# 33 "originaux/insertsort.c"
			a[j] = a[j - 1];
# 34 "originaux/insertsort.c"
			a[j - 1] = temp;
# 35 "originaux/insertsort.c"
			j--;
		}
# 40 "originaux/insertsort.c"
		i++;
	}
# 45 "originaux/insertsort.c"
	return 1;
}

