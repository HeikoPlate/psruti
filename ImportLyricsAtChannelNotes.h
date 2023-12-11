#if !defined(AFX_IMPORTLYRICSATCHANNELNOTES_H__F7734199_628D_4A72_B704_3529EF70B677__INCLUDED_)
#define AFX_IMPORTLYRICSATCHANNELNOTES_H__F7734199_628D_4A72_B704_3529EF70B677__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImportLyricsAtChannelNotes.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld ImportLyricsAtChannelNotes 

class ImportLyricsAtChannelNotes : public CDialog
{
// Konstruktion
public:
	ImportLyricsAtChannelNotes(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(ImportLyricsAtChannelNotes)
	enum { IDD = IDD_LYRICS_AT_CHANNEL_NOTES };
	CButton	m_check_chan1;
	CButton	m_check_chan2;
	CButton	m_check_chan3;
	CButton	m_check_chan4;
	CButton	m_check_chan5;
	CButton	m_check_chan6;
	CButton	m_check_chan7;
	CButton	m_check_chan8;
	CButton	m_check_chan9;
	CButton	m_check_chan10;
	CButton	m_check_chan11;
	CButton	m_check_chan12;
	CButton	m_check_chan13;
	CButton	m_check_chan14;
	CButton	m_check_chan15;
	CButton	m_check_chan16;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(ImportLyricsAtChannelNotes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(ImportLyricsAtChannelNotes)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
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
	afx_msg void OnOpenLyricFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	HPMF_Interface *hpmfi;
	int selected_chan;
	CString lyricfile;


private:
	CButton *check_chan[16];
	int	idc_type[16]; // voice names

	void CheckChan(int chan);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_IMPORTLYRICSATCHANNELNOTES_H__F7734199_628D_4A72_B704_3529EF70B677__INCLUDED_
