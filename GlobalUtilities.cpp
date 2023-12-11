// GlobalUtilities.cpp: Implementierung der Klasse GlobalUtilities.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "HP_midifile.h" only PSRUTI
#include "GlobalUtilities.h"

#if defined(ADD_PSRUTI_FUNCTIONS)
#include "HP_midifile.h"
#include "resource.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#if defined(ADD_PSRUTI_FUNCTIONS)

//**************************************************************************
//*
//*		LoadStringFromDLL
//*
//**************************************************************************


CString GlobalUtilities::LoadStringFromDLL(HINSTANCE hInst, int ids)
{
	// (c) 1998-2000 Golden Crater Software, All rights reserved.
	// You may freely use this code
	// You may freely redistribute this code, provided this comment block remains
	// intact.
	// The body of this function is from the epAssist EAX SDK:
	//   Use plain English to control your PC over email, AppBar, and soon
	//   voice telephone.
	//   Check out this free SDK that allows you to interface to epAssist.
	//   Easily add natural language functionality to your application and
	//   provide your users with access to your program from anywhere they
	//   can send and receive email (2-way pagers, public terminals and email
	//   enabled telephones included.) MFC AppWizard and HTML Help, and sample
	//   source included.             http://www.goldencrater.com/software
	if (!hInst) {
		ASSERT(0);
		return "Error loading resource.";
	}
	CString str;
	TCHAR szTemp[256];		// Raise limit of 255 char if needed.
	int nLen;
	LPCTSTR lpszName = MAKEINTRESOURCE((ids>>4)+1);
	if (::FindResource(hInst, lpszName, RT_STRING) != NULL &&
		(nLen = ::LoadString(hInst, ids, szTemp, 255) != 0)) {
		str = szTemp;
	}
	return str;
}

//**************************************************************************
//*
//*		get_resource_string
//*
//**************************************************************************

CString GlobalUtilities::get_resource_string (int ids)
{
	extern HINSTANCE hlanguage_dll;
	return LoadStringFromDLL(hlanguage_dll,ids);
}
#endif


//**************************************************************************
//*
//*		is_printable
//*
//**************************************************************************

bool GlobalUtilities::is_printable(unsigned char ch)  // is valid lyrics-char?
{
	return printable[ch];
}

//**************************************************************************
//*
//*		is_letter
//*
//**************************************************************************

bool GlobalUtilities::is_letter(unsigned char ch)
{
	return (printable[ch]&&(ch!='-')&&(ch!='_'));
}


//**************************************************************************
//*
//*		convert_CString_to_cstring
//*
//**************************************************************************

void GlobalUtilities::convert_CString_to_cstring(char** cstr, CString CStr)
{
	int i;
	int len = CStr.GetLength();
	*cstr = new char[len+1];

	for (i=0; i<len; i++)
	{
		(*cstr)[i] = CStr.GetAt(i);
	}
	(*cstr)[len] = (char)0;
}

//**************************************************************************
//*
//*		convert_cstring_to_printable
//*
//**************************************************************************

CString GlobalUtilities::convert_cstring_to_printable(char* str)
{
	int i;
	char c;
	if (str[0] == 0) return "\"\"";

	CString new_str = "\"";

	for( i=0; i<(int)strlen(str); i++)
	{
		c = str[i];
		if (c == 0x0d)
		{
			new_str += "/";
		}
		else
		{
			new_str += c;
		}
	}
	new_str += "\"";

	return new_str;
}

//**************************************************************************
//*
//*		convert_string_to_printable
//*
//**************************************************************************

CString GlobalUtilities::convert_string_to_printable(CString str)
{
	int i;
	char c;
	if (str.GetLength() == 0) return "\"\"";

	CString new_str = "\"";

	for( i=0; i<str.GetLength(); i++)
	{
		c = str[i];
		if (c == 0x0d)
		{
			new_str += "/";
		}
		else
		{
			new_str += c;
		}
	}
	new_str += "\"";

	return new_str;
}

//**************************************************************************
//*
//*		convert_printable_to_string
//*
//**************************************************************************

CString GlobalUtilities::convert_printable_to_string(CString str, char lf)
{
	CString str1 = str;
	str1 = str1.Right(str1.GetLength()-1);
	str1 = str1.Left(str1.GetLength()-1);

	int i;
	char c;
	CString new_str;

	for (i=0; i<str1.GetLength(); i++)
	{
		c = str1[i];
		if (c == '/') // Slash
		{
			new_str += lf;
		}
		else
		{
			new_str += c;
		}
	}
	return new_str;
}

#if defined(ADD_PSRUTI_FUNCTIONS)

//**************************************************************************
//*
//*		compute number from text
//*
//**************************************************************************

int GlobalUtilities::compute_number(char* s, int l)
{
	int val = 0;
	int i;

	for (i=0; (i<l)&&(i<3); i++)
	{
		if (s[i] == 0x20) continue;
		if ((s[i] < '0') || (s[i] > '9')) break;
		val = 10*val + (s[i]-'0');
	}

	return val;
}

//**************************************************************************
//*
//*		compute number from text
//*
//**************************************************************************

double GlobalUtilities::compute_double_number(char* s, int l)
{
	char* stop_s;

	double val = strtod( s, &stop_s);
	return val;
}


#endif

//**************************************************************************
//*
//*		convert_sysex_data_to_string
//*
//**************************************************************************

CString GlobalUtilities::convert_sysex_data_to_string(unsigned char *data)
{
	int i;
	CString sysexstr = "";
	unsigned char ch, ch0, ch1;

	const CString convert_table[16] =
	{"0","1","2","3","4","5","6","7",
	"8","9","a","b","c","d","e","f"};

	for (i=0; true; i++)
	{
		ch = data[i];
		ch0 = ch/16;
		ch1 = ch%16;

		sysexstr += convert_table[ch0];
		sysexstr += convert_table[ch1];
		sysexstr += " ";

		if (ch == 0xf7) break;
	}

	return sysexstr;
}


//**************************************************************************
//*
//*		convert_sysex_string_to_data
//*
//**************************************************************************

bool GlobalUtilities::convert_sysex_string_to_data(CString cstring, unsigned char **data, int *length)
{
	int i;
	cstring.MakeUpper();
	char ch0, ch1;
	int n0, n1;
	int len = cstring.GetLength();
	if (len%2 != 0) return false;
	*data = new unsigned char[len/2];
	*length = len/2;

	for (i=0; i<len; i+=2)
	{
		ch0 = cstring[i];
		ch1 = cstring[i+1];
		n0 = (ch0>='A' && ch0 <='F')?(ch0-'A')+10:ch0-'0';
		n1 = (ch1>='A' && ch1 <='F')?(ch1-'A')+10:ch1-'0';
		(*data)[i/2] = 16*n0 + n1;
	}
	if (((*data)[0] != 0xf0)||((*data)[(len-2)/2] != 0xf7))
	{
//		MessageBox(NULL,"F0 or F7 missed",NULL,MB_OK);
		return false;
	}
	return true;
}


//**************************************************************************
//*
//*		is_gm_on_sysex
//*
//**************************************************************************

bool GlobalUtilities::is_gm_on_sysex(unsigned char *data)
{
	int i;
	bool is = true;
	for (i=0; i<6; i++)
	{
		if (data[i]!=gm_on_data[i])
		{
			is = false;
			break;
		}
	}
	return is;
}


//**************************************************************************
//*
//*		is_xg_on_sysex
//*
//**************************************************************************

bool GlobalUtilities::is_xg_on_sysex(unsigned char *data)
{
	int i;
	bool is = true;
	for (i=0; i<9; i++)
	{
		if (data[i]!=xg_on_data[i])
		{
			if ((i==2)&&((data[i]&0x10)==0x10)) continue;
			is = false;
			break;
		}
	}
	return is;
}

//**************************************************************************
//*
//*		is_turn_tg300b_on
//*
//**************************************************************************

bool GlobalUtilities::is_turn_tg300b_on(unsigned char *data)
{
	int i;
	bool is = true;
	for (i=0; i<11; i++)
	{
		if (data[i]!=turn_tg300b_on_data[i])
		{
			is = false;
			break;
		}
	}
	return is;
}

//**************************************************************************
//*
//*		is_part_mode_sysex
//*
//**************************************************************************

bool GlobalUtilities::is_part_mode_sysex(unsigned char *data)
{
	unsigned char part_mode[9] =
		{0xf0, 0x43, 0x10, 0x4c, 0x08, 0xff, 0x07, 0xff, 0xf7};
	// do not check index = 5 and 7
	if (!compare_data(data, 5, part_mode, 5))
	{
		return false;
	}

	return data[6]==part_mode[6]?true: false;
}

//**************************************************************************
//*
//*		is_lyrics_part_score_on_sysex
//*
//**************************************************************************

bool GlobalUtilities::is_lyrics_part_score_on_sysex(unsigned char *data)
{
	int i;
	bool is = true;
	for (i=0; i<10; i++)
	{
		if (data[i]!=lyrics_part_score_on_data[i])
		{
			is = false;
			break;
		}
	}
	return is;
}

//**************************************************************************
//*
//*		is_chord_part_score_on_sysex
//*
//**************************************************************************

bool GlobalUtilities::is_chord_part_score_on_sysex(unsigned char *data)
{
	int i;
	bool is = true;
	for (i=0; i<10; i++)
	{
		if (data[i]!=chord_part_score_on_data[i])
		{
			is = false;
			break;
		}
	}
	return is;
}

//**************************************************************************
//*
//*		is_score_layout_sysex
//*     look for sysex F0 43 73 01 50 12 00 <type> <value> F7
//*
//**************************************************************************

bool GlobalUtilities::is_score_layout_sysex(unsigned char *data, unsigned char *type, unsigned char *value)
{
	*type = 0xff; // undef

	int i;
	bool is = true;
	for (i=0; i<10; i++)
	{
		if ((i==7)||(i==8))
		{
			continue;
		}
		if (data[i]!=score_layout_data[i])
		{
			is = false;
			break;
		}
	}

	if (is)
	{
		*type = data[7];
		*value = data[8];
	}
	return is;
}


//**************************************************************************
//*
//*		is_part_not_used_sysex
//*
//**************************************************************************

bool GlobalUtilities::is_part_not_used_sysex(unsigned char *data)
{
	int i;
	unsigned char part_not_used[9] =
		{0xf0, 0x43, 0x10, 0x4c, 0x08, 0xff, 0x00, 0xff, 0xf7};

	// do not check index = 5 and 7
	for (i=0; i<9; i++)
	{
		if ((i==5) || (i==7)) continue;
		if (data[i] != part_not_used[i])
		{
			return false;
		}
	}
	return true;
}

//**************************************************************************
//*
//*		is_part_mode_normal_sysex
//*
//**************************************************************************

bool GlobalUtilities::is_part_mode_normal_sysex(unsigned char *data)
{
	int i;
	unsigned char part_mode_normal[9] =
		{0xf0, 0x43, 0x10, 0x4c, 0x08, 0xff, 0x07, 0x00, 0xf7};

	// do not check index = 5
	for (i=0; i<9; i++)
	{
		if (i==5) continue;
		if (data[i] != part_mode_normal[i])
		{
			return false;
		}
	}
	return true;
}


//**************************************************************************
//*
//*		compare_data
//*
//**************************************************************************

bool GlobalUtilities::compare_data(unsigned char* data1, int len1, unsigned char* data2, int len2)
{
	if (len1 != len2) return false;

	int i;
	for (i=0; i<len1; i++)
	{
		if (data1[i]!= data2[i]) return false;
	}

	return true;
}

//**************************************************************************
//*
//*		pack_msb_lsb_voice
//*
//**************************************************************************

int GlobalUtilities::pack_msb_lsb_voice(int msb, int lsb, int voice)
{
	return ((msb*128)+lsb)*128+voice;
}

//**************************************************************************
//*
//*		unpack_msb_lsb_voice
//*
//**************************************************************************

void GlobalUtilities::unpack_msb_lsb_voice(int data, int *msb, int *lsb, int * voice)
{
	int scr = data;
	*voice = scr%128;
	scr /= 128;
	*lsb = scr%128;
	scr /= 128;
	*msb = scr%128;
}

//**************************************************************************
//*
//*		is_flat_key
//*		finds out if a key uses flats (b)
//*
//**************************************************************************

#if defined(ADD_PSRUTI_FUNCTIONS)

