static char Bitlist[64];
unsigned long int
	tm_entered_EINSCHALTSTROM_MESSEN_BLOCK_ERKENNUNG_CTRLch_BLOCK_ERKENNUNG_CTRL__N_copy;
unsigned long int
	tm_entered_WIEDERHOLSPERRE_FH_TUERMODUL_CTRLexited_BEREIT_FH_TUERMODUL_CTRL;
unsigned long int tm_entered_WIEDERHOLSPERRE_FH_TUERMODUL_CTRL;
unsigned long int sc_FH_TUERMODUL_CTRL_2375_2;
unsigned long int sc_FH_TUERMODUL_CTRL_2352_1;
unsigned long int sc_FH_TUERMODUL_CTRL_2329_1;
int FH_TUERMODUL_CTRL__N;
int FH_TUERMODUL_CTRL__N_copy;
int FH_TUERMODUL_CTRL__N_old;
unsigned long int sc_FH_TUERMODUL_CTRL_1781_10;
unsigned long int sc_FH_TUERMODUL_CTRL_1739_10;
int FH_TUERMODUL__POSITION;
int FH_TUERMODUL__I_EIN;
int FH_TUERMODUL__I_EIN_old;
int FH_DU__MFH;
int FH_DU__MFH_copy;
int FH_DU__POSITION;
int FH_DU__I_EIN;
int FH_DU__I_EIN_old;
int BLOCK_ERKENNUNG_CTRL__I_EIN_MAX;
int BLOCK_ERKENNUNG_CTRL__I_EIN_MAX_copy;
int BLOCK_ERKENNUNG_CTRL__N;
int BLOCK_ERKENNUNG_CTRL__N_copy;
int BLOCK_ERKENNUNG_CTRL__N_old;
char FH_TUERMODUL_CTRL__INREVERS2;
char FH_TUERMODUL_CTRL__INREVERS2_copy;
char FH_TUERMODUL_CTRL__INREVERS1;
char FH_TUERMODUL_CTRL__INREVERS1_copy;
char FH_TUERMODUL_CTRL__FT;
char FH_TUERMODUL__SFHZ_ZENTRAL;
char FH_TUERMODUL__SFHZ_ZENTRAL_old;
char FH_TUERMODUL__SFHZ_MEC;
char FH_TUERMODUL__SFHZ_MEC_old;
char FH_TUERMODUL__SFHA_ZENTRAL;
char FH_TUERMODUL__SFHA_ZENTRAL_old;
char FH_TUERMODUL__SFHA_MEC;
char FH_TUERMODUL__SFHA_MEC_old;
char FH_TUERMODUL__KL_50;
char FH_TUERMODUL__BLOCK;
char FH_TUERMODUL__BLOCK_copy;
char FH_TUERMODUL__BLOCK_old;
char FH_TUERMODUL__FT;
char FH_TUERMODUL__SFHZ;
char FH_TUERMODUL__SFHZ_copy;
char FH_TUERMODUL__SFHZ_old;
char FH_TUERMODUL__SFHA;
char FH_TUERMODUL__SFHA_copy;
char FH_TUERMODUL__SFHA_old;
char FH_TUERMODUL__MFHZ;
char FH_TUERMODUL__MFHZ_copy;
char FH_TUERMODUL__MFHZ_old;
char FH_TUERMODUL__MFHA;
char FH_TUERMODUL__MFHA_copy;
char FH_TUERMODUL__MFHA_old;
char FH_TUERMODUL__EKS_LEISTE_AKTIV;
char FH_TUERMODUL__EKS_LEISTE_AKTIV_old;
char FH_TUERMODUL__COM_OPEN;
char FH_TUERMODUL__COM_CLOSE;
char FH_DU__KL_50;
char FH_DU__S_FH_FTZU;
char FH_DU__S_FH_FTAUF;
char FH_DU__FT;
char FH_DU__EKS_LEISTE_AKTIV;
char FH_DU__EKS_LEISTE_AKTIV_old;
char FH_DU__S_FH_TMBFAUFCAN;
char FH_DU__S_FH_TMBFAUFCAN_copy;
char FH_DU__S_FH_TMBFAUFCAN_old;
char FH_DU__S_FH_TMBFZUCAN;
char FH_DU__S_FH_TMBFZUCAN_copy;
char FH_DU__S_FH_TMBFZUCAN_old;
char FH_DU__S_FH_TMBFZUDISC;
char FH_DU__S_FH_TMBFZUDISC_old;
char FH_DU__S_FH_TMBFAUFDISC;
char FH_DU__S_FH_TMBFAUFDISC_old;
char FH_DU__S_FH_ZUDISC;
char FH_DU__S_FH_AUFDISC;
char FH_DU__DOOR_ID;
char FH_DU__BLOCK;
char FH_DU__BLOCK_copy;
char FH_DU__BLOCK_old;
char FH_DU__MFHZ;
char FH_DU__MFHZ_copy;
char FH_DU__MFHZ_old;
char FH_DU__MFHA;
char FH_DU__MFHA_copy;
char FH_DU__MFHA_old;
unsigned long int time;
char stable;
char step;
char NICHT_INITIALISIERT_NICHT_INITIALISIERT_next_state;
char ZENTRAL_KINDERSICHERUNG_CTRL_next_state;
char MEC_KINDERSICHERUNG_CTRL_next_state;
char KINDERSICHERUNG_CTRL_KINDERSICHERUNG_CTRL_next_state;
char B_FH_TUERMODUL_CTRL_next_state;
char A_FH_TUERMODUL_CTRL_next_state;
char WIEDERHOLSPERRE_FH_TUERMODUL_CTRL_next_state;
char INITIALISIERT_FH_TUERMODUL_CTRL_next_state;
char TIPP_SCHLIESSEN_FH_TUERMODUL_CTRL_next_state;
char MANUELL_SCHLIESSEN_FH_TUERMODUL_CTRL_next_state;
char OEFFNEN_FH_TUERMODUL_CTRL_next_state;
char SCHLIESSEN_FH_TUERMODUL_CTRL_next_state;
char FH_STEUERUNG_DUMMY_FH_STEUERUNG_DUMMY_next_state;
char EINKLEMMSCHUTZ_CTRL_EINKLEMMSCHUTZ_CTRL_next_state;
char BEWEGUNG_BLOCK_ERKENNUNG_CTRL_next_state;
char BLOCK_ERKENNUNG_CTRL_BLOCK_ERKENNUNG_CTRL_next_state;

void interface(void )
{
# 174 "originaux/statemate.c"
	if(Bitlist[4])
# 175 "originaux/statemate.c"
		tm_entered_WIEDERHOLSPERRE_FH_TUERMODUL_CTRL = time;
# 176 "originaux/statemate.c"
	if(Bitlist[4] || Bitlist[6])
# 177 "originaux/statemate.c"
		tm_entered_WIEDERHOLSPERRE_FH_TUERMODUL_CTRLexited_BEREIT_FH_TUERMODUL_CTRL
			= time;
# 178 "originaux/statemate.c"
	if(sc_FH_TUERMODUL_CTRL_2375_2 != 0 && time -
		sc_FH_TUERMODUL_CTRL_2375_2 >= 0.5)
# 179 "originaux/statemate.c"
	{
# 180 "originaux/statemate.c"
		FH_TUERMODUL__MFHA_copy = 0;
# 181 "originaux/statemate.c"
		sc_FH_TUERMODUL_CTRL_2375_2 = 0;
	}
# 184 "originaux/statemate.c"
	if(sc_FH_TUERMODUL_CTRL_2352_1 != 0 && time -
		sc_FH_TUERMODUL_CTRL_2352_1 >= 0.5)
# 185 "originaux/statemate.c"
	{
# 186 "originaux/statemate.c"
		FH_TUERMODUL__MFHZ_copy = 0;
# 187 "originaux/statemate.c"
		sc_FH_TUERMODUL_CTRL_2352_1 = 0;
	}
# 190 "originaux/statemate.c"
	if(sc_FH_TUERMODUL_CTRL_2329_1 != 0 && time -
		sc_FH_TUERMODUL_CTRL_2329_1 >= 0.5)
# 191 "originaux/statemate.c"
	{
# 192 "originaux/statemate.c"
		FH_TUERMODUL__MFHZ_copy = 0;
# 193 "originaux/statemate.c"
		sc_FH_TUERMODUL_CTRL_2329_1 = 0;
	}
# 196 "originaux/statemate.c"
	if(sc_FH_TUERMODUL_CTRL_1781_10 != 0 && time -
		sc_FH_TUERMODUL_CTRL_1781_10 >= 0.5)
# 197 "originaux/statemate.c"
	{
# 198 "originaux/statemate.c"
		sc_FH_TUERMODUL_CTRL_1781_10 = 0;
	}
# 201 "originaux/statemate.c"
	if(sc_FH_TUERMODUL_CTRL_1739_10 != 0 && time -
		sc_FH_TUERMODUL_CTRL_1739_10 >= 0.5)
# 202 "originaux/statemate.c"
	{
# 203 "originaux/statemate.c"
		sc_FH_TUERMODUL_CTRL_1739_10 = 0;
	}
# 206 "originaux/statemate.c"
	if(Bitlist[0] || BLOCK_ERKENNUNG_CTRL__N != BLOCK_ERKENNUNG_CTRL__N_old)
# 207 "originaux/statemate.c"
		tm_entered_EINSCHALTSTROM_MESSEN_BLOCK_ERKENNUNG_CTRLch_BLOCK_ERKENNUNG_CTRL__N_copy
			= time;
}

void init(void )
{
# 215 "originaux/statemate.c"
	tm_entered_EINSCHALTSTROM_MESSEN_BLOCK_ERKENNUNG_CTRLch_BLOCK_ERKENNUNG_CTRL__N_copy
		= 0;
# 216 "originaux/statemate.c"
	tm_entered_WIEDERHOLSPERRE_FH_TUERMODUL_CTRLexited_BEREIT_FH_TUERMODUL_CTRL
		= 0;
# 217 "originaux/statemate.c"
	tm_entered_WIEDERHOLSPERRE_FH_TUERMODUL_CTRL = 0;
# 218 "originaux/statemate.c"
	NICHT_INITIALISIERT_NICHT_INITIALISIERT_next_state = 0;
# 219 "originaux/statemate.c"
	ZENTRAL_KINDERSICHERUNG_CTRL_next_state = 0;
# 220 "originaux/statemate.c"
	MEC_KINDERSICHERUNG_CTRL_next_state = 0;
# 221 "originaux/statemate.c"
	KINDERSICHERUNG_CTRL_KINDERSICHERUNG_CTRL_next_state = 0;
# 222 "originaux/statemate.c"
	B_FH_TUERMODUL_CTRL_next_state = 0;
# 223 "originaux/statemate.c"
	A_FH_TUERMODUL_CTRL_next_state = 0;
# 224 "originaux/statemate.c"
	WIEDERHOLSPERRE_FH_TUERMODUL_CTRL_next_state = 0;
# 225 "originaux/statemate.c"
	INITIALISIERT_FH_TUERMODUL_CTRL_next_state = 0;
# 226 "originaux/statemate.c"
	TIPP_SCHLIESSEN_FH_TUERMODUL_CTRL_next_state = 0;
# 227 "originaux/statemate.c"
	MANUELL_SCHLIESSEN_FH_TUERMODUL_CTRL_next_state = 0;
# 228 "originaux/statemate.c"
	OEFFNEN_FH_TUERMODUL_CTRL_next_state = 0;
# 229 "originaux/statemate.c"
	SCHLIESSEN_FH_TUERMODUL_CTRL_next_state = 0;
# 230 "originaux/statemate.c"
	FH_STEUERUNG_DUMMY_FH_STEUERUNG_DUMMY_next_state = 0;
# 231 "originaux/statemate.c"
	EINKLEMMSCHUTZ_CTRL_EINKLEMMSCHUTZ_CTRL_next_state = 0;
# 232 "originaux/statemate.c"
	BEWEGUNG_BLOCK_ERKENNUNG_CTRL_next_state = 0;
# 233 "originaux/statemate.c"
	BLOCK_ERKENNUNG_CTRL_BLOCK_ERKENNUNG_CTRL_next_state = 0;
}

