#include <stdio.h>
struct DATA {
	int key;
	int value;
} ;

struct DATA data[15] = {{1, 100}, {4, 200}, {5, 300}, {6, 700}, {7, 900}, {8,
	250}, {9, 400}, {11, 600}, {12, 800}, {13, 1500}, {14, 1200}, {15,
	110}, {16, 140}, {17, 133}, {18, 10}};

main()
{
# 73 "originaux/bs.c"
	binary_search(10);
}

binary_search(x)
{
	int fvalue, mid, up, low;
# 80 "originaux/bs.c"
	low = 0;
# 81 "originaux/bs.c"
	up = 14;
# 82 "originaux/bs.c"
	fvalue = -1;
# 83 "originaux/bs.c"
	while(low <= up)
# 83 "originaux/bs.c"
	{
# 84 "originaux/bs.c"
		mid = low + up >> 1;
# 85 "originaux/bs.c"
		if((data[mid]).key == x)
# 85 "originaux/bs.c"
		{
# 86 "originaux/bs.c"
			up = low - 1;
printf("test 1 %d up %d low %d mid\n", up, low, mid);
# 87 "originaux/bs.c"
			fvalue = (data[mid]).value;
		}
		else
		{
# 92 "originaux/bs.c"
# 93 "originaux/bs.c"
			if((data[mid]).key > x)
# 93 "originaux/bs.c"
			{printf("test 2 %d up %d low %d mid\n", up, low, mid);
# 94 "originaux/bs.c"
				up = mid - 1;
			}
			else
# 99 "originaux/bs.c"
# 99 "originaux/bs.c"
			{printf("test 3 %d up %d low %d mid\n", up, low, mid);
# 100 "originaux/bs.c"
				low = mid + 1;
			}
		}
	}
# 112 "originaux/bs.c"
	return fvalue;
}

