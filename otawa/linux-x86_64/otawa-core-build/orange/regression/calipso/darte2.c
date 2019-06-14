
int indet();


void f(int m)
{
	int y=m;
	int x = m;
	while(x>=2)
	{
		x--; y = y+x;
		 
		while(y >= x &&  indet()) y--;
		x--;y = y-x;
		 
	}
}

void main()
{
	f(10);
}
