// HPMF_Interface2.cpp: Implementierung der Klasse HPMF_Interface.
//
//////////////////////////////////////////////////////////////////////

#include "HPMF_Interface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "stdafx.h"
#include "resource.h"

//**************************************************************************
//*
//*		eval_revoice_from_file
//*		msb, lsb, voice by revoice_file
//*
//**************************************************************************

bool HPMF_Interface::eval_revoice_from_file(char* revoice_file)
{

	int chan, type, id, time;
	int i;
	int source, dest, msb, lsb, voice;
	CString r;
	
	ArrayTwoInts *ati = new ArrayTwoInts;

	bool effect_notes_to_deleted[16];

	for (chan=0; chan<16; chan++)
	{
		effect_notes_to_deleted[chan] = false;
	}

	source_changed = false;

	if (!read_voices_from_file(revoice_file,ati))
	{
		delete ati;
		return false;
	}

	int no_double_notes;
	int no_pitch_wheels;
	eval_xg_convert(&no_double_notes, &no_pitch_wheels);

	typedef struct patch_elem {int packed_patch; int msb; int id_msb; 
	                                int lsb; int id_lsb; int voice; int id_voice;} PATCH_ELEM;
	PATCH_ELEM patch_list[16];

	for (chan=0; chan<16; chan++)
	{
		patch_list[chan]. packed_patch = -1;
		patch_list[chan]. msb = -1;
		patch_list[chan]. id_msb = -1;
		patch_list[chan]. lsb = -1;
		patch_list[chan]. id_lsb = -1;
		patch_list[chan]. voice = -1;
		patch_list[chan]. id_voice = -1;
	}

	int number, value;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (chan==-1)
		{
			continue;
		}

		if (mute[chan])
		{
			continue;
		}


		if (type == HP_BANK_SELECT_MSB)
		{
			HP_ReadController(mf,id,&time,&chan,&number,&value);
			patch_list[chan].msb = value;
			patch_list[chan].id_msb = id;
			continue;
		}
		if (type == HP_BANK_SELECT_LSB)
		{
			HP_ReadController(mf,id,&time,&chan,&number,&value);
			patch_list[chan].lsb = value;
			patch_list[chan].id_lsb = id;
			continue;
		}
		if (type == HP_PROGRAM_CHANGE)
		{
			HP_ReadProgramChange(mf,id,&time,&chan,&number);
			patch_list[chan].voice = number;
			patch_list[chan].id_voice = id;

			if ((patch_list[chan].msb==-1) ||
				(patch_list[chan].lsb==-1) ||
				(patch_list[chan].voice==-1))
			{
				r.Format("Error patch_list: msb=%i, lsb=%i, voice=%i",
						patch_list[chan].msb, patch_list[chan].lsb, patch_list[chan].voice);
				MessageBox(r);

				delete ati;	
				return false;
			}

			patch_list[chan].packed_patch = 
				GlobalUtilities::pack_msb_lsb_voice(patch_list[chan].msb,
					                                patch_list[chan].lsb,
													patch_list[chan].voice);
			int ati_len = ati->get_length();

			for (i=0; i < ati_len; i++)
			{
				ati->get(i,&source, &dest);
				if (source != patch_list[chan].packed_patch)
				{
					continue;
				}
				GlobalUtilities::unpack_msb_lsb_voice(dest, &msb, &lsb, &voice);
				HP_ChangeController(mf,patch_list[chan].id_msb,HP_BANK_SELECT_MSB,msb,HP_NO_PERCENT);
				HP_ChangeController(mf,patch_list[chan].id_lsb,HP_BANK_SELECT_LSB,lsb,HP_NO_PERCENT);
				HP_ChangeProgram(mf,patch_list[chan].id_voice,voice);

				if ( (is_mega_voice(patch_list[chan].msb, patch_list[chan].lsb)) &&
					 (!is_mega_voice(msb,lsb)))
				{
					// the effectnotes of this chan must be deleted later
					effect_notes_to_deleted[chan] = true;
				}

				break;
			}

			// initialize for next loop
			patch_list[chan]. packed_patch = -1;
			patch_list[chan]. msb = -1;
			patch_list[chan]. id_msb = -1;
			patch_list[chan]. lsb = -1;
			patch_list[chan]. id_lsb = -1;
			patch_list[chan]. voice = -1;
			patch_list[chan]. id_voice = -1;
		}
	}

	for (chan=0; chan<16; chan++)
	{
		if (effect_notes_to_deleted[chan])
		{
			delete_mega_effectnotes(chan);
		}
	}

	delete ati;	
	update_mlv_list();
	source_changed = true;
	return true;
}

//**************************************************************************
//*
//*		eval_drum_from_file,
//*		midifile identified by mf
//*
//**************************************************************************

bool HPMF_Interface::eval_drum_from_file(char* drum_file, bool drum_folder_running)
{
	int i;
	bool is_drum_list[16];
	int ch;
	int source = -1;
	int dest = -1;

	for( ch=0; ch<16; ch++)
	{
		if ((mlv_list[ch].melody)||
			(no_notes[ch]==0)||
			(is_sfx_bank(mlv_list[ch].msb*128)))
		{
			is_drum_list[ch] = false;
		}
		else
		{
			is_drum_list[ch] = true;;
		}
	}


	ArraySixInts *asi = new ArraySixInts;
	int drum_chan_to_revoice;

	source_changed = false;

	if (!read_drums_from_file(drum_file, &drum_chan_to_revoice, asi))
	{
		delete asi;
		return false;
	}

	int id, time, type;
	int note, velocity, length;
	int asi_source, asi_dest, asi_action;
	int msb_to_revoice = -1;
	int lsb_to_revoice = -1;
	int	voice_to_revoice = -1;

	bool drum_changed;
	int no_drums_changed = 0;
	int msb, lsb, voice;


	HP_Rewind(mf);
	HP_SetFirst(mf, HP_LAST);
	while (HP_ReadEvent(mf,&id,&ch,&time,&type)==HP_ERR_NONE)
	{
		drum_changed = false;

		if(!is_drum_list[ch])
		{
			continue;
		}


		if (type == HP_NOTE)
		{
			HP_ReadNote(mf, id, &time, &ch, &note, &velocity, &length);

			if ((drum_chan_to_revoice==-1) || (drum_chan_to_revoice==ch))
			{
				for (i=0; i<asi->get_length(); i++)
				{
					asi->get(i,&msb_to_revoice, &lsb_to_revoice, &voice_to_revoice, &asi_source,&asi_dest, &asi_action);
/*
CString r;
r.Format(" index %i, drum_chan %i, msb %i, lsb %i, voice %i, source %i, dest %i, asi_action %i",
		  i, drum_chan_to_revoice, msb_to_revoice, lsb_to_revoice, voice_to_revoice, asi_source, asi_dest, asi_action);
MessageBox(r);
*/					
					if (msb_to_revoice != -1)
					{
						msb = mlv_list[ch].msb;
						lsb = mlv_list[ch].lsb;
						voice = mlv_list[ch].voice;

						if ((msb_to_revoice!=msb)||(lsb_to_revoice!=lsb)||(voice_to_revoice!=voice))
						{
							continue;
						}
					}

					if (note==asi_source)
					{
						if (asi_action == DRUM_CHANGE)
						{
							HP_ChangeNote(mf, id, ch,asi_dest,HP_ABSOLUTE);
						}

						if (asi_action == DRUM_DELETE)
						{
							HP_DeleteEvent(mf, id);
						}
						
						if (asi_action == DRUM_COPY)
						{
							HP_InsertNote(mf, time, length, asi_dest, ch, velocity);
						}

						no_drums_changed++;
						drum_changed = true;
						break;
					}
				}
				if (drum_changed)
				{
					continue;
				}
			}
		}
	}

	delete asi;

	if (!drum_folder_running)
	{
//		CString r;
//		r.Format("no_drums_changed %i", no_drums_changed);
//		MessageBox(r);

		if (no_drums_changed > 0)
		{
			source_changed = true;
		}
	}
	return true;
}

//**************************************************************************
//*
//*		read_voices_from_file
//*		analyze revoice file and fill array with dest and dest voices
//*
//**************************************************************************

bool HPMF_Interface::read_voices_from_file(char* revoice_file, ArrayTwoInts *ati)
{
	int line_number = 0; // counts from 1 to last line
	int i;
	unsigned char ch;

	CStdioFile *rf_f;
	CFileException e;
	CString line;
	int msb_source, lsb_source, voice_source;
	int msb_dest, lsb_dest, voice_dest;

	if (revoice_file == "")
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_REVOICEFILE),NULL,MB_OK|MB_TASKMODAL);
		return false; // file does not exist
	}

	CFileStatus status;

	if (!CFile::GetStatus(revoice_file,status))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_REVOICEFILE),NULL,MB_OK|MB_TASKMODAL);
		return false; // file does not exist
	}

	rf_f = new CStdioFile;
	if (!rf_f->Open(revoice_file, CFile::shareExclusive | CFile::modeRead | CFile::typeText, &e))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_REVOICEFILE),NULL,MB_OK|MB_TASKMODAL);
		return false; // file does not exist
    }

	while (true)
	{
		if (!rf_f->ReadString(line))
		{
			rf_f->Close();
			CString r = GlobalUtilities::get_resource_string(IDS_NO_START_REVOICELIST);
			r.Format ("(%i) "+r,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			return false;
		}
		line.TrimRight();
		line_number ++;
		if (line == GlobalUtilities::start_revoicelist) break;
	}

	CString error_revoicefile = GlobalUtilities::get_resource_string(IDS_REVOICEFILE);
	CString r;
	
	// analyse voice-assignments
	while (rf_f->ReadString(line))
	{
		line.TrimRight(); // removes blanks and tabs
		line.TrimLeft();
		int len = line.GetLength();
		if (len == 0) continue;
		if (line[0]==';') continue;
		
		CString line1 = line;	
		line1.TrimRight();
		if (line1==GlobalUtilities::end_list) break;

		if (line[0]!='#')
		{
			rf_f->Close();
			r.Format ("(%i) "+error_revoicefile,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			return false;
		}

		msb_source = 0;
		lsb_source = 0;
		voice_source = 0;
		msb_dest = 0;
		lsb_dest = 0;
		voice_dest = 0;
		for (i=1; i<len; i++)
		{
			ch = line[i];
			if (ch=='-') break;
			if ((ch<'0')||(ch>'9')) continue;
			msb_source = 10*msb_source + (ch-'0');
		}
		if (ch!='-')
		{
			rf_f->Close();
			r.Format ("(%i) "+error_revoicefile,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			return false;
		}

		for (i=i+1; i<len; i++)
		{
			ch = line[i];
			if (ch=='-') break;
			if ((ch<'0')||(ch>'9')) continue;
			lsb_source = 10*lsb_source + (ch-'0');
		}
		if (ch!='-')
		{
			rf_f->Close();
			r.Format ("(%i) "+error_revoicefile,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			return false;
		}

		for (i=i+1; i<len; i++)
		{
			ch = line[i];
			if (ch==':') break;
			if ((ch<'0')||(ch>'9')) continue;
			voice_source = 10*voice_source + (ch-'0');
		}
		if (ch!=':')
		{
			rf_f->Close();
			r.Format ("(%i) "+error_revoicefile,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			return false;
		}

		// look for '#'

		for (i=i+1; i<len;i++)
		{
			ch = line[i];
			if (ch=='#') break;
		}

		if (ch!='#')
		{
			rf_f->Close();
			r.Format ("(%i) "+error_revoicefile,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			return false;
		}
		for (i=i+1; i<len; i++)
		{
			ch = line[i];
			if (ch=='-') break;
			if ((ch<'0')||(ch>'9')) continue;
			msb_dest = 10*msb_dest + (ch-'0');
		}
		if (ch!='-')
		{
			rf_f->Close();
			r.Format ("(%i) "+error_revoicefile,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			return false;
		}
		for (i=i+1; i<len; i++)
		{
			ch = line[i];
			if (ch=='-') break;
			if ((ch<'0')||(ch>'9')) continue;
			lsb_dest = 10*lsb_dest + (ch-'0');
		}
		if (ch!='-')
		{
			rf_f->Close();
			r.Format ("(%i) "+error_revoicefile,line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			return false;
		}
		for (i=i+1; i<len; i++)
		{
			ch = line[i];
			if (ch==';') break;
			if ((ch<'0')||(ch>'9')) continue;
			voice_dest = 10*voice_dest + (ch-'0');
		}

		// check msb, lsb, voice

		if ((msb_source<0)||(msb_source>127)||
		    (msb_dest<0)||(msb_dest>127))
		{
			rf_f->Close();
			r.Format ("(%i) "+error_revoicefile+" MSB",line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			return false;
		}
		if ((lsb_source<0)||(lsb_source>127)||
		    (lsb_dest<0)||(lsb_dest>127))
		{
			rf_f->Close();
			r.Format ("(%i) "+error_revoicefile+" LSB",line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			return false;
		}
		if ((voice_source<0)||(voice_source>127)||
		    (voice_dest<0)||(voice_dest>127))
		{
			rf_f->Close();
			r.Format ("(%i) "+error_revoicefile+" Voice",line_number);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			return false;
		}

		// add to list
		int source_pack = GlobalUtilities::pack_msb_lsb_voice(msb_source, lsb_source, voice_source);
		int dest_pack = GlobalUtilities::pack_msb_lsb_voice(msb_dest, lsb_dest, voice_dest);
		ati->add(source_pack,dest_pack);
		line_number++;
	}

	rf_f->Close();

	CString line1 = line;
	line1.TrimRight();
	if (line1 != GlobalUtilities::end_list)
	{
		r = GlobalUtilities::get_resource_string(IDS_NO_END_LIST);
		::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
		return false;
	}

	if (ati->get_length() == 0)
	{	// no voice-assignments
		return false;
	}
	return true;
}

//**************************************************************************
//*
//*		read_drums_from_file
//*		analyze drum_file, fill drum_chan and array with drum_kit (msb, lsb, 
//*     voice#),source and dest drum
//*
//**************************************************************************

bool HPMF_Interface::read_drums_from_file(char* drum_file, int *drum_chan_to_revoice, ArraySixInts *asi)
{

	int line_number = 0; // counts from 1 to last line
	int i;
	unsigned char ch;

	CStdioFile *df_f;
	CFileException e;
	CString line;
	int drum_source;
	CString drum_source_cstr;
	int drum_dest;
	int drum_action;
		;
	CString drum_dest_cstr;
	int dr_chan = 0;
	CString dr_chan_cstr;

	*drum_chan_to_revoice = -1;
	int msb_source = -1;
	int lsb_source = -1;
	int voice_source = -1;

	int msb_to_revoice = -1;
	int lsb_to_revoice = -1;
	int	voice_to_revoice = -1;
	int nstart = 0; // start line index to search single colon 

	if (drum_file == "")
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_DRUMFILE),NULL,MB_OK|MB_TASKMODAL);
		return false; // file does not exist
	}

	CFileStatus status;

	if (!CFile::GetStatus(drum_file,status))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_DRUMFILE),NULL,MB_OK|MB_TASKMODAL);
		return false; // file does not exist
	}

	df_f = new CStdioFile;
	if (!df_f->Open(drum_file, CFile::shareExclusive | CFile::modeRead | CFile::typeText, &e))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_DRUMFILE),NULL,MB_OK|MB_TASKMODAL);
		return false; // file does not exist
    }

	while (true)
	{
		if (!df_f->ReadString(line))
		{
			df_f->Close();
			CString r = GlobalUtilities::get_resource_string(IDS_NO_START_DRUMLIST);
			r.Format (r);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			df_f->Close();
			return false;
		}
		line.TrimRight();
		line_number ++;
		if (line == GlobalUtilities::start_drumlist) break;
	}

	CString error_drumfile = GlobalUtilities::get_resource_string(IDS_DRUMFILE);
    CString r;
	
	// analyse drum assignments
	while (df_f->ReadString(line))
	{
		line_number++;
		line.TrimRight(); // removes blanks and tabs
		line.TrimLeft();
		int len = line.GetLength();
		if (len == 0) continue;
		if (line[0]==';') continue;
		if (len > 4)
		{
			if (line.Left(4) == "chan")
			{
				for (i=4; i<len; i++)
				{
					ch = line[i];
					if ((ch==9)||(ch==' ')) continue;
					if (line[i]==';')
					{
						break;
					}
					if ((ch-'0' < 0) || (ch-'0' > 9))
					{
						CString r = GlobalUtilities::get_resource_string(IDS_NO_CHAN_NUMBER);
					}
					else
					{
						dr_chan = (dr_chan*10)+(ch-'0');
					}
				}
				*drum_chan_to_revoice = dr_chan-1;
				continue;
			}
		}

		if (line==GlobalUtilities::end_list) break;

		int double_colon_position = line.Find("::");
		if (double_colon_position != -1)
		{	// drumkit specifiéd
			msb_source = 0;
			lsb_source = 0;
			voice_source = 0;

			int char_position = line.Find("#");
			if (char_position == -1)
			{
				df_f->Close();
				r.Format ("(%i) "+error_drumfile,line_number);
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
				return false;
			}

			for (i=char_position+1; i<len; i++)
			{
				ch = line[i];
				if (ch=='-')
				{
					break;
				}
				if ((ch<'0')||(ch>'9')) continue;
				msb_source = 10*msb_source + (ch-'0');
			}
			if (ch!='-')
			{
				df_f->Close();
				r.Format ("(%i) "+error_drumfile,line_number);
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
				return false;
			}

			for (i=i+1; i<len; i++)
			{
				ch = line[i];
				if (ch=='-') break;
				if ((ch<'0')||(ch>'9')) continue;
				lsb_source = 10*lsb_source + (ch-'0');
			}
			if (ch!='-')
			{
				df_f->Close();
				r.Format ("(%i) "+error_drumfile,line_number);
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
				return false;
			}

			for (i=i+1; i<len; i++)
			{
				ch = line[i];
				if (i == double_colon_position) break;
				if ((ch<'0')||(ch>'9')) continue;
				voice_source = 10*voice_source + (ch-'0');
			}

//			CString r;
//			r.Format("msb %i, lsb %i, voice %i",msb_source, lsb_source, voice_source);
//			MessageBox(r);

			msb_to_revoice = msb_source;
			lsb_to_revoice = lsb_source;
			voice_to_revoice = voice_source;
			nstart = double_colon_position+2;
		}
		else
		{	// revoice with all drumkits
			msb_to_revoice = -1;
			lsb_to_revoice = -1;
			voice_to_revoice = -1;
			nstart = 0;
		};

		int colon_position = line.Find(":",nstart);
		if (colon_position == -1)
		{
			CString r = GlobalUtilities::get_resource_string(IDS_NO_COLON);
			r.Format("r, line \"%s\", line number %i", line, line_number-1);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			df_f->Close();
			return false;
		}

		drum_source_cstr = "";
		drum_dest_cstr = "";
		drum_action = DRUM_CHANGE;

		for (i=nstart; i< colon_position; i++)
		{
			if ((line[i]==9)||(line[i]==' '))
			{
				continue;
			}
			if (line[i]==';')
			{
				break;
			}
			drum_source_cstr += line[i];
		}
		for (i=colon_position+1; i<len; i++)
		{
			if ((line[i]==9)||(line[i]==' '))
			{
				continue;
			}
			if ((line[i] == '-') && (drum_dest_cstr==""))
			{	// delete source drum
				drum_dest_cstr = "-";
				drum_action = DRUM_DELETE;
				break;
			}
			if ((line[i] == '+') && (drum_dest_cstr==""))
			{	// add 
				drum_action = DRUM_COPY;
				continue;
			}
			if (line[i]==';')
			{
				break;
			}
			drum_dest_cstr += line[i];
		}
		
		drum_source = GlobalUtilities::compute_notevalue(drum_source_cstr);
		if (drum_dest_cstr == "-")
		{
			drum_dest = -1;
		}
		else
		{
			drum_dest = GlobalUtilities::compute_notevalue(drum_dest_cstr);
		}

		if ((drum_source==-1)||
			((drum_action==DRUM_COPY)&&(drum_dest==-1)) ||
			((drum_action==DRUM_CHANGE)&&(drum_dest==-1)) )
		{
			CString r = GlobalUtilities::get_resource_string(IDS_DRUMFILE);
			r.Format(r + ": \"%s\" (%i)", line, line_number-1);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			df_f->Close();
			return false;
		}
		asi->add(msb_to_revoice, lsb_to_revoice, voice_to_revoice, drum_source, drum_dest, drum_action);

/*
CString r;
r.Format ("msb_to_revoice %i, lsb_to_revoice %i, voice_to_revoice%i, drum_source %i,drum_dest %i,drum_action %i",
		  msb_to_revoice, lsb_to_revoice, voice_to_revoice, drum_source,drum_dest,drum_action);
MessageBox(r)
*/
		;
	}

	df_f->Close();

	CString line1 = line;
	line1.TrimRight();

	if (line1 != GlobalUtilities::end_list)
	{
		r = GlobalUtilities::get_resource_string(IDS_NO_END_LIST);
		::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
		return false;
	}

	if (asi->get_length() == 0)
	{	// no voice-assignments
		return false;
	}
	return true;
}

