#if !defined(AFX_DELETE_FILL_LYRICS_DLG_H__38F71C3A_96F2_4B7B_AD72_E2DB849597BF__INCLUDED_)
#define AFX_DELETE_FILL_LYRICS_DLG_H__38F71C3A_96F2_4B7B_AD72_E2DB849597BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Delete_Fill_Lyrics_Dlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDelete_Fill_Lyrics_Dlg 

class CDelete_Fill_Lyrics_Dlg : public CDialog
{
// Konstruktion
public:
	CDelete_Fill_Lyrics_Dlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDelete_Fill_Lyrics_Dlg)
	enum { IDD = IDD_DELETE_FILL_LYRICS };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDelete_Fill_Lyrics_Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDelete_Fill_Lyrics_Dlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	HPMF_Interface * hpmfi;
	CString taktlyric, beatlyric, endlyric; 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DELETE_FILL_LYRICS_DLG_H__38F71C3A_96F2_4B7B_AD72_E2DB849597BF__INCLUDED_
