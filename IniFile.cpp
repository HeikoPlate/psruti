// IniFile.cpp: Implementierung der Klasse IniFile.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniFile.h"
#include "Log.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

IniFile::IniFile()
{
	lf = NULL;

	is_user = 1;
	user1_taktlyric	= "default";
	user1_beatlyric	= "default";
	user1_endlyric	= "default";
	user1_linefeedlyrictick = 30;
	user2_taktlyric	= "default";
	user2_beatlyric	= "default";
	user2_endlyric	= "default";
	user2_linefeedlyrictick = 30;
	user3_taktlyric	= "default";
	user3_beatlyric	= "default";
	user3_endlyric	= "default";
	user3_linefeedlyrictick = 30;
	sourcefile	= "";
	protfile	= "";
	recordfile  = "";
	chordlyricfile  = "";
	revoicefile = "";
	drumfile = "";
	language	= "";
	insdeffile = "";
	insdef = "\"\"";
	xgeffectfile = "";
	keyboardmodel = "\"\"";
	countin_drum = 31;	// CountIn-note Snare Soft
	countin_vel  = 64;	// CountIn-velocity
	multipart_convert = 1;
	drumsetup_convert = 0;
	double_notes = false;
	not_double_drum_notes = false;
	delete_empty_chan = true;
	voicefile_folder = "";
	fill_sequ_track = 1;
	no_effect_blocks = 10;
	vh_effect_block = 5;
	alien_sysex = false;
	alien_voice = true;
	with_lyric_cuepoint = false;
	with_drums_from_insfile = false;
	vh_events_delete = false;
	click_main_vol = 60;
	click_note_meas = 24;
	click_note_beat = 23;
	click_vel_meas = 127;
	click_vel_beat = 100;
	with_sysex_drumkit_mode = false;

	psruti_text = true;

	char path[MAX_PATH];
	SHGetSpecialFolderPath(NULL, path, CSIDL_PERSONAL, FALSE);
	strcat(path,"\\");
	inifile = path;
	inifile += inifilename;

	// read inifile and fill 
	ReadIniFile();
}

IniFile::~IniFile()
{
	// create new inifile
	WriteIniFile();
}

