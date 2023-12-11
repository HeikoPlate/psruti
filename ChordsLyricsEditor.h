#if !defined(AFX_CHORDSLYRICSEDITOR_H__5F8BC986_D015_461A_9EF5_1AA7D63CD3D7__INCLUDED_)
#define AFX_CHORDSLYRICSEDITOR_H__5F8BC986_D015_461A_9EF5_1AA7D63CD3D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChordsLyricsEditor.h : Header-Datei
//

#include "MyArrays.h" 
#include "LyricFrame.h"

// Play Monitor

class MY_EDIT_PLAY_MONITOR : public HP_PLAY_MONITOR
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
// Dialogfeld CChordsLyricsEditor 


class CChordsLyricsEditor : public CDialog
{
// Konstruktion

#define	MAX_LYRIC_LINES 1000

public:
	CChordsLyricsEditor(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CChordsLyricsEditor)
	enum { IDD = IDD_CHORDS_LYRICS_EDITOR_DLG };
	CButton	m_select_words;
	CListBox	m_lyric_lines_box;
	CSliderCtrl	m_zoom_slider;
	CComboBox	m_chord_raster_combo;
	CSliderCtrl	m_edit_slider_tempo;
	CEdit m_chord_lyric_syllable;
	CButton	m_cancel;
	CButton	m_ok;
	CSliderCtrl	m_edit_slider_time;
	CButton	m_edit_stop;
	CButton	m_edit_play;
	CSliderCtrl	m_rgn_slider;
	CButton	m_select_lyric_lines;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CChordsLyricsEditor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CChordsLyricsEditor)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnCustomdrawRgnSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditPlay();
	afx_msg void OnEditStop();
	afx_msg void OnReleasedcaptureEditSliderTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawEditSliderTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditSliderPos();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEditDefaultTempo();
	afx_msg void OnCustomdrawEditSliderTempo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureEditSliderTempo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSelchangeChordRasterCombo();
	afx_msg void OnCustomdrawZoomSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnInitZoom();
	afx_msg void OnSelectLyricLines();
	afx_msg void OnSelectWordsSyllables();
	afx_msg void OnStartRecord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	HPMF_Interface *hpmfi;
	LyricChordEditArray lce_array;
	Log *logf;
	IniFile *o_inifile;
	HP_MIDIFILE_MODULE* mf;
	char linefeed_char;

private:
	int rgn_x1;	// upper-left corner
	int rgn_y1;
	int rgn_x2;	// lower_right corner
	int rgn_y2;
	int height_of_text_line;
	int chord_y;			// upper-left corner y of chords
	int lyric_y;			// upper-left corner y of lyrics
	int linefeed_y;			// upper-left corner y of single linefeeds
	int m_x, m_y, m_h, m_w;	// relative to m_memDC
	int pos_x, pos_y;		// positions of region


	static const COLORREF color_lyric;
	static const COLORREF color_chord;
	static const COLORREF color_black;
	static const COLORREF color_green;
	static const COLORREF color_lyric_light;
	static const COLORREF color_chord_light;

	// range of zoom slider from 0 to max_zoom
	static const int max_zoom;

	static const double max_factor;
	double init_zoom_factor;

	static int max_rel_time_in_rgn_init;
	static int rel_pos_act_time_in_rgn_init;
	int max_rel_time_in_rgn;
	int rel_pos_act_time_in_rgn;
	int left_time_in_rgn;
	int right_time_in_rgn;
	int play_time;

	CString lyric_event_text;
	int new_edit_slider_time;

	LyricChordEditElement lce_elem;

	LOGFONT lf;
	HFONT hfont;
	CFont* cfont;
	CFont* def_font;
	
	HICON hIcon_play;
	HICON hIcon_stop;
	HICON hIcon_pause;
	HICON hIcon_record_red;
	HICON hIcon_record_yellow;
	HICON hIcon_record_green;


	int lenx;
	bool signal_record_text;

	CDC *dc;
	CBrush white;
	CBrush red;
	CRgn rgn;
	bool l_button_down;
	bool l_button_paste_down;
	bool rasterize;
	RECORD_CHORD_LYRIC_ELEM record_chord_lyric_list[NO_CHORDS_LYRICS];
	int record_lyric_length;

	// Recording from Lyric Textfile
	CString lyric_file;
	CString lyric_event_array[NO_CHORDS_LYRICS]; 
	int lyric_event_array_len; //actual length
	int actual_lyric_event_array_index;	

	bool is_lyric_record;
	CStdioFile *cf_f;
	CFileException e;

	CString lyric_list[MAX_LYRIC_LINES];
	int list_number;
	int line_number;
	
	bool is_pause;
	bool is_record;
	bool load_lyric_file();
	bool fill_lyric_list();
	bool lyricline_check_and_add_words_in_list(CString line);

	int scroll_pos;
	int chord_raster_ticks;

	CDC m_memDC;
 	CBitmap m_bmp;
	CBrush  m_bkbrush;
	CPen m_cpen_black;
	CPen m_cpen_grey;
	CPen m_cpen_green;
	CWnd * wnd;
	CClientDC *pdc;

	int last_time;	// last time of midifile
	int clicked_array_index;
	int act_time;	// act_time to display rgn
	bool is_lyric_insert;

	virtual BOOL PreTranslateMessage(MSG* pMSG);
	void InitDisplay(CWnd *Wnd);
	void FillRgn();
	void Lines();
	void SetText(int array_i, int x, CString text);
	void PlayLine();
	void set_meas_no_in_rgn(CString meas_cstr,int x,int y,COLORREF crColor, int width);
	void Chords_Lyrics();
	int	 compute_rgn_x(int rgn_time);
	int	 compute_rgn_x_midi_time(int time);
	int	 compute_rgn_time(int x);
	int	 compute_midi_time_from_x(int x);
	void blit();

	UINT_PTR m_nTimer;
	MY_EDIT_PLAY_MONITOR pm;
	void set_edit_tempo(); 

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_CHORDSLYRICSEDITOR_H__5F8BC986_D015_461A_9EF5_1AA7D63CD3D7__INCLUDED_
