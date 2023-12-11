#if !defined(AFX_LENGTHEN_NOTES_H__1FA3F23F_B0D1_48D0_BA0D_811C7D7CD115__INCLUDED_)
#define AFX_LENGTHEN_NOTES_H__1FA3F23F_B0D1_48D0_BA0D_811C7D7CD115__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Lengthen_Notes.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CLengthen_Notes 

class CLengthen_Notes : public CDialog
{
// Konstruktion
public:
	CLengthen_Notes(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CLengthen_Notes)
	enum { IDD = IDD_LENGTHEN };
	CButton	m_run;
	CButton	m_cancel;
	CButton	m_tempo_check;
	CListBox	m_percent_list;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CLengthen_Notes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CLengthen_Notes)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangePercentList();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:

	HPMF_Interface * hpmfi;
	int last_id;
	bool tempo_checked;
	CProgressCtrl m_progressctrl;

private:
	int list_index_selected;
	int progressctrl_upper;
	bool run_done;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_LENGTHEN_NOTES_H__1FA3F23F_B0D1_48D0_BA0D_811C7D7CD115__INCLUDED_
