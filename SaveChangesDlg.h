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
		// HINWEIS: Der Klassen-Assistent f�gt hier Datenelemente ein
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(SaveChangesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
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
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_SAVECHANGESDLG_H__C7E59CC8_830E_4BB1_95D0_22FAA75CA864__INCLUDED_
