// Extras_Dlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Extras_Dlg.h"
#include "Songname.h"
#include "Score.h"
#include "Quickstart.h"
#include "ScoreChanDlg.h"
#include "ScoreNotesOptDlg.h"
#include "CopyrightDlg.h"
#include "VHChanDlg.h"
#include "QuantizeDlg.h"
#include "Delete_short_notes.h"
#include "Delete_MIDI_Events.h"
#include "Lengthen_Notes.h"
#include "lickChanDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Extras_Dlg 


Extras_Dlg::Extras_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Extras_Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Extras_Dlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	vh_act_deact_folder_running = false;
	vh_act_deact_folder_abort_wanted = false;
	vh_act_deact_dlg = NULL;
	delete_kbd_events_folder_running = false;
	delete_kbd_events_folder_abort_wanted = false;
	delete_kbd_events_dlg = NULL;
	del_kbd_voice_events = false;
	del_phrase_events = false;
	del_guide_track_events = false;
	del_lyrics_bitmap_events = false;
	del_score_start_bar_events = false;
	del_style_events = false;;
}


void Extras_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Extras_Dlg)
	DDX_Control(pDX, IDC_KLICKSPUR, m_click_chan);
	DDX_Control(pDX, IDC_TIME_SIGNATURE, m_time_signature);
	DDX_Control(pDX, IDC_LENGTHEN, m_lengthen);
	DDX_Control(pDX, IDC_DELETE_SHORT_NOTES, m_delete_short_notes);
	DDX_Control(pDX, IDC_DELETE_MIDI_EVENTS, m_delete_midi_events);
	DDX_Control(pDX, IDC_QUANTIZE, m_quantize);
	DDX_Control(pDX, IDC_VH_KANAL, m_vh_chan);
	DDX_Control(pDX, IDC_NORMALIZE_CHORDS, m_normalize_chords);
	DDX_Control(pDX, IDC_DELETE_KBD_EVENTS, m_delete_kbd_events);
	DDX_Control(pDX, IDC_SONGNAME, m_songname);
	DDX_Control(pDX, IDC_QUICKSTART, m_quickstart);
	DDX_Control(pDX, IDC_COPYRIGHT, m_copyright);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Extras_Dlg, CDialog)
	//{{AFX_MSG_MAP(Extras_Dlg)
	ON_BN_CLICKED(IDC_SONGNAME, OnSongname)
	ON_BN_CLICKED(IDC_COPYRIGHT, OnCopyright)
	ON_BN_CLICKED(IDC_QUICKSTART, OnQuickstart)
	ON_BN_CLICKED(IDC_DELETE_KBD_EVENTS, OnDeleteKbdEvents)
	ON_BN_CLICKED(IDC_NORMALIZE_CHORDS, OnNormalizeChords)
	ON_BN_CLICKED(IDC_VH_KANAL, OnVocalHarmony)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_QUANTIZE, OnQuantize)
	ON_BN_CLICKED(IDC_DELETE_SHORT_NOTES, OnDeleteShortNotes)
	ON_BN_CLICKED(IDC_DELETE_MIDI_EVENTS, OnDeleteMidiEvents)
	ON_BN_CLICKED(IDC_LENGTHEN, OnLengthen)
	ON_BN_CLICKED(IDC_TIME_SIGNATURE, OnTimeSignature)
	ON_BN_CLICKED(IDC_KLICKSPUR, OnClickChan)
	ON_BN_CLICKED(IDC_SCORE, OnScore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipDlg Nachrichten-Handler


BOOL Extras_Dlg::PreTranslateMessage(MSG* pMSG)
{
	m_pToolTip.RelayEvent(pMSG);
	return CDialog::PreTranslateMessage(pMSG);
}

BOOL Extras_Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_pToolTip.Create(this);
	m_pToolTip.SetDelayTime(TTDT_AUTOPOP,4000);
	m_pToolTip.SetMaxTipWidth(200);

	m_pToolTip.AddTool(&m_quickstart,GlobalUtilities::get_resource_string(IDS_QUICKSTART));
	m_pToolTip.AddTool(&m_copyright,GlobalUtilities::get_resource_string(IDS_COPYRIGHT));
//	m_pToolTip.AddTool(&m_scorechan,GlobalUtilities::get_resource_string(IDS_SCORECHAN));
//	m_pToolTip.AddTool(&m_score_notes_opt,GlobalUtilities::get_resource_string(IDS_SCORE_NOTES_OPT));
	m_pToolTip.AddTool(&m_songname,GlobalUtilities::get_resource_string(IDS_SONGNAME));
	m_pToolTip.AddTool(&m_delete_kbd_events,GlobalUtilities::get_resource_string(IDS_KBD_EVENTS));
	m_pToolTip.AddTool(&m_normalize_chords,GlobalUtilities::get_resource_string(IDS_NORMALIZE_CHORDS));
	m_pToolTip.AddTool(&m_vh_chan,GlobalUtilities::get_resource_string(IDS_VH_CHAN));
	m_pToolTip.AddTool(&m_delete_midi_events,GlobalUtilities::get_resource_string(IDS_DELETE_MIDI_EVENTS));
	m_pToolTip.AddTool(&m_delete_short_notes,GlobalUtilities::get_resource_string(IDS_DELETE_SHORT_NOTES));
	m_pToolTip.AddTool(&m_quantize,GlobalUtilities::get_resource_string(IDS_QUANTIZE));
	m_pToolTip.AddTool(&m_lengthen,GlobalUtilities::get_resource_string(IDS_LENGTHEN));
	m_pToolTip.AddTool(&m_time_signature,GlobalUtilities::get_resource_string(IDS_TIME_SIGNATURE));
	m_pToolTip.AddTool(&m_click_chan,GlobalUtilities::get_resource_string(IDS_CLICK_CHAN));
	
	m_pToolTip.Activate(true);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Extras_Dlg 

void Extras_Dlg::OnSongname() 
{
	if (batch_running||delete_kbd_events_folder_running||vh_act_deact_folder_running) return;

	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = mainfun->Selectsource();
		if (hpmfi==NULL)
		{
			return;
		}
	}
	mainfun->Stop();

	CString composer;
	CString lyricist;
	hpmfi->get_composer_lyricist(&composer, &lyricist);

	CSongname dlg;
	dlg.songname = hpmfi->get_songname();
	dlg.composer = composer;
	dlg.lyricist = lyricist;

	int dlg_result = dlg.DoModal();
	if (dlg_result == 1)
	{	SetCursor(hCursorWait);	
		mainfun->save_state();
		hpmfi->eval_songname_composer_lyricist(dlg.songname, dlg.composer, dlg.lyricist);
		mainfun->analyse_changes();
		SetCursor(hCursorOld);	
	}
}