bool GlobalUtilities::is_flat_key(char *key)
{
	bool is_flat = true;
	int i;
	for (i=0; i<30; i++)
	{
		if (strcmp(key,flat_sharp_list[i].key)==0)
		{
			is_flat = flat_sharp_list[i].is_flat;
			break;
		}
	}
	return is_flat;
}

#endif



//**************************************************************************
//*
//*		change_flat_sharp_bn
//*
//**************************************************************************

unsigned char GlobalUtilities::change_flat_sharp_bn(unsigned char bn, unsigned char cr)
{
	// change flat to sharp and inverse. Use only for transposed base-roots bn

	int bn03 = (int)(bn>>4);
	int cr03 = (int)(cr>>4);

	if (((bn03<3)&&(cr03>3))||((bn03>3)&&(cr03<3)))
	{	// change flat to sharp and inverse
		if (bn == 0x41) return 0x22; // C# -> Db
		if (bn == 0x22) return 0x41; // Db -> C#

		if (bn == 0x23) return 0x42; // Eb -> D#
		if (bn == 0x42) return 0x23; // D# -> Eb

		if (bn == 0x44) return 0x25; // F# -> Gb
		if (bn == 0x25) return 0x44; // Gb -> F#

		if (bn == 0x26) return 0x45; // Ab -> G#
		if (bn == 0x45) return 0x26; // G# -> Ab

		if (bn == 0x27) return 0x46; // Bb -> A#
		if (bn == 0x46) return 0x27; // A# -> Bb
	}
	return bn; // default: old value
}

//**************************************************************************
//*
//*		enharmonic_cr
//*
//**************************************************************************

unsigned char GlobalUtilities::enharmonic_cr(unsigned char cr, bool is_flat)
{
	unsigned char new_cr;
	if (is_flat)
	{
		new_cr = null_table_flat[cr];
	}
	else
	{
		new_cr = null_table_sharp[cr];
	}
	return new_cr;
}


//**************************************************************************
//*
//*		transpose_cr
//*
//**************************************************************************

unsigned char GlobalUtilities::transpose_cr(unsigned char cr, int delta, bool is_flat)
{
	unsigned char base = cr;
	int i;

	if (base == 0x7f) return base;

	if (delta > 0)
	{
		if (base > 0x67) return 0x7f;
		for (i=0; i<delta; i++)
		{
			if (is_flat)
			{
				base = plus_table_flat[base];
			}
			else
			{
				base = plus_table_sharp[base];
			}
		}
	}
	else
	{
		if (base > 0x67) return 0x7f;
		for (i=0; i<-delta; i++)
		{
			if (is_flat)
			{
				base = minus_table_flat[base];
			}
			else
			{
				base = minus_table_sharp[base];
			}
		}
	}

	return base;
}


//**************************************************************************
//*
//*		transpose_key_signature
//*
//**************************************************************************

CString GlobalUtilities::transpose_key_signature(CString old_key, int transpose_no)
{
	const CString keylist[12] =
	{ "C","Db","D","Eb","E","F","F#","G","Ab","A","Bb","B" };
	const CString keylist_moll[12] =
	{ "Cm","Dbm","Dm","Ebm","Em","Fm","F#m","Gm","Abm","Am","Bbm","Bm" };

	bool found = false;
	CString transposed_key;
	int i;

	CString tr_key = old_key;
	const struct {char* ok; char* tk;} ok_tk[6] =
	{
		{"Cb","B"},
		{"Cbm","Bm"},
		{"Gb","F#"},
		{"Gbm","F#m"},
		{"C#","Db"},
		{"C#m","Dbm"}
	};

	// convert old_key to char*
	char ck[5];
	for (i=0; i<old_key.GetLength(); i++)
	{
		ck[i] = old_key[i];
	}
	ck[i] = (char)0x00;

	// convert some keys more simple keys
	for (i=0; i<6; i++)
	{
		if (strcmp(ck,ok_tk[i].ok)==0)
		{
			tr_key = ok_tk[i].tk;
		}
	}

	// try to transpose dur keys
	for (i=0; i<12; i++)
	{
		if (keylist[i]==tr_key)
		{
			found = true;
			int ix = i+transpose_no;
			if (ix < 0) ix+=12;
			transposed_key = keylist[ix%12];
			break;
		}
	}
	if (found) return transposed_key;

	// try to transpose moll keys
	for (i=0; i<12; i++)
	{
		if (keylist_moll[i]==tr_key)
		{
			found = true;
			int ix = i+transpose_no;
			if (ix < 0) ix+=12;
			transposed_key = keylist_moll[ix%12];
			break;
		}
	}
	if (found) return transposed_key;

	return "C";
}


//**************************************************************************
//*
//*		find_cr_ct_bn_bt
//*		compute cr, ct, bn, bt from chord text
//*
//**************************************************************************

bool GlobalUtilities::find_cr_ct_bn_bt(CString chord_text, unsigned char *cr, unsigned char *ct,
		                                 unsigned char *bn, unsigned char *bt)
{
	int i;

	if (chord_text=="")
	{
		return false;
	}

	CString chrd_txt = chord_text=="cc"?"Ccc":chord_text;

	const CString chord_type[38] =
	{
		"",			// 0x00
		"6",
		"M7",
		"M7(#11)",
		"9",
		"M7(9)",
		"6(9)",
		"aug",
		"m",		// 0x08
		"m6",
		"m7",
		"m7b5",
		"m(9)",
		"m7(9)",
		"m7_11",
		"mM7",
		"mM7_9",	// 0x10
		"dim",
		"dim7",
		"7",
		"7sus4",
		"7b5",
		"7(9)",
		"7(#11)",
		"7(13)",	// 0x18
		"7(b9)",
		"7(b13)",
		"7(#9)",
		"M7aug",
		"7aug",
		"1+8",
		"1+5",
		"sus4",		// 0x20
		"sus2",
		"cc",
		"M7b5",
		"(b5)",
		"mM7b5",	// 0x25
	};

	const CString xg_works_chord_type[38] =
	{
		"(Maj)",	// 0x00
		"6",
		"M7",
		"M7(#11)",
		"add9",
		"M7(9)",
		"6(9)",
		"5+",
		"min",		// 0x08
		"min6",
		"min7",
		"min7b5",
		"madd9",
		"min7(9)",
		"min7(11)",
		"mM7",
		"mM7(9)",	// 0x10
		"dim",
		"dim7",
		"7",
		"7sus4",
		"7b5",
		"7(9)",
		"7(#11)",
		"7(13)",	// 0x18
		"7(b9)",
		"7(b13)",
		"7(#9)",
		"M7aug",
		"7aug",
		"1+8",
		"1+5",
		"sus4",		// 0x20
		"sus2",
		"cc",
		"M7b5",
		"5-",
		"mM7b5",	// 0x25
	};

	unsigned char cr_left, cr_right, bn_left, bn_right;

	int tr_base_note;

	tr_base_note = chrd_txt[0] - 'A';

	if ((tr_base_note < 0) || (tr_base_note > 6))
	{
		return false;
	}

	cr_right = tr_base_note < 2? tr_base_note+6:tr_base_note-1;

	cr_left = 3;

	for (i = 1; i < chrd_txt.GetLength(); i++)
	{
		unsigned char ch = chrd_txt[i];
		if(ch=='#')
		{
			cr_left++;
		}
		else
		if(ch=='b')
		{
			cr_left--;
		}
		else
		{
			break;
		}
	}

	if ((cr_left < 0)||(cr_left > 6)) return false;

	cr_left<<=4;
	*cr = cr_left | cr_right;

	// index i points to beginning of type_part

	CString type_text = "";

	for (i=i; i<chrd_txt.GetLength(); i++)
	{
		unsigned char ch = chrd_txt[i];
		if(ch=='/')
		{
			break;
		}
		type_text += ch;
	}

	*ct = 0x7f;
	int k;
	for (k=0; k<38; k++)
	{
		if (chord_type[k] == type_text)
		{
			*ct = (unsigned char) k;
			break;
		}
	}

	if (*ct == 0x7f)
	{	// try with xg-works notation
		for (k=0; k<38; k++)
		{
			if (xg_works_chord_type[k] == type_text)
			{
				*ct = (unsigned char) k;
				break;
			}
		}
	}

	if (*ct == 0x7f) return false;


	if (i>=chrd_txt.GetLength())
	{
		*bn = 0x7f;
		*bt = 0x7f;
		return true;
	}

	if (chrd_txt[i]!='/')
	{
		*bn = 0x7f;
		*bt = 0x7f;
		return true;
	}

	i++;

	tr_base_note = chrd_txt[i] - 'A';

	if ((tr_base_note < 0) || (tr_base_note > 6))
	{
		return false;
	}

	bn_right = tr_base_note < 2? tr_base_note+6:tr_base_note-1;

	bn_left = 3;
	for (i = i+1; i < chrd_txt.GetLength(); i++)
	{
		unsigned char ch = chrd_txt[i];
		if(ch=='#')
		{
			bn_left++;
		}
		else
		if(ch=='b')
		{
			bn_left--;
		}
		else
		{
			break;
		}
	}

	if ((bn_left < 0)||(bn_left > 6)) return false;

	bn_left<<=4;
	*bn = bn_left | bn_right;

	*bt = 0x7f;

	return true;
}


#if defined(ADD_PSRUTI_FUNCTIONS)


//**************************************************************************
//*
//*		is_vh_channel_sysex
//*		looks if sysex string is vh_chan-sysex; returns channel or -1 if no
//*
//**************************************************************************

int GlobalUtilities::is_vh_channel_sysex(unsigned char* data, int length)
{
	int i;

	if (length!=9) return -1;

	unsigned char vh_sysex_chan[9] = {0xf0, 0x43, 0x10, 0x4c, 0x04, 0x00, 0x14, 0x00, 0xf7}; // data[7] = channel

	bool is = true;
	for (i=0; i<9; i++)
	{
		if (i==7) continue;
		if (data[i] != vh_sysex_chan[i])
		{
			return -1;
		}
	}
	return data[7];
}


//**************************************************************************
//*
//*		is_vh_sysex
//*		looks if sysex string is vh sysex that sets other vh types
//*		than vocoder 
//*
//**************************************************************************

/* 8.19 
bool GlobalUtilities::is_vh_sysex(unsigned char* data, int length)
{
	int i;

	bool result_se = true; // init: there are vh types defined.
	bool result_so = true;

	if (length<7) return false;

	// MIDI Parameter Change table (SPECIAL EFFECT) 
	unsigned char vh_sysex_start_se[7] = {0xf0, 0x43, 0x10, 0x4c, 0x04, 0x00, 0x00};
	for (i=0; i<7; i++)
	{
		if (data[i] != vh_sysex_start_se[i])
		{
			result_se = false;
			break;
		}
	}

	if ( (data[7]==0x59) || // vocoder XG
		 (data[7]==0x5a) || // chordal
		 (data[7]==0x5b) || // detune XG
		 (data[7]==0x5c)    // chromatic XG
	   )
	{
		result_se = true;
	}
	else
	{
		result_se = false;
	}

	// VH AD On/Off
	unsigned char vh_sysex_start_so[6] = {0xf0, 0x43, 0x10, 0x4c, 0x04, 0x00};
	for (i=0; i<6; i++)
	{
		if (data[i] != vh_sysex_start_so[i])
		{
			result_so = false;
			break;
		}
	}

	if (result_so)
	{
		result_so = (data[6]==0x0c)||(data[6]==0x14); // VH AD or Song Harmony Channel
	}

	return result_se || result_so;
}
*/

// 8.20 All VH SysExes are controlled

bool GlobalUtilities::is_vh_sysex(unsigned char* data, int length)
{
	int i;
	bool result_se; 
	bool result_cl;
	bool result_ad;

    if (!((length==9) || (length==10))) return false; 

	// MIDI Parameter Change table (SPECIAL EFFECT) 
	unsigned char special_effect_sysex_start[6] = {0xf0, 0x43, 0x10, 0x4c, 0x04,0x00};

	result_se = true;
	for (i=0; i<6; i++)
	{
		if (data[i] != special_effect_sysex_start[i])
		{
			result_se = false;
		}
	}
	

	// MIDI Parameter Change table (Clavinova Part)
	unsigned char clavinova_part_sysex_start[6] = {0xf0, 0x43, 0x73, 0x01, 0x11, 0x00};
	result_cl = true;

	for (i=0; i<6; i++)
	{
		if (data[i] != clavinova_part_sysex_start[i])
		{
			result_cl = false;
		}
	}

	// MIDI Parameter Change table (AD Part)
	unsigned char ad_part_sysex_start[6] = {0xf0, 0x43, 0x10, 0x4c, 0x10, 0x00};
	result_ad = true;

	for (i=0; i<6; i++)
	{
		if (data[i] != ad_part_sysex_start[i])
		{
			result_ad = false;
		}
	}
	return result_se||result_cl||result_ad;
}


