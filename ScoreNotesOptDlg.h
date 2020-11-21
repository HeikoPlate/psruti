#if !defined(AFX_SCORENOTESOPTDLG_H__8CAB1A09_40E6_48FB_AA4A_588188E6E014__INCLUDED_)
#define AFX_SCORENOTESOPTDLG_H__8CAB1A09_40E6_48FB_AA4A_588188E6E014__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScoreNotesOptDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld ScoreNotesOptDlg 

class ScoreNotesOptDlg : public CDialog
{
// Konstruktion
public:
	ScoreNotesOptDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(ScoreNotesOptDlg)
	enum { IDD = IDD_SCORE_NOTES_OPT };
	CListBox	m_max_notes_list;
	CEdit	m_no_quarters;
	CComboBox	m_score_chan_list;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(ScoreNotesOptDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(ScoreNotesOptDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeScoreChanList();
	afx_msg void OnSelchangeMaxNotesList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	HPMF_Interface * hpmfi;
	int act_score_channel;
	int max_note_ticks;
private:
	int score_channel_index_list[16]; // score_channel_index_list[i] = k, i = index ComboBox, k = channel
    int max_notes_list_index_selected;
	static const int max_note_ticks_list[6];

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SCORENOTESOPTDLG_H__8CAB1A09_40E6_48FB_AA4A_588188E6E014__INCLUDED_
