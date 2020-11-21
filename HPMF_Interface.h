// HPMF_Interface.h: Schnittstelle für die Klasse HPMF_Interface.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HPMF_INTERFACE_H__2CDB02A7_A93E_4AAA_9790_82F4AF974BFD__INCLUDED_)
#define AFX_HPMF_INTERFACE_H__2CDB02A7_A93E_4AAA_9790_82F4AF974BFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//
// Standard Includes
//
#include <afx.h>
#include <afxtempl.h>
#include <stdlib.h>
#include <search.h>
#include "StdAfx.h"

//
// Project Includes
//
#include "Chd.h"
#include "HP_midifile.h"
#include "my_play_monitor.h"
#include "GlobalUtilities.h"
#include "IniFile.h"
#include "VoiceFileElement.h"
#include "MyArrays.h"
#include "XgEffects.h"

//
// Defines
//
#define OFF_LIST_LENGTH 1024
#define TAKT 0
#define BEAT 1
#define END  2

#define BEAT_RESOLUTION_1	1
#define BEAT_RESOLUTION_13	2
#define BEAT_RESOLUTION_ALL	3

#define CHORDS 0
#define LYRICS 1

// MultiPart Defines for Voicefile Revoicing
#define VELOCITY_SENSE_DEPTH		0x80c
#define VELOCITY_SENSE_OFFSET		0x80d
#define MW_FILTER_CONTROL			0x81e
#define MW_LFO_PMOD					0x820			
#define MW_LFO_FMOD					0x821			
#define MW_LFO_AMOD					0x822			
#define OFFSET_LEVEL_CONTROL_MW		0xa40
#define OFFSET_LEVEL_CONTROL_CAT	0xa42			
#define CAT_FILTER_CONTROL			0x84e			
#define CAT_LFO_PMOD				0x850
#define CAT_LFO_FMOD				0x851
#define CAT_LFO_AMOD				0x852
#define EQ_BASS_GAIN				0x872	
#define EQ_TREBLE_GAIN				0x873
#define EQ_BASS_FREQU				0x876
#define EQ_TREBLE_FREQU				0x877
	
// parameters of eval_fill_lyrics
#define NOT_AT_LYRICS				0
#define NOT_IN_BEATS_WITH_LYRICS	1
#define NOT_IN_MEASURES_WITH_LYRICS	2

// parameters of drumfile revocing (drum_action)

#define DRUM_CHANGE	0
#define DRUM_DELETE 1
#define DRUM_COPY	2

#define NO_EFF_BLOCKS				127

//
// Global Types
//
typedef struct vel_compress
{
	int min;
	int max;
	int delete_upto;
	int min_new;
	int max_new;
} VEL_COMPRESS_ELEM;

typedef struct voicelist_elem
{
	int msb;
	int lsb;
	int voice;
	bool with_note;
} VOICELIST_ELEM;


typedef struct bank_voices_elem
{
	unsigned long bank_no;
	CString voice_name[128];
} BANK_VOICES_ELEM;


// **************************************
//
// HPMF_Interface
//
// **************************************

class HPMF_Interface: public CDialog  
{

//
// Local Types
//

typedef struct lyriclist_elem
{	
  int time;
  int takt;
  int bar;
  int delta_tick;
  int num;
  CString text;
} LYRICLIST_ELEM;


typedef struct takt_bar_time_elem
{
	int takt;
	int	bar;
	int time;
	int num;
	int tbe; // TAKT, BEAT or END
} TAKT_BAR_TIME_ELEM;


typedef struct lscr
{
	int time;
	CString text;
} LSCR;

typedef struct note_struct
{
	int id;
	int note;
	int time;
	int next_i; // index in notelist to next following same note;
	int old_length;
	int new_length;
}NOTE;

// element of local_lyriclist for function "eval_lyrics_at_channel_notes" only
typedef struct ll
{
	CString text;
	bool linefeed_before;
} LL;

// element of local list for function "delete_unneeded_sysex"
typedef struct sysex_data
{
	bool used;
	int part;
	int channel;
	bool with_off;
	bool is_insertion;
	bool is_system;
} SYSEX_DATA;

// element of sysexlist
typedef struct sysex_elem
{
	int time;
	int measure;
	int beat;
	int tick;
	CString data_str;
} SYSEX_ELEM;


private:

//
// Static local const data
//
	static const CString chordfile_title;
	static const CString xfchordfile_title;
	static const CString shortpatch[128];
	static const CString lyricfile_title;
	static const CString sysexfile_title;
	static const CString timefile_title;
	static const CString chordlyricfile_title;
	static const CString chord_indicator;
	static const CString lyric_indicator;
	static const CString drywet_text[128];
	static const char* heikoplate_text;

public:

//
// Public data
//
	HP_MIDIFILE_MODULE* mf; // hp midifile handle for working, initialized with source-file
	bool bad_error;
	bool with_additional_chunks;
	Log* lf;
	int ppqn;
	int original_ppqn;
	CString sourcefile;
	CString proposed_songname;
	CString copyrightname;
	CString composer;
	CString lyricist;