//**************************************************************************
//*
//*		is_vocoder_sysex
//*		looks if sysex string is vocoder sysex
//*
//**************************************************************************

bool GlobalUtilities::is_vocoder_sysex(unsigned char* data, int length)
{
	int i;

	if (length != 10) return false;

	unsigned char vocoder_sysex[10] = {0xf0, 0x43, 0x10, 0x4c, 0x04, 0x00, 0x00, 0x59, 0x00, 0xf7};

	for (i=0; i<8; i++)
	{
		if (data[i] != vocoder_sysex[i])
		{
			return false;
		}
	}
	return true;
}

//**************************************************************************
//*
//*		is_score_sysex
//*		looks if sysex string is score sysex
//*
//**************************************************************************

bool GlobalUtilities::is_score_sysex(unsigned char* data, int length)
{
	int i;

	if (length != 10) return false;

	unsigned char seven_score_sysex_bytes[7] = {0xf0, 0x43, 0x73, 0x01, 0x50, 0x12, 0x00};

	for (i=0; i<7; i++)
	{
		if (data[i] != seven_score_sysex_bytes[i])
		{
			return false;
		}
	}
	return true;
}



//**************************************************************************
//*
//*		is_vh_ad_on_sysex
//*		looks if sysex string is VH AD On sysex
//*
//**************************************************************************

bool GlobalUtilities::is_vh_ad_on_sysex(unsigned char* data, int length)
{
	int i;

	if (length != 9) return false;

	unsigned char vh_ad_on_sysex[9] = {0xf0, 0x43, 0x10, 0x4c, 0x04, 0x00, 0x0c, 0x40, 0xf7};

	for (i=0; i<9; i++)
	{
		if (data[i] != vh_ad_on_sysex[i])
		{
			return false;
		}
	}
	return true;
}


//**************************************************************************
//*
//*		is_vh_ad_off_sysex
//*		looks if sysex string is VH AD On sysex
//*
//**************************************************************************

bool GlobalUtilities::is_vh_ad_off_sysex(unsigned char* data, int length)
{
	int i;

	if (length != 9) return false;

	unsigned char vh_ad_off_sysex[9] = {0xf0, 0x43, 0x10, 0x4c, 0x04, 0x00, 0x0c, 0x00, 0xf7};

	for (i=0; i<9; i++)
	{
		if (data[i] != vh_ad_off_sysex[i])
		{
			return false;
		}
	}
	return true;
}


//**************************************************************************
//*
//*		analyse_mbt
//*		syntax analysis of measure:bar:tick string
//*
//**************************************************************************

bool GlobalUtilities::analyse_mbt(CString mbt_str, int* meas, int* bar, int* tick)
{
	int i;
	char ch;
	int no_colons = 0;
	int next_i;
	int m = 0;
	int b = 0;
	int t = 0;
	int len = mbt_str.GetLength();
	if (len<5) return false;
	for (i=0; i<len; i++)
	{
		ch = mbt_str.GetAt(i);
		if ((ch==':')||(ch==' '))
		{
			no_colons++;
			next_i = i+1;
			break;
		}
		if ((ch<'0')||(ch>'9'))
		{
			return false;
		}
		m = 10*m+(int)ch-(int)'0';
	}
	if (m<1) return false;

	for (i=next_i; i<len; i++)
	{
		ch = mbt_str.GetAt(i);
		if ((ch==':')||(ch==' '))
		{
			no_colons++;
			next_i = i+1;
			break;
		}
		if ((ch<'0')||(ch>'9'))
		{
			return false;
		}
		b = 10*b+(int)ch-(int)'0';
	}
	if (b<1) return false;

	for (i=next_i; i<len; i++)
	{
		ch = mbt_str.GetAt(i);
		if ((ch==':')||(ch==' '))
		{
			no_colons++;
			next_i = i+1;
			break;
		}
		if ((ch<'0')||(ch>'9'))
		{
			return false;
		}
		t = 10*t+(int)ch-(int)'0';
	}
	if (no_colons != 2) return false;
	if (t > 479) return false;
	*meas = m-1;
	*bar = b-1;
	*tick = t;
	return true;
}


//**************************************************************************
//*
//*		find_bn
//*		compute sharp bn from note value
//*
//**************************************************************************

unsigned char GlobalUtilities::find_bn(int note)
{

	static unsigned char sharplist[13] =
	{
		0x00, // reserved
		0x31, // C
		0x41, // C#
		0x32, // D
		0x42, // D#
		0x33, // E
		0x34, // F
		0x44, // F#
		0x35, // G
		0x45, // G#
		0x36, // A
		0x46, // A#
		0x37  // B
	};

	unsigned char val;
	int note_index = note%12+1;
	val = sharplist[note_index];
	return val;
}

//**************************************************************************
//*
//*		convert_bn
//*		changes bn and bn text according to cr; for example G/Db to G/C#
//*		changes C/C or Gb/F# to C resp. Gb
//*
//**************************************************************************

CString GlobalUtilities::convert_bn(unsigned char bn, unsigned char cr, unsigned char ct, unsigned char* new_bn)
{
	const struct {unsigned char flat; unsigned char sharp;} bn_convertlist[9] =
	{
		{0x31,0x31},	// flat C , sharp C
		{0x22,0x41},	// flat Db, sharp C#
		{0x23,0x42},	// flat Eb, sharp D#
		{0x33,0x33},	// flat E , sharp E
		{0x34,0x34},	// flat F , sharp F
		{0x25,0x44},	// flat Gb, sharp F#
		{0x26,0x45},	// flat Ab, sharp G#
		{0x27,0x46},	// flat Bb, sharp A#
		{0x37,0x37}		// flat B , sharp B
	};

	// only used with chord types min (0x08 <= ct <= 0x10)
	const struct {unsigned char cr; bool flat;} cr_flat_min_list[17] =
	{
		{0x31,true},	// C,  min is flat
		{0x41,false},	// C#, min is sharp
		{0x22,false},	// Db, min is sharp
		{0x32,true},	// D,  min is flat
		{0x42,true},	// D#, min is sharp
		{0x23,true},	// Eb, min is sharp
		{0x33,true},	// E,  min is sharp
		{0x34,true},	// F,  min is flat
		{0x44,true},	// F#, min is sharp
		{0x25,true},	// Gb, min is sharp
		{0x35,true},	// G,  min is flat
		{0x45,true},	// G#, min is sharp
		{0x26,true},	// Ab, min is sharp
		{0x36,true},	// A,  min is flat
		{0x46,true},	// A#, min is flat
		{0x27,true},	// Bb, min is flat
		{0x37,true}		// B,  min is sharp
	};

	const int bn_convertlist_len = 9;
	const int cr_flat_min_list_len = 17;

	int i;

	// initial values
	CString new_bn_text = compute_short_notestring(bn,false);
	*new_bn = bn;

	// adjust bn to flat/sharp of cr
	bool flat_cr;
	if (((cr&0xf0)==0x20)||(cr==0x31)||(cr==0x34))
	{ // cr flat, note C or F
		flat_cr = true;
	}
	else
	{
		flat_cr = false;
	}

	if (((char)ct>=0x08) && ((char)ct<=0x10))
	{ // special for min chord types
		for (i=0; i<cr_flat_min_list_len; i++)
		{
			if (cr == cr_flat_min_list[i].cr)
			{
				flat_cr = cr_flat_min_list[i].flat;
				break;
			}
		}
	}

	// bn and cr without any sign?
	bool natural_bn = (bn&0xf0)==0x30;
	if (natural_bn)
	{
		*new_bn = bn;
		new_bn_text = compute_short_notestring(bn,flat_cr);
		return new_bn_text;
	}

	// bn and cr have the same sign?
	if ((flat_cr &&((bn&0xf0)==0x20)) ||
		(!flat_cr &&((bn&0xf0)==0x40)))
	{
		*new_bn = bn;
		new_bn_text = compute_short_notestring(bn,flat_cr);
		return new_bn_text;
	};

	// bn and cr with different sign?
	// bn must be changed

	// cr flat, bn sharp? convert bn to flat
	if (flat_cr && ((bn&0xf0)==0x40))
	{
//		MessageBox(NULL,"cr flat, bn sharp",NULL,MB_OK);
		*new_bn = bn;
		for (i=0; i<bn_convertlist_len; i++)
		{
			if (bn_convertlist[i].sharp==bn)
			{
				*new_bn = bn_convertlist[i].flat;
				new_bn_text = compute_short_notestring(*new_bn,flat_cr);
				break;
			}
		}
		return new_bn_text;
	}

	// cr sharp, bn flat? convert bn to sharp
	if (!flat_cr && ((bn&0xf0)==0x20))
	{
//		MessageBox(NULL,"cr sharp, bn flat",NULL,MB_OK);
		*new_bn = bn;
		for (i=0; i<bn_convertlist_len; i++)
		{
			if (bn_convertlist[i].flat==bn)
			{
				*new_bn = bn_convertlist[i].sharp;
				new_bn_text = compute_short_notestring(*new_bn,flat_cr);
				break;
			}
		}
		return new_bn_text;
	}

	return new_bn_text; // function should not perform it
}


//**************************************************************************
//*
//*		short note name from bn value
//*
//**************************************************************************

CString GlobalUtilities::compute_short_notestring(unsigned char bn, bool flat_cr)
{
	const CString flatlist[8] =    {"","C","Db","Eb","F" ,"Gb","Ab","Bb"};
	const CString naturallist[8] = {"","C","D" ,"E" ,"F" ,"G" ,"A" ,"B" };
	const CString sharplist[8] =   {"","C","D#","E" ,"F#","G#","A#","B" };

	CString note_text;
	if ((bn&0xf0)==0x20) note_text = flatlist[bn&0x0f];
	if ((bn&0xf0)==0x30) note_text = naturallist[bn&0x0f];
	if ((bn&0xf0)==0x40) note_text = sharplist[bn&0x0f];

	return note_text;
}


//**************************************************************************
//*
//*		note name from note value
//*
//**************************************************************************

CString GlobalUtilities::compute_notestring(int notevalue)
{
	const CString notes[12] = {"C","Db","D","Eb","E","F","F#","G","Ab","A","Bb","B"};
	const CString octaves[11] = {"-2","-1","0","1","2","3","4","5","6","7","8"};
	return notes[notevalue%12]+octaves[notevalue/12];
}

//**************************************************************************
//*
//*		note value from note name
//*
//**************************************************************************

int GlobalUtilities::compute_notevalue(CString note_name)
{
	int i = 0;
	int note_value = -1;
	CString list_name;

	for (i=0; i<NO_NOTE_NAME_ELEMS; i++)
	{
		list_name = (note_name_list[i]).name;
		if (list_name == note_name)
		{
			note_value = (note_name_list[i]).value;
			break;
		}
	}
	return note_value;;
}

//**************************************************************************
//*
//*		get fixed linefeed CR
//*
//**************************************************************************

char GlobalUtilities::get_linefeed_char()
{
	return 0x0d;
}

//**************************************************************************
//*
//*		get_id
//*
//**************************************************************************

int GlobalUtilities::get_id(CString midiport)
{
	HP_DEVICE *devices;
	int no_devices;
	int port_id = -1;
	int k;

	// get list available of MIDI-devices
	HP_GetMIDIDevices(&devices,&no_devices);

	// save id's local and  device-names in dlg-list
	for (k=0; k<no_devices; k++)
	{
		int id = devices[k].device_id;
		char* name = devices[k].device_name;
		CString cname = name;
		if (cname == midiport)
		{
			port_id = id;
			break;
		}
	}
	HP_Delete(devices);
	return port_id;
}

//**************************************************************************
//*
//*		SelectProtFile
//*
//**************************************************************************

