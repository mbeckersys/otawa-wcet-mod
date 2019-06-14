
unsigned char num_to_lcd(unsigned char a)
{
	char __tmp_1__ = 0, __tmp_2__ = 0, __tmp_3__ = 0, __tmp_4__ = 0,
		__tmp_5__ = 0, __tmp_6__ = 0, __tmp_7__ = 0, __tmp_8__ = 0,
		__tmp_9__ = 0, __tmp_10__ = 0, __tmp_11__ = 0, __tmp_12__ = 0,
		__tmp_13__ = 0, __tmp_14__ = 0, __tmp_15__ = 0, __tmp_16__ = 0,
		__tmp_0__ = 0;
	unsigned char __return__;
# 45 "originaux/lcdnum.c"
	{
		int __tag_0__ = a;
		if(__tag_0__ == 0x00)
			__tmp_1__ = 1 != 0;
		else
		{
			if(__tag_0__ == 0x01)
				__tmp_2__ = 1 != 0;
			else
			{
				if(__tag_0__ == 0x02)
					__tmp_3__ = 1 != 0;
				else
				{
					if(__tag_0__ == 0x03)
						__tmp_4__ = 1 != 0;
					else
					{
						if(__tag_0__ == 0x04)
							__tmp_5__ = 1 != 0;
						else
						{
							if(__tag_0__ == 0x05)
	__tmp_6__ = 1 != 0;
							else
							{
	if(__tag_0__ == 0x06)
		__tmp_7__ = 1 != 0;
	else
	{
		if(__tag_0__ == 0x07)
			__tmp_8__ = 1 != 0;
		else
		{
			if(__tag_0__ == 0x08)
				__tmp_9__ = 1 != 0;
			else
			{
				if(__tag_0__ == 0x09)
					__tmp_10__ = 1 != 0;
				else
				{
					if(__tag_0__ == 0x0A)
						__tmp_11__ = 1 != 0;
					else
					{
						if(__tag_0__ == 0x0B)
							__tmp_12__ = 1 != 0;
						else
						{
							if(__tag_0__ == 0x0C)
	__tmp_13__ = 1 != 0;
							else
							{
	if(__tag_0__ == 0x0D)
		__tmp_14__ = 1 != 0;
	else
	{
		if(__tag_0__ == 0x0E)
			__tmp_15__ = 1 != 0;
		else
			__tmp_16__ = __tag_0__ == 0x0F;
	}
							}
						}
					}
				}
			}
		}
	}
							}
						}
					}
				}
			}
		}
		if(__tmp_1__ || (__tmp_2__ || (__tmp_3__ || (__tmp_4__ ||
			(__tmp_5__ || (__tmp_6__ || (__tmp_7__ || (__tmp_8__ ||
			(__tmp_9__ || (__tmp_10__ || (__tmp_11__ || (__tmp_12__
			|| (__tmp_13__ || (__tmp_14__ || (__tmp_15__ ||
			(__tmp_16__ || 0))))))))))))))))
# 47 "originaux/lcdnum.c"
		{
			if(!__tmp_16__)
			{
				if(!__tmp_15__)
				{
					if(!__tmp_14__)
					{
						if(!__tmp_13__)
						{
							if(!__tmp_12__)
							{
	if(!__tmp_11__)
	{
		if(!__tmp_10__)
		{
			if(!__tmp_9__)
			{
				if(!__tmp_8__)
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
# 49 "originaux/lcdnum.c"
				__tmp_1__ = 0;
# 49 "originaux/lcdnum.c"
				__return__ = 0;
				__tmp_0__ = 1 != 0;
			}
			if(!__tmp_0__)
			{
# 51 "originaux/lcdnum.c"
				__tmp_2__ = 0;
# 51 "originaux/lcdnum.c"
				__return__ = 0x24;
				__tmp_0__ = 1 != 0;
			}
		}
		if(!__tmp_0__)
		{
# 53 "originaux/lcdnum.c"
			__tmp_3__ = 0;
# 53 "originaux/lcdnum.c"
			__return__ = 1 + 4 + 8 + 16 + 64;
			__tmp_0__ = 1 != 0;
		}
	}
	if(!__tmp_0__)
	{
# 55 "originaux/lcdnum.c"
		__tmp_4__ = 0;
# 55 "originaux/lcdnum.c"
		__return__ = 1 + 4 + 8 + 32 + 64;
		__tmp_0__ = 1 != 0;
	}
							}
							if(!__tmp_0__)
							{
# 57 "originaux/lcdnum.c"
	__tmp_5__ = 0;
# 57 "originaux/lcdnum.c"
	__return__ = 2 + 4 + 8 + 32;
	__tmp_0__ = 1 != 0;
							}
						}
						if(!__tmp_0__)
						{
# 59 "originaux/lcdnum.c"
							__tmp_6__ = 0;
# 59 "originaux/lcdnum.c"
							__return__ = 1 + 4 + 8 +
								16 + 64;
							__tmp_0__ = 1 != 0;
						}
					}
					if(!__tmp_0__)
					{
# 61 "originaux/lcdnum.c"
						__tmp_7__ = 0;
# 61 "originaux/lcdnum.c"
						__return__ = 1 + 2 + 8 + 16 + 32
							+ 64;
						__tmp_0__ = 1 != 0;
					}
				}
				if(!__tmp_0__)
				{
# 63 "originaux/lcdnum.c"
					__tmp_8__ = 0;
# 63 "originaux/lcdnum.c"
					__return__ = 1 + 4 + 32;
					__tmp_0__ = 1 != 0;
				}
			}
			if(!__tmp_0__)
			{
# 65 "originaux/lcdnum.c"
				__tmp_9__ = 0;
# 65 "originaux/lcdnum.c"
				__return__ = 0x7F;
				__tmp_0__ = 1 != 0;
			}
		}
		if(!__tmp_0__)
		{
# 67 "originaux/lcdnum.c"
			__tmp_10__ = 0;
# 67 "originaux/lcdnum.c"
			__return__ = 0x0F + 32 + 64;
			__tmp_0__ = 1 != 0;
		}
	}
	if(!__tmp_0__)
	{
# 69 "originaux/lcdnum.c"
		__tmp_11__ = 0;
# 69 "originaux/lcdnum.c"
		__return__ = 0x0F + 16 + 32;
		__tmp_0__ = 1 != 0;
	}
							}
							if(!__tmp_0__)
							{
# 71 "originaux/lcdnum.c"
	__tmp_12__ = 0;
# 71 "originaux/lcdnum.c"
	__return__ = 2 + 8 + 16 + 32 + 64;
	__tmp_0__ = 1 != 0;
							}
						}
						if(!__tmp_0__)
						{
# 73 "originaux/lcdnum.c"
							__tmp_13__ = 0;
# 73 "originaux/lcdnum.c"
							__return__ = 1 + 2 + 16
								+ 64;
							__tmp_0__ = 1 != 0;
						}
					}
					if(!__tmp_0__)
					{
# 75 "originaux/lcdnum.c"
						__tmp_14__ = 0;
# 75 "originaux/lcdnum.c"
						__return__ = 4 + 8 + 16 + 32 +
							64;
						__tmp_0__ = 1 != 0;
					}
				}
				if(!__tmp_0__)
				{
# 77 "originaux/lcdnum.c"
					__tmp_15__ = 0;
# 77 "originaux/lcdnum.c"
					__return__ = 1 + 2 + 8 + 16 + 64;
					__tmp_0__ = 1 != 0;
				}
			}
			if(!__tmp_0__)
			{
# 79 "originaux/lcdnum.c"
				__tmp_16__ = 0;
# 79 "originaux/lcdnum.c"
				__return__ = 1 + 2 + 8 + 16;
				__tmp_0__ = 1 != 0;
			}
		}
	}
# 83 "originaux/lcdnum.c"
	if(!__tmp_0__)
		__return__ = 0;
	__tmp_0__ = 0;
	return __return__;
}

unsigned char  volatile IN;
unsigned char  volatile OUT;

void main(void )
{
	int i;
	unsigned char a;
# 105 "originaux/lcdnum.c"
	for(i = 0; i < 10; i++)
# 107 "originaux/lcdnum.c"
	{
# 109 "originaux/lcdnum.c"
		a = IN;
# 111 "originaux/lcdnum.c"
		if(i < 5)
# 113 "originaux/lcdnum.c"
		{
# 115 "originaux/lcdnum.c"
			a = a & 0x0F;
# 117 "originaux/lcdnum.c"
			OUT = num_to_lcd(a);
		}
	}
}

