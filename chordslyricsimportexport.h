#if !defined(AFX_CHORDS_LYRICS_IMPORT_EXPORT_H__72827AA7_69F0_4912_81B5_63975EE3DF39__INCLUDED_)
#define AFX_CHORDS_LYRICS_IMPORT_EXPORT_H__72827AA7_69F0_4912_81B5_63975EE3DF39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChordsLyricsImportExport.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld ChordsLyricsImportExport 

class ChordsLyricsImportExport : public CDialog
{
// Konstruktion
public:
	ChordsLyricsImportExport(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(ChordsLyricsImportExport)
	enum { IDD = IDD_CHORDS_LYRICS_IMPORT_EXPORT_DGL };
	CButton	m_check_lyric_chords;
	CButton	m_check_select_import;
	CButton	m_check_select_export;
	CButton	m_check_remove_after;
	CButton	m_check_chord_sysex;
	CButton	m_chord_check;
	CButton	m_lyric_check;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(ChordsLyricsImportExport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(ChordsLyricsImportExport)
	afx_msg void OnChordCheck();
	afx_msg void OnLyricCheck();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckSelectExport();
	afx_msg void OnCheckSelectImport();
	afx_msg void OnCheckSelectLyricChords();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	IniFile *o_inifile;
	CString chord_lyricfile;
	bool is_chords;
	bool is_lyrics;
	bool is_import;
	bool is_export;
	bool is_export_as_lyrics;
	bool is_chord_sysex;
	bool is_remove_after;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_CHORDS_LYRICS_IMPORT_EXPORT_H__72827AA7_69F0_4912_81B5_63975EE3DF39__INCLUDED_
