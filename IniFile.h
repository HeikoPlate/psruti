// IniFile.h: Schnittstelle für die Klasse IniFile.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__40BAFC01_1F02_11D6_9348_0080AD7896CF__INCLUDED_)
#define AFX_INIFILE_H__40BAFC01_1F02_11D6_9348_0080AD7896CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class IniFile  
{
public:
	Log* lf;

	IniFile();
	virtual ~IniFile();
	CString get_sourcefile();
	CString get_protfile();
	CString get_recordfile();
	CString get_chordlyricfile();
	CString get_revoicefile();
	CString get_drumfile();
	CString get_language();
	int get_user();
	CString get_user1_taktlyric();
	CString get_user1_beatlyric();
	CString get_user1_endlyric();
	int get_user1_linefeedlyrictick();
	CString get_user2_taktlyric();
	CString get_user2_beatlyric();
	CString get_user2_endlyric();
	int get_user2_linefeedlyrictick();
	CString get_user3_taktlyric();
	CString get_user3_beatlyric();
	CString get_user3_endlyric();
	int get_user3_linefeedlyrictick();
	CString get_midiport();
	CString get_insdeffile();
	CString get_xgeffectfile();
	CString get_insdef();
	CString get_keyboardmodel();
	int get_countin_drum();
	int get_countin_vel();
	int get_multipart_convert();
	int get_drumsetup_convert();
	bool get_double_notes();
	bool get_not_double_drum_notes();
	bool get_delete_empty_chan();
	CString get_voicefile_folder();
	bool get_fill_sequ_track();
	int get_no_effect_blocks();
	int get_vh_effect_block();
	bool get_alien_sysex();
	bool get_alien_voice();
	bool get_psruti_text();
	bool get_with_lyric_cuepoint();
	bool get_with_drums_from_insfile();
	bool get_vh_events_delete();
	int get_click_main_vol();
	int get_click_note_meas();
	int get_click_note_beat();
	int get_click_vel_meas();
	int get_click_vel_beat();
	bool get_with_sysex_drumkit_mode();
	
	void set_sourcefile(CString filename);
	void set_protfile(CString filename);
	void set_recordfile(CString filename);
	void set_chordlyricfile(CString filename);
	void set_revoicefile(CString filename);
	void set_drumfile(CString filename);
	void set_language(CString lang);
	void set_user(int is_usr);
	void set_user1_taktlyric(CString taktl);
	void set_user1_beatlyric(CString beatl);
	void set_user1_endlyric(CString endl);
	void set_user1_linefeedlyrictick(int tick);
	void set_user2_taktlyric(CString taktl);
	void set_user2_beatlyric(CString beatl);
	void set_user2_endlyric(CString endl);
	void set_user2_linefeedlyrictick(int tick);
	void set_user3_taktlyric(CString taktl);
	void set_user3_beatlyric(CString beatl);
	void set_user3_endlyric(CString endl);
	void set_user3_linefeedlyrictick(int tick);
	void set_midiport(CString midip);
	void set_insdeffile(CString file);
	void set_xgeffectfile(CString file);
	void set_insdef(CString insdf);
	void set_keyboardmodel(CString model);
	void set_countin_drum(int drum);
	void set_countin_vel(int vel);
	void set_multipart_convert(int val);
	void set_drumsetup_convert(int val);
	void set_double_notes (bool val);
	void set_not_double_drum_notes (bool val);
	void set_delete_empty_chan(bool del);
	void set_voicefile_folder(CString folder);
	void set_fill_sequ_track(bool val);
	void set_no_effect_blocks(int no);
	void set_vh_effect_block(int block);
	void set_alien_sysex(bool set);
	void set_alien_voice(bool set);
	void set_psruti_text(bool set);
	void set_with_lyric_cuepoint(bool set);
	void set_with_drums_from_insfile(bool set);
	void set_vh_events_delete(bool set);
	void set_click_main_vol(int mv);
	void set_click_note_meas(int nm);
	void set_click_note_beat(int nb);
	void set_click_vel_meas(int vm);
	void set_click_vel_beat(int vb);
	void set_with_sysex_drumkit_mode(bool set);

	void WriteIniFile();

private:
	bool file_exists(CString file);

	CString sourcefile;
	CString protfile;
	CString recordfile;
	CString chordlyricfile;
	CString revoicefile;
	CString drumfile;
	CString language;
	int is_user;
	CString user1_taktlyric;
	CString user1_beatlyric;
	CString user1_endlyric;
	int user1_linefeedlyrictick;
	CString user2_taktlyric;
	CString user2_beatlyric;
	CString user2_endlyric;
	int user2_linefeedlyrictick;
	CString user3_taktlyric;
	CString user3_beatlyric;
	CString user3_endlyric;
	int user3_linefeedlyrictick;
	CString midiport;
	CString inifile;
	CString insdeffile;
	CString insdef;
	CString xgeffectfile;
	CString keyboardmodel;
	int countin_drum;
	int countin_vel;
	int multipart_convert;
	int drumsetup_convert;
	bool double_notes;
	bool not_double_drum_notes;
	bool delete_empty_chan;
	CString voicefile_folder;
	bool fill_sequ_track;
	int no_effect_blocks;
	int vh_effect_block;
	bool alien_sysex;
	bool alien_voice;
	bool psruti_text;
	bool with_lyric_cuepoint;
	bool with_drums_from_insfile;
	bool vh_events_delete;
	int click_main_vol;
	int click_note_meas;
	int click_note_beat;
	int click_vel_meas;
	int click_vel_beat;
	bool with_sysex_drumkit_mode;

	void ReadIniFile();

	static const CString sourcelabel;
	static const CString protlabel;
	static const CString recordlabel;
	static const CString chordlyriclabel;
	static const CString revoicefilelabel;
	static const CString drumfilelabel;
	static const CString languagelabel;
	static const CString userlabel;
	static const CString user1_taktlyriclabel;
	static const CString user1_beatlyriclabel;
	static const CString user1_endlyriclabel;
	static const CString user1_linefeedlyriclabel;
	static const CString user2_taktlyriclabel;
	static const CString user2_beatlyriclabel;
	static const CString user2_endlyriclabel;
	static const CString user2_linefeedlyriclabel;
	static const CString user3_taktlyriclabel;
	static const CString user3_beatlyriclabel;
	static const CString user3_endlyriclabel;
	static const CString user3_linefeedlyriclabel;
	static const CString midiportlabel;
	static const CString insdeffilelabel;
	static const CString insdeflabel;
	static const CString xgeffectfilelabel;
	static const CString keyboardmodellabel;
	static const CString countin_drumlabel;
	static const CString countin_vellabel;
	static const CString multipart_convertlabel;
	static const CString drumsetup_convertlabel;
	static const CString double_noteslabel;
	static const CString not_double_drum_noteslabel;
	static const CString delete_empty_chanlabel;
	static const CString voicefile_folderlabel;
	static const CString fill_sequ_tracklabel;
	static const CString no_effect_blockslabel;
	static const CString vh_effect_blocklabel;
	static const CString alien_sysexlabel;
	static const CString alien_voicelabel;
	static const CString psruti_textlabel;
	static const CString lyric_cuepointlabel;
	static const CString with_drums_from_insfilelabel;
	static const CString vh_events_deletelabel;
	static const CString click_main_vollabel;
	static const CString click_note_measlabel;
	static const CString click_note_beatlabel;
	static const CString click_vel_measlabel;
	static const CString click_vel_beatlabel;
	static const CString with_sysex_drumkit_modelabel;

	static const CString inifilename;
};

#endif // !defined(AFX_INIFILE_H__40BAFC01_1F02_11D6_9348_0080AD7896CF__INCLUDED_)