void Extras_Dlg::OnCopyright() 
{
	if (batch_running||delete_kbd_events_folder_running||vh_act_deact_folder_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = mainfun->Selectsource();
		if (hpmfi==NULL)
		{
			return;
		}
	}

	mainfun->Stop();

	CopyrightDlg dlg;
	dlg.hpmfi = hpmfi;

	int no_double_notes;
	int no_pitch_wheels;
	hpmfi->eval_xg_convert(&no_double_notes,&no_pitch_wheels);

	CString old_copyright = hpmfi->get_copyright();
	dlg.copyright = old_copyright;

	int dlg_result = dlg.DoModal();
	if (dlg_result == 1)
	{
		SetCursor(hCursorWait);	
		mainfun->save_state();
		hpmfi->eval_copyright(old_copyright,dlg.copyright);
		mainfun->analyse_changes();
		SetCursor(hCursorOld);	
	}
}

void Extras_Dlg::OnVocalHarmony() 
{
	bool singlefile_wanted = false;

	if ((batch_running||delete_kbd_events_folder_running)&&!vh_act_deact_folder_running) return;
	if (vh_act_deact_folder_running)
	{
		if (IDNO == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_VH_ACT_DEACT_ABORT),MB_YESNO,0)) return;
		vh_act_deact_folder_abort_wanted = true;
		return;
	}

	if (hpmfi == NULL)
	{
		CString r;
		r.Format(GlobalUtilities::get_resource_string(IDS_VH_ACT_DEACT_FOLDER));
	
		if (IDYES != AfxMessageBox(r,MB_YESNO,0))
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
			hpmfi = mainfun->Selectsource();
			return;
		}
		
		if ((hpmfi==0) && !singlefile_wanted)
		{
			// initiate batch
			MSG msg;
			vh_act_deact_folder_running = true;
			vh_act_deact_folder_abort_wanted = false;
			CString batch_running_text = GlobalUtilities::get_resource_string(IDS_BATCH_RUNNING);
			SetWindowText("Vocal Harmony    "+batch_running_text);

			vh_act_deact_dlg = new VhActDeactDlg;

			int return_value = vh_act_deact_dlg->DoModal();

			if (return_value == -1)
			{
				delete vh_act_deact_dlg;
				vh_act_deact_dlg = NULL;
				vh_act_deact_folder_running = false;
				vh_act_deact_folder_abort_wanted = false;
				SetDlgItemText(IDC_FILENAME,"");
				SetWindowText("Extras");
				Invalidate();   
				UpdateWindow();
				return;
			}

			hThread = CreateThread(
				NULL,	// Security attribute
				0,		// Initial stacksize
				(LPTHREAD_START_ROUTINE)vh_act_deact_thread_run, // start function in the thread
				this,	// Argument for the start function, here pointer to the actual object
				0,		// Creation flags
				&threadID // Pointer of the thread identifier
							);	
			SetThreadPriority(hThread,THREAD_PRIORITY_BELOW_NORMAL);

			// The thread is interrupted all 50 milliseconds.
			// to look for and pump messages.  
			while (WaitForSingleObject(hThread,50) != WAIT_OBJECT_0)
			{
				while ( ::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)) 
				{ 
					if (!AfxGetApp()->PumpMessage()) 
					{ 
						break; 
					} 
				}
			}

			CloseHandle(hThread);

			delete vh_act_deact_dlg;
			vh_act_deact_dlg = NULL;

			vh_act_deact_folder_running = false;
			vh_act_deact_folder_abort_wanted = false;
			SetDlgItemText(IDC_FILENAME,"");
			SetWindowText("Extras");
			Invalidate();   
			UpdateWindow();
			::MessageBox(AfxGetMainWnd()->m_hWnd,
				GlobalUtilities::get_resource_string(IDS_BATCH_PERFORMED),"",MB_OK|MB_TASKMODAL);
			return;
		}
	}

	// single file

	mainfun->Stop();
	VHChanDlg dlg;
	dlg.hpmfi = hpmfi;

	int dlg_result = dlg.DoModal();
	if (dlg_result == -1) return; // cancel

	SetCursor(hCursorWait);	
	mainfun->save_state();

	hpmfi->eval_vh_vocoder( dlg.act_vocoder_channel,
							dlg.vocoder_channel_set,
							dlg.vocoder_channel_delete,
							dlg.vocoder_channel_act);
	
	if (dlg.no_quarters>0)
	{
		if (dlg.act_vocoder_channel>=0)
		{
			// is_vocoder == true: minimal distance from next note 4 ticks 
/*	
			CString r;
			r.Format("channel %i, no_quarters %i",dlg.act_vocoder_channel,dlg.no_quarters);
			MessageBox(r);
*/
			hpmfi->eval_lengthen_vh_notes(dlg.act_vocoder_channel,(dlg.no_quarters)*hpmfi->ppqn,true);

		}
	}
	mainfun->analyse_changes();
	SetCursor(hCursorOld);	
}


