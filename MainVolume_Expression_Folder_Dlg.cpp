// MainVolume_Expression_Folder_Dlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "MainVolume_Expression_Folder_Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld MainVolume_Expression_Folder_Dlg 


MainVolume_Expression_Folder_Dlg::MainVolume_Expression_Folder_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(MainVolume_Expression_Folder_Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(MainVolume_Expression_Folder_Dlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	mainvolume_to_expression_val = true;
}


void MainVolume_Expression_Folder_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MainVolume_Expression_Folder_Dlg)
	DDX_Control(pDX, IDC_MAINVOLUME_TO_EXPRESSION_CHECK, m_mainvolume_to_expression_check);
	DDX_Control(pDX, IDC_EXPRESSION_TO_MAINVOLUME_CHECK, m_expression_to_mainvolume_check);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MainVolume_Expression_Folder_Dlg, CDialog)
	//{{AFX_MSG_MAP(MainVolume_Expression_Folder_Dlg)
	ON_BN_CLICKED(IDC_EXPRESSION_TO_MAINVOLUME_CHECK, OnExpressionToMainvolumeCheck)
	ON_BN_CLICKED(IDC_MAINVOLUME_TO_EXPRESSION_CHECK, OnMainvolumeToExpressionCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten MainVolume_Expression_Folder_Dlg 

bool MainVolume_Expression_Folder_Dlg::get_mainvolume_to_expression()
{
	return mainvolume_to_expression_val;
}

void MainVolume_Expression_Folder_Dlg::OnCancel() 
{
	EndDialog(-1);
}

void MainVolume_Expression_Folder_Dlg::OnOK() 
{
	EndDialog(1);
}

BOOL MainVolume_Expression_Folder_Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_mainvolume_to_expression_check.SetCheck(1);
	m_expression_to_mainvolume_check.SetCheck(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void MainVolume_Expression_Folder_Dlg::OnExpressionToMainvolumeCheck() 
{
	if (m_expression_to_mainvolume_check.GetCheck()==1)
	{
		mainvolume_to_expression_val = false;
		m_mainvolume_to_expression_check.SetCheck(0);
	}
	else
	{
		mainvolume_to_expression_val = true;
		m_mainvolume_to_expression_check.SetCheck(1);
	}
}

void MainVolume_Expression_Folder_Dlg::OnMainvolumeToExpressionCheck() 
{
	if (m_mainvolume_to_expression_check.GetCheck()==1)
	{
		mainvolume_to_expression_val = true;
		m_expression_to_mainvolume_check.SetCheck(0);
	}
	else
	{
		mainvolume_to_expression_val = false;
		m_expression_to_mainvolume_check.SetCheck(1);
	}
}
