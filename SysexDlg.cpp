// SysexDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "resource.h"
#include "SysexDlg.h"
#include "HPMF_Interface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Dialogfeld CSysexDlg 

CSysexDlg::CSysexDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysexDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSysexDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	p_inifile = CPsrutiDlg::o_inifile;
}


void CSysexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysexDlg)
	DDX_Control(pDX, IDC_MBT_CHECK, m_mbt_check);
	DDX_Control(pDX, IDC_CHECK_READ_NOTE_AREA, m_check_read_note_area);
	DDX_Control(pDX, IDC_TICK, m_tick);
	DDX_Control(pDX, IDC_MEASURE, m_measure);
	DDX_Control(pDX, IDC_BEAT, m_beat);
	DDX_Control(pDX, IDC_CHECK_POSITION, m_check_position);
	DDX_Control(pDX, IDC_SELECT_SYSEX_PASTE_IMPORT_CHECK, m_select_sysex_paste_import_check);
	DDX_Control(pDX, IDC_SYSEX_DELETE_CHECK, m_sysex_delete_check);
	DDX_Control(pDX, IDC_SELECT_SYSEX_FILE_IMPORT_CHECK, m_select_sysex_file_import_check);
	DDX_Control(pDX, IDC_SELECT_SYSEX_EXPORT_CHECK, m_select_sysex_export_check);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSysexDlg, CDialog)
	//{{AFX_MSG_MAP(CSysexDlg)
	ON_BN_CLICKED(IDC_SELECT_SYSEX_FILE_IMPORT_CHECK, OnSelectSysexFileImportCheck)
	ON_BN_CLICKED(IDC_SELECT_SYSEX_EXPORT_CHECK, OnSelectSysexExportCheck)
	ON_BN_CLICKED(IDC_SYSEX_DELETE_CHECK, OnSysexDeleteCheck)
	ON_BN_CLICKED(IDC_SELECT_SYSEX_PASTE_IMPORT_CHECK, OnSelectSysexPasteImportCheck)
	ON_BN_CLICKED(IDC_CHECK_POSITION, OnCheckPosition)
	ON_EN_UPDATE(IDC_MEASURE, OnUpdateMeasure)
	ON_EN_UPDATE(IDC_BEAT, OnUpdateBeat)
	ON_EN_UPDATE(IDC_TICK, OnUpdateTick)
	ON_BN_CLICKED(IDC_CHECK_READ_NOTE_AREA, OnCheckReadNoteArea)
	ON_BN_CLICKED(IDC_MBT_CHECK, OnMbtCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CSysexDlg 

CString CSysexDlg::SelectSysexFile()
{
	int i;
	CString sysexfile;

	char BASED_CODE szFilter[] = 
		"Prot-File (*.txt)|*.txt||";

	CFileDialog openfile_dlg(FALSE,
						  "txt",
						  NULL,
						  OFN_PATHMUSTEXIST,
						  szFilter,
						  NULL);

	// Get last_prot
	CString last_prot = p_inifile->get_protfile();
	if (last_prot != "")
	{
	   openfile_dlg.m_ofn.lpstrInitialDir = last_prot;
	   char lp[MAX_PATH];
	   for (i=0; i<last_prot.GetLength(); i++)
	   {
		   lp[i] = last_prot[i];
	   }
	   lp[last_prot.GetLength()] = (char)0;
	   openfile_dlg.m_ofn.lpstrFile = lp;
	}

	int return_value = openfile_dlg.DoModal();

/* Test */
	if (return_value == IDOK)
	{
		sysexfile = openfile_dlg.m_ofn.lpstrFile;
	}
	else 
	{
		if (return_value == IDCANCEL)
		{
			CString r;
			r.Format("CommDlgExtendedError %x", CommDlgExtendedError());
			MessageBox(r);

			return "";
		}
	}

	// Try sysexfile

	CFile mf_newf;
	CFileException e;

	if (mf_newf.Open(sysexfile, CFile::modeRead,&e))
	{
		int length = mf_newf.GetLength();
		mf_newf.Close();

		if (length>0)
		{
			CString r;
			r.Format(GlobalUtilities::get_resource_string(IDS_UseExistingFile)+"\"%s\" ?",sysexfile); 
			if (IDYES != AfxMessageBox(r,MB_YESNO,0))
			{
				return "";
			}
		}
	}

	p_inifile->set_protfile(sysexfile);
	return sysexfile;
}


bool CSysexDlg::selected_file_import()
{
	return import_file_selected;
}

bool CSysexDlg::selected_paste_import()
{
	return import_paste_selected;
}

bool CSysexDlg::selected_export()
{
	return export_selected;
}

bool CSysexDlg::with_delete()
{
	return is_delete;
}

bool CSysexDlg::selected_note_area()
{
	return is_note_area;
}

CString CSysexDlg::get_protfile()
{
	return protfile;
}

void CSysexDlg::new_position(bool *with_mbt, int *measure,int *beat,int *tick)
{
	*measure = -1;
	*beat = -1;
	*tick = -1;
	*with_mbt = false;

	if (is_note_area && !export_selected)
	{
		if (!is_mbt)
		{
			int scr_time = hpmfi->get_time_from_takt_bar_tick(new_meas, new_bea, new_tic);
			if (scr_time < time_first_note)
			{
				new_meas = measure_first_note;
				new_bea = beat_first_note;
				new_tic = tick_first_note;
			}

			*measure = new_meas;
			*beat = new_bea;
			*tick = new_tic;
		}
		else
		{
			*with_mbt = true;
		}
	}
}

void CSysexDlg::display_measure_beat_tick(int measure, int beat, int tick)
{
	no_on_update_measure_beat_tick = true;
	int display_measure = measure+1;
	int display_beat = beat+1;
	int display_tick = tick;
		
	CWnd::SetDlgItemInt(IDC_MEASURE,display_measure,FALSE);
	CWnd::SetDlgItemInt(IDC_BEAT,display_beat,FALSE);
	CWnd::SetDlgItemInt(IDC_TICK,display_tick,FALSE);
	UpdateWindow();
	no_on_update_measure_beat_tick = false;

	new_meas = measure;
	new_bea = beat;
	new_tic = tick;
}

void CSysexDlg::display_measure_beat_tick_with_blanks()
{
	no_on_update_measure_beat_tick = true;
	SetDlgItemText(IDC_MEASURE,"");
	SetDlgItemText(IDC_BEAT,"");
	SetDlgItemText(IDC_TICK,"");
	no_on_update_measure_beat_tick = false;
}

BOOL CSysexDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_select_sysex_file_import_check.SetCheck(0);
	m_select_sysex_export_check.SetCheck(0);
	m_sysex_delete_check.SetCheck(0);
	
	m_check_position.SetCheck(0);
	m_check_position.EnableWindow(false);

	hpmfi->get_takt_bar_tick_time_first_note(&measure_first_note, 
		&beat_first_note, &tick_first_note, &time_first_note);

	new_meas = measure_first_note;
	new_bea = beat_first_note;
	new_tic = tick_first_note;
	no_on_update_measure_beat_tick = false;


	m_measure.EnableWindow(false);
	m_beat.EnableWindow(false);
	m_tick.EnableWindow(false);
	m_mbt_check.EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CSysexDlg::OnCancel() 
{
	EndDialog(0);
}

void CSysexDlg::OnOK() 
{
	import_file_selected = (m_select_sysex_file_import_check.GetCheck()==1);	
	import_paste_selected = (m_select_sysex_paste_import_check.GetCheck()==1);	
	export_selected = (m_select_sysex_export_check.GetCheck()==1);	
	is_delete = (m_sysex_delete_check.GetCheck()==1);
	is_note_area = ((m_check_position.GetCheck()==1)||(m_check_read_note_area.GetCheck()==1));
	is_mbt = (m_mbt_check.GetCheck()==1);


	
	if (import_paste_selected && is_note_area && !is_mbt)
	{
		int scr_time = hpmfi->get_time_from_takt_bar_tick(new_meas, new_bea, new_tic);
		if (scr_time < time_first_note)
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_ONLY_NOTEAREA),NULL,MB_OK|MB_TASKMODAL);
			display_measure_beat_tick(measure_first_note,beat_first_note,tick_first_note+5);
			new_meas = measure_first_note;
			new_bea = beat_first_note;
			new_tic = tick_first_note+5;
			return;
		}
	}

	if (is_delete && !export_selected)
	{
		if (IDNO == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_REMOVE_WITHOUT_EXPORT),MB_YESNO,0))
		{
			return;
		}
	}

	if (export_selected) 
	{
		protfile = SelectSysexFile();
		EndDialog((protfile != "") ? 1:0);
	}
	EndDialog(1);
}

