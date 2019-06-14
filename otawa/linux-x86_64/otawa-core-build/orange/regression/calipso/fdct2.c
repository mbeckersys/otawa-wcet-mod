short int block[64] = {99, 104, 109, 113, 115, 115, 55, 55, 104, 111, 113, 116,
	119, 56, 56, 56, 110, 115, 120, 119, 118, 56, 56, 56, 119, 121, 122,
	120, 120, 59, 59, 59, 119, 120, 121, 122, 122, 55, 55, 55, 121, 121,
	121, 121, 60, 57, 57, 57, 122, 122, 61, 63, 62, 57, 57, 57, 62, 62, 61,
	61, 63, 58, 58, 58};

void fdct(short int *blk, int lx)
{
	int tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
	int tmp10, tmp11, tmp12, tmp13;
	int z1, z2, z3, z4, z5;
	int i;
	short int *block;
	int constant;
# 43 "originaux/fdct2.c"
	block = blk;
# 45 "originaux/fdct2.c"
	for(i = 0; i < 8; i++)
# 46 "originaux/fdct2.c"
	{
# 47 "originaux/fdct2.c"
		tmp0 = block[0] + block[7];
# 48 "originaux/fdct2.c"
		tmp7 = block[0] - block[7];
# 49 "originaux/fdct2.c"
		tmp1 = block[1] + block[6];
# 50 "originaux/fdct2.c"
		tmp6 = block[1] - block[6];
# 51 "originaux/fdct2.c"
		tmp2 = block[2] + block[5];
# 52 "originaux/fdct2.c"
		tmp5 = block[2] - block[5];
# 53 "originaux/fdct2.c"
		tmp3 = block[3] + block[4];
# 54 "originaux/fdct2.c"
		tmp4 = block[3] - block[4];
# 58 "originaux/fdct2.c"
		tmp10 = tmp0 + tmp3;
# 59 "originaux/fdct2.c"
		tmp13 = tmp0 - tmp3;
# 60 "originaux/fdct2.c"
		tmp11 = tmp1 + tmp2;
# 61 "originaux/fdct2.c"
		tmp12 = tmp1 - tmp2;
# 63 "originaux/fdct2.c"
		block[0] = tmp10 + tmp11 << 2;
# 64 "originaux/fdct2.c"
		block[4] = tmp10 - tmp11 << 2;
# 66 "originaux/fdct2.c"
		constant = 4433;
# 67 "originaux/fdct2.c"
		z1 = ((tmp12 + tmp13)) * constant;
# 68 "originaux/fdct2.c"
		constant = 6270;
# 69 "originaux/fdct2.c"
		block[2] = z1 + tmp13 * constant >> 13 - 2;
# 70 "originaux/fdct2.c"
		constant = -15137;
# 71 "originaux/fdct2.c"
		block[6] = z1 + tmp12 * constant >> 13 - 2;
# 75 "originaux/fdct2.c"
		z1 = tmp4 + tmp7;
# 76 "originaux/fdct2.c"
		z2 = tmp5 + tmp6;
# 77 "originaux/fdct2.c"
		z3 = tmp4 + tmp6;
# 78 "originaux/fdct2.c"
		z4 = tmp5 + tmp7;
# 79 "originaux/fdct2.c"
		constant = 9633;
# 80 "originaux/fdct2.c"
		z5 = ((z3 + z4)) * constant;
# 82 "originaux/fdct2.c"
		constant = 2446;
# 83 "originaux/fdct2.c"
		tmp4 = tmp4 * constant;
# 84 "originaux/fdct2.c"
		constant = 16819;
# 85 "originaux/fdct2.c"
		tmp5 = tmp5 * constant;
# 86 "originaux/fdct2.c"
		constant = 25172;
# 87 "originaux/fdct2.c"
		tmp6 = tmp6 * constant;
# 88 "originaux/fdct2.c"
		constant = 12299;
# 89 "originaux/fdct2.c"
		tmp7 = tmp7 * constant;
# 90 "originaux/fdct2.c"
		constant = -7373;
# 91 "originaux/fdct2.c"
		z1 = z1 * constant;
# 92 "originaux/fdct2.c"
		constant = -20995;
# 93 "originaux/fdct2.c"
		z2 = z2 * constant;
# 94 "originaux/fdct2.c"
		constant = -16069;
# 95 "originaux/fdct2.c"
		z3 = z3 * constant;
# 96 "originaux/fdct2.c"
		constant = -3196;
# 97 "originaux/fdct2.c"
		z4 = z4 * constant;
# 99 "originaux/fdct2.c"
		z3 += z5;
# 100 "originaux/fdct2.c"
		z4 += z5;
# 102 "originaux/fdct2.c"
		block[7] = tmp4 + z1 + z3 >> 13 - 2;
# 103 "originaux/fdct2.c"
		block[5] = tmp5 + z2 + z4 >> 13 - 2;
# 104 "originaux/fdct2.c"
		block[3] = tmp6 + z2 + z3 >> 13 - 2;
# 105 "originaux/fdct2.c"
		block[1] = tmp7 + z1 + z4 >> 13 - 2;
# 108 "originaux/fdct2.c"
		block += lx;
	}
# 114 "originaux/fdct2.c"
	block = blk;
# 116 "originaux/fdct2.c"
	for(i = 0; i < 8; i++)
# 117 "originaux/fdct2.c"
	{
# 118 "originaux/fdct2.c"
		tmp0 = block[0] + block[7 * lx];
# 119 "originaux/fdct2.c"
		tmp7 = block[0] - block[7 * lx];
# 120 "originaux/fdct2.c"
		tmp1 = block[lx] + block[6 * lx];
# 121 "originaux/fdct2.c"
		tmp6 = block[lx] - block[6 * lx];
# 122 "originaux/fdct2.c"
		tmp2 = block[2 * lx] + block[5 * lx];
# 123 "originaux/fdct2.c"
		tmp5 = block[2 * lx] - block[5 * lx];
# 124 "originaux/fdct2.c"
		tmp3 = block[3 * lx] + block[4 * lx];
# 125 "originaux/fdct2.c"
		tmp4 = block[3 * lx] - block[4 * lx];
# 129 "originaux/fdct2.c"
		tmp10 = tmp0 + tmp3;
# 130 "originaux/fdct2.c"
		tmp13 = tmp0 - tmp3;
# 131 "originaux/fdct2.c"
		tmp11 = tmp1 + tmp2;
# 132 "originaux/fdct2.c"
		tmp12 = tmp1 - tmp2;
# 134 "originaux/fdct2.c"
		block[0] = tmp10 + tmp11 >> 2 + 3;
# 135 "originaux/fdct2.c"
		block[4 * lx] = tmp10 - tmp11 >> 2 + 3;
# 137 "originaux/fdct2.c"
		constant = 4433;
# 138 "originaux/fdct2.c"
		z1 = ((tmp12 + tmp13)) * constant;
# 139 "originaux/fdct2.c"
		constant = 6270;
# 140 "originaux/fdct2.c"
		block[2 * lx] = z1 + tmp13 * constant >> 13 + 2 + 3;
# 141 "originaux/fdct2.c"
		constant = -15137;
# 142 "originaux/fdct2.c"
		block[6 * lx] = z1 + tmp12 * constant >> 13 + 2 + 3;
# 146 "originaux/fdct2.c"
		z1 = tmp4 + tmp7;
# 147 "originaux/fdct2.c"
		z2 = tmp5 + tmp6;
# 148 "originaux/fdct2.c"
		z3 = tmp4 + tmp6;
# 149 "originaux/fdct2.c"
		z4 = tmp5 + tmp7;
# 150 "originaux/fdct2.c"
		constant = 9633;
# 151 "originaux/fdct2.c"
		z5 = ((z3 + z4)) * constant;
# 153 "originaux/fdct2.c"
		constant = 2446;
# 154 "originaux/fdct2.c"
		tmp4 = tmp4 * constant;
# 155 "originaux/fdct2.c"
		constant = 16819;
# 156 "originaux/fdct2.c"
		tmp5 = tmp5 * constant;
# 157 "originaux/fdct2.c"
		constant = 25172;
# 158 "originaux/fdct2.c"
		tmp6 = tmp6 * constant;
# 159 "originaux/fdct2.c"
		constant = 12299;
# 160 "originaux/fdct2.c"
		tmp7 = tmp7 * constant;
# 161 "originaux/fdct2.c"
		constant = -7373;
# 162 "originaux/fdct2.c"
		z1 = z1 * constant;
# 163 "originaux/fdct2.c"
		constant = -20995;
# 164 "originaux/fdct2.c"
		z2 = z2 * constant;
# 165 "originaux/fdct2.c"
		constant = -16069;
# 166 "originaux/fdct2.c"
		z3 = z3 * constant;
# 167 "originaux/fdct2.c"
		constant = -3196;
# 168 "originaux/fdct2.c"
		z4 = z4 * constant;
# 170 "originaux/fdct2.c"
		z3 += z5;
# 171 "originaux/fdct2.c"
		z4 += z5;
# 173 "originaux/fdct2.c"
		block[7 * lx] = tmp4 + z1 + z3 >> 13 + 2 + 3;
# 174 "originaux/fdct2.c"
		block[5 * lx] = tmp5 + z2 + z4 >> 13 + 2 + 3;
# 175 "originaux/fdct2.c"
		block[3 * lx] = tmp6 + z2 + z3 >> 13 + 2 + 3;
# 176 "originaux/fdct2.c"
		block[lx] = tmp7 + z1 + z4 >> 13 + 2 + 3;
# 179 "originaux/fdct2.c"
		block++;
	}
}

int main()
{
	int i2;
# 187 "originaux/fdct2.c"
	fdct(block, 8);
# 190 "originaux/fdct2.c"
	for(i2 = 0; i2 < 64; i2 += 2)
# 190 "originaux/fdct2.c"
		printf("block[%2d] -> %8d . block[%2d] -> %8d\n", i2, block[i2],
			i2 + 1, block[i2 + 1]);
# 193 "originaux/fdct2.c"
	return block[0];
}

