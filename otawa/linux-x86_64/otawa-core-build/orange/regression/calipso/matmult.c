
typedef int matrix[20][20];

int Seed;
matrix ArrayA, ArrayB, ResultArray;
void Multiply(matrix A, matrix B, matrix Res);
void InitSeed(void );
void Test(matrix A, matrix B, matrix Res);
void Initialize(matrix Array);
int RandomInteger(void );

void InitSeed(void )
{
# 62 "originaux/matmult.c"
	Seed = 0;
}

void Test(matrix A, matrix B, matrix Res)
{
# 77 "originaux/matmult.c"
	Initialize(A);
# 78 "originaux/matmult.c"
	Initialize(B);
# 85 "originaux/matmult.c"
	Multiply(A, B, Res);
}

void Initialize(matrix Array)
{
	int OuterIndex, InnerIndex;
# 104 "originaux/matmult.c"
	for(OuterIndex = 0; OuterIndex < 20; OuterIndex++)
# 105 "originaux/matmult.c"
		for(InnerIndex = 0; InnerIndex < 20; InnerIndex++)
# 106 "originaux/matmult.c"
			(Array[OuterIndex])[InnerIndex] = RandomInteger();
}

int RandomInteger(void )
{
# 115 "originaux/matmult.c"
	Seed = ((Seed * 133 + 81)) % 8095;
# 116 "originaux/matmult.c"
	return Seed;
}

void Multiply(matrix A, matrix B, matrix Res)
{
	register int Outer, Inner, Index;
# 143 "originaux/matmult.c"
	for(Outer = 0; Outer < 20; Outer++)
# 144 "originaux/matmult.c"
		for(Inner = 0; Inner < 20; Inner++)
# 145 "originaux/matmult.c"
		{
# 146 "originaux/matmult.c"
			(Res[Outer])[Inner] = 0;
# 147 "originaux/matmult.c"
			for(Index = 0; Index < 20; Index++)
# 149 "originaux/matmult.c"
				(Res[Outer])[Inner] += (A[Outer])[Index] *
					(B[Index])[Inner];
		}
}

int main()
{
# 155 "originaux/matmult.c"
	InitSeed();
# 162 "originaux/matmult.c"
	Test(ArrayA, ArrayB, ResultArray);
# 163 "originaux/matmult.c"
	return 0;
}