	char  filetitle[81];
	bool with_insdef;
	HP_CWBANK *bank_list;
	int no_banks;

	XgEffects *xg_effects;

	BANK_VOICES_ELEM bank_voices_list[128];

	int bank_voices_list_free;

	bool is_simple_chords;
	bool is_sysex_chords;
	bool is_fill_lyrics;
	bool vh_channel[16];
	bool vh_channel_sysex_exist[16];
	bool vocoder_sysex_exist;
	bool vh_ad_on_sysex_exist;
	bool vh_ad_off_sysex_exist;
	bool chord_protocol;
	bool chord_protocol_lyric;
	CString protfile;
	int no_chords;
	int selected_chord_chan;

	bool with_gm_on;
	bool with_xg_on;
	bool with_gs_on;
	bool with_songname;
	bool with_xfchords;
	bool with_lyrics;
	bool with_cuepoint_lyrics;
	bool with_copyright;
	bool with_xfhd;
	bool with_xfln;
	bool with_xf_version;
	bool with_drums_from_insfile;
	bool vh_events_delete;
	int no_blocks; // no of programmable insertion effect blocks

	// xg convert parameter
	int no_notes[16];

	int  maxvolume[16];
	bool mute[16];
	bool new_mute[16];
	int  lowlimit[16];
	int	 new_lowlimit[16];
	int	 highlimit[16];
	int	 new_highlimit[16];
	int	 transpose_delta_list[16];
	CString patchname[16];

	CString first_key ;
	bool lyric_cuepoint;

	struct mlv_list_struct {char msb; int time_msb; char lsb; int time_lsb; 
							char voice; int time_voice;	bool melody; 
							bool is_mega; bool is_sart; CString bankname; CString voicename;} mlv_list[16];

//
// Public non-static functions
//
	HPMF_Interface();
	HPMF_Interface(Log* logf, CString sourcef, IniFile *o_inifile);

	HPMF_Interface(const HPMF_Interface& h); // Copy-Constructor
	virtual ~HPMF_Interface();
	void init_hpmfiledata();

	bool is_source_changed ();
	void source_attributes (CString *source, CString *songname, CString *copyright, bool *with_chunks, CString *format, CString *sub_format, 
		int *ppq, CString *tkt, double *tmpo, CString *key, bool *lyrics, 
		bool * chords, bool * count_in, int *no_measures, int *duration, CString *vh_channels);

//	bool is_vh_velocities(int channel);

	// eval-functions, called from CPsrutiDlg
	void eval_volume(int v[16]);
	void eval_max_values(int effect_index, int maxvalue[16], bool insert_event[16], bool chan_changed[16]);
	int  eval_delete_short_notes(int chan_list[16],int upto_tick);
	bool eval_delete_start_beats(int time_start_beat_start,int time_start_beat_end);
	void eval_insert_klick( int msb_chan10,int lsb_chan10,int main_vol_chan10,
							int noteval_meas, int vel_meas, int noteval_beat, int vel_beat);
	bool eval_insert_start_beats(int drum, int velocity, bool on_all_beats, bool one_measure_count_in);
	void eval_tempo(double tempo);
	int  eval_expr_mvolume(bool change_to_mvolume);
	void eval_transpose(int transpose_no, CString new_key, bool transpose_chords);
	bool pre_eval_chords(int no_list[18], bool sel_list[16], bool is_simple, int bass_channel);
	void remove_chords();
	int  eval_chords(int chord_chan, bool sel_list[16], int bass_channel);
	bool eval_chords_lyrics_from_file(CString chord_lyricfile, bool is_chords, 
		     bool is_lyrics, bool is_chord_sysex);
	bool eval_chords_lyrics_export(CString chord_lyricfile, bool is_chords, 
		     bool is_lyrics, bool is_remove_after, bool is_export, bool is_export_as_lyrics);
	void eval_exchange_channels(int selection, bool source_channels[16], int dest_channel);
	void eval_lyrics_at_channel_notes(CString lyricfile, int chan);
	void eval_fill_lyrics(int where);
	int  eval_delete_fill_lyrics(CString fl1, CString fl2, CString fl3);
	int  eval_xg_convert(int *no_double_notes, int *no_pitch_wheels);
	bool eval_gm_convert();
	void repair_overlapping_notes(int chan);
	void exchange_drumsysex_to_nrpn();
	UINT eval_save(CString m_destination);
	void eval_vel_compress(VEL_COMPRESS_ELEM final_vel_compress_list[16]);
	void eval_voice_browse(char search_string[64],HP_CWBANKVOICE **bank_voice_list,long *bank_voice_list_len);
	void delete_bank_voice_list(HP_CWBANKVOICE **bank_voice_list,long *bank_voice_list_len);
	void eval_quantize_chords(int beat_resolution);
	void eval_quantize_lyrics(int resolution);
	void eval_shift_chordlyrics(int resolution);
	void eval_sysex_export(char *sysexfile, bool with_delete);
	void eval_sysex_export_note_area(char *sysexfile, bool with_delete);
	void eval_score_layout(unsigned char lyrics_value,
						   unsigned char chords_value,
						   unsigned char note_names_value,
						   unsigned char size_value,
						   unsigned char quantize_triole_value,
						   unsigned char quantize_value,
						   unsigned char notenamestype_value,
						   unsigned char note_colour_value
						  );
	void get_layout_sysex_values(unsigned char *lyrics_value, 
								 unsigned char *chords_value, 
								 unsigned char *notenames_value, 
								 unsigned char *size_value,
								 unsigned char *quantize_triole_value, 
								 unsigned char *quantize_value, 
								 unsigned char *notenamestype_value,
								 unsigned char *notecolour_value
								);

