
void memset(int *buf, int c, int size)
{
	char __tmp_0__ = 0;
	void __return__;
	int pat = c << 24 | c << 16 | c << 8 | c;
	int *top = buf + size;
# 5 "originaux/memset.c"
	if(size == 0)
# 6 "originaux/memset.c"
		__tmp_0__ = 1 != 0;
	if(!__tmp_0__)
	{
# 7 "originaux/memset.c"
	/*	if(buf & 0x1 == 1)
# 8 "originaux/memset.c"
			*buf++ = pat;
# 9 "originaux/memset.c"
		if(buf + 2 <= top && buf & 0x2 == 2)
# 10 "originaux/memset.c"
			*((((int*)buf)))++ = pat;*/
# 11 "originaux/memset.c"
		while(buf + 4 <= top)
# 12 "originaux/memset.c"
			*((((int*)buf)))++ = pat;
# 13 "originaux/memset.c"
		if(buf + 2 <= top)
# 14 "originaux/memset.c"
			*((((int*)buf)))++ = pat;
	}
# 15 "originaux/memset.c"
	if(!__tmp_0__)
	{
		if(buf + 1 <= top)
# 16 "originaux/memset.c"
			*buf++ = pat;
	}
	__tmp_0__ = 0;
	return __return__;
}

void main()
{
	int buf[512];
# 22 "originaux/memset.c"
	memset(buf, 5, 511);
}

