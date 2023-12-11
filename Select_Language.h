#if !defined(AFX_SELECT_LANGUAGE_H__5E9DD890_7CD8_4486_A46A_0613DF64F64C__INCLUDED_)
#define AFX_SELECT_LANGUAGE_H__5E9DD890_7CD8_4486_A46A_0613DF64F64C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Select_Language.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Select_Language 

class Select_Language : public CDialog
{
// Konstruktion
public:
	Select_Language(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(Select_Language)
	enum { IDD = IDD_SELECT_LANGUAGE };
	CButton	m_select_german;
	CButton	m_select_english;
	//}}AFX_DATA

	CString initial_language;
	CString language;


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Select_Language)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Select_Language)
	afx_msg void OnSelectEnglish();
	afx_msg void OnSelectGerman();
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SELECT_LANGUAGE_H__5E9DD890_7CD8_4486_A46A_0613DF64F64C__INCLUDED_