void Extras_Dlg::OnQuickstart() 
{
	if (batch_running||delete_kbd_events_folder_running||vh_act_deact_folder_running) return;

	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = mainfun->Selectsource();
		if (hpmfi==NULL)
		{
			return;
		}
	}
	mainfun->Stop();

	Quickstart dlg;
	bool orig_quickstart = hpmfi->get_quickstart();
	dlg.with_quickstart = orig_quickstart;

	int dlg_result = dlg.DoModal();
	if ((dlg_result == 1) && (orig_quickstart != dlg.with_quickstart))
	{
		SetCursor(hCursorWait);	
		mainfun->save_state();
		hpmfi->eval_quickstart(dlg.with_quickstart);
		mainfun->analyse_changes();
		SetCursor(hCursorOld);	
	}
}

void Extras_Dlg::OnDeleteShortNotes() 
{
	if (batch_running||delete_kbd_events_folder_running||vh_act_deact_folder_running) return;

	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = mainfun->Selectsource();
		if (hpmfi==NULL)
		{
			return;
		}
	}

	Delete_short_notes dlg;
	dlg.hpmfi = hpmfi;

	int dlg_result = dlg.DoModal();

	if (dlg_result == 1)
	{
		SetCursor(hCursorWait);	
		mainfun->save_state();
		hpmfi->eval_delete_short_notes(dlg.chan_list,dlg.upto_tick);
		mainfun->analyse_changes();
		SetCursor(hCursorOld);	
	}
}


