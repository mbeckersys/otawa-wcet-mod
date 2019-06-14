
typedef long int code_int;

typedef long int count_int;

typedef unsigned char char_type;

int n_bits;
int maxbits = 16;
code_int maxcode;
code_int maxmaxcode = 1 << 16;
code_int hsize = 257;
count_int fsize;
code_int free_ent = 0;
int exit_stat = 0;
int nomagic = 1;
int zcat_flg = 0;
int quiet = 1;
int block_compress = 0x80;
int clear_flg = 0;
long int ratio = 0;
count_int checkpoint = 10000;
int force = 0;
char ofname[100];
int InCnt;
int apsim_InCnt;
unsigned char *InBuff;
unsigned char *OutBuff;
char orig_text_buffer[50];
char comp_text_buffer[50 + 5];
count_int htab[257];
unsigned short int codetab[257];
char buf[16];
void initbuffer(void );
void compress(void );
void cl_hash(count_int 
hsize);
unsigned int getbyte(void );
void putbyte(char c);
void cl_block(void );
void output(code_int code);
void writebytes(char *buf, int n);

void main(void )
{
	int count = 50;
# 383 "originaux/compress.c"
	initbuffer();
# 395 "originaux/compress.c"
	maxbits = 16;
# 397 "originaux/compress.c"
	maxmaxcode = 1 << maxbits;
# 401 "originaux/compress.c"
	InCnt = count;
# 403 "originaux/compress.c"
	apsim_InCnt = 50 + 3;
# 405 "originaux/compress.c"
	InBuff = (unsigned char*)orig_text_buffer;
# 407 "originaux/compress.c"
	OutBuff = (unsigned char*)comp_text_buffer;
# 411 "originaux/compress.c"
	compress();
}

void initbuffer(void )
{
	int seed = 1;
	int i;
	int tabort;
# 435 "originaux/compress.c"
	for(i = 0; i < 50; i++)
# 435 "originaux/compress.c"
	{
# 439 "originaux/compress.c"
		tabort = i;
# 441 "originaux/compress.c"
		seed = ((seed * 133 + 81)) % 8095;
# 445 "originaux/compress.c"
		orig_text_buffer[i] = seed % 256;
	}
}

static int offset;
long int in_count = 1;
long int bytes_out;
long int out_count = 0;

void compress(void )
{
	char probe = 0, nomatch = 0, __tmp_0__ = 0;
	register long int fcode;
	register code_int i = 0;
	register int c;
	register code_int ent;
	register int disp;
	register code_int hsize_reg;
	register int hshift;
# 491 "originaux/compress.c"
	offset = 0;
# 493 "originaux/compress.c"
	bytes_out = 3;
# 495 "originaux/compress.c"
	out_count = 0;
# 497 "originaux/compress.c"
	clear_flg = 0;
# 499 "originaux/compress.c"
	ratio = 0;
# 501 "originaux/compress.c"
	in_count = 1;
# 503 "originaux/compress.c"
	checkpoint = 10000;
# 505 "originaux/compress.c"
	maxcode = ((1 << (((n_bits = 9))))) - 1;
# 507 "originaux/compress.c"
	free_ent = block_compress ? 257 : 256;
# 511 "originaux/compress.c"
	ent = getbyte();
# 515 "originaux/compress.c"
	hshift = 0;
# 517 "originaux/compress.c"
	for(fcode = (long int)hsize; fcode < 65536; fcode *= 2)
# 519 "originaux/compress.c"
	{
# 521 "originaux/compress.c"
		hshift++;
	}
# 527 "originaux/compress.c"
	hshift = 8 - hshift;
# 531 "originaux/compress.c"
	hsize_reg = hsize;
# 533 "originaux/compress.c"
	cl_hash((count_int)hsize_reg);
# 539 "originaux/compress.c"
	while(InCnt > 0)
	{
# 541 "originaux/compress.c"
		{
			int apsim_bound111 = 0;
# 547 "originaux/compress.c"
			c = getbyte();
# 551 "originaux/compress.c"
			in_count++;
# 553 "originaux/compress.c"
			fcode = (long int)(((((long int)c << maxbits)) + ent));
# 555 "originaux/compress.c"
			i = c << hshift ^ ent;
# 559 "originaux/compress.c"
			if(htab[i] == fcode)
# 559 "originaux/compress.c"
			{
# 561 "originaux/compress.c"
				ent = codetab[i];
# 563 "originaux/compress.c"
				__tmp_0__ = 1 != 0;
			}
			else
			{
# 565 "originaux/compress.c"
# 565 "originaux/compress.c"
				if((long int)htab[i] < 0)
# 565 "originaux/compress.c"
				{
# 567 "originaux/compress.c"
					nomatch = 1 != 0;
				}
			}
			if(!__tmp_0__)
			{
				if(!nomatch)
				{
# 571 "originaux/compress.c"
					disp = hsize_reg - i;
					do
					{
						if(!probe)
						{
# 573 "originaux/compress.c"
							if(i == 0)
# 573 "originaux/compress.c"
							{
# 574 "originaux/compress.c"
	disp = 1;
							}
						}
						probe = 0;
# 578 "originaux/compress.c"
						if((((i -= disp))) < 0)
# 578 "originaux/compress.c"
						{
# 579 "originaux/compress.c"
							i += hsize_reg;
						}
# 582 "originaux/compress.c"
						if(htab[i] == fcode)
# 582 "originaux/compress.c"
						{
# 583 "originaux/compress.c"
							ent = codetab[i];
# 584 "originaux/compress.c"
							__tmp_0__ = 1 != 0;
						}
						if(!__tmp_0__)
						{
# 587 "originaux/compress.c"
							if((long int)htab[i] > 0
								&&
								++apsim_bound111
								< in_count)
# 588 "originaux/compress.c"
	probe = 1 != 0;
						}
					}
					while(probe);
				}
				if(!__tmp_0__)
				{
					nomatch = 0;
# 591 "originaux/compress.c"
					out_count++;
# 592 "originaux/compress.c"
					ent = c;
# 593 "originaux/compress.c"
					if(free_ent < maxmaxcode)
# 593 "originaux/compress.c"
					{
# 594 "originaux/compress.c"
						codetab[i] = free_ent++;
# 595 "originaux/compress.c"
						htab[i] = fcode;
					}
					else
					{
# 596 "originaux/compress.c"
# 596 "originaux/compress.c"
						if((count_int)in_count >=
							checkpoint &&
							block_compress)
# 596 "originaux/compress.c"
						{
# 598 "originaux/compress.c"
							cl_block();
						}
					}
				}
			}
		}
		__tmp_0__ = 0;
	}
# 603 "originaux/compress.c"
	if(bytes_out > in_count)
# 603 "originaux/compress.c"
	{
# 604 "originaux/compress.c"
		exit_stat = 2;
	}
# 606 "originaux/compress.c"
	;
}