bool IniFile::file_exists(CString file)
{
	CFileFind finder;
	if (finder.FindFile(file))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Statics
const CString IniFile::sourcelabel	= "[source]";
const CString IniFile::protlabel	= "[prot]";
const CString IniFile::recordlabel	= "[record]";
const CString IniFile::chordlyriclabel	= "[chordlyric]";
const CString IniFile::revoicefilelabel = "[revoicefile]";
const CString IniFile::drumfilelabel = "[drumfile]";
const CString IniFile::languagelabel= "[lang]";
const CString IniFile::user1_taktlyriclabel = "[user1_taktl]";
const CString IniFile::user1_beatlyriclabel = "[user1_beatl]";
const CString IniFile::user1_endlyriclabel = "[user1_endl]";
const CString IniFile::user1_linefeedlyriclabel = "[user1_lfl]";
const CString IniFile::user2_taktlyriclabel = "[user2_taktl]";
const CString IniFile::user2_beatlyriclabel = "[user2_beatl]";
const CString IniFile::user2_endlyriclabel = "[user2_endl]";
const CString IniFile::user2_linefeedlyriclabel = "[user2_lfl]";
const CString IniFile::user3_taktlyriclabel = "[user3_taktl]";
const CString IniFile::user3_beatlyriclabel = "[user3_beatl]";
const CString IniFile::user3_endlyriclabel = "[user3_endl]";
const CString IniFile::user3_linefeedlyriclabel = "[user3_lfl]";
const CString IniFile::userlabel = "[user]";
const CString IniFile::midiportlabel = "[midip]";
const CString IniFile::insdeffilelabel = "[insdeffile]";
const CString IniFile::insdeflabel = "[insdef]";
const CString IniFile::xgeffectfilelabel = "[xgeffectfile]";
const CString IniFile::keyboardmodellabel = "[keyboardmodel]";
const CString IniFile::countin_drumlabel = "[cidrum]";
const CString IniFile::countin_vellabel = "[civel]";
const CString IniFile::multipart_convertlabel = "[mpconvert]";
const CString IniFile::drumsetup_convertlabel = "[drumsetupconvert]";
const CString IniFile::double_noteslabel = "[doublenotes]";
const CString IniFile::not_double_drum_noteslabel = "[notdoubledrumnotes]";
const CString IniFile::delete_empty_chanlabel = "[dchan]";
const CString IniFile::voicefile_folderlabel = "[vffolder]";
const CString IniFile::fill_sequ_tracklabel = "[fill_sequ_track]";
const CString IniFile::no_effect_blockslabel = "[no_eff_blocks]";
const CString IniFile::vh_effect_blocklabel = "[vh_eff_block]";
const CString IniFile::alien_sysexlabel = "[allow_alien_sysex]";
const CString IniFile::alien_voicelabel = "[allow_alien_voice]";
const CString IniFile::lyric_cuepointlabel = "[with_lyric_cuepoint]";
const CString IniFile::with_drums_from_insfilelabel = "[with_drums_from_insfile]";
const CString IniFile::vh_events_deletelabel = "[vh_events_delete]";
const CString IniFile::psruti_textlabel = "[psruti_text]";
const CString IniFile::click_main_vollabel = "[click_main_vol]";
const CString IniFile::click_note_measlabel = "[click_note_meas]";
const CString IniFile::click_note_beatlabel = "[click_note_beat]";
const CString IniFile::click_vel_measlabel = "[click_vel_meas]";
const CString IniFile::click_vel_beatlabel = "[click_vel_beat]";
const CString IniFile::with_sysex_drumkit_modelabel = "[with_sysex_drumkit_mode]";

const CString IniFile::inifilename  = "psruti.ini";

// *************** get functions ***************

CString IniFile::get_sourcefile() 
{
	return file_exists(sourcefile)?sourcefile:"";
}

CString IniFile::get_protfile() 
{
	return file_exists(protfile)?protfile:"";
}

CString IniFile::get_recordfile() 
{
	return file_exists(recordfile)?recordfile:"";
}

CString IniFile::get_chordlyricfile() 
{
	return file_exists(chordlyricfile)?chordlyricfile:"";
}

CString IniFile::get_revoicefile() 
{
	return file_exists(revoicefile)?revoicefile:"";
}

CString IniFile::get_drumfile() 
{
	return file_exists(drumfile)?drumfile:"";
}


CString IniFile::get_language() 
{
	return language;
}


int IniFile::get_user()
{
	return is_user;
}


CString IniFile::get_user1_taktlyric() 
{
	return user1_taktlyric;
}


CString IniFile::get_user1_beatlyric() 
{
	return user1_beatlyric;
}


CString IniFile::get_user1_endlyric() 
{
	return user1_endlyric;
}

int IniFile::get_user1_linefeedlyrictick()
{
	return user1_linefeedlyrictick;
}


CString IniFile::get_user2_taktlyric() 
{
	return user2_taktlyric;
}


CString IniFile::get_user2_beatlyric() 
{
	return user2_beatlyric;
}


CString IniFile::get_user2_endlyric() 
{
	return user2_endlyric;
}

int IniFile::get_user2_linefeedlyrictick()
{
	return user2_linefeedlyrictick;
}

CString IniFile::get_user3_taktlyric() 
{
	return user3_taktlyric;
}


CString IniFile::get_user3_beatlyric() 
{
	return user3_beatlyric;
}


CString IniFile::get_user3_endlyric() 
{
	return user3_endlyric;
}

int IniFile::get_user3_linefeedlyrictick()
{
	return user3_linefeedlyrictick;
}


CString IniFile::get_midiport() 
{
	return midiport;
}

CString IniFile::get_insdeffile()
{
	bool exist = file_exists(insdeffile);
	if(exist)
	{
		return insdeffile;
	}
	else
	{
		return "";
	}
//	return file_exists(insdeffile)?insdeffile:"";
}

CString IniFile::get_insdef()
{
	CString insdf = insdef.Mid(1,insdef.GetLength()-2);
	return insdf;
}

CString IniFile::get_xgeffectfile()
{
	return file_exists(xgeffectfile)?xgeffectfile:"";
}

CString IniFile::get_keyboardmodel()
{
	CString model = keyboardmodel.Mid(1,keyboardmodel.GetLength()-2);
	return model;
}

int IniFile::get_countin_drum()
{
	return countin_drum;
}

int IniFile::get_countin_vel()
{
	return countin_vel;
}

int IniFile::get_multipart_convert()
{
	return multipart_convert;
}

int IniFile::get_drumsetup_convert()
{
	return drumsetup_convert;
}

bool IniFile::get_double_notes()
{
	return double_notes;
}

bool IniFile::get_not_double_drum_notes()
{
	return not_double_drum_notes;
}

bool IniFile::get_delete_empty_chan()
{
	return delete_empty_chan;
}

CString IniFile::get_voicefile_folder()
{
	return voicefile_folder;
}

bool IniFile::get_fill_sequ_track()
{
	return fill_sequ_track;
}

int IniFile::get_no_effect_blocks()
{
	return no_effect_blocks;
}

int IniFile::get_vh_effect_block()
{
	return vh_effect_block;
}

bool IniFile::get_alien_sysex()
{
	return alien_sysex;
}

bool IniFile::get_alien_voice()
{
	return alien_voice;
}

bool IniFile::get_with_lyric_cuepoint()
{
	return with_lyric_cuepoint;
}

bool IniFile::get_with_drums_from_insfile()
{
	return with_drums_from_insfile;
}

bool IniFile::get_vh_events_delete()
{
	return vh_events_delete;
}

bool IniFile::get_psruti_text()
{
	return psruti_text;
}

int IniFile::get_click_main_vol()
{
	return click_main_vol;
}

int IniFile::get_click_note_meas()
{
	return click_note_meas;
}

int IniFile::get_click_note_beat()
{
	return click_note_beat;
}

int IniFile::get_click_vel_meas()
{
	return click_vel_meas;
}

int IniFile::get_click_vel_beat()
{
	return click_vel_beat;
}

bool IniFile::get_with_sysex_drumkit_mode()
{
	return with_sysex_drumkit_mode;
}

// *************** set functions ***************

void IniFile::set_sourcefile(CString filename) 
{
	sourcefile = filename;
}

void IniFile::set_protfile(CString filename) 
{
	protfile = filename;
}

void IniFile::set_recordfile(CString filename) 
{
	recordfile = filename;
}

void IniFile::set_chordlyricfile(CString filename) 
{
	chordlyricfile = filename;
}

void IniFile::set_revoicefile(CString filename) 
{
	revoicefile = filename;
}

void IniFile::set_drumfile(CString filename) 
{
	drumfile = filename;
}

void IniFile::set_language(CString lang) 
{
	language = lang;
}

void IniFile::set_user(int is_usr)
{
	is_user = is_usr;
}

void IniFile::set_user1_taktlyric(CString taktl) 
{
	user1_taktlyric = taktl;	
}

void IniFile::set_user1_beatlyric(CString beatl)
{
	user1_beatlyric = beatl;
}

void IniFile::set_user1_endlyric(CString endl)
{
	user1_endlyric = endl;
}

void IniFile::set_user1_linefeedlyrictick(int tick)
{
	user1_linefeedlyrictick = tick;
}

void IniFile::set_user2_taktlyric(CString taktl) 
{
	user2_taktlyric = taktl;	
}

void IniFile::set_user2_beatlyric(CString beatl)
{
	user2_beatlyric = beatl;
}

void IniFile::set_user2_endlyric(CString endl)
{
	user2_endlyric = endl;
}

void IniFile::set_user2_linefeedlyrictick(int tick)
{
	user2_linefeedlyrictick = tick;
}

void IniFile::set_user3_taktlyric(CString taktl) 
{
	user3_taktlyric = taktl;	
}

void IniFile::set_user3_beatlyric(CString beatl)
{
	user3_beatlyric = beatl;
}

void IniFile::set_user3_endlyric(CString endl)
{
	user3_endlyric = endl;
}

void IniFile::set_user3_linefeedlyrictick(int tick)
{
	user3_linefeedlyrictick = tick;
}

void IniFile::set_midiport(CString midip)
{
	midiport = midip;
}

void IniFile::set_insdeffile(CString file)
{
	insdeffile = file;
}

void IniFile::set_insdef(CString insdf)
{
	insdef = "\""+insdf+"\"";
}

void IniFile::set_xgeffectfile(CString file)
{
	xgeffectfile = file;
}

void IniFile::set_keyboardmodel(CString model)
{
	keyboardmodel = "\""+model+"\"";
}

void IniFile::set_countin_drum(int drum)
{
	countin_drum = drum;
}

void IniFile::set_countin_vel(int vel)
{
	countin_vel = vel;
}

void IniFile::set_multipart_convert(int val)
{
	multipart_convert = val;
}

void IniFile::set_drumsetup_convert(int val)
{
	drumsetup_convert = val;
}

void IniFile::set_double_notes(bool val)
{
	double_notes = val;
}

void IniFile::set_not_double_drum_notes(bool val)
{
	not_double_drum_notes = val;
}

void IniFile::set_delete_empty_chan(bool del)
{
	delete_empty_chan = del;
}

void IniFile::set_voicefile_folder(CString folder)
{
	voicefile_folder = folder;
}

void IniFile::set_fill_sequ_track(bool val)
{
	fill_sequ_track = val;
}

void IniFile::set_no_effect_blocks(int no)
{
	no_effect_blocks = no;
}

void IniFile:: set_vh_effect_block(int block)
{
	vh_effect_block = block;
}

void IniFile::set_alien_sysex(bool set)
{
	alien_sysex = set;
}

void IniFile::set_alien_voice(bool set)
{
	alien_voice = set;
}

void IniFile::set_with_lyric_cuepoint(bool set)
{
	with_lyric_cuepoint = set;
}

void IniFile::set_with_drums_from_insfile(bool set)
{
	with_drums_from_insfile = set;
}

void IniFile::set_vh_events_delete(bool set)
{
	vh_events_delete = set;
}

void IniFile::set_psruti_text(bool set)
{
	psruti_text = set;
}

void IniFile::set_click_main_vol(int mv)
{
	click_main_vol = mv;
}

void IniFile::set_click_note_meas(int nm)
{
	click_note_meas = nm;
}

void IniFile::set_click_note_beat(int nb)
{
	click_note_beat = nb;
}

void IniFile::set_click_vel_meas(int vm)
{
	click_vel_meas = vm;
}

void IniFile::set_click_vel_beat(int vb)
{
	click_vel_beat = vb;
}

void IniFile::set_with_sysex_drumkit_mode(bool set)
{
	with_sysex_drumkit_mode = set;
}


void IniFile::ReadIniFile()
{
	int i;

	CStdioFile psruti_ini;
	
	if (!psruti_ini.Open(inifile, CFile::modeRead))   
	{
		return;
	}

	CString line;
	bool found;
	CString searchstring;
		
	// Look for source
	found = false;	
	searchstring=sourcelabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get source-path				
			{
				found = true;
			}
			break;
		}
	}
	sourcefile = found?line:"";

	// Look for prot
	found = false;	
	searchstring=protlabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get prot-path				
			{
				found = true;
			}
			break;
		}
	}
	protfile = found?line:"";

	// Look for record
	found = false;	
	searchstring=recordlabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get record-path				
			{
				found = true;
			}
			break;
		}
	}
	recordfile = found?line:"";

	// Look for chordlyric
	found = false;	
	searchstring=chordlyriclabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get chordlyric-path				
			{
				found = true;
			}
			break;
		}
	}
	chordlyricfile = found?line:"";

	// Look for revoicefile
	found = false;	
	searchstring=revoicefilelabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get revoicefile-path				
			{
				found = true;
			}
			break;
		}
	}
	revoicefile = found?line:"";
	
	// Look for drumfile
	found = false;	
	searchstring=drumfilelabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get drumfile-path				
			{
				found = true;
			}
			break;
		}
	}
	drumfile = found?line:"";
	
	// Look for language
	found = false;	
	searchstring=languagelabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get language				
			{
				found = true;
			}
			break;
		}
	}
	language = found?line:"";

	// Look for user1_taktlyric
	found = false;	
	searchstring=user1_taktlyriclabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get taktlyric				
			{
				found = true;
			}
			break;
		}
	}
	if (found) user1_taktlyric = line;

	// Look for user1_beatlyric
	found = false;	
	searchstring=user1_beatlyriclabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get beatlyric				
			{
				found = true;
			}
			break;
		}
	}
	if (found) user1_beatlyric = line;


	// Look for user1_endlyric
	found = false;	
	searchstring=user1_endlyriclabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get endlyric				
			{
				found = true;
			}
			break;
		}
	}
	if (found) user1_endlyric = line;


	// Look for user1_linefeedlyric
	found = false;	
	searchstring=user1_linefeedlyriclabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get linefeedlyric				
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		if (line=="-1")
		{
			user1_linefeedlyrictick = -1;
		}
		else
		{
			int ticks = 0;
			for (i=0; i<line.GetLength(); i++)
			{
				ticks = 10*ticks + (line[i]-'0');
			}
			user1_linefeedlyrictick = ticks;
		}
	}

	// Look for user2_taktlyric
	found = false;	
	searchstring=user2_taktlyriclabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get taktlyric				
			{
				found = true;
			}
			break;
		}
	}
	if (found) user2_taktlyric = line;

	// Look for user2_beatlyric
	found = false;	
	searchstring=user2_beatlyriclabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get beatlyric				
			{
				found = true;
			}
			break;
		}
	}
	if (found) user2_beatlyric = line;


	// Look for user2_endlyric
	found = false;	
	searchstring=user2_endlyriclabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get endlyric				
			{
				found = true;
			}
			break;
		}
	}
	if (found) user2_endlyric = line;


	// Look for user2_linefeedlyric
	found = false;	
	searchstring=user2_linefeedlyriclabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get linefeedlyric				
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		if (line=="-1")
		{
			user2_linefeedlyrictick = -1;
		}
		else
		{
			int ticks = 0;
			for (i=0; i<line.GetLength(); i++)
			{
				ticks = 10*ticks + (line[i]-'0');
			}
			user2_linefeedlyrictick = ticks;
		}
	}

	// Look for user3_taktlyric
	found = false;	
	searchstring=user3_taktlyriclabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get taktlyric				
			{
				found = true;
			}
			break;
		}
	}
	if (found) user3_taktlyric = line;

	// Look for user3_beatlyric
	found = false;	
	searchstring=user3_beatlyriclabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get beatlyric				
			{
				found = true;
			}
			break;
		}
	}
	if (found) user3_beatlyric = line;


	// Look for user3_endlyric
	found = false;	
	searchstring=user3_endlyriclabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get endlyric				
			{
				found = true;
			}
			break;
		}
	}
	if (found) user3_endlyric = line;


	// Look for user3_linefeedlyric
	found = false;	
	searchstring=user3_linefeedlyriclabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get linefeedlyric				
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		if (line=="-1")
		{
			user3_linefeedlyrictick = -1;
		}
		else
		{
			int ticks = 0;
			for (i=0; i<line.GetLength(); i++)
			{
				ticks = 10*ticks + (line[i]-'0');
			}
			user3_linefeedlyrictick = ticks;
		}
	}


	// Look for is_user
	found = false;	
	searchstring=userlabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get user text				
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		is_user = (line=="1")?1:(line=="2")?2:(line=="3")?3:1; 
	}

	// Look for midiport
	found = false;	
	searchstring=midiportlabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get midiport				
			{
				found = true;
			}
			break;
		}
	}
	if (found) midiport = line;

	// Look for insdeffile
	found = false;	
	searchstring=insdeffilelabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get insdeffile				
			{
				found = true;
			}
			break;
		}
	}
	if (found) insdeffile = line;

	// Look for insdef
	found = false;	
	searchstring=insdeflabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get insdef				
			{
				found = true;
			}
			break;
		}
	}
	if (found) insdef = line;

	// Look for xgeffectfile
	found = false;	
	searchstring=xgeffectfilelabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get xgeffectfile				
			{
				found = true;
			}
			break;
		}
	}
	if (found) xgeffectfile = line;

	// Look for keyboardmodel
	found = false;	
	searchstring=keyboardmodellabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get keyboardmodel				
			{
				found = true;
			}
			break;
		}
	}
	if (found) keyboardmodel = line;

	// Look for CountIn drum note
	found = false;	
	searchstring=countin_drumlabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get string of drum-number				
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		int drum = 0;
		for (i=0; i<line.GetLength(); i++)
		{
			drum = 10*drum + (line[i]-'0');
		}
		countin_drum = drum;
	}

	// Look for CountIn velocity
	found = false;	
	searchstring=countin_vellabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get count-in velocity				
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		int vel = 0;
		for (i=0; i<line.GetLength(); i++)
		{
			vel = 10*vel + (line[i]-'0');
		}
		countin_vel = vel;
	}

	// Look for Multipart Convert
	found = false;	
	searchstring=multipart_convertlabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get multipart convert				
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		multipart_convert = line=="0"?0:1;
	}

	// Look for Drum Setup Convert
	found = false;	
	searchstring=drumsetup_convertlabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get drumsetup convert				
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		drumsetup_convert = line=="0"?0:1;
	}	

	// Look for Double Notes
	found = false;	
	searchstring=double_noteslabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get double notes				
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		double_notes = line=="1"?true:false;
	}

	// Look for Double Drum Notes
	found = false;	
	searchstring=not_double_drum_noteslabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get double notes				
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		not_double_drum_notes = line=="1"?true:false;
	}

	// Look for Delete Empty Chan
	found = false;	
	searchstring=delete_empty_chanlabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get delete empty channels				
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		delete_empty_chan = (line=="1");
	}

	// Look for voicefile path
	found = false;	
	searchstring=voicefile_folderlabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get string voicefile path				
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		voicefile_folder = line;
	}
	else
	{
		voicefile_folder = "";
	}

	// Look for fill_sequ_track
	found = false;	
	searchstring=fill_sequ_tracklabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get fill_sequ_track				
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		fill_sequ_track = (line=="1");
	}

	// Look for no_effect_blocks
	found = false;	
	searchstring=no_effect_blockslabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get no_effect_blocks				
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		int len = 0;
		for (i=0; i<line.GetLength(); i++)
		{
			len = 10*len + (line[i]-'0');
		}
		no_effect_blocks = (len<1)?0:len;
	}
	else
	{
		no_effect_blocks = 5; // DSP2 to DSP6 (Tyros3)
	}
	
	
	// Look for vh_effect_block
	found = false;	
	searchstring=vh_effect_blocklabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get vh_effect_block				
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		int len = 0;
		for (i=0; i<line.GetLength(); i++)
		{
			len = 10*len + (line[i]-'0');
		}
		vh_effect_block = (len<1)?1:len;
	}
	else
	{
		vh_effect_block = 5; // init for all keyboards since PSR-9000
	}

	// Look for alien sysex allowed
	found = false;	
	searchstring=alien_sysexlabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get alien sysex			
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		alien_sysex = (line=="1");
	}

	// Look for alien voice allowed
	found = false;	
	searchstring=alien_voicelabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get alien sysex			
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		alien_voice = (line=="1");
	}

	// Look for with lyric cuepoint
	found = false;	
	searchstring = lyric_cuepointlabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) 			
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		with_lyric_cuepoint = (line=="1");
	}

	// Look for drums from insfile
	found = false;	
	searchstring = with_drums_from_insfilelabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) 		
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		with_drums_from_insfile = (line=="1");
	}

	// Look for delete events with activate VH
	found = false;	
	searchstring = vh_events_deletelabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) 		
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		vh_events_delete = (line=="1");
	}

	
	// Look for psruti_text
	found = false;	
	searchstring=psruti_textlabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get psruti_text		
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		psruti_text = (line=="1");
	}


	// Look for click_main_vol
	found = false;	
	searchstring=click_main_vollabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get click_mail_vol		
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		int len = 0;
		for (i=0; i<line.GetLength(); i++)
		{
			len = 10*len + (line[i]-'0');
		}
		click_main_vol = (len<0)?60:(len>127)?60:len;
	}

	// Look for click_note_meas
	found = false;	
	searchstring=click_note_measlabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get click_note_meas		
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		int len = 0;
		for (i=0; i<line.GetLength(); i++)
		{
			len = 10*len + (line[i]-'0');
		}
		click_note_meas = (len<0)?24:(len>127)?24:len;
	}


	// Look for click_note_beat
	found = false;	
	searchstring=click_note_beatlabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get click_note_beat		
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		int len = 0;
		for (i=0; i<line.GetLength(); i++)
		{
			len = 10*len + (line[i]-'0');
		}
		click_note_beat = (len<0)?23:(len>127)?23:len;
	}


	// Look for click_vel_meas
	found = false;	
	searchstring=click_vel_measlabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // get click_vel_meas		
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		int len = 0;
		for (i=0; i<line.GetLength(); i++)
		{
			len = 10*len + (line[i]-'0');
		}
		click_vel_meas = (len<0)?127:(len>127)?127:len;
	}


	// Look for click_vel_beat
	found = false;	
	searchstring=click_vel_beatlabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) // click_vel_beat		
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		int len = 0;
		for (i=0; i<line.GetLength(); i++)
		{
			len = 10*len + (line[i]-'0');
		}
		click_vel_beat = (len<0)?60:(len>127)?60:len;
	}


	// Look for with sysex drumkit mode
	found = false;	
	searchstring = with_sysex_drumkit_modelabel;
	psruti_ini.SeekToBegin();
	while (psruti_ini.ReadString(line))
	{
		if (line == searchstring)
		{
			if (psruti_ini.ReadString(line)) 			
			{
				found = true;
			}
			break;
		}
	}
	if (found)
	{
		with_sysex_drumkit_mode = (line=="1");
	}

	
	psruti_ini.Close();
}

