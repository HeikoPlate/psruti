#if !defined(AFX_TIME_SIGNATURE_H__FB40D1D4_83B8_40D7_8164_32FD5A794CF4__INCLUDED_)
#define AFX_TIME_SIGNATURE_H__FB40D1D4_83B8_40D7_8164_32FD5A794CF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Time_Signature.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Time_Signature 

class Time_Signature : public CDialog
{

#define NO_NUM 8
#define NO_DENUM 6

// Konstruktion
public:
	Time_Signature(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(Time_Signature)
	enum { IDD = IDD_TIME_SIGNATURE };
	CButton	m_switch;
	CButton	m_export_note_area;
	CButton	m_import_note_area;
	CButton	m_run_before_notes;
	CListBox	m_denum;
	CListBox	m_num;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Time_Signature)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung

public:

	HPMF_Interface * hpmfi;
	HCURSOR hCursorOld;
	HCURSOR hCursorWait;
	IniFile *p_inifile;

private:
	
	HICON hIcon_switch;
	bool before_notes_selected;
	bool note_area_selected;
	bool export_area_selected;
	bool import_area_selected;
	int num_selected;
	int denum_selected;
	int id;
	int time;
	int chan;
	int type;
	int metronome_click;
	int n32;
	int num;
	int denum;
	bool time_signature_found;
	int no_time_signatures;
	bool source_changed;

	static const CString numlist[NO_NUM];
	static const int int_numlist[NO_NUM];
	static const CString denumlist[NO_DENUM];
	static const int int_denumlist[NO_DENUM];

	CString select_prot_file(bool export);

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Time_Signature)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeNum();
	afx_msg void OnSelchangeDenum();
	afx_msg void OnRunBeforeNotes();
	afx_msg void OnFinish();
	afx_msg void OnExportNoteArea();
	afx_msg void OnImportNoteArea();
	afx_msg void OnSwitch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_TIME_SIGNATURE_H__FB40D1D4_83B8_40D7_8164_32FD5A794CF4__INCLUDED_