	void read_sysex_from_mf(bool with_delete);
	void read_sysex_from_mf_note_area(bool with_delete);
	bool read_sysex_from_file(char *sysexfile);
	bool read_sysex_from_file_mbt(char *sysexfile);

	void eval_sysex_file_import(char *sysexfile);
	void eval_sysex_file_import_position(char *sysexfile, int position);
	void eval_sysex_file_import_mbt(char *sysexfile);
	void eval_sysex_paste_import(CString sysex_chain);
    void eval_sysex_paste_import_note_area(CString sysex_chain, int position);

	void eval_time_export_note_area(CString timefile);	
	void eval_time_import_note_area(CString timefile);	
	
	void eval_songname_composer_lyricist(CString new_songname, 
		                         CString new_composer, CString new_lyricist);
	void eval_copyright(CString old_copyright, CString copyright);
	void eval_scorechan(int old_score_chan_left, int score_chan_left,
						int old_score_chan_right, int score_chan_right);
	void eval_quickstart(bool quickstart);
	void eval_cuepoint_lyric(int offset);
	bool eval_change_drum(int chan, int note, int new_note, int new_velocity,
						  bool dynamic, int min_vel, int max_vel);
	void eval_insert_or_change_master_volume(int master_volume);
	void eval_shift_linefeeds(int ticks, int ticks_at);
    int  eval_delete_kbd_events(bool kbd_voice_events, bool score_start_bar_events, bool phrase_events,
                                bool guide_track_events, bool del_sysex_guide_events, bool lyrics_bitmap_events,
								bool style_events, bool del_sp_marker_events);
	int  eval_delete_midi_events(bool is_checked[], int event_type, int ctrl_number, 
		                         bool before_notes_checked, bool note_area_checked);
	int  eval_normalize_chords();
	void eval_vh_vocoder(int vocoder_channel,bool vocoder_channel_set,bool vocoder_channel_delete, int vocoder_channel_act);
	void eval_lengthen_vh_notes (int vh_channel, int max_length, bool is_vocoder);
	void eval_quantize_notes(int chan, int length_code, bool starts, bool note_length);

	bool with_start_beats(int *time_start_beat_start, int *time_start_beat_end);
	void update_low_high_limit_lists();
	void transpose_mega_note(int id, int delta);
	void delete_mega_effectnotes(int ch);
	void fill_protfile();
	void fill_patchname_list();
	void set_user1_fill_lyric_data(char* tl,char *bl, char *el, int lflt);
	void set_user2_fill_lyric_data(char* tl,char *bl, char *el, int lflt);
	void set_user3_fill_lyric_data(char* tl,char *bl, char *el, int lflt);
	void set_is_user(int is_usr);
	void set_songname(CString sn);
	CString get_songname();
	void get_composer_lyricist(CString *composer, CString *lyricist);
	CString get_copyright();
	void get_scorechan(int *chan_left, int *chan_right);
	bool get_quickstart();
	
