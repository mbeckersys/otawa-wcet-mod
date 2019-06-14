
void pakonpozan(int x)
{
	int i = 0;
# 4 "originaux/clement12.c"
	for(i = 0; i < x; i++)
# 4 "originaux/clement12.c"
		;
# 7 "originaux/clement12.c"
	for(i = 0; i < Y; i++)
# 7 "originaux/clement12.c"
		;
# 9 "originaux/clement12.c"
	Y = 1;
}

int Y;

int main(void )
{
	int k;
	int v;
	int i;
	int x;
# 19 "originaux/clement12.c"
	for(v = 0; v < 5; v++)
# 19 "originaux/clement12.c"
	{
# 20 "originaux/clement12.c"
		k = 0;
# 21 "originaux/clement12.c"
		for(k = 0; k < 10; k++)
# 21 "originaux/clement12.c"
		{
# 22 "originaux/clement12.c"
			Y = k * 2;
# 23 "originaux/clement12.c"
			pakonpozan(k + 5);
		}
	}
}

