#if !defined(AFX_VHACTDEACTDLG_H__EC79314D_6F5B_4D5C_A458_85112F92DC8A__INCLUDED_)
#define AFX_VHACTDEACTDLG_H__EC79314D_6F5B_4D5C_A458_85112F92DC8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VhActDeactDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld VhActDeactDlg 

class VhActDeactDlg : public CDialog
{
// Konstruktion
public:
	VhActDeactDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(VhActDeactDlg)
	enum { IDD = IDD_VH_ACT_DEACT };
	CListBox	m_channel_list;
	CButton	m_select;
	CButton	m_deselect;
	CButton	m_vh_deact;
	CButton	m_vh_act;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(VhActDeactDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(VhActDeactDlg)
	afx_msg void OnVhActCheck();
	afx_msg void OnVhDeactCheck();
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelect();
	afx_msg void OnDeselect();
	afx_msg void OnSelchangeChannelList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int channel_index_list[16];
	int vh_deact;

public:
	bool vh_select;
	bool vh_deselect;
	int vh_act;
	int vh_channel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_VHACTDEACTDLG_H__EC79314D_6F5B_4D5C_A458_85112F92DC8A__INCLUDED_
