#if !defined(AFX_COPYRIGHTDLG_H__4A0C3EB2_DDF4_442E_9C11_3CCA4B7AD3D1__INCLUDED_)
#define AFX_COPYRIGHTDLG_H__4A0C3EB2_DDF4_442E_9C11_3CCA4B7AD3D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CopyrightDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CopyrightDlg 

class CopyrightDlg : public CDialog
{
// Konstruktion
public:
	CopyrightDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CopyrightDlg)
	enum { IDD = IDD_COPYRIGHT };
	CEdit	m_text;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CopyrightDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung

public:
	HPMF_Interface *hpmfi;
	CString copyright;

private:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CString text_buffer;
	int right_margin, down_margin;
	CString text;
	int no_lines;

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CopyrightDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateEditCopyright();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_COPYRIGHTDLG_H__4A0C3EB2_DDF4_442E_9C11_3CCA4B7AD3D1__INCLUDED_
