#if !defined(AFX_DRUMSDLG_H__EE9D600B_7A93_422E_9F0D_E695C9B59BEF__INCLUDED_)
#define AFX_DRUMSDLG_H__EE9D600B_7A93_422E_9F0D_E695C9B59BEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrumsDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDrumsDlg 

class CDrumsDlg : public CDialog
{
// Konstruktion
public:
	CDrumsDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDrumsDlg)
	enum { IDD = IDD_ABOUTBOX };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDrumsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDrumsDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DRUMSDLG_H__EE9D600B_7A93_422E_9F0D_E695C9B59BEF__INCLUDED_