void Extras_Dlg::OnDeleteMidiEvents() 
{
	if (batch_running||delete_kbd_events_folder_running||vh_act_deact_folder_running) return;

	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = mainfun->Selectsource();
		if (hpmfi==NULL)
		{
			return;
		}
	}

	Delete_MIDI_Events dlg;
	dlg.hpmfi = hpmfi;

	int dlg_result = dlg.DoModal();

	if (dlg_result == 1)
	{
		SetCursor(hCursorWait);	
		mainfun->save_state();
		hpmfi->eval_delete_midi_events(dlg.is_checked,dlg.event_type,dlg.ctrl_number,dlg.before_notes_checked,dlg.note_area_checked);
		mainfun->analyse_changes();
		SetCursor(hCursorOld);	
	}
}


DWORD Extras_Dlg::delete_kbd_events_thread_run(Extras_Dlg *this_thread)
{
	this_thread->delete_kbd_events_folder();
	return 1;
}


void Extras_Dlg::delete_kbd_events_folder()
{
	if (delete_kbd_events_dlg == NULL) return;

	CString source_title = GlobalUtilities::get_resource_string(IDS_SOURCE_FOLDER_EXECUTE);
	CString dest_title = GlobalUtilities::get_resource_string(IDS_DEST_FOLDER_EXECUTE);
	char sel_path[MAX_PATH];

	// source folder
	
	ITEMIDLIST *sourceitemidlist;
	BROWSEINFO path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		source_title, // Select the path for source-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	sourceitemidlist = SHBrowseForFolder(&path_info);
	if(!SHGetPathFromIDList(sourceitemidlist,sel_path))
	{
		return;
	}
	
	// Conversion to CString
	CString selected_source_path = (CString)sel_path;

	// destination folder
	ITEMIDLIST *destitemidlist;
	BROWSEINFO dest_path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		dest_title, // Select the path for the destination-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	destitemidlist = SHBrowseForFolder(&dest_path_info);
	if(!SHGetPathFromIDList(destitemidlist,sel_path))
	{
		return;
	}

	CString selected_dest_path = (CString)sel_path;
	
	int last_index = selected_source_path.GetLength()-1;
	if (selected_source_path.GetAt(last_index)=='\\')
	{
		selected_source_path = selected_source_path.Left(last_index);
	}


	// Look for midifiles
	CFileFind mid_finder;
	if (mid_finder.FindFile(selected_source_path+"\\"+"*.mid"))
	{
		int nextfile;
		while (true)
		{
			if (delete_kbd_events_folder_abort_wanted)
			{
				break;
			}
			nextfile = mid_finder.FindNextFile();
			CString midifile = mid_finder.GetFilePath();
			delete_kbd_events_folder_file(midifile,selected_dest_path,del_kbd_voice_events,del_style_events);
			if (nextfile==0) break;
		}
	}

	// Look for kar-files
	CFileFind kar_finder;
	if (!kar_finder.FindFile(selected_source_path+"\\"+"*.kar"))
	{
		return;
	}
	else
	{
		int nextfile;
		while (true)
		{
			if (delete_kbd_events_folder_abort_wanted)
			{
				break;
			}
			nextfile = kar_finder.FindNextFile();
			CString midifile = kar_finder.GetFilePath();
			delete_kbd_events_folder_file(midifile,selected_dest_path,del_kbd_voice_events,del_style_events);
			if (nextfile==0) break;
		}
	}
}

void Extras_Dlg::delete_kbd_events_folder_file(CString midifile,CString dest_path,bool del_kbd_voice_events,bool del_style_events)
{
	int i;
	for (i=0; i<midifile.GetLength();i++)
	{
		sourcefile[i] = midifile.GetAt(i);
	}
	sourcefile[i] = 0x00;
	initialize_source_reduced();
	if (hpmfi == NULL) return;

	int no_double_notes;
	int no_pitch_wheels;
	hpmfi->eval_xg_convert(&no_double_notes, &no_pitch_wheels);

	CString batch_running_text = GlobalUtilities::get_resource_string(IDS_BATCH_RUNNING);

	midifile = midifile.Left(midifile.GetLength()-4);
	char title[MAX_PATH];
	GetFileTitle(midifile,title,MAX_PATH);
	SetWindowText("Keyboard Events    "+batch_running_text+ ":   "+title);
		
    hpmfi->eval_delete_kbd_events(del_kbd_voice_events, del_score_start_bar_events, del_phrase_events,
                                del_guide_track_events, del_sysex_guide_events, del_lyrics_bitmap_events,
								del_style_events, del_sp_marker_events);
	
	CString destination = dest_path+"\\";
	destination += title;
	destination += ".mid";

	hpmfi->eval_save(destination);

	delete hpmfi;
	hpmfi = NULL;
}

