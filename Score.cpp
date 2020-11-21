// Score.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Score.h"
#include "ScoreChanDlg.h"
#include "ScoreLayout.h"
#include "ScoreNotesOptDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Score 


Score::Score(CWnd* pParent /*=NULL*/)
	: CDialog(Score::IDD, pParent)
{
	//{{AFX_DATA_INIT(Score)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	scorelayout_folder_running = false;
	scorechan_folder_running = false;
}


void Score::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Score)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Score, CDialog)
	//{{AFX_MSG_MAP(Score)
	ON_BN_CLICKED(IDC_SCORECHAN, OnScorechan)
	ON_BN_CLICKED(IDC_SCORE_LAYOUT, OnScoreLayout)
	ON_BN_CLICKED(IDC_SCORENOTESOPT, OnScorenotesopt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Score 

void Score::OnScorechan() 
{
	bool singlefile_wanted = false;

	if (batch_running || scorelayout_folder_running) return;
	
	mainfun->Stop();

	if (scorechan_folder_running)
	{
		if (IDNO == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_SCORECHAN_ABORT),MB_YESNO,0))
		{
			return;
		}
			
		scorechan_folder_abort_wanted = true;
		return;
	}

	if (hpmfi == NULL)
	{

	/* *********** Scorechan batch ****************************************** */

		CString r;
		r.Format(GlobalUtilities::get_resource_string(IDS_SCORECHAN_FOLDER));
		if (IDYES != AfxMessageBox(r,MB_YESNO,0))
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
			hpmfi = mainfun->Selectsource();
			return;
		}

		if ((hpmfi==NULL) && !singlefile_wanted)
		{
			scorechan_folder_running = true;
			scorechan_folder_abort_wanted = false;

			scorechan_dlg = new ScoreChanDlg;
			scorechan_dlg->chan_left = 0;
			scorechan_dlg->chan_right = 0;
			scorechan_dlg->hpmfi = NULL;


			// initiate batch
			MSG msg;
			CString batch_running_text = GlobalUtilities::get_resource_string(IDS_BATCH_RUNNING);
			SetWindowText("Score Channel    "+batch_running_text);


			int return_value = scorechan_dlg->DoModal();

			if (return_value == -1)
			{
				delete scorechan_dlg;
				scorechan_dlg = NULL;
				scorechan_folder_running = false;
				scorechan_folder_abort_wanted = false;
				SetDlgItemText(IDC_FILENAME,"");
				SetWindowText("Score");
				Invalidate();   
				UpdateWindow();
				return;
			}

			hThread = CreateThread(
				NULL,	// Security attribute
				0,		// Initial stacksize
				(LPTHREAD_START_ROUTINE)scorechan_thread_run, // start function in the thread
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

			delete scorechan_dlg;
			scorechan_dlg = NULL;

			scorechan_folder_running = false;
			scorechan_folder_abort_wanted = false;

			SetDlgItemText(IDC_FILENAME,"");
			SetWindowText("Score");
			Invalidate();   
			UpdateWindow();
			::MessageBox(AfxGetMainWnd()->m_hWnd,
				GlobalUtilities::get_resource_string(IDS_BATCH_PERFORMED),"",MB_OK|MB_TASKMODAL);
			return;
		}
	}

    /* *********** Score Chan for single file ***************************** */

	ScoreChanDlg dlg;
	dlg.hpmfi = hpmfi;
	int old_score_chan_left;
	int old_score_chan_right;
	hpmfi->get_scorechan(&old_score_chan_left, &old_score_chan_right);
	dlg.chan_left = old_score_chan_left;
	dlg.chan_right = old_score_chan_right;

	int dlg_result = dlg.DoModal();
	if (dlg_result == 1)
	{
		SetCursor(hCursorWait);	
		mainfun->save_state();

		// Quickstart obligat  
		bool orig_quickstart = hpmfi->get_quickstart();
		if (!orig_quickstart)
		{
			hpmfi->eval_quickstart(true);
		}

		hpmfi->eval_scorechan(old_score_chan_left,dlg.chan_left,
			                  old_score_chan_right,dlg.chan_right);
		mainfun->analyse_changes();
		SetCursor(hCursorOld);	
	}
}

