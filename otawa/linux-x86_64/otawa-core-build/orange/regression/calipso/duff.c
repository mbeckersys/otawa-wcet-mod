
void duffcopy(char *to, char *from, int count)
{
	char __tmp_0__ = 0, __tmp_1__ = 0, __tmp_2__ = 0, __tmp_3__ = 0,
		__tmp_4__ = 0, __tmp_5__ = 0, __tmp_6__ = 0, __tmp_7__ = 0;
	int n = ((count + 7)) / 8;
# 14 "originaux/duff.c"
	do
# 14 "originaux/duff.c"
	{
# 14 "originaux/duff.c"
		n--;
# 15 "originaux/duff.c"
		{
			int __tag_0__ = count % 8;
			if(__tag_0__ == 0)
				__tmp_0__ = 1 != 0;
			else
			{
				if(__tag_0__ == 7)
					__tmp_1__ = 1 != 0;
				else
				{
					if(__tag_0__ == 6)
						__tmp_2__ = 1 != 0;
					else
					{
						if(__tag_0__ == 5)
							__tmp_3__ = 1 != 0;
						else
						{
							if(__tag_0__ == 4)
	__tmp_4__ = 1 != 0;
							else
							{
	if(__tag_0__ == 3)
		__tmp_5__ = 1 != 0;
	else
	{
		if(__tag_0__ == 2)
			__tmp_6__ = 1 != 0;
		else
			__tmp_7__ = __tag_0__ == 1;
	}
							}
						}
					}
				}
			}
			if(__tmp_0__ || (__tmp_1__ || (__tmp_2__ || (__tmp_3__
				|| (__tmp_4__ || (__tmp_5__ || (__tmp_6__ ||
				(__tmp_7__ || 0))))))))
# 16 "originaux/duff.c"
			{
				if(!__tmp_7__)
				{
					if(!__tmp_6__)
					{
						if(!__tmp_5__)
						{
							if(!__tmp_4__)
							{
	if(!__tmp_3__)
	{
		if(!__tmp_2__)
		{
			if(!__tmp_1__)
			{
# 18 "originaux/duff.c"
				__tmp_0__ = 0;
# 20 "originaux/duff.c"
				*to++ = *from++;
			}
# 22 "originaux/duff.c"
			__tmp_1__ = 0;
# 22 "originaux/duff.c"
			*to++ = *from++;
		}
# 24 "originaux/duff.c"
		__tmp_2__ = 0;
# 24 "originaux/duff.c"
		*to++ = *from++;
	}
# 26 "originaux/duff.c"
	__tmp_3__ = 0;
# 26 "originaux/duff.c"
	*to++ = *from++;
							}
# 28 "originaux/duff.c"
							__tmp_4__ = 0;
# 28 "originaux/duff.c"
							*to++ = *from++;
						}
# 30 "originaux/duff.c"
						__tmp_5__ = 0;
# 30 "originaux/duff.c"
						*to++ = *from++;
					}
# 32 "originaux/duff.c"
					__tmp_6__ = 0;
# 32 "originaux/duff.c"
					*to++ = *from++;
				}
# 34 "originaux/duff.c"
				__tmp_7__ = 0;
# 34 "originaux/duff.c"
				*to++ = *from++;
			}
		}
	}
	while(n > 0);
}

void initialize(char *arr, int length)
{
	int i;
# 53 "originaux/duff.c"
	for(i = 0; i < length; i++)
# 55 "originaux/duff.c"
	{
# 57 "originaux/duff.c"
		arr[i] = length - i;
	}
}

char source[100];
char target[100];

void main(void )
{
# 77 "originaux/duff.c"
	initialize(source, 100);
# 79 "originaux/duff.c"
	duffcopy(source, target, 43);
}

