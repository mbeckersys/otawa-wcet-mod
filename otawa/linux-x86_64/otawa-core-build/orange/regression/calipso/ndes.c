
typedef struct IMMENSE {
	unsigned long int l, r;
} immense;

typedef struct GREAT {
	unsigned long int l, c, r;
} great;

unsigned long int bit[33];
static immense icd;
static char ipc1[57] = {0, 57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39,
	31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21,
	13, 5, 28, 20, 12, 4};
static char ipc2[49] = {0, 14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19,
	12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51,
	45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};
void des(immense inp, immense key, int *newkey, int isw, immense *out);
unsigned long int getbit(immense source, int bitno, int nbits);
void ks(int n, great *kn);
void cyfun(unsigned long int ir, great k, unsigned long int *iout);

void des(immense inp, immense key, int *newkey, int isw, immense *out)
{
	static char ip[65] = {0, 58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36,
		28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40,
		32, 24, 16, 8, 57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27,
		19, 11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31,
		23, 15, 7};
	static char ipm[65] = {0, 40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15,
		55, 23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13,
		53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11,
		51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49,
		17, 57, 25};
	static great kns[17];
	static int initflag = 1;
	int ii, i, j, k;
	unsigned long int ic, shifter, getbit();
	immense itmp;
	great pg;
# 62 "originaux/ndes.c"
	if(initflag)
# 62 "originaux/ndes.c"
	{
# 63 "originaux/ndes.c"
		initflag = 0;
# 64 "originaux/ndes.c"
		bit[1] = ((shifter = 1L));
# 65 "originaux/ndes.c"
		for(j = 2; j <= 32; j++)
# 65 "originaux/ndes.c"
			bit[j] = (((shifter <<= 1)));
	}
# 67 "originaux/ndes.c"
	if(*newkey)
# 67 "originaux/ndes.c"
	{
# 68 "originaux/ndes.c"
		*newkey = 0;
# 69 "originaux/ndes.c"
		icd.r = ((icd.l = 0L));
# 70 "originaux/ndes.c"
		for(j = 28, k = 56; j >= 1; j--, k--)
# 70 "originaux/ndes.c"
		{
# 71 "originaux/ndes.c"
			icd.r = (((icd.r <<= 1))) | getbit(key, ipc1[j], 32);
# 72 "originaux/ndes.c"
			icd.l = (((icd.l <<= 1))) | getbit(key, ipc1[k], 32);
		}
# 75 "originaux/ndes.c"
		for(i = 1; i <= 16; i++)
# 75 "originaux/ndes.c"
		{
# 75 "originaux/ndes.c"
			pg = kns[i];
# 75 "originaux/ndes.c"
			ks(i, &pg);
# 75 "originaux/ndes.c"
			kns[i] = pg;
		}
	}
# 77 "originaux/ndes.c"
	itmp.r = ((itmp.l = 0L));
# 78 "originaux/ndes.c"
	for(j = 32, k = 64; j >= 1; j--, k--)
# 78 "originaux/ndes.c"
	{
# 79 "originaux/ndes.c"
		itmp.r = (((itmp.r <<= 1))) | getbit(inp, ip[j], 32);
# 80 "originaux/ndes.c"
		itmp.l = (((itmp.l <<= 1))) | getbit(inp, ip[k], 32);
	}
# 82 "originaux/ndes.c"
	for(i = 1; i <= 16; i++)
# 82 "originaux/ndes.c"
	{
# 83 "originaux/ndes.c"
		ii = isw == 1 ? 17 - i : i;
# 84 "originaux/ndes.c"
		cyfun(itmp.l, kns[ii], &ic);
# 85 "originaux/ndes.c"
		ic ^= itmp.r;
# 86 "originaux/ndes.c"
		itmp.r = itmp.l;
# 87 "originaux/ndes.c"
		itmp.l = ic;
	}
# 89 "originaux/ndes.c"
	ic = itmp.r;
# 90 "originaux/ndes.c"
	itmp.r = itmp.l;
# 91 "originaux/ndes.c"
	itmp.l = ic;
# 92 "originaux/ndes.c"
	((*out)).r = ((((*out)).l = 0L));
# 93 "originaux/ndes.c"
	for(j = 32, k = 64; j >= 1; j--, k--)
# 93 "originaux/ndes.c"
	{
# 94 "originaux/ndes.c"
		((*out)).r = (((((*out)).r <<= 1))) | getbit(itmp, ipm[j], 32);
# 95 "originaux/ndes.c"
		((*out)).l = (((((*out)).l <<= 1))) | getbit(itmp, ipm[k], 32);
	}
}

