#if !defined(AFX_INSDEFONOFFDLG_H__074E2D7C_2C23_4812_8890_43A55B4F26A4__INCLUDED_)
#define AFX_INSDEFONOFFDLG_H__074E2D7C_2C23_4812_8890_43A55B4F26A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsDefOnOffDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld InsDefOnOffDlg 

class InsDefOnOffDlg : public CDialog
{
// Konstruktion
public:
	InsDefOnOffDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(InsDefOnOffDlg)
	enum { IDD = IDD_INSDEF_ON_OFF };
		// HINWEIS: Der Klassen-Assistent f�gt hier Datenelemente ein
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(InsDefOnOffDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(InsDefOnOffDlg)
	afx_msg void OnInsdefOn();
	afx_msg void OnInsdefOff();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_INSDEFONOFFDLG_H__074E2D7C_2C23_4812_8890_43A55B4F26A4__INCLUDED_
