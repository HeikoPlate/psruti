#if !defined(AFX_VOLUMEMETHODDLG_H__5DAC8ADF_9EC1_4EC0_AECD_3CF4762B010C__INCLUDED_)
#define AFX_VOLUMEMETHODDLG_H__5DAC8ADF_9EC1_4EC0_AECD_3CF4762B010C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VolumeMethodDlg.h : Header-Datei
//

#include "HPMF_Interface.h"
#include "Master_Volume_Folder_Dlg.h"
#include "MainVolume_Expression_Folder_Dlg.h"
#include "Inifile.h"
#include "Log.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld VolumeMethodDlg 

class VolumeMethodDlg : public CDialog
{
// Konstruktion
public:
	VolumeMethodDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(VolumeMethodDlg)
	enum { IDD = IDD_VOLUME_METHOD };
	CButton	m_expression_mainvolume;
	CButton	m_master_volume;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(VolumeMethodDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(VolumeMethodDlg)
	afx_msg void OnExpressionMainvolume();
	afx_msg void OnMasterVolume();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	MainFunctions *mainfun;
	HPMF_Interface *hpmfi;
	HCURSOR hCursorOld;
	HCURSOR hCursorWait;
	IniFile *o_inifile;
	Log *lf;

private:
	void GoBackOK();
	CToolTipCtrl m_pToolTip;
	virtual BOOL PreTranslateMessage(MSG* pMSG);

	HANDLE hThread;
	DWORD threadID;
	bool batch_running;
	void mini_initialize_source();
	char sourcefile[MAX_PATH+512];
	char destfile[MAX_PATH+512];

	Master_Volume_Folder_Dlg *master_volume_dlg;
	bool master_volume_folder_running;
	bool master_volume_folder_abort_wanted;
	static DWORD master_volume_thread_run(VolumeMethodDlg *this_thread);
	void master_volume_folder();
	void master_volume_folder_file(CString midifile,CString dest_path,int master_volume_val);

	MainVolume_Expression_Folder_Dlg *mainvolume_expression_dlg;
	bool mainvolume_expression_folder_running;
	bool mainvolume_expression_abort_wanted;
	static DWORD mainvolume_expression_thread_run(VolumeMethodDlg *this_thread);
	void mainvolume_expression_folder();
	void mainvolume_expression_folder_file(CString midifile,CString dest_path,bool mainvolume_to_expression);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_VOLUMEMETHODDLG_H__5DAC8ADF_9EC1_4EC0_AECD_3CF4762B010C__INCLUDED_
