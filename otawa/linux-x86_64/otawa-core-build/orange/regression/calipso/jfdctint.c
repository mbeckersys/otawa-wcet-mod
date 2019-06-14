int data[64];

void jpeg_fdct_islow()
{
	int tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
	int tmp10, tmp11, tmp12, tmp13;
	int z1, z2, z3, z4, z5;
	int *dataptr;
	int ctr;
# 435 "originaux/jfdctint.c"
	dataptr = data;
# 437 "originaux/jfdctint.c"
	for(ctr = 8 - 1; ctr >= 0; ctr--)
# 437 "originaux/jfdctint.c"
	{
# 439 "originaux/jfdctint.c"
		tmp0 = dataptr[0] + dataptr[7];
# 441 "originaux/jfdctint.c"
		tmp7 = dataptr[0] - dataptr[7];
# 443 "originaux/jfdctint.c"
		tmp1 = dataptr[1] + dataptr[6];
# 445 "originaux/jfdctint.c"
		tmp6 = dataptr[1] - dataptr[6];
# 447 "originaux/jfdctint.c"
		tmp2 = dataptr[2] + dataptr[5];
# 449 "originaux/jfdctint.c"
		tmp5 = dataptr[2] - dataptr[5];
# 451 "originaux/jfdctint.c"
		tmp3 = dataptr[3] + dataptr[4];
# 453 "originaux/jfdctint.c"
		tmp4 = dataptr[3] - dataptr[4];
# 465 "originaux/jfdctint.c"
		tmp10 = tmp0 + tmp3;
# 467 "originaux/jfdctint.c"
		tmp13 = tmp0 - tmp3;
# 469 "originaux/jfdctint.c"
		tmp11 = tmp1 + tmp2;
# 471 "originaux/jfdctint.c"
		tmp12 = tmp1 - tmp2;
# 475 "originaux/jfdctint.c"
		dataptr[0] = (int)((tmp10 + tmp11 << 2));
# 477 "originaux/jfdctint.c"
		dataptr[4] = (int)((tmp10 - tmp11 << 2));
# 481 "originaux/jfdctint.c"
		z1 = ((tmp12 + tmp13)) * (int)4433;
# 483 "originaux/jfdctint.c"
		dataptr[2] = (int)((z1 + tmp13 * (int)6270 + (((int)1 << 13 - 2
			- 1)) >> 13 - 2));
# 487 "originaux/jfdctint.c"
		dataptr[6] = (int)((z1 + tmp12 * -(int)15137 + (((int)1 << 13 -
			2 - 1)) >> 13 - 2));
# 503 "originaux/jfdctint.c"
		z1 = tmp4 + tmp7;
# 505 "originaux/jfdctint.c"
		z2 = tmp5 + tmp6;
# 507 "originaux/jfdctint.c"
		z3 = tmp4 + tmp6;
# 509 "originaux/jfdctint.c"
		z4 = tmp5 + tmp7;
# 511 "originaux/jfdctint.c"
		z5 = ((z3 + z4)) * (int)9633;
# 515 "originaux/jfdctint.c"
		tmp4 = tmp4 * (int)2446;
# 517 "originaux/jfdctint.c"
		tmp5 = tmp5 * (int)16819;
# 519 "originaux/jfdctint.c"
		tmp6 = tmp6 * (int)25172;
# 521 "originaux/jfdctint.c"
		tmp7 = tmp7 * (int)12299;
# 523 "originaux/jfdctint.c"
		z1 = z1 * -(int)7373;
# 525 "originaux/jfdctint.c"
		z2 = z2 * -(int)20995;
# 527 "originaux/jfdctint.c"
		z3 = z3 * -(int)16069;
# 529 "originaux/jfdctint.c"
		z4 = z4 * -(int)3196;
# 533 "originaux/jfdctint.c"
		z3 += z5;
# 535 "originaux/jfdctint.c"
		z4 += z5;
# 539 "originaux/jfdctint.c"
		dataptr[7] = (int)((tmp4 + z1 + z3 + (((int)1 << 13 - 2 - 1)) >>
			13 - 2));
# 541 "originaux/jfdctint.c"
		dataptr[5] = (int)((tmp5 + z2 + z4 + (((int)1 << 13 - 2 - 1)) >>
			13 - 2));
# 543 "originaux/jfdctint.c"
		dataptr[3] = (int)((tmp6 + z2 + z3 + (((int)1 << 13 - 2 - 1)) >>
			13 - 2));
# 545 "originaux/jfdctint.c"
		dataptr[1] = (int)((tmp7 + z1 + z4 + (((int)1 << 13 - 2 - 1)) >>
			13 - 2));
# 549 "originaux/jfdctint.c"
		dataptr += 8;
	}
# 565 "originaux/jfdctint.c"
	dataptr = data;
# 567 "originaux/jfdctint.c"
	for(ctr = 8 - 1; ctr >= 0; ctr--)
# 567 "originaux/jfdctint.c"
	{
# 569 "originaux/jfdctint.c"
		tmp0 = dataptr[8 * 0] + dataptr[8 * 7];
# 571 "originaux/jfdctint.c"
		tmp7 = dataptr[8 * 0] - dataptr[8 * 7];
# 573 "originaux/jfdctint.c"
		tmp1 = dataptr[8 * 1] + dataptr[8 * 6];
# 575 "originaux/jfdctint.c"
		tmp6 = dataptr[8 * 1] - dataptr[8 * 6];
# 577 "originaux/jfdctint.c"
		tmp2 = dataptr[8 * 2] + dataptr[8 * 5];
# 579 "originaux/jfdctint.c"
		tmp5 = dataptr[8 * 2] - dataptr[8 * 5];
# 581 "originaux/jfdctint.c"
		tmp3 = dataptr[8 * 3] + dataptr[8 * 4];
# 583 "originaux/jfdctint.c"
		tmp4 = dataptr[8 * 3] - dataptr[8 * 4];
# 595 "originaux/jfdctint.c"
		tmp10 = tmp0 + tmp3;
# 597 "originaux/jfdctint.c"
		tmp13 = tmp0 - tmp3;
# 599 "originaux/jfdctint.c"
		tmp11 = tmp1 + tmp2;
# 601 "originaux/jfdctint.c"
		tmp12 = tmp1 - tmp2;
# 605 "originaux/jfdctint.c"
		dataptr[8 * 0] = (int)((tmp10 + tmp11 + (((int)1 << 2 - 1)) >>
			2));
# 607 "originaux/jfdctint.c"
		dataptr[8 * 4] = (int)((tmp10 - tmp11 + (((int)1 << 2 - 1)) >>
			2));
# 611 "originaux/jfdctint.c"
		z1 = ((tmp12 + tmp13)) * (int)4433;
# 613 "originaux/jfdctint.c"
		dataptr[8 * 2] = (int)((z1 + tmp13 * (int)6270 + (((int)1 << 13
			+ 2 - 1)) >> 13 + 2));
# 617 "originaux/jfdctint.c"
		dataptr[8 * 6] = (int)((z1 + tmp12 * -(int)15137 + (((int)1 <<
			13 + 2 - 1)) >> 13 + 2));
# 633 "originaux/jfdctint.c"
		z1 = tmp4 + tmp7;
# 635 "originaux/jfdctint.c"
		z2 = tmp5 + tmp6;
# 637 "originaux/jfdctint.c"
		z3 = tmp4 + tmp6;
# 639 "originaux/jfdctint.c"
		z4 = tmp5 + tmp7;
# 641 "originaux/jfdctint.c"
		z5 = ((z3 + z4)) * (int)9633;
# 645 "originaux/jfdctint.c"
		tmp4 = tmp4 * (int)2446;
# 647 "originaux/jfdctint.c"
		tmp5 = tmp5 * (int)16819;
# 649 "originaux/jfdctint.c"
		tmp6 = tmp6 * (int)25172;
# 651 "originaux/jfdctint.c"
		tmp7 = tmp7 * (int)12299;
# 653 "originaux/jfdctint.c"
		z1 = z1 * -(int)7373;
# 655 "originaux/jfdctint.c"
		z2 = z2 * -(int)20995;
# 657 "originaux/jfdctint.c"
		z3 = z3 * -(int)16069;
# 659 "originaux/jfdctint.c"
		z4 = z4 * -(int)3196;
# 663 "originaux/jfdctint.c"
		z3 += z5;
# 665 "originaux/jfdctint.c"
		z4 += z5;
# 669 "originaux/jfdctint.c"
		dataptr[8 * 7] = (int)((tmp4 + z1 + z3 + (((int)1 << 13 + 2 -
			1)) >> 13 + 2));
# 673 "originaux/jfdctint.c"
		dataptr[8 * 5] = (int)((tmp5 + z2 + z4 + (((int)1 << 13 + 2 -
			1)) >> 13 + 2));
# 677 "originaux/jfdctint.c"
		dataptr[8 * 3] = (int)((tmp6 + z2 + z3 + (((int)1 << 13 + 2 -
			1)) >> 13 + 2));
# 681 "originaux/jfdctint.c"
		dataptr[8 * 1] = (int)((tmp7 + z1 + z4 + (((int)1 << 13 + 2 -
			1)) >> 13 + 2));
# 687 "originaux/jfdctint.c"
		dataptr++;
	}
}

void main(void )
{
	int i, seed;
# 733 "originaux/jfdctint.c"
	seed = 1;
# 735 "originaux/jfdctint.c"
	for(i = 0; i < 64; i++)
# 735 "originaux/jfdctint.c"
	{
# 737 "originaux/jfdctint.c"
		seed = ((seed * 133 + 81)) % 65535;
# 739 "originaux/jfdctint.c"
		data[i] = seed;
	}
# 745 "originaux/jfdctint.c"
	jpeg_fdct_islow();
}

