#if !defined(AFX_PLAY_H__13F9BD1B_7BEF_400B_9F82_828AD6AB42F3__INCLUDED_)
#define AFX_PLAY_H__13F9BD1B_7BEF_400B_9F82_828AD6AB42F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Play.h : Header-Datei
//

#include "LyricFrame.h"
#include "MainFunctions.h"

// Play Monitor

class MY_PLAY_MONITOR : public HP_PLAY_MONITOR
{
public:
	void HP_PlayTBMonitor(int takt, int beat);
	void HP_PlayChMonitor(char* chord_text);
	void HP_PlayLyMonitor(char* lyric_text);

	HWND whandle;		// needed to display of takt, beat, chord and lyric
	HPMF_Interface *hpmfi;
	LyricFrame *p_lfr;	// needed to initiate displaying lyrics and chords
	Log *logf;
};

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CPlay 

typedef struct record_chord_lyric_elem
{
	int time;
	CString text;
	unsigned char cr;
	unsigned char ct;
	unsigned char bn;
	unsigned char bt;
} RECORD_CHORD_LYRIC_ELEM;

#define NO_CHORDS_LYRICS 1500


class CPlay : public CDialog
{
// Konstruktion
public:
	CPlay(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CPlay)
	enum { IDD = IDD_PLAY };
	CSliderCtrl	m_slider_volume;
	CEdit	m_v1;
	CEdit	m_v2;
	CEdit	m_v3;
	CEdit	m_v4;
	CEdit	m_v5;
	CEdit	m_v6;
	CEdit	m_v7;
	CEdit	m_v8;
	CEdit	m_v9;
	CEdit	m_v10;
	CEdit	m_v11;
	CEdit	m_v12;
	CEdit	m_v13;
	CEdit	m_v14;
	CEdit	m_v15;
	CEdit	m_v16;
	CEdit	m_slider_time_pos;
	CButton	m_check_eins;
	CButton	m_check_zwei;
	CButton	m_check_drei;
	CButton	m_check_vier;
	CButton	m_check_fuenf;
	CButton	m_check_sechs;
	CButton	m_check_sieben;
	CButton	m_check_acht;
	CButton	m_check_neun;
	CButton	m_check_zehn;
	CButton	m_check_elf;
	CButton	m_check_zwoelf;
	CButton	m_check_dreizehn;
	CButton	m_check_vierzehn;
	CButton	m_check_fuenfzehn;
	CButton	m_check_sechzehn;
	CButton	m_check_play_all;
	CSliderCtrl	m_slider_time;
	CButton	m_insert_chords_lyrics;
	CButton	m_ok;
	CButton	m_record_chords;
	CSliderCtrl	m_slider_transpose;
	CSliderCtrl	m_slider_tempo;
	CButton	m_stop;
	CButton	m_play;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CPlay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
public:
		HPMF_Interface * hpmfi;
		MainFunctions *mainfun;
		HP_MIDIFILE_MODULE* mf;
		MY_PLAY_MONITOR pm;
		Log *logf;
		bool chan_transpose_list[16];
		bool chan_mute_list[16];
		IniFile *o_inifile;

		bool with_lyrics;

		UINT_PTR m_nTimer;
		void Stop();
		LyricFrame m_lfr;

		void prepare_lyrics_chords();
		void print(CString protfile, bool show);
		bool source_changed;
		char linefeed_char;
		RECORD_CHORD_LYRIC_ELEM record_chord_lyric_list[NO_CHORDS_LYRICS];


private:
		void PositWindow(int distance);
		virtual BOOL PreTranslateMessage(LPMSG lpmsg);
		CToolTipCtrl* m_pToolTip;
		CEdit   *m_voice_type[16];	

		bool is_record_prepared;
		bool is_record;
		bool signal_record_text;
		bool is_pause;

		CString record_text;
		CRect record_rect;

		int nTempo;
		void set_play_tempo();
		int nTranspose;
		void set_play_transpose();
		int nVolume;
		void set_play_volume(int volume);
		void set_play_mute();
		bool initialize_recording();
		void check_chan(int chan);
		int new_slider_time;
		int orig_master_volume;
		CButton *check_chan_ctrl[16];
		
		// Dimensions of Karaoke Window
		int posx;
		int posy;
		int lenx;
		int leny;

		HICON hIcon_play;
		HICON hIcon_play_green;
		HICON hIcon_stop;
		HICON hIcon_pause;
		HICON hIcon_pause_green;
		HICON hIcon_record_red;
		HICON hIcon_record_yellow;
		HICON hIcon_record_green;
		HICON hIcon_record_darkgreen;

		int record_chord_lyric_length;
		int act_list_no;

		static const CString start_chordlist;

		bool is_chord_record;
		bool is_lyric_record;
		int idc_voice_type[16];

		bool mega_channel_list[16];


protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CPlay)
	virtual BOOL OnInitDialog();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDefaultTempo();
	afx_msg void OnClose();
	afx_msg void OnDefaultTranspose();
	afx_msg void OnRecordChordsLyrics();
	afx_msg void OnInsertChordsLyrics();
	afx_msg void OnReleasedcaptureSliderTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckEins();
	afx_msg void OnCheckZwei();
	afx_msg void OnCheckDrei();
	afx_msg void OnCheckVier();
	afx_msg void OnCheckFuenf();
	afx_msg void OnCheckSechs();
	afx_msg void OnCheckSieben();
	afx_msg void OnCheckAcht();
	afx_msg void OnCheckNeun();
	afx_msg void OnCheckZehn();
	afx_msg void OnCheckElf();
	afx_msg void OnCheckZwoelf();
	afx_msg void OnCheckDreizehn();
	afx_msg void OnCheckVierzehn();
	afx_msg void OnCheckFuenfzehn();
	afx_msg void OnCheckSechzehn();
	afx_msg void OnCheckPlayAll();
	afx_msg void OnKillFocusSliderTimePos();
	afx_msg void OnReleasedcaptureSliderMasterVolume(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderMasterVolume(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PLAY_H__13F9BD1B_7BEF_400B_9F82_828AD6AB42F3__INCLUDED_