unsigned long int getbit(immense source, int bitno, int nbits)
{
	char __tmp_0__ = 0;
	unsigned long int __return__;
# 99 "originaux/ndes.c"
	if(bitno <= nbits)
	{
# 100 "originaux/ndes.c"
		__return__ = bit[bitno] & source.r ? 1L : 0L;
		__tmp_0__ = 1 != 0;
	}
	else
	{
# 101 "originaux/ndes.c"
# 102 "originaux/ndes.c"
		__return__ = bit[bitno - nbits] & source.l ? 1L : 0L;
		__tmp_0__ = 1 != 0;
	}
	__tmp_0__ = 0;
	return __return__;
}

void ks(int n, great *kn)
{
	int i, j, k, l;
# 108 "originaux/ndes.c"
	if(n == 1 || n == 2 || n == 9 || n == 16)
# 108 "originaux/ndes.c"
	{
# 109 "originaux/ndes.c"
		icd.r = ((icd.r | ((icd.r & 1L)) << 28)) >> 1;
# 110 "originaux/ndes.c"
		icd.l = ((icd.l | ((icd.l & 1L)) << 28)) >> 1;
	}
	else
# 112 "originaux/ndes.c"
# 113 "originaux/ndes.c"
		for(i = 1; i <= 2; i++)
# 113 "originaux/ndes.c"
		{
# 114 "originaux/ndes.c"
			icd.r = ((icd.r | ((icd.r & 1L)) << 28)) >> 1;
# 115 "originaux/ndes.c"
			icd.l = ((icd.l | ((icd.l & 1L)) << 28)) >> 1;
		}
# 117 "originaux/ndes.c"
	((*kn)).r = ((((*kn)).c = ((((*kn)).l = 0))));
# 118 "originaux/ndes.c"
	for(j = 16, k = 32, l = 48; j >= 1; j--, k--, l--)
# 118 "originaux/ndes.c"
	{
# 120 "originaux/ndes.c"
		((*kn)).r = (((((*kn)).r <<= 1))) |
			(unsigned short int)getbit(icd, ipc2[j], 28);
# 122 "originaux/ndes.c"
		((*kn)).c = (((((*kn)).c <<= 1))) |
			(unsigned short int)getbit(icd, ipc2[k], 28);
# 124 "originaux/ndes.c"
		((*kn)).l = (((((*kn)).l <<= 1))) |
			(unsigned short int)getbit(icd, ipc2[l], 28);
	}
}

void cyfun(unsigned long int ir, great k, unsigned long int *iout)
{
	static char iet[49] = {0, 32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10,
		11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20,
		21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,
		1};
	static char ipp[33] = {0, 16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26,
		5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22,
		11, 4, 25};
	static char is[16][4][9] = {0, 14, 15, 10, 7, 2, 12, 4, 13, 0, 0, 3, 13,
		13, 14, 10, 13, 1, 0, 4, 0, 13, 10, 4, 9, 1, 7, 0, 15, 13, 1, 3,
		11, 4, 6, 2, 0, 4, 1, 0, 13, 12, 1, 11, 2, 0, 15, 13, 7, 8, 11,
		15, 0, 15, 0, 1, 14, 6, 6, 2, 14, 4, 11, 0, 12, 8, 10, 15, 8, 3,
		11, 1, 0, 13, 8, 9, 14, 4, 10, 2, 8, 0, 7, 4, 0, 11, 2, 4, 11,
		13, 0, 14, 7, 4, 9, 1, 15, 11, 4, 0, 8, 10, 13, 0, 12, 2, 13,
		14, 0, 1, 14, 14, 3, 1, 15, 14, 4, 0, 4, 7, 9, 5, 12, 2, 7, 8,
		0, 8, 11, 9, 0, 11, 5, 13, 1, 0, 2, 1, 0, 6, 7, 12, 8, 7, 0, 2,
		6, 6, 0, 7, 9, 15, 6, 0, 14, 15, 3, 6, 4, 7, 4, 10, 0, 13, 10,
		8, 12, 10, 2, 12, 9, 0, 4, 3, 6, 10, 1, 9, 1, 4, 0, 15, 11, 3,
		6, 10, 2, 0, 15, 0, 2, 2, 4, 15, 7, 12, 9, 3, 0, 6, 4, 15, 11,
		13, 8, 3, 12, 0, 9, 15, 9, 1, 14, 5, 4, 10, 0, 11, 3, 15, 9, 11,
		6, 8, 11, 0, 13, 8, 6, 0, 13, 9, 1, 7, 0, 2, 13, 3, 7, 7, 12, 7,
		14, 0, 1, 4, 8, 13, 2, 15, 10, 8, 0, 8, 4, 5, 10, 6, 8, 13, 1,
		0, 1, 14, 10, 3, 1, 5, 10, 4, 0, 11, 1, 0, 13, 8, 3, 14, 2, 0,
		7, 2, 7, 8, 13, 10, 7, 13, 0, 3, 9, 1, 1, 8, 0, 3, 10, 0, 10,
		12, 2, 4, 5, 6, 14, 12, 0, 15, 5, 11, 15, 15, 7, 10, 0, 0, 5,
		11, 4, 9, 6, 11, 9, 15, 0, 10, 7, 13, 2, 5, 13, 12, 9, 0, 6, 0,
		8, 7, 0, 1, 3, 5, 0, 12, 8, 1, 1, 9, 0, 15, 6, 0, 11, 6, 15, 4,
		15, 14, 5, 12, 0, 6, 2, 12, 8, 3, 3, 9, 3, 0, 12, 1, 5, 2, 15,
		13, 5, 6, 0, 9, 12, 2, 3, 12, 4, 6, 10, 0, 3, 7, 14, 5, 0, 1, 0,
		9, 0, 12, 13, 7, 5, 15, 4, 7, 14, 0, 11, 10, 14, 12, 10, 14, 12,
		11, 0, 7, 6, 12, 14, 5, 10, 8, 13, 0, 14, 12, 3, 11, 9, 7, 15,
		0, 0, 5, 12, 11, 11, 13, 14, 5, 5, 0, 9, 6, 12, 1, 3, 0, 2, 0,
		0, 3, 9, 5, 5, 6, 1, 0, 15, 0, 10, 0, 11, 12, 10, 6, 14, 3, 0,
		9, 0, 4, 12, 0, 7, 10, 0, 0, 5, 9, 11, 10, 9, 11, 15, 14, 0, 10,
		3, 10, 2, 3, 13, 5, 3, 0, 0, 5, 5, 7, 4, 0, 2, 5, 0, 0, 5, 2, 4,
		14, 5, 6, 12, 0, 3, 11, 15, 14, 8, 3, 8, 9, 0, 5, 2, 14, 8, 0,
		11, 9, 5, 0, 6, 14, 2, 2, 5, 8, 3, 6, 0, 7, 10, 8, 15, 9, 11, 1,
		7, 0, 8, 5, 1, 9, 6, 8, 6, 2, 0, 0, 15, 7, 4, 14, 6, 2, 8, 0,
		13, 9, 12, 14, 3, 13, 12, 11};
	static char ibin[16] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11,
		7, 15};
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
//		 pie->l =1;//(((ie.l <<= 1))) | ((p[iet[m]] & ir ? 1 : 0));
	}