void Extras_Dlg::OnDeleteKbdEvents() 
{
	bool singlefile_wanted = false;

	if ((batch_running||vh_act_deact_folder_running)&&!delete_kbd_events_folder_running) return;

	if (delete_kbd_events_folder_running)
	{
		if (IDNO == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_DELETE_KBD_EVENTS_ABORT),MB_YESNO,0)) return;
		delete_kbd_events_folder_abort_wanted = true;
		return;
	}

	if (hpmfi == NULL)
	{
		CString r;
		r.Format(GlobalUtilities::get_resource_string(IDS_DELETE_KBD_EVENTS_FOLDER));
		if (IDYES != AfxMessageBox(r,MB_YESNO,0))
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
			hpmfi = mainfun->Selectsource();
			return;
		}
		
		if ((hpmfi==NULL) && !singlefile_wanted)
		{
			// initiate batch
			MSG msg;
			delete_kbd_events_folder_running = true;
			delete_kbd_events_folder_abort_wanted = false;
			CString batch_running_text = GlobalUtilities::get_resource_string(IDS_BATCH_RUNNING);
			SetWindowText("Keyboard Events    "+batch_running_text);

			delete_kbd_events_dlg = new delete_keyboard_events;

			int return_value = delete_kbd_events_dlg->DoModal();

			if (return_value == -1)
			{
				delete delete_kbd_events_dlg;
				delete_kbd_events_dlg = NULL;
				delete_kbd_events_folder_running = false;
				delete_kbd_events_folder_abort_wanted = false;
				SetDlgItemText(IDC_FILENAME,"");
				SetWindowText("Extras");
				Invalidate();   
				UpdateWindow();
				return;
			}
			del_kbd_voice_events = delete_kbd_events_dlg->del_kbd_voice_events;
			del_score_start_bar_events = delete_kbd_events_dlg->del_score_start_bar_events;
			del_phrase_events = delete_kbd_events_dlg->del_phrase_events;
			del_guide_track_events = delete_kbd_events_dlg->del_guide_track_events;
			del_sysex_guide_events = delete_kbd_events_dlg->del_sysex_guide_events;
			del_lyrics_bitmap_events = delete_kbd_events_dlg->del_lyrics_bitmap_events;
			del_style_events = delete_kbd_events_dlg->del_style_events;
			del_sp_marker_events = delete_kbd_events_dlg->del_sp_marker_events;
			
			if (!del_kbd_voice_events && 
				!del_score_start_bar_events &&
				!del_phrase_events &&
				!del_guide_track_events &&
				!del_sysex_guide_events &&
				!del_lyrics_bitmap_events &&
				!del_style_events &&
				!del_sp_marker_events
			   )
			{  // same as above  
				delete delete_kbd_events_dlg;
				delete_kbd_events_dlg = NULL;
				delete_kbd_events_folder_running = false;
				delete_kbd_events_folder_abort_wanted = false;
				SetDlgItemText(IDC_FILENAME,"");
				SetWindowText("Extras");
				Invalidate();   
				UpdateWindow();
				return;
			}
			
			
			hThread = CreateThread(
				NULL,	// Security attribute
				0,		// Initial stacksize
				(LPTHREAD_START_ROUTINE)delete_kbd_events_thread_run, // start function in the thread
				this,	// Argument for the start function, here pointer to the actual object
				0,		// Creation flags
				&threadID // Pointer of the thread identifier
							);	
			SetThreadPriority(hThread,THREAD_PRIORITY_BELOW_NORMAL);

			// The thread is interrupted all 50 milliseconds.
			// to look for and pump messages.  
			while (WaitForSingleObject(hThread,50) != WAIT_OBJECT_0)
			{
				while ( ::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)) 
				{ 
					if (!AfxGetApp()->PumpMessage()) 
					{ 
						break; 
					} 
				}
			}

			CloseHandle(hThread);

			delete delete_kbd_events_dlg;
			delete_kbd_events_dlg = NULL;

			delete_kbd_events_folder_running = false;
			delete_kbd_events_folder_abort_wanted = false;
			del_kbd_voice_events = false;
			del_style_events = false;

			SetDlgItemText(IDC_FILENAME,"");
			SetWindowText("Extras");
			Invalidate();   
			UpdateWindow();
			::MessageBox(AfxGetMainWnd()->m_hWnd,
				GlobalUtilities::get_resource_string(IDS_BATCH_PERFORMED),"",MB_OK|MB_TASKMODAL);
			return;
		}
	}

	// single file

	del_kbd_voice_events = false;
	del_style_events = false;
	mainfun->Stop();
	delete_keyboard_events dlg;
	int dlg_result = dlg.DoModal();
	if (dlg_result != 1) return;

	del_kbd_voice_events = dlg.del_kbd_voice_events;
	del_score_start_bar_events = dlg.del_score_start_bar_events;
	del_phrase_events = dlg.del_phrase_events;
	del_guide_track_events = dlg.del_guide_track_events;
	del_sysex_guide_events = dlg.del_sysex_guide_events;
	del_lyrics_bitmap_events = dlg.del_lyrics_bitmap_events;
	del_style_events = dlg.del_style_events;
	del_sp_marker_events = dlg.del_sp_marker_events;

	bool eval_needed =
		del_kbd_voice_events||
		del_style_events ||
		del_score_start_bar_events ||
		del_phrase_events ||
		del_guide_track_events ||
		del_sysex_guide_events ||
		del_lyrics_bitmap_events||
		del_sp_marker_events;


	if (eval_needed)
	{
		SetCursor(hCursorWait);	
		mainfun->save_state();
		int no = 
			hpmfi->eval_delete_kbd_events(del_kbd_voice_events, del_score_start_bar_events, 
			                              del_phrase_events, del_guide_track_events, del_sysex_guide_events, 
										  del_lyrics_bitmap_events, del_style_events, del_sp_marker_events);
		mainfun->analyse_changes();
		SetCursor(hCursorOld);
		CString r;
		r.Format("%i ",no);
		r = r+GlobalUtilities::get_resource_string(IDS_NO_KBD_EVENTS);
		MessageBox(r);
	}
}

