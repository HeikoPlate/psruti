// DrumsDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "DrumsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDrumsDlg 


CDrumsDlg::CDrumsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrumsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDrumsDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CDrumsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrumsDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDrumsDlg, CDialog)
	//{{AFX_MSG_MAP(CDrumsDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDrumsDlg 
