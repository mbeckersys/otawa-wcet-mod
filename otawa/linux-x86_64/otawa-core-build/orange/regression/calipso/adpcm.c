
typedef struct  {
	int real, imag;
} COMPLEX;

void fft(COMPLEX *, int );
int fir_filter(int input, int *coef, int n, int *history);
int iir_filter(int input, int *coef, int n, int *history);
int gaussian(void );
int my_abs(int n);
void setup_codec(int ), key_down(), int_enable(), int_disable();
int flags(int );
int getinput(void );
void sendout(int ), flush();
int encode(int , int );
void decode(int );
int filtez(int *bpl, int *dlt);
void upzero(int dlt, int *dlti, int *bli);
int filtep(int rlt1, int al1, int rlt2, int al2);
int quantl(int el, int detl);
int logscl(int il, int nbl);
int scalel(int nbl, int shift_constant);
int uppol2(int al1, int al2, int plt, int plt1, int plt2);
int uppol1(int al1, int apl2, int plt, int plt1);
int logsch(int ih, int nbh);
void reset();
int my_fabs(int n);
int my_cos(int n);
int my_sin(int n);
int tqmf[24];
int h[24] = {12, -44, -44, 212, 48, -624, 128, 1448, -840, -3220, 3804, 15504,
	15504, 3804, -3220, -840, 1448, 128, -624, 48, 212, -44, -44, 12};
int xl, xh;
int accumc[11], accumd[11];
int xout1, xout2;
int xs, xd;
int il, szl, spl, sl, el;
int qq4_code4_table[16] = {0, -20456, -12896, -8968, -6288, -4240, -2584, -1200,
	20456, 12896, 8968, 6288, 4240, 2584, 1200, 0};
int qq5_code5_table[32] = {-280, -280, -23352, -17560, -14120, -11664, -9752,
	-8184, -6864, -5712, -4696, -3784, -2960, -2208, -1520, -880, 23352,
	17560, 14120, 11664, 9752, 8184, 6864, 5712, 4696, 3784, 2960, 2208,
	1520, 880, 280, -280};
int qq6_code6_table[64] = {-136, -136, -136, -136, -24808, -21904, -19008,
	-16704, -14984, -13512, -12280, -11192, -10232, -9360, -8576, -7856,
	-7192, -6576, -6000, -5456, -4944, -4464, -4008, -3576, -3168, -2776,
	-2400, -2032, -1688, -1360, -1040, -728, 24808, 21904, 19008, 16704,
	14984, 13512, 12280, 11192, 10232, 9360, 8576, 7856, 7192, 6576, 6000,
	5456, 4944, 4464, 4008, 3576, 3168, 2776, 2400, 2032, 1688, 1360, 1040,
	728, 432, 136, -432, -136};
int delay_bpl[6];
int delay_dltx[6];
int wl_code_table[16] = {-60, 3042, 1198, 538, 334, 172, 58, -30, 3042, 1198,
	538, 334, 172, 58, -30, -60};
int wl_table[8] = {-60, -30, 58, 172, 334, 538, 1198, 3042};
int ilb_table[32] = {2048, 2093, 2139, 2186, 2233, 2282, 2332, 2383, 2435, 2489,
	2543, 2599, 2656, 2714, 2774, 2834, 2896, 2960, 3025, 3091, 3158, 3228,
	3298, 3371, 3444, 3520, 3597, 3676, 3756, 3838, 3922, 4008};
int nbl;
int al1, al2;
int plt, plt1, plt2;
int rs;
int dlt;
int rlt, rlt1, rlt2;
int decis_levl[30] = {280, 576, 880, 1200, 1520, 1864, 2208, 2584, 2960, 3376,
	3784, 4240, 4696, 5200, 5712, 6288, 6864, 7520, 8184, 8968, 9752, 10712,
	11664, 12896, 14120, 15840, 17560, 20456, 23352, 32767};
int detl;
int quant26bt_pos[31] = {61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48,
	47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 32};
int quant26bt_neg[31] = {63, 62, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20,
	19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 4};
