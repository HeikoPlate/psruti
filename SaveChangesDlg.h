#if !defined(AFX_SAVECHANGESDLG_H__C7E59CC8_830E_4BB1_95D0_22FAA75CA864__INCLUDED_)
#define AFX_SAVECHANGESDLG_H__C7E59CC8_830E_4BB1_95D0_22FAA75CA864__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveChangesDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld SaveChangesDlg 

class SaveChangesDlg : public CDialog
{
// Konstruktion
public:
	SaveChangesDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(SaveChangesDlg)
	enum { IDD = IDD_SAVE_CHANGES };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(SaveChangesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(SaveChangesDlg)
	afx_msg void OnSaveNo();
	virtual void OnCancel();
	afx_msg void OnSaveYes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SAVECHANGESDLG_H__C7E59CC8_830E_4BB1_95D0_22FAA75CA864__INCLUDED_
