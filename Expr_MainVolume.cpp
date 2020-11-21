// Expr_MainVolume.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Expr_MainVolume.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Expr_MainVolume 


Expr_MainVolume::Expr_MainVolume(CWnd* pParent /*=NULL*/)
	: CDialog(Expr_MainVolume::IDD, pParent)
{
	//{{AFX_DATA_INIT(Expr_MainVolume)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void Expr_MainVolume::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Expr_MainVolume)
	DDX_Control(pDX, IDC_CHANGE_TO_MVOLUME, m_to_mvolume);
	DDX_Control(pDX, IDC_CHANGE_TO_EXPRESSION, m_to_expression);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Expr_MainVolume, CDialog)
	//{{AFX_MSG_MAP(Expr_MainVolume)
	ON_BN_CLICKED(IDC_CHANGE_TO_MVOLUME, OnChangeToMvolume)
	ON_BN_CLICKED(IDC_CHANGE_TO_EXPRESSION, OnChangeToExpression)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Expr_MainVolume 

void Expr_MainVolume::OnCancel() 
{
	EndDialog(0); // 0: cancelled, 1: OK
}

void Expr_MainVolume::OnOK() 
{
	is_change_to_mvolume = (m_to_mvolume.GetCheck()==1);

	EndDialog(1); // 0: cancelled, 1: OK
}

bool Expr_MainVolume::change_to_mvolume()
{
	return is_change_to_mvolume;
}

BOOL Expr_MainVolume::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_to_mvolume.SetCheck(0);
	m_to_expression.SetCheck(1);
	is_change_to_mvolume = true;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void Expr_MainVolume::OnChangeToMvolume() 
{
	int check = m_to_mvolume.GetCheck();
	m_to_expression.SetCheck(check==1?0:1);
}

void Expr_MainVolume::OnChangeToExpression() 
{
	int check = m_to_expression.GetCheck();
	m_to_mvolume.SetCheck(check==1?0:1);
}