void Score::OnScoreLayout() 
{
	bool singlefile_wanted = false;

	if (batch_running || scorechan_folder_running) return;
	mainfun->Stop();

	if (scorelayout_folder_running)
	{
		if (IDNO == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_SCORELAYOUT_ABORT),MB_YESNO,0))
		{
			return;
		}
			
		scorelayout_folder_abort_wanted = true;
		return;
	}


	if (hpmfi == NULL)
	{

	/* *********** Score Layout batch ****************************************** */

		CString r;
		r.Format(GlobalUtilities::get_resource_string(IDS_SCORELAYOUT_FOLDER));
		if (IDYES != AfxMessageBox(r,MB_YESNO,0))
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
			hpmfi = mainfun->Selectsource();
			return;
		}

		if ((hpmfi==NULL) && !singlefile_wanted)
		{
			scorelayout_folder_running = true;
			scorelayout_folder_abort_wanted = false;

			scorelayout_dlg = new ScoreLayout;
			scorelayout_dlg->lyrics_value = 0xff;		
			scorelayout_dlg->notenames_value = 0xff;		 
			scorelayout_dlg->chords_value = 0xff;			 
			scorelayout_dlg->size_value = 0xff;			 
			scorelayout_dlg->quantize_triole_value = 0xff; 
			scorelayout_dlg->quantize_value = 0xff;		 
			scorelayout_dlg->notenamestype_value = 0xff;	 
			scorelayout_dlg->notecolour_value = 0xff;
			scorelayout_dlg->hpmfi = NULL;

			// initiate batch
			MSG msg;
			CString batch_running_text = GlobalUtilities::get_resource_string(IDS_BATCH_RUNNING);
			SetWindowText("Score Layout    "+batch_running_text);

			int return_value = scorelayout_dlg->DoModal();

			if (return_value == -1)
			{
				delete scorelayout_dlg;
				scorelayout_dlg = NULL;
				scorelayout_folder_running = false;
				scorelayout_folder_abort_wanted = false;
				SetDlgItemText(IDC_FILENAME,"");
				SetWindowText("Score");
				Invalidate();   
				UpdateWindow();
				return;
			}
	
			lyrics_value = scorelayout_dlg->lyrics_value;		
			notenames_value = scorelayout_dlg->notenames_value;		 
			chords_value = scorelayout_dlg->chords_value;			 
			size_value = scorelayout_dlg->size_value;			 
			quantize_triole_value = scorelayout_dlg->quantize_triole_value; 
			quantize_value = scorelayout_dlg->quantize_value;		 
			notenamestype_value = scorelayout_dlg->notenamestype_value;	 
			notecolour_value = scorelayout_dlg->notecolour_value;		 
		
			hThread = CreateThread(
				NULL,	// Security attribute
				0,		// Initial stacksize
				(LPTHREAD_START_ROUTINE)scorelayout_thread_run, // start function in the thread
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

			delete scorelayout_dlg;
			scorelayout_dlg = NULL;

			scorelayout_folder_running = false;
			scorelayout_folder_abort_wanted = false;

			SetDlgItemText(IDC_FILENAME,"");
			SetWindowText("Score");
			Invalidate();   
			UpdateWindow();
			::MessageBox(AfxGetMainWnd()->m_hWnd,
				GlobalUtilities::get_resource_string(IDS_BATCH_PERFORMED),"",MB_OK|MB_TASKMODAL);
			return;
		}
	}

    /* *********** Score Layout for single file ***************************** */

    ScoreLayout dlg;
	dlg.hpmfi = hpmfi;


	int dlg_result = dlg.DoModal();
	if (dlg_result == 1) // finished with OnOK; -1 for OnCancel and OnClose
	{

		SetCursor(hCursorWait);	
		mainfun->save_state();

		hpmfi->eval_score_layout(	dlg.lyrics_value, 
									dlg.chords_value, 
									dlg.notenames_value, 
									dlg.size_value, 
									dlg.quantize_triole_value, 
									dlg.quantize_value, 
									dlg.notenamestype_value, 
									dlg.notecolour_value
								);

		mainfun->analyse_changes();
		SetCursor(hCursorOld);
	}
}

DWORD Score::scorelayout_thread_run(Score *this_thread)
{
    this_thread->scorelayout_folder();
	return 1;
}

void Score::scorelayout_folder()
{

	if (scorelayout_dlg == NULL) return;

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
			if (scorelayout_folder_abort_wanted)
			{
				break;
			}
			nextfile = mid_finder.FindNextFile();
			CString midifile = mid_finder.GetFilePath();
			scorelayout_folder_file(midifile,selected_dest_path);
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
			if (scorelayout_folder_abort_wanted)
			{
				break;
			}
			nextfile = kar_finder.FindNextFile();
			CString midifile = kar_finder.GetFilePath();
			scorelayout_folder_file(midifile,selected_dest_path);
			if (nextfile==0) break;
		}
	}
}

