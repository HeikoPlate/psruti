#if !defined(AFX_REVOICINGDLG_H__73582D39_8C5B_4F3A_B359_EE11428D5890__INCLUDED_)
#define AFX_REVOICINGDLG_H__73582D39_8C5B_4F3A_B359_EE11428D5890__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RevoicingDlg.h : Header-Datei
//

#include "IniFile.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld RevoicingDlg 

class RevoicingDlg : public CDialog
{
// Konstruktion
public:
	RevoicingDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(RevoicingDlg)
	enum { IDD = IDD_REVOICING };
	CButton	m_cancel;
	CButton	m_ok;
	CButton	m_voice_browse1;
	CButton	m_voice_browse2;
	CButton	m_voice_browse3;
	CButton	m_voice_browse4;
	CButton	m_voice_browse5;
	CButton	m_voice_browse6;
	CButton	m_voice_browse7;
	CButton	m_voice_browse8;
	CButton	m_voice_browse9;
	CButton	m_voice_browse10;
	CButton	m_voice_browse11;
	CButton	m_voice_browse12;
	CButton	m_voice_browse13;
	CButton	m_voice_browse14;
	CButton	m_voice_browse15;
	CButton	m_voice_browse16;
	CButton	m_voice_test1;
	CButton	m_voice_test2;
	CButton	m_voice_test3;
	CButton	m_voice_test4;
	CButton	m_voice_test5;
	CButton	m_voice_test6;
	CButton	m_voice_test7;
	CButton	m_voice_test8;
	CButton	m_voice_test9;
	CButton	m_voice_test10;
	CButton	m_voice_test11;
	CButton	m_voice_test12;
	CButton	m_voice_test13;
	CButton	m_voice_test14;
	CButton	m_voice_test15;
	CButton	m_voice_test16;
	CEdit	m_bankno1;
	CEdit	m_voiceno1;
	CComboBox	m_bankname1;
	CComboBox	m_voicename1;
	CEdit	m_bankno2;
	CEdit	m_voiceno2;
	CComboBox	m_bankname2;
	CComboBox	m_voicename2;
	CEdit	m_bankno3;
	CEdit	m_voiceno3;
	CComboBox	m_bankname3;
	CComboBox	m_voicename3;
	CEdit	m_bankno4;
	CEdit	m_voiceno4;
	CComboBox	m_bankname4;
	CComboBox	m_voicename4;
	CEdit	m_bankno5;
	CEdit	m_voiceno5;
	CComboBox	m_bankname5;
	CComboBox	m_voicename5;
	CEdit	m_bankno6;
	CEdit	m_voiceno6;
	CComboBox	m_bankname6;
	CComboBox	m_voicename6;
	CEdit	m_bankno7;
	CEdit	m_voiceno7;
	CComboBox	m_bankname7;
	CComboBox	m_voicename7;
	CEdit	m_bankno8;
	CEdit	m_voiceno8;
	CComboBox	m_bankname8;
	CComboBox	m_voicename8;
	CEdit	m_bankno9;
	CEdit	m_voiceno9;
	CComboBox	m_bankname9;
	CComboBox	m_voicename9;
	CEdit	m_bankno10;
	CEdit	m_voiceno10;
	CComboBox	m_bankname10;
	CComboBox	m_voicename10;
	CEdit	m_bankno11;
	CEdit	m_voiceno11;
	CComboBox	m_bankname11;
	CComboBox	m_voicename11;
	CEdit	m_bankno12;
	CEdit	m_voiceno12;
	CComboBox	m_bankname12;
	CComboBox	m_voicename12;
	CEdit	m_bankno13;
	CEdit	m_voiceno13;
	CComboBox	m_bankname13;
	CComboBox	m_voicename13;
	CEdit	m_bankno14;
	CEdit	m_voiceno14;
	CComboBox	m_bankname14;
	CComboBox	m_voicename14;
	CEdit	m_bankno15;
	CEdit	m_voiceno15;
	CComboBox	m_bankname15;
	CComboBox	m_voicename15;
	CEdit	m_bankno16;
	CEdit	m_voiceno16;
	CComboBox	m_bankname16;
	CComboBox	m_voicename16;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(RevoicingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
public:
	IniFile *p_inifile;
	HPMF_Interface * hpmfi;
	HCURSOR hCursorOld;
	HCURSOR hCursorWait;
	VOICELIST_ELEM voicelist[16];

	HP_MIDIFILE_MODULE* mf_voiceplay_melody;	// starts a MIDI-file session
	HP_MIDIFILE_MODULE* mf_voiceplay_drum;	// starts a MIDI-file session
	UINT_PTR m_nTimer;

private:
	CToolTipCtrl* m_pToolTip;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void get_init_data();
	void set_banknames(int chan);
	void set_voicenames(unsigned long bank, int chan);
	void ChangeBankno(int chan);
	void ChangeVoiceno(int chan);
	void SelchangeBankname(int chan);
	void SelchangeVoicename(int chan);
	void VoiceBrowse(int chan);
	void VoiceTest(int chan);
	long bankno_idlist[16];
	CEdit *bankno_list[16];
	CComboBox *banknamelist[16];
	long voiceno_idlist[16];
	CEdit *voiceno_list[16];
	CButton *browse_list[16];
	CButton *test_list[16];
	CComboBox *voicenamelist[16];
	HP_CWVOICE *voices;

//	BANK_VOICES_ELEM bank_voices_list[128];
//	int bank_voices_list_free;

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(RevoicingDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeBankname1();
	afx_msg void OnSelchangeBankname2();
	afx_msg void OnSelchangeBankname3();
	afx_msg void OnSelchangeBankname4();
	afx_msg void OnSelchangeBankname5();
	afx_msg void OnSelchangeBankname6();
	afx_msg void OnSelchangeBankname7();
	afx_msg void OnSelchangeBankname8();
	afx_msg void OnSelchangeBankname9();
	afx_msg void OnSelchangeBankname10();
	afx_msg void OnSelchangeBankname11();
	afx_msg void OnSelchangeBankname12();
	afx_msg void OnSelchangeBankname13();
	afx_msg void OnSelchangeBankname14();
	afx_msg void OnSelchangeBankname15();
	afx_msg void OnSelchangeBankname16();
	afx_msg void OnSelchangeVoicename1();
	afx_msg void OnSelchangeVoicename2();
	afx_msg void OnSelchangeVoicename3();
	afx_msg void OnSelchangeVoicename4();
	afx_msg void OnSelchangeVoicename5();
	afx_msg void OnSelchangeVoicename6();
	afx_msg void OnSelchangeVoicename7();
	afx_msg void OnSelchangeVoicename8();
	afx_msg void OnSelchangeVoicename9();
	afx_msg void OnSelchangeVoicename10();
	afx_msg void OnSelchangeVoicename11();
	afx_msg void OnSelchangeVoicename12();
	afx_msg void OnSelchangeVoicename13();
	afx_msg void OnSelchangeVoicename14();
	afx_msg void OnSelchangeVoicename15();
	afx_msg void OnSelchangeVoicename16();
	afx_msg void OnChangeBankno1();
	afx_msg void OnChangeBankno2();
	afx_msg void OnChangeBankno3();
	afx_msg void OnChangeBankno4();
	afx_msg void OnChangeBankno5();
	afx_msg void OnChangeBankno6();
	afx_msg void OnChangeBankno7();
	afx_msg void OnChangeBankno8();
	afx_msg void OnChangeBankno9();
	afx_msg void OnChangeBankno10();
	afx_msg void OnChangeBankno11();
	afx_msg void OnChangeBankno12();
	afx_msg void OnChangeBankno13();
	afx_msg void OnChangeBankno14();
	afx_msg void OnChangeBankno15();
	afx_msg void OnChangeBankno16();
	afx_msg void OnChangeVoiceno1();
	afx_msg void OnChangeVoiceno2();
	afx_msg void OnChangeVoiceno3();
	afx_msg void OnChangeVoiceno4();
	afx_msg void OnChangeVoiceno5();
	afx_msg void OnChangeVoiceno6();
	afx_msg void OnChangeVoiceno7();
	afx_msg void OnChangeVoiceno8();
	afx_msg void OnChangeVoiceno9();
	afx_msg void OnChangeVoiceno10();
	afx_msg void OnChangeVoiceno11();
	afx_msg void OnChangeVoiceno12();
	afx_msg void OnChangeVoiceno13();
	afx_msg void OnChangeVoiceno14();
	afx_msg void OnChangeVoiceno15();
	afx_msg void OnChangeVoiceno16();
	afx_msg void OnVoiceBrowse1();
	afx_msg void OnVoiceBrowse2();
	afx_msg void OnVoiceBrowse3();
	afx_msg void OnVoiceBrowse4();
	afx_msg void OnVoiceBrowse5();
	afx_msg void OnVoiceBrowse6();
	afx_msg void OnVoiceBrowse7();
	afx_msg void OnVoiceBrowse8();
	afx_msg void OnVoiceBrowse9();
	afx_msg void OnVoiceBrowse10();
	afx_msg void OnVoiceBrowse11();
	afx_msg void OnVoiceBrowse12();
	afx_msg void OnVoiceBrowse13();
	afx_msg void OnVoiceBrowse14();
	afx_msg void OnVoiceBrowse15();
	afx_msg void OnVoiceBrowse16();
	afx_msg void OnVoiceTest1();
	afx_msg void OnVoiceTest2();
	afx_msg void OnVoiceTest3();
	afx_msg void OnVoiceTest4();
	afx_msg void OnVoiceTest5();
	afx_msg void OnVoiceTest6();
	afx_msg void OnVoiceTest7();
	afx_msg void OnVoiceTest8();
	afx_msg void OnVoiceTest9();
	afx_msg void OnVoiceTest10();
	afx_msg void OnVoiceTest11();
	afx_msg void OnVoiceTest12();
	afx_msg void OnVoiceTest13();
	afx_msg void OnVoiceTest14();
	afx_msg void OnVoiceTest15();
	afx_msg void OnVoiceTest16();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_REVOICINGDLG_H__73582D39_8C5B_4F3A_B359_EE11428D5890__INCLUDED_
