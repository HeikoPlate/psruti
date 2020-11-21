// Songname.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Songname.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSongname 


CSongname::CSongname(CWnd* pParent /*=NULL*/)
	: CDialog(CSongname::IDD, pParent)
{
	songname = "";
	//{{AFX_DATA_INIT(CSongname)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}

BOOL CSongname::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetWindowText(GlobalUtilities::get_resource_string(IDS_SONGNAME_TITLE));
	SetDlgItemText(IDC_COMPOSER_TEXT,GlobalUtilities::get_resource_string(IDS_COMPOSER));
	SetDlgItemText(IDC_LYRICIST_TEXT,GlobalUtilities::get_resource_string(IDS_LYRICIST));

	SetDlgItemText(IDC_EDIT_NEW_SONGNAME,songname);
	SetDlgItemText(IDC_EDIT_NEW_COMPOSER,composer);
	SetDlgItemText(IDC_EDIT_NEW_LYRICIST,lyricist);
	m_edit_new_songname.SetSel(0,-1); // only possible, if first tabulator

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CSongname::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSongname)
	DDX_Control(pDX, IDC_EDIT_NEW_SONGNAME, m_edit_new_songname);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSongname, CDialog)
	//{{AFX_MSG_MAP(CSongname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CSongname 

void CSongname::OnOK() 
{
	GetDlgItemText(IDC_EDIT_NEW_SONGNAME,songname);
	GetDlgItemText(IDC_EDIT_NEW_COMPOSER,composer);
	GetDlgItemText(IDC_EDIT_NEW_LYRICIST,lyricist);
	EndDialog(1);
}

void CSongname::OnCancel() 
{
	EndDialog(-1);
}

