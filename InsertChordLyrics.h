#if !defined(AFX_INSERTCHORDLYRICS_H__2874D07A_64C0_4C51_92ED_E545404CB369__INCLUDED_)
#define AFX_INSERTCHORDLYRICS_H__2874D07A_64C0_4C51_92ED_E545404CB369__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// InsertChordLyrics.h : Header-Datei
//

#include "Play.h"



/////////////////////////////////////////////////////////////////////////////
// Dialogfeld InsertChordLyrics 

class InsertChordLyrics : public CDialog
{
// Konstruktion
public:
	InsertChordLyrics(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(InsertChordLyrics)
	enum { IDD = IDD_RECORD_CHORDS_LYRICS_DLG };
	CButton	m_whole_note;
	CButton	m_quarter_note;
	CButton	m_eighth_note;
	CButton	m_half_note;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(InsertChordLyrics)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(InsertChordLyrics)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnEighthNoteButton();
	afx_msg void OnHalfNoteButton();
	afx_msg void OnWholeNoteButton();
	afx_msg void OnQuarterNoteButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int resolution;


public:
	HPMF_Interface * hpmfi;
	HP_MIDIFILE_MODULE* mf;
	RECORD_CHORD_LYRIC_ELEM *record_chord_lyric_list;
	int play_tempo;
	int act_list_no;
	bool is_chord_record;
	bool is_lyric_record;
	char linefeed_char;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_INSERTCHORDLYRICS_H__2874D07A_64C0_4C51_92ED_E545404CB369__INCLUDED_
