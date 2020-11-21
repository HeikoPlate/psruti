#if !defined(AFX_DRUMS_H__EDA248E5_6247_40FA_9AD7_5012F7200F9D__INCLUDED_)
#define AFX_DRUMS_H__EDA248E5_6247_40FA_9AD7_5012F7200F9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Drums.h : Header-Datei
//

#include "MainFunctions.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Drums 

class Drums : public CDialog
{
// Konstruktion
public:
	Drums(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(Drums)
	enum { IDD = IDD_DRUMS_DLG };
	CButton	m_drums_dialog;
	CButton	m_drums_batch;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Drums)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Drums)
	afx_msg void OnChangeDrumsDialog();
	afx_msg void OnChangeDrumsBatch();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	CToolTipCtrl* m_pToolTip;

	DECLARE_MESSAGE_MAP()
	BOOL Drums::PreTranslateMessage(MSG* pMSG);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DRUMS_H__EDA248E5_6247_40FA_9AD7_5012F7200F9D__INCLUDED_
