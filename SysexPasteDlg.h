#if !defined(AFX_SYSEXPASTEDLG_H__58ED055D_936F_46C3_8478_803EA2A4A63C__INCLUDED_)
#define AFX_SYSEXPASTEDLG_H__58ED055D_936F_46C3_8478_803EA2A4A63C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SysexPasteDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld SysexPasteDlg 

class SysexPasteDlg : public CDialog
{
// Konstruktion
public:
	SysexPasteDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(SysexPasteDlg)
	enum { IDD = IDD_PASTE_SYSEX };
	CEdit	m_paste_edit;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(SysexPasteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(SysexPasteDlg)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString sysex_chain;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SYSEXPASTEDLG_H__58ED055D_936F_46C3_8478_803EA2A4A63C__INCLUDED_
