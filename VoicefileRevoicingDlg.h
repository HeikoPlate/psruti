#if !defined(AFX_VOICEFILEREVOICINGDLG_H__8F76BB59_4EF5_432C_B2FA_26E0E3377A99__INCLUDED_)
#define AFX_VOICEFILEREVOICINGDLG_H__8F76BB59_4EF5_432C_B2FA_26E0E3377A99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VoicefileRevoicingDlg.h : Header-Datei
//

#include "IniFile.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld VoicefileRevoicingDlg 

class VoicefileRevoicingDlg : public CDialog
{
// Konstruktion
public:
	VoicefileRevoicingDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(VoicefileRevoicingDlg)
	enum { IDD = IDD_VOICEFILE_REVOICING };
	CButton	m_ok;
	CButton	m_cancel;
	CButton	m_test_chan1;
	CButton	m_test_chan2;
	CButton	m_test_chan3;
	CButton	m_test_chan4;
	CButton	m_test_chan5;
	CButton	m_test_chan6;
	CButton	m_test_chan7;
	CButton	m_test_chan8;
	CButton	m_test_chan9;
	CButton	m_test_chan10;
	CButton	m_test_chan11;
	CButton	m_test_chan12;
	CButton	m_test_chan13;
	CButton	m_test_chan14;
	CButton	m_test_chan15;
	CButton	m_test_chan16;	
	CEdit	m_voicename1;
	CEdit	m_voicename2;
	CEdit	m_voicename3;
	CEdit	m_voicename4;
	CEdit	m_voicename5;
	CEdit	m_voicename6;
	CEdit	m_voicename7;
	CEdit	m_voicename8;
	CEdit	m_voicename9;
	CEdit	m_voicename10;
	CEdit	m_voicename11;
	CEdit	m_voicename12;
	CEdit	m_voicename13;
	CEdit	m_voicename14;
	CEdit	m_voicename15;
	CEdit	m_voicename16;	
	CEdit	m_block_chan1;
	CEdit	m_block_chan2;
	CEdit	m_block_chan3;
	CEdit	m_block_chan4;
	CEdit	m_block_chan5;
	CEdit	m_block_chan6;
	CEdit	m_block_chan7;
	CEdit	m_block_chan8;
	CEdit	m_block_chan9;
	CEdit	m_block_chan10;
	CEdit	m_block_chan11;
	CEdit	m_block_chan12;
	CEdit	m_block_chan13;
	CEdit	m_block_chan14;
	CEdit	m_block_chan15;
	CEdit	m_block_chan16;
	CButton	m_ctrl1;
	CButton	m_ctrl2;
	CButton	m_ctrl3;
	CButton	m_ctrl4;
	CButton	m_ctrl5;
	CButton	m_ctrl6;
	CButton	m_ctrl7;
	CButton	m_ctrl8;
	CButton	m_ctrl9;
	CButton	m_ctrl10;
	CButton	m_ctrl11;
	CButton	m_ctrl12;
	CButton	m_ctrl13;
	CButton	m_ctrl14;
	CButton	m_ctrl15;
	CButton	m_ctrl16;
	CButton	m_revoice1;
	CButton	m_revoice2;
	CButton	m_revoice3;
	CButton	m_revoice4;
	CButton	m_revoice5;
	CButton	m_revoice6;
	CButton	m_revoice7;
	CButton	m_revoice8;
	CButton	m_revoice9;
	CButton	m_revoice10;
	CButton	m_revoice11;
	CButton	m_revoice12;
	CButton	m_revoice13;
	CButton	m_revoice14;
	CButton	m_revoice15;
	CButton	m_revoice16;
	CEdit	m_bankno1;
	CEdit	m_voiceno1;
	CEdit	m_bankno2;
	CEdit	m_voiceno2;
	CEdit	m_bankno3;
	CEdit	m_voiceno3;
	CEdit	m_bankno4;
	CEdit	m_voiceno4;
	CEdit	m_bankno5;
	CEdit	m_voiceno5;
	CEdit	m_bankno6;
	CEdit	m_voiceno6;
	CEdit	m_bankno7;
	CEdit	m_voiceno7;
	CEdit	m_bankno8;
	CEdit	m_voiceno8;
	CEdit	m_bankno9;
	CEdit	m_voiceno9;
	CEdit	m_bankno10;
	CEdit	m_voiceno10;
	CEdit	m_bankno11;
	CEdit	m_voiceno11;
	CEdit	m_bankno12;
	CEdit	m_voiceno12;
	CEdit	m_bankno13;
	CEdit	m_voiceno13;
	CEdit	m_bankno14;
	CEdit	m_voiceno14;
	CEdit	m_bankno15;
	CEdit	m_voiceno15;
	CEdit	m_bankno16;
	CEdit	m_voiceno16;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(VoicefileRevoicingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(VoicefileRevoicingDlg)
	afx_msg void OnRevoice1();
	afx_msg void OnRevoice2();
	afx_msg void OnRevoice3();
	afx_msg void OnRevoice4();
	afx_msg void OnRevoice5();
	afx_msg void OnRevoice6();
	afx_msg void OnRevoice7();
	afx_msg void OnRevoice8();
	afx_msg void OnRevoice9();
	afx_msg void OnRevoice10();
	afx_msg void OnRevoice11();
	afx_msg void OnRevoice12();
	afx_msg void OnRevoice13();
	afx_msg void OnRevoice14();
	afx_msg void OnRevoice15();
	afx_msg void OnRevoice16();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnTestChan1();
	afx_msg void OnTestChan2();
	afx_msg void OnTestChan3();
	afx_msg void OnTestChan4();
	afx_msg void OnTestChan5();
	afx_msg void OnTestChan6();
	afx_msg void OnTestChan7();
	afx_msg void OnTestChan8();
	afx_msg void OnTestChan9();
	afx_msg void OnTestChan10();
	afx_msg void OnTestChan11();
	afx_msg void OnTestChan12();
	afx_msg void OnTestChan13();
	afx_msg void OnTestChan14();
	afx_msg void OnTestChan15();
	afx_msg void OnTestChan16();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:

	void get_init_data();
	void revoice(int chan);
	void voicetest(int voice_chan);
	void set_voicenames();
	void add_insertions_play(HP_MIDIFILE_MODULE* mf_voice, int voice_chan);
	void add_multipart_play(HP_MIDIFILE_MODULE* mf_voice, int voice_chan);
	void add_standard_drum_sysex_play(HP_MIDIFILE_MODULE* mf_voice);
	void ctrl(int chan);

	long bankno_idlist[16];
	CEdit *bankno_list[16];
	
	long voiceno_idlist[16];
	CEdit *voiceno_list[16];

	long voicename_idlist[16];
	CEdit *voicename_list[16];
	
	CButton *revoice_list[16];
	
	CButton *ctrl_list[16];

	CButton *testchan_list[16];
	int act_testchan;
	
	long block_idlist[16];
	CEdit *block_list[16];
	
	int external_blocklist[16];
	int internal_blocklist[16];

	// voiceplay data
	HP_MIDIFILE_MODULE* mf_voiceplay_melody;	// starts a MIDI-file session
	HP_MIDIFILE_MODULE* mf_voiceplay_drum;	    // starts a MIDI-file session
	int time_first_playnote; 
	int time_first_play_effect_event;
	int act_effect_event_time;

public:
	IniFile *p_inifile;
	HPMF_Interface *hpmfi;
	HCURSOR hCursorOld;
	HCURSOR hCursorWait;
	VOICELIST_ELEM voicelist[16];
	VoiceFilePathElement voicefilepath_list[16];
	UINT_PTR m_nTimer;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_VOICEFILEREVOICINGDLG_H__8F76BB59_4EF5_432C_B2FA_26E0E3377A99__INCLUDED_