CString GlobalUtilities::SelectProtFile(CString last_protfile)
{
	CString protfile;
	int i;

	char BASED_CODE szFilter[] =
		"Prot-File (*.txt)|*.txt||";

	CFileDialog openfile_dlg(FALSE,
						  "txt",
						  NULL,
						  OFN_PATHMUSTEXIST,
						  szFilter,
						  NULL);

	if (last_protfile != "")
	{
		openfile_dlg.m_ofn.lpstrInitialDir = last_protfile;
		char lp[MAX_PATH];
		for (i=0; i<last_protfile.GetLength(); i++)
		{
			lp[i] = last_protfile[i];
		}
		lp[last_protfile.GetLength()] = (char)0;
		openfile_dlg.m_ofn.lpstrFile = lp;
	}

	int return_value = openfile_dlg.DoModal();
	if (return_value == IDOK)
	{
		protfile = openfile_dlg.m_ofn.lpstrFile;
	}
	else
	{
		if (return_value == IDCANCEL)
		{
			return "";
		}
	}

	// Try protfile

	CFile mf_newf;
	CFileException e;

	if (mf_newf.Open(protfile, CFile::modeRead,&e))
	{
		int length = mf_newf.GetLength();
		mf_newf.Close();

		if (length>0)
		{
			CString r;
			r.Format(GlobalUtilities::get_resource_string(IDS_UseExistingFile)+"\"%s\" ?",protfile);
			if (IDYES != AfxMessageBox(r,MB_YESNO,0))
			{
				return "";
			}
		}
	}

	return protfile;
}

//**************************************************************************
//*
//*		reduce_voicename, applied for indef voicenames
//*		cuts voinename behind '}' or before '('
//*
//**************************************************************************

void GlobalUtilities::reduce_voicename(CString *voicename)
{
	CString vn = (*voicename).Left(30);
	int stop_index;

	// stop before '('
	stop_index = vn.Find('(');
	if (stop_index != -1)
	{
		vn = vn.Left(stop_index-1);
	}

	// stop behind '}'
	stop_index = vn.Find('}');
	if (stop_index != -1)
	{
		vn = vn.Left(stop_index+1);
	}

	*voicename = vn;
}

//**************************************************************************
//*
//*		get_sysex_parno_effectno
//*		called from classes SysExEventProt, XgEffects
//*
//**************************************************************************

bool GlobalUtilities::get_sysex_parno_effectno(int AdrH, int AdrL, int DataMSB, int DataLSB, int *par_no, int *effect_no)
{
	if (AdrH == 2)
	{
		switch (AdrL)
		{
		case 0x02:
		case 0x22:
			*par_no = 1;
			*effect_no = DataMSB;
			break;
		case 0x42:
			*par_no = 1;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x03:
		case 0x23:
			*par_no = 2;
			*effect_no = DataMSB;
			break;
		case 0x44:
			*par_no = 2;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x04:
		case 0x24:
			*par_no = 3;
			*effect_no = DataMSB;
			break;
		case 0x46:
			*par_no = 3;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x05:
		case 0x25:
			*par_no = 4;
			*effect_no = DataMSB;
			break;
		case 0x48:
			*par_no = 4;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x06:
		case 0x26:
			*par_no = 5;
			*effect_no = DataMSB;
			break;
		case 0x4a:
			*par_no = 5;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x07:
		case 0x27:
			*par_no = 6;
			*effect_no = DataMSB;
			break;
		case 0x4c:
			*par_no = 6;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x08:
		case 0x28:
			*par_no = 7;
			*effect_no = DataMSB;
			break;
		case 0x4e:
			*par_no = 7;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x09:
		case 0x29:
			*par_no = 8;
			*effect_no = DataMSB;
			break;
		case 0x50:
			*par_no = 8;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x0a:
		case 0x2a:
			*par_no = 9;
			*effect_no = DataMSB;
			break;
		case 0x52:
			*par_no = 9;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x0b:
		case 0x2b:
			*par_no = 10;
			*effect_no = DataMSB;
			break;
		case 0x54:
			*par_no = 10;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x10:
		case 0x30:
		case 0x70:
			*par_no = 11;
			*effect_no = DataMSB;
			break;
		case 0x11:
		case 0x31:
		case 0x71:
			*par_no = 12;
			*effect_no = DataMSB;
			break;
		case 0x12:
		case 0x32:
		case 0x72:
			*par_no = 13;
			*effect_no = DataMSB;
			break;
		case 0x13:
		case 0x33:
		case 0x73:
			*par_no = 14;
			*effect_no = DataMSB;
			break;
		case 0x14:
		case 0x34:
		case 0x74:
			*par_no = 15;
			*effect_no = DataMSB;
			break;
		case 0x15:
		case 0x35:
		case 0x75:
			*par_no = 18;
			*effect_no = DataMSB;
			break;
		default:
			return false;
		}
		return true;
	}

	if (AdrH == 3)
	{
		switch (AdrL)
		{
		case 0x02:
			*par_no = 1;
			*effect_no = DataMSB;
			break;
		case 0x03:
			*par_no = 2;
			*effect_no = DataMSB;
			break;
		case 0x04:
			*par_no = 3;
			*effect_no = DataMSB;
			break;
		case 0x05:
			*par_no = 4;
			*effect_no = DataMSB;
			break;
		case 0x06:
			*par_no = 5;
			*effect_no = DataMSB;
			break;
		case 0x07:
			*par_no = 6;
			*effect_no = DataMSB;
			break;
		case 0x08:
			*par_no = 7;
			*effect_no = DataMSB;
			break;
		case 0x09:
			*par_no = 8;
			*effect_no = DataMSB;
			break;
		case 0x0a:
			*par_no = 9;
			*effect_no = DataMSB;
			break;
		case 0x0b:
			*par_no = 10;
			*effect_no = DataMSB;
			break;
		case 0x30:
			*par_no = 1;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x32:
			*par_no = 2;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x34:
			*par_no = 3;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x36:
			*par_no = 4;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x38:
			*par_no = 5;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x3a:
			*par_no = 6;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x3c:
			*par_no = 7;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x3e:
			*par_no = 8;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x40:
			*par_no = 9;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x42:
			*par_no = 10;
			*effect_no = 128*DataMSB+DataLSB;
			break;
		case 0x20:
			*par_no = 11;
			*effect_no = DataMSB;
			break;
		case 0x21:
			*par_no = 12;
			*effect_no = DataMSB;
			break;
		case 0x22:
			*par_no = 13;
			*effect_no = DataMSB;
			break;
		case 0x23:
			*par_no = 14;
			*effect_no = DataMSB;
			break;
		case 0x24:
			*par_no = 15;
			*effect_no = DataMSB;
			break;
		case 0x25:
			*par_no = 16;
			*effect_no = DataMSB;
			break;
		default:
			return false;
		}
		return true;;
	}

	return false; // AdrH != 0x02, 0x03
}

#endif


//**************************************************************************
//*
//*		data
//*
//**************************************************************************


unsigned char GlobalUtilities::gm_on_data[6] =
	{0xf0, 0x7e, 0x7f, 0x09, 0x01, 0xf7};

unsigned char GlobalUtilities::xg_on_data[9] =
	{0xf0, 0x43, 0x10, 0x4c, 0x00, 0x00, 0x7e, 0x00, 0xf7};

unsigned char GlobalUtilities::turn_tg300b_on_data[11] =
{0xf0, 0x41, 0x10, 0x42, 0x12, 0x40, 0x00, 0x7f, 0x00, 0x41, 0xf7};

unsigned char GlobalUtilities::lyrics_part_score_on_data[10] =
{0xf0, 0x43, 0x73, 0x01, 0x50, 0x12, 0x00, 0x02, 0x7F, 0xf7};

unsigned char GlobalUtilities::chord_part_score_on_data[10] =
{0xf0, 0x43, 0x73, 0x01, 0x50, 0x12, 0x00, 0x03, 0x7F, 0xf7};

unsigned char GlobalUtilities::score_layout_data[10] =
{0xf0, 0x43, 0x73, 0x01, 0x50, 0x12, 0x00, 0x00, 0x00, 0xf7};

// unsigned char GlobalUtilities::score_representation_medium_data[10] =
// {0xf0, 0x43, 0x73, 0x01, 0x50, 0x12, 0x00, 0x05, 0x01, 0xf7};


const CString GlobalUtilities::start_lyriclist = "[start lyriclist]"; // without time
const CString GlobalUtilities::start_sysexlist = "[start sysexlist]";
const CString GlobalUtilities::start_sysexlist_mbt = "[start sysexlist mbt]";
const CString GlobalUtilities::start_revoicelist = "[start revoicelist]";
const CString GlobalUtilities::start_drumlist = "[start drumlist]";
const CString GlobalUtilities::start_timelist_mbt = "[start timelist mbt]";
const CString GlobalUtilities::start_chords_lyrics	= "[start chords+lyrics]";	// with time
const CString GlobalUtilities::end_list				= "[end list]";	// with and without time

const CString GlobalUtilities::empty_xfhd = "XFhd:::-:-:1:no:::::";
const CString GlobalUtilities::empty_xfln = "XFln:L1::::";

unsigned char GlobalUtilities::xfversion[13] =
	{0xff, 0x7f, 0x09, 0x43, 0x7b, 0x00, 0x58, 0x46, 0x30, 0x32, 0x00, 0x00};
const int GlobalUtilities::xfversion_len = 12;

unsigned char GlobalUtilities::quickstart[9] =
	{0xff, 0x7f, 0x06, 0x43, 0x73, 0x0a, 0x00, 0x04, 0x01};
const int GlobalUtilities::quickstart_len = 9;

const unsigned char GlobalUtilities::guidetrackflag[8] =
	{0xff, 0x7f, 0x05, 0x43, 0x7b, 0x0c, 0x00, 0x00};
const int GlobalUtilities::guidetrackflag_len = 8;

const unsigned char GlobalUtilities::plus_table_sharp[0x68] =
{	// transpose +1
	0x00,	// 0x00		not used
	0x46,	// 0x01	Cbbb -> A#
	0x31,	// 0x02	Dbbb -> C
	0x32,	// 0x03 Ebbb -> D
	0x42,	// 0x04 Fbbb -> D#
	0x34,	// 0x05 Gbbb -> F
	0x35,	// 0x06 Abbb -> G
	0x36,	// 0x07 Bbbb -> A
	0x00,	// 0x08
	0x00,	// 0x09
	0x00,	// 0x0a
	0x00,	// 0x0b
	0x00,	// 0x0c
	0x00,	// 0x0d
	0x00,	// 0x0e
	0x00,	// 0x0f
	0x00,	// 0x10		not used
	0x37,	// 0x11 Cbb -> B
	0x41,	// 0x12 Dbb -> C#
	0x42,	// 0x13 Ebb -> D#
	0x33,	// 0x14 Fbb -> E
	0x44,	// 0x15 Gbb -> F#
	0x45,	// 0x16 Abb -> G#
	0x46,	// 0x17 Bbb -> A#
	0x00,	// 0x18
	0x00,	// 0x19
	0x00,	// 0x1a
	0x00,	// 0x1b
	0x00,	// 0x1c
	0x00,	// 0x1d
	0x00,	// 0x1e
	0x00,	// 0x1f
	0x00,	// 0x20		not used
	0x31,	// 0x21 Cb -> C
	0x32,	// 0x22 Db -> D
	0x33,	// 0x23 Eb -> E
	0x34,	// 0x24 Fb -> F
	0x35,	// 0x25 Gb -> G
	0x36,	// 0x26 Ab -> A
	0x37,	// 0x27 Bb -> B
	0x00,	// 0x28
	0x00,	// 0x29
	0x00,	// 0x2a
	0x00,	// 0x2b
	0x00,	// 0x2c
	0x00,	// 0x2d
	0x00,	// 0x2e
	0x00,	// 0x2f
	0x00,	// 0x30		not used
	0x41,	// 0x31 C -> C#
	0x42,	// 0x32 D -> D#
	0x34,	// 0x33 E -> F
	0x44,	// 0x34 F -> F#
	0x45,	// 0x35 G -> G#
	0x46,	// 0x36 A -> A#
	0x31,	// 0x37 B -> C
	0x00,	// 0x38
	0x00,	// 0x39
	0x00,	// 0x3a
	0x00,	// 0x3b
	0x00,	// 0x3c
	0x00,	// 0x3d
	0x00,	// 0x3e
	0x00,	// 0x3f
	0x00,	// 0x40		not used
	0x32,	// 0x41 C# -> D
	0x33,	// 0x42 D# -> E
	0x44,	// 0x43 E# -> F#
	0x35,	// 0x44 F# -> G
	0x36,	// 0x45 G# -> A
	0x37,	// 0x46 A# -> B
	0x41,	// 0x47 B# -> C#
	0x00,	// 0x48
	0x00,	// 0x49
	0x00,	// 0x4a
	0x00,	// 0x4b
	0x00,	// 0x4c
	0x00,	// 0x4d
	0x00,	// 0x4e
	0x00,	// 0x4f
	0x00,	// 0x50		not used
	0x42,	// 0x51 C## -> D#
	0x34,	// 0x52 D## -> F
	0x35,	// 0x53 E## -> G
	0x45,	// 0x54 F## -> G#
	0x46,	// 0x55 G## -> A#
	0x31,	// 0x56 A## -> C
	0x32,	// 0x57 B## -> D
	0x00,	// 0x58
	0x00,	// 0x59
	0x00,	// 0x5a
	0x00,	// 0x5b
	0x00,	// 0x5c
	0x00,	// 0x5d
	0x00,	// 0x5e
	0x00,	// 0x5f
	0x00,	// 0x60		not used
	0x33,	// 0x61 C### -> E
	0x44,	// 0x62 D### -> F#
	0x45,	// 0x63 E### -> G#
	0x36,	// 0x64 F### -> A
	0x37,	// 0x65 G### -> B
	0x41,	// 0x66 A### -> C#
	0x42	// 0x67 B### -> D#
};

