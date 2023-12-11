#if !defined(AFX_MASTERVOLUME_H__6AEB49CA_FBEE_44A2_8711_E15B2F0FA282__INCLUDED_)
#define AFX_MASTERVOLUME_H__6AEB49CA_FBEE_44A2_8711_E15B2F0FA282__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MasterVolume.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld MasterVolume 

class MasterVolume : public CDialog
{
// Konstruktion
public:
	MasterVolume(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(MasterVolume)
	enum { IDD = IDD_MASTER_VOLUME };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(MasterVolume)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(MasterVolume)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditMasterVolume();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int init_master_volume;
	int master_volume;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_MASTERVOLUME_H__6AEB49CA_FBEE_44A2_8711_E15B2F0FA282__INCLUDED_
