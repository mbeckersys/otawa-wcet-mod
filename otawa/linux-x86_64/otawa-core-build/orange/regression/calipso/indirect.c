
main()
{
	char L7 = 0;
	int i, j;
# 9 "originaux/indirect.c"
	for(i = 0, j = 1; j <= 10; i += 2, j = i)
# 9 "originaux/indirect.c"
		;
# 11 "originaux/indirect.c"
	for(i = 10, j = 1; j >= 0; i -= 2, j = i)
# 11 "originaux/indirect.c"
		;
# 13 "originaux/indirect.c"
	for(i = 0, j = 1; j <= 10; j = i, i += 2)
# 13 "originaux/indirect.c"
		;
# 15 "originaux/indirect.c"
	for(i = 10, j = 1; j >= 0; j = i, i -= 2)
# 15 "originaux/indirect.c"
		;
# 17 "originaux/indirect.c"
	j = 1;
# 17 "originaux/indirect.c"
	i = 0;
# 19 "originaux/indirect.c"
	while(j <= 10)
# 19 "originaux/indirect.c"
	{
# 19 "originaux/indirect.c"
		i += 2;
# 19 "originaux/indirect.c"
		j = i;
	}
# 21 "originaux/indirect.c"
	j = 1;
# 21 "originaux/indirect.c"
	i = 10;
# 23 "originaux/indirect.c"
	while(j >= 0)
# 23 "originaux/indirect.c"
	{
# 23 "originaux/indirect.c"
		i -= 2;
# 23 "originaux/indirect.c"
		j = i;
	}
	L7 = 0;
# 25 "originaux/indirect.c"
	j = 1;
# 25 "originaux/indirect.c"
	i = 0;
# 27 "originaux/indirect.c"
	while(j <= 10)
# 27 "originaux/indirect.c"
	{
# 27 "originaux/indirect.c"
		j = i;
# 27 "originaux/indirect.c"
		i += 2;
	}
# 27 "originaux/indirect.c"
	;
# 29 "originaux/indirect.c"
	j = 1;
# 29 "originaux/indirect.c"
	i = 10;
# 31 "originaux/indirect.c"
	while(j >= 0)
# 31 "originaux/indirect.c"
	{
# 31 "originaux/indirect.c"
		j = i;
# 31 "originaux/indirect.c"
		i -= 2;
	}
# 31 "originaux/indirect.c"
	;
# 33 "originaux/indirect.c"
	j = 1;
# 33 "originaux/indirect.c"
	i = 0;
# 35 "originaux/indirect.c"
	do
# 35 "originaux/indirect.c"
	{
# 35 "originaux/indirect.c"
		i += 2;
# 35 "originaux/indirect.c"
		j = i;
	}
	while(j <= 10);
# 37 "originaux/indirect.c"
	j = 1;
# 37 "originaux/indirect.c"
	i = 10;
# 39 "originaux/indirect.c"
	do
# 39 "originaux/indirect.c"
	{
# 39 "originaux/indirect.c"
		i -= 2;
# 39 "originaux/indirect.c"
		j = i;
	}
	while(j >= 0);
# 41 "originaux/indirect.c"
	j = 1;
# 41 "originaux/indirect.c"
	i = 0;
# 43 "originaux/indirect.c"
	do
# 43 "originaux/indirect.c"
	{
# 43 "originaux/indirect.c"
		j = i;
# 43 "originaux/indirect.c"
		i += 2;
	}
	while(j <= 10);
# 45 "originaux/indirect.c"
	j = 1;
# 45 "originaux/indirect.c"
	i = 10;
# 47 "originaux/indirect.c"
	do
# 47 "originaux/indirect.c"
	{
# 47 "originaux/indirect.c"
		j = i;
# 47 "originaux/indirect.c"
		i -= 2;
	}
	while(j >= 0);
# 49 "originaux/indirect.c"
	for(i = 0 + 1, j = 1; j <= 10; i *= 2, j = i)
# 49 "originaux/indirect.c"
		;
# 51 "originaux/indirect.c"
	for(i = 10, j = 1; j > 0; i /= 2, j = i)
# 51 "originaux/indirect.c"
		;
# 53 "originaux/indirect.c"
	for(i = 0 + 1, j = 1; j <= 10; j = i, i *= 2)
# 53 "originaux/indirect.c"
		;
# 55 "originaux/indirect.c"
	for(i = 10, j = 1; j > 0; j = i, i /= 2)
# 55 "originaux/indirect.c"
		;
# 57 "originaux/indirect.c"
	j = 1;
# 57 "originaux/indirect.c"
	i = 0 + 1;
# 59 "originaux/indirect.c"
	while(j <= 10)
# 59 "originaux/indirect.c"
	{
# 59 "originaux/indirect.c"
		i *= 2;
# 59 "originaux/indirect.c"
		j = i;
	}
# 61 "originaux/indirect.c"
	j = 1;
# 61 "originaux/indirect.c"
	i = 10;
# 63 "originaux/indirect.c"
	while(j > 0)
# 63 "originaux/indirect.c"
	{
# 63 "originaux/indirect.c"
		i /= 2;
# 63 "originaux/indirect.c"
		j = i;
	}
# 65 "originaux/indirect.c"
	j = 1;
# 65 "originaux/indirect.c"
	i = 0 + 1;
# 67 "originaux/indirect.c"
	while(j <= 10)
# 67 "originaux/indirect.c"
	{
# 67 "originaux/indirect.c"
		j = i;
# 67 "originaux/indirect.c"
		i *= 2;
	}
# 69 "originaux/indirect.c"
	j = 1;
# 69 "originaux/indirect.c"
	i = 10;
# 71 "originaux/indirect.c"
	while(j > 0)
# 71 "originaux/indirect.c"
	{
# 71 "originaux/indirect.c"
		j = i;
# 71 "originaux/indirect.c"
		i /= 2;
	}
# 73 "originaux/indirect.c"
	j = 1;
# 73 "originaux/indirect.c"
	i = 0 + 1;
# 75 "originaux/indirect.c"
	do
# 75 "originaux/indirect.c"
	{
# 75 "originaux/indirect.c"
		i *= 2;
# 75 "originaux/indirect.c"
		j = i;
	}
	while(j <= 10);
# 77 "originaux/indirect.c"
	j = 1;
# 77 "originaux/indirect.c"
	i = 10;
# 79 "originaux/indirect.c"
	do
# 79 "originaux/indirect.c"
	{
# 79 "originaux/indirect.c"
		i /= 2;
# 79 "originaux/indirect.c"
		j = i;
	}
	while(j > 0);
# 81 "originaux/indirect.c"
	j = 1;
# 81 "originaux/indirect.c"
	i = 0 + 1;
# 83 "originaux/indirect.c"
	do
# 83 "originaux/indirect.c"
	{
# 83 "originaux/indirect.c"
		j = i;
# 83 "originaux/indirect.c"
		i *= 2;
	}
	while(j <= 10);
# 85 "originaux/indirect.c"
	j = 1;
# 85 "originaux/indirect.c"
	i = 10;
# 87 "originaux/indirect.c"
	do
# 87 "originaux/indirect.c"
	{
# 87 "originaux/indirect.c"
		j = i;
# 87 "originaux/indirect.c"
		i /= 2;
	}
	while(j > 0);
}