const unsigned char GlobalUtilities::plus_table_flat[0x68] =
{	// transpose +1
	0x00,	// 0x00		not used
	0x27,	// 0x01	Cbbb -> Bb
	0x31,	// 0x02	Dbbb -> C
	0x32,	// 0x03 Ebbb -> D
	0x23,	// 0x04 Fbbb -> Eb
	0x34,	// 0x05 Gbbb -> F
	0x35,	// 0x06 Abbb -> G
	0x36,	// 0x07 Bbbb -> A
	0x00,	// 0x08
	0x00,	// 0x09
	0x00,	// 0x0a
	0x00,	// 0x0b
	0x00,	// 0x0c
	0x00,	// 0x0d
	0x00,	// 0x0e
	0x00,	// 0x0f
	0x00,	// 0x10		not used
	0x37,	// 0x11 Cbb -> B
	0x22,	// 0x12 Dbb -> Db
	0x23,	// 0x13 Ebb -> Eb
	0x33,	// 0x14 Fbb -> E
	0x25,	// 0x15 Gbb -> Gb
	0x26,	// 0x16 Abb -> Ab
	0x27,	// 0x17 Bbb -> Bb
	0x00,	// 0x18
	0x00,	// 0x19
	0x00,	// 0x1a
	0x00,	// 0x1b
	0x00,	// 0x1c
	0x00,	// 0x1d
	0x00,	// 0x1e
	0x00,	// 0x1f
	0x00,	// 0x20		not used
	0x31,	// 0x21 Cb -> C
	0x32,	// 0x22 Db -> D
	0x33,	// 0x23 Eb -> E
	0x34,	// 0x24 Fb -> F
	0x35,	// 0x25 Gb -> G
	0x36,	// 0x26 Ab -> A
	0x37,	// 0x27 Bb -> B
	0x00,	// 0x28
	0x00,	// 0x29
	0x00,	// 0x2a
	0x00,	// 0x2b
	0x00,	// 0x2c
	0x00,	// 0x2d
	0x00,	// 0x2e
	0x00,	// 0x2f
	0x00,	// 0x30		not used
	0x22,	// 0x31 C -> Db
	0x23,	// 0x32 D -> Eb
	0x34,	// 0x33 E -> F
	0x25,	// 0x34 F -> Gb
	0x26,	// 0x35 G -> Ab
	0x27,	// 0x36 A -> Bb
	0x31,	// 0x37 B -> C
	0x00,	// 0x38
	0x00,	// 0x39
	0x00,	// 0x3a
	0x00,	// 0x3b
	0x00,	// 0x3c
	0x00,	// 0x3d
	0x00,	// 0x3e
	0x00,	// 0x3f
	0x00,	// 0x40		not used
	0x32,	// 0x41 C# -> D
	0x33,	// 0x42 D# -> E
	0x25,	// 0x43 E# -> Gb
	0x35,	// 0x44 F# -> G
	0x36,	// 0x45 G# -> A
	0x37,	// 0x46 A# -> B
	0x22,	// 0x47 B# -> Db
	0x00,	// 0x48
	0x00,	// 0x49
	0x00,	// 0x4a
	0x00,	// 0x4b
	0x00,	// 0x4c
	0x00,	// 0x4d
	0x00,	// 0x4e
	0x00,	// 0x4f
	0x00,	// 0x50		not used
	0x23,	// 0x51 C## -> Eb
	0x34,	// 0x52 D## -> F
	0x35,	// 0x53 E## -> G
	0x26,	// 0x54 F## -> Ab
	0x27,	// 0x55 G## -> Bb
	0x31,	// 0x56 A## -> C
	0x32,	// 0x57 B## -> D
	0x00,	// 0x58
	0x00,	// 0x59
	0x00,	// 0x5a
	0x00,	// 0x5b
	0x00,	// 0x5c
	0x00,	// 0x5d
	0x00,	// 0x5e
	0x00,	// 0x5f
	0x00,	// 0x60		not used
	0x33,	// 0x61 C### -> E
	0x25,	// 0x62 D### -> Gb
	0x26,	// 0x63 E### -> Ab
	0x36,	// 0x64 F### -> A
	0x37,	// 0x65 G### -> B
	0x22,	// 0x66 A### -> Db
	0x23	// 0x67 B### -> Eb
};

const unsigned char GlobalUtilities::minus_table_sharp[0x68] =
{	// transpose +1
	0x00,	// 0x00		not used
	0x45,	// 0x01	Cbbb -> G#
	0x46,	// 0x02	Dbbb -> A#
	0x31,	// 0x03 Ebbb -> C
	0x41,	// 0x04 Fbbb -> C#
	0x42,	// 0x05 Gbbb -> D#
	0x34,	// 0x06 Abbb -> F
	0x35,	// 0x07 Bbbb -> G
	0x00,	// 0x08
	0x00,	// 0x09
	0x00,	// 0x0a
	0x00,	// 0x0b
	0x00,	// 0x0c
	0x00,	// 0x0d
	0x00,	// 0x0e
	0x00,	// 0x0f
	0x00,	// 0x10		not used
	0x36,	// 0x11 Cbb -> A
	0x37,	// 0x12 Dbb -> B
	0x41,	// 0x13 Ebb -> C#
	0x32,	// 0x14 Fbb -> D
	0x33,	// 0x15 Gbb -> E
	0x44,	// 0x16 Abb -> F#
	0x45,	// 0x17 Bbb -> G#
	0x00,	// 0x18
	0x00,	// 0x19
	0x00,	// 0x1a
	0x00,	// 0x1b
	0x00,	// 0x1c
	0x00,	// 0x1d
	0x00,	// 0x1e
	0x00,	// 0x1f
	0x00,	// 0x20		not used
	0x46,	// 0x21 Cb -> A#
	0x31,	// 0x22 Db -> C
	0x32,	// 0x23 Eb -> D
	0x42,	// 0x24 Fb -> D#
	0x34,	// 0x25 Gb -> F
	0x35,	// 0x26 Ab -> G
	0x36,	// 0x27 Bb -> A
	0x00,	// 0x28
	0x00,	// 0x29
	0x00,	// 0x2a
	0x00,	// 0x2b
	0x00,	// 0x2c
	0x00,	// 0x2d
	0x00,	// 0x2e
	0x00,	// 0x2f
	0x00,	// 0x30		not used
	0x37,	// 0x31 C -> B
	0x41,	// 0x32 D -> C#
	0x42,	// 0x33 E -> D#
	0x33,	// 0x34 F -> E
	0x44,	// 0x35 G -> F#
	0x45,	// 0x36 A -> G#
	0x46,	// 0x37 B -> A#
	0x00,	// 0x38
	0x00,	// 0x39
	0x00,	// 0x3a
	0x00,	// 0x3b
	0x00,	// 0x3c
	0x00,	// 0x3d
	0x00,	// 0x3e
	0x00,	// 0x3f
	0x00,	// 0x40		not used
	0x31,	// 0x41 C# -> C
	0x32,	// 0x42 D# -> D
	0x33,	// 0x43 E# -> E
	0x34,	// 0x44 F# -> F
	0x35,	// 0x45 G# -> G
	0x36,	// 0x46 A# -> A
	0x37,	// 0x47 B# -> B
	0x00,	// 0x48
	0x00,	// 0x49
	0x00,	// 0x4a
	0x00,	// 0x4b
	0x00,	// 0x4c
	0x00,	// 0x4d
	0x00,	// 0x4e
	0x00,	// 0x4f
	0x00,	// 0x50		not used
	0x41,	// 0x51 C## -> C#
	0x42,	// 0x52 D## -> D#
	0x34,	// 0x53 E## -> F
	0x44,	// 0x54 F## -> F#
	0x45,	// 0x55 G## -> G#
	0x46,	// 0x56 A## -> A#
	0x31,	// 0x57 B## -> C
	0x00,	// 0x58
	0x00,	// 0x59
	0x00,	// 0x5a
	0x00,	// 0x5b
	0x00,	// 0x5c
	0x00,	// 0x5d
	0x00,	// 0x5e
	0x00,	// 0x5f
	0x00,	// 0x60		not used
	0x32,	// 0x61 C### -> D
	0x33,	// 0x62 D### -> E
	0x44,	// 0x63 E### -> F#
	0x35,	// 0x64 F### -> G
	0x36,	// 0x65 G### -> A
	0x37,	// 0x66 A### -> B
	0x41	// 0x67 B### -> C#
};

const unsigned char GlobalUtilities::minus_table_flat[0x68] =
{	// transpose +1
	0x00,	// 0x00		not used
	0x26,	// 0x01	Cbbb -> Ab
	0x27,	// 0x02	Dbbb -> Bb
	0x31,	// 0x03 Ebbb -> C
	0x42,	// 0x04 Fbbb -> Db
	0x43,	// 0x05 Gbbb -> Eb
	0x34,	// 0x06 Abbb -> F
	0x35,	// 0x07 Bbbb -> G
	0x00,	// 0x08
	0x00,	// 0x09
	0x00,	// 0x0a
	0x00,	// 0x0b
	0x00,	// 0x0c
	0x00,	// 0x0d
	0x00,	// 0x0e
	0x00,	// 0x0f
	0x00,	// 0x10		not used
	0x36,	// 0x11 Cbb -> A
	0x37,	// 0x12 Dbb -> B
	0x22,	// 0x13 Ebb -> Db
	0x32,	// 0x14 Fbb -> D
	0x33,	// 0x15 Gbb -> E
	0x25,	// 0x16 Abb -> Gb
	0x26,	// 0x17 Bbb -> Ab
	0x00,	// 0x18
	0x00,	// 0x19
	0x00,	// 0x1a
	0x00,	// 0x1b
	0x00,	// 0x1c
	0x00,	// 0x1d
	0x00,	// 0x1e
	0x00,	// 0x1f
	0x00,	// 0x20		not used
	0x27,	// 0x21 Cb -> Bb
	0x31,	// 0x22 Db -> C
	0x32,	// 0x23 Eb -> D
	0x23,	// 0x24 Fb -> Eb
	0x34,	// 0x25 Gb -> F
	0x35,	// 0x26 Ab -> G
	0x36,	// 0x27 Bb -> A
	0x00,	// 0x28
	0x00,	// 0x29
	0x00,	// 0x2a
	0x00,	// 0x2b
	0x00,	// 0x2c
	0x00,	// 0x2d
	0x00,	// 0x2e
	0x00,	// 0x2f
	0x00,	// 0x30		not used
	0x37,	// 0x31 C -> B
	0x22,	// 0x32 D -> Db
	0x23,	// 0x33 E -> Eb
	0x33,	// 0x34 F -> E
	0x25,	// 0x35 G -> Gb
	0x26,	// 0x36 A -> Ab
	0x27,	// 0x37 B -> Bb
	0x00,	// 0x38
	0x00,	// 0x39
	0x00,	// 0x3a
	0x00,	// 0x3b
	0x00,	// 0x3c
	0x00,	// 0x3d
	0x00,	// 0x3e
	0x00,	// 0x3f
	0x00,	// 0x40		not used
	0x31,	// 0x41 C# -> C
	0x32,	// 0x42 D# -> D
	0x33,	// 0x43 E# -> E
	0x34,	// 0x44 F# -> F
	0x35,	// 0x45 G# -> G
	0x36,	// 0x46 A# -> A
	0x37,	// 0x47 B# -> B
	0x00,	// 0x48
	0x00,	// 0x49
	0x00,	// 0x4a
	0x00,	// 0x4b
	0x00,	// 0x4c
	0x00,	// 0x4d
	0x00,	// 0x4e
	0x00,	// 0x4f
	0x00,	// 0x50		not used
	0x22,	// 0x51 C## -> Db
	0x23,	// 0x52 D## -> Eb
	0x34,	// 0x53 E## -> F
	0x25,	// 0x54 F## -> Gb
	0x26,	// 0x55 G## -> Ab
	0x27,	// 0x56 A## -> Bb
	0x31,	// 0x57 B## -> C
	0x00,	// 0x58
	0x00,	// 0x59
	0x00,	// 0x5a
	0x00,	// 0x5b
	0x00,	// 0x5c
	0x00,	// 0x5d
	0x00,	// 0x5e
	0x00,	// 0x5f
	0x00,	// 0x60		not used
	0x32,	// 0x61 C### -> D
	0x33,	// 0x62 D### -> E
	0x25,	// 0x63 E### -> Gb
	0x35,	// 0x64 F### -> G
	0x36,	// 0x65 G### -> A
	0x37,	// 0x66 A### -> B
	0x22	// 0x67 B### -> Db
};

