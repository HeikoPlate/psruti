#if !defined(AFX_SPECIALPREFERENCES_H__8E39A342_470F_490F_B851_F589150048FB__INCLUDED_)
#define AFX_SPECIALPREFERENCES_H__8E39A342_470F_490F_B851_F589150048FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpecialPreferences.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSpecialPreferences 

class CSpecialPreferences : public CDialog
{
// Konstruktion
public:
	CSpecialPreferences(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CSpecialPreferences)
	enum { IDD = IDD_SPECIAL_PREFERENCES };
	CButton	m_without_sysex_drumkit_mode;
	CButton	m_vh_events_delete;
	CButton	m_drums_from_insfile;
	CButton	m_no_lyric_cuepoint;
	CButton	m_allow_alien_voices;
	CButton	m_allow_alien_sysex;
	CButton	m_fill_sequ_track;
	CButton	m_drum_setup_convert;
	CButton	m_mp_convert;
	CButton	m_delete_double_notes;
	CButton	m_delete_not_double_drum_notes;
	CButton	m_check_dchan;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CSpecialPreferences)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CSpecialPreferences)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDefault();
	afx_msg void OnDeleteDoubleNotes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	IniFile *o_inifile;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPECIALPREFERENCES_H__8E39A342_470F_490F_B851_F589150048FB__INCLUDED_
