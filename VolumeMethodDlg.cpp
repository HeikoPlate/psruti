// VolumeMethodDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "VolumeMethodDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "GlobalUtilities.h"
#include "Expr_Mainvolume.h"
#include "MasterVolume.h"
#include "MainFunctions.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld VolumeMethodDlg 

DWORD VolumeMethodDlg::master_volume_thread_run(VolumeMethodDlg *this_thread)
{
	this_thread->master_volume_folder();
	return 1; // Return with any value. The thread will be ended implicitely.
}

void VolumeMethodDlg::master_volume_folder()
{	
	if (master_volume_dlg == NULL) return;

	int master_volume_value = master_volume_dlg->get_value();

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
			if (master_volume_folder_abort_wanted)
			{
				break;
			}
			nextfile = mid_finder.FindNextFile();
			CString midifile = mid_finder.GetFilePath();
			master_volume_folder_file(midifile,selected_dest_path,master_volume_value);
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
			if (master_volume_folder_abort_wanted)
			{
				break;
			}
			nextfile = kar_finder.FindNextFile();
			CString midifile = kar_finder.GetFilePath();
			master_volume_folder_file(midifile,selected_dest_path,master_volume_value);
			if (nextfile==0) break;
		}
	}

}

void VolumeMethodDlg::master_volume_folder_file(CString midifile,CString dest_path, int master_volume_val)
{
	int i;
	for (i=0; i<midifile.GetLength();i++)
	{
		sourcefile[i] = midifile.GetAt(i);
	}
	sourcefile[i] = 0x00;
	mini_initialize_source(); 
	if (hpmfi == NULL) return;

	hpmfi->eval_insert_or_change_master_volume(master_volume_val);

	int no_double_notes;
	int no_pitch_wheels;
	hpmfi->eval_xg_convert(&no_double_notes, &no_pitch_wheels);

	midifile = midifile.Left(midifile.GetLength()-4);
	char title[MAX_PATH];
	GetFileTitle(midifile,title,MAX_PATH);
	CString destination = dest_path+"\\";
	destination += title;
	destination += ".mid";

	hpmfi->eval_save(destination);
	if (hpmfi != NULL)
	{
		delete hpmfi;
		hpmfi = NULL;
	}
}

DWORD VolumeMethodDlg::mainvolume_expression_thread_run(VolumeMethodDlg *this_thread)
{
	this_thread->mainvolume_expression_folder();
	return 1; // Return with any value. The thread will be ended implicitely.
}


void VolumeMethodDlg::mini_initialize_source()
{
	hpmfi = new HPMF_Interface(lf,sourcefile,o_inifile);
	
	if (hpmfi->bad_error)
	{
		delete hpmfi;
		hpmfi = NULL;
		return;
	}
}

void VolumeMethodDlg::mainvolume_expression_folder()
{	
	if (mainvolume_expression_dlg == NULL) return;

	bool mainvolume_to_expression = mainvolume_expression_dlg->get_mainvolume_to_expression();

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
			if (mainvolume_expression_abort_wanted)
			{
				break;
			}
			nextfile = mid_finder.FindNextFile();
			CString midifile = mid_finder.GetFilePath();
			mainvolume_expression_folder_file(midifile,selected_dest_path,mainvolume_to_expression);
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
			if (mainvolume_expression_abort_wanted)
			{
				break;
			}
			nextfile = kar_finder.FindNextFile();
			CString midifile = kar_finder.GetFilePath();
			mainvolume_expression_folder_file(midifile,selected_dest_path,mainvolume_to_expression);
			if (nextfile==0) break;
		}
	}
}

void VolumeMethodDlg::mainvolume_expression_folder_file(CString midifile,CString dest_path, bool mainvolume_to_expression)
{
	int i;
	for (i=0; i<midifile.GetLength();i++)
	{
		sourcefile[i] = midifile.GetAt(i);
	}
	sourcefile[i] = 0x00;
	mini_initialize_source(); 
	if (hpmfi == NULL) return;
	hpmfi->eval_expr_mvolume(!mainvolume_to_expression);
	midifile = midifile.Left(midifile.GetLength()-4);
	char title[MAX_PATH];
	GetFileTitle(midifile,title,MAX_PATH);
	CString destination = dest_path+"\\";
	destination += title;
	destination += ".mid";

	hpmfi->eval_save(destination);
	if (hpmfi != NULL)
	{
		delete hpmfi;
		hpmfi = NULL;
	}
}