const unsigned char GlobalUtilities::null_table_sharp[0x68] =
{	// transpose 0
	0x00,	// 0x00		not used
	0x36,	// 0x01	Cbbb -> A
	0x37,	// 0x02	Dbbb -> B
	0x41,	// 0x03 Ebbb -> C#
	0x32,	// 0x04 Fbbb -> D
	0x33,	// 0x05 Gbbb -> E
	0x44,	// 0x06 Abbb -> F#
	0x45,	// 0x07 Bbbb -> G#
	0x00,	// 0x08
	0x00,	// 0x09
	0x00,	// 0x0a
	0x00,	// 0x0b
	0x00,	// 0x0c
	0x00,	// 0x0d
	0x00,	// 0x0e
	0x00,	// 0x0f
	0x00,	// 0x10		not used
	0x46,	// 0x11 Cbb -> A#
	0x31,	// 0x12 Dbb -> C
	0x32,	// 0x13 Ebb -> D
	0x43,	// 0x14 Fbb -> D#
	0x34,	// 0x15 Gbb -> F
	0x35,	// 0x16 Abb -> G
	0x36,	// 0x17 Bbb -> A
	0x00,	// 0x18
	0x00,	// 0x19
	0x00,	// 0x1a
	0x00,	// 0x1b
	0x00,	// 0x1c
	0x00,	// 0x1d
	0x00,	// 0x1e
	0x00,	// 0x1f
	0x00,	// 0x20		not used
	0x37,	// 0x21 Cb -> B
	0x41,	// 0x22 Db -> C#
	0x42,	// 0x23 Eb -> D#
	0x33,	// 0x24 Fb -> E
	0x44,	// 0x25 Gb -> F#
	0x45,	// 0x26 Ab -> G#
	0x46,	// 0x27 Bb -> A#
	0x00,	// 0x28
	0x00,	// 0x29
	0x00,	// 0x2a
	0x00,	// 0x2b
	0x00,	// 0x2c
	0x00,	// 0x2d
	0x00,	// 0x2e
	0x00,	// 0x2f
	0x00,	// 0x30		not used
	0x31,	// 0x31 C -> C
	0x32,	// 0x32 D -> D
	0x33,	// 0x33 E -> E
	0x34,	// 0x34 F -> F
	0x35,	// 0x35 G -> G
	0x36,	// 0x36 A -> A
	0x37,	// 0x37 B -> B
	0x00,	// 0x38
	0x00,	// 0x39
	0x00,	// 0x3a
	0x00,	// 0x3b
	0x00,	// 0x3c
	0x00,	// 0x3d
	0x00,	// 0x3e
	0x00,	// 0x3f
	0x00,	// 0x40		not used
	0x41,	// 0x41 C# -> C#
	0x42,	// 0x42 D# -> D#
	0x43,	// 0x43 E# -> E#
	0x44,	// 0x44 F# -> F#
	0x45,	// 0x45 G# -> G#
	0x46,	// 0x46 A# -> A#
	0x31,	// 0x47 B# -> C
	0x00,	// 0x48
	0x00,	// 0x49
	0x00,	// 0x4a
	0x00,	// 0x4b
	0x00,	// 0x4c
	0x00,	// 0x4d
	0x00,	// 0x4e
	0x00,	// 0x4f
	0x00,	// 0x50		not used
	0x32,	// 0x51 C## -> D
	0x33,	// 0x52 D## -> E
	0x44,	// 0x53 E## -> F#
	0x35,	// 0x54 F## -> G
	0x36,	// 0x55 G## -> A
	0x37,	// 0x56 A## -> B
	0x41,	// 0x57 B## -> C#
	0x00,	// 0x58
	0x00,	// 0x59
	0x00,	// 0x5a
	0x00,	// 0x5b
	0x00,	// 0x5c
	0x00,	// 0x5d
	0x00,	// 0x5e
	0x00,	// 0x5f
	0x00,	// 0x60		not used
	0x42,	// 0x61 C### -> D#
	0x34,	// 0x62 D### -> F
	0x35,	// 0x63 E### -> G
	0x45,	// 0x64 F### -> G#
	0x46,	// 0x65 G### -> A#
	0x31,	// 0x66 A### -> C
	0x32	// 0x67 B### -> D
};

const unsigned char GlobalUtilities::null_table_flat[0x68] =
{	// transpose 0
	0x00,	// 0x00		not used
	0x36,	// 0x01	Cbbb -> A
	0x37,	// 0x02	Dbbb -> B
	0x22,	// 0x03 Ebbb -> Db
	0x32,	// 0x04 Fbbb -> D
	0x33,	// 0x05 Gbbb -> E
	0x25,	// 0x06 Abbb -> Gb
	0x26,	// 0x07 Bbbb -> Ab
	0x00,	// 0x08
	0x00,	// 0x09
	0x00,	// 0x0a
	0x00,	// 0x0b
	0x00,	// 0x0c
	0x00,	// 0x0d
	0x00,	// 0x0e
	0x00,	// 0x0f
	0x00,	// 0x10		not used
	0x27,	// 0x11 Cbb -> Bb
	0x31,	// 0x12 Dbb -> C
	0x32,	// 0x13 Ebb -> D
	0x23,	// 0x14 Fbb -> Eb
	0x34,	// 0x15 Gbb -> F
	0x35,	// 0x16 Abb -> G
	0x36,	// 0x17 Bbb -> A
	0x00,	// 0x18
	0x00,	// 0x19
	0x00,	// 0x1a
	0x00,	// 0x1b
	0x00,	// 0x1c
	0x00,	// 0x1d
	0x00,	// 0x1e
	0x00,	// 0x1f
	0x00,	// 0x20		not used
	0x37,	// 0x21 Cb -> B
	0x22,	// 0x22 Db -> Db
	0x23,	// 0x23 Eb -> Eb
	0x33,	// 0x24 Fb -> E
	0x25,	// 0x25 Gb -> Gb
	0x26,	// 0x26 Ab -> Ab
	0x27,	// 0x27 Bb -> Bb
	0x00,	// 0x28
	0x00,	// 0x29
	0x00,	// 0x2a
	0x00,	// 0x2b
	0x00,	// 0x2c
	0x00,	// 0x2d
	0x00,	// 0x2e
	0x00,	// 0x2f
	0x00,	// 0x30		not used
	0x31,	// 0x31 C -> C
	0x32,	// 0x32 D -> D
	0x33,	// 0x33 E -> E
	0x34,	// 0x34 F -> F
	0x35,	// 0x35 G -> G
	0x36,	// 0x36 A -> A
	0x37,	// 0x37 B -> B
	0x00,	// 0x38
	0x00,	// 0x39
	0x00,	// 0x3a
	0x00,	// 0x3b
	0x00,	// 0x3c
	0x00,	// 0x3d
	0x00,	// 0x3e
	0x00,	// 0x3f
	0x00,	// 0x40		not used
	0x22,	// 0x41 C# -> Db
	0x23,	// 0x42 D# -> Eb
	0x34,	// 0x43 E# -> F
	0x25,	// 0x44 F# -> Gb
	0x26,	// 0x45 G# -> Ab
	0x27,	// 0x46 A# -> Bb
	0x31,	// 0x47 B# -> C
	0x00,	// 0x48
	0x00,	// 0x49
	0x00,	// 0x4a
	0x00,	// 0x4b
	0x00,	// 0x4c
	0x00,	// 0x4d
	0x00,	// 0x4e
	0x00,	// 0x4f
	0x00,	// 0x50		not used
	0x32,	// 0x51 C## -> D
	0x33,	// 0x52 D## -> E
	0x25,	// 0x53 E## -> Gb
	0x35,	// 0x54 F## -> G
	0x36,	// 0x55 G## -> A
	0x37,	// 0x56 A## -> B
	0x22,	// 0x57 B## -> Db
	0x00,	// 0x58
	0x00,	// 0x59
	0x00,	// 0x5a
	0x00,	// 0x5b
	0x00,	// 0x5c
	0x00,	// 0x5d
	0x00,	// 0x5e
	0x00,	// 0x5f
	0x00,	// 0x60		not used
	0x23,	// 0x61 C### -> Eb
	0x34,	// 0x62 D### -> F
	0x35,	// 0x63 E### -> G
	0x26,	// 0x64 F### -> Ab
	0x27,	// 0x65 G### -> Bb
	0x31,	// 0x66 A### -> C
	0x32	// 0x67 B### -> D
};

// Chord-lists
const CString GlobalUtilities::cr03_list[] =
{"bbb","bb","b","","#","##","###"};
const int GlobalUtilities::cr03_list_length = 7;

const CString GlobalUtilities::cr47_list[] =
{"","C","D","E","F","G","A","B"};
const int GlobalUtilities::cr47_list_length = 8;

const CString GlobalUtilities::ct_list[] =
{
	"   ",			// 0
    "Maj6",
	"Maj7",
	"Maj7(#11)",
	"Maj9",
	"Maj7(9)",
	"Maj6(9)",
	"aug",
	"m  ",
	"m6 ",
	"m7 ",			// 10
	"m7b5",
	"m9 ",
	"m7(9)",
	"m7(11)",
	"minMaj7",
	"minMaj7(9)",
	"dim",
	"dim7",
	"7  ",
	"7sus4",		// 20
	"7b5",
	"7(9)",
	"7(#11)",
	"7(13)",
	"7(b9)",
	"7(b13)",
	"7(#9)",
	"Maj7aug",
	"7aug",
	"1+8",			// 30
	"1+5",
	"sus4",
	"sus2",
	"cc"			// 34
};
const int GlobalUtilities::ct_list_length = 35;

#if defined(ADD_PSRUTI_FUNCTIONS)

const CString GlobalUtilities::init_takt_lyric = ".-- "; // \r = 0x0d
const CString GlobalUtilities::init_beat_lyric = "--- ";
const CString GlobalUtilities::init_end_lyric = "---";

// list to get the correct enharmonic chord
// first: key, second true if flat (b), else sharp (#)
const GlobalUtilities::FLAT_SHARP_ELEM GlobalUtilities::flat_sharp_list[30] =
{
	{"C",true},
	{"F",true},
	{"G",false},
	{"Bb",true},
	{"D",false},
	{"A",false},
	{"E",false},
	{"Eb",true},
	{"Ab",true},
	{"Db",true},
	{"Gb",true},
	{"Cb",true},
	{"B",false},
	{"F#",false},
	{"C#",false},
	{"Cm",true},
	{"Fm",true},
	{"Gm",true},
	{"Bbm",true},
	{"Dm",true},
	{"Am",false},
	{"Em",false},
	{"Ebm",true},
	{"Abm",true}, // 16.05.09
	{"Dbm",true}, //
	{"Gbm",true}, //
	{"Cbm",true}, //
	{"Bm",false},
	{"F#m",false},
	{"C#m",false}
};

