
typedef unsigned char uchar;

unsigned char lin[256] = "asdffeagewaHAFEFaeDsFEawFdsFaefaeerdjgp";

unsigned short int icrc1(unsigned short int crc, unsigned char onech)
{
	int i;
	unsigned short int ans = crc ^ onech << 8;
# 62 "originaux/crc.c"
	for(i = 0; i < 8; i++)
# 62 "originaux/crc.c"
	{
# 63 "originaux/crc.c"
		if(ans & 0x8000)
# 64 "originaux/crc.c"
			ans = (((ans <<= 1))) ^ 4129;
		else
# 65 "originaux/crc.c"
# 66 "originaux/crc.c"
			ans <<= 1;
	}
# 68 "originaux/crc.c"
	return ans;
}

unsigned short int icrc(unsigned short int crc, unsigned long int len, short int
	jinit, int jrev)
{
	static unsigned short int icrctb[256], init = 0;
	static uchar rchr[256];
	unsigned short int tmp1, tmp2, j, cword = crc;
	static uchar it[16] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7,
		15};
# 80 "originaux/crc.c"
	if(!init)
# 80 "originaux/crc.c"
	{
# 81 "originaux/crc.c"
		init = 1;
# 82 "originaux/crc.c"
		for(j = 0; j <= 255; j++)
# 82 "originaux/crc.c"
		{
# 83 "originaux/crc.c"
			icrctb[j] = icrc1(j << 8, (uchar)0);
# 84 "originaux/crc.c"
			rchr[j] = (uchar)((it[j & 0xF] << 4 | it[j >> 4]));
		}
	}
# 87 "originaux/crc.c"
	if(jinit >= 0)
# 87 "originaux/crc.c"
		cword = (uchar)jinit | (uchar)jinit << 8;
	else
	{
# 88 "originaux/crc.c"
# 88 "originaux/crc.c"
		if(jrev < 0)
# 89 "originaux/crc.c"
			cword = rchr[(uchar)((cword >> 8))] |
				rchr[(uchar)((cword & 0xFF))] << 8;
	}
# 93 "originaux/crc.c"
	for(j = 1; j <= len; j++)
# 93 "originaux/crc.c"
	{
# 94 "originaux/crc.c"
		if(jrev < 0)
# 94 "originaux/crc.c"
		{
# 95 "originaux/crc.c"
			tmp1 = rchr[lin[j]] ^ (uchar)((cword >> 8));
		}
		else
# 97 "originaux/crc.c"
# 97 "originaux/crc.c"
		{
# 98 "originaux/crc.c"
			tmp1 = lin[j] ^ (uchar)((cword >> 8));
		}
# 100 "originaux/crc.c"
		cword = icrctb[tmp1] ^ (uchar)((cword & 0xFF)) << 8;
	}
# 102 "originaux/crc.c"
	if(jrev >= 0)
# 102 "originaux/crc.c"
	{
# 103 "originaux/crc.c"
		tmp2 = cword;
	}
	else
# 105 "originaux/crc.c"
# 105 "originaux/crc.c"
	{
# 106 "originaux/crc.c"
		tmp2 = rchr[(uchar)((cword >> 8))] | rchr[(uchar)((cword &
			0xFF))] << 8;
	}
# 108 "originaux/crc.c"
	return tmp2;
}
volatile int n2 =40;
int main(void )
{
	unsigned short int i1, i2;
	unsigned long int n;
# 118 "originaux/crc.c"
	n = 40;
# 119 "originaux/crc.c"
	lin[n + 1] = 0;
# 120 "originaux/crc.c"
	i1 = icrc(0, n, 0, 1);
# 121 "originaux/crc.c"
	lin[n + 1] = (uchar)((i1 >> 8));
# 122 "originaux/crc.c"
	lin[n + 2] = (uchar)((i1 & 0xFF));
# 123 "originaux/crc.c"
	i2 = icrc(i1, n + 2, 0, 1);
# 124 "originaux/crc.c"
 
	i2 = icrc(i1, n2, 0, 1);
#125 "originaux/crc.c"	
	return 0;
}

