// SysExEventProt.h: Schnittstelle für die Klasse SysExEventProt.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSEXEVENTPROT_H__19FB00C1_148E_11D6_9348_0080AD7896CF__INCLUDED_)
#define AFX_SYSEXEVENTPROT_H__19FB00C1_148E_11D6_9348_0080AD7896CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyArrays.h"
#include "HPMF_Interface.h"


typedef struct act_effect_type {int msb; int lsb;} ACT_EFFECT_TYPE;

typedef struct effect_type_elem {int msb; int lsb; char type[64]; int epl; } EFFECT_TYPE_ELEM;
typedef struct effect_param_elem {char name[32];int data_list;} EFFECT_PARAM_ELEM;
typedef struct effect_data_lists_elem {const CString *list; int len;} EFFECT_DATA_LISTS_ELEM;

// class SysExEventProt : public MIDIEvent
class SysExEventProt
{
#define NO_DSP_BLOCKS     32

#define EFFECT_DATA_0_LEN 201
#define EFFECT_DATA_1_LEN 128
#define EFFECT_DATA_2_LEN 128
#define EFFECT_DATA_3_LEN 61
#define EFFECT_DATA_4_LEN 70
#define EFFECT_DATA_5_LEN 128
#define EFFECT_DATA_6_LEN 45
#define EFFECT_DATA_7_LEN 128
#define EFFECT_DATA_8_LEN 20
#define EFFECT_DATA_9_LEN 16
#define EFFECT_DATA_10_LEN 8
#define EFFECT_DATA_11_LEN 105
#define EFFECT_DATA_12_LEN 68
#define EFFECT_DATA_13_LEN 128
#define EFFECT_DATA_14_LEN 78
#define EFFECT_DATA_15_LEN 128
#define EFFECT_DATA_16_LEN 128
#define EFFECT_DATA_17_LEN 128
#define EFFECT_DATA_18_LEN 128
#define EFFECT_DATA_19_LEN 128
#define EFFECT_DATA_20_LEN 128
#define EFFECT_DATA_21_LEN 128
#define EFFECT_DATA_22_LEN 128
#define EFFECT_DATA_23_LEN 140
#define EFFECT_DATA_24_LEN 17
#define EFFECT_DATA_25_LEN 128
#define EFFECT_DATA_26_LEN 11
#define EFFECT_DATA_27_LEN 128
#define EFFECT_DATA_28_LEN 128
#define EFFECT_DATA_29_LEN 128
#define EFFECT_DATA_30_LEN 128
#define EFFECT_DATA_31_LEN 121
#define EFFECT_DATA_32_LEN 2
#define EFFECT_DATA_33_LEN 3
#define EFFECT_DATA_34_LEN 125
#define EFFECT_DATA_35_LEN 7
#define EFFECT_DATA_36_LEN 6
#define EFFECT_DATA_37_LEN 6
#define EFFECT_DATA_38_LEN 2
#define EFFECT_DATA_39_LEN 8
#define EFFECT_DATA_40_LEN 3
#define EFFECT_DATA_41_LEN 128
#define EFFECT_DATA_42_LEN 128
#define EFFECT_DATA_43_LEN 128
#define EFFECT_DATA_44_LEN 61
#define EFFECT_DATA_45_LEN 128
#define EFFECT_DATA_46_LEN 2
#define EFFECT_DATA_47_LEN 5
#define EFFECT_DATA_48_LEN 43
#define EFFECT_DATA_49_LEN 6
#define EFFECT_DATA_50_LEN 1 // dummy list effect_data_50
#define EFFECT_DATA_51_LEN 2
#define EFFECT_DATA_52_LEN 5 // ?
#define EFFECT_DATA_53_LEN 6
#define EFFECT_DATA_54_LEN 2
#define EFFECT_DATA_55_LEN 128
#define EFFECT_DATA_56_LEN 128
#define EFFECT_DATA_57_LEN 70
#define EFFECT_DATA_58_LEN 128
#define EFFECT_DATA_59_LEN 3
#define EFFECT_DATA_60_LEN 201
#define EFFECT_DATA_61_LEN 13
#define EFFECT_DATA_62_LEN 6
#define EFFECT_DATA_63_LEN 2
#define EFFECT_DATA_64_LEN 2
#define EFFECT_DATA_65_LEN 10

#define EFFECT_PARAM_LISTS_LEN 146


public:
	SysExEventProt();
	virtual ~SysExEventProt();
	CString sysex_string(unsigned char* data, int length);
	HPMF_Interface * hpmfi;
private:
	void analyze_sysex();
	void sysex_non_yamaha();
	void analyze_sysex_yamaha();
	void prot_fmt_text(char* fmt,...);
	void not_documented();
	void undocumented_type();
	void unknown_type();
	void xg_par_change();
	void xg_EFFECT1();
	void xg_EFFECT2();
	void reverb_effect_type();
	void reverb_effect_type_effectfile();
	void chorus_effect_type();
	void chorus_effect_type_effectfile(); 
	void dsp_effect_type();
	void dsp_effect_type_effectfile();  
	CString reverb_data_text();
	CString reverb_data_text_effectfile();
	CString chorus_data_text();
	CString chorus_data_text_effectfile();
	CString dsp_data_text();
	CString dsp_data_text_effectfile();
	void clavinova();
	void style();
	unsigned char eventstr[512];
	int slength;
	int AdrH;
	int AdrM;
	int AdrL;
	int DataMSB;
	int DataLSB;

