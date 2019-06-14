
int ttime()
{
	struct tms buffer;
	int utime;
# 43 "originaux/bsort100.c"
	utime = buffer.tms_utime / 60.0 * 1000.0;
# 44 "originaux/bsort100.c"
	return utime;
}

void Initialize(int Array[])
{
	int Index, fact;
# 54 "originaux/bsort100.c"
	factor = -1;
# 59 "originaux/bsort100.c"
	fact = factor;
# 60 "originaux/bsort100.c"
	for(Index = 1; Index <= 100; Index++)
# 61 "originaux/bsort100.c"
		Array[Index] = Index * fact * (int)((*(char*)0x80200001));
}

void BubbleSort(int Array[])
{
	int Sorted = 0;
	int Temp, LastIndex, Index, i;
# 72 "originaux/bsort100.c"
	for(i = 1; i <= 100 - 1; i++)
# 73 "originaux/bsort100.c"
	{
# 74 "originaux/bsort100.c"
		Sorted = 1;
# 75 "originaux/bsort100.c"
		for(Index = 1; Index <= 100 - 1; Index++)
# 76 "originaux/bsort100.c"
		{
# 79 "originaux/bsort100.c"
			if(Array[Index] > Array[Index + 1])
# 80 "originaux/bsort100.c"
			{
# 81 "originaux/bsort100.c"
				Temp = Array[Index];
# 82 "originaux/bsort100.c"
				Array[Index] = Array[Index + 1];
# 83 "originaux/bsort100.c"
				Array[Index + 1] = Temp;
# 84 "originaux/bsort100.c"
				Sorted = 0;
			}
		}
	}
}

void main()
{
	long int StartTime, StopTime;
	float TotalTime;
	int Array[100 + 1], Seed;
	int factor;
# 111 "originaux/bsort100.c"
	Initialize(Array);
# 113 "originaux/bsort100.c"
	BubbleSort(Array);
}

