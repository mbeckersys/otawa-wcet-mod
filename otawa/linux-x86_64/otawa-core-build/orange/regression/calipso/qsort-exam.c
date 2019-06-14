float arr[20] = {5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99, 10, 150, 222.22,
	101, 77, 44, 35, 20.54, 99.99, 88.88};
int istack[100];

void sort(unsigned long int n)
{
	char __tmp_0__ = 0, __tmp_2__ = 0, __tmp_1__ = 0;
	unsigned long int i, ir = n, j, k, l = 1;
	int jstack = 0;
	int flag;
	float a, temp;
# 63 "originaux/qsort-exam.c"
	flag = 0;
# 64 "originaux/qsort-exam.c"
	for(; !__tmp_1__; __tmp_1__)
# 65 "originaux/qsort-exam.c"
	{
# 66 "originaux/qsort-exam.c"
		if(ir - l < 7)
# 67 "originaux/qsort-exam.c"
		{
# 68 "originaux/qsort-exam.c"
			for(j = l + 1; j <= ir; j++)
# 69 "originaux/qsort-exam.c"
			{
# 70 "originaux/qsort-exam.c"
				a = arr[j];
# 71 "originaux/qsort-exam.c"
				for(i = j - 1; !__tmp_0__ && i >= l; __tmp_0__
					|| i--)
# 72 "originaux/qsort-exam.c"
				{
# 73 "originaux/qsort-exam.c"
					if(arr[i] <= a)
# 73 "originaux/qsort-exam.c"
						__tmp_0__ = 1 != 0;
					if(!__tmp_0__)
# 74 "originaux/qsort-exam.c"
						arr[i + 1] = arr[i];
				}
				__tmp_0__ = 0;
# 76 "originaux/qsort-exam.c"
				arr[i + 1] = a;
			}
# 78 "originaux/qsort-exam.c"
			if(jstack == 0)
# 78 "originaux/qsort-exam.c"
				__tmp_1__ = 1 != 0;
			if(!__tmp_1__)
			{
# 79 "originaux/qsort-exam.c"
				ir = istack[jstack--];
# 80 "originaux/qsort-exam.c"
				l = istack[jstack--];
			}
		}
		else
# 81 "originaux/qsort-exam.c"
# 82 "originaux/qsort-exam.c"
		{
# 83 "originaux/qsort-exam.c"
			k = l + ir >> 1;
# 84 "originaux/qsort-exam.c"
			temp = arr[k];
# 84 "originaux/qsort-exam.c"
			arr[k] = arr[l + 1];
# 84 "originaux/qsort-exam.c"
			arr[l + 1] = temp;
# 85 "originaux/qsort-exam.c"
			if(arr[l] > arr[ir])
# 86 "originaux/qsort-exam.c"
			{
# 87 "originaux/qsort-exam.c"
				temp = arr[l];
# 87 "originaux/qsort-exam.c"
				arr[l] = arr[ir];
# 87 "originaux/qsort-exam.c"
				arr[ir] = temp;
			}
# 89 "originaux/qsort-exam.c"
			if(arr[l + 1] > arr[ir])
# 90 "originaux/qsort-exam.c"
			{
# 91 "originaux/qsort-exam.c"
				temp = arr[l + 1];
# 91 "originaux/qsort-exam.c"
				arr[l + 1] = arr[ir];
# 91 "originaux/qsort-exam.c"
				arr[ir] = temp;
			}
# 93 "originaux/qsort-exam.c"
			if(arr[l] > arr[l + 1])
# 94 "originaux/qsort-exam.c"
			{
# 95 "originaux/qsort-exam.c"
				temp = arr[l];
# 95 "originaux/qsort-exam.c"
				arr[l] = arr[l + 1];
# 95 "originaux/qsort-exam.c"
				arr[l + 1] = temp;
			}
# 97 "originaux/qsort-exam.c"
			i = l + 1;
# 98 "originaux/qsort-exam.c"
			j = ir;
# 99 "originaux/qsort-exam.c"
			a = arr[l + 1];
# 100 "originaux/qsort-exam.c"
			for(; !__tmp_2__; __tmp_2__)
# 101 "originaux/qsort-exam.c"
			{
# 102 "originaux/qsort-exam.c"
				i++;
# 102 "originaux/qsort-exam.c"
				while(arr[i] < a)
# 102 "originaux/qsort-exam.c"
					i++;
# 103 "originaux/qsort-exam.c"
				j--;
# 103 "originaux/qsort-exam.c"
				while(arr[j] > a)
# 103 "originaux/qsort-exam.c"
					j--;
# 104 "originaux/qsort-exam.c"
				if(j < i)
# 104 "originaux/qsort-exam.c"
					__tmp_2__ = 1 != 0;
				if(!__tmp_2__)
				{
# 105 "originaux/qsort-exam.c"
					temp = arr[i];
# 105 "originaux/qsort-exam.c"
					arr[i] = arr[j];
# 105 "originaux/qsort-exam.c"
					arr[j] = temp;
# 105 "originaux/qsort-exam.c"
					;
				}
			}
			__tmp_2__ = 0;
# 107 "originaux/qsort-exam.c"
			arr[l + 1] = arr[j];
# 108 "originaux/qsort-exam.c"
			arr[j] = a;
# 109 "originaux/qsort-exam.c"
			jstack += 2;
# 111 "originaux/qsort-exam.c"
			if(ir - i + 1 >= j - l)
# 111 "originaux/qsort-exam.c"
			{
# 112 "originaux/qsort-exam.c"
				istack[jstack] = ir;
# 113 "originaux/qsort-exam.c"
				istack[jstack - 1] = i;
# 114 "originaux/qsort-exam.c"
				ir = j - 1;
			}
			else
# 115 "originaux/qsort-exam.c"
# 115 "originaux/qsort-exam.c"
			{
# 116 "originaux/qsort-exam.c"
				istack[jstack] = j - 1;
# 117 "originaux/qsort-exam.c"
				istack[jstack - 1] = l;
# 118 "originaux/qsort-exam.c"
				l = i;
			}
		}
	}
	__tmp_1__ = 0;
}

main()
{
# 126 "originaux/qsort-exam.c"
	sort(20);
}

