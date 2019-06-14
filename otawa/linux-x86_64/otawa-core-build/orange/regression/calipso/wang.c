/* wang.c article Flow analysis on Intermediate Source code for Wcet estimation of compiler-optimized Program */

int main()
{
	int a[50];
	int i, j, temp;
	a[0]=0;
	i=2;
	while(i<=10)
	{
		j= i;
		while(a[j]<a[j-1])
		{
			j--;
		}
		i++;
	}
	

}