int deth;
int sh;
int eh;
int qq2_code2_table[4] = {-7408, -1616, 7408, 1616};
int wh_code_table[4] = {798, -214, 798, -214};
int dh, ih;
int nbh, szh;
int sph, ph, yh, rh;
int delay_dhx[6];
int delay_bph[6];
int ah1, ah2;
int ph1, ph2;
int rh1, rh2;
int ilr, yl, rl;
int dec_deth, dec_detl, dec_dlt;
int dec_del_bpl[6];
int dec_del_dltx[6];
int dec_plt, dec_plt1, dec_plt2;
int dec_szl, dec_spl, dec_sl;
int dec_rlt1, dec_rlt2, dec_rlt;
int dec_al1, dec_al2;
int dl;
int dec_nbl, dec_yh, dec_dh, dec_nbh;
int dec_del_bph[6];
int dec_del_dhx[6];
int dec_szh;
int dec_rh1, dec_rh2;
int dec_ah1, dec_ah2;
int dec_ph, dec_sph;
int dec_sh, dec_rh;
int dec_ph1, dec_ph2;

int my_abs(int n)
{
	int m;
# 269 "originaux/adpcm.c"
	if(n >= 0)
# 269 "originaux/adpcm.c"
		m = n;
	else
# 270 "originaux/adpcm.c"
# 270 "originaux/adpcm.c"
		m = -n;
# 271 "originaux/adpcm.c"
	return m;
}

int my_fabs(int n)
{
	int f;
# 279 "originaux/adpcm.c"
	if(n >= 0)
# 279 "originaux/adpcm.c"
		f = n;
	else
# 280 "originaux/adpcm.c"
# 280 "originaux/adpcm.c"
		f = -n;
# 281 "originaux/adpcm.c"
	return f;
}

int my_sin(int rad2)
{
	int diff;
	int app = 0;
	int inc = 1;
# 292 "originaux/adpcm.c"
	while(rad2 > 2 * 3141)
# 293 "originaux/adpcm.c"
		rad2 -= 2 * 3141;
# 295 "originaux/adpcm.c"
	while(rad2 < -(2 * 3141))
# 296 "originaux/adpcm.c"
		rad2 += 2 * 3141;
# 297 "originaux/adpcm.c"
	diff = rad2;
# 298 "originaux/adpcm.c"
	app = diff;
# 300 "originaux/adpcm.c"
	diff = diff * -((rad2 * rad2)) / ((2 * inc * ((2 * inc + 1))));
# 301 "originaux/adpcm.c"
	app = app + diff;
# 302 "originaux/adpcm.c"
	inc++;
# 305 "originaux/adpcm.c"
	while(my_fabs(diff) >= 1)
# 305 "originaux/adpcm.c"
	{	    diff = (diff * (-(rad2*rad2))) /
	((2 * inc) * (2 * inc + 1));
    app = app + diff;
    inc++;}
# 313 "originaux/adpcm.c"
	return app;
}

int my_cos(int rad)
{
# 319 "originaux/adpcm.c"
	return my_sin(3141 / 2 - rad);
}