void cl_block(void )
{
	register long int rat;
# 613 "originaux/compress.c"
	checkpoint = in_count + 10000;
# 615 "originaux/compress.c"
	if(in_count > 0x007fffff)
# 615 "originaux/compress.c"
	{
# 617 "originaux/compress.c"
		rat = bytes_out >> 8;
# 619 "originaux/compress.c"
		if(rat == 0)
# 619 "originaux/compress.c"
		{
# 620 "originaux/compress.c"
			rat = 0x7fffffff;
		}
		else
# 621 "originaux/compress.c"
# 621 "originaux/compress.c"
		{
# 622 "originaux/compress.c"
			rat = in_count / rat;
		}
	}
	else
# 625 "originaux/compress.c"
# 625 "originaux/compress.c"
	{
# 626 "originaux/compress.c"
		rat = ((in_count << 8)) / bytes_out;
	}
# 629 "originaux/compress.c"
	if(rat > ratio)
# 629 "originaux/compress.c"
	{
# 630 "originaux/compress.c"
		ratio = rat;
	}
	else
# 631 "originaux/compress.c"
# 631 "originaux/compress.c"
	{
# 632 "originaux/compress.c"
		ratio = 0;
# 633 "originaux/compress.c"
		cl_hash((count_int)hsize);
# 634 "originaux/compress.c"
		free_ent = 257;
# 635 "originaux/compress.c"
		clear_flg = 1;
# 636 "originaux/compress.c"
		output((code_int)256);
	}
}

void cl_hash(count_int hsize)
{
	register count_int *htab_p = htab + hsize;
	register long int i;
	register long int m1 = -1;
# 645 "originaux/compress.c"
	i = hsize - 16;
# 647 "originaux/compress.c"
	do
# 647 "originaux/compress.c"
	{
# 648 "originaux/compress.c"
		*((htab_p - 16)) = m1;
# 649 "originaux/compress.c"
		*((htab_p - 15)) = m1;
# 650 "originaux/compress.c"
		*((htab_p - 14)) = m1;
# 651 "originaux/compress.c"
		*((htab_p - 13)) = m1;
# 652 "originaux/compress.c"
		*((htab_p - 12)) = m1;
# 653 "originaux/compress.c"
		*((htab_p - 11)) = m1;
# 654 "originaux/compress.c"
		*((htab_p - 10)) = m1;
# 655 "originaux/compress.c"
		*((htab_p - 9)) = m1;
# 656 "originaux/compress.c"
		*((htab_p - 8)) = m1;
# 657 "originaux/compress.c"
		*((htab_p - 7)) = m1;
# 658 "originaux/compress.c"
		*((htab_p - 6)) = m1;
# 659 "originaux/compress.c"
		*((htab_p - 5)) = m1;
# 660 "originaux/compress.c"
		*((htab_p - 4)) = m1;
# 661 "originaux/compress.c"
		*((htab_p - 3)) = m1;
# 662 "originaux/compress.c"
		*((htab_p - 2)) = m1;
# 663 "originaux/compress.c"
		*((htab_p - 1)) = m1;
# 664 "originaux/compress.c"
		htab_p -= 16;
# 665 "originaux/compress.c"
		i -= 16;
	}
	while(i >= 0);
# 668 "originaux/compress.c"
	for(i = i + 16; i > 0; i--)
# 668 "originaux/compress.c"
	{
# 669 "originaux/compress.c"
		*--htab_p = m1;
	}
}

