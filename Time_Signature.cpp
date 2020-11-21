// Time_Signature.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Time_Signature.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Time_Signature 

const CString Time_Signature::numlist[NO_NUM] = {"1","2","3","4","5","6","7","8"};
const int Time_Signature::int_numlist[NO_NUM] = { 1,  2,  3,  4,  5,  6,  7,  8 };
const CString Time_Signature::denumlist[NO_DENUM] = {"1","2","4","8","16","32"};
const int Time_Signature::int_denumlist[NO_DENUM] = { 1,  2,  4,  8,  16,  32 };

Time_Signature::Time_Signature(CWnd* pParent /*=NULL*/)
	: CDialog(Time_Signature::IDD, pParent)
{
	//{{AFX_DATA_INIT(Time_Signature)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT

	num_selected = -1;
	denum_selected = -1;
	num = -1;
	denum = -1;
	export_area_selected = false;
	import_area_selected = false;

	time_signature_found = false;
	no_time_signatures = 0;
    source_changed = false;
}


void Time_Signature::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Time_Signature)
	DDX_Control(pDX, IDC_SWITCH, m_switch);
	DDX_Control(pDX, IDC_EXPORT_NOTE_AREA, m_export_note_area);
	DDX_Control(pDX, IDC_IMPORT_NOTE_AREA, m_import_note_area);
	DDX_Control(pDX, IDC_RUN, m_run_before_notes);
	DDX_Control(pDX, IDC_DENUM, m_denum);
	DDX_Control(pDX, IDC_NUM, m_num);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Time_Signature, CDialog)
	//{{AFX_MSG_MAP(Time_Signature)
	ON_LBN_SELCHANGE(IDC_NUM, OnSelchangeNum)
	ON_LBN_SELCHANGE(IDC_DENUM, OnSelchangeDenum)
	ON_BN_CLICKED(IDC_RUN, OnRunBeforeNotes)
	ON_BN_CLICKED(IDC_FINISH, OnFinish)
	ON_BN_CLICKED(IDC_EXPORT_NOTE_AREA, OnExportNoteArea)
	ON_BN_CLICKED(IDC_IMPORT_NOTE_AREA, OnImportNoteArea)
	ON_BN_CLICKED(IDC_SWITCH, OnSwitch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Time_Signature 

BOOL Time_Signature::OnInitDialog() 
{
	int i;
    CString r;
	int scr1, scr2;

	CDialog::OnInitDialog();

	hIcon_switch = AfxGetApp()->LoadIcon(IDI_ICON20);
	m_switch.SetIcon(hIcon_switch);


	SetCursor(hCursorWait);

	// disable note area buttons
	m_export_note_area.EnableWindow(false);
	m_import_note_area.EnableWindow(false);

	// enable before notes buttons
	m_num.EnableWindow(true);
	m_denum.EnableWindow(true);
	m_run_before_notes.EnableWindow(true);

	before_notes_selected = true;
	note_area_selected = false;;

	for (i=0; i<NO_NUM; i++)
	{
		m_num.InsertString(i,numlist[i]);
	}

	for (i=0; i<NO_DENUM; i++)
	{
		m_denum.InsertString(i,denumlist[i]);
	}

	hpmfi->eval_xg_convert(&scr1,&scr2);
	
	HP_Rewind(hpmfi->mf); 
	while (HP_ReadEvent(hpmfi->mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		// skip 4/4 of initial measure
		if (time < 4*hpmfi->ppqn) continue;
		if (type==HP_TIME_SIGNATURE)
		{
			if (time==4*hpmfi->ppqn)
			{
				no_time_signatures++;
				HP_ReadTimeSignature(hpmfi->mf,id,&time,&num,&denum,&metronome_click,&n32);
				char str[3];
				sprintf(str,"%i",num);
				num_selected = m_num.SelectString(-1,str);
				sprintf(str,"%i",denum);
				denum_selected = m_denum.SelectString(-1,str);
				time_signature_found = true;
				if((num_selected!=LB_ERR)&&(denum_selected!=LB_ERR))
				{
					r.Format("%i/%i", num, denum);
					SetDlgItemText(IDC_TIME,r);
				}
				else
				{
					SetDlgItemText(IDC_TIME,"");
				}
			}
			else
			{
				no_time_signatures++;
			}
		}
	}

	if (!time_signature_found)
	{
		num_selected = m_num.SelectString(-1,"4");
		denum_selected = m_denum.SelectString(-1,"4");
		SetDlgItemText(IDC_TIME,"4/4");
		no_time_signatures++;
	}

	SetCursor(hCursorOld);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void Time_Signature::OnSelchangeNum() 
{
	num_selected = m_num.GetCurSel();
}

void Time_Signature::OnSelchangeDenum() 
{
	denum_selected = m_denum.GetCurSel();
}

void Time_Signature::OnRunBeforeNotes() 
{
	if (no_time_signatures > 1)
	{
		CString r;
		r.Format(GlobalUtilities::get_resource_string(IDS_MORE_TIME_SIGNATURES),no_time_signatures);
		MessageBox(r);
	}

	HP_SetFirst(hpmfi->mf);

	if (time_signature_found)
	{
		HP_Rewind(hpmfi->mf); 
		while (HP_ReadEvent(hpmfi->mf,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (time < 4*hpmfi->ppqn) continue;
			if (time > 4*hpmfi->ppqn) break;
			if (type==HP_TIME_SIGNATURE)
			{
				HP_ReadTimeSignature(hpmfi->mf,id,&time,&num,&denum,&metronome_click,&n32);
				if ((num==int_numlist[num_selected])&&(denum==int_denumlist[denum_selected]))
				{
					break;
				}
				HP_DeleteEvent(hpmfi->mf,id);
				HP_SetFirst(hpmfi->mf,HP_FIRST);
				HP_InsertTimeSignature(hpmfi->mf,time,int_numlist[num_selected],int_denumlist[denum_selected],0x18, 0x08);
				CString r;
				r.Format("%s/%s", numlist[num_selected],denumlist[denum_selected]);
				SetDlgItemText(IDC_TIME,r);
				source_changed = true;
				Invalidate();   
				UpdateWindow();
			}
		}
	}
	else
	{
		if ((int_numlist[num_selected]!=4)||(int_denumlist[denum_selected]!=4))
		{
			HP_InsertTimeSignature(hpmfi->mf,4*hpmfi->ppqn,int_numlist[num_selected],int_denumlist[denum_selected]);
			CString r;
			r.Format("%s/%s", numlist[num_selected],denumlist[denum_selected]);
			SetDlgItemText(IDC_TIME,r);
			time_signature_found = true;
			source_changed = true;
			Invalidate();   
			UpdateWindow();
		}
	}
	if (source_changed)
	{
		int scr1, scr2;
		hpmfi->eval_xg_convert(&scr1, &scr2);
	}
}

void Time_Signature::OnFinish() 
{
	EndDialog(source_changed?1:0);
}

void Time_Signature::OnExportNoteArea() 
{

	export_area_selected = true;
	import_area_selected = false;

	CString timefile = select_prot_file(true);
	if (timefile == "") return;

	p_inifile->set_protfile(timefile);
	hpmfi->eval_time_export_note_area(timefile);	

}

void Time_Signature::OnImportNoteArea() 
{
	export_area_selected = false;
	import_area_selected = true;
	
	CString timefile = select_prot_file(false);
	if (timefile == "") return;

	p_inifile->set_protfile(timefile);
	hpmfi->eval_time_import_note_area(timefile);	

}

CString Time_Signature::select_prot_file(bool export)
{

	int i;
	CString timefile;

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

	if (return_value == IDOK)
	{
		timefile = openfile_dlg.m_ofn.lpstrFile;
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

	if (export)
	{
		// Try timefile

		CFile mf_newf;
		CFileException e;

		if (mf_newf.Open(timefile, CFile::modeRead,&e))
		{
			int length = mf_newf.GetLength();
			mf_newf.Close();

			if (length>0)
			{
				CString r;
				r.Format(GlobalUtilities::get_resource_string(IDS_UseExistingFile)+"\"%s\" ?",timefile); 
				if (IDYES != AfxMessageBox(r,MB_YESNO,0))
				{
					return "";
				}
			}
		}
	}

	return timefile;
}


void Time_Signature::OnSwitch() 
{
	if (before_notes_selected)
	{
		// enable note area buttons
		m_export_note_area.EnableWindow(true);
		m_import_note_area.EnableWindow(true);

		// disable before notes buttons
		m_num.EnableWindow(false);
		m_denum.EnableWindow(false);
		m_run_before_notes.EnableWindow(false);

		before_notes_selected = false;
		note_area_selected = true;
	}
	else
	{
		// disable note area buttons
		m_export_note_area.EnableWindow(false);
		m_import_note_area.EnableWindow(false);

		// enable before notes buttons
		m_num.EnableWindow(true);
		m_denum.EnableWindow(true);
		m_run_before_notes.EnableWindow(true);

		before_notes_selected = true;
		note_area_selected = false;
	}

	export_area_selected = false;
	import_area_selected = false;
}