const GlobalUtilities::NOTE_NAME_ELEM GlobalUtilities::note_name_list[NO_NOTE_NAME_ELEMS] =
{
	{"C-2",0},
	{"C#-2",1},
	{"Db-2",1},
	{"D-2",2},
	{"D#-2",3},
	{"Eb-2",3},
	{"E-2",4},
	{"F-2",5},
	{"F#-2",6},
	{"Gb-2",6},
	{"G-2",7},
	{"G#-2",8},
	{"Ab-2",8},
	{"A-2",9},
	{"A#-2",10},
	{"Bb-2",10},
	{"B-2",11},
	{"C-1",12},
	{"C#-1",13},
	{"Db-1",13},
	{"D-1",14},
	{"D#-1",15},
	{"Eb-1",15},
	{"E-1",16},
	{"F-1",17},
	{"F#-1",18},
	{"Gb-1",18},
	{"G-1",19},
	{"G#-1",20},
	{"Ab-1",20},
	{"A-1",21},
	{"A#-1",22},
	{"Bb-1",22},
	{"B-1",23},
	{"C0",24},
	{"C#0",25},
	{"Db0",25},
	{"D0",26},
	{"D#0",27},
	{"Eb0",27},
	{"E0",28},
	{"F0",29},
	{"F#0",30},
	{"Gb0",30},
	{"G0",31},
	{"G#0",32},
	{"Ab0",32},
	{"A0",33},
	{"A#0",34},
	{"Bb0",34},
	{"B0",35},
	{"C1",36},
	{"C#1",37},
	{"Db1",37},
	{"D1",38},
	{"D#1",39},
	{"Eb1",39},
	{"E1",40},
	{"F1",41},
	{"F#1",42},
	{"Gb1",42},
	{"G1",43},
	{"G#1",44},
	{"Ab1",44},
	{"A1",45},
	{"A#1",46},
	{"Bb1",46},
	{"B1",47},
	{"C2",48},
	{"C#2",49},
	{"Db2",49},
	{"D2",50},
	{"D#2",51},
	{"Eb2",51},
	{"E2",52},
	{"F2",53},
	{"F#2",54},
	{"Gb2",54},
	{"G2",55},
	{"G#2",56},
	{"Ab2",56},
	{"A2",57},
	{"A#2",58},
	{"Bb2",58},
	{"B2",59},
	{"C3",60},
	{"C#3",61},
	{"Db3",61},
	{"D3",62},
	{"D#3",63},
	{"Eb3",63},
	{"E3",64},
	{"F3",65},
	{"F#3",66},
	{"Gb3",66},
	{"G3",67},
	{"G#3",68},
	{"Ab3",68},
	{"A3",69},
	{"A#3",70},
	{"Bb3",70},
	{"B3",71},
	{"C4",72},
	{"C#4",73},
	{"Db4",73},
	{"D4",74},
	{"D#4",75},
	{"Eb4",75},
	{"E4",76},
	{"F4",77},
	{"F#4",78},
	{"Gb4",78},
	{"G4",79},
	{"G#4",80},
	{"Ab4",80},
	{"A4",81},
	{"A#4",82},
	{"Bb4",82},
	{"B4",83},
	{"C5",84},
	{"C#5",85},
	{"Db5",85},
	{"D5",86},
	{"D#5",87},
	{"Eb5",87},
	{"E5",88},
	{"F5",89},
	{"F#5",90},
	{"Gb5",90},
	{"G5",91},
	{"G#5",92},
	{"Ab5",92},
	{"A5",93},
	{"A#5",94},
	{"Bb5",94},
	{"B5",95},
	{"C6",96},
	{"C#6",97},
	{"Db6",97},
	{"D6",98},
	{"D#6",99},
	{"Eb6",99},
	{"E6",100},
	{"F6",101},
	{"F#6",102},
	{"Gb6",102},
	{"G6",103},
	{"G#6",104},
	{"Ab6",104},
	{"A6",105},
	{"A#6",106},
	{"Bb6",106},
	{"B6",107},
	{"C7",108},
	{"C#7",109},
	{"Db7",109},
	{"D7",110},
	{"D#7",111},
	{"Eb7",111},
	{"E7",112},
	{"F7",113},
	{"F#7",114},
	{"Gb7",114},
	{"G7",115},
	{"G#7",116},
	{"Ab7",116},
	{"A7",117},
	{"A#7",118},
	{"Bb7",118},
	{"B7",119},
	{"C8",120},
	{"C#8",121},
	{"Db8",121},
	{"D8",122},
	{"D#8",123},
	{"Eb8",123},
	{"E8",124},
	{"F8",125},
	{"F#8",126},
	{"Gb8",126},
	{"G8",127}
};

#endif

CString GlobalUtilities::note(short note_value)
{
	CString notevalue_name = "";
	const CString names[] =
	{
		"C",
		"C#",
		"D",
		"D#",
		"E",
		"F",
		"F#",
		"G",
		"G#",
		"A",
		"A#",
		"B"
	};
	CString level;
	level.Format("%i",(note_value/12)-2);
	notevalue_name = names[note_value%12]+level;
	if (notevalue_name.GetLength()==2) notevalue_name+=" ";
	return notevalue_name;
}

// used with Controller_Dlg and HPMF_Interface

const GlobalUtilities::EFFECT_ELEM GlobalUtilities::effect_list[] =
{
//  {Name, ctrl-no or Aftertouch-no, default-value, with percentage?}
	{"1: Modulation",			1,	0,	true},
	{"5: Portamento Time",		5,	0,	true},
	{"7: Main Volume",			7,	100,true},
	{"10: Panorama",			10,	64, false},
	{"11: Expression",			11,	127,true},
	{"71: Harmonic Content",	71,	64, false},
	{"72: Release Time",		72,	64,	true},
	{"73: Attack Time",			73,	64,	true},
	{"74: Brightness",			74,	64, true},
	{"75: Decay Time",			75,	0,	true},
	{"76: Vibrato Rate",		76,	0,	false},
	{"77: Vibrato Depth",		77,	0,	false},
	{"78: Vibrato Delay",		78,	0,	false},
	{"84: Portamento Control",	84,	0,	true},
	{"91: Reverb Send Level",	91,	0,	true},
	{"93: Chorus Send Level",	93,	0,	true},
	{"94: Variation Send Level",94,	0,	false},
	{"Channel Aftertouch",		0xd0,0,	true}
};

const GlobalUtilities::GM_DRUM GlobalUtilities::gm_drum_list[NO_GM_DRUMS] =
{
	//  int drum_note_number, char[] drumname
 {13, "Surdo Mute"},
 {14, "Surdo Open"},
 {15, "Hi Q"},
 {16, "Whip Slap"},
 {17, "Scratch H"},
 {18, "Scratch L"},
 {19, "Finger Snap"},
 {20, "Click Noise"},
 {21, "Metronome Click"},
 {22, "Metronome Bell"},
 {23, "Seq Click L"},
 {24, "Seq Click H"},
 {25, "Brush Tap"},
 {26, "Brush Swirl"},
 {27, "Brush Slap"},
 {28, "Brush Tap Swirl"},
 {29, "Snare Roll"},
 {30, "Castanet"},
 {31, "Snare Soft"},
 {32, "Sticks"},
 {33, "Kick Soft"},
 {34, "Open Rim Shot"},
 {35, "Kick Tight"},
 {36, "Kick"},
 {37, "Side Stick"},
 {38, "Snare"},
 {39, "Hand Clap"},
 {40, "Snare Tight"},
 {41, "Floor Tom L"},
 {42, "Hi-Hat Closed"},
 {43, "Floor Tom H"},
 {44, "Hi-Hat Pedal"},
 {45, "Low Tom"},
 {46, "Hi-Hat Open"},
 {47, "Mid Tom L"},
 {48, "Mid Tom H"},
 {49, "Crash Cymbal 1"},
 {50, "High Tom"},
 {51, "Ride Cymbal 1"},
 {52, "Chinese Cymbal"},
 {53, "Ride Cymbal Cup"},
 {54, "Tambourine"},
 {55, "Splash Cymbal"},
 {56, "Cowbell"},
 {57, "Crash Cymbal 2"},
 {58, "Vibraslap"},
 {59, "Ride Cymbal 2"},
 {60, "Bongo H"},
 {61, "Bongo L"},
 {62, "Conga H Mute"},
 {63, "Conga H Open"},
 {64, "Conga L"},
 {65, "Timbale H"},
 {66, "Timbale L"},
 {67, "Agogo H"},
 {68, "Agogo L"},
 {69, "Cabasa"},
 {70, "Maracas"},
 {71, "Samba Whistle H"},
 {72, "Samba Whistle L"},
 {73, "Guiro Short"},
 {74, "Guiro Long"},
 {75, "Claves"},
 {76, "Wood Block H"},
 {77, "Wood Block L"},
 {78, "Cuica Mute"},
 {79, "Cuica Open"},
 {80, "Triangle Mute"},
 {81, "Triangle Open"},
 {82, "Shaker"},
 {83, "Jingle Bell"},
 {84, "Bell Tree"}
};


