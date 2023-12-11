/*
Module : LyricFrame.h
Purpose: Defines the header implementation for the LyricFrame class
*/

#ifndef LYRICFRAME_H
#define LYRICFRAME_H

#define  NO_FRAME_LINES	   6
#define  FRAME_LINE_SWITCH 5
#define  NO_FRAME_CHARS   47
#define  NO_LYRICS_LINE   50

#define  NO_LIST_LINES  1000


#define  START_X           8


class LyricFrame
{

public:

	typedef struct lyricframe_elem
	{
		int  time;
		char *chord;	// chord_text
		char *lyric;	// lyric syllable
		int char_pos;   // pos in line (character number)
		int x;			// pos in line (pixel)
		bool c_printed;
		bool l_printed;
	} LYRICFRAME_ELEM;

//	LYRICFRAME_ELEM **lyricframelist;

	LYRICFRAME_ELEM lyricframelist[NO_LIST_LINES][NO_LYRICS_LINE];

	int no_lyric_lines;
	int l_no;
	int syll_no;
	Log *logf;

	char* last_lightened_lyric;
	int last_lightened_lyric_line;
	int last_lightened_lyric_x;

	char* last_lightened_chord;
	int last_lightened_chord_line;
	int last_lightened_chord_x;

	int m_x,m_y,m_h,m_w;
	CDC m_memDC;
	
	static const int char_width_lyric;
	static const int char_width_chord;
	static const COLORREF color_lyric;
	static const COLORREF color_chord;
	static const COLORREF color_lyric_light;
	static const COLORREF color_chord_light;

	char line_map[NO_LIST_LINES];
		// line l of lyricframe displays line line_map[l] of lyriclist. Default -1

	int ly_of_line(int line);
	int cy_of_line(int line);

	void display_title(char* songname, char* copyrightname, char* composername, char* lyricistname);

	// functions called from MY_PLAY_MONITOR callbacks
	void display_next_lyric(char *lyric);
	void display_next_chord(char *chord);
	void initialize_first_frame(int lineno, int syllno);
	void display_next_frame();
	void posit_time(int new_time);
	void blit();

protected:
	CBitmap m_bmp;
	CBrush  m_bkbrush;
	CWnd * wnd;
	CClientDC *pdc;
public:
	LyricFrame();
	~LyricFrame();

	CString songname;

	InitDisplay(CWnd *Wnd,int xp,int yp,int wp,int hp);
	SetText(CString strText,int x,int y,COLORREF crColor, int width, bool with_bitblt);
	EraseText(CString strText,int x,int y,int width);
	EraseRegion();
	void print(CString protfile, bool show, bool with_xfchords);
};

#endif