	ACT_EFFECT_TYPE act_reverb_type;
	int act_reverb_param_list_no;
	ACT_EFFECT_TYPE act_chorus_type;
	int act_chorus_param_list_no;
	ACT_EFFECT_TYPE act_variation_type;
	int act_variation_param_list_no;
	ACT_EFFECT_TYPE act_dsp_type[NO_DSP_BLOCKS];
	int act_dsp_param_list_no[NO_DSP_BLOCKS];

	// Constant Data Lists

	static const CString manufactor[];

	static const EFFECT_TYPE_ELEM reverb_effect_type_list[];
	static const EFFECT_TYPE_ELEM chorus_effect_type_list[];
	static const EFFECT_TYPE_ELEM dsp_effect_type_list[];

	static const EFFECT_PARAM_ELEM effect_param_1[16];
	static const EFFECT_PARAM_ELEM effect_param_2[16];
	static const EFFECT_PARAM_ELEM effect_param_3[16];
	static const EFFECT_PARAM_ELEM effect_param_4[16];
	static const EFFECT_PARAM_ELEM effect_param_5[16];
	static const EFFECT_PARAM_ELEM effect_param_6[16];
	static const EFFECT_PARAM_ELEM effect_param_7[16];
	static const EFFECT_PARAM_ELEM effect_param_8[16];
	static const EFFECT_PARAM_ELEM effect_param_9[16];
	static const EFFECT_PARAM_ELEM effect_param_10[16];
	static const EFFECT_PARAM_ELEM effect_param_11[16];
	static const EFFECT_PARAM_ELEM effect_param_12[16];
	static const EFFECT_PARAM_ELEM effect_param_13[16];
	static const EFFECT_PARAM_ELEM effect_param_14[16];
	static const EFFECT_PARAM_ELEM effect_param_15[16];
	static const EFFECT_PARAM_ELEM effect_param_16[16];
	static const EFFECT_PARAM_ELEM effect_param_17[16];
	static const EFFECT_PARAM_ELEM effect_param_18[16];
	static const EFFECT_PARAM_ELEM effect_param_19[16];
	static const EFFECT_PARAM_ELEM effect_param_20[16];
	static const EFFECT_PARAM_ELEM effect_param_21[16];
	static const EFFECT_PARAM_ELEM effect_param_22[16];
	static const EFFECT_PARAM_ELEM effect_param_23[16];
	static const EFFECT_PARAM_ELEM effect_param_24[16];
	static const EFFECT_PARAM_ELEM effect_param_25[16];
	static const EFFECT_PARAM_ELEM effect_param_26[16];
	static const EFFECT_PARAM_ELEM effect_param_27[16];
	static const EFFECT_PARAM_ELEM effect_param_28[16];
	static const EFFECT_PARAM_ELEM effect_param_29[16];
	static const EFFECT_PARAM_ELEM effect_param_30[16];
	static const EFFECT_PARAM_ELEM effect_param_31[16];
	static const EFFECT_PARAM_ELEM effect_param_32[16];
	static const EFFECT_PARAM_ELEM effect_param_33[16];
	static const EFFECT_PARAM_ELEM effect_param_34[16];
	static const EFFECT_PARAM_ELEM effect_param_35[16];
	static const EFFECT_PARAM_ELEM effect_param_36[16];
	static const EFFECT_PARAM_ELEM effect_param_37[16];
	static const EFFECT_PARAM_ELEM effect_param_38[16];
	static const EFFECT_PARAM_ELEM effect_param_39[16];
	static const EFFECT_PARAM_ELEM effect_param_40[16];
	static const EFFECT_PARAM_ELEM effect_param_41[16];
	static const EFFECT_PARAM_ELEM effect_param_42[16];
	static const EFFECT_PARAM_ELEM effect_param_43[16];
	static const EFFECT_PARAM_ELEM effect_param_44[16];
	static const EFFECT_PARAM_ELEM effect_param_45[16];
	static const EFFECT_PARAM_ELEM effect_param_46[16];
	static const EFFECT_PARAM_ELEM effect_param_47[16];
	static const EFFECT_PARAM_ELEM effect_param_48[16];
	static const EFFECT_PARAM_ELEM effect_param_49[16];
	static const EFFECT_PARAM_ELEM effect_param_50[16];
	static const EFFECT_PARAM_ELEM effect_param_51[16];
	static const EFFECT_PARAM_ELEM effect_param_52[16];
	static const EFFECT_PARAM_ELEM effect_param_53[16];
	static const EFFECT_PARAM_ELEM effect_param_54[16];
	static const EFFECT_PARAM_ELEM effect_param_55[16];
	static const EFFECT_PARAM_ELEM effect_param_56[16];
	static const EFFECT_PARAM_ELEM effect_param_57[16];
	static const EFFECT_PARAM_ELEM effect_param_58[16];
	static const EFFECT_PARAM_ELEM effect_param_59[16];
	static const EFFECT_PARAM_ELEM effect_param_60[16];
	static const EFFECT_PARAM_ELEM effect_param_61[16];
	static const EFFECT_PARAM_ELEM effect_param_62[16];
	static const EFFECT_PARAM_ELEM effect_param_63[16];
	static const EFFECT_PARAM_ELEM effect_param_64[16];
	static const EFFECT_PARAM_ELEM effect_param_65[16];
	static const EFFECT_PARAM_ELEM effect_param_66[16];
	static const EFFECT_PARAM_ELEM effect_param_67[16];
	static const EFFECT_PARAM_ELEM effect_param_68[16];
	static const EFFECT_PARAM_ELEM effect_param_69[16];
	static const EFFECT_PARAM_ELEM effect_param_70[16];
	static const EFFECT_PARAM_ELEM effect_param_71[16];
	static const EFFECT_PARAM_ELEM effect_param_72[16];
	static const EFFECT_PARAM_ELEM effect_param_73[16];
	static const EFFECT_PARAM_ELEM effect_param_74[16];
	static const EFFECT_PARAM_ELEM effect_param_101[16];
	static const EFFECT_PARAM_ELEM effect_param_102[16];
	static const EFFECT_PARAM_ELEM effect_param_109[16];
	static const EFFECT_PARAM_ELEM effect_param_113[16];
	static const EFFECT_PARAM_ELEM effect_param_114[16];
	static const EFFECT_PARAM_ELEM effect_param_115[16];
	static const EFFECT_PARAM_ELEM effect_param_122[16];
	static const EFFECT_PARAM_ELEM effect_param_145[16];

