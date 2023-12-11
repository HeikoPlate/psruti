// SysexPasteDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "SysexPasteDlg.h"
#include "GlobalUtilities.h"
#include "afx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld SysexPasteDlg 


SysexPasteDlg::SysexPasteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SysexPasteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SysexPasteDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT

	sysex_chain = "";
}


void SysexPasteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SysexPasteDlg)
	DDX_Control(pDX, IDC_PASTE_EDIT, m_paste_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SysexPasteDlg, CDialog)
	//{{AFX_MSG_MAP(SysexPasteDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten SysexPasteDlg 

void SysexPasteDlg::OnCancel() 
{
	sysex_chain = "";
	EndDialog(0);	
}

void SysexPasteDlg::OnOK() 
{
	int i;
	char ch;
	CString orig_text, prepared_text, r;
	sysex_chain = "";
	m_paste_edit.GetWindowText(orig_text);
	orig_text.MakeUpper();
	prepared_text = "";

	for (i=0; i<orig_text.GetLength(); i++)
	{
		ch = orig_text[i];

		if (ch!=' ')
		{
			prepared_text += ch;
		}
	}

	i = 0;

	while (true)
	{
		i++; 
		int f7_index = prepared_text.Find("F7");
		int f0_index = prepared_text.Find("F0");
		if (f0_index == -1)
		{
			break;
		}
		if ((f7_index == -1)||(f7_index<f0_index))
		{
			r.Format(GlobalUtilities::get_resource_string(IDS_BAD_SYSEX),i);
			::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
			sysex_chain = "";
			break;
		}

		for (i=f0_index; i<f7_index+2; i++)
		{
			ch = prepared_text[i];
			if ((ch<'0')||((ch>'9')&&(ch<'A'))||(ch>'F'))
			{
				r.Format(GlobalUtilities::get_resource_string(IDS_BAD_SYSEX),i);
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
				sysex_chain = "";
				break;
			}
			sysex_chain += ch;
		}
//		MessageBox(sysex_chain);
		prepared_text = prepared_text.Right(prepared_text.GetLength()-(f7_index+2));
//		MessageBox(prepared_text);
	
	}

//	MessageBox(sysex_chain);

	EndDialog(1);	
}

BOOL SysexPasteDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_paste_edit.SetSel(0, -1);
	m_paste_edit.Paste();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