void CSysexDlg::OnSelectSysexFileImportCheck() 
{
	m_mbt_check.SetCheck(0);
	m_mbt_check.EnableWindow(false);
	if (m_select_sysex_file_import_check.GetCheck()==1)
	{
		m_select_sysex_export_check.SetCheck(0);
		m_select_sysex_paste_import_check.SetCheck(0);

		m_check_position.EnableWindow(true);

		bool enable = m_check_position.GetCheck()==1;

		if (enable)
		{
			m_measure.EnableWindow(true);
			m_beat.EnableWindow(true);
			m_tick.EnableWindow(true);
			m_mbt_check.EnableWindow(true);
		}
		else
		{
			display_measure_beat_tick_with_blanks();
			m_measure.EnableWindow(false);
			m_beat.EnableWindow(false);
			m_tick.EnableWindow(false);
			m_mbt_check.SetCheck(0);
			if (m_select_sysex_paste_import_check.GetCheck()==1)
			{
				m_mbt_check.EnableWindow(false);
			}
		}
	}
	m_sysex_delete_check.SetCheck(0);
	m_check_read_note_area.SetCheck(0);
	SetDlgItemText(IDC_WITH_MBT,"");
}

void CSysexDlg::OnSelectSysexPasteImportCheck() 
{
	m_mbt_check.SetCheck(0);
	m_mbt_check.EnableWindow(false);
	if (m_select_sysex_paste_import_check.GetCheck()==1)
	{
		m_select_sysex_export_check.SetCheck(0);
		m_select_sysex_file_import_check.SetCheck(0);

		m_check_position.EnableWindow(true);

		bool enable = m_check_position.GetCheck()==1;

		if (enable)
		{
			m_measure.EnableWindow(true);
			m_beat.EnableWindow(true);
			m_tick.EnableWindow(true);
		}
		else
		{
			display_measure_beat_tick_with_blanks();
			m_measure.EnableWindow(false);
			m_beat.EnableWindow(false);
			m_tick.EnableWindow(false);
		}
	}
	m_sysex_delete_check.SetCheck(0);
	m_check_read_note_area.SetCheck(0);
	SetDlgItemText(IDC_WITH_MBT,"");
}

