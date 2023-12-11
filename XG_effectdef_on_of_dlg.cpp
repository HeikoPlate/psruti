// XG_effectdef_on_of_dlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "XG_effectdef_on_of_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld XG_effectdef_on_of_dlg 


XG_effectdef_on_of_dlg::XG_effectdef_on_of_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(XG_effectdef_on_of_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(XG_effectdef_on_of_dlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void XG_effectdef_on_of_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(XG_effectdef_on_of_dlg)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(XG_effectdef_on_of_dlg, CDialog)
	//{{AFX_MSG_MAP(XG_effectdef_on_of_dlg)
	ON_BN_CLICKED(IDC_ON, OnOn)
	ON_BN_CLICKED(IDC_OFF, OnOff)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_IGNORE, OnCancel)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten XG_effectdef_on_of_dlg 

void XG_effectdef_on_of_dlg::OnOn() 
{
	EndDialog(1);	
}

void XG_effectdef_on_of_dlg::OnOff() 
{
	EndDialog(0);	
}

void XG_effectdef_on_of_dlg::OnCancel() 
{
	EndDialog(-1);	
}

void XG_effectdef_on_of_dlg::OnClose() 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	
	CDialog::OnClose();
}
