#if !defined(AFX_STARTBEATFOLDERDLG_H__6C6BEA70_48B6_4D32_B3A6_918A9613FF61__INCLUDED_)
#define AFX_STARTBEATFOLDERDLG_H__6C6BEA70_48B6_4D32_B3A6_918A9613FF61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StartBeatFolderDlg.h : Header-Datei
//

#define NO_DRUMS 72
#define FIRST_DRUM 13

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld StartBeatFolderDlg 

class StartBeatFolderDlg : public CDialog
{
// Konstruktion
public:
	StartBeatFolderDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(StartBeatFolderDlg)
	enum { IDD = IDD_START_BEAT_FOLDER };
	CButton	m_check_one_measure;
	CEdit	m_start_beat_vel;
	CComboBox	m_drum;
	CButton	m_insert_count_in;
	CButton	m_delete_count_in;
	CButton	m_check_all_beats;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(StartBeatFolderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung

// Implementierung

public:
	
	bool start_beat_delete;
	bool on_all_beats;
	bool only_one_measure;
	bool get_start_beat_delete();
	int get_drum();
	int get_velocity();
	void set_velocity(int vel);
	void set_drum(int note);

private:
	int drum;
	int velocity;
	static const char* drums[NO_DRUMS+1];

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(StartBeatFolderDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeStartBeatVel();
	afx_msg void OnCheckAllBeats();
	afx_msg void OnDeleteCountIn();
	afx_msg void OnInsertCountIn();
	virtual void OnCancel();
	afx_msg void OnCheckOneMeasure();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_STARTBEATFOLDERDLG_H__6C6BEA70_48B6_4D32_B3A6_918A9613FF61__INCLUDED_