VolumeMethodDlg::VolumeMethodDlg(CWnd* pParent /*=NULL*/)
	: CDialog(VolumeMethodDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(VolumeMethodDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	batch_running = false;
	master_volume_folder_running = false;
	master_volume_folder_abort_wanted = false;
	master_volume_dlg = NULL;
	mainvolume_expression_folder_running = false;
	mainvolume_expression_abort_wanted = false;
	mainvolume_expression_dlg = NULL;
}


void VolumeMethodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VolumeMethodDlg)
	DDX_Control(pDX, IDC_EXPRESSION_MAINVOLUME, m_expression_mainvolume);
	DDX_Control(pDX, IDC_MASTER_VOLUME, m_master_volume);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VolumeMethodDlg, CDialog)
	//{{AFX_MSG_MAP(VolumeMethodDlg)
	ON_BN_CLICKED(IDC_EXPRESSION_MAINVOLUME, OnExpressionMainvolume)
	ON_BN_CLICKED(IDC_MASTER_VOLUME, OnMasterVolume)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipDlg Nachrichten-Handler


BOOL VolumeMethodDlg::PreTranslateMessage(MSG* pMSG)
{
	m_pToolTip.RelayEvent(pMSG);
	return CDialog::PreTranslateMessage(pMSG);
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten VolumeMethodDlg 

void VolumeMethodDlg::OnExpressionMainvolume() 
{
	bool singlefile_wanted = false;

	if (master_volume_folder_running) return;

	if (mainvolume_expression_folder_running)
	{
		if (IDNO == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_MAIN_VOLUME_EXPRESSION_ABORT),MB_YESNO,0)) return;
		mainvolume_expression_abort_wanted = true;
		return;
	}
	if (hpmfi == NULL)
	{
		CString r;
		r.Format(GlobalUtilities::get_resource_string(IDS_MAIN_VOLUME_EXPRESSION_FOLDER));
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
			mainvolume_expression_folder_running = true;
			mainvolume_expression_abort_wanted = false;
			batch_running = true;
			CString batch_running_text = GlobalUtilities::get_resource_string(IDS_BATCH_RUNNING);
			SetWindowText("Expr.<->MainVol.   "+batch_running_text);

			mainvolume_expression_dlg = new MainVolume_Expression_Folder_Dlg;
			int return_value = mainvolume_expression_dlg->DoModal();

			if (return_value == -1)
			{
				delete mainvolume_expression_dlg;
				mainvolume_expression_dlg = NULL;
				mainvolume_expression_folder_running = false;
				mainvolume_expression_abort_wanted = false;
				batch_running = false;
				Invalidate();   
				UpdateWindow();
				return;
			}


			hThread = CreateThread(
				NULL,	// Security attribute
				0,		// Initial stacksize
				(LPTHREAD_START_ROUTINE)mainvolume_expression_thread_run, // start function in the thread
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

			delete mainvolume_expression_dlg;
			mainvolume_expression_dlg = NULL;
			mainvolume_expression_folder_running = false;
			mainvolume_expression_abort_wanted = false;
			batch_running = false;
			::MessageBox(AfxGetMainWnd()->m_hWnd,
				GlobalUtilities::get_resource_string(IDS_BATCH_PERFORMED),"",MB_OK|MB_TASKMODAL);
			SetWindowText("Expression <-> Main Volume");
			Invalidate();   
			UpdateWindow();
			return;
		}
	}

	// single file

	Expr_MainVolume dlg;
	if (dlg.DoModal() == 0) // 0: cancelled, 1: OK
	{
		EndDialog(0);
		return;
	}

	bool change_to_mvolume = dlg.change_to_mvolume();

    // Set the predefined Windows "Wait" cursor.
	SetCursor(hCursorWait);
	mainfun->save_state();
	int no_changes = hpmfi->eval_expr_mvolume(change_to_mvolume);

	// Set the old cursor back
	SetCursor(hCursorOld);

	CString r = GlobalUtilities::get_resource_string(IDS_NO_EXPR_MVOLUME_CHANGES);
	CString s;
	s.Format("%i %s",no_changes,r);
	::MessageBox(AfxGetMainWnd()->m_hWnd,s,"",MB_OK|MB_TASKMODAL);
	GoBackOK();
}

