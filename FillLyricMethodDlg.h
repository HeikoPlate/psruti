#if !defined(AFX_FILLLYRICMETHODDLG_H__56828B28_B384_4E16_BB60_C26B3227EB71__INCLUDED_)
#define AFX_FILLLYRICMETHODDLG_H__56828B28_B384_4E16_BB60_C26B3227EB71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FillLyricMethodDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld FillLyricMethodDlg 

class FillLyricMethodDlg : public CDialog
{
// Konstruktion
public:
	FillLyricMethodDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(FillLyricMethodDlg)
	enum { IDD = IDD_FILL_LYRIC_METHOD };
	CButton	m_user2_fill_lyrics;
	CButton	m_user1_fill_lyrics;
	CButton	m_not_in_measures_with_lyrics;
	CButton	m_not_at_lyrics;
	CButton	m_not_in_beats_with_lyrics;
	CButton	m_user3_fill_lyrics;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(FillLyricMethodDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(FillLyricMethodDlg)
	afx_msg void OnNotInBeatsWithLyrics();
	afx_msg void OnNotAtLyrics();
	afx_msg void OnNotInMeasuresWithLyrics();
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnUser1FillLyrics();
	afx_msg void OnUser2FillLyrics();
	afx_msg void OnUser3FillLyrics();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString user1_takt_lyric;
	CString user1_beat_lyric;
	CString user1_end_lyric;
	CString user2_takt_lyric;
	CString user2_beat_lyric;
	CString user2_end_lyric;
	CString user3_takt_lyric;
	CString user3_beat_lyric;
	CString user3_end_lyric;
	int is_user;

	void display_actual_fill_lyrics();

public:
	void set_fill_lyric_data(CString u1_takt_l, CString u1_beat_l, CString u1_end_l,
							 CString u2_takt_l, CString u2_beat_l, CString u2_end_l,
							 CString u3_takt_l, CString u3_beat_l, CString u3_end_l,
							 int is_u);
	int get_actual_user();
	int method;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_FILLLYRICMETHODDLG_H__56828B28_B384_4E16_BB60_C26B3227EB71__INCLUDED_