int encode(int xin1, int xin2)
{
	int i;
	int *h_ptr, *tqmf_ptr, *tqmf_ptr1;
	long int xa, xb;
	int decis;
# 332 "originaux/adpcm.c"
	h_ptr = h;
# 333 "originaux/adpcm.c"
	tqmf_ptr = tqmf;
# 334 "originaux/adpcm.c"
	xa = (long int)((*tqmf_ptr++)) * *h_ptr++;
# 335 "originaux/adpcm.c"
	xb = (long int)((*tqmf_ptr++)) * *h_ptr++;
# 338 "originaux/adpcm.c"
	for(i = 0; i < 10; i++)
# 338 "originaux/adpcm.c"
	{
# 339 "originaux/adpcm.c"
		xa += (long int)((*tqmf_ptr++)) * *h_ptr++;
# 340 "originaux/adpcm.c"
		xb += (long int)((*tqmf_ptr++)) * *h_ptr++;
	}
# 343 "originaux/adpcm.c"
	xa += (long int)((*tqmf_ptr++)) * *h_ptr++;
# 344 "originaux/adpcm.c"
	xb += (long int)((*tqmf_ptr)) * *h_ptr++;
# 347 "originaux/adpcm.c"
	tqmf_ptr1 = tqmf_ptr - 2;
# 349 "originaux/adpcm.c"
	for(i = 0; i < 22; i++)
# 349 "originaux/adpcm.c"
		*tqmf_ptr-- = *tqmf_ptr1--;
# 350 "originaux/adpcm.c"
	*tqmf_ptr-- = xin1;
# 351 "originaux/adpcm.c"
	*tqmf_ptr = xin2;
# 354 "originaux/adpcm.c"
	xl = xa + xb >> 15;
# 355 "originaux/adpcm.c"
	xh = xa - xb >> 15;
# 362 "originaux/adpcm.c"
	szl = filtez(delay_bpl, delay_dltx);
# 365 "originaux/adpcm.c"
	spl = filtep(rlt1, al1, rlt2, al2);
# 368 "originaux/adpcm.c"
	sl = szl + spl;
# 369 "originaux/adpcm.c"
	el = xl - sl;
# 372 "originaux/adpcm.c"
	il = quantl(el, detl);
# 376 "originaux/adpcm.c"
	dlt = (long int)detl * qq4_code4_table[il >> 2] >> 15;
# 379 "originaux/adpcm.c"
	nbl = logscl(il, nbl);
# 383 "originaux/adpcm.c"
	detl = scalel(nbl, 8);
# 386 "originaux/adpcm.c"
	plt = dlt + szl;
# 392 "originaux/adpcm.c"
	upzero(dlt, delay_dltx, delay_bpl);
# 396 "originaux/adpcm.c"
	al2 = uppol2(al1, al2, plt, plt1, plt2);
# 400 "originaux/adpcm.c"
	al1 = uppol1(al1, al2, plt, plt1);
# 403 "originaux/adpcm.c"
	rlt = sl + dlt;
# 406 "originaux/adpcm.c"
	rlt2 = rlt1;
# 407 "originaux/adpcm.c"
	rlt1 = rlt;
# 408 "originaux/adpcm.c"
	plt2 = plt1;
# 409 "originaux/adpcm.c"
	plt1 = plt;
# 413 "originaux/adpcm.c"
	szh = filtez(delay_bph, delay_dhx);
# 415 "originaux/adpcm.c"
	sph = filtep(rh1, ah1, rh2, ah2);
# 418 "originaux/adpcm.c"
	sh = sph + szh;
# 420 "originaux/adpcm.c"
	eh = xh - sh;
# 424 "originaux/adpcm.c"
	if(eh >= 0)
# 424 "originaux/adpcm.c"
	{
# 425 "originaux/adpcm.c"
		ih = 3;
	}
	else
# 427 "originaux/adpcm.c"
# 427 "originaux/adpcm.c"
	{
# 428 "originaux/adpcm.c"
		ih = 1;
	}
# 430 "originaux/adpcm.c"
	decis = 564 * (long int)deth >> 12;
# 431 "originaux/adpcm.c"
	if(my_abs(eh) > decis)
# 431 "originaux/adpcm.c"
		ih--;
# 434 "originaux/adpcm.c"
	dh = (long int)deth * qq2_code2_table[ih] >> 15;
# 437 "originaux/adpcm.c"
	nbh = logsch(ih, nbh);
# 440 "originaux/adpcm.c"
	deth = scalel(nbh, 10);
# 443 "originaux/adpcm.c"
	ph = dh + szh;
# 448 "originaux/adpcm.c"
	upzero(dh, delay_dhx, delay_bph);
# 452 "originaux/adpcm.c"
	ah2 = uppol2(ah1, ah2, ph, ph1, ph2);
# 455 "originaux/adpcm.c"
	ah1 = uppol1(ah1, ah2, ph, ph1);
# 458 "originaux/adpcm.c"
	yh = sh + dh;
# 461 "originaux/adpcm.c"
	rh2 = rh1;
# 462 "originaux/adpcm.c"
	rh1 = yh;
# 463 "originaux/adpcm.c"
	ph2 = ph1;
# 464 "originaux/adpcm.c"
	ph1 = ph;
# 467 "originaux/adpcm.c"
	return il | ih << 6;
}

