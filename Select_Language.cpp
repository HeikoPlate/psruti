// Select_Language.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Select_Language.h"
#include "psrutidlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Select_Language 


Select_Language::Select_Language(CWnd* pParent /*=NULL*/)
	: CDialog(Select_Language::IDD, pParent)
{
	//{{AFX_DATA_INIT(Select_Language)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void Select_Language::DoDataExchange(CDataExchange* pDX)
{

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Select_Language)
	DDX_Control(pDX, IDC_SELECT_GERMAN, m_select_german);
	DDX_Control(pDX, IDC_SELECT_ENGLISH, m_select_english);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Select_Language, CDialog)
	//{{AFX_MSG_MAP(Select_Language)
	ON_BN_CLICKED(IDC_SELECT_ENGLISH, OnSelectEnglish)
	ON_BN_CLICKED(IDC_SELECT_GERMAN, OnSelectGerman)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Select_Language 

void Select_Language::OnSelectEnglish() 
{
	if (m_select_english.GetCheck()==1)
	{
		m_select_german.SetCheck(0);
		language = "ENGLISH";
	}
	else
	{
		m_select_german.SetCheck(1);
		language = "GERMAN";
	}
}

void Select_Language::OnSelectGerman() 
{
	if (m_select_german.GetCheck()==1)
	{
		m_select_english.SetCheck(0);
		language = "GERMAN";
	}
	else
	{
		m_select_english.SetCheck(1);
		language = "ENGLISH";
	}
}

void Select_Language::OnCancel() 
{
	EndDialog(0);
}

void Select_Language::OnOK() 
{
	EndDialog(1);
}

BOOL Select_Language::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// initialize the other language
	if (initial_language == "ENGLISH")
	{
		m_select_german.SetCheck(1);
		m_select_english.SetCheck(0);
		language = "GERMAN";
	}
	else
	{
		m_select_german.SetCheck(0);
		m_select_english.SetCheck(1);
		language = "ENGLISH";
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
