#if !defined(AFX_LICKCHANDLG_H__1BEB66E4_B088_49F8_B1BB_45303871383C__INCLUDED_)
#define AFX_LICKCHANDLG_H__1BEB66E4_B088_49F8_B1BB_45303871383C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClickChanDlg.h : Header-Datei
//

#include "IniFile.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld ClickChanDlg 

class ClickChanDlg : public CDialog
{
// Konstruktion
public:
	ClickChanDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(ClickChanDlg)
	enum { IDD = IDD_CLICK_CHAN };
	CComboBox	m_beat_drum_combo;
	CEdit	m_drum_mainvolume;
	CComboBox	m_measure_drum_combo;
	CEdit	m_measure_drum_velocity;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(ClickChanDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(ClickChanDlg)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeDrumMainvolume();
	afx_msg void OnChangeMeasureDrumVelocity();
	afx_msg void OnChangeBeatDrumVelocity();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int main_vol_chan10;
	int noteval_meas;
	int vel_meas;
	int noteval_beat;
	int vel_beat;
	IniFile *o_inifile;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_LICKCHANDLG_H__1BEB66E4_B088_49F8_B1BB_45303871383C__INCLUDED_