void VolumeMethodDlg::OnMasterVolume() 
{
	bool singlefile_wanted = false;
	if (mainvolume_expression_folder_running) return;

	if (master_volume_folder_running)
	{
		if (IDNO == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_MASTER_VOLUME_ABORT),MB_YESNO,0)) return;
		master_volume_folder_abort_wanted = true;
		return;
	}
	if (hpmfi == NULL)
	{
		CString r;
		r.Format(GlobalUtilities::get_resource_string(IDS_MASTER_VOLUME_FOLDER));
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
			master_volume_folder_running = true;
			master_volume_folder_abort_wanted = false;
			batch_running = true;
			CString batch_running_text = GlobalUtilities::get_resource_string(IDS_BATCH_RUNNING);
			SetWindowText("Volume         "+batch_running_text);

			master_volume_dlg = new Master_Volume_Folder_Dlg;
			int return_value = master_volume_dlg->DoModal();

			if (return_value == -1)
			{
				delete master_volume_dlg;
				master_volume_dlg = NULL;
				master_volume_folder_running = false;
				master_volume_folder_abort_wanted = false;
				batch_running = false;
				Invalidate();   
				UpdateWindow();
				return;
			}


			hThread = CreateThread(
				NULL,	// Security attribute
				0,		// Initial stacksize
				(LPTHREAD_START_ROUTINE)master_volume_thread_run, // start function in the thread
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

			delete master_volume_dlg;
			master_volume_dlg = NULL;
			master_volume_folder_running = false;
			master_volume_folder_abort_wanted = false;
			batch_running = false;
			::MessageBox(AfxGetMainWnd()->m_hWnd,
				GlobalUtilities::get_resource_string(IDS_BATCH_PERFORMED),"",MB_OK|MB_TASKMODAL);
			SetWindowText("Volume");
			Invalidate();   
			UpdateWindow();
			return;
		}
	}

	
	MasterVolume dlg;

	SetCursor(hCursorWait);
	int max_vol = hpmfi->analyze_master_volume(false);
	SetCursor(hCursorOld);

	dlg.init_master_volume = max_vol==-1?127:max_vol;

	int result = dlg.DoModal();

	if (result == 0) 
	{
		EndDialog(0);
		return;
	}

	SetCursor(hCursorWait);
	mainfun->save_state();
	hpmfi->eval_insert_or_change_master_volume(dlg.master_volume);

	int no_double_notes;
	int no_pitch_wheels;
	hpmfi->eval_xg_convert(&no_double_notes, &no_pitch_wheels);

	SetCursor(hCursorOld);

	return;
}

void VolumeMethodDlg::OnCancel() 
{
	if (batch_running) return;
	EndDialog(0); // 0: cancelled, 1: OK
}

void VolumeMethodDlg::GoBackOK() 
{
	if (batch_running) return;
	mainfun->analyse_changes();
	EndDialog(1); // 0: cancelled, 1: OK
}

BOOL VolumeMethodDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_pToolTip.Create(this);
	m_pToolTip.SetDelayTime(TTDT_AUTOPOP,4000);
	m_pToolTip.SetMaxTipWidth(200);

	m_pToolTip.AddTool(&m_master_volume,GlobalUtilities::get_resource_string(IDS_MASTER_VOLUME));
	m_pToolTip.AddTool(&m_expression_mainvolume,GlobalUtilities::get_resource_string(IDS_EXPR_MVOLUME));

	m_pToolTip.Activate(true);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
