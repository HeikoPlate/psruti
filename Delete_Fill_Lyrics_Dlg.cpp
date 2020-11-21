// Delete_Fill_Lyrics_Dlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Delete_Fill_Lyrics_Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDelete_Fill_Lyrics_Dlg 


CDelete_Fill_Lyrics_Dlg::CDelete_Fill_Lyrics_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDelete_Fill_Lyrics_Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDelete_Fill_Lyrics_Dlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CDelete_Fill_Lyrics_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDelete_Fill_Lyrics_Dlg)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDelete_Fill_Lyrics_Dlg, CDialog)
	//{{AFX_MSG_MAP(CDelete_Fill_Lyrics_Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDelete_Fill_Lyrics_Dlg 

void CDelete_Fill_Lyrics_Dlg::OnOK() 
{
	GetDlgItemText(IDC_FL1,taktlyric);
	GetDlgItemText(IDC_FL2,beatlyric);
	GetDlgItemText(IDC_FL3,endlyric);

	int len_tl = taktlyric.GetLength();
	int len_bl = beatlyric.GetLength();
	int len_el = endlyric.GetLength();

	if ((taktlyric[0] != '\"') || (taktlyric[len_tl-1] != '\"'))
	{
		MessageBox("Error Fill-Lyric 1");
		return;
	}
	if ((beatlyric[0] != '\"') || (beatlyric[len_bl-1] != '\"'))
	{
		MessageBox("Error Fill-Lyric 2");
		return;
	}
	if ((endlyric[0] != '\"') || (endlyric[len_el-1] != '\"'))
	{
		MessageBox("Error Fill-Lyric 3");
		return;
	}

	EndDialog(0);
}

void CDelete_Fill_Lyrics_Dlg::OnCancel() 
{
	EndDialog(-1);
}

BOOL CDelete_Fill_Lyrics_Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_FL1,taktlyric);
	SetDlgItemText(IDC_FL2,beatlyric);
	SetDlgItemText(IDC_FL3,endlyric);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