void CSysexDlg::OnSelectSysexExportCheck() 
{
	if (m_select_sysex_export_check.GetCheck()==1)
	{
		m_select_sysex_file_import_check.SetCheck(0);
		m_select_sysex_paste_import_check.SetCheck(0);
		m_check_position.SetCheck(0);
		m_check_position.EnableWindow(false);
		m_mbt_check.SetCheck(0);
		m_mbt_check.EnableWindow(false);

		display_measure_beat_tick_with_blanks();
		m_measure.EnableWindow(false);
		m_beat.EnableWindow(false);
		m_tick.EnableWindow(false);

		if(m_check_read_note_area.GetCheck()==0)
		{
			SetDlgItemText(IDC_WITH_MBT,"");
		}
		else
		{
			SetDlgItemText(IDC_WITH_MBT,GlobalUtilities::get_resource_string(IDS_WITH_MBT));
		}

	}
	else
	{
		SetDlgItemText(IDC_WITH_MBT,"");
	}

}


void CSysexDlg::OnSysexDeleteCheck() 
{
	if ((m_select_sysex_paste_import_check.GetCheck()==1) ||
		(m_select_sysex_file_import_check.GetCheck()==1))
	{
		m_sysex_delete_check.SetCheck(0);
		return;
	}

	if (m_sysex_delete_check.GetCheck()==1)
	{
		m_select_sysex_file_import_check.SetCheck(0);
		m_select_sysex_paste_import_check.SetCheck(0);
		if (m_select_sysex_export_check.GetCheck()==0)
		{
			SetDlgItemText(IDC_WITH_MBT,"");
		}
	}
}


