#if !defined(AFX_SONGNAME_H__87CDA7D5_41A2_4C74_86B0_C8E219E8B8EA__INCLUDED_)
#define AFX_SONGNAME_H__87CDA7D5_41A2_4C74_86B0_C8E219E8B8EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Songname.h : Header-Datei
//

#include "HPMF_interface.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSongname 

class CSongname : public CDialog
{
// Konstruktion
public:
	CSongname(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CSongname)
	enum { IDD = IDD_CHANGE_SONGNAME };
	CEdit	m_edit_new_songname;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CSongname)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
public:

HPMF_Interface *hpmfi;
CString songname;
CString composer;
CString lyricist;

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CSongname)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SONGNAME_H__87CDA7D5_41A2_4C74_86B0_C8E219E8B8EA__INCLUDED_
