// Lengthen_Notes.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Lengthen_Notes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CLengthen_Notes 


CLengthen_Notes::CLengthen_Notes(CWnd* pParent /*=NULL*/)
	: CDialog(CLengthen_Notes::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLengthen_Notes)
	//}}AFX_DATA_INIT
	list_index_selected = -1;
	progressctrl_upper = 100;
	tempo_checked = true;
}


void CLengthen_Notes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLengthen_Notes)
	DDX_Control(pDX, IDOK, m_run);
	DDX_Control(pDX, IDC_CANCEL, m_cancel);
	DDX_Control(pDX, IDC_TEMPO_CHECK, m_tempo_check);
	DDX_Control(pDX, IDC_PERCENT_LIST, m_percent_list);
	DDX_Control(pDX, IDC_PROGRESSCTRL, m_progressctrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLengthen_Notes, CDialog)
	//{{AFX_MSG_MAP(CLengthen_Notes)
	ON_LBN_SELCHANGE(IDC_PERCENT_LIST, OnSelchangePercentList)
	ON_WM_CLOSE()
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CLengthen_Notes 

BOOL CLengthen_Notes::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_percent_list.InsertString(0,"20%");
	m_percent_list.InsertString(1,"25%");
	m_percent_list.InsertString(2,"33%");
	m_percent_list.InsertString(3,"50%");
	m_percent_list.InsertString(4,"66%");
	m_percent_list.InsertString(5,"75%");
	m_percent_list.InsertString(6,"133%");
	m_percent_list.InsertString(7,"150%");
	m_percent_list.InsertString(8,"200%");
	m_percent_list.InsertString(9,"300%");
	m_percent_list.InsertString(10,"400%");

	m_tempo_check.SetCheck(1);

	last_id = hpmfi->get_last_id();

	m_run.EnableWindow(false);
	run_done = false;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CLengthen_Notes::OnCancel() 
{
	EndDialog(0);
}


void CLengthen_Notes::OnClose() 
{
	OnCancel();
}


void CLengthen_Notes::OnSelchangePercentList() 
{
	list_index_selected = m_percent_list.GetCurSel();
	m_run.EnableWindow(true);
}

void CLengthen_Notes::OnOK() 
{	// realizes the Note Lengthen function

	int ticks_of_first_measure = 4*(hpmfi->ppqn); // xg_convert already done

	tempo_checked = m_tempo_check.GetCheck()==1?true:false;;

	const double percent_factor_list[11] = {0.2, 0.25, 1.0/3.0, 0.5, 2.0/3.0, 0.75, 4.0/3.0, 1.5, 2.0, 3.0, 4.0};
	const int percent_list[11] = {20, 25, 33, 50, 66, 75, 133, 150, 200, 300, 400};

	m_cancel.EnableWindow(false);
	m_percent_list.EnableWindow(false);
	m_tempo_check.EnableWindow(false);
	m_run.EnableWindow(false);

	double factor = percent_factor_list[list_index_selected];
	int percent = percent_list[list_index_selected];
	double maxtempo;

	int id, chan, time, type;
	int scratch1, scratch2;

	int raster = last_id/progressctrl_upper;
	

	m_progressctrl.SetRange(0, progressctrl_upper);
	m_progressctrl.SetPos(0);
	m_progressctrl.SetStep(progressctrl_upper);

	if (tempo_checked)
	{
		maxtempo = hpmfi->get_max_tempo();
		hpmfi->eval_tempo(maxtempo*factor);
		hpmfi->set_max_tempo(maxtempo*factor);
	}

	HP_MIDIFILE_MODULE* mf1 = HP_Init();
	HP_ChangePPQN(mf1,hpmfi->ppqn);	// use original ppqn
	
	HP_SetFirst(hpmfi->mf,HP_LAST);	// insert one after another
	HP_SetFirst(mf1,HP_LAST);	    // insert one after another
	HP_Deselect(hpmfi->mf);

	HP_Rewind(hpmfi->mf);
	
	while (HP_ReadEvent(hpmfi->mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{

		if (time < ticks_of_first_measure)
		{
			HP_Select(hpmfi->mf,id);
			HP_Copy(hpmfi->mf);
			HP_Paste(mf1,time, HP_NO_DELETE,0);
			HP_Deselect(hpmfi->mf,id);
		}
		else
		{
			HP_Select(hpmfi->mf,id);
			HP_Copy(hpmfi->mf);

			int new_time = int(ticks_of_first_measure+(time-ticks_of_first_measure)*factor);

			HP_Paste(mf1,new_time, HP_NO_DELETE,0);
			HP_Deselect(hpmfi->mf,id);
		}

		if (raster != 0)
		{
			if (id % raster == 0)
			{
				m_progressctrl.OffsetPos(1);
			}
		}
	}

	HP_Deselect(hpmfi->mf);
	HP_ChangeNoteLength(mf1, HP_ALL_EVENTS, HP_ALL_CHAN, HP_ALL_NOTES,percent,HP_PERCENT); 
	HP_Free(hpmfi->mf);			
	hpmfi->mf = mf1;
	mf1= NULL;


	hpmfi->init_hpmfiledata();
	hpmfi->eval_xg_convert(&scratch1, &scratch2);

	// not necessary:
	m_cancel.EnableWindow(true);
	m_percent_list.EnableWindow(true);
	m_tempo_check.EnableWindow(true);
	m_run.EnableWindow(true);
	run_done = true; // no need
	EndDialog(1);
}

