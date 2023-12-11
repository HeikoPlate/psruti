#if !defined(AFX_SYSEXDLG_H__1BF79A81_1C9D_4CDF_B28A_705440F5CFE7__INCLUDED_)
#define AFX_SYSEXDLG_H__1BF79A81_1C9D_4CDF_B28A_705440F5CFE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SysexDlg.h : Header-Datei
//
// #include "resource.h"
// #include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSysexDlg 

class CSysexDlg : public CDialog
{
// Konstruktion
public:
	CSysexDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CSysexDlg)
	enum { IDD = IDD_SYSEX_IMPORT_EXPORT_DLG };
	CButton	m_mbt_check;
	CButton	m_check_read_note_area;
	CEdit	m_tick;
	CEdit	m_measure;
	CEdit	m_beat;
	CButton	m_check_position;
	CButton	m_select_sysex_paste_import_check;
	CButton	m_sysex_delete_check;
	CButton	m_select_sysex_file_import_check;
	CButton	m_select_sysex_export_check;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CSysexDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
public:
	HPMF_Interface * hpmfi;
	bool selected_file_import();
	bool selected_paste_import();
	bool selected_export();
	bool with_delete();
	bool selected_note_area();
	void new_position(bool *with_mbt, int *measure,int *beat,int *tick);
	CString get_protfile();

private:
	int measure_first_note, beat_first_note, tick_first_note, time_first_note;

	bool import_file_selected;
	bool import_paste_selected;
	bool export_selected;
	bool is_delete;
	bool is_note_area;
	bool is_mbt;
	CString protfile;
	CString SelectSysexFile();
	void display_measure_beat_tick(int measure, int beat, int tick);
	void display_measure_beat_tick_with_blanks();
	IniFile *p_inifile;
	int new_meas;
	int new_bea;
	int new_tic;
	Log *logf;
	bool no_on_update_measure_beat_tick;

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CSysexDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelectSysexFileImportCheck();
	afx_msg void OnSelectSysexExportCheck();
	afx_msg void OnSysexDeleteCheck();
	afx_msg void OnSelectSysexPasteImportCheck();
	afx_msg void OnCheckPosition();
	afx_msg void OnUpdateMeasure();
	afx_msg void OnUpdateBeat();
	afx_msg void OnUpdateTick();
	afx_msg void OnCheckReadNoteArea();
	afx_msg void OnMbtCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SYSEXDLG_H__1BF79A81_1C9D_4CDF_B28A_705440F5CFE7__INCLUDED_
