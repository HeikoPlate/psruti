#if !defined(AFX_SLCTCHORDCHAN_H__4AEA4D6B_2BD8_4846_AB8E_7DF6F1CEEE43__INCLUDED_)
#define AFX_SLCTCHORDCHAN_H__4AEA4D6B_2BD8_4846_AB8E_7DF6F1CEEE43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SlctChordChan.h : Header-Datei
//

#include "HP_midifile.h"
#include "HPMF_Interface.h"
#include "Chd.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld SlctChordChan 

class SlctChordChan : public CDialog
{

// Konstruktion
public:
	SlctChordChan(CWnd* pParent = NULL);   // Standardkonstruktor
	bool allowed_selection[NO_CHORDLIST_CHAN-1];
	int no_list[NO_CHORDLIST_CHAN]; // no of computed chords per channel
	HPMF_Interface * hpmfi;
	bool chords_save;
	bool chords_print;
	bool chords_print_lyric;
	int bass_channel;

	void get_chan_list(bool chan_l[16]);

// Dialogfelddaten
	//{{AFX_DATA(SlctChordChan)
	enum { IDD = IDD_SLCTCHORDCHAN };
	CEdit	m_chord_patch1;
	CEdit	m_chord_patch2;
	CEdit	m_chord_patch3;
	CEdit	m_chord_patch4;
	CEdit	m_chord_patch5;
	CEdit	m_chord_patch6;
	CEdit	m_chord_patch7;
	CEdit	m_chord_patch8;
	CEdit	m_chord_patch9;
	CEdit	m_chord_patch10;
	CEdit	m_chord_patch11;
	CEdit	m_chord_patch12;
	CEdit	m_chord_patch13;
	CEdit	m_chord_patch14;
	CEdit	m_chord_patch15;
	CEdit	m_chord_patch16;
	CButton	m_prot_chords_lyric;
	CButton	m_check_chan_1;
	CButton	m_check_chan_2;
	CButton	m_check_chan_3;
	CButton	m_check_chan_4;
	CButton	m_check_chan_5;
	CButton	m_check_chan_6;
	CButton	m_check_chan_7;
	CButton	m_check_chan_8;
	CButton	m_check_chan_9;
	CButton	m_check_chan_10;
	CButton	m_check_chan_11;
	CButton	m_check_chan_12;
	CButton	m_check_chan_13;
	CButton	m_check_chan_14;
	CButton	m_check_chan_15;
	CButton	m_check_chan_16;
	CButton	m_check_chan_all;
	CButton	m_check_bass_1;
	CButton	m_check_bass_2;
	CButton	m_check_bass_3;
	CButton	m_check_bass_4;
	CButton	m_check_bass_5;
	CButton	m_check_bass_6;
	CButton	m_check_bass_7;
	CButton	m_check_bass_8;
	CButton	m_check_bass_9;
	CButton	m_check_bass_10;
	CButton	m_check_bass_11;
	CButton	m_check_bass_12;
	CButton	m_check_bass_13;
	CButton	m_check_bass_14;
	CButton	m_check_bass_15;
	CButton	m_check_bass_16;
	CButton	m_prot_chords;
	CButton	m_insert_chords;
	CButton	m_sysex_chords;
	CButton	m_simple_chord;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(SlctChordChan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung

private:
	CToolTipCtrl* m_pToolTip;
	CEdit   *value[16];
	bool multi_selected;
	bool all_selected;
	bool single_selected;
	bool is_simple_chords;
	int single_chan;
	bool chan_list[16];
	CButton	*check_list[17];
	CButton	*bass_check_list[16];

	void check_chan_event(int list_index, bool on);
	void check_bass_event(int list_index, bool on);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(SlctChordChan)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnOk();
	afx_msg void OnCheckProtChords();
	afx_msg void OnCheckInsertChords();
	afx_msg void OnCheckChan1();
	afx_msg void OnCheckChan2();
	afx_msg void OnCheckChan3();
	afx_msg void OnCheckChan4();
	afx_msg void OnCheckChan5();
	afx_msg void OnCheckChan6();
	afx_msg void OnCheckChan7();
	afx_msg void OnCheckChan8();
	afx_msg void OnCheckChan9();
	afx_msg void OnCheckChan10();
	afx_msg void OnCheckChan11();
	afx_msg void OnCheckChan12();
	afx_msg void OnCheckChan13();
	afx_msg void OnCheckChan14();
	afx_msg void OnCheckChan15();
	afx_msg void OnCheckChan16();
	afx_msg void OnCheckChanAll();
	afx_msg void OnCheckBass1();
	afx_msg void OnCheckBass2();
	afx_msg void OnCheckBass3();
	afx_msg void OnCheckBass4();
	afx_msg void OnCheckBass5();
	afx_msg void OnCheckBass6();
	afx_msg void OnCheckBass7();
	afx_msg void OnCheckBass8();
	afx_msg void OnCheckBass9();
	afx_msg void OnCheckBass10();
	afx_msg void OnCheckBass11();
	afx_msg void OnCheckBass12();
	afx_msg void OnCheckBass13();
	afx_msg void OnCheckBass14();
	afx_msg void OnCheckBass15();
	afx_msg void OnCheckBass16();
	afx_msg void OnCheckProtChordsLyric();
	afx_msg void OnCheckSimple();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // AFX_SLCTCHORDCHAN_H__4AEA4D6B_2BD8_4846_AB8E_7DF6F1CEEE43__INCLUDED_
