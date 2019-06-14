


typedef struct GREAT {
	unsigned long int l, c, r;
} great;





void cyfun(unsigned long int ir)
{

	great ie , *pie;
	pie=&ie;
	unsigned long int itmp, ietmp1, ietmp2;
	char iec[9];
	int jj, irow, icol, iss, j, l, m;
	unsigned long int *p;
# 176 "originaux/ndes.c"
	p = bit;
# 177 "originaux/ndes.c"
	ie.r = ((ie.c = ((ie.l = 0))));
# 178 "originaux/ndes.c"
	for(j = 16, l = 32, m = 48; j >= 1; j--, l--, m--)
# 178 "originaux/ndes.c"
	{
# 179 "originaux/ndes.c"
		ie.r = (((ie.r <<= 1))) | ((p[iet[j]] & ir ? 1 : 0));
# 180 "originaux/ndes.c"
		ie.c = (((ie.c <<= 1))) | ((p[iet[l]] & ir ? 1 : 0));
ie.l = 1;
# 181 "originaux/ndes.c"
	 pie->l =1;//(((ie.l <<= 1))) | ((p[iet[m]] & ir ? 1 : 0));
	}

}


int main(void )
{

	cyfun(12);

	return 0;
}