unsigned int getbyte(void )
{
	char __tmp_0__ = 0;
	unsigned int __return__;
# 677 "originaux/compress.c"
	if(InCnt > 0 && apsim_InCnt-- > 0)
# 677 "originaux/compress.c"
	{
# 678 "originaux/compress.c"
		InCnt--;
# 679 "originaux/compress.c"
		__return__ = (unsigned int)(*InBuff++);
		__tmp_0__ = 1 != 0;
	}
	else
# 680 "originaux/compress.c"
# 680 "originaux/compress.c"
	{
# 681 "originaux/compress.c"
		__return__ = -1;
		__tmp_0__ = 1 != 0;
	}
	__tmp_0__ = 0;
	return __return__;
}

void putbyte(char c)
{
# 689 "originaux/compress.c"
	*OutBuff++ = c;
}

void writebytes(char *buf, int n)
{
	int i;
# 696 "originaux/compress.c"
	for(i = 0; i < n && i < 16; i++)
# 696 "originaux/compress.c"
	{
# 697 "originaux/compress.c"
		*OutBuff++ = buf[i];
	}
}

char_type lmask[9] = {0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00};
char_type rmask[9] = {0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff};

void output(code_int code)
{
	register int r_off = offset, bits = n_bits;
	register char *bp = buf;
# 716 "originaux/compress.c"
	if(code >= 0)
# 716 "originaux/compress.c"
	{
# 723 "originaux/compress.c"
		bp += r_off >> 3;
# 724 "originaux/compress.c"
		r_off &= 7;
# 730 "originaux/compress.c"
		*bp = *bp & rmask[r_off] | code << r_off & lmask[r_off];
# 731 "originaux/compress.c"
		bp++;
# 732 "originaux/compress.c"
		bits -= 8 - r_off;
# 733 "originaux/compress.c"
		code >>= 8 - r_off;
# 736 "originaux/compress.c"
		if(bits >= 8)
# 736 "originaux/compress.c"
		{
# 737 "originaux/compress.c"
			*bp++ = code;
# 738 "originaux/compress.c"
			code >>= 8;
# 739 "originaux/compress.c"
			bits -= 8;
		}
# 743 "originaux/compress.c"
		if(bits)
# 743 "originaux/compress.c"
		{
# 745 "originaux/compress.c"
			*bp = code;
		}
# 748 "originaux/compress.c"
		offset += n_bits;
# 750 "originaux/compress.c"
		if(offset == n_bits << 3)
# 750 "originaux/compress.c"
		{
# 751 "originaux/compress.c"
			bp = buf;
# 752 "originaux/compress.c"
			bits = n_bits;
# 753 "originaux/compress.c"
			bytes_out += bits;
# 755 "originaux/compress.c"
			do
# 755 "originaux/compress.c"
			{
# 756 "originaux/compress.c"
				putbyte(*bp++);
			}
			while(--bits && bp - buf < 16);
# 758 "originaux/compress.c"
			offset = 0;
		}
# 764 "originaux/compress.c"
		if(free_ent > maxcode || clear_flg > 0)
# 764 "originaux/compress.c"
		{
# 769 "originaux/compress.c"
			if(offset > 0)
# 769 "originaux/compress.c"
			{
# 770 "originaux/compress.c"
				writebytes(buf, n_bits);
# 771 "originaux/compress.c"
				bytes_out += n_bits;
			}
# 773 "originaux/compress.c"
			offset = 0;
# 774 "originaux/compress.c"
			if(clear_flg)
# 774 "originaux/compress.c"
			{
# 775 "originaux/compress.c"
				maxcode = ((1 << (((n_bits = 9))))) - 1;
# 776 "originaux/compress.c"
				clear_flg = 0;
			}
			else
# 777 "originaux/compress.c"
# 777 "originaux/compress.c"
			{
# 778 "originaux/compress.c"
				n_bits++;
# 779 "originaux/compress.c"
				if(n_bits == maxbits)
# 780 "originaux/compress.c"
				{
# 781 "originaux/compress.c"
					maxcode = maxmaxcode;
				}
				else
# 783 "originaux/compress.c"
# 785 "originaux/compress.c"
				{
# 786 "originaux/compress.c"
					maxcode = ((1 << n_bits)) - 1;
				}
			}
		}
	}
	else
# 791 "originaux/compress.c"
# 791 "originaux/compress.c"
	{
# 796 "originaux/compress.c"
		if(offset > 0)
# 797 "originaux/compress.c"
		{
# 798 "originaux/compress.c"
			writebytes(buf, ((offset + 7)) / 8);
		}
# 800 "originaux/compress.c"
		bytes_out += ((offset + 7)) / 8;
# 801 "originaux/compress.c"
		offset = 0;
	}
}