void decode(int input)
{
	int i;
	long int xa1, xa2;
	int *h_ptr, *ac_ptr, *ac_ptr1, *ad_ptr, *ad_ptr1;
# 479 "originaux/adpcm.c"
	ilr = input & 0x3f;
# 480 "originaux/adpcm.c"
	ih = input >> 6;
# 485 "originaux/adpcm.c"
	dec_szl = filtez(dec_del_bpl, dec_del_dltx);
# 488 "originaux/adpcm.c"
	dec_spl = filtep(dec_rlt1, dec_al1, dec_rlt2, dec_al2);
# 490 "originaux/adpcm.c"
	dec_sl = dec_spl + dec_szl;
# 493 "originaux/adpcm.c"
	dec_dlt = (long int)dec_detl * qq4_code4_table[ilr >> 2] >> 15;
# 496 "originaux/adpcm.c"
	dl = (long int)dec_detl * qq6_code6_table[il] >> 15;
# 498 "originaux/adpcm.c"
	rl = dl + dec_sl;
# 501 "originaux/adpcm.c"
	dec_nbl = logscl(ilr, dec_nbl);
# 504 "originaux/adpcm.c"
	dec_detl = scalel(dec_nbl, 8);
# 508 "originaux/adpcm.c"
	dec_plt = dec_dlt + dec_szl;
# 511 "originaux/adpcm.c"
	upzero(dec_dlt, dec_del_dltx, dec_del_bpl);
# 514 "originaux/adpcm.c"
	dec_al2 = uppol2(dec_al1, dec_al2, dec_plt, dec_plt1, dec_plt2);
# 517 "originaux/adpcm.c"
	dec_al1 = uppol1(dec_al1, dec_al2, dec_plt, dec_plt1);
# 520 "originaux/adpcm.c"
	dec_rlt = dec_sl + dec_dlt;
# 523 "originaux/adpcm.c"
	dec_rlt2 = dec_rlt1;
# 524 "originaux/adpcm.c"
	dec_rlt1 = dec_rlt;
# 525 "originaux/adpcm.c"
	dec_plt2 = dec_plt1;
# 526 "originaux/adpcm.c"
	dec_plt1 = dec_plt;
# 531 "originaux/adpcm.c"
	dec_szh = filtez(dec_del_bph, dec_del_dhx);
# 534 "originaux/adpcm.c"
	dec_sph = filtep(dec_rh1, dec_ah1, dec_rh2, dec_ah2);
# 537 "originaux/adpcm.c"
	dec_sh = dec_sph + dec_szh;
# 540 "originaux/adpcm.c"
	dec_dh = (long int)dec_deth * qq2_code2_table[ih] >> 15;
# 543 "originaux/adpcm.c"
	dec_nbh = logsch(ih, dec_nbh);
# 546 "originaux/adpcm.c"
	dec_deth = scalel(dec_nbh, 10);
# 549 "originaux/adpcm.c"
	dec_ph = dec_dh + dec_szh;
# 552 "originaux/adpcm.c"
	upzero(dec_dh, dec_del_dhx, dec_del_bph);
# 555 "originaux/adpcm.c"
	dec_ah2 = uppol2(dec_ah1, dec_ah2, dec_ph, dec_ph1, dec_ph2);
# 558 "originaux/adpcm.c"
	dec_ah1 = uppol1(dec_ah1, dec_ah2, dec_ph, dec_ph1);
# 561 "originaux/adpcm.c"
	rh = dec_sh + dec_dh;
# 564 "originaux/adpcm.c"
	dec_rh2 = dec_rh1;
# 565 "originaux/adpcm.c"
	dec_rh1 = rh;
# 566 "originaux/adpcm.c"
	dec_ph2 = dec_ph1;
# 567 "originaux/adpcm.c"
	dec_ph1 = dec_ph;
# 572 "originaux/adpcm.c"
	xd = rl - rh;
# 573 "originaux/adpcm.c"
	xs = rl + rh;
# 576 "originaux/adpcm.c"
	h_ptr = h;
# 577 "originaux/adpcm.c"
	ac_ptr = accumc;
# 578 "originaux/adpcm.c"
	ad_ptr = accumd;
# 579 "originaux/adpcm.c"
	xa1 = (long int)xd * *h_ptr++;
# 580 "originaux/adpcm.c"
	xa2 = (long int)xs * *h_ptr++;
# 582 "originaux/adpcm.c"
	for(i = 0; i < 10; i++)
# 582 "originaux/adpcm.c"
	{
# 583 "originaux/adpcm.c"
		xa1 += (long int)((*ac_ptr++)) * *h_ptr++;
# 584 "originaux/adpcm.c"
		xa2 += (long int)((*ad_ptr++)) * *h_ptr++;
	}
# 587 "originaux/adpcm.c"
	xa1 += (long int)((*ac_ptr)) * *h_ptr++;
# 588 "originaux/adpcm.c"
	xa2 += (long int)((*ad_ptr)) * *h_ptr++;
# 591 "originaux/adpcm.c"
	xout1 = xa1 >> 14;
# 592 "originaux/adpcm.c"
	xout2 = xa2 >> 14;
# 595 "originaux/adpcm.c"
	ac_ptr1 = ac_ptr - 1;
# 596 "originaux/adpcm.c"
	ad_ptr1 = ad_ptr - 1;
# 597 "originaux/adpcm.c"
	for(i = 0; i < 10; i++)
# 597 "originaux/adpcm.c"
	{
# 598 "originaux/adpcm.c"
		*ac_ptr-- = *ac_ptr1--;
# 599 "originaux/adpcm.c"
		*ad_ptr-- = *ad_ptr1--;
	}
# 601 "originaux/adpcm.c"
	*ac_ptr = xd;
# 602 "originaux/adpcm.c"
	*ad_ptr = xs;
# 604 "originaux/adpcm.c"
	;
}

