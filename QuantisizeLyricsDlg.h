#if !defined(AFX_QUANTISIZELYRICSDLG_H__515CC9BE_00D0_498F_BC61_2C0833A8F1A5__INCLUDED_)
#define AFX_QUANTISIZELYRICSDLG_H__515CC9BE_00D0_498F_BC61_2C0833A8F1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QuantisizeLyricsDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld QuantisizeLyricsDlg 

class QuantisizeLyricsDlg : public CDialog
{
// Konstruktion
public:
	QuantisizeLyricsDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(QuantisizeLyricsDlg)
	enum { IDD = IDD_QUANTISIZE_LYRICS };
	CButton	m_eighth_triole_quantisize;
	CButton	m_lyrics_at_chords;
	CButton	m_sixteenth_quantisize;
	CButton	m_quarter_quantisize;
	CButton	m_eighth_quantisize;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(QuantisizeLyricsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(QuantisizeLyricsDlg)
	afx_msg void OnQuarterQuantisize();
	afx_msg void OnEighthQuantisize();
	afx_msg void OnSixteenthQuantisize();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnLyricsAtChords();
	afx_msg void OnEighthTrioleQuantisize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int ppqn;
	int resolution;
	bool is_lyrics_at_chords;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_QUANTISIZELYRICSDLG_H__515CC9BE_00D0_498F_BC61_2C0833A8F1A5__INCLUDED_