const GlobalUtilities::MIDI_EVENT_ELEM GlobalUtilities::midi_event_list[] =
{
// name, HP Midifile type, value for non standard controller, else -1
	{"Polyphone Aftertouch",						HP_AFTERTOUCH,			-1},
	{"Channel Aftertouch",				HP_CHANNEL_PRESSURE,	-1},
	{"Pitch Wheel",						HP_PITCH_WHEEL,			-1},
	{"SysEx",							HP_SYSEX,				-1},
	{"RPN",								HP_RPN,					-1},
	{"NRPN",							HP_NRPN,				-1},
	{"Ctrl. 1 Modulation",				HP_MODULATION,			-1},
	{"Ctrl. 2 Breath",					HP_BREATH,				-1},
	{"Ctrl. 3",							HP_CONTROLLER_TYPE,		 3},
	{"Ctrl. 4 Foot Pedal",		        HP_CONTROLLER_TYPE,	 	 4},
	{"Ctrl. 5 Portamento Time",			HP_PORTAMENTO_TIME,		-1},
	{"Ctrl. 7 Main Volume",				HP_MAIN_VOLUME,			-1},
	{"Ctrl. 8 Balance",					HP_CONTROLLER_TYPE,	 	 8},
	{"Ctrl. 9",					        HP_CONTROLLER_TYPE,	 	 9},
	{"Ctrl. 10 Pan Position",			HP_PANPOT,				-1},
	{"Ctrl. 11 Expression",				HP_EXPRESSION,			-1},
	{"Ctrl. 12",					    HP_CONTROLLER_TYPE,	 	12},
	{"Ctrl. 13",				        HP_CONTROLLER_TYPE,	 	13},
	{"Ctrl. 14",				        HP_CONTROLLER_TYPE,	 	14},
	{"Ctrl. 15",				        HP_CONTROLLER_TYPE,	 	15},
	{"Ctrl. 16",				        HP_CONTROLLER_TYPE,	 	16},
	{"Ctrl. 17",				        HP_CONTROLLER_TYPE,	 	17},
	{"Ctrl. 18",				        HP_CONTROLLER_TYPE,	 	18},
	{"Ctrl. 19",				        HP_CONTROLLER_TYPE,	 	19},
	{"Ctrl. 20",				        HP_CONTROLLER_TYPE,	 	20},
	{"Ctrl. 21",				        HP_CONTROLLER_TYPE,	 	21},
	{"Ctrl. 22",				        HP_CONTROLLER_TYPE,	 	22},
	{"Ctrl. 23",				        HP_CONTROLLER_TYPE,	 	23},
	{"Ctrl. 24",				        HP_CONTROLLER_TYPE,	 	24},
	{"Ctrl. 25",				        HP_CONTROLLER_TYPE,	 	25},
	{"Ctrl. 26",				        HP_CONTROLLER_TYPE,	 	26},
	{"Ctrl. 27",				        HP_CONTROLLER_TYPE,	 	27},
	{"Ctrl. 28",				        HP_CONTROLLER_TYPE,	 	28},
	{"Ctrl. 29",				        HP_CONTROLLER_TYPE,	 	29},
	{"Ctrl. 30",				        HP_CONTROLLER_TYPE,	 	30},
	{"Ctrl. 31",				        HP_CONTROLLER_TYPE,	 	31},
	{"Ctrl. 33",				        HP_CONTROLLER_TYPE,	 	33},
	{"Ctrl. 34",				        HP_CONTROLLER_TYPE,	 	34},
	{"Ctrl. 35",				        HP_CONTROLLER_TYPE,	 	35},
	{"Ctrl. 36",				        HP_CONTROLLER_TYPE,	 	36},
	{"Ctrl. 37",				        HP_CONTROLLER_TYPE,	 	37},
	{"Ctrl. 39",				        HP_CONTROLLER_TYPE,	 	39},
	{"Ctrl. 40",				        HP_CONTROLLER_TYPE,	 	40},
	{"Ctrl. 41",				        HP_CONTROLLER_TYPE,	 	41},
	{"Ctrl. 42",				        HP_CONTROLLER_TYPE,	 	42},
	{"Ctrl. 43",				        HP_CONTROLLER_TYPE,	 	43},
	{"Ctrl. 44",				        HP_CONTROLLER_TYPE,	 	44},
	{"Ctrl. 45",				        HP_CONTROLLER_TYPE,	 	45},
	{"Ctrl. 46",				        HP_CONTROLLER_TYPE,	 	46},
	{"Ctrl. 47",				        HP_CONTROLLER_TYPE,	 	47},
	{"Ctrl. 48",				        HP_CONTROLLER_TYPE,	 	48},
	{"Ctrl. 49",				        HP_CONTROLLER_TYPE,	 	49},
	{"Ctrl. 50",				        HP_CONTROLLER_TYPE,	 	50},
	{"Ctrl. 51",				        HP_CONTROLLER_TYPE,	 	51},
	{"Ctrl. 52",				        HP_CONTROLLER_TYPE,	 	52},
	{"Ctrl. 53",				        HP_CONTROLLER_TYPE,	 	53},
	{"Ctrl. 54",				        HP_CONTROLLER_TYPE,	 	54},
	{"Ctrl. 55",				        HP_CONTROLLER_TYPE,	 	55},
	{"Ctrl. 56",				        HP_CONTROLLER_TYPE,	 	56},
	{"Ctrl. 57",				        HP_CONTROLLER_TYPE,	 	57},
	{"Ctrl. 58",				        HP_CONTROLLER_TYPE,	 	58},
	{"Ctrl. 59",				        HP_CONTROLLER_TYPE,	 	59},
	{"Ctrl. 60",				        HP_CONTROLLER_TYPE,	 	60},
	{"Ctrl. 61",				        HP_CONTROLLER_TYPE,	 	61},
	{"Ctrl. 62",				        HP_CONTROLLER_TYPE,	 	62},
	{"Ctrl. 63",				        HP_CONTROLLER_TYPE,	 	63},
	{"Ctrl. 64 Sustain",				HP_SUSTAIN,				-1},
	{"Ctrl. 65 Portamento",				HP_PORTAMENTO,			-1},
	{"Ctrl. 66 Sostenuto",				HP_SOSTENUTO,			-1},
	{"Ctrl. 67 Soft Pedal",				HP_SOFT_PEDAL,			-1},
	{"Ctrl. 68 Legato Pedal",	        HP_CONTROLLER_TYPE,	 	68},
	{"Ctrl. 69 Hold2 Pedal",	        HP_CONTROLLER_TYPE,	 	69},
	{"Ctrl. 70 Sound Variation",        HP_CONTROLLER_TYPE,	 	70},
	{"Ctrl. 71 Harmonic Content",		HP_HARMONIC_CONTENT,	-1},
	{"Ctrl. 72 Release Time",			HP_RELEASE_TIME,		-1},
	{"Ctrl. 73 Attack Time",			HP_ATTACK_TIME,			-1},
	{"Ctrl. 74 Brightness",				HP_BRIGHTNESS,			-1},
	{"Ctrl. 75 Decay Time",				HP_DECAY_TIME,			-1},
	{"Ctrl. 76 Vibrato Rate",			HP_VIBRATO_RATE,		-1},
	{"Ctrl. 77 Vibrato Depth",			HP_VIBRATO_DEPTH,		-1},
	{"Ctrl. 78 Vibrato Delay",			HP_VIBRATO_DELAY,		-1},
	{"Ctrl. 79",				        HP_CONTROLLER_TYPE,	 	79},
	{"Ctrl. 80",				        HP_CONTROLLER_TYPE,	 	80},
	{"Ctrl. 81",				        HP_CONTROLLER_TYPE,	 	81},
	{"Ctrl. 82",				        HP_CONTROLLER_TYPE,	 	82},
	{"Ctrl. 83",				        HP_CONTROLLER_TYPE,	 	83},
	{"Ctrl. 84 Portamento Control",		HP_PORTAMENTO_CONTROL,	-1},
	{"Ctrl. 85",				        HP_CONTROLLER_TYPE,	 	85},
	{"Ctrl. 86",				        HP_CONTROLLER_TYPE,	 	86},
	{"Ctrl. 87",				        HP_CONTROLLER_TYPE,	 	87},
	{"Ctrl. 88",				        HP_CONTROLLER_TYPE,	 	88},
	{"Ctrl. 89",				        HP_CONTROLLER_TYPE,	 	89},
	{"Ctrl. 90",				        HP_CONTROLLER_TYPE,	 	90},
	{"Ctrl. 91 Reverb Send Level",		HP_REVERB_SEND_LEVEL,	 -1},
	{"Ctrl. 92 Tremulo Level",	        HP_CONTROLLER_TYPE,	 	 92},
	{"Ctrl. 93 Chorus Send Level",		HP_CHORUS_SEND_LEVEL,	 -1},
	{"Ctrl. 94 Variation Send Level",	HP_VARIATION_SEND_LEVEL, -1},
	{"Ctrl. 95 Phaser Level",	        HP_CONTROLLER_TYPE,	 	 95},
	{"Ctrl. 102",				        HP_CONTROLLER_TYPE,		102},
	{"Ctrl. 103",				        HP_CONTROLLER_TYPE,	 	103},
	{"Ctrl. 104",				        HP_CONTROLLER_TYPE,	 	104},
	{"Ctrl. 105",				        HP_CONTROLLER_TYPE,	 	105},
	{"Ctrl. 106",				        HP_CONTROLLER_TYPE,	 	106},
	{"Ctrl. 107",				        HP_CONTROLLER_TYPE,	 	107},
	{"Ctrl. 108",				        HP_CONTROLLER_TYPE,	 	108},
	{"Ctrl. 109",				        HP_CONTROLLER_TYPE,	 	109},
	{"Ctrl. 110",				        HP_CONTROLLER_TYPE,	 	110},
	{"Ctrl. 111",				        HP_CONTROLLER_TYPE,	 	111},
	{"Ctrl. 112",				        HP_CONTROLLER_TYPE,	 	112},
	{"Ctrl. 113",				        HP_CONTROLLER_TYPE,	 	113},
	{"Ctrl. 114",				        HP_CONTROLLER_TYPE,	 	114},
	{"Ctrl. 115",				        HP_CONTROLLER_TYPE,	 	115},
	{"Ctrl. 116",				        HP_CONTROLLER_TYPE,	 	116},
	{"Ctrl. 117",				        HP_CONTROLLER_TYPE,	 	117},
	{"Ctrl. 118",				        HP_CONTROLLER_TYPE,	 	118},
	{"Ctrl. 119",				        HP_CONTROLLER_TYPE,	 	119},
	{"Ctrl. 120 All Sound Off",			HP_ALL_SOUND_OFF,		 -1},
	{"Ctrl. 121 Reset All Controller",	HP_RESET_ALL_CONTROLLERS,-1},
	{"Ctrl. 122 Local Keyboard on/off", HP_CONTROLLER_TYPE,     122},
	{"Ctrl. 123 All Notes Off",			HP_ALL_NOTES_OFF,		 -1},
	{"Ctrl. 124 Omni Off",				HP_OMNI_OFF,			 -1},
	{"Ctrl. 125 Omni On",				HP_OMNI_ON,				 -1},
	{"Ctrl. 126 Mono",					HP_MONO,				 -1},
	{"Ctrl. 127 Poly",					HP_POLY,				 -1}
};

const bool GlobalUtilities::printable[256]=
{
	false,	// 00
	false,	// 01
	false,	// 02
	false,	// 03
	false,	// 04
	false,	// 05
	false,	// 06
	false,	// 07
	false,	// 08
	false,	// 09
	false,	// 0A
	false,	// 0B
	false,	// 0C
	false,	// 0D
	false,	// 0E
	false,	// 0F
	false,	// 10
	false,	// 11
	false,	// 12
	false,	// 13
	false,	// 14
	false,	// 15
	false,	// 16
	false,	// 17
	false,	// 18
	false,	// 19
	false,	// 1A
	false,	// 1B
	false,	// 1C
	false,	// 1D
	false,	// 1E
	false,	// 1F
	true,	// 20
	true,	// 21
	true,	// 22
	true,	// 23
	true,	// 24
	true,	// 25
	true,	// 26
	true,	// 27
	true,	// 28
	true,	// 29
	true,	// 2A
	true,	// 2B
	true,	// 2C
	true,	// 2D
	true,	// 2E
	true,	// 2F
	true,	// 30
	true,	// 31
	true,	// 32
	true,	// 33
	true,	// 34
	true,	// 35
	true,	// 36
	true,	// 37
	true,	// 38
	true,	// 39
	true,	// 3A
	true,	// 3B
	true,	// 3C
	true,	// 3D
	true,	// 3E
	true,	// 3F
	true,	// 40
	true,	// 41
	true,	// 42
	true,	// 43
	true,	// 44
	true,	// 45
	true,	// 46
	true,	// 47
	true,	// 48
	true,	// 49
	true,	// 4A
	true,	// 4B
	true,	// 4C
	true,	// 4D
	true,	// 4E
	true,	// 4F
	true,	// 50
	true,	// 51
	true,	// 52
	true,	// 53
	true,	// 54
	true,	// 55
	true,	// 56
	true,	// 57
	true,	// 58
	true,	// 59
	true,	// 5A
	true,	// 5B
	true,	// 5C
	true,	// 5D
	true,	// 5E
	true,	// 5F
	true,	// 60
	true,	// 61
	true,	// 62
	true,	// 63
	true,	// 64
	true,	// 65
	true,	// 66
	true,	// 67
	true,	// 68
	true,	// 69
	true,	// 6A
	true,	// 6B
	true,	// 6C
	true,	// 6D
	true,	// 6E
	true,	// 6F
	true,	// 70
	true,	// 71
	true,	// 72
	true,	// 73
	true,	// 74
	true,	// 75
	true,	// 76
	true,	// 77
	true,	// 78
	true,	// 79
	true,	// 7A
	true,	// 7B
	true,	// 7C
	true,	// 7D
	true,	// 7E
	false,	// 7F
	true,	// 80
	false,	// 81
	false,	// 82
	false,	// 83
	true,	// 84
	false,	// 85
	false,	// 86
	false,	// 87
	false,	// 88
	false,	// 89
	true,	// 8A
	false,	// 8B
	true,	// 8C
	false,	// 8D
	true,	// 8E
	false,	// 8F
	false,	// 90
	false,	// 91
	false,	// 92
	false,	// 93
	false,	// 94
	false,	// 95
	false,	// 96
	false,	// 97
	false,	// 98
	false,	// 99
	true,	// 9A
	false,	// 9B
	true,	// 9C
	false,	// 9D
	true,	// 9E
	false,	// 9F
	false,	// A0
	true,	// A1
	false,	// A2
	true,	// A3
	false,	// A4
	false,	// A5
	false,	// A6
	false,	// A7
	false,	// A8
	false,	// A9
	false,	// AA
	false,	// AB
	false,	// AC
	false,	// AD
	false,	// AE
	false,	// AF
	false,	// B0
	false,	// B1
	false,	// B2
	false,	// B3
	false,	// B4
	false,	// B5
	false,	// B6
	false,	// B7
	false,	// B8
	false,	// B9
	false,	// BA
	false,	// BB
	false,	// BC
	false,	// BD
	false,	// BE
	true,	// BF
	true,	// C0
	true,	// C1
	true,	// C2
	true,	// C3
	true,	// C4
	true,	// C5
	true,	// C6
	true,	// C7
	true,	// C8
	true,	// C9
	true,	// CA
	true,	// CB
	true,	// CC
	true,	// CD
	true,	// CE
	true,	// CF
	true,	// D0
	true,	// D1
	true,	// D2
	true,	// D3
	true,	// D4
	true,	// D5
	true,	// D6
	true,	// D7
	true,	// D8
	true,	// D9
	true,	// DA
	true,	// DB
	true,	// DC
	true,	// DD
	true,	// DE
	true,	// DF
	true,	// E0
	true,	// E1
	true,	// E2
	true,	// E3
	true,	// E4
	true,	// E5
	true,	// E6
	true,	// E7
	true,	// E8
	true,	// E9
	true,	// EA
	true,	// EB
	true,	// EC
	true,	// ED
	true,	// EE
	true,	// EF
	true,	// F0
	true,	// F1
	true,	// F2
	true,	// F3
	true,	// F4
	true,	// F5
	true,	// F6
	true,	// F7
	true,	// F8
	true,	// F9
	true,	// FA
	true,	// FB
	true,	// FC
	true,	// FD
	true,	// FE
	true 	// FF
};