# 183 "originaux/ndes.c"
	ie.r ^= k.r;
# 184 "originaux/ndes.c"
	ie.c ^= k.c;
# 185 "originaux/ndes.c"
	ie.l ^= k.l;
# 186 "originaux/ndes.c"
	ietmp1 = (((unsigned long int)ie.c << 16)) + (unsigned long int)ie.r;
# 187 "originaux/ndes.c"
	ietmp2 = (((unsigned long int)ie.l << 8)) + (((unsigned long int)ie.c >>
		8));
# 188 "originaux/ndes.c"
	for(j = 1, m = 5; j <= 4; j++, m++)
# 188 "originaux/ndes.c"
	{
# 189 "originaux/ndes.c"
		iec[j] = ietmp1 & 0x3fL;
# 190 "originaux/ndes.c"
		iec[m] = ietmp2 & 0x3fL;
# 191 "originaux/ndes.c"
		ietmp1 >>= 6;
# 192 "originaux/ndes.c"
		ietmp2 >>= 6;
	}
# 194 "originaux/ndes.c"
	itmp = 0L;
# 195 "originaux/ndes.c"
	for(jj = 8; jj >= 1; jj--)
# 195 "originaux/ndes.c"
	{
# 196 "originaux/ndes.c"
		j = iec[jj];
# 197 "originaux/ndes.c"
		irow = ((((j & 0x1)) << 1)) + ((((j & 0x20)) >> 5));
# 199 "originaux/ndes.c"
		icol = ((((j & 0x2)) << 2)) + ((j & 0x4)) + ((((j & 0x8)) >> 2))
			+ ((((j & 0x10)) >> 4));
# 200 "originaux/ndes.c"
		iss = ((is[icol])[irow])[jj];
# 201 "originaux/ndes.c"
		itmp = (((itmp <<= 4))) | ibin[iss];
	}
# 203 "originaux/ndes.c"
	*iout = 0L;
# 204 "originaux/ndes.c"
	p = bit;
# 205 "originaux/ndes.c"
	for(j = 32; j >= 1; j--)
# 206 "originaux/ndes.c"
		*iout = (((*iout <<= 1))) | ((p[ipp[j]] & itmp ? 1 : 0));
}

int value = 1;

int main(void )
{
	immense inp, key, out;
	int newkey, isw;
# 219 "originaux/ndes.c"
	inp.l = 1 * 35;
# 220 "originaux/ndes.c"
	inp.r = 1 * 26;
# 221 "originaux/ndes.c"
	key.l = 1 * 2;
# 222 "originaux/ndes.c"
	key.r = 1 * 16;
# 224 "originaux/ndes.c"
	newkey = value;
# 225 "originaux/ndes.c"
	isw = value;
# 227 "originaux/ndes.c"
	des(inp, key, &newkey, isw, &out);
# 229 "originaux/ndes.c"
	return 0;
}

