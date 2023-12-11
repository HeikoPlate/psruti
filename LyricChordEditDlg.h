#if !defined(AFX_LYRICCHORDEDITDLG_H__AA7C5134_2F81_4182_8DEA_A96DB7562DFB__INCLUDED_)
#define AFX_LYRICCHORDEDITDLG_H__AA7C5134_2F81_4182_8DEA_A96DB7562DFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LyricChordEditDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld LyricChordEditDlg 

class LyricChordEditDlg : public CDialog
{
// Konstruktion
public:
	LyricChordEditDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(LyricChordEditDlg)
	enum { IDD = IDD_CHORD_LYRIC_DLG };
	CButton	m_ok;
	CButton	m_newpage;
	CButton	m_linefeed;
	CButton	m_delete;
	CEdit	m_text;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(LyricChordEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(LyricChordEditDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDelete();
	afx_msg void OnLinefeed();
	afx_msg void OnNewpage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	HPMF_Interface *hpmfi;
	int last_time;
	int type; // in
	int takt; // in/out
	int beat; // in/out
	int tick; // in/out
	CString text; // in/out
	bool delete_event; // out
	unsigned char cr; // out
	unsigned char ct; // out
	unsigned char bn; // out
	unsigned char bt; // out

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_LYRICCHORDEDITDLG_H__AA7C5134_2F81_4182_8DEA_A96DB7562DFB__INCLUDED_
