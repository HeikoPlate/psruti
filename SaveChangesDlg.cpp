// SaveChangesDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "SaveChangesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld SaveChangesDlg 


SaveChangesDlg::SaveChangesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SaveChangesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SaveChangesDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void SaveChangesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SaveChangesDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SaveChangesDlg, CDialog)
	//{{AFX_MSG_MAP(SaveChangesDlg)
	ON_BN_CLICKED(IDC_SAVE_NO, OnSaveNo)
	ON_BN_CLICKED(IDOK, OnSaveYes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten SaveChangesDlg 

void SaveChangesDlg::OnSaveYes() 
{
	EndDialog(1);	
}

void SaveChangesDlg::OnSaveNo() 
{
	EndDialog(0);	
}

void SaveChangesDlg::OnCancel() 
{
	EndDialog(-1);	
}