void reset()
{
	int i;
# 613 "originaux/adpcm.c"
	detl = ((dec_detl = 32));
# 614 "originaux/adpcm.c"
	deth = ((dec_deth = 8));
# 615 "originaux/adpcm.c"
	nbl = ((al1 = ((al2 = ((plt1 = ((plt2 = ((rlt1 = ((rlt2 = 0))))))))))));
# 616 "originaux/adpcm.c"
	nbh = ((ah1 = ((ah2 = ((ph1 = ((ph2 = ((rh1 = ((rh2 = 0))))))))))));
# 617 "originaux/adpcm.c"
	dec_nbl = ((dec_al1 = ((dec_al2 = ((dec_plt1 = ((dec_plt2 = ((dec_rlt1 =
		((dec_rlt2 = 0))))))))))));
# 618 "originaux/adpcm.c"
	dec_nbh = ((dec_ah1 = ((dec_ah2 = ((dec_ph1 = ((dec_ph2 = ((dec_rh1 =
		((dec_rh2 = 0))))))))))));
# 620 "originaux/adpcm.c"
	for(i = 0; i < 6; i++)
# 620 "originaux/adpcm.c"
	{
# 621 "originaux/adpcm.c"
		delay_dltx[i] = 0;
# 622 "originaux/adpcm.c"
		delay_dhx[i] = 0;
# 623 "originaux/adpcm.c"
		dec_del_dltx[i] = 0;
# 624 "originaux/adpcm.c"
		dec_del_dhx[i] = 0;
	}
# 627 "originaux/adpcm.c"
	for(i = 0; i < 6; i++)
# 627 "originaux/adpcm.c"
	{
# 628 "originaux/adpcm.c"
		delay_bpl[i] = 0;
# 629 "originaux/adpcm.c"
		delay_bph[i] = 0;
# 630 "originaux/adpcm.c"
		dec_del_bpl[i] = 0;
# 631 "originaux/adpcm.c"
		dec_del_bph[i] = 0;
	}
# 634 "originaux/adpcm.c"
	for(i = 0; i < 23; i++)
# 634 "originaux/adpcm.c"
		tqmf[i] = 0;
# 636 "originaux/adpcm.c"
	for(i = 0; i < 11; i++)
# 636 "originaux/adpcm.c"
	{
# 637 "originaux/adpcm.c"
		accumc[i] = 0;
# 638 "originaux/adpcm.c"
		accumd[i] = 0;
	}
# 640 "originaux/adpcm.c"
	;
}

int filtez(int *bpl, int *dlt)
{
	int i;
	long int zl;
# 650 "originaux/adpcm.c"
	zl = (long int)((*bpl++)) * *dlt++;
# 652 "originaux/adpcm.c"
	for(i = 1; i < 6; i++)
# 653 "originaux/adpcm.c"
		zl += (long int)((*bpl++)) * *dlt++;
# 655 "originaux/adpcm.c"
	return (int)((zl >> 14));
}

