// MasterVolume.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "MasterVolume.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld MasterVolume 


MasterVolume::MasterVolume(CWnd* pParent /*=NULL*/)
	: CDialog(MasterVolume::IDD, pParent)
{
	//{{AFX_DATA_INIT(MasterVolume)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	master_volume = 16273;
}


void MasterVolume::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MasterVolume)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MasterVolume, CDialog)
	//{{AFX_MSG_MAP(MasterVolume)
	ON_EN_CHANGE(IDC_EDIT_MASTER_VOLUME, OnChangeEditMasterVolume)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten MasterVolume 

void MasterVolume::OnOK() 
{
	EndDialog(1); // 0: cancelled, 1: OK
}

void MasterVolume::OnCancel() 
{
	master_volume = 127;
	EndDialog(0); // 0: cancelled, 1: OK
}


BOOL MasterVolume::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetDlgItemInt(IDC_EDIT_MASTER_VOLUME,init_master_volume,FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void MasterVolume::OnChangeEditMasterVolume() 
{
	int vol = GetDlgItemInt(IDC_EDIT_MASTER_VOLUME);
	master_volume = vol > 127?127:vol;
	if ((vol != master_volume) || (vol == 0)) SetDlgItemInt(IDC_EDIT_MASTER_VOLUME,master_volume,FALSE);
}