void IniFile::WriteIniFile()
{
	CString scr;
	CStdioFile psruti_ini;
	
	if (psruti_ini.Open(inifile, CFile::modeRead))   
	{
		psruti_ini.Close();
		CFile::Remove(inifile);
	}

	psruti_ini.Open(inifile,CFile::modeCreate | CFile::modeWrite);
	psruti_ini.SeekToBegin();

	// Build new inifile

	psruti_ini.WriteString(sourcelabel+"\n");
	psruti_ini.WriteString(sourcefile+"\n");

	if (protfile !="")
	{
		psruti_ini.WriteString(protlabel+"\n");
		psruti_ini.WriteString(protfile+"\n");
	}

	if (recordfile !="")
	{
		psruti_ini.WriteString(recordlabel+"\n");
		psruti_ini.WriteString(recordfile+"\n");
	}

	if (chordlyricfile !="")
	{
		psruti_ini.WriteString(chordlyriclabel+"\n");
		psruti_ini.WriteString(chordlyricfile+"\n");
	}
	
	if (revoicefile !="")
	{
		psruti_ini.WriteString(revoicefilelabel+"\n");
		psruti_ini.WriteString(revoicefile+"\n");
	}

	if (drumfile !="")
	{
		psruti_ini.WriteString(drumfilelabel+"\n");
		psruti_ini.WriteString(drumfile+"\n");
	}
	
	psruti_ini.WriteString(languagelabel+"\n");
	psruti_ini.WriteString(language+"\n");

	if (user1_taktlyric !="")
	{
		psruti_ini.WriteString(user1_taktlyriclabel+"\n");
		psruti_ini.WriteString(user1_taktlyric+"\n");
	}

	if (user1_beatlyric !="")
	{
		psruti_ini.WriteString(user1_beatlyriclabel+"\n");
		psruti_ini.WriteString(user1_beatlyric+"\n");
	}


	if (user1_endlyric !="")
	{
		psruti_ini.WriteString(user1_endlyriclabel+"\n");
		psruti_ini.WriteString(user1_endlyric+"\n");
	}

	// Linefeedlyric
	scr.Format("%i",user1_linefeedlyrictick);
	psruti_ini.WriteString(user1_linefeedlyriclabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	if (user2_taktlyric !="")
	{
		psruti_ini.WriteString(user2_taktlyriclabel+"\n");
		psruti_ini.WriteString(user2_taktlyric+"\n");
	}

	if (user2_beatlyric !="")
	{
		psruti_ini.WriteString(user2_beatlyriclabel+"\n");
		psruti_ini.WriteString(user2_beatlyric+"\n");
	}


	if (user2_endlyric !="")
	{
		psruti_ini.WriteString(user2_endlyriclabel+"\n");
		psruti_ini.WriteString(user2_endlyric+"\n");
	}

	// Linefeedlyric
	scr.Format("%i",user2_linefeedlyrictick);
	psruti_ini.WriteString(user2_linefeedlyriclabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	if (user3_taktlyric !="")
	{
		psruti_ini.WriteString(user3_taktlyriclabel+"\n");
		psruti_ini.WriteString(user3_taktlyric+"\n");
	}

	if (user3_beatlyric !="")
	{
		psruti_ini.WriteString(user3_beatlyriclabel+"\n");
		psruti_ini.WriteString(user3_beatlyric+"\n");
	}


	if (user3_endlyric !="")
	{
		psruti_ini.WriteString(user3_endlyriclabel+"\n");
		psruti_ini.WriteString(user3_endlyric+"\n");
	}

	// Linefeedlyric
	scr.Format("%i",user3_linefeedlyrictick);
	psruti_ini.WriteString(user3_linefeedlyriclabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// is_user
	scr = (is_user==1)?"1":(is_user==2)?"2":(is_user==3)?"3":"1";
	psruti_ini.WriteString(userlabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	if (midiport !="")
	{
		psruti_ini.WriteString(midiportlabel+"\n");
		psruti_ini.WriteString(midiport+"\n");
	}

	// insdeffile

	if (insdeffile !="")
	{
		psruti_ini.WriteString(insdeffilelabel+"\n");
		psruti_ini.WriteString(insdeffile+"\n");
	}

	// insdef

	if (insdef !="")
	{
		psruti_ini.WriteString(insdeflabel+"\n");
		psruti_ini.WriteString(insdef+"\n");
	}

	// xgeffectfile

	if (xgeffectfile !="")
	{
		psruti_ini.WriteString(xgeffectfilelabel+"\n");
		psruti_ini.WriteString(xgeffectfile+"\n");
	}

	// keyboardmodel

	if (keyboardmodel !="")
	{
		psruti_ini.WriteString(keyboardmodellabel+"\n");
		psruti_ini.WriteString(keyboardmodel+"\n");
	}

	// CountIn drum
	scr.Format("%i",countin_drum);
	psruti_ini.WriteString(countin_drumlabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// CountIn velocity
	scr.Format("%i",countin_vel);
	psruti_ini.WriteString(countin_vellabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// Multipart Convert
	scr.Format("%i",multipart_convert);
	psruti_ini.WriteString(multipart_convertlabel+"\n");
	psruti_ini.WriteString(scr+"\n");
	
	// Drum Setup Convert
	scr.Format("%i",drumsetup_convert);
	psruti_ini.WriteString(drumsetup_convertlabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// Double Notes
	scr.Format("%i",double_notes?1:0);
	psruti_ini.WriteString(double_noteslabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// Not Double Drum Notes
	scr.Format("%i",not_double_drum_notes?1:0);
	psruti_ini.WriteString(not_double_drum_noteslabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// Delete Empty Chan
	scr = delete_empty_chan?"1":"0";
	psruti_ini.WriteString(delete_empty_chanlabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// Voicefile Folder
	if (voicefile_folder !="")
	{
		psruti_ini.WriteString(voicefile_folderlabel+"\n");
		psruti_ini.WriteString(voicefile_folder+"\n");
	}

	// fill_sequ_track
	scr.Format("%i",fill_sequ_track?1:0);
	psruti_ini.WriteString(fill_sequ_tracklabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// no_effect_blocks
	scr.Format("%i",no_effect_blocks);
	psruti_ini.WriteString(no_effect_blockslabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// vh_effect_block
	scr.Format("%i",vh_effect_block);
	psruti_ini.WriteString(vh_effect_blocklabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// alien sysex

	scr.Format("%i",alien_sysex?1:0);
	psruti_ini.WriteString(alien_sysexlabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// alien voice

	scr.Format("%i",alien_voice?1:0);
	psruti_ini.WriteString(alien_voicelabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// with_lyric_cuepoint

	scr.Format("%i",with_lyric_cuepoint?1:0);
	psruti_ini.WriteString(lyric_cuepointlabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// with_drums_from_insfile

	scr.Format("%i",with_drums_from_insfile?1:0);
	psruti_ini.WriteString(with_drums_from_insfilelabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// with_drums_from_insfile

	scr.Format("%i",vh_events_delete?1:0);
	psruti_ini.WriteString(vh_events_deletelabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// hpmusic text
	if (!psruti_text)
	{
		scr.Format("%i",psruti_text?1:0);
		psruti_ini.WriteString(psruti_textlabel+"\n");
		psruti_ini.WriteString(scr+"\n");
	}

	// click_main_vol
	scr.Format("%i",click_main_vol);
	psruti_ini.WriteString(click_main_vollabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// click_note_meas
	scr.Format("%i",click_note_meas);
	psruti_ini.WriteString(click_note_measlabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// click_note_beat
	scr.Format("%i",click_note_beat);
	psruti_ini.WriteString(click_note_beatlabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// click_vel_meas
	scr.Format("%i",click_vel_meas);
	psruti_ini.WriteString(click_vel_measlabel+"\n");
	psruti_ini.WriteString(scr+"\n");
	
	// click_vel_beat
	scr.Format("%i",click_vel_beat);
	psruti_ini.WriteString(click_vel_beatlabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	// with_sysex_drumkit_mode
	scr.Format("%i",with_sysex_drumkit_mode?1:0);
	psruti_ini.WriteString(with_sysex_drumkit_modelabel+"\n");
	psruti_ini.WriteString(scr+"\n");

	psruti_ini.Close();

//	if (lf != NULL) lf->add("Ini-Datei wurde geschrieben");
}


