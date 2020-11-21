#if !defined(AFX_CONTROLLEREFFECTSDLG_H__499603DE_81A9_4620_ACEA_4F65C391CAC2__INCLUDED_)
#define AFX_CONTROLLEREFFECTSDLG_H__499603DE_81A9_4620_ACEA_4F65C391CAC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ControllerEffectsDlg.h : Header-Datei
//
#include "HPMF_Interface.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CControllerEffectsDlg 

class CControllerEffectsDlg : public CDialog
{
// Konstruktion
public:
	CControllerEffectsDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CControllerEffectsDlg)
	enum { IDD = IDD_CONTROLLER_EFFECTS };
	CButton	m_effects;
	CButton	m_controller;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CControllerEffectsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CControllerEffectsDlg)
	afx_msg void OnSelectController();
	afx_msg void OnSelectEffects();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CToolTipCtrl m_pToolTip;
	virtual BOOL PreTranslateMessage(MSG* pMSG);

public:
	HPMF_Interface * hpmfi;
	HCURSOR hCursorWait;
	HCURSOR hCursorOld;
	bool source_changed;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_CONTROLLEREFFECTSDLG_H__499603DE_81A9_4620_ACEA_4F65C391CAC2__INCLUDED_
