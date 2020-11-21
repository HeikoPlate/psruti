#if !defined(AFX_SCORELAYOUT_H__1E2B87CD_FBF1_4AD7_9B3B_95B43EE7DFDD__INCLUDED_)
#define AFX_SCORELAYOUT_H__1E2B87CD_FBF1_4AD7_9B3B_95B43EE7DFDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScoreLayout.h : Header-Datei
//

#include "MyArrays.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld ScoreLayout 

class ScoreLayout : public CDialog
{
// Konstruktion
public:
	ScoreLayout(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(ScoreLayout)
	enum { IDD = IDD_SCORE_LAYOUT };
	CComboBox	m_sizecombo;
	CComboBox	m_quantizetriolecombo;
	CComboBox	m_notenamescombo;
	CComboBox	m_lyricscombo;
	CComboBox	m_notecolourcombo;
	CComboBox	m_chordscombo;
	CComboBox	m_notenamestypecombo;
	CComboBox	m_quantizecombo;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(ScoreLayout)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung

public:
    HPMF_Interface *hpmfi;
	
	unsigned char lyrics_value;			 // sysex type 0x02
	unsigned char chords_value;			 // sysex type 0x03
	unsigned char notenames_value;		 // sysex type 0x04
	unsigned char size_value;			 // sysex type 0x05
	unsigned char quantize_triole_value; // sysex type 0x08
	unsigned char quantize_value;		 // sysex type 0x09
	unsigned char notenamestype_value;	 // sysex type 0x0a
	unsigned char notecolour_value;		 // sysex type 0x0b

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(ScoreLayout)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeChordscombo();
	afx_msg void OnSelchangeSizecombobox();
	afx_msg void OnSelchangeNotecolourcombo();
	afx_msg void OnSelchangeNotenamescombo();
	afx_msg void OnSelchangeNotenamestypecombo();
	afx_msg void OnSelchangeQuantizecombo();
	afx_msg void OnSelchangeQuantizetriolecombo();
	afx_msg void OnSelchangeLyriccombobox();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SCORELAYOUT_H__1E2B87CD_FBF1_4AD7_9B3B_95B43EE7DFDD__INCLUDED_
