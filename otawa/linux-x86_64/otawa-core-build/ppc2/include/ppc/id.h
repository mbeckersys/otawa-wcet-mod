/* Generated by gep (119/02/26 23:30:56) copyright (c) 2008 IRIT - UPS */
#ifndef GLISS_PPC_INCLUDE_PPC_ID_H
#define GLISS_PPC_INCLUDE_PPC_ID_H

#define PPC_INSTRUCTIONS_NB 537

/* (ppc_ident_t enumeration */
typedef enum ppc_ident_t {
	PPC_UNKNOWN = 0,
	PPC_WRTEE_D = 1,
	PPC_WRTEE_RD = 2,
	PPC_TLBWE = 3,
	PPC_TLBSYNC = 4,
	PPC_TLBSX_RD__RD = 5,
	PPC_TLBRE = 6,
	PPC_TLBIVAX_RD__RD = 7,
	PPC_MSYNC = 8,
	PPC_MTDCR_D__RD = 9,
	PPC_MFDCR__RD__D = 10,
	PPC_MBAR_D = 11,
	PPC_ICBT_D__RD__RD = 12,
	PPC_XOR__RD_RD_RD = 13,
	PPC_XOR_RD_RD_RD = 14,
	PPC_ICBI_RD_RD = 15,
	PPC_DCBZ_RD_RD = 16,
	PPC_DCBTST_RD_RD = 17,
	PPC_DCBT_RD_RD = 18,
	PPC_DCBST_RD_RD = 19,
	PPC_DCBI_RD__RD = 20,
	PPC_DCBF_RD__RD = 21,
	PPC_DCBA_RD_RD = 22,
	PPC_TW_D_RD_RD = 23,
	PPC_MFCR_RD = 24,
	PPC_SUBFZEO__RD_RD = 25,
	PPC_SUBFZEO_RD_RD = 26,
	PPC_SUBFZE__RD_RD = 27,
	PPC_SUBFZE_RD_RD = 28,
	PPC_SUBFMEO__RD_RD = 29,
	PPC_SUBFMEO_RD_RD = 30,
	PPC_SUBFME__RD_RD = 31,
	PPC_SUBFME_RD_RD = 32,
	PPC_SUBFEO__RD_RD_RD = 33,
	PPC_SUBFEO_RD_RD_RD = 34,
	PPC_SUBFE__RD_RD_RD = 35,
	PPC_SUBFE_RD_RD_RD = 36,
	PPC_SUBFCO__RD_RD_RD = 37,
	PPC_SUBFCO_RD_RD_RD = 38,
	PPC_SUBFC__RD_RD_RD = 39,
	PPC_SUBFC_RD_RD_RD = 40,
	PPC_SUBFO__RD_RD_RD = 41,
	PPC_SUBFO_RD_RD_RD = 42,
	PPC_SUBF__RD_RD_RD = 43,
	PPC_SUBF_RD_RD_RD = 44,
	PPC_STWCX__RD_RD_RD = 45,
	PPC_STWBRX_RD_RD_RD = 46,
	PPC_STSWI_RD_RD_D = 47,
	PPC_STSWX_RD_RD_RD = 48,
	PPC_STHBRX_RD_RD_RD = 49,
	PPC_STWUX_RD_RD_RD = 50,
	PPC_STWX_RD_RD_RD = 51,
	PPC_STHUX_RD_RD_RD = 52,
	PPC_STHX_RD_RD_RD = 53,
	PPC_STBUX_RD_RD_RD = 54,
	PPC_STBX_RD_RD_RD = 55,
	PPC_SRW__RD_RD_RD = 56,
	PPC_SRW_RD_RD_RD = 57,
	PPC_SRAWI__RD_RD_D = 58,
	PPC_SRAWI_RD_RD_D = 59,
	PPC_SRAW__RD_RD_RD = 60,
	PPC_SRAW_RD_RD_RD = 61,
	PPC_SLW__RD_RD_RD = 62,
	PPC_SLW_RD_RD_RD = 63,
	PPC_ORC__RD_RD_RD = 64,
	PPC_ORC_RD_RD_RD = 65,
	PPC_OR__RD_RD_RD = 66,
	PPC_OR_RD_RD_RD = 67,
	PPC_MTSPR_D_RD = 68,
	PPC_MTMSR_RD = 69,
	PPC_MFSPR_RD_D = 70,
	PPC_MFMSR_RD = 71,
	PPC_NOR__RD_RD_RD = 72,
	PPC_NOR_RD_RD_RD = 73,
	PPC_NEGO__RD_RD = 74,
	PPC_NEGO_RD_RD = 75,
	PPC_NEG__RD_RD = 76,
	PPC_NEG_RD_RD = 77,
	PPC_NAND__RD_RD_RD = 78,
	PPC_NAND_RD_RD_RD = 79,
	PPC_MULLWO__RD_RD_RD = 80,
	PPC_MULLWO_RD_RD_RD = 81,
	PPC_MULLW__RD_RD_RD = 82,
	PPC_MULLW_RD_RD_RD = 83,
	PPC_MULHWU__RD_RD_RD = 84,
	PPC_MULHWU_RD_RD_RD = 85,
	PPC_MULHW__RD_RD_RD = 86,
	PPC_MULHW_RD_RD_RD = 87,
	PPC_MTSPR_S_RD = 88,
	PPC_MCRXR_CRFD = 89,
	PPC_MTCRF_D_RD = 90,
	PPC_MFSPR_RD_S = 91,
	PPC_LWARX_RD_RD_RD = 92,
	PPC_LWBRX_RD_RD_RD = 93,
	PPC_LWZUX_RD_RD_RD = 94,
	PPC_LWZX_RD_RD_RD = 95,
	PPC_LHZUX_RD_RD_RD = 96,
	PPC_LHZX_RD_RD_RD = 97,
	PPC_LHBRX_RD_RD_RD = 98,
	PPC_LHAUX_RD_RD_RD = 99,
	PPC_LHAX_RD_RD_RD = 100,
	PPC_LBZUX_RD_RD_RD = 101,
	PPC_LBZX_RD_RD_RD = 102,
	PPC_ISEL_RD__RD__R5B__D = 103,
	PPC_EXTSH__RD_RD = 104,
	PPC_EXTSH_RD_RD = 105,
	PPC_EXTSB__RD_RD = 106,
	PPC_EXTSB_RD_RD = 107,
	PPC_EQV__RD_RD_RD = 108,
	PPC_EQV_RD_RD_RD = 109,
	PPC_DIVWUO__RD_RD_RD = 110,
	PPC_DIVWUO_RD_RD_RD = 111,
	PPC_DIVWU__RD_RD_RD = 112,
	PPC_DIVWU_RD_RD_RD = 113,
	PPC_DIVWO__RD_RD_RD = 114,
	PPC_DIVWO_RD_RD_RD = 115,
	PPC_DIVW__RD_RD_RD = 116,
	PPC_DIVW_RD_RD_RD = 117,
	PPC_CNTLZW__RD__RD = 118,
	PPC_CNTLZW_RD__RD = 119,
	PPC_CMPL_D_D_RD_RD = 120,
	PPC_CMP_D_D_RD_RD = 121,
	PPC_ANDC__RD_RD_RD = 122,
	PPC_ANDC_RD_RD_RD = 123,
	PPC_AND__RD_RD_RD = 124,
	PPC_AND_RD_RD_RD = 125,
	PPC_ADDZEO__RD_RD = 126,
	PPC_ADDZEO_RD_RD = 127,
	PPC_ADDZE__RD_RD = 128,
	PPC_ADDZE_RD_RD = 129,
	PPC_ADDMEO__RD_RD = 130,
	PPC_ADDMEO_RD_RD = 131,
	PPC_ADDME__RD_RD = 132,
	PPC_ADDME_RD_RD = 133,
	PPC_ADDEO__RD_RD_RD = 134,
	PPC_ADDEO_RD_RD_RD = 135,
	PPC_ADDE__RD_RD_RD = 136,
	PPC_ADDE_RD_RD_RD = 137,
	PPC_ADDCO__RD_RD_RD = 138,
	PPC_ADDCO_RD_RD_RD = 139,
	PPC_ADDC__RD_RD_RD = 140,
	PPC_ADDC_RD_RD_RD = 141,
	PPC_ADDSS_RD_RD_RD = 142,
	PPC_E_XORIS_RD__RD__X = 143,
	PPC_E_SUBFICS_RD__RD__D = 144,
	PPC_E_STMW_RD__D_LP_RD_RP_ = 145,
	PPC_E_STWU_RD__D_LP_RD_RP_ = 146,
	PPC_E_STW_RD__D_LP_RD_RP_ = 147,
	PPC_E_STHU_RD__D_LP_RD_RP_ = 148,
	PPC_E_STH_RD__D_LP_RD_RP_ = 149,
	PPC_E_STBU_RD__D_LP_RD_RP_ = 150,
	PPC_E_STB_RD__D_LP_RD_RP_ = 151,
	PPC_E_SRWIS_RD__RD__D = 152,
	PPC_E_SLWIS_RD__RD__D = 153,
	PPC_E_RLWINM_RD__RD__D__D__D = 154,
	PPC_E_RLWIMI_RD__RD__D__D__D = 155,
	PPC_E_RLWIS_RD__RD__D = 156,
	PPC_E_RLWS_RD__RD__RD = 157,
	PPC_E_ORIS_RD__RD__X = 158,
	PPC_E_OR2IS_RD__X = 159,
	PPC_E_OR2I_RD__X = 160,
	PPC_E_MULL2I_RD__D = 161,
	PPC_E_MULLI_RD__RD__D = 162,
	PPC_E_MCRF_CRD__CRD = 163,
	PPC_E_LMW_RD__D_LP_RD_RP_ = 164,
	PPC_E_LWZU_RD__D_LP_RD_RP_ = 165,
	PPC_E_LWZ_RD__D_LP_RD_RP_ = 166,
	PPC_E_LIS_RD__X = 167,
	PPC_E_LI_RD__X = 168,
	PPC_E_LHZU_RD__D_LP_RD_RP_ = 169,
	PPC_E_LHZ_RD__D_LP_RD_RP_ = 170,
	PPC_E_LHAU_RD__D_LP_RD_RP_ = 171,
	PPC_E_LHA_RD__D_LP_RD_RP_ = 172,
	PPC_E_LBZU_RD__D_LP_RD_RP_ = 173,
	PPC_E_LBZ_RD__D_LP_RD_RP_ = 174,
	PPC_E_CRXOR_CRBD__CRBD__CRBD = 175,
	PPC_E_CRORC_CRBD__CRBD__CRBD = 176,
	PPC_E_CROR_CRBD__CRBD__CRBD = 177,
	PPC_E_CRNOR_CRBD__CRBD__CRBD = 178,
	PPC_E_CRNAND_CRBD__CRBD__CRBD = 179,
	PPC_E_CREQV_CRBD__CRBD__CRBD = 180,
	PPC_E_CRANDC_CRBD__CRBD__CRBD = 181,
	PPC_E_CRAND_CRBD__CRBD__CRBD = 182,
	PPC_E_CMPLI_CRD__RD__D = 183,
	PPC_E_CMPL16I_RD__D = 184,
	PPC_E_CMPI_CRD__RD__D = 185,
	PPC_E_CMPHL16I_RD__D = 186,
	PPC_E_CMPHL_CRD__RD__RD = 187,
	PPC_E_CMPH16I_RD__D = 188,
	PPC_E_CMPH_CRD__RD__RD = 189,
	PPC_E_CMP16I_RD__D = 190,
	PPC_E_BCS_X__X_08X = 191,
	PPC_E_BS_08X = 192,
	PPC_E_ADDICS_RD__RD__D = 193,
	PPC_E_AND2IS__RD__D = 194,
	PPC_E_AND2I__RD__D = 195,
	PPC_E_ADDICS_RD__RD__D_0 = 196,
	PPC_E_ADDIS_RD__RD__D = 197,
	PPC_E_ADD2IS_RD__D = 198,
	PPC_E_ADD2I__RD__D = 199,
	PPC_E_ADD16I_RD__RD__D = 200,
	PPC_SE_SUBIS_RD__D = 201,
	PPC_SE_SUBF_RD__RD = 202,
	PPC_SE_SUB_RD__RD = 203,
	PPC_SE_STW_RD__D_LP_RD_RP_ = 204,
	PPC_SE_STH_RD__D_LP_RD_RP_ = 205,
	PPC_SE_STB_RD__D_LP_RD_RP_ = 206,
	PPC_SE_SRWI_RD__D = 207,
	PPC_SE_SRW_RD__RD = 208,
	PPC_SE_SRAWI_RD__D = 209,
	PPC_SE_SRAW_RD__RD = 210,
	PPC_SE_SLWI_RD__D = 211,
	PPC_SE_SLW_RD__RD = 212,
	PPC_SE_SC = 213,
	PPC_SE_RFI = 214,
	PPC_SE_RFDI = 215,
	PPC_SE_RFCI = 216,
	PPC_SE_OR_RD__RD = 217,
	PPC_SE_NOT_RD = 218,
	PPC_SE_NEG_RD = 219,
	PPC_SE_MULLW_RD__RD = 220,
	PPC_SE_MTLR_RD = 221,
	PPC_SE_MTCTR_RD = 222,
	PPC_SE_MTAR_RD__RD = 223,
	PPC_SE_MR_RD__RD = 224,
	PPC_SE_MFLR_RD = 225,
	PPC_SE_MFCTR_RD = 226,
	PPC_SE_MFAR_RD__RD = 227,
	PPC_SE_LI_RD__D = 228,
	PPC_SE_LWZ_RD__D_LP_RD_RP_ = 229,
	PPC_SE_LHZ_RD__D_LP_RD_RP_ = 230,
	PPC_SE_LBZ_RD__D_LP_RD_RP_ = 231,
	PPC_SE_EXTZH_RD = 232,
	PPC_SE_EXTZB_RD = 233,
	PPC_SE_EXTSH_RD = 234,
	PPC_SE_EXTSB_RD = 235,
	PPC_SE_CMPLI_RD__D = 236,
	PPC_SE_CMPL_RD__RD = 237,
	PPC_SE_CMPI_RD__D = 238,
	PPC_SE_CMPHL_RD__RD = 239,
	PPC_SE_CMPH_RD__RD = 240,
	PPC_SE_CMP_RD__RD = 241,
	PPC_SE_BTSTI_RD__D = 242,
	PPC_SE_BSETI_RD__D = 243,
	PPC_SE_BMSKI_RD__D = 244,
	PPC_BLRS = 245,
	PPC_BGENI_RD__D = 246,
	PPC_SE_BCTRS = 247,
	PPC_BCLRI_RD__D = 248,
	PPC_SE_BC_X__X__08X = 249,
	PPC_SE_BS_08X = 250,
	PPC_SE_ANDC_RD__RD = 251,
	PPC_SE_ANDI_RD__D = 252,
	PPC_E_ANDS_RD__RD_ = 253,
	PPC_SE_ADDI_RD__D = 254,
	PPC_SE_ADD_RD_RD = 255,
	PPC_MFAPIDI_RD__RD = 256,
	PPC_TLBSYNC_0 = 257,
	PPC_TLBIE_RD = 258,
	PPC_TLBIA = 259,
	PPC_RFI = 260,
	PPC_MTSRIN_RD_RD = 261,
	PPC_MTSR_D_RD = 262,
	PPC_MFSRIN_RD_RD = 263,
	PPC_MFSR_RD_D = 264,
	PPC_MTSPR_D_RD_0 = 265,
	PPC_MTMSR_RD_0 = 266,
	PPC_MFSPR_RD_D_0 = 267,
	PPC_MFMSR_RD_0 = 268,
	PPC_MFTB_RD_D = 269,
	PPC_ISYNC = 270,
	PPC_EIEIO = 271,
	PPC_ECOWX_RD_RD_RD = 272,
	PPC_ECIWX_RD_RD_RD = 273,
	PPC_ICBI_RD_RD_0 = 274,
	PPC_DCBZ_RD_RD_0 = 275,
	PPC_DCBTST_RD_RD_0 = 276,
	PPC_DCBT_RD_RD_0 = 277,
	PPC_DCBST_RD_RD_0 = 278,
	PPC_DCBI_RD__RD_0 = 279,
	PPC_DCBF_RD__RD_0 = 280,
	PPC_DCBA_RD_RD_0 = 281,
	PPC_MTFSFI__CRFD_D = 282,
	PPC_MTFSFI_CRFD_D = 283,
	PPC_MTFSF__D_FRD = 284,
	PPC_MTFSF_D_FRD = 285,
	PPC_MTFSB1__CRBD = 286,
	PPC_MTFSB1_CRBD = 287,
	PPC_MTFSB0__CRBD = 288,
	PPC_MTFSB0_CRBD = 289,
	PPC_MFFS__FRD = 290,
	PPC_MFFS_FRD = 291,
	PPC_MCRFS_CRFD_CRFD = 292,
	PPC_FCTIWZ__FRD_FRD = 293,
	PPC_FCTIWZ_FRD_FRD = 294,
	PPC_FCTIW__FRD_FRD = 295,
	PPC_FCTIW_FRD_FRD = 296,
	PPC_FRSP__FRD_FRD = 297,
	PPC_FRSP_FRD_FRD = 298,
	PPC_FNABS__FRD_FRD = 299,
	PPC_FNABS_FRD_FRD = 300,
	PPC_FABS__FRD_FRD = 301,
	PPC_FABS_FRD_FRD = 302,
	PPC_FNEG__FRD_FRD = 303,
	PPC_FNEG_FRD_FRD = 304,
	PPC_FMR__FRD_FRD = 305,
	PPC_FMR_FRD_FRD = 306,
	PPC_FCMPU_CRFD_FRD_FRD = 307,
	PPC_FCMPO_CRFD_FRD_FRD = 308,
	PPC_FNMSUBS__FRD_FRD_FRD_FRD = 309,
	PPC_FNMSUBS_FRD_FRD_FRD_FRD = 310,
	PPC_FNMSUB__FRD_FRD_FRD_FRD = 311,
	PPC_FNMSUB_FRD_FRD_FRD_FRD = 312,
	PPC_FMSUBS__FRD_FRD_FRD_FRD = 313,
	PPC_FMSUBS_FRD_FRD_FRD_FRD = 314,
	PPC_FMSUB__FRD_FRD_FRD_FRD = 315,
	PPC_FMSUB_FRD_FRD_FRD_FRD = 316,
	PPC_FNMADDS__FRD_FRD_FRD_FRD = 317,
	PPC_FNMADDS_FRD_FRD_FRD_FRD = 318,
	PPC_FNMADD__FRD_FRD_FRD_FRD = 319,
	PPC_FNMADD_FRD_FRD_FRD_FRD = 320,
	PPC_FMADDS__FRD_FRD_FRD_FRD = 321,
	PPC_FMADDS_FRD_FRD_FRD_FRD = 322,
	PPC_FMADD__FRD_FRD_FRD_FRD = 323,
	PPC_FMADD_FRD_FRD_FRD_FRD = 324,
	PPC_FDIVS__FRD_FRD_FRD = 325,
	PPC_FDIVS_FRD_FRD_FRD = 326,
	PPC_FDIV__FRD_FRD_FRD = 327,
	PPC_FDIV_FRD_FRD_FRD = 328,
	PPC_FMULS__FRD_FRD_FRD = 329,
	PPC_FMULS_FRD_FRD_FRD = 330,
	PPC_FMUL__FRD_FRD_FRD = 331,
	PPC_FMUL_FRD_FRD_FRD = 332,
	PPC_FSUBS__FRD_FRD_FRD = 333,
	PPC_FSUBS_FRD_FRD_FRD = 334,
	PPC_FSUB__FRD_FRD_FRD = 335,
	PPC_FSUB_FRD_FRD_FRD = 336,
	PPC_FADDS__FRD_FRD_FRD = 337,
	PPC_FADDS_FRD_FRD_FRD = 338,
	PPC_FADD__FRD_FRD_FRD = 339,
	PPC_FADD_FRD_FRD_FRD = 340,
	PPC_STFSUX_FRD_RD_RD = 341,
	PPC_STFSU_FRD_D_LP_RD_RP_ = 342,
	PPC_STFSX_FRD_RD_RD = 343,
	PPC_STFS_FRD_D_LP_RD_RP_ = 344,
	PPC_STFDUX_FRD_RD_RD = 345,
	PPC_STFDU_FRD_D_LP_RD_RP_ = 346,
	PPC_STFDX_FRD_RD_RD = 347,
	PPC_STFD_FRD_D_LP_RD_RP_ = 348,
	PPC_LFSUX_FRD_RD_RD = 349,
	PPC_LFSU_FRD_D_LP_RD_RP_ = 350,
	PPC_LFSX_FRD_RD_RD = 351,
	PPC_LFS_FRD_D_LP_RD_RP_ = 352,
	PPC_LFDUX_FRD_RD_RD = 353,
	PPC_LFDU_FRD_D_LP_RD_RP_ = 354,
	PPC_LFDX_FRD_RD_RD = 355,
	PPC_LFD_FRD_D_LP_RD_RP_ = 356,
	PPC_TWI_D_RD_D = 357,
	PPC_TW_D_RD_RD_0 = 358,
	PPC_SYNC = 359,
	PPC_STWCX__RD_RD_RD_0 = 360,
	PPC_LWARX_RD_RD_RD_0 = 361,
	PPC_MFSPR_RD_S_0 = 362,
	PPC_MTSPR_S_RD_0 = 363,
	PPC_MFCR_RD_0 = 364,
	PPC_ISEL_RD__RD__R5B__D_0 = 365,
	PPC_MCRXR_CRFD_0 = 366,
	PPC_MTCRF_D_RD_0 = 367,
	PPC_MCRF_CRFD_CRFD = 368,
	PPC_CRORC_CRBD_CRBD_CRBD = 369,
	PPC_CRANDC_CRBD_CRBD_CRBD = 370,
	PPC_CREQV_CRBD_CRBD_CRBD = 371,
	PPC_CRNOR_CRBD_CRBD_CRBD = 372,
	PPC_CRNAND_CRBD_CRBD_CRBD = 373,
	PPC_CRXOR_CRBD_CRBD_CRBD = 374,
	PPC_CROR_CRBD_CRBD_CRBD = 375,
	PPC_CRAND_CRBD_CRBD_CRBD = 376,
	PPC_SRAW__RD_RD_RD_0 = 377,
	PPC_SRAW_RD_RD_RD_0 = 378,
	PPC_SRAWI__RD_RD_D_0 = 379,
	PPC_SRAWI_RD_RD_D_0 = 380,
	PPC_SRW__RD_RD_RD_0 = 381,
	PPC_SRW_RD_RD_RD_0 = 382,
	PPC_SLW__RD_RD_RD_0 = 383,
	PPC_SLW_RD_RD_RD_0 = 384,
	PPC_RLWIMI__RD_RD_D_D_D = 385,
	PPC_RLWIMI_RD_RD_D_D_D = 386,
	PPC_RLWNM__RD_RD_RD_D_D = 387,
	PPC_RLWNM_RD_RD_RD_D_D = 388,
	PPC_RLWINM__RD_RD_D_D_D = 389,
	PPC_RLWINM_RD_RD_D_D_D = 390,
	PPC_CNTLZW__RD__RD_0 = 391,
	PPC_CNTLZW_RD__RD_0 = 392,
	PPC_EXTSH__RD_RD_0 = 393,
	PPC_EXTSH_RD_RD_0 = 394,
	PPC_EXTSB__RD_RD_0 = 395,
	PPC_EXTSB_RD_RD_0 = 396,
	PPC_EQV__RD_RD_RD_0 = 397,
	PPC_EQV_RD_RD_RD_0 = 398,
	PPC_NAND__RD_RD_RD_0 = 399,
	PPC_NAND_RD_RD_RD_0 = 400,
	PPC_NOR__RD_RD_RD_0 = 401,
	PPC_NOR_RD_RD_RD_0 = 402,
	PPC_XORIS_RD_RD_D = 403,
	PPC_XORI_RD_RD_D = 404,
	PPC_XOR__RD_RD_RD_0 = 405,
	PPC_XOR_RD_RD_RD_0 = 406,
	PPC_ANDC__RD_RD_RD_0 = 407,
	PPC_ANDC_RD_RD_RD_0 = 408,
	PPC_ANDIS__RD_RD_D = 409,
	PPC_ANDI__RD_RD_D = 410,
	PPC_AND__RD_RD_RD_0 = 411,
	PPC_AND_RD_RD_RD_0 = 412,
	PPC_ORC__RD_RD_RD_0 = 413,
	PPC_ORC_RD_RD_RD_0 = 414,
	PPC_ORIS_RD_RD_D = 415,
	PPC_ORI_RD_RD_D = 416,
	PPC_OR__RD_RD_RD_0 = 417,
	PPC_OR_RD_RD_RD_0 = 418,
	PPC_CMPL_D_D_RD_RD_0 = 419,
	PPC_CMPLI_D_D_RD_D = 420,
	PPC_CMP_D_D_RD_RD_0 = 421,
	PPC_CMPI_D_D_RD_D = 422,
	PPC_NEGO__RD_RD_0 = 423,
	PPC_NEGO_RD_RD_0 = 424,
	PPC_NEG__RD_RD_0 = 425,
	PPC_NEG_RD_RD_0 = 426,
	PPC_DIVWUO__RD_RD_RD_0 = 427,
	PPC_DIVWUO_RD_RD_RD_0 = 428,
	PPC_DIVWU__RD_RD_RD_0 = 429,
	PPC_DIVWU_RD_RD_RD_0 = 430,
	PPC_DIVWO__RD_RD_RD_0 = 431,
	PPC_DIVWO_RD_RD_RD_0 = 432,
	PPC_DIVW__RD_RD_RD_0 = 433,
	PPC_DIVW_RD_RD_RD_0 = 434,
	PPC_MULHWU__RD_RD_RD_0 = 435,
	PPC_MULHWU_RD_RD_RD_0 = 436,
	PPC_MULHW__RD_RD_RD_0 = 437,
	PPC_MULHW_RD_RD_RD_0 = 438,
	PPC_MULLI_RD_RD_D = 439,
	PPC_MULLWO__RD_RD_RD_0 = 440,
	PPC_MULLWO_RD_RD_RD_0 = 441,
	PPC_MULLW__RD_RD_RD_0 = 442,
	PPC_MULLW_RD_RD_RD_0 = 443,
	PPC_SUBFZEO__RD_RD_0 = 444,
	PPC_SUBFZEO_RD_RD_0 = 445,
	PPC_SUBFZE__RD_RD_0 = 446,
	PPC_SUBFZE_RD_RD_0 = 447,
	PPC_SUBFMEO__RD_RD_0 = 448,
	PPC_SUBFMEO_RD_RD_0 = 449,
	PPC_SUBFME__RD_RD_0 = 450,
	PPC_SUBFME_RD_RD_0 = 451,
	PPC_SUBFEO__RD_RD_RD_0 = 452,
	PPC_SUBFEO_RD_RD_RD_0 = 453,
	PPC_SUBFE__RD_RD_RD_0 = 454,
	PPC_SUBFE_RD_RD_RD_0 = 455,
	PPC_SUBFCO__RD_RD_RD_0 = 456,
	PPC_SUBFCO_RD_RD_RD_0 = 457,
	PPC_SUBFC__RD_RD_RD_0 = 458,
	PPC_SUBFC_RD_RD_RD_0 = 459,
	PPC_SUBFIC_RD_RD_D = 460,
	PPC_SUBFO__RD_RD_RD_0 = 461,
	PPC_SUBFO_RD_RD_RD_0 = 462,
	PPC_SUBF__RD_RD_RD_0 = 463,
	PPC_SUBF_RD_RD_RD_0 = 464,
	PPC_ADDZEO__RD_RD_0 = 465,
	PPC_ADDZEO_RD_RD_0 = 466,
	PPC_ADDZE__RD_RD_0 = 467,
	PPC_ADDZE_RD_RD_0 = 468,
	PPC_ADDMEO__RD_RD_0 = 469,
	PPC_ADDMEO_RD_RD_0 = 470,
	PPC_ADDME__RD_RD_0 = 471,
	PPC_ADDME_RD_RD_0 = 472,
	PPC_ADDEO__RD_RD_RD_0 = 473,
	PPC_ADDEO_RD_RD_RD_0 = 474,
	PPC_ADDE__RD_RD_RD_0 = 475,
	PPC_ADDE_RD_RD_RD_0 = 476,
	PPC_ADDCO__RD_RD_RD_0 = 477,
	PPC_ADDCO_RD_RD_RD_0 = 478,
	PPC_ADDC__RD_RD_RD_0 = 479,
	PPC_ADDC_RD_RD_RD_0 = 480,
	PPC_ADDIC__RD_RD_D = 481,
	PPC_ADDIC_RD_RD_D = 482,
	PPC_ADDIS_RD_RD_D = 483,
	PPC_ADDI_RD_RD_D = 484,
	PPC_ADDSS_RD_RD_RD_0 = 485,
	PPC_STSWX_RD_RD_RD_0 = 486,
	PPC_STSWI_RD_RD_D_0 = 487,
	PPC_STMW_RD_D_LP_RD_RP_ = 488,
	PPC_STWBRX_RD_RD_RD_0 = 489,
	PPC_STHBRX_RD_RD_RD_0 = 490,
	PPC_STWUX_RD_RD_RD_0 = 491,
	PPC_STWU_RD_D_LP_RD_RP_ = 492,
	PPC_STWX_RD_RD_RD_0 = 493,
	PPC_STW_RD_D_LP_RD_RP_ = 494,
	PPC_STHUX_RD_RD_RD_0 = 495,
	PPC_STHU_RD_D_LP_RD_RP_ = 496,
	PPC_STHX_RD_RD_RD_0 = 497,
	PPC_STH_RD_D_LP_RD_RP_ = 498,
	PPC_STBUX_RD_RD_RD_0 = 499,
	PPC_STBU_RD_D_LP_RD_RP_ = 500,
	PPC_STBX_RD_RD_RD_0 = 501,
	PPC_STB_RD_D_LP_RD_RP_ = 502,
	PPC_LSWX_RD_RD_RD = 503,
	PPC_LSWI_RD_RD_D = 504,
	PPC_LMW_RD_D_LP_RD_RP_ = 505,
	PPC_LWBRX_RD_RD_RD_0 = 506,
	PPC_LHBRX_RD_RD_RD_0 = 507,
	PPC_LWZUX_RD_RD_RD_0 = 508,
	PPC_LWZU_RD_D_LP_RD_RP_ = 509,
	PPC_LWZX_RD_RD_RD_0 = 510,
	PPC_LWZ_RD_D_LP_RD_RP_ = 511,
	PPC_LHAUX_RD_RD_RD_0 = 512,
	PPC_LHAU_RD_D_LP_RD_RP_ = 513,
	PPC_LHAX_RD_RD_RD_0 = 514,
	PPC_LHA_RD_D_LP_RD_RP_ = 515,
	PPC_LHZUX_RD_RD_RD_0 = 516,
	PPC_LHZU_RD_D_LP_RD_RP_ = 517,
	PPC_LHZX_RD_RD_RD_0 = 518,
	PPC_LHZ_RD_D_LP_RD_RP_ = 519,
	PPC_LBZUX_RD_RD_RD_0 = 520,
	PPC_LBZU_RD_D_LP_RD_RP_ = 521,
	PPC_LBZX_RD_RD_RD_0 = 522,
	PPC_LBZ_RD_D_LP_RD_RP_ = 523,
	PPC_SC = 524,
	PPC_BCLRL_D_D = 525,
	PPC_BCLR_D_D = 526,
	PPC_BCCTRL_D_D = 527,
	PPC_BCCTR_D_D = 528,
	PPC_BCLA_D_D_D = 529,
	PPC_BCL_D_D_D = 530,
	PPC_BCA_D_D_D = 531,
	PPC_BC_D_D_D = 532,
	PPC_BLA_D = 533,
	PPC_BL_0X08X = 534,
	PPC_BA_D = 535,
	PPC_B_D = 536,
	PPC_TOP
} ppc_ident_t;

#endif /* GLISS_PPC_INCLUDE_PPC_ID_H */
