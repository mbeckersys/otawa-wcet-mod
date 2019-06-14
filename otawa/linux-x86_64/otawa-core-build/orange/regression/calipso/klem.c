extern int X;
int kompop(int j);/*
{
int k;
for(k=0;k<j;k++);X=X+10;
}*/

int main()
{
	int i;X=3;
	kompop(5);

	for(i=0;i<X;i++); 
}


