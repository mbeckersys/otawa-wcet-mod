int _MAX(select_0);
int _MAX(select_0_0);
int _MAX(select_0_0_0);
int _MAX(select_0_0_1);
float arr[20] = {5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99, 10, 150, 222.22,
	101, 77, 44, 35, 20.54, 99.99, 888.88};

float select(unsigned long int k, unsigned long int n)
{
	unsigned long int i, ir, j, l, mid;
	float a, temp;
	int flag, flag2;
# 67 "originaux/select.c"
	_BEGIN(select_0);
# 69 "originaux/select.c"
	l = 1;
# 70 "originaux/select.c"
	ir = n;
# 71 "originaux/select.c"
	flag = ((flag2 = 0));
# 72 "originaux/select.c"
	while(!flag)
# 72 "originaux/select.c"
	{
# 73 "originaux/select.c"
		_BEGIN(select_0_0);
# 74 "originaux/select.c"
		_COUNT(select_0);
# 75 "originaux/select.c"
		if(ir <= l + 1)
# 75 "originaux/select.c"
		{
# 76 "originaux/select.c"
			if(ir == l + 1)
			{
# 77 "originaux/select.c"
				if(arr[ir] < arr[l])
# 77 "originaux/select.c"
				{
# 78 "originaux/select.c"
					temp = arr[l];
# 78 "originaux/select.c"
					arr[l] = arr[ir];
# 78 "originaux/select.c"
					arr[ir] = temp;
				}
			}
# 80 "originaux/select.c"
			flag = 1;
		}
		else
		{
# 81 "originaux/select.c"
# 81 "originaux/select.c"
			if(!flag)
# 81 "originaux/select.c"
			{
# 82 "originaux/select.c"
				mid = l + ir >> 1;
# 83 "originaux/select.c"
				temp = arr[mid];
# 83 "originaux/select.c"
				arr[mid] = arr[l + 1];
# 83 "originaux/select.c"
				arr[l + 1] = temp;
# 84 "originaux/select.c"
				if(arr[l + 1] > arr[ir])
# 84 "originaux/select.c"
				{
# 85 "originaux/select.c"
					temp = arr[l + 1];
# 85 "originaux/select.c"
					arr[l + 1] = arr[ir];
# 85 "originaux/select.c"
					arr[ir] = temp;
				}
# 87 "originaux/select.c"
				if(arr[l] > arr[ir])
# 87 "originaux/select.c"
				{
# 88 "originaux/select.c"
					temp = arr[l];
# 88 "originaux/select.c"
					arr[l] = arr[ir];
# 88 "originaux/select.c"
					arr[ir] = temp;
				}
# 90 "originaux/select.c"
				if(arr[l + 1] > arr[l])
# 90 "originaux/select.c"
				{
# 91 "originaux/select.c"
					temp = arr[l + 1];
# 91 "originaux/select.c"
					arr[l + 1] = arr[l];
# 91 "originaux/select.c"
					arr[l] = temp;
				}
# 93 "originaux/select.c"
				i = l + 1;
# 94 "originaux/select.c"
				j = ir;
# 95 "originaux/select.c"
				a = arr[l];
# 96 "originaux/select.c"
				while(!flag2)
# 96 "originaux/select.c"
				{
# 97 "originaux/select.c"
					_BEGIN(select_0_0_0);
# 98 "originaux/select.c"
					_BEGIN(select_0_0_1);
# 99 "originaux/select.c"
					_COUNT(select_0_0);
# 100 "originaux/select.c"
					i++;
# 101 "originaux/select.c"
					while(arr[i] < a)
# 101 "originaux/select.c"
					{
# 101 "originaux/select.c"
						i++;
# 101 "originaux/select.c"
						_COUNT(select_0_0_0);
					}
# 102 "originaux/select.c"
					j--;
# 103 "originaux/select.c"
					while(arr[j] > a)
# 103 "originaux/select.c"
					{
# 103 "originaux/select.c"
						j--;
# 103 "originaux/select.c"
						_COUNT(select_0_0_1);
					}
# 104 "originaux/select.c"
					if(j < i)
# 104 "originaux/select.c"
						flag2 = 1;
# 105 "originaux/select.c"
					if(!flag2)
# 105 "originaux/select.c"
						temp = arr[i];
# 105 "originaux/select.c"
					arr[i] = arr[j];
# 105 "originaux/select.c"
					arr[j] = temp;
# 105 "originaux/select.c"
					;
# 106 "originaux/select.c"
					_END(select_0_0_0);
# 107 "originaux/select.c"
					_END(select_0_0_1);
				}
# 109 "originaux/select.c"
				_END(select_0_0);
# 110 "originaux/select.c"
				arr[l] = arr[j];
# 111 "originaux/select.c"
				arr[j] = a;
# 112 "originaux/select.c"
				if(j >= k)
# 112 "originaux/select.c"
					ir = j - 1;
# 113 "originaux/select.c"
				if(j <= k)
# 113 "originaux/select.c"
					l = i;
			}
		}
	}
# 117 "originaux/select.c"
	_END(select_0);
# 118 "originaux/select.c"
	return arr[k];
}

main()
{
# 123 "originaux/select.c"
	select(10, 20);
# 124 "originaux/select.c"
	_PRINT(select_0);
# 125 "originaux/select.c"
	_PRINT(select_0_0);
# 126 "originaux/select.c"
	_PRINT(select_0_0_0);
# 127 "originaux/select.c"
	_PRINT(select_0_0_1);
}

