#if !defined(AFX_XG_EFFECTDEFDLG_H__EF2B2B37_F1AA_476E_BD13_27F395289B1E__INCLUDED_)
#define AFX_XG_EFFECTDEFDLG_H__EF2B2B37_F1AA_476E_BD13_27F395289B1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XG_effectdefdlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld XG_effectdefdlg 

class XG_effectdefdlg : public CDialog
{
// Konstruktion
public:
	XG_effectdefdlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(XG_effectdefdlg)
	enum { IDD = IDD_EFFECTDEFDLG };
	CComboBox	m_keyboardcombobox;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(XG_effectdefdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(XG_effectdefdlg)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString keyboard;

public:
	CArray <CString,CString> *instruments;
	CString get_keyboardmodel();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_XG_EFFECTDEFDLG_H__EF2B2B37_F1AA_476E_BD13_27F395289B1E__INCLUDED_