//**************************************************************************
//*
//*		check_voicefile
//*		used by VoiceFileBrowseDlg
//*
//**************************************************************************

bool HPMF_Interface::check_voicefile(CString voicefile)
{
	HP_MIDIFILE_MODULE* mfvoice;
	UINT result;
	bool return_value = true;

	if (voicefile=="") return false;

	mfvoice = HP_Init();
	if (mfvoice == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,"Err HP_Init",NULL,MB_OK);
		return false;
	}

	result = HP_Load(mfvoice,voicefile);
	if (result!=HP_ERR_NONE)
	{
		HP_Free(mfvoice);
		return false;
	}

	HP_Rewind(mfvoice);
	int id, chan, time, type;
	while (HP_ReadEvent(mfvoice,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (((chan != 0)&&(chan!=HP_NO_CHAN)) || (type==HP_NOTE))
		{
			return_value = false;
			break;
		}
	}

	HP_Free(mfvoice);
	return return_value;
}

//**************************************************************************
//*
//*		eval_voicefile_revoice
//*		basic function for voicefile revoice
//*
//**************************************************************************

void HPMF_Interface::eval_voicefile_revoice(VoiceFilePathElement voicefilepath_list[16])
{
	unsigned char mp_notused_data[]  = {0xf0,0x43,0x10,0x4c,0x08,0x00,0x00,0x08,0xf7};
	unsigned char mp_partmode_data[] = {0xf0,0x43,0x10,0x4c,0x08,0x00,0x07,0x00,0xf7};

	int revoice_chan;
	CString voicefilepath;
	HP_MIDIFILE_MODULE* mf_voice;
	int id, chan, time, type;
	int id_voice, chan_voice, time_voice, type_voice, length_voice;
	int number_voice, value_voice;
	unsigned char* data_voice;
	int last_event_time_before_notes = 0;
	int partmode = 0; // Mode normal

	source_changed = false;

	bool anything_ordered = false;
	for (chan=0; chan<16; chan++)
	{
		if ((voicefilepath_list[chan]).filepath != "")
		{
			anything_ordered = true;
			break;
		}
	}

	if (!anything_ordered) return;
	
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

		last_event_time_before_notes = time;
	}

	add_standard_hall_chorus_variation(last_event_time_before_notes);

	HP_SetFirst(mf,HP_LAST);


	for (revoice_chan=0; revoice_chan<16; revoice_chan++)
	{
		bool is_drum = false;
		voicefilepath = voicefilepath_list[revoice_chan].filepath;
		if (voicefilepath=="") continue;
		bool is_mega_revoice_chan = mlv_list[revoice_chan].is_mega;
		delete_chan_events(mf,revoice_chan, true, false,true,true);
		
		mf_voice = HP_Init();
		HP_Load(mf_voice,voicefilepath);

		if (is_mega_revoice_chan)
		{
			// find out, if revoicefile addresses a mega voice;
			int msb_revoicefile = -1;
			int lsb_revoicefile = -1;

			HP_Rewind(mf_voice);
			while (HP_ReadEvent(mf_voice,&id_voice,&chan_voice,&time_voice,&type_voice)==HP_ERR_NONE)
			{
				if (type_voice == HP_BANK_SELECT_MSB)
				{
					HP_ReadController(mf_voice,id_voice,&time_voice,&chan_voice,&number_voice,&msb_revoicefile);
				}
				if (type_voice == HP_BANK_SELECT_LSB)
				{
					HP_ReadController(mf_voice,id_voice,&time_voice,&chan_voice,&number_voice,&lsb_revoicefile);
				}
			}
			if ((msb_revoicefile!=-1)&&(lsb_revoicefile!=-1))
			{
				if (!is_mega_voice(msb_revoicefile,lsb_revoicefile))
				{
					delete_mega_effectnotes(revoice_chan);
				}
			}
		}

		// search and insert controller + program change
		HP_Rewind(mf_voice);
		while (HP_ReadEvent(mf_voice,&id_voice,&chan_voice,&time_voice,&type_voice)==HP_ERR_NONE)
		{

			if ((type_voice&HP_TYPE_MASK)==HP_CONTROLLER_TYPE)
			{
				HP_ReadController(mf_voice,id_voice,&time_voice,&chan_voice,&number_voice,&value_voice);
				if (!voicefilepath_list[revoice_chan].with_controller)
				{
					if ((number_voice!=0)&&(number_voice!=32))
					{
						continue;
					}
				}
				
				if ((number_voice==0)&&(value_voice==127))
				{
					partmode = 0x02; // mode Drums
					is_drum = true;
				}
				if (type_voice != HP_RELEASE_TIME)
				{   // too high release in voicefile
					HP_InsertController(mf,last_event_time_before_notes,revoice_chan,type_voice,value_voice,number_voice);
				}
			}
			if (type_voice==HP_PROGRAM_CHANGE)
			{
				HP_ReadProgramChange(mf_voice,id_voice,&time_voice,&chan_voice,&number_voice);
				HP_InsertProgramChange(mf,last_event_time_before_notes,revoice_chan,number_voice);
			}
		}
/*
		// MultiPart NotUsed
		mp_notused_data[5] = revoice_chan;
		HP_InsertSysEx(mf,last_event_time_before_notes,mp_notused_data);

		// MultiPart Mode
		mp_partmode_data[5] = revoice_chan;
		mp_partmode_data[7] = partmode;
		HP_InsertSysEx(mf,last_event_time_before_notes,mp_partmode_data);
*/

		// insert insertions

		if (voicefilepath_list[revoice_chan].block >= 0)
		{
			int block = voicefilepath_list[revoice_chan].block;
			add_insertions(last_event_time_before_notes,revoice_chan,block,mf_voice);
		}
		
		// search amd insert OrganFlute
		HP_Rewind(mf_voice);
		while (HP_ReadEvent(mf_voice,&id_voice,&chan_voice,&time_voice,&type_voice)==HP_ERR_NONE)
		{
			if (type_voice==HP_SYSEX)
			{
				HP_ReadSysex(mf_voice, id_voice, &time_voice, &data_voice, &length_voice);
				if ((data_voice[1]==0x43)&&
					(data_voice[2]==0x73)&&
					(data_voice[3]==0x01)&&
					(data_voice[4]==0x06)&&
					(data_voice[5]==0x0b))
				{
					CString r;
					int check=0;
					int i;

					data_voice[10]=revoice_chan;

					// a bad Organ Flute Bulk Dump in voicefiles:
					unsigned char correct_data[34];
					for (i=0; i<28; i++)
					{
						correct_data[i] = data_voice[i];
					}
					correct_data[28] = 0;
					correct_data[29] = 0;
					correct_data[30] = 0;
					correct_data[31] = 0;
					correct_data[32] = 0; // -> check
					correct_data[33] = 0xf7;

					// checksum
					for (i=10; i<=31; i++)
					{
						check += (int)correct_data[i];
						check &= 0x7f;
					}
					check = (128-check)&0x7f;
					correct_data[32]= check;
					HP_InsertSysEx(mf,last_event_time_before_notes,correct_data);
/*	 test checksum
					check = 0;
					for (i=32; i>=0; i--)
					{
						check+= correct_data[i];
						check = check&0x7f;
						if (i==10)
						{
							r.Format("i=%i, check %x",i,check);
							::MessageBox(AfxGetMainWnd()->m_hWnd,r,"Test",MB_OK|MB_TASKMODAL);
						}
					}
*/
				}
			}
		}

		// search and insert MultiPart and OffSet Level SysEx
		add_multipart(last_event_time_before_notes, revoice_chan,mf_voice);

		if (is_drum)
		{
			add_standard_drum_sysex(last_event_time_before_notes);
		}

		HP_Free(mf_voice);
	}
	exchange_drumsysex_to_nrpn();

	int no_double_notes;
	int no_pitch_wheels;
	eval_xg_convert(&no_double_notes, &no_pitch_wheels);

	update_mlv_list();
	int no_vh_chan = find_vh_channel();
		// only after update_mlv_list
	source_changed = true;
	return;
}

//**************************************************************************
//*
//*		delete_needless_sysex
//*		deletes XG-sysex, which have no effect 
//*
//**************************************************************************

void HPMF_Interface::delete_needless_sysex()
{
	int block = -1;
	int bl;
	int id, chan, time, type;
	unsigned char *data;
	int length;

	SYSEX_DATA insertion_data_list[NO_EFF_BLOCKS];
	SYSEX_DATA variation_data;

	SYSEX_DATA *sysex_data;

	bool delete_insertion[NO_EFF_BLOCKS];
	for (bl=0; bl<NO_EFF_BLOCKS;bl++)
	{
		sysex_data = &(insertion_data_list[bl]);

		sysex_data->used = false;
		sysex_data->part = -1;
		sysex_data->channel = -1;
		sysex_data->with_off = false;
		sysex_data->is_insertion = false;
		sysex_data->is_system = false;
		delete_insertion[bl] = false;
	}

	bool delete_variation = false;
	variation_data.used = false;
	variation_data.part = -1;
	variation_data.channel = -1;
	variation_data.with_off = false;
	variation_data.is_insertion = false;
	variation_data.is_system = false;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if (type != HP_SYSEX) continue;

		HP_ReadSysex(mf,id,&time,&data,&length);

		if ((data[1] != 0x43) ||
			(data[2] != 0x10) ||
			(data[3] != 0x4C) )
		{
			HP_Delete(data);
			continue;
		}

		// look for Variation
		if (data[4] == 0x02)
		{
			if ((data[5]!=0x01) ||
				((int)(data[6])< 0x40))
			{
				HP_Delete(data);
				continue;
			}
			// Variation

			if (data[6]==0x5b)
			{
				if (data[7]==0x7f)
				{ // Variation OFF
					variation_data.with_off = true;
				}
				else
				{
					if (((int)(data[7])>=0)&&((int)(data[7])<16))
					{ // Variation Part
						variation_data.part = data[7];
					}
				}
			}
			else
			{
				if(data[6]==0x5a)
				{
					if (data[7]==0)
					{
						variation_data.is_insertion = true;
					}
					else
						if (data[7]==1)
						{
							variation_data.is_system = true;
						}
				}
				else
				{
					variation_data.used = true;
				}
			}
			HP_Delete(data);
			continue;
		}

		// look for Insertion
		if (data[4]	== 0x03)
		{
			block = data[5];
			if ((block<0) || (block>=NO_EFF_BLOCKS))
			{
				MessageBox("block");
				return;
			}

			sysex_data = &(insertion_data_list[block]);

			if (data[6]==0x0c)
			{
				if (data[7]==0x7f)
				{ // Insertion OFF
					sysex_data->with_off = true;
				}
				else
				{
					if (((int)(data[7])>=0)&&((int)(data[7])<16))
					{ // Insertion Part
						sysex_data->part = data[7];
					}
				}
			}
			else
			{
				sysex_data->used = true;
			}

			sysex_data->is_insertion = true;

			HP_Delete(data);
			continue;
		}

		// look for MultiPart
		int part;

		if (data[4] == 0x08)
		{
			part = data[5];
			if (data[6]==4)
			{
				int channel = data[7];
				if (channel==0x7f)
				{ // part OFF
					for (bl = 0; bl < NO_EFF_BLOCKS; bl++)
					{
						if (insertion_data_list[bl].part==part)
						{
							insertion_data_list[bl].with_off = true;
						}
					}

					if (variation_data.used && variation_data.is_insertion)
					{
						if (variation_data.part==part)
						{
							variation_data.with_off = true;;
						}
					}
				}
				else
				{
					for (bl = 0; bl < NO_EFF_BLOCKS; bl++)
					{
						if (insertion_data_list[bl].part==part)
						{
							break;
						}
					}
					if ((channel>=0)&&(channel<16)&&((bl>=0)&&(bl<NO_EFF_BLOCKS)))
					{ // Insertion Part
						insertion_data_list[bl].channel = channel;
					}
				}
			}
			HP_Delete(data);
			continue;
		}
	}

	if (variation_data.used)
	{
		if (!variation_data.is_insertion && !variation_data.is_system)
		{
			variation_data.is_insertion = true; // default
		}
	}


