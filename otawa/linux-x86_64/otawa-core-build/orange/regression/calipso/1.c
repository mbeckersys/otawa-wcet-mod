/* loop bound depend on a variable of assigned into a previous one */

int X = 0;

int main(void) 
{
	int i,j,k;

	for (i = 0; i < 10; i++) 
	{
	  for (j = 0; j < 5; j ++) 
		{
		    X = 15;
		  }
		for (k = 0; k < X; k ++) {
	  }
}}