void generic_KINDERSICHERUNG_CTRL(void )
{
	char __tmp_4__ = 0, __tmp_2__ = 0, __tmp_3__ = 0, __tmp_1__ = 0,
		__tmp_8__ = 0, __tmp_6__ = 0, __tmp_7__ = 0, __tmp_5__ = 0,
		__tmp_9__ = 0, __tmp_10__ = 0, __tmp_0__ = 0;
# 242 "originaux/statemate.c"
	if(Bitlist[10])
# 243 "originaux/statemate.c"
	{
# 244 "originaux/statemate.c"
		{
			int __tag_2__
				= KINDERSICHERUNG_CTRL_KINDERSICHERUNG_CTRL_next_state;
			if(__tag_2__ == 1)
				__tmp_4__ = 1 != 0;
			else
			{
				if(__tag_2__ == 2)
					__tmp_8__ = 1 != 0;
				else
				{
					if(__tag_2__ == 3)
						__tmp_9__ = 1 != 0;
					else
						__tmp_10__ = 1 != 0;
				}
			}
			if(__tmp_4__ || (__tmp_8__ || (__tmp_9__ || (__tmp_10__
				|| 0))))
# 245 "originaux/statemate.c"
			{
				if(!__tmp_10__)
				{
					if(!__tmp_9__)
					{
						if(!__tmp_8__)
						{
# 246 "originaux/statemate.c"
							__tmp_4__ = 0;
# 247 "originaux/statemate.c"
							{
# 248 "originaux/statemate.c"
	if(!((FH_TUERMODUL__SFHA_ZENTRAL || FH_TUERMODUL__SFHZ_ZENTRAL)))
# 249 "originaux/statemate.c"
	{
# 250 "originaux/statemate.c"
		stable = 0;
# 251 "originaux/statemate.c"
		FH_TUERMODUL__SFHZ_copy = 0;
# 252 "originaux/statemate.c"
		FH_TUERMODUL__SFHA_copy = 0;
# 254 "originaux/statemate.c"
		KINDERSICHERUNG_CTRL_KINDERSICHERUNG_CTRL_next_state = 3;
# 255 "originaux/statemate.c"
		ZENTRAL_KINDERSICHERUNG_CTRL_next_state = 0;
# 256 "originaux/statemate.c"
		__tmp_0__ = 1 != 0;
	}
	if(!__tmp_0__)
	{
# 258 "originaux/statemate.c"
		{
			int __tag_0__ = ZENTRAL_KINDERSICHERUNG_CTRL_next_state;
			if(__tag_0__ == 1)
				__tmp_2__ = 1 != 0;
			else
				__tmp_3__ = 1 != 0;
			if(__tmp_2__ || (__tmp_3__ || 0))
# 259 "originaux/statemate.c"
			{
				if(!__tmp_3__)
				{
# 260 "originaux/statemate.c"
					__tmp_2__ = 0;
# 261 "originaux/statemate.c"
					{
# 262 "originaux/statemate.c"
						if(FH_TUERMODUL__SFHA_ZENTRAL &&
							!FH_TUERMODUL__SFHA_ZENTRAL_old
							)
# 263 "originaux/statemate.c"
						{
# 264 "originaux/statemate.c"
							stable = 0;
# 265 "originaux/statemate.c"
							FH_TUERMODUL__SFHA_copy
								= 1;
# 267 "originaux/statemate.c"
							ZENTRAL_KINDERSICHERUNG_CTRL_next_state
								= 1;
# 268 "originaux/statemate.c"
							__tmp_1__ = 1 != 0;
						}
						if(!__tmp_1__)
						{
# 270 "originaux/statemate.c"
							if(FH_TUERMODUL__SFHZ_ZENTRAL
								&&
								!FH_TUERMODUL__SFHZ_ZENTRAL_old)
# 271 "originaux/statemate.c"
							{
# 272 "originaux/statemate.c"
	stable = 0;
# 273 "originaux/statemate.c"
	FH_TUERMODUL__SFHZ_copy = 1;
# 275 "originaux/statemate.c"
	ZENTRAL_KINDERSICHERUNG_CTRL_next_state = 1;
# 276 "originaux/statemate.c"
	__tmp_1__ = 1 != 0;
							}
							if(!__tmp_1__)
							{
# 278 "originaux/statemate.c"
	if(!FH_TUERMODUL__SFHA_ZENTRAL && FH_TUERMODUL__SFHA_ZENTRAL_old)
# 279 "originaux/statemate.c"
	{
# 280 "originaux/statemate.c"
		stable = 0;
# 281 "originaux/statemate.c"
		FH_TUERMODUL__SFHA_copy = 0;
# 283 "originaux/statemate.c"
		ZENTRAL_KINDERSICHERUNG_CTRL_next_state = 1;
# 284 "originaux/statemate.c"
		__tmp_1__ = 1 != 0;
	}
	if(!__tmp_1__)
	{
# 286 "originaux/statemate.c"
		if(!FH_TUERMODUL__SFHZ_ZENTRAL &&
			FH_TUERMODUL__SFHZ_ZENTRAL_old)
# 287 "originaux/statemate.c"
		{
# 288 "originaux/statemate.c"
			stable = 0;
# 289 "originaux/statemate.c"
			FH_TUERMODUL__SFHZ_copy = 0;
# 291 "originaux/statemate.c"
			ZENTRAL_KINDERSICHERUNG_CTRL_next_state = 1;
# 292 "originaux/statemate.c"
			__tmp_1__ = 1 != 0;
		}
		if(!__tmp_1__)
# 294 "originaux/statemate.c"
			__tmp_1__ = 1 != 0;
	}
							}
						}
					}
				}
				if(!__tmp_1__)
				{
# 296 "originaux/statemate.c"
					__tmp_3__ = 0;
# 297 "originaux/statemate.c"
					{
# 298 "originaux/statemate.c"
						stable = 0;
# 299 "originaux/statemate.c"
						__tmp_1__ = 1 != 0;
					}
				}
			}
			__tmp_1__ = 0;
		}
# 302 "originaux/statemate.c"
		__tmp_0__ = 1 != 0;
	}
							}
						}
						if(!__tmp_0__)
						{
# 304 "originaux/statemate.c"
							__tmp_8__ = 0;
# 305 "originaux/statemate.c"
							{
# 306 "originaux/statemate.c"
	if(!((FH_TUERMODUL__SFHA_MEC || FH_TUERMODUL__SFHZ_MEC)))
# 307 "originaux/statemate.c"
	{
# 308 "originaux/statemate.c"
		stable = 0;
# 309 "originaux/statemate.c"
		FH_TUERMODUL__SFHZ_copy = 0;
# 310 "originaux/statemate.c"
		FH_TUERMODUL__SFHA_copy = 0;
# 312 "originaux/statemate.c"
		KINDERSICHERUNG_CTRL_KINDERSICHERUNG_CTRL_next_state = 3;
# 313 "originaux/statemate.c"
		MEC_KINDERSICHERUNG_CTRL_next_state = 0;
# 314 "originaux/statemate.c"
		__tmp_0__ = 1 != 0;
	}
	if(!__tmp_0__)
	{
# 316 "originaux/statemate.c"
		{
			int __tag_1__ = MEC_KINDERSICHERUNG_CTRL_next_state;
			if(__tag_1__ == 1)
				__tmp_6__ = 1 != 0;
			else
				__tmp_7__ = 1 != 0;
			if(__tmp_6__ || (__tmp_7__ || 0))
# 317 "originaux/statemate.c"
			{
				if(!__tmp_7__)
				{
# 318 "originaux/statemate.c"
					__tmp_6__ = 0;
# 319 "originaux/statemate.c"
					{
# 320 "originaux/statemate.c"
						if(FH_TUERMODUL__SFHA_MEC &&
							!FH_TUERMODUL__SFHA_MEC_old)
# 321 "originaux/statemate.c"
						{
# 322 "originaux/statemate.c"
							stable = 0;
# 323 "originaux/statemate.c"
							FH_TUERMODUL__SFHA_copy
								= 1;
# 325 "originaux/statemate.c"
							MEC_KINDERSICHERUNG_CTRL_next_state
								= 1;
# 326 "originaux/statemate.c"
							__tmp_5__ = 1 != 0;
						}
						if(!__tmp_5__)
						{
# 328 "originaux/statemate.c"
							if(FH_TUERMODUL__SFHZ_MEC
								&&
								!FH_TUERMODUL__SFHZ_MEC_old)
# 329 "originaux/statemate.c"
							{
# 330 "originaux/statemate.c"
	stable = 0;
# 331 "originaux/statemate.c"
	FH_TUERMODUL__SFHZ_copy = 1;
# 333 "originaux/statemate.c"
	MEC_KINDERSICHERUNG_CTRL_next_state = 1;
# 334 "originaux/statemate.c"
	__tmp_5__ = 1 != 0;
							}
							if(!__tmp_5__)
							{
# 336 "originaux/statemate.c"
	if(!FH_TUERMODUL__SFHA_MEC && FH_TUERMODUL__SFHA_MEC_old)
# 337 "originaux/statemate.c"
	{
# 338 "originaux/statemate.c"
		stable = 0;
# 339 "originaux/statemate.c"
		FH_TUERMODUL__SFHA_copy = 0;
# 341 "originaux/statemate.c"
		MEC_KINDERSICHERUNG_CTRL_next_state = 1;
# 342 "originaux/statemate.c"
		__tmp_5__ = 1 != 0;
	}
	if(!__tmp_5__)
	{
# 344 "originaux/statemate.c"
		if(!FH_TUERMODUL__SFHZ_MEC && FH_TUERMODUL__SFHZ_MEC_old)
# 345 "originaux/statemate.c"
		{
# 346 "originaux/statemate.c"
			stable = 0;
# 347 "originaux/statemate.c"
			FH_TUERMODUL__SFHZ_copy = 0;
# 349 "originaux/statemate.c"
			MEC_KINDERSICHERUNG_CTRL_next_state = 1;
# 350 "originaux/statemate.c"
			__tmp_5__ = 1 != 0;
		}
		if(!__tmp_5__)
# 352 "originaux/statemate.c"
			__tmp_5__ = 1 != 0;
	}
							}
						}
					}
				}
				if(!__tmp_5__)
				{
# 354 "originaux/statemate.c"
					__tmp_7__ = 0;
# 355 "originaux/statemate.c"
					{
# 356 "originaux/statemate.c"
						stable = 0;
# 357 "originaux/statemate.c"
						__tmp_5__ = 1 != 0;
					}
				}
			}
			__tmp_5__ = 0;
		}
# 360 "originaux/statemate.c"
		__tmp_0__ = 1 != 0;
	}
							}
						}
					}
					if(!__tmp_0__)
					{
# 362 "originaux/statemate.c"
						__tmp_9__ = 0;
# 363 "originaux/statemate.c"
						{
# 364 "originaux/statemate.c"
							if(!FH_TUERMODUL__KL_50
								&&
								((FH_TUERMODUL__SFHZ_MEC
								&&
								FH_TUERMODUL__SFHA_MEC)
								))
# 365 "originaux/statemate.c"
							{
# 366 "originaux/statemate.c"
	stable = 0;
# 367 "originaux/statemate.c"
	FH_TUERMODUL__SFHZ_copy = 1;
# 368 "originaux/statemate.c"
	FH_TUERMODUL__SFHA_copy = 1;
# 370 "originaux/statemate.c"
	KINDERSICHERUNG_CTRL_KINDERSICHERUNG_CTRL_next_state = 2;
# 371 "originaux/statemate.c"
	__tmp_0__ = 1 != 0;
							}
							if(!__tmp_0__)
							{
# 373 "originaux/statemate.c"
	if(!FH_TUERMODUL__KL_50 && ((FH_TUERMODUL__SFHZ_MEC &&
		!FH_TUERMODUL__SFHA_MEC)))
# 374 "originaux/statemate.c"
	{
# 375 "originaux/statemate.c"
		stable = 0;
# 376 "originaux/statemate.c"
		FH_TUERMODUL__SFHZ_copy = 1;
# 378 "originaux/statemate.c"
		KINDERSICHERUNG_CTRL_KINDERSICHERUNG_CTRL_next_state = 2;
# 379 "originaux/statemate.c"
		__tmp_0__ = 1 != 0;
	}
	if(!__tmp_0__)
	{
# 381 "originaux/statemate.c"
		if(!FH_TUERMODUL__KL_50 && ((!FH_TUERMODUL__SFHZ_MEC &&
			FH_TUERMODUL__SFHA_MEC)))
# 382 "originaux/statemate.c"
		{
# 383 "originaux/statemate.c"
			stable = 0;
# 384 "originaux/statemate.c"
			FH_TUERMODUL__SFHA_copy = 1;
# 386 "originaux/statemate.c"
			KINDERSICHERUNG_CTRL_KINDERSICHERUNG_CTRL_next_state =
				2;
# 387 "originaux/statemate.c"
			__tmp_0__ = 1 != 0;
		}
		if(!__tmp_0__)
		{
# 389 "originaux/statemate.c"
			if(!FH_TUERMODUL__SFHZ_ZENTRAL &&
				FH_TUERMODUL__SFHA_ZENTRAL &&
				!FH_TUERMODUL__KL_50)
# 390 "originaux/statemate.c"
			{
# 391 "originaux/statemate.c"
				stable = 0;
# 392 "originaux/statemate.c"
				FH_TUERMODUL__SFHA_copy = 1;
# 394 "originaux/statemate.c"
				KINDERSICHERUNG_CTRL_KINDERSICHERUNG_CTRL_next_state
					= 1;
# 395 "originaux/statemate.c"
				__tmp_0__ = 1 != 0;
			}
			if(!__tmp_0__)
			{
# 397 "originaux/statemate.c"
				if(FH_TUERMODUL__SFHZ_ZENTRAL &&
					FH_TUERMODUL__SFHA_ZENTRAL)
# 398 "originaux/statemate.c"
				{
# 399 "originaux/statemate.c"
					stable = 0;
# 400 "originaux/statemate.c"
					FH_TUERMODUL__SFHA_copy = 1;
# 401 "originaux/statemate.c"
					FH_TUERMODUL__SFHZ_copy = 1;
# 403 "originaux/statemate.c"
					KINDERSICHERUNG_CTRL_KINDERSICHERUNG_CTRL_next_state
						= 1;
# 404 "originaux/statemate.c"
					__tmp_0__ = 1 != 0;
				}
				if(!__tmp_0__)
				{
# 406 "originaux/statemate.c"
					if(FH_TUERMODUL__SFHZ_ZENTRAL &&
						!FH_TUERMODUL__SFHA_ZENTRAL &&
						!FH_TUERMODUL__KL_50)
# 407 "originaux/statemate.c"
					{
# 408 "originaux/statemate.c"
						stable = 0;
# 409 "originaux/statemate.c"
						FH_TUERMODUL__SFHZ_copy = 1;
# 411 "originaux/statemate.c"
						KINDERSICHERUNG_CTRL_KINDERSICHERUNG_CTRL_next_state
							= 1;
# 412 "originaux/statemate.c"
						__tmp_0__ = 1 != 0;
					}
					if(!__tmp_0__)
# 414 "originaux/statemate.c"
						__tmp_0__ = 1 != 0;
				}
			}
		}
	}
							}
						}
					}
				}
				if(!__tmp_0__)
				{
# 416 "originaux/statemate.c"
					__tmp_10__ = 0;
# 417 "originaux/statemate.c"
					{
# 418 "originaux/statemate.c"
						stable = 0;
# 419 "originaux/statemate.c"
						KINDERSICHERUNG_CTRL_KINDERSICHERUNG_CTRL_next_state
							= 3;
# 420 "originaux/statemate.c"
						__tmp_0__ = 1 != 0;
					}
				}
			}
			__tmp_0__ = 0;
		}
	}
}

