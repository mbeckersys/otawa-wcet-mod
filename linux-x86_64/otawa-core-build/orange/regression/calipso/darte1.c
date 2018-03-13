
int indet();


void f(int m)
{
	int y=0;
	int x = m;
	while(x>=0 && y>=0)
	{
		if ( indet() )
		{
			while(y >= m &&  indet()) y++;
			x--;
		}
		y--;
	}
}

void main()
{
	f(10);
}
