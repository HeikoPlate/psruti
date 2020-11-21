#if !defined(AFX_VOICEFILEBROWSEDLG_H__8F847880_58AB_4F5A_B405_E9909A55D1F6__INCLUDED_)
#define AFX_VOICEFILEBROWSEDLG_H__8F847880_58AB_4F5A_B405_E9909A55D1F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VoiceFileBrowseDlg.h : Header-Datei
//

#include "IniFile.h"
#include "MyArrays.h"
#include <direct.h>

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld VoiceFileBrowseDlg 

class VoiceFileBrowseDlg : public CDialog
{

typedef struct rvc_ext_ele
{
	char extension[20];
	char voice_attribute[20];
} RVC_EXT_ELE;

// Konstruktion
public:
	VoiceFileBrowseDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(VoiceFileBrowseDlg)
	enum { IDD = IDD_VOICEFILE_BROWSE };
	CListBox	m_block_list;
	CEdit	m_search_strg;
	CListBox	m_browse_list;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(VoiceFileBrowseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(VoiceFileBrowseDlg)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectFolder();
	afx_msg void OnUpdateSearchStrg();
	afx_msg void OnSelchangeBrowseList();
	afx_msg void OnSelchangeBlockList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString voicefile_folder;
	void display_folder(CString long_folder);
	void rvc_fill_voicename_lists(CString voicefile_folder);
	void display_voices();


	static const RVC_EXT_ELE rvc_extension_list[];
	static const int rvc_extension_list_len;

	VoiceArray *rvc_all_voicenames;
	VoiceArray *rvc_act_voicenames;



public:
	HPMF_Interface *hpmfi;
	int chan;
	IniFile *p_inifile;
	// after revoicing:
	CString voicename;
	CString voicefile_path;
	int block;
	int blocklist[16];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_VOICEFILEBROWSEDLG_H__8F847880_58AB_4F5A_B405_E9909A55D1F6__INCLUDED_
