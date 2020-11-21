#if !defined(AFX_DELETE_MIDI_EVENTS_H__97FD7356_BF7E_4349_8FF3_0E3A7002E6D5__INCLUDED_)
#define AFX_DELETE_MIDI_EVENTS_H__97FD7356_BF7E_4349_8FF3_0E3A7002E6D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Delete_MIDI_Events.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Delete_MIDI_Events 

class Delete_MIDI_Events : public CDialog
{
// Konstruktion
public:
	Delete_MIDI_Events(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(Delete_MIDI_Events)
	enum { IDD = IDD_DELETE_MIDI_EVENTS };
	CButton	m_note_area;
	CButton	m_before_notes;
	CButton	m_check1;
	CButton	m_check2;
	CButton	m_check3;
	CButton	m_check4;
	CButton	m_check5;
	CButton	m_check6;
	CButton	m_check7;
	CButton	m_check8;
	CButton	m_check9;
	CButton	m_check10;
	CButton	m_check11;
	CButton	m_check12;
	CButton	m_check13;
	CButton	m_check14;
	CButton	m_check15;
	CButton	m_check16;
	CButton	m_check_all;
	CComboBox	m_midi_event_combobox;
	CEdit	m_v_voice1;
	CEdit	m_v_voice2;
	CEdit	m_v_voice3;
	CEdit	m_v_voice4;
	CEdit	m_v_voice5;
	CEdit	m_v_voice6;
	CEdit	m_v_voice7;
	CEdit	m_v_voice8;
	CEdit	m_v_voice9;
	CEdit	m_v_voice10;
	CEdit	m_v_voice11;
	CEdit	m_v_voice12;
	CEdit	m_v_voice13;
	CEdit	m_v_voice14;
	CEdit	m_v_voice15;
	CEdit	m_v_voice16;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Delete_MIDI_Events)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Delete_MIDI_Events)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCheck7();
	afx_msg void OnCheck8();
	afx_msg void OnCheck9();
	afx_msg void OnCheck10();
	afx_msg void OnCheck11();
	afx_msg void OnCheck12();
	afx_msg void OnCheck13();
	afx_msg void OnCheck14();
	afx_msg void OnCheck15();
	afx_msg void OnCheck16();
	afx_msg void OnCheck_All();
	afx_msg void OnSelchangeMidiEventCombobox();
	afx_msg void OnBeforeNotes();
	afx_msg void OnNoteArea();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	HPMF_Interface *hpmfi;
	bool is_checked[16];
	int event_type;
	int ctrl_number;
	bool before_notes_checked;
	bool note_area_checked;
private:
	CToolTipCtrl* m_pToolTip;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int		idc_voice_type[16]; // voice names
	int		idc_no_list[17];	// actual number of events
	CButton *checklist[17];
	CEdit   *m_voice_type[16];
	int no_midi_events_list[17][NO_MIDI_EVENTS];
	int no_midi_events_before_notes_list[17][NO_MIDI_EVENTS];
	int no_midi_events_note_area_list[17][NO_MIDI_EVENTS];
    void fill_no_midi_events_list();
	void checked(int chan, bool is);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DELETE_MIDI_EVENTS_H__97FD7356_BF7E_4349_8FF3_0E3A7002E6D5__INCLUDED_