void generic_FH_TUERMODUL_CTRL(void )
{
	char __tmp_1__ = 0, __tmp_7__ = 0, __tmp_3__ = 0, __tmp_4__ = 0,
		__tmp_5__ = 0, __tmp_6__ = 0, __tmp_2__ = 0, __tmp_29__ = 0,
		__tmp_13__ = 0, __tmp_10__ = 0, __tmp_11__ = 0, __tmp_12__ = 0,
		__tmp_9__ = 0, __tmp_26__ = 0, __tmp_19__ = 0, __tmp_16__ = 0,
		__tmp_17__ = 0, __tmp_18__ = 0, __tmp_15__ = 0, __tmp_24__ = 0,
		__tmp_21__ = 0, __tmp_22__ = 0, __tmp_23__ = 0, __tmp_20__ = 0,
		__tmp_25__ = 0, __tmp_14__ = 0, __tmp_27__ = 0, __tmp_28__ = 0,
		__tmp_8__ = 0, __tmp_30__ = 0, __tmp_0__ = 0, __tmp_35__ = 0,
		__tmp_33__ = 0, __tmp_34__ = 0, __tmp_32__ = 0, __tmp_36__ = 0,
		__tmp_31__ = 0;
# 428 "originaux/statemate.c"
	if(!Bitlist[13] && Bitlist[15] && !Bitlist[14])
# 429 "originaux/statemate.c"
	{
# 430 "originaux/statemate.c"
		Bitlist[4] = 0;
# 431 "originaux/statemate.c"
		Bitlist[6] = 0;
	}
# 433 "originaux/statemate.c"
	if(Bitlist[13])
# 434 "originaux/statemate.c"
	{
# 435 "originaux/statemate.c"
		if(!Bitlist[10])
# 436 "originaux/statemate.c"
		{
# 437 "originaux/statemate.c"
			KINDERSICHERUNG_CTRL_KINDERSICHERUNG_CTRL_next_state =
				3;
		}
# 439 "originaux/statemate.c"
		Bitlist[11] = 0;
# 440 "originaux/statemate.c"
		if(!Bitlist[19])
# 441 "originaux/statemate.c"
		{
# 442 "originaux/statemate.c"
			Bitlist[0] = 0;
# 443 "originaux/statemate.c"
			BLOCK_ERKENNUNG_CTRL_BLOCK_ERKENNUNG_CTRL_next_state =
				1;
		}
# 445 "originaux/statemate.c"
		Bitlist[20] = 0;
# 446 "originaux/statemate.c"
		Bitlist[11] = 1;
# 447 "originaux/statemate.c"
		Bitlist[20] = 1;
# 448 "originaux/statemate.c"
		{
			int __tag_6__ = B_FH_TUERMODUL_CTRL_next_state;
			if(__tag_6__ == 1)
				__tmp_1__ = 1 != 0;
			else
			{
				if(__tag_6__ == 2)
					__tmp_7__ = 1 != 0;
				else
				{
					if(__tag_6__ == 3)
						__tmp_29__ = 1 != 0;
					else
						__tmp_30__ = 1 != 0;
				}
			}
			if(__tmp_1__ || (__tmp_7__ || (__tmp_29__ || (__tmp_30__
				|| 0))))
# 449 "originaux/statemate.c"
			{
				if(!__tmp_30__)
				{
					if(!__tmp_29__)
					{
						if(!__tmp_7__)
						{
# 450 "originaux/statemate.c"
							__tmp_1__ = 0;
# 451 "originaux/statemate.c"
							{
# 452 "originaux/statemate.c"
	if(FH_TUERMODUL_CTRL__N == 59 && !((FH_TUERMODUL_CTRL__N_old == 59)))
# 453 "originaux/statemate.c"
	{
# 454 "originaux/statemate.c"
		stable = 0;
# 456 "originaux/statemate.c"
		B_FH_TUERMODUL_CTRL_next_state = 3;
# 457 "originaux/statemate.c"
		INITIALISIERT_FH_TUERMODUL_CTRL_next_state = 3;
# 458 "originaux/statemate.c"
		__tmp_0__ = 1 != 0;
	}
	if(!__tmp_0__)
# 460 "originaux/statemate.c"
		__tmp_0__ = 1 != 0;
							}
						}
						if(!__tmp_0__)
						{
# 462 "originaux/statemate.c"
							__tmp_7__ = 0;
# 463 "originaux/statemate.c"
							{
# 464 "originaux/statemate.c"
	if(FH_TUERMODUL__BLOCK && !FH_TUERMODUL__BLOCK_old &&
		FH_TUERMODUL__MFHZ)
# 465 "originaux/statemate.c"
	{
# 466 "originaux/statemate.c"
		stable = 0;
# 467 "originaux/statemate.c"
		FH_TUERMODUL__MFHZ_copy = 0;
# 468 "originaux/statemate.c"
		sc_FH_TUERMODUL_CTRL_2329_1 = time;
# 470 "originaux/statemate.c"
		B_FH_TUERMODUL_CTRL_next_state = 3;
# 471 "originaux/statemate.c"
		INITIALISIERT_FH_TUERMODUL_CTRL_next_state = 3;
# 472 "originaux/statemate.c"
		__tmp_0__ = 1 != 0;
	}
	if(!__tmp_0__)
	{
# 474 "originaux/statemate.c"
		{
			int __tag_0__
				= NICHT_INITIALISIERT_NICHT_INITIALISIERT_next_state;
			if(__tag_0__ == 1)
				__tmp_3__ = 1 != 0;
			else
			{
				if(__tag_0__ == 2)
					__tmp_4__ = 1 != 0;
				else
				{
					if(__tag_0__ == 3)
						__tmp_5__ = 1 != 0;
					else
						__tmp_6__ = 1 != 0;
				}
			}
			if(__tmp_3__ || (__tmp_4__ || (__tmp_5__ || (__tmp_6__
				|| 0))))
# 475 "originaux/statemate.c"
			{
				if(!__tmp_6__)
				{
					if(!__tmp_5__)
					{
						if(!__tmp_4__)
						{
# 476 "originaux/statemate.c"
							__tmp_3__ = 0;
# 477 "originaux/statemate.c"
							{
# 478 "originaux/statemate.c"
	if(!FH_TUERMODUL__SFHZ)
# 479 "originaux/statemate.c"
	{
# 480 "originaux/statemate.c"
		stable = 0;
# 481 "originaux/statemate.c"
		FH_TUERMODUL__MFHZ_copy = 0;
# 483 "originaux/statemate.c"
		NICHT_INITIALISIERT_NICHT_INITIALISIERT_next_state = 3;
# 484 "originaux/statemate.c"
		__tmp_2__ = 1 != 0;
	}
	if(!__tmp_2__)
# 486 "originaux/statemate.c"
		__tmp_2__ = 1 != 0;
							}
						}
						if(!__tmp_2__)
						{
# 488 "originaux/statemate.c"
							__tmp_4__ = 0;
# 489 "originaux/statemate.c"
							{
# 490 "originaux/statemate.c"
	if(!FH_TUERMODUL__SFHA)
# 491 "originaux/statemate.c"
	{
# 492 "originaux/statemate.c"
		stable = 0;
# 493 "originaux/statemate.c"
		FH_TUERMODUL__MFHA_copy = 0;
# 495 "originaux/statemate.c"
		NICHT_INITIALISIERT_NICHT_INITIALISIERT_next_state = 3;
# 496 "originaux/statemate.c"
		__tmp_2__ = 1 != 0;
	}
	if(!__tmp_2__)
# 498 "originaux/statemate.c"
		__tmp_2__ = 1 != 0;
							}
						}
					}
					if(!__tmp_2__)
					{
# 500 "originaux/statemate.c"
						__tmp_5__ = 0;
# 501 "originaux/statemate.c"
						{
# 502 "originaux/statemate.c"
							if(FH_TUERMODUL__SFHA)
# 503 "originaux/statemate.c"
							{
# 504 "originaux/statemate.c"
	stable = 0;
# 505 "originaux/statemate.c"
	FH_TUERMODUL__MFHA_copy = 1;
# 507 "originaux/statemate.c"
	NICHT_INITIALISIERT_NICHT_INITIALISIERT_next_state = 2;
# 508 "originaux/statemate.c"
	__tmp_2__ = 1 != 0;
							}
							if(!__tmp_2__)
							{
# 510 "originaux/statemate.c"
	if(FH_TUERMODUL__SFHZ)
# 511 "originaux/statemate.c"
	{
# 512 "originaux/statemate.c"
		stable = 0;
# 513 "originaux/statemate.c"
		FH_TUERMODUL__MFHZ_copy = 1;
# 515 "originaux/statemate.c"
		NICHT_INITIALISIERT_NICHT_INITIALISIERT_next_state = 1;
# 516 "originaux/statemate.c"
		__tmp_2__ = 1 != 0;
	}
	if(!__tmp_2__)
# 518 "originaux/statemate.c"
		__tmp_2__ = 1 != 0;
							}
						}
					}
				}
				if(!__tmp_2__)
				{
# 520 "originaux/statemate.c"
					__tmp_6__ = 0;
# 521 "originaux/statemate.c"
					{
# 522 "originaux/statemate.c"
						stable = 0;
# 523 "originaux/statemate.c"
						NICHT_INITIALISIERT_NICHT_INITIALISIERT_next_state
							= 3;
# 524 "originaux/statemate.c"
						__tmp_2__ = 1 != 0;
					}
				}
			}
			__tmp_2__ = 0;
		}
# 527 "originaux/statemate.c"
		__tmp_0__ = 1 != 0;
	}
							}
						}
					}
					if(!__tmp_0__)
					{
# 529 "originaux/statemate.c"
						__tmp_29__ = 0;
# 530 "originaux/statemate.c"
						{
# 531 "originaux/statemate.c"
							if(FH_TUERMODUL_CTRL__N
								> 60 &&
								!((FH_TUERMODUL_CTRL__N_old
								> 60)) &&
								!((FH_TUERMODUL_CTRL__INREVERS1
								||
								FH_TUERMODUL_CTRL__INREVERS2)
								))
# 532 "originaux/statemate.c"
							{
# 533 "originaux/statemate.c"
	stable = 0;
# 534 "originaux/statemate.c"
	FH_TUERMODUL__MFHZ_copy = 0;
# 535 "originaux/statemate.c"
	FH_TUERMODUL__MFHA_copy = 0;
# 537 "originaux/statemate.c"
	B_FH_TUERMODUL_CTRL_next_state = 1;
# 538 "originaux/statemate.c"
	__tmp_0__ = 1 != 0;
							}
							if(!__tmp_0__)
							{
# 540 "originaux/statemate.c"
	if(FH_TUERMODUL__BLOCK && !FH_TUERMODUL__BLOCK_old &&
		FH_TUERMODUL__MFHA)
# 541 "originaux/statemate.c"
	{
# 542 "originaux/statemate.c"
		stable = 0;
# 543 "originaux/statemate.c"
		FH_TUERMODUL__MFHA_copy = 0;
# 544 "originaux/statemate.c"
		sc_FH_TUERMODUL_CTRL_2375_2 = time;
# 546 "originaux/statemate.c"
		B_FH_TUERMODUL_CTRL_next_state = 2;
# 547 "originaux/statemate.c"
		NICHT_INITIALISIERT_NICHT_INITIALISIERT_next_state = 3;
# 548 "originaux/statemate.c"
		__tmp_0__ = 1 != 0;
	}
	if(!__tmp_0__)
	{
# 550 "originaux/statemate.c"
		if(FH_TUERMODUL__BLOCK && !FH_TUERMODUL__BLOCK_old &&
			FH_TUERMODUL__MFHZ)
# 551 "originaux/statemate.c"
		{
# 552 "originaux/statemate.c"
			stable = 0;
# 553 "originaux/statemate.c"
			FH_TUERMODUL__MFHZ_copy = 0;
# 554 "originaux/statemate.c"
			sc_FH_TUERMODUL_CTRL_2352_1 = time;
# 556 "originaux/statemate.c"
			B_FH_TUERMODUL_CTRL_next_state = 2;
# 557 "originaux/statemate.c"
			NICHT_INITIALISIERT_NICHT_INITIALISIERT_next_state = 3;
# 558 "originaux/statemate.c"
			__tmp_0__ = 1 != 0;
		}
		if(!__tmp_0__)
		{
# 560 "originaux/statemate.c"
			{
				int __tag_5__
					= INITIALISIERT_FH_TUERMODUL_CTRL_next_state;
				if(__tag_5__ == 1)
					__tmp_13__ = 1 != 0;
				else
				{
					if(__tag_5__ == 2)
						__tmp_26__ = 1 != 0;
					else
					{
						if(__tag_5__ == 3)
							__tmp_27__ = 1 != 0;
						else
							__tmp_28__ = 1 != 0;
					}
				}
				if(__tmp_13__ || (__tmp_26__ || (__tmp_27__ ||
					(__tmp_28__ || 0))))
# 561 "originaux/statemate.c"
				{
					if(!__tmp_28__)
					{
						if(!__tmp_27__)
						{
							if(!__tmp_26__)
							{
# 562 "originaux/statemate.c"
	__tmp_13__ = 0;
# 563 "originaux/statemate.c"
	{
# 564 "originaux/statemate.c"
		if(FH_TUERMODUL__POSITION >= 405)
# 565 "originaux/statemate.c"
		{
# 566 "originaux/statemate.c"
			stable = 0;
# 567 "originaux/statemate.c"
			FH_TUERMODUL__MFHA_copy = 0;
# 569 "originaux/statemate.c"
			INITIALISIERT_FH_TUERMODUL_CTRL_next_state = 3;
# 570 "originaux/statemate.c"
			__tmp_8__ = 1 != 0;
		}
		if(!__tmp_8__)
		{
# 572 "originaux/statemate.c"
			{
				int __tag_1__
					= OEFFNEN_FH_TUERMODUL_CTRL_next_state;
				if(__tag_1__ == 1)
					__tmp_10__ = 1 != 0;
				else
				{
					if(__tag_1__ == 2)
						__tmp_11__ = 1 != 0;
					else
						__tmp_12__ = 1 != 0;
				}
				if(__tmp_10__ || (__tmp_11__ || (__tmp_12__ ||
					0)))
# 573 "originaux/statemate.c"
				{
					if(!__tmp_12__)
					{
						if(!__tmp_11__)
						{
# 574 "originaux/statemate.c"
							__tmp_10__ = 0;
# 575 "originaux/statemate.c"
							{
# 576 "originaux/statemate.c"
	if(FH_TUERMODUL__SFHZ && !FH_TUERMODUL__SFHZ_old || FH_TUERMODUL__SFHA
		&& !FH_TUERMODUL__SFHA_old)
# 577 "originaux/statemate.c"
	{
# 578 "originaux/statemate.c"
		stable = 0;
# 579 "originaux/statemate.c"
		FH_TUERMODUL__MFHA_copy = 0;
# 581 "originaux/statemate.c"
		INITIALISIERT_FH_TUERMODUL_CTRL_next_state = 3;
# 582 "originaux/statemate.c"
		OEFFNEN_FH_TUERMODUL_CTRL_next_state = 0;
# 583 "originaux/statemate.c"
		__tmp_9__ = 1 != 0;
	}
	if(!__tmp_9__)
# 585 "originaux/statemate.c"
		__tmp_9__ = 1 != 0;
							}
						}
						if(!__tmp_9__)
						{
# 587 "originaux/statemate.c"
							__tmp_11__ = 0;
# 588 "originaux/statemate.c"
							{
# 589 "originaux/statemate.c"
	if(FH_TUERMODUL__SFHZ && !FH_TUERMODUL__SFHZ_old)
# 590 "originaux/statemate.c"
	{
# 591 "originaux/statemate.c"
		stable = 0;
# 593 "originaux/statemate.c"
		OEFFNEN_FH_TUERMODUL_CTRL_next_state = 1;
# 594 "originaux/statemate.c"
		__tmp_9__ = 1 != 0;
	}
	if(!__tmp_9__)
	{
# 596 "originaux/statemate.c"
		if(!FH_TUERMODUL__SFHA && FH_TUERMODUL__SFHA_old)
# 597 "originaux/statemate.c"
		{
# 598 "originaux/statemate.c"
			stable = 0;
# 599 "originaux/statemate.c"
			FH_TUERMODUL__MFHA_copy = 0;
# 601 "originaux/statemate.c"
			INITIALISIERT_FH_TUERMODUL_CTRL_next_state = 3;
# 602 "originaux/statemate.c"
			OEFFNEN_FH_TUERMODUL_CTRL_next_state = 0;
# 603 "originaux/statemate.c"
			__tmp_9__ = 1 != 0;
		}
		if(!__tmp_9__)
# 605 "originaux/statemate.c"
			__tmp_9__ = 1 != 0;
	}
							}
						}
					}
					if(!__tmp_9__)
					{
# 607 "originaux/statemate.c"
						__tmp_12__ = 0;
# 608 "originaux/statemate.c"
						{
# 609 "originaux/statemate.c"
							stable = 0;
# 610 "originaux/statemate.c"
							OEFFNEN_FH_TUERMODUL_CTRL_next_state
								= 2;
# 611 "originaux/statemate.c"
							__tmp_9__ = 1 != 0;
						}
					}
				}
				__tmp_9__ = 0;
			}
# 614 "originaux/statemate.c"
			__tmp_8__ = 1 != 0;
		}
	}
							}
							if(!__tmp_8__)
							{
# 616 "originaux/statemate.c"
	__tmp_26__ = 0;
# 617 "originaux/statemate.c"
	{
# 618 "originaux/statemate.c"
		if(FH_TUERMODUL__POSITION <= 0)
# 619 "originaux/statemate.c"
		{
# 620 "originaux/statemate.c"
			stable = 0;
# 621 "originaux/statemate.c"
			FH_TUERMODUL__MFHZ_copy = 0;
# 623 "originaux/statemate.c"
			INITIALISIERT_FH_TUERMODUL_CTRL_next_state = 3;
# 624 "originaux/statemate.c"
			__tmp_8__ = 1 != 0;
		}
		if(!__tmp_8__)
		{
# 626 "originaux/statemate.c"
			{
				int __tag_4__
					= SCHLIESSEN_FH_TUERMODUL_CTRL_next_state;
				if(__tag_4__ == 1)
					__tmp_19__ = 1 != 0;
				else
				{
					if(__tag_4__ == 2)
						__tmp_24__ = 1 != 0;
					else
						__tmp_25__ = 1 != 0;
				}
				if(__tmp_19__ || (__tmp_24__ || (__tmp_25__ ||
					0)))
# 627 "originaux/statemate.c"
				{
					if(!__tmp_25__)
					{
						if(!__tmp_24__)
						{
# 628 "originaux/statemate.c"
							__tmp_19__ = 0;
# 629 "originaux/statemate.c"
							{
# 630 "originaux/statemate.c"
	if(FH_TUERMODUL__SFHA && !FH_TUERMODUL__SFHA_old || FH_TUERMODUL__SFHZ
		&& !FH_TUERMODUL__SFHZ_old)
# 631 "originaux/statemate.c"
	{
# 632 "originaux/statemate.c"
		stable = 0;
# 633 "originaux/statemate.c"
		FH_TUERMODUL__MFHZ_copy = 0;
# 635 "originaux/statemate.c"
		INITIALISIERT_FH_TUERMODUL_CTRL_next_state = 3;
# 636 "originaux/statemate.c"
		__tmp_14__ = 1 != 0;
	}
	if(!__tmp_14__)
	{
# 638 "originaux/statemate.c"
		{
			int __tag_2__
				= TIPP_SCHLIESSEN_FH_TUERMODUL_CTRL_next_state;
			if(__tag_2__ == 1)
				__tmp_16__ = 1 != 0;
			else
			{
				if(__tag_2__ == 2)
					__tmp_17__ = 1 != 0;
				else
					__tmp_18__ = 1 != 0;
			}
			if(__tmp_16__ || (__tmp_17__ || (__tmp_18__ || 0)))
# 639 "originaux/statemate.c"
			{
				if(!__tmp_18__)
				{
					if(!__tmp_17__)
					{
# 640 "originaux/statemate.c"
						__tmp_16__ = 0;
# 641 "originaux/statemate.c"
						{
# 642 "originaux/statemate.c"
							Bitlist[23] = 0;
# 643 "originaux/statemate.c"
							if(Bitlist[22])
# 644 "originaux/statemate.c"
							{
# 645 "originaux/statemate.c"
	stable = 0;
# 646 "originaux/statemate.c"
	FH_TUERMODUL__MFHZ_copy = 1;
# 647 "originaux/statemate.c"
	FH_TUERMODUL_CTRL__INREVERS2_copy = 0;
# 649 "originaux/statemate.c"
	TIPP_SCHLIESSEN_FH_TUERMODUL_CTRL_next_state = 2;
# 650 "originaux/statemate.c"
	FH_TUERMODUL__MFHA_copy = 0;
# 652 "originaux/statemate.c"
	Bitlist[17] = 1;
# 653 "originaux/statemate.c"
	__tmp_15__ = 1 != 0;
							}
							if(!__tmp_15__)
# 655 "originaux/statemate.c"
	__tmp_15__ = 1 != 0;
						}
					}
					if(!__tmp_15__)
					{
# 657 "originaux/statemate.c"
						__tmp_17__ = 0;
# 658 "originaux/statemate.c"
						{
# 659 "originaux/statemate.c"
							if(Bitlist[24])
# 660 "originaux/statemate.c"
							{
# 661 "originaux/statemate.c"
	stable = 0;
# 662 "originaux/statemate.c"
	FH_TUERMODUL_CTRL__INREVERS2_copy = 1;
# 664 "originaux/statemate.c"
	Bitlist[23] = 1;
# 665 "originaux/statemate.c"
	TIPP_SCHLIESSEN_FH_TUERMODUL_CTRL_next_state = 1;
# 666 "originaux/statemate.c"
	Bitlist[17] = 0;
# 667 "originaux/statemate.c"
	FH_TUERMODUL__MFHZ_copy = 0;
# 669 "originaux/statemate.c"
	sc_FH_TUERMODUL_CTRL_1781_10 = time;
# 670 "originaux/statemate.c"
	FH_TUERMODUL__MFHA_copy = 1;
# 671 "originaux/statemate.c"
	__tmp_15__ = 1 != 0;
							}
							if(!__tmp_15__)
# 673 "originaux/statemate.c"
	__tmp_15__ = 1 != 0;
						}
					}
				}
				if(!__tmp_15__)
				{
# 675 "originaux/statemate.c"
					__tmp_18__ = 0;
# 676 "originaux/statemate.c"
					{
# 677 "originaux/statemate.c"
						stable = 0;
# 678 "originaux/statemate.c"
						TIPP_SCHLIESSEN_FH_TUERMODUL_CTRL_next_state
							= 2;
# 679 "originaux/statemate.c"
						Bitlist[17] = 1;
# 680 "originaux/statemate.c"
						__tmp_15__ = 1 != 0;
					}
				}
			}
			__tmp_15__ = 0;
		}
# 683 "originaux/statemate.c"
		__tmp_14__ = 1 != 0;
	}
							}
						}
						if(!__tmp_14__)
						{
# 685 "originaux/statemate.c"
							__tmp_24__ = 0;
# 686 "originaux/statemate.c"
							{
# 687 "originaux/statemate.c"
	if(!FH_TUERMODUL__SFHZ && FH_TUERMODUL__SFHZ_old)
# 688 "originaux/statemate.c"
	{
# 689 "originaux/statemate.c"
		stable = 0;
# 690 "originaux/statemate.c"
		FH_TUERMODUL__MFHZ_copy = 0;
# 692 "originaux/statemate.c"
		INITIALISIERT_FH_TUERMODUL_CTRL_next_state = 3;
# 693 "originaux/statemate.c"
		__tmp_14__ = 1 != 0;
	}
	if(!__tmp_14__)
	{
# 695 "originaux/statemate.c"
		{
			int __tag_3__
				= MANUELL_SCHLIESSEN_FH_TUERMODUL_CTRL_next_state;
			if(__tag_3__ == 1)
				__tmp_21__ = 1 != 0;
			else
			{
				if(__tag_3__ == 2)
					__tmp_22__ = 1 != 0;
				else
					__tmp_23__ = 1 != 0;
			}
			if(__tmp_21__ || (__tmp_22__ || (__tmp_23__ || 0)))
# 696 "originaux/statemate.c"
			{
				if(!__tmp_23__)
				{
					if(!__tmp_22__)
					{
# 697 "originaux/statemate.c"
						__tmp_21__ = 0;
# 698 "originaux/statemate.c"
						{
# 699 "originaux/statemate.c"
							Bitlist[23] = 0;
# 700 "originaux/statemate.c"
							if(Bitlist[22])
# 701 "originaux/statemate.c"
							{
# 702 "originaux/statemate.c"
	stable = 0;
# 703 "originaux/statemate.c"
	FH_TUERMODUL_CTRL__INREVERS1_copy = 0;
# 705 "originaux/statemate.c"
	MANUELL_SCHLIESSEN_FH_TUERMODUL_CTRL_next_state = 2;
# 706 "originaux/statemate.c"
	FH_TUERMODUL__MFHA_copy = 0;
# 708 "originaux/statemate.c"
	Bitlist[17] = 1;
# 709 "originaux/statemate.c"
	FH_TUERMODUL__MFHZ_copy = 1;
# 710 "originaux/statemate.c"
	__tmp_20__ = 1 != 0;
							}
							if(!__tmp_20__)
# 712 "originaux/statemate.c"
	__tmp_20__ = 1 != 0;
						}
					}
					if(!__tmp_20__)
					{
# 714 "originaux/statemate.c"
						__tmp_22__ = 0;
# 715 "originaux/statemate.c"
						{
# 716 "originaux/statemate.c"
							if(Bitlist[24])
# 717 "originaux/statemate.c"
							{
# 718 "originaux/statemate.c"
	stable = 0;
# 719 "originaux/statemate.c"
	FH_TUERMODUL__MFHZ_copy = 0;
# 720 "originaux/statemate.c"
	FH_TUERMODUL_CTRL__INREVERS1_copy = 1;
# 722 "originaux/statemate.c"
	Bitlist[23] = 1;
# 723 "originaux/statemate.c"
	MANUELL_SCHLIESSEN_FH_TUERMODUL_CTRL_next_state = 1;
# 724 "originaux/statemate.c"
	Bitlist[17] = 0;
# 726 "originaux/statemate.c"
	sc_FH_TUERMODUL_CTRL_1739_10 = time;
# 727 "originaux/statemate.c"
	FH_TUERMODUL__MFHA_copy = 1;
# 728 "originaux/statemate.c"
	__tmp_20__ = 1 != 0;
							}
							if(!__tmp_20__)
							{
# 730 "originaux/statemate.c"
	if(FH_TUERMODUL__SFHA && !FH_TUERMODUL__SFHA_old)
# 731 "originaux/statemate.c"
	{
# 732 "originaux/statemate.c"
		stable = 0;
# 734 "originaux/statemate.c"
		SCHLIESSEN_FH_TUERMODUL_CTRL_next_state = 1;
# 735 "originaux/statemate.c"
		MANUELL_SCHLIESSEN_FH_TUERMODUL_CTRL_next_state = 0;
# 736 "originaux/statemate.c"
		__tmp_20__ = 1 != 0;
	}
	if(!__tmp_20__)
# 738 "originaux/statemate.c"
		__tmp_20__ = 1 != 0;
							}
						}
					}
				}
				if(!__tmp_20__)
				{
# 740 "originaux/statemate.c"
					__tmp_23__ = 0;
# 741 "originaux/statemate.c"
					{
# 742 "originaux/statemate.c"
						stable = 0;
# 743 "originaux/statemate.c"
						MANUELL_SCHLIESSEN_FH_TUERMODUL_CTRL_next_state
							= 2;
# 744 "originaux/statemate.c"
						Bitlist[17] = 1;
# 745 "originaux/statemate.c"
						FH_TUERMODUL__MFHZ_copy = 1;
# 746 "originaux/statemate.c"
						__tmp_20__ = 1 != 0;
					}
				}
			}
			__tmp_20__ = 0;
		}
# 749 "originaux/statemate.c"
		__tmp_14__ = 1 != 0;
	}
							}
						}
					}
					if(!__tmp_14__)
					{
# 751 "originaux/statemate.c"
						__tmp_25__ = 0;
# 752 "originaux/statemate.c"
						{
# 753 "originaux/statemate.c"
							stable = 0;
# 754 "originaux/statemate.c"
							SCHLIESSEN_FH_TUERMODUL_CTRL_next_state
								= 2;
# 755 "originaux/statemate.c"
							MANUELL_SCHLIESSEN_FH_TUERMODUL_CTRL_next_state
								= 2;
# 756 "originaux/statemate.c"
							Bitlist[17] = 1;
# 757 "originaux/statemate.c"
							FH_TUERMODUL__MFHZ_copy
								= 1;
# 758 "originaux/statemate.c"
							__tmp_14__ = 1 != 0;
						}
					}
				}
				__tmp_14__ = 0;
			}
# 761 "originaux/statemate.c"
			__tmp_8__ = 1 != 0;
		}
	}
							}
						}
						if(!__tmp_8__)
						{
# 763 "originaux/statemate.c"
							__tmp_27__ = 0;
# 764 "originaux/statemate.c"
							{
# 765 "originaux/statemate.c"
	if(FH_TUERMODUL__SFHZ && !FH_TUERMODUL__SFHZ_old &&
		FH_TUERMODUL__POSITION > 0)
# 766 "originaux/statemate.c"
	{
# 767 "originaux/statemate.c"
		stable = 0;
# 769 "originaux/statemate.c"
		INITIALISIERT_FH_TUERMODUL_CTRL_next_state = 2;
# 770 "originaux/statemate.c"
		SCHLIESSEN_FH_TUERMODUL_CTRL_next_state = 2;
# 771 "originaux/statemate.c"
		MANUELL_SCHLIESSEN_FH_TUERMODUL_CTRL_next_state = 2;
# 772 "originaux/statemate.c"
		Bitlist[17] = 1;
# 773 "originaux/statemate.c"
		FH_TUERMODUL__MFHZ_copy = 1;
# 774 "originaux/statemate.c"
		__tmp_8__ = 1 != 0;
	}
	if(!__tmp_8__)
	{
# 776 "originaux/statemate.c"
		if(FH_TUERMODUL__SFHA && !FH_TUERMODUL__SFHA_old &&
			FH_TUERMODUL__POSITION < 405)
# 777 "originaux/statemate.c"
		{
# 778 "originaux/statemate.c"
			stable = 0;
# 779 "originaux/statemate.c"
			FH_TUERMODUL__MFHA_copy = 1;
# 781 "originaux/statemate.c"
			INITIALISIERT_FH_TUERMODUL_CTRL_next_state = 1;
# 782 "originaux/statemate.c"
			OEFFNEN_FH_TUERMODUL_CTRL_next_state = 2;
# 783 "originaux/statemate.c"
			__tmp_8__ = 1 != 0;
		}
		if(!__tmp_8__)
# 785 "originaux/statemate.c"
			__tmp_8__ = 1 != 0;
	}
							}
						}
					}
					if(!__tmp_8__)
					{
# 787 "originaux/statemate.c"
						__tmp_28__ = 0;
# 788 "originaux/statemate.c"
						{
# 789 "originaux/statemate.c"
							stable = 0;
# 790 "originaux/statemate.c"
							INITIALISIERT_FH_TUERMODUL_CTRL_next_state
								= 3;
# 791 "originaux/statemate.c"
							__tmp_8__ = 1 != 0;
						}
					}
				}
				__tmp_8__ = 0;
			}
# 794 "originaux/statemate.c"
			__tmp_0__ = 1 != 0;
		}
	}
							}
						}
					}
				}
				if(!__tmp_0__)
				{
# 796 "originaux/statemate.c"
					__tmp_30__ = 0;
# 797 "originaux/statemate.c"
					{
# 798 "originaux/statemate.c"
						stable = 0;
# 799 "originaux/statemate.c"
						B_FH_TUERMODUL_CTRL_next_state =
							2;
# 800 "originaux/statemate.c"
						__tmp_0__ = 1 != 0;
					}
				}
			}
			__tmp_0__ = 0;
		}
# 803 "originaux/statemate.c"
		{
			int __tag_8__ = A_FH_TUERMODUL_CTRL_next_state;
			if(__tag_8__ == 1)
				__tmp_35__ = 1 != 0;
			else
				__tmp_36__ = 1 != 0;
			if(__tmp_35__ || (__tmp_36__ || 0))
# 804 "originaux/statemate.c"
			{
				if(!__tmp_36__)
				{
# 805 "originaux/statemate.c"
					__tmp_35__ = 0;
# 806 "originaux/statemate.c"
					{
# 807 "originaux/statemate.c"
						Bitlist[5] = 0;
# 808 "originaux/statemate.c"
						if(step == 1 &&
							tm_entered_WIEDERHOLSPERRE_FH_TUERMODUL_CTRLexited_BEREIT_FH_TUERMODUL_CTRL
							!= 0 && time -
							tm_entered_WIEDERHOLSPERRE_FH_TUERMODUL_CTRLexited_BEREIT_FH_TUERMODUL_CTRL
							== 1 &&
							(((FH_TUERMODUL__MFHZ ||
							FH_TUERMODUL__MFHA))))
# 809 "originaux/statemate.c"
						{
# 810 "originaux/statemate.c"
							stable = 0;
# 811 "originaux/statemate.c"
							FH_TUERMODUL_CTRL__N =
								FH_TUERMODUL_CTRL__N
								+ 1;
# 813 "originaux/statemate.c"
							A_FH_TUERMODUL_CTRL_next_state
								= 1;
# 814 "originaux/statemate.c"
							Bitlist[5] = 1;
# 815 "originaux/statemate.c"
							WIEDERHOLSPERRE_FH_TUERMODUL_CTRL_next_state
								= 1;
# 816 "originaux/statemate.c"
							__tmp_31__ = 1 != 0;
						}
						if(!__tmp_31__)
						{
# 818 "originaux/statemate.c"
							{
	int __tag_7__ = WIEDERHOLSPERRE_FH_TUERMODUL_CTRL_next_state;
	if(__tag_7__ == 1)
		__tmp_33__ = 1 != 0;
	else
		__tmp_34__ = 1 != 0;
	if(__tmp_33__ || (__tmp_34__ || 0))
# 819 "originaux/statemate.c"
	{
		if(!__tmp_34__)
		{
# 820 "originaux/statemate.c"
			__tmp_33__ = 0;
# 821 "originaux/statemate.c"
			{
# 822 "originaux/statemate.c"
				if(step == 1 &&
					tm_entered_WIEDERHOLSPERRE_FH_TUERMODUL_CTRL
					!= 0 && time -
					tm_entered_WIEDERHOLSPERRE_FH_TUERMODUL_CTRL
					== 3 && (((!((FH_TUERMODUL__MFHZ ||
					FH_TUERMODUL__MFHA)) &&
					FH_TUERMODUL_CTRL__N > 0))))
# 823 "originaux/statemate.c"
				{
# 824 "originaux/statemate.c"
					stable = 0;
# 825 "originaux/statemate.c"
					FH_TUERMODUL_CTRL__N =
						FH_TUERMODUL_CTRL__N - 1;
# 827 "originaux/statemate.c"
					WIEDERHOLSPERRE_FH_TUERMODUL_CTRL_next_state
						= 1;
# 828 "originaux/statemate.c"
					__tmp_32__ = 1 != 0;
				}
				if(!__tmp_32__)
# 830 "originaux/statemate.c"
					__tmp_32__ = 1 != 0;
			}
		}
		if(!__tmp_32__)
		{
# 832 "originaux/statemate.c"
			__tmp_34__ = 0;
# 833 "originaux/statemate.c"
			{
# 834 "originaux/statemate.c"
				stable = 0;
# 835 "originaux/statemate.c"
				Bitlist[5] = 1;
# 836 "originaux/statemate.c"
				WIEDERHOLSPERRE_FH_TUERMODUL_CTRL_next_state =
					1;
# 837 "originaux/statemate.c"
				__tmp_32__ = 1 != 0;
			}
		}
	}
	__tmp_32__ = 0;
							}
# 840 "originaux/statemate.c"
							__tmp_31__ = 1 != 0;
						}
					}
				}
				if(!__tmp_31__)
				{
# 842 "originaux/statemate.c"
					__tmp_36__ = 0;
# 843 "originaux/statemate.c"
					{
# 844 "originaux/statemate.c"
						stable = 0;
# 845 "originaux/statemate.c"
						FH_TUERMODUL_CTRL__N = 0;
# 846 "originaux/statemate.c"
						A_FH_TUERMODUL_CTRL_next_state =
							1;
# 847 "originaux/statemate.c"
						Bitlist[5] = 1;
# 848 "originaux/statemate.c"
						WIEDERHOLSPERRE_FH_TUERMODUL_CTRL_next_state
							= 1;
# 849 "originaux/statemate.c"
						__tmp_31__ = 1 != 0;
					}
				}
			}
			__tmp_31__ = 0;
		}
# 852 "originaux/statemate.c"
		Bitlist[5] = Bitlist[4];
# 853 "originaux/statemate.c"
		Bitlist[7] = Bitlist[6];
	}
}

