// ChangeDrumVoicesDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "ChangeDrumVoicesDlg.h"
#include "HP_midifile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld ChangeDrumVoicesDlg 


ChangeDrumVoicesDlg::ChangeDrumVoicesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ChangeDrumVoicesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ChangeDrumVoicesDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT

	drum_chan = -1;
	note = -1;
	new_note = -1;
	new_velocity = -1;
	scr_drum_chan = -1;
	scr_note = -1;
	scr_new_note = -1;
	scr_new_velocity = -1;
	min_vel = -1;
	max_vel = -1;
	last_new_list_index = -1;
	drums_changed = false;
	m_nTimer = NULL;

	int i;

	for (i=0; i<16; i++)
	{
		drum_chan_list[i].is_drum = false;
		drum_chan_list[i].drumbank_name = NULL;
		drum_chan_list[i].drumkit_name = NULL;
	}
	mf_voiceplay = NULL;
}


BOOL ChangeDrumVoicesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	
	if (get_init_data()==0)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,
			GlobalUtilities::get_resource_string(IDS_NO_DRUMS),
			NULL,MB_OK|MB_TASKMODAL);
		OnCancel();
	}


	SetDlgItemText(IDC_VEL_MIN,"");
	SetDlgItemText(IDC_VEL_MAX,"");
	SetDlgItemText(IDC_EDIT_VELOCITY,"");

	m_edit_velocity.EnableWindow(FALSE);
	m_check_dyn_vel.SetCheck(1);

	// initialize test sequence
	int time_count = 0;
	mf_voiceplay = HP_Init();	// starts a MIDI-file session
	if (mf_voiceplay != NULL)   // do nothing if not possible
	{
		const int PPQN = 480;
		const int quaver = PPQN;	// ticks of a quaver note
		HP_ChangePPQN(mf_voiceplay,HP_PPQN480);	// set PPQN
		HP_SetFirst(mf_voiceplay,HP_FIRST);	// add events of same time at the end
		HP_InsertSysEx(mf_voiceplay,time_count,GlobalUtilities::gm_on_data);
		time_count += 100;
		HP_InsertSysEx(mf_voiceplay,time_count,GlobalUtilities::xg_on_data);
		time_count += 100;
		HP_InsertTempo(mf_voiceplay,time_count,120); // bpm = 360
		time_count += 10;
		time_count = hpmfi->insert_voicetest_effects(mf_voiceplay,time_count);
		HP_InsertController(mf_voiceplay,time_count,1,HP_BANK_SELECT_MSB,0);
		time_count += 1;
		HP_InsertController(mf_voiceplay,time_count,1,HP_BANK_SELECT_LSB,0);
		time_count += 1;
		HP_InsertProgramChange(mf_voiceplay,time_count,1,0);
		time_count += 10;
		// prepare note
		HP_InsertNote(mf_voiceplay,time_count,quaver,0x30,9,100);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void ChangeDrumVoicesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ChangeDrumVoicesDlg)
	DDX_Control(pDX, IDC_CHECK_DYN_VEL, m_check_dyn_vel);
	DDX_Control(pDX, IDC_EDIT_VELOCITY, m_edit_velocity);
	DDX_Control(pDX, IDC_NEW_NOTE_LIST, m_new_note_list);
	DDX_Control(pDX, IDC_SOURCE_NOTE_LIST, m_source_note_list);
	DDX_Control(pDX, IDC_DRUM_CHAN_LIST, m_drum_chan_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ChangeDrumVoicesDlg, CDialog)
	//{{AFX_MSG_MAP(ChangeDrumVoicesDlg)
	ON_LBN_SELCHANGE(IDC_DRUM_CHAN_LIST, OnSelchangeDrumChanList)
	ON_LBN_SELCHANGE(IDC_SOURCE_NOTE_LIST, OnSelchangeSourceNoteList)
	ON_LBN_SELCHANGE(IDC_NEW_NOTE_LIST, OnSelchangeNewNoteList)
	ON_EN_CHANGE(IDC_EDIT_VELOCITY, OnChangeEditVelocity)
	ON_BN_CLICKED(IDC_CHECK_DYN_VEL, OnCheckDynVel)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten ChangeDrumVoicesDlg 