	void set_max_tempo(double mt);
	double get_max_tempo();
	CString get_key_signature();
	int  get_time_from_takt_bar_tick(int takt, int bar, int tick);
	void get_takt_bar_tick_from_time(int time, int *takt, int *bar, int *tick);
	void get_takt_bar_tick_time_first_note( int *takt, int *bar, int *tick, int *time);

	void get_user1_fill_lyric_data(char* tl,char *bl, char *el, int *lflt);
	void get_user2_fill_lyric_data(char *tl, char *bl, char *el, int *lflt);
	void get_user3_fill_lyric_data(char *tl, char *bl, char *el, int *lflt);
	void get_user( int *user);

	void remove_lyrics_chords(UINT type);
	void remove_double_chords();
	void insert_heikoplate_text();
	void compute_songname();
	int  least_note_length(int chan);

	int  get_ppqn();
	void get_last_takt_beat(int* takt, int* beat, int* last_tick);
	void get_max_min_max_average_vel(int min_max_average_vel_list[16][3]); // 0: min, 1: max, 2: average
	void compute_actual_average_vel(VEL_COMPRESS_ELEM actual_vel_compress_list[16], int actual_average_list[16]);
	void get_max_values(int maxvalue[16], int effect_index);
	int  get_no_chords();
	int  find_vh_channel();
	bool with_vh_sysexes(bool with_delete);
	bool is_vocalharmony_vocoder();

	int	 analyze_master_volume(bool change);

	CString find_key();

	bool Pause();
	void Stop();
	bool is_playing();

	// Insdef Funktions
	bool open_insdeffile(CString file);
	bool get_insdefs(HP_CWDEF **def_list, int *no_defs);
	bool set_insdef(int index);
	void get_initialvoices(VOICELIST_ELEM voicelist[16]);

private:

//
// static private data
//
	static const char* kar_string;
	static unsigned char XG_master_volume_data[];
	static const int XG_master_volume_data_len;
	static unsigned char GM2_master_volume_data[];
	static const int GM2_master_volume_data_len;
	static unsigned char vh_sysex_chan[9];
	static unsigned char vocoder_sysex[10];
	static unsigned char vh_ad_on_sysex[9];
	static unsigned char vh_ad_off_sysex[9];

//
//  private data
//

	struct off_list_struct {int note; int chan; int time;} off_list[OFF_LIST_LENGTH];
	int free_off_list;

    CArray<Chrd::CHORD_EVENT,Chrd::CHORD_EVENT> cevlist;
	int cevlist_free;
	CArray<Chrd::BASS_NOTE_ELEM,Chrd::BASS_NOTE_ELEM> bass_note_list;
	int bass_note_list_free;

    CArray<LYRICLIST_ELEM,LYRICLIST_ELEM> lyriclist;
	int lyriclist_free;

	CArray <TAKT_BAR_TIME_ELEM,TAKT_BAR_TIME_ELEM> takt_bar_time_list;
	int takt_bar_time_list_free;

	CArray <SYSEX_ELEM,SYSEX_ELEM> sysexlist;
	CArray <CString,CString> sysextextlist;

	int sysexlist_free;

	int part_chan_list[128];
	bool rcv_chan_exist[16];
	
	Chrd *chord;
	int no_key_signatures;
	int num, denum;
	int last_num;
	int last_denum;
	double  max_tempo;

	CString songname;
	
	char user1_beat_lyric[80];
	char user1_takt_lyric[80];
	char user1_end_lyric[80];
	int  user1_linefeedlyrictick;

	char user2_beat_lyric[80];
	char user2_takt_lyric[80];
	char user2_end_lyric[80];
	int  user2_linefeedlyrictick;

	char user3_beat_lyric[80];
	char user3_takt_lyric[80];
	char user3_end_lyric[80];
	int  user3_linefeedlyrictick;

	int is_user;
	char userbeat_lyric[80];
	char usertakt_lyric[80];
	char userend_lyric[80];
	int  userlinefeedlyrictick;

	IniFile *p_inifile;
	char linefeed_char;
	int multipart_convert;
	int drum_setup_convert;
	bool double_notes_allowed;
	bool double_drum_notes_allowed;
	bool delete_empty_chan;
	bool fill_sequ_track;
	int vh_block;
	bool alien_sysex;
	bool alien_voice;
	bool psruti_text;
	bool is_pause;