void Score::scorelayout_folder_file(CString midifile,CString dest_path)
{
	
	int i;
	for (i=0; i<midifile.GetLength();i++)
	{
		sourcefile[i] = midifile.GetAt(i);
	}
	sourcefile[i] = 0x00;
	initialize_source_reduced();
	if (hpmfi == NULL) return;

	midifile = midifile.Left(midifile.GetLength()-4);
	char title[MAX_PATH];
	GetFileTitle(midifile,title,MAX_PATH);
		
	hpmfi->eval_score_layout(	lyrics_value, 
								chords_value, 
								notenames_value, 
								size_value, 
								quantize_triole_value, 
								quantize_value, 
								notenamestype_value, 
								notecolour_value
							);
	
	CString destination = dest_path+"\\";
	destination += title;
	destination += ".mid";

	hpmfi->eval_save(destination);

	delete hpmfi;
	hpmfi = NULL;

}


DWORD Score::scorechan_thread_run(Score *this_thread)
{
    this_thread->scorechan_folder();
	return 1;
}

void Score::scorechan_folder()
{
	if (scorechan_dlg == NULL) return;

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
			if (scorechan_folder_abort_wanted)
			{

				break;
			}
			nextfile = mid_finder.FindNextFile();
			CString midifile = mid_finder.GetFilePath();
			scorechan_folder_file(midifile,selected_dest_path);
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
			if (scorechan_folder_abort_wanted)
			{
				break;
			}
			nextfile = kar_finder.FindNextFile();
			CString midifile = kar_finder.GetFilePath();
			scorechan_folder_file(midifile,selected_dest_path);
			if (nextfile==0) break;
		}
	}
}

void Score::scorechan_folder_file(CString midifile,CString dest_path)
{
	int i;
	for (i=0; i<midifile.GetLength();i++)
	{
		sourcefile[i] = midifile.GetAt(i);
	}
	sourcefile[i] = 0x00;
	initialize_source_reduced();
	if (hpmfi == NULL) return;

	midifile = midifile.Left(midifile.GetLength()-4);
	char title[MAX_PATH];
	GetFileTitle(midifile,title,MAX_PATH);

	/* ************** insert/change Score chans ***************** */

	// Quickstart obligat  
	bool orig_quickstart = hpmfi->get_quickstart();
	if (!orig_quickstart)
	{
		hpmfi->eval_quickstart(true);
	}

	int old_chan_left; // jetzt belegen
	int old_chan_right; // jetzt belegen

	hpmfi->get_scorechan(&old_chan_left, &old_chan_right);

	int new_chan_left = scorechan_dlg->chan_left;
	int new_chan_right = scorechan_dlg->chan_right;

	// new chans allowed?

	bool allowed_new_chan_left = true;
	bool allowed_new_chan_right = true;
/*
CString r;
r.Format("old_chan_left %i, new_chan_left %i, old_chan_right %i, new_chan_right %i",old_chan_left, new_chan_left, old_chan_right, new_chan_right);
MessageBox(r);
*/
	if (new_chan_left != -1)
	{
		if (((hpmfi->mute)[new_chan_left])||(!(hpmfi->mlv_list)[new_chan_left].melody))
		{
			allowed_new_chan_left = false;
		}
	}

	if (new_chan_right != -1)
	{
		if (((hpmfi->mute)[new_chan_right])||(!(hpmfi->mlv_list)[new_chan_right].melody))
		{
			allowed_new_chan_right = false;
		}
	}



	// insert/change midifile only if channels allowed

	if (allowed_new_chan_left && allowed_new_chan_right)
	{

		hpmfi->eval_scorechan(old_chan_left,scorechan_dlg->chan_left,
			                  old_chan_right,scorechan_dlg->chan_right);
	/*
		CString r;
		r.Format("chan_left %i, chan_right %i",scorechan_dlg->chan_left, scorechan_dlg->chan_right);
		MessageBox(r);
	*/
		CString destination = dest_path+"\\";
		destination += title;
		destination += ".mid";

		hpmfi->eval_save(destination);
	}

	delete hpmfi;
	hpmfi = NULL;

}

void Score::initialize_source_reduced()
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

void Score::OnScorenotesopt() 
{
	if (batch_running || scorelayout_folder_running) return;

	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,
			GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = mainfun->Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}

	mainfun->Stop();

	ScoreNotesOptDlg dlg;
	dlg.hpmfi = hpmfi;

	int dlg_result = dlg.DoModal();
	if (dlg_result == -1) return; // cancel

	SetCursor(hCursorWait);	
	mainfun->save_state();
	if (dlg.act_score_channel>=0)
	{
		// is_vocoder == false: no distance from next note allowed
		hpmfi->eval_lengthen_vh_notes(dlg.act_score_channel,dlg.max_note_ticks,false);
	}
	mainfun->analyse_changes();
	SetCursor(hCursorOld);		
}

void Score::OnOK() 
{
	CDialog::OnOK();
}
