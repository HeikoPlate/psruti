#if !defined(AFX_QUICKSTART_H__0E0489F0_C030_4DD8_85E1_916CD412E830__INCLUDED_)
#define AFX_QUICKSTART_H__0E0489F0_C030_4DD8_85E1_916CD412E830__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Quickstart.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Quickstart 

class Quickstart : public CDialog
{
// Konstruktion
public:
	Quickstart(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(Quickstart)
	enum { IDD = IDD_QUICKSTART };
		// HINWEIS: Der Klassen-Assistent f�gt hier Datenelemente ein
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(Quickstart)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Quickstart)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	bool with_quickstart;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_QUICKSTART_H__0E0489F0_C030_4DD8_85E1_916CD412E830__INCLUDED_
