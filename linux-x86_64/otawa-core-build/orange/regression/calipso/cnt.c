
typedef int matrix[10][10];

int main(void );
int Test(matrix );
int Initialize(matrix );
int InitSeed(void );
void Sum(matrix );
int RandomInteger(void );
int Seed;
matrix Array;
int Postotal, Negtotal, Poscnt, Negcnt;

int main(void )
{
# 61 "originaux/cnt.c"
	InitSeed();
# 67 "originaux/cnt.c"
	Test(Array);
# 69 "originaux/cnt.c"
	return 1;
}

int Test(matrix Array)
{
	long int StartTime, StopTime;
	float TotalTime;
# 87 "originaux/cnt.c"
	Initialize(Array);
# 89 "originaux/cnt.c"
	StartTime = 1000.0;
# 91 "originaux/cnt.c"
	Sum(Array);
# 93 "originaux/cnt.c"
	StopTime = 1500.0;
# 97 "originaux/cnt.c"
	TotalTime = ((StopTime - StartTime)) / 1000.0;
# 111 "originaux/cnt.c"
	return 0;
}

int Initialize(matrix Array)
{
	register int OuterIndex, InnerIndex;
# 129 "originaux/cnt.c"
	for(OuterIndex = 0; OuterIndex < 10; OuterIndex++)
# 131 "originaux/cnt.c"
		for(InnerIndex = 0; InnerIndex < 10; InnerIndex++)
# 133 "originaux/cnt.c"
			(Array[OuterIndex])[InnerIndex] = RandomInteger();
# 137 "originaux/cnt.c"
	return 0;
}

int InitSeed(void )
{
# 151 "originaux/cnt.c"
	Seed = 0;
# 153 "originaux/cnt.c"
	return 0;
}

void Sum(matrix Array)
{
	register int Outer, Inner;
	int Ptotal = 0;
	int Ntotal = 0;
	int Pcnt = 0;
	int Ncnt = 0;
# 177 "originaux/cnt.c"
	for(Outer = 0; Outer < 10; Outer++)
# 179 "originaux/cnt.c"
		for(Inner = 0; Inner < 10; Inner++)
		{
# 187 "originaux/cnt.c"
			if((Array[Outer])[Inner] < 0)
# 187 "originaux/cnt.c"
			{
# 191 "originaux/cnt.c"
				Ptotal += (Array[Outer])[Inner];
# 193 "originaux/cnt.c"
				Pcnt++;
			}
			else
# 197 "originaux/cnt.c"
# 197 "originaux/cnt.c"
			{
# 199 "originaux/cnt.c"
				Ntotal += (Array[Outer])[Inner];
# 201 "originaux/cnt.c"
				Ncnt++;
			}
		}
# 207 "originaux/cnt.c"
	Postotal = Ptotal;
# 209 "originaux/cnt.c"
	Poscnt = Pcnt;
# 211 "originaux/cnt.c"
	Negtotal = Ntotal;
# 213 "originaux/cnt.c"
	Negcnt = Ncnt;
}

int RandomInteger(void )
{
# 251 "originaux/cnt.c"
	Seed = ((Seed * 133 + 81)) % 8095;
# 253 "originaux/cnt.c"
	return Seed;
}