void Extras_Dlg::OnNormalizeChords() 
{
	if (batch_running||delete_kbd_events_folder_running||vh_act_deact_folder_running) return;

	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = mainfun->Selectsource();
		if (hpmfi==NULL)
		{
			return;
		}
	}

	mainfun->Stop();
	int no = hpmfi->eval_normalize_chords();
	mainfun->analyse_changes();

	CString r;
	r.Format("%i ",no);
	r = r+GlobalUtilities::get_resource_string(IDS_CHORDS_CHANGED);
	MessageBox(r);
}


void Extras_Dlg::OnQuantize() 
{
	if (batch_running||delete_kbd_events_folder_running||vh_act_deact_folder_running) return;

	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = mainfun->Selectsource();
		if (hpmfi==NULL)
		{
			return;
		}
	}

	mainfun->Stop();

	CQuantizeDlg dlg;

	dlg.hpmfi = hpmfi;

	int dlg_result = dlg.DoModal();

	if (dlg_result == 1)
	{
		SetCursor(hCursorWait);	
		mainfun->save_state();
		hpmfi->eval_quantize_notes(dlg.chan, dlg.length_code, dlg.starts, dlg.note_length);
		mainfun->analyse_changes();
		SetCursor(hCursorOld);	
	}
}


void Extras_Dlg::OnOK() 
{
	if (batch_running||delete_kbd_events_folder_running||vh_act_deact_folder_running) return;
	EndDialog(0); // 0: cancelled, 1: OK
}

void Extras_Dlg::OnClose() 
{
	if (batch_running||delete_kbd_events_folder_running||vh_act_deact_folder_running) return;
	OnOK();
}



DWORD Extras_Dlg::vh_act_deact_thread_run(Extras_Dlg *this_thread)
{
	this_thread->vh_act_deact_folder();
	return 1;
}