void generic_EINKLEMMSCHUTZ_CTRL(void )
{
	char __tmp_1__ = 0, __tmp_2__ = 0, __tmp_3__ = 0, __tmp_0__ = 0;
# 859 "originaux/statemate.c"
	if(Bitlist[16])
# 860 "originaux/statemate.c"
	{
# 861 "originaux/statemate.c"
		{
			int __tag_0__
				= EINKLEMMSCHUTZ_CTRL_EINKLEMMSCHUTZ_CTRL_next_state;
			if(__tag_0__ == 1)
				__tmp_1__ = 1 != 0;
			else
			{
				if(__tag_0__ == 2)
					__tmp_2__ = 1 != 0;
				else
					__tmp_3__ = 1 != 0;
			}
			if(__tmp_1__ || (__tmp_2__ || (__tmp_3__ || 0)))
# 862 "originaux/statemate.c"
			{
				if(!__tmp_3__)
				{
					if(!__tmp_2__)
					{
# 863 "originaux/statemate.c"
						__tmp_1__ = 0;
# 864 "originaux/statemate.c"
						{
# 865 "originaux/statemate.c"
							if(FH_TUERMODUL__EKS_LEISTE_AKTIV
								&&
								!FH_TUERMODUL__EKS_LEISTE_AKTIV_old
								&&
								!((FH_TUERMODUL__SFHZ
								&&
								FH_TUERMODUL__SFHA)
								))
# 866 "originaux/statemate.c"
							{
# 867 "originaux/statemate.c"
	stable = 0;
# 869 "originaux/statemate.c"
	Bitlist[24] = 1;
# 870 "originaux/statemate.c"
	EINKLEMMSCHUTZ_CTRL_EINKLEMMSCHUTZ_CTRL_next_state = 2;
# 871 "originaux/statemate.c"
	__tmp_0__ = 1 != 0;
							}
							if(!__tmp_0__)
# 873 "originaux/statemate.c"
	__tmp_0__ = 1 != 0;
						}
					}
					if(!__tmp_0__)
					{
# 875 "originaux/statemate.c"
						__tmp_2__ = 0;
# 876 "originaux/statemate.c"
						{
# 877 "originaux/statemate.c"
							Bitlist[24] = 0;
# 878 "originaux/statemate.c"
							if(!FH_TUERMODUL__EKS_LEISTE_AKTIV
								&&
								FH_TUERMODUL__EKS_LEISTE_AKTIV_old)
# 879 "originaux/statemate.c"
							{
# 880 "originaux/statemate.c"
	stable = 0;
# 882 "originaux/statemate.c"
	EINKLEMMSCHUTZ_CTRL_EINKLEMMSCHUTZ_CTRL_next_state = 1;
# 883 "originaux/statemate.c"
	__tmp_0__ = 1 != 0;
							}
							if(!__tmp_0__)
# 885 "originaux/statemate.c"
	__tmp_0__ = 1 != 0;
						}
					}
				}
				if(!__tmp_0__)
				{
# 887 "originaux/statemate.c"
					__tmp_3__ = 0;
# 888 "originaux/statemate.c"
					{
# 889 "originaux/statemate.c"
						stable = 0;
# 890 "originaux/statemate.c"
						EINKLEMMSCHUTZ_CTRL_EINKLEMMSCHUTZ_CTRL_next_state
							= 1;
# 891 "originaux/statemate.c"
						__tmp_0__ = 1 != 0;
					}
				}
			}
			__tmp_0__ = 0;
		}
	}
}