int ChangeDrumVoicesDlg::get_init_data()
{
	bool result = false;
	bool found = false;

	CString insdeffile = p_inifile->get_insdeffile();
	CString insdef = p_inifile->get_insdef();

	// open file and insdef

	if (!hpmfi->with_insdef)
	{
		SetCursor(hCursorWait);

		if (insdeffile!="")
		{
			CFileFind finder;
			if (finder.FindFile(insdeffile))
			{	// file exists
				result = hpmfi->open_insdeffile(insdeffile);
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
			result = hpmfi->get_insdefs(&def_list, &no_defs);
			if (result)
			{
				int i;
				for (i=0; i<no_defs; i++)
				{
					CString act_insdef = def_list[i].def_name;
					if (act_insdef == insdef)
					{
						hpmfi->set_insdef(i);
						found = true;
						break;
					}
				}
				HP_Delete(def_list);
			}
			hpmfi->with_insdef = found;
		}
		else
		{
			hpmfi->with_insdef = false;
			SetDlgItemText(IDC_INSDEFFILENAME,"");
		}
		SetCursor(hCursorWait);
	}

	if (hpmfi->with_insdef)
	{
		// display insdeffile and insdef
		CString short_filename = insdeffile;
		if (insdeffile.GetLength()>57)
		{
			short_filename = "..."+insdeffile.Right(54);
		}

		SetDlgItemText(IDC_INSDEFFILENAME,short_filename+" ("+insdef+")");
	}
	else
	{
		SetDlgItemText(IDC_INSDEFFILENAME,"");
	}

	// display drum-banks and kits
	int no_drums = fill_drum_names();
	if (no_drums!=0)
	{
		m_drum_chan_list.ResetContent();
		int chan;
		int line_number = 0;
		for (chan=0; chan<16; chan++)
		{
			CString str;
			if (!drum_chan_list[chan].is_drum) continue;
			str.Format("Kanal %i: Bank \"%s\", Drumkit \"%s\"",
				chan+1,
				drum_chan_list[chan].drumbank_name,
				drum_chan_list[chan].drumkit_name);
			drum_chan_list[chan].line = line_number;
			m_drum_chan_list.AddString(str);
			line_number++;
		}
		scr_drum_chan = -1;
		clear_drum_note_lists();
	}
	return no_drums;
}

int ChangeDrumVoicesDlg::fill_drum_names()
{
	int no_drumchan = 0;
	int chan;
	m_drum_chan_list.ResetContent();

	if ((hpmfi->with_insdef) && (hpmfi->bank_list == NULL))
	{
		HP_CWInsGetBanks(hpmfi->mf,&hpmfi->bank_list,&hpmfi->no_banks);
	}

	hpmfi->update_mlv_list();
	
	for (chan=0; chan<16; chan++)
	{
		if ((hpmfi->mlv_list[chan].melody)||
			(hpmfi->no_notes[chan]==0))
		{
			drum_chan_list[chan].is_drum = false;
			drum_chan_list[chan].drumbank_name = NULL;
			drum_chan_list[chan].drumkit_name = NULL;
		}
		else
		{
			no_drumchan++;

			drum_chan_list[chan].is_drum = true;
			int bank = 128*(hpmfi->mlv_list[chan].msb) + hpmfi->mlv_list[chan].lsb;
			int kit = hpmfi->mlv_list[chan].voice;
			drum_chan_list[chan].bank = bank;
			drum_chan_list[chan].kit = kit;
			bool err_bank_voices = false;

			if (hpmfi->with_insdef)
			{
				// find names of drumbank and drumkit
		        char *bank_name;
				HP_CWVOICE *voices;

				err_bank_voices = (HP_ERR_NONE != HP_CWInsGetBankVoices(hpmfi->mf,bank,&bank_name,&voices));
				if (!err_bank_voices)
				{
					drum_chan_list[chan].drumbank_name = new char[(int)strlen(bank_name)+1];
					strcpy(drum_chan_list[chan].drumbank_name,bank_name);

					char* kit_name = voices[kit].voice_name;
					drum_chan_list[chan].drumkit_name = new char[(int)strlen(kit_name)+1];
					strcpy(drum_chan_list[chan].drumkit_name,kit_name);
					HP_Delete(voices);
					HP_Delete(bank_name);
				}
			}
			if (!hpmfi->with_insdef||err_bank_voices)
			{
				char banknumber_text[8];
				char kitnumber_text[8];
				sprintf(banknumber_text,"%i",bank);
				sprintf(kitnumber_text,"%i",kit);

				drum_chan_list[chan].drumbank_name = new char[8];
				strcpy(drum_chan_list[chan].drumbank_name,banknumber_text);

				drum_chan_list[chan].drumkit_name = new char[8];
				strcpy(drum_chan_list[chan].drumkit_name,kitnumber_text);
			}
		}
	}

	return no_drumchan;
}


void ChangeDrumVoicesDlg::fill_drum_note_lists(int bank, int kit)
{
	int id, chan, time, type, note, velocity, length;
	bool with_key_line = false;

	clear_drum_note_lists();

	if (hpmfi->with_insdef)
	{
	    char* bank_name;
		char* kit_name;
		HP_CWNOTE *note_names;

		HP_CWInsGetNoteNames(hpmfi->mf,bank,kit,&bank_name,&kit_name,&note_names);

		for (note=0; note<128; note++)
		{
			note_list[note].note_name = note_names[note].note_name;
			note_list[note].source_line = -1;
			note_list[note].dest_line = -1;

//			CString r;
//			r.Format("note_list[note].note_name = %s",note_list[note].note_name);
//			MessageBox(r);

			// key lines exist in insfile?
			if (note_list[note].note_name.GetLength()>=5)
			{
				with_key_line = true;
			}
		}
		HP_Delete(note_names);
		HP_Delete(bank_name);
		HP_Delete(kit_name);
	}


	if (!hpmfi->with_insdef || !with_key_line)
	{
		CString note_number;
		for (note=0; note<128; note++)
		{
			note_number.Format("%3d ",note);
			note_list[note].note_name = note_number + GlobalUtilities::compute_notestring(note);
			note_list[note].source_line = -1;
			note_list[note].dest_line = -1;
		}
	}

	// fill dest-info
	for (note=0; note<128; note++)
	{
		note_list[note].is_source = false;
		if (hpmfi->with_insdef && with_key_line)
		{	// only real drum-names
			note_list[note].is_dest = (note_list[note].note_name.GetLength()>=4) &&
				((note_list[note].note_name).GetAt(1) != 'b') &&
				((note_list[note].note_name).GetAt(1) != '#');
		}
		else
		{	// all note-names
			note_list[note].is_dest = true;
		}
	}

	if (hpmfi->with_insdef && with_key_line)
	{
		CString note_number;
		for(note=0; note<128; note++)
		{
			note_number.Format("%3d ",note);
			if (note_list[note].is_dest)
			{
				note_list[note].note_name = 
					note_number + 
					GlobalUtilities::compute_notestring(note)+": "
					+note_list[note].note_name;
			}
		}
	}
	
	// fill source-info
	HP_Rewind(hpmfi->mf);
	while (HP_ReadEvent(hpmfi->mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (chan != scr_drum_chan) continue;

		if (type == HP_NOTE)
		{
			HP_ReadNote(hpmfi->mf,id,&time, &chan, &note, &velocity, &length);
			note_list[note].is_source = true;
		}
	}

	// Fill source_note_list
	int source_line_number = 0;
	int dest_line_number = 0;

	for (note=0; note<128; note++)
	{
		if (note_list[note].is_source)
		{
			m_source_note_list.AddString(note_list[note].note_name);
			note_list[note].source_line = source_line_number;
			source_line_number++;
		}
		if (note_list[note].is_dest)
		{
			m_new_note_list.AddString(note_list[note].note_name);
			note_list[note].dest_line = dest_line_number;
			dest_line_number++;
		}
	}
}



void ChangeDrumVoicesDlg::clear_drum_note_lists()
{
	// clear note_list
	for (note=0; note<128; note++)
	{
		note_list[note].is_source = false;
		note_list[note].is_dest = false;
	}
	m_source_note_list.ResetContent();
	m_new_note_list.ResetContent();
}



void ChangeDrumVoicesDlg::destroy_chan_list()
{
	int chan;
	for (chan=0; chan<16; chan++)
	{
		if (drum_chan_list[chan].is_drum)
		{
			if (drum_chan_list[chan].drumbank_name != NULL)
			{
				delete[] drum_chan_list[chan].drumbank_name;
			}
			if (drum_chan_list[chan].drumkit_name != NULL)
			{
				delete[] drum_chan_list[chan].drumkit_name;
			}
		}
	}
}

void ChangeDrumVoicesDlg::OnExit() 
{
	destroy_chan_list();
	if (mf_voiceplay != NULL)
	{
		HP_Free(mf_voiceplay);
		mf_voiceplay = NULL;
	}
	EndDialog(drums_changed?0:-1);
}

void ChangeDrumVoicesDlg::OnOK() 
{	// called from button "Execute"
	if ((scr_drum_chan == -1) || (scr_note == -1))
	{
		return;
	}

	if (((scr_note!=-1) && (scr_new_note==-1))||((scr_note!=-1) && (scr_new_velocity==0)))
	{	//	(scr_new_note==-1) or (new velocity==0) -> source drum will be deleted
		if (IDYES != AfxMessageBox(GlobalUtilities::get_resource_string(IDS_DELETE_DRUM),MB_YESNO,0))
		{
			return;
		}
	}

	drum_chan = scr_drum_chan;
	note = scr_note;
	new_note = scr_new_note;
	new_velocity = scr_new_velocity;
	dynamic = (m_check_dyn_vel.GetCheck()==1);

	SetCursor(hCursorWait);
	if (!hpmfi->eval_change_drum(
			drum_chan, 
			note,
			new_note,
			new_velocity,
			dynamic,
			min_vel,
			max_vel))
	{
		MessageBox("Error Transpose Drums");
	}
	else
	{
		drums_changed = true;
	}
	SetCursor(hCursorOld);

	fill_drum_note_lists(drum_chan_list[scr_drum_chan].bank,
							drum_chan_list[scr_drum_chan].kit);

	SetDlgItemText(IDC_VEL_MIN,"");
	SetDlgItemText(IDC_VEL_MAX,"");
	SetDlgItemText(IDC_EDIT_VELOCITY,"");

	m_edit_velocity.EnableWindow(FALSE);
}

void ChangeDrumVoicesDlg::OnSelchangeDrumChanList() 
{
	scr_drum_chan = -1;
	scr_note = -1;
	int chan;
	int list_index = m_drum_chan_list.GetCurSel();
	for (chan=0; chan<16; chan++)
	{
		if (!drum_chan_list[chan].is_drum) continue;
		if (drum_chan_list[chan].line==list_index)
		{
			scr_drum_chan = chan;
			break;
		}
	}
	fill_drum_note_lists(drum_chan_list[scr_drum_chan].bank,
							drum_chan_list[scr_drum_chan].kit);

	SetDlgItemText(IDC_VEL_MIN,"");
	SetDlgItemText(IDC_VEL_MAX,"");
	SetDlgItemText(IDC_EDIT_VELOCITY,"");

	m_edit_velocity.EnableWindow(FALSE);
	m_check_dyn_vel.SetCheck(1);	


/* Test
	CString r;
	r.Format("chan %i, bank %i, kit %i", 
		scr_drum_chan,
		drum_chan_list[scr_drum_chan].bank,
		drum_chan_list[scr_drum_chan].kit);
	MessageBox(r);
*/
}

void ChangeDrumVoicesDlg::OnSelchangeSourceNoteList() 
{
	int note;
	if (scr_drum_chan == -1) return;
	scr_note = -1;

	int list_index = m_source_note_list.GetCurSel();
	for (note = 0; note <128; note++)
	{
		if (note_list[note].source_line == list_index)
		{
			scr_note = note;
			break;
		}
	}

	if (scr_note >= 0)
	{
		hpmfi->compute_drum_velocity(scr_drum_chan, scr_note, &min_vel, &max_vel);

		if (min_vel >=1)
		{
			SetDlgItemInt(IDC_VEL_MIN,min_vel,FALSE);
		}
		else
		{
			SetDlgItemInt(IDC_VEL_MIN,1,FALSE);
			min_vel = 1;
		}
		if (max_vel <= 127)
		{
			SetDlgItemInt(IDC_VEL_MAX,max_vel,FALSE);
			SetDlgItemInt(IDC_EDIT_VELOCITY,max_vel,FALSE);
		}
		else
		{
			SetDlgItemInt(IDC_VEL_MAX,127,FALSE);
			SetDlgItemInt(IDC_EDIT_VELOCITY,127,FALSE);
			max_vel = 127;
		}
		m_edit_velocity.EnableWindow(TRUE);
	}
}

void ChangeDrumVoicesDlg::OnSelchangeNewNoteList() 
{
	int list_index = m_new_note_list.GetCurSel();
	if (list_index == last_new_list_index)
	{
		((CListBox*)GetDlgItem(IDC_NEW_NOTE_LIST))->SetCurSel(-1);
		scr_new_note = -1;
		last_new_list_index = -1;
		return;
	}

	int note;
	scr_new_note = -1;
	for (note = 0; note <128; note++)
	{
		if (note_list[note].dest_line == list_index)
		{
			scr_new_note = note;
			break;
		}
	}
	if (scr_new_note != -1)
	{
		VoiceTest();
	}
}

void ChangeDrumVoicesDlg::OnChangeEditVelocity() 
{
	// do nothing, if called from OnInitDialog
	if ((scr_drum_chan==-1) || (scr_note==-1)) return;

	int val = GetDlgItemInt(IDC_EDIT_VELOCITY);
	if (val > 127)
	{
		SetDlgItemInt(IDC_EDIT_VELOCITY,127,FALSE);
		val = 127;
	}
	if (val <= 0)
	{
		SetDlgItemInt(IDC_EDIT_VELOCITY,1,FALSE);
		val = 1;
	}
	
	scr_new_velocity = val;
	bool dynamic = (m_check_dyn_vel.GetCheck()==1);
	if (scr_new_velocity != -1)
	{
		if (dynamic)
		{
			if ((min_vel != -1) && (max_vel != -1))
			{
				int dyn_min = (max_vel>0)?(scr_new_velocity*min_vel)/max_vel:1;
				if (dyn_min <= 0) dyn_min = 1;
				int dyn_max = scr_new_velocity;
				if (dyn_max <= 0) dyn_max = 1;
				SetDlgItemInt(IDC_VEL_MIN,dyn_min,FALSE);
				SetDlgItemInt(IDC_VEL_MAX,dyn_max,FALSE);
			}
		}
		else
		{
			SetDlgItemInt(IDC_VEL_MIN,scr_new_velocity,FALSE);
			SetDlgItemInt(IDC_VEL_MAX,scr_new_velocity,FALSE);
		}
	}
}


void ChangeDrumVoicesDlg::OnCheckDynVel() 
{
	if ((scr_drum_chan==-1)||(scr_note==-1)) return;
	bool dynamic = (m_check_dyn_vel.GetCheck()==1);
	if (scr_new_velocity != -1)
	{
		if (scr_new_velocity <=0) scr_new_velocity = 1;
		if (dynamic)
		{
			if ((min_vel != -1) && (max_vel != -1))
			{
				int dyn_min = (max_vel>0)?(scr_new_velocity*min_vel)/max_vel:1;
				if (dyn_min <= 0) dyn_min = 1;
				int dyn_max = scr_new_velocity;
				if (dyn_max <= 0) dyn_max = 1;
				SetDlgItemInt(IDC_VEL_MIN,dyn_min,FALSE);
				SetDlgItemInt(IDC_VEL_MAX,dyn_max,FALSE);
			}
		}
		else
		{
			SetDlgItemInt(IDC_VEL_MIN,scr_new_velocity,FALSE);
			SetDlgItemInt(IDC_VEL_MAX,scr_new_velocity,FALSE);
		}
	}
}

void ChangeDrumVoicesDlg::VoiceTest()
{
	if (mf_voiceplay == NULL) return; // do nothing if not possible

	int chan = 9;
	int bank = drum_chan_list[scr_drum_chan].bank;
    int voice = drum_chan_list[scr_drum_chan].kit;
	int note;
	int velocity;

	if (scr_new_note==-1)
	{
		return;
	}
	else
	{
		note = scr_new_note;
	}
	if (scr_new_velocity<=0)
	{
		velocity = 100;
	}
	else
	{
		velocity = scr_new_velocity;
	}

	int id, ch, time, type;
	int number, value;

	// set test voice
	HP_Rewind(mf_voiceplay);
	while (HP_ReadEvent(mf_voiceplay,&id,&ch,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_BANK_SELECT_MSB) 
		{
			HP_ReadController(mf_voiceplay,id, &time, &ch, &number, &value);
			HP_DeleteEvent(mf_voiceplay,id);
			HP_InsertController(mf_voiceplay,time,chan,HP_BANK_SELECT_MSB,bank/128,HP_NO_CONTROLLER_NUMBER);
			continue;
		}
		if (type == HP_BANK_SELECT_LSB) 
		{
			HP_ReadController(mf_voiceplay,id, &time, &ch, &number, &value);
			HP_DeleteEvent(mf_voiceplay,id);
			HP_InsertController(mf_voiceplay,time,chan,HP_BANK_SELECT_LSB,bank%128,HP_NO_CONTROLLER_NUMBER);
			continue;
		}
		if (type == HP_PROGRAM_CHANGE) 
		{
			HP_ReadProgramChange(mf_voiceplay,id, &time, &ch, &number);
			HP_DeleteEvent(mf_voiceplay,id);
			HP_InsertProgramChange(mf_voiceplay,time,chan,voice);
			continue;
		}
		if (type == HP_NOTE)
		{
			HP_ChangeNote(mf_voiceplay,id,chan,note,HP_ABSOLUTE);
			HP_ChangeVelocity(mf_voiceplay,id,chan,note,velocity,HP_NO_PERCENT);
		}
	}

	SetCursor(hCursorWait);
	HP_Play(mf_voiceplay,HP_ALL);
	// activate timer, no really used
	m_nTimer = SetTimer(1, 500, 0); 
	
//	HP_Save(mf_voiceplay,"c:/temp/drum_voice_test.mid",HP_SMF0);
}

void ChangeDrumVoicesDlg::OnTimer(UINT nIDEvent) 
{
	if (!HP_IsPlaying(mf_voiceplay))
	{	// play done
		KillTimer(m_nTimer);
		m_nTimer = NULL;
		SetCursor(hCursorOld);
	}

	CDialog::OnTimer(nIDEvent);
}