/*	Test */
/*
	CString r;

	if (variation_data.used)
	{
		r.Format("Variation: part=%i, chan=%i, with_off=%s, is_insertion=%s, is_system=%s",
			variation_data.part,
			variation_data.channel,
			variation_data.with_off?"TRUE":"FALSE",
			variation_data.is_insertion?"TRUE":"FALSE",
			variation_data.is_system?"TRUE":"FALSE");
		::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
	}
*/

/*
	for (block=0; block<NO_EFF_BLOCKS; block++)
	{
		if (!insertion_data_list[block].used) continue;
		r.Format("Insertion: block=%i, part=%i, chan=%i, with_off=%s, is_insertion=%s, is_system=%s",
			block,
			insertion_data_list[block].part,
			insertion_data_list[block].channel,
			insertion_data_list[block].with_off?"TRUE":"FALSE",
			insertion_data_list[block].is_insertion?"TRUE":"FALSE",
			insertion_data_list[block].is_system?"TRUE":"FALSE");
		::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
	}
*/


// Set delete markers

	if (variation_data.used)
	{
		if (variation_data.is_insertion==variation_data.is_system)
		{ // only one must be set
			delete_variation = true;
		}
		if (variation_data.is_insertion)
		{
			if ((variation_data.with_off)||
				(variation_data.part==-1))
			{
				delete_variation = true;
			}
		}
	}

	for (block=0; block<NO_EFF_BLOCKS; block++)
	{
		sysex_data = &(insertion_data_list[block]);
		if (!sysex_data->used) continue;
		if ((sysex_data->with_off)&&(block!=vh_block-1))
		{
			delete_insertion[block] = true;
		}
	}

	// Delete SysEx

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf,id,&time,&data,&length);
		if ((data[1] != 0x43) ||
			(data[2] != 0x10) ||
			(data[3] != 0x4C) )
		{
			HP_Delete(data);
			continue;
		}
		// look for Variation
		if (data[4] == 0x02)
		{
			if ((data[5]!=0x01) ||
				((int)(data[6])< 0x40))
			{
				HP_Delete(data);
				continue;
			}
			// Variation
			if (delete_variation)
			{
				HP_DeleteEvent(mf,id);
				HP_Delete(data);
				continue;
			}
			if (variation_data.is_system)
			{
				if (((data[6]==0x54)&&(data[7]==0x00))||(data[6]==0x5B))
				{ // Dry/Wet or Part Assignment, only with Variation-Insertion
					HP_DeleteEvent(mf,id);
					HP_Delete(data);
					continue;
				}
			}
			if (variation_data.is_insertion)
			{ // Das muss ausprobiert werden!!!
				if (data[6]==0x56)
				{ // Variation Return, only with Variation-System
					HP_DeleteEvent(mf,id);
					HP_Delete(data);
					continue;
				}
			}

			HP_Delete(data);
			continue;
		}

		// look for Insertion
		if (data[4]	== 0x03)
		{
			block = data[5];
			if (delete_insertion[block])
			{
				HP_DeleteEvent(mf,id);
			}
			HP_Delete(data);
			continue;
		}

		// look for MultiPart: Assign Part to Off
		if ((data[4]==0x08) && (data[6]==4) && (data[7]==0x7f))
		{	// Assign Part to OFF
			int part = data[5];
			for (block=0; block<NO_EFF_BLOCKS; block++)
			{
				if (insertion_data_list[block].part==part)
				{
					HP_DeleteEvent(mf,id);
					HP_Delete(data);
					continue;
				}
			}
			if (variation_data.used && variation_data.is_insertion)
			{
				if (variation_data.part==part)
				{
					HP_DeleteEvent(mf,id);
					HP_Delete(data);
					continue;
				}
			}
			HP_Delete(data);
			continue;
		}
	}

	// look for correct vh channel sysex
	bool vh_chan_sysex_list[16];
	int no_vh_chan_sysex = 0;

	for (chan=0; chan<16; chan++)
	{
		vh_chan_sysex_list[chan] = false;
	}

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf,id,&time,&data,&length);
		int vh_chan = GlobalUtilities::is_vh_channel_sysex(data, length);
		if (vh_chan >= 0)
		{
			if (vh_channel[vh_chan])
			{
				vh_chan_sysex_list[vh_chan] = true;
				no_vh_chan_sysex++;
			}
			else
			{
				HP_DeleteEvent(mf,id);
			}
		}
		HP_Delete(data);
	}

	if (no_vh_chan_sysex > 1)
	{ // delete all vh_chan_sysex
		HP_Rewind(mf);
		while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (type == HP_NOTE) break;
			if (type != HP_SYSEX) continue;
			HP_ReadSysex(mf,id,&time,&data,&length);
			int vh_chan = GlobalUtilities::is_vh_channel_sysex(data, length);
			if (vh_chan >= 0)
			{
				HP_DeleteEvent(mf,id);
			}
			HP_Delete(data);
		}
	}
}

//**************************************************************************
//*
//*		add_standard_hall_chorus_variation
//*		subordinate function of eval_voicefile_revoice
//*
//*		insert Reverb Type Hall3 if no other Reverb Type defined
//*		insert Chorus Type Chorus3 if no other Chorus Type defined
//*		insert Variation Block if no other Variation defined
//*
//**************************************************************************

void HPMF_Interface::add_standard_hall_chorus_variation(int start_time)
{
	bool is_reverb = false;
	bool is_chorus = false;
	bool is_variation;

/* 
  F0 43 10 4C 02 01 00 01 11 F7  ; (XG) Reverb Type HALL 3
  F0 43 10 4C 02 01 20 42 10 F7  ; (XG) Chorus Type CHORUS 3
  F0 43 10 4C 02 01 40 4B 08 F7  ; (XG) Variation Type Stereo Amp Simulator 3
  F0 43 10 4C 02 01 42 00 18 F7  ; (XG) Variation Drive 24
  F0 43 10 4C 02 01 46 00 2A F7  ; (XG) Variation LPF Cutoff 2.5kHz
  F0 43 10 4C 02 01 48 00 26 F7  ; (XG) Variation Output Level 38
  F0 43 10 4C 02 01 58 26 F7 	 ; (XG) Send Variation to Reverb 38
  F0 43 10 4C 02 01 59 0C F7 	 ; (XG) Send Variation to Chorus 12
  F0 43 10 4C 02 01 5A 01 F7 	 ; (XG) Variation Connection: System
*/

	unsigned char reverb_hall3[] = {0xf0,0x43,0x10,0x4c,0x02,0x01,0x00,0x01,0x11,0xf7};
	unsigned char chorus3[]      = {0xf0,0x43,0x10,0x4c,0x02,0x01,0x20,0x42,0x10,0xf7};
	unsigned char stereo_amp[]   = {0xf0,0x43,0x10,0x4c,0x02,0x01,0x40,0x4b,0x08,0xf7};
	unsigned char drive24[]      = {0xf0,0x43,0x10,0x4c,0x02,0x01,0x42,0x00,0x18,0xf7};
	unsigned char cutoff[]       = {0xf0,0x43,0x10,0x4c,0x02,0x01,0x46,0x00,0x2a,0xf7};
	unsigned char output[]       = {0xf0,0x43,0x10,0x4c,0x02,0x01,0x48,0x00,0x26,0xf7};

	unsigned char to_reverb[]    = {0xf0,0x43,0x10,0x4c,0x02,0x01,0x58,0x26,0xf7};
	unsigned char to_chorus[]    = {0xf0,0x43,0x10,0x4c,0x02,0x01,0x59,0x0c,0xf7};
	unsigned char con_sys[]      = {0xf0,0x43,0x10,0x4c,0x02,0x01,0x5a,0x01,0xf7};

	unsigned char reverb_type[]	= {0xf0,0x43,0x10,0x4c,0x02,0x01,0x00};
	unsigned char chorus_type[]	= {0xf0,0x43,0x10,0x4c,0x02,0x01,0x20};
	unsigned char con[]			= {0xf0,0x43,0x10,0x4c,0x02,0x01,0x5a};
	int len = 7;

	bool is_variation_sysex;
	bool is_system;
	bool is_insertion;
	int variation_insertion_channel;

	int id, chan, time, type;
	unsigned char *data;
	int length;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf,id,&time,&data,&length);
		if (GlobalUtilities::compare_data(reverb_type,len,data,length-3))
		{
			// reverb type in file
			is_reverb = true;
			HP_Delete(data);
			continue;
		}
		if (GlobalUtilities::compare_data(chorus_type,len,data,length-3))
		{
			// chorus type in file
			is_chorus = true;
			HP_Delete(data);
			continue;
		}
		HP_Delete(data);
	}

	is_variation = is_variation_effect(&is_variation_sysex,
		                               &is_system,
									   &is_insertion,
									   &variation_insertion_channel);
	HP_SetFirst(mf, HP_LAST);
	if (!is_reverb) HP_InsertSysEx(mf,start_time,reverb_hall3);
	if (!is_chorus) HP_InsertSysEx(mf,start_time,chorus3);
	if (!is_variation)
	{
		HP_InsertSysEx(mf,start_time,stereo_amp);
		HP_InsertSysEx(mf,start_time,drive24);
		HP_InsertSysEx(mf,start_time,cutoff);
		HP_InsertSysEx(mf,start_time,output);
		HP_InsertSysEx(mf,start_time,to_reverb);
		HP_InsertSysEx(mf,start_time,to_chorus);
		HP_InsertSysEx(mf,start_time,con_sys);
	}
}

//**************************************************************************
//*
//*		remove_standard_drum_sysex
//*		not used at this time
//*
//**************************************************************************

void HPMF_Interface::remove_standard_drum_sysex()
{
	int id, chan, time, type, length;
	unsigned char* data;
	unsigned char drum[]  = {0xF0,0x43,0x10,0x4C}; 	// (XG) Drum Setup (no 0) Note C3 , Reverb Send Level  0

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf,id,&time,&data,&length);

		if (GlobalUtilities::compare_data(drum,4,data,4) && ((data[4]&0x30)==0x30))
		{
			HP_DeleteEvent(mf,id);
		}
		HP_Delete(data);
	}
}

//**************************************************************************
//*
//*		add_standard_drum_sysex
//*		subordinate function of eval_voicefile_revoice
//*
//**************************************************************************

void HPMF_Interface::add_standard_drum_sysex(int start_time)
{
	int id, chan, time, type, length;
	unsigned char* data;

	unsigned char drum1[]  = {0xF0,0x43,0x10,0x4C,0x30,0x24,0x05,0x00,0xF7}; 	// (XG) Drum Setup (no 0) Note C3 , Reverb Send Level  0
	unsigned char drum2[]  = {0xF0,0x43,0x10,0x4C,0x30,0x2A,0x05,0x5C,0xF7}; 	// (XG) Drum Setup (no 0) Note F#3, Reverb Send Level 92
	unsigned char drum3[]  = {0xF0,0x43,0x10,0x4C,0x30,0x2C,0x05,0x5C,0xF7}; 	// (XG) Drum Setup (no 0) Note G#3, Reverb Send Level 92
	unsigned char drum4[]  = {0xF0,0x43,0x10,0x4C,0x30,0x2E,0x05,0x5C,0xF7}; 	// (XG) Drum Setup (no 0) Note A#3, Reverb Send Level 92
	unsigned char drum5[]  = {0xF0,0x43,0x10,0x4C,0x30,0x2A,0x02,0x66,0xF7}; 	// (XG) Drum Setup (no 0) Note F#3, Level 102
	unsigned char drum6[]  = {0xF0,0x43,0x10,0x4C,0x30,0x2C,0x02,0x70,0xF7}; 	// (XG) Drum Setup (no 0) Note G#3, Level 112
	unsigned char drum7[]  = {0xF0,0x43,0x10,0x4C,0x30,0x2E,0x02,0x7A,0xF7}; 	// (XG) Drum Setup (no 0) Note A#3, Level 122
	unsigned char drum8[]  = {0xF0,0x43,0x10,0x4C,0x31,0x45,0x02,0x32,0xF7}; 	// (XG) Drum Setup (no 1) Note A5 , Level 50
	unsigned char drum9[]  = {0xF0,0x43,0x10,0x4C,0x31,0x52,0x02,0x49,0xF7}; 	// (XG) Drum Setup (no 1) Note A#6, Level 73
	unsigned char drum10[] = {0xF0,0x43,0x10,0x4C,0x30,0x24,0x02,0x68,0xF7}; 	// (XG) Drum Setup (no 0) Note C3 , Level 104
	unsigned char drum11[] = {0xF0,0x43,0x10,0x4C,0x30,0x26,0x02,0x7C,0xF7}; 	// (XG) Drum Setup (no 0) Note D3 , Level 124
	unsigned char drum12[] = {0xF0,0x43,0x10,0x4C,0x31,0x36,0x05,0x7F,0xF7}; 	// (XG) Drum Setup (no 1) Note F#4, Reverb Send Level 127

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf,id,&time,&data,&length);

		if (GlobalUtilities::compare_data(drum1,4,data,4))
		{
			if ((data[4]&0x30)==0x30)
			{
				HP_Delete(data);
				return;
			}
		}
		HP_Delete(data);
	}

	HP_InsertSysEx(mf,start_time,drum1);
	HP_InsertSysEx(mf,start_time,drum2);
	HP_InsertSysEx(mf,start_time,drum3);
	HP_InsertSysEx(mf,start_time,drum4);
	HP_InsertSysEx(mf,start_time,drum5);
	HP_InsertSysEx(mf,start_time,drum6);
	HP_InsertSysEx(mf,start_time,drum7);
	HP_InsertSysEx(mf,start_time,drum8);
	HP_InsertSysEx(mf,start_time,drum9);
	HP_InsertSysEx(mf,start_time,drum10);
	HP_InsertSysEx(mf,start_time,drum11);
	HP_InsertSysEx(mf,start_time,drum12);
}

//**************************************************************************
//*
//*		add_insertions
//*		subordinate function of eval_voicefile_revoice
//*
//**************************************************************************

