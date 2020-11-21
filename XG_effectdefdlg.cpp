// XG_effectdefdlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "XG_effectdefdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld XG_effectdefdlg 


XG_effectdefdlg::XG_effectdefdlg(CWnd* pParent /*=NULL*/)
	: CDialog(XG_effectdefdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(XG_effectdefdlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void XG_effectdefdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(XG_effectdefdlg)
	DDX_Control(pDX, IDC_KEYBOARDCOMBOBOX, m_keyboardcombobox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(XG_effectdefdlg, CDialog)
	//{{AFX_MSG_MAP(XG_effectdefdlg)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten XG_effectdefdlg 



void XG_effectdefdlg::OnCancel() 
{
	EndDialog(-1);
}

void XG_effectdefdlg::OnOK() 
{
	int nIndex = m_keyboardcombobox.GetCurSel();
	int nCount = m_keyboardcombobox.GetCount();

	m_keyboardcombobox.GetLBText(nIndex, keyboard); 


	EndDialog(1);
}

void XG_effectdefdlg::OnClose() 
{
	EndDialog(-1);
}

BOOL XG_effectdefdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int i;
	CString instrument;
	for (i=0; i<=instruments->GetUpperBound();i++) 
	{
		instrument = instruments->GetAt(i);
		m_keyboardcombobox.InsertString(i,instrument);
	}

	m_keyboardcombobox.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

CString XG_effectdefdlg::get_keyboardmodel()
{
	return keyboard;
}
