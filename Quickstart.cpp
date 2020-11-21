// Quickstart.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Quickstart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Quickstart 


Quickstart::Quickstart(CWnd* pParent /*=NULL*/)
	: CDialog(Quickstart::IDD, pParent)
{
	//{{AFX_DATA_INIT(Quickstart)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	with_quickstart = false;
}


void Quickstart::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Quickstart)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Quickstart, CDialog)
	//{{AFX_MSG_MAP(Quickstart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Quickstart 

void Quickstart::OnOK() 
{
	with_quickstart = !with_quickstart;
	EndDialog(1);
}

BOOL Quickstart::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	SetDlgItemText(IDC_INSERT_REMOVE, 
		with_quickstart?GlobalUtilities::get_resource_string(IDS_REMOVE):
	                    GlobalUtilities::get_resource_string(IDS_INSERT));
						
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void Quickstart::OnCancel() 
{
	EndDialog(-1);
}
