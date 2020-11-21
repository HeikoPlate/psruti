// psrutiDlg.h : Header-Datei
//

#if !defined(AFX_PSRMIDIDLG_H__F24E2687_C3E6_11D5_9348_0080AD7896CF__INCLUDED_)
#define AFX_PSRMIDIDLG_H__F24E2687_C3E6_11D5_9348_0080AD7896CF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "HPMF_Interface.h"
#include "MainFunctions.h"
#include "HP_midifile.h" 
#include "my_play_monitor.h"
#include "StartBeatFolderDlg.h"
#include "FillLyricMethodDlg.h"
#include "Play.h"
#include "MyArrays.h" // used for Score

// class CPsrutiDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CPsrutiDlg Dialogfeld

class CPsrutiDlg : public CDialog,MainFunctions
{
	DECLARE_DYNAMIC(CPsrutiDlg);
//	friend class CPsrutiDlgAutoProxy;
public:
	HPMF_Interface  *hpmfi;	// psruti-functions with interface to HP MIDIFILE
	HPMF_Interface  *hpmfi_save; // for saving last state
	CString language;
private:
	bool source_changed;
	void analyse_changes();

	CPlay *pdlg;
	CToolTipCtrl* m_pToolTip;
	virtual BOOL PreTranslateMessage(MSG* pMSG);
	void Stop();
	HPMF_Interface* Selectsource();

	void save_state();		// save hpmfi to hpmfi_save
	void restore_state();	// restore hpmfi from hpmfi_save
	void free_saved_state();// deletes saved state

	bool chords_print;		 // print chords wanted
	bool chords_print_lyric; // print chords as lyrics wanted
	bool chords_save;		 // chords to be saved wanted

	// Thread-function: Run xg_optimize_folder and revoicefile_folder
	static DWORD xg_convert_thread_run(CPsrutiDlg *this_thread); 
	static DWORD gm_convert_thread_run(CPsrutiDlg *this_thread); 
	static DWORD revoicefile_thread_run(CPsrutiDlg *this_thread); 
	static DWORD drum_thread_run(CPsrutiDlg *this_thread);	
	static DWORD print_thread_run(CPsrutiDlg *this_thread); 
	static DWORD fileformat_thread_run(CPsrutiDlg *this_thread); 
	static DWORD count_in_thread_run(CPsrutiDlg *this_thread);
	static DWORD fill_lyric_thread_run(CPsrutiDlg *this_thread);

	StartBeatFolderDlg *count_in_dlg;
	FillLyricMethodDlg *fill_lyric_dlg;


	HANDLE hThread;
	DWORD threadID;

public:
	CPsrutiDlg(CWnd* pParent = NULL);	// Standard-Konstruktor
	~CPsrutiDlg();
	void fill_sourcefile_list_from_command_line();

	static Log *lf;
	char* command_line;

	char sourcefile[MAX_PATH+512];
	char destfile[MAX_PATH+512];

	char chordfile[MAX_PATH];
	char lyricfile[MAX_PATH];
	CString destination;
	static IniFile* o_inifile;

	static CString hlpfilename_germ;
	static CString hlpfilename_eng;

	CString hlpfile_germ;
	CString hlpfile_eng;

