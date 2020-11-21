// Master_Volume_Folder_Dlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Master_Volume_Folder_Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Master_Volume_Folder_Dlg 


Master_Volume_Folder_Dlg::Master_Volume_Folder_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Master_Volume_Folder_Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Master_Volume_Folder_Dlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	value = 127;
}


void Master_Volume_Folder_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Master_Volume_Folder_Dlg)
	DDX_Control(pDX, IDC_MASTER_VOLUM_EDIT, m_master_volume_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Master_Volume_Folder_Dlg, CDialog)
	//{{AFX_MSG_MAP(Master_Volume_Folder_Dlg)
	ON_EN_CHANGE(IDC_MASTER_VOLUM_EDIT, OnChangeMasterVolumEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int Master_Volume_Folder_Dlg::get_value()
{
	return value;
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Master_Volume_Folder_Dlg 

void Master_Volume_Folder_Dlg::OnCancel() 
{
	EndDialog(-1);
}

void Master_Volume_Folder_Dlg::OnOK() 
{
	EndDialog(1);
}

void Master_Volume_Folder_Dlg::OnChangeMasterVolumEdit() 
{
	value = GetDlgItemInt(IDC_MASTER_VOLUM_EDIT);
	if (value>127)
	{
		SetDlgItemInt(IDC_MASTER_VOLUM_EDIT,127,FALSE);
	}
}

BOOL Master_Volume_Folder_Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetDlgItemInt(IDC_MASTER_VOLUM_EDIT,value,FALSE);
	m_master_volume_edit.SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
