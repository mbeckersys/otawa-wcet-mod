
int complex(int a, int b)
{
# 31 "originaux/janne_complex.c"
	while(a < 30)
# 32 "originaux/janne_complex.c"
	{
# 33 "originaux/janne_complex.c"
		while(b < a)
# 34 "originaux/janne_complex.c"
		{
# 35 "originaux/janne_complex.c"
			if(b > 5)
# 36 "originaux/janne_complex.c"
				b = b * 3;
			else
# 37 "originaux/janne_complex.c"
# 38 "originaux/janne_complex.c"
				b = b + 2;
# 39 "originaux/janne_complex.c"
			if(b >= 10 && b <= 12)
# 40 "originaux/janne_complex.c"
				a = a + 10;
			else
# 41 "originaux/janne_complex.c"
# 42 "originaux/janne_complex.c"
				a = a + 1;
		}
# 44 "originaux/janne_complex.c"
		a = a + 2;
# 45 "originaux/janne_complex.c"
		b = b - 10;
	}
# 47 "originaux/janne_complex.c"
	return 1;
}

int main()
{
	int a = 1, b = 1, answer = 0;
# 58 "originaux/janne_complex.c"
	answer = complex(a, b);
# 59 "originaux/janne_complex.c"
	return answer;
}