	HCURSOR hCursorOld;
	HCURSOR hCursorWait;

// Dialogfelddaten
	//{{AFX_DATA(CPsrutiDlg)
	enum { IDD = IDD_PSRUTI_DIALOG };
	CButton	m_convert_gm;
	CButton	m_source_close;
	CButton	m_drums;
	CButton	m_preferences;
	CButton	m_file_format;
	CButton	m_save;
	CButton	m_chord_lyric_editor;
	CButton	m_quantisize_lyrics;
	CButton	m_exchange_channels;
	CButton	m_extras;
	CButton	m_controller_effects;
	CButton	m_chords_lyrics_import_export;
	CButton	m_lyrics_at_channel_notes;
	CButton	m_undo;
	CButton	m_revoicing;
	CButton	m_print;
	CButton	m_start_beat;
	CButton	m_vel_compress;
	CButton	m_quantisize_chords;
	CButton	m_play;
	CButton	m_select_fill_lyrics_linefeed;
	CButton	m_insert_fill_lyrics;
	CButton	m_compute_chords;
	CButton	m_lyric_import_export;
	CButton	m_chords_import_export;
	CButton	m_sysex_import_export;
	CButton	m_expr_mvolume;
	CButton	m_language;
	CButton	m_help;
	CButton	m_save_as;
	CButton	m_tempo;
	CButton	m_transpose;
	CButton	m_xg_convert;
	CButton	m_exit;
	CButton	m_selectsource;
	CButton	m_info;
	CButton	m_sourcebutton;
	CButton	m_events;
	CString	m_filename;
	CString	m_destination;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CPsrutiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
private:
	DynArray sourcefile_list;
	int sourcefile_list_index;
	void load_dropped_file(char* source);
	void initialize_source();
	void set_new_sourcefile(CString new_sourcefile);
	bool ask_for_revoicefile(char* revoicefile);
	bool ask_for_drumfile(char* drumfile);
	void xg_convert_folder();
	void xg_convert_folder_file(CString midifile,CString dest_path);
	void gm_convert_folder();
	void gm_convert_folder_file(CString midifile,CString dest_path);
	void revoicefile_folder();
	bool drum_folder_file(CString midifile,char* drumfile,CString dest_path);
	void revoicefile_folder_file(CString midifile, char* revoicefile, CString dest_path);
	void CPsrutiDlg::drum_folder();
	void print_folder();
	void print_folder_file(CString midifile,CString dest_path);
	void fileformat_folder();
	void fileformat_folder_file(CString midifile,CStdioFile *pf_f);
	void count_in_folder();
	void count_in_folder_file(CString midifile,CString dest_path,bool start_beat_delete,
								 int time_first_note, int drum, int velocity, 
								 bool on_all_beats,bool only_one_measure);
	void fill_lyric_folder();
	void fill_lyric_folder_file(CString midifile, CString dest_path, int method);

public:
	bool batch_running;

	bool xg_convert_folder_running;
	bool xg_convert_folder_abort_wanted;
	bool gm_convert_folder_running;
	bool gm_convert_folder_abort_wanted;
	bool revoicefile_folder_running;
	bool revoicefile_folder_abort_wanted;
	bool print_folder_running;
	bool print_folder_abort_wanted;
	bool fileformat_folder_running;
	bool fileformat_folder_abort_wanted;
	bool count_in_folder_running;
	bool count_in_folder_abort_wanted;
	bool expr_main_volume_folder_running;
	bool expr_main_volume_folder_abort_wanted;
	bool fill_lyric_folder_running;
	bool fill_lyric_folder_abort_wanted;
	bool drum_folder_running;
	bool drum_folder_abort_wanted;
	bool from_close;


protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CPsrutiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnInfo();
	afx_msg void OnTranspose();
	afx_msg void OnInsertChords();
	afx_msg void OnHelp();
	afx_msg void OnLanguage();
	afx_msg void OnClose();
	virtual void OnOK();
	afx_msg void OnSaveAs();
	afx_msg void OnSelectsource();
	afx_msg void OnFilllyrics();
	afx_msg void OnSelectFillLyricsLinefeed();
	afx_msg void OnXgConvert();
	afx_msg void OnTempo();
	afx_msg void OnVolume();
	afx_msg void OnPlayButton();
	afx_msg void OnPrint();
	afx_msg void OnStartBeat();
	afx_msg void OnQuantisizeChords();
	afx_msg void OnVelCompress();
	afx_msg void OnRevoicing();
	afx_msg void OnUndo();
	afx_msg void OnSysex();
	afx_msg void OnLyricsAtChannelNotes();
	afx_msg void OnChordsLyricsImportExport();
	afx_msg void OnController();
	afx_msg void OnExtras();
	afx_msg void OnExchangeChannels();
	afx_msg void OnQuantisizeLyrics();
	afx_msg void OnLyricsChordsEditor();
	afx_msg void OnSave();
	afx_msg void OnFileFormat();
	afx_msg void OnPreferences();
	afx_msg void OnSourceClose();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnDrums();
	afx_msg void OnGmConvert();
	afx_msg void OnDeleteFillLyrics();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_PSRMIDIDLG_H__F24E2687_C3E6_11D5_9348_0080AD7896CF__INCLUDED_)
