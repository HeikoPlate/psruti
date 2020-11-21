#if !defined(AFX_QUANTISIZECHORDS_H__447CFD37_2B94_400C_ACAC_9B10FF4DC7F0__INCLUDED_)
#define AFX_QUANTISIZECHORDS_H__447CFD37_2B94_400C_ACAC_9B10FF4DC7F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QuantisizeChords.h : Header-Datei
//

#include "HPMF_Interface.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld QuantisizeChords 

class QuantisizeChords : public CDialog
{
// Konstruktion
public:
	QuantisizeChords(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(QuantisizeChords)
	enum { IDD = IDD_QUANTISIZE_CHORDS };
	CButton	m_beat1_quantisize;
	CButton	m_beat_1_3_quantisize;
	CButton	m_beat_all_quantisize;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(QuantisizeChords)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung

public:
	int get_beat_resolution();

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(QuantisizeChords)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnBeat1Quantisize();
	afx_msg void OnBeat13Quantisize();
	afx_msg void OnBeatAllQuantisize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int beat_resolution; // BEAT_RESOLUTION_1: Beat1,
						 //	BEAT_RESOLUTION_13: Beat 1,3,5..., 
						 // BEAT_RESOLUTION_ALL: All Beats
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_QUANTISIZECHORDS_H__447CFD37_2B94_400C_ACAC_9B10FF4DC7F0__INCLUDED_
