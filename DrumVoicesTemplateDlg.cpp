// DrumVoicesTemplateDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "DrumVoicesTemplateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DrumVoicesTemplateDlg 


DrumVoicesTemplateDlg::DrumVoicesTemplateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(DrumVoicesTemplateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DrumVoicesTemplateDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void DrumVoicesTemplateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DrumVoicesTemplateDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DrumVoicesTemplateDlg, CDialog)
	//{{AFX_MSG_MAP(DrumVoicesTemplateDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten DrumVoicesTemplateDlg 

void DrumVoicesTemplateDlg::OnCancel() 
{
	// TODO: Zusätzlichen Bereinigungscode hier einfügen
	
	CDialog::OnCancel();
}
