#if !defined(AFX_PREFERENCESDLG_H__15A63066_559A_4A38_BFEB_DD8BE3431613__INCLUDED_)
#define AFX_PREFERENCESDLG_H__15A63066_559A_4A38_BFEB_DD8BE3431613__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreferencesDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CPreferencesDlg 

class CPreferencesDlg : public CDialog
{
// Konstruktion
public:
	CPreferencesDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CPreferencesDlg)
	enum { IDD = IDD_PREFERENCES };
	CButton	m_xg_effectdef;
	CButton	m_insdef;
	CButton	m_special_preferences;
	CButton	m_fill_lyrics_linefeed;
	CButton	m_select_midi_device;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CPreferencesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CPreferencesDlg)
	afx_msg void OnSelectMidiDevice();
	afx_msg void OnInsdef();
	afx_msg void OnFillLyricsLinefeed();
	virtual BOOL OnInitDialog();
	afx_msg void OnSpecialPreferences();
	virtual void OnOK();
	afx_msg void OnXgEffectdef();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	bool batch_running;
	HPMF_Interface *hpmfi;
	CPlay *pdlg;
	IniFile *o_inifile;
	HCURSOR hCursorWait, hCursorOld;
	MainFunctions *mainfun;

private:
	HP_MIDIFILE_MODULE* local_mf;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CToolTipCtrl *m_pToolTip;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PREFERENCESDLG_H__15A63066_559A_4A38_BFEB_DD8BE3431613__INCLUDED_
