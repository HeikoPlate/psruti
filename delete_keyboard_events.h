#if !defined(AFX_DELETE_KEYBOARD_EVENTS_H__BDF14C1A_6F8C_459B_BBF2_0B89BD4C4C25__INCLUDED_)
#define AFX_DELETE_KEYBOARD_EVENTS_H__BDF14C1A_6F8C_459B_BBF2_0B89BD4C4C25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// delete_keyboard_events.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld delete_keyboard_events 

class delete_keyboard_events : public CDialog
{
// Konstruktion
public:
	delete_keyboard_events(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(delete_keyboard_events)
	enum { IDD = IDD_KBD_EVENTS };
	CButton	m_sp_marker;
	CButton	m_sysex_guide;
	CButton	m_phrase_metas;
	CButton	m_score_start_bar;
	CButton	m_guide_track_flag;
	CButton	m_lyrics_bitmap_events;
	CButton	m_kbd_voice_events;
	CButton	m_style_sysex;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(delete_keyboard_events)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(delete_keyboard_events)
	afx_msg void OnKbdVoiceEvents();
	afx_msg void OnStyleSysex();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnGuideTrackFlag();
	afx_msg void OnLyricsBitmapEvents();
	afx_msg void OnPhraseMetas();
	afx_msg void OnScoreStartBar();
	afx_msg void OnSysExGuide();
	afx_msg void OnSpMarker();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	bool del_kbd_voice_events;
	bool del_phrase_events;
	bool del_guide_track_events;
	bool del_sysex_guide_events;
	bool del_lyrics_bitmap_events;
	bool del_score_start_bar_events;
	bool del_style_events;
	bool del_sp_marker_events;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DELETE_KEYBOARD_EVENTS_H__BDF14C1A_6F8C_459B_BBF2_0B89BD4C4C25__INCLUDED_
