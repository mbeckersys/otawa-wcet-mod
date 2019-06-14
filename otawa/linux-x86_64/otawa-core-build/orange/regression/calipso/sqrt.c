
float sqrt(float val)
{
	float x = val / 10;
	float dx;
	double diff;
	double min_tol = 0.00001;
	int i, flag;
# 57 "originaux/sqrt.c"
	flag = 0;
# 58 "originaux/sqrt.c"
	if(val == 0)
# 58 "originaux/sqrt.c"
		x = 0;
	else
# 59 "originaux/sqrt.c"
# 59 "originaux/sqrt.c"
	{
# 60 "originaux/sqrt.c"
		for(i = 1; i < 20; i++)
# 61 "originaux/sqrt.c"
		{
# 62 "originaux/sqrt.c"
			if(!flag)
# 62 "originaux/sqrt.c"
			{
# 63 "originaux/sqrt.c"
				dx = ((val - x * x)) / ((2.0 * x));
# 64 "originaux/sqrt.c"
				x = x + dx;
# 65 "originaux/sqrt.c"
				diff = val - x * x;
# 66 "originaux/sqrt.c"
				if(fabs(diff) <= min_tol)
# 66 "originaux/sqrt.c"
					flag = 1;
			}
			else
# 68 "originaux/sqrt.c"
# 69 "originaux/sqrt.c"
				x = x;
		}
	}
# 72 "originaux/sqrt.c"
	return x;
}

void main()
{
# 77 "originaux/sqrt.c"
	sqrt(5);
}

