#if !defined(AFX_HANGEDRUMVOICESDLG_H__F868B10D_3C9F_4E14_91F3_98A9F639DA86__INCLUDED_)
#define AFX_HANGEDRUMVOICESDLG_H__F868B10D_3C9F_4E14_91F3_98A9F639DA86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// hangeDrumVoicesDlg.h : Header-Datei
//

#include "HPMF_Interface.h"
#include "InsdefDlg.h"
#include "InsDefOnOffDlg.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld ChangeDrumVoicesDlg 

class ChangeDrumVoicesDlg : public CDialog
{
// Konstruktion
public:
	ChangeDrumVoicesDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(ChangeDrumVoicesDlg)
	enum { IDD = IDD_TRANSPOSE_DRUMS };
	CButton	m_check_dyn_vel;
	CEdit	m_edit_velocity;
	CListBox	m_new_note_list;
	CListBox	m_source_note_list;
	CListBox	m_drum_chan_list;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(ChangeDrumVoicesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(ChangeDrumVoicesDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnInsdef();
	afx_msg void OnSelchangeDrumChanList();
	afx_msg void OnSelchangeSourceNoteList();
	afx_msg void OnSelchangeNewNoteList();
	afx_msg void OnChangeEditVelocity();
	afx_msg void OnCheckDynVel();
	afx_msg void OnExit();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	int get_init_data();
	int fill_drum_names();
	void fill_drum_note_lists(int bank, int kit);
	void clear_drum_note_lists();
	void destroy_chan_list();
	void VoiceTest();


	int scr_drum_chan;
	int scr_note;
	int scr_new_note;
	int scr_new_velocity;
	int last_new_list_index;
	bool drums_changed;

	struct drum_chan_elem 
		{	bool is_drum;
			int bank;
			int kit;
			char* drumbank_name; 
			char* drumkit_name;
			int line;
		} drum_chan_list[16];

	struct note_elem 
		{	bool is_source; 
			bool is_dest; 
			int source_line; 
			int dest_line; 
			CString note_name;
		} note_list[128];

	HP_MIDIFILE_MODULE* mf_voiceplay;

public:
	HPMF_Interface * hpmfi;
	IniFile *p_inifile;
	HCURSOR hCursorOld;
	HCURSOR hCursorWait;

	int drum_chan;
	int note;
	int new_note;
	int new_velocity;
	bool dynamic;
	int min_vel;
	int max_vel;
	UINT_PTR m_nTimer;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_HANGEDRUMVOICESDLG_H__F868B10D_3C9F_4E14_91F3_98A9F639DA86__INCLUDED_