	bool source_changed;

//
//  private functions
//
	int  exchange_lyric_linefeed();
	void fill_part_chan_list();
	void convert_multipart_sysex_to_controller(int id);
	bool is_organflute_sysex(HP_MIDIFILE_MODULE *mf, int id, int *chan);
	bool is_part_sysex(HP_MIDIFILE_MODULE *mf, int id, int *part);
	void fill_takt_bar_time_list(int old_takt_of_taktchange, int takt_of_taktchange,bool last,int last_event_time);
	void fill_chord_list(bool sel_list[16]);
	void fill_bass_note_list(int bass_channel);

	void insert_sysex_chord(int time, int cr, int ct, int bn, int bt);
	bool is_rpn_nrpn_ctrl(int number);
	bool is_sart_ctrl(int number);
	void get_rounded_takt_bar(int time, int time_of_taktchange, int takt_of_taktchange,  
						  int *rtkt, int *rbr, int *deltatick, int *rounded_event_time);
	void sort_off_list();
	bool is_mega_voice(int msb, int lsb);
	bool is_sart_voice(int msb, int lsb);

	void update_lyriclist();
	void update_takt_bar_time_list();
	void convert_kar_to_mid(bool at_not_needed);

	void extract_composer_lyricist(char *xfln_text, CString *composer, CString *lyricist);
	CString insert_xfln_item(const CString xfln_text, const CString item, int pos);

	void cut_copy_chan_events(HP_MIDIFILE_MODULE *mf_par, int source_chan, int dest_chan);
	int  delete_chan_events(HP_MIDIFILE_MODULE *mf_par, int chan, bool until_notes, bool delete_controller, bool with_vocoder_sysex, bool with_vh_ad_on_sysex);
	void exchange_or_copy_chan_events(int source_chan, int dest_chan, bool exchange);
	void delete_all_layout_sysexes();

//  implemented in HPMF_Interface2.cpp:
	
public:
	void eval_voicefile_revoice(VoiceFilePathElement voicefilepath_list[16]);
	void eval_standard_revoice(VOICELIST_ELEM voicelist[16]);
	bool eval_revoice_from_file(char* revoice_file);
	bool eval_drum_from_file(char* drum_file, bool drum_folder_running);
	void eval_change_effectfilter_controller(int reverb_list[16], int chorus_list[16], int variation_list[16]);
	void eval_change_effectfilter_drywet(int block_list[16], int drywet_list[16]);
	void eval_lyrics_chords_editor(LyricChordEditArray *lce_array);
	bool check_voicefile(CString voicefile);
	void update_blocklist(HP_MIDIFILE_MODULE *mf_par, int blocklist[16]);
	void update_chan_blocklist(int blocklist[16], int chan_blocklist[16], int block_chanlist[16]);
	void update_mlv_list();
	void remove_sysex_drum_mode();
	void update_no_notes(int no_notes[16]);
	bool is_variation_effect(bool *is_variation_sysex, bool *is_system, bool *is_insertion, int *variation_insertion_channel);
	bool insertion_sysex_defined(int chan, int *block);
	void get_reverb_chorus_variation_value(int chan, int *reverb, int *chorus, int *variation);
	CString get_drywet_value(int block, int *value);
	CString get_drywet_text(int value);
	bool check_and_insert_drywet(int chan);
	void compute_drum_velocity(int drum_chan, int note, int *min, int* max);
	void fill_lyric_chord_edit_list(LyricChordEditArray *list);
	int insert_voicetest_effects(HP_MIDIFILE_MODULE* mf_voiceplay,int time_count);
	void find_insfile_bank_voicenames();
	void xgeffects_from_file();
	bool is_sfx_bank(int bank);
	int get_last_id();
	HP_MIDIFILE_MODULE* create_testsequence_melody();
	HP_MIDIFILE_MODULE* create_testsequence_drum();


private:

	void delete_needless_sysex();
	void remove_standard_drum_sysex();
	void add_standard_hall_chorus_variation(int start_time);
	void add_standard_drum_sysex(int start_time);
	bool add_insertions(int start_time, int part, int block, HP_MIDIFILE_MODULE* mf_voice);
	void add_multipart(int start_time, int part, HP_MIDIFILE_MODULE* mf_voice);
	bool is_yamaha_melody_voice(long bank, int voice);

	bool read_voices_from_file(char* revoice_file, ArrayTwoInts *ati);
	bool read_drums_from_file(char* drum_file, int *drum_chan_to_revoice, ArraySixInts *asi);
	void read_time_from_note_area(CString timefile, ArraySixInts *asi);
	bool read_time_from_file_mbt(CString timefile, ArraySixInts *asi, int first_measure_note_area);


};


#endif // !defined(AFX_HPMF_INTERFACE_H__2CDB02A7_A93E_4AAA_9790_82F4AF974BFD__INCLUDED_)