	static const CString effect_data_0[EFFECT_DATA_0_LEN];
	static const CString effect_data_1[EFFECT_DATA_1_LEN];
	static const CString effect_data_2[EFFECT_DATA_2_LEN];
	static const CString effect_data_3[EFFECT_DATA_3_LEN];
	static const CString effect_data_4[EFFECT_DATA_4_LEN];
	static const CString effect_data_5[EFFECT_DATA_5_LEN];
	static const CString effect_data_6[EFFECT_DATA_6_LEN];
	static const CString effect_data_7[EFFECT_DATA_7_LEN];
	static const CString effect_data_8[EFFECT_DATA_8_LEN];
	static const CString effect_data_9[EFFECT_DATA_9_LEN];
	static const CString effect_data_10[EFFECT_DATA_10_LEN];
	static const CString effect_data_11[EFFECT_DATA_11_LEN];
	static const CString effect_data_12[EFFECT_DATA_12_LEN];
	static const CString effect_data_13[EFFECT_DATA_13_LEN];
	static const CString effect_data_14[EFFECT_DATA_14_LEN];
	static const CString effect_data_15[EFFECT_DATA_15_LEN];
	static const CString effect_data_16[EFFECT_DATA_16_LEN];
	static const CString effect_data_17[EFFECT_DATA_17_LEN];
	static const CString effect_data_18[EFFECT_DATA_18_LEN];
	static const CString effect_data_19[EFFECT_DATA_19_LEN];
	static const CString effect_data_20[EFFECT_DATA_20_LEN];
	static const CString effect_data_21[EFFECT_DATA_21_LEN];
	static const CString effect_data_22[EFFECT_DATA_22_LEN];
	static const CString effect_data_23[EFFECT_DATA_23_LEN];
	static const CString effect_data_24[EFFECT_DATA_24_LEN];
	static const CString effect_data_25[EFFECT_DATA_25_LEN];
	static const CString effect_data_26[EFFECT_DATA_26_LEN];
	static const CString effect_data_27[EFFECT_DATA_27_LEN];
	static const CString effect_data_28[EFFECT_DATA_28_LEN];
	static const CString effect_data_29[EFFECT_DATA_29_LEN];
	static const CString effect_data_30[EFFECT_DATA_30_LEN];
	static const CString effect_data_31[EFFECT_DATA_31_LEN];
	static const CString effect_data_32[EFFECT_DATA_32_LEN];
	static const CString effect_data_33[EFFECT_DATA_33_LEN];
	static const CString effect_data_34[EFFECT_DATA_34_LEN];
	static const CString effect_data_35[EFFECT_DATA_35_LEN];
	static const CString effect_data_36[EFFECT_DATA_36_LEN];
	static const CString effect_data_37[EFFECT_DATA_37_LEN];
	static const CString effect_data_38[EFFECT_DATA_38_LEN];
	static const CString effect_data_39[EFFECT_DATA_39_LEN];
	static const CString effect_data_40[EFFECT_DATA_40_LEN];
	static const CString effect_data_41[EFFECT_DATA_41_LEN];
	static const CString effect_data_42[EFFECT_DATA_42_LEN];
	static const CString effect_data_43[EFFECT_DATA_43_LEN];
	static const CString effect_data_44[EFFECT_DATA_44_LEN];
	static const CString effect_data_45[EFFECT_DATA_45_LEN];
	static const CString effect_data_46[EFFECT_DATA_46_LEN];
	static const CString effect_data_47[EFFECT_DATA_47_LEN];
	static const CString effect_data_48[EFFECT_DATA_48_LEN];
	static const CString effect_data_49[EFFECT_DATA_49_LEN];
	static const CString effect_data_50[EFFECT_DATA_50_LEN];
	static const CString effect_data_51[EFFECT_DATA_51_LEN];
	static const CString effect_data_52[EFFECT_DATA_52_LEN];
	static const CString effect_data_53[EFFECT_DATA_53_LEN];
	static const CString effect_data_54[EFFECT_DATA_54_LEN];
	static const CString effect_data_55[EFFECT_DATA_55_LEN];
	static const CString effect_data_56[EFFECT_DATA_56_LEN];
	static const CString effect_data_57[EFFECT_DATA_57_LEN];
	static const CString effect_data_58[EFFECT_DATA_58_LEN];
	static const CString effect_data_59[EFFECT_DATA_59_LEN];
	static const CString effect_data_60[EFFECT_DATA_60_LEN];
	static const CString effect_data_61[EFFECT_DATA_61_LEN];
	static const CString effect_data_62[EFFECT_DATA_62_LEN];
	static const CString effect_data_63[EFFECT_DATA_63_LEN];
	static const CString effect_data_64[EFFECT_DATA_64_LEN];
	static const CString effect_data_65[EFFECT_DATA_65_LEN];

	static const EFFECT_PARAM_ELEM *effect_param_lists[146];
	static const EFFECT_DATA_LISTS_ELEM effect_data_lists[66];

private:
	CString print_str;
};


#endif // !defined(AFX_SYSEXEVENTPROT_H__19FB00C1_148E_11D6_9348_0080AD7896CF__INCLUDED_)
