#if !defined(AFX_DELETE_SHORT_NOTES_H__30B5D9DA_A145_4C68_A4AD_DB4310AD761D__INCLUDED_)
#define AFX_DELETE_SHORT_NOTES_H__30B5D9DA_A145_4C68_A4AD_DB4310AD761D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Delete_short_notes.h : Header-Datei
//

#include "HPMF_Interface.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Delete_short_notes 

class Delete_short_notes : public CDialog
{
// Konstruktion
public:
	Delete_short_notes(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(Delete_short_notes)
	enum { IDD = IDD_DELETE_SHORT_NOTES };
	CButton	m_check_all;
	CEdit	m_v_voice1;
	CEdit	m_v_voice2;
	CEdit	m_v_voice3;
	CEdit	m_v_voice4;
	CEdit	m_v_voice5;
	CEdit	m_v_voice6;
	CEdit	m_v_voice7;
	CEdit	m_v_voice8;
	CEdit	m_v_voice9;
	CEdit	m_v_voice10;
	CEdit	m_v_voice11;
	CEdit	m_v_voice12;
	CEdit	m_v_voice13;
	CEdit	m_v_voice14;
	CEdit	m_v_voice15;
	CEdit	m_v_voice16;
	CEdit	m_ticks;
	CButton	m_check1;
	CButton	m_check2;
	CButton	m_check3;
	CButton	m_check4;
	CButton	m_check5;
	CButton	m_check6;
	CButton	m_check7;
	CButton	m_check8;
	CButton	m_check9;
	CButton	m_check10;
	CButton	m_check11;
	CButton	m_check12;
	CButton	m_check13;
	CButton	m_check14;
	CButton	m_check15;
	CButton	m_check16;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Delete_short_notes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Delete_short_notes)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnChangeUptoTick();
	afx_msg void OnClose();
	afx_msg void OnCheckAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	HPMF_Interface *hpmfi;
	int upto_tick;
	int chan_list[16]; // -1 not allowed, 0 not selected, 1 selected
private:
	CToolTipCtrl* m_pToolTip;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int		idc_voice_type[16]; // voice names
	CButton *checklist[16];
	CEdit   *m_voice_type[16];	
	int idclist_length[16];
	int min_note_length[16];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DELETE_SHORT_NOTES_H__30B5D9DA_A145_4C68_A4AD_DB4310AD761D__INCLUDED_