void generic_BLOCK_ERKENNUNG_CTRL(void )
{
	char __tmp_1__ = 0, __tmp_7__ = 0, __tmp_3__ = 0, __tmp_4__ = 0,
		__tmp_5__ = 0, __tmp_6__ = 0, __tmp_2__ = 0, __tmp_8__ = 0,
		__tmp_0__ = 0;
# 899 "originaux/statemate.c"
	if(!Bitlist[19] && Bitlist[21] && !Bitlist[20])
# 900 "originaux/statemate.c"
	{
# 901 "originaux/statemate.c"
		Bitlist[0] = 0;
	}
# 903 "originaux/statemate.c"
	if(Bitlist[19])
# 904 "originaux/statemate.c"
	{
# 905 "originaux/statemate.c"
		{
			int __tag_1__
				= BLOCK_ERKENNUNG_CTRL_BLOCK_ERKENNUNG_CTRL_next_state;
			if(__tag_1__ == 1)
				__tmp_1__ = 1 != 0;
			else
			{
				if(__tag_1__ == 2)
					__tmp_7__ = 1 != 0;
				else
					__tmp_8__ = 1 != 0;
			}
			if(__tmp_1__ || (__tmp_7__ || (__tmp_8__ || 0)))
# 906 "originaux/statemate.c"
			{
				if(!__tmp_8__)
				{
					if(!__tmp_7__)
					{
# 907 "originaux/statemate.c"
						__tmp_1__ = 0;
# 908 "originaux/statemate.c"
						{
# 909 "originaux/statemate.c"
							if(FH_TUERMODUL__I_EIN
								!=
								FH_TUERMODUL__I_EIN_old
								&&
								FH_TUERMODUL__I_EIN
								> 0)
# 910 "originaux/statemate.c"
							{
# 911 "originaux/statemate.c"
	stable = 0;
# 912 "originaux/statemate.c"
	FH_TUERMODUL__BLOCK_copy = 0;
# 914 "originaux/statemate.c"
	BLOCK_ERKENNUNG_CTRL_BLOCK_ERKENNUNG_CTRL_next_state = 2;
# 915 "originaux/statemate.c"
	BLOCK_ERKENNUNG_CTRL__N = 0;
# 916 "originaux/statemate.c"
	BLOCK_ERKENNUNG_CTRL__I_EIN_MAX = 2;
# 917 "originaux/statemate.c"
	BEWEGUNG_BLOCK_ERKENNUNG_CTRL_next_state = 3;
# 918 "originaux/statemate.c"
	Bitlist[0] = 1;
# 919 "originaux/statemate.c"
	__tmp_0__ = 1 != 0;
							}
							if(!__tmp_0__)
# 921 "originaux/statemate.c"
	__tmp_0__ = 1 != 0;
						}
					}
					if(!__tmp_0__)
					{
# 923 "originaux/statemate.c"
						__tmp_7__ = 0;
# 924 "originaux/statemate.c"
						{
# 925 "originaux/statemate.c"
							if(!FH_TUERMODUL__MFHA
								&&
								FH_TUERMODUL__MFHA_old
								||
								!FH_TUERMODUL__MFHZ
								&&
								FH_TUERMODUL__MFHZ_old)
# 926 "originaux/statemate.c"
							{
# 927 "originaux/statemate.c"
	stable = 0;
# 929 "originaux/statemate.c"
	BLOCK_ERKENNUNG_CTRL_BLOCK_ERKENNUNG_CTRL_next_state = 1;
# 930 "originaux/statemate.c"
	BEWEGUNG_BLOCK_ERKENNUNG_CTRL_next_state = 0;
# 931 "originaux/statemate.c"
	__tmp_0__ = 1 != 0;
							}
							if(!__tmp_0__)
							{
# 933 "originaux/statemate.c"
	{
		int __tag_0__ = BEWEGUNG_BLOCK_ERKENNUNG_CTRL_next_state;
		if(__tag_0__ == 1)
			__tmp_3__ = 1 != 0;
		else
		{
			if(__tag_0__ == 2)
				__tmp_4__ = 1 != 0;
			else
			{
				if(__tag_0__ == 3)
					__tmp_5__ = 1 != 0;
				else
					__tmp_6__ = 1 != 0;
			}
		}
		if(__tmp_3__ || (__tmp_4__ || (__tmp_5__ || (__tmp_6__ || 0))))
# 934 "originaux/statemate.c"
		{
			if(!__tmp_6__)
			{
				if(!__tmp_5__)
				{
					if(!__tmp_4__)
					{
# 935 "originaux/statemate.c"
						__tmp_3__ = 0;
# 936 "originaux/statemate.c"
						{
# 937 "originaux/statemate.c"
							__tmp_2__ = 1 != 0;
						}
					}
					if(!__tmp_2__)
					{
# 939 "originaux/statemate.c"
						__tmp_4__ = 0;
# 940 "originaux/statemate.c"
						{
# 941 "originaux/statemate.c"
							if(FH_TUERMODUL__I_EIN >
								BLOCK_ERKENNUNG_CTRL__I_EIN_MAX
								- 2)
# 942 "originaux/statemate.c"
							{
# 943 "originaux/statemate.c"
	stable = 0;
# 944 "originaux/statemate.c"
	FH_TUERMODUL__BLOCK_copy = 1;
# 946 "originaux/statemate.c"
	BEWEGUNG_BLOCK_ERKENNUNG_CTRL_next_state = 1;
# 947 "originaux/statemate.c"
	__tmp_2__ = 1 != 0;
							}
							if(!__tmp_2__)
# 949 "originaux/statemate.c"
	__tmp_2__ = 1 != 0;
						}
					}
				}
				if(!__tmp_2__)
				{
# 951 "originaux/statemate.c"
					__tmp_5__ = 0;
# 952 "originaux/statemate.c"
					{
# 953 "originaux/statemate.c"
						Bitlist[0] = 0;
# 954 "originaux/statemate.c"
						if(BLOCK_ERKENNUNG_CTRL__N == 11
							&&
							!((BLOCK_ERKENNUNG_CTRL__N_old
							== 11)))
# 955 "originaux/statemate.c"
						{
# 956 "originaux/statemate.c"
							stable = 0;
# 958 "originaux/statemate.c"
							BEWEGUNG_BLOCK_ERKENNUNG_CTRL_next_state
								= 2;
# 959 "originaux/statemate.c"
							__tmp_2__ = 1 != 0;
						}
						if(!__tmp_2__)
						{
# 962 "originaux/statemate.c"
							if(BEWEGUNG_BLOCK_ERKENNUNG_CTRL_next_state
								== 3)
# 963 "originaux/statemate.c"
							{
# 964 "originaux/statemate.c"
	if(step == 1 &&
		tm_entered_EINSCHALTSTROM_MESSEN_BLOCK_ERKENNUNG_CTRLch_BLOCK_ERKENNUNG_CTRL__N_copy
		!= 0 && time -
		tm_entered_EINSCHALTSTROM_MESSEN_BLOCK_ERKENNUNG_CTRLch_BLOCK_ERKENNUNG_CTRL__N_copy
		== 0.002)
# 965 "originaux/statemate.c"
	{
# 966 "originaux/statemate.c"
		BLOCK_ERKENNUNG_CTRL__N = BLOCK_ERKENNUNG_CTRL__N + 1;
# 967 "originaux/statemate.c"
		if(FH_TUERMODUL__I_EIN > BLOCK_ERKENNUNG_CTRL__I_EIN_MAX)
# 968 "originaux/statemate.c"
		{
# 969 "originaux/statemate.c"
			BLOCK_ERKENNUNG_CTRL__I_EIN_MAX = FH_TUERMODUL__I_EIN;
		}
	}
							}
# 976 "originaux/statemate.c"
							__tmp_2__ = 1 != 0;
						}
					}
				}
			}
			if(!__tmp_2__)
			{
# 978 "originaux/statemate.c"
				__tmp_6__ = 0;
# 979 "originaux/statemate.c"
				{
# 980 "originaux/statemate.c"
					stable = 0;
# 981 "originaux/statemate.c"
					BLOCK_ERKENNUNG_CTRL__N = 0;
# 982 "originaux/statemate.c"
					BLOCK_ERKENNUNG_CTRL__I_EIN_MAX = 2;
# 983 "originaux/statemate.c"
					BEWEGUNG_BLOCK_ERKENNUNG_CTRL_next_state
						= 3;
# 984 "originaux/statemate.c"
					Bitlist[0] = 1;
# 985 "originaux/statemate.c"
					__tmp_2__ = 1 != 0;
				}
			}
		}
		__tmp_2__ = 0;
	}
# 988 "originaux/statemate.c"
	__tmp_0__ = 1 != 0;
							}
						}
					}
				}
				if(!__tmp_0__)
				{
# 990 "originaux/statemate.c"
					__tmp_8__ = 0;
# 991 "originaux/statemate.c"
					{
# 992 "originaux/statemate.c"
						stable = 0;
# 993 "originaux/statemate.c"
						BLOCK_ERKENNUNG_CTRL_BLOCK_ERKENNUNG_CTRL_next_state
							= 1;
# 994 "originaux/statemate.c"
						__tmp_0__ = 1 != 0;
					}
				}
			}
			__tmp_0__ = 0;
		}
	}
}

