// InsDefOnOffDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "InsDefOnOffDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld InsDefOnOffDlg 


InsDefOnOffDlg::InsDefOnOffDlg(CWnd* pParent /*=NULL*/)
	: CDialog(InsDefOnOffDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(InsDefOnOffDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void InsDefOnOffDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InsDefOnOffDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(InsDefOnOffDlg, CDialog)
	//{{AFX_MSG_MAP(InsDefOnOffDlg)
	ON_BN_CLICKED(IDOK, OnInsdefOn)
	ON_BN_CLICKED(IDC_INSDEF_OFF, OnInsdefOff)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten InsDefOnOffDlg 

void InsDefOnOffDlg::OnInsdefOn() 
{
	EndDialog(1);	
}

void InsDefOnOffDlg::OnInsdefOff() 
{
	EndDialog(0);	
}

void InsDefOnOffDlg::OnCancel() 
{
	EndDialog(-1);	
}