void CSysexDlg::OnCheckPosition() 
{
	if (m_check_position.GetCheck()==1)
	{
		m_mbt_check.EnableWindow(true);
		if (m_mbt_check.GetCheck()==0)
		{
			m_measure.EnableWindow(true);
			m_beat.EnableWindow(true);
			m_tick.EnableWindow(true);
			display_measure_beat_tick(measure_first_note,beat_first_note,tick_first_note+5);
		}
		else
		{
			display_measure_beat_tick_with_blanks();
			m_measure.EnableWindow(false);
			m_beat.EnableWindow(false);
			m_tick.EnableWindow(false);
		}
	}
	else
	{
		m_mbt_check.SetCheck(0);
		m_mbt_check.EnableWindow(false);
		display_measure_beat_tick_with_blanks();
		m_measure.EnableWindow(false);
		m_beat.EnableWindow(false);
		m_tick.EnableWindow(false);
		m_mbt_check.SetCheck(0);
		m_mbt_check.EnableWindow(false);
	}
	if (m_select_sysex_paste_import_check.GetCheck()==1)
	{
		m_mbt_check.SetCheck(0);
		m_mbt_check.EnableWindow(false);
	}
}


void CSysexDlg::OnUpdateMeasure() 
{
	if (no_on_update_measure_beat_tick)
	{
		return;
	}

	int scr_measure = GetDlgItemInt(IDC_MEASURE)-1;
	int scr_beat = GetDlgItemInt(IDC_BEAT)-1;
	int scr_tick = GetDlgItemInt(IDC_TICK);

	int scr_time = hpmfi->get_time_from_takt_bar_tick(scr_measure, scr_beat, scr_tick);

	new_meas = scr_measure;
	new_bea = scr_beat;
	new_tic = scr_tick;

}



void CSysexDlg::OnUpdateBeat() 
{
	OnUpdateMeasure();	
 }

void CSysexDlg::OnUpdateTick() 
{
	OnUpdateMeasure();
}

void CSysexDlg::OnCheckReadNoteArea() 
{
	if ((m_check_read_note_area.GetCheck()==1) && (m_select_sysex_export_check.GetCheck()==1))
	{
		SetDlgItemText(IDC_WITH_MBT,GlobalUtilities::get_resource_string(IDS_WITH_MBT));
	}
	else
	{
		SetDlgItemText(IDC_WITH_MBT,"");
	}
}

void CSysexDlg::OnMbtCheck() 
{
	if (m_mbt_check.GetCheck()==1)
	{
		display_measure_beat_tick_with_blanks();
		m_measure.EnableWindow(false);
		m_beat.EnableWindow(false);
		m_tick.EnableWindow(false);
	}
	else
	{
		m_measure.EnableWindow(true);
		m_beat.EnableWindow(true);
		m_tick.EnableWindow(true);
		display_measure_beat_tick(measure_first_note,beat_first_note+1,tick_first_note);
	}
}

