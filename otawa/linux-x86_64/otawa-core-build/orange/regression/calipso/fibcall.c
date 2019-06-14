
int fib(int n)
{
	int i, Fnew, Fold, temp, ans;
# 69 "originaux/fibcall.c"
	Fnew = 1;
# 69 "originaux/fibcall.c"
	Fold = 0;
# 70 "originaux/fibcall.c"
	i = 2;
# 71 "originaux/fibcall.c"
	while(i <= n)
# 72 "originaux/fibcall.c"
	{
# 73 "originaux/fibcall.c"
		temp = Fnew;
# 74 "originaux/fibcall.c"
		Fnew = Fnew + Fold;
# 75 "originaux/fibcall.c"
		Fold = temp;
# 76 "originaux/fibcall.c"
		i++;
	}
# 78 "originaux/fibcall.c"
	ans = Fnew;
# 79 "originaux/fibcall.c"
	return ans;
}

int main()
{
	int a;
# 86 "originaux/fibcall.c"
	a = 30;
# 87 "originaux/fibcall.c"
	fib(a);
# 88 "originaux/fibcall.c"
	return a;
}