bool HPMF_Interface::add_insertions
     (int start_time, int part, int block, HP_MIDIFILE_MODULE* mf_voice)
{
	// for instance:
	// F0 43 10 4C 03 bb 00 01 11 F7; (XG) Insertion Type, Eff. Block bb, HALL 3 
	// F0 43 10 4C 03 bb 0B 1E F7 	; (XG) Insertion Eff. Block bb, Dry/Wet D34>W
	// F0 43 10 4C 03 bb 0C pp F7 	; (XG) Insertion Part, Eff. Block bb, Part pp 

	int i;
	unsigned char insertion_top[] = {0xf0, 0x43, 0x10, 0x4c, 0x03};

	int id, chan, time, type, length;
	unsigned char* data;

	int blocklist[16];
	update_blocklist(mf, blocklist);
	
	for (chan=0; chan<16; chan++)
	{
		if (blocklist[chan]==block)
		{
			return false;
		}
	}

	unsigned char* insertion_data_list[128];
	int no_insertion = 0;
	unsigned char* dry_wet_data = NULL;
	unsigned char assign_block[] = {0xf0, 0x43, 0x10, 0x4c, 0x03, 0x7f, 0x0c, 0x7f, 0xf7};

	HP_Rewind(mf_voice);
	while (HP_ReadEvent(mf_voice,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf_voice,id,&time,&data,&length);
		if (!GlobalUtilities::compare_data(insertion_top,5,data,5))
		{
			HP_Delete(data);
			continue;
		}

		data[5] = block;

		if (data[6] == 0x0b)
		{
			if (dry_wet_data != NULL)
			{
				HP_Delete(dry_wet_data);
			}
			dry_wet_data = data;
		}
		else
		{
			insertion_data_list[no_insertion] = data;
			no_insertion++;
		}
	}

	// insert insertions
	HP_SetFirst(mf, HP_LAST);
	for (i=0; i<no_insertion; i++)
	{
		HP_InsertSysEx(mf,start_time,insertion_data_list[i]);
		HP_Delete(insertion_data_list[i]);
	}

	if (no_insertion > 0)
	{
		if (dry_wet_data != NULL)
		{
			HP_InsertSysEx(mf,start_time,dry_wet_data);
			HP_Delete(dry_wet_data);
		}

		assign_block[5] = block;
		assign_block[7] = part;
		HP_InsertSysEx(mf,start_time,assign_block);
	}
	else
	{
		if (dry_wet_data != NULL)
		{
			HP_Delete(dry_wet_data);
		}
	}
	
	blocklist[part] = block;
	return true;
}

//**************************************************************************
//*
//*		add_multipart
//*		subordinate function of eval_voicefile_revoice
//*
//**************************************************************************

void HPMF_Interface::add_multipart(int start_time, int part, HP_MIDIFILE_MODULE* mf_voice)
{
/*
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
*/

	struct{int type; unsigned char* data; bool is_default;} mp_list[512];
	int no_mp = 0;
	unsigned char sysex_top[] = {0xf0, 0x43, 0x10, 0x4c};
	unsigned char rcvchannel_data[]  = {0xf0,0x43,0x10,0x4c,0x08,0x00,0x04,0x00,0xf7};

	int id, chan, time, type, length;
	unsigned char* data;

	HP_Rewind(mf_voice);
	while (HP_ReadEvent(mf_voice,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf_voice,id,&time,&data,&length);
		if (!GlobalUtilities::compare_data(sysex_top,4,data,4))
		{
			HP_Delete(data);
			continue;
		}
		if ((data[4]!=0x08)&&(data[4]!=0x0a))
		{
			HP_Delete(data);
			continue;
		}


		if (data[4]==0x08)
		{
			switch (data[6])
			{
			case 0x0c:
				mp_list[no_mp].type = VELOCITY_SENSE_DEPTH;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x40;
				no_mp++;
				continue;
			case 0x0d:
				mp_list[no_mp].type = VELOCITY_SENSE_OFFSET;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x40;
				no_mp++;
				continue;
			case 0x1e:
				mp_list[no_mp].type = MW_FILTER_CONTROL;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x40;
				no_mp++;
				continue;
			case 0x20:
				mp_list[no_mp].type = MW_LFO_PMOD;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x0a;
				no_mp++;
				continue;
			case 0x21:
				mp_list[no_mp].type = MW_LFO_FMOD;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x00;
				no_mp++;
				continue;
			case 0x22:
				mp_list[no_mp].type = MW_LFO_AMOD;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x00;
				no_mp++;
				continue;
			case 0x4e:
				mp_list[no_mp].type =  CAT_FILTER_CONTROL;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x40;
				no_mp++;
				continue;
			case 0x50:
				mp_list[no_mp].type =  CAT_LFO_PMOD;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x00;
				no_mp++;
				continue;
			case 0x51:
				mp_list[no_mp].type =  CAT_LFO_FMOD;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x00;
				no_mp++;
				continue;
			case 0x52:
				mp_list[no_mp].type =  CAT_LFO_AMOD;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x00;
				no_mp++;
				continue;
			case 0x72:
				mp_list[no_mp].type =  EQ_BASS_GAIN;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x40;
				no_mp++;
				continue;
			case 0x73:
				mp_list[no_mp].type =  EQ_TREBLE_GAIN;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x40;
				no_mp++;
				continue;
			case 0x76:
				mp_list[no_mp].type =  EQ_BASS_FREQU;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x0c;
				no_mp++;
				continue;
			case 0x77:
				mp_list[no_mp].type =  EQ_TREBLE_FREQU;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x36;
				no_mp++;
				continue;
			default:
				HP_Delete(data);
				continue;
 			}
		}// end data[4] == 0x08
		else if(data[4]==0x0a)
		{
			switch(data[6])
			{
			case 0x40:
				mp_list[no_mp].type =  OFFSET_LEVEL_CONTROL_MW;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x40;
				no_mp++;
				continue;
			case 0x42:
				mp_list[no_mp].type =  OFFSET_LEVEL_CONTROL_CAT;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x40;
				no_mp++;
				continue;
			default:
				HP_Delete(data);
				continue;
 			}
		} // end data[4] == 0x0a
	} // end loop voicefile 
	// mp_list is filled

	// Set part in all multi_part-sysex

	int i;

	for (i=0; i<no_mp; i++)
	{
		(mp_list[i].data)[5] = part;
	}

	// insert multiparts:
	
	HP_SetFirst(mf, HP_LAST);

	// 1. EQ Bass Gain
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==EQ_BASS_GAIN) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf, start_time, mp_list[i].data);
			break;
		}
	}
	// 2. EQ Treble Gain
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==EQ_TREBLE_GAIN) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf, start_time, mp_list[i].data);
			break;
		}
	}
	// 3. EQ Bass Frequ.
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==EQ_BASS_FREQU) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf, start_time, mp_list[i].data);
			break;
		}
	}
	// 4. EQ Treble Frequ.
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==EQ_TREBLE_FREQU) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf, start_time, mp_list[i].data);
			break;
		}
	}

	// 5. Velocity Sense Depth
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==VELOCITY_SENSE_DEPTH) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf, start_time, mp_list[i].data);
			break;
		}
	}

	// 6. Velocity Sense Offset
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==VELOCITY_SENSE_OFFSET) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf, start_time, mp_list[i].data);
			break;
		}
	}

	// 7. CAT LFO Pmod.
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==CAT_LFO_PMOD) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf, start_time, mp_list[i].data);
			break;
		}
	}

	// 8. CAT LFO Fmod.
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==CAT_LFO_FMOD) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf, start_time, mp_list[i].data);
			break;
		}
	}

	// 9. CAT LFO Amod
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==CAT_LFO_AMOD) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf, start_time, mp_list[i].data);
			break;
		}
	}

	// 10. MW LFO Pmod
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==MW_LFO_PMOD) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf, start_time, mp_list[i].data);
			break;
		}
	}

	// 11. MW LFO Fmod
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==MW_LFO_FMOD) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf, start_time, mp_list[i].data);
			break;
		}
	}

	// 12. MW LFO Amod
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==MW_LFO_AMOD) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf, start_time, mp_list[i].data);
			break;
		}
	}

	// 13. CAT Filter Control
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==CAT_FILTER_CONTROL) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf, start_time, mp_list[i].data);
			break;
		}
	}

	// 14. Offset Level Control CAT
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==OFFSET_LEVEL_CONTROL_CAT) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf, start_time, mp_list[i].data);
			break;
		}
	}

	// 15. MW Filter Control
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==MW_FILTER_CONTROL) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf, start_time, mp_list[i].data);
			break;
		}
	}

	// 16. Offset Level Control MW
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==OFFSET_LEVEL_CONTROL_MW) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf, start_time, mp_list[i].data);
			break;
		}
	}

	for (i=0; i<no_mp; i++)
	{
		HP_Delete(mp_list[i].data);
	}

	rcvchannel_data[5] = part;
	rcvchannel_data[7] = part;
	HP_InsertSysEx(mf,start_time,rcvchannel_data);
}

//**************************************************************************
//*
//*		update_blocklist
//*		fills a list blocklist[part] = effect_block
//*		only parts < 16 used
//*
//**************************************************************************

void HPMF_Interface::update_blocklist(HP_MIDIFILE_MODULE *mf_par, int blocklist[16])
{
	int id, chan, time, type, length;
	int part;
	unsigned char* data;
	int variation_block = -2;
	int variation_part = -1;

	unsigned char insertion_top[] = {0xf0, 0x43, 0x10, 0x4c, 0x03};
	// F0 43 10 4C 03 bb 0C pp F7 	; (XG) Insertion Part, Eff. Block bb, Part pp 

	unsigned char variation_insertion[] = {0xf0, 0x43, 0x10, 0x4c, 0x02, 0x01, 0x5a, 0x00, 0xf7};
	unsigned char variation_part_top[] = {0xf0, 0x43, 0x10, 0x4c, 0x02, 0x01, 0x5b};

	for (part=0; part<16; part++)
	{
		blocklist[part] = -1;
	}


	HP_Rewind(mf_par);
	while (HP_ReadEvent(mf_par,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf_par,id,&time,&data,&length);
		if (GlobalUtilities::compare_data(insertion_top,5,data,5))
		{
			if(data[6]==0x0c)
			{
				int block = data[5];
				part = data[7];
				if (part>15) continue;
				blocklist[part] = block;
			}
		}
		else if (GlobalUtilities::compare_data(variation_insertion,9,data,9))
		{
			variation_block = -2;
		}
		else if (GlobalUtilities::compare_data(variation_part_top,7,data,7))
		{
			variation_part = data[7];
		}
		
		HP_Delete(data);
	}

	if ((variation_block==-2)&&(variation_part>0))
	{
		blocklist[variation_part]= -2; 
	}
}

//**************************************************************************
//*
//*		update_chan_blocklist
//*		fills a list chan_blocklist[chan] = effect_block by a given
//*		blocklist (index part, value effect_block
//*		use the sequence update_blocklist -> update_chan_blocklist
//*
//**************************************************************************

void HPMF_Interface::update_chan_blocklist(int blocklist[16], int chan_blocklist[16], int block_chanlist[16])
{
	int bl, part;

	// init: empty
	for (bl=0; bl<16; bl++)
	{
		block_chanlist[bl] = -1;
	}
	// init: part = chan; may be changed by Multipart Rcv Chan
	for (part=0; part<16; part++)
	{
		bl = blocklist[part];
		if (bl > -1)
		{
			block_chanlist[bl] = part;
		}
	}

	int id, chan, time, type, length;
	unsigned char* data;
	unsigned char rcv_chan_top[] = {0xf0, 0x43, 0x10, 0x4c, 0x08};
	// Multipart rcv-chan: F0 43 10 4C 08 <part> 04 chan F7

	// init chan_blocklist, may only be changed by Multipart Rcv Chan 
	for (chan=0; chan<16; chan++)
	{	
		chan_blocklist[chan]= (blocklist[chan]==-2)?-1:blocklist[chan];
	}

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf,id,&time,&data,&length);
		if (GlobalUtilities::compare_data(rcv_chan_top,5,data,5))
		{
			if (data[6]!=0x04)
			{	// no rcv channel
				HP_Delete(data);
				continue;
			}
			if (data[5]==data[7])
			{	// part == chan
				HP_Delete(data);
				continue;
			}
			part = data[5];
			int chan = data[7];
			int block = chan_blocklist[part];
			chan_blocklist[part] = -1;
			chan_blocklist[chan] = block;
			block_chanlist[block] = chan;
		}
		HP_Delete(data);
		continue;
	}
}


//**************************************************************************
//*
//*		analyze_master_volume
//*		finds out, if a Master Volume SysEx exists
//*     if more than one Master Volume SysEx delete the preceding ones
//*
//*		change = true:
//*			exchanges all GM2 Master Volume SysEx by XG Master Volume SysEx
//*			inserts XG Master Volume SysEx 127 before first note
//*		returns -1 if no Master Volume SysEx found, otherwise max. Volume (MSB)

//*
//**************************************************************************

int	 HPMF_Interface::analyze_master_volume(bool change)
{
	int id, chan, time, type, length;
	int time_of_first_note = -1;
	bool master_volume_arrived_before_note = false;
	unsigned char* data;
	int max_vol = -1;
	int act_vol = -1;
	int dummy;
	int i;

	ArrayTwoInts all_vols;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			if (time_of_first_note == -1) time_of_first_note = time;
			continue;
		}

		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf,id,&time,&data,&length);
		if((length!=XG_master_volume_data_len) && 
		   (length!=GM2_master_volume_data_len))
		{
			HP_Delete(data);
			continue;
		}

		// analyze GM2 Master Volumes an converte if wanted
		if ((length==GM2_master_volume_data_len) && 
			(data[1]==GM2_master_volume_data[1]) && 
			(data[3]==GM2_master_volume_data[3]) &&
			(data[4]==GM2_master_volume_data[4])   )
		{	// GM2 Master Volume; convert to XG Master Volume
			act_vol = data[6]; // MSB, ignore LSB
			if (change)
			{
				XG_master_volume_data[7] = act_vol;
				HP_ChangeSysex(mf,id,XG_master_volume_data);
			}
			if (time_of_first_note==-1) master_volume_arrived_before_note = true;
			all_vols.add(act_vol,-1);
			HP_Delete(data);
			continue;
		}

		if (length==XG_master_volume_data_len)
		{ // XG Master Volume ?
			bool is = true;
			int i;
			for (i=1; i<7; i++)
			{
				if (data[i] != XG_master_volume_data[i])
				{
					is = false;
					break;
				}
			}
			if (is)
			{
				if (time_of_first_note==-1) master_volume_arrived_before_note = true;
				act_vol = data[7];
				all_vols.add(act_vol,-1);
			}
			HP_Delete(data);
			continue;
		}
		HP_Delete(data);
	}

	int no_vols = all_vols.get_length();
	for (i=0; i<no_vols; i++)
	{
		all_vols.get(i,&act_vol,&dummy);
		if (act_vol> max_vol)
		{
			max_vol = act_vol;
		}
	}

	if(!master_volume_arrived_before_note)
	{
		if (change)
		{
			int time_of_sysex = time_of_first_note>0?time_of_first_note-1:time_of_first_note;
			HP_SetFirst(mf);
			XG_master_volume_data[7]= 127;
			HP_InsertSysEx(mf,time_of_sysex,XG_master_volume_data);
		}
		max_vol = 127;
	}


/*
	int id_of_mastervolume_before = -1;
	
	int time_of_first_note = -1;
	bool master_volume_arrived_before_note = false;
	
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			if (time_of_first_note == -1) time_of_first_note = time;
			continue;
		}

		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf,id,&time,&data,&length);
		if((length!=XG_master_volume_data_len) && 
		   (length!=GM2_master_volume_data_len))
		{
			HP_Delete(data);
			continue;
		}

		if ((length==GM2_master_volume_data_len) && 
			(data[1]==GM2_master_volume_data[1]) && 
			(data[3]==GM2_master_volume_data[3]) &&
			(data[4]==GM2_master_volume_data[4])   )
		{	// GM2 Master Volume; convert to XG Master Volume
			int mv = data[6]; // MSB, ignore LSB
			if (change)
			{
				XG_master_volume_data[7] = mv;
				HP_ChangeSysex(mf,id,XG_master_volume_data);
			}
			if (id_of_mastervolume_before >= 0)
			{
				max_vol = -1;
			}

			if (mv>max_vol) max_vol = mv;
			if (time_of_first_note==-1) master_volume_arrived_before_note = true;
			HP_Delete(data);

			if (id_of_mastervolume_before >= 0)
			{
				HP_DeleteEvent(mf,id_of_mastervolume_before);
			}
			id_of_mastervolume_before = id;

			continue;
		}

		if (length==XG_master_volume_data_len)
		{ // XG Master Volume ?
			bool is = true;
			int i;
			for (i=1; i<7; i++)
			{
				if (data[i] != XG_master_volume_data[i])
				{
					is = false;
					break;
				}
			}
			if (is)
			{
				if (id_of_mastervolume_before >= 0)
				{
					max_vol = -1;
				}
			
				if (data[7]>max_vol) max_vol = data[7];

				if (id_of_mastervolume_before >= 0)
				{
					HP_DeleteEvent(mf,id_of_mastervolume_before);
				}
				id_of_mastervolume_before = id;

				if (time_of_first_note==-1) master_volume_arrived_before_note = true;
			}
			HP_Delete(data);
			continue;
		}
		HP_Delete(data);
	}

	if(!master_volume_arrived_before_note && change)
	{
		int time_of_sysex = time_of_first_note>0?time_of_first_note-1:time_of_first_note;
		HP_SetFirst(mf);
		XG_master_volume_data[7]= 127;
		HP_InsertSysEx(mf,time_of_sysex,XG_master_volume_data);
		max_vol = 127;
	}
*/
	return max_vol;
}