void Extras_Dlg::vh_act_deact_folder()
{
	if (vh_act_deact_dlg == NULL) return;

	int  vh_channel =  vh_act_deact_dlg->vh_channel;
	bool vh_select =   vh_act_deact_dlg->vh_select;
	bool vh_deselect = vh_act_deact_dlg->vh_deselect;
	int vh_act =      vh_act_deact_dlg->vh_act;
/*
	CString r;
	r.Format("vh_channel %i\nvh_select %i\nvh_deselect %i\nvh_act %i",
		vh_channel,vh_select,vh_deselect,vh_act);
	MessageBox(r);
	return;
*/

	CString source_title = GlobalUtilities::get_resource_string(IDS_SOURCE_FOLDER_EXECUTE);
	CString dest_title = GlobalUtilities::get_resource_string(IDS_DEST_FOLDER_EXECUTE);

	// source folder
//
	char sel_path[MAX_PATH];
	
	ITEMIDLIST *sourceitemidlist;
	BROWSEINFO path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		source_title, // Select the path for source-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	sourceitemidlist = SHBrowseForFolder(&path_info);
	if(!SHGetPathFromIDList(sourceitemidlist,sel_path))
	{
		return;
	}
	
	// Conversion to CString
	CString selected_source_path = (CString)sel_path;


	// destination folder
	ITEMIDLIST *destitemidlist;
	BROWSEINFO dest_path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		dest_title, // Select the path for the destination-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	destitemidlist = SHBrowseForFolder(&dest_path_info);
	if(!SHGetPathFromIDList(destitemidlist,sel_path))
	{
		return;
	}

	CString selected_dest_path = (CString)sel_path;

	int last_index = selected_source_path.GetLength()-1;
	if (selected_source_path.GetAt(last_index)=='\\')
	{
		selected_source_path = selected_source_path.Left(last_index);
	}


	// Look for midifiles
	CFileFind mid_finder;

	if (mid_finder.FindFile(selected_source_path+"\\"+"*.mid"))
	{
		int nextfile;
		while (true)
		{
			if (vh_act_deact_folder_abort_wanted)
			{
				break;
			}
			nextfile = mid_finder.FindNextFile();
			CString midifile = mid_finder.GetFilePath();
			vh_act_deact_folder_file(midifile,selected_dest_path,
				vh_channel,	vh_select, vh_deselect,	vh_act);
	
			if (nextfile==0) break;
		}
	}

	// Look for kar-files
	CFileFind kar_finder;
	if (!kar_finder.FindFile(selected_source_path+"\\"+"*.kar"))
	{
		return;
	}
	else
	{
		int nextfile;
		while (true)
		{
			if (vh_act_deact_folder_abort_wanted)
			{
				break;
			}
			nextfile = kar_finder.FindNextFile();
			CString midifile = kar_finder.GetFilePath();
			vh_act_deact_folder_file(midifile,selected_dest_path,
				vh_channel,	vh_select, vh_deselect,	vh_act);

			if (nextfile==0) break;
		}
	}
}

void Extras_Dlg::vh_act_deact_folder_file(CString midifile,CString selected_dest_path,
					int vh_channel,	bool vh_select, bool vh_deselect, int vh_act)
{
	int i;
	for (i=0; i<midifile.GetLength();i++)
	{
		sourcefile[i] = midifile.GetAt(i);
	}
	sourcefile[i] = 0x00;
	initialize_source_reduced();
	if (hpmfi == NULL) return;

	int no_double_notes;
	int no_pitch_wheels;
	if (!vh_deselect)
	{
		int no_vh_chan = hpmfi->find_vh_channel(); // no of channels with low velocity
		if (!(hpmfi->vh_channel)[vh_channel])
		{
			//		MessageBox("no VH channel");
			delete hpmfi;
			hpmfi = NULL;
			return;
		}
	}

	hpmfi->eval_xg_convert(&no_double_notes, &no_pitch_wheels);

	CString batch_running_text = GlobalUtilities::get_resource_string(IDS_BATCH_RUNNING);

	midifile = midifile.Left(midifile.GetLength()-4);
	char title[MAX_PATH];
	GetFileTitle(midifile,title,MAX_PATH);
	SetWindowText("Vocal Harmony    "+batch_running_text+ ":   "+title);

	hpmfi->eval_vh_vocoder(vh_channel,vh_select,vh_deselect,vh_act);

	CString destination = selected_dest_path+"\\";
	destination += title;
	destination += ".mid";

	hpmfi->eval_save(destination);

	delete hpmfi;
	hpmfi = NULL;
}

void Extras_Dlg::initialize_source_reduced()
{
	hpmfi = new HPMF_Interface(
		NULL, // here no logging
		sourcefile,
		o_inifile);
	
	if (hpmfi->bad_error)
	{
		delete hpmfi;
		hpmfi = NULL;
		SetDlgItemText(IDC_FILENAME,"");
		SetCursor(hCursorOld);
		return;
	}
}


