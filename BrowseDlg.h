#if !defined(AFX_BROWSEDLG_H__33D64F86_1D6F_414E_949E_32406960D533__INCLUDED_)
#define AFX_BROWSEDLG_H__33D64F86_1D6F_414E_949E_32406960D533__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BrowseDlg.h : Header-Datei
//

#include "HP_midifile.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld BrowseDlg 

class BrowseDlg : public CDialog
{
// Konstruktion
public:
	BrowseDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(BrowseDlg)
	enum { IDD = IDD_BROWSE };
	CEdit	m_search_string;
	CListBox	m_browse_list;
	CButton	m_ok;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(BrowseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung

public:
	HPMF_Interface * hpmfi;
	int chan;
	char bank_name[64];
	long bank_no;
	char voice_name[64];
	long voice_no;

private:
	HP_CWBANKVOICE *bank_voice_list;
	long bank_voice_list_len;
	char search_string[64];
	int browse_list_index;
	void DisplayVoices();

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(BrowseDlg)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeBrowseList();
	afx_msg void OnUpdateSearchString();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_BROWSEDLG_H__33D64F86_1D6F_414E_949E_32406960D533__INCLUDED_
