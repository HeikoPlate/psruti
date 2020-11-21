#if !defined(AFX_STARTBEAT_H__A9051B9E_C9E9_40B8_BC60_446C2FEEC9A0__INCLUDED_)
#define AFX_STARTBEAT_H__A9051B9E_C9E9_40B8_BC60_446C2FEEC9A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StartBeat.h : Header-Datei
//

#define NO_DRUMS 72
#define FIRST_DRUM 13

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld StartBeat 

class StartBeat : public CDialog
{
// Konstruktion
public:
	StartBeat(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(StartBeat)
	enum { IDD = IDD_START_BEAT };
	CButton	m_check_one_measure;
	CButton	m_check_all_beats;
	CComboBox	m_drum;
	CEdit	m_start_beat_vel;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(StartBeat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung

public:
	
	bool start_beat_delete;
	bool on_all_beats;
	bool only_one_measure;
	int get_drum();
	int get_velocity();
	void set_velocity(int vel);
	void set_drum(int note);
	HPMF_Interface * hpmfi;

private:
	int drum;
	int velocity;
	static const char* drums[NO_DRUMS+1];

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(StartBeat)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeStartBeatVel();
	afx_msg void OnCheckAllBeats();
	virtual void OnCancel();
	afx_msg void OnCheckOneMeasure();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_STARTBEAT_H__A9051B9E_C9E9_40B8_BC60_446C2FEEC9A0__INCLUDED_
