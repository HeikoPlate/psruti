#if !defined(AFX_TEMPO_DLG_H__6775E14B_8F30_4959_AEA0_D7C8DC66E203__INCLUDED_)
#define AFX_TEMPO_DLG_H__6775E14B_8F30_4959_AEA0_D7C8DC66E203__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Tempo_Dlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Tempo_Dlg 

class Tempo_Dlg : public CDialog
{
// Konstruktion
public:
	Tempo_Dlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(Tempo_Dlg)
	enum { IDD = IDD_TEMPO };
	CEdit	m_edit_tempo;
	CEdit	m_edit_percent;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Tempo_Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung

public:
	double max_tempo;
	double get_tempo();

private:
	double edit_max_tempo_val;

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Tempo_Dlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnTakeIt();
	afx_msg void OnKillfocusEditTempo();
	afx_msg void OnKillfocusEditPercent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_TEMPO_DLG_H__6775E14B_8F30_4959_AEA0_D7C8DC66E203__INCLUDED_
