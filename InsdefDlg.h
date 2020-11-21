#if !defined(AFX_INSDEFDLG_H__FEEB364E_5743_4744_95FA_E734C156E03D__INCLUDED_)
#define AFX_INSDEFDLG_H__FEEB364E_5743_4744_95FA_E734C156E03D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsdefDlg.h : Header-Datei
//

#include "HP_midifile.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld InsdefDlg 

class InsdefDlg : public CDialog
{
// Konstruktion
public:
	InsdefDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(InsdefDlg)
	enum { IDD = IDD_INSDEFDLG };
	CComboBox	m_insdefcombobox;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(InsdefDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
public:

	HPMF_Interface * hpmfi;
	CString insdef;
	HCURSOR hCursorOld;
	HCURSOR hCursorWait;
	HP_MIDIFILE_MODULE* local_mf;

private:

	HP_CWDEF* def_list;


protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(InsdefDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_INSDEFDLG_H__FEEB364E_5743_4744_95FA_E734C156E03D__INCLUDED_