void FH_DU(void )
{
	char __tmp_1__ = 0, __tmp_2__ = 0, __tmp_3__ = 0, __tmp_4__ = 0,
		__tmp_0__ = 0;
# 1004 "originaux/statemate.c"
	time = 1;
# 1005 "originaux/statemate.c"
	stable = 0;
# 1006 "originaux/statemate.c"
	step = 0;
# 1007 "originaux/statemate.c"
	while(!stable)
# 1008 "originaux/statemate.c"
	{
# 1009 "originaux/statemate.c"
		stable = 1;
# 1010 "originaux/statemate.c"
		step++;
# 1011 "originaux/statemate.c"
		{
# 1012 "originaux/statemate.c"
			{
				int __tag_0__
					= FH_STEUERUNG_DUMMY_FH_STEUERUNG_DUMMY_next_state;
				if(__tag_0__ == 1)
					__tmp_1__ = 1 != 0;
				else
				{
					if(__tag_0__ == 2)
						__tmp_2__ = 1 != 0;
					else
					{
						if(__tag_0__ == 3)
							__tmp_3__ = 1 != 0;
						else
							__tmp_4__ = 1 != 0;
					}
				}
				if(__tmp_1__ || (__tmp_2__ || (__tmp_3__ ||
					(__tmp_4__ || 0))))
# 1013 "originaux/statemate.c"
				{
					if(!__tmp_4__)
					{
						if(!__tmp_3__)
						{
							if(!__tmp_2__)
							{
# 1014 "originaux/statemate.c"
	__tmp_1__ = 0;
# 1015 "originaux/statemate.c"
	{
# 1016 "originaux/statemate.c"
		if(!FH_DU__MFHZ && FH_DU__MFHZ_old)
# 1017 "originaux/statemate.c"
		{
# 1018 "originaux/statemate.c"
			stable = 0;
# 1019 "originaux/statemate.c"
			FH_DU__MFH = 0;
# 1021 "originaux/statemate.c"
			FH_STEUERUNG_DUMMY_FH_STEUERUNG_DUMMY_next_state = 2;
# 1022 "originaux/statemate.c"
			__tmp_0__ = 1 != 0;
		}
		if(!__tmp_0__)
# 1024 "originaux/statemate.c"
			__tmp_0__ = 1 != 0;
	}
							}
							if(!__tmp_0__)
							{
# 1026 "originaux/statemate.c"
	__tmp_2__ = 0;
# 1027 "originaux/statemate.c"
	{
# 1028 "originaux/statemate.c"
		if(FH_DU__MFHZ && !FH_DU__MFHZ_old)
# 1029 "originaux/statemate.c"
		{
# 1030 "originaux/statemate.c"
			stable = 0;
# 1031 "originaux/statemate.c"
			FH_DU__MFH = -100;
# 1033 "originaux/statemate.c"
			FH_STEUERUNG_DUMMY_FH_STEUERUNG_DUMMY_next_state = 1;
# 1034 "originaux/statemate.c"
			__tmp_0__ = 1 != 0;
		}
		if(!__tmp_0__)
		{
# 1036 "originaux/statemate.c"
			if(FH_DU__MFHA && !FH_DU__MFHA_old)
# 1037 "originaux/statemate.c"
			{
# 1038 "originaux/statemate.c"
				stable = 0;
# 1039 "originaux/statemate.c"
				FH_DU__MFH = 100;
# 1041 "originaux/statemate.c"
				FH_STEUERUNG_DUMMY_FH_STEUERUNG_DUMMY_next_state
					= 3;
# 1042 "originaux/statemate.c"
				__tmp_0__ = 1 != 0;
			}
			if(!__tmp_0__)
# 1044 "originaux/statemate.c"
				__tmp_0__ = 1 != 0;
		}
	}
							}
						}
						if(!__tmp_0__)
						{
# 1046 "originaux/statemate.c"
							__tmp_3__ = 0;
# 1047 "originaux/statemate.c"
							{
# 1048 "originaux/statemate.c"
	if(!FH_DU__MFHA && FH_DU__MFHA_old)
# 1049 "originaux/statemate.c"
	{
# 1050 "originaux/statemate.c"
		stable = 0;
# 1051 "originaux/statemate.c"
		FH_DU__MFH = 0;
# 1053 "originaux/statemate.c"
		FH_STEUERUNG_DUMMY_FH_STEUERUNG_DUMMY_next_state = 2;
# 1054 "originaux/statemate.c"
		__tmp_0__ = 1 != 0;
	}
	if(!__tmp_0__)
# 1056 "originaux/statemate.c"
		__tmp_0__ = 1 != 0;
							}
						}
					}
					if(!__tmp_0__)
					{
# 1058 "originaux/statemate.c"
						__tmp_4__ = 0;
# 1059 "originaux/statemate.c"
						{
# 1060 "originaux/statemate.c"
							stable = 0;
# 1061 "originaux/statemate.c"
							FH_DU__MFH = 0;
# 1062 "originaux/statemate.c"
							FH_STEUERUNG_DUMMY_FH_STEUERUNG_DUMMY_next_state
								= 2;
# 1063 "originaux/statemate.c"
							__tmp_0__ = 1 != 0;
						}
					}
				}
				__tmp_0__ = 0;
			}
		}
# 1067 "originaux/statemate.c"
		{
# 1068 "originaux/statemate.c"
			{
# 1069 "originaux/statemate.c"
				if(!Bitlist[10])
# 1070 "originaux/statemate.c"
				{
# 1071 "originaux/statemate.c"
					KINDERSICHERUNG_CTRL_KINDERSICHERUNG_CTRL_next_state
						= 3;
				}
# 1073 "originaux/statemate.c"
				Bitlist[11] = 0;
# 1074 "originaux/statemate.c"
				if(!Bitlist[16])
# 1075 "originaux/statemate.c"
				{
# 1076 "originaux/statemate.c"
					EINKLEMMSCHUTZ_CTRL_EINKLEMMSCHUTZ_CTRL_next_state
						= 1;
				}
# 1078 "originaux/statemate.c"
				Bitlist[17] = 0;
# 1079 "originaux/statemate.c"
				if(!Bitlist[19])
# 1080 "originaux/statemate.c"
				{
# 1081 "originaux/statemate.c"
					Bitlist[0] = 0;
# 1082 "originaux/statemate.c"
					BLOCK_ERKENNUNG_CTRL_BLOCK_ERKENNUNG_CTRL_next_state
						= 1;
				}
# 1084 "originaux/statemate.c"
				Bitlist[20] = 0;
# 1085 "originaux/statemate.c"
				if(!Bitlist[13])
# 1086 "originaux/statemate.c"
				{
# 1087 "originaux/statemate.c"
					Bitlist[4] = 0;
# 1088 "originaux/statemate.c"
					Bitlist[6] = 0;
# 1089 "originaux/statemate.c"
					B_FH_TUERMODUL_CTRL_next_state = 2;
# 1090 "originaux/statemate.c"
					FH_TUERMODUL_CTRL__N = 0;
# 1091 "originaux/statemate.c"
					A_FH_TUERMODUL_CTRL_next_state = 1;
# 1092 "originaux/statemate.c"
					Bitlist[5] = 1;
# 1093 "originaux/statemate.c"
					WIEDERHOLSPERRE_FH_TUERMODUL_CTRL_next_state
						= 1;
				}
# 1095 "originaux/statemate.c"
				Bitlist[14] = 0;
# 1096 "originaux/statemate.c"
				Bitlist[11] = 1;
# 1097 "originaux/statemate.c"
				Bitlist[17] = 1;
# 1098 "originaux/statemate.c"
				Bitlist[20] = 1;
# 1099 "originaux/statemate.c"
				Bitlist[14] = 1;
# 1101 "originaux/statemate.c"
				if(FH_DU__S_FH_TMBFZUCAN !=
					FH_DU__S_FH_TMBFZUCAN_old)
# 1102 "originaux/statemate.c"
				{
# 1103 "originaux/statemate.c"
					if(!FH_DU__DOOR_ID)
# 1104 "originaux/statemate.c"
					{
# 1105 "originaux/statemate.c"
						FH_DU__S_FH_FTZU =
							FH_DU__S_FH_TMBFZUCAN;
					}
				}
# 1110 "originaux/statemate.c"
				if(FH_DU__S_FH_TMBFZUDISC !=
					FH_DU__S_FH_TMBFZUDISC_old)
# 1111 "originaux/statemate.c"
				{
# 1112 "originaux/statemate.c"
					if(FH_DU__DOOR_ID)
# 1113 "originaux/statemate.c"
					{
# 1114 "originaux/statemate.c"
						FH_DU__S_FH_TMBFZUCAN =
							FH_DU__S_FH_TMBFZUDISC;
					}
				}
# 1119 "originaux/statemate.c"
				if(FH_DU__S_FH_TMBFAUFCAN !=
					FH_DU__S_FH_TMBFAUFCAN_old)
# 1120 "originaux/statemate.c"
				{
# 1121 "originaux/statemate.c"
					if(!FH_DU__DOOR_ID)
# 1122 "originaux/statemate.c"
					{
# 1123 "originaux/statemate.c"
						FH_DU__S_FH_FTAUF =
							FH_DU__S_FH_TMBFAUFCAN;
					}
				}
# 1128 "originaux/statemate.c"
				if(FH_DU__S_FH_TMBFAUFDISC !=
					FH_DU__S_FH_TMBFAUFDISC_old)
# 1129 "originaux/statemate.c"
				{
# 1130 "originaux/statemate.c"
					if(FH_DU__DOOR_ID)
# 1131 "originaux/statemate.c"
					{
# 1132 "originaux/statemate.c"
						FH_DU__S_FH_TMBFAUFCAN =
							FH_DU__S_FH_TMBFAUFDISC;
					}
				}
			}
		}
# 1140 "originaux/statemate.c"
		Bitlist[10] = Bitlist[12];
# 1141 "originaux/statemate.c"
		Bitlist[13] = Bitlist[15];
# 1142 "originaux/statemate.c"
		Bitlist[16] = Bitlist[18];
# 1143 "originaux/statemate.c"
		Bitlist[19] = Bitlist[21];
# 1144 "originaux/statemate.c"
		FH_TUERMODUL__SFHA_MEC = FH_DU__S_FH_AUFDISC;
# 1145 "originaux/statemate.c"
		FH_TUERMODUL__SFHA_ZENTRAL = FH_DU__S_FH_FTAUF;
# 1146 "originaux/statemate.c"
		FH_TUERMODUL__SFHZ_MEC = FH_DU__S_FH_ZUDISC;
# 1147 "originaux/statemate.c"
		FH_TUERMODUL__SFHZ_ZENTRAL = FH_DU__S_FH_FTZU;
# 1149 "originaux/statemate.c"
		generic_KINDERSICHERUNG_CTRL();
# 1151 "originaux/statemate.c"
		FH_DU__MFHA = FH_TUERMODUL__MFHA;
# 1152 "originaux/statemate.c"
		FH_DU__MFHZ = FH_TUERMODUL__MFHZ;
# 1153 "originaux/statemate.c"
		FH_DU__I_EIN = FH_TUERMODUL__I_EIN;
# 1154 "originaux/statemate.c"
		FH_DU__EKS_LEISTE_AKTIV = FH_TUERMODUL__EKS_LEISTE_AKTIV;
# 1155 "originaux/statemate.c"
		FH_DU__POSITION = FH_TUERMODUL__POSITION;
# 1156 "originaux/statemate.c"
		FH_DU__FT = FH_TUERMODUL__FT;
# 1157 "originaux/statemate.c"
		FH_DU__S_FH_AUFDISC = FH_TUERMODUL__SFHA_MEC;
# 1158 "originaux/statemate.c"
		FH_DU__S_FH_FTAUF = FH_TUERMODUL__SFHA_ZENTRAL;
# 1159 "originaux/statemate.c"
		FH_DU__S_FH_ZUDISC = FH_TUERMODUL__SFHZ_MEC;
# 1160 "originaux/statemate.c"
		FH_DU__S_FH_FTZU = FH_TUERMODUL__SFHZ_ZENTRAL;
# 1161 "originaux/statemate.c"
		FH_DU__KL_50 = FH_TUERMODUL__KL_50;
# 1162 "originaux/statemate.c"
		FH_DU__BLOCK = FH_TUERMODUL__BLOCK;
# 1164 "originaux/statemate.c"
		FH_TUERMODUL__SFHA_MEC = FH_DU__S_FH_AUFDISC;
# 1165 "originaux/statemate.c"
		FH_TUERMODUL__SFHA_ZENTRAL = FH_DU__S_FH_FTAUF;
# 1166 "originaux/statemate.c"
		FH_TUERMODUL__SFHZ_MEC = FH_DU__S_FH_ZUDISC;
# 1167 "originaux/statemate.c"
		FH_TUERMODUL__SFHZ_ZENTRAL = FH_DU__S_FH_FTZU;
# 1169 "originaux/statemate.c"
		generic_FH_TUERMODUL_CTRL();
# 1171 "originaux/statemate.c"
		FH_DU__MFHA = FH_TUERMODUL__MFHA;
# 1172 "originaux/statemate.c"
		FH_DU__MFHZ = FH_TUERMODUL__MFHZ;
# 1173 "originaux/statemate.c"
		FH_DU__I_EIN = FH_TUERMODUL__I_EIN;
# 1174 "originaux/statemate.c"
		FH_DU__EKS_LEISTE_AKTIV = FH_TUERMODUL__EKS_LEISTE_AKTIV;
# 1175 "originaux/statemate.c"
		FH_DU__POSITION = FH_TUERMODUL__POSITION;
# 1176 "originaux/statemate.c"
		FH_DU__FT = FH_TUERMODUL__FT;
# 1177 "originaux/statemate.c"
		FH_DU__S_FH_AUFDISC = FH_TUERMODUL__SFHA_MEC;
# 1178 "originaux/statemate.c"
		FH_DU__S_FH_FTAUF = FH_TUERMODUL__SFHA_ZENTRAL;
# 1179 "originaux/statemate.c"
		FH_DU__S_FH_ZUDISC = FH_TUERMODUL__SFHZ_MEC;
# 1180 "originaux/statemate.c"
		FH_DU__S_FH_FTZU = FH_TUERMODUL__SFHZ_ZENTRAL;
# 1181 "originaux/statemate.c"
		FH_DU__KL_50 = FH_TUERMODUL__KL_50;
# 1182 "originaux/statemate.c"
		FH_DU__BLOCK = FH_TUERMODUL__BLOCK;
# 1184 "originaux/statemate.c"
		FH_TUERMODUL__SFHA_MEC = FH_DU__S_FH_AUFDISC;
# 1185 "originaux/statemate.c"
		FH_TUERMODUL__SFHA_ZENTRAL = FH_DU__S_FH_FTAUF;
# 1186 "originaux/statemate.c"
		FH_TUERMODUL__SFHZ_MEC = FH_DU__S_FH_ZUDISC;
# 1187 "originaux/statemate.c"
		FH_TUERMODUL__SFHZ_ZENTRAL = FH_DU__S_FH_FTZU;
# 1189 "originaux/statemate.c"
		generic_EINKLEMMSCHUTZ_CTRL();
# 1191 "originaux/statemate.c"
		FH_DU__MFHA = FH_TUERMODUL__MFHA;
# 1192 "originaux/statemate.c"
		FH_DU__MFHZ = FH_TUERMODUL__MFHZ;
# 1193 "originaux/statemate.c"
		FH_DU__I_EIN = FH_TUERMODUL__I_EIN;
# 1194 "originaux/statemate.c"
		FH_DU__EKS_LEISTE_AKTIV = FH_TUERMODUL__EKS_LEISTE_AKTIV;
# 1195 "originaux/statemate.c"
		FH_DU__POSITION = FH_TUERMODUL__POSITION;
# 1196 "originaux/statemate.c"
		FH_DU__FT = FH_TUERMODUL__FT;
# 1197 "originaux/statemate.c"
		FH_DU__S_FH_AUFDISC = FH_TUERMODUL__SFHA_MEC;
# 1198 "originaux/statemate.c"
		FH_DU__S_FH_FTAUF = FH_TUERMODUL__SFHA_ZENTRAL;
# 1199 "originaux/statemate.c"
		FH_DU__S_FH_ZUDISC = FH_TUERMODUL__SFHZ_MEC;
# 1200 "originaux/statemate.c"
		FH_DU__S_FH_FTZU = FH_TUERMODUL__SFHZ_ZENTRAL;
# 1201 "originaux/statemate.c"
		FH_DU__KL_50 = FH_TUERMODUL__KL_50;
# 1202 "originaux/statemate.c"
		FH_DU__BLOCK = FH_TUERMODUL__BLOCK;
# 1204 "originaux/statemate.c"
		FH_TUERMODUL__SFHA_MEC = FH_DU__S_FH_AUFDISC;
# 1205 "originaux/statemate.c"
		FH_TUERMODUL__SFHA_ZENTRAL = FH_DU__S_FH_FTAUF;
# 1206 "originaux/statemate.c"
		FH_TUERMODUL__SFHZ_MEC = FH_DU__S_FH_ZUDISC;
# 1207 "originaux/statemate.c"
		FH_TUERMODUL__SFHZ_ZENTRAL = FH_DU__S_FH_FTZU;
# 1209 "originaux/statemate.c"
		generic_BLOCK_ERKENNUNG_CTRL();
# 1211 "originaux/statemate.c"
		FH_DU__MFHA = FH_TUERMODUL__MFHA;
# 1212 "originaux/statemate.c"
		FH_DU__MFHZ = FH_TUERMODUL__MFHZ;
# 1213 "originaux/statemate.c"
		FH_DU__I_EIN = FH_TUERMODUL__I_EIN;
# 1214 "originaux/statemate.c"
		FH_DU__EKS_LEISTE_AKTIV = FH_TUERMODUL__EKS_LEISTE_AKTIV;
# 1215 "originaux/statemate.c"
		FH_DU__POSITION = FH_TUERMODUL__POSITION;
# 1216 "originaux/statemate.c"
		FH_DU__FT = FH_TUERMODUL__FT;
# 1217 "originaux/statemate.c"
		FH_DU__S_FH_AUFDISC = FH_TUERMODUL__SFHA_MEC;
# 1218 "originaux/statemate.c"
		FH_DU__S_FH_FTAUF = FH_TUERMODUL__SFHA_ZENTRAL;
# 1219 "originaux/statemate.c"
		FH_DU__S_FH_ZUDISC = FH_TUERMODUL__SFHZ_MEC;
# 1220 "originaux/statemate.c"
		FH_DU__S_FH_FTZU = FH_TUERMODUL__SFHZ_ZENTRAL;
# 1221 "originaux/statemate.c"
		FH_DU__KL_50 = FH_TUERMODUL__KL_50;
# 1222 "originaux/statemate.c"
		FH_DU__BLOCK = FH_TUERMODUL__BLOCK;
# 1224 "originaux/statemate.c"
		Bitlist[11] = Bitlist[10];
# 1225 "originaux/statemate.c"
		Bitlist[14] = Bitlist[13];
# 1226 "originaux/statemate.c"
		Bitlist[17] = Bitlist[16];
# 1227 "originaux/statemate.c"
		Bitlist[20] = Bitlist[19];
# 1228 "originaux/statemate.c"
		FH_TUERMODUL_CTRL__N_old = FH_TUERMODUL_CTRL__N;
# 1229 "originaux/statemate.c"
		FH_TUERMODUL__I_EIN_old = FH_TUERMODUL__I_EIN;
# 1230 "originaux/statemate.c"
		FH_DU__MFH = FH_DU__MFH_copy;
# 1231 "originaux/statemate.c"
		FH_DU__I_EIN_old = FH_DU__I_EIN;
# 1232 "originaux/statemate.c"
		BLOCK_ERKENNUNG_CTRL__N_old = BLOCK_ERKENNUNG_CTRL__N;
# 1233 "originaux/statemate.c"
		FH_TUERMODUL__SFHZ_ZENTRAL_old = FH_TUERMODUL__SFHZ_ZENTRAL;
# 1234 "originaux/statemate.c"
		FH_TUERMODUL__SFHZ_MEC_old = FH_TUERMODUL__SFHZ_MEC;
# 1235 "originaux/statemate.c"
		FH_TUERMODUL__SFHA_ZENTRAL_old = FH_TUERMODUL__SFHA_ZENTRAL;
# 1236 "originaux/statemate.c"
		FH_TUERMODUL__SFHA_MEC_old = FH_TUERMODUL__SFHA_MEC;
# 1237 "originaux/statemate.c"
		FH_TUERMODUL__BLOCK = FH_TUERMODUL__BLOCK_copy;
# 1238 "originaux/statemate.c"
		FH_TUERMODUL__BLOCK_old = FH_TUERMODUL__BLOCK;
# 1239 "originaux/statemate.c"
		FH_TUERMODUL__SFHZ = FH_TUERMODUL__SFHZ_copy;
# 1240 "originaux/statemate.c"
		FH_TUERMODUL__SFHZ_old = FH_TUERMODUL__SFHZ;
# 1241 "originaux/statemate.c"
		FH_TUERMODUL__SFHA = FH_TUERMODUL__SFHA_copy;
# 1242 "originaux/statemate.c"
		FH_TUERMODUL__SFHA_old = FH_TUERMODUL__SFHA;
# 1243 "originaux/statemate.c"
		FH_TUERMODUL__MFHZ = FH_TUERMODUL__MFHZ_copy;
# 1244 "originaux/statemate.c"
		FH_TUERMODUL__MFHZ_old = FH_TUERMODUL__MFHZ;
# 1245 "originaux/statemate.c"
		FH_TUERMODUL__MFHA = FH_TUERMODUL__MFHA_copy;
# 1246 "originaux/statemate.c"
		FH_TUERMODUL__MFHA_old = FH_TUERMODUL__MFHA;
# 1247 "originaux/statemate.c"
		FH_TUERMODUL__EKS_LEISTE_AKTIV_old =
			FH_TUERMODUL__EKS_LEISTE_AKTIV;
# 1248 "originaux/statemate.c"
		FH_DU__EKS_LEISTE_AKTIV_old = FH_DU__EKS_LEISTE_AKTIV;
# 1249 "originaux/statemate.c"
		FH_DU__S_FH_TMBFAUFCAN_old = FH_DU__S_FH_TMBFAUFCAN;
# 1250 "originaux/statemate.c"
		FH_DU__S_FH_TMBFZUCAN_old = FH_DU__S_FH_TMBFZUCAN;
# 1251 "originaux/statemate.c"
		FH_DU__S_FH_TMBFZUDISC_old = FH_DU__S_FH_TMBFZUDISC;
# 1252 "originaux/statemate.c"
		FH_DU__S_FH_TMBFAUFDISC_old = FH_DU__S_FH_TMBFAUFDISC;
# 1253 "originaux/statemate.c"
		FH_DU__BLOCK = FH_DU__BLOCK_copy;
# 1254 "originaux/statemate.c"
		FH_DU__BLOCK_old = FH_DU__BLOCK;
# 1255 "originaux/statemate.c"
		FH_DU__MFHZ = FH_DU__MFHZ_copy;
# 1256 "originaux/statemate.c"
		FH_DU__MFHZ_old = FH_DU__MFHZ;
# 1257 "originaux/statemate.c"
		FH_DU__MFHA = FH_DU__MFHA_copy;
# 1258 "originaux/statemate.c"
		FH_DU__MFHA_old = FH_DU__MFHA;
	}
}

int main(void )
{
# 1268 "originaux/statemate.c"
	init();
# 1269 "originaux/statemate.c"
	interface();
# 1270 "originaux/statemate.c"
	FH_DU();
# 1272 "originaux/statemate.c"
	return 0;
}