int filtep(int rlt1, int al1, int rlt2, int al2)
{
	long int pl, pl2;
# 664 "originaux/adpcm.c"
	pl = 2 * rlt1;
# 665 "originaux/adpcm.c"
	pl = (long int)al1 * pl;
# 666 "originaux/adpcm.c"
	pl2 = 2 * rlt2;
# 667 "originaux/adpcm.c"
	pl += (long int)al2 * pl2;
# 668 "originaux/adpcm.c"
	return (int)((pl >> 15));
}

int quantl(int el, int detl)
{
	char __tmp_0__ = 0;
	int ril, mil;
	long int wd, decis;
# 678 "originaux/adpcm.c"
	wd = my_abs(el);
# 681 "originaux/adpcm.c"
	for(mil = 0; !__tmp_0__ && mil < 30; __tmp_0__ || mil++)
# 681 "originaux/adpcm.c"
	{
# 682 "originaux/adpcm.c"
		decis = decis_levl[mil] * (long int)detl >> 15;
# 683 "originaux/adpcm.c"
		if(wd <= decis)
# 683 "originaux/adpcm.c"
			__tmp_0__ = 1 != 0;
	}
	__tmp_0__ = 0;
# 686 "originaux/adpcm.c"
	if(el >= 0)
# 686 "originaux/adpcm.c"
		ril = quant26bt_pos[mil];
	else
# 687 "originaux/adpcm.c"
# 687 "originaux/adpcm.c"
		ril = quant26bt_neg[mil];
# 688 "originaux/adpcm.c"
	return ril;
}

int logscl(int il, int nbl)
{
	long int wd;
# 707 "originaux/adpcm.c"
	wd = (long int)nbl * 127L >> 7L;
# 708 "originaux/adpcm.c"
	nbl = (int)wd + wl_code_table[il >> 2];
# 709 "originaux/adpcm.c"
	if(nbl < 0)
# 709 "originaux/adpcm.c"
		nbl = 0;
# 710 "originaux/adpcm.c"
	if(nbl > 18432)
# 710 "originaux/adpcm.c"
		nbl = 18432;
# 711 "originaux/adpcm.c"
	return nbl;
}

int scalel(int nbl, int shift_constant)
{
	int wd1, wd2, wd3;
# 719 "originaux/adpcm.c"
	wd1 = nbl >> 6 & 31;
# 720 "originaux/adpcm.c"
	wd2 = nbl >> 11;
# 721 "originaux/adpcm.c"
	wd3 = ilb_table[wd1] >> shift_constant + 1 - wd2;
# 722 "originaux/adpcm.c"
	return wd3 << 3;
}

void upzero(int dlt, int *dlti, int *bli)
{
	int i, wd2, wd3;
# 732 "originaux/adpcm.c"
	if(dlt == 0)
# 732 "originaux/adpcm.c"
	{
# 733 "originaux/adpcm.c"
		for(i = 0; i < 6; i++)
# 733 "originaux/adpcm.c"
		{
# 734 "originaux/adpcm.c"
			bli[i] = (int)((255 * bli[i] >> 8));
		}
	}
	else
# 737 "originaux/adpcm.c"
# 737 "originaux/adpcm.c"
	{
# 738 "originaux/adpcm.c"
		for(i = 0; i < 6; i++)
# 738 "originaux/adpcm.c"
		{
# 739 "originaux/adpcm.c"
			if((long int)dlt * dlti[i] >= 0)
# 739 "originaux/adpcm.c"
				wd2 = 128;
			else
# 739 "originaux/adpcm.c"
# 739 "originaux/adpcm.c"
				wd2 = -128;
# 740 "originaux/adpcm.c"
			wd3 = (int)((255L * bli[i] >> 8L));
# 741 "originaux/adpcm.c"
			bli[i] = wd2 + wd3;
		}
	}
# 745 "originaux/adpcm.c"
	dlti[5] = dlti[4];
# 746 "originaux/adpcm.c"
	dlti[4] = dlti[3];
# 747 "originaux/adpcm.c"
	dlti[3] = dlti[2];
# 748 "originaux/adpcm.c"
	dlti[1] = dlti[0];
# 749 "originaux/adpcm.c"
	dlti[0] = dlt;
# 750 "originaux/adpcm.c"
	;
}

