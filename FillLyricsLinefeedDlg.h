#if !defined(AFX_FILLLYRICSLINEFEEDDLG_H__A88E8FFD_3375_4913_B1E0_1306617DBFBE__INCLUDED_)
#define AFX_FILLLYRICSLINEFEEDDLG_H__A88E8FFD_3375_4913_B1E0_1306617DBFBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FillLyricsLinefeedDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CFillLyricsLinefeedDlg 

class CFillLyricsLinefeedDlg : public CDialog
{
// Konstruktion
public:
	CFillLyricsLinefeedDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CFillLyricsLinefeedDlg)
	enum { IDD = IDD_FILLLYRICS_LINEFEED };
	CButton	m_user3;
	CButton	m_user2;
	CButton	m_user1;
	CEdit	m_lflyric_ticks;
	CButton	m_lflyric_check;
	CButton	m_fill_lyrics;
	CString	m_takt_lyric;
	CString	m_beat_lyric;
	CString	m_end_lyric;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CFillLyricsLinefeedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CFillLyricsLinefeedDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnLflyricCheck();
	afx_msg void OnChangeLflyricTicks();
	afx_msg void OnDefaultLyrics();
	virtual void OnOK();
	afx_msg void OnCancel();
	afx_msg void OnChangeTaktLyric();
	afx_msg void OnChangeBeatLyric();
	afx_msg void OnChangeEndLyric();
	afx_msg void OnUser1FillLyrics();
	afx_msg void OnUser2FillLyrics();
	afx_msg void OnUser3FillLyrics();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int is_user;
	HPMF_Interface* hpmfi;
	Log *logf;
	CString user1_takt_lyric;
	CString user1_beat_lyric;
	CString user1_end_lyric;
	int user1_linefeedlyrictick;
	CString user2_takt_lyric;
	CString user2_beat_lyric;
	CString user2_end_lyric;
	int user2_linefeedlyrictick;
	CString user3_takt_lyric;
	CString user3_beat_lyric;
	CString user3_end_lyric;
	int user3_linefeedlyrictick;

	int get_user();
	CString get_user1_takt_lyric();
	CString get_user1_beat_lyric();
	CString get_user1_end_lyric();
	int     get_user1_linefeedlyrictick();
	CString get_user2_takt_lyric();
	CString get_user2_beat_lyric();
	CString get_user2_end_lyric();
	int     get_user2_linefeedlyrictick();
	CString get_user3_takt_lyric();
	CString get_user3_beat_lyric();
	CString get_user3_end_lyric();
	int     get_user3_linefeedlyrictick();

	void set_user(int user);
	void set_user1_fill_lyric_data(CString tl, CString bl, CString el, int lflt);
	void set_user2_fill_lyric_data(CString tl, CString bl, CString el, int lflt);
	void set_user3_fill_lyric_data(CString tl, CString bl, CString el, int lflt);
	void actualize();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_FILLLYRICSLINEFEEDDLG_H__A88E8FFD_3375_4913_B1E0_1306617DBFBE__INCLUDED_