void HPMF_Interface::eval_insert_or_change_master_volume(int master_volume)
{
	int id, chan, time, type;
	unsigned char* data;
	int length;
	
	// if needed: 
	//		insert initial Master Volume sysex 127
	//		change all GM2 SysEx to XG
	int max_vol = analyze_master_volume(true); // 

	
	if (max_vol==master_volume) return;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf,id,&time,&data,&length);
		if (length!=XG_master_volume_data_len)
		{
			HP_Delete(data);
			continue;
		}

		bool is = true;
		int i;
		for (i=1; i<7; i++)
		{
			if (data[i] != XG_master_volume_data[i])
			{
				is = false;
				break;
			}
		}
		if (is)
		{
			int vol = data[7];
			int new_vol;
			if (max_vol == 0)
			{
				new_vol = master_volume;
			}
			else
			{
				new_vol = (int) (((float)master_volume*(float)vol)/(float)max_vol);
			}
			data[7] = new_vol;
			HP_ChangeSysex(mf,id,data);
		}
		HP_Delete(data);
	}
}


//****************************************************************************************
//*
//*		find_vh_channel
//*     finds the channels with notes and velocities lower than 5
//*     fills vh_channel, vh_channel_sysex_exist, vocoder_sysex_exist, vh_ad_off_sysex_exist
//*		vh_ad_on_sysex_exist;
//*		returns no of vh_channels
//*
//****************************************************************************************

int  HPMF_Interface::find_vh_channel()
{
	int i;
	int id, chan, time, type, note, velocity, length;
	int max_vel[16];
	unsigned char* data;
	int no_vh_chan = 0;


	for (chan=0; chan<16; chan++)
	{
		max_vel[chan]= -1;
	}
	for (i=0; i<16; i++)
	{
		vh_channel[i] = false;
		vh_channel_sysex_exist[i] = false;
	}

	update_no_notes(no_notes);

	vocoder_sysex_exist = false;
	vh_ad_on_sysex_exist = false;
	vh_ad_off_sysex_exist = false;

	HP_Rewind(mf);

	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			HP_ReadNote(mf,id,&time, &chan, &note, &velocity, &length);
			if (velocity > max_vel[chan]) max_vel[chan] = velocity;
		}
		if (type == HP_SYSEX)
		{
			HP_ReadSysex(mf,id,&time,&data,&length);

			int vh_chan = GlobalUtilities::is_vh_channel_sysex(data, length);
			if (vh_chan != -1)
			{
				if (!vh_channel_sysex_exist[vh_chan]) 
				{
					vh_channel_sysex_exist[vh_chan]	= true;
					HP_Delete(data);
					continue;
				}
			}

			if ((vocoder_sysex_exist==false)&&(length==10))
			{
				if (GlobalUtilities::is_vocoder_sysex(data,length))
				{
					vocoder_sysex_exist = true;
					HP_Delete(data);
					continue;
				}
			}

			if ((vh_ad_on_sysex_exist==false)&&(length==9))
			{
				if (GlobalUtilities::is_vh_ad_on_sysex(data,length))
				{
					vh_ad_on_sysex_exist = true;
					HP_Delete(data);
					continue;
				}
			}

			if ((vh_ad_off_sysex_exist==false)&&(length==9))
			{
				if (GlobalUtilities::is_vh_ad_off_sysex(data,length))
				{
					vh_ad_off_sysex_exist = true;
					HP_Delete(data);
					continue;
				}
			}
			HP_Delete(data);
		}
	}

	int least_max_vel[16] = {127,127,127,127,127,127,127,127,
							 127,127,127,127,127,127,127,127};
	for (chan=0; chan<16; chan++)
	{
		if (no_notes[chan]==0) continue;

		if (max_vel[chan]<least_max_vel[chan])
		{
			least_max_vel[chan] = max_vel[chan];
		}
		if (least_max_vel[chan]<=5)
		{
			vh_channel[chan] = true;
			no_vh_chan++;
		}
	}
	fill_patchname_list();

/*
	for (chan=0; chan<16; chan++)
	{
		CString r;
		r.Format("chan %i vh_channel? %s", chan, vh_channel[chan]?"yes":"no");
		MessageBox(r);
	}
*/
	
	return no_vh_chan;
}

//****************************************************************************************
//*
//*		is_vocalharmony_vocoder()
//*     looks if vocalharmony method vocoder defined
//*     with_delete true: deletes all vh sysexes
//*		returns true when vocoder
//*
//****************************************************************************************

bool HPMF_Interface::is_vocalharmony_vocoder()
{
	bool result = true;
	int id, chan, time, type, length;
	unsigned char* data;
	int i;

	if (!with_vh_sysexes(false))
	{
		return false;
	}

	// Look only for F0 43 10 4C 04 00 14 xx F7 	; (XG) (Spec. Eff.) VH Song Harmony Channel xx

	unsigned char vocoder_channel_sysex_start[7] = {0xf0, 0x43, 0x10, 0x4c, 0x04, 0x00, 0x14};

	HP_Rewind(mf);
	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if (type == HP_SYSEX)
		{
			result = true;
			HP_ReadSysex(mf,id,&time,&data,&length);
			if (length != 9)
			{
				HP_Delete(data);
				continue;
			}
			else
			{
				for (i=0; i<7; i++)
				{
					if (data[i] != vocoder_channel_sysex_start[i])
					{
						result = false;
						break;
					}
				}
				HP_Delete(data);

				if (result)
				{
					return true;
				}
			}
		}
		continue;
	}
	return false;
}


//****************************************************************************************
//*
//*		with_vh_sysexes(with_delete)
//*     looks if vh sysexes exist that define other vh types than vocoder
//*     with_delete true: deletes all these sysexes
//*		vh_ad_on_sysex_exist;
//*		returns true when vh sysexes exist
//*
//****************************************************************************************

bool  HPMF_Interface::with_vh_sysexes(bool with_delete)
{
	int id, chan, time, type, length;
	int dummy1, dummy2;
	unsigned char* data;

	HP_Rewind(mf);

	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if (type == HP_SYSEX)
		{
			HP_ReadSysex(mf,id,&time,&data,&length);

			if (GlobalUtilities::is_vh_sysex(data,length))
			{
				HP_Delete(data);
				if (!with_delete)
				{
					return true;
				}
				else
				{
					HP_DeleteEvent(mf, id);
				}

			}
		}
	}

	if (with_delete)
	{
		eval_xg_convert(&dummy1,&dummy2);
	}

	return false;
}


//**************************************************************************
//*
//*		is_variation_effect
//*     looks, if midifile has variation effect
//*
//**************************************************************************

bool HPMF_Interface::is_variation_effect(bool *is_variation_sysex, 
										 bool *is_system, bool *is_insertion, 
										 int *variation_insertion_channel)
{
	unsigned char consystem[]      = {0xf0,0x43,0x10,0x4c,0x02,0x01,0x5a,0x01,0xf7};
	// index 7 -> 1: system; index 7 -> 0: insertion

	// (XG) Variation , part no = index 7 
	unsigned char variation_insertion_part[] = {0xf0,0x43,0x10,0x4c,0x02,0x01,0x5b,0x00,0xf7}; 
	
	int len_con = 9;
	int len_part = 7; // stop before part-number


	int id, chan, time, type;
	unsigned char *data;
	int length;

	*is_variation_sysex = false;
	*is_system = false;
	*is_insertion = true; // default
	*variation_insertion_channel = -1;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf,id,&time,&data,&length);
		if ((length==9)||(length==10))
		{
			bool compare;

			compare = GlobalUtilities::compare_data(consystem,6,data,6);
			if (compare && ((int)(data[6])>=0x40))
			{
				// sysex starts with F0 43 10 4C 02 01 xx; xx >= 40
				*is_variation_sysex = true;
			}

			compare = GlobalUtilities::compare_data(consystem,len_con-2,data,length-2);
			if (compare)
			{
				if (data[7]==0x01)
				{
					*is_system = true;
					*is_insertion = false;
				}
				else if (data[7]==0x00)
				{
					*is_system = false;
					*is_insertion = true;
				}
			}
			
			compare = GlobalUtilities::compare_data(variation_insertion_part,7,data,length-2);
			if (compare)
			{
				*variation_insertion_channel = (int)(data[7]);
			}
			HP_Delete(data);
		}
	}
	if (*variation_insertion_channel==-1)
	{
		*is_insertion = false;
	}
	return (*is_variation_sysex && (*is_system || *is_insertion));
}

//**************************************************************************
//*
//*		insertion_sysex_defined
//*     looks, if insertion sysex are defined at given channel
//*
//**************************************************************************

bool HPMF_Interface::insertion_sysex_defined(int chan, int *block)
{
	int part;
	bool is_insertion = false;
	*block = -1;
	int blocklist[16];
	update_blocklist(mf, blocklist); // index = part < 16, value = block or -1
	fill_part_chan_list();			 // part_chan_list: index = part, value = chan;

	for (part=0; part<16; part++)
	{
		if (part_chan_list[part]==chan)
		{
			if (blocklist[part] == -1) continue;
			*block = blocklist[part];
			is_insertion = true;
			break;
		}
	}

	return is_insertion;
}

//**************************************************************************
//*
//*		get_reverb_chorus_variation_value
//*     reads the last values of reverb, chorus and variation before the first notes
//*
//**************************************************************************

void HPMF_Interface::get_reverb_chorus_variation_value(int chan, int *reverb, int *chorus, int *variation)
{
	*reverb = 0;
	*chorus = 0;
	*variation = 0;

	int id, ch, time, type, number, value;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&ch,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if (ch != chan) continue;

		if (type == HP_REVERB_SEND_LEVEL)
		{
			HP_ReadController(mf, id, &time, &ch, &number, &value);
			*reverb = value;
			continue;
		}
		if (type == HP_CHORUS_SEND_LEVEL)
		{
			HP_ReadController(mf, id, &time, &ch, &number, &value);
			*chorus = value;
			continue;
		}
		if (type == HP_VARIATION_SEND_LEVEL)
		{
			HP_ReadController(mf, id, &time, &ch, &number, &value);
			*variation = value;
			continue;
		}
	}
}

//**************************************************************************
//*
//*		get_drywet_value
//*     reads the dry/wet value for a given block
//*
//**************************************************************************

CString HPMF_Interface::get_drywet_value(int block, int *value)
{
	*value = -1; // no dry/wet defined for this block
	CString text = "Default";
	unsigned char drywet_start[] = {0xf0,0x43,0x10,0x4c,0x03,(unsigned char)(block&0x7f)};
	unsigned char variation_drywet_start[] = {0xf0, 0x43, 0x10, 0x4c, 0x02, 0x01, 0x54};
	// index = 8: dry/wet value

	int len_drywet_start = 6;
	int len_variation_drywet_start = 7;

	int id, chan, time, type;
	unsigned char *data;
	int length;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf,id,&time,&data,&length);
		if (block >= 0)
		{
			if (GlobalUtilities::compare_data(drywet_start,len_drywet_start,data,len_drywet_start))
			{
				if (data[6]==0x0b)
				{
					*value = data[7];
				}
				else if (data[6]==0x42)
				{
					*value = data[8]+128*data[7];
				}
			}
		}
		if (block==-2)
		{
			if (GlobalUtilities::compare_data(variation_drywet_start,len_variation_drywet_start,
				                              data,len_variation_drywet_start))
			{
					*value = data[8]+128*data[7];
			}
		}

		HP_Delete(data);
	}

	if ((*value >= 0)&&(*value < 128))
	{
		text = drywet_text[*value];
	}
	return text;
}

//**************************************************************************
//*
//*		get_drywet_text
//*     returns the text of a dry/wet data
//*
//**************************************************************************

CString HPMF_Interface::get_drywet_text(int value)
{
	return drywet_text[value];
}


/*******************************************************************************/
/*
/* check_and_insert_drywet
/* insert default dry/wet-sysex for insertion-effects, if needed
/* returns true, if drywet inserted
/*
/*******************************************************************************/

bool HPMF_Interface::check_and_insert_drywet(int chan)
{
	bool insertion_defined;
	int block;
	int drywet;
	int id, ch, type, time, length;
	unsigned char *data;
	
	
	HP_SetFirst(mf,HP_LAST);
	
	if (mute[chan]) return false;
	insertion_defined=insertion_sysex_defined(chan,&block);
	if (!insertion_defined) return false;
	get_drywet_value(block,&drywet);
	if ((drywet>=0)&&(drywet<=127)) return false;

	if (block >= 0)
	{ // insertion effects (EFFECT2)
		int time_of_last_block_sysex = -1;
		unsigned char default_drywet[9] = {0xf0, 0x43, 0x10, 0x4c, 0x03, 0x00, 0x0b, 0x40, 0xf7};
		// index 5: block; index 7: value
		unsigned char insertion_sysex_top[5] = {0xf0, 0x43, 0x10, 0x4c, 0x03};

		// insert default drywet-sysex 
		default_drywet[5] = (unsigned char) block;
		
		HP_Rewind(mf);
		while (HP_ReadEvent(mf,&id,&ch,&time,&type)==HP_ERR_NONE)
		{
			if (type==HP_NOTE) break;
			if (type != HP_SYSEX) continue;
			HP_ReadSysex(mf,id,&time,&data,&length);
			if (!GlobalUtilities::compare_data(data, 5, insertion_sysex_top,5)) 
			{
				HP_Delete(data);
				continue;
			}
			if (block != data[5]) 
			{
				HP_Delete(data);
				continue;
			}
			time_of_last_block_sysex = time;
			HP_Delete(data);
		}
		HP_InsertSysEx(mf,time_of_last_block_sysex,default_drywet);
	}

	if (block == -2)
	{ // variation insertion (EFFECT1)
		int time_of_last_variation;
		unsigned char default_variation_drywet[10] = {0xf0, 0x43, 0x10, 0x4c, 0x02, 0x01, 0x54, 0x00, 0x40, 0xf7};
		unsigned char variation_top[6] = {0xf0, 0x43, 0x10, 0x4c, 0x02, 0x01};
		HP_Rewind(mf);
		while (HP_ReadEvent(mf,&id,&ch,&time,&type)==HP_ERR_NONE)
		{
			if (type==HP_NOTE) break;
			if (type != HP_SYSEX) continue;
			HP_ReadSysex(mf,id,&time,&data,&length);
			if (!GlobalUtilities::compare_data(data, 5, variation_top,5)) 
			{
				HP_Delete(data);
				continue;
			}
			time_of_last_variation = time;
			HP_Delete(data);
		}
		HP_InsertSysEx(mf,time_of_last_variation,default_variation_drywet);
	}
	return true;
}


//**************************************************************************
//*
//*		eval_change_effectfilter_controller
//*     changes ctrl 91, 93 and 94 before the first notes
//*		called from EffectFilterDlg
//*		list[chan] = -1: do not change
//*
//**************************************************************************

void HPMF_Interface::eval_change_effectfilter_controller(int reverb_list[16],
														 int chorus_list[16],
														 int variation_list[16])
{
	int id, chan, time, type;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;

		if (type == HP_REVERB_SEND_LEVEL)
		{
			if (reverb_list[chan] != -1)
			{
				HP_ChangeController(mf, id, HP_REVERB_SEND_LEVEL, reverb_list[chan], HP_NO_PERCENT); 
			}
			continue;
		}
		if (type == HP_CHORUS_SEND_LEVEL)
		{
			if (chorus_list[chan] != -1)
			{
				HP_ChangeController(mf, id, HP_CHORUS_SEND_LEVEL, chorus_list[chan], HP_NO_PERCENT); 
			}
			continue;
		}
		if (type == HP_VARIATION_SEND_LEVEL)
		{
			if (variation_list[chan] != -1)
			{
				HP_ChangeController(mf, id, HP_VARIATION_SEND_LEVEL, variation_list[chan], HP_NO_PERCENT); 
			}
			continue;
		}
	}
}

