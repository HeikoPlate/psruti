// CopyrightDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "CopyrightDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CopyrightDlg 

CopyrightDlg::CopyrightDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CopyrightDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CopyrightDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}

void CopyrightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CopyrightDlg)
	DDX_Control(pDX, IDC_EDIT_COPYRIGHT, m_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CopyrightDlg, CDialog)
	//{{AFX_MSG_MAP(CopyrightDlg)
	ON_EN_UPDATE(IDC_EDIT_COPYRIGHT, OnUpdateEditCopyright)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CopyrightDlg 

BOOL CopyrightDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    CString new_copyright = "";
	int i;
	for (i=0; i<copyright.GetLength(); i++)
	{
		new_copyright += copyright[i];
		if (copyright[i] == (char)0x0d) 
		{
			new_copyright += (char)0x0a;
		}
	}
	if (new_copyright.GetLength()>0)
	{
		new_copyright += (char)0x0d;
		new_copyright += (char)0x0a;
	}

	m_text.SetWindowText(new_copyright);
	m_text.SetLimitText(512);
	m_text.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

BOOL CopyrightDlg::PreTranslateMessage(MSG* pMsg)
{
	int tmp1,tmp2;			//Hier wird die Position der aktuellen Markierung gespeichert
	
	switch (pMsg->message)
    {
	case WM_KEYDOWN:					//Taste gedrückt
		switch (pMsg->wParam)			//welches Zeichnen?
		{
		case VK_RETURN:					//der Tabulator
			if (GetFocus() == &m_text)						//ist der Eingabefokus auch auf dem Textfeld?
			{
				m_text.GetWindowText(text_buffer);			//Den Text vom Textfeld kopieren
				m_text.GetSel(tmp1, tmp2);					//Die Position des Cursors ermitteln
				m_text.SetWindowText(text_buffer.Left(tmp2)+
					(char)0x0d+(char)0x0a+
					text_buffer.Right(text_buffer.GetLength()-tmp2));	//Bei der Cursorposition den Tabulator einfügen
				m_text.SetSel(tmp2+2, tmp2+2, false);		//Den Cursor wieder an die richtige Stelle setzen
				return true;								//Raus, Message nicht an den Client weiterleiten
			}
		}
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CopyrightDlg::OnUpdateEditCopyright() 
{
	int tmp1, tmp2, len, no_chars;
	char buffer[1024]; // 81 may be enough
	no_lines = m_text.GetLineCount();
	m_text.GetWindowText(text_buffer);
	no_chars = text_buffer.GetLength();
	len = m_text.GetLine(no_lines-1,buffer,80);
	buffer[len] = 0;
	while (len >= 63)
	{
		m_text.GetSel(tmp1, tmp2);					
		m_text.SetWindowText(text_buffer.Left(tmp2)+
			(char)0x0d+(char)0x0a+
			text_buffer.Right(text_buffer.GetLength()-tmp2));	
		m_text.SetSel(tmp2+2, tmp2+2, false);	
		no_lines = m_text.GetLineCount();
		m_text.GetWindowText(text_buffer);
		no_chars = text_buffer.GetLength();
		len = m_text.GetLine(no_lines-1,buffer,80);
		buffer[len] = 0;
	}

	if ((no_lines > 12)||(no_chars > 512))
	{
		int no = no_lines>12?2:1;
		m_text.GetSel(tmp1, tmp2);
		m_text.SetWindowText(text_buffer.Left(tmp2-no));
		m_text.SetSel(tmp2-no+1, tmp2-no+1, false);	
		no_lines = m_text.GetLineCount();
		len = m_text.GetLine(no_lines-1,buffer,80);
		buffer[len] = 0;
	}
/*
	if (no_lines > 11)
	{
		buffer[len] = 0;
		CString r;
		r.Format("line %i\n %s",no_lines,buffer);
		::MessageBox(AfxGetMainWnd()->m_hWnd,r,"Test",MB_OK|MB_TASKMODAL);
	}
*/
}

void CopyrightDlg::OnOK() 
{
	char ch;
	int i;
	no_lines = 1;

	copyright = "";

	m_text.GetWindowText(text_buffer);

	int text_len = text_buffer.GetLength();
	for (i=0; i<text_len; i++)
	{
		ch = text_buffer[i];
		if (ch !=(char)0x0a)
		{
			copyright += ch;
		}
		else
		{
			no_lines++;
		}
	}
	copyright.TrimRight();

/*
	int no_chars = copyright.GetLength();
	CString r;
	r.Format("no_lines %i \n no_chars %i\n\n"+ copyright,no_lines,no_chars);
	::MessageBox(AfxGetMainWnd()->m_hWnd,r,"Test",MB_OK|MB_TASKMODAL);
*/
	EndDialog(1);
}

void CopyrightDlg::OnCancel() 
{
	// TODO: Zusätzlichen Bereinigungscode hier einfügen
	
	EndDialog(0);
}
