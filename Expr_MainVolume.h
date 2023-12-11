#if !defined(AFX_EXPR_MAINVOLUME_H__A3DB9212_A90A_4599_9B2B_AD83C934144F__INCLUDED_)
#define AFX_EXPR_MAINVOLUME_H__A3DB9212_A90A_4599_9B2B_AD83C934144F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Expr_MainVolume.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Expr_MainVolume 

class Expr_MainVolume : public CDialog
{
// Konstruktion
public:
	Expr_MainVolume(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(Expr_MainVolume)
	enum { IDD = IDD_EXPR_MVOLUME };
	CButton	m_to_mvolume;
	CButton	m_to_expression;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Expr_MainVolume)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
public:

	bool change_to_mvolume();

private:
	bool is_change_to_mvolume;

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Expr_MainVolume)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeToMvolume();
	afx_msg void OnChangeToExpression();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_EXPR_MAINVOLUME_H__A3DB9212_A90A_4599_9B2B_AD83C934144F__INCLUDED_
