#if !defined(AFX_ONTROLLER_DLG_H__B41F98F9_AECE_4B1E_8017_909A7F5F9079__INCLUDED_)
#define AFX_ONTROLLER_DLG_H__B41F98F9_AECE_4B1E_8017_909A7F5F9079__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Controller_Dlg.h : Header-Datei
//

#include "HPMF_Interface.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Controller_Dlg 

class Controller_Dlg : public CDialog
{
// Konstruktion
public:
	Controller_Dlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(Controller_Dlg)
	enum { IDD = IDD_CONTROLLER };
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
	CButton	m_cancel;
	CEdit	m_edit_all;
	CEdit	m_edit_v1;
	CEdit	m_edit_v2;
	CEdit	m_edit_v3;
	CEdit	m_edit_v4;
	CEdit	m_edit_v5;
	CEdit	m_edit_v6;
	CEdit	m_edit_v7;
	CEdit	m_edit_v8;
	CEdit	m_edit_v9;
	CEdit	m_edit_v10;
	CEdit	m_edit_v11;
	CEdit	m_edit_v12;
	CEdit	m_edit_v13;
	CEdit	m_edit_v14;
	CEdit	m_edit_v15;
	CEdit	m_edit_v16;
	CComboBox	m_effectcombobox;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Controller_Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung

private:
	CToolTipCtrl* m_pToolTip;
	CEdit	*value[16];
	CEdit   *m_voice_type[16];	
	int		idc_value[16];
	int		idc_voice_type[16]; // voice names
	bool	source_changed;

	void KillfocusEdit(int chan);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	HPMF_Interface * hpmfi;
	HCURSOR hCursorWait;
	HCURSOR hCursorOld;
	
	int		effect_index;
	int		maxvalue[16];
	bool	insert_event[16];
	bool	chan_changed[16];

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Controller_Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeEffectcombobox();
	afx_msg void OnKillfocusEditAll();
	afx_msg void OnKillfocusEditV1();
	afx_msg void OnKillfocusEditV2();
	afx_msg void OnKillfocusEditV3();
	afx_msg void OnKillfocusEditV4();
	afx_msg void OnKillfocusEditV5();
	afx_msg void OnKillfocusEditV6();
	afx_msg void OnKillfocusEditV7();
	afx_msg void OnKillfocusEditV8();
	afx_msg void OnKillfocusEditV9();
	afx_msg void OnKillfocusEditV10();
	afx_msg void OnKillfocusEditV11();
	afx_msg void OnKillfocusEditV12();
	afx_msg void OnKillfocusEditV13();
	afx_msg void OnKillfocusEditV14();
	afx_msg void OnKillfocusEditV15();
	afx_msg void OnKillfocusEditV16();
	afx_msg void OnTakeIt();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void init_data();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_ONTROLLER_DLG_H__B41F98F9_AECE_4B1E_8017_909A7F5F9079__INCLUDED_