int uppol2(int al1, int al2, int plt, int plt1, int plt2)
{
	long int wd2, wd4;
	int apl2;
# 760 "originaux/adpcm.c"
	wd2 = 4 * (long int)al1;
# 761 "originaux/adpcm.c"
	if((long int)plt * plt1 >= 0)
# 761 "originaux/adpcm.c"
		wd2 = -wd2;
# 762 "originaux/adpcm.c"
	wd2 = wd2 >> 7;
# 763 "originaux/adpcm.c"
	if((long int)plt * plt2 >= 0)
# 763 "originaux/adpcm.c"
	{
# 764 "originaux/adpcm.c"
		wd4 = wd2 + 128;
	}
	else
# 766 "originaux/adpcm.c"
# 766 "originaux/adpcm.c"
	{
# 767 "originaux/adpcm.c"
		wd4 = wd2 - 128;
	}
# 769 "originaux/adpcm.c"
	apl2 = wd4 + ((127 * (long int)al2 >> 7));
# 772 "originaux/adpcm.c"
	if(apl2 > 12288)
# 772 "originaux/adpcm.c"
		apl2 = 12288;
# 773 "originaux/adpcm.c"
	if(apl2 < -12288)
# 773 "originaux/adpcm.c"
		apl2 = -12288;
# 774 "originaux/adpcm.c"
	return apl2;
}

int uppol1(int al1, int apl2, int plt, int plt1)
{
	long int wd2;
	int wd3, apl1;
# 784 "originaux/adpcm.c"
	wd2 = (long int)al1 * 255 >> 8;
# 785 "originaux/adpcm.c"
	if((long int)plt * plt1 >= 0)
# 785 "originaux/adpcm.c"
	{
# 786 "originaux/adpcm.c"
		apl1 = (int)wd2 + 192;
	}
	else
# 788 "originaux/adpcm.c"
# 788 "originaux/adpcm.c"
	{
# 789 "originaux/adpcm.c"
		apl1 = (int)wd2 - 192;
	}
# 792 "originaux/adpcm.c"
	wd3 = 15360 - apl2;
# 793 "originaux/adpcm.c"
	if(apl1 > wd3)
# 793 "originaux/adpcm.c"
		apl1 = wd3;
# 794 "originaux/adpcm.c"
	if(apl1 < -wd3)
# 794 "originaux/adpcm.c"
		apl1 = -wd3;
# 795 "originaux/adpcm.c"
	return apl1;
}

int logsch(int ih, int nbh)
{
	int wd;
# 814 "originaux/adpcm.c"
	wd = (long int)nbh * 127 >> 7;
# 815 "originaux/adpcm.c"
	nbh = wd + wh_code_table[ih];
# 816 "originaux/adpcm.c"
	if(nbh < 0)
# 816 "originaux/adpcm.c"
		nbh = 0;
# 817 "originaux/adpcm.c"
	if(nbh > 22528)
# 817 "originaux/adpcm.c"
		nbh = 22528;
# 818 "originaux/adpcm.c"
	return nbh;
}

int main()
{
	int i, j, f;
	static int test_data[2 * 2], compressed[2], result[2 * 2];
# 829 "originaux/adpcm.c"
	reset();
# 834 "originaux/adpcm.c"
	j = 10;
# 834 "originaux/adpcm.c"
	f = 2000;
# 840 "originaux/adpcm.c"
	for(i = 0; i < 2; i++)
# 840 "originaux/adpcm.c"
	{
# 841 "originaux/adpcm.c"
		test_data[i] = (int)j * my_cos(f * 3141 * i);
	}
# 854 "originaux/adpcm.c"
	for(i = 0; i < 4; i += 2)
# 855 "originaux/adpcm.c"
		compressed[i / 2] = encode(test_data[i], test_data[i + 1]);
# 857 "originaux/adpcm.c"
	for(i = 0; i < 4; i += 2)
# 857 "originaux/adpcm.c"
	{
# 858 "originaux/adpcm.c"
		decode(compressed[i / 2]);
# 859 "originaux/adpcm.c"
		result[i] = xout1;
# 860 "originaux/adpcm.c"
		result[i + 1] = xout2;
	}
# 874 "originaux/adpcm.c"
	return result[i] + result[i + 1];
}

