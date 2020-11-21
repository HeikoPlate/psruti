#if !defined(AFX_SELECTFILLLYRICS_H__F529D3A7_727F_49F7_B259_71F509E13FCA__INCLUDED_)
#define AFX_SELECTFILLLYRICS_H__F529D3A7_727F_49F7_B259_71F509E13FCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectFillLyrics.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld SelectFillLyrics 

class SelectFillLyrics : public CDialog
{
// Konstruktion
public:
	SelectFillLyrics(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(SelectFillLyrics)
	enum { IDD = IDD_LINEFEED };
	CButton	m_shift_linefeeds_at;
	CEdit	m_shift_ticks_at;
	CEdit	m_shift_ticks;
	CButton	m_shift_linefeeds;
	CEdit	m_cuepoint_lyrc_ticks;
	CButton	m_select_cuepoint_lyrc;
	CButton	m_select_linefeed;
//	CButton	m_select_fill_lyrics;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(SelectFillLyrics)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(SelectFillLyrics)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectLinefeedCheck();
	afx_msg void OnSelectCuepointLyrc();
	afx_msg void OnChangeEditLyrcTicks();
	afx_msg void OnChangeShiftTicks();
	afx_msg void OnShiftLinefeeds();
	afx_msg void OnShiftLinefeedsAt();
	afx_msg void OnChangeShiftTicksAt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	HPMF_Interface * hpmfi;
	Log *logf;
	int linefeedlyrictick;

	int cuepointlyrctick;
	int shift_ticks;
	int shift_ticks_at;

	bool linefeed_selected();
	bool cuepoint_lyrc_selected();
	
	int		get_cuepoint_lyrc_tick();
	int		get_shift_ticks();
	int		get_shift_ticks_at();

private:

	bool is_linefeed;
	bool is_cuepoint_lyrc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SELECTFILLLYRICS_H__F529D3A7_727F_49F7_B259_71F509E13FCA__INCLUDED_