//**************************************************************************
//*
//*		eval_change_effectfilter_drywet
//*     changes drywet-sysex before the first notes
//*		called from EffectFilterDlg
//*		list[chan] = -1: do not change; 
//*     list[chan]=block: change dry/wet 
//*		list[chan]=-2: change dry/wet (variation)
//*
//**************************************************************************

void HPMF_Interface::eval_change_effectfilter_drywet(int block_list[16], int drywet_list[16])
{
//	unsigned char drywet[] = {0xf0,0x43,0x10,0x4c,0x03,(unsigned char)(block&0x7f),0x0b};
	unsigned char drywet_start[] = {0xf0,0x43,0x10,0x4c,0x03};
	unsigned char variation_drywet_start[] = {0xf0,0x43,0x10,0x4c,0x02,0x01,0x54};
	int len_drywet = 5;
	int len_variation_drywet = 7;

	int id, chan, time, type, ch;
	unsigned char *data;
	int length;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf,id,&time,&data,&length);
		if (GlobalUtilities::compare_data(drywet_start,len_drywet,data,len_drywet))
		{
			int block = data[5];
			bool block_found = false;
			if ((data[6]==0x0b)||(data[6]==0x42))
			{	// dry/wet
				for (ch=0; ch<16; ch++)
				{
					if (block == block_list[ch])
					{
						block_found = true;
						break;
					}
				}
				if (block_found)
				{
					if(data[6]==0x0b)
					{
						data[7] = drywet_list[ch];
					}
					else if (data[6]==0x42)
					{
						data[8] = drywet_list[ch];
					}
					HP_ChangeSysex(mf, id, data);
				}
			}
		}
		if (GlobalUtilities::compare_data(variation_drywet_start,len_variation_drywet,data,len_variation_drywet))
		{
			int ch_found = false;

			for (ch=0; ch<16;ch++)
			{
				if (block_list[ch]==-2)
				{
					ch_found = true;
					break;
				}
			}
			if (ch_found)
			{
				data[8] = drywet_list[ch];
				HP_ChangeSysex(mf,id,data);
			}
		}
		HP_Delete(data);
	}
}

//**************************************************************************
//*
//*		compute_drum_velocity
//*     computes min and max velocity of a drum note
//*		called from ChangeDrumVoicesDlg
//*
//**************************************************************************

void HPMF_Interface::compute_drum_velocity(int drum_chan, int note, int *min, int* max)
{
	int min_vel = 128;
	int max_vel = -1;

	int id, chan, time, type, scr_note, velocity,length;;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type != HP_NOTE) continue;
		if (chan != drum_chan) continue;
		HP_ReadNote(mf,id,&time,&chan,&scr_note,&velocity,&length);
		if (scr_note != note) continue;

		if (velocity < min_vel) min_vel = velocity;
		if (velocity > max_vel) max_vel = velocity;
	}
	*min = (min_vel>=128)?(-1):min_vel;
	*max = (max_vel<0)?(-1):max_vel;
}

//**************************************************************************
//*
//*		fill_lyric_chord_edit_list
//*     fills work list for ChordLyricEditor Dialog
//*
//**************************************************************************

void HPMF_Interface::fill_lyric_chord_edit_list(LyricChordEditArray *list)
{
	int i;
	int id, time, chan, type, length;
	int takt, beat, tick;
    unsigned char cr, ct,bn, bt;
    char *chord;
	char *lyric;
	unsigned char *data;
	int takt_no = 1;
	CString takt_no_cstr;

	LyricChordEditElement lce_elem;	
	TAKT_BAR_TIME_ELEM tbte;

	HP_Rewind(mf);

	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{

		if (type==HP_LYRIC)
		{
			int is_linefeed = false;
		
			HP_ReadLyric(mf,id,&time,&lyric);
			lce_elem.text = lyric;
			int len = lce_elem.text.GetLength();

			if (len==1)
			{
				unsigned char ch = (lce_elem.text)[0];

				if (ch==0x0d)
				{
					(lce_elem.text).SetAt(0,'/');
					is_linefeed = true;
				}
				if (ch==0x0a)
				{
					(lce_elem.text).SetAt(0,'<');
					is_linefeed = true;
				}
			}
			else
			{
				unsigned char ch;

				for (i=0; i<len; i++)
				{
					ch = (lce_elem.text)[i];
					if ((ch==0x0d)&&(i==len-1))
					{
						(lce_elem.text).SetAt(i,'/');
					}
					if ((ch==0x0a)&&(i==len-1))
					{
						(lce_elem.text).SetAt(i,'<');
					}
				}
			}

			lce_elem.type = (is_linefeed)?LINEFEED_TYPE:LYRIC_TYPE;
			lce_elem.time = time;

			get_takt_bar_tick_from_time(time,&takt,&beat,&tick);
			(*list).add(&lce_elem, false);
			(*list).set_takt_beat_tick((*list).get_length()-1,takt,beat,tick);
			HP_Delete(lyric);
			continue;
		}

		if (type==HP_CHORD_NAME)
		{
			HP_ReadChord(mf,id,&time,&cr,&ct,&bn,&bt,&chord);
			lce_elem.type = CHORD_TYPE;
			lce_elem.time = time;
			lce_elem.text = chord;
			lce_elem.cr = cr;
			lce_elem.ct = ct;
			lce_elem.bn = bn;
			lce_elem.bt = bt;
			get_takt_bar_tick_from_time(time,&takt,&beat,&tick);
			(*list).add(&lce_elem, false);
			(*list).set_takt_beat_tick((*list).get_length()-1,takt,beat,tick);
			HP_Delete(chord);
			continue;
		}

		if (type==HP_SYSEX)
		{
			HP_ReadSysex(mf,id,&time,&data,&length);
			if (length==9)
			{
				if((data[1]==0x43)&&(data[2]==0x7e)&&(data[3]==0x02))
				{ // chord sysex
					cr = data[4];
					ct = data[5];
					bn = data[6];
					bt = data[7];
					HP_ConvertChordToText(cr,ct,bn,bt,&chord);
					lce_elem.type = CHORD_TYPE;
					lce_elem.time = time;
					lce_elem.text = chord;
					lce_elem.cr = cr;
					lce_elem.ct = ct;
					lce_elem.bn = bn;
					lce_elem.bt = bt;
					get_takt_bar_tick_from_time(time,&takt,&beat,&tick);
					(*list).add(&lce_elem, false);
					(*list).set_takt_beat_tick((*list).get_length()-1,takt,beat,tick);
					HP_Delete(chord);
				}
			}
			HP_Delete(data);
			continue;
		}
	}

	// Fill TAKT_TYPE and BEAT_TYPE elements

	for (i=0; i<takt_bar_time_list_free; i++) 
	{
		tbte = takt_bar_time_list[i];
		if (tbte.bar != 0)
		{ // beats
			lce_elem.type = BEAT_TYPE;
			lce_elem.text = "";
			lce_elem.beat = tbte.bar;
		}
		else
		{ // measure positions
			takt_no_cstr.Format("%i",takt_no);
			lce_elem.type = TAKT_TYPE;
			lce_elem.text = takt_no_cstr;
			lce_elem.beat = 0;
			takt_no++;
		}
		lce_elem.time = tbte.time;
		lce_elem.takt = tbte.takt;
		lce_elem.tick = 0;
		(*list).add(&lce_elem, false);
	}

	(*list).sort();
}

//**************************************************************************
//*
//*		eval_lyrics_chords_editor
//*     inserts all edited chords and lyrics 
//*
//**************************************************************************

void HPMF_Interface::eval_lyrics_chords_editor(LyricChordEditArray *lce_array)
{
	source_changed = false;

	int i;
	int id, time, chan, type, length;
    unsigned char cr, ct,bn, bt;
	char *lyric;
	unsigned char *data;
	int takt_no = 1;
	LyricChordEditElement lce_elem;	

	// delete all lyrics and chords
	HP_Rewind(mf);
	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if ((type==HP_LYRIC)||(type==HP_CHORD_NAME))
		{
			HP_DeleteEvent(mf,id);
			continue;
		}
		if (type==HP_SYSEX)
		{
			HP_ReadSysex(mf,id,&time,&data,&length);
			if (length==9)
			{
				if((data[1]==0x43)&&(data[2]==0x7e)&&(data[3]==0x02))
				{ 
					HP_DeleteEvent(mf,id);
					continue;
				}
			}
		}
	}

	for (i=0; i<lce_array->get_length(); i++)
	{
		int type = lce_array->get_type(i);
		
		if ((type == TAKT_TYPE) || (type == BEAT_TYPE))
		{
			continue;
		}
		if ((type == LYRIC_TYPE)||(type == LINEFEED_TYPE))
		{
			CString text = lce_array->get_text(i);
			time = lce_array->get_time(i);
			GlobalUtilities::convert_CString_to_cstring(&lyric,text);

			int k;
			for (k=0; (k<(int)strlen(lyric)+1) && (k<80); k++)
			{
				if ((lyric[k]=='\\')||(lyric[k]=='/'))
				{
					lyric[k] = linefeed_char;
				}
				if (lyric[k]=='<')
				{
					lyric[k]= 0x0a;
				}
			}

			HP_InsertLyric(mf,time,lyric);

			with_lyrics = true;
			delete lyric;
			continue;
		}
		if (lce_array->get_type(i) == CHORD_TYPE)
		{
			lce_array->get_cr_ct_bn_bt(i,&cr,&ct,&bn,&bt);
			time = lce_array->get_time(i);
			HP_InsertChord(mf, time, cr, ct, bn, bt);
			with_xfchords = true;
		}
	}

	update_lyriclist();
	source_changed = true;
}

//**************************************************************************
//*
//*		source_attributes;
//*     delivers format-attributes of the sourcefile 
//*
//**************************************************************************

void HPMF_Interface::source_attributes (CString *source, CString *songname, CString *copyright, bool *with_chunks, CString *format, CString *sub_format, 
										int *ppq, CString *tkt, double *tmpo, CString *key, 
										bool *lyrics, bool *chords, bool *count_in, int *no_measures, int *duration,
										CString *vh_channels)
{
	int i; 
	int id, chan, type, time; 
	
	// source
	char filename[81];
	GetFileTitle(sourcefile,filename,80);

	*source = filename;
	*songname = get_songname();
	*copyright = get_copyright();
	*with_chunks = with_additional_chunks;
	*lyrics = with_lyrics;
	*chords = with_xfchords;
	int time_start_beat_start, time_start_beat_end;
	*count_in = with_start_beats(&time_start_beat_start,&time_start_beat_end);
	// format, sub-format
	unsigned char mthd_header[14];
	char *source_c;

	GlobalUtilities::convert_CString_to_cstring(&source_c, sourcefile);

	FILE *source_mf  = fopen(source_c, "rb" );
	for (i=0; i<14; i++)
	{
		mthd_header[i] = (unsigned char) getc(source_mf);
	}
	fclose(source_mf);

	delete[] source_c;
	*format =  mthd_header[9]==0?"SMF0":(mthd_header[9]==1?"SMF1":"?   ");
	*sub_format = with_xg_on?"XG":with_gs_on?"GS":with_gm_on?"GM":"--";
	
	// PPQN
	*ppq = (mthd_header[12])*256+(mthd_header[13]);

	// key, takt, tempo
	char *ky;
	bool keysignature_found = false;
	bool timesignature_found = false;
	bool tempo_found = false;
	int num, denum,metronome_click,n32;
	double bpm_double;
	int cps;


	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if ((type == HP_KEY_SIGNATURE)&&!keysignature_found)
		{
			HP_ReadKeySignature(mf,id,&time,&ky);
			keysignature_found = true;
		}

		if (type == HP_TIME_SIGNATURE)
		{
			HP_ReadTimeSignature(mf,id,&time,&num,&denum,&metronome_click,&n32);
			timesignature_found = true;
		}

		if (type == HP_TEMPO && !tempo_found)
		{
			HP_ReadTempo(mf,id,&time,&bpm_double,&cps);
			tempo_found = true;
		}


	}
	if (tempo_found)
	{
		*tmpo = bpm_double;
	}
	else
	{
		*tmpo = -1.0;
	}

	if (timesignature_found)
	{
		CString takt;
		takt.Format("%i/%-2i",num,denum);
		*tkt = takt;
	}
	else
	{
		*tkt = "4/4 ";
	}

	if(keysignature_found)
	{
		(*key).Format("%-2.2s",ky);
		HP_Delete(ky);
	}
	else
	{	
		*key = "--";
	}

	// no_measures
	TAKT_BAR_TIME_ELEM tbte = takt_bar_time_list[takt_bar_time_list_free - 1];
	*no_measures = tbte.takt+1;

	// duration
	*duration = (HP_Duration(mf)+500)/1000;

	int ch;
    *vh_channels = "";
	CString vc;
	CString r;

	for (ch=0; ch<16 ;ch++)
	{
		if (vh_channel[ch])
		{
			if (vc =="")
			{
				r.Format("%i",ch+1);
			}
			else
			{
				r.Format(",%i",ch+1);
			}
			r += (vocoder_sysex_exist && vh_channel_sysex_exist[ch])?"VH":"";
		}
		else
		{
			continue;
		}

		vc += r;
	}

	if (vc == "")
	{
		*vh_channels = "--     ";
	}
	else
	{
		(*vh_channels).Format("%-7s",vc);
	}
}

//**************************************************************************
//*
//*		is_yamaha_drum_bank(long bank, int voice)
//*
//**************************************************************************

bool HPMF_Interface::is_yamaha_melody_voice(long bank, int voice)
{
	bool is_drum;
	int drum = 0;

	// try with drum statements of instrument definition (if wanted)

	with_drums_from_insfile = p_inifile->get_with_drums_from_insfile();

    if (with_drums_from_insfile && with_insdef)
	{
		if (HP_CWInsIsDrumVoice(mf,bank,voice,&drum) == HP_ERR_NONE)
		{
			is_drum = (drum==1);
			return !is_drum;
		}
	}

	// standard drums of Yamaha Keyboards, only look at banks

	is_drum = 
		( 
			(bank==6016) ||  // 9000 Pro Plugin Card Drums
			(bank==7936) ||  // Tyros Custom Voice Drums
			(bank==8192) ||  // XG SFX Bank
			(bank==10112)||  // 9000 Pro Plugin Card Drums
			(bank==16128)||  // Drums and SFX
			(bank==16256)||  // Drums
			(bank==16264)||  // added with Genos
			(bank==15360)||  // GM2 Drums and SFX
			(bank==15104)    // GS kompatible Drums
		);

	return !is_drum;
}

//**************************************************************************
//*
//*		is_sfx_bank(int bank)
//*
//**************************************************************************

bool HPMF_Interface::is_sfx_bank(int bank)
{
	bool is_sfx =
			((bank==8192) ||	// XG SX Bank
			(bank==16128)    ); // Preset SFX Bank
	return is_sfx;
}

//**************************************************************************
//*
//*		insert_voicetest_effect
//*     Copies SysEx of sourcefile mf into voicetest   
//*
//**************************************************************************

int HPMF_Interface::insert_voicetest_effects(HP_MIDIFILE_MODULE* mf_voiceplay,int time_count)
{
	int tc = time_count;
	int id, chan, time, type;
	unsigned char *data;
	int length;
	int delta;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type==HP_SYSEX)
		{
			HP_ReadSysex(mf, id, &time, &data, &length);
			delta = 5;
			if (!GlobalUtilities::is_gm_on_sysex(data) && !GlobalUtilities::is_xg_on_sysex(data))
			{
				HP_InsertSysEx(mf_voiceplay,tc,data);
				if (length == 9)
				{
					if ((data[1]==0x43)&&
						(data[2]==0x10)&&
						(data[3]==0x4c)&&
						(data[4]==0x70))
					{	// 9000 Pro Plugin Boards
						delta = 150;
					}
				}
			}
			HP_Delete(data);
			tc += delta;
		}
	}
	return tc;
}

