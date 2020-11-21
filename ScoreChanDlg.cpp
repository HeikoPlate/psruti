// ScoreChanDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "ScoreChanDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld ScoreChanDlg 


ScoreChanDlg::ScoreChanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ScoreChanDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ScoreChanDlg)
	//}}AFX_DATA_INIT
}


void ScoreChanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ScoreChanDlg)
	DDX_Control(pDX, IDC_LIST_SCORECHAN_RIGHT, m_scorechan_right);
	DDX_Control(pDX, IDC_LIST_SCORECHAN, m_scorechan_left);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ScoreChanDlg, CDialog)
	//{{AFX_MSG_MAP(ScoreChanDlg)
	ON_LBN_SELCHANGE(IDC_LIST_SCORECHAN, OnSelchangeListScorechan)
	ON_LBN_SELCHANGE(IDC_LIST_SCORECHAN_RIGHT, OnSelchangeListScorechanRight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten ScoreChanDlg 

void ScoreChanDlg::OnOK() 
{
	int gcs;
	
	gcs = m_scorechan_left.GetCurSel( );
	if (gcs == LB_ERR) return;
	if (!allowed_chan_selection[gcs])
	{
		return;
	}
	chan_left = gcs - 1; // chan==0? remove event: channel number;

	gcs = m_scorechan_right.GetCurSel( );
	if (gcs == LB_ERR) return;
	if (!allowed_chan_selection[gcs])
	{
		return;
	}
	chan_right = gcs - 1; // chan==0? remove event: channel number;
	
	EndDialog(1);
}

void ScoreChanDlg::OnCancel() 
{
	EndDialog(0);
}

void ScoreChanDlg::OnSelchangeListScorechan() 
{
	if (hpmfi == NULL)
	{
		return;
	}
	int gcs = m_scorechan_left.GetCurSel( );
	if (gcs == LB_ERR) return;
	if (!allowed_chan_selection[gcs])
	{
		m_scorechan_left.SetCurSel(chan_left+1);
		return;
	}
}

void ScoreChanDlg::OnSelchangeListScorechanRight() 
{
	if (hpmfi == NULL)
	{
		return;
	}
	int gcs = m_scorechan_right.GetCurSel( );
	if (gcs == LB_ERR) return;
	if (!allowed_chan_selection[gcs])
	{
		m_scorechan_right.SetCurSel(chan_right+1);
		return;
	}
}


BOOL ScoreChanDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetWindowText(GlobalUtilities::get_resource_string(IDS_SCORECHAN_TITLE));

	int i;
	
	const CString chanlist[17] =
	{
		"---", "1", "2", "3", "4", "5", "6", "7", "8",
		"9", "10", "11", "12", "13", "14", "15", "16"
	};

	for (i=0; i<17;i++)
	{
		m_scorechan_left.AddString(chanlist[i]);
		m_scorechan_right.AddString(chanlist[i]);
	}

	int score_voice_IDC_list[17] =
	{
		IDC_SCORE_REMOVE,
		IDC_SCORE_PATCH1,
		IDC_SCORE_PATCH2,
		IDC_SCORE_PATCH3,
		IDC_SCORE_PATCH4,
		IDC_SCORE_PATCH5,
		IDC_SCORE_PATCH6,
		IDC_SCORE_PATCH7,
		IDC_SCORE_PATCH8,
		IDC_SCORE_PATCH9,
		IDC_SCORE_PATCH10,
		IDC_SCORE_PATCH11,
		IDC_SCORE_PATCH12,
		IDC_SCORE_PATCH13,
		IDC_SCORE_PATCH14,
		IDC_SCORE_PATCH15,
		IDC_SCORE_PATCH16,
	};

	CString pn[17];

	pn[0] = "";
	allowed_chan_selection[0] = true;	// Remove

	if (hpmfi != NULL)
	{

		for (i=1; i<17; i++)
		{
			int k = i-1;
			if (((hpmfi->mute)[k])||(!(hpmfi->mlv_list)[k].melody))
			{
				pn[i] = "";
				allowed_chan_selection[i] = false;
			}
			else
			{
				pn[i] = (hpmfi->patchname)[k];
				pn[i].TrimLeft();
				allowed_chan_selection[i] = true;
			}
		}
	
		for (i=0; i<17; i++)
		{
			SetDlgItemText(score_voice_IDC_list[i],pn[i]);
		}


		m_scorechan_left.SetCurSel(chan_left+1);
		m_scorechan_right.SetCurSel(chan_right+1);
	}
	else
	{	// Batch
		for (i=0; i<17; i++)
		{
			allowed_chan_selection[i] = true;
		}
		m_scorechan_left.SetCurSel(0);
		m_scorechan_right.SetCurSel(0);
	}
	
	return TRUE;  
}