void Extras_Dlg::OnLengthen() 
{
	if (batch_running||delete_kbd_events_folder_running||vh_act_deact_folder_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = mainfun->Selectsource();
		if (hpmfi==NULL)
		{
			return;
		}
	}
	mainfun->Stop();
	CLengthen_Notes dlg;

	dlg.hpmfi = hpmfi;
	mainfun->save_state();
	int dlg_result = dlg.DoModal();
/*
CString r;
r.Format("OnLengthen 6: %i",dlg_result);
MessageBox(r);
*/
	if (dlg_result == 1)
	{
		mainfun->analyse_changes();
	}
}

void Extras_Dlg::OnTimeSignature() 
{
	if (batch_running||delete_kbd_events_folder_running||vh_act_deact_folder_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = mainfun->Selectsource();
		if (hpmfi==NULL)
		{
			return;
		}
	}

	mainfun->Stop();

	Time_Signature dlg;
	dlg.hpmfi = hpmfi;
	dlg.p_inifile = o_inifile;
	dlg.hCursorWait = hCursorWait;
	dlg.hCursorOld = hCursorOld;

	mainfun->save_state();
	int dlg_result = dlg.DoModal();

	if (dlg_result == 1)
	{
		mainfun->analyse_changes();
	}

}

void Extras_Dlg::OnClickChan() 
{
	if (batch_running||delete_kbd_events_folder_running||vh_act_deact_folder_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = mainfun->Selectsource();
		if (hpmfi==NULL)
		{
			return;
		}
	}
	
	mainfun->Stop();

	int time_start_beat_start;
	int time_start_beat_end;

	bool with_start_beats = hpmfi->with_start_beats(&time_start_beat_start,&time_start_beat_end);

	if (with_start_beats)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_DELETE_COUNT_IN),NULL,MB_OK|MB_TASKMODAL);
		return;
	}

	bool chan_empty = hpmfi->no_notes[9]==0;

	if (!chan_empty)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_DELETE_CHAN_10),NULL,MB_OK|MB_TASKMODAL);
		return;
	}

	ClickChanDlg dlg;
	dlg.o_inifile = o_inifile;

	int result = dlg.DoModal();
	if (result==1)
	{
		return;
	}

	int msb_chan10=127;
	int lsb_chan10=0;

	int main_vol_chan10 = dlg.main_vol_chan10;
	int noteval_meas = dlg.noteval_meas;
	int vel_meas = dlg.vel_meas;
	int noteval_beat = dlg.noteval_beat;
	int vel_beat = dlg.vel_beat;

/*
	Default values:	
	int main_vol_chan10 = 60;
	int noteval_meas = 24; // Seq Klick H
	int vel_meas = 127;
	int noteval_beat = 23; // Seq Klick L
	int vel_beat = 100;
*/
    // Set the predefined Windows "Wait" cursor.
	SetCursor(hCursorWait);

	mainfun->save_state();

	hpmfi->eval_insert_klick(msb_chan10,lsb_chan10,main_vol_chan10,
		noteval_meas, vel_meas, noteval_beat, vel_beat);

	o_inifile->set_click_main_vol(main_vol_chan10);
	o_inifile->set_click_note_meas(noteval_meas);
	o_inifile->set_click_note_beat(noteval_beat);
	o_inifile->set_click_vel_meas(vel_meas);
	o_inifile->set_click_vel_beat(vel_beat);

	mainfun->analyse_changes();

	SetCursor(hCursorOld);


	::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_CLICKS_INSERTED),NULL,MB_OK|MB_TASKMODAL);
}

void Extras_Dlg::OnScore() 
{
	if (batch_running||delete_kbd_events_folder_running||vh_act_deact_folder_running) return;

	mainfun->Stop();

	Score dlg;

	dlg.hpmfi = hpmfi;
	dlg.hCursorWait = hCursorWait;
	dlg.hCursorOld = hCursorOld;
	dlg.batch_running = batch_running||delete_kbd_events_folder_running||vh_act_deact_folder_running;
	dlg.o_inifile = o_inifile;
	dlg.mainfun = mainfun;

	int dlg_result = dlg.DoModal();

	if (dlg_result == 10)
	{
		OnScore();
	}
}