//**************************************************************************
//*
//*		eval_delete_kbd_events
//*     deletes Meta Events Keyboard Voice. Score Start Bar, Phase Mark, 
//*     Max Phrase, Guide Track Flag. Lyrics Bitmap and/or
//*		Guide SysExe	F0 43 73 01 1F...
//*     Style SysExe:
//*		F0 43 7E 00...	Style Section Control
//*		F0 43 73 01...	Style Splitpoint
//*		F0 43 73 7C...	Style No
//*		F0 43 6...		Keyboard Start Stop (PSR-8000) 
//*		Return: No of deleted Events  
//*
//**************************************************************************

int HPMF_Interface::eval_delete_kbd_events(bool kbd_voice_events, bool score_start_bar_events, 
										   bool phrase_events, bool guide_track_events, 
										   bool del_sysex_guide_events, bool lyrics_bitmap_events, 
										   bool style_events, bool del_sp_marker_events)
{
	source_changed = false;
	int no = 0;
	int id, chan, time, type, length;
	unsigned char *data;
	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		// Sysex Style and Guide
		if (type==HP_SYSEX)
		{
			HP_ReadSysex(mf, id, &time, &data, &length);

			if (style_events)
			{
				if (data[1]==0x43)
				{
					if (((data[2]==0x7e)&&(data[3]==0x00)) ||			// style section
						((data[2]==0x73)&&(data[3]==0x01)&&				// style splitpoint, but allow style DSP's
						      (data[4]==0x51)) ||	
						((data[2]==0x73)&&(data[3]==0x7c)) ||			// style no
						((data[2]&0xf0)==0x60)							// kbd start stop
						)
					{
						HP_DeleteEvent(mf,id);
						no++;
					}
				}
			}
			if (del_sysex_guide_events)
			{
				if (data[1]==0x43)
				{
					if ((data[2]==0x73)&&(data[3]==0x01)&&(data[4]==0x1f)) 
					{
						HP_DeleteEvent(mf,id);
						no++;
					}
				}
			}
			HP_Delete(data);
		}

		// Meta Events

		if ((type==HP_KEYBOARD_VOICE)&&kbd_voice_events)
		{
			HP_DeleteEvent(mf,id);	
			no++;
		}
		if ((type==HP_SCORE_START_BAR)&&score_start_bar_events)
		{
			HP_DeleteEvent(mf,id);	 
			no++;
		}
		if (((type==HP_PHRASE_MARK)||(type==HP_MAX_PHRASE_MARK))&&phrase_events)
		{
			HP_DeleteEvent(mf,id);	 
			no++;
		}
		if ((type==HP_GUIDE_TRACK_FLAG)&&guide_track_events)
		{
			HP_DeleteEvent(mf,id);
			no++;
		}
		if ((type==HP_LYRICS_BITMAP)&&lyrics_bitmap_events)
		{
			HP_DeleteEvent(mf,id);	
			no++;
		}
		if ((type==HP_MARKER)&&del_sp_marker_events)
		{
			char* text;
			HP_ReadMarker(mf,id,&time,&text);
			CString ctext = text;
			if (ctext.GetLength()==6)
			{
				if (ctext.Left(4)=="SPJ-")
				{
					HP_DeleteEvent(mf,id);	
					no++;
				}
			}
			HP_Delete(text);
		}
	}
	if (no > 0) source_changed = true;
	return no;
}

//**************************************************************************
//*
//*		eval_normalize_chords
//*     deletes bass note chord type ( example: C7/C7 -> C7)   
//*
//**************************************************************************

int HPMF_Interface::eval_normalize_chords()
{
	if (!with_xfchords) return 0;

	source_changed = false;
	int no = 0;

	int id, chan, time, type, length;
    unsigned char cr, ct,bn, bt;
    char *chord;
	unsigned char *data;

	HP_Rewind(mf);

	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if (type == HP_CHORD_NAME)
		{
			HP_ReadChord(mf,id,&time,&cr,&ct,&bn,&bt,&chord);
			if ((bt!=0x7f) || (cr == bn))
			{
				if (bt != 0x7f)
				{
					bt = 0x7f;
				}
				if (cr == bn)
				{
					bn = 0x7f;
				}
				HP_ChangeChord(mf,id,cr,ct,bn,bt);
				no++;
			}
			HP_Delete(chord);
			continue;
		}
		if (type == HP_SYSEX)
		{
			HP_ReadSysex(mf, id, &time, &data, &length);
			if (length==9)
			{
				if((data[1]==0x43)&&(data[2]==0x7e)&&(data[3]==0x02))
				{ // chord sysex
					cr = data[4];
					ct = data[5];
					bn = data[6];
					bt = data[7];
					if ((bt!=0x7f) || (cr == bn))
					{
						if (bt != 0x7f)
						{
							bt = 0x7f;
						}
						if (cr == bn)
						{
							bn = 0x7f;
						}
						data[6] = bn;
						data[7] = bt;
						HP_DeleteEvent(mf,id);
						HP_InsertSysEx(mf,time,data);
						no++;
					}
				}
			}
			HP_Delete(data);
			continue;
		}
	}
	if (no > 0) source_changed = true;
	return no;
}

//**************************************************************************
//*
//*		eval_vh_vocoder
//*     inserts or deletes vocoder sysexes and vh channel sysexes 
//*
//**************************************************************************


void HPMF_Interface::eval_vh_vocoder(int vocoder_channel,
									 bool vocoder_channel_set,
									 bool vocoder_channel_delete,
									 int vocoder_channel_act)
{
	if ((vocoder_channel==-1) && !vocoder_channel_set && !vocoder_channel_delete && (vocoder_channel_act==-1))
	{
		return;
	}

/*
	CString r;
	r.Format("vh_channel %i\nvh_channel_set %i\nvh_channel_delete %i\nvh_channel_act %i",
		vocoder_channel,vocoder_channel_set,vocoder_channel_delete,vocoder_channel_act);
	MessageBox(r);
*/
	if (vocoder_channel >= 0)
	{
		vh_sysex_chan[7] = (unsigned char) vocoder_channel; // actualize
	}

	int chan;
	int id, time, type; 
	int time_last_sysex = 0;
	int time_first_note = -1;
	int chan_first_note = -1;
	int no_double_notes;
	int no_pitch_wheels;
	int no_vh_chan = find_vh_channel();
	int last_time;

	source_changed = false;
	
	if (vocoder_channel_delete) // if delete vocoder channel)
	{
		with_vh_sysexes(true); // delete all vh syexes	
		eval_xg_convert(&no_double_notes, &no_pitch_wheels);
		source_changed = true;
		return;
	}

	HP_GetLastTime(mf, &last_time);

	HP_Rewind(mf);
	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if (type == HP_SYSEX)
		{
			time_last_sysex = time;
		}
		if (type == HP_NOTE)
		{
			time_first_note = time;
			chan_first_note = chan;
			break;
		}
	}

	if(vocoder_channel_set || ((vocoder_channel_act==1)&&(vh_channel_sysex_exist[vocoder_channel])))
	{
		if(vocoder_channel_set)
		{
			// insert vocoder sysex
			HP_SetFirst(mf,HP_LAST);

			HP_InsertSysEx(mf,time_last_sysex, vocoder_sysex);
			HP_InsertSysEx(mf,time_last_sysex, vh_sysex_chan);
		}

		if (vocoder_channel_act==1)
		{
			HP_InsertSysEx(mf,time_last_sysex, vh_ad_off_sysex);
		
			HP_SetFirst(mf);

			// insert sysex VH Off at the end of midifile
			HP_InsertSysEx(mf,last_time, vh_ad_off_sysex);

			// insert sysex VH On behind first note
			HP_InsertSysEx(mf,time_first_note+1, vh_ad_on_sysex);
		}
	}
	
	if(!vocoder_channel_set && !vocoder_channel_delete && (vocoder_channel_act==0))
	{
		// delete vh_ad_on/off sysexes

		int length;
		unsigned char* data;

		HP_Rewind(mf);
		while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
		{
			if (type == HP_SYSEX)
			{
				HP_ReadSysex(mf,id,&time,&data,&length);

				// look for vh_ad_on sysex
				if (GlobalUtilities::is_vh_ad_on_sysex(data,length))
				{
					HP_DeleteEvent(mf, id);
					HP_Delete(data);
					continue;
				}

				// look for vh_ad_off sysex
				if (GlobalUtilities::is_vh_ad_off_sysex(data,length))
				{
					HP_DeleteEvent(mf, id);
					HP_Delete(data);
					continue;
				}
				HP_Delete(data);
				continue;
			}
		}
	}
	
	if (vocoder_channel_set || vocoder_channel_delete || (vocoder_channel_act>=0))
	{
		eval_xg_convert(&no_double_notes, &no_pitch_wheels);
		source_changed = true;
	}
	else
	{
		source_changed = false;
	}
}


//**************************************************************************
//*
//*		eval_delete_midi_events
//*     deletes SysEx and all other channel specific selected midi events
//*
//**************************************************************************

int  HPMF_Interface::eval_delete_midi_events(bool is_checked[], int event_type, int ctrl_number, 
											 bool before_notes_checked, bool note_area_checked)
{
	int id, chan, time, type, number, value;
	int no = 0;
	int i = 0;
	int time_of_first_note = -1;

	HP_Rewind(mf); 
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			time_of_first_note = time;
			break;
		}
	}

	source_changed = false;

	HP_Rewind(mf); 
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (before_notes_checked && !note_area_checked && (time >= time_of_first_note))
		{
			break;
		}
		if (!before_notes_checked && note_area_checked && (time < time_of_first_note))
		{
			continue;
		}
		if (((chan < 0) && (event_type != HP_SYSEX))||(type != event_type))
		{
			continue;
		}
		
		if (chan != -1)
		{
			if ((!is_checked[chan]) && (event_type != HP_SYSEX))
			{
				continue;
			}
		}
		
		if (ctrl_number == -1)
		{
			HP_DeleteEvent(mf,id);
			no++;
			continue;
		}

		HP_ReadController(mf,id, &time, &chan, &number, &value);
		if (number != ctrl_number)
		{
			continue;
		}

		HP_DeleteEvent(mf,id);
		no++;
	}

	if (no > 0)
	{
		source_changed = true;
	}

	return no;
}


//**************************************************************************
//*
//*		find_insfile_bank_voicenames
//*     inserts bank- and voicenames in mlv_list
//*		called from update_mlv_list and if insdef is changed
//*
//**************************************************************************

void HPMF_Interface::find_insfile_bank_voicenames()
{
	int chan;
	char *bank_name;
	char *voice_name;
	char *note_name;
	CString cstr_voicename;
	CString cstr_bankname;

	CString insdeffile = p_inifile->get_insdeffile();
	CString insdef = p_inifile->get_insdef();
	bool result = false;
	bool found = false;
	
	if (!with_insdef)
	{
		if (insdeffile!="")
		{
			CFileFind finder;
			if (finder.FindFile(insdeffile))
			{	// file exists
				result = open_insdeffile(insdeffile);
			}
			else
			{	// file does not exist
				result = false;
			}
		}
		if (result)
		{
			HP_CWDEF* def_list;
			int no_defs;
			result = get_insdefs(&def_list, &no_defs);
			if (result)
			{
				int i;
				for (i=0; i<no_defs; i++)
				{
					CString act_insdef = def_list[i].def_name;
					if (act_insdef == insdef)
					{
						set_insdef(i);
						found = true;
						break;
					}
				}
				HP_Delete(def_list);
			}
			with_insdef = found;
		}
		else
		{
			with_insdef = false;
		}
	}
	
	if (!with_insdef) return;


	for (chan=0; chan<16;chan++)
	{
	
		if (mute[chan])
		{
			continue;
		}


		HP_CWInsGetBankVoiceNoteName(mf,
			128*mlv_list[chan].msb+mlv_list[chan].lsb,
			mlv_list[chan].voice,
			0,
			&bank_name,&voice_name,&note_name);

		cstr_voicename = voice_name;
		GlobalUtilities::reduce_voicename(&cstr_voicename);
		(mlv_list[chan]).voicename = cstr_voicename;

		cstr_bankname = bank_name;
		(mlv_list[chan]).bankname = cstr_bankname;

		HP_Delete(bank_name);
		HP_Delete(voice_name);
		HP_Delete(note_name);
/* Test
		CString r;
		r.Format("Chan %i, bank %s, voice %s",chan+1,(mlv_list[chan]).bankname,(mlv_list[chan]).voicename);
		MessageBox(r);
*/
	}
}


//**************************************************************************
//*
//*		xgeffects_from_file
//*		called from init_hpmfiledata
//*
//**************************************************************************

void HPMF_Interface::xgeffects_from_file()
{
	CString xgeffectfile = p_inifile->get_xgeffectfile();
	CString keyboardmodel = p_inifile->get_keyboardmodel();
	bool found = false;
	
	if (xgeffectfile!="")
	{
		CFileFind finder;
		if (finder.FindFile(xgeffectfile))
		{	// file exists
			found = true;
		}
		else
		{	// file does not exist
			found = false;
		}
	}

	if (found)
	{
		if (xg_effects != NULL)
		{
			delete xg_effects;
			xg_effects = NULL;
		}
		xg_effects = new XgEffects(xgeffectfile);
		if (!xg_effects->ReadEffectFile(keyboardmodel))
		{
			found = false;
			delete xg_effects;
			xg_effects = NULL;
		}
	}
}

//**************************************************************************
//*
//*		eval_lengthen_vh_notes
//*     it is recommended to lengthen notes of a vocal harmony channel up 
//*     to the next note, but only to a given length
//*
//**************************************************************************


void HPMF_Interface::eval_lengthen_vh_notes(int vh_channel, int max_length, bool is_vocoder)
{
	int i,k;
	int id, chan, time, type;
	int note, velocity, length;

	repair_overlapping_notes(vh_channel);

	CString r;

	CArray <NOTE,NOTE> notelist;
	NOTE vh_note, vh_note_scr;

	// initial values

	vh_note.new_length = -1; 
	vh_note.next_i = -1; // notelist index to immediately following same note

	// fill notelist

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			if (chan != vh_channel)
			{
				continue;
			}

			HP_ReadNote(mf,id,&time, &chan, &note, &velocity, &length);
			vh_note.id = id;
			vh_note.note = note;
			vh_note.time = time;
			vh_note.old_length = length;
			notelist.Add(vh_note);
		}
	}

	// set new_length upto next note, max next max_length

	int time0;
	int time1 = -1;
	int len0;
	int new_len0;
	int distance;
	for (i=0; i<notelist.GetSize(); i++)
	{
		vh_note = notelist.GetAt(i);
		time0 = vh_note.time;
		len0 = vh_note.old_length;

		bool next_time_found = false;
		for (k=i+1; k<notelist.GetSize(); k++)
		{
			vh_note_scr = notelist.GetAt(k);
			time1 = vh_note_scr.time;
			distance = time1-time0;
			if ((time0+len0>time1)&&(time0+len0-time1<120))
			{	// shorten if note overlaps less then 120 ticks
				len0 = distance;
			}

			if(distance<len0) 
			{
				continue;
			}
			if (distance>0)
			{
				next_time_found = true;
				break;
			}
		}
		if (next_time_found)
		{
			// reduce distance to next note by 4 ticks only if is_vocoder
			new_len0 = time1 - time0 - (is_vocoder?4:0);
			if (new_len0 > max_length+len0)
			{
				new_len0 = max_length+len0;
			}
		}
		else
		{
			new_len0 = len0<max_length?max_length:len0;
		}
		vh_note.new_length = new_len0;
		notelist.SetAt(i,vh_note);
	}

	// next analyse chain and compute new length

	for (i=0; i<notelist.GetSize(); i++)
	{
		vh_note = notelist.GetAt(i);
		if ((vh_note.next_i<0) || (vh_note.new_length==0))
		{
			continue;
		}

		int ni = vh_note.next_i;

		while (ni > 0)
		{
			vh_note_scr = notelist.GetAt(ni);
			int len = vh_note_scr.new_length;
			if (len==0) continue;
			vh_note.new_length += len;
			vh_note_scr.new_length = 0;
			notelist.SetAt(ni,vh_note_scr);
			ni = vh_note_scr.next_i;
		}
		notelist.SetAt(i,vh_note);
	}


	// last action: lengthen or delete notes

	for (i=notelist.GetUpperBound(); i>=0; i--)
	{
		vh_note = notelist.GetAt(i);
		if (vh_note.old_length == vh_note.new_length)
		{
			continue;
		}
		if (vh_note.new_length != -1)
		{
			if (vh_note.new_length>0)
			{
				HP_ChangeNoteLength(mf,vh_note.id,vh_channel,vh_note.note,vh_note.new_length,HP_NO_PERCENT);
			}
			else
			{
				HP_DeleteEvent(mf, vh_note.id);
			}
		}
	}
