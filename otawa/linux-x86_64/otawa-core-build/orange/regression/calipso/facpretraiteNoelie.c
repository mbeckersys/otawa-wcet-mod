
int fac(int n)
{
	signed long int b;
	int a;
# 6 "originaux/facpretraiteNoelie.c"
	a = 1;
# 7 "originaux/facpretraiteNoelie.c"
	for(b = n; b != 0; b = b - 1)
# 8 "originaux/facpretraiteNoelie.c"
		a = b * a;
# 9 "originaux/facpretraiteNoelie.c"
	return a;
}

int main(void )
{
	int i;
	int s = 0;
	int  volatile n;
# 17 "originaux/facpretraiteNoelie.c"
	n = 5;
# 18 "originaux/facpretraiteNoelie.c"
	for(i = 0; i <= n; i++)
# 19 "originaux/facpretraiteNoelie.c"
		s += fac(i);
# 20 "originaux/facpretraiteNoelie.c"
	return s;
}

