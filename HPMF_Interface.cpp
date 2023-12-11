// HPMF_Interface.cpp: Implementierung der Klasse HPMF_Interface.
//
//////////////////////////////////////////////////////////////////////

#include "HPMF_Interface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "stdafx.h"
#include "psruti.h"
#include "resource.h"
#include "Play.h"
#include "sysex_event_prot.h"
#include "MyArrays.h"


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

HPMF_Interface::HPMF_Interface()
{
	mf = NULL;
	bank_list = NULL;
	bad_error = false;
}


HPMF_Interface::HPMF_Interface(Log* logf, CString sourcef,
							   IniFile *o_inifile)
{
	p_inifile = o_inifile;

	linefeed_char = GlobalUtilities::get_linefeed_char();
	multipart_convert = p_inifile->get_multipart_convert();
	drum_setup_convert = p_inifile->get_drumsetup_convert();
	double_notes_allowed = p_inifile->get_double_notes();
	double_drum_notes_allowed = p_inifile->get_not_double_drum_notes();
	delete_empty_chan = p_inifile->get_delete_empty_chan();
	fill_sequ_track = p_inifile->get_fill_sequ_track();
	no_blocks = p_inifile->get_no_effect_blocks();
	vh_block = p_inifile->get_vh_effect_block();
	alien_sysex = p_inifile->get_alien_sysex();
	alien_voice = p_inifile->get_alien_voice();
	lyric_cuepoint = p_inifile->get_with_lyric_cuepoint();
	with_drums_from_insfile = p_inifile->get_with_drums_from_insfile();
	vh_events_delete = p_inifile->get_vh_events_delete();
	psruti_text = p_inifile->get_psruti_text();

	is_user = 1;
	bad_error = false;
	bank_list = NULL;
	mf = NULL;

	mf = HP_Init();

	if (mf == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_HP_INIT),NULL,MB_OK|MB_TASKMODAL);
		bad_error = true;
		return;
	}

	lf = logf;
	sourcefile = sourcef;

	UINT result;
	source_changed = false;

	result = HP_Load(mf, sourcefile);

	if (result!=HP_ERR_NONE)
	{
		CString r;
		r.Format("%s: %s",GlobalUtilities::get_resource_string(IDS_ERROR_SOURCE),sourcefile);
		::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);

		bad_error = true;
		HP_Free(mf);
		mf = NULL;
		return;
	}

	// Some more chunks are ignored. Format XF or SFF?
	with_additional_chunks = (HP_MoreChunks(mf) != 0);

	xg_effects = NULL;

	init_hpmfiledata();

	if (!(p_inifile->get_with_sysex_drumkit_mode()) )
	{
		remove_sysex_drum_mode();
	}
}

HPMF_Interface::HPMF_Interface(const HPMF_Interface& h)
{
	int i, k;

	// Copy eventlist, tempolist
	HP_Select(h.mf,HP_ALL_EVENTS);
	HP_Copy(h.mf);
	mf = HP_Init();
	HP_Paste(mf,0,HP_NO_DELETE,HP_ALL_EVENTS);
	HP_Deselect(mf);

	multipart_convert = h.multipart_convert;
	drum_setup_convert = h.drum_setup_convert;
	double_notes_allowed = h.double_notes_allowed;
	double_drum_notes_allowed = h.double_drum_notes_allowed;
	no_key_signatures = h.no_key_signatures;
	no_chords = h.no_chords;
	last_num = h.last_num;
	last_denum = h.last_denum;

	with_cuepoint_lyrics = h.with_cuepoint_lyrics;
	with_drums_from_insfile = h.with_drums_from_insfile;
	vh_events_delete = h.vh_events_delete;
	with_gm_on = h.with_gm_on;
	with_xg_on = h.with_xg_on;
	with_gs_on = h.with_gs_on;
	with_songname = h.with_songname;
	with_xfchords = h.with_xfchords;
	with_lyrics = h.with_lyrics;
	with_copyright = h.with_copyright;
	with_xfhd = h.with_xfhd;
	with_xfln = h.with_xfln;
	alien_sysex = h.alien_sysex;
	alien_voice = h.alien_voice;
	lyric_cuepoint = h.lyric_cuepoint;

	first_key = h.first_key;

	max_tempo = h.max_tempo;

	with_insdef = h.with_insdef;
	for (i=0; i<16; i++)
	{
		vh_channel[i] = h.vh_channel[i];
		vh_channel_sysex_exist[i] = h.vh_channel_sysex_exist[i];
	}
	vocoder_sysex_exist = h.vocoder_sysex_exist;
	vh_ad_on_sysex_exist = h.vh_ad_on_sysex_exist;
	vh_ad_off_sysex_exist = h.vh_ad_off_sysex_exist;
	no_banks = 0;
	bank_list = NULL;

	bank_voices_list_free = h.bank_voices_list_free;
	for (i=0; i<bank_voices_list_free; i++)
	{
		bank_voices_list[i].bank_no = h.bank_voices_list[i].bank_no;
		for (k=0; k<128; k++)
		{
			bank_voices_list[i].voice_name[k] = h.bank_voices_list[i].voice_name[k];
		}
	}

	lf = h.lf;
	sourcefile = h.sourcefile;
	proposed_songname = h.proposed_songname;
	songname = h.songname;
	copyrightname = h.copyrightname;
	composer = h.composer;
	lyricist = h.lyricist;
	strcpy(filetitle,h.filetitle);

	strcpy(user1_takt_lyric,h.user1_takt_lyric);
	strcpy(user1_beat_lyric,h.user1_beat_lyric);
	strcpy(user1_end_lyric,h.user1_end_lyric);
	user1_linefeedlyrictick = h.user1_linefeedlyrictick;
	strcpy(user2_takt_lyric,h.user2_takt_lyric);
	strcpy(user2_beat_lyric,h.user2_beat_lyric);
	strcpy(user2_end_lyric,h.user2_end_lyric);
	user2_linefeedlyrictick = h.user2_linefeedlyrictick;
	strcpy(user3_takt_lyric,h.user3_takt_lyric);
	strcpy(user3_beat_lyric,h.user3_beat_lyric);
	strcpy(user3_end_lyric,h.user3_end_lyric);
	user3_linefeedlyrictick = h.user3_linefeedlyrictick;
	is_user = h.is_user;
	linefeed_char = h.linefeed_char;
	no_blocks = h.no_blocks;
	vh_block = h.vh_block;
	p_inifile = h.p_inifile;

	is_simple_chords = h.is_simple_chords;
	is_sysex_chords = h.is_sysex_chords;
	chord_protocol = h.chord_protocol;
	chord_protocol_lyric = h.chord_protocol_lyric;
	protfile = h.protfile;
	is_fill_lyrics = h.is_fill_lyrics;
	selected_chord_chan = h.selected_chord_chan;
	for (i=0; i<16; i++)
	{
		no_notes[i] = h.no_notes[i];
		maxvolume[i] = h.maxvolume[i];
		mute[i] = h.mute[i];
		new_mute[i] = h.new_mute[i];
		lowlimit[i] = h.lowlimit[i];
		new_lowlimit[i] = h.new_lowlimit[i];
		highlimit[i] = new_highlimit[i];

		mlv_list[i].msb = h.mlv_list[i].msb;
		mlv_list[i].time_msb = h.mlv_list[i].time_msb;
		mlv_list[i].lsb = h.mlv_list[i].lsb;
		mlv_list[i].time_lsb = h.mlv_list[i].time_lsb;
		mlv_list[i].voice = h.mlv_list[i].voice;
		mlv_list[i].time_voice = h.mlv_list[i].time_voice;
		mlv_list[i].melody = h.mlv_list[i].melody;
		mlv_list[i].is_mega = h.mlv_list[i].is_mega;
		mlv_list[i].is_sart = h.mlv_list[i].is_sart;

		patchname[i] = h.patchname[i];

		transpose_delta_list[i] = h.transpose_delta_list[i];
	}

	ppqn = h.ppqn;
	original_ppqn = h.original_ppqn;
	chord = NULL;
	is_pause = h.is_pause;
	num = h.num;
	denum = h.denum;

	free_off_list = h.free_off_list;
	for (i=0; i<free_off_list; i++)
	{
		off_list[i].note = h.off_list[i].note;
		off_list[i].chan = h.off_list[i].chan;
		off_list[i].time = h.off_list[i].time;
	}
	cevlist_free = h.cevlist_free;
	cevlist.Copy(h.cevlist);

	lyriclist_free = h.lyriclist_free;
	lyriclist.Copy(h.lyriclist);

	takt_bar_time_list_free = h.takt_bar_time_list_free;
	takt_bar_time_list.Copy(h.takt_bar_time_list);

	sysexlist_free = h.sysexlist_free;
	sysexlist.Copy(h.sysexlist);

	HP_Deselect(mf);
	init_hpmfiledata(); // try to avoid this call
}

HPMF_Interface::~HPMF_Interface()
{
	if (bank_list != NULL)
	{
		HP_Delete(bank_list);
		bank_list = NULL;
		no_banks = 0;
	}
	if (mf != NULL) HP_Free(mf);
}


const char* HPMF_Interface::heikoplate_text = "Converted with PSRUTI http://www.heikoplate.de";
const char* HPMF_Interface::kar_string = "@KMIDI KARAOKE FILE";

const int HPMF_Interface::XG_master_volume_data_len = 9;
unsigned char HPMF_Interface::XG_master_volume_data[9] =
	{0xf0,0x43,0x10,0x4c,0x00,0x00,0x04,0x00,0xf7};

const int HPMF_Interface::GM2_master_volume_data_len = 8;
unsigned char HPMF_Interface::GM2_master_volume_data[8] =
	{0xf0,0x7f,0x7f,0x04,0x01,0x00,0x00,0xf7};

const CString HPMF_Interface::shortpatch[128] =
{
	" Piano",
	"BrtPno",
	" ElPno",
	"HonkyT",
	"ElPno1",
	"ElPno2",
	"HrpsiC",
	" Clav ",
	"Celest",
	"GlockS",
	"MusBox",
	"  Vib ",
	"Marimb",
	"  Xyl ",
	"TubCel",
	"Dulcim",
	"DrwOrg",
	"PrcOrg",
	"RckOrg",
	" ChOrg",
	" RdOrg",
	" Accrd",
	"Hrmonc",
	"TAccrd",
	"Guitar",
	"Guitar",
	"Guitar",
	"Guitar",
	"Guitar",
	"Guitar",
	"Guitar",
	" GtHrm",
	" Bass ",
	" Bass ",
	" EBass",
	" FBass",
	"SlBass",
	"SlBass",
	"SyBass",
	"SyBass",
	"Violin",
	" Viola",
	" Cello",
	" CBass",
	" Strs ",
	" PStrs",
	"OrStrs",
	"Timpan",
	"StrEns",
	"StrEns",
	"SyStrs",
	"SyStrs",
	"ChAahs",
	"VcOohs",
	" SyVce",
	"OrcHit",
	" Trump",
	" Tromb",
	" Tuba ",
	"MutTrp",
	" FHorn",
	"BrassS",
	"SBrass",
	"SBrass",
	"SopSax",
	"AltSax",
	"TenSax",
	"BarSax",
	" Oboe ",
	"EngHrn",
	"Bassoo",
	" Clari",
	" Picc ",
	" Flute",
	"Record",
	" PanFl",
	"Bottle",
	"Shakuh",
	"Whistl",
	" Ocar ",
	" Lead1",
	" Lead2",
	" Lead3",
	" Lead4",
	" Lead5",
	" Lead6",
	" Lead7",
	" Lead8",
	" Pad1 ",
	" Pad2 ",
	" Pad3 ",
	" Pad4 ",
	" Pad5 ",
	" Pad6 ",
	" Pad7 ",
	" Pad8 ",
	" Rain ",
	"Sndtrk",
	" Cryst",
	"Atmosp",
	"Britns",
	"Goblns",
	"Echoes",
	" SciFi",
	" Sitar",
	" Banjo",
	"Shamis",
	" Koto ",
	"Kalimb",
	" Bagp ",
	"Fiddle",
	"Shanai",
	" TBell",
	" Agogo",
	"SteelD",
	"Woodbl",
	"TaikoD",
	"MelTom",
	"SynthD",
	" RCymb",
	"FretNs",
	"BreaNs",
	"Seashr",
	"BirdTw",
	"TelRng",
	" Heli ",
	" Appl ",
	"Gunsht"
};

const CString HPMF_Interface::drywet_text[128] =
{	// the same list in file sysex_event_data
	"-----",
	"D63>W",
	"D62>W",
	"D61>W",
	"D60>W",
	"D59>W",
	"D58>W",
	"D57>W",
	"D56>W",
	"D55>W",
	"D54>W",
	"D53>W",
	"D52>W",
	"D51>W",
	"D50>W",
	"D49>W",
	"D48>W",
	"D47>W",
	"D46>W",
	"D45>W",
	"D44>W",
	"D43>W",
	"D42>W",
	"D41>W",
	"D40>W",
	"D39>W",
	"D38>W",
	"D37>W",
	"D36>W",
	"D35>W",
	"D34>W",
	"D33>W",
	"D32>W",
	"D31>W",
	"D30>W",
	"D29>W",
	"D28>W",
	"D27>W",
	"D26>W",
	"D25>W",
	"D24>W",
	"D23>W",
	"D22>W",
	"D21>W",
	"D20>W",
	"D19>W",
	"D18>W",
	"D17>W",
	"D16>W",
	"D15>W",
	"D14>W",
	"D13>W",
	"D12>W",
	"D11>W",
	"D10>W",
	"D9>W",
	"D8>W",
	"D7>W",
	"D6>W",
	"D5>W",
	"D4>W",
	"D3>W",
	"D2>W",
	"D1>W",
	"D=W",
	"D<W1",
	"D<W2",
	"D<W3",
	"D<W4",
	"D<W5",
	"D<W6",
	"D<W7",
	"D<W8",
	"D<W9",
	"D<W10",
	"D<W11",
	"D<W12",
	"D<W13",
	"D<W14",
	"D<W15",
	"D<W16",
	"D<W17",
	"D<W18",
	"D<W19",
	"D<W20",
	"D<W21",
	"D<W22",
	"D<W23",
	"D<W24",
	"D<W25",
	"D<W26",
	"D<W27",
	"D<W28",
	"D<W29",
	"D<W30",
	"D<W31",
	"D<W32",
	"D<W33",
	"D<W34",
	"D<W35",
	"D<W36",
	"D<W37",
	"D<W38",
	"D<W39",
	"D<W40",
	"D<W41",
	"D<W42",
	"D<W43",
	"D<W44",
	"D<W45",
	"D<W46",
	"D<W47",
	"D<W48",
	"D<W49",
	"D<W50",
	"D<W51",
	"D<W52",
	"D<W53",
	"D<W54",
	"D<W55",
	"D<W56",
	"D<W57",
	"D<W58",
	"D<W59",
	"D<W60",
	"D<W61",
	"D<W62",
	"D<W63"
};

unsigned char HPMF_Interface::vh_sysex_chan[9] = {0xf0, 0x43, 0x10, 0x4c, 0x04, 0x00, 0x14, 0x0f, 0xf7};
unsigned char HPMF_Interface::vocoder_sysex[10] = {0xf0, 0x43, 0x10, 0x4c, 0x04, 0x00, 0x00, 0x59, 0x00, 0xf7};
unsigned char HPMF_Interface::vh_ad_on_sysex[9] = {0xf0, 0x43, 0x10, 0x4c, 0x04, 0x00, 0x0c, 0x40, 0xf7};
unsigned char HPMF_Interface::vh_ad_off_sysex[9] = {0xf0, 0x43, 0x10, 0x4c, 0x04, 0x00, 0x0c, 0x00, 0xf7};

const CString HPMF_Interface::chordfile_title = "PSRUTI Chord-Analysis";
const CString HPMF_Interface::xfchordfile_title = "PSRUTI XF Chord-Protocol";
const CString HPMF_Interface::lyricfile_title = "PSRUTI Lyric-Protocol";
const CString HPMF_Interface::sysexfile_title = "PSRUTI SysEx-Protocol";
const CString HPMF_Interface::timefile_title = "PSRUTI Time-Protocol";
const CString HPMF_Interface::chordlyricfile_title = "PSRUTI Chord and Lyric Protocol";
const CString HPMF_Interface::chord_indicator = "Chd";
const CString HPMF_Interface::lyric_indicator = "Lyr"; // same length!

//**************************************************************************
//*
//*		fill_takt_bar_time_list
//*		fills list between two Time Signatures and from last to end
//*
//**************************************************************************

void HPMF_Interface::fill_takt_bar_time_list(int old_takt_of_taktchange, int takt_of_taktchange, bool last, int last_event_time)
{
	TAKT_BAR_TIME_ELEM tbte;
	int takt;
	int bar;
	// number of ticks of a bar
	int no_per_denum = last_denum==1?ppqn*4:last_denum==2?ppqn*2:last_denum==4?ppqn:last_denum==8?ppqn/2:ppqn;
	int last_time = takt_bar_time_list[takt_bar_time_list_free-1].time;
	for (takt = old_takt_of_taktchange; takt < takt_of_taktchange; takt++)
	{
		//		for (bar = takt==0?1:0; bar < last_num; bar++)
		for (bar = (takt==old_takt_of_taktchange)?1:0; bar < last_num; bar++)
		{
			tbte.takt = takt;
			tbte.bar = bar;
			tbte.time = last_time + no_per_denum;
			tbte.num = last_num;
			tbte.tbe = (bar==0)?TAKT:((bar==last_num-1)?END:BEAT);
			last_time = tbte.time;

			takt_bar_time_list.SetAtGrow(takt_bar_time_list_free,tbte);
			takt_bar_time_list_free++;
		}
	}

	if (last)
	{
		for (bar=0; bar < last_num; bar++)
		{
			tbte.time = last_time +no_per_denum;
			if (tbte.time > last_event_time)
			{
				break;
			}
			tbte.takt = takt_of_taktchange;
			tbte.bar = bar;
			tbte.num = last_num;
			tbte.tbe = (bar==0)?TAKT:((bar==last_num-1)?END:BEAT);
			takt_bar_time_list.SetAtGrow(takt_bar_time_list_free,tbte);
			takt_bar_time_list_free++;
			last_time = tbte.time;
		}
	}
	else
	{
		tbte.takt = takt_of_taktchange;
		tbte.bar = 0;
		tbte.time = last_time +no_per_denum;
		tbte.num = last_num;
		tbte.tbe = TAKT;
		takt_bar_time_list.SetAtGrow(takt_bar_time_list_free,tbte);
		takt_bar_time_list_free++;
	}

}

//**************************************************************************
//*
//*		fill_part_chan_list
//*		index is multipart_sysex part, value is channel
//*
//**************************************************************************

void HPMF_Interface::fill_part_chan_list()
{
	int i;
	int id, chan, time, type;
	int part, channel;

	// initialize part_chan_list
	for (i=0; i<128; i++)
	{
		if (i<16)
		{
			part_chan_list[i] = i;
		}
		else
		{
			part_chan_list[i] = -1;
		}
	}

	for (i=0; i<16; i++)
	{
		rcv_chan_exist[i] = false;
	}

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_SYSEX)
		{
			unsigned char *data;
			int length;

			HP_ReadSysex(mf,id,&time,&data,&length);

			if (data[1]==0x43 &&
				data[2]==0x10 &&
				data[3]==0x4c &&
				data[4]==0x08 &&
				data[6]==0x04)
			{ // Multipart SysEx Rcv Channel
				part = data[5];
				channel = data[7];
				part_chan_list[part] = channel;
				rcv_chan_exist[channel] = true;
			}
			HP_Delete(data);
		}
	}
}

//**************************************************************************
//*
//*		is_organflute_sysex
//*		finds out, if sysex is a clavinova organ flute sysEx
//*
//**************************************************************************


//**************************************************************************
//*
//*		is_part_sysex
//*		finds out, if sysex is a YAMAHA Multipart SysEx
//*
//**************************************************************************

bool HPMF_Interface::is_organflute_sysex(HP_MIDIFILE_MODULE *mf, int id, int *chan)
{
	int time;
	unsigned char* data;
	int length;
	bool is = false;
	*chan = -1;
	HP_ReadSysex(mf,id,&time,&data,&length);

	if ((data[1]==0x43)&&
		(data[2]==0x73)&&
		(data[3]==0x01)&&
		(data[4]==0x06)&&
		(data[5]==0x0b))
	{
		*chan = data[10];
		is = true;
	}
	HP_Delete(data);
	return is;
}


bool HPMF_Interface::is_part_sysex(HP_MIDIFILE_MODULE *mf, int id, int *part)
{
	int time;
	unsigned char* data;
	int length;
	bool is = false;
	*part = -1;
	HP_ReadSysex(mf,id,&time,&data,&length);
	if (data[1]!=0x43 ||
		data[2]!=0x10 ||
		data[3]!=0x4c)
	{
		HP_Delete(data);
		return is;
	}

	if ((data[4]==0x08)||(data[4]==0x0a))
	{
		*part = data[5];
		is = true;
	}
	else
	if (data[4]==0x02 && data[6]==0x5b)
	{ // Variation Part
		*part = data[7];
		is = true;
	}
	else
	if (data[4]==0x03 && data[6]==0x0c)
	{ // Variation Part
		*part = data[7];
		is = true;
	}

	HP_Delete(data);
	return is;
}

//**************************************************************************
//*
//*		convert_multipart_sysex_to_controller
//*		argument id must point to an arbitrary sysex
//*     at this time part = channel always, even if part may
//*     be connected by SysEx rcv channel.
//*
//**************************************************************************

void HPMF_Interface::convert_multipart_sysex_to_controller(int id)
{
	// convert some Multipart SysEx into standard MIDI-Events

	int time;
	unsigned char* data;
	int length;

	if (multipart_convert==0) return;

	HP_ReadSysex(mf,id,&time,&data,&length);

	if (data[1]==0x43 && length==9)
	{
		if (data[2]==0x10 && data[3]==0x4c && data[4]==0x08)
		{
			int part = data[5];
			int channel;
			if ((part >= 0) && (part <= 15))
			{
				if (part_chan_list[part] == part)
				{
					channel = part;
					switch(data[6])
					{
					case 1:
						{
							HP_DeleteEvent(mf,id);
							HP_InsertController(mf,time,channel,HP_BANK_SELECT_MSB,data[7]);
							break;
						}
					case 2:
						{
							HP_DeleteEvent(mf,id);
							HP_InsertController(mf,time,channel,HP_BANK_SELECT_LSB,data[7]);
							break;
						}
					case 3:
						{
							HP_DeleteEvent(mf,id);
							HP_InsertProgramChange(mf,time,channel,data[7]);
							break;
						}
					case 5:
						{
							HP_DeleteEvent(mf,id);
							HP_InsertController(mf,time,channel,
								data[7]==0?HP_MONO:HP_POLY, data[7]);
							break;
						}
					case 11:
						{
							HP_DeleteEvent(mf,id);
							HP_InsertController(mf,time,channel,HP_MAIN_VOLUME,data[7]);
							break;
						}
					case 14:
						{
							HP_DeleteEvent(mf,id);
							HP_InsertController(mf,time,channel,HP_PANPOT,data[7]);
							break;
						}
					case 18:
						{
							HP_DeleteEvent(mf,id);
							HP_InsertController(mf,time,channel,HP_CHORUS_SEND_LEVEL,data[7]);
							break;
						}
					case 19:
						{
							HP_DeleteEvent(mf,id);
							HP_InsertController(mf,time,channel,HP_REVERB_SEND_LEVEL,data[7]);
							break;
						}
					case 20:
						{
							HP_DeleteEvent(mf,id);
							HP_InsertController(mf,time,channel,HP_VARIATION_SEND_LEVEL,data[7]);
							break;
						}
					case 21:
						{
							HP_DeleteEvent(mf,id);
							HP_InsertController(mf,time,channel,HP_VIBRATO_RATE,data[7]);
							break;
						}
					case 22:
						{
							HP_DeleteEvent(mf,id);
							HP_InsertController(mf,time,channel,HP_VIBRATO_DEPTH,data[7]);
							break;
						}
					case 23:
						{
							HP_DeleteEvent(mf,id);
							HP_InsertController(mf,time,channel,HP_VIBRATO_DELAY,data[7]);
							break;
						}
					case 26:
						{
							HP_DeleteEvent(mf,id);
							HP_InsertController(mf,time,channel,HP_ATTACK_TIME,data[7]);
							break;
						}
					case 27:
						{
							HP_DeleteEvent(mf,id);
							HP_InsertController(mf,time,channel,HP_DECAY_TIME,data[7]);
							break;
						}
					case 28:
						{
							HP_DeleteEvent(mf,id);
							HP_InsertController(mf,time,channel,HP_RELEASE_TIME,data[7]);
							break;
						}
					case 103:
						{
							HP_DeleteEvent(mf,id);
							HP_InsertController(mf,time,channel,HP_PORTAMENTO,data[7]);
							break;
						}
					case 104:
						{
							HP_DeleteEvent(mf,id);
							HP_InsertController(mf,time,channel,HP_PORTAMENTO_TIME,data[7]);
							break;
						}
					}
				}
			}
		}
	}
	HP_Delete(data);
}

//**************************************************************************
//*
//*		init_hpmfiledata
//*		only an extension of the constructor
//*
//**************************************************************************

void HPMF_Interface::init_hpmfiledata()
{
	int i;
	bool is_kar = false;
	bool at_not_needed = false;

	double last_tempo = -1.0;
	int last_tempo_time = -1;

	struct {int last_id; int last_note; int last_time; int last_length;} notelist[16];

	source_changed = false;
	no_key_signatures = 0;
	no_chords = 0;
	cevlist_free = 0;
	bass_note_list_free = 0;
	lyriclist_free = 0;
	takt_bar_time_list_free = 0;
	sysexlist_free = 0;
	xg_effects = NULL;

	last_num = 4;
	last_denum = 4;

	with_cuepoint_lyrics = false;
	with_drums_from_insfile = false;
	with_gm_on = false;
	with_xg_on = false;
	with_gs_on = false;
	with_xfchords = false;
	with_lyrics = false;
	with_copyright = false;
	with_xf_version = false;
	with_xfhd = false;

	first_key = get_key_signature();

	max_tempo = -1.0;

	bank_voices_list_free = 0;
	bank_list = NULL;
	no_banks = 0;
	with_insdef = false;

	// maxvolume, mute, mlv

	for (i=0; i<16; i++)
	{
		maxvolume[i] = -2; // chan doesn't exist
		mute[i] = true;
		new_mute[i] = true;
		lowlimit[i] = 127;
		new_lowlimit[i] = 127;
		highlimit[i] = 0;
		new_highlimit[i] = 0;
		transpose_delta_list[i] = 0;
		patchname[i] = "";
		mlv_list[i].bankname = "";
		mlv_list[i].voicename = "";

		notelist[i].last_id = -1;
		notelist[i].last_note = -1;
		notelist[i].last_time = -1;
		notelist[i].last_length = -1;
	}

	int id, chan, type, time, number, value, note, vel, length;

	// change PPQN strict to 480

	HP_ReadPPQN(mf,&original_ppqn);

	if (original_ppqn != 480)
	{
		HP_ChangePPQN(mf,HP_PPQN480);
		ppqn = 480;
	}
	else
	{
		ppqn = 480;
	}

/*
	CString r;
	r.Format("original_ppqn %i; ppqn %i",original_ppqn, ppqn);
	MessageBox(r);
*/

	/* Delete all double SysEx at same time positions *******************/

	unsigned char *sysex_data = NULL;
	unsigned char *last_sysex_data = NULL;
	int last_sysex_time = -1;
	int last_sysex_length = -1;
	int no_sysex_deleted = 0;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_SYSEX)
		{
			HP_ReadSysex(mf,id,&time,&sysex_data,&length);
			if (last_sysex_time == -1)
			{
				last_sysex_time = time;
				last_sysex_length = length;
				last_sysex_data = sysex_data;
				continue;
			}
			else
			{
				if ((time != last_sysex_time)||(length != last_sysex_length))
				{
					HP_Delete(last_sysex_data);
					last_sysex_time = time;
					last_sysex_length = length;
					last_sysex_data = sysex_data;
					continue;
				}
				else
				{
					bool same_sysex = true;
					for (i=0; i<length; i++)
					{
						if (sysex_data[i] != last_sysex_data[i])
						{
							same_sysex = false;
							break;
						}
					}
					if (!same_sysex)
					{
						HP_Delete(last_sysex_data);
						last_sysex_time = time;
						last_sysex_length = length;
						last_sysex_data = sysex_data;
						continue;
					}
					else
					{
						HP_DeleteEvent(mf,id);
						no_sysex_deleted++;
					}
				}
			}
		}
	}

	if (last_sysex_data != NULL)
	{
		HP_Delete(last_sysex_data);
	}

/*
	CString r;
	r.Format("%i SysEx deleted",no_sysex_deleted);
	MessageBox(r);
*/


	/* Delete all double Lyrics at same time positions ************************/

	char *lyric_text = NULL;
	char *preceding_lyric_text = NULL;
	int preceding_lyric_time = -1;
	int preceding_lyric_length = -1;
	int no_lyric_deleted = 0;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_LYRIC)
		{
			HP_ReadLyric(mf,id,&time,&lyric_text);
			length = strlen(lyric_text);
			if (preceding_lyric_time == -1)
			{
				preceding_lyric_time = time;
				preceding_lyric_length = length;
				preceding_lyric_text = lyric_text;
				continue;
			}
			else
			{
				if ((time != preceding_lyric_time)||(length != preceding_lyric_length))
				{
					HP_Delete(preceding_lyric_text);
					preceding_lyric_time = time;
					preceding_lyric_length = length;
					preceding_lyric_text = lyric_text;
					continue;
				}
				else
				{
					bool same_lyric = true;
					for (i=0; i<length; i++)
					{
						if (lyric_text[i] != preceding_lyric_text[i])
						{
							same_lyric = false;
							break;
						}
					}
					if (!same_lyric)
					{
						HP_Delete(preceding_lyric_text);
						preceding_lyric_time = time;
						preceding_lyric_length = length;
						preceding_lyric_text = lyric_text;
						continue;
					}
					else
					{
						HP_DeleteEvent(mf,id);
						no_lyric_deleted++;
					}
				}
			}
		}
	}

	if (preceding_lyric_text != NULL)
	{
		HP_Delete(preceding_lyric_text);
	}
/*
	CString r;
	r.Format("%i Lyrics deleted",no_lyric_deleted);
	MessageBox(r);
*/

   // Delete all events after last note + 8 quarters
   int time_of_last_note_off = -1;
   HP_Rewind(mf);
   while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
   {
	   if (type==HP_NOTE)
	   {
		   HP_ReadNote(mf,id,&time, &chan,&note,&vel,&length);
		   if (time+length > time_of_last_note_off)
		   {
			   time_of_last_note_off = time+length;
		   }
	   }
   }

   int time_of_end_midi = time_of_last_note_off + 8*ppqn;

   HP_Rewind(mf);
   while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
   {
	   if (time > time_of_last_note_off)
	   {
		   if (time < time_of_end_midi)
		   {
//			   if (type == HP_TEMPO)
//			   {
//				   HP_DeleteEvent(mf,id);
//			   }
		   }
		   else
		   {
			   HP_DeleteEvent(mf,id);
		   }
	   }
   }


	// Are there any Rcv Channel SysEx, which map a part to an different channel-number?
	fill_part_chan_list();

	HP_Rewind(mf);
	HP_SetFirst(mf,HP_LAST);

	compute_songname();

	// A file is a Karaoke-file if it has the extension ".kar!
	CString fileextension = "";
	int last = sourcefile.GetLength()-1;
	for (i=last; i>0; i--)
	{
		char ch = sourcefile.GetAt(i);
		if (ch=='.') break;
		fileextension.Insert(0,ch);
	}
	if (fileextension=="kar")
	{
		is_kar = true;
		at_not_needed = true;
	}

	// init copyrightname, composer and lyricist
	copyrightname = "";
	composer = "";
	lyricist = "";

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_TEXT)
		{
			int i;
			char* text;

			HP_ReadText(mf,id,&time,&text);

			// find out, if XFhd Event
			{
				if ((int)strlen(text)>=4)
				{
					if ((text[0]=='X') &&
						(text[1]=='F') &&
						(text[2]=='h') &&
						(text[3]=='d')    )
					{
						with_xfhd = true;
						HP_Delete(text);
						continue;
					}
				}
			}

			// find out, if we have got a .kar-file
			if (is_kar)
			{
				HP_Delete(text);
				continue;
			}

			if (!is_kar)
			{
				if (text[0]=='@' && text[1]=='K')
				{
					is_kar = true;
					for (i=2; (i<(int)strlen(kar_string))&&(i<(int)strlen(text));i++)
					{
						if (text[i] != kar_string[i])
						{
							is_kar = false;
							break;
						}
					}
				}
				if (is_kar || (text[0]!='K'))
				{
					HP_Delete(text);
					continue;
				}

				is_kar = true;
				for (i=1; (i<(int)strlen(kar_string)-1)&&(i<(int)strlen(text));i++)
				{
					if (text[i] != kar_string[i+1])
					{
						is_kar = false;
						break;
					}
				}
				HP_Delete(text);
				if (is_kar) HP_DeleteEvent(mf,id);
				continue;
			}
		}

		if (type==HP_COPYRIGHT)
		{
			char* text;
			with_copyright = true;
			HP_ReadCopyright(mf,id,&time,&text);
			copyrightname = text;
			HP_Delete(text);
			continue;
		}

		if (type == HP_XF_VERSION_ID)
		{
			if (with_xf_version)
			{ // only one meta event XF Version
				HP_DeleteEvent(mf,id);
			}
			else
			{
				with_xf_version = true;
			}
			continue;
		}

		if (type == HP_NOTE)
		{
			HP_ReadNote(mf,id,&time,&chan,&value,&vel,&length);
			mute[chan] = false;
			continue;
		}

		if (type == HP_SYSEX)
		{
			convert_multipart_sysex_to_controller(id);
			continue;
		}
	}

	update_no_notes(no_notes);

	get_composer_lyricist(&composer, &lyricist);

	// delete all events from channels without notes if wanted
	if (delete_empty_chan)
	{
		HP_Rewind(mf);
		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			// Look for empty channels?
			if (chan != HP_NO_CHAN)
			{
				if (no_notes[chan]==0)
				{
					HP_DeleteEvent(mf,id);
				}
			}
		}
	}

	// Now scan other events
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (chan != HP_NO_CHAN)
		{
			if ((maxvolume[chan]==-2)&&(!mute[chan]))
			{
				maxvolume[chan] = -1; // channel exist, but no volume controller
			}

			if (type==HP_MAIN_VOLUME)
			{
				HP_ReadController(mf,id,&time,&chan,&number,&value);

				if (value > maxvolume[chan])
				{
					maxvolume[chan] = value;
				}
				continue;
			}

			if (type== HP_NOTE)
			{
				HP_ReadNote(mf,id,&time, &chan, &note, &vel, &length);
				if (note < lowlimit[chan]) lowlimit[chan] = note;
				if (note > highlimit[chan]) highlimit[chan] = note;

				if (maxvolume[chan]==-1)
				{
//					int new_time = time<2?0:time-2;
//					HP_SetFirst(mf);
//					HP_InsertController(mf,new_time,chan,HP_MAIN_VOLUME,100);
					maxvolume[chan]=100;
				}
				continue;
			}
			continue;
		}

		// look for tempo
		if (type == HP_TEMPO)
		{
			double bpm_double;
			int cps;
			HP_ReadTempo(mf,id,&time,&bpm_double,&cps);
			if (bpm_double == last_tempo)
			{
				HP_DeleteEvent(mf,id);
				continue;
			}
			last_tempo = bpm_double;
			last_tempo_time = time;
			if(bpm_double > max_tempo)
			{
				max_tempo = bpm_double;
			}
			continue;
		}

		// look for key signatures and chords
		if (type == HP_KEY_SIGNATURE)
		{
			no_key_signatures++;
			if (first_key == "")
			{
				char* key;
				HP_ReadKeySignature(mf,id,&time,&key);
				first_key = key;
				HP_Delete(key);
			}
			continue;
		}

		// look for time signature and repair, if denum > 16

		if (type == HP_TIME_SIGNATURE)
		{
			int num, denum, metronome_click, n32;
			HP_ReadTimeSignature(mf,id,&time,&num,&denum,&metronome_click,&n32);
			if (denum > 16)
			{
				int div = denum/16;
				int new_denum = 16;
				int new_num = num/div==0?1:num/div;
				int result = HP_ChangeTimeSignature(mf,id,new_num,new_denum,metronome_click,n32);
			}
		}


		if (type == HP_CHORD_NAME)
		{
			with_xfchords = true;
			continue;
		}

		if (type == HP_CUE_POINT)
		{
			bool found = true;
			char* text = NULL;
			HP_ReadCuePoint(mf,id,&time,&text);
			const CString r = "$Lyrc:"; // look for "$Lyrc:" only
			int len = strlen(text);
			if (len>r.GetLength())
			{
				for (int i = 0; i<r.GetLength(); i++)
				{
					if (text[i] != r[i])
					{
						found = false;
						break;
					}
				}
			}

			if (found)
			{
				if (lyric_cuepoint)
				{	// lyric_cuepoint wanted
					if (!with_cuepoint_lyrics)
					{
						with_cuepoint_lyrics = true;
					}
				}
				else
				{	// ordered: delete alle lyric cuepoints
					HP_DeleteEvent(mf,id);
				}

			}
			if (text != NULL) HP_Delete(text);
			continue;
		}

		if (type == HP_TEXT)
		{
			char* text;
			HP_ReadText(mf,id,&time,&text);

			// Bei alten Einträgen war noch ein 0a dabei
			if ((int)strlen(text)==(int)strlen(heikoplate_text)+1)
			{
				text[(int)strlen(heikoplate_text)] = (char)0;
			}

			if (strcmp(text,heikoplate_text)==0)
			{
				HP_DeleteEvent(mf,id);
			}
			HP_Delete(text);
			continue;
		}

		if (type == HP_SYSEX)
		{
			// look for gm_on, xg_on and chord sysex
			unsigned char *data;
			int length;

			if (with_gm_on && with_xg_on && with_xfchords) continue;

			HP_ReadSysex(mf,id,&time,&data,&length);

			if (length == 6)
			{
				// look for gm on
				bool is = GlobalUtilities::is_gm_on_sysex(data);

				if (is && with_gm_on)
				{
					HP_DeleteEvent(mf,id);
				}
				else
				{
					if (is)
					{
						with_gm_on = true;
						if (time > 0)
						{
							HP_DeleteEvent(mf,id);
							HP_SetFirst(mf);
							HP_InsertSysEx(mf,0,data);
						}
					}
				}
				HP_Delete(data);
				continue;
			}

			if (length == 9)
			{	// both, xg_on and chord-sysex have same length

				// look for xg on
				bool is = GlobalUtilities::is_xg_on_sysex(data);
				if (is)
				{
					with_xg_on = true;
					HP_Delete(data);
					continue;
				}

				// look for Chord SysEx
				if ( (data[1]==0x43) && (data[2]==0x7e) && (data[3]==0x02))
				{
					with_xfchords=true;
					HP_Delete(data);
					continue;
				}

				HP_Delete(data);
				continue;
			}

			if (GlobalUtilities::is_turn_tg300b_on(data))
			{
				with_gs_on = true;
				HP_Delete(data);
				continue;
			}

			HP_Delete(data);
			continue;
		}
	}
	// end scan HP MIDIFILE eventlist

	if (is_kar)
	{
		convert_kar_to_mid(at_not_needed);
	}

	update_mlv_list();

	if (drum_setup_convert==1)
	{
		exchange_drumsysex_to_nrpn();
	}

	int no_vh_chan = find_vh_channel();
		// only after update_mlv_list
	exchange_lyric_linefeed();
	update_lyriclist();
	update_takt_bar_time_list();
	fill_patchname_list();
	xgeffects_from_file();

	chord = NULL;
	protfile = "";
	free_off_list = 0;
	last_num = 4;
	last_denum = 4;
	is_simple_chords = false;
	is_fill_lyrics = true;
	is_pause = false;
}

//**************************************************************************
//*
//*		convert_kar_to_mid
//*		called only from init_hpmfiledata
//*
//**************************************************************************

void HPMF_Interface::convert_kar_to_mid(bool at_not_needed)
{
	int id, chan, type, time;
	char *text;
	bool at_arrived = false;
	int T_arrived = 0; // counts @T
	bool first_slash = true; // for removing first lyric '\\'

	int no_of_text_events = 0;
	int no_of_lyric_events = 0;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_LYRIC)
		{
			no_of_lyric_events++;
			continue;
		}

		if (type==HP_TEXT)
		{
			no_of_text_events++;
			continue;
		}

		if ((type==HP_SONG_TRACK_NAME)&&(!at_not_needed))
		{
			HP_DeleteEvent(mf,id);
			with_songname = false;
			proposed_songname = "";
			songname = "";
			continue;
		}
	}

	bool delete_lyrics = (no_of_lyric_events>0)&&(no_of_text_events>10);

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if ((type==HP_LYRIC)&&delete_lyrics)
		{
			HP_DeleteEvent(mf,id);
			continue;
		}
	}

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		int i;
		char new_text[80];

		if (type==HP_TEXT)
		{
			HP_ReadText(mf,id,&time,&text);
			if (text[0]=='@')
			{
				at_arrived = true;

				switch (text[1])
				{
				case 'T':
					T_arrived++;
					{
						int l = 0;
						for (i=2;(i<(int)strlen(text)+1)&&(i<80);i++)
						{
							if ((text[i]==0x0a) || (text[i]==0x0d))
							{
								continue;
							}
							new_text[l]=text[i];
							l++;
						}
					}

					if (T_arrived==1)
					{
						if (!with_songname)
						{
							proposed_songname = new_text;
							songname = proposed_songname; // real songname in file
							HP_InsertSongTrackName(mf,new_text);
							with_songname = true;
						}
					}
					else
					if (T_arrived==2)
					{
						if (!with_copyright)
						{
							copyrightname = new_text;
							HP_InsertCopyright(mf,time,new_text);
							with_copyright = true;
						}
					}
					HP_DeleteEvent(mf,id);
					break;
				default:
					HP_DeleteEvent(mf,id);
					break;
				}
			}
			else
			{
				if (at_arrived || at_not_needed)
				{
					// lyric_textevent
					if ((text[0]=='\\')&& first_slash)
					{	// remove first slash
						for (i=1; i<(int)strlen(text)+1; i++)
						{
							text[i-1] = text[i];
						}
						first_slash = false;
					}

					for (i=0; (i<(int)strlen(text)+1) && (i<80); i++)
					{
						if ((text[i]=='\\')||(text[i]=='/'))
						{
							text[i] = linefeed_char;
						}
					}
					HP_DeleteEvent(mf,id);
					HP_InsertLyric(mf,time,text);

				}
			}
			HP_Delete(text);
			continue;
		}
	}
	source_changed = true;
}

//**************************************************************************
//*
//*		is_source_changed
//*
//**************************************************************************

bool HPMF_Interface::is_source_changed()
{
	return source_changed;
}

//**************************************************************************
//*
//*		eval_save
//*
//**************************************************************************

UINT HPMF_Interface::eval_save(CString m_destination)
{
	int id, chan, type, time, note, vel, length;
	insert_heikoplate_text();
	source_changed = false;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
//		if ((type==HP_NOTE)&&!(mlv_list[chan].melody))
		if (type==HP_NOTE)
		{
			HP_ReadNote(mf,id,&time,&chan,&note,&vel,&length);
			if (length==0)
			{
				HP_ChangeNoteLength(mf,id,chan,note,1,HP_NO_PERCENT);
			}
		}
	}
    return HP_Save(mf,m_destination,HP_SMF0);
}

//**************************************************************************
//*
//*		eval_volume
//*		realizes volume changes, HP MIDIFILE used
//*
//**************************************************************************

void HPMF_Interface::eval_volume (int v[16])
{
	int id, chan, type, time, number, value;

	source_changed = false;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		// Look for empty channels?
		if (chan == HP_NO_CHAN)
		{
			continue;
		}
		if (mute[chan])
		{
			continue;
		}

		if ((type&HP_TYPE_MASK)==HP_CONTROLLER_TYPE)
		{
			HP_ReadController(mf,id,&time,&chan,&number,&value);

			if (number == 7)
			{
				int new_v;
				if(maxvolume[chan]==value)
				{
					new_v = v[chan];
				}
				else
				{
					new_v = (maxvolume[chan]!=0)?
						(int)(((float)value * (float)(v[chan]))/(float)(maxvolume[chan])):
					v[chan];
				}
				UINT result = HP_ChangeController(mf,id,HP_MAIN_VOLUME,new_v,HP_NO_PERCENT);
				if (result != HP_ERR_NONE)
				{
					::MessageBox(AfxGetMainWnd()->m_hWnd,HP_ErrText(result),NULL,MB_OK|MB_TASKMODAL);
				}
			}
		}
	}

	for (chan=0; chan<16; chan++)
	{
		if (mute[chan]) continue;
		maxvolume[chan] = v[chan];
	}
	source_changed = true;
}

//**************************************************************************
//*
//*		eval_voice_browse
//*
//**************************************************************************

void HPMF_Interface::eval_voice_browse(char search_string[64],
									   HP_CWBANKVOICE **bank_voice_list,
									   long *bank_voice_list_len)
{
	UINT result = HP_CWInsGetBankVoiceList(mf, search_string,
						bank_voice_list,bank_voice_list_len);
	return;
}

//**************************************************************************
//*
//*		delete_bank_voice_list
//*		(for voice browse)
//*
//**************************************************************************

void HPMF_Interface::delete_bank_voice_list(HP_CWBANKVOICE **bank_voice_list,long *bank_voice_list_len)
{
	HP_Delete(*bank_voice_list);
	*bank_voice_list_len = 0;
}

//**************************************************************************
//*
//*		eval_max_values
//*		eval changes of effects of GlobalUtilities::effect_list
//*
//**************************************************************************

void HPMF_Interface::eval_max_values(int effect_index,
									 int maxvalue[16],
									 bool insert_event[16],
									 bool chan_changed[16])
{
	int i;
	int id, chan, type, time, number, value;
	bool local_chan_changed[16];
	bool xg_convert_needed = false;
	source_changed = false;

	int no = GlobalUtilities::effect_list[effect_index].no;

	for (i=0; i<16; i++)
	{
		if (chan_changed[i]&&insert_event[i])
		{
			HP_SetFirst(mf, HP_LAST);
			// insert event
			if (no <= 127)
			{	// Controller, no = controller-number
				HP_InsertController(mf,0,i,HP_CONTROLLER_TYPE,maxvalue[i],no);
				xg_convert_needed = true;
			}
			else
			{
				if (no == 0xd0)
				{	// insert Channel Pressure strictly after first note of channel
					HP_Rewind(mf);
					while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
					{
						if (chan != i) continue;
						if (type != HP_NOTE) continue;
						HP_InsertChannelPressure(mf,time+1,i,maxvalue[i]);
						break;
					}
				}
			}
			local_chan_changed[i] = false; // done here
		}
		else
		{
			local_chan_changed[i] = chan_changed[i];
		}
	}

	// get  max-values before changes
	int old_maxvalue[16];
	get_max_values(old_maxvalue, effect_index);

	if (no <= 127)
	{	// Controller, no = controller-number
		HP_Rewind(mf);
		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (chan == HP_NO_CHAN) continue;
			if (!local_chan_changed[chan]) continue;
			if ((type&HP_TYPE_MASK)==HP_CONTROLLER_TYPE)
			{
				HP_ReadController(mf,id,&time,&chan,&number,&value);
				if (number != no) continue;

				int new_v;

				if(old_maxvalue[chan]==value)
				{
					new_v = maxvalue[chan];
				}
				else
				{
					new_v = (old_maxvalue[chan]!=0)?
						(int)(((float)value * (float)(maxvalue[chan]))/(float)(old_maxvalue[chan])):
							maxvalue[chan];
				}
				HP_ChangeController(mf,id,type,new_v,HP_NO_PERCENT);
				xg_convert_needed = true;
			}
		}
	}
	else
	{
		if (no != 0xd0) return;
		HP_Rewind(mf);
		int last_new_v = 0;
		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (chan == HP_NO_CHAN) continue;
			if (!local_chan_changed[chan]) continue;
			if (type != HP_CHANNEL_PRESSURE) continue;
			HP_ReadChannelPressure(mf,id, &time, &chan, &value);
			int new_v;

			if(old_maxvalue[chan]==value)
			{
				new_v = maxvalue[chan];
			}
			else
			{
				new_v = (old_maxvalue[chan]!=0)?
					(int)(((float)value * (float)(maxvalue[chan]))/(float)(old_maxvalue[chan])):
						maxvalue[chan];
			}
			if (new_v==last_new_v)
			{
				HP_DeleteEvent(mf,id);
			}
			else
			{
				last_new_v = new_v;
				HP_ChangeChannelPressure(mf,id,new_v);
			}
		}
	}

	if (xg_convert_needed)
	{
		int no_double_notes;
		int no_pitch_wheels;
		eval_xg_convert(&no_double_notes, &no_pitch_wheels);
	}

	source_changed = true;
}

//**************************************************************************
//*
//*		with_start_beats
//*		finds out, if file with drum-start-beats (count in)
//*		if all_drums, all drums before first note (used outside batch)
//*
//**************************************************************************

bool HPMF_Interface::with_start_beats(int *time_start_beat_start, int *time_start_beat_end)
{
	int i;
	int id, chan, type, time, note, velocity, length;;
	int count_in_start_time = -1;
	int count_in_end_time = -1;
	int last_drum_time = -1;
	int first_drum_note = -1;
	int no_countin_notes = 0;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{

		if (type == HP_NOTE)
		{
			if (mlv_list[chan].melody)
			{
				if (count_in_end_time == -1)
				{
					count_in_end_time = time;
				}
				break;
			}
			else
			{
				HP_ReadNote(mf,id,&time,&chan,&note,&velocity,&length);
				if (first_drum_note == -1)
				{
					first_drum_note = note;
				}
				else
				{
					if (first_drum_note != note)
					{
						count_in_end_time = time;
					}
				}

				if (count_in_start_time==-1)
				{
					count_in_start_time = time;
				}

				// look if drum note outside beat
				if (count_in_end_time == -1)
				{
					bool is_on_beat = false;
					for (i=0; i<takt_bar_time_list_free;i++)
					{
						int beat_time = (takt_bar_time_list[i]).time;
						if (beat_time > time+25) break;

						if ((time >= beat_time-25)&&(time<=beat_time+25))
						{
							is_on_beat = true;
							no_countin_notes++;
							break;
						}
					}
					if (!is_on_beat)
					{
						count_in_end_time = last_drum_time==-1?time:last_drum_time;
						break;
					}
				}
				else
				{
					break;
				}
				last_drum_time = time;
			}
		}
	}

	if ((count_in_start_time==count_in_end_time) || (no_countin_notes<2))
	{	// drums start at same time as melody -> no start-beats
		*time_start_beat_start = -1;
		*time_start_beat_end   = -1;
	}
	else
	{
		*time_start_beat_start = count_in_start_time;
		*time_start_beat_end   = count_in_end_time;
	}

	return (*time_start_beat_start!=-1)&&(*time_start_beat_end!=-1);
}

//**************************************************************************
//*
//*		eval_delete_short_notes
//*     chan selected if Par. chan_list[chan] = 1
//*     delete all notes of selected chan with length <= upto_tick
//*
//**************************************************************************

int HPMF_Interface::eval_delete_short_notes(int chan_list[16],int upto_tick)
{
	int no_notes_deleted = 0;
	int id, chan, type, time;
	int note,velocity,length;
	source_changed = false;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if ((chan_list[chan] <= 0) || (type != HP_NOTE) || (!mlv_list[chan].melody)) continue;
		HP_ReadNote(mf,id,&time,&chan,&note,&velocity,&length);
		if(length <= upto_tick)
		{
			HP_DeleteEvent(mf,id);
			no_notes_deleted++;
		}
	}
	if (no_notes_deleted > 0)
	{
		source_changed = true;
	}
	return no_notes_deleted;
}

//**************************************************************************
//*
//*		eval_delete_start_beats
//*		remove measures with drum-start-beats (count in)
//*
//**************************************************************************

bool HPMF_Interface::eval_delete_start_beats(int time_start_beat_start,int time_start_beat_end)
{
	int id, chan, type, time;
	
	int song_num = -1;
	int song_denum = -1;
	source_changed = false;

	// delete all notes between time_start_beat_start and time_start_beat_end
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if ((time >= time_start_beat_start)&& (time < time_start_beat_end))
		{
			if ((type==HP_NOTE)||(type==HP_LYRIC)) 
			{
				HP_DeleteEvent(mf,id);
			}
		}
		if (time >= time_start_beat_end) break;
	}

	int starttakt, startbeat, starttick;
	int endtakt, endtick, endbeat;

	HP_GetTaktBeatTick(mf,time_start_beat_start,&starttakt, &startbeat, &starttick);
	HP_GetTaktBeatTick(mf,time_start_beat_end,&endtakt, &endbeat, &endtick);

	// starttakt to next takt
	starttakt = ((startbeat>0)||(starttick>0))?starttakt+1:starttakt;

	int starttime, endtime;
	HP_GetTimeFromTaktBeatTick(mf,starttakt,0,0,&starttime);
	HP_GetTimeFromTaktBeatTick(mf,endtakt,0,0,&endtime);

	if (starttime >= endtime) return true;

	// other events between starttime and endtime?
	bool other_events = false;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (time >= endtime) break;
		if (time > starttime) // Time Signature at time == starttime possible
		{
			other_events = true;
			break;
		}
	}

	if (!other_events)
	{	// only shift if no other events
		HP_Deselect(mf);
		// select all events after endtime
		HP_Rewind(mf);
		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (time >= endtime)
			{
				HP_Select(mf,id);
			}
		}

		// shift
		HP_ShiftSelected(mf,-(endtime-starttime));
		HP_Deselect(mf);
	}

	update_takt_bar_time_list();
	source_changed = true;

	return (true);
}

//**************************************************************************
//*
//*		eval_insert_klick
//*		inserts klick/klack notes in channel 10
//*
//**************************************************************************

void HPMF_Interface::eval_insert_klick( int msb_chan10,int lsb_chan10,int main_vol_chan10,
										int noteval_meas, int vel_meas, 
										int noteval_beat, int vel_beat)
{
	int no_double_notes, no_pitch_wheels;
	int i;
	TAKT_BAR_TIME_ELEM tbte;

	eval_xg_convert(&no_double_notes, &no_pitch_wheels);

	// use StandardKit1:
	HP_InsertController(mf, 4*ppqn-5, 9, HP_BANK_SELECT_MSB, msb_chan10);
	HP_InsertController(mf, 4*ppqn-4, 9, HP_BANK_SELECT_LSB, lsb_chan10);
	HP_InsertController(mf,	4*ppqn-3, 9, HP_MAIN_VOLUME, main_vol_chan10);
	HP_InsertProgramChange(mf,4*ppqn-2, 9, 0);

	HP_SetFirst(mf,HP_FIRST);
	for (i = 0; i < takt_bar_time_list_free; i++)
	{
		tbte = takt_bar_time_list[i];
	
// lf->add("tbte[%i], Takt=%i, Bar=%i, Time=%i, Num=%i", i, tbte.takt+1, tbte.bar, tbte.time, tbte.num);

		if (tbte.takt==0) continue; // no clicks in measure 0

		if (tbte.bar==0)
		{
			HP_InsertNote(mf,tbte.time+1, 2, noteval_meas, 9, vel_meas);
// lf->add("Measure: Takt=%i, Bar=%i, Time=%i, Num=%i ,noteval_meas %i", 
//		tbte.takt+1, tbte.bar, tbte.time, tbte.num,noteval_meas);

		}
		else
		{
			HP_InsertNote(mf,tbte.time+1, 2, noteval_beat, 9, vel_beat);
// lf->add("Beat: Takt=%i, Bar=%i, Time=%i, Num=%i ,noteval_beat %i", 
//		tbte.takt+1, tbte.bar, tbte.time, tbte.num,noteval_meas);
		}
	}

	eval_xg_convert(&no_double_notes, &no_pitch_wheels);
}

//**************************************************************************
//*
//*		eval_insert_start_beats
//*		inserts drum-start-beats (count in)
//*
//**************************************************************************

bool HPMF_Interface::eval_insert_start_beats(int drum, int velocity, bool on_all_beats, bool one_measure_count_in)
{
	int id, chan, type, time;
	int num_of_first_note, denum_of_first_note;
	int measure, beat, tick;
	int ticks_of_beat;
	int ticks_of_measure;
	int time_of_shift;
	int scr_time;
	int measures_to_shift;
	int ticks_to_shift;
    int metronome_click,n32;
	int time_first_note;
	const int drum_length = 1;

	bool is_drums = (mlv_list[9].msb!=-1)&&(mlv_list[9].lsb!=-1);

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			time_first_note = time;
			break;
		}
		if (type == HP_TIME_SIGNATURE)
		{
			HP_ReadTimeSignature(mf,id,&time,&num_of_first_note,&denum_of_first_note,&metronome_click,&n32);
		}
	}

	ticks_of_beat = denum_of_first_note==4?ppqn:
					denum_of_first_note==8?ppqn/2:
					denum_of_first_note=2?2*ppqn:
					ppqn;

	ticks_of_measure = num_of_first_note*ticks_of_beat;

// Test
//	CString r;
//	r.Format ("num_of_first_note %i, denum_of_first_note %i, ticks_of_measure %i",num_of_first_note,denum_of_first_note,ticks_of_measure);
//	MessageBox(r);

	HP_GetTaktBeatTick(mf,time_first_note,&measure, &beat, &tick);
	HP_GetTimeFromTaktBeatTick(mf,measure,0,0,&time_of_shift);

    measures_to_shift = (beat!=0)||(tick!=0)?1:2;

	if ((beat!=0)||(tick!=0))
	{
		// Upbeat found: One measure not wise
		one_measure_count_in = false;
	}

	if (one_measure_count_in)
	{
		measures_to_shift--;
	}


// Test
//	r.Format("measure of first note %i, time_of_shift %i, measures_to_shift %i",
//		measure,time_of_shift,measures_to_shift);
//	MessageBox(r);


	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			break;
		}
		if ((type == HP_TIME_SIGNATURE) && (time >= 4*ppqn))
		{
			int n, dn;

			HP_ReadTimeSignature(mf,id,&time,&n,&dn,&metronome_click,&n32);

			if (!((n == 1) && (dn == 4)))
			{
				HP_DeleteEvent(mf,id); //symptom korr.
			}
		}
	}

	HP_Deselect(mf);
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (time >= time_of_shift)
		{
			HP_Select(mf,id);
		}
	}

	// compute ticks of one measure
	HP_GetTimeFromTaktBeatTick(mf,measure+1,0,0,&scr_time);
	ticks_to_shift = measures_to_shift * ticks_of_measure;

	// shift
	HP_ShiftSelected(mf,ticks_to_shift);

	HP_Deselect(mf);

	time_first_note += ticks_to_shift;

	if (!is_drums)
	{
		HP_SetFirst(mf,HP_LAST);
		HP_InsertController(mf,0,9,HP_BANK_SELECT_MSB,127);
		HP_InsertController(mf,0,9,HP_BANK_SELECT_LSB,0);
		HP_InsertProgramChange(mf,0,9,0);
	}

	chan = 9;

	int i;
	time = time_of_shift;

	if (on_all_beats)
	{
		if ((num_of_first_note==12)&&(denum_of_first_note==8))
		{	// 12/8
			for (i=0; i<2*num_of_first_note; i++)
			{
				if (time >= time_first_note) break;
				int vel = velocity;
				if (i%num_of_first_note==0)
				{
					vel += 16;
					if (vel>127) vel=127;
				}

				if (i%3==0)
				{
					HP_InsertNote(mf, time, drum_length, drum, chan, vel);
				}
				time += ticks_of_beat;
			}
		}
		else
		{	// all others
			for (i=0; i<2*num_of_first_note; i++)
			{
				if (time >= time_first_note) break;
				int vel = velocity;

				if (i%num_of_first_note==0)
				{
					vel+=16;
					if (vel>127) vel=127;
				}

				HP_InsertNote(mf, time, drum_length, drum, chan, vel);
				time += ticks_of_beat;
			}
		}
	}
	else
	{	// not at each beat
		for (i=0; i<num_of_first_note;i++)
		{ // first measure

			if (one_measure_count_in)
			{
				break; // second measure only
			}

			int vel = velocity;
			if (i%num_of_first_note==0)
			{
				vel+=16;
				if (vel>127) vel=127;
			}

			if (num_of_first_note==4)
			{	// 4/x
				if ((i==0)||(i==2))
				{
					HP_InsertNote(mf, time, drum_length, drum, chan, vel);
				}
				time += ticks_of_beat;
				continue;
			}
			if (num_of_first_note==3)
			{	// 3/x
				if (i==0)
				{
					HP_InsertNote(mf, time, drum_length, drum, chan, vel);
				}
				time += ticks_of_beat;
				continue;
			}
			if ((num_of_first_note==6)||(num_of_first_note==5))
			{	// 6/x and 5/x
				if ((i==0)||(i==3))
				{
					HP_InsertNote(mf, time, drum_length, drum, chan, vel);
				}
				time += ticks_of_beat;
				continue;
			}

			if ((num_of_first_note==12)&&(denum_of_first_note==8))
			{	// 12/8
				if (i%6==0)
				{
					HP_InsertNote(mf, time, drum_length, drum, chan, vel);
				}
				time += ticks_of_beat;
				continue;
			}

			if (num_of_first_note%3==0)
			{
				if (i%3==0)
				{
					HP_InsertNote(mf, time, drum_length, drum, chan, vel);
				}
				time += ticks_of_beat;
				continue;
			}
			if (num_of_first_note%2==0)
			{
				if (i%2==0)
				{
					HP_InsertNote(mf, time, drum_length, drum, chan, vel);
				}
				time += ticks_of_beat;
				continue;
			}

			// default
			if (i%2==0)
			{
				HP_InsertNote(mf, time, drum_length, drum, chan, vel);
			}
			time += ticks_of_beat;
		}

		for (i=num_of_first_note; i<2*num_of_first_note; i++)
		{ // second measure
			int vel = velocity;
			if (i%num_of_first_note==0)
			{
				vel+=16;
				if (vel>127) vel=127;
			}

			if (time >= time_first_note) break;
			if ((num_of_first_note==12)&&(denum_of_first_note==8))
			{	// 12/8
				if (i%3==0)
				{
					HP_InsertNote(mf, time, drum_length, drum, chan, vel);
				}
				time += ticks_of_beat;
				continue;
			}
			HP_InsertNote(mf, time, drum_length, drum, chan, vel);
			time += ticks_of_beat;
		}
	}

	if ((num_of_first_note!=4)||(denum_of_first_note!=4))
	{
		HP_SetFirst(mf);
		HP_InsertTimeSignature(mf,
			time_of_shift,
 			num_of_first_note,
			denum_of_first_note,
			metronome_click,n32);
	}

	source_changed = true;
	return true;
}

//**************************************************************************
//*
//*		eval_tempo
//*		realizes tempo changes, HP MIDIFILE used
//*
//**************************************************************************

void HPMF_Interface::eval_tempo(double tempo)
{
	HP_Rewind(mf);

	int id, chan, type, time;
	int cps;
	double new_t;
	double bpm_double;

	source_changed = false;

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if ((max_tempo==-1.0) && (type==HP_NOTE))
		{
			HP_SetFirst(mf);
			HP_InsertTempo(mf,time,tempo); // insert the only one event
			source_changed = true;
			max_tempo = tempo; // he should not take chan again
			return;
		}
		if (type==HP_TEMPO)
		{
			HP_ReadTempo(mf,id,&time,&bpm_double,&cps);
			if(max_tempo==bpm_double)
			{
				new_t = tempo;
			}
			else
			{
				new_t = (max_tempo!=0.0)?
					((bpm_double * tempo)/(max_tempo)):5.0;
				if (new_t < 5.0) new_t = 5.0;
			}
			HP_ChangeTempo(mf,id,new_t,HP_NO_PERCENT);
			source_changed = true;
		}
	}
	max_tempo = tempo;
}

//**************************************************************************
//*
//*		eval_expr_mvolume
//*		change controller_events expression to main volume vice versa
//*
//**************************************************************************

int HPMF_Interface::eval_expr_mvolume(bool change_to_mvolume)
{
	int no_changes = 0;
	CArray <double,double> volumes[16];
	double max_volume[16] = {-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.};
	int no_ctrl7[16]  = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int no_ctrl11[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	double last_ctrl7_val[16]  = {100.,100.,100.,100.,100.,100.,100.,100.,100.,100.,100.,100.,100.,100.,100.,100.};
	double last_ctrl11_val[16] = {127.,127.,127.,127.,127.,127.,127.,127.,127.,127.,127.,127.,127.,127.,127.,127.};

	int id, chan, type, time, number, value;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_MAIN_VOLUME)
		{
			HP_ReadController(mf,id, &time, &chan, &number, &value);
			no_ctrl7[chan]++;
			last_ctrl7_val[chan] = (double)value;
			double actual_value = (last_ctrl7_val[chan]*last_ctrl11_val[chan])/127.;
			if (actual_value > max_volume[chan])
			{
				max_volume[chan] = actual_value;
			}
			volumes[chan].Add(actual_value);
			continue;
		}

		if (type == HP_EXPRESSION)
		{
			HP_ReadController(mf,id, &time, &chan, &number, &value);
			no_ctrl11[chan]++;
			last_ctrl11_val[chan] = (double)value;
			double actual_value = (last_ctrl7_val[chan]*last_ctrl11_val[chan])/127.;
			if (actual_value > max_volume[chan])
			{
				max_volume[chan] = actual_value;
			}
			volumes[chan].Add(actual_value);
			continue;
		}
	}

	if (change_to_mvolume)
	{
		bool already_done = true;
		for (chan=0; chan<16; chan++)
		{
			if (no_ctrl11[chan]>1)
			{
				already_done = false;
				break;
			}
		}
		if (already_done) return no_changes;
	}

	if (!change_to_mvolume)
	{
		bool already_done = true;
		for (chan=0; chan<16; chan++)
		{
			if (no_ctrl7[chan]>1)
			{
				already_done = false;
				break;
			}
		}
		if (already_done) return no_changes;
	}

	if (change_to_mvolume)
	{
		HP_Rewind(mf);
		int index[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if ((type == HP_MAIN_VOLUME)||(type == HP_EXPRESSION))
			{
				int new_val = (int)(volumes[chan].GetAt(index[chan])+0.5);
				HP_ReadController(mf,id, &time, &chan, &number, &value);
				if ((type==HP_EXPRESSION)||(new_val!=value))
				{
					HP_ChangeController(mf,id,HP_MAIN_VOLUME,new_val,HP_NO_PERCENT);
					no_changes++;
				}
				index[chan]++;
				continue;
			}
		}

	}
	else // change to expression
	{
		bool first_main_volume_performed[16] =
			{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};

		HP_Rewind(mf);
		int index[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (type == HP_MAIN_VOLUME)
			{
				HP_ReadController(mf,id, &time, &chan, &number, &value);
				if (!first_main_volume_performed[chan])
				{
					if ((type!=HP_MAIN_VOLUME)||((int)(max_volume[chan]+0.5)!=value))
					{
						HP_ChangeController(mf,id,HP_MAIN_VOLUME,(int)(max_volume[chan]+0.5),HP_NO_PERCENT);
						no_changes++;
					}
					first_main_volume_performed[chan] = true;
				}
				else
				{
					int new_val_expr = (int)(((volumes[chan].GetAt(index[chan])*127.)/max_volume[chan])+0.5);
					if ((type!=HP_EXPRESSION)||(new_val_expr!=value))
					{
						HP_ChangeController(mf,id,HP_EXPRESSION,new_val_expr,HP_NO_PERCENT);
						no_changes++;
					}
				}
				index[chan]++;
			}
			if (type == HP_EXPRESSION)
			{
				HP_ReadController(mf,id, &time, &chan, &number, &value);
				int new_val_expr = (int)(((volumes[chan].GetAt(index[chan])*127.)/max_volume[chan])+0.5);
				if ((type!=HP_EXPRESSION)||(new_val_expr!=value))
				{
					HP_ChangeController(mf,id,HP_EXPRESSION,new_val_expr,HP_NO_PERCENT);
					no_changes++;
				}
				index[chan]++;
			}
		}
	}

	if (no_changes > 0)
	{
		int no_double_notes;
		int no_pitch_wheels;
		eval_xg_convert(&no_double_notes, &no_pitch_wheels);
		source_changed = true;
	}

	return no_changes;
}

//**************************************************************************
//*
//*		find_key
//*		tries to find the key by the chords
//*
//**************************************************************************

CString HPMF_Interface::find_key()
{
	CString key = "** ***";

	int i;
	bool sel_list[16];
	for (i=0; i<16; i++)
	{
		sel_list[i] = false;
	}

	if (no_key_signatures > 1) return key;

	// global is_simple_chords, bad
	bool is_simple_chords_old = is_simple_chords;
	is_simple_chords = false;

	fill_chord_list(sel_list);
	CString chrd = chord->get_last_chord_text();

	is_simple_chords = is_simple_chords_old;

	int l = chrd.GetLength();
	switch (l)
	{
	case 1:
		key = chrd+"  maj";
		break;
	case 2:
		{
			if (chrd[1]=='#' || chrd[1]=='b')
			{
				key = chrd+" maj";
				break;
			}
			if (chrd[1]=='m')
			{
				key = chrd.Left(1)+"  min";
				break;
			}
			if (chrd[1]=='6')
			{
				key = chrd.Left(1)+"  maj";
				break;
			}
			break;
		}
	case 3:
		{
			if (chrd[2]=='m')
			{
				key = chrd.Left(2)+" min";
				break;
			}
			if (chrd[2]=='6')
			{
				key = chrd.Left(2)+" maj";
				break;
			}
			break;
		}
	}
	return key;
}

//**************************************************************************
//*
//*		eval_vel_compress
//*		realizes the Velocity Compress function
//*
//**************************************************************************

void HPMF_Interface::eval_vel_compress(VEL_COMPRESS_ELEM final_vel_compress_list[16])
{

	int id, chan, time, type;
	int note, vel, length;

	int vel_new;
	source_changed = false;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_NOTE)
		{
			HP_ReadNote(mf,id,&time,&chan,&note,&vel,&length);

			if (vel < final_vel_compress_list[chan].delete_upto)
			{
				HP_DeleteEvent(mf,id);
				continue;
			}
			if (chan==0)
			{
				int i = time;
			}
			int min = final_vel_compress_list[chan].min;
			int max = final_vel_compress_list[chan].max;
			int min_new = final_vel_compress_list[chan].min_new;
			int max_new = final_vel_compress_list[chan].max_new;

			if (min==max)
			{
				vel_new = min_new;
			}
			else
			{
				vel_new = (int)((float)((max_new-min_new)*(vel-min))/(float)(max - min)) + min_new;
			}

			if (vel_new != vel)
			{
				HP_ChangeVelocity(mf,id,chan,note,vel_new,HP_NO_PERCENT);
			}
		}
	}
	int no_vh_chan = find_vh_channel();
		// may be velocity set to low values
	source_changed = true;
}

//**************************************************************************
//*
//*		eval_transpose
//*		realizes the transpose funktion, HP MIDIFILE used
//*
//**************************************************************************

void HPMF_Interface::eval_transpose(int transpose_no, CString new_key, bool transpose_chords)
{
	int i;
	char nk[5];
	int id, time, chan /*, number, value, voice*/;
    unsigned char cr, ct,bn, bt;
    char *chord;
	bool is_flat;
	source_changed = false;
	bool actual_melody[16];

	for (i=0; i<new_key.GetLength(); i++)
	{
		nk[i] = new_key[i];
	}
	nk[new_key.GetLength()] = (char)0;

	is_flat = new_key!=""? GlobalUtilities::is_flat_key(nk): true;

	if (first_key=="" && new_key!="")
	{ // keysignature event has to be inserted with key = new_key.
		HP_SetFirst(mf,HP_LAST);
		HP_InsertKeySignature(mf,0,nk);
		source_changed = true;
	}

	for (chan=0; chan<16; chan++)
	{
		actual_melody[chan] = mlv_list[chan].melody;
	}

	HP_Rewind(mf);
	int type;

	bool first_key_arrived = false;

	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if (type == HP_BANK_SELECT_MSB)
		{
			// ignore LSB; I think it's OK
			int number, value;
			HP_ReadController(mf,id, &time, &chan, &number, &value);
			actual_melody[chan] = is_yamaha_melody_voice(128*value,-1);
			continue;
		}

		if ((type == HP_NOTE) && actual_melody[chan])
		{
			if (mlv_list[chan].is_mega)
			{
				transpose_mega_note(id,transpose_delta_list[chan]);
			}
			else
			{
				int value, vel, length;
				int delta = transpose_delta_list[chan];

				HP_ReadNote(mf,id,&time,&chan,&value,&vel,&length);

				if (value+delta<new_lowlimit[chan])
				{
					while (value+delta<new_lowlimit[chan]) delta+=12;
				}
				if (value+delta>new_highlimit[chan])
				{
					while (value+delta>new_highlimit[chan]) delta-=12;
				}
				HP_ChangeNote(mf,id,chan,delta,HP_RELATIVE);
			}
			continue;
		}

		if (type==HP_KEY_SIGNATURE)
		{
			char* key;
			HP_ReadKeySignature(mf,id,&time,&key);
			CString old_key = key;

			if (!first_key_arrived)
			{
				if (old_key != new_key)
				{
					HP_ChangeKeySignature(mf,id,nk); // the last time the nk with new_key used
				}
				first_key_arrived = true;
			}
			else
			{
				// transpose next key_signatures read
				CString transposed_key =
					GlobalUtilities::transpose_key_signature(old_key, transpose_no);

				for (i=0; i<transposed_key.GetLength(); i++)
				{
					nk[i] = transposed_key[i];
				}
				nk[i] = (char)0x00;
				is_flat = GlobalUtilities::is_flat_key(nk);

				HP_ChangeKeySignature(mf,id,nk);
			}
			HP_Delete(key);
			continue;
		}

		if (transpose_chords)
		{
			if (type==HP_CHORD_NAME)
			{
				HP_ReadChord(mf,id,&time,&cr,&ct,&bn,&bt,&chord);

				if (transpose_no == 0)
				{	// set correct enharmonic chords
					if (cr != 0x7f) cr = GlobalUtilities::enharmonic_cr(cr, is_flat);
					if (bn != 0x7f) bn = GlobalUtilities::enharmonic_cr(bn, is_flat);
				}
				else
				{
					// transpose cr
					if (cr != 0x7f) cr = GlobalUtilities::transpose_cr(cr, transpose_no, is_flat);
					// transpose bn
					if (bn != 0x7f) bn = GlobalUtilities::transpose_cr(bn, transpose_no, is_flat);
				}

				// same flats/sharps for cr and bn
				bn = GlobalUtilities::change_flat_sharp_bn(bn,cr);
				// with new cr, ct, bn, bt
				HP_ChangeChord(mf,id,cr,ct,bn,bt);

				HP_Delete(chord);
				continue;
			}

			if (type==HP_SYSEX)
			{
				unsigned char * data;
				int length;

				HP_ReadSysex(mf,id,&time,&data,&length);
				if (length==9)
				{
					if((data[1]==0x43)&&(data[2]==0x7e)&&(data[3]==0x02))
					{ // chord sysex
						int cr = data[4];
						int bn = data[6];

						if (transpose_no == 0)
						{	// set correct enharmonic chords
							if (cr != 0x7f) cr = GlobalUtilities::enharmonic_cr(cr, is_flat);
							if (bn != 0x7f) bn = GlobalUtilities::enharmonic_cr(bn, is_flat);
						}
						else
						{
							// transpose cr
							if (cr != 0x7f) cr = GlobalUtilities::transpose_cr(cr, transpose_no, is_flat);
							// transpose bn
							if (bn != 0x7f) bn = GlobalUtilities::transpose_cr(bn, transpose_no, is_flat);
						}

						// same flats/sharps for cr and bn
						bn = GlobalUtilities::change_flat_sharp_bn(bn,cr);
						// with new cr, bn
						data[4] = cr;
						data[6] = bn;
						HP_ChangeSysex(mf,id,data);
					}
				}
				HP_Delete(data);
				continue;
			}
		}
	}

	for (i=0; i<16; i++)
	{
		if (mlv_list[i].melody)
		{
			mute[i] = new_mute[i];
			highlimit[i] = new_highlimit[i];
			lowlimit[i] = new_lowlimit[i];
		}
	}
	first_key = new_key;
	init_hpmfiledata();
	source_changed = true;
}

//**************************************************************************
//*
//*		eval_quantize_chords
//*		realizes the quantize chords funktion
//*
//**************************************************************************

void HPMF_Interface::eval_quantize_chords(int beat_resolution)
{
	int i;
	int id, chan, time, type;
	int time_of_last_time_signature = 0;
	int takt_of_last_time_signature = 0;
	int num = 4;
	int denum = 4;
	int takt, beat, tick;
	int metronome_click,n32;
	int ticks_per_beat = ppqn;
	unsigned char cr, ct, bn, bt;
	char *chord = NULL;
	int length;

	ArrayChord *orig_chord_list = new ArrayChord;
	ElementChordList scr_elem_chord;

	// fill orig_chord_list and delete all chords in file

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		unsigned char* data = NULL;
		int is_chord = -1;	// -1: either xf-chord or sysex-chord
							//  0: xf-chord
							//  1: sysex-chord


		if (type == HP_TIME_SIGNATURE)
		{
			HP_ReadTimeSignature(mf,id,&time_of_last_time_signature,&num,&denum,&metronome_click,&n32);
			HP_GetTaktBeatTick(mf,time,&takt_of_last_time_signature,&beat,&tick);

			ticks_per_beat = (denum==4)?ppqn:
							 (denum==2)?2*ppqn:
							 (denum==8)?(ppqn)/2:ppqn;
			continue;
		}

		if (type == HP_CHORD_NAME)
		{
			is_chord = 0;
		}
		else
		{
			if (type == HP_SYSEX)
			{
				HP_ReadSysex(mf, id, &time, &data, &length);
				if (length==9)
				{
					if((data[1]==0x43)&&(data[2]==0x7e)&&(data[3]==0x02))
					{ // chord sysex
						is_chord = 1;
					}
					else
					{
						HP_Delete(data);
						data = NULL;
						continue;
					}
				}
				else
				{
					HP_Delete(data);
					data = NULL;
					continue;
				}
			}
		}

		if (is_chord >= 0) // only this possible
		{

			HP_GetTaktBeatTick(mf,time,time_of_last_time_signature,takt_of_last_time_signature,num,denum,&takt,&beat,&tick);

			if (is_chord == 0)
			{	// XF Cord-Event
				HP_ReadChord(mf,id,&time,&cr,&ct,&bn,&bt,&chord);
				HP_Delete(chord);
				chord = NULL;
				scr_elem_chord.time = time;
				scr_elem_chord.takt = takt;
				scr_elem_chord.beat = beat;
				scr_elem_chord.tick = tick;
				scr_elem_chord.ticks_per_beat = ticks_per_beat;
				scr_elem_chord.num = num;
				scr_elem_chord.cr = cr;
				scr_elem_chord.ct = ct;
				scr_elem_chord.bn = bn;
				scr_elem_chord.bt = bt;
				scr_elem_chord.is_sysex = false;
				orig_chord_list->add(&scr_elem_chord);
				HP_DeleteEvent(mf, id);
				continue;
			}
			if (is_chord == 1)
			{
				scr_elem_chord.time = time;
				scr_elem_chord.takt = takt;
				scr_elem_chord.beat = beat;
				scr_elem_chord.tick = tick;
				scr_elem_chord.num = num;
				scr_elem_chord.ticks_per_beat = ticks_per_beat;
				scr_elem_chord.is_sysex = true;
				for (i=0; i<9; i++)
				{
					scr_elem_chord.data[i] = data[i];
				}
				orig_chord_list->add(&scr_elem_chord);
				HP_Delete(data);
				data = NULL;
				HP_DeleteEvent(mf,id);
			}
		}
	}

/*
// check orig_chord_list
	CString r;
	for (i=0; i<orig_chord_list->get_length(); i++)
	{
		orig_chord_list->get(i,&scr_elem_chord);
		r.Format("Orig Chord at time %i, takt %i, beat %i, tick %i, num %i, %s sysex",
			scr_elem_chord.time, scr_elem_chord.takt,scr_elem_chord.beat,
			scr_elem_chord.tick,scr_elem_chord.num,scr_elem_chord.is_sysex?"":"no ");
		MessageBox(r);
		if (scr_elem_chord.is_sysex)
		{
			r.Format("   SysEx: cr: %x, ct: %x, bn %x, bt %x",
				scr_elem_chord.data[4],
				scr_elem_chord.data[5],
				scr_elem_chord.data[6],
				scr_elem_chord.data[7]);
			MessageBox(r);
		}
	}
*/

	// Quantize now in a new array new_chord_list
	ArrayChord *new_chord_list = new ArrayChord;


	for (i=0; i<orig_chord_list->get_length(); i++)
	{
		orig_chord_list->get(i,&scr_elem_chord);
		time = scr_elem_chord.time;
		takt = scr_elem_chord.takt;
		beat = scr_elem_chord.beat;
		tick = scr_elem_chord.tick;
		num = scr_elem_chord.num;
		ticks_per_beat = scr_elem_chord.ticks_per_beat;

		switch (beat_resolution)
		{
		case BEAT_RESOLUTION_1:  // beat 0
			{
				int time_of_last_takt, time_of_next_takt;
				HP_GetTimeFromTaktBeatTick(mf,takt,0,0,&time_of_last_takt);
				time_of_next_takt = time_of_last_takt + num*ticks_per_beat;
				if ((time-time_of_last_takt)<=(time_of_next_takt-time))
				{
					time = time_of_last_takt;
				}
				else
				{
					time = time_of_next_takt;
					takt++;
				}

				beat = 0;
				tick = 0;
				break;
			}
		case BEAT_RESOLUTION_13: // beat 0, 2, 4...
			{
				int time_of_last_even_beat, time_of_next_even_beat;
				int last_even_beat, next_even_beat;
				last_even_beat = (2*(beat/2) == beat)?beat:beat-1;
				next_even_beat = last_even_beat+2;
				if (next_even_beat>=num)
				{
					next_even_beat = last_even_beat;
				}
				HP_GetTimeFromTaktBeatTick(mf,takt,last_even_beat,0,&time_of_last_even_beat);
				time_of_next_even_beat =
					(next_even_beat==last_even_beat)?time_of_last_even_beat:time_of_last_even_beat+2*ticks_per_beat;

				if ((time-time_of_last_even_beat)<=(time_of_next_even_beat-time))
				{
					time = time_of_last_even_beat;
					beat = last_even_beat;
				}
				else
				{
					time = time_of_next_even_beat;
					beat = next_even_beat;
				}

				tick = 0;
			}

		case BEAT_RESOLUTION_ALL: // at beat-position
			{
				if (tick > ticks_per_beat/2)
				{
					beat++;
				}
				if (beat >= num)
				{
					beat = 0;
					takt++;
				}
				tick = 0;

				HP_GetTimeFromTaktBeatTick(mf,takt,beat,tick,&time);

				break;
			}
		}
		scr_elem_chord.time = time;
		scr_elem_chord.takt = takt;
		scr_elem_chord.beat = beat;
		scr_elem_chord.tick = tick;
		new_chord_list->add(&scr_elem_chord);
	}

/*
// check new_chord_list
	CString r;
	for (i=0; i<new_chord_list->get_length(); i++)
	{
		new_chord_list->get(i,&scr_elem_chord);
		r.Format("New Chord at time %i, takt %i, beat %i, tick %i, num %i, %s sysex",
			scr_elem_chord.time, scr_elem_chord.takt,scr_elem_chord.beat,
			scr_elem_chord.tick,scr_elem_chord.num,scr_elem_chord.is_sysex?"":"no ");
		MessageBox(r);
	}
*/

	// Insert the chords of different times into midifile

	int last_time = -1;
	int last_time_inserted = -1;

	HP_SetFirst(mf);
	for (i=0; i<new_chord_list->get_length(); i++)
	{
		new_chord_list->get(i,&scr_elem_chord);
		time = scr_elem_chord.time;
		if ((last_time != -1) && (time > last_time))
		{ // insert last chord_event
			last_time = time;
			new_chord_list->get(i-1,&scr_elem_chord);
			last_time_inserted = scr_elem_chord.time;
			if (scr_elem_chord.is_sysex)
			{
				HP_InsertSysEx(mf,last_time_inserted,scr_elem_chord.data);
			}
			else
			{
				HP_InsertChord(mf,last_time_inserted,
					scr_elem_chord.cr,
					scr_elem_chord.ct,
					scr_elem_chord.bn,
					scr_elem_chord.bt);
			}
		}
		else
		{
			last_time = time;
		}
	}

	// Insert last chord of file
	new_chord_list->get(new_chord_list->get_length()-1,&scr_elem_chord);
	time = scr_elem_chord.time;

	if (time > last_time_inserted)
	{
		if (scr_elem_chord.is_sysex)
		{
			HP_InsertSysEx(mf,time,scr_elem_chord.data);
		}
		else
		{
			HP_InsertChord(mf,time,
				scr_elem_chord.cr,
				scr_elem_chord.ct,
				scr_elem_chord.bn,
				scr_elem_chord.bt);
		}
	}

	delete orig_chord_list;
	delete new_chord_list;
	remove_double_chords();
	source_changed = true;
}

//**************************************************************************
//*
//*		eval_quantize_lyrics
//*		realizes the quantize lyrics function
//*
//**************************************************************************

void HPMF_Interface::eval_quantize_lyrics(int resolution)
{
	int i;

	CArray <LSCR,LSCR> scrlist;
	int no_scr = 0;
	LSCR lscr;
	LSCR lscr2;

	lscr.time = -1;
	lscr.text = "";

	int res_half = resolution/2;

	int id, chan, time, type;
	char* text;
	int new_time;

	bool note_arrived = false;

	// put all quantized lyrics into scrlist
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			note_arrived = true;
			continue;
		}

		if (type == HP_LYRIC)
		{
			if (!note_arrived)
			{
				// do not quantize lyrics before the first note
				continue;
			}

			HP_ReadLyric(mf,id,&time,&text);
			HP_DeleteEvent(mf,id);

			// quantize algorithm:

			new_time = resolution>0?(time/resolution)*resolution:time;
			if(new_time < time - res_half)
			{
				new_time += resolution;
			}

			// eliminate linefeeds from text
			bool split_lf = false;
			int len = strlen(text);
			char ch;

			if (len > 1)
			{
				ch = text[len-1];

				if ((ch=='/')||(ch==0x0d))
				{
					split_lf = true;
					text[len-1] = 0x00;
				}
			}

			lscr.time = new_time;
			lscr.text = text;
			scrlist.Add(lscr);
			no_scr++;

			if (split_lf)
			{
				text[0] = ch;
				text[1] = 0x00;
				lscr.text = text;
				scrlist.Add(lscr);
				no_scr++;
			}

			HP_Delete(text);
		}
	}

	// spread lyrics with same time to different times
	int time1;
	int time2;
	int time3;

	bool changed = true;
	while (changed) // we have to loop this action
	{
		time1 = -1;
		time2 = -2;
		time3 = -3;
		changed = false;
		for (i=0; i<=scrlist.GetUpperBound(); i++)
		{
			lscr = scrlist.GetAt(i);
			time1 = time2;
			time2 = time3;
			time3 = lscr.time;

			if ((time1==time2)&&(time3!=time1)&&(time1>0))
			{
				int new_time2 = time2 + ((time3-time2)>240?120:(time3-time2)/2);
				lscr2 = scrlist.GetAt(i-1);
				lscr2.time = new_time2;
				scrlist.SetAt(i-1,lscr2);
				time2 = new_time2;
				changed = true;
			}
		}
	}

	HP_SetFirst(mf,HP_LAST);

	// Fill quantized lyrics in file
	for (i=0; i<no_scr; i++)
	{
		lscr = scrlist.GetAt(i);
		GlobalUtilities::convert_CString_to_cstring(&text, lscr.text);
		HP_InsertLyric(mf,lscr.time,text);
		delete[] text;
	}

	update_lyriclist();
	source_changed = true;
}

//**************************************************************************
//*
//*		eval_shift_chordlyrics
//*		shift lyrics which are close by a chord at this chord.
//*		Only shift right (to higher time)
//*
//**************************************************************************

void HPMF_Interface::eval_shift_chordlyrics(int resolution)
{
	int id, chan, time, type, length;
	unsigned char *data;
	char *text;

	if (lyriclist_free==0) return;


	// fill list of times of all chords
	CArray<int,int> chordtime;
	int chordtime_free = 0;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_CHORD_NAME)
		{
			chordtime.Add(time);
			chordtime_free++;
			continue;
		}
		if (type == HP_SYSEX)
		{
			HP_ReadSysex(mf, id, &time, &data, &length);
			if (length==9)
			{
				if((data[1]==0x43)&&(data[2]==0x7e)&&(data[3]==0x02))
				{ // chord sysex
					chordtime.Add(time);
					chordtime_free++;
				}
			}
			HP_Delete(data);
			continue;
		}
	}
	if (chordtime_free == 0) return;

	// analyse lyrics

	int last_lyric_id = -1;
	int last_lf_lyric_id = -1;
	int chordtime_index = 0;
	int next_chord_time = chordtime[chordtime_index];

	HP_SetFirst(mf);

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_LYRIC)
		{
			if (time >= next_chord_time)
			{
				char * lyric_text = "";
				char * lf_text = "";
				if (last_lf_lyric_id >= 0)
				{
					HP_ReadLyric(mf,last_lf_lyric_id,&time,&lf_text);
					HP_DeleteEvent(mf,last_lf_lyric_id);
					HP_InsertLyric(mf,next_chord_time+30,lf_text);
					last_lf_lyric_id = -1;
					HP_Delete(lf_text);
					source_changed = true;
				}

				if (last_lyric_id >= 0)
				{
					HP_ReadLyric(mf,last_lyric_id,&time,&lyric_text);
					HP_DeleteEvent(mf,last_lyric_id);
					HP_InsertLyric(mf,next_chord_time,lyric_text);
					last_lyric_id = -1;
					HP_Delete(lyric_text);
					source_changed = true;
				}

				chordtime_index++;
				if (chordtime_index >= chordtime_free)
				{
					break;
				}
				next_chord_time = chordtime[chordtime_index];


				while (time > next_chord_time)
				{
					chordtime_index++;
					if (chordtime_index >= chordtime_free)
					{
						break;
					}
					next_chord_time = chordtime[chordtime_index];
				}
				if (chordtime_index >= chordtime_free)
				{
					break;
				}
			}

			if ((next_chord_time-resolution<time)&&(time<=next_chord_time))
			{

				HP_ReadLyric(mf,id,&time,&text);
				if ((strlen(text)==1)&&((text[0]=='/')||(text[0]==0x0d)))
				{
					last_lf_lyric_id = id;
				}
				else
				{
					last_lyric_id = id;
					last_lf_lyric_id = -1;
				}
			}
		}
	}
	// spread '/' and lyrics at same times
	eval_quantize_lyrics(0); // will call update_lyriclist at the end
}

//**************************************************************************
//*
//*		transpose_mega_note
//*
//**************************************************************************

void HPMF_Interface::transpose_mega_note(int id, int delta)
{
	int time, chan, note, vel, length;

    HP_ReadNote(mf,id,&time, &chan, &note,&vel,&length);

	if (note >= 96)
	{
		return; // original note in noise region, no action
	}

	int new_note = note+delta;

	while ((new_note < 24)||(new_note < new_lowlimit[chan]))
	{	// don't tranpose in region outside keyboard
		delta += 12;
		new_note = note+delta;
	}

	while ((new_note >= 96)||(new_note > new_highlimit[chan]))
	{	// don't transpose in noise region
		delta -= 12;
		new_note = note+delta;
	}

	HP_ChangeNote(mf, id, chan , delta, HP_RELATIVE);
}

//**************************************************************************
//*
//*		delete_mega_effectnotes
//*		used only if the mega/sart-channel will be revoiced to a
//*     non-mega/sart voice
//*
//**************************************************************************

void HPMF_Interface::delete_mega_effectnotes(int ch)
{
	if (!mlv_list[ch].is_mega)
	{
		return;
	}

	int id, type, time, chan, note, vel, length;

	HP_Rewind(mf);

	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if (chan != ch)
		{
			continue;
		}
		if (type == HP_NOTE)
		{
		    HP_ReadNote(mf,id,&time, &chan, &note,&vel,&length);
			if (note >= 96)
			{
				HP_DeleteEvent(mf,id);
			}
		}
	}
}


//**************************************************************************
//*
//*		fill_patchname_list
//*		fills the list patchname with short names of voices
//*
//**************************************************************************

void HPMF_Interface::fill_patchname_list()
{
	int chan;
	for (chan=0; chan<16; chan++)
	{
		patchname[chan]= "";
		if (mute[chan]) continue;

		if (mlv_list[chan].melody)
		{
			if (!(mlv_list[chan].is_mega) && !(mlv_list[chan].is_sart))
			{
				if (vh_channel[chan])
				{
					patchname[chan] = " VH ";
				}
				else
				{
					patchname[chan] = shortpatch[mlv_list[chan].voice];
				}
			}
			else
			{
				if(mlv_list[chan].is_mega)
				{
					patchname[chan] = "Mega";
				}
				if(mlv_list[chan].is_sart)
				{
					patchname[chan] = "SArt";
				}
			}
		}
		else
		{
			if (is_sfx_bank(mlv_list[chan].msb*128))
			{
				patchname[chan] = "SFX";
			}
			else
			{
				patchname[chan] = "Drum";
			}
		}
	}
}

//**************************************************************************
//*
//*		set_user1_fill_lyric_data
//*		called from CPsrutiDlg to fill the fill_lyric_data of HPMF_Interface
//*
//**************************************************************************

void HPMF_Interface::set_user1_fill_lyric_data(char *tl, char *bl, char *el, int lflt)
{
	strcpy(user1_takt_lyric,tl);
	strcpy(user1_beat_lyric,bl);
	strcpy(user1_end_lyric,el);
	user1_linefeedlyrictick = lflt;
}

//**************************************************************************
//*
//*		set_user2_fill_lyric_data
//*		called from CPsrutiDlg to fill the fill_lyric_data of HPMF_Interface
//*
//**************************************************************************

void HPMF_Interface::set_user2_fill_lyric_data(char *tl, char *bl, char *el, int lflt)
{
	strcpy(user2_takt_lyric,tl);
	strcpy(user2_beat_lyric,bl);
	strcpy(user2_end_lyric,el);
	user2_linefeedlyrictick = lflt;
}

//**************************************************************************
//*
//*		set_user3_fill_lyric_data
//*		called from CPsrutiDlg to fill the fill_lyric_data of HPMF_Interface
//*
//**************************************************************************

void HPMF_Interface::set_user3_fill_lyric_data(char *tl, char *bl, char *el, int lflt)
{
	strcpy(user3_takt_lyric,tl);
	strcpy(user3_beat_lyric,bl);
	strcpy(user3_end_lyric,el);
	user3_linefeedlyrictick = lflt;
}


//**************************************************************************
//*
//*		set_is_user
//*		called from CPsrutiDlg to set the fill lyric marker is_user
//*
//**************************************************************************

void HPMF_Interface::set_is_user(int is_usr)
{
	is_user = is_usr;
}

//**************************************************************************
//*
//*		get_user1_fill_lyric_data
//*		called from CPsrutiDlg to get the fill_lyric_data of HPMF_Interface
//*
//**************************************************************************

void HPMF_Interface::get_user1_fill_lyric_data(char *tl, char *bl, char *el, int *lflt)
{
	strcpy(tl,user1_takt_lyric);
	strcpy(bl,user1_beat_lyric);
	strcpy(el,user1_end_lyric);
	*lflt = user1_linefeedlyrictick;
}

//**************************************************************************
//*
//*		get_user2_fill_lyric_data
//*		called from CPsrutiDlg to get the fill_lyric_data of HPMF_Interface
//*
//**************************************************************************

void HPMF_Interface::get_user2_fill_lyric_data(char *tl, char *bl, char *el, int *lflt)
{
	strcpy(tl,user2_takt_lyric);
	strcpy(bl,user2_beat_lyric);
	strcpy(el,user2_end_lyric);
	*lflt = user2_linefeedlyrictick;
}

//**************************************************************************
//*
//*		get_user3_fill_lyric_data
//*		called from CPsrutiDlg to get the fill_lyric_data of HPMF_Interface
//*
//**************************************************************************

void HPMF_Interface::get_user3_fill_lyric_data(char *tl, char *bl, char *el, int *lflt)
{
	strcpy(tl,user3_takt_lyric);
	strcpy(bl,user3_beat_lyric);
	strcpy(el,user3_end_lyric);
	*lflt = user3_linefeedlyrictick;
}



//**************************************************************************
//*
//*		fill_protfile
//*		creates "protfile_name" and fills it with title, "measure:bar" and
//*		chord-names
//*		chord_protocol?       protocol as Chords
//*     chord_protocol_lyric? protocol as Lyrics
//*
//**************************************************************************

void HPMF_Interface::fill_protfile()
{
	int i;
	CStdioFile *pf_f;
	CFileException e;
	CString t;

	if (protfile == "") return;

	CFileStatus status;

	if (CFile::GetStatus( protfile,status))
	{
		CFile::Remove(protfile);
	}

	pf_f = new CStdioFile;
	if (!pf_f->Open(protfile, CFile::modeCreate | CFile::modeNoTruncate |
		CFile::modeReadWrite | CFile::shareExclusive, &e))
	{
		// Error Meldung
		return;
    }
	pf_f->SetLength(0);
	pf_f->SeekToBegin();

	t = chordlyricfile_title + "\n\n";
	pf_f->WriteString(t);

	CString pf = "File:  "+ sourcefile + "\n\n";
	pf_f->WriteString(pf);

	if (cevlist_free==0)
	{
		pf_f->WriteString("No chords generated\n");
	}
	else
	{
		pf_f->WriteString(GlobalUtilities::start_chords_lyrics+"\n");

		CString indicator = chord_protocol?chord_indicator:lyric_indicator;

		for (i=0; i<cevlist_free; i++)
		{
			int takt = cevlist[i].takt+1;
			int bar = cevlist[i].bar+1;
			CString text = cevlist[i].text;
			if (chord_protocol_lyric) text = '"'+text+' '+'"';
			t.Format("%3.3i:%2.2i:%3.3i\t%s\n", takt, bar, 0, text);

			pf_f->WriteString(indicator+"\t"+t);
		}
		pf_f->WriteString(GlobalUtilities::end_list + "\n");
	}
	pf_f->Close();
    ShellExecute(this->m_hWnd,"open",protfile,NULL,NULL,SW_SHOWNORMAL);
	return;
}

//**************************************************************************
//*
//*		pre_eval_chords
//*		fills no_list with the number of simple chords
//*
//**************************************************************************

bool HPMF_Interface::pre_eval_chords(int no_list[18], bool sel_list[16], bool is_simple, int bass_channel)
{
	int i;

	// skip chord-evaluation if chords already in source
	if (with_xfchords) return false; // don't insert chords if already in file

	is_simple_chords = is_simple;

	if (bass_channel == -1)
	{
		bass_note_list_free = 0;
	}
	else
	{
		fill_bass_note_list(bass_channel);
	}

	fill_chord_list(sel_list);

	for (i=0; i<18; i++)
	{
		no_list[i] = chord->get_no_chords(i);
	}

	is_simple_chords = false;

	return true;
}

//**************************************************************************
//*
//*		remove_chords
//*		removes all XG chord-events from source
//*
//**************************************************************************

void HPMF_Interface::remove_chords()
{
	int id, chan, time, type;
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_CHORD_NAME)
		{
			HP_DeleteEvent(mf,id);
			source_changed = true;
			continue;
		}
		if (type==HP_SYSEX)
		{
			unsigned char * data;
			int length;
			HP_ReadSysex(mf,id,&time,&data,&length);
			if (length != 9)
			{
				HP_Delete(data);
				continue;
			}

			if ((data[1]!=0x43)||(data[2]!=0x7e)||(data[3]!=0x02))
			{
				HP_Delete(data);
				continue;
			}
			HP_DeleteEvent(mf,id);
			HP_Delete(data);
			source_changed = true;
		}
	}
	with_xfchords = false;
}

//**************************************************************************
//*
//*		eval_chords
//*		realizes the chord function, HP MIDIFILE used
//*
//**************************************************************************

int HPMF_Interface::eval_chords(int chord_chan, bool sel_list[16], int bass_channel)
{
	// Test
/*
	CString r;
	r.Format("eval chords: bass_channel %i",bass_channel);
	MessageBox(r);
*/
	source_changed = false;

	selected_chord_chan = chord_chan;
	if (bass_channel == -1)
	{
		bass_note_list_free = 0;
	}
	else
	{
		fill_bass_note_list(bass_channel);
	}

	fill_chord_list(sel_list); // needed, because simple-chords may be selected


	no_chords = chord->fill_chordeventlist(selected_chord_chan,&cevlist,&cevlist_free);

	if (no_chords==0)
	{
		if (chord_chan != 16)
		{
			return -1;
		}
		else
		{
			return -2;
		}
	}


	if (chord_protocol || chord_protocol_lyric)
	{
		fill_protfile();
		chord_protocol = false;
		chord_protocol_lyric = false;
		return 0;
	}

	// insert chords in file

	Chrd::CHORD_EVENT cev;
	int cev_i; // index cevlist

	HP_SetFirst(mf,HP_LAST);
	for (cev_i = 0; cev_i < cevlist_free; cev_i++)
	{
		cev = cevlist[cev_i];
		if (is_sysex_chords)
		{
			insert_sysex_chord(cev.event_time,
				cev.event[6],cev.event[7],cev.event[8], cev.event[9]);
		}
		else
		{
			HP_InsertChord(mf,cev.event_time,
				cev.event[6],cev.event[7],cev.event[8],cev.event[9]);
		}
	}

	with_xfchords = true; // don't insert chord twice
	source_changed = true;
	bass_note_list.RemoveAll();
	bass_note_list_free = 0;
	return 0;
}

//**************************************************************************
//*
//*		sort_off_list
//*		sorts off_list by time
//*
//**************************************************************************

void HPMF_Interface::sort_off_list()
{
	int i,j;

	for (i=1; i<free_off_list; i++)
	{
		int n = off_list[i].note;
		int c = off_list[i].chan;
		int t = off_list[i].time;

		j = i-1;
		while ((j>=0) && (off_list[j].time > t))
		{
			off_list[j+1].note = off_list[j].note;
			off_list[j+1].chan = off_list[j].chan;
			off_list[j+1].time = off_list[j].time;
			j--;
		}
		off_list[j+1].note = n;
		off_list[j+1].chan = c;
		off_list[j+1].time = t;
	}

	if ((free_off_list==4)&&((off_list[0]).note==58))
	{
		i = 0;
	}
}

//**************************************************************************
//*
//*		fill_chord_list
//*		basic function for chord evaluation, HP MIDIFILE used
//*
//**************************************************************************

void HPMF_Interface::fill_chord_list(bool sel_list[16])
{
	if (chord != NULL)
	{
		delete chord;
		chord = NULL;
	}

	chord = new Chrd(mf);
	chord->lf = lf;

	int id, chan, time, type, note, vel, length;
	int takt = -1;
	int bar = -1;
	int delta_tick = -1;
	int last_takt = 0;
	int last_bar = 0;

	int last_time = 0;
	int rounded_event_time;
	int time_of_taktchange = 0; // time of last timesignature-event
	int takt_of_taktchange = 0; // takt of last Timesignature-event
	bool chord_analyzed;
	bool rounded_done;
	bool is_flat = true; // use flat chords, if no time signature
	bool first_note_arrived = false;

	int time_of_beat = ppqn;

	free_off_list = 0;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		chord_analyzed = false;
		rounded_done = false;
		if (free_off_list > 0)
		{
			get_rounded_takt_bar(time,time_of_taktchange, takt_of_taktchange, &takt,&bar,&delta_tick,&rounded_event_time);
			rounded_done = true;
			if (off_list[0].time <= rounded_event_time)
			{
				int no_offs = 0;
				int i = 0;
				while (off_list[i].time <= rounded_event_time)
				{
					no_offs++;
					i++;
					if (i >= free_off_list) break;
				}
				chord->analyze_chord(is_simple_chords, &bass_note_list, bass_note_list_free);
				chord_analyzed = true;

				for (i=0; i<no_offs; i++)
				{
					chord->remove_chord_note(off_list[i].note, off_list[i].chan, sel_list);
				}

				for (i = no_offs; i < free_off_list; i++)
				{
					off_list[i-no_offs].note = off_list[i].note;
					off_list[i-no_offs].chan = off_list[i].chan;
					off_list[i-no_offs].time = off_list[i].time;
				}
				free_off_list -= no_offs;
			}
		}

		if (type==HP_KEY_SIGNATURE)
		{
			char* key;
			HP_ReadKeySignature(mf,id,&time,&key);
			is_flat = GlobalUtilities::is_flat_key(key);
			HP_Delete(key);
			continue;
		}

		if (type==HP_TIME_SIGNATURE)
		{
			int metronome_click,n32, scr_bar, scr_tick;
			HP_ReadTimeSignature(mf,id,&time_of_taktchange,&last_num,&last_denum,&metronome_click,&n32);
			time_of_beat = (4*ppqn)/last_denum;
			HP_GetTaktBeatTick(mf,time, &takt_of_taktchange,&scr_bar, &scr_tick);
		}

		if (((bar != last_bar)||(takt != last_takt)) && first_note_arrived)
		{
			last_bar = bar;
			last_takt = takt;
/* ! */		if (!chord_analyzed && (free_off_list >= 3))
			{
				chord->analyze_chord(is_simple_chords, &bass_note_list, bass_note_list_free);

				chord_analyzed = true;
				int i = 0;
				for (i=0; i<free_off_list; i++)
				{
					chord->remove_chord_note(off_list[i].note, off_list[i].chan, sel_list);
				}
				free_off_list = 0;
/*   */
			}
		}

		if (type==HP_NOTE)
		{
			if (!rounded_done ) get_rounded_takt_bar(time,time_of_taktchange, takt_of_taktchange, &takt,&bar,&delta_tick,&rounded_event_time);
			HP_ReadNote(mf,id,&time, &chan,&note,&vel,&length);

			if (mlv_list[chan].is_mega && (note>=96))
			{	// only melody notes in mega voice
				continue;
			}

			first_note_arrived =true;

			// correcture of length needed, if rounded note gets over next bar
			int bar_time = last_denum==1?
							ppqn*4:last_denum==2?
							ppqn*2:last_denum==4?
							ppqn:last_denum==8?ppqn/2:ppqn;
			if ((rounded_event_time-time>0)&&
				(length>bar_time)&&
				(length<bar_time+rounded_event_time-time))
			{
				int tkt,br,d_tick,r_event_time;
				get_rounded_takt_bar(time+length,time_of_taktchange, takt_of_taktchange, &tkt,&br,&d_tick,&r_event_time);
				if (bar != br)
				{
					length = length - (rounded_event_time -time);
				}
			}

			// fill note_off_list with note, channel and off_event_time
			off_list[free_off_list].note = note;
			off_list[free_off_list].chan = chan;
			if (length > time_of_beat/4)
			{
				off_list[free_off_list].time = ((rounded_event_time + length)/(time_of_beat/4))*(time_of_beat/4);
			}
			else
			{
				off_list[free_off_list].time = rounded_event_time + length;
			}

			free_off_list++;
			if (free_off_list >= OFF_LIST_LENGTH)
			{
				free_off_list--; // overwrite last off
			}
			sort_off_list();

			chord->add_chord_note(
				note,chan,is_flat, takt,bar,delta_tick,rounded_event_time,!mlv_list[chan].melody, sel_list);
/*
	CString r;
	r.Format("call add_chord_note: note %i, chan %i, takt %i, bar %i, delta_tick %i, time %i, off_time %i",
	note, chan, takt, bar, delta_tick, rounded_event_time, rounded_event_time+length);
	::MessageBox(AfxGetMainWnd()->m_hWnd,r,"Test",MB_OK|MB_TASKMODAL);
*/

		}
	}

	// May be there is a chord left at the end
	last_bar = bar;
	last_takt = takt;
	chord->analyze_chord(is_simple_chords, &bass_note_list, bass_note_list_free);

/* ! */
	chord_analyzed = true;
	int i;
	for (i=0; i<free_off_list; i++)
	{
		chord->remove_chord_note(off_list[i].note, off_list[i].chan, sel_list);
	}
	free_off_list = 0;
/*   */
}


//**************************************************************************
//*
//*		fill_bass_note_list
//*		local
//*
//**************************************************************************

void HPMF_Interface::fill_bass_note_list(int bass_channel)
{
	bass_note_list.RemoveAll();
	bass_note_list_free = 0;
	int id, chan, time, type, note, vel, length;
	int takt = -1;
	int bar = -1;
	int delta_tick = -1;
	int time_of_beat = ppqn;
	int rounded_event_time;
	int time_of_taktchange = 0; // time of last timesignature-event
	int takt_of_taktchange = 0; // takt of last Timesignature-event

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		get_rounded_takt_bar(time,time_of_taktchange, takt_of_taktchange, &takt,&bar,&delta_tick,&rounded_event_time);
		if (type==HP_TIME_SIGNATURE)
		{
			int metronome_click,n32, scr_bar, scr_tick;
			HP_ReadTimeSignature(mf,id,&time_of_taktchange,&last_num,&last_denum,&metronome_click,&n32);
			HP_GetTaktBeatTick(mf,time, &takt_of_taktchange,&scr_bar, &scr_tick);
			time_of_beat = (4*ppqn)/last_denum;
		}

		if (type==HP_NOTE)
		{
			HP_ReadNote(mf,id,&time, &chan,&note,&vel,&length);
			if (chan != bass_channel) continue;

			if (mlv_list[chan].is_mega && (note>=96))
			{	// only melody notes in mega voice
				continue;
			}

			if ((time-rounded_event_time > time_of_beat/8)||(rounded_event_time-time > time_of_beat/8))
			{
				continue;
			}

			if (bass_note_list_free > 0)
			{
				if(bass_note_list[bass_note_list_free-1].event_time == rounded_event_time) continue;
			}
			Chrd::BASS_NOTE_ELEM bass_note_elem;
			bass_note_elem.bn = GlobalUtilities::find_bn(note);
			bass_note_elem.event_time = rounded_event_time;
			bass_note_list.SetAtGrow(bass_note_list_free,bass_note_elem);
			bass_note_list_free++;
		}
	}
/*
	CString r;
	int i;
	for (i=0; i<bass_note_list_free;i++)
	{
		r.Format("bass_note_list[%i]: bn %2.2x, event_time %i",
			i,
			bass_note_list[i].bn,
			bass_note_list[i].event_time);
		MessageBox(r);
	}
*/
}

//**************************************************************************
//*
//*		insert_sysex_chord
//*		local
//*
//**************************************************************************

void HPMF_Interface::insert_sysex_chord(int time, int cr, int ct, int bn, int bt)
{
	unsigned char chord_sysex[] = {0xf0,0x43, 0x7e, 0x02, cr, ct, bn, bt, 0xf7};
	HP_SetFirst(mf);
	HP_InsertSysEx(mf, time, chord_sysex);
}

//**************************************************************************
//*
//*		eval_chords_lyrics_from_file
//*
//**************************************************************************

bool HPMF_Interface::eval_chords_lyrics_from_file(CString chord_lyricfile,
			 bool is_chords, bool is_lyrics, bool is_chord_sysex)
{
	int i;
	int line_number = 0; // counts from 1 to last chord or lyric
	int time;
	int time_of_chord = -1;
	int last_time_of_chord = -1;
	int time_of_lyric = -1;
	int last_time_of_lyric = -1;
	TAKT_BAR_TIME_ELEM tbte;

	CStdioFile *cf_f;
	CFileException e;
	CString line;
	CString r;
	bool lyrics_inserted = false;
	bool chords_inserted = false;

	source_changed = false;


	if (chord_lyricfile == "")
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_CHORDLYRICFILE),NULL,MB_OK|MB_TASKMODAL);
		return false; // file does not exist
	}

	CFileStatus status;

	if (!CFile::GetStatus(chord_lyricfile,status))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_CHORDLYRICFILE),NULL,MB_OK|MB_TASKMODAL);
		return false; // file does not exist
	}

	cf_f = new CStdioFile;
	if (!cf_f->Open(chord_lyricfile, CFile::shareExclusive | CFile::modeRead | CFile::typeText, &e))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_CHORDLYRICFILE),NULL,MB_OK|MB_TASKMODAL);
		return false; // file does not exist
    }

	while (true)
	{
		if (!cf_f->ReadString(line))
		{
			cf_f->Close();
			CString r = GlobalUtilities::get_resource_string(IDS_NO_START_CHORDS_LYRICS);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			if (cf_f != NULL)
			{
				delete cf_f;
				cf_f = NULL;
			}
			return false;
		}
		line_number ++;

		line.TrimRight();
		if (line == GlobalUtilities::start_chords_lyrics) break;
	}

	if (chord != NULL)
	{
		delete chord;
		chord = NULL;
	}

	chord = new Chrd(mf);
	chord->lf = lf;
	int old_takt = -1;
	int old_bar  = -1;
	int old_tick = -1;
	int act_is_lyric;
	int act_is_chord;

	HP_SetFirst(mf,HP_LAST);

	while (cf_f->ReadString(line))
	{
		line_number++;

		line.TrimRight();
		if (line == GlobalUtilities::end_list) break;
		int takt = -1;
		int bar = 0;
		int tick = 0;
		char ch;
		int line_idx = 0;
		int len = line.GetLength();
		act_is_lyric = false;
		act_is_chord = false;

		// find out Chord- or Lyric-Line

		CString indicator = line.Left(chord_indicator.GetLength());

		if (indicator==chord_indicator)
		{
			if (!is_chords) continue;
			act_is_chord = true;

		}

		if (indicator==lyric_indicator)
		{
			if (!is_lyrics) continue;
			act_is_lyric = true;
		}

		if (!act_is_chord && !act_is_lyric) continue;

		line_idx += chord_indicator.GetLength();

		// Find takt, bar, tick

		for (i=line_idx; i<len; i++)
		{
			ch = line[i];
			if ((ch >= (int)'0') && (ch <= (int)'9'))
			{
				break;
			}
		}
		line_idx = i+1;

		takt = (ch - '0');
		if (takt < 0)
		{
			r = GlobalUtilities::get_resource_string(IDS_CHORDLYRICFILE);
			r.Format ("(%i) "+line+"\n"+r,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			continue;
		}

		for (i=line_idx; i<len;i++)
		{
			ch = line[i];
			if ((ch<(int)'0')||(ch>(int)'9'))
			{
				break;
			}
			takt = 10*takt+(ch - '0');
		}

		takt -= 1;
		line_idx = i+1;
		if (line_idx >= len)
		{
			r = GlobalUtilities::get_resource_string(IDS_CHORDLYRICFILE);
			r.Format ("(%i) "+line+"\n"+r,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			continue;
		}

		if (ch==':')
		{
			for (i=line_idx; true; i++)
			{
				ch = line[i];
				if ((ch < (int)'0') || (ch > (int)'9')) break;
				bar = 10*bar + (ch - '0');
			}
			if (bar <= 0) continue; // Error
			bar -= 1;
			line_idx = i+1;
			if (line_idx >= len)
			{
				r = GlobalUtilities::get_resource_string(IDS_CHORDLYRICFILE);
				r.Format ("(%i) "+line+"\n"+r,line_number);
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
				continue;
			}

			if (ch==':')
			{
				for (i=line_idx; true; i++)
				{
					ch = line[i];
					if ((ch < (int)'0') || (ch > (int)'9')) break;
					tick = 10*tick + (ch - '0');
				}
				line_idx = i+1;
				if (line_idx >= len)
				{
					r = GlobalUtilities::get_resource_string(IDS_CHORDLYRICFILE);
					r.Format ("(%i) "+line+"\n"+r,line_number);
					::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
					continue;
				}
			}
		}


		if (act_is_lyric)
		{
			// analyze lyric_lines

			char* scr_lyric;
			scr_lyric = new char[len-line_idx+1];
			char *lyric;
			lyric = new char[len-line_idx+1];
			int k;
			int l = 0;

			for (i=line_idx; i<len; i++)
			{
				ch = line[i];
				if (ch == '"') break;
			}
			int first_apostrophe_index = i;

			for (i=len-1; i>=line_idx; i--)
			{
				ch = line[i];
				if (ch == '"') break;
			}
			int last_apostrophe_index = i;

			if ((first_apostrophe_index >= len) || (first_apostrophe_index == last_apostrophe_index))
			{   // Error no start with "
				r = GlobalUtilities::get_resource_string(IDS_CHORDLYRICFILE);
				r.Format ("(%i) "+line+"\n"+r,line_number);
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
				delete[] scr_lyric;
				delete[] lyric;
				continue;
			}

			for (k = first_apostrophe_index; k < len; k++)
			{
				scr_lyric[l] = line[k];
				l++;
			}
			scr_lyric[l] = 0;
			for (k=l-1; k>0; k--)
			{
				if (scr_lyric[k]=='"') break;
				scr_lyric[k]=0;
			}

			if (scr_lyric[k]!='"')
			{   // Error no end with "
				r = GlobalUtilities::get_resource_string(IDS_CHORDLYRICFILE);
				r.Format ("(%i) "+line+"\n"+r,line_number);
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
				delete[] lyric;
				delete[] scr_lyric;
				continue;
			}


			k = 0;
			for (i= 1; i<(int)strlen(scr_lyric)-1; i++)
			{
				ch = scr_lyric[i];
				if ((ch != ' ')&&(ch != '-')&&(!GlobalUtilities::is_printable(ch))) continue;

				if (ch=='/')
				{
					ch = linefeed_char;
				}

				if (ch=='<')
				{
					ch = (char)0x0a; // Newpage
				}

				lyric[k] = ch;
				k++;
			}

			lyric[k] = (char)0;
			HP_GetTimeFromTaktBeatTick(mf,takt,bar,tick,&time);
			HP_InsertLyric(mf,time,lyric);
			lyrics_inserted = true;
			delete[] scr_lyric;
			delete[] lyric;
		}

		if (act_is_chord)
		{
/*
			if (tick != 0)
			{
				r = GlobalUtilities::get_resource_string(IDS_CHORD_TICKNUMBER);
				r.Format ("(%i) "+line+"\n"+r,line_number);
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,"Test",MB_OK|MB_TASKMODAL);
				if (cf_f != NULL)
				{
					delete cf_f;
					cf_f = NULL;
				}
				return false;
			}
*/
			// analyze chord-lines
			// line_idx points to first char of chord
			// dont'allow two equal takt/bar one after another

			if ((takt == old_takt) && (bar == old_bar) && (tick == old_tick))
			{
				r = GlobalUtilities::get_resource_string(IDS_CHORDLYRICFILE);
				r.Format ("(%i) "+line+"\n"+r,line_number);
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
				continue;
			}

			old_takt = takt;
			old_bar = bar;
			old_tick = tick;

			// find time of chord
			for (i=0; i<takt_bar_time_list_free; i++)
			{
				tbte = takt_bar_time_list[i];
				if ((tbte.takt == takt) && (tbte.bar == bar))
				{
					time_of_chord = tbte.time + tick;
					break;
				}
			}

			if (time_of_chord == last_time_of_chord)
			{
				continue;
			}
			else
			{
				last_time_of_chord = time_of_chord;
			}

			// get chordname
			CString chord_text;
			for (i=line_idx; i<len; i++)
			{
				char ch = line[i];
				if (((ch >= 'A') && (ch <= 'G')) || ((ch >= 'a') && (ch <= 'g')))
				{
					chord_text = line.Right(line.GetLength()-i);
					break;
				}
			}

			if (!chord->analyze_from_line(takt, bar, tick, time_of_chord, chord_text))
			{
				cf_f->Close();
				CString r = GlobalUtilities::get_resource_string(IDS_CHORDLYRICFILE);
				r.Format ("(%i) "+line+"\n"+r,line_number);
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
				if (cf_f != NULL)
				{
					delete cf_f;
					cf_f = NULL;
				}
				return false;
			}
		}
	}

	line.TrimRight();
	if (line != GlobalUtilities::end_list)
	{
		cf_f->Close();
		CString r = GlobalUtilities::get_resource_string(IDS_NO_END_LIST);
		::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
		if (cf_f != NULL)
		{
			delete cf_f;
			cf_f = NULL;
		}
		return false;
	}

	if (is_chords)
	{
		// fill cevlist with chords from chan 0

		if (chord->fill_chordeventlist(0,&cevlist,&cevlist_free)==0)
		{	// no chords in file
			chords_inserted = false;
		}
		else
		{
			chords_inserted = true;
		}

		if (chords_inserted)
		{
			// insert chords in file

			Chrd::CHORD_EVENT cev;
			int cev_i; // index cevlist

			HP_SetFirst(mf,HP_LAST);
			for (cev_i = 0; cev_i < cevlist_free; cev_i++)
			{
				cev = cevlist[cev_i];

				if (is_chord_sysex)
				{
					insert_sysex_chord(cev.event_time,
						cev.event[6],cev.event[7],cev.event[8],cev.event[9]);
				}
				else
				{
					HP_InsertChord(mf,cev.event_time,
						cev.event[6],cev.event[7],cev.event[8],cev.event[9]);
				}
			}
		}
	}

	if (chords_inserted)
	{
		with_xfchords = true;
	}

	source_changed = lyrics_inserted || chords_inserted;


	if (cf_f != NULL)
	{
		delete cf_f;
		cf_f = NULL;
	}

	update_lyriclist();
	return true;
}

//**************************************************************************
//*
//*		eval_chords_lyrics_export
//*
//**************************************************************************

bool HPMF_Interface::eval_chords_lyrics_export(CString chord_lyricfile,
			 bool is_chords, bool is_lyrics, bool is_remove_after, bool is_export,
			 bool is_export_as_lyrics)
{
	// initialize chord_lyricfile

	CStdioFile *pf_f = NULL;
	CFileException e;
	CString t;

	source_changed = false;

	if (is_export && chord_lyricfile=="") return false;
	if (!is_export && !is_remove_after) return false;
	if (is_remove_after && !is_export &&chord_lyricfile!="") return false;

	if (!is_export && is_remove_after)
	{
		if (IDYES != AfxMessageBox(GlobalUtilities::get_resource_string(IDS_REMOVE_WITHOUT_EXPORT),MB_YESNO,0))
		{
			return false;
		}
	}


	if (is_export)
	{
		CFileStatus status;

		if (CFile::GetStatus(chord_lyricfile,status))
		{
			CFile::Remove(chord_lyricfile);
		}

		pf_f = new CStdioFile;
		if (!pf_f->Open(chord_lyricfile, CFile::modeCreate | CFile::modeNoTruncate |
			CFile::modeReadWrite | CFile::shareExclusive, &e))
		{
			return false;
		}

		pf_f->SetLength(0);
		pf_f->SeekToBegin();

		t = chordlyricfile_title + "\n";

		CString pf = "File:  "+ sourcefile + "\n\n";

		pf_f->WriteString(t);
		pf_f->WriteString(pf);
		pf_f->WriteString(GlobalUtilities::start_chords_lyrics+"\n");
	}

	// loop eventlist
	int id, type, chan, time;

	int i;
	int time_of_last_time_signature = 0;
	int takt_of_last_time_signature = 0;
	int takt, beat, tick;
	int num = 4;
	int denum = 4;
	int metronome_click,n32;
	char *text;
	CString line;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_TIME_SIGNATURE)
		{
			int scr_bar, scr_tick;
			HP_GetTaktBeatTick(mf,time, &takt_of_last_time_signature,&scr_bar, &scr_tick);
			HP_ReadTimeSignature(mf,id,&time_of_last_time_signature,&num,&denum,&metronome_click,&n32);
			continue;
		}

		if (type==HP_CHORD_NAME)
		{
			if (!is_chords) continue;

			if (is_export)
			{
				CString indicator = is_export_as_lyrics?lyric_indicator:chord_indicator;
				unsigned char cr, ct, bn, bt;
				char *chord;

				HP_ReadChord(mf,id,&time,&cr,&ct,&bn,&bt,&chord);
				HP_GetTaktBeatTick(mf,time,time_of_last_time_signature,takt_of_last_time_signature,num,denum,&takt,&beat,&tick);

				CString text =  chord;
				if (is_export_as_lyrics)
				{
					text = '"'+text+' '+'"';
				}
				t.Format("%3.3i:%2.2i:%3.3i\t%s\n", takt+1, beat+1, tick, text);
				pf_f->WriteString(indicator+"\t"+t);
				HP_Delete(chord);
			}
			if (is_remove_after)
			{
				HP_DeleteEvent(mf,id);
				source_changed = true;
			}
			continue;
		}

		if (type==HP_SYSEX)
		{
			if (!is_chords) continue;

			unsigned char * data;
			int length;
			HP_ReadSysex(mf,id,&time,&data,&length);
			if (length != 9)
			{
				HP_Delete(data);
				continue;
			}

			if ((data[1]!=0x43)||(data[2]!=0x7e)||(data[3]!=0x02))
			{
				HP_Delete(data);
				continue;
			}

			if (is_export)
			{
				unsigned char cr = data[4];
				unsigned char ct = data[5];
				unsigned char bn = data[6];
				unsigned char bt = data[7];

				char *chord;
				HP_ConvertChordToText(cr,ct,bn,bt,&chord);
				HP_GetTaktBeatTick(mf,time,time_of_last_time_signature,takt_of_last_time_signature,num,denum,&takt,&beat,&tick);
				CString text =  chord;
				t.Format("%3.3i:%2.2i:%3.3i\t%s\n", takt+1, beat+1, tick, text);

				pf_f->WriteString(chord_indicator+"\t"+t);
				HP_Delete(data);
				HP_Delete(chord);
			}

			if (is_remove_after)
			{
				HP_DeleteEvent(mf,id);
				source_changed = true;
			}
		}

		if (type == HP_LYRIC)
		{
			if (!is_lyrics) continue;

			if (is_export)
			{
				char ch;

				CString good_text = "";
				HP_ReadLyric(mf,id,&time,&text);

				for (i=0; i<(int)(strlen(text)); i++)
				{
					ch = text[i];
					if (ch == (char)0x0d) ch = '/';
					if (ch == (char)0x0a) ch = '<';
					if ((ch != ' ')&&(ch != '-')&&(!GlobalUtilities::is_printable(ch))) continue;
					good_text += ch;
				}
				good_text = '"'+good_text+'"';

				HP_GetTaktBeatTick(mf,time,time_of_last_time_signature,takt_of_last_time_signature,num,denum,&takt,&beat,&tick);

				line.Format("%3.3i:%2.2i:%3.3i\t%s\n",takt+1, beat+1,tick,good_text);
				pf_f->WriteString(lyric_indicator+"\t"+line);
				HP_Delete(text);
			}
			if (is_remove_after)
			{
				HP_DeleteEvent(mf,id);
				source_changed = true;
			}
		}
	}
	if (is_export)
	{
		pf_f->WriteString(GlobalUtilities::end_list + "\n");
		pf_f->Close();
	}

	if (is_remove_after)
	{
		if (is_chords)
		{
			with_xfchords = false;
		}
		if (is_lyrics)
		{
			update_lyriclist();
		}
	}

	if (is_export)
	{
		ShellExecute(this->m_hWnd,"open",chord_lyricfile,NULL,NULL,SW_SHOWNORMAL);
	}
	return true;
}

//**************************************************************************
//*
//*		update_lyriclist
//*
//**************************************************************************

void HPMF_Interface::update_lyriclist()
{
	int id, chan, type, time;

	lyriclist.RemoveAll();
	lyriclist_free = 0;

	int takt_of_taktchange = 0;
	int time_of_taktchange = 0;

	// Following needed to concat lyrics at same time-stamps
	CArray <LSCR,LSCR> concat_scrlist;
	int no_scr = 0;
	LSCR lscr;
	lscr.time = -1;
	lscr.text = "";
	bool was_same_time = false;

	int time_of_last_lyric = -1;
	CString text_of_last_lyric = "";

	// fill concat_scrlist with concatenated texts of same time-stamps
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type != HP_LYRIC) continue;

		if (time != time_of_last_lyric)
		{
			if (was_same_time)
			{
				int i;
				CString text;
				// exchange 0d0a by 0d and 0a by 0d
				for (i=0; i<(lscr.text).GetLength(); i++)
				{
					if (((lscr.text).GetAt(i)==0x0a)&&
						(i>0)&&
						((lscr.text).GetAt(i-1)==0x0d))
					{
						continue;
					}
					if ((lscr.text).GetAt(i)==0x0a)
					{
						text += 0x0a;
					}
					else
					{
						text += (lscr.text).GetAt(i);
					}
				}
				lscr.text = text;

				concat_scrlist.Add(lscr);
				no_scr++;
				lscr.text = "";
				was_same_time = false;
			}
		}

		if (type == HP_LYRIC)
		{
			char* text;

			HP_ReadLyric(mf,id,&time,&text);

			if (time == time_of_last_lyric)
			{
				if (was_same_time)
				{
					lscr.text += text;
				}
				else
				{
					lscr.time = time;
					lscr.text = text_of_last_lyric + text;
					was_same_time = true;
				}
			}
			else
			{
				text_of_last_lyric = text;
				time_of_last_lyric = time;
			}
		}
	}

	// look at last lyrics
	if (was_same_time)
	{
		int i;
		CString text;
		// exchange 0d0a by 0d and 0a by 0d
		for (i=0; i<(lscr.text).GetLength(); i++)
		{
			if (((lscr.text).GetAt(i)==0x0a)&&
				(i>0)&&
				((lscr.text).GetAt(i-1)==0x0d))
			{
				continue;
			}
			if ((lscr.text).GetAt(i)==0x0a)
			{
				text += 0x0a;
			}
			else
			{
				text += (lscr.text).GetAt(i);
			}
		}
		lscr.text = text;
		concat_scrlist.Add(lscr);
		no_scr++;
		lscr.text = "";
		was_same_time = false;
	}

	// delete all lyrics with double times
	if (no_scr > 0)
	{
		// init concat_scrlist variables
		int act_scr_index = 0;
		lscr.time = concat_scrlist[act_scr_index].time;

		HP_Rewind(mf);
		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (time > lscr.time)
			{
				act_scr_index++ ;
				if (act_scr_index < no_scr)
				{
					lscr.time = concat_scrlist[act_scr_index].time;
				}
				else
				{
					break;
				}
			}

			if (type == HP_LYRIC)
			{
				// delete all lyrics with same times
				if (no_scr > 0)
				{
					if (time==lscr.time)
					{
						HP_DeleteEvent(mf,id);
					}
				}
			}
		}

		// insert concatenated lyrics

		HP_SetFirst(mf);
		for (act_scr_index=0; act_scr_index < no_scr;act_scr_index++)
		{
			int time = concat_scrlist[act_scr_index].time;
			CString c_text = concat_scrlist[act_scr_index].text;
			char *text;
			GlobalUtilities::convert_CString_to_cstring(&text,c_text);
			if (time>0)
			{
				HP_InsertLyric(mf,time,text);
			}
			else
			{	// lyrics at time 0 are displayed as copyright
				HP_InsertCopyright(mf,time,text);
				with_copyright = true;
				copyrightname = text;
			}
			delete[] text;
		}
	}

	// Remove non printable characters and lyrics with empty strings

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		int i,k,len;
		char* old_text = NULL;
		char* new_text = NULL;
		char ch;
		HP_SetFirst(mf);

		if (type == HP_LYRIC)
		{
			HP_ReadLyric(mf,id,&time,&old_text);
			len = (int)strlen(old_text);

			if (len==0)
			{
				HP_DeleteEvent(mf,id);
				HP_Delete(old_text);
				continue;
			}

			new_text = new char[len+1];
			bool ok = true;

			k = 0;
			for (i=0; i<len; i++)
			{
				ch = old_text[i];
				if ((i>0)&&(ch==0x0a)&&(len>1))
				{
					ok = false; // no newpage in lyric text
					continue;
				}
				if ((ch != 0x0d)&&(ch != '/')&&(ch != 0x0a) && !GlobalUtilities::is_printable(ch))
				{
					if((i>0)&&(ch==0x0a))
					ok = false; // skip nonprintable chars
					continue;
				}

				new_text[k] = old_text[i];
				k++;
			}
			new_text[k] = 0x00;

			if (ok)
			{
				HP_DeleteEvent(mf,id);
				if (new_text[0]!=0)
				{
					HP_InsertLyric(mf,time,new_text);
				}
			}

			HP_Delete(old_text);
			delete[] new_text;
		}
	}

	// split starting linefeeds from lyrics
	time_of_last_lyric = -1;
	HP_Rewind(mf);
	HP_SetFirst(mf);

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		int i,len;
		char* old_text = NULL;
		char* new_text = NULL;

		char lf_str[2];
		lf_str[1]= 0x00;


		if (type == HP_LYRIC)
		{
			HP_ReadLyric(mf,id,&time,&old_text);
			len = (int)strlen(old_text);

			if (((old_text[0]=='/')||(old_text[0]==0x0d)||(old_text[0]==0x0a))&&(len>1))
			{
				lf_str[0] = old_text[0];

				new_text = new char[len+1];
				strcpy(new_text,"/H");

				// new_text without starting linefeed
				for (i=1; i<len+1; i++)
				{
					new_text[i-1] = old_text[i];
				}

				if (time_of_last_lyric==-1)
				{
					// first lyric: delete linefeed only
					HP_DeleteEvent(mf,id);
					HP_InsertLyric(mf,time,new_text);
				}
				else
				{
					int delta_time = time-time_of_last_lyric;
// old				int lf_time = delta_time>60?time-30:time_of_last_lyric+delta_time/2;
					int lf_time = delta_time>120?time-60:time_of_last_lyric+delta_time/2;
					if ((lf_time!=time)&&(lf_time!=time_of_last_lyric))
					{
						HP_DeleteEvent(mf,id);
						HP_InsertLyric(mf,time,new_text);
						HP_InsertLyric(mf,lf_time,lf_str);
					}
				}

				if (new_text != NULL)
				{
					delete[] new_text;
					new_text = NULL;
				}
			}

			time_of_last_lyric = time;
			if (old_text != NULL)
			{
				HP_Delete(old_text);
				old_text = NULL;
			}
		}
	}

	// Insert ending blank at last lyric before linefeeds if needed and delete long lyrics (>128)

	int last_text_id = -1;
	char last_text[256];
	char first_ch;
	char last_ch;
	char last_ch_last_text;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_LYRIC)
		{
			char *text;
			HP_ReadLyric(mf,id,&time,&text);
			if (strlen(text)>128)
			{
				HP_DeleteEvent(mf,id);
				HP_Delete(text);
				continue;
			}
			first_ch = text[0];
			last_ch = text[strlen(text)-1];

			if ((first_ch != 0x0d) && (first_ch != 0x0a) && (first_ch != '/'))
			{
				last_text_id = id;
				strcpy(last_text,text);
				last_ch_last_text = last_ch;
				HP_Delete(text);
				continue;
			}
			if ((first_ch == 0x0d) || (first_ch == 0x0a) || (first_ch == '/'))
			{
				if (last_text_id != -1)
				{
					if (last_ch_last_text != ' ')
					{
						strcat(last_text," ");
						HP_ChangeLyric(mf,last_text_id,last_text);
						last_text_id = -1;
						last_text[0] = (char) 0;
					}
				}
			}
			HP_Delete(text);
		}
    }

	// fill lyriclist
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{

		if (type == HP_TIME_SIGNATURE)
		{
			int metronome_click,n32, scr_bar, scr_tick;
			HP_GetTaktBeatTick(mf,time, &takt_of_taktchange,&scr_bar, &scr_tick);
			HP_ReadTimeSignature(mf,id,&time_of_taktchange,&last_num,&last_denum,&metronome_click,&n32);
			continue;
		}

		if (type == HP_LYRIC)
		{
			char *text;
			HP_ReadLyric(mf,id,&time,&text);

			LYRICLIST_ELEM lem;

			HP_GetTaktBeatTick(mf,
				time,
				time_of_taktchange,
				takt_of_taktchange,
				last_num,
				last_denum,
				&lem.takt,
				&lem.bar,
				&lem.delta_tick);

			lem.time = time;
			lem.text = text;
			lem.num = last_num;

			HP_Delete(text);
			lyriclist.SetAtGrow(lyriclist_free,lem);


/* Test
CString r;
r.Format("Lyr \"%s\" time %i, takt %i, bar %i, delta_tick %i num %i",
			 lem.text,lem.time, lem.takt, lem.bar, lem.delta_tick, lem.num);
::MessageBox(AfxGetMainWnd()->m_hWnd,r,"Test",MB_OK|MB_TASKMODAL);
*/

			lyriclist_free++;
		}
	}

	with_lyrics = (lyriclist_free > 0);
}

//**************************************************************************
//*
//*		update_mlv_list
//*		updates the list of voices
//*
//**************************************************************************

void HPMF_Interface::update_mlv_list()
{
	int id, chan, type, time;
	int number, value;
	int voice;

	int tofnote[16]; // time of first note

	for (chan=0; chan<16; chan++)
	{
		tofnote[chan] = -1;
		mlv_list[chan].msb = -1;
		mlv_list[chan].time_msb = -1;
		mlv_list[chan].lsb = -1;
		mlv_list[chan].time_lsb = -1;
		mlv_list[chan].voice = -1;
		mlv_list[chan].time_voice = -1;
		mlv_list[chan].melody = chan==9?false:true; // init. GM
		mlv_list[chan].is_mega = false;
		mlv_list[chan].is_sart = false;
		mlv_list[chan].bankname = "";
		mlv_list[chan].voicename = "";
	}
/*
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_NOTE)
		{
			if (tofnote[chan]==-1)
			{
				tofnote[chan] = time;
			}
			continue;
		}
	}

	int max_tofnote = -1;
	for (chan=0; chan<16; chan++)
	{
		if (tofnote[chan]>max_tofnote)
		{
			max_tofnote = tofnote[chan];
		}
	}

	for (chan=0; chan<16; chan++)
	{
		if (tofnote[chan]==-1)
		{
			tofnote[chan]= max_tofnote;
		}
	}
*/

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
//
		if (type==HP_NOTE)
		{
			if (tofnote[chan]==-1)
			{
				tofnote[chan] = time;
			}
			continue;
		}
//

		if ((type==HP_BANK_SELECT_MSB) && (tofnote[chan]==-1))
		{
			HP_ReadController(mf,id,&time,&chan,&number,&value);
			if ((chan==9) && !with_xg_on && (value!=62) && (value!=127) && (value!=118) && (value!=120) && !alien_voice)
			{
				HP_DeleteEvent(mf,id);
				continue;
			}

			mlv_list[chan].msb = value;
			mlv_list[chan].time_msb = time;
			continue;
		}

		if ((type==HP_BANK_SELECT_LSB) && (tofnote[chan]==-1))
		{
			HP_ReadController(mf,id,&time,&chan,&number,&value);
			if ((chan==9) && !with_xg_on && (value!=0) && !alien_voice)
			{
				HP_DeleteEvent(mf,id);
				continue;
			}
			mlv_list[chan].lsb = value;
			mlv_list[chan].time_lsb = time;
			continue;
		}

		if ((type==HP_PROGRAM_CHANGE)&& (tofnote[chan]==-1))
		{
			HP_ReadProgramChange(mf,id,&time,&chan,&voice);
			mlv_list[chan].voice = voice;
			mlv_list[chan].time_voice = time;

			if (mlv_list[chan].msb==-1) mlv_list[chan].msb = chan==9?127:0;
			if (mlv_list[chan].lsb==-1) mlv_list[chan].lsb = 0;

			mlv_list[chan].is_mega = is_mega_voice(mlv_list[chan].msb,mlv_list[chan].lsb);
			mlv_list[chan].is_sart = is_sart_voice(mlv_list[chan].msb,mlv_list[chan].lsb);
			continue;
		}
	}

/* Test
	CString r;
	r.Format("update_mlv_list chan 10: MSB %i, LSB %i, Voice %i",mlv_list[9].msb,mlv_list[9].lsb,mlv_list[9].voice);
	MessageBox(r);
// r.Format("update_mlv_list chan 2: MSB %i, LSB %i, Voice %i",mlv_list[1].msb,mlv_list[1].lsb,mlv_list[1].voice);
//	MessageBox(r);
*/

	// set default voices and mlv_list[i].melody
	for (chan=0; chan<16; chan++)
	{
		if (mlv_list[chan].voice == -1)
		{
			mlv_list[chan].msb = (chan==9)?127:0;
			mlv_list[chan].lsb = 0;
			mlv_list[chan].voice = 0;
		}
		if (mlv_list[chan].msb == -1)
		{
			mlv_list[chan].msb = (chan==9)?127:0;
		}
		if (mlv_list[chan].lsb == -1)
		{
			mlv_list[chan].lsb = 0;
		}
	}

	find_insfile_bank_voicenames();

	for (chan=0; chan<16; chan++)
	{
		// compute melody/drum channels
		int bank = 128*mlv_list[chan].msb + mlv_list[chan].lsb;
		mlv_list[chan].melody = is_yamaha_melody_voice(bank,mlv_list[chan].voice) && (chan!=9);
	}
}

//**************************************************************************
//*
//*     remove_sysex_drum_mode()
//*
//**************************************************************************

void HPMF_Interface::remove_sysex_drum_mode()
{
	/*
		Drum-Kits SysEx "F0 43 10 4C 08 <channel> 07 <partmode> F7"
   
		Partmode:
		00 Normal (melody voice)
		01 Drum   (first channe |= 10)		
		02 DrumS1 (channel 10 only)
		03 DrumS2  (second channel |= 10)
	*/
	// Look for drum kit sysex

	int i;
	int id, chan, type, time, length;
	unsigned char* data;
	int part = -1;
	int partmode = -1;

	int no_drumchan = 0;
	const int chanx = 5;
	const int partmodex = 7;

	unsigned char drumkit_sysex[9]  = {0xf0,0x43,0x10,0x4C,0x08,0,0x07,0,0xf7}; 	// (XG) Drum Kit SysEx
	
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type != HP_SYSEX) continue;

		HP_ReadSysex(mf,id,&time,&data,&length);
	
		bool drumkit_sysex_found = false;
		
		if (length != 9)
		{
			HP_Delete(data);
			continue;
		}
		
		for (i=0; i<9; i++)
		{
			if ((i==chanx) || (i==partmodex))
			{
				continue;
			}
			if (data[i] != drumkit_sysex[i])
			{
				HP_Delete(data);
				break;
				
			}
			if (i==8)
			{
				drumkit_sysex_found = true;
				HP_Delete(data);
				HP_DeleteEvent(mf,id);
			}
		}
	}
}


//**************************************************************************
//*
//*     update_no_notes(int no_notes[16])
//*		computes the number on notes of each channel
//*
//**************************************************************************

void HPMF_Interface::update_no_notes(int no_notes[16])
{
	int id, chan, time, type;

	for (chan=0; chan<16; chan++)
	{
		no_notes[chan] = 0;
	}


	HP_Rewind(mf);

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			no_notes[chan]++;
		}
	}
}


//**************************************************************************
//*
//*		is_mega_voice
//*		finds out if a voice-bank is a mega voice bank
//*
//**************************************************************************

bool HPMF_Interface::is_mega_voice(int msb, int lsb)
{
	return ((msb==8) && (lsb<32));
}

//**************************************************************************
//*
//*		is_sart_voice
//*		finds out if a voice-bank is a S.Art voice bank
//*
//**************************************************************************

bool HPMF_Interface::is_sart_voice(int msb, int lsb)
{
	return ((msb==8) && (lsb>=32));
}

//**************************************************************************
//*
//*		update_takt_bar_time_list
//*		to be used after changing ppqn, deleting or inserting takts
//*
//**************************************************************************

void HPMF_Interface::update_takt_bar_time_list()
{
	int id, chan, type, time;
	TAKT_BAR_TIME_ELEM tbte;
	int time_of_taktchange = 0;
	int takt_of_taktchange = 0;
	int last_event_time;
	takt_bar_time_list_free = 0; // clear list

	// insert first takt/bar/time Element
	tbte.takt = 0;
	tbte.bar = 0;
	tbte.time = 0;
	tbte.num = 4;
	tbte.tbe = TAKT;
	last_num = 4;


	takt_bar_time_list.SetAtGrow(takt_bar_time_list_free,tbte);
	takt_bar_time_list_free++;

	HP_Rewind(mf);

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_TIME_SIGNATURE)
		{
			int metronome_click,n32, scr_bar, scr_tick;
			int old_takt_of_taktchange = takt_of_taktchange;
			HP_GetTaktBeatTick(mf,time, &takt_of_taktchange,&scr_bar, &scr_tick);
			if (takt_of_taktchange > old_takt_of_taktchange)
			{	// fill all missing takt_bar_times in list
				fill_takt_bar_time_list(old_takt_of_taktchange, takt_of_taktchange,false,-1);
			}
			HP_ReadTimeSignature(mf,id,&time_of_taktchange,&last_num,&last_denum,&metronome_click,&n32);
			if (takt_bar_time_list_free > 0)
			{
				(takt_bar_time_list[takt_bar_time_list_free-1]).num = last_num;
			}
			continue;
		}
	}
	last_event_time = time;
	// complete takt_bar_time_list
	int takt, bar, tick;

	HP_GetTaktBeatTick(mf,time, &takt,&bar, &tick);
	if (takt > takt_of_taktchange)
	{	// fill all missing takt_bar_times in list
		fill_takt_bar_time_list(takt_of_taktchange, takt,true,last_event_time);
	}

/*
// Test
	int i;
	for(i=0; i<takt_bar_time_list_free; i++)
	{
		tbte = takt_bar_time_list[i];
		CString r;
		r.Format("takt=%i,bar=%i,time=%i,num=%i,tbe=%s",
			tbte.takt,tbte.bar,tbte.time,tbte.num,
			tbte.tbe==TAKT?"TAKT":tbte.tbe==END?"END":"BEAT");
		MessageBox(r);
	}
*/
}

//**************************************************************************
//*
//*		update_low_high_limit_lists
//*
//**************************************************************************

void HPMF_Interface::update_low_high_limit_lists()
{
	int id, chan, time, type;
	int note, vel, length;
	bool is_mega[16];

	int megachan_limit = 96; // mega_voices: above only effect notes

	for (chan=0; chan<16; chan++)
	{
		highlimit[chan] = 0;
		lowlimit[chan] = 127;
		is_mega[chan] = mlv_list[chan].is_mega;
	}

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (chan == HP_NO_CHAN) continue;
		if (type== HP_NOTE)
		{
			HP_ReadNote(mf,id,&time, &chan, &note, &vel, &length);

			if (!is_mega[chan])
			{
				if (note<lowlimit[chan]) lowlimit[chan] = note;
				if (note>highlimit[chan]) highlimit[chan] = note;
			}
			else
			{
				if ((note<lowlimit[chan])&&(note<megachan_limit)) lowlimit[chan] = note;
				if ((note>highlimit[chan])&&(note<megachan_limit)) highlimit[chan] = note;  
			}
		}
	}
/*
    CString r;
	r.Format("lowlimit[0] %i, highlimit[0] %i", lowlimit[0], highlimit[0]);
	MessageBox(r);
*/
}

//**************************************************************************
//*
//*		eval_lyrics_at_channel_notes
//*		glues lyrics from file at notes of a melody-channel
//*
//**************************************************************************

void HPMF_Interface::eval_lyrics_at_channel_notes(CString lyricfile, int chan)
{
	int line_number = 0; // counts from 1 to last lyric
	CStdioFile *cf_f = NULL;
	CFileException e;
	CString line;

	source_changed = false;

	CFileStatus status;

	if (!CFile::GetStatus(lyricfile,status))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_LYRICFILE),NULL,MB_OK|MB_TASKMODAL);
		return; // file does not exist
	}

	cf_f = new CStdioFile;
	if (!cf_f->Open(lyricfile, CFile::shareExclusive | CFile::modeRead | CFile::typeText, &e))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_LYRICFILE),NULL,MB_OK|MB_TASKMODAL);
		return; // file does not exist
    }
	while (true)
	{
		if (!cf_f->ReadString(line))
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_NO_START_LYRICLIST),NULL,MB_OK|MB_TASKMODAL);
			cf_f->Close();
			delete cf_f;
			cf_f = NULL;
			return;
		}
		line_number ++;

		CString line1 = line;;
		line1.TrimRight();
		if (line1 == GlobalUtilities::start_lyriclist)
		{
			break;
		}
	}

	CArray <LL,LL> local_lyriclist;
	int no_lyrics = 0;
	LL ll;
	bool lf_before = false;

	// read and store lyrics in list
	while (true)
	{

		if (!cf_f->ReadString(line))
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_NO_END_LIST),NULL,MB_OK|MB_TASKMODAL);
			cf_f->Close();
			delete cf_f;
			cf_f = NULL;
			return;
		}
		CString line1 = line;
		line1.TrimRight();
		if (line1 == GlobalUtilities::end_list)
		{
			break;
		}

		// check line
		int char_no = 0;
		char ch = (char)0;
		char last_ch = (char)0;
		char next_ch = (char)0;
		while (true)
		{
			CString lyrictxt;
			while (char_no < line.GetLength())
			{
				if (char_no > 0)
				{
					last_ch = ch;
				}
				ch = line.GetAt(char_no);
				if (char_no < line.GetLength()-1)
				{
					next_ch = line.GetAt(char_no+1);
				}
				if (GlobalUtilities::is_printable(ch))
				{
					if (ch=='/')
					{
						lyrictxt += linefeed_char;
					}
					else
					if (ch=='_')
					{
						lyrictxt += ' ';
					}
					else
					if (ch=='-')
					{ // display '-' sequences outside of words
						if 	(!GlobalUtilities::is_letter(last_ch) || (!GlobalUtilities::is_letter(next_ch)))
						{
							lyrictxt += ch;
							char_no++;
							continue;
						}
						else
						{
							char_no++;
							break;
						}
					}
					else
					if (ch==' ')
					{
						lyrictxt += ch;
						char_no++;
						break;
					}
					else
					{
						lyrictxt += ch;
					}
					char_no++;
				}
				else
				{
					char_no++;
					break;
				}
			}

			ll.text = lyrictxt;
			ll.linefeed_before = lf_before;
			local_lyriclist.Add(ll);
			no_lyrics++;
			if (char_no >= line.GetLength())
			{
				lf_before = true;
				break;
			}
			else
			{
				lf_before = false;
			}
		}
		line_number++;
		last_ch = (char)0;
		next_ch = (char)0;
	}

	delete cf_f;

	int id, channel, time, type;
	int last_time = -1;
	int act_lyric_index = 0;
	char *lyric_ctext;

	CString act_lyric_text;
	bool act_linefeed_before;

	char linefeed_text[3];
	sprintf(linefeed_text,"%c",linefeed_char);

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&channel,&time,&type)==HP_ERR_NONE)
	{
		if (act_lyric_index >= no_lyrics) break;
		if (channel != chan) continue;

		if ((type != HP_NOTE) || (time <= last_time+8))
		{
			continue;
		}

		ll = local_lyriclist.GetAt(act_lyric_index);
		act_linefeed_before = ll.linefeed_before;
		while ((ll.text).GetLength()==0)
		{
			act_lyric_index++;
			if (act_lyric_index >= no_lyrics) break;
			ll = local_lyriclist.GetAt(act_lyric_index);
			act_linefeed_before |= ll.linefeed_before;
		}
		if (act_lyric_index >= no_lyrics) break;

		act_lyric_text = ll.text;

		GlobalUtilities::convert_CString_to_cstring(&lyric_ctext,act_lyric_text);

		HP_InsertLyric(mf,time,	lyric_ctext);
		if (act_linefeed_before)
		{
			HP_InsertLyric(mf,last_time+30,linefeed_text);
		}
		act_lyric_index++;
		delete[] lyric_ctext;

		last_time = time;
	}
	update_lyriclist();
	source_changed = true;
}

//**************************************************************************
//*
//*		eval_fill_lyrics
//*		inserts some hyphens as lyrics
//*		parameters of eval_fill_lyrics
//*		 NOT_AT_LYRIC
//*		 NOT_IN_QUARTER_WITH_LYRIC
//*		 NOT_IN_MEASURE_WITH_LYRIC	2
//*
//**************************************************************************

void HPMF_Interface::eval_fill_lyrics(int where)
{
	int i;
	int l = 0; // index lyriclist
	LYRICLIST_ELEM lem;		// element of lyriclist
	TAKT_BAR_TIME_ELEM tbte;// element of takt_bar_time_list

	// look if last lyric ends with linefeed
	int time_last_lyric_lf = -1;
	// -1 if last lyric ends with lf; time > 0 if last lyric does not end with lf

	if (lyriclist_free > 0)
	{
		lem = lyriclist[lyriclist_free-1];
		CString last_lyric = lem.text;
		char last_char = last_lyric[last_lyric.GetLength()-1];
		if ((last_char==0x0d) || (last_char=='/') || (last_char=='\\'))
		{
			time_last_lyric_lf = -1;
		}
		else
		{
			time_last_lyric_lf = lem.time;
		}
	}

	typedef struct {int takt;int bar; bool is_lyric;} LYRIC_IN_TAKT_BAR_ELEM;

	bool no_lyrics;
	bool insert_lyrics;
	CString act_takt_lyric, act_beat_lyric, act_end_lyric;
	int act_linefeedlyrictick;

	switch (is_user)
	{
	case 1:
		{
			act_takt_lyric = user1_takt_lyric;
			act_beat_lyric = user1_beat_lyric;
			act_end_lyric = user1_end_lyric;
			act_linefeedlyrictick = user1_linefeedlyrictick;
			break;
		}
	case 2:
		{
			act_takt_lyric = user2_takt_lyric;
			act_beat_lyric = user2_beat_lyric;
			act_end_lyric = user2_end_lyric;
			act_linefeedlyrictick = user2_linefeedlyrictick;
			break;
		}
	case 3:
		{
			act_takt_lyric = user3_takt_lyric;
			act_beat_lyric = user3_beat_lyric;
			act_end_lyric = user3_end_lyric;
			act_linefeedlyrictick = user3_linefeedlyrictick;
			break;
		}
	}

	int bar_no = 0;

	int list_len = takt_bar_time_list_free>lyriclist_free?takt_bar_time_list_free:lyriclist_free;

	// only for where = NOT_IN_QUARTER_WITH_LYRIC and NOT_IN_MEASURE_WITH_LYRIC:
	bool *lyric_in_takt_list = new bool[list_len];
	LYRIC_IN_TAKT_BAR_ELEM *lyric_in_takt_bar_list =
		new LYRIC_IN_TAKT_BAR_ELEM[list_len];

	for (i=0; i<list_len; i++)
	{
		lyric_in_takt_list[i] = false;
		lyric_in_takt_bar_list[i].takt = -1;
		lyric_in_takt_bar_list[i].bar = -1;
		lyric_in_takt_bar_list[i].is_lyric = false;
	};

	// look if Fill-Lyrics before other lyrics need to end with lf, and
	// look if Fill-Lyrics behind other lyric need to start with lf.
	// hint: update_lyriclist already has deleted lf at the beginning of the first lyric
	// and after the last char of the last lyric.

	bool last_fill_with_ending_lf = true;
	int time_of_first_lyric = -1;
	int time_of_last_lyric = -1;
	int time_of_last_fill_before_lyrics = -1;
	bool lf_before_inserted = false;
	bool lf_behind_inserted = false;

	if (lyriclist_free > 0)
	{
		time_of_first_lyric = (lyriclist[0]).time;
		time_of_last_lyric = (lyriclist[lyriclist_free-1]).time;
	}

	for (i=0; i<lyriclist_free; i++)
	{
		lem = lyriclist[i];

		if (bar_no >= list_len)
		{
			MessageBox("Error");
			break;
		}

		lyric_in_takt_list[lem.takt] = true;
		lyric_in_takt_bar_list[bar_no].takt = lem.takt;
		lyric_in_takt_bar_list[bar_no].bar = lem.bar;
		lyric_in_takt_bar_list[bar_no].is_lyric = true;
		bar_no++;
	}
	// end only for where = NOT_IN_QUARTER_WITH_LYRIC and NOT_IN_MEASURE_WITH_LYRIC

	source_changed = false;

	// initial: dummy lem
	lem.takt = -1;
	lem.bar = -1;
	lem.text = "";
	lem.delta_tick = -1;
	lem.num = 4;
	lem.time = -1;

	for (i = 0; i < takt_bar_time_list_free; i++)
	{
		insert_lyrics = false;

		no_lyrics = (l >= lyriclist_free);
		if (!no_lyrics)
		{
			lem = lyriclist[l];
		}
		else
		{
			// dummy lem
			lem.takt = -1;
			lem.bar = -1;
			lem.text = "";
			lem.delta_tick = -1;
			lem.num = 4;
			lem.time = -1;
		}

		if((lem.takt == 0)&&no_lyrics)
		{   // don't look at takt 0
			l++;
			continue;
		}

		tbte = takt_bar_time_list[i];

CString r;
r.Format("Takt=%i, Bar=%i, time=%i, num = %i", tbte.takt, tbte.bar, tbte.time, tbte.num);
// MessageBox(r);

		if (tbte.takt==0) continue; // no fill lyrics in takt 0

		if (no_lyrics)
		{
			insert_lyrics = true;
		}
		else
		{
			switch (where)
			{
			case NOT_AT_LYRICS:
				{
					if ((lem.takt != tbte.takt) || (lem.bar != tbte.bar))
					{
						insert_lyrics = true;
					}
					else
					{
						if (((lem.text).GetLength() > 1) || (lem.delta_tick==0))
						{
							insert_lyrics = false; // a lyric at same time with a fill-lyric
						}
						else
						{   // ignore blank and linefeed
							insert_lyrics = (lem.text == " ")||
								(lem.text == "/")||
								(lem.text[0]==0x0d);
						}
						l++;

						// find next lyric with tick = 0
						while (l < lyriclist_free)
						{
							lem = lyriclist[l];
							if (lem.delta_tick ==0)
							{
								if ((lem.takt!=tbte.takt) || (lem.bar != tbte.bar))
								{
									break;
								}
							}
							l++;
						}
					}
					break;
				}

			case NOT_IN_BEATS_WITH_LYRICS:
				{
					insert_lyrics = true;
					for (bar_no=0; bar_no<list_len ; bar_no++)
					{
						if ((lyric_in_takt_bar_list[bar_no].takt==tbte.takt)&&
							(lyric_in_takt_bar_list[bar_no].bar==tbte.bar)&&
							(lyric_in_takt_bar_list[bar_no].is_lyric))
						{
							insert_lyrics = false;
							break;
						}
					}
					break;
				}
			case NOT_IN_MEASURES_WITH_LYRICS:
				{
					insert_lyrics = !lyric_in_takt_list[tbte.takt];
					break;
				}

			default:
				{
					break;
				}
			}
		}

		if (insert_lyrics)
		{
			char inserted_fill[32];
			inserted_fill[0] = 0;

			char lf_lyric[2];
			lf_lyric[0] = linefeed_char;
			lf_lyric[1] = 0x00;

			if ((tbte.tbe==TAKT)&&(act_takt_lyric[0]==0)) continue;
			if ((tbte.tbe==BEAT)&&(act_beat_lyric[0]==0)) continue;
			if ((tbte.tbe==END) &&(act_end_lyric[0] ==0)) continue;

			// if last original lyric does not end with lf, insert lf
			if ((time_last_lyric_lf > 0) && (tbte.time > time_last_lyric_lf))
			{
				HP_InsertLyric(mf, (tbte.time+time_last_lyric_lf)/2, lf_lyric);
				time_last_lyric_lf = -1; // only one!
			}

			strcpy(inserted_fill,(tbte.tbe==TAKT)?act_takt_lyric:((tbte.tbe==BEAT)?act_beat_lyric:act_end_lyric));
			HP_InsertLyric(mf,tbte.time,inserted_fill);


			if ((tbte.time>time_of_first_lyric) &&
				(time_of_last_fill_before_lyrics!=-1) &&
				!lf_before_inserted)
			{
				if (!last_fill_with_ending_lf)
				{
					HP_InsertLyric(mf,time_of_last_fill_before_lyrics+30,lf_lyric);
					lf_before_inserted = true;
				}
			}

			if ((tbte.time<time_of_first_lyric)&&(tbte.time<time_of_last_lyric))
			{
				char ch;

				time_of_last_fill_before_lyrics = tbte.time;

				ch = inserted_fill[strlen(inserted_fill)-1];
				last_fill_with_ending_lf = (ch=='/')||(ch==0x0d);
			}

			if (tbte.time>time_of_first_lyric)
			{
				lf_before_inserted = true;
			}

			if ((tbte.time>time_of_first_lyric)&&(tbte.time>time_of_last_lyric)&&(tbte.takt>1))
			{
				if (!lf_before_inserted && (tbte.tbe==TAKT))
				{
					char ch = inserted_fill[0];
					if ((ch!='/')&&(ch!=0x0d))
					{
						HP_InsertLyric(mf,tbte.time-30,lf_lyric);
					}
					lf_behind_inserted = true; // means: all OK after
				}
			}

			if ((tbte.tbe==END)&&(act_linefeedlyrictick!= -1))
			{
				int k;
				bool time_occupied = false;
				int lf_tick_time = tbte.time+act_linefeedlyrictick;
				LYRICLIST_ELEM lem1;
				for (k=0; k<lyriclist_free; k++)
				{
					lem1 = lyriclist[k];
					if (lem1.time == lf_tick_time)
					{
						time_occupied = true;
						break;
					}
				}

				if(!time_occupied)
				{
					HP_InsertLyric(mf,lf_tick_time,lf_lyric);

					if ((lf_tick_time<time_of_first_lyric))
					{
						time_of_last_fill_before_lyrics = lf_tick_time;
						last_fill_with_ending_lf = true;
					}

				}
			}
			with_lyrics = true;
		}
	}
	delete[] lyric_in_takt_list;
	delete[] lyric_in_takt_bar_list;
	source_changed = true;
	update_lyriclist();
}

//**************************************************************************
//*
//*		eval_delete_fill_lyrics
//*
//**************************************************************************

int HPMF_Interface::eval_delete_fill_lyrics(CString fl1, CString fl2, CString fl3)
{
	int id, chan, time, type;
	int measure, bar, tick;
	char* text;
	CString text_cstr;
	int no_fill_lyrics_deleted = 0;

	source_changed = false;

	bool fl_deleted = false;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_LYRIC)
		{
			HP_ReadLyric(mf,id,&time,&text);
			text_cstr = text;
		
			if (fl_deleted)
			{ // look for following linefeed

				fl_deleted = false;
				if ((text[0]==0x0d)&&(text[1]==0))
				{
					HP_DeleteEvent(mf,id);
					no_fill_lyrics_deleted++;
					continue;
				}
			}

			{ // look for fill lyric
				HP_GetTaktBeatTick(mf, time, &measure, &bar, &tick);
				if (tick != 0)
				{
					continue;
				}
				// lyric at beat position, look if fl1, fl2 or fl3

				if ((text_cstr==fl1)||(text_cstr==fl2)||(text_cstr==fl3))
				{
					HP_DeleteEvent(mf,id);
					fl_deleted = true;
					no_fill_lyrics_deleted++;
					continue;
				}

				CString short_text_cstr = text_cstr;

				short_text_cstr.Remove(' ');
				short_text_cstr.Remove(0x0d);


				CString short_fl1 = fl1;
				short_fl1.Remove(' ');
				short_fl1.Remove('/');

				CString short_fl2 = fl2;
				short_fl2.Remove(' ');
				short_fl2.Remove('/');

				CString short_fl3 = fl3;
				short_fl3.Remove(' ');
				short_fl3.Remove('/');

				if ((short_text_cstr==short_fl1) ||
					(short_text_cstr==short_fl2) ||
					(short_text_cstr==short_fl3) )
				{
					HP_DeleteEvent(mf,id);
					fl_deleted = true;
					no_fill_lyrics_deleted++;
					continue;
				}
			}
		}
	}


	update_lyriclist();

	if (no_fill_lyrics_deleted > 0)
	{
		source_changed = true;
	}
	return no_fill_lyrics_deleted;
}



//**************************************************************************
//*
//*		eval_shift_linefeeds
//*		shift all linefeeds some ticks later from the last text_lyric
//*
//**************************************************************************

void HPMF_Interface::eval_shift_linefeeds(int ticks, int ticks_at)
{
	bool is_at = (ticks_at > 0);

	int id, chan, time, type;
	int i;
	int len;
	int lyric_type = -1;
	ArrayLinefeeds lfs;
	ArrayLinefeeds additional_lfs;
	char* text;
	char lf_char;	 // linefeed 0x0d or newpage 0x0a
	char lf[] = " "; // string with lf_char


	TAKT_BAR_TIME_ELEM tbte;

	source_changed = false;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_LYRIC)
		{
			HP_ReadLyric(mf,id,&time,&text);
			// text is deleted by ArrayLinefeeds
			len = strlen(text);
			bool lf_found = false;
			lf_char = 0x00;

			for (i=len-1; i>=0; i--)
			{
				if (text[i]==' ') continue;
				if ((text[i]==0x0d)||(text[i]==0x0a))
				{
					lyric_type = lfs.single_lf;
					lf_char = text[i];
					lf_found = true;
					continue;
				}
				if ((text[i]!=0x0d)&&(text[i]!=0x0a))
				{
					lyric_type = lf_found?lfs.with_lf:lfs.without_lf;
					break;
				}
			}
			lfs.add(time,lyric_type,text,lf_char);
			// only with_lf and single_lf must be changed, delete these
			if (lyric_type!=lfs.without_lf) HP_DeleteEvent(mf,id);
		}
	}

/*
	CString r;
	for (i=0; i<lfs.get_length(); i++)
	{

		lfs.get(i,&time, &lyric_type, &text, &lf_char);
		r.Format("lfs: i= %i, time=%i,lyric_type=%i, text=%s, lf_char=%x",
			i, time, lyric_type,text,lf_char);
		MessageBox(r);
	}
*/

	int lfs_i;
	int old_time = -1;
	int last_time = -1;
	int next_time = -1;
	char old_lf_char = ' ';
	bool last_lf_deleted = false;
	bool is_single_lf = false;
	bool is_linefeed = false;
	bool is_newpage = false;

	for (lfs_i=0; lfs_i<lfs.get_length(); lfs_i++)
	{
		old_time = last_time==-1?next_time:last_time;
		last_time = next_time;
		old_lf_char = lf_char;

		lfs.get(lfs_i,&next_time, &type, &text, &lf_char);
		if (last_lf_deleted && (last_time!=-1))
		{
			int lf_time;
			if (is_at)
			{
				if (is_single_lf)
				{
					for (i = 0; i < takt_bar_time_list_free-1; i++)
					{
						tbte = takt_bar_time_list[i];
						if (tbte.time+ticks_at > old_time)
						{
							if (tbte.time+ticks_at < next_time-30)
							{
								lf_time = tbte.time+ticks_at;
							}
							else
							{
								lf_time = old_time+(next_time-old_time)/2;
							}
							break;
						}
						else
						{
							continue;
						}
					}
				}
				else
				{
					for (i = 0; i < takt_bar_time_list_free-1; i++)
					{
						tbte = takt_bar_time_list[i];
						if (tbte.time+ticks_at > last_time)
						{
							if (tbte.time+ticks_at < next_time-30)
							{
								lf_time = tbte.time+ticks_at;
							}
							else
							{
								lf_time = last_time+(next_time-last_time)/2;
							}
							break;
						}
						else
						{
							continue;
						}
					}
				}
			}
			else
			{
				if (is_single_lf)
				{
					lf_time = (next_time-old_time)>2*ticks?old_time+ticks:
			                              old_time+(next_time-old_time)/2;
				}
				else
				{
					lf_time = last_time + ticks;
					if (lf_time > next_time-ticks) lf_time = (next_time+last_time)/2;
				}
			}
			additional_lfs.add(lf_time,lfs.single_lf,NULL, old_lf_char);
			last_time = lf_time;
			last_lf_deleted = false;
			is_single_lf = false;
		}

		if (type==lfs.without_lf)
		{
			last_lf_deleted = false;
			is_single_lf = false;
			continue; // nothing to do
		}

		if (type==lfs.with_lf)
		{
			// delete lf and blank from end
			int len = strlen(text);
			for (i=len-1; i>=0; i--)
			{
				if ((text[i]!=' ')&&(text[i]!=0x0d)&&(text[i]!=0x0a)) break;
				text[i] = 0;
			}
			is_single_lf = false;
			last_lf_deleted = true;
			continue;
		}

		if (type==lfs.single_lf)
		{
			is_single_lf = true;
			last_lf_deleted = true;
			continue;
		}
	}

	// do not store a lf at the end of all lyrics; update_lyriclist()
	// will delete it always

	for (i=0; i<lfs.get_length();i++)
	{
		lfs.get(i,&time, &type, &text,&lf_char);
		if (type!=lfs.with_lf) continue;
		HP_InsertLyric(mf,time,text);
		source_changed = true;
	}

	for (i=0; i<additional_lfs.get_length();i++)
	{
		additional_lfs.get(i,&time, &type, &text, &lf_char);
		lf[0] = lf_char;
		HP_InsertLyric(mf,time,lf);
		source_changed = true;
	}
	update_lyriclist();

/*
	CString r;

	for (i=0; i<lfs.get_length(); i++)
	{
		lfs.get(i,&time, &type, &text, &lf_char);

		CString ctype = type==lfs.single_lf?"single_lf":type==lfs.with_lf?"with_lf":"without_lf";

		r.Format("lfs: time %i, type %s, text <%s>, lf_char %2.2x",time,ctype,text,lf_char);
		MessageBox(r);
	}

	for (i=0; i<additional_lfs.get_length(); i++)
	{
		int time, type;
		additional_lfs.get(i,&time, &type, &text,&lf_char);
		r.Format("addtional_lfs: time %i",time);
		MessageBox(r);
	}
*/

}

//**************************************************************************
//*
//*		exchange_lyric_linefeed
//*		exchanges '/' by GlobalUtilities::get_linefeed_char() ( == 0x0d)
//*
//**************************************************************************

int HPMF_Interface::exchange_lyric_linefeed()
{
	int id, chan, time, type;
	int i;
	int len;
	int no_lyrics_changed = 0;

	source_changed = false;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_LYRIC)
		{
			bool is_changed = false;
			char* text;
			HP_ReadLyric(mf,id,&time,&text);
			len = strlen(text);

			for (i=0; i<len; i++)
			{
				if (text[i]=='/')
				{
					is_changed = true;
					text[i] = linefeed_char;
				}
			}

			if (is_changed)
			{
				HP_ChangeLyric(mf,id,text);
				no_lyrics_changed++;
			}
			HP_Delete(text);
		}
	}
	if (no_lyrics_changed > 0)
	{
		source_changed = true;
	}
	return no_lyrics_changed;
}

//**************************************************************************
//*
//*		is_rpn_nrpn_ctrl
//*
//**************************************************************************

bool HPMF_Interface::is_rpn_nrpn_ctrl(int number)
{
	// look at controller of RPN/NRPN
	return ((number==  6)||
		(number== 38)||
		(number== 96)||
		(number== 97)||
		(number== 98)||
		(number== 99)||
		(number==100)||
		(number==101)   );
}

//**************************************************************************
//*
//*		is_sart_ctrl
//*
//**************************************************************************

bool HPMF_Interface::is_sart_ctrl(int number)
{
	// look at controller of RPN/NRPN
	return ((number==  80)||
		    (number== 81)||
		    (number== 82)   );
}

//**************************************************************************
//*
//*		extract_composer_lyricist
//*		delivers composer and lyricist from xfln-string
//*
//**************************************************************************

void HPMF_Interface::extract_composer_lyricist(char *xfln_text, CString *composer, CString *lyricist)
{
	int i, k, l;
	int pos = 3; // position at ':' of first item composer
	int actual_colon_no = 0;
	*composer = "";
	*lyricist = "";

	for (i = 0; i<(int)strlen(xfln_text); i++)
	{
		if (xfln_text[i]==':')
		{
			actual_colon_no++;
			if (actual_colon_no < pos)
			{
				continue;
			}
		}

		if (xfln_text[i] != ':') continue;

		// the pos'th colon arrived
		for (k=i+1; k<(int)strlen(xfln_text); k++)
		{
			if (xfln_text[k]==':') break;
			*composer += xfln_text[k];
		}
		for (l=k+1; l<(int)strlen(xfln_text); l++)
		{
			if (xfln_text[l]==':') break;
			*lyricist += xfln_text[l];
		}

		break;
	}
}

//**************************************************************************
//*
//*		insert_xfln_item
//*		sets the item behind the pos'th colon
//*		into the XFln Text Event string
//*
//**************************************************************************

CString HPMF_Interface::insert_xfln_item(const CString xfln_text, const CString item, int pos)
{
	CString new_xfln_text = "";
	int i, k;
	int actual_colon_no = 0;

	for (i=0; i<xfln_text.GetLength(); i++)
	{
		new_xfln_text += xfln_text[i];
		if (xfln_text[i]==':')
		{
			actual_colon_no++;
			if (actual_colon_no == pos)
			{
				break;
			}
		}
	}

	// new_xfln_text filled until pos'th colon

	new_xfln_text += item;

	for (k=i+1; k<xfln_text.GetLength(); k++)
	{
		if (xfln_text[k] != ':')
		{
			continue;
		}
		new_xfln_text += xfln_text[k];
	}
	return new_xfln_text;
}

//**************************************************************************
//*
//*		eval_cuepoint_lyrc
//*		Inserts or changes the cuepoint $Lyrc:1:<offset>:L1
//*
//**************************************************************************

void HPMF_Interface::eval_cuepoint_lyric(int offset)
{
	if (!lyric_cuepoint) return; // no cuepoint lyrics wanted
	source_changed = false;
	if (with_cuepoint_lyrics)
	{
		char* text = NULL;
		int id, chan, type, time;
		const CString r = "$Lyrc:"; // look for "$Lyrc:" only

		HP_Rewind(mf);
		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (type != HP_CUE_POINT) continue;
			HP_ReadCuePoint(mf,id,&time,&text);
			int len = strlen(text);
			if (len>r.GetLength())
			{
				bool found = true;
				for (int i = 0; i<r.GetLength(); i++)
				{
					if (text[i] != r[i])
					{
						found = false;
						break;
					}
				}
				if (found) HP_DeleteEvent(mf,id);;
			}
			if (text != NULL) HP_Delete(text);
			text = NULL;
			continue;
		}
	}

	char cuepoint_text[128];
	sprintf(cuepoint_text,"$Lyrc:1:%i:L1",offset);
	HP_SetFirst(mf,HP_LAST);
	HP_InsertCuePoint(mf,0,cuepoint_text);
	with_cuepoint_lyrics = true;
	source_changed = true;
}

//**************************************************************************
//*
//*		eval_change_drum
//*		changes all notes with value note of a drum-chan chan to a new note
//*     new_note == -1: Delete note-event
//*		new_velocity == -1: Do not change velocity
//*		called from changedrumvoicesdlg.cpp
//*
//**************************************************************************

bool HPMF_Interface::eval_change_drum(int chan,
									  int note,
									  int new_note,
									  int new_velocity,
									  bool dynamic,
									  int min_vel,
							          int max_vel)
{
	source_changed = false;

	if ((chan==-1)||(note==-1))
	{
		return false;
	}

	if (mlv_list[chan].melody)
	{
		return false;
	}

	int id, scr_chan, type, time;
	int scr_note, velocity,length;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&scr_chan,&time,&type)==HP_ERR_NONE)
	{
		if (scr_chan != chan) continue;
		if (type != HP_NOTE) continue;
		HP_ReadNote(mf,id,&time, &scr_chan, &scr_note, &velocity, &length);
		if (scr_note != note) continue;
		if (new_note == -1)
		{
			HP_DeleteEvent(mf,id);
			continue;
		}

		if (note != new_note)
		{
			HP_ChangeNote(mf,id,chan,new_note,HP_ABSOLUTE);
		}

		if (new_velocity != -1)
		{
			if (!dynamic)
			{
				HP_ChangeVelocity(mf,id,chan,new_note,new_velocity,HP_NO_PERCENT);
			}
			else
			{
				int dyn_vel = (new_velocity*velocity)/max_vel;
				if (dyn_vel <= 0) dyn_vel = 1;
				HP_ChangeVelocity(mf,id,chan,new_note,dyn_vel,HP_NO_PERCENT);
			}
		}
	}

	source_changed = true;
	return true;
}


//**************************************************************************
//*
//*		eval_exchange_channels
//*		copies, deletes or exchanges channels
//*
//**************************************************************************

void HPMF_Interface::eval_exchange_channels(int selection, bool source_channels[16], int dest_channel)
{
/*
	CString r;
	r.Format("eval_exchange_channel: selection %i, source_channel %i, dest_channel %i",
		selection, source_channel, dest_channel);
	::MessageBox(AfxGetMainWnd()->m_hWnd,r,"Test",MB_OK|MB_TASKMODAL);
*/
	int id, chan, time, type, length;
	unsigned char *data;

	int only_source_channel = -1; // not used with DELETE_SELECTED
	for (chan=0; chan<16; chan++)
	{
		if (source_channels[chan])
		{
			only_source_channel = chan;
			break;
		}
	}

	source_changed = false;

	int no_double_notes;
	int no_pitch_wheels;
	eval_xg_convert(&no_double_notes, &no_pitch_wheels);

	fill_part_chan_list();
	switch (selection)
	{
	case DELETE_SELECTED:
		{
			for (chan=0; chan<16; chan++)
			{
				if (!source_channels[chan]) continue;
				if (delete_chan_events(mf,chan,false,true,true,true) > 0)
				{
					source_changed = true;
				}
			}
			break;
		}
	case EXCHANGE_SELECTED:
		{
			exchange_or_copy_chan_events(only_source_channel, dest_channel, true);
			source_changed = true;
			break;
		}
	case CUT_COPY_SELECTED:
		{
			cut_copy_chan_events(mf, only_source_channel, dest_channel);
			source_changed = true;
			break;
		}
	case COPY_SELECTED:
		{
			exchange_or_copy_chan_events(only_source_channel, dest_channel, false);

			// delete vh channel sysex all channels != only_source_channel
			HP_Rewind(mf);
			while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
			{
				if (type==HP_NOTE)
				{
					break;
				}
				if (type==HP_SYSEX)
				{
					HP_ReadSysex(mf,id,&time,&data,&length);
					int vh_chan = GlobalUtilities::is_vh_channel_sysex(data,length);
					if ((vh_chan!=-1) && (vh_chan!=only_source_channel))
					{
						HP_DeleteEvent(mf,id);
					}
					HP_Delete(data);
				}
			}

			source_changed = true;
			break;
		}
	default:
		{
		}
	}
	init_hpmfiledata();
	eval_xg_convert(&no_double_notes,&no_pitch_wheels);
}

//**************************************************************************
//*
//*		eval_xg_convert
//*		convert to XG: delete non-YAMAHA sysex, change unknown bank-MSB's to 0
//*		insert GM On and XG ON if missed
//*     returns no_controller_deleted
//*     fills no_double_notes, no_pitch_wheels
//*
//**************************************************************************

int HPMF_Interface::eval_xg_convert(int *no_double_notes, int *no_pitch_wheels)
{
	int id, chan, time, type;
	int value, vel, length;
	int i, ch;
	int ppqn_old = ppqn;
	int tofnote[16];
	int time_of_last_event = -1;
	int time_of_first_relevant_takt;
	int no_controller_deleted = 0;
	int no_pitchwheels_deleted = 0;
	int no_all_notes = 0;
	bool was_gs_on = false;
	char* last_marker_text = NULL;
	int last_marker_time = -1;
	int last_marker_id = -1;

	*no_double_notes = 0;
	*no_pitch_wheels = 0;

	bool not_delete_empty_channel[16]; 

	// repair overlapping equal notes
	for (ch=0; ch<16; ch++)
	{
		if (mute[ch])
		{
			continue;
		}
		if (!(mlv_list[ch]).melody)
		{
			continue;
		}
		repair_overlapping_notes(ch);
	}

	HP_Deselect(mf);

	// delete needless sysex
	delete_needless_sysex();

	struct vlstruct {int msb; int lsb; int voice; int time_last_voice;} vl[16];

	const struct{int prg_ch; char* kit;} kit_list[24] =
	{
		{0,"Standard Kit 1"},
		{1,"Standard Kit 2"},
		{4,"Hit Kit"},
		{8,"Room Kit"},
		{16,"Rock Kit"},
		{24,"Electro Kit"},
		{25,"Analog Kit"},
		{27,"Dance Kit"},
		{32,"Jazz Kit"},
		{40,"Brush Kit"},
		{48,"Symphony Kit"},
		{80,"Live! Standard Kit"},
		{81,"Live! Funk Kit"},
		{82,"Live! Brush Kit"},
		{83,"Live! Standard + Percussion Kit"},
		{84,"Live! Funk + Percussion Kit"},
		{85,"Live! Brush + Percussion Kit"},
		{86,"Live! Studio Kit"},
		{87,"Live! Power Kit1"},
		{88,"Live! Power Kit2"},
		{123,"Live! Standard Kit"},
		{124,"Live! Funk Kit"},
		{125,"Live! Standard + Percussion Kit"},
		{126,"Live! Funk + Percussion Kit"},
	};

	// channel specific time of first note;
	// channel specific msb/lsb/voice until first note

	for (i=0; i<16; i++)
	{
		tofnote[i] = -1;
		vl[i].msb = -1;
		vl[i].lsb = -1;
		vl[i].voice = -1;
		vl[i].time_last_voice = -1;
		mute[i] = true;
	}

	int time_of_first_note = -1;

	source_changed = false;

	if (with_lyrics && !with_cuepoint_lyrics && lyric_cuepoint)
	{
		eval_cuepoint_lyric(0);
	}

	/* compute no_notes[chan], not_notes[chan] and 
	   not_delete_empty_channel[chan] ************************************/

	update_no_notes(no_notes);

	int not_notes[16]; // no of events /= notes of all channels

	for (chan=0; chan<16; chan++)
	{
		not_notes[chan] = 0;
	}

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if ((type!=HP_NOTE)&&(chan!=HP_NO_CHAN))
		{
			not_notes[chan]++;
		}
	}

	for (chan=0; chan<16; chan++)
	{
		if (delete_empty_chan)
		{
			not_delete_empty_channel[chan] = false;
		}
		else
		{
			if ((no_notes[chan]==0)&&(not_notes[chan]>0))
			{
				not_delete_empty_channel[chan] = true;
				// arbritrary note; will be deleted at the end:
				HP_InsertNote(mf,1921,480,0x40,chan,0x01); 
			}
			else
			{
				not_delete_empty_channel[chan] = false;
			}
		}
	}


	/* compute mute, time_of_last_event and no_all_notes ******************/

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_NOTE)
		{
			mute[chan] = false;
			no_all_notes++;
		}
		time_of_last_event = time;
	}

	/* delete double notes if wanted **************************************/

	if (!double_notes_allowed)
	{
		int actual_time[16];
		int delete_list_index = 0;

		int *delete_notes_id_list = new int[no_all_notes];
		ArrayNotesAtSameTime *same_time_notes = new ArrayNotesAtSameTime[16];

		CString r;

		HP_Rewind(mf);
		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (type == HP_NOTE)
			{
				if (!mlv_list[chan].melody && double_drum_notes_allowed)
				{
					continue;
				}

				HP_ReadNote(mf,id,&time,&chan,&value,&vel,&length);
				if (same_time_notes[chan].get_length() == 0)
				{
					actual_time[chan] = time;
					same_time_notes[chan].add(id,value,length);
				}
				else
				{
					if (actual_time[chan] == time)
					{
						same_time_notes[chan].add(id,value,length);
					}
					else
					{	// analyze list same_time_notes[chan]
						int ix, iy, idx, idy, notex, notey, lenx, leny;
						int no_notes = same_time_notes[chan].get_length();
						if (no_notes > 1)
						{
							same_time_notes[chan].sort();
							for (ix=0; ix<no_notes; ix++)
							{
								same_time_notes[chan].get(ix,&idx,&notex,&lenx);
								for (iy=ix+1; iy<no_notes; iy++)
								{
									same_time_notes[chan].get(iy,&idy,&notey,&leny);
									if (notex==notey)
									{
										bool already_in_list = false;
										for (i=0; i<delete_list_index; i++)
										{
											if (delete_notes_id_list[i]==idy)
											{
												already_in_list = true;
												break;
											}
										}
										if (!already_in_list)
										{
											delete_notes_id_list[delete_list_index] = idy;
											delete_list_index++;
										}
									}
								}
							}
						}
						same_time_notes[chan].clear_list();
						same_time_notes[chan].add(id,value,length);
						actual_time[chan] = time;
					}
				}
			}
			// look at last notes
			for (chan=0; chan<16; chan++)
			{
				{	// analyze list same_time_notes[chan]
					int ix, iy, idx, idy, notex, notey, lenx, leny;
					int no_notes = same_time_notes[chan].get_length();
					if (no_notes > 1)
					{
						same_time_notes[chan].sort();
						for (ix=0; ix<no_notes; ix++)
						{
							same_time_notes[chan].get(ix,&idx,&notex,&lenx);
							for (iy=ix+1; iy<no_notes; iy++)
							{
								same_time_notes[chan].get(iy,&idy,&notey,&leny);
								if (notex==notey)
								{
									bool already_in_list = false;
									for (i=0; i<delete_list_index; i++)
									{
										if (delete_notes_id_list[i]==idy)
										{
											already_in_list = true;
											break;
										}
									}
									if (!already_in_list)
									{
										delete_notes_id_list[delete_list_index] = idy;
										delete_list_index++;
									}
								}
							}
						}
					}
				}
			}
		}

		// sort delete_notes_id_list by id's
		{
			int i,j;
			for (i=1; i<delete_list_index; i++)
			{
				int id_i = delete_notes_id_list[i];
				j = i-1;
				while ((j>=0) && (id_i < delete_notes_id_list[j]))
				{
					delete_notes_id_list[j+1] = delete_notes_id_list[j];
					j--;
				}
				delete_notes_id_list[j+1] = id_i;
			}
		}

		for (i=delete_list_index-1; i>=0; i--)
		{
			HP_DeleteEvent(mf,delete_notes_id_list[i]);
		}

		*no_double_notes = delete_list_index;

		delete[] delete_notes_id_list;
		delete[] same_time_notes;
	}

	/* Loop over all events ***********************************************/

	HP_Rewind(mf);
	int last_event_time = -1;

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		last_event_time = time;

		if (type == HP_SYSEX)
		{
			// Delete all sub_format-specific non YAMAHA-SysEx
			unsigned char *data;
			int length;
			HP_ReadSysex(mf,id,&time,&data,&length);

			if (GlobalUtilities::is_turn_tg300b_on(data))
			{
				HP_DeleteEvent(mf,id);
				HP_Delete(data);
				if (alien_sysex==1)
				{
					// insert event together with GM On an XG On
					// allow turn_tg300b_on
					with_xg_on = false;
					with_gs_on = true;
					was_gs_on = true;
				}
				else
				{
					// no GS emulation
					with_xg_on = false;
					with_gs_on = false;
					was_gs_on = true;
				}
				continue;
			}

			if ((data[1] != 0x7e) && (data[1] != 0x7f) && (data[1] != 0x43) && !alien_sysex)
			{
				HP_DeleteEvent(mf,id);
				HP_Delete(data);
				continue;
			}

			// Delete GM-On, will be inserted later
			if (GlobalUtilities::is_gm_on_sysex(data))
			{
				HP_DeleteEvent(mf,id);
				HP_Delete(data);
				continue;
			}

			// Delete XG-On, will be inserted later
			if (GlobalUtilities::is_xg_on_sysex(data))
			{
				HP_DeleteEvent(mf,id);
				HP_Delete(data);
				continue;
			}
/*
			// Delete lyrics_part_score_on_sysex, will be inserted later
			if (GlobalUtilities::is_lyrics_part_score_on_sysex(data))
			{
				HP_DeleteEvent(mf,id);
				HP_Delete(data);
				continue;
			}

			// Delete chord_part_score_on_sysex, will be inserted later
			if (GlobalUtilities::is_chord_part_score_on_sysex(data))
			{
				HP_DeleteEvent(mf,id);
				HP_Delete(data);
				continue;
			}
*/
			if (GlobalUtilities::is_part_not_used_sysex(data))
			{
				HP_DeleteEvent(mf,id);
				HP_Delete(data);
				continue;
			}

			if (GlobalUtilities::is_part_mode_normal_sysex(data))
			{
				HP_DeleteEvent(mf,id);
				HP_Delete(data);
				continue;
			}

			HP_Delete(data);
			continue;
		}

		// Delete meta events channel prefix 
		if (type==HP_CHANNEL_PREFIX)
		{
			HP_DeleteEvent(mf,id);
			continue;
		}

		// delete Ctrl. Reset all Controller (not needed with GM/XG On
		if (type == HP_RESET_ALL_CONTROLLERS)
		{
			HP_DeleteEvent(mf,id);
			continue;
		}

		// Ctrl. 65, 65, 66, 67: ON/OFF-Controller. Set all ON to 127 and all OFF to 0
		if ((type==HP_SUSTAIN) ||
			(type==HP_PORTAMENTO) ||
			(type==HP_SOSTENUTO) ||
			(type==HP_SOFT_PEDAL))
		{
			int number, value;
			HP_ReadController(mf,id,&time,&chan,&number,&value);
			if ((value>1) && (value<64))
			{
				HP_ChangeController(mf,id,type,0,HP_NO_PERCENT);
			}
			if ((value>=64) && (value<127))
			{
				HP_ChangeController(mf,id,type,127,HP_NO_PERCENT);
			}
		}

		// Bank Select MSB
		if (type == HP_BANK_SELECT_MSB)
		{
			int number, bank_msb;
			HP_ReadController(mf,id,&time,&chan,&number,&bank_msb);

			if (chan==9)
			{
				if ((bank_msb!=126)&&(bank_msb!=127)&&(bank_msb!=118)&&!with_xg_on&&!alien_voice)
				{
					//bank_msb==118 -> GS Drum
					HP_ChangeController(mf,id,HP_BANK_SELECT_MSB,127,HP_NO_PERCENT);
					bank_msb = 127;
				}
				if ((bank_msb==118)&&!alien_voice)
				{	// GS Drums
					HP_ChangeController(mf,id,HP_BANK_SELECT_MSB,127,HP_NO_PERCENT);
					bank_msb = 127;
				}
			}

			if (!alien_voice)
			{
				if (with_xg_on)
				{
					if ((bank_msb != 0)   &&	// Melody
						(bank_msb != 8)   &&	// Mega Voices, Articulation
						(bank_msb != 9)   &&	// Ensemble Part
						(bank_msb != 10)  &&	// Organ Flutes
						(bank_msb != 32)  &&    // Melody 9000 Pro Plugin
						(bank_msb != 47)  &&    // Drum Kits 9000 Pro Plugin
						(bank_msb != 62)  &&	// Custom Drumkit / Tyros 2
						(bank_msb != 63)  &&	// Custom Voices PSR-9000 / Tyros
						(bank_msb != 64)  &&	// XG SFX
						(bank_msb != 79)  &&    // Drum Kits 9000 Pro Plugin
						(bank_msb != 104) &&	// Melody
						(bank_msb != 109) &&	// Ensemble Part
						(bank_msb != 111) &&	// Custom Voices PSR-8000
						(bank_msb != 118) &&	// GS Drum Kits
						(bank_msb != 120) &&	// GM2 Drum Kits
						(bank_msb != 121) &&	// GM2 Melody
						(bank_msb != 126) &&	// Drum + SFX Kits
						(bank_msb != 127) )   	// Drum Kits
					{
						HP_ChangeController(mf,id,HP_BANK_SELECT_MSB,0,HP_NO_PERCENT);
					}

				}
				else
				{
					HP_ChangeController(mf,id,HP_BANK_SELECT_MSB,chan==9?127:0,HP_NO_PERCENT);
				}
				continue;
			}
		}

		if (!alien_voice)
		{
			// Bank Select LSB, only 0 allowed
			if (type == HP_BANK_SELECT_LSB)
			{
				int number, bank_lsb;
				HP_ReadController(mf,id,&time,&chan,&number,&bank_lsb);

				if ((bank_lsb!=0)&&!with_xg_on)
				{
					bool change = false;
					if(was_gs_on || with_gs_on)
					{
						change = true;
					}
					else
					{	// not GS and not XG change LSB only for chan 9
						if (chan==9) change = true;
					}
					if (change)	HP_ChangeController(mf,id,HP_BANK_SELECT_LSB,0,HP_NO_PERCENT);
				}
				continue;
			}
		}


		if (!alien_voice)
		{

			// Program Change
			if (type == HP_PROGRAM_CHANGE)
			{
				int number;
				HP_ReadProgramChange(mf,id,&time,&chan,&number);

				if ((chan==9)&&!with_xg_on)
				{
					int k;
					CString kit = "";
					int new_prg_no = 0; // initial Standard Kit 1
					for (k=1; k<22; k++) // don't ask for Standard Kit 1
					{
						if (number==kit_list[k].prg_ch)
						{
							kit = kit_list[k].kit;
							break;
						}
					}

					if (kit == "")
					{	// no kit found, use Standard Kit 1
						HP_ChangeProgram(mf,id,0);
					}
				}
				continue;
			}
		}

		// compute time of first notes (channel specific or the very first note)
		if (type == HP_NOTE)
		{
			// channel specific first note
			if (tofnote[chan]==-1)
			{
				tofnote[chan] = time;
			}
			// first note of all channel
			if (time_of_first_note == -1)
			{
				time_of_first_note = time;
			}
		}

		if (type == HP_MARKER)
		{
			char *text;
			HP_ReadMarker(mf,id,&time,&text);
			if ((time_of_first_note!=-1) && (time>time_of_first_note))
			{

				HP_Delete(text);
				continue;
			}
			if (last_marker_text != NULL)
			{
				HP_Delete(last_marker_text);
			}

			last_marker_text = text;
			last_marker_time = time;
			last_marker_id = id;
   		}
	}

	if (time_of_first_note==-1)
	{
		// Midifile without any notes
		time_of_first_note = last_event_time;
	}

/* Test
	{
		CString r;
		r.Format("Marker: last_marker_time %i, last_marker_text %s, last_marker_id %i, time_of_first_note %i",
				last_marker_time,last_marker_text,last_marker_id,time_of_first_note);
		MessageBox(r,NULL,MB_OK);
	}
*/

	if (last_marker_text != NULL)
	{
		HP_DeleteEvent(mf,last_marker_id); // Marker will be set later at first note measure
	}

	/* find msb/lsb/voice until first notes ***************************/

	// find the last time of all channel-specific first notes
	int last_time_of_first_note = -1;

	for (ch = 0; ch < 16; ch++)
	{
		if (tofnote[ch] > last_time_of_first_note)
		{
			last_time_of_first_note = tofnote[ch];
		}
	}

	int number;
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (time > last_time_of_first_note) break;
		if (chan == HP_NO_CHAN)        continue;
		if (tofnote[chan]==-1)         continue;	// empty channel
		if (time > tofnote[chan])      continue;

		// fill voice_list vl[chan] with last msb, lsb and voice
		if (type==HP_BANK_SELECT_MSB)
		{
			HP_ReadController(mf,id,&time,&chan,&number,&vl[chan].msb);
			HP_DeleteEvent(mf,id);
			continue;
		}

		if (type==HP_BANK_SELECT_LSB)
		{
			HP_ReadController(mf,id,&time,&chan,&number,&vl[chan].lsb);
			HP_DeleteEvent(mf,id);
			continue;
		}

		if (type==HP_PROGRAM_CHANGE)
		{
			HP_ReadProgramChange(mf,id,&time,&chan,&vl[chan].voice);
			vl[chan].time_last_voice = time;
			HP_DeleteEvent(mf,id);
			continue;
		}
	}

	/* delete needless Drum NRPN before last Drum Program Change **************/

	bool absolute;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (time > last_time_of_first_note) break;
		if (chan == HP_NO_CHAN)				continue;
		if (mlv_list[chan].melody)			continue;
		if (tofnote[chan]==-1)				continue;
		if (time > tofnote[chan])			break;
		if (time >= vl[chan].time_last_voice) break;
		if (type != HP_NRPN) continue;
		int number, value, msb_number;
		HP_ReadNRPN(mf,id,&time,&chan,&absolute,&number,&value);
		msb_number = number/128;
		if (((msb_number>=0x14)&&(msb_number<=0x35))||(msb_number==127))
		{
			HP_DeleteEvent(mf,id);
		}
	}

/* TTT Test Delete leading Pitchwheel and Chan Aftertouch before first note of each Channel ****/

	int time_first_note_chan[16];
	for (chan=0;chan<16; chan++)
	{
		time_first_note_chan[chan] = -1;
	}


	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_NOTE)
		{
			if (time_first_note_chan[chan]<0)
			{
				time_first_note_chan[chan]=time;
			}
		}
	}

/*
	for (chan=0;chan<16;chan++)
	{
		CString r;
		r.Format("chan %i, time %i", chan, time_first_note_chan[chan]);
		MessageBox(r);
	}
*/

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if ((type==HP_PITCH_WHEEL)||(type==HP_AFTERTOUCH)||(type==HP_CHANNEL_PRESSURE))
		{
			if (time < time_first_note_chan[chan])
			{
				HP_DeleteEvent(mf,id);
			}
		}
	}

	
/* End TTT Test Delete leading Pitchwheel and Chan Aftertouch befor first note of each Channel ****/
	
	
	/* find first takt (beat=0, tick=0) with notes ****************************/
	{
		int takt, beat, tick;
		HP_GetTaktBeatTick(mf,time_of_first_note,&takt, &beat, &tick);
		// get time of beat/takt = 0;
		HP_GetTimeFromTaktBeatTick(mf,takt,0,0,&time_of_first_relevant_takt);
	}

	/* change TimeSignature to 4/4, delete all TimeSignatures upto first note          */
	/* and store num and denum of the last before the notes in song_num and song-denum */
	/* Look for TimeSignature and delete                                               */

	int metronome_click,n32;
	int song_num = -1;
	int song_denum = -1;
	time = -1;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			break;
		}

		if (type == HP_TIME_SIGNATURE)
		{
			HP_ReadTimeSignature(mf,id,&time,&song_num,&song_denum,&metronome_click,&n32);
			HP_DeleteEvent(mf,id);
			// remember last time signature, will be inserted at the first song-takt
		}
	}

	/* insert mesasure 4/4 for the initial part *******************************/
	num = 4;
	denum = 4;
	HP_InsertTimeSignature(mf,0,num,denum);


	/* Delete all double controller in the whole midifile *********************/

	int ctrl_list[16][128];
	int k;

	for (i=0; i<16; i++)
	{
		for (k=0; k<128; k++)
		{
			ctrl_list[i][k]=-1;
		}
	}

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if ((type&HP_TYPE_MASK)==HP_CONTROLLER_TYPE)
		{
			HP_ReadController(mf,id,&time,&ch,&number,&value);

			// don't optimize RPN/NRPN
			if (is_rpn_nrpn_ctrl(number))
			{
				continue;
			}
/* TTT */
			// don't optimize SArt
			if (is_sart_ctrl(number))
			{
				continue;
			}
			
			// don't optimize Ctrl 0 and Ctrl 32
			if ((number==0)||(number==32))
			{
				continue;
			}

			if (ctrl_list[chan][number]==value)
			{
				HP_DeleteEvent(mf,id);
				no_controller_deleted++;
			}
			else
			{
				ctrl_list[chan][number] = value;
			}
		}
	}

	/* Delete all double Pitch Wheels in the whole midifile *******************/

	CString r;
	int last_pitchwheel_list[16];

	for (i=0; i<16; i++)
	{
		last_pitchwheel_list[i] = -1;
	}

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_PITCH_WHEEL)
		{
			HP_ReadPitchWheel(mf,id,&time,&ch,&value);
			if (last_pitchwheel_list[ch] == -1)
			{
				last_pitchwheel_list[ch] = value;
				continue;
			}

			if (value == last_pitchwheel_list[ch])
			{
				HP_DeleteEvent(mf,id);
				no_pitchwheels_deleted++;
			}

			last_pitchwheel_list[ch] = value;
		}
	}
	*no_pitch_wheels = no_pitchwheels_deleted;

	/* Delete all double RPN / NRPN in the whole midifile *********************/

	int* rpn_list[16];

	/* RPN */
	for (i=0; i<16;i++)
	{
		rpn_list[i] = new int[16384];
	}

	for (i=0; i<16; i++)
	{
		for (k=0; k<16384; k++)
		{
			(rpn_list[i])[k]=-1;
		}
	}

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_RPN)
		{
			HP_ReadRPN(mf,id,&time,&ch,&absolute, &number,&value);
			if(!absolute) continue;
			if ((rpn_list[chan])[number]==value)
			{
				HP_DeleteEvent(mf,id);
				no_controller_deleted++;
			}
			else
			{
				(rpn_list[chan])[number] = value;
			}
		}
	}

	/* NRPN */

	for (i=0; i<16; i++)
	{
		for (k=0; k<16384; k++)
		{
			(rpn_list[i])[k]=-1;
		}
	}

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_NRPN)
		{
			HP_ReadNRPN(mf,id,&time,&ch,&absolute, &number,&value);
			if(!absolute) continue;
			if ((rpn_list[chan])[number]==value)
			{
				HP_DeleteEvent(mf,id);
				no_controller_deleted++;
			}
			else
			{
				(rpn_list[chan])[number] = value;
			}
		}
	}

	for (i=0; i<16; i++)
	{
		delete[] rpn_list[i];
	}


	/* delete unneeded controller before notes ********************************/

	for (i=0; i<16; i++)
	{
		for (k=0; k<128; k++)
		{
			ctrl_list[i][k]=-1;
		}
	}


	// note all controller before notes and delete these
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (time > last_time_of_first_note) break;
		if (chan == HP_NO_CHAN)        continue;
		if (tofnote[chan]==-1)         continue;	// empty channel
		if (time > tofnote[chan])      continue;

		if ((type&HP_TYPE_MASK)==HP_CONTROLLER_TYPE)
		{
			int value;
			HP_ReadController(mf,id,&time,&chan,&number,&value);

			// no RPN/NRPN-type
			if (is_rpn_nrpn_ctrl(number)) continue;
			
			// no SArt-type
			if (is_sart_ctrl(number)) continue;

			ctrl_list[chan][number] = value;
			HP_DeleteEvent(mf,id);
		}
	}

	// compute no_notes[chan] again:

	update_no_notes(no_notes);

	/* insert controller with defaults for ***********************************/
	// 7: MainVolume (100), 10: Panorama (64), 11: Expression (127)
	// 71: Harmonic Content (64), 72: Release Time (64), 73: Attack Time (64)
	// 74: Brightness (64), 91: Reverb (40), 93: Chorus (0), 94: Variation (0)

	for (ch=0; ch < 16; ch++)
	{
		if (no_notes[ch]==0) continue;	// empty channel

		if (ctrl_list[ch][7]==-1)
		{
			ctrl_list[ch][7]= 100; // Main Volume default 100
		}
		if (ctrl_list[ch][10]==-1)
		{
			ctrl_list[ch][10]= 64; // Panorama default 64
		}
		if (ctrl_list[ch][11]==-1)
		{
			ctrl_list[ch][11]= 127; // Expression default 127
		}
		if (ctrl_list[ch][71]==-1)
		{
			ctrl_list[ch][71]= 64; // Harmonic Content default 64
		}
		if (ctrl_list[ch][72]==-1)
		{
			ctrl_list[ch][72]= 64; // Release Time default 64
		}
		if (ctrl_list[ch][73]==-1)
		{
			ctrl_list[ch][73]= 64; // Attack Time default 64
		}
		if (ctrl_list[ch][74]==-1)
		{
			ctrl_list[ch][74]= 64; // Brightness default 64
		}
		if (ctrl_list[ch][91]==-1)
		{
			ctrl_list[ch][91]= 40; // Reverb default 40
		}
		if (ctrl_list[ch][93]==-1)
		{
			ctrl_list[ch][93]= 0; // Chorus default 0
		}
		if (ctrl_list[ch][94]==-1)
		{
			ctrl_list[ch][94]= 0; // Variation default 0
		}
	}

	/*******************************************************************************/
	/* insert bank and voice and other controller for all channels, if needed.     */
	/* The events are inserted at same times, but splitted to different times later*/
	/*******************************************************************************/

	for (ch=0; ch<16; ch++)
	{
		if (tofnote[ch]==-1) continue;	// empty channel

		int mlv_time = tofnote[ch]>0?tofnote[ch]:0;

		HP_SetFirst(mf);

		int vn = vl[ch].voice!=-1?vl[ch].voice:0;

		HP_InsertProgramChange(mf,mlv_time,ch,vn);

		mlv_list[ch].voice = vn;
		vl[ch].voice = vn;

		int lsbn = vl[ch].lsb!=-1?vl[ch].lsb:0;

		HP_InsertController(mf,mlv_time,ch,HP_BANK_SELECT_LSB,lsbn);
		vl[ch].lsb = lsbn;
		mlv_list[ch].lsb = lsbn;

		int msbn = vl[ch].msb!=-1?vl[ch].msb:(ch!=9?0:127);

		HP_InsertController(mf,mlv_time,ch,HP_BANK_SELECT_MSB,msbn);
		mlv_list[ch].msb = msbn;
		vl[ch].msb = msbn;

		// insert controller from ctrl-list

		for (k=127; k>=0; k--)
		{
			value = ctrl_list[ch][k];
			if (value == -1) continue;
			HP_InsertController(mf,mlv_time,ch,HP_CONTROLLER_TYPE,value,k);
		}
	}

	/*******************************************************************************/
	/* insert Quickstart event, if needed.                                         */
	/*******************************************************************************/

	bool is_quickstart = false;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_QUICK_START)
		{
			is_quickstart = true;
			break;
		}
	}

	if (!is_quickstart)
	{
		// insert quickstart
		unsigned char data_qs[] = {0xff,0x7f, 0x06, 0x43,0x73,0x0a,0x00,0x04,0x01};
		HP_InsertQuickStart(mf, 0 ,data_qs,9);
		is_quickstart = true;
	}


    /***************************************************************/
	/* Sort all events before first notes in another session mf1   */
	/***************************************************************/

	char* text;
	bool found;

	HP_MIDIFILE_MODULE* mf1; // hp midifile handle  new start-events
	mf1 = HP_Init();
	HP_ChangePPQN(mf1,ppqn);	// use original ppqn

	HP_SetFirst(mf,HP_LAST);	// insert one after another
	HP_SetFirst(mf1,HP_LAST);	// insert one after another

	int new_time = 0;           // actual time to insert event in mf1

	/* Look for SongName and insert ****************************/

	time = -1;
	found = false;
	HP_Rewind(mf);
	char* song_trackname;
	bool song_trackname_found = false;

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (time > time_of_first_note) break;

		if (type == HP_SONG_TRACK_NAME)
		{
			song_trackname_found = true;
			HP_ReadSongTrackName(mf,id,&time,&song_trackname);
			HP_DeleteEvent(mf, id);
			break;
		}
	}

	char* ps;
	if (song_trackname_found)
	{
		if (!fill_sequ_track)
		{
			HP_InsertSongTrackName(mf1,song_trackname);
		}
		HP_Delete(song_trackname);
	}
	if (fill_sequ_track)
	{
		GlobalUtilities::convert_CString_to_cstring(&ps,proposed_songname);
		HP_InsertSongTrackName(mf1,ps);
		delete[] ps;
	}

	with_songname = true;

	/* Look for Instrument events and insert ****************************/

	time = -1;
	char* instrument_text;

	HP_Rewind(mf);

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (time > time_of_first_note) break;

		if (type == HP_INSTRUMENT)
		{
			HP_ReadInstrument(mf,id,&time,&instrument_text);
			HP_DeleteEvent(mf, id);
			HP_InsertInstrument(mf1,new_time, instrument_text);
			HP_Delete(instrument_text);
		}
	}

	/* Look for Copyright and insert ****************************/

	time = -1;
	found = false;
	HP_Rewind(mf);

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (time > time_of_first_note) break;

		if (type == HP_COPYRIGHT)
		{
			HP_ReadCopyright(mf,id,&time,&text);
			found = true;
			HP_DeleteEvent(mf, id);
			break;
		}
	}

	if(found)
	{
		HP_InsertCopyright(mf1,new_time,text);
		HP_Delete(text);
	}

	// Default: No Copyright

	/* Look for SMPTE Offset and insert ****************************/

	time = -1;
	found = false;
	HP_Rewind(mf);
    int hr, mn, se, fr, ff;

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (time > time_of_first_note) break;
		if (type == HP_SMPTE_OFFSET)
		{
			HP_ReadSmpteOffset(mf,id,&hr,&mn,&se,&fr,&ff);
			found = true;
			HP_DeleteEvent(mf, id);
			break;
		}
	}

	if(found)
	{
		HP_InsertSmpteOffset(mf1,hr,mn,se,fr,ff);
	}

	// Default: No SMPTE Offset


	/* Look for XF-Meta **************************************************/

	HP_Rewind(mf);

	unsigned char* event_data;
	int event_length;

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (time >= time_of_first_note) break;

		if ((type == HP_LYRIC) && (time==0) && (time_of_first_note>0))
		{	// S&M files often have isolated lyrics on 1:1:0
			HP_ReadLyric(mf,id,&time,&text);
			HP_InsertLyric(mf1,0,text);
			HP_DeleteEvent(mf,id);
			HP_Delete(text);
			continue;
		}

		if (type == HP_SCORE_START_BAR)
		{
			HP_ReadScoreStartBar(mf,id,&time,&event_data,&event_length);
			HP_InsertScoreStartBar(mf1,new_time,event_data,event_length);
			HP_Delete(event_data);
			HP_DeleteEvent(mf,id);
			continue;
		}

		if (type == HP_QUICK_START)
		{
			HP_ReadQuickStart(mf,id,&time,&event_data,&event_length);
			HP_InsertQuickStart(mf1,new_time,event_data,event_length);
			HP_Delete(event_data);
			HP_DeleteEvent(mf,id);
			continue;
		}

		if (type == HP_SCORE_LAYOUT)
		{
			HP_ReadScoreLayout(mf,id,&time,&event_data,&event_length);
			HP_InsertScoreLayout(mf1,new_time,event_data,event_length);
			HP_Delete(event_data);
			HP_DeleteEvent(mf,id);
			continue;
		}

		if (type == HP_KEYBOARD_VOICE)
		{
			HP_ReadKeyboardVoice(mf,id,&time,&event_data,&event_length);
			HP_InsertKeyboardVoice(mf1,new_time,event_data,event_length);
			HP_Delete(event_data);
			HP_DeleteEvent(mf,id);
			continue;
		}

		if (type == HP_XF_VERSION_ID)
		{
			HP_ReadXFVersionID(mf,id,&time,&event_data,&event_length);
			HP_InsertXFVersionID(mf1,new_time,event_data,event_length);
			HP_Delete(event_data);
			HP_DeleteEvent(mf,id);
			continue;
		}

		if (type == HP_REHEARSAL_MARK)
		{
			HP_ReadRehearsalMark(mf,id,&time,&event_data,&event_length);
			HP_InsertRehearsalMark(mf1,new_time,event_data,event_length);
			HP_Delete(event_data);
			HP_DeleteEvent(mf,id);
			continue;
		}

		if (type == HP_PHRASE_MARK)
		{
			HP_ReadPhraseMark (mf,id,&time,&event_data,&event_length);
			HP_InsertPhraseMark (mf1,new_time,event_data,event_length);
			HP_Delete(event_data);
			HP_DeleteEvent(mf,id);
			continue;
		}

		if (type == HP_GUIDE_TRACK_FLAG)
		{
			HP_ReadGuideTrackFlag(mf,id,&time,&event_data,&event_length);
			HP_InsertGuideTrackFlag(mf1,new_time,event_data,event_length);
			HP_Delete(event_data);
			HP_DeleteEvent(mf,id);
			continue;
		}

		if (type == HP_GUITAR_INFORMATION_FLAG)
		{
			HP_ReadGuitarInformationFlag(mf,id,&time,&event_data,&event_length);
			HP_InsertGuitarInformationFlag(mf1,new_time,event_data,event_length);
			HP_Delete(event_data);
			HP_DeleteEvent(mf,id);
			continue;
		}

		if (type == HP_LYRICS_BITMAP)
		{
			HP_ReadLyricsBitmap(mf,id,&time,&event_data,&event_length);
			HP_InsertLyricsBitmap(mf1,new_time,event_data,event_length);
			HP_Delete(event_data);
			HP_DeleteEvent(mf,id);
			continue;
		}

		if (type == HP_OTHER_YAMAHA_META)
		{
			HP_ReadOtherYamahaMeta(mf,id,&time,&event_data,&event_length);
			HP_InsertOtherYamahaMeta(mf1,new_time,event_data,event_length);
			HP_Delete(event_data);
			HP_DeleteEvent(mf,id);
			continue;
		}

		if (type == HP_CUE_POINT)
		{
			HP_ReadCuePoint(mf,id,&time,&text);
			HP_InsertCuePoint(mf1,new_time,text);
			HP_Delete(text);
			HP_DeleteEvent(mf,id);
			continue;
		}
	}

	/* Look for all other text- and marker-events and insert ***********************/

	time = -1;
	found = false;
	HP_Rewind(mf);

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (time > time_of_first_note) break;
		if (type == HP_TEXT)
		{
			HP_ReadText(mf,id,&time,&text);
			HP_InsertText(mf1,new_time,text);
			HP_Delete(text);
			HP_DeleteEvent(mf, id);
			continue;
		}

		if (type == HP_MARKER)
		{   // insert at the original time
			HP_ReadMarker(mf,id,&time,&text);
			HP_InsertMarker(mf1,time,text);
			HP_Delete(text);
			HP_DeleteEvent(mf, id);
			continue;
		}
	}

	/* Look for TimeSignature and delete ********************************/

	time = -1;
	found = false;
	HP_Rewind(mf);

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (time > time_of_first_note) break;

		if (type == HP_TIME_SIGNATURE)
		{
			HP_ReadTimeSignature(mf,id,&time,&num,&denum,&metronome_click,&n32);
			found = true;
			HP_DeleteEvent(mf,id);
			// take last time signature, here only 4/4 possible
		}
	}

	if(found)
	{
		HP_InsertTimeSignature(mf1,new_time,num,denum);
	}
	else
	{	// insert 4/4
		num = 4;
		denum = 4;
		HP_InsertTimeSignature(mf1,new_time,num,denum);
	}

	/* Look for KeySignature and insert ********************************/

	char* key;

	time = -1;
	found = false;
	HP_Rewind(mf);

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (time > time_of_first_note) break;
		if (type == HP_KEY_SIGNATURE)
		{
			HP_ReadKeySignature(mf,id,&time,&key);
			found = true;
			HP_DeleteEvent(mf,id);
			// take last key signature
		}
	}

	if(found)
	{
		HP_InsertKeySignature(mf1,new_time,key);
		first_key = key;
		HP_Delete(key);
	}
	else
	{	// insert C dur
		HP_InsertKeySignature(mf1,0,"C");
		first_key = "C";
	}

	/* Look for tempo and insert ***************************************/

	double bpm_double = -1.0;
	int cps;

	HP_Rewind(mf);

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (time > time_of_first_note) break;
		if (type == HP_TEMPO)
		{
			HP_ReadTempo(mf,id,&time,&bpm_double,&cps);
			HP_DeleteEvent(mf,id);
		}
	}

	if(bpm_double != -1.0)
	{
		HP_InsertTempo(mf1,new_time,bpm_double);
	}
	else
	{	// insert Tempo 100
		HP_InsertTempo(mf1,new_time,100);
	}

	/* Insert GM On and XG On ********************************************/

	HP_InsertMIDIPort(mf1,new_time,0,0);
	HP_InsertSysEx(mf1,new_time,GlobalUtilities::gm_on_data);
	new_time += 200;
	HP_InsertMIDIPort(mf1,new_time,0,0);
	HP_InsertSysEx(mf1,new_time,GlobalUtilities::xg_on_data);
	new_time += 50;
	HP_InsertMIDIPort(mf1,new_time,0,0);
	if (alien_sysex && with_gs_on)
	{
		new_time += 50;
		HP_InsertSysEx(mf1,new_time,GlobalUtilities::turn_tg300b_on_data);
		HP_InsertMIDIPort(mf1,new_time,0,0);
	}

	// Other YAMAHA SysEx in source are posited at 1:2 ff

	// Posit on 1:2:0

	new_time =
		denum==4? ppqn:
	denum==3? ppqn*3/2:
	denum==6? ppqn*3/4:
	denum==8? ppqn/2:
	denum==2? ppqn*2:ppqn;

	/* Look for Part Mode SysEx ******************************************/

	HP_Rewind(mf);

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		unsigned char* data;
		if (time > time_of_first_note) break;
		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf,id, &time, &data, &length);
		if ((data[2]==0x10)&&(data[3]==0x4c)&&(data[4]==0x70))
		{	// Assign 9000pro Plugin Board
			HP_DeleteEvent(mf,id);
			HP_InsertSysEx(mf1, new_time, data);
			HP_Delete(data);
			new_time +=150;
			continue;
		}

		if (!GlobalUtilities::is_part_mode_sysex(data))
		{
			HP_Delete(data);
			continue;
		}
		HP_DeleteEvent(mf,id);
		HP_InsertSysEx(mf1, new_time, data);
		HP_Delete(data);
		new_time +=5;
	}

	/********************************************************************
	**   insert formerly deleted SysExes
	**   lyrics_part_score_on, chord_part_score_on, score_representation_medium
	********************************************************************/
/*
	HP_InsertSysEx(mf1, new_time, GlobalUtilities::lyrics_part_score_on_data);
	new_time +=5;
	HP_InsertSysEx(mf1, new_time, GlobalUtilities::chord_part_score_on_data);
	new_time +=5;
*/
	/* Controller Events *************************************************/

	int voice;

	for (ch=0; ch<16; ch++)
	{
		if (no_notes[ch]==0) continue;

		// Insert Voice
		time = -1;
		HP_Rewind(mf);
		while (true)
		{
			if (HP_ReadEvent(mf,&id,&chan,&time,&type)!=HP_ERR_NONE) break;
			if (time > tofnote[ch]) break;
			if (chan == ch)
			{
				if ((type == HP_BANK_SELECT_MSB)||(type == HP_BANK_SELECT_LSB))
				{
					HP_ReadController(mf,id,&time,&chan,&number,&value);
					HP_InsertController(mf1,new_time,chan,type,value,number);
					HP_DeleteEvent(mf,id);
					new_time++;
				}
				if (type == HP_PROGRAM_CHANGE)
				{
					HP_ReadProgramChange(mf,id,&time,&chan,&voice);
					HP_DeleteEvent(mf,id);
					HP_InsertProgramChange(mf1,new_time,ch,voice);
					new_time++;
				}
			}
		}

		// Insert other Controller but no RPN and NRPN
		time = -1;
		HP_Rewind(mf);
		while (true)
		{	if (HP_ReadEvent(mf,&id,&chan,&time,&type)!=HP_ERR_NONE) break;
			if (time > tofnote[ch]) break;
			if (chan == ch)
			{
			   if ((type&HP_TYPE_MASK)==HP_CONTROLLER_TYPE)
			   {
 				   if (type==HP_RPN)
				   {
					   continue;
					}
					if (type==HP_NRPN)
					{
					   continue;
					}
					// standard controller, but not Send Level Controller 91,93,94

					HP_ReadController(mf,id,&time,&chan,&number,&value);

					if ((number!=91)&&(number!=93)&&(number!=94))
					{	// insert 91, 93 and 94 after SysEx
						// don't insert parts of RPN/NRPN
						if ( !is_rpn_nrpn_ctrl(number))
						{
						   HP_InsertController(mf1,new_time,chan,type,value,number);
						   new_time++;
						}
						HP_DeleteEvent(mf,id);
					}
			   } // end controller-type
			} // end chan ch11
		} // end other controller

		// insert RPN and NRPN
		time = -1;
		HP_Rewind(mf);
		while (true)
		{	// insert RPN and NRPN
			if (HP_ReadEvent(mf,&id,&chan,&time,&type)!=HP_ERR_NONE) break;
			if (time > tofnote[ch]) break;
			if (chan == ch)
			{
			   if (type==HP_RPN)
			   {
				   HP_ReadRPN(mf,id,&time,&chan,&absolute,&number,&value);
				   HP_DeleteEvent(mf,id);
				   if (absolute)
				   {
					   HP_InsertRPNAbsolute(mf1, new_time, chan, number,value);
				   }
				   else
				   {
					   HP_InsertRPNRelative(mf1, new_time, chan, number,value);
				   }
				   new_time++;
				   continue;
				}
				if (type==HP_NRPN)
				{
				   HP_ReadNRPN(mf,id,&time,&chan,&absolute,&number,&value);
				   HP_DeleteEvent(mf,id);
				   if (absolute)
				   {
					   HP_InsertNRPNAbsolute(mf1, new_time, chan, number,value);
				   }
				   else
				   {
					   HP_InsertNRPNRelative(mf1, new_time, chan, number,value);
				   }
				   new_time++;
				   continue;
				}
			}
		} // end RPN and NRPN
	}

	/* Look for Pitch Wheel in mf ***************************************/
	time = -1;
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (time > time_of_first_note) break;
		if (type==HP_PITCH_WHEEL)
		{
			HP_ReadPitchWheel(mf,id,&time,&chan,&value);
			HP_DeleteEvent(mf,id);
			HP_InsertPitchWheel(mf1, new_time,chan,value);
			new_time++;
		}
	}

	/* Look for YAMAHA SysEx ***************************************/

	unsigned char *data;

	time = -1;
	found = false;
	HP_Rewind(mf);

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (time > time_of_first_note) break;
		if (type == HP_SYSEX)
		{
			HP_ReadSysex(mf,id,&time,&data,&length);

			// Insert Bulk Dump SysEx later
			if ((data[1]==0x43)&&((data[2]&0xf0)==0))
			{
				HP_Delete(data);
				continue;
			}

			// only XG SysEx allowed
			HP_DeleteEvent(mf,id);

			if ((data[1]==0x43)||(data[1]==0x7F)||(alien_sysex==1))
			{
				HP_InsertSysEx(mf1,new_time,data);
				if (length > 20)
				{
					new_time +=5;
					HP_InsertMIDIPort(mf1,new_time,0,0);
				}
				HP_Delete(data);
				new_time+=5;
				continue;
			}

			/* Look for Score Chord SysEx in mf 
				F0 43 73 01 50 12 00 02 7F F7        ; Lyrics Part Score ON
				F0 43 73 01 50 12 00 03 7F F7        ; Chord Part Score ON
				F0 43 73 01 50 12 00 05 01 F7        ; Score Representation medium
			   and insert into mf1 if needed.
			*/

			HP_Delete(data);
		}
	}

	/* Look for Controller 91, 93 and 94 ***************************************/
	for (ch=0; ch<16; ch++)
	   {
		if (no_notes[ch]==0) continue;

		time = -1;
		HP_Rewind(mf);

		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (time > tofnote[ch]) break;
			if (chan == ch)
			{
				if ((type&HP_TYPE_MASK)==HP_CONTROLLER_TYPE)
				{
					HP_ReadController(mf,id,&time,&chan,&number,&value);
					if ((number==91)||(number==93)||(number==94))
					{
						HP_DeleteEvent(mf,id);
						HP_InsertController(mf1,new_time,chan,type,value,number);
						new_time++;
					}
					continue;
				}
			}
		}
	}

   /* Look for remainding lyrics ***************************************/
   time = -1;
   HP_Rewind(mf);
   while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
   {
	   if (time >= time_of_first_relevant_takt) break;
	   if (type==HP_LYRIC)
	   {
		   HP_ReadLyric(mf,id,&time,&text);
		   HP_DeleteEvent(mf,id);
		   HP_InsertLyric(mf1,time,text);
		   HP_Delete(text);
	   }
   }

   /* Look for remainding events in mf *********************************/

   time = -1;
   HP_Rewind(mf);
   while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
   {
	   if (time >= time_of_first_relevant_takt) break;
	   if (type==HP_NOTE) break;

	   // Look for remainding Bulk Dump
	   if (type == HP_SYSEX)
	   {
			HP_ReadSysex(mf,id,&time,&data,&length);

			// Insert Bulk Dump SysEx later
			if ((data[1]==0x43)&&((data[2]&0xf0)==0))
			{
			   HP_InsertSysEx(mf1,new_time,data);
			   new_time += 10;
			   if (length > 20)
			   {
				   HP_InsertMIDIPort(mf1,new_time,0,0);
				   new_time +=5;
			   }
			}
			else
			{
				if (alien_sysex && data[1]!=0x43)
				{
					HP_InsertSysEx(mf1,new_time,data);
					new_time += 10;
				}
			}
			HP_Delete(data);
	   }

	   HP_DeleteEvent(mf,id);
   }


   /***************************************************************/
   /* Shift play-events of session mf                             */
   /***************************************************************/

   int ticks_in_takt =
		denum==4? num*ppqn:
		denum==8? num*ppqn/2:
		denum==2? num*ppqn*2:
		denum==3? num*ppqn*3/2:
		denum==6? num*ppqn*3/4: ppqn*num;

   int shift_ticks;

   int time_of_new_first_relevant_takt = time_of_first_relevant_takt;

   // 1. Shift play_events to takt 1

   shift_ticks = ticks_in_takt - time_of_new_first_relevant_takt;
   if (shift_ticks !=0)
   {
	   HP_Select(mf);
	   HP_ShiftSelected(mf,shift_ticks);
	   time_of_new_first_relevant_takt = ticks_in_takt;
	   HP_Deselect(mf);
   }

   // 2. Shift play_events to the next takt behind new_time

   if (new_time < time_of_new_first_relevant_takt)
   {
	   while(new_time  < time_of_new_first_relevant_takt)
	   {
		   time_of_new_first_relevant_takt-=ticks_in_takt;
	   }
	   time_of_new_first_relevant_takt+=ticks_in_takt;
   }

   else

   {
	   if (new_time > time_of_new_first_relevant_takt)
	   {
		   while (new_time > time_of_new_first_relevant_takt)
		   {
			   time_of_new_first_relevant_takt+=ticks_in_takt;
		   }
	   }
   }

   shift_ticks = time_of_new_first_relevant_takt-ticks_in_takt;

   if (shift_ticks != 0)
   {
	   HP_Select(mf);
	   HP_ShiftSelected(mf,shift_ticks);
	   HP_Deselect(mf);
   }

   // insert TimeSignature of song
   if ((song_num != -1) && ((num != song_num) || (denum != song_denum)))
   {
	   HP_SetFirst(mf);
	   HP_InsertTimeSignature (mf,time_of_new_first_relevant_takt,song_num,song_denum);
   }

   // insert last Marker found before notes into the first relevant measure
   if (last_marker_text != NULL)
   {
	   HP_InsertMarker(mf,time_of_new_first_relevant_takt,last_marker_text);
	   HP_Delete(last_marker_text);
   }

   /***************************************************************/
   /* Merge mf1 into mf                                           */
   /***************************************************************/

   HP_Select(mf1);
   HP_Copy(mf1);
   HP_Paste(mf,0,HP_NO_DELETE,HP_ALL_EVENTS);
   HP_Deselect(mf1);
   HP_Free(mf1);

   /*************************************************************************/
   /* re-compute tofnote: channel specific time of first note                                                 */
   /*************************************************************************/

   for (ch=0; ch<16; ch++)
   {
	   tofnote[ch] = -1;
   }

   HP_Rewind(mf);
   while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
   {
	   if (type == HP_NOTE)
	   {
		   // channel specific first note
		   if (tofnote[chan]==-1)
		   {
			   tofnote[chan] = time;
		   }
	   }
   }


   /*************************************************************************/
   /*
   /*Insert standard voice definitions in the region of notes
   /*All Patch Changes will be preceded by Ctrl. 0 and 32 with distance of 1 tick
   /*
   /*************************************************************************/

   // Initialize vl to GM

   for (chan=0; chan<16; chan++)
   {
	   vl[chan].msb = 0;
	   vl[chan].lsb = 0;
	   vl[chan].voice = 0;
   }

   // Fill vl with the actual voice definitions of the first notes 	
   
   HP_Rewind(mf);
   while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
   {
	   if (chan == HP_NO_CHAN)
	   {
		   continue;
	   }

	   if (chan < 0 || chan > 15)
	   {
		   MessageBox("not correct chan");
		   continue;
	   }

	   if (time > tofnote[chan])
	   {
		   continue;
	   }

   	   if (type == HP_BANK_SELECT_MSB)
	   {
		   HP_ReadController(mf,id,&time,&chan,&number,&value);
		   vl[chan].msb = value;
	   }

   	   if (type == HP_BANK_SELECT_LSB)
	   {
		   HP_ReadController(mf,id,&time,&chan,&number,&value);
		   vl[chan].lsb = value;
	   }

	   if (type == HP_PROGRAM_CHANGE)
	   {
		   HP_ReadProgramChange(mf,id,&time,&chan,&voice);
		   vl[chan].voice = voice;
	   }
   }
/*
   for (chan=0; chan<16; chan++)
   {
      r.Format("init-vl: chan %i, msb %i, lsb %i, voice %i",
		  chan, vl[chan].msb, vl[chan].lsb, vl[chan].voice);
      MessageBox(r);
   }
*/
   // Delete old and create new Ctrl. 0/32 in note area
   // 

   HP_Rewind(mf);
   while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
   {
	   int changed = 0;

	   if (chan == HP_NO_CHAN)
	   {
		   continue;
	   }
	   if (time <= tofnote[chan])
	   {
		   continue;
	   }
  	   if (type == HP_BANK_SELECT_MSB)
	   {
		   HP_ReadController(mf,id,&time,&chan,&number,&value);
		   vl[chan].msb = value;
		   HP_DeleteEvent(mf,id);
		   changed = 1;
	   }
	   else
   	   if (type == HP_BANK_SELECT_LSB)
	   {
		   HP_ReadController(mf,id,&time,&chan,&number,&value);
		   vl[chan].lsb = value;
		   HP_DeleteEvent(mf,id);
		   changed = 2;
	   }
	   else
	   if (type == HP_PROGRAM_CHANGE)
	   {
		   HP_ReadProgramChange(mf,id,&time,&chan,&voice);
		   vl[chan].voice = voice;
		   int new_time_lsb = time-1;
		   int new_time_msb = time-2;
		   if ((new_time_lsb <= tofnote[chan]) || (new_time_msb <= tofnote[chan]))
		   {
			   new_time_msb = time;
			   new_time_lsb = time;
		   }
		   HP_InsertController(mf,new_time_msb,chan,HP_BANK_SELECT_MSB,vl[chan].msb); 
		   HP_InsertController(mf,new_time_lsb,chan,HP_BANK_SELECT_LSB,vl[chan].lsb); 
		   changed = 3;
	   }
   }


   /*************************************************************************/
   /* Last actions
   /*************************************************************************/

    // vh_channel_sysex_exist[chan]belegen
   	for (chan=0; chan<16; chan++)
	{
		vh_channel_sysex_exist[chan] = false;
	}

	chan = -1;
	
	HP_Rewind(mf);
	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if (type == HP_SYSEX)
		{
			HP_ReadSysex(mf,id,&time,&data,&length);
			int vh_channel = GlobalUtilities::is_vh_channel_sysex(data,length);
			if (vh_channel >= 0)
			{
				vh_channel_sysex_exist[vh_channel] = true;
			}
			HP_Delete(data);
		}
	}
/*
	for (chan =0; chan < 16; chan++)
	{
		if (vh_channel_sysex_exist[chan])
		{
 			CString r;
			r.Format("chan %i ist VH-Channel",chan);
			MessageBox (r);
		}
	}
*/
	//  delete midievents of vh-channels if wanted

	if (vh_events_delete)
	{
		int v_c;
		for (v_c=0; v_c<16; v_c++)
		{
			if (!vh_channel[v_c])
			{
				continue;
			}
			HP_Rewind(mf);
			while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
			{
				if (chan != v_c)
				{
					continue;
				}
				if (type!=HP_NOTE)
				{
					HP_DeleteEvent(mf,id);
				}
			}
		}
	}
	
   // remove double lyrics from shift
   HP_Rewind(mf);
   int last_lyric_time = -1;
   while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
   {
	   if (type == HP_LYRIC)
	   {
		   if (last_lyric_time == time)
		   {
			   HP_DeleteEvent(mf,id);
			   continue;
		   }
		   last_lyric_time = time;
	   }
   }

   // remove the notes from channels with not_delete_empty_channel == true
   HP_Rewind(mf);
   if (!delete_empty_chan)
   {
		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (chan == HP_NO_CHAN) continue;
			if (!not_delete_empty_channel[chan])
			{
				continue;
			}
			if (type == HP_NOTE)
			{
				HP_DeleteEvent(mf,id);
			}
		}
   }

   update_no_notes(no_notes);
   
   int no_vh_chan = find_vh_channel();
	// only after update_mlv_list
   update_lyriclist();
   fill_patchname_list();
   HP_ChangeTempo(mf,HP_ALL_EVENTS,100.0,HP_PERCENT);
   update_takt_bar_time_list();

   with_gm_on = true;
   with_xg_on = true;
   with_gs_on = false;
   source_changed = true;

   HP_Deselect(mf);

   return no_controller_deleted;
}

//**************************************************************************
//*
//*		Convert all types of midifiles to GM
//*
//**************************************************************************

bool HPMF_Interface::eval_gm_convert()
{
//  MessageBox("eval_gm_convert");

	int no_double_notes, no_pitch_wheels;
	int chan;
	int id, time, type;
	int length;
	unsigned char *data;
	int note, velocity;
	int number, value;
	
	// if there exist a non empty drum channel drum_chan |= 9 and channel 9 without notes
	// cut and copy channel to channel 9

	if (no_notes[9]==0)
	{
		// look for a drum channel
		int drum_chan = -1;
		for (chan=0; chan<16; chan++)
		{
			if (!mlv_list[chan].melody && (no_notes[chan]>0))
			{
				drum_chan = chan;
				break;
			}
		}
		if (drum_chan != -1)
		{
			// cut and paste notes of drum_chan to channel 9
			HP_Rewind(mf);
			while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
			{
				if (chan==drum_chan)
				{
					if (type==HP_NOTE)
					{
						HP_ReadNote(mf,id,&time,&chan,&note,&velocity,&length);
						HP_DeleteEvent(mf,id);
						HP_InsertNote(mf,time,length,note,9,velocity);
					}
					else if (type==HP_CONTROLLER_TYPE)
					{
						HP_ReadController(mf,id,&time,&chan,&number,&value);
						HP_DeleteEvent(mf,id);
						HP_InsertController(mf,time,9,type,value,number);
					}
					else if (type==HP_PITCH_WHEEL)
					{
						HP_ReadPitchWheel(mf,id,&time,&chan,&value);
						HP_DeleteEvent(mf,id);
						HP_InsertPitchWheel(mf,time,9,value);
					}
					else
					{
						HP_DeleteEvent(mf,id);
					}
				}
			}
		}
	}

	// Optimize XG
	eval_xg_convert(&no_double_notes, &no_pitch_wheels);


	bool is_mega_sart = false;

	for (chan=0; chan<16; chan++)
	{
		if (mlv_list[chan].is_mega || mlv_list[chan].is_sart)
		{
			is_mega_sart = true;
			break;
		}
	}

	if (is_mega_sart)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,
			GlobalUtilities::get_resource_string(IDS_CONVERSION_NOT_POSSIBLE_META),"",MB_OK|MB_TASKMODAL);
		return false;
	}

	if (mlv_list[9].melody)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,
			GlobalUtilities::get_resource_string(IDS_CONVERSION_NOT_POSSIBLE_CH9),"",MB_OK|MB_TASKMODAL);
		return false;
	}


	// Look at all events

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
    {
		if (type == HP_SYSEX)
		{	// delete all SysEx except GM-On
			HP_ReadSysex(mf,id,&time,&data,&length);
			if (!GlobalUtilities::is_gm_on_sysex(data))
			{
				HP_DeleteEvent(mf,id);
			}
			HP_Delete(data);
			continue;
		}

		if ((type==HP_BANK_SELECT_MSB)||
			(type==HP_BANK_SELECT_LSB)||
			(type==HP_NRPN)||
			(type==HP_PORTAMENTO_CONTROL))
		{	// delete all bank controller 0, 32, 84 and NRPN
			HP_DeleteEvent(mf,id);
			continue;
		}

		if ((type==HP_NOTE)&&(!mlv_list[chan].melody)&&(chan!=9))
		{ // change note channel to 9
			HP_ReadNote(mf,id,&time,&chan,&note,&velocity,&length);
			HP_DeleteEvent(mf,id);
			HP_InsertNote(mf,time,length,note,9,velocity);
			continue;
		}

		if ((type==HP_CHORD_NAME) ||
			(type==HP_CHORD_VOICING_FOR_GUITAR) ||
			(type==HP_FINGERING_NUMBER) ||
			(type==HP_GUIDE_TRACK_FLAG) ||
			(type==HP_GUITAR_INFORMATION_FLAG) ||
			(type==HP_KEYBOARD_VOICE) ||
			(type==HP_LYRICS_BITMAP) ||
			(type==HP_MAX_PHRASE_MARK) ||
			(type==HP_OTHER_YAMAHA_META) ||
			(type==HP_PHRASE_MARK) ||
			(type==HP_REHEARSAL_MARK) ||
			(type==HP_SCORE_START_BAR) ||
			(type==HP_QUICK_START) ||
			(type==HP_SCORE_LAYOUT) ||
			(type==HP_CUE_POINT) ||
			(type==HP_TEXT) ||
			(type==HP_MIDI_PORT) ||
			(type==HP_XF_VERSION_ID))
		{   // delete all Yamaha meta events
			HP_DeleteEvent(mf,id);
			continue;
		}

		if ((chan==9)&&(type==HP_PROGRAM_CHANGE))
		{
			HP_DeleteEvent(mf,id);
			continue;
		}

	}

	with_gm_on = true;
	with_gs_on = false;
	with_xg_on = false;
	with_xfchords = false;

	// Delete all events of old drum channels /= 10 and
	// delete all events of SFX Kits (MSB = 126)
	bool is_sfx[16];

	for (chan=0; chan<16; chan++)
	{
		is_sfx[chan] = is_sfx_bank(mlv_list[chan].msb*128);
	}

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
    {
		if (chan == -1) continue;
		if ((!mlv_list[chan].melody && (chan!=9)) || is_sfx[chan])
		{
			HP_DeleteEvent(mf,id);
		}
	}

	for(chan=0; chan<16;chan++)
	{
		if ((!mlv_list[chan].melody && (chan!=9)) ||
			is_sfx[chan])
		{
			mute[chan] = true;
			mlv_list[chan].voice = -1;
			patchname[chan] = "";
			mlv_list[chan].voicename = "";
		}

		mlv_list[chan].msb = -1;
		mlv_list[chan].time_msb = -1;
		mlv_list[chan].lsb = -1;
		mlv_list[chan].time_lsb = -1;
		mlv_list[chan].time_voice = -1;
		mlv_list[chan].melody = chan==9?false:true;
		mlv_list[chan].is_sart = false;
		mlv_list[chan].bankname = "";
	}
	return true;
}

//**************************************************************************
//*
//*		exchange_drumsysex_to_nrpn
//*
//**************************************************************************

void HPMF_Interface::exchange_drumsysex_to_nrpn()
{
	if (drum_setup_convert==0) return;

	unsigned char setup1_part = 0x09;
	unsigned char setup2_part = 0xff; // default: all parts other than setup1-part


	// SysEx-format: f0 43 10 4c 30 <note> <sysex_type> <value> f7
	// NRPN-format: MSB = nrpn_msb, LSB = note, data_MSB = value, data_LSB = 0

	const int type_list_len = 12;
	const struct type_list_elem {int sysex_type; int nrpn_msb;} type_list[12] =
	{
		{0x00,0x18},
		{0x01,0x19},
		{0x02,0x1a},
		{0x04,0x1c},
		{0x05,0x1d},
		{0x06,0x1e},
		{0x07,0x1f},
		{0x0b,0x14},
		{0x0c,0x15},
		{0x0d,0x16},
		{0x0e,0x17},
		{0x0f,0x17}
	};

	int id, chan, time, type, length;
	unsigned char *data;
	unsigned char mp_part_mode_start[5] = {0xf0,0x43,0x10,0x4c,0x08};
	unsigned char drum_sysex_start0[5] = {0xf0,0x43,0x10,0x4c,0x30};
	unsigned char drum_sysex_start1[5] = {0xf0,0x43,0x10,0x4c,0x31};
	unsigned char sysex_type, note, value, setup_no;
	int i;

	// Look for Part Mode Drum Setup
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if (type == HP_SYSEX)
		{
			HP_ReadSysex(mf,id,&time,&data,&length);
			if (length != 9)
			{
				HP_Delete(data);
				continue;
			}

			if (!GlobalUtilities::compare_data(data,5,mp_part_mode_start,5)||(data[6] != 0x07))
			{
				HP_Delete(data);
				continue;
			}
			if ((data[7]!=0x02)&&(data[7]!=0x03))
			{
				HP_Delete(data);
				continue;
			}

			// Part Mode for Setup 1 or 2
			if (data[7]==0x02) setup1_part = data[5];
			if (data[7]==0x03) setup2_part = data[5];
			HP_Delete(data);
		}
	}


	HP_Rewind(mf);
	HP_SetFirst(mf, HP_LAST);

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if (type == HP_SYSEX)
		{
			HP_ReadSysex(mf,id,&time,&data,&length);
			if (length != 9)
			{
				HP_Delete(data);
				continue;
			}

			if (!GlobalUtilities::compare_data(data,5,drum_sysex_start0,5)&&
				!GlobalUtilities::compare_data(data,5,drum_sysex_start1,5)    )
			{
				HP_Delete(data);
				continue;
			}

			note = data[5];
			sysex_type = data[6];
			value = data[7];
			setup_no = data[4]&0x01;

			HP_Delete(data);

			for (i=0; i<type_list_len; i++)
			{	// look if nrpn possible
				unsigned char st = (unsigned char) (type_list[i]).sysex_type;
				if (st == sysex_type)
				{
					HP_DeleteEvent(mf,id);
					if ((setup_no==0)&&
						(mlv_list[setup1_part].msb!=-1)&&
						(mlv_list[setup1_part].lsb!=-1)&&(
						!mlv_list[setup1_part].melody)
					   )
					{ // setup_no 0: only chan setup1_part (default 9)
						HP_InsertNRPNAbsolute(mf,time, setup1_part,
							(type_list[i]).nrpn_msb*128+note,
							 value*128);
					}

					if (setup_no==1)
					{ // setup_no 1: all chan != setup1_part
						int ch;
						bool is_drums;

						for (ch=0; ch<16; ch++)
						{
							if (ch == setup1_part) continue;
							if ((setup2_part!=0xff)&&(setup2_part!=ch)) continue;
							is_drums = (mlv_list[ch].msb!=-1)&&(mlv_list[ch].lsb!=-1)&&(!mlv_list[ch].melody);
							if (is_drums)
							{

								HP_InsertNRPNAbsolute(mf,time, ch,
									(type_list[i]).nrpn_msb*128+note,
									value*128);
							}
						}
					}
					break;
				}
			}	// end look if nrpn possible
		} // end sysex
	} // end scan midifile
}


//**************************************************************************
//*
//*		eval_songname_composer_lyricist
//*
//**************************************************************************

void HPMF_Interface::eval_songname_composer_lyricist(CString new_songname, CString new_composer, CString new_lyricist)
{
	int id, chan, time, type;
	char *new_songname_char;
	char *xfln_text;
	CString xfln_text_CString;

	source_changed = false;

	GlobalUtilities::convert_CString_to_cstring(&new_songname_char, new_songname);

	if (fill_sequ_track)
	{
		if (with_songname)
		{
			HP_Rewind(mf);
			while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
			{
				if (type==HP_SONG_TRACK_NAME)
				{
					HP_ChangeSongTrackName(mf,id,new_songname_char);
					break; // only one in file
				}
			}
		}
		else
		{
			HP_InsertSongTrackName(mf,new_songname_char);
			with_songname = true;
		}
	}

	proposed_songname = new_songname_char;
	songname = new_songname_char;
	delete[] new_songname_char;


	// fill songname, composer and lyricist into XFln Text-Event

	if (with_xfln)
	{
		HP_Rewind(mf);
		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (type==HP_TEXT)
			{
				HP_ReadText(mf,id,&time,&xfln_text);
				if ((xfln_text[0] != 'X') ||
					(xfln_text[1] != 'F') ||
					(xfln_text[2] != 'l') ||
					(xfln_text[3] != 'n')    )
				{
					HP_Delete(xfln_text);
					continue;
				}
				// xfln_text found
				xfln_text_CString = xfln_text;
				HP_Delete(xfln_text);
				xfln_text_CString = insert_xfln_item(xfln_text_CString, new_songname, 2);
				xfln_text_CString = insert_xfln_item(xfln_text_CString, new_composer, 3);
				xfln_text_CString = insert_xfln_item(xfln_text_CString, new_lyricist, 4);
				GlobalUtilities::convert_CString_to_cstring(&xfln_text, xfln_text_CString);
				HP_ChangeText(mf,id,xfln_text);
				delete[] xfln_text;
				break; // only one in file
			}
		}
	}
	else
	{
		xfln_text_CString = GlobalUtilities::empty_xfln;
		xfln_text_CString = insert_xfln_item(xfln_text_CString, new_songname, 2);
		xfln_text_CString = insert_xfln_item(xfln_text_CString, new_composer, 3);
		xfln_text_CString = insert_xfln_item(xfln_text_CString, new_lyricist, 4);
		GlobalUtilities::convert_CString_to_cstring(&xfln_text, xfln_text_CString);
		HP_SetFirst(mf);
		HP_InsertXFVersionID(mf, 0, GlobalUtilities::xfversion,GlobalUtilities::xfversion_len);
		HP_SetFirst(mf, HP_LAST);
		if (!with_xfhd)
		{
			char* xfhd_cstring;
			GlobalUtilities::convert_CString_to_cstring(&xfhd_cstring,GlobalUtilities::empty_xfhd);
			HP_InsertText(mf,0,xfhd_cstring);
			delete[] xfhd_cstring;
			with_xfhd = true;
		}
		HP_InsertText(mf,0,xfln_text);
		delete[] xfln_text;
		with_xfln = true;
	}

	if (new_songname=="")
	{	// recompute songname
		compute_songname();
	}

	composer = new_composer;
	lyricist = new_lyricist;
	source_changed = true;
}

//**************************************************************************
//*
//*		eval_copyright
//*
//**************************************************************************

void HPMF_Interface::eval_copyright(CString old_copyright, CString copyright)
{
	int id, chan, type, time;
	char* copyright_char;
	source_changed = false;

	if (copyright == old_copyright) return;

	copyrightname = copyright;

	GlobalUtilities::convert_CString_to_cstring(&copyright_char,copyright);

	if (old_copyright.GetLength() == 0)
	{	// insert new event
		HP_SetFirst(mf, HP_LAST);
		HP_InsertCopyright(mf, 0, copyright_char);
		delete[] copyright_char;
		source_changed = true;
		return;
	}

	// event already exist
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if (type != HP_COPYRIGHT) continue;
		if (copyright.GetLength()!=0)
		{
			HP_ChangeCopyright(mf,id,copyright_char);
		}
		else
		{
			HP_DeleteEvent(mf,id);
		}
		delete[] copyright_char;
		source_changed = true;
		return;
	}
}

//**************************************************************************
//*
//*		eval_scorechan
//*
//**************************************************************************

void HPMF_Interface::eval_scorechan(int old_score_chan_left, int score_chan_left,
									int old_score_chan_right, int score_chan_right)
{
	int id, chan, type, time, length;
	bool left_chan_sysex_is = false;
	bool right_chan_sysex_is = false;
	bool left_part_sysex_is = false;
	bool right_part_sysex_is = false;
	bool is_score_start_bar = false;
	bool is_score_layout = false;
	bool is_quickstart = false;
	int time_of_first_note;
	source_changed = false;
	unsigned char *data;

	unsigned char score_sysex_data[10] =
	{0xf0, 0x43, 0x73, 0x01, 0x50, 0x12, 0x00, 0x00, 0x00, 0xf7};

	if ((score_chan_left == old_score_chan_left)&&
		(score_chan_right == old_score_chan_right)) return;

	// First: Delete GuideTrackFlag and Score SysExe: LeftPartOn/Off,
	// RightPartOn/Off, Lyrics Indication, Chords Indication, Note Names
	// Change Left/Right Chan SysEx if exist

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{

		if (type == HP_NOTE)
		{
			time_of_first_note = time;
			break;
		}

		if (type == HP_GUIDE_TRACK_FLAG)
		{
			unsigned char *str;
			HP_ReadGuideTrackFlag(mf, id, &time, &str, &length);
			if (length != 8)
			{
				HP_Delete(str);
				continue;
			}
			HP_DeleteEvent(mf, id);
			continue;
		}

		if (type == HP_SCORE_START_BAR)
		{
			// Event must be deleted becoause in former versions with measure 15
			HP_DeleteEvent(mf,id);
			is_score_start_bar = false;
			continue;
		}

		if (type == HP_QUICK_START)
		{
			is_quickstart = true;
			continue;
		}

		if (type == HP_SCORE_LAYOUT)
		{
			is_score_layout = true;
			continue;
		}

		if (type == HP_SYSEX)
		{
			HP_ReadSysex(mf, id, &time, &data, &length);
			if (!GlobalUtilities::is_score_sysex(data, length))
			{
				HP_Delete(data);
				continue;
			}

			if (data[7] == 0x02 ||  // Lyrics Score ON/OFF
				data[7] == 0x03 ||  // Chords ON/OFF
				data[7] == 0x04   ) // Note Names
			{
				HP_Delete(data);
				HP_DeleteEvent(mf,id);
				continue;
			}

			if (data[7] == 0x00)
			{ // Left Part ON/OFF
				if (left_part_sysex_is)
				{
					HP_Delete(data);
					HP_DeleteEvent(mf,id);
					continue;
				}

				left_part_sysex_is = true;
				data[8] = score_chan_left==-1?0x00:0x7f;
				HP_ChangeSysex(mf,id,data);
			}

			if (data[7] == 0x01)
			{ // Right Part ON/OFF
				if (right_part_sysex_is)
				{
					HP_Delete(data);
					HP_DeleteEvent(mf,id);
					continue;
				}

				right_part_sysex_is = true;
				data[8] = score_chan_right==-1?0x00:0x7f;
				HP_ChangeSysex(mf,id,data);
			}

			if (data[7] == 0x06) // left channel sysex
			{
				if (left_chan_sysex_is)
				{
					HP_Delete(data);
					HP_DeleteEvent(mf,id);
					continue;
				}
				left_chan_sysex_is = true;
				data[8] = score_chan_left==-1?0x7e:(unsigned char) score_chan_left;
				HP_ChangeSysex(mf,id,data);
			}
			if (data[7] == 0x07) // right channel sysex
			{
				if (right_chan_sysex_is)
				{
					HP_Delete(data);
					HP_DeleteEvent(mf,id);
					continue;
				}

				right_chan_sysex_is = true;
				data[8] = score_chan_right==-1?0x7e:(unsigned char) score_chan_right;
				HP_ChangeSysex(mf,id,data);
			}

			HP_Delete(data);
		}
	}

	HP_SetFirst(mf, HP_FIRST);

	if(!is_score_layout)
	{
		// insert Score Layout
		unsigned char data_sl[] = {0xff,0x7f,0x15, 0x43,0x73,0x0a,0x00,0x05,0x5a,0x5a,0x4f,0x4f,0x5a,
		                     0x5a,0x4f,0x4f,0x4f,0x5a,0x5a,0x5a,0x4f,0x5a,0x5a,0x5a};

		HP_InsertScoreLayout(mf, 0 ,data_sl,24);
		is_score_layout = true;
	}

	if(!is_score_start_bar)
	{
		// insert Score Startbar

		unsigned char data_ss[] = {0xff,0x7f, 0x06, 0x43,0x73,0x0a,0x00,0x07,0x02};
		HP_InsertScoreStartBar(mf, 0 ,data_ss,9);
		is_score_layout = true;
	}

	if (!is_quickstart && !left_part_sysex_is && !right_part_sysex_is)
	{
		// insert quickstart

		unsigned char data_qs[] = {0xff,0x7f, 0x06, 0x43,0x73,0x0a,0x00,0x04,0x01};
		HP_InsertQuickStart(mf, 0 ,data_qs,9);
		is_quickstart = true;
	}

	if (!left_part_sysex_is)
	{
		score_sysex_data[7] = 0x00;
		score_sysex_data[8] = score_chan_left==-1?0x00:0x7f;
		HP_InsertSysEx (mf, 0, score_sysex_data);
	}

	if (!right_part_sysex_is)
	{
		score_sysex_data[7] = 0x01;
		score_sysex_data[8] = score_chan_right==-1?0x00:0x7f;
		HP_InsertSysEx (mf, 0, score_sysex_data);
	}

	if (!left_chan_sysex_is)
	{
		score_sysex_data[7] = 0x06;
		score_sysex_data[8] = score_chan_left==-1?0x7e:(unsigned char) score_chan_left;
		HP_InsertSysEx (mf, 0, score_sysex_data);
	}

	if (!right_chan_sysex_is)
	{
		score_sysex_data[7] = 0x07;
		score_sysex_data[8] = score_chan_right==-1?0x7e:(unsigned char) score_chan_right;
		HP_InsertSysEx (mf, 0, score_sysex_data);
	}


	int no_double_notes;
	int no_pitch_wheels;
	eval_xg_convert(&no_double_notes, &no_pitch_wheels);
	source_changed = true;
}

//**************************************************************************
//*
//*		eval_quickstart
//*
//**************************************************************************

void HPMF_Interface::eval_quickstart(bool quickstart)
{
	source_changed = false;
	if (quickstart)
	{
		int no_double_notes;
		int no_pitch_wheels;
		eval_xg_convert(&no_double_notes, &no_pitch_wheels);
		HP_SetFirst(mf);
		HP_InsertQuickStart(mf,0,GlobalUtilities::quickstart,GlobalUtilities::quickstart_len);
		source_changed = true;
	}
	else
	{
		int id, chan, type, time;
		bool with_quickstart = true;

		HP_Rewind(mf);
		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (type == HP_NOTE)
			{
				with_quickstart = false;
				break;
			}

			if (type == HP_QUICK_START)
			{
				HP_DeleteEvent(mf,id);
				source_changed = true;
				continue;
			}
		}
		with_quickstart = false;
	}
}

//**************************************************************************
//*
//*		insert_heikoplate_text
//*		insert an information, that PSRUTI changed the source
//*		insert only if inifile says without psruti_text
//*
//**************************************************************************

void HPMF_Interface::insert_heikoplate_text()
{
	bool already_inserted = false;
	int id, chan, time, type;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_TEXT)
		{
			char* text;
			HP_ReadText(mf,id,&time,&text);
			if (strcmp(text,heikoplate_text)==0)
			{
				already_inserted = true;
			}
			HP_Delete(text);
		}
		if (already_inserted || (type==HP_NOTE)) break;
	}

	if (psruti_text && !already_inserted)
	{
		char *hpt = new char[(int)strlen(heikoplate_text)+1];
		strcpy(hpt,heikoplate_text);
		HP_SetFirst(mf, HP_LAST);
		HP_InsertText(mf,0,hpt);
		delete[] hpt;
	}
}

//**************************************************************************
//*
//*		compute_songname
//*		1. initialize with file title
//*		2. look for sequencer track event, overwrite the name from here
//*		3. look for text event XFln, overwrite the name from here
//*
//**************************************************************************

void HPMF_Interface::compute_songname()
{
	int i;
	int id, chan, type, time;
	with_songname = false;
	with_xfln = false;
	// generate proposed_songname from sourcefile
	GetFileTitle(sourcefile,filetitle,80);
	// delete extension
	for (i=0; i<(int)strlen(filetitle); i++)
	{
		if (filetitle[i] == '.')
		{
			filetitle[i] = (char)0;
			break;
		}
	}
	proposed_songname = filetitle;

	// look for Sequencer_Track Event
	HP_Rewind(mf);
	HP_SetFirst(mf,HP_LAST);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_SONG_TRACK_NAME)
		{
			if (with_songname)
			{
//				proposed_songname = filetitle;
				HP_DeleteEvent(mf,id);
			}
			else
			{
				char* text;
				HP_ReadSongTrackName(mf,id,&time,&text);
				if (text[0] != 0x00)
				{
					proposed_songname = text;
				}
				HP_Delete(text);
				with_songname = true;
			}
			continue;
		}
	}

	// look for XFln Textevent
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		char *text;

		if (type==HP_TEXT)
		{
			if (!with_xfln)
			{
				HP_ReadText(mf,id,&time,&text);
				if ((text[0]=='X') &&
					(text[1]=='F') &&
					(text[2]=='l') &&
					(text[3]=='n')    )
				{
					with_xfln = true;
					// extract songname
					CString scr_songname = "";
					int no_colons=0;
					for (i=4; text[i]!=0x00; i++)
					{
						if (text[i]==':')
						{
							no_colons++;
							if (no_colons<=2) continue;
							break;
						}
						if (no_colons==2) scr_songname += text[i];
					}
					if (scr_songname!="") proposed_songname = scr_songname;
					HP_Delete(text);
//					break;
				}
			}
			else
			{
				HP_ReadText(mf,id,&time,&text);
				if ((text[0]=='X') &&
					(text[1]=='F') &&
					(text[2]=='l') &&
					(text[3]=='n')    )
				{
					HP_Delete(text);
					HP_DeleteEvent(mf,id);
				}
//				break;
			}
		}
	}

	if (proposed_songname == "untitled")
	{
		proposed_songname = filetitle;
	}
	songname = proposed_songname;
}


//**************************************************************************
//*
//*		get_rounded_takt_bar
//*		a sort of quantisizing notes to takt/bar for chords
//*
//**************************************************************************

void HPMF_Interface::get_rounded_takt_bar(int time, int time_of_taktchange, int takt_of_taktchange,
										  int *rtkt, int *rbr, int *deltatick, int *rounded_event_time)
{
    int bar_time = last_denum==1?ppqn*4:last_denum==2?ppqn*2:last_denum==4?ppqn:last_denum==8?ppqn/2:ppqn;
	int tick = time%bar_time;
//	int limit = (bar_time*9)/16;
	int limit = (bar_time*11)/16; // bis einschließlich 8.5

	int time_of_last_bar = ppqn==-1?0:(time-time_of_taktchange)/bar_time;
	int time_of_bar = ppqn==-1?0:tick<=limit?time_of_last_bar:time_of_last_bar+1;

	*rbr = last_num==0?0:time_of_bar%last_num;
	*rtkt = takt_of_taktchange + (last_num==0?0:time_of_bar/last_num);
	*deltatick = tick<=limit?tick:bar_time-tick; // the ticks from rounded_bar
	*rounded_event_time = time + (tick<=limit?-*deltatick:*deltatick);
/*
	CString r;
	r.Format("get_rounded_takt_bar: time %i, meas %i, bar %i, tick %i, rounded_event_time %i",
		time, *rtkt, *rbr, *deltatick, *rounded_event_time);
	::MessageBox(AfxGetMainWnd()->m_hWnd,r,"Test",MB_OK|MB_TASKMODAL);
*/
}

//**************************************************************************
//*
//*		remove_lyrics_chords
//*		type: LYRICS or CHORDS, called from CPlay
//*
//**************************************************************************

void HPMF_Interface::remove_lyrics_chords(UINT type)
{
	int id, chan, time, event_type;
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&event_type)==HP_ERR_NONE)
	{
		if (((event_type==HP_CHORD_NAME)&&(type==CHORDS)) ||
			((event_type==HP_LYRIC)&&(type==LYRICS))        )
		{
			HP_DeleteEvent(mf,id);
		}
	}
}

//**************************************************************************
//*
//*		get_max_min_max_average_vel
//*		find min, max and average value of velocity
//*
//**************************************************************************

void HPMF_Interface::get_max_min_max_average_vel(int min_max_average_vel_list[16][3])
{
	// initialize list
	int id, chan, time, type, note, vel, length;
	float no_notes_float[16];
	float sum_velocities[16];

	for (chan=0; chan < 16; chan++)
	{
		min_max_average_vel_list[chan][0] = 128; // min default
		min_max_average_vel_list[chan][1] = -1;  // max default
		min_max_average_vel_list[chan][2] = 0;   // any value
		no_notes_float[chan] = 0.;
		sum_velocities[chan] = 0.;
	}

	HP_Rewind(mf);

	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			HP_ReadNote(mf,id,&time, &chan, &note,&vel,&length);
			if (vel < min_max_average_vel_list[chan][0]) min_max_average_vel_list[chan][0] = vel;
			if (vel > min_max_average_vel_list[chan][1]) min_max_average_vel_list[chan][1] = vel;
			no_notes_float[chan] += 1.;
			sum_velocities[chan] += (float)vel;
		}
	}

	for (chan=0; chan < 16; chan++)
	{
		if (no_notes_float[chan]==0.) continue;
		min_max_average_vel_list[chan][2] = (int)(sum_velocities[chan]/no_notes[chan]);

	}
}

//**************************************************************************
//*
//*		compute_actual_average_vel
//*		for class VelCompress
//*
//**************************************************************************

void HPMF_Interface::compute_actual_average_vel(VEL_COMPRESS_ELEM actual_vel_compress_list[16],
												int actual_average_list[16])
{

	// initialize list
	int id, chan, time, type, note, vel, length;
	float no_notes[16];
	float sum_velocities[16];
	float vel_new;


	for (chan=0; chan < 16; chan++)
	{
		no_notes[chan] = 0.;
		sum_velocities[chan] = 0.;
	}

	HP_Rewind(mf);

	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			HP_ReadNote(mf,id,&time, &chan, &note,&vel,&length);

			int delete_upto = actual_vel_compress_list[chan].delete_upto;
			if (vel < delete_upto) continue;

			int min = actual_vel_compress_list[chan].min;

			int max = actual_vel_compress_list[chan].max;
			int min_new = actual_vel_compress_list[chan].min_new;
			int max_new = actual_vel_compress_list[chan].max_new;

			if (min==max)
			{
				vel_new = (float)min_new;
			}
			else
			{
				vel_new = (float)((max_new-min_new)*(vel-min))/(float)(max - min) + (float)min_new;
			}

			sum_velocities[chan] += vel_new;
			no_notes[chan] += 1.;
		}
	}

	for (chan=0; chan < 16; chan++)
	{
		if (no_notes[chan]==0) continue;
		actual_average_list[chan] = (int)(sum_velocities[chan]/no_notes[chan]);
	}

}

//**************************************************************************
//*
//*		get_max_values
//*		find max values of the effect-events of GlobalUtilities::effect_list
//*
//**************************************************************************

void HPMF_Interface::get_max_values(int maxvalue[16], int effect_index)
{
	int i;
	int id, chan, type, time, number, value;

	for (i=0; i<16; i++)
	{
		maxvalue[i] = -1;
	}

	int no = GlobalUtilities::effect_list[effect_index].no;

	if (no <= 127)
	{	// Controller, no = controller-number

		HP_Rewind(mf);
		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (chan == HP_NO_CHAN) continue;
			if ((type&HP_TYPE_MASK)==HP_CONTROLLER_TYPE)
			{
				HP_ReadController(mf,id,&time,&chan,&number,&value);
				int val = (unsigned int) value;
				if (number != no) continue;
				if (val > maxvalue[chan])
				{
					maxvalue[chan] = val;
				}
			}
			else
			{
				continue;
			}
		}
	}
	else
	{
		if (no != 0xd0) return;
		HP_Rewind(mf);
		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (type != HP_CHANNEL_PRESSURE) continue;

			HP_ReadChannelPressure(mf,id,&time,&chan,&value);
			if (value > maxvalue[chan])
			{
				maxvalue[chan] = value;
			}
		}
	}
}

//**************************************************************************
//*
//*		get_time_from_takt_bar_tick
//*		deliver time from takt_bar_time_list by given takt and beat
//*
//**************************************************************************

int  HPMF_Interface::get_time_from_takt_bar_tick(int takt, int bar, int tick)
{
	int i;
	int result = -1;
	TAKT_BAR_TIME_ELEM tbte;

	for (i=0; i<takt_bar_time_list_free; i++)
	{
		tbte = takt_bar_time_list[i];
		if ((tbte.takt == takt) && (tbte.bar == bar))
		{
			result = tbte.time + tick;
		}
	}
	return result;
}

//**************************************************************************
//*
//*		get_takt_bar_tick_from_time
//*		delivers takt and beat from takt_bar_time_list by given time
//*
//**************************************************************************

void  HPMF_Interface::get_takt_bar_tick_from_time(int time, int *takt, int *bar, int *tick)
{
	int i;
	TAKT_BAR_TIME_ELEM tbte, old_tbte;
	bool first = true;
	int result = 0;

	for (i=0; i<takt_bar_time_list_free; i++)
	{
		tbte = takt_bar_time_list[i];

		if (first) // must be initialized
		{
			 old_tbte = tbte;
			 first = false;
		}
		if (tbte.time == time)
		{
			*takt = tbte.takt;
			*bar = tbte.bar;
			*tick = 0;
			return;
		}
		else if (tbte.time>time)
		{
			*takt = old_tbte.takt;
			*bar = old_tbte.bar;
			*tick = time - old_tbte.time;
			return;
		}
		old_tbte = tbte;
	}
	*takt = 0;
	*bar = 0;
	*tick = 0;
}


//**************************************************************************
//*
//*		get_takt_bar_tick_time_first_note
//*		deliver position of first note
//*
//**************************************************************************

void HPMF_Interface::get_takt_bar_tick_time_first_note( int *takt, int *bar, int *tick, int *time)
{
	int id, chan, scr_time, type;
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&scr_time,&type) == HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			break;
		}
	}

	*time = scr_time;
	get_takt_bar_tick_from_time(scr_time, takt, bar, tick);
}


//**************************************************************************
//*
//*		get_no_chords
//*		deliver no of chords
//*
//**************************************************************************

int  HPMF_Interface::get_no_chords()
{
	int no = 0;
	int id, chan, time, type, length;
	unsigned char *data;
	HP_Rewind(mf);

	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if (type == HP_CHORD_NAME)
		{
			no++;
			continue;
		}
		if (type == HP_SYSEX)
		{
			HP_ReadSysex(mf, id, &time, &data, &length);
			if (length==9)
			{
				if((data[1]==0x43)&&(data[2]==0x7e)&&(data[3]==0x02))
				{ // chord sysex
					no++;
				}
			}
			HP_Delete(data);
			continue;
		}
	}
	return no;
}


//**************************************************************************
//*
//*		get_ppqn
//*
//**************************************************************************

int  HPMF_Interface::get_ppqn()
{
	return ppqn;
}

//**************************************************************************
//*
//*		get_songname
//*
//**************************************************************************

CString  HPMF_Interface::get_songname()
{
	return songname;
}

//**************************************************************************
//*
//*		set_songname
//*
//**************************************************************************

void  HPMF_Interface::set_songname(CString sn)
{
	songname = sn;
}

//**************************************************************************
//*
//*		get_max_tempo
//*
//**************************************************************************

double HPMF_Interface::get_max_tempo()
{
	return max_tempo;
}

//**************************************************************************
//*
//*		set_max_tempo
//*
//**************************************************************************

void HPMF_Interface::set_max_tempo(double mt)
{
	max_tempo = mt;
}

//**************************************************************************
//*
//*		get_key_signature
//*
//**************************************************************************

CString HPMF_Interface::get_key_signature()
{
	CString cstr_key = "";
	int id, chan, type, time;
	char *key = "";
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_KEY_SIGNATURE)
		{
			HP_ReadKeySignature(mf,id,&time,&key);
			cstr_key = key;
			HP_Delete(key);
			break;
		}
	}
	return cstr_key;
}

//**************************************************************************
//*
//*		get_composer_lyricist
//*
//**************************************************************************

void HPMF_Interface::get_composer_lyricist(CString *composer, CString *lyricist)
{
	if (!with_xfln)
	{
		*composer = "";
		*lyricist = "";
	}
	else
	{
		int id, chan, type, time;
		char *xfln_text;

		HP_Rewind(mf);
		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (type != HP_TEXT) continue;

			HP_ReadText(mf,id,&time,&xfln_text);

			if ((xfln_text[0] != 'X')||
				(xfln_text[1] != 'F')||
				(xfln_text[2] != 'l')||
				(xfln_text[3] != 'n')   )
			{
				HP_Delete(xfln_text);
				continue;
			}

			extract_composer_lyricist(xfln_text, composer, lyricist);
			HP_Delete(xfln_text);
			break;
		}
	}
}

//**************************************************************************
//*
//*		get_copyright
//*
//**************************************************************************

CString HPMF_Interface::get_copyright()
{
	int id, chan, type, time;
	CString copyright;
	char *text;

	// Do not allow more than one copyright and also copyrights behind the first note
	int first_copyright_arrived = false;
	int first_note_arrived = false;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			first_note_arrived = true;
		}
		if (type != HP_COPYRIGHT)
		{
			continue;
		}
		if(!first_copyright_arrived && !first_note_arrived)
		{
			first_copyright_arrived = true;
			HP_ReadCopyright(mf,id,&time,&text);
			copyright = text;
			HP_Delete(text);
		}
		else
		{
			HP_DeleteEvent(mf,id);
		}
	}
	return copyright;
}

//**************************************************************************
//*
//*		get_scorechan
//*
//**************************************************************************

void  HPMF_Interface::get_scorechan(int *chan_left, int *chan_right)
{
	int id, chan, type, time, length;
	int chan_left_sysex = -1; // default
	int chan_right_sysex = -1; // default
	int chan_left_meta = -1; // default
	int chan_right_meta = -1; // default
	
	unsigned char *str; // default
	unsigned char *data; // default

	bool left_chan_sysex_off = false;
	bool right_chan_sysex_off = false;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if (type == HP_SYSEX)
		{
			HP_ReadSysex(mf, id, &time, &data, &length);

			if (!GlobalUtilities::is_score_sysex(data, length))
			{
				HP_Delete(data);
				continue;
			}

			if (data[7] == 0x00)
			{   // Left Part ON/OFF
				if (data[8] == 0x00)
				{
					left_chan_sysex_off = true;
				}
			}
			if (data[7] == 0x01)
			{   // Right Part ON/OFF
				if (data[8] == 0x00)
				{
					right_chan_sysex_off = true;
				}
			}

			if (data[7] == 0x06)
			{   // left channel
				if (left_chan_sysex_off)
				{
					chan_left_sysex = -1;
				}
				else
				{
					if ((data[8] == 0x7e)||(data[8] == 0x7f))
					{   // OFF or AUTO
						chan_left_sysex = -1;
					}
					else
					{
						chan_left_sysex = data[8];
					}
				}
			}

			if (data[7] == 0x07)
			{ // right channel
				if (right_chan_sysex_off)
				{
					chan_right_sysex = -1;
				}
				else
				{
					if ((data[8] == 0x7e)||(data[8] == 0x7f))
					{   // OFF or AUTO
						chan_right_sysex = -1;
					}
					else
					{
						chan_right_sysex = data[8];
					}
				}
			}

			HP_Delete(data);
		}


		if (type != HP_GUIDE_TRACK_FLAG) continue;
		HP_ReadGuideTrackFlag(mf, id, &time, &str, &length);
		if (length != 8)
		{
			HP_Delete(str);
			continue;
		}
		chan_right_meta = str[6]-1;
		chan_left_meta = str[7]-1;
		HP_Delete(str);
		break;
	}
	if (chan_left_sysex != -1)
	{
		*chan_left = chan_left_sysex;
	}
	else
	{
		*chan_left = chan_left_meta;
	}

	if (chan_right_sysex != -1)
	{
		*chan_right = chan_right_sysex;
	}
	else
	{
		*chan_right = chan_right_meta;
	}
}

 //**************************************************************************
//*
//*		get_quickstart
//*
//**************************************************************************

bool HPMF_Interface::get_quickstart()
{
	int id, chan, type, time;
	bool with_quickstart = true;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			with_quickstart = false;
			break;
		}

		if (type == HP_QUICK_START)
		{
			with_quickstart = true;
			break;
		}
	}
	return with_quickstart;
}

//**************************************************************************
//*
//*		remove_double_chords
//*
//**************************************************************************

void HPMF_Interface::remove_double_chords()
{
	int i;

	int id, chan, time, type;
	unsigned char cr, ct,bn, bt;
	char *new_chord;
	char old_chord[20] = "";

	int length;
	unsigned char *new_data = NULL;
	unsigned char* old_data = new unsigned char[9];
	for (i=0; i<9; i++) old_data[i] = 0;

	HP_Rewind(mf);
	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if (type == HP_CHORD_NAME)
		{
			HP_ReadChord(mf,id,&time,&cr,&ct,&bn,&bt,&new_chord);
			if(strcmp(old_chord,new_chord)==0)
			{
				HP_DeleteEvent(mf,id);
			}
			else
			{
				strcpy(old_chord,new_chord);
			}
			HP_Delete(new_chord);
			continue;
		}
		if (type == HP_SYSEX)
		{
			HP_ReadSysex(mf, id, &time, &new_data, &length);
			if (length==9)
			{
				if((new_data[1]==0x43)&&(new_data[2]==0x7e)&&(new_data[3]==0x02))
				{ // chord sysex
					bool is_equal = true;
					for (i=0; i<9; i++)
					{
						if (old_data[i] != new_data[i])
						{
							is_equal = false;
							if (old_data[0]!=0)
							{
								HP_Delete(old_data);
							}
							old_data = new_data;
							new_data = NULL;
							break;
						}
					}
					if (is_equal)
					{
						HP_DeleteEvent(mf,id);
						HP_Delete(new_data);
						new_data = NULL;
					}
					continue;
				}
			}
			if (new_data != NULL)
			{
				HP_Delete(new_data);
				new_data = NULL;
			}
			continue;
		}
	}
	if (old_data != NULL)
	{
		if(old_data[0]!=0)
		{
			HP_Delete(old_data);
		}
		else
		{
			delete[] old_data;
		}
	}
}

/********************************* Play Functions **************************/

//**************************************************************************
//*
//*		get_last_takt_beat
//*
//**************************************************************************

void  HPMF_Interface::get_last_takt_beat(int* takt, int* beat, int* last_tick)
{
	int last_time;
	HP_GetLastTime(mf,&last_time);
	*last_tick = last_time;

	int tick;
	HP_GetTaktBeatTick(mf,last_time,takt,beat,&tick);
}

//**************************************************************************
//*
//*		Stop
//*		stops Playing
//*
//**************************************************************************

void HPMF_Interface::Stop()
{
	HP_SetPlayStopWait(mf, HP_STOP_PLAY);
	is_pause = false;
}

//**************************************************************************
//*
//*		Pause
//*		pauses Playing
//*
//**************************************************************************

bool HPMF_Interface::Pause()
{
	if (HP_IsPlaying(mf))
	{
		if (is_pause)
		{
			while (HP_SetPlayStopWait(mf, HP_GO_PLAY) != HP_ERR_NONE)
			{
				continue;
			}
			is_pause = false;
		}
		else
		{
			while (HP_SetPlayStopWait(mf, HP_WAIT_PLAY) != HP_ERR_NONE)
			{
				continue;
			}
			is_pause = true;
		}
	}
	return is_pause;
}

//**************************************************************************
//*
//*		is_playing
//*		looks if the song plays
//*
//**************************************************************************

bool HPMF_Interface::is_playing()
{
	return HP_IsPlaying(mf);
}

//**************************************************************************
//*
//*		open_insdeffile
//*		opens insdeffile
//*
//**************************************************************************

bool HPMF_Interface::open_insdeffile(CString file)
{
	char *cfile;

	GlobalUtilities::convert_CString_to_cstring(&cfile,file);
	UINT result = HP_CWInsLoad(mf,cfile);
	delete[] cfile;

	return (result==HP_ERR_NONE);
}

//**************************************************************************
//*
//*		get_insdefs
//*		get list of insdefs; user has do apply HP_Delete(deflist)
//*
//**************************************************************************

bool HPMF_Interface::get_insdefs(HP_CWDEF **def_list, int *no_defs)
{
	UINT result = HP_CWInsGetDefs(mf, def_list, no_defs);
	if (result!=HP_ERR_NONE)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,HP_ErrText(result),NULL,MB_OK|MB_TASKMODAL);
		return false;
	}
	return true;
}

//**************************************************************************
//*
//*		set_insdef
//*
//**************************************************************************

bool HPMF_Interface::set_insdef(int index)
{
	UINT result = HP_CWInsSetDef(mf,index);
	return (result==HP_ERR_NONE);
}

//**************************************************************************
//*
//*		get_initialvoices
//*		gets msb, lsb, voice before the first notes
//*
//**************************************************************************

void HPMF_Interface::get_initialvoices(VOICELIST_ELEM voicelist[16])
{
	int id, chan, time, type;
	int number, value, voice;

	for (chan=0; chan<16; chan++)
	{
		voicelist[chan].msb = -1;
		voicelist[chan].lsb = -1;
		voicelist[chan].voice = -1;
		voicelist[chan].with_note = false;
	}

	HP_Rewind(mf);
	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if (chan == HP_NO_CHAN) continue;
		if (voicelist[chan].with_note) continue;

		if (type == HP_BANK_SELECT_MSB)
		{
			HP_ReadController(mf,id,&time,&chan,&number,&value);
			voicelist[chan].msb = value;
			continue;
		}
		if (type == HP_BANK_SELECT_LSB)
		{
			HP_ReadController(mf,id,&time,&chan,&number,&value);
			voicelist[chan].lsb = value;
			continue;
		}
		if (type == HP_PROGRAM_CHANGE)
		{
			HP_ReadProgramChange(mf,id,&time,&chan,&voice);
			voicelist[chan].voice = voice;
			continue;
		}
		if (type == HP_NOTE)
		{
			voicelist[chan].with_note = true;
		}
	}

	for (chan=0; chan<16; chan++)
	{
		if (voicelist[chan].with_note)
		{
			if (voicelist[chan].msb==-1) voicelist[chan].msb = (chan==9)?127:0;
			if (voicelist[chan].lsb==-1) voicelist[chan].lsb = 0;
			if (voicelist[chan].voice==-1) voicelist[chan].voice = 0;
		}
	}
}

//**************************************************************************
//*
//*		eval_standard_revoice
//*		sets msb, lsb, voice before the first notes
//*
//**************************************************************************

void HPMF_Interface::eval_standard_revoice(VOICELIST_ELEM voicelist[16])
{
	bool note_arrived[16] =
		{ false,false,false,false,false,false,false,false,
		  false,false,false,false,false,false,false,false };
	int id, chan, time, type;
	int number, value;

	bool msb_arrived[16] =
		{ false,false,false,false,false,false,false,false,
		  false,false,false,false,false,false,false,false };
	bool lsb_arrived[16] =
		{ false,false,false,false,false,false,false,false,
		  false,false,false,false,false,false,false,false };
	bool voice_arrived[16] =
		{ false,false,false,false,false,false,false,false,
		  false,false,false,false,false,false,false,false };

	source_changed = false;

	// delete megavoice effect notes, if orig. channel is mega and shall be revoiced
	// to normal melody channel
	for (chan = 0; chan < 16; chan++)
	{
		if (mlv_list[chan].is_mega && !is_mega_voice(voicelist[chan].msb,voicelist[chan].lsb))
		{
			delete_mega_effectnotes(chan);
		}
	}

	HP_Rewind(mf);
	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if (chan == HP_NO_CHAN) continue;
		if (note_arrived[chan]) continue;
		if (!voicelist[chan].with_note) continue;

		if (type == HP_BANK_SELECT_MSB)
		{
			HP_ReadController(mf,id,&time,&chan,&number,&value);
			if (value != voicelist[chan].msb)
			{
				HP_ChangeController(mf,id,type,voicelist[chan].msb,HP_NO_PERCENT);
				mlv_list[chan].msb = voicelist[chan].msb;
			}
			msb_arrived[chan] = true;
			continue;
		}
		if (type == HP_BANK_SELECT_LSB)
		{
			HP_ReadController(mf,id,&time,&chan,&number,&value);
			if (value != voicelist[chan].lsb)
			{
			    HP_ChangeController(mf,id,type,voicelist[chan].lsb,HP_NO_PERCENT);
				mlv_list[chan].lsb = voicelist[chan].lsb;
			}
			lsb_arrived[chan] = true;
			continue;
		}
		if (type == HP_PROGRAM_CHANGE)
		{
			HP_ReadProgramChange(mf, id, &time, &chan, &number);
			if (number != voicelist[chan].voice)
			{
				HP_ChangeProgram(mf,id,voicelist[chan].voice);
				mlv_list[chan].voice = voicelist[chan].voice;
			}
			voice_arrived[chan] = true;
			continue;
		}
		if (type == HP_NOTE)
		{
			HP_SetFirst(mf);
			if (!voice_arrived[chan])
			{
				HP_InsertProgramChange(mf,time,chan,voicelist[chan].voice);
				mlv_list[chan].time_voice = time;

			}
			if (!lsb_arrived[chan])
			{
				HP_InsertController(mf,time,chan,HP_BANK_SELECT_LSB,voicelist[chan].lsb);
				mlv_list[chan].time_lsb = time;
			}
			if (!msb_arrived[chan])
			{
				HP_InsertController(mf,time,chan,HP_BANK_SELECT_MSB,voicelist[chan].msb);
				mlv_list[chan].time_msb = time;
			}
			note_arrived[chan] = true;
		}
	}
	for (chan=0; chan<16; chan++)
	{
		int voice = mlv_list[chan].voice;
		mlv_list[chan].is_sart = false;
		mlv_list[chan].is_mega = is_mega_voice(mlv_list[chan].msb,voicelist[chan].lsb);
		mlv_list[chan].is_sart = is_sart_voice(mlv_list[chan].msb,voicelist[chan].lsb);

		mlv_list[chan].melody = chan==9?false:true;
		int bank = 128*voicelist[chan].msb+voicelist[chan].lsb;
		mlv_list[chan].melody = is_yamaha_melody_voice(bank,voice);
	}
	source_changed = true;
}

//**************************************************************************
//*
//*		eval_sysex_export
//*
//**************************************************************************

void HPMF_Interface::eval_sysex_export(char *sysexfile, bool with_delete)
{

	read_sysex_from_mf(with_delete);
	if ((sysexfile[0]==0) && with_delete)
	{
		source_changed = true;
		return;
	}

	CStdioFile *sf_f;
	CFileException e;
	CString t;

	if (sysexfile[0] == 0)
	{
		source_changed = false;
		return;
	}

	source_changed = with_delete;

	CFileStatus status;

	if (CFile::GetStatus(sysexfile,status))
	{
		CFile::Remove(sysexfile);
	}

	sf_f = new CStdioFile;
	if (!sf_f->Open(sysexfile, CFile::modeCreate | CFile::modeNoTruncate |
		CFile::modeReadWrite | CFile::shareExclusive, &e))
	{
		delete sf_f;
		return;
    }

	sf_f->SetLength(0);
	sf_f->SeekToBegin();

	t = sysexfile_title + "\n";

	CString sf = "File:  "+ sourcefile + "\n\n";

	sf_f->WriteString(t);
	sf_f->WriteString(sf);
	sf_f->WriteString(GlobalUtilities::start_sysexlist+"\n\n");

	int i;

	SYSEX_ELEM sysex_elem;
	CString str;
	CString comment;
	for (i=0; i<sysexlist_free; i++)
	{
		str = (sysexlist.GetAt(i)).data_str;
		comment = sysextextlist.GetAt(i);
		if (comment == "Turn General Midi System On")
		{
			str += "\t";
		}
		str.MakeUpper();
		sf_f->WriteString(str+"\t; "+comment+"\n");
	}
	sf_f->WriteString("\n"+GlobalUtilities::end_list+"\n");

	sf_f->Close();
	delete sf_f;

	if (with_delete && (sysexlist_free > 0))
	{
		source_changed = true;
	}

    ShellExecute(this->m_hWnd,"open",sysexfile,NULL,NULL,SW_SHOWNORMAL);
}

//**************************************************************************
//*
//*		eval_sysex_export_note_area
//*
//**************************************************************************

void HPMF_Interface::eval_sysex_export_note_area(char *sysexfile, bool with_delete)
{
	read_sysex_from_mf_note_area(with_delete);

	// now fill sysexfile with content of sysexlist and sysextextlist
	if ((sysexfile[0]==0) && with_delete)
	{
		source_changed = true;
		return;
	}

	CStdioFile *sf_f;
	CFileException e;
	CString t;

	if (sysexfile[0] == 0)
	{
		source_changed = false;
		return;
	}

	source_changed = with_delete;

	CFileStatus status;

	if (CFile::GetStatus(sysexfile,status))
	{
		CFile::Remove(sysexfile);
	}

	sf_f = new CStdioFile;
	if (!sf_f->Open(sysexfile, CFile::modeCreate | CFile::modeNoTruncate |
		CFile::modeReadWrite | CFile::shareExclusive, &e))
	{
		delete sf_f;
		return;
    }

	sf_f->SetLength(0);
	sf_f->SeekToBegin();

	t = sysexfile_title + "\n";

	CString sf = "File:  "+ sourcefile + "\n\n";

	sf_f->WriteString(t);
	sf_f->WriteString(sf);
	sf_f->WriteString(GlobalUtilities::start_sysexlist_mbt+"\n\n");

	int i;

	SYSEX_ELEM sysex_elem;
	CString str;
	CString mbt_text;
	CString comment;
	for (i=0; i<sysexlist_free; i++)
	{
		sysex_elem = sysexlist.GetAt(i);
		mbt_text.Format("%3.3i:%2.2i:%3.3i",sysex_elem.measure+1, sysex_elem.beat+1,sysex_elem.tick);
		str = (sysexlist.GetAt(i)).data_str;
		comment = sysextextlist.GetAt(i);
		str.MakeUpper();
		sf_f->WriteString(mbt_text+"\t"+str+"\t; "+comment+"\n");
	}
	sf_f->WriteString("\n"+GlobalUtilities::end_list+"\n");

	sf_f->Close();
	delete sf_f;

	if (with_delete && (sysexlist_free > 0))
	{
		source_changed = true;
	}

    ShellExecute(this->m_hWnd,"open",sysexfile,NULL,NULL,SW_SHOWNORMAL);
}

//**************************************************************************
//*
//*		read_sysex_from_file
//*
//**************************************************************************

bool HPMF_Interface::read_sysex_from_file(char *sysexfile)
{
	int i;
	int line_number = 0; // counts from 1 to last sysex

	CStdioFile *sf_f;
	CFileException e;
	CString line;

	if (sysexfile == "")
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SYSEXFILE),NULL,MB_OK|MB_TASKMODAL);
		return false; // file does not exist
	}

	CFileStatus status;

	if (!CFile::GetStatus(sysexfile,status))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SYSEXFILE),NULL,MB_OK|MB_TASKMODAL);
		return false; // file does not exist
	}

	sf_f = new CStdioFile;
	if (!sf_f->Open(sysexfile, CFile::modeRead | CFile::typeText | CFile::shareExclusive, &e))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SYSEXFILE),NULL,MB_OK|MB_TASKMODAL);
		delete sf_f;
		return false; // file does not exist
    }

	while (true)
	{
		if (!sf_f->ReadString(line))
		{
			sf_f->Close();
			CString r = GlobalUtilities::get_resource_string(IDS_NO_START_SYSEXLIST);
			r.Format ("(%i) "+r,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			delete sf_f;
			return false;
		}
		line.TrimRight();
		line_number ++;
		if (line == GlobalUtilities::start_sysexlist) break;
	}

	CString sysexes = "";

	while (sf_f->ReadString(line))
	{
		line.TrimRight();
		line_number++;
		if (line == GlobalUtilities::end_list) break;
		sysexes += line;
	}

	sf_f->Close();
	delete sf_f;

	line.TrimRight();
	if (line != GlobalUtilities::end_list)
	{
		CString r = GlobalUtilities::get_resource_string(IDS_NO_END_LIST);
		::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
		return false;
	}

	sysexes.MakeUpper();

	int si = 0; // index in sysexes pointing to "F0"
	int ei;		// index in sysexes pointing to "F7"
	int err = false;

	SYSEX_ELEM sysex_elem;

	// no need in this function
	sysex_elem.time = -1;
	sysex_elem.measure = -1;
	sysex_elem.beat = -1;
	sysex_elem.tick = -1;

	sysexlist.RemoveAll();
	sysexlist_free = 0;

	while (true)
	{
		si = sysexes.Find("F0",si);
		if (si == -1)
		{
			break;
		}
		ei = sysexes.Find("F7",si);
		if (ei == -1)
		{
			err = true;
			break;
		}
		CString sysex_str;

		for (i=si; i<ei; i++)
		{
			unsigned char ch = sysexes[i];
			if (((ch>='0')&&(ch<='9'))||((ch>='A')&&(ch<='F')))
			{
				sysex_str += ch;
			}
			else
			{
				if (ch != ' ')
				{
					err = true;
					break;
				}
			}
		}
		int len = sysex_str.GetLength();
		if ((len/2)*2 != len)
		{	// not even length
			err = true;
		}
		if (err) break;
		sysex_str += "F7";

		sysex_elem.data_str = sysex_str;

		sysexlist.Add(sysex_elem);
		sysexlist_free++;
		si = ei;
	}

	if (err)
	{
		CString r = GlobalUtilities::get_resource_string(IDS_SYSEXFILE);
		::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
		return false;
	}
/*
	for (i=0; i<sysexlist_free; i++)
	{
		SYSEX_ELEM sysex_elem;

		::MessageBox(AfxGetMainWnd()->m_hWnd,(sysexlist.GetAt(i)).data_str,"Test",MB_OK|MB_TASKMODAL);
	}
*/
	return true;
}


//**************************************************************************
//*
//*		read_sysex_from_file_mbt
//*
//**************************************************************************

bool HPMF_Interface::read_sysex_from_file_mbt(char *sysexfile)
{
	int i;
	int line_number = 0;	// counts from 1 to last line
	int line_idx = 0;
	CStdioFile *sf_f;
	CFileException e;
	CString line;
	int err = false;
	SYSEX_ELEM sysex_elem;

	CString err_basic_text;
	err_basic_text = GlobalUtilities::get_resource_string(IDS_SYSEXFILE);
	CString r;

	if (sysexfile == "")
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,err_basic_text,NULL,MB_OK|MB_TASKMODAL);
		return false; // file does not exist
	}

	CFileStatus status;

	if (!CFile::GetStatus(sysexfile,status))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,err_basic_text,NULL,MB_OK|MB_TASKMODAL);
		return false; // file does not exist
	}

	sf_f = new CStdioFile;
	if (!sf_f->Open(sysexfile, CFile::modeRead | CFile::typeText | CFile::shareExclusive, &e))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,err_basic_text,NULL,MB_OK|MB_TASKMODAL);
		delete sf_f;
		return false; // file does not exist
    }

	sysexlist.RemoveAll();
	sysexlist_free = 0;

	while (true)
	{
		if (!sf_f->ReadString(line))
		{
			sf_f->Close();
			r = GlobalUtilities::get_resource_string(IDS_NO_START_SYSEXLIST_MBT);
			r.Format ("(%i) "+r,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			delete sf_f;
			return false;
		}
		line.TrimRight();
		line_number ++;
		if (line == GlobalUtilities::start_sysexlist_mbt) break;
	}

	while (sf_f->ReadString(line))
	{
		line_number ++;
		int len = line.GetLength();
		if (len == 0) continue;
		char ch;
		int takt = -1;
		int bar = 0;
		int tick = 0;
		line.TrimRight();
		if (line == GlobalUtilities::end_list) break;
		int line_idx = 0; // index in line

		// Find takt, bar, tick

		for (i=line_idx; i<len; i++)
		{
			ch = line[i];
			if ((ch >= (int)'0') && (ch <= (int)'9'))
			{
				break;
			}
		}
		line_idx = i+1;

		takt = (ch - '0');
		if (takt < 0)
		{
			r.Format ("(%i) "+err_basic_text+"\n"+line,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			err = true;
			continue;
		}

		for (i=line_idx; i<len;i++)
		{
			ch = line[i];
			if ((ch<(int)'0')||(ch>(int)'9'))
			{
				break;
			}
			takt = 10*takt+(ch - '0');
		}

		takt -= 1;
		sysex_elem.measure = takt;


		line_idx = i+1;
		if (line_idx >= len)
		{
			r.Format ("(%i) "+err_basic_text+"\n"+line,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			err = true;
			continue;
		}

		if (ch==':')
		{
			for (i=line_idx; true; i++)
			{
				ch = line[i];
				if ((ch < (int)'0') || (ch > (int)'9')) break;
				bar = 10*bar + (ch - '0');
			}
			if (bar <= 0) continue; // Error
			bar -= 1;
			sysex_elem.beat = bar;

			line_idx = i+1;
			if (line_idx >= len)
			{
				r.Format ("(%i) "+err_basic_text+"\n"+line,line_number);
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
				err = true;
				continue;
			}

			if (ch==':')
			{
				for (i=line_idx; true; i++)
				{
					ch = line[i];
					if ((ch < (int)'0') || (ch > (int)'9')) break;
					tick = 10*tick + (ch - '0');
				}

				sysex_elem.tick = tick;

				HP_GetTimeFromTaktBeatTick(mf,takt,bar,tick,&sysex_elem.time);

				line_idx = i+1;

				// here starts analysis of sysex string

				if (line_idx >= len)
				{
					r.Format ("(%i) "+err_basic_text+"\n"+line,line_number);
					::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
					err = true;
					continue;
				}
			}
		}
		int si = 0; // index in line of F0
		int ei;     // index in line of F7

		si = line.Find("F0",si);
		if (si == -1)
		{
			break;
		}
		ei = line.Find("F7",si);
		if (ei == -1)
		{
			r.Format ("(%i) "+err_basic_text+"\n"+line,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			err = true;
			break;
		}
		CString sysex_str;

		for (i=si; i<ei; i++)
		{
			unsigned char ch = line[i];
			if (((ch>='0')&&(ch<='9'))||((ch>='A')&&(ch<='F')))
			{
				sysex_str += ch;
			}
			else
			{
				if (ch != ' ')
				{
					r.Format ("(%i) "+err_basic_text+"\n"+line,line_number);
					::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
					err = true;
					break;
				}
			}
		}

		len = sysex_str.GetLength();
		if ((len/2)*2 != len)
		{	// not even length
			r.Format ("(%i) "+err_basic_text+"\n"+line,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			err = true;
		}

		if (err) break;

		sysex_str += "F7";

		sysex_elem.data_str = sysex_str;

		sysexlist.Add(sysex_elem);
		sysexlist_free++;
	}

	sf_f->Close();
	delete sf_f;

	if (err)
	{
		return false;
	}
/*
	// test
	for (i=0; i<sysexlist_free; i++)
	{
		sysex_elem = sysexlist.GetAt(i);
		r.Format("sysexlist[%i]: time %i, measure %i, beat %i, tick %i, data_str %s",
			i, sysex_elem.time,sysex_elem.measure,sysex_elem.beat,sysex_elem.tick,sysex_elem.data_str);
		MessageBox(r);
	}

*/
	return true;
}

//**************************************************************************
//*
//*		read_sysex_from_mf
//*
//**************************************************************************

void HPMF_Interface::read_sysex_from_mf(bool with_delete)
{
	int id, chan, type, time, length;
	unsigned char *data1;
	CString sysex_str;
	SYSEX_ELEM sysex_elem;

	// no need here
	sysex_elem.time = -1;
	sysex_elem.measure = -1;
	sysex_elem.beat = -1;
	sysex_elem.tick = -1;

	char ch;
	int i;

	SysExEventProt sep;
	sep.hpmfi = this;

	sysexlist.RemoveAll();
	sysextextlist.RemoveAll();
	sysexlist_free = 0;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			break;
		}
		if (type == HP_SYSEX)
		{
			sysex_str = "";
			HP_ReadSysex(mf,id,&time,&data1,&length);
			for (i=0; i<length; i++)
			{
				sprintf(&ch,"%1.1x", data1[i]>>4);
				sysex_str += ch;
				sprintf(&ch,"%1.1x",data1[i]&0x0f);
				sysex_str += ch;
				sysex_str += " ";
			}
			sysex_str.MakeUpper();
			sysex_elem.data_str = sysex_str;
			sysexlist.Add(sysex_elem);
			sysextextlist.Add(sep.sysex_string(data1,length));
			sysexlist_free++;
			if (with_delete)
			{
				if((!GlobalUtilities::is_gm_on_sysex(data1))&&
				   (!GlobalUtilities::is_xg_on_sysex(data1)))
				{
					HP_DeleteEvent(mf,id);
				}
			}
			HP_Delete(data1);
		}
	}
}

//**************************************************************************
//*
//*		read_sysex_from_mf_note_area
//*
//**************************************************************************

void HPMF_Interface::read_sysex_from_mf_note_area(bool with_delete)
{
	int id, chan, type, time, length;
	unsigned char *data1;
	CString sysex_str;
	char ch;
	int i;

	int time_of_last_time_signature = 0;
	int takt_of_last_time_signature = 0;
	int takt, beat, tick;
	int num = 4;
	int denum = 4;
	int metronome_click,n32;
	CString line;


	SysExEventProt sep;
	sep.hpmfi = this;

	sysexlist.RemoveAll();
	sysextextlist.RemoveAll();
	sysexlist_free = 0;

	SYSEX_ELEM sysex_elem;

	bool now_note_area = false;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_TIME_SIGNATURE)
		{
			int scr_bar, scr_tick;
			HP_GetTaktBeatTick(mf,time, &takt_of_last_time_signature,&scr_bar, &scr_tick);
			HP_ReadTimeSignature(mf,id,&time_of_last_time_signature,&num,&denum,&metronome_click,&n32);
			continue;
		}

		if (type == HP_NOTE)
		{
			now_note_area = true;
			continue;
		}
		if ((type == HP_SYSEX) && now_note_area)
		{
			sysex_str = "";

			HP_GetTaktBeatTick(mf,time,time_of_last_time_signature,takt_of_last_time_signature,num,denum,&takt,&beat,&tick);

			HP_ReadSysex(mf,id,&time,&data1,&length);
			for (i=0; i<length; i++)
			{
				sprintf(&ch,"%1.1x", data1[i]>>4);
				sysex_str += ch;
				sprintf(&ch,"%1.1x",data1[i]&0x0f);
				sysex_str += ch;
				sysex_str += " ";
			}
			sysex_str.MakeUpper();
				// no need in this function
			sysex_elem.time = time;
			sysex_elem.measure = takt;
			sysex_elem.beat = beat;
			sysex_elem.tick = tick;


			sysex_elem.data_str = sysex_str;
			sysexlist.Add(sysex_elem);

			sysextextlist.Add(sep.sysex_string(data1,length));
			sysexlist_free++;
			if (with_delete)
			{
				if((!GlobalUtilities::is_gm_on_sysex(data1))&&
				   (!GlobalUtilities::is_xg_on_sysex(data1)))
				{
					HP_DeleteEvent(mf,id);
				}
			}
			HP_Delete(data1);
		}
	}
}

//**************************************************************************
//*
//*		eval_sysex_file_import
//*
//**************************************************************************

void HPMF_Interface::eval_sysex_file_import(char *sysexfile)
{
	source_changed = false;
	if (!read_sysex_from_file(sysexfile)) return;
	if (sysexlist_free == 0) return;

	int id, chan, type, time;
	int time_of_first_note = 0;
	int no_sysex = 0;

	unsigned char *data;
	int length;
	int result;

	SYSEX_ELEM sysex_elem;

	// no need in this function
	sysex_elem.time = -1;
	sysex_elem.measure = -1;
	sysex_elem.beat = -1;
	sysex_elem.tick = -1;

	CString sysex_str;
	int i;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			time_of_first_note = time;
			break;
		}
		if (type == HP_SYSEX)
		{
			HP_ReadSysex(mf,id,&time,&data,&length);
			if((!GlobalUtilities::is_gm_on_sysex(data))&&(!GlobalUtilities::is_xg_on_sysex(data)))
			{
				no_sysex++;
			}
			HP_Delete(data);
		}
	}

	if (no_sysex > 0)
	{
		CString r;
		r.Format(GlobalUtilities::get_resource_string(IDS_WANT_INSERT_SYSEX),no_sysex);
		if (IDYES != AfxMessageBox(r,MB_YESNO,0))
		{
			return;
		}
	}

	HP_SetFirst(mf,HP_FIRST);
	for (i=sysexlist_free-1; i>=0; i--)
	{
		sysex_elem = sysexlist.GetAt(i);
		sysex_str = sysex_elem.data_str;
		GlobalUtilities::convert_sysex_string_to_data(sysex_str, &data, &length);
		if ((GlobalUtilities::is_gm_on_sysex(data)) || (GlobalUtilities::is_xg_on_sysex(data)))
		{
			delete[] data;
			continue;
		}

		result = HP_InsertSysEx(mf,time_of_first_note,data);
		delete[] data;

		if (result != HP_ERR_NONE)
		{
			CString r = GlobalUtilities::get_resource_string(IDS_SYSEX);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			break;
		}
		else
		{
			source_changed = true;
		}
	}

	// is ist possible to convert multipart sysex to controller?
	// fill part_chan_list
	fill_part_chan_list();

	// convert multipart sysex to controller
	if (multipart_convert==1)
	{
		HP_Rewind(mf);
		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (type == HP_NOTE)
			{
				break;
			}
			if (type == HP_SYSEX)
			{
				convert_multipart_sysex_to_controller(id);
			}
		}
	}

	if (drum_setup_convert==1)
	{
		exchange_drumsysex_to_nrpn();
	}

	int no_double_notes;
	int no_pitch_wheels;
	eval_xg_convert(&no_double_notes, &no_pitch_wheels);
}

//**************************************************************************
//*
//*		eval_sysex_file_import_position
//*     Insert SysEx from file at a time position inside the area of notes
//*
//**************************************************************************

void HPMF_Interface::eval_sysex_file_import_position(char *sysexfile, int position)
{
	source_changed = false;
	if (!read_sysex_from_file(sysexfile)) return;
	if (sysexlist_free == 0) return;

	int id, chan, type, time;
	int time_of_first_note = 0;
	int actual_position = position;

	unsigned char *data;
	int length;
	int result;
	bool sysex_ok;

	CString sysex_str;
	SYSEX_ELEM sysex_elem;

	int i;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			time_of_first_note = time;
			break;
		}
	}

	HP_SetFirst(mf,HP_LAST);
	for (i=0; i<sysexlist_free; i++)
	{
		sysex_elem = sysexlist.GetAt(i);
		sysex_str = sysex_elem.data_str;
		if (position < time_of_first_note)
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_ONLY_NOTEAREA),NULL,MB_OK|MB_TASKMODAL);
			return;
		}

		sysex_ok = GlobalUtilities::convert_sysex_string_to_data(sysex_str, &data, &length);
		if (!sysex_ok)
		{
			CString r = GlobalUtilities::get_resource_string(IDS_SYSEX);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			delete[] data;
            break;
		}

		if ((GlobalUtilities::is_gm_on_sysex(data)) || (GlobalUtilities::is_xg_on_sysex(data)))
		{
			delete[] data;
			continue;
		}

		result = HP_InsertSysEx(mf,actual_position,data);
		delete[] data;

		if (result != HP_ERR_NONE)
		{
			CString r = GlobalUtilities::get_resource_string(IDS_SYSEX);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			break;
		}
		else
		{
			source_changed = true;
		}

		actual_position +=5;
	}
}

//**************************************************************************
//*
//*		eval_sysex_file_import_mbt
//*		inserts sysex from mbt-textfile (sysex date with preceding
//*		meas/beat/tick into the note area
//*
//**************************************************************************

void HPMF_Interface::eval_sysex_file_import_mbt(char *sysexfile)
{
	if (!read_sysex_from_file_mbt(sysexfile)) return;

	// Test return
//	return;

	int i;
	int id, chan, time, type;
	int time_of_first_note = 0;
	int position = -1;
	unsigned char *data;
	int length;
	int result;

	CString sysex_str;
	SYSEX_ELEM sysex_elem;

	// look for time of first note
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			time_of_first_note = time;
			break;
		}
	}

	HP_SetFirst(mf,HP_LAST);
	for (i=0; i<sysexlist_free; i++)
	{
		sysex_elem = sysexlist.GetAt(i);
		sysex_str = sysex_elem.data_str;
		position = sysex_elem.time;
		if (position < time_of_first_note)
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_ONLY_NOTEAREA),NULL,MB_OK|MB_TASKMODAL);
			return;
		}

		GlobalUtilities::convert_sysex_string_to_data(sysex_str, &data, &length);
		if ((GlobalUtilities::is_gm_on_sysex(data)) || (GlobalUtilities::is_xg_on_sysex(data)))
		{
			delete[] data;
			continue;
		}

		result = HP_InsertSysEx(mf,position,data);
		delete[] data;
		if (result != HP_ERR_NONE)
		{
			CString r = GlobalUtilities::get_resource_string(IDS_SYSEX);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			break;
		}		
		else
		{
			source_changed = true;
		}
	}
}

//**************************************************************************
//*
//*		sysex import from clipboard
//*
//**************************************************************************

void HPMF_Interface::eval_sysex_paste_import(CString sysex_chain)
{
	if (sysex_chain=="") return;

	source_changed = false;
	int id, chan, type, time;
	int last_event_time_before_notes = 0;
	int no_sysex = 0;

	unsigned char *data;
	int length;
	int result;
	CString sysex;
	int i;

	delete_needless_sysex();

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_NOTE)
		{
			if (time == last_event_time_before_notes)
			{
				last_event_time_before_notes>0?last_event_time_before_notes--:0;
			}
			break;
		}
		if (type == HP_SYSEX)
		{
			HP_ReadSysex(mf,id,&time,&data,&length);
			if((!GlobalUtilities::is_gm_on_sysex(data))&&(!GlobalUtilities::is_xg_on_sysex(data)))
			{
				no_sysex++;
			}
			HP_Delete(data);
		}
		last_event_time_before_notes = time;
	}

	if (no_sysex > 0)
	{
		CString r;
		r.Format(GlobalUtilities::get_resource_string(IDS_WANT_INSERT_SYSEX),no_sysex);
		if (IDYES != AfxMessageBox(r,MB_YESNO,0))
		{
			return;
		}
	}

	// eliminate sysex from sysex_chain and insert

	HP_SetFirst(mf, HP_LAST);

	CString chain = sysex_chain;
	bool sysex_ok = true;
	while (true)
	{
		sysex = "";
		if (chain=="")
		{
			break;
		}
		int f7_index = chain.Find("F7");
		if (f7_index == -1)
		{
			CString r = GlobalUtilities::get_resource_string(IDS_SYSEX);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			break;
		}
		int f0_index = chain.Find("F0");
		if (f0_index == -1)
		{
			CString r = GlobalUtilities::get_resource_string(IDS_SYSEX);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			break;
		}
		for (i=f0_index; i<f7_index+2; i++)
		{
			sysex += chain[i];
		}
		chain = chain.Right(chain.GetLength()-(f7_index+2));
		sysex_ok = GlobalUtilities::convert_sysex_string_to_data(sysex, &data, &length);
		if (sysex_ok)
		{
			result = HP_InsertSysEx(mf,last_event_time_before_notes,data);
			delete data;

			if (result != HP_ERR_NONE)
			{
				CString r = GlobalUtilities::get_resource_string(IDS_SYSEX);
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
				break;
			}
			else
			{
				source_changed = true;
			}
		}
		else
		{
			CString r = GlobalUtilities::get_resource_string(IDS_SYSEX);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			break;
		}
	}

	int no_double_notes;
	int no_pitch_wheels;
	eval_xg_convert(&no_double_notes, &no_pitch_wheels);
}

//**************************************************************************
//*
//*		eval_sysex_paste_import_note_area
//*     Sysex import from clipboard inside the area of notes
//*
//**************************************************************************

void HPMF_Interface::eval_sysex_paste_import_note_area(CString sysex_chain, int position)
{
	int actual_time_position = position;
	if (sysex_chain=="") return;

	source_changed = false;
	int id, chan, type, time;
	int time_of_first_note = 0;

	unsigned char *data;
	int length;
	int result;

	CString sysex;
	int i;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_NOTE)
		{
			time_of_first_note = time;
			break;
		}
	}

	if (position <= time_of_first_note)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_ONLY_NOTEAREA),NULL,MB_OK|MB_TASKMODAL);
		return;
	}


	// eliminate sysex from sysex_chain and insert

	HP_SetFirst(mf, HP_LAST);

	CString chain = sysex_chain;
	bool sysex_ok = true;
	while (true)
	{
		sysex = "";
		if (chain=="")
		{
			break;
		}
		int f7_index = chain.Find("F7");
		if (f7_index == -1)
		{
			break;
		}
		int f0_index = chain.Find("F0");
		for (i=f0_index; i<f7_index+2; i++)
		{
			sysex += chain[i];
		}
		chain = chain.Right(chain.GetLength()-(f7_index+2));
		sysex_ok = GlobalUtilities::convert_sysex_string_to_data(sysex, &data, &length);
		if (sysex_ok)
		{
			result = HP_InsertSysEx(mf,actual_time_position,data);
			delete data;

			if (result != HP_ERR_NONE)
			{
				CString r = GlobalUtilities::get_resource_string(IDS_SYSEX);
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
				break;
			}
			else
			{
				source_changed = true;
			}

			actual_time_position+=5;
		}
		else
		{
			CString r = GlobalUtilities::get_resource_string(IDS_SYSEX);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			break;
		}
	}
}


//**************************************************************************
//*
//*		eval_time_export_note_area
//*
//**************************************************************************

void HPMF_Interface::eval_time_export_note_area(CString timefile)
{
	int i, time, measure, bar, tick, num, denum;

	CStdioFile *t_f;
	CFileException e;
	CString t;

	if (timefile == "")
	{
		return;
	}


	CFileStatus status;

	if (CFile::GetStatus(timefile,status))
	{
		CFile::Remove(timefile);
	}

	t_f = new CStdioFile;
	if (!t_f->Open(timefile, CFile::modeCreate | CFile::modeNoTruncate |
		CFile::modeReadWrite | CFile::shareExclusive, &e))
	{
		delete t_f;
		return;
    }

	t_f->SetLength(0);
	t_f->SeekToBegin();


	ArraySixInts *asi = new ArraySixInts;

	read_time_from_note_area(timefile, asi);

	int len_asi = asi->get_length();

	t = timefile_title + "\n";

	CString sf = "File:  "+ sourcefile + "\n\n";

	t_f->WriteString(t);
	t_f->WriteString(sf);
	t_f->WriteString(GlobalUtilities::start_timelist_mbt+"\n\n");

	CString r;

	for (i =0; i < len_asi; i++)
	{
		asi->get(i, &time, &measure, &bar, &tick, &num, &denum);
		
/* Test
		r.Format("i %i, time %i, measure %i, bar %i, tick %i, num %i, denum %i",
		i, time, measure, bar, tick, num, denum); 
		MessageBox(r);
*/

		r.Format("%3.3i:%2.2i:%3.3i\t%i/%i",measure, bar, tick, num, denum);
		t_f->WriteString(r+"\n");

	}


	t_f->WriteString("\n"+GlobalUtilities::end_list+"\n");

	t_f->Close();
	delete t_f;
	delete asi;

    ShellExecute(this->m_hWnd,"open",timefile,NULL,NULL,SW_SHOWNORMAL);	
}

//**************************************************************************
//*
//*		read_time_from_note_area
//*
//**************************************************************************

void HPMF_Interface::read_time_from_note_area(CString timefile, ArraySixInts *asi)
{

	int no_times = 0;
	int id, chan, time, type, num, denum, metronome_click, n32;
	int measure, bar, tick;

	HP_Rewind(mf);

	// posit note area
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			break;
		}
	}

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type != HP_TIME_SIGNATURE) continue;
		no_times++;
		HP_ReadTimeSignature(mf,id,&time,&num,&denum,&metronome_click,&n32);

		HP_GetTaktBeatTick(mf,time,&measure, &bar, &tick);

		// usual numbering
		measure++;
		bar++;

		asi->add(time, measure, bar, tick, num, denum);
	}
}

//**************************************************************************
//*
//*		eval_time_import_note_area
//*
//**************************************************************************


void HPMF_Interface::eval_time_import_note_area(CString timefile)
{
	int first_measure_note_area;
	int id, chan, time, type;
	int bar, tick;
	int measure;
	int i;

	ArraySixInts *asi = new ArraySixInts;

	// find first measure with notes

	HP_Rewind(mf);
	
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			break;
		}
	}

	HP_GetTaktBeatTick(mf,time,&first_measure_note_area,&bar,&tick);


	if (!read_time_from_file_mbt(timefile,asi, first_measure_note_area))
	{
		delete asi;
		return;
	}

	asi->sort(); // sort in ascending order by time

	// delete all time signatures in note area

	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_TIME_SIGNATURE)
		{
			HP_DeleteEvent(mf,id);
		}
	}

	HP_SetFirst(mf, HP_FIRST);
	for (i=0; i<asi->get_length(); i++)
	{
		asi->get(i,&time, &measure, &bar, &tick,&num, &denum);
		HP_InsertTimeSignature(mf,time, num, denum, 0x18, 0x08);
	}

	delete asi;

	int dummy1, dummy2;
	eval_xg_convert(&dummy1, &dummy2);

	source_changed = true;
}

//**************************************************************************
//*
//*		read_time_from_file_mbt
//*
//**************************************************************************

bool HPMF_Interface::read_time_from_file_mbt(CString timefile, ArraySixInts *asi, int first_measure_note_area)
{
	int i;
	int line_number = 0;	// counts from 1 to last line
	int line_idx = 0;
	CStdioFile *t_f;
	CFileException e;
	CString line;
	int err = false;

	int time;
	int measure = -1;
	int bar = -1;
	int tick = -1;
	int num = 0;
	int denum = 0;

	CString err_basic_text;
	err_basic_text = GlobalUtilities::get_resource_string(IDS_TIMEFILE);
	CString r;

	if (timefile == "")
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,err_basic_text,NULL,MB_OK|MB_TASKMODAL);
		return false; // file does not exist
	}

	CFileStatus status;

	if (!CFile::GetStatus(timefile,status))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,err_basic_text,NULL,MB_OK|MB_TASKMODAL);
		return false; // file does not exist
	}

	t_f = new CStdioFile;
	if (!t_f->Open(timefile, CFile::modeRead | CFile::typeText | CFile::shareExclusive, &e))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,err_basic_text,NULL,MB_OK|MB_TASKMODAL);
		delete t_f;
		return false; // file does not exist
    }

	while (true)
	{
		if (!t_f->ReadString(line))
		{
			t_f->Close();
			r = GlobalUtilities::get_resource_string(IDS_NO_START_TIMELIST_MBT);
			r.Format ("(%i) "+r,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			delete t_f;
			return false;
		}
		line.TrimRight();
		line_number ++;
		if (line == GlobalUtilities::start_timelist_mbt) break;
	}


	while (t_f->ReadString(line))
	{
		line_number ++;
		int len = line.GetLength();
		if (len == 0) continue;
		char ch;
		measure = -1;
		bar = 0;
		tick = 0;
		num = 0;
		denum = 0;

		line.TrimRight();
		if (line == GlobalUtilities::end_list) break;
		int line_idx = 0; // index in line

		// Find measure, bar, tick

		for (i=line_idx; i<len; i++)
		{
			ch = line[i];
			if ((ch >= (int)'0') && (ch <= (int)'9'))
			{
				break;
			}
		}
		line_idx = i+1;

		measure = (ch - '0');
		if (measure < 0)
		{
			r.Format ("(%i) "+err_basic_text+"\n"+line,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			err = true;
			continue;
		}

		for (i=line_idx; i<len;i++)
		{
			ch = line[i];
			if ((ch<(int)'0')||(ch>(int)'9'))
			{
				break;
			}
			measure = 10*measure+(ch - '0');
		}

		measure -= 1;
		
		line_idx = i+1;
		if ((line_idx >= len) || (measure < first_measure_note_area) )
		{
			r.Format ("(%i) "+err_basic_text+"\n"+line,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			err = true;
			continue;
		}

		if (ch==':')
		{
			bar = 0;
			for (i=line_idx; true; i++)
			{
				ch = line[i];
				if ((ch < (int)'0') || (ch > (int)'9')) break;
				bar = 10*bar + (ch - '0');
			}
			if (bar <= 0) continue; // Error
			bar -= 1;

			line_idx = i+1;
			if (line_idx >= len)
			{
				r.Format ("(%i) "+err_basic_text+"\n"+line,line_number);
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
				err = true;
				continue;
			}

			if (ch==':')
			{
				tick = 0;
				for (i=line_idx; true; i++)
				{
					ch = line[i];
					if ((ch < (int)'0') || (ch > (int)'9')) break;
					tick = 10*tick + (ch - '0');
				}

				if ((bar != 0) || (tick != 0) || (measure < first_measure_note_area))
				{
				    r.Format ("(%i) "+err_basic_text+"\n"+line,line_number);
					::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
					err = true;
				}
				

				HP_GetTimeFromTaktBeatTick(mf,measure,bar,tick,&time);

//				r.Format("time %i, measure %i, bar %i, tick %i", time, measure, bar, tick);
//				MessageBox(r);

				line_idx = i+1;

				// here starts analysis of time denotation num/denum

				if (line_idx >= len)
				{
					r.Format ("(%i) "+err_basic_text+"\n"+line,line_number);
					::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
					err = true;
					continue;
				}
			}
		}

		// line_idx behind m:b:t; now look for num/denum
		bool look_for_num = false;
		bool look_for_denum = false;

		for (i=line_idx; i<len; i++)
		{
			ch = line[i];

			if (((ch < (int)'1')||(ch > (int)'9')) && (ch != '\t') && (ch != ' ') && 
				!look_for_num && !look_for_denum)
			{
				r.Format ("(%i) "+err_basic_text+"\n"+line,line_number);
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
				err = true;
				continue;
			}

			if ((ch >= (int)'1') && (ch <= (int)'9') && !look_for_denum)
			{
				look_for_num = true;
				num = 10*num + (ch - '0');
				continue;
			}

			if (ch =='/')
			{
				look_for_denum = true;
				look_for_num = false;
				continue;
			}

			if ((ch >= (int)'1') && (ch <= (int)'9') && look_for_denum)
			{
				denum = 10*denum + (ch - '0');
				continue;
			}

			if (ch ==';')
			{
				break;
			}
		}
		if ((num==0) || (denum==0))
		{
			r.Format ("(%i) "+err_basic_text+"\n"+line,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			err = true;
			continue;
		}

		asi->add(time, measure, bar, tick, num, denum);
	}

	t_f->Close();
	delete t_f;
/*
	// test
	for (i=0; i<asi->get_length(); i++)
	{
		asi->get(i,&time, &measure, &bar, &tick, &num, &denum);
		r.Format("asi[%i]: time %i, measure %i, bar %i, tick %i, num %i, denum %i",
			i, time,measure,bar,tick,num, denum);
		MessageBox(r);
	}
*/
	if (err)
	{
		return false;
	}

	return true;
}



//**************************************************************************
//*
//*		cut_copy_chan_events
//*
//**************************************************************************

void HPMF_Interface::cut_copy_chan_events(HP_MIDIFILE_MODULE *mf_par, int source_chan, int dest_chan)
{
	int id, chan, time, type;
	unsigned char* data;
	int length;
	int i;

	// first: standard midi events
	delete_chan_events(mf_par, dest_chan,false,true,false,false);

	HP_Rewind(mf_par);
	HP_Deselect(mf_par);

	while ( HP_ReadEvent(mf_par,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if (chan == source_chan)
		{
			HP_Select(mf_par,id);
		}
		else
		{
			continue;
		}
	}
	HP_ChangeChannel(mf_par,dest_chan);
	HP_Deselect(mf_par);

	// then: part sysex

	int part;
	int part_channel = -1;

	HP_Rewind(mf_par);
	while (HP_ReadEvent(mf_par,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_SYSEX)
		{
			// First: Look for Organ Flute Bulk Dump
			HP_ReadSysex(mf_par, id, &time, &data, &length);

			if ((data[1]==0x43)&&
				(data[2]==0x73)&&
				(data[3]==0x01)&&
				(data[4]==0x06)&&
				(data[5]==0x0b))
			{
				int organflute_chan = data[10];
				if (organflute_chan != source_chan)
				{
					HP_Delete(data);
					continue;
				}
				data[10]= dest_chan;

				// checksum
				int check = 0;
				for (i=10; i<=31; i++)
				{
					check += (int)data[i];
					check &= 0x7f;
				}
				check = (128-check)&0x7f;
				data[32]= check;
				HP_DeleteEvent(mf_par,id);
				HP_InsertSysEx(mf_par,time,data);
				HP_Delete(data);
				continue;
			}

			// vh channel sysex
			int vh_chan = GlobalUtilities::is_vh_channel_sysex(data,length);

			if (vh_chan != -1)
			{
				if (vh_chan != source_chan)
				{
					HP_Delete(data);
					continue;
				}
				data[7]= dest_chan;
				HP_DeleteEvent(mf_par,id);
				HP_InsertSysEx(mf_par,time,data);
				HP_Delete(data);
				continue;
			}


			// part sysex
			if (!is_part_sysex(mf_par,id,&part))
			{
				HP_Delete(data);
				continue;
			}

			// change all part sysex: MultiPart, Variation Part, Insertion Part
			HP_SetFirst(mf_par);

			if (data[4]==0x08)
			{ // MultiPart SysEx
				part = data[5];
				if (part==source_chan)
				{
					data[5]= dest_chan;
					if (data[1]==0x43 &&
						data[2]==0x10 &&
						data[3]==0x4c &&
						data[4]==0x08 &&
						data[6]==0x04)
					{
						data[7] = dest_chan;
					}
					HP_DeleteEvent(mf_par,id);
					HP_InsertSysEx(mf_par,time,data);
				}
			}

			if (data[4]==0x02 && data[6]==0x5b)
			{ // Variation Part SysEx
				part = data[7];
				if(part==source_chan)
				{
					data[7] = dest_chan;
					HP_DeleteEvent(mf_par,id);
					HP_InsertSysEx(mf_par,time,data);
				}
			}

			if (data[4]==0x03 && data[6]==0x0c)
			{ // Insertion Part SysEx
				part = data[7];
				if(part==source_chan)
				{
					data[7] = dest_chan;
					HP_DeleteEvent(mf_par,id);
					HP_InsertSysEx(mf_par,time,data);
				}
			}
			HP_Delete(data);
			continue;

		} // end look at sysex
	} // end loop over all events
}

//**************************************************************************
//*
//*		delete_chan_events
//*
//**************************************************************************

int HPMF_Interface::delete_chan_events(HP_MIDIFILE_MODULE *mf_par, int chan, bool until_notes, bool delete_controller, bool with_vocoder_sysex, bool with_vh_ad_on_sysex)
{
	int no_deleted = 0;
	int id, channel, time, type;
	unsigned char* data;
	int length;

	int part;
	int part_to_delete = -1;
	int block_to_delete = -1;

	unsigned char insertion_top[] = {0xf0, 0x43, 0x10, 0x4c, 0x03};

	int blocklist[16];

	// look for VH channels
	bool is_vh_chan;
	bool more_than_one_vh_chan = false;

	int no_vh_chan = find_vh_channel();
	is_vh_chan = vh_channel[chan];
	for (channel=0; channel<16; channel++)
	{
		if (channel==chan) continue;
		if (vh_channel[channel])
		{
			more_than_one_vh_chan = true;
			break;
		}
	}

	// prepare deleting of parts and blocks
	update_blocklist(mf_par, blocklist); // index = part, value = block
	fill_part_chan_list(); // part_chan_list: index = part, value = chan;

	for (part=0;part<16; part++)
	{
		if (part_chan_list[part]==chan)
		{
			if (part_to_delete == -1)
			{
				part_to_delete = part;
			}
			else
			{
				part_to_delete = -1;
				break;
			}
		}
	}

	if (part_to_delete != -1)
	{
		block_to_delete = blocklist[part_to_delete];
	}


	HP_Rewind(mf_par);
	while (HP_ReadEvent(mf_par,&id,&channel,&time,&type)==HP_ERR_NONE)
	{
		if (until_notes && (type == HP_NOTE))
		{
			return no_deleted;
		}

		if (channel == chan)
		{
			if (!delete_controller)
			{
				if ((type==HP_RPN)||(type==HP_NRPN)) continue;
				if (((type&HP_CONTROLLER_TYPE)==HP_CONTROLLER_TYPE)&&
					(type != HP_BANK_SELECT_MSB)&&
					(type!=HP_BANK_SELECT_LSB)) continue;
			}

			HP_DeleteEvent(mf_par,id);
			no_deleted++;
			continue;
		}
		if (type == HP_SYSEX)
		{
			if (is_part_sysex(mf_par, id,&part))
			{
				if (rcv_chan_exist[chan])
				{
					channel = part_chan_list[part];
					if (channel==chan)
					{
						HP_DeleteEvent(mf_par,id);
						no_deleted++;
						continue;
					}
				}
				else
				{
					if (part == chan)
					{
						HP_DeleteEvent(mf_par,id);
						no_deleted++;
						continue;
					}
				}
				continue;
			}

			// delete Insertions
			if (block_to_delete >= 0)
			{
				HP_ReadSysex(mf_par,id,&time,&data,&length);
				if (GlobalUtilities::compare_data(insertion_top,5,data,5))
				{
					if (data[5]==block_to_delete)
					{
						HP_DeleteEvent(mf_par,id);
						no_deleted++;
					}
				}
				HP_Delete(data);
				continue;
			}

			// Organ Flute Bulk Dump
			HP_ReadSysex(mf_par,id,&time,&data,&length);

			if ((data[1]==0x43)&&
				(data[2]==0x73)&&
				(data[3]==0x01)&&
				(data[4]==0x06)&&
				(data[5]==0x0b))
			{
				if (data[10]==chan)
				{
					HP_DeleteEvent(mf_par,id);
					no_deleted++;
				}
			}

			if (is_vh_chan && !more_than_one_vh_chan && vocoder_sysex_exist && with_vocoder_sysex)
			{
				if (GlobalUtilities::is_vocoder_sysex(data,length))
				{
					HP_DeleteEvent(mf_par,id);
					no_deleted++;
				}
			}

			if (is_vh_chan && !more_than_one_vh_chan && vh_ad_on_sysex_exist && with_vh_ad_on_sysex)
			{
				if (GlobalUtilities::is_vh_ad_on_sysex(data,length))
				{
					HP_DeleteEvent(mf_par,id);
					no_deleted++;
				}
			}

			if (is_vh_chan)
			{
				if (chan == GlobalUtilities::is_vh_channel_sysex(data, length))
				{
					HP_DeleteEvent(mf_par,id);
					no_deleted++;
				}
			}
			HP_Delete(data);
		}
	}
	if (mf_par == mf) mute[chan] = true;
	return no_deleted;
}

//**************************************************************************
//*
//*		is_vh_velocities
//*
//**************************************************************************
/*
bool HPMF_Interface::is_vh_velocities(int channel)
{
	return (patchname[channel] == " VH");
}
*/
//**************************************************************************
//*
//*		exchange_or_copy_chan_events
//*
//**************************************************************************

void HPMF_Interface::exchange_or_copy_chan_events(int source_chan, int dest_chan, bool exchange)
{

	// look for VH channels
	bool is_vh_chan;
	bool is_vh_chan_sysex;
	bool vh_channel[16];

	int no_vh_chan = find_vh_channel();
	is_vh_chan = vh_channel[source_chan];
	is_vh_chan_sysex = vh_channel_sysex_exist[source_chan];

	HP_MIDIFILE_MODULE *mf1 = HP_Init();
	HP_ChangePPQN(mf1,ppqn);

	int first_event_time = -1;
	int id, chan, time, type;
	HP_Deselect(mf);

	// copy source-channel-events to mf1

	HP_Rewind(mf);

	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if (chan == source_chan)
		{
			if (first_event_time == -1)
			{
				first_event_time = time;
			}
			HP_Select(mf,id);
		}
		else
		{
			continue;
		}
	}

	// now SysEx
	int part;
	int part_chan = -1;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_SYSEX)
		{
			if (is_organflute_sysex(mf,id,&part))
			{
				if (part==source_chan)
				{
					HP_Select(mf,id);
					if (time < first_event_time)
					{
						first_event_time = time;
					}
				}
			}

			if (is_vh_chan_sysex)
			{
				unsigned char* data;
				int length;
				HP_ReadSysex(mf,id,&time,&data,&length);
				if (source_chan == GlobalUtilities::is_vh_channel_sysex(data,length))
				{
					HP_Select(mf,id);
					if (time < first_event_time)
					{
						first_event_time = time;
					}
				}

				HP_Delete(data);
			}

			if (is_part_sysex(mf,id,&part))
			{

				// change all part sysex: MultiPart, Variation Part, Insertion Part
				unsigned char* data;
				int length;
				HP_ReadSysex(mf,id,&time,&data,&length);

				if (data[4]==0x08)
				{ // MultiPart SysEx
					part = data[5];
					if (part==source_chan)
					{
						HP_Select(mf,id);
						if (time < first_event_time)
						{
							first_event_time = time;
						}
					}
				}

				if(exchange)
				{ // do not double insertions
					if (data[4]==0x02 && data[6]==0x5b)
					{ // Variation Part SysEx
						part = data[7];
						if (part==source_chan)
						{
							HP_Select(mf,id);
							if (time < first_event_time)
							{
								first_event_time = time;
							}
						}
					}

					if (data[4]==0x03 && data[6]==0x0c)
					{ // Insertion Part SysEx
						part = data[7];
						if (part==source_chan)
						{
							HP_Select(mf,id);
							if (time < first_event_time)
							{
								first_event_time = time;
							}
						}
					}
				}
				HP_Delete(data);
			}
		}
		// end look at sysex
	} // end loop over all events


	// move all selected source-chan events to mf1;

	HP_Copy(mf);
	HP_Paste(mf1,first_event_time,HP_NO_DELETE,HP_ALL_EVENTS);
	HP_Deselect(mf);

	if (exchange)
	{
		// delete all selected source-chan events of mf;
		delete_chan_events(mf,source_chan,false,true,false,false);

		// copy dest_chan to source-chan in mf
		cut_copy_chan_events(mf,dest_chan,source_chan);
	}
	else
	{
		delete_chan_events(mf,dest_chan,false,true,false,false);
	}

	// change all source_chan events of mf1 to dest_chan

	cut_copy_chan_events(mf1, source_chan, dest_chan);

	// move all events of mf1 to mf

	HP_Select(mf1, HP_ALL_EVENTS);
	HP_Copy(mf1);
	HP_Paste(mf,first_event_time,HP_NO_DELETE,HP_ALL_EVENTS);
	HP_Free(mf1);
	HP_Deselect(mf);
}