/*
	for (i=0; i<notelist.GetSize(); i++)
	{
		vh_note = notelist.GetAt(i);
		r.Format("index %i, vh_note: id %i, time %i, next_i %i, old_length %i, new_length %i",i,
			vh_note.id, vh_note.time, vh_note.next_i, vh_note.old_length, vh_note.new_length);
		MessageBox(r);
	}
*/

	source_changed = true;
}

//**************************************************************************
//*
//*		repair_overlapping_notes
//*     if notes of a given channel overlap the following same note 
//*     the length of the first note is shortened upto the next note  
//*
//**************************************************************************

void HPMF_Interface::repair_overlapping_notes(int chan)
{
	int i,n;
	int id, ch, time, type;
	int note_val, velocity, length;

	CArray <NOTE,NOTE> notelist[128];
	NOTE note, note_scr;

	note_scr.note = -1;
	note_scr.next_i = -1;
	note_scr.new_length = -1;
	
	// fill notelist

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&ch,&time,&type)==HP_ERR_NONE)
	{
		if (ch != chan)
		{
			continue;
		}
		if (type == HP_NOTE)
		{
			HP_ReadNote(mf,id,&time, &chan, &note_val, &velocity, &length);
			note_scr.id = id;
			note_scr.time = time;
			note_scr.old_length = length;
			(notelist[note_val]).Add(note_scr);
		}
	}

	// look for overlapping notes
	for (n=0; n<128; n++)
	{ // note value n
		int size = (notelist[n]).GetSize();
		if (size<=1)
		{ // no action
			continue;
		}

		for (i=1; i<size; i++)
		{
			note = (notelist[n]).GetAt(i-1);
			note_scr = (notelist[n]).GetAt(i);

			if ((note.time==note_scr.time)&&(note.old_length==note_scr.old_length))
			{	// do nothing with double notes
				continue;
			}

			if ((note.time+note.old_length) > note_scr.time)
			{	// overlapping
				int new_len = note_scr.time - note.time;
				HP_ChangeNoteLength(mf,note.id,chan,n,new_len,HP_NO_PERCENT);
			}
		}
	}
}

//**************************************************************************
//*
//*		eval_quantize_notes
//*     Performs quantisize of notes of a single channel
//*
//**************************************************************************

void HPMF_Interface::eval_quantize_notes(int chan, int length_code, bool starts, bool note_length)
{
	source_changed = false;
	if (chan==-1) return;
	HP_Deselect(mf);
	HP_SelectChanTime(mf,chan);

	HP_QuantisizeSelected(mf,length_code,starts,note_length);

	HP_Deselect(mf);
	source_changed = true;
}


//**************************************************************************
//*
//*		least_note_length
//*     computes the length ouf the shortest note of a channel
//*
//**************************************************************************

int HPMF_Interface::least_note_length(int chan)
{
	int least = -1;
	int id, ch, time, type, note_val, velocity, length;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&ch,&time,&type)==HP_ERR_NONE)
	{
		if (ch != chan)
		{
			continue;
		}
		if (type == HP_NOTE)
		{
			HP_ReadNote(mf,id,&time, &chan, &note_val, &velocity, &length);
			if (least==-1)
			{
				least=length;
			}
			else
			{
				if (length<least)
				{
					least = length;
				}
			}
		}
	}
	return least;
}

//**************************************************************************
//*
//*		get_last_id
//*
//**************************************************************************

int HPMF_Interface::get_last_id()
{

	int	id, chan, time, type;

	HP_Rewind(mf); 
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		continue;
	}

	return id;
}

//**************************************************************************
//*
//*		eval_score_layout
//*
//**************************************************************************

void HPMF_Interface::eval_score_layout(unsigned char lyrics_value,
									   unsigned char chords_value,
									   unsigned char note_names_value,
									   unsigned char size_value,
									   unsigned char quantize_triole_value,
									   unsigned char quantize_value,
									   unsigned char notenamestype_value,
									   unsigned char note_colour_value
									  )
{

/* test
	CString r;
	r.Format("eval_score_layout:\n lyrics: %x, chords: %x, notenames %x\nsize %x,\nquantize_tr %x, quantize %x, notenamestype %x, notecolour %x",
		lyrics_value, chords_value, note_names_value, size_value, quantize_triole_value,
		quantize_value, notenamestype_value, note_colour_value);
	MessageBox(r);
*/
	delete_all_layout_sysexes();

	// find time_of_first_note
	int id, chan, time, type;
	int time_of_first_note = 0;

	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			time_of_first_note = time;
			break;
		}
	}

	// insert layout sysexes before first note

	unsigned char sysex_data[10] = {0xf0,0x43,0x73,0x01,0x50,0x12,0x00,0x00,0x00,0xf7};

	HP_SetFirst(mf,HP_LAST);

	// insert lyrics
	if (lyrics_value!=0xff)
	{
		sysex_data[7] = 0x02;
		sysex_data[8] = lyrics_value;
		HP_InsertSysEx(mf, 0, sysex_data);
	}

	// insert chords
	if (chords_value!=0xff)
	{
		sysex_data[7] = 0x03;
		sysex_data[8] = chords_value;
		HP_InsertSysEx(mf, 0, sysex_data);
	}

	// insert size
	if (size_value!=0xff)
	{
		sysex_data[7] = 0x05;
		sysex_data[8] = size_value;
		HP_InsertSysEx(mf, 0, sysex_data);
	}

	// insert note_colour
	if (note_colour_value!=0xff)
	{
		sysex_data[7] = 0x0b;
		sysex_data[8] = note_colour_value;
		HP_InsertSysEx(mf, 0, sysex_data);
	}

	// insert note_names
	if (note_names_value!=0xff)
	{
		sysex_data[7] = 0x04;
		sysex_data[8] = note_names_value;
		HP_InsertSysEx(mf, 0, sysex_data);
	}

	// insert notenamestype
	if (notenamestype_value!=0xff)
	{
		sysex_data[7] = 0x0a;
		sysex_data[8] = notenamestype_value;
		HP_InsertSysEx(mf, 0, sysex_data);
	}

	// insert quantize
	if (quantize_value!=0xff)
	{
		sysex_data[7] = 0x09;
		sysex_data[8] = quantize_value;
		HP_InsertSysEx(mf, 0, sysex_data);
	}

	// insert quantize_triole
	if (quantize_triole_value!=0xff)
	{
		sysex_data[7] = 0x08;
		sysex_data[8] = quantize_triole_value;
		HP_InsertSysEx(mf, 0, sysex_data);
	}

	int dummy1, dummy2;
	eval_xg_convert(&dummy1,&dummy2);
}

//**************************************************************************
//*
//*		get_layout_sysex_values 
//*		(find initial values)
//*
//**************************************************************************

void HPMF_Interface::get_layout_sysex_values(unsigned char *lyrics_value, 
											 unsigned char *chords_value, 
											 unsigned char *notenames_value, 
											 unsigned char *size_value,
											 unsigned char *quantize_triole_value, 
											 unsigned char *quantize_value, 
											 unsigned char *notenamestype_value,
											 unsigned char *notecolour_value
											)
{
	unsigned char *data;
	int id;
	int chan;
	int time;
	int type;
	int length;
	bool is;

	unsigned char layout_type, layout_value; 

	// init values
	*lyrics_value = 0xff;			// sysex type 0x02
	*chords_value = 0xff;			// sysex type 0x03
	*notenames_value = 0xff;		// sysex type 0x04
	*size_value = 0xff;				// sysex type 0x05
	*quantize_triole_value = 0xff;	// sysex type 0x08
	*quantize_value = 0xff;			// sysex type 0x09
	*notenamestype_value = 0xff;	// sysex type 0x0a
	*notecolour_value = 0xff;		// sysex type 0x0b


	HP_Rewind(mf);

	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		is = false;
		if (type == HP_NOTE)
		{
			break;
		}
		if (type == HP_SYSEX)
		{
			HP_ReadSysex(mf,id,&time,&data,&length);
			is = GlobalUtilities::is_score_layout_sysex(data,&layout_type, &layout_value);
			if (is)
			{	
				// ignore  left/right part on/off and left/right chan
				if ((layout_type==0x00) ||
					(layout_type==0x01) ||
					(layout_type==0x06) ||
					(layout_type==0x07)    )
				{
					HP_Delete(data);
					continue;
				}

				// switch for sysex_types
				switch(layout_type)
				{
				case 0x02:
					*lyrics_value = layout_value;
					break;
				case 0x03:
					*chords_value = layout_value;
					break;
				case 0x04:
					*notenames_value = layout_value;
					break;
				case 0x05:
					*size_value = layout_value;
					break;
				case 0x08:
					*quantize_triole_value = layout_value;
					break;
				case 0x09:
					*quantize_value = layout_value;
					break;
				case 0x0a:
					*notenamestype_value = layout_value;
					break;
				case 0x0b:
					*notecolour_value = layout_value;
					break;
				default:
					break;
				}
			}
			HP_Delete(data);
		}
	}
}

//**************************************************************************
//*
//*		delete_all_layout_sysexes 
//*		called from from eval_score_layout
//*
//**************************************************************************

void HPMF_Interface::delete_all_layout_sysexes()
{
	unsigned char *data;
	int id;
	int chan;
	int time;
	int type;
	int length;
	bool is;

	unsigned char layout_type, layout_value; 
	HP_Rewind(mf);										   
	while ( HP_ReadEvent(mf,&id,&chan,&time,&type) == HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			break;
		}
		if (type == HP_SYSEX)
		{
			HP_ReadSysex(mf,id,&time,&data,&length);
			is = GlobalUtilities::is_score_layout_sysex(data,&layout_type, &layout_value);
			if (is)
			{	
				// do not delete left/right part on/off and left/right chan
				if ((layout_type==0x00) ||
					(layout_type==0x01) ||
					(layout_type==0x06) ||
					(layout_type==0x07)    )
				{
					HP_Delete(data);
					continue;
				}
				HP_Delete(data);
				HP_DeleteEvent(mf,id);
			}
		}
	}	
}

//**************************************************************************
//*
//*		create_testsequence_melody
//*		called from from standard an voicefile revoicing
//*
//**************************************************************************


HP_MIDIFILE_MODULE* HPMF_Interface::create_testsequence_melody()
{
	HP_MIDIFILE_MODULE* local_mf;
	// initialize test sequence
	local_mf = HP_Init();	// starts a MIDI-file session
	if (local_mf != NULL)   // do nothing if not possible
	{
		const int PPQN = 480;
		int time_count = 0;
		int i;
		// note-length
		const int whole = PPQN*4;	// ticks of a whole note
		const int quaver = PPQN/2;	// ticks of 1/8 note
		
		HP_ChangePPQN(local_mf,HP_PPQN480);	// set PPQN
		
		HP_SetFirst(local_mf,HP_FIRST);	// add events of same time at the end
		HP_InsertSysEx(local_mf,time_count,GlobalUtilities::gm_on_data);
		time_count += 100;
		HP_InsertSysEx(local_mf,time_count,GlobalUtilities::xg_on_data);
		time_count += 100;
		HP_InsertTempo(local_mf,200,120); // bpm = 360
		time_count += 10;
		time_count = insert_voicetest_effects(local_mf,time_count);
		HP_InsertController(local_mf,time_count,1,HP_BANK_SELECT_MSB,0);
		time_count += 1;
		HP_InsertController(local_mf,time_count,1,HP_BANK_SELECT_LSB,0);
		time_count += 1;
		HP_InsertProgramChange(local_mf,time_count,1,0);
		time_count += 10;

		// prepare notes
		struct	{int time;
				int length;
				int note;
				int chan;
				int vel;	} note[] =
		{
			{0,	quaver, 0x30,1,100},	// c
			{quaver*1,	quaver, 0x34,1,70},		// e		
			{quaver*2,	quaver, 0x37,1,70},		// g
			{quaver*3,	quaver, 0x3c,1,100},	// c
			{quaver*4,	quaver, 0x40,1,70},		// e		
			{quaver*5,	quaver, 0x43,1,70},		// g
			{quaver*6,	quaver, 0x48,1,100},	// c
			{quaver*7,	quaver, 0x4c,1,70},		// e
			{quaver*8,	quaver, 0x4f,1,70},		// g
			{quaver*9,	whole  , 0x54,1,127},	// c
			{quaver*9,	whole  , 0x43,1,127},	// g
			{quaver*9,	whole  , 0x40,1,127},	// e
			{quaver*9,	whole  , 0x30,1,127},	// c
			{-1,		quaver, 0x00,0,0  }
		};
		
		// insert notes
		
		for (i=0; true; i++)
		{
			if (note[i].time == -1) break;
			HP_InsertNote(local_mf,time_count+note[i].time,note[i].length,note[i].note,note[i].chan,note[i].vel);
		}
		return local_mf;
	}
	else
	{
		return NULL;
	}
}

//**************************************************************************
//*
//*		create_testsequence_drum
//*		called from from standard an voicefile revoicing
//*
//**************************************************************************


HP_MIDIFILE_MODULE* HPMF_Interface::create_testsequence_drum()
{
	HP_MIDIFILE_MODULE* local_mf;
	// initialize test sequence
	local_mf = HP_Init();	// starts a MIDI-file session
	if (local_mf != NULL)   // do nothing if not possible
	{
		const int PPQN = 480;
		int time_count = 0;
		int i;
		// note-length
		const int whole = PPQN*4;	// ticks of a whole note
		const int quaver = PPQN/2;	// ticks of 1/8 note
		
		HP_ChangePPQN(local_mf,HP_PPQN480);	// set PPQN
		
		HP_SetFirst(local_mf,HP_FIRST);	// add events of same time at the end
		HP_InsertSysEx(local_mf,time_count,GlobalUtilities::gm_on_data);
		time_count += 100;
		HP_InsertSysEx(local_mf,time_count,GlobalUtilities::xg_on_data);
		time_count += 100;
		HP_InsertTempo(local_mf,200,120); // bpm = 360
		time_count += 10;
		time_count = insert_voicetest_effects(local_mf,time_count);
		HP_InsertController(local_mf,time_count,1,HP_BANK_SELECT_MSB,0);
		time_count += 1;
		HP_InsertController(local_mf,time_count,1,HP_BANK_SELECT_LSB,0);
		time_count += 1;
		HP_InsertProgramChange(local_mf,time_count,1,0);
		time_count += 10;

		// prepare notes
		struct	{int time;
				int length;
				int note;
				int chan;
				int vel;	} note[] =
		{
			{0,	quaver, 0x30,1,100},	// c
			{quaver*1,	quaver, 0x34,1,70},		// e		
			{quaver*2,	quaver, 0x37,1,70},		// g
			{quaver*3,	quaver, 0x3c,1,100},	// c
			{quaver*4,	quaver, 0x40,1,70},		// e		
			{quaver*5,	quaver, 0x43,1,70},		// g
			{quaver*6,	quaver, 0x48,1,100},	// c
			{quaver*7,	quaver, 0x4c,1,70},		// e
			{quaver*8,	quaver, 0x4f,1,70},		// g
			{quaver*9,	whole  , 0x54,1,127},	// c
			{quaver*9,	whole  , 0x43,1,127},	// g
			{quaver*9,	whole  , 0x40,1,127},	// e
			{quaver*9,	whole  , 0x30,1,127},	// c
			{-1,		quaver, 0x00,0,0  }
		};
		
		// insert notes
		
		for (i=0; true; i++)
		{
			if (note[i].time == -1) break;
			HP_InsertNote(local_mf,time_count+note[i].time,note[i].length,note[i].note,note[i].chan,note[i].vel);
		}
		return local_mf;
	}
	else
	{
		return NULL;
	}
}
