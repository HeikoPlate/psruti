// ScoreNotesOptDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "ScoreNotesOptDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld ScoreNotesOptDlg 

const int ScoreNotesOptDlg::max_note_ticks_list[6] = {30,60,120,240,480,960};

ScoreNotesOptDlg::ScoreNotesOptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ScoreNotesOptDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ScoreNotesOptDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT

    max_notes_list_index_selected = -1;
	max_note_ticks = -1;

}


void ScoreNotesOptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ScoreNotesOptDlg)
	DDX_Control(pDX, IDC_MAX_NOTES_LIST, m_max_notes_list);
	DDX_Control(pDX, IDC_SCORE_CHAN_LIST, m_score_chan_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ScoreNotesOptDlg, CDialog)
	//{{AFX_MSG_MAP(ScoreNotesOptDlg)
	ON_CBN_SELCHANGE(IDC_SCORE_CHAN_LIST, OnSelchangeScoreChanList)
	ON_LBN_SELCHANGE(IDC_MAX_NOTES_LIST, OnSelchangeMaxNotesList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten ScoreNotesOptDlg 

BOOL ScoreNotesOptDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int chan;
	int no_score_chans = 0;

	CString r;
	
	for (chan=0; chan<16; chan++)
	{
		if (hpmfi->vh_channel[chan])
		{
			r.Format("%2i",chan+1);
			m_score_chan_list.InsertString(no_score_chans,r);
			score_channel_index_list[no_score_chans] = chan;
			no_score_chans++;
		}
	}
	if (no_score_chans == 0)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_NO_SCORE_CHANNEL_FOUND),NULL,MB_OK|MB_TASKMODAL);
		OnCancel();
	}
	else
	{
		m_score_chan_list.SetCurSel(0);
		act_score_channel = score_channel_index_list[0];
	}

	m_max_notes_list.InsertString(0,"1/64");
	m_max_notes_list.InsertString(1,"1/32");
	m_max_notes_list.InsertString(2,"1/16");
	m_max_notes_list.InsertString(3,"1/8");
	m_max_notes_list.InsertString(4,"1/4");
	m_max_notes_list.InsertString(5,"1/2");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void ScoreNotesOptDlg::OnCancel() 
{
	EndDialog(-1);
}

void ScoreNotesOptDlg::OnOK() 
{
	if (max_note_ticks == -1)
	{
		return;
	}

	EndDialog(0);
}

void ScoreNotesOptDlg::OnSelchangeScoreChanList() 
{
	int nIndex = m_score_chan_list.GetCurSel();
	act_score_channel = score_channel_index_list[nIndex];
/*
	CString r;
	r.Format("selected score chan %i",act_score_channel+1);
	MessageBox(r);
*/  
}

void ScoreNotesOptDlg::OnSelchangeMaxNotesList() 
{
	max_notes_list_index_selected = m_max_notes_list.GetCurSel();
	max_note_ticks = max_note_ticks_list[max_notes_list_index_selected];
/*
	CString r;
	r.Format("index %i, ticks %i",max_notes_list_index_selected,max_note_ticks);
	MessageBox(r);
*/
}

