// GlobalUtilities.h: Schnittstelle für die Klasse GlobalUtilities.
//
//////////////////////////////////////////////////////////////////////

#define ADD_PSRUTI_FUNCTIONS // comment for PSRMIDI, no comment for PSRUTI


#if !defined(AFX_GLOBALUTILITIES_H__A4EAAA59_B201_4CAF_A6CE_5CE23B182921__INCLUDED_)
#define AFX_GLOBALUTILITIES_H__A4EAAA59_B201_4CAF_A6CE_5CE23B182921__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class GlobalUtilities
{

#if defined(ADD_PSRUTI_FUNCTIONS)

typedef struct flat_sharp_elem
{
	char key[4];
	bool is_flat;
} FLAT_SHARP_ELEM;

#endif

// indexes in List Copy Exchange
#define NONE_SELECTED    -1
#define DELETE_SELECTED   0
#define EXCHANGE_SELECTED 1
#define CUT_COPY_SELECTED 2
#define COPY_SELECTED     3

public:
// functions

#if defined(ADD_PSRUTI_FUNCTIONS)
	static CString get_resource_string (int ids);
#endif
	static bool is_printable(unsigned char ch);			  // is valid lyrics-char?
	static bool is_letter(unsigned char ch);

	static void convert_CString_to_cstring(char** cstr, CString CStr);
	static CString convert_cstring_to_printable(char* str);
	static CString convert_string_to_printable(CString str);
	static CString convert_printable_to_string(CString str, char lf);

	static CString convert_sysex_data_to_string(unsigned char *data);
	static bool convert_sysex_string_to_data(CString cstring, unsigned char** data, int *length);
	static bool is_gm_on_sysex(unsigned char *data);
	static bool is_xg_on_sysex(unsigned char *data);
	static bool is_turn_tg300b_on(unsigned char *data);
	static bool is_part_mode_sysex(unsigned char *data);
	static bool is_part_not_used_sysex(unsigned char *data);
	static bool is_part_mode_normal_sysex(unsigned char *data);
	static bool is_lyrics_part_score_on_sysex(unsigned char *data);
	static bool is_chord_part_score_on_sysex(unsigned char *data);
	static bool is_score_layout_sysex(unsigned char *data, unsigned char *type, unsigned char *value);

	static bool compare_data(unsigned char* data1, int len1, unsigned char* data2, int len2);

	static int pack_msb_lsb_voice(int msb, int lsb, int voice);
	static void unpack_msb_lsb_voice(int data, int *msb, int *lsb, int * voice);

	// Chord functions
	static unsigned char change_flat_sharp_bn(unsigned char bn, unsigned char cr);
	static unsigned char enharmonic_cr(unsigned char cr, bool is_flat);
	static unsigned char transpose_cr(unsigned char cr, int delta, bool is_flat);
	static bool find_cr_ct_bn_bt(CString chord_text, unsigned char *cr, unsigned char *ct,
									unsigned char *bn, unsigned char *bt);
	static CString transpose_key_signature(CString old_key, int transpose_no);
#if defined(ADD_PSRUTI_FUNCTIONS)
	static unsigned char find_bn(int note);
	static CString convert_bn(unsigned char bn, unsigned char cr, unsigned char ct, unsigned char* new_bn);
	static int get_id(CString midiport);
	static CString compute_notestring(int notevalue);
	static int compute_notevalue(CString note_name);
    static CString compute_short_notestring(unsigned char bn, bool flat_cr);

	static 	bool is_flat_key(char *key);
	static int compute_number(char* s, int l);
	static double compute_double_number(char* s, int l);
	static CString SelectProtFile(CString last_protfile);
	static bool analyse_mbt(CString mbt_str, int* meas, int* bar, int* tick);
	static int  is_vh_channel_sysex(unsigned char* data, int length);
	static bool is_vh_sysex(unsigned char* data, int length);
	static bool is_vocoder_sysex(unsigned char* data, int length);
	static bool is_score_sysex(unsigned char* data, int length);
	static bool is_vh_ad_on_sysex(unsigned char* data, int length);
    static bool is_vh_ad_off_sysex(unsigned char* data, int length);
	static char get_linefeed_char();
	static bool get_sysex_parno_effectno(int AdrH, int AdrL, int DataMSB, int DataLSB, int *par_no, int *effect_no);
	static void reduce_voicename(CString *voicename);

#endif


// data
	static unsigned char gm_on_data[6];
	static unsigned char xg_on_data[9];
	static unsigned char turn_tg300b_on_data[11];
	static unsigned char GlobalUtilities::lyrics_part_score_on_data[10];
	static unsigned char GlobalUtilities::chord_part_score_on_data[10];
	static unsigned char GlobalUtilities::score_layout_data[10];
    static unsigned char GlobalUtilities::score_representation_medium_data[10];
	static const unsigned char plus_table_sharp[0x68], plus_table_flat[0x68];
	static const unsigned char minus_table_sharp[0x68], minus_table_flat[0x68];
	static const unsigned char null_table_sharp[0x68], null_table_flat[0x68];

	static CString note(short note_value);

	// Chord-lists
	static const CString cr03_list[7];
	static const int cr03_list_length;
	static const CString cr47_list[8];
	static const int cr47_list_length;
	static const CString ct_list[];
	static const int ct_list_length;

#if defined(ADD_PSRUTI_FUNCTIONS)
	static const FLAT_SHARP_ELEM flat_sharp_list[30];
	static const CString init_takt_lyric;
	static const CString init_beat_lyric;
	static const CString init_end_lyric;
#endif

	static const CString start_lyriclist;
	static const CString start_sysexlist;
	static const CString start_sysexlist_mbt;
	static const CString start_revoicelist;
	static const CString start_drumlist;
	static const CString start_timelist_mbt;
	static const CString start_chords_lyrics;
	static const CString end_list;

	static const CString empty_xfhd;
	static const CString empty_xfln;
	static unsigned char xfversion[13];
	static const int xfversion_len;
	static unsigned char quickstart[9];
	static const int quickstart_len;
	static const unsigned char guidetrackflag[8];
	static const int guidetrackflag_len;

	// used to get note values from note names

	#define NO_NOTE_NAME_ELEMS 181
	typedef struct note_name_elem {char name[5]; int value;} NOTE_NAME_ELEM;
	static const NOTE_NAME_ELEM note_name_list[NO_NOTE_NAME_ELEMS];

	// used with Controller_Dlg and HPMF_Interface:

	#define NO_EFFECT_ELEMS 18
	typedef struct effect_elem {char name[32]; int no; int default_value; bool global_change;} EFFECT_ELEM;
 	static const EFFECT_ELEM effect_list[NO_EFFECT_ELEMS];

	// used with Delete MIDI Events and HPMF_Interface

	#define NO_MIDI_EVENTS 124
	typedef struct midi_event_elem {char name[32]; int event_type; int number;} MIDI_EVENT_ELEM;
 	static const MIDI_EVENT_ELEM midi_event_list[NO_MIDI_EVENTS];

	#define NO_GM_DRUMS 72
	typedef struct gm_drum {int drum_note_number; char drum_name[25];} GM_DRUM;
	static const GM_DRUM gm_drum_list[NO_GM_DRUMS];

private:

#if defined(ADD_PSRUTI_FUNCTIONS)
	static CString LoadStringFromDLL(HINSTANCE hInst, int ids);
#endif
	static const bool printable[256];
};

#endif // !defined(AFX_GLOBALUTILITIES_H__A4EAAA59_B201_4CAF_A6CE_5CE23B182921__INCLUDED_)
