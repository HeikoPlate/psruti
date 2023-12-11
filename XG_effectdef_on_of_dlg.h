#if !defined(AFX_XG_EFFECTDEF_ON_OF_DLG_H__22F4AB2C_6123_409F_9564_A407FFDAA374__INCLUDED_)
#define AFX_XG_EFFECTDEF_ON_OF_DLG_H__22F4AB2C_6123_409F_9564_A407FFDAA374__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XG_effectdef_on_of_dlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld XG_effectdef_on_of_dlg 

class XG_effectdef_on_of_dlg : public CDialog
{
// Konstruktion
public:
	XG_effectdef_on_of_dlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(XG_effectdef_on_of_dlg)
	enum { IDD = IDD_XG_EFFECTDEF_ON_OFF_DLG };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(XG_effectdef_on_of_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(XG_effectdef_on_of_dlg)
	afx_msg void OnOn();
	afx_msg void OnOff();
	afx_msg void OnCancel();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_XG_EFFECTDEF_ON_OF_DLG_H__22F4AB2C_6123_409F_9564_A407FFDAA374__INCLUDED_
