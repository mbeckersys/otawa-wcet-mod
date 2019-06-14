
struct DATA {
	int key;
	int value;
} ;

struct DATA data[15] = {{1, 100}, {5, 200}, {6, 300}, {7, 700}, {8, 900}, {9,
	250}, {10, 400}, {11, 600}, {12, 800}, {13, 1500}, {14, 1200}, {15,
	110}, {16, 140}, {17, 133}, {18, 10}};

main()
{
# 43 "originaux/bc.c"
	binary_search(8);
}

binary_search(x)
{
	int fvalue, mid, up, low;
# 50 "originaux/bc.c"
	low = 0;
# 51 "originaux/bc.c"
	up = 14;
# 52 "originaux/bc.c"
	fvalue = -1;
# 53 "originaux/bc.c"
	while(low <= up)
# 54 "originaux/bc.c"
	{
# 55 "originaux/bc.c"
		mid = low + up >> 1;
# 56 "originaux/bc.c"
		if((data[mid]).key == x)
# 57 "originaux/bc.c"
		{
# 58 "originaux/bc.c"
			up = low - 1;
# 59 "originaux/bc.c"
			fvalue = (data[mid]).value;
		}
		else
		{
# 61 "originaux/bc.c"
# 62 "originaux/bc.c"
			if((data[mid]).key > x)
# 62 "originaux/bc.c"
				up = mid - 1;
			else
# 63 "originaux/bc.c"
# 63 "originaux/bc.c"
				low = mid + 1;
		}
	}
# 65 "originaux/bc.c"
	return fvalue;
}

