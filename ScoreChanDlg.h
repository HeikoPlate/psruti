#if !defined(AFX_SCORECHANDLG_H__8C3822EA_A8FE_4B90_9689_1B549E81FE1A__INCLUDED_)
#define AFX_SCORECHANDLG_H__8C3822EA_A8FE_4B90_9689_1B549E81FE1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScoreChanDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld ScoreChanDlg 

class ScoreChanDlg : public CDialog
{
// Konstruktion
public:
	ScoreChanDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(ScoreChanDlg)
	enum { IDD = IDD_SCORECHAN };
	CListBox	m_scorechan_right;
	CListBox	m_scorechan_left;
	CSpinButtonCtrl	m_channelspin;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(ScoreChanDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(ScoreChanDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeListScorechan();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListScorechanRight();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool allowed_chan_selection[17];
public:
	HPMF_Interface * hpmfi;
	int chan_left;
	int chan_right;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SCORECHANDLG_H__8C3822EA_A8FE_4B90_9689_1B549E81FE1A__INCLUDED_
