#if !defined(AFX_EXTRAS_DLG_H__24C3AF30_34EF_4F90_AAD1_9A1BC08F9966__INCLUDED_)
#define AFX_EXTRAS_DLG_H__24C3AF30_34EF_4F90_AAD1_9A1BC08F9966__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Extras_Dlg.h : Header-Datei
//

#include "MainFunctions.h"
#include "VhActDeactDlg.h"
#include "delete_keyboard_events.h"
#include "Time_Signature.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Extras_Dlg 

class Extras_Dlg : public CDialog
{
// Konstruktion
public:
	Extras_Dlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(Extras_Dlg)
	enum { IDD = IDD_EXTRAS };
	CButton	m_click_chan;
	CButton	m_time_signature;
	CButton	m_lengthen;
	CButton	m_delete_short_notes;
	CButton	m_delete_midi_events;
	CButton	m_quantize;
	CButton	m_vh_chan;
	CButton	m_normalize_chords;
	CButton	m_delete_kbd_events;
	CButton	m_songname;
	CButton	m_quickstart;
	CButton	m_copyright;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Extras_Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Extras_Dlg)
	afx_msg void OnSongname();
	afx_msg void OnCopyright();
	afx_msg void OnQuickstart();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDeleteKbdEvents();
	afx_msg void OnNormalizeChords();
	afx_msg void OnVocalHarmony();
	afx_msg void OnClose();
	afx_msg void OnQuantize();
	afx_msg void OnDeleteShortNotes();
	afx_msg void OnDeleteMidiEvents();
	afx_msg void OnLengthen();
	afx_msg void OnTimeSignature();
	afx_msg void OnClickChan();
	afx_msg void OnScore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CToolTipCtrl m_pToolTip;
	virtual BOOL PreTranslateMessage(MSG* pMSG);
	bool vh_act_deact_folder_abort_wanted;
	bool vh_act_deact_folder_running;
	bool delete_kbd_events_folder_abort_wanted;
	bool delete_kbd_events_folder_running;
	bool del_kbd_voice_events;
	bool del_phrase_events;
	bool del_guide_track_events;
	bool del_sysex_guide_events;
	bool del_lyrics_bitmap_events;
	bool del_score_start_bar_events;
	bool del_style_events;
	bool del_sp_marker_events;

	HANDLE hThread;
	DWORD threadID;
	char sourcefile[MAX_PATH+512];
	char destfile[MAX_PATH+512];
	VhActDeactDlg *vh_act_deact_dlg;
	static DWORD vh_act_deact_thread_run(Extras_Dlg *this_thread);
	void vh_act_deact_folder();
	void vh_act_deact_folder_file(CString midifile,CString dest_path,
			int vh_channel,	bool vh_select, bool vh_deselect, int vh_act);
	delete_keyboard_events *delete_kbd_events_dlg;
	static DWORD delete_kbd_events_thread_run(Extras_Dlg *this_thread);
	void delete_kbd_events_folder();
	void delete_kbd_events_folder_file(CString midifile,CString dest_path,bool del_kbd_voice_events,bool del_style_events);
	
	void initialize_source_reduced();

public:
	HPMF_Interface *hpmfi;
	MainFunctions *mainfun;
	HCURSOR hCursorWait;
	HCURSOR hCursorOld;
	bool batch_running;
	IniFile *o_inifile;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_EXTRAS_DLG_H__24C3AF30_34EF_4F90_AAD1_9A1BC08F9966__INCLUDED_
