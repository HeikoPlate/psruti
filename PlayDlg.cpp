// PlayDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "PlayDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CPlayDlg 


CPlayDlg::CPlayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlayDlg)
		// HINWEIS: Der Klassen-Assistent f�gt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CPlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayDlg)
		// HINWEIS: Der Klassen-Assistent f�gt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlayDlg, CDialog)
	//{{AFX_MSG_MAP(CPlayDlg)
		// HINWEIS: Der Klassen-Assistent f�gt hier Zuordnungsmakros f�r Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CPlayDlg